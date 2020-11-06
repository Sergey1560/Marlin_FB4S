#ifndef MKS_WIFI_SERIAL_OUT_H
#define MKS_WIFI_SERIAL_OUT_H

#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"
#include "../../libs/Segger/log.h"
#include "mks_wifi_settings.h"

#ifdef MKS_WIFI


void mks_wifi_print_var(uint8_t count, ...);

void mks_wifi_print_f(float f,uint8_t size);

void mks_wifi_print(const char *s);
void mks_wifi_print(int32 i);
void mks_wifi_print(uint32 i);
void mks_wifi_print(double f);
//void mks_wifi_print(int i);
void mks_wifi_print(long int i);
void mks_wifi_print(unsigned int i);
void mks_wifi_print(float f);


void mks_wifi_println(const char *s);
void mks_wifi_println(int32 i);
void mks_wifi_println(uint32 i);
void mks_wifi_println(double f);
//void mks_wifi_println(int i);
void mks_wifi_println(long int i);
void mks_wifi_println(unsigned int i);
void mks_wifi_println(float f);

#endif

#endif