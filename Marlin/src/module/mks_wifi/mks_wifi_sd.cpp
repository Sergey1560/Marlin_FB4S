#include "mks_wifi_sd.h"

#include "../../libs/fatfs/ff.h"

FRESULT result;
FATFS FATFS_Obj;
DIR dir;
UINT i;

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