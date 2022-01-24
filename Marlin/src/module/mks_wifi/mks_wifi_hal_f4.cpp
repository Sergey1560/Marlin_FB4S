#include "mks_wifi_hal_f4.h"

#ifdef STM32F4
volatile unsigned char *buff;
volatile unsigned char buffer_ready;
volatile unsigned char dma_stopped;

volatile __attribute__ ((aligned (4)))  unsigned int *dma_buff[2];
volatile unsigned char dma_buff_index=0;


void mks_wifi_hw_prepare(unsigned int buf, unsigned int count){
   //На время передачи отключение systick
   SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

   RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
   RCC->APB2ENR &= ~RCC_APB2ENR_TIM10EN;

   RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
   RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

   USART1->CR1 = USART_CR1_UE;
   USART1->CR1 = USART_CR1_TE | USART_CR1_UE;
   USART1->BRR = (uint32_t)(84000000+1958400/2)/1958400;
   USART1->CR2 = 0;
   USART1->CR3 = USART_CR3_DMAR;
   USART1->SR = 0;
   USART1->CR1 |= USART_CR1_RE;

   DMA2_Stream5->CR = 0;
   DMA2->HIFCR=DMA_S5_CLEAR;
   
   DMA2_Stream5->PAR = (uint32_t)&USART1->DR;
   DMA2_Stream5->M0AR = (uint32_t)buf;
   DMA2_Stream5->NDTR = count;
   
   DMA2_Stream5->CR = DMA_CONF|DMA_SxCR_EN;

   NVIC_EnableIRQ(DMA2_Stream5_IRQn);
};

void mks_wifi_disable_dma(void){
   DMA2->HIFCR=DMA_S5_CLEAR;
   DMA2_Stream5->CR = 0;
}

void mks_wifi_empty_uart(void){
    while(USART1->SR & USART_SR_RXNE){
        (void)USART1->DR;
    };
}

void wd_reset(void){
   HAL_watchdog_refresh();
}

void mks_wifi_hw_restore(void){
   RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
   RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;

   SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void mks_wifi_sys_rst(void){
   NVIC_SystemReset();
};


extern "C" void DMA2_Stream5_IRQHandler(void){

      if(DMA2->HISR & DMA_HISR_TEIF5){
         DEBUG("DMA Error");
         dma_stopped = 2;
         DMA2->HIFCR=DMA_S5_CLEAR;
         return;
      }
      
      if(buffer_ready > 0){ 
         GPIOC->BSRR = GPIO_BSRR_BS7;  //остановить передачу от esp
         dma_stopped=1;
      };

      DMA2->HIFCR=DMA_S5_CLEAR;
      //Указатель на полученный буфер
      buff=(unsigned char*)dma_buff[dma_buff_index];
      //переключить индекс
      dma_buff_index = (dma_buff_index) ? 0 : 1;


      DMA2_Stream5->CR = DMA_CONF;
      DMA2_Stream5->M0AR = (uint32_t)dma_buff[dma_buff_index];
      DMA2_Stream5->NDTR = ESP_PACKET_SIZE;
      DMA2_Stream5->CR = DMA_CONF|DMA_SxCR_EN;

      ++buffer_ready;
}

#endif