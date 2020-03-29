#include "mks_wifi.h"

ESP_PROTOC_FRAME esp_frame;
uint8_t mks_buffer[ESP_PACKET_DATA_MAX_SIZE];
uint8_t mks_out_buffer[ESP_PACKET_DATA_MAX_SIZE];
uint8_t esp_packet[ESP_PACKET_DATA_MAX_SIZE];


/*
const char home_ssid[] = "MikroTik2";
const char home_passwd[] = "vg3Apswqvg3Aps";
*/
const char wifi_ap[]="bus_station";
const char wifi_key[]="RAnRZj2JQbSMD5djh3";
const uint8_t wifi_mode_sel=0;

void mks_wifi_init(void){
	
    DEBUG("Init MKS WIFI");
	SET_OUTPUT(MKS_WIFI_IO_RST);
	WRITE(MKS_WIFI_IO_RST, LOW);

	safe_delay(2000);	
	WRITE(MKS_WIFI_IO_RST, HIGH);
	
//	safe_delay(2000);	
//	mks_wifi_set_param();
    // SET_INPUT_PULLUP(MKS_WIFI_IO0);
    // attachInterrupt(MKS_WIFI_IO0, mks_wifi_io0_irq, FALLING);
}


void mks_wifi_set_param(void){
	char buf_to_wifi[256];
	int index_to_wifi = 0;

	int data_offset = 4;
	int apLen = strlen((const char *)wifi_ap);
	int keyLen = strlen((const char *)wifi_key);
		
	memset(buf_to_wifi, 0, sizeof(buf_to_wifi));
	index_to_wifi = 0;

	buf_to_wifi[data_offset] = wifi_mode_sel;
	buf_to_wifi[data_offset + 1]  = apLen;
	strncpy(&buf_to_wifi[data_offset + 2], (const char *)wifi_ap, apLen);
	buf_to_wifi[data_offset + apLen + 2]  = keyLen;
	strncpy(&buf_to_wifi[data_offset + apLen + 3], (const char *)wifi_key, keyLen);
	buf_to_wifi[data_offset + apLen + keyLen + 3] = ESP_PROTOC_TAIL;
	DEBUG("Tail index %d",(data_offset + apLen + keyLen + 3));
	index_to_wifi = apLen + keyLen + 3;

	buf_to_wifi[0] = ESP_PROTOC_HEAD;
	buf_to_wifi[1] = 0;
	buf_to_wifi[2] = index_to_wifi & 0xff;
	buf_to_wifi[3] = (index_to_wifi >> 8) & 0xff;

	DEBUG("Sending config %d",(uint32_t)(5 + index_to_wifi));
	for( uint32_t i=0; i< (uint32_t)(5 + index_to_wifi); i++){
		while(MYSERIAL1.availableForWrite() == 0){NOP;};
		MYSERIAL1.write(buf_to_wifi[i]);
	}
}

/* Тестовая функция на обработчик EXTI прерывания */
void mks_wifi_io0_irq(void){
    INFO("IO0 Irq");
}

/*
Принимает по символу из входных данных.
Сладывает в буфер, формирует пакет.
Возвращаемые занчения:
1 - найден признак начала пакета, отдавать байт мардину не надо
0 - начало пакета не найдено, передать байт дальше марлину
*/
uint8_t mks_wifi_input(uint8_t data){
	static uint8_t packet_start_flag=0;
	static uint8_t packet_type=0;
	static uint16_t packet_index=0;
	static uint16_t payload_size=ESP_PACKET_DATA_MAX_SIZE;
	uint8_t ret_val=1;


	if(data == ESP_PROTOC_HEAD){
		payload_size = ESP_PACKET_DATA_MAX_SIZE;
		packet_start_flag=1;
		packet_index=0;
		memset(mks_buffer,0,ESP_PACKET_DATA_MAX_SIZE);
	}

	if(packet_start_flag){
		mks_buffer[packet_index]=data;
	}

	if(packet_index == 1){
		packet_type = mks_buffer[1];
	}

	if(packet_index == 3){
		payload_size = uint16_t(mks_buffer[3] << 8) | mks_buffer[2];
	}

	if( (packet_index >= (payload_size+4)) || (packet_index >= ESP_PACKET_DATA_MAX_SIZE) ){
		esp_frame.type = packet_type;
		esp_frame.dataLen = payload_size;
		esp_frame.data = &mks_buffer[4];

		mks_wifi_parse_packet(&esp_frame);

		packet_start_flag=0;
		packet_index=0;
	}

	/* Если в пакете G-Сode, отдаем payload дальше в обработчик марлина */
	if((packet_type == ESP_TYPE_GCODE) && 
	   (packet_index >= 4) && 
	   (packet_index < payload_size+5) 
	  ){
		ret_val=0;
	}

	if(packet_start_flag){
		packet_index++;
	}

	return ret_val;
}

void mks_wifi_parse_packet(ESP_PROTOC_FRAME *packet){
	
	switch(packet->type){
		case ESP_TYPE_NET:
			
			if(packet->data[6] == ESP_NET_WIFI_CONNECTED){
				DEBUG("[Net] connected, IP: %d.%d.%d.%d",packet->data[0],packet->data[1],packet->data[2],packet->data[3]);
			}else if(packet->data[6] == ESP_NET_WIFI_EXCEPTION){
				DEBUG("[Net] wifi exeption");
			}else{
				DEBUG("[Net] wifi not config");
			}
			break;
		case ESP_TYPE_GCODE:
				//DEBUG("[Gcode] %s",packet->data);
			break;
		case ESP_TYPE_FILE_FIRST:
				DEBUG("[FILE_FIRST]");
			break;
		case ESP_TYPE_FILE_FRAGMENT:
				DEBUG("[FILE_FRAGMENT]");
			break;
		case ESP_TYPE_WIFI_LIST:
			DEBUG("[WIFI_LIST]");
			break;
		default:
			DEBUG("[Unkn]");
		 	break;

	}

}


void mks_wifi_out(uint8_t count, ...){
	static uint16_t line_index=0;
	va_list args;
	uint8_t data;
	uint16_t datalen;
	uint16_t packet_size;

	va_start(args, count);

    while (count--) {


        data = va_arg(args, unsigned);
		if(data == 0x0a){

			if(mks_out_buffer[line_index-1] == 't'){
				DEBUG("Line");
			}

			//сформировать пакет
			datalen=strnlen((char *)mks_out_buffer,ESP_PACKET_DATA_MAX_SIZE);
			packet_size=mks_wifi_build_packet(esp_packet,ESP_TYPE_FILE_FIRST,mks_out_buffer,datalen);

			//выпихнуть в uart
			mks_wifi_send(esp_packet, packet_size);

			DEBUG("%s",mks_out_buffer);

			//очистить буфер
			memset(mks_out_buffer,0,ESP_SERIAL_OUT_MAX_SIZE);
			//сбросить индекс
			line_index=0;
		}else{
			mks_out_buffer[line_index++]=data;
		}

		if(line_index >= ESP_SERIAL_OUT_MAX_SIZE){
			DEBUG("Max line size");
			line_index=0;
		}
    }
    va_end(args);
}


void mks_println(const char *s){
	uint16_t datalen;
	uint16_t packet_size;

	DEBUG("%s",s);

	//сформировать пакет
	datalen=strnlen((char *)mks_out_buffer,ESP_PACKET_DATA_MAX_SIZE);
	packet_size=mks_wifi_build_packet(esp_packet,ESP_TYPE_FILE_FIRST,mks_out_buffer,datalen);

	//выпихнуть в uart
	mks_wifi_send(esp_packet, packet_size);
}

void mks_println_ln(const char *s){

	DEBUG("NEW LN %s");

}

void mks_println_ln(float f){
	
	DEBUG("NEW LN float %d",(uint32_t)f);

}

uint16_t mks_wifi_build_packet(uint8_t *packet, uint8_t type, uint8_t *data, uint16_t count){
	uint16_t packet_size;

	memset(packet,0,ESP_PACKET_DATA_MAX_SIZE);
	packet[0] = ESP_PROTOC_HEAD;
	packet[1] = type;

	*((uint16_t *)&packet[2]) = count + 2; //Два байта на 0x0d 0x0a

	for(uint32_t i=0; i < count; i++){
		packet[i+4]=data[i];
	}

	packet_size = count + 4;
	packet[count + 4] = 0x0d;
	packet[count + 5] = 0x0a; 
	
	packet_size = count + 6; //Два байта на 0x0d 0x0a
	packet[packet_size] = ESP_PROTOC_TAIL;
	return packet_size;
}


void mks_wifi_send(uint8_t *packet, uint16_t size){
	for( uint32_t i=0; i < (uint32_t)(size); i++){
		MYSERIAL1.write(packet[i]);
	}
}

void mks_println(int i){
	DEBUG("int %d",i);
	SERIAL_OUT(print, i);
}