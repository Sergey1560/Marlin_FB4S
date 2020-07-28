#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#ifdef DEBUG_TO_UART

#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"

void debug_to_uart(char *fmt,...);

#endif

#endif