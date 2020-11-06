#include "mks_wifi_serial_out.h"
#include "mks_wifi.h"
#ifdef MKS_WIFI


void mks_wifi_print_var(uint8_t count, ...){
	va_list args;
	uint8_t data;

	va_start(args, count);

    while (count--) {
        data = va_arg(args, unsigned);
		mks_wifi_out_add(&data, 1);
    }
    va_end(args);
}

void mks_wifi_print_f(float f,uint8_t size){
	char str[20];
	char format[10];
	
	sprintf(format,"%%0.%df",size);
	sprintf(str,format,f);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}


// PRINT functions

void mks_wifi_print(const char *s){
	mks_wifi_out_add((uint8_t *)s, strnlen((char *)s,ESP_PACKET_DATA_MAX_SIZE));
}

//Signed int
void mks_wifi_print(int32 i){
	char str[12];

	sprintf(str,"%d",i);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}
//Unsigned int
void mks_wifi_print(uint32 i){
	char str[12];

	sprintf(str,"%ld",i);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}
//Float
void mks_wifi_print(double f){
	char str[12];

	sprintf(str,"%.2f",f);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}

/*
void mks_wifi_print(int i){
    mks_wifi_print((int32)i);
}
*/
void mks_wifi_print(long int i){
    mks_wifi_print((int32)i);
}

void mks_wifi_print(unsigned int i){
    mks_wifi_print((uint32_t)i);
}
void mks_wifi_print(float f){
    mks_wifi_print((double)f);
}


//PRINTLN
void mks_wifi_println(const char *s){
    char str[100];

    sprintf(str,"%s\n",s);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}
//Int
void mks_wifi_println(int32 i){
	char str[14];
	sprintf(str,"%d\n",i);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}
//Unsigned int
void mks_wifi_println(uint32 i){
	char str[14];
	sprintf(str,"%ld\n",i);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}
//Float
void mks_wifi_println(double f){
	char str[14];

	sprintf(str,"%.2f\n",f);
	mks_wifi_out_add((uint8_t *)str, strnlen((char *)str,ESP_PACKET_DATA_MAX_SIZE));
}
void mks_wifi_println(long int i){
    mks_wifi_println((int32)i);
}

void mks_wifi_println(unsigned int i){
    mks_wifi_println((uint32_t)i);
}
void mks_wifi_println(float f){
    mks_wifi_println((double)f);
}



#endif
