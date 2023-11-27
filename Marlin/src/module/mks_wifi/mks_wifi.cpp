#include "mks_wifi.h"


#ifdef MKS_WIFI

#include "../../lcd/marlinui.h"
#include "mks_wifi_sd.h"

enum ESP_IN_PACKER_STATUS {
	ESP_IN_PACKER_IDLE,
	ESP_IN_PACKER_HEAD_FOUND,
	ESP_IN_PACKER_DATALEN,
	ESP_IN_PACKER_DATALEN2,
	ESP_IN_PACKER_DATA,
	ESP_IN_PACKER_TAIL,
};

volatile ESP_IN_PACKER_STATUS mks_in_packer_status = ESP_IN_PACKER_IDLE;
volatile uint8_t mks_in_data_buffer[MKS_IN_BUFF_SIZE];
volatile uint16_t mks_in_data_ctr = 0;
volatile ESP_PROTOC_FRAME mks_in_frame;
uint8_t mks_out_packet_buffer[MKS_OUT_BUFF_SIZE+2];
volatile uint8_t mks_out_data_buffer[MKS_TOTAL_PACKET_SIZE];
uint8_t mks_txt_out_buffer[MKS_OUT_BUFF_SIZE];
char mks_in_gcode_cmd[128];
uint8_t mks_in_gcode_cmd_idx = 0;

ESP_NET_STATUS mks_global_net_status;
ESP_SCAN_RESULT mks_global_scan_result;


void mks_wifi_init(void){

	SERIAL_ECHO_MSG("Init MKS WIFI");	
    DEBUG("Init MKS WIFI");

	mks_global_scan_result.net_cnt = 0;
	for(int i = 0; i < 20; i++) {
		mks_global_scan_result.networks[i].name_len = 0;
		mks_global_scan_result.networks[i].name[0] = 0;
	}
	mks_global_net_status.cloud_host_len = 0;
	mks_global_net_status.id_len = 0;
	mks_global_net_status.ver_len = 0; mks_global_net_status.ver[0] = 0;
	mks_global_net_status.wifi_key_len = 0; mks_global_net_status.wifi_key[0] = 0;
	mks_global_net_status.wifi_name_len = 0; mks_global_net_status.wifi_name[0] = 0;
	
	// SET_OUTPUT(MKS_WIFI_IO0);
	// WRITE(MKS_WIFI_IO0, HIGH);

	SET_OUTPUT(MKS_WIFI_IO4);
	WRITE(MKS_WIFI_IO4, HIGH);

	SET_OUTPUT(MKS_WIFI_IO_RST);
	WRITE(MKS_WIFI_IO_RST, LOW);

	#if ENABLED(MKS_WIFI_SHOW_IP_IN_STATUS)
		ui.set_status((const char *)"WIFI: waiting... ",false);
	#endif

	memset(mks_txt_out_buffer, 0, MKS_OUT_BUFF_SIZE);
	memset(mks_in_gcode_cmd, 0, 128);

	safe_delay(200);	
	WRITE(MKS_WIFI_IO_RST, HIGH);
	
	safe_delay(200);	
	WRITE(MKS_WIFI_IO4, LOW);
}

void mks_wifi_reset() {
	WRITE(MKS_WIFI_IO_RST, LOW);
	safe_delay(100);
	WRITE(MKS_WIFI_IO_RST, HIGH);
	safe_delay(100);
}


/*
Получает данные из всех функций, как только
есть перевод строки 0x0A, формирует пакет для
ESP и отправляет
*/
void mks_wifi_out_add(uint8_t *data, uint32_t size){
	static uint32_t line_index=0;

	while (size--) {
		if(*data == '\n' || line_index >= MKS_OUT_BUFF_SIZE){
			//Перевод строки или перегрузка => сформировать пакет, отправить, сбросить индекс
			mks_wifi_send_gcoderep(line_index, (char*)mks_txt_out_buffer);
			//очистить буфер
			memset(mks_txt_out_buffer, 0, MKS_OUT_BUFF_SIZE);
			//сбросить индекс
			line_index=0;
		}else{
			//писать в буфер
			mks_txt_out_buffer[line_index++]=*data++;
		}
	}
}

uint8_t mks_wifi_input(uint8_t data) {
	switch(mks_in_packer_status) {
		case ESP_IN_PACKER_IDLE:
			if(data == ESP_PROTOC_HEAD) {
				mks_in_packer_status = ESP_IN_PACKER_HEAD_FOUND;
				memset((uint8_t*)mks_in_data_buffer, 0, MKS_IN_BUFF_SIZE*sizeof(uint8_t));
				mks_in_frame.type = 0;
				mks_in_frame.dataLen = 0;
			}
			break;
		case ESP_IN_PACKER_HEAD_FOUND:
			//прошлый байт был HEAD, этот - type
			mks_in_frame.type = data;
			mks_in_packer_status = ESP_IN_PACKER_DATALEN;
			break;
		case ESP_IN_PACKER_DATALEN:
			//первый байт datalen
			mks_in_frame.dataLen = data;
			mks_in_packer_status = ESP_IN_PACKER_DATALEN2;
			break;
		case ESP_IN_PACKER_DATALEN2:
			//второй байт datalen
			mks_in_frame.dataLen |= uint16_t(data << 8);
			if(mks_in_frame.dataLen > ESP_PACKET_DATA_MAX_SIZE) {
				ERROR("Invalid packet length from ESP: ", mks_in_frame.dataLen);
				mks_in_packer_status = ESP_IN_PACKER_IDLE;
			}
			mks_in_packer_status = ESP_IN_PACKER_DATA;
			break;
		case ESP_IN_PACKER_DATA:
			//идёт N байтов данных
			if(mks_in_data_ctr+1 < mks_in_frame.dataLen) { //+1 нужен, видимо, потому что хвостовой байт тоже считается частью данных
				mks_in_data_buffer[mks_in_data_ctr] = data;
				mks_in_data_ctr++;
			} else {
				mks_in_data_ctr = 0;
				mks_in_packer_status = ESP_IN_PACKER_TAIL;
			}
			break;
		case ESP_IN_PACKER_TAIL:
			//хвостовой байт
			if(data != ESP_PROTOC_TAIL) {
				ERROR("Invalid tail byte from ESP");
				mks_in_packer_status = ESP_IN_PACKER_IDLE;
			} else {
				mks_in_frame.data = (uint8_t*)mks_in_data_buffer;
				//всё хорошо, обрабатываем собранный пакет
				mks_wifi_parse_in_packet((ESP_PROTOC_FRAME*)&mks_in_frame);
				mks_in_packer_status = ESP_IN_PACKER_IDLE;
			}
			break;
	}
	return 1;
}

void mks_wifi_parse_in_packet(ESP_PROTOC_FRAME *packet) {
	switch(packet->type) {
		case ESP_TYPE_NET: {
			for(int i = 0; i < 4; i++) {
				mks_global_net_status.ip[i] = packet->data[0+i];
			}
			mks_global_net_status.port = (uint16_t)packet->data[4];
			mks_global_net_status.state = packet->data[6]; //ESP_NET_WIFI_CONNECTED - ok; ESP_NET_WIFI_FAIL - fail; ESP_NET_WIFI_EXCEPTION - exception
			mks_global_net_status.mode = packet->data[7]; //WIFI_MODE_AP или WIFI_MODE_CLIENT
			mks_global_net_status.wifi_name_len = packet->data[8];
			for(int i = 0; i < mks_global_net_status.wifi_name_len; i++) {
				mks_global_net_status.wifi_name[i] = packet->data[9+i];
			}
			mks_global_net_status.wifi_name[mks_global_net_status.wifi_name_len+1] = 0;
			uint16_t shift = mks_global_net_status.wifi_name_len; //костыль, но так по идее удобнее
			mks_global_net_status.wifi_key_len = packet->data[9+shift];
			for(int i = 0; i < mks_global_net_status.wifi_key_len; i++) {
				mks_global_net_status.wifi_key[i] = packet->data[10+shift+i];
			}
			mks_global_net_status.wifi_key[mks_global_net_status.wifi_key_len+1] = 0;
			shift+=mks_global_net_status.wifi_key_len;
			mks_global_net_status.cloud_state = packet->data[10+shift]; //0x12 - ok; 0x11 - not binded; 0x10 - not connected; 0x00 - cloud disabled
			mks_global_net_status.cloud_host_len = packet->data[11+shift];
			#if ENABLED(MKS_WIFI_CLOUD_SUPPORT)
				for(int i = 0; i < mks_global_net_status.cloud_host_len; i++) {
					mks_global_net_status.cloud_host[i] = packet->data[12+shift+i];
				}
				mks_global_net_status.cloud_host[mks_global_net_status.cloud_host_len+1] = 0;
			#endif
			shift+=mks_global_net_status.cloud_host_len;
			mks_global_net_status.cloud_port = (uint16_t)packet->data[12+shift];
			mks_global_net_status.id_len = packet->data[14+shift];
			#if ENABLED(MKS_WIFI_CLOUD_SUPPORT)
				for(int i = 0; i < mks_global_net_status.id_len; i++) {
					mks_global_net_status.id_str[i] = packet->data[15+shift+i];
				}
				mks_global_net_status.id_str[mks_global_net_status.id_len+1] = 0;
			#endif
			shift+=mks_global_net_status.id_len;
			mks_global_net_status.ver_len = packet->data[15+shift];
			for(int i = 0; i < mks_global_net_status.ver_len; i++) {
				mks_global_net_status.ver[i] = packet->data[16+shift+i];
			}
			mks_global_net_status.ver[mks_global_net_status.ver_len+1] = 0;
			mks_wifi_update_netstatus();
			break;
		}
		case ESP_TYPE_GCODE: {
			for(uint16_t i = 0; i < packet->dataLen; i++) {
				if(packet->data[i] != '\n' && packet->data[i] != '\r' && packet->data[i] != '\0' && mks_in_gcode_cmd_idx < 127) { //Иногда команды разделяются \n, иногда \0, возможно и \r
					mks_in_gcode_cmd[mks_in_gcode_cmd_idx++] = packet->data[i];
				} else {
					GCodeQueue::ring_buffer.enqueue((const char *)mks_in_gcode_cmd, false, MKS_WIFI_SERIAL_NUM);
					mks_in_gcode_cmd_idx = 0;
					memset(mks_in_gcode_cmd, 0, 128);
				}
			}
		break;
		}
		case ESP_TYPE_FILE_FIRST: {
			DEBUG("[FILE_FIRST]");
			//Передача файла останавливает все процессы,
			//поэтому печать в этот момент не возможна.
			if (!CardReader::isPrinting()) {
				mks_wifi_start_file_upload(packet);
			} else {
				//Попытка запустить передачу файла во время печати
				//Отключение модуля wifi
				DEBUG("Shutdown wifi");
				WRITE(MKS_WIFI_IO_RST, LOW);
				delay(50);
				WRITE(MKS_WIFI_IO_RST, HIGH);
			}
			break;
		}
		case ESP_TYPE_FILE_FRAGMENT: {
			DEBUG("[FILE_FRAGMENT]");
		}
		break;
		case ESP_TYPE_WIFI_LIST: {
			DEBUG("[WIFI_LIST]");
			mks_global_scan_result.net_cnt = packet->data[0];
			uint16_t shift = 1;
			for(int i = 0; i < mks_global_scan_result.net_cnt; i++) {
				uint8_t real_str_len = packet->data[shift++];
				mks_global_scan_result.networks[i].name_len = min(real_str_len, (uint8_t)31);
				for(int k = 0; k < real_str_len; k++) {
					char c = packet->data[shift++];
					if(k < 32) {
						mks_global_scan_result.networks[i].name[k] = c;
					}
				}
				mks_global_scan_result.networks[i].name[mks_global_scan_result.networks[i].name_len] = 0;
				mks_global_scan_result.networks[i].rssi = packet->data[shift++];
			}
			mks_wifi_update_scanresult();
		break;
		}
		default: {
			//хз
			break;
		}
	}
}

void mks_wifi_update_netstatus() {
	static uint8_t show_ip_once=0;
	if(mks_global_net_status.state == ESP_NET_WIFI_CONNECTED) {
		if(show_ip_once == 0) {
			show_ip_once=1;
			char str[128];
			sprintf(str,"IP %d.%d.%d.%d", mks_global_net_status.ip[0], mks_global_net_status.ip[1], mks_global_net_status.ip[2], mks_global_net_status.ip[3]);
			#if ENABLED(MKS_WIFI_SHOW_IP_IN_STATUS)
				ui.set_status((const char *)str,true);
			#endif
			SERIAL_ECHO_START();
			SERIAL_ECHOLN((char*)str);

			//Вывод имени сети

			SERIAL_ECHO_START();
			SERIAL_ECHO("WIFI: ");
			SERIAL_ECHOLN(mks_global_net_status.wifi_name);
			DEBUG("[Net] connected, IP: %d.%d.%d.%d", mks_global_net_status.ip[0], mks_global_net_status.ip[1], mks_global_net_status.ip[2], mks_global_net_status.ip[3]);
		}
	} else if(mks_global_net_status.state == ESP_NET_WIFI_EXCEPTION) {
		DEBUG("[Net] wifi exeption");
	} else {
		DEBUG("[Net] wifi not config");
	}
}

void mks_wifi_update_scanresult() {
	//TODO
}

void mks_wifi_send(uint8_t *packet, uint16_t size) {
	static uint32_t error_flag=0;
	uint32_t timeout;

	/*
	Если уже был выход по превышению ожидания и место
	очереди так и не освободилось, сразу выход.
	*/

	if(error_flag == 1){
		if(MYSERIAL2.availableForWrite()==0){
			return;
		}else{
			error_flag = 0;
		}
	}

	for( uint32_t i=0; i < (uint32_t)(size+1); i++){
		timeout = 0xaffffff;
		while(MYSERIAL2.availableForWrite()==0){
			--timeout;
			if(!timeout){
				error_flag=1;
				return;
			};
		}
		MYSERIAL2.write(packet[i]);
	}
}

uint16_t mks_wifi_build_packet(uint8_t *packet, ESP_PROTOC_FRAME *esp_frame) {
	uint16_t packet_size=0;

	memset(packet, 0, MKS_TOTAL_PACKET_SIZE);
	packet[0] = ESP_PROTOC_HEAD;
	packet[1] = esp_frame->type;

	for(uint32_t i=0; i < esp_frame->dataLen; i++){
		packet[i+4]=esp_frame->data[i]; //4 байта заголовка отступить
	}

	packet_size = esp_frame->dataLen + 4;

	if(packet_size > MKS_TOTAL_PACKET_SIZE){
		ERROR("ESP packet too big");
		return 0;
	}

	*((uint16_t *)&packet[2]) = esp_frame->dataLen;

	packet[packet_size] = ESP_PROTOC_TAIL;
	return packet_size;
}

void mks_wifi_send_netconf(uint8_t mode, uint8_t name_len, char* name, uint8_t key_len, char* key) {
	memset(mks_out_packet_buffer, 0, MKS_OUT_BUFF_SIZE);
	mks_out_packet_buffer[0] = mode;
	mks_out_packet_buffer[1] = name_len;
	memcpy((char *)&mks_out_packet_buffer[2], (const char *)name, name_len);
	mks_out_packet_buffer[2+name_len] = key_len;
	memcpy((char *)&mks_out_packet_buffer[2 + name_len + 1], (const char *)key, key_len);
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_NETCFG;
	esp_frame.dataLen = 2 + name_len + key_len + 1;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);

	if(packet_size > 8) { //4 байта заголовка + 2 байта длины + хвост + название сети и пароль
		//выпихнуть в uart
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

void mks_wifi_send_gcoderep(uint8_t len, char* str) {
	memset(mks_out_packet_buffer, 0, MKS_OUT_BUFF_SIZE+2);
	memcpy((char *)mks_out_packet_buffer, (const char *)str, len);
	mks_out_packet_buffer[len++] = '\r';
	mks_out_packet_buffer[len++] = '\n';
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_GCODEREPLY;
	esp_frame.dataLen = len;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);
	if(packet_size > 2) {
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

void mks_wifi_send_exception(uint8_t code) {
	memset(mks_out_packet_buffer, 0, MKS_OUT_BUFF_SIZE);
	mks_out_packet_buffer[0] = code;
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_EXCEPTION;
	esp_frame.dataLen = 1;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);
	if(packet_size > 2) {
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

void mks_wifi_send_cloud_config(uint8_t enable, uint8_t host_len, char* host, uint16_t port) {
	memset(mks_out_packet_buffer, 0, MKS_OUT_BUFF_SIZE);
	mks_out_packet_buffer[0] = enable;
	mks_out_packet_buffer[1] = host_len;
	memcpy((char *)&mks_out_packet_buffer[2], (const char *)host, host_len);
	memcpy((char *)&mks_out_packet_buffer[2 + host_len], (const uint16_t *)&port, sizeof(uint16_t));
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_CLOUDCFG;
	esp_frame.dataLen = 2 + host_len + 2;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);

	if(packet_size > 2) {
		//выпихнуть в uart
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

void mks_wifi_send_unbind() {
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_UNBIND;
	esp_frame.dataLen = 0;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);

	if(packet_size > 2) {
		//выпихнуть в uart
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

void mks_wifi_send_scan() {
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_NETSCAN;
	esp_frame.dataLen = 0;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);

	if(packet_size > 0) {
		//выпихнуть в uart
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

void mks_wifi_send_wifi_connect(uint8_t mode) {
	memset(mks_out_packet_buffer, 0, MKS_OUT_BUFF_SIZE);
	mks_out_packet_buffer[0] = mode;
	ESP_PROTOC_FRAME esp_frame;
	esp_frame.type = ESP_RTYPE_WIFICONN;
	esp_frame.dataLen = 1;
	esp_frame.data = mks_out_packet_buffer;
	uint16_t packet_size = mks_wifi_build_packet((uint8_t *)mks_out_data_buffer, &esp_frame);
	if(packet_size > 2) {
		mks_wifi_send((uint8_t *)mks_out_data_buffer, packet_size);
	}
}

/*
Проверяет, что символы из текстового диапазона
для G-code команд
*/
uint8_t check_char_allowed(char data){

	if( data == 0x0a || data == 0x0d){
		return 0;
	}

	if( (data >= 0x20) && (data <= 0x7E) ){
		return 0;
	}

	return 1;

}

#else
void mks_wifi_out_add(uint8_t *data, uint32_t size){
	while(size--){
		MYSERIAL2.write(*data++);
	}
	return;
};

#endif