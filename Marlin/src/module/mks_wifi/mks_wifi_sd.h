#ifndef MKS_WIFI_SD_H
#define MKS_WIFI_SD_H

#define DMA_TIMEOUT 0xFffffff

#include "mks_wifi.h"
#include "../../sd/cardreader.h"
#include "small_cmsis.h"


#define ESP_PACKET_SIZE     1024
#define ESP_FILE_BUFF_COUNT 8

#define DATA_SIZE 16*1024
#define WRITE_COUNT 255


void mks_wifi_sd_init(void);
void mks_wifi_sd_deinit(void);
void sd_delete_file(char *filename);

void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet);

#endif