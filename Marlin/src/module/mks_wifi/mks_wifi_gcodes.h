#ifndef MKS_WIFI_GCODES_H
#define MKS_WIFI_GCODES_H

#include "../../gcode/gcode.h"
#include "../temperature.h"
#include "../../sd/cardreader.h"
#include "mks_wifi.h"

void mks_m991(void);
void mks_m997(void);

#endif