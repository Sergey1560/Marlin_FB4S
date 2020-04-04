#ifndef MKS_WIFI_SD_H
#define MKS_WIFI_SD_H

#define DMA_TIMEOUT 0xffffff

#include "mks_wifi.h"
#include "../../sd/cardreader.h"
#include "small_cmsis.h"

void mks_wifi_sd_init(void);
void mks_wifi_sd_deinit(void);
void sd_delete_file(char *filename);

void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet);

#endif