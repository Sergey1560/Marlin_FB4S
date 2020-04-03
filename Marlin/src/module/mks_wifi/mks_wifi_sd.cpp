#include "mks_wifi_sd.h"

#include "../../libs/fatfs/ff.h"

FRESULT result;
FATFS FATFS_Obj;
FIL upload_file;
// DIR dir;
// UINT i;

void mks_wifi_sd_init(void){
   CardReader::release();

   result = f_mount((FATFS *)&FATFS_Obj, "0", 1);
   DEBUG("SD init %d",result);
/*  
   result = f_opendir(&dir, "0:");                       
      if (result == FR_OK) {
         for (;;) {
            result = f_readdir(&dir, &fno);              
            if (result != FR_OK || fno.fname[0] == 0) break;
                  DEBUG("%s", fno.fname);
            }
         f_closedir(&dir);
      }else{
         DEBUG("Open dir error %d",result);
      }
*/
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
	uint32_t file_size;
   
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

   //Выключить прием по UART RX, включить через DMA, изменить скорость
   //Выставить флаг приема по DMA
   /*
   В бесконечном цикле ждем флага приема от DMA{
      Если флаг есть => {
         //переключить буфер, запустить прием дальше
         //передать пакет в функцию парсера и сохранения
      }
      Парсер пакета, сохранение{

      }
      Проверка тайм-аута. Если долго нет данных, 
      значит все кончилось => остановить DMA, переключить UART
   }
   */

}
