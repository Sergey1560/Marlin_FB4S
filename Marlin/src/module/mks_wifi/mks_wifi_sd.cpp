#include "mks_wifi_sd.h"

#include "../../libs/fatfs/ff.h"

FRESULT result;
FATFS FATFS_Obj;
FIL upload_file;


volatile uint8_t __attribute__ ((aligned (4))) dma_buff1[1030];
volatile uint8_t __attribute__ ((aligned (4))) dma_buff2[1030];
volatile uint8_t dma_buff_index=0;
volatile uint8_t *dma_buff_ptr;
volatile uint32_t dma_timeout;
volatile uint8_t *save;
volatile uint16_t data_size;

void mks_wifi_sd_init(void){
   CardReader::release();

   result = f_mount((FATFS *)&FATFS_Obj, "0", 1);
   DEBUG("SD init %d",result);
}

void mks_wifi_sd_deinit(void){
   f_mount(0, "", 0);                   
   CardReader::mount();
};

void sd_delete_file(char *filename){

   mks_wifi_sd_init();
   DEBUG("Remove %s",filename);
   f_unlink(filename);

   mks_wifi_sd_deinit();
}


void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet){
	char str[100];
   UINT bytes_writen=0;
	uint32_t file_size, file_inc_size;
   uint32_t dma_count;
   uint32_t usart1_brr;
   
   FRESULT res;

   //Установить имя файла. Смещение на 3 байта, чтобы добавить путь к диску
   str[0]='0';
   str[1]=':';
   str[2]='/';

   memcpy((uint8_t *)str+3,(uint8_t *)&packet->data[5],(packet->dataLen - 5));
   str[packet->dataLen - 5 + 3] = 0; 
 
   //Установить размер файла
   file_size=(packet->data[4] << 24) | (packet->data[3] << 16) | (packet->data[2] << 8) | packet->data[1];
   
   DEBUG("Start file %s size %d",str,file_size);
   
   //Отмонтировать SD от Marlin, Монтировать FATFs 
   mks_wifi_sd_init();
   
   //открыть файл для записи
   f_open((FIL *)&upload_file,str,FA_CREATE_ALWAYS | FA_WRITE);

   //Выключить прием по UART RX, включить через DMA, изменить скорость, Выставить флаг приема по DMA
   USART1->CR1 = 0;

   WRITE(MKS_WIFI_IO4, LOW);
   safe_delay(200); 
   usart1_brr = USART1->BRR;

   USART1->CR1 = USART_CR1_UE;
   USART1->BRR = 0x25;
   USART1->CR2 = 0;
   USART1->CR3 = USART_CR3_DMAR;
   USART1->CR1 |= USART_CR1_RE;


   (void)USART1->DR;

   dma_buff_ptr=(uint8_t*)&dma_buff1;
   dma_buff_index=0;

   safe_delay(200);
   USART1->SR &= ~USART_SR_RXNE;

   DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC;
   DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
   DMA1_Channel5->CMAR = (uint32_t)dma_buff_ptr;
   DMA1_Channel5->CNDTR = 1024;
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR |= DMA_CCR_EN;
   

   dma_count=0;
   dma_timeout = DMA_TIMEOUT;
   while(dma_timeout > 0){

      if(DMA1->ISR & DMA_ISR_TCIF5){
         DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   
         DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC;
         DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
         if(dma_buff_index == 0){
            dma_buff_index=1;
            dma_buff_ptr=(uint8_t*)&dma_buff2;
            save=(uint8_t*)&dma_buff1;
         }else{
            dma_buff_index=0;
            dma_buff_ptr=(uint8_t*)&dma_buff1;
            save=(uint8_t*)&dma_buff2;
         }  
         DMA1_Channel5->CMAR = (uint32_t)dma_buff_ptr;
         DMA1_Channel5->CNDTR = 1024;
         DMA1_Channel5->CCR |= DMA_CCR_EN;

       	WRITE(MKS_WIFI_IO4, HIGH);

         data_size = (*(save+3) << 8) | *(save+2);
         DEBUG("[%d]Save %d bytes",dma_count,data_size);

         res=f_write((FIL *)&upload_file,(uint8_t*)(save+8),(data_size-4),&bytes_writen);
         if(res){
            ERROR("Write err %d",res);
            break;
         }
         
         f_sync((FIL *)&upload_file);
         WRITE(MKS_WIFI_IO4, LOW);
         memset((uint8_t*)save,0,1024);
         dma_count++;
         dma_timeout = DMA_TIMEOUT;

      }

      if(DMA1->ISR & DMA_ISR_TEIF5){
         ERROR("DMA Error");
      }
      
      dma_timeout=dma_timeout-1;
   }
   
   f_close((FIL *)&upload_file);

   USART1->CR1 = 0;
   USART1->CR1 = (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
   USART1->CR3 = 0;
   USART1->BRR = usart1_brr;
   USART1->CR1 |= USART_CR1_UE;

   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR = 0;
   DMA1_Channel5->CPAR = 0;
   DMA1_Channel5->CMAR = 0;
   DMA1_Channel5->CNDTR = 0;

   mks_wifi_sd_deinit();
   DEBUG("Settings restored");

}
