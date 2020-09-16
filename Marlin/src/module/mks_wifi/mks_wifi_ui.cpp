#include "mks_wifi_ui.h"

#if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)

#include "../../lcd/tft/tft.h"
#include "../../lcd/tft/tft_color.h"

extern TFT tft;

void mks_update_status(char *filename,int current_filesize, int file_size){
    char str[100];
    static uint32_t last_value = 200;
    uint8_t percent_done;

    percent_done = current_filesize*100/file_size;
    if((percent_done != last_value)){
      tft.queue.reset();
      tft.canvas(0, 0, TFT_WIDTH, TFT_HEIGHT);
      tft.set_background(COLOR_BACKGROUND);

      sprintf(str,"%s",filename);
      tft.add_text(8, 100, COLOR_WHITE, str);
      
      tft.add_bar(8,150, ((TFT_WIDTH-10)*percent_done)/100, 30, COLOR_GREEN);

      sprintf(str,"%d of %d (%d%%)",current_filesize,file_size,percent_done);
      tft.add_text(100, 150, COLOR_WHITE, str);
      
      tft.queue.sync();
        last_value = percent_done;
    };

}

void mks_end_transmit(void){
  tft.queue.reset();
  tft.fill(0, 0, TFT_WIDTH, TFT_HEIGHT, COLOR_BACKGROUND);
  tft.queue.sync();
}


#endif