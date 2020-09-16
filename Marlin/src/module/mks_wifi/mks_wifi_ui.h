#ifndef MKS_WIFI_UI_H
#define MKS_WIFI_UI_H

#include "../../MarlinCore.h"

#if ENABLED(TFT_480x320) || ENABLED(TFT_480x320_SPI)

void mks_update_status(char *filename,int current_filesize, int file_size);
void mks_end_transmit(void);

#endif

#endif