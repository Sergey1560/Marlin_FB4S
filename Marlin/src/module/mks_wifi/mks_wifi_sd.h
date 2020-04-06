#ifndef MKS_WIFI_SD_H
#define MKS_WIFI_SD_H

#define DMA_TIMEOUT 0xffffff

#include "mks_wifi.h"
#include "../../sd/cardreader.h"
#include "small_cmsis.h"

#define DMA_BUFF_COUNT      2
#define DMA_BUFF_SIZE       1024

#define ESP_PACKET_SIZE     1024

void mks_wifi_sd_init(void);
void mks_wifi_sd_deinit(void);
void sd_delete_file(char *filename);

void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet);

void __irq_dma1_channel5(void);

#endif