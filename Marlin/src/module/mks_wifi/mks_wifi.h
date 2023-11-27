#ifndef MKS_WIFI_H
#define MKS_WIFI_H
#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"
#include "../../libs/Segger/log.h"
#include "mks_wifi_settings.h"
#include "../../gcode/queue.h"

void mks_wifi_out_add(uint8_t *data, uint32_t size); //Вызывается, когда пришёл текстовый ответ от выполнения GCODа

#ifdef MKS_WIFI

#define MKS_OUT_BUFF_SIZE (ESP_PACKET_DATA_MAX_SIZE)
#define MKS_IN_BUFF_SIZE (ESP_PACKET_DATA_MAX_SIZE + 30)
#define MKS_TOTAL_PACKET_SIZE (ESP_PACKET_DATA_MAX_SIZE+10)

#define WIFI_MODE_AP				(uint8_t)1
#define WIFI_MODE_CLIENT			(uint8_t)2

#define ESP_NET_WIFI_CONNECTED		(uint8_t)0x0A
#define ESP_NET_WIFI_FAIL			(uint8_t)0x05
#define ESP_NET_WIFI_EXCEPTION		(uint8_t)0x0E

#define ESP_WIFI_ACT_CONN			(uint8_t)0x01
#define ESP_WIFI_ACT_DISCONN		(uint8_t)0x02
#define ESP_WIFI_ACT_FORGET			(uint8_t)0x03

#define ESP_PROTOC_HEAD				(uint8_t)0xa5
#define ESP_PROTOC_TAIL				(uint8_t)0xfc

//от есп к мк
#define ESP_TYPE_NET				(uint8_t)0x0
#define ESP_TYPE_GCODE				(uint8_t)0x1
#define ESP_TYPE_FILE_FIRST			(uint8_t)0x2
#define ESP_TYPE_FILE_FRAGMENT		(uint8_t)0x3
#define ESP_TYPE_WIFI_LIST		    (uint8_t)0x4

//от мк к есп
#define ESP_RTYPE_NETCFG			(uint8_t)0x0
#define ESP_RTYPE_GCODEREPLY		(uint8_t)0x2
#define ESP_RTYPE_EXCEPTION			(uint8_t)0x3
#define ESP_RTYPE_CLOUDCFG			(uint8_t)0x4
#define ESP_RTYPE_UNBIND			(uint8_t)0x5
#define ESP_RTYPE_NETSCAN			(uint8_t)0x7 //Значение из документации 0x06 - вранье
#define ESP_RTYPE_WIFICONN			(uint8_t)0x9

#define ESP_PACKET_DATA_MAX_SIZE	1024
#define ESP_SERIAL_OUT_MAX_SIZE		1024



#define NOP	__asm volatile ("nop")

typedef struct {
	uint8_t type;
	uint16_t dataLen;
	uint8_t *data;
} ESP_PROTOC_FRAME;

typedef struct {
	uint8_t ip[4];
	uint16_t port;
	uint8_t state;
	uint8_t mode;
	uint8_t wifi_name_len;
	char wifi_name[256];
	uint8_t wifi_key_len;
	char wifi_key[256];
	uint8_t cloud_state;
	uint8_t cloud_host_len;
	uint16_t cloud_port;
	uint8_t id_len;
	#if ENABLED(MKS_WIFI_CLOUD_SUPPORT) //экономим память
		char cloud_host[256];
		char id_str[256];
	#endif
	uint8_t ver_len;
	char ver[256];
} ESP_NET_STATUS;

typedef struct {
	uint8_t name_len;
	char name[32];
	uint8_t rssi;
} ESP_NET_DATA;

typedef struct {
	uint8_t net_cnt;
	ESP_NET_DATA networks[20];
} ESP_SCAN_RESULT;

extern ESP_NET_STATUS mks_global_net_status;
extern ESP_SCAN_RESULT mks_global_scan_result;

void mks_wifi_init(void); //инициализация MKS WIFI модуля
void mks_wifi_reset(); //Перезагрузить модуль
uint8_t mks_wifi_input(uint8_t data); //Вызывается, когда от ESPшки пришёл байт
void mks_wifi_parse_in_packet(ESP_PROTOC_FRAME *packet); //Обработать пакет, пришедший от ESPшки
void mks_wifi_update_netstatus(); //Вызывается при каждом обновлении статуса сети
void mks_wifi_update_scanresult(); //Вызывается при каждом получении результатов сканирования сетей

void mks_wifi_send(uint8_t *packet, uint16_t size); //Отправить байты напрямую в ESPшку
uint16_t mks_wifi_build_packet(uint8_t *packet, ESP_PROTOC_FRAME *esp_frame); //Собрать пакет esp_frame в буфер packet, возвращает размер; нужен буфер размером MKS_TOTAL_PACKET_SIZE
void mks_wifi_send_netconf(uint8_t mode, uint8_t name_len, char* name, uint8_t key_len, char* key); //Настроить сеть; mode=WIFI_MODE_*; name_len - длина имени сети(<32 байт); key_len - длина пароля(<64 байт)
void mks_wifi_send_gcoderep(uint8_t len, char* str); //Ответ от выполнения gcodа
void mks_wifi_send_exception(uint8_t code); //В документации не описано, что это и когда отправлять, пусть будет
void mks_wifi_send_cloud_config(uint8_t enable, uint8_t host_len, char* host, uint16_t port); //настройки облака; host_len<=96
void mks_wifi_send_unbind(); //отключиться от сети
void mks_wifi_send_scan(); //сканировать сети
void mks_wifi_send_wifi_connect(uint8_t mode); //подключиться(ESP_WIFI_ACT_CONN) к сохраненной/отключиться(ESP_WIFI_ACT_DISCONN)/забыть пароль от сети(ESP_WIFI_ACT_FORGET)

uint8_t check_char_allowed(char data);

#endif
#endif