#ifndef DWT_H
#define DWT_H

#include "small_cmsis.h"

#define SYS_CLK (uint32_t)72000000UL
#define MAX_TIMEOUT (uint32_t)((0xFFFFFFFF/SYS_CLK)*1000)


void dwt_init(void);
uint32_t dwt_get_tick(void);
uint32_t dwt_get_diff_tick(uint32_t tick);
uint32_t dwt_get_diff_sec(uint32_t tick);
uint32_t dwt_get_tick_in_sec(void);

void dwt_settimeout(uint32_t timeout);
uint32_t dwt_get_timeout(void);

#endif
