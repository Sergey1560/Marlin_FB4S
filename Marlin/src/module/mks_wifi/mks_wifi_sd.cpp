#include "mks_wifi_sd.h"

#include "../../lcd/ultralcd.h"
#include "../../libs/fatfs/ff.h"

FRESULT result;
FATFS FATFS_Obj;
FIL upload_file;

volatile uint8_t __attribute__ ((aligned (4))) dma_buff1[ESP_PACKET_SIZE];
volatile uint8_t __attribute__ ((aligned (4))) dma_buff2[ESP_PACKET_SIZE];
volatile uint8_t *dma_buff[] = {dma_buff1,dma_buff2};
volatile uint8_t dma_buff_index=0;
volatile uint8_t *buff;

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
	uint32_t file_size, file_inc_size, file_size_writen;
   uint32_t dma_count;
   uint32_t usart1_brr;
   uint32_t dma_timeout;
   uint16_t data_size;
   FRESULT res;

 	mks_wifi_sd_init();

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

   ui.set_status((const char *)"Upload file...",true);
   ui.update();

   //Выключить прием по UART RX, включить через DMA, изменить скорость, Выставить флаг приема по DMA
   USART1->CR1 = 0;

   safe_delay(100); 
   //Сохранение делителя, чтобы потом восстановить
   usart1_brr = USART1->BRR;

   USART1->CR1 = USART_CR1_UE;
   USART1->BRR = 0x25;
   USART1->CR2 = 0;
   USART1->CR3 = USART_CR3_DMAR;
   USART1->CR1 |= USART_CR1_RE;

   dma_buff_index=0;
   memset((uint8_t*)dma_buff[0],0,ESP_PACKET_SIZE);
   memset((uint8_t*)dma_buff[1],0,ESP_PACKET_SIZE);

   /*
   Прием пакета с данными начинается примерно через 2 секунды
   после переключения скорости.
   Без этой тупой задержки, UART успевает принять 
   мусор, до пакета с данными и все ломается
   */
   safe_delay(200);

   DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC;
   DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
   DMA1_Channel5->CMAR = (uint32_t)dma_buff[dma_buff_index];
   DMA1_Channel5->CNDTR = ESP_PACKET_SIZE;
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR |= DMA_CCR_EN;
   

   dma_count = 0; //Счетчик принятых пакетов через DMA. Для отладки
   file_inc_size=0; //Счетчик принятых данных, для записи в файл
   file_size_writen = 0; //Счетчик записанных в файл данных
   
   dma_timeout = DMA_TIMEOUT; //Тайм-аут, на случай если передача зависла.
   
   while(dma_timeout-- > 0){

      if(DMA1->ISR & DMA_ISR_TCIF5){
         DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   
         //Указатель на полученный буфер
         buff=dma_buff[dma_buff_index];
         //переключить индекс
         dma_buff_index = (dma_buff_index) ? 0 : 1;

         DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC;
         DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
         DMA1_Channel5->CMAR = (uint32_t)dma_buff[dma_buff_index];
         DMA1_Channel5->CNDTR = ESP_PACKET_SIZE;
         DMA1_Channel5->CCR |= DMA_CCR_EN;

       	WRITE(MKS_WIFI_IO4, HIGH); //Остановить передачу от ESP

         if(*buff != ESP_PROTOC_HEAD){
            ERROR("Wrong packet head");
            break;
         }

         data_size = (*(buff+3) << 8) | *(buff+2);
         file_inc_size += (data_size - 4); //4 байта с номером сегмента и флагами

         DEBUG("[%d]Save %d bytes (%d of %d) ",dma_count,data_size,file_inc_size,file_size);
         res=f_write((FIL *)&upload_file,(uint8_t*)(buff+8),(data_size-4),&bytes_writen);
         if(res){
            ERROR("Write err %d",res);
            break;
         }
         file_size_writen+=bytes_writen;
         f_sync((FIL *)&upload_file);

         sprintf(str,"Upload %ld%%",file_inc_size*100/file_size);
         ui.set_status((const char *)str,true);
         ui.update();

         WRITE(MKS_WIFI_IO4, LOW); //Записано, сигнал ESP продолжать


         if(*(buff+7) == 0x80){
            DEBUG("Last packet");
            break;
         }
         
         memset((uint8_t*)buff,0,ESP_PACKET_SIZE);
         dma_count++;
         dma_timeout = DMA_TIMEOUT;
      }

      if(DMA1->ISR & DMA_ISR_TEIF5){
         ERROR("DMA Error");
      }

   }
   
   f_close((FIL *)&upload_file);

   if( (file_size == file_inc_size) && (file_size == file_size_writen) ){
         ui.set_status((const char *)"Upload done",true);
         ui.update();
         DEBUG("Upload ok");
   }else{
         ui.set_status((const char *)"Upload failed",true);
         DEBUG("Upload failed: %d; Recieve %d; SD write %d",file_size,file_inc_size,file_size_writen);
   }
  

   //Восстановить USART1
   USART1->CR1 = 0;
   USART1->CR1 = (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
   USART1->CR3 = 0;
   USART1->BRR = usart1_brr;
   USART1->CR1 |= USART_CR1_UE;

   //Выключить DMA
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR = 0;
   DMA1_Channel5->CPAR = 0;
   DMA1_Channel5->CMAR = 0;
   DMA1_Channel5->CNDTR = 0;

   mks_wifi_sd_deinit();

   WRITE(MKS_WIFI_IO4, LOW); //Включить передачу от ESP 

   DEBUG("Settings restored");

}
