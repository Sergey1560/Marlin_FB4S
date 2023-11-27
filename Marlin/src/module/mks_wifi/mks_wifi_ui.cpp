#include "mks_wifi_ui.h"

#if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)

#include "../../lcd/tft/tft.h"
#include "../../lcd/tft/tft_color.h"
#include "../../lcd/marlinui.h"
#include "../temperature.h"


extern TFT tft;
char str[100];

uint32_t last_status_value = 200;

void mks_update_status(char *filename,uint32_t current_filesize, uint32_t file_size){
    static uint32_t call_count = 0;

    uint32_t percent_done;
    uint16_t width;
    
    // thermalManager.setTargetBed(0);
    // thermalManager.setTargetHotend(0,0);
    // thermalManager.task();
    // OUT_WRITE(FAN1_PIN,HIGH);

    //При расчете процентов размер файла превышает максимум для uint32_t
    if(current_filesize >= (UINT32_MAX/100) ){
      current_filesize = current_filesize/100;
      file_size = file_size/100;
    }

    percent_done = (current_filesize*100)/file_size;
    if(((uint8_t)percent_done != last_status_value)){
      call_count++;
      DEBUG("LCD call %ld CF: %ld  FS: %ld",call_count,current_filesize,file_size);
      tft.queue.reset();
      tft.canvas(0, 0, TFT_WIDTH, TFT_HEIGHT);
      tft.set_background(COLOR_BACKGROUND);

      sprintf(str,"%s",filename);
      tft.add_text(8, 100, COLOR_WHITE, str);
      
      width = ((TFT_WIDTH-10)*(uint8_t)percent_done)/100;
      tft.add_bar(8,150, width, 30, COLOR_GREEN);

      sprintf(str,"%ld of %ld (%d%%)",current_filesize,file_size,(uint8_t)percent_done);
      tft.add_text(100, 150, COLOR_WHITE, str);
      
      tft.queue.sync();
      last_status_value = percent_done;
    };

}


void mks_upload_screen(void){

      tft.queue.reset();
      tft.canvas(0, 0, TFT_WIDTH, TFT_HEIGHT);
      tft.set_background(COLOR_BACKGROUND);
      tft.add_text(8, 100, COLOR_WHITE, "Uploading...");
      tft.queue.sync();
}


void mks_end_transmit(void) {
  last_status_value = 200;
  tft.queue.reset();
  tft.fill(0, 0, TFT_WIDTH, TFT_HEIGHT, COLOR_BACKGROUND);
  tft.queue.sync();
}


#endif