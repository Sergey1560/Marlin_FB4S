#include "mks_wifi_sd_low_lev.h"
#include "../../sd/Sd2Card_sdio.h"

uint8_t sd_init(void){
    
    if(SDIO_Init()){
        return 0;
    }else{
        return 1;
    }
}


uint8_t sd_read(uint8_t *buf, uint32_t sector,uint32_t count){
    uint8_t res;

    while (count--){
        res=SDIO_ReadBlock(sector,buf);
        if(!res){
            return 1;
        }else{
            sector++;
            buf=buf+512;
        }
    }
    return 0;
}


uint8_t sd_write(uint8_t *buf, uint32_t sector,uint32_t count){
    uint8_t res;

    while (count--){
        res=SDIO_WriteBlock(sector,buf);
        if(!res){
            return 1;
        }else{
            sector++;
            buf=buf+512;
        }
    }
    return 0;
}