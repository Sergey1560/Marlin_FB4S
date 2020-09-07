#include "dwt.h"

#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"

volatile uint32_t timeout;

/*
Счетчик за секунду "щелкает" SYS_CLK (72 000 000) раз.
DWT->CYCCNT 32-bit, 4294967295 / 72000000 = 59,6 секунд до переполнения
*/


void dwt_settimeout(uint32_t time){

    if(time > (MAX_TIMEOUT-1)){
        DEBUG("Timeout too much, reset to %d",MAX_TIMEOUT);
        time = MAX_TIMEOUT;
    }

    //DEBUG("Set timeout %d %d",time, time * (SYS_CLK / 1000));

    timeout = time * (SYS_CLK / 1000);
    DWT->CYCCNT = 0;
}

uint32_t dwt_get_timeout(void){
    volatile uint32_t current_timer = DWT->CYCCNT;
    
    if(current_timer >= timeout) {
        DEBUG("TO %d %d",current_timer,timeout);
        timeout = 0;
        return 0;
    }
    
    return 1;
}


void dwt_init(void){

	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

}


uint32_t dwt_get_tick(void){
    return DWT->CYCCNT;
}

uint32_t dwt_get_tick_in_sec(void){
    return DWT->CYCCNT/(SYS_CLK/1000);
}

uint32_t dwt_get_diff_tick(uint32_t tick){
    uint32_t result=0;

    if(DWT->CYCCNT > tick){
        result=DWT->CYCCNT-tick;
    }else{
        result=(uint32_t)(0xFFFFFFFF-tick)+DWT->CYCCNT;
    };

    return result;
}

uint32_t dwt_get_diff_sec(uint32_t tick){

    return dwt_get_diff_tick(tick)/(SYS_CLK/1000);
}


