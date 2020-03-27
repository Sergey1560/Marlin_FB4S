#include "mks_wifi.h"

ESP_PROTOC_FRAME esp_frame;
uint8_t mks_buffer[ESP_PACKET_DATA_MAX_SIZE];

void mks_wifi_init(void){
	
    DEBUG("Init MKS WIFI");
	SET_OUTPUT(MKS_WIFI_IO_RST);
	WRITE(MKS_WIFI_IO_RST, LOW);

	safe_delay(2000);	
	WRITE(MKS_WIFI_IO_RST, HIGH);

    // SET_INPUT_PULLUP(MKS_WIFI_IO0);
    // attachInterrupt(MKS_WIFI_IO0, mks_wifi_io0_irq, FALLING);
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
	   (packet_index < (payload_size+5)) 
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
				DEBUG("[Gcode] %s",packet->data);
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


