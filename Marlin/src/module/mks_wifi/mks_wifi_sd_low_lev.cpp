#include "mks_wifi_sd_low_lev.h"
#include "../../sd/Sd2Card_sdio.h"


volatile uint8_t __attribute__ ((aligned (4))) align_buff[512];

uint8_t sd_init(void){
    
    if(SDIO_Init()){
        return 0;
    }else{
        return 1;
    }
}


uint8_t sd_read(uint8_t *buf, uint32_t sector,uint32_t count){
    uint8_t res;
    uint8_t *ptr;

    while (count--){
        if ((0x03 & (uint32_t)buf)){
            ptr=(uint8_t*)align_buff;
        }else{
            ptr=buf;
        } 

        res=SDIO_ReadBlock(sector,ptr);
        if(!res){
            ERROR("Read error");
            return 1;
        }else{
            if ((0x03 & (uint32_t)buf)){
                memcpy((uint8_t *)buf,(uint8_t *)align_buff,512);
            } 
            sector++;
            buf=buf+512;
        }
    }
    return 0;
}


uint8_t sd_write(uint8_t *buf, uint32_t sector,uint32_t count){
    uint8_t res;
    uint8_t *ptr;

    while (count--){
        if ((0x03 & (uint32_t)buf)){
            memcpy((uint8_t *)align_buff,(uint8_t *)buf,512);
            ptr=(uint8_t*)align_buff;
        }else{
            ptr=buf;
        } 
        
        res=SDIO_WriteBlock(sector,ptr);
        if(!res){
            ERROR("Write block error");
            return 1;
        }else{
            sector++;
            buf=buf+512;
        }
    }
    return 0;
}