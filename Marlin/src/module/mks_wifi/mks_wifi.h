#ifndef MKS_WIFI_H
#define MKS_WIFI_H

#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"
#include "../../libs/Segger/log.h"
#include "mks_wifi_settings.h"

#ifdef MKS_WIFI

#define MKS_OUT_BUFF_SIZE 256
//#define SDIO_TEST_AT_STARTUP		
//#define LIST_FILES_AT_STARTUP		(uint8_t)1

#define MKS_WIFI_SERIAL_NUM        (uint8_t)1
#define WIFI_MODE_STA				(uint8_t)2
#define WIFI_MODE_AP				(uint8_t)1

typedef struct
{
	uint8_t type; 
	uint16_t dataLen;
	uint8_t *data; 
} ESP_PROTOC_FRAME;

#define ESP_PROTOC_HEAD				(uint8_t)0xa5
#define ESP_PROTOC_TAIL				(uint8_t)0xfc

#define ESP_TYPE_NET				(uint8_t)0x0
#define ESP_TYPE_GCODE				(uint8_t)0x1
#define ESP_TYPE_FILE_FIRST			(uint8_t)0x2
#define ESP_TYPE_FILE_FRAGMENT		(uint8_t)0x3
#define ESP_TYPE_WIFI_LIST		    (uint8_t)0x4

#define ESP_PACKET_DATA_MAX_SIZE	1024
#define ESP_SERIAL_OUT_MAX_SIZE		1024

#define ESP_NET_WIFI_CONNECTED		(uint8_t)0x0A
#define ESP_NET_WIFI_EXCEPTION		(uint8_t)0x0E

#define NOP	__asm volatile ("nop")


void mks_wifi_init(void);

void mks_wifi_set_param(void);

uint8_t mks_wifi_input(uint8_t data);
void mks_wifi_parse_packet(ESP_PROTOC_FRAME *packet);

void mks_wifi_out_add(uint8_t *data, uint32_t size);

uint16_t mks_wifi_build_packet(uint8_t *packet, ESP_PROTOC_FRAME *esp_frame);

void mks_wifi_send(uint8_t *packet, uint16_t size);

void mks_wifi_print_var(uint8_t count, ...);

void mks_wifi_print(const char *s);
void mks_wifi_print(int i);

void mks_wifi_println(const char *s);
void mks_wifi_println(float);

#endif
#endif