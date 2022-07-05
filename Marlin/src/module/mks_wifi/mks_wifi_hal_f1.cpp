#include "mks_wifi_hal_f1.h"
#include "../../libs/Segger/log.h"


#ifdef STM32F1

#ifdef MAPLE_STM32F1
#include "stm32f103xe.h"
#else
#include "../../MarlinCore.h"
#endif

volatile unsigned char *buff;
volatile unsigned char buffer_ready;
volatile unsigned char dma_stopped;

volatile __attribute__ ((aligned (4)))  unsigned int *dma_buff[2];
volatile unsigned char dma_buff_index=0;


void mks_wifi_hw_prepare(unsigned int buf, unsigned int count){
   //На время передачи отключение systick
   SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

   //Отключение тактирования не используемых блоков
   RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN|RCC_APB1ENR_TIM4EN);
   RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN|RCC_APB1ENR_USART3EN);
   RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
   RCC->AHBENR &= ~(RCC_AHBENR_FSMCEN);

   //Максимальная частота в режиме out
   GPIOC->CRL |= GPIO_CRL_MODE7;
   GPIOC->CRL &= ~GPIO_CRL_CNF7;

   RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
   RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

   USART1->CR1 = USART_CR1_UE;
   USART1->BRR = 0x25;
   USART1->CR2 = 0;
   USART1->CR3 = USART_CR3_DMAR;
   USART1->SR = 0;
   USART1->CR1 |= USART_CR1_RE;

   DMA1_Channel5->CCR = DMA_CONF;
   DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
   DMA1_Channel5->CMAR = (uint32_t)buf;   //dma_buff[dma_buff_index];
   DMA1_Channel5->CNDTR = count; //ESP_PACKET_SIZE;
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR = DMA_CONF|DMA_CCR_EN;

   NVIC_EnableIRQ(DMA1_Channel5_IRQn);
   // DEBUG("Start DMA %0X / %d",buf, count);
   // DEBUG("CCRR %0X",DMA1_Channel5->CCR);
   // DEBUG("CMAR %0X",DMA1_Channel5->CMAR);
   // DEBUG("CPAR %0X",DMA1_Channel5->CPAR);
   // DEBUG("NDTR %0X",DMA1_Channel5->CNDTR);
   // DEBUG("IFC %0X",DMA1->IFCR);

   // DEBUG("USART CR1 %0X",USART1->CR1);
   // DEBUG("CR2 %0X",USART1->CR2);
   // DEBUG("CR3 %0X",USART1->CR3);
   // DEBUG("BRR %0X",USART1->BRR);
   // DEBUG("SR %0X",USART1->SR);
}


void mks_wifi_hw_restore(void){
   //Включение обратно переферии
   SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
   RCC->APB1ENR |= (RCC_APB1ENR_TIM5EN|RCC_APB1ENR_TIM4EN);
   RCC->APB1ENR |= (RCC_APB1ENR_SPI2EN|RCC_APB1ENR_USART3EN);
   RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
   RCC->AHBENR |= (RCC_AHBENR_FSMCEN);
}


void mks_wifi_disable_dma(void){
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR = 0;
   NVIC_DisableIRQ(DMA1_Channel5_IRQn);
}

void mks_wifi_empty_uart(void){
    while(USART1->SR & USART_SR_RXNE){
        (void)USART1->DR;
    };
}

void wd_reset(void){
   #ifdef MAPLE_STM32F1
   IWDG->KR = 0xAAAA;
   #else
   hal.watchdog_refresh();
   #endif
}

#ifdef MAPLE_STM32F1
extern "C" void __irq_dma1_channel5(void) {
#else
extern "C" void DMA1_Channel5_IRQHandler(void){
#endif
      if(DMA1->ISR & DMA_ISR_TEIF5){
         DEBUG("DMA Error");
         dma_stopped = 2;
         DMA1->IFCR = DMA_CLEAR;
         return;
      }
      
      if(buffer_ready > 0){ 
         GPIOC->BSRR = GPIO_BSRR_BS7;  //остановить передачу от esp
         dma_stopped=1;
      };

      DMA1->IFCR = DMA_CLEAR;
      //Указатель на полученный буфер
      buff=(unsigned char*)dma_buff[dma_buff_index];
      //переключить индекс
      dma_buff_index = (dma_buff_index) ? 0 : 1;

      DMA1_Channel5->CCR = DMA_CONF;
      DMA1_Channel5->CMAR = (uint32_t)dma_buff[dma_buff_index];
      DMA1_Channel5->CNDTR = ESP_PACKET_SIZE;
      DMA1_Channel5->CCR = DMA_CONF|DMA_CCR_EN;
      ++buffer_ready;
}


void mks_wifi_sys_rst(void){

   #ifdef MAPLE_STM32F1
   asm volatile ("dsb 0xF":::"memory");
   SCB->AIRCR  = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)|(SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk)|SCB_AIRCR_SYSRESETREQ_Msk);
   asm volatile ("dsb 0xF":::"memory");
   while(1);
   #else
   NVIC_SystemReset();
   #endif

};


#ifdef MAPLE_STM32F1
#define __NVIC_PRIO_BITS          4U

void NVIC_SetPriority(int IRQn, unsigned int priority){
  if ((int)(IRQn) < 0){
    SCB->SHP[(((unsigned int)(int)IRQn) & 0xFUL)-4UL] = (unsigned char)((priority << (8U - __NVIC_PRIO_BITS)) & (unsigned int)0xFFUL);
  }else{
    NVIC->IP[((unsigned int)(int)IRQn)]               = (unsigned char)((priority << (8U - __NVIC_PRIO_BITS)) & (unsigned int)0xFFUL);
  }
}

void NVIC_EnableIRQ(int IRQn){
  NVIC->ISER[(((unsigned int)(int)IRQn) >> 5UL)] = (unsigned int)(1UL << (((unsigned int)(int)IRQn) & 0x1FUL));
}

void NVIC_DisableIRQ(int IRQn){
  NVIC->ICER[(((unsigned int)(int)IRQn) >> 5UL)] = (unsigned int)(1UL << (((unsigned int)(int)IRQn) & 0x1FUL));
}

#endif

#endif