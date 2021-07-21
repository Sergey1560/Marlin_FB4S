#include "mks_wifi_sd.h"

#include "../../MarlinCore.h"
#include "../../lcd/marlinui.h"
#include "../../libs/fatfs/ff.h"
#include "../../libs/buzzer.h"  
#include "../temperature.h"
#include "../../libs/fatfs/fatfs_shared.h"
#include "uart.h"

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
    res = f_opendir((DIR*)&dir, "0:");                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir((DIR*)&dir,(FILINFO*) &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
                DEBUG("%s\n", fno.fname);
            }
       }else{
          ERROR("Opendir error %d",res);
      }
   f_closedir((DIR*)&dir);
}

uint8_t mks_wifi_sd_init(void){
   card.release();
   DEBUG("Card release");
   res = f_mount((FATFS *)&FATFS_Obj, "0", 1);
   DEBUG("SD init result:%d",res);
   return (uint8_t)res;
}

void mks_wifi_sd_deinit(void){
   DEBUG("Unmount SD");
   f_mount(0, "", 1);
   DEBUG("Marlin mount");
   card.mount();
   card.mount();
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

    res = f_opendir((DIR*)&dir, "0:");                       /* Open the directory */
    
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir((DIR*)&dir, (FILINFO*)&fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            
            if(!strcmp((char *)fno.fname,filename)){
               DEBUG("Found %s %s\n", fno.fname, fno.altname);
               strncpy(dosfilename,(char *)fno.altname,13);
               ret_val = 1;
            }
                
            }
       }else{
          ERROR("Opendir error %d",res);
      }
   f_closedir((DIR*)&dir);

   mks_wifi_sd_deinit();

   return ret_val;
}



void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet){
	char str[100];
   UINT bytes_writen=0;
	uint32_t file_size, file_inc_size, file_size_writen;

   uint16_t in_sector;
   uint16_t last_sector;

   volatile uint32_t dma_timeout;
   uint16_t data_size;
   int16_t save_bed,save_e0;

   uint32_t data_to_write=0;

   char file_name[100];

   save_bed=thermalManager.degTargetBed();
   save_e0=thermalManager.degTargetHotend(0);
   
   DEBUG("Saved target temp E0 %d Bed %d",save_e0,save_bed);
   
   thermalManager.setTargetBed(0);
   thermalManager.setTargetHotend(0,0);
   thermalManager.manage_heater();
   OUT_WRITE(FAN1_PIN,HIGH);
 	//Установить имя файла. Смещение на 3 байта, чтобы добавить путь к диску
   file_name[0]='0';
   file_name[1]=':';
   file_name[2]='/';

   memcpy((uint8_t *)file_name+3,(uint8_t *)&packet->data[5],(packet->dataLen - 5));
   file_name[packet->dataLen - 5 + 3] = 0; 

   file_size=(packet->data[4] << 24) | (packet->data[3] << 16) | (packet->data[2] << 8) | packet->data[1];
   DEBUG("Start file %s size %d",file_name,file_size);
   
   //Отмонтировать SD от Marlin, Монтировать FATFs 
   if(mks_wifi_sd_init()){
      ERROR("Error SD mount");
      ui.set_status((const char *)"Error SD mount",true);
      ui.update();
      mks_wifi_sd_deinit();
      return;
   }
   
   DEBUG("Open file");
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
      #ifdef SHOW_PROGRESS
      mks_update_status(file_name+3,0,file_size);
      #else
      mks_upload_screen();
      #endif
   #endif   

   dma_buff_index=0;
   file_inc_size=0; //Счетчик принятых данных, для записи в файл
   file_size_writen = 0; //Счетчик записанных в файл данных
   file_data_size = 0;
   dma_timeout = DMA_TIMEOUT; //Тайм-аут, на случай если передача зависла.
   last_sector = 0;


   DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC;
   DMA1_Channel5->CPAR = (uint32_t)&USART1->DR;
   DMA1_Channel5->CMAR = (uint32_t)dma_buff[dma_buff_index];
   DMA1_Channel5->CNDTR = ESP_PACKET_SIZE;
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR |= DMA_CCR_EN;

   USART1->CR1 = 0;
   USART1->BRR = 0x25;
   USART1->CR2 = 0;
   USART1->CR3 = USART_CR3_DMAR;
   USART1->SR = 0;

   safe_delay(200);
   USART1->CR1 = USART_CR1_RE | USART_CR1_UE;

   TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
   DEBUG("DMA1 buff: %0X", dma_buff[0]);
   DEBUG("DMA2 buff: %0X", dma_buff[1]);
   DEBUG("File buff: %0X size %d (%0X)", file_buff, FILE_BUFFER_SIZE, FILE_BUFFER_SIZE);

   while(dma_timeout-- > 0){

      TERN_(USE_WATCHDOG, HAL_watchdog_refresh());

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
         DMA1_Channel5->CCR = DMA_CCR_PL|DMA_CCR_MINC|DMA_CCR_EN;

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

         data_to_write = file_data_size / 512;
         data_to_write = data_to_write * 512;

         //DEBUG("In[%d] d_size: %d f_size: %d to_w: %d",in_sector,data_size,file_data_size,data_to_write);

         //Если буфер полон и писать некуда, запись в файл
         if((data_size + file_data_size) > FILE_BUFFER_SIZE){
            WRITE(MKS_WIFI_IO4, HIGH); //Остановить передачу от ESP

            file_inc_size += data_to_write; 
            DEBUG("[%d]Save %d bytes (%d of %d) ",in_sector,data_to_write,file_inc_size,file_size);
            
            res=f_write((FIL *)&upload_file,(uint8_t*)file_buff,data_to_write,&bytes_writen);
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
               #ifdef SHOW_PROGRESS
               mks_update_status(file_name+3,file_inc_size,file_size);
               #endif
            #else
            sprintf(str,"Upload %ld%%",file_inc_size*100/file_size);
            ui.set_status((const char *)str,true);
            ui.update();
            #endif
            file_data_size = file_data_size - data_to_write;
            
            memcpy((uint8_t *)file_buff,(uint8_t *)(file_buff+data_to_write),file_data_size);
            WRITE(MKS_WIFI_IO4, LOW); //Записано, сигнал ESP продолжать
         }

         //DEBUG("Check in_sector %d data %d filesize %d",in_sector,data_size,file_size);

         if(in_sector == 0){
            if(data_size == file_size){
               DEBUG("1-packet file");
               *(buff+7) = 0x80;
            }
         }

         if(*(buff+7) == 0x80){ //Последний пакет с данными
            WRITE(MKS_WIFI_IO4, HIGH); //Остановить передачу от ESP
            DEBUG("Last packet");
            if(file_data_size != 0){ //В буфере что-то есть
               file_inc_size += file_data_size; 

               DEBUG("Save last %d bytes from buffer (%d of %d) ",file_data_size,file_inc_size,file_size);
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

         //memset((uint8_t*)buff,0,ESP_PACKET_SIZE);
         dma_timeout = DMA_TIMEOUT;
      }

      if(DMA1->ISR & DMA_ISR_TEIF5){
         ERROR("DMA Error");
         break;
      }

   }
   
   if(dma_timeout == 0){
      DEBUG("End of while by timeout, NDTR: %d",DMA1_Channel5->CNDTR);
   }
   //Выключить DMA
   DMA1->IFCR = DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5;
   DMA1_Channel5->CCR = 0;

   MYSERIAL2.begin(BAUDRATE_2);

   TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
   f_close((FIL *)&upload_file);
   DEBUG("File closed");

   if( (file_size == file_inc_size) && (file_size == file_size_writen) ){
         TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
         mks_wifi_sd_deinit();
         DEBUG("Remount SD");

         #if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)
         mks_end_transmit();
         #endif
         ui.set_status((const char *)"Upload done",true);
         DEBUG("Upload ok");
         BUZZ(1000,260);

         if(!strcmp(file_name,"0:/Robin_Nano35.bin")){
            TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
            DEBUG("Firmware found, reboot");
            safe_delay(1000);
            NVIC_SystemReset();
         }
   }else{
         TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
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

         TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
         mks_wifi_sd_deinit();
         DEBUG("Remount SD");

         BUZZ(436,392);
         BUZZ(109,0);
         BUZZ(436,392);
         BUZZ(109,0);
         BUZZ(436,392);
   }


   TERN_(USE_WATCHDOG, HAL_watchdog_refresh());
   thermalManager.setTargetBed(save_bed);
   thermalManager.setTargetHotend(save_e0,0);
   DEBUG("Restore thermal settings E0:%d Bed:%d",save_bed,save_e0);
   WRITE(MKS_WIFI_IO4, LOW); //Включить передачу от ESP 
}

#endif