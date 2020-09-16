#include "mks_wifi_sd.h"



#include "../../MarlinCore.h"
#include "../../lcd/ultralcd.h"
#include "../../libs/fatfs/ff.h"
#include "../../libs/buzzer.h"  
#include "../temperature.h"
#include "../../libs/fatfs/fatfs_shared.h"

#ifdef MKS_WIFI

#if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)
#include "mks_wifi_ui.h"
#endif

volatile uint8_t *file_buff=shared_mem;
volatile uint8_t *file_buff_pos;
volatile uint16_t file_data_size;

volatile uint8_t *dma_buff1=file_buff+FILE_BUFFER_SIZE;
volatile uint8_t *dma_buff2=dma_buff1+ESP_PACKET_SIZE;
volatile uint8_t *dma_buff[] = {dma_buff1,dma_buff2};
volatile uint8_t dma_buff_index=0;
volatile uint8_t *buff;

FIL upload_file;

void mks_wifi_sd_ls(void){
    res = f_opendir(&dir, "0:");                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
                DEBUG("%s\n", fno.fname);
            }
       }else{
          ERROR("Opendir error %d",res);
      }
   f_closedir(&dir);
}

uint8_t mks_wifi_sd_init(void){
   CardReader::release();
   res = f_mount((FATFS *)&FATFS_Obj, "0", 1);
   DEBUG("SD init result:%d",res);
   return (uint8_t)res;
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

/*
Ищет файл filename и возвращает 8.3 имя в dosfilename
Возвращаемое значение 1 если нашлось, 0 если нет
*/

uint8_t get_dos_filename(char *filename, char* dosfilename){
    uint8_t ret_val=0;
   
   mks_wifi_sd_init();

    res = f_opendir(&dir, "0:");                       /* Open the directory */
    
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            
            if(!strcmp(fno.fname,filename)){
               DEBUG("Found %s %s\n", fno.fname, fno.altname);
               strncpy(dosfilename,fno.altname,13);
               ret_val = 1;
            }
                
            }
       }else{
          ERROR("Opendir error %d",res);
      }
   f_closedir(&dir);

   mks_wifi_sd_deinit();

   return ret_val;
}



void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet){
	char str[100];
   UINT bytes_writen=0;
	uint32_t file_size, file_inc_size, file_size_writen;

   uint16_t in_sector;
   uint16_t last_sector;

   uint32_t usart1_brr;
   volatile uint32_t dma_timeout;
   uint16_t data_size;
   int16_t save_bed,save_e0;

   char file_name[100];

   save_bed=thermalManager.degTargetBed();
   save_e0=thermalManager.degTargetHotend(0);
   
   DEBUG("Saved target temp E0 %d Bed %d",save_e0,save_bed);
   
   thermalManager.setTargetBed(0);
   thermalManager.setTargetHotend(0,0);
   OUT_WRITE(HEATER_1_PIN,HIGH);
   //safe_delay(10);

 	//Установить имя файла. Смещение на 3 байта, чтобы добавить путь к диску
   file_name[0]='0';
   file_name[1]=':';
   file_name[2]='/';

   memcpy((uint8_t *)file_name+3,(uint8_t *)&packet->data[5],(packet->dataLen - 5));
   file_name[packet->dataLen - 5 + 3] = 0; 

   file_size=(packet->data[4] << 24) | (packet->data[3] << 16) | (packet->data[2] << 8) | packet->data[1];
   DEBUG("Start file %s size %d",str,file_size);
   
   //Отмонтировать SD от Marlin, Монтировать FATFs 
   if(mks_wifi_sd_init()){
      ERROR("Error SD mount");
      ui.set_status((const char *)"Error SD mount",true);
      ui.update();
      mks_wifi_sd_deinit();
      return;
   }
   
   //открыть файл для записи
   res=f_open((FIL *)&upload_file,file_name,FA_CREATE_ALWAYS | FA_WRITE);
   if(res){
      ERROR("File open error %d",res);
      ui.set_status((const char *)"File open error",true);
      ui.update();
      mks_wifi_sd_deinit();
      return;
   }

   #if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)
   mks_update_status(file_name+3,0,file_size);
   #endif   

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
   

   file_inc_size=0; //Счетчик принятых данных, для записи в файл
   file_size_writen = 0; //Счетчик записанных в файл данных
   file_data_size = 0;
   dma_timeout = DMA_TIMEOUT; //Тайм-аут, на случай если передача зависла.
   last_sector = 0;

   DEBUG("DMA1 buff: %0X", dma_buff[0]);
   DEBUG("DMA2 buff: %0X", dma_buff[1]);
   DEBUG("File buff: %0X size %d (%0X)", file_buff, FILE_BUFFER_SIZE, FILE_BUFFER_SIZE);

   while(dma_timeout-- > 0){

      if(DMA1->ISR & DMA_ISR_TCIF5){
         DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   
         //Указатель на полученный буфер
         buff=dma_buff[dma_buff_index];
         //переключить индекс
         dma_buff_index = (dma_buff_index) ? 0 : 1;

         //Запустить DMA на прием следующего пакета, пока обрабатывается этот
         DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC;
         DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
         DMA1_Channel5->CMAR = (uint32_t)dma_buff[dma_buff_index];
         DMA1_Channel5->CNDTR = ESP_PACKET_SIZE;
         DMA1_Channel5->CCR |= DMA_CCR_EN;

         if(*buff != ESP_PROTOC_HEAD){
            ERROR("Wrong packet head");
            break;
         }

         in_sector = (*(buff+5) << 8) | *(buff+4);
         if((in_sector - last_sector) > 1){
            ERROR("IN Sec: %d Prev sec: %d",in_sector,last_sector);
            break;
         }else{
            last_sector=in_sector;
         }

         data_size = (*(buff+3) << 8) | *(buff+2);
         data_size -= 4; //4 байта с номером сегмента и флагами

         //DEBUG("In sector: %d data_size: %d",in_sector,data_size);

         //Если буфер полон и писать некуда, запись в файл
         if((data_size + file_data_size) > FILE_BUFFER_SIZE){
           	
            WRITE(MKS_WIFI_IO4, HIGH); //Остановить передачу от ESP
            
            file_inc_size += file_data_size; 
            DEBUG("[%d]Save %d bytes (%d of %d) ",in_sector,file_data_size,file_inc_size,file_size);
            
            res=f_write((FIL *)&upload_file,(uint8_t*)file_buff,file_data_size,&bytes_writen);
            if(res){
               ERROR("Write err %d",res);
               break;
            }
            file_size_writen+=bytes_writen;
            res=f_sync((FIL *)&upload_file);
            if(res){
               ERROR("Fsync err %d",res);
               break;
            }
            
            #if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)
            mks_update_status(file_name+3,file_inc_size,file_size);
            #else
            sprintf(str,"Upload %ld%%",file_inc_size*100/file_size);
            ui.set_status((const char *)str,true);
            ui.update();
            #endif
            memset((uint8_t *)file_buff,0,FILE_BUFFER_SIZE);
            file_data_size=0;
            WRITE(MKS_WIFI_IO4, LOW); //Записано, сигнал ESP продолжать
         }
        

         if(*(buff+7) == 0x80){ //Последний пакет с данными
            DEBUG("Last packet");
            if(file_data_size != 0){ //В буфере что-то есть
               file_inc_size += file_data_size; 

               DEBUG("Save %d bytes from buffer (%d of %d) ",file_data_size,file_inc_size,file_size);
               res=f_write((FIL *)&upload_file,(uint8_t*)file_buff,file_data_size,&bytes_writen);
               if(res){
                  ERROR("Write err %d",res);
                  break;
               }
               file_size_writen+=bytes_writen;
            }   
           
            file_inc_size += data_size;
            DEBUG("Save %d bytes from dma (%d of %d) ",data_size,file_inc_size,file_size);
            res=f_write((FIL *)&upload_file,(uint8_t*)(buff+8),data_size,&bytes_writen);
            if(res){
               ERROR("Write err %d",res);
               break;
            }
            file_size_writen+=bytes_writen;
            
            f_sync((FIL *)&upload_file);
            break;
         }
         
         memcpy((uint8_t *)file_buff+file_data_size,(uint8_t*)(buff+8),data_size);
         file_data_size+=data_size;

         memset((uint8_t*)buff,0,ESP_PACKET_SIZE);
         dma_timeout = DMA_TIMEOUT;
      }

      if(DMA1->ISR & DMA_ISR_TEIF5){
         ERROR("DMA Error");
      }

   }
   
   f_close((FIL *)&upload_file);

   if( (file_size == file_inc_size) && (file_size == file_size_writen) ){
         #if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)
         mks_end_transmit();
         #endif
         ui.set_status((const char *)"Upload done",true);
         DEBUG("Upload ok");
         BUZZ(1000,260);

         if(!strcmp(file_name,"0:/Robin_Nano35.bin")){
            DEBUG("Firmware found, reboot");
            safe_delay(1000);
            nvic_sys_reset();
         }
   }else{
         #if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)
         mks_end_transmit();
         #endif
         ui.set_status((const char *)"Upload failed",true);
         DEBUG("Upload failed! File size: %d; Recieve %d; SD write %d",file_size,file_inc_size,file_size_writen);
         //Установить имя файла.
         str[0]='0';
         str[1]=':';
         str[2]='/';

         memcpy((uint8_t *)str+3,(uint8_t *)&packet->data[5],(packet->dataLen - 5));
         str[packet->dataLen - 5 + 3] = 0; 

         DEBUG("Rename file %s",file_name);
         f_rename(file_name,"file_failed.gcode");

         BUZZ(436,392);
         BUZZ(109,0);
         BUZZ(436,392);
         BUZZ(109,0);
         BUZZ(436,392);
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

   mks_wifi_sd_deinit();

   WRITE(MKS_WIFI_IO4, LOW); //Включить передачу от ESP 

   thermalManager.setTargetBed(save_bed);
   thermalManager.setTargetHotend(save_e0,0);
   DEBUG("Restore thermal settings E0:%d Bed:%d",save_bed,save_e0);
}

#endif