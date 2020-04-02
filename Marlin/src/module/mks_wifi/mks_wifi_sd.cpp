#include "mks_wifi_sd.h"

#include "../../libs/fatfs/ff.h"

FRESULT result;
FATFS FATFS_Obj;

void mks_wifi_sd_init(void){

   result = f_mount((FATFS *)&FATFS_Obj, "0", 1);
   DEBUG("SD init %d",result);



}