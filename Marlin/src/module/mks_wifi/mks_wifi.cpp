#include "mks_wifi.h"

void mks_wifi_init(void){
    DEBUG("Init MKS WIFI");
    SET_INPUT_PULLUP(MKS_WIFI_IO0);
    attachInterrupt(MKS_WIFI_IO0, mks_wifi_io0_irq, FALLING);
}


void mks_wifi_io0_irq(void){

    INFO("IO0 Irq");

}

