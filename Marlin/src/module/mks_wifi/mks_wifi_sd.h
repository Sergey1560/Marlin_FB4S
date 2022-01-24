#ifndef MKS_WIFI_SD_H
#define MKS_WIFI_SD_H
#include "mks_wifi.h"
#include "../../sd/cardreader.h"
#include "../shared_mem/shared_mem.h"

#ifdef MKS_WIFI

//#define SHOW_PROGRESS

#define DMA_TIMEOUT 0x1ffffff
#define ESP_PACKET_SIZE     1024

//Под буфер для DMA два последних КБ из буфера
#define ESP_FILE_BUFF_COUNT (SHARED_MEM_1KB_COUNT-2)
//Под буфер для записи в файл все оставшееся с начала
#define FILE_BUFFER_SIZE  ESP_PACKET_SIZE*ESP_FILE_BUFF_COUNT

void mks_wifi_sd_ls(void);

uint8_t mks_wifi_sd_init(void);
void mks_wifi_sd_deinit(void);
void sd_delete_file(char *filename);

uint8_t get_dos_filename(char *filename, char* dosfilename);

void mks_wifi_start_file_upload(ESP_PROTOC_FRAME *packet);

#endif

#endif