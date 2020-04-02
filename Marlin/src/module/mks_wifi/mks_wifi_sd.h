#ifndef MKS_WIFI_SD_H
#define MKS_WIFI_SD_H

#include "mks_wifi.h"
#include "../../sd/cardreader.h"

void mks_wifi_sd_init(void);
void mks_wifi_sd_deinit(void);
void sd_delete_file(char *filename);

#endif