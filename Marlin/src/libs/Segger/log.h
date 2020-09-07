#ifndef LOG_H
#define LOG_H
#include "SEGGER_RTT.h"
#include "../../module/mks_wifi/debug_to_uart.h"

//#define DEBUG_MSG
//#define INFO_MSG
//#define WARNING_MSG
//#define ERROR_MSG

//#define COLOR_LOG_RTT 

//#define DEBUG_TO_UART
#define DEBUG_TO_SEGGER_RTT

#ifdef COLOR_LOG_RTT

    #ifdef DEBUG_MSG
        #define DEBUG(fmt, args...) SEGGER_RTT_printf(0,"%sDEBUG %-20s:%-4d [%d]:" fmt "%s\r\n",RTT_CTRL_TEXT_BLUE,  __func__, __LINE__,dwt_get_tick_in_sec(), ## args, RTT_CTRL_RESET)
    #else
        #define DEBUG(fmt, args...)
    #endif
    #ifdef INFO_MSG
        #define INFO(fmt, args...)  SEGGER_RTT_printf(0,"%s[I] %-20s:%-4d [%d]:" fmt "%s\r\n",RTT_CTRL_TEXT_WHITE, __func__, __LINE__,dwt_get_tick_in_sec(), ## args,RTT_CTRL_RESET)
    #else
        #define INFO(fmt, args...)
    #endif
    #ifdef WARNING_MSG
        #define WARNING(fmt, args...) SEGGER_RTT_printf(0,"%s[W] %-20s:%-4d [%d]:" fmt "%s\r\n",RTT_CTRL_TEXT_BRIGHT_YELLOW, __func__, __LINE__,dwt_get_tick_in_sec(), ## args,RTT_CTRL_RESET)
    #else
        #define WARNING(fmt, args...)
    #endif
    #ifdef ERROR_MSG
        #define ERROR(fmt, args...) SEGGER_RTT_printf(0,"%s[E] %-20s:%-4d [%d]:" fmt "%s\r\n",RTT_CTRL_TEXT_RED,  __func__, __LINE__,dwt_get_tick_in_sec(),## args,RTT_CTRL_RESET)
    #else
        #define ERROR(fmt, args...)
    #endif
#else
    #ifdef DEBUG_TO_UART

    #ifdef DEBUG_MSG
        #define DEBUG(fmt, args...) debug_to_uart((char*)"[D] %-20s:%-4d :" fmt "\n", __func__, __LINE__, ## args)
    #else
        #define DEBUG(fmt, args...)
    #endif
    #ifdef INFO_MSG
        #define INFO(fmt, args...)  debug_to_uart((char*)"[I] %-20s:%-4d :" fmt "\n", __func__, __LINE__, ## args)
    #else
        #define INFO(fmt, args...)
    #endif
    #ifdef WARNING_MSG
        #define WARNING(fmt, args...) debug_to_uart((char*)"[W] %-20s:%-4d :" fmt "\n",  __func__, __LINE__, ## args)
    #else
        #define WARNING(fmt, args...)
    #endif
    #ifdef ERROR_MSG
        #define ERROR(fmt, args...) debug_to_uart((char*)"[E] %-20s:%-4d :" fmt "\n",  __func__, __LINE__,## args)
    #else
        #define ERROR(fmt, args...)
    #endif

    #endif

    #ifdef DEBUG_TO_SEGGER_RTT

    #ifdef DEBUG_MSG
        #define DEBUG(fmt, args...) SEGGER_RTT_printf(0,"[D] %-20s:%-4d :" fmt "\r\n", __func__, __LINE__, ## args)
    #else
        #define DEBUG(fmt, args...)
    #endif
    #ifdef INFO_MSG
        #define INFO(fmt, args...)  SEGGER_RTT_printf(0,"[I] %-20s:%-4d :" fmt "\n", __func__, __LINE__, ## args)
    #else
        #define INFO(fmt, args...)
    #endif
    #ifdef WARNING_MSG
        #define WARNING(fmt, args...) SEGGER_RTT_printf(0,"[W] %-20s:%-4d :" fmt "\n",  __func__, __LINE__, ## args)
    #else
        #define WARNING(fmt, args...)
    #endif
    #ifdef ERROR_MSG
        #define ERROR(fmt, args...) SEGGER_RTT_printf(0,"[E] %-20s:%-4d :" fmt "\n",  __func__, __LINE__,## args)
    #else
        #define ERROR(fmt, args...)
    #endif

    #endif

#endif

#endif
