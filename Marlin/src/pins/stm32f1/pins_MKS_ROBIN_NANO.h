/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * MKS Robin nano (STM32F103VET6) board pin assignments
 * https://github.com/makerbase-mks/MKS-Robin-Nano-V1.X/tree/master/hardware
 */

#define ALLOW_STM32DUINO
#include "env_validate.h"

#define BOARD_INFO_NAME "MKS Robin Nano"

//
// Release PB4 (Y_ENABLE_PIN) from JTAG NRST role
//
#define DISABLE_JTAG

//
// Thermocouples
//
//#define TEMP_0_CS_PIN                     PE5   // TC1 - CS1
//#define TEMP_0_CS_PIN                     PE6   // TC2 - CS2

//#define LED_PIN                           PB2

#include "pins_MKS_ROBIN_NANO_common.h"

//#define PRINTER_NAME_FB5
#define PRINTER_NAME_FB4S

#ifdef PRINTER_NAME_FB5
  #ifdef PRINTER_NAME_FB4S
    #error "Select only one printer name"
  #endif
#endif

/*
Управление подсветкой платой в разъеме второго экструдера
Управление ногой En
https://easyeda.com/sst78rust/fb4s-led-control
*/
//#define CASE_LED_INSTEAD_E1

#ifdef CASE_LED_INSTEAD_E1
  #define LED_CASE_PIN                      PA3
#endif


/*
BlTouch
*/
#define SERVO_PIN                           PB2   
#define BL_TOUCH_Z_PIN                      PC4


/*
Управление питанием
https://sergey1560.github.io/fb4s_howto/mks_pwc/
*/
#if ENABLED(MKS_PWC)
    #undef SUICIDE_PIN
    #undef SUICIDE_PIN_STATE
    #undef KILL_PIN
    #undef KILL_PIN_STATE

    #define SUICIDE_PIN                       PE5
    #define SUICIDE_PIN_STATE                 LOW
    #define KILL_PIN                          PA2
    #define KILL_PIN_STATE                    HIGH
#endif

#ifdef PRINTER_NAME_FB5
  #define FIL_RUNOUT_LEVEL  LOW
#endif 

#ifdef PRINTER_NAME_FB4S
  #define FIL_RUNOUT_LEVEL  HIGH
#endif 

#ifndef FIL_RUNOUT_LEVEL
  #define FIL_RUNOUT_LEVEL HIGH
#endif

#if HAS_FSMC_TFT
    #undef TFT_BUFFER_SIZE
    #define TFT_BUFFER_SIZE                  480*8
#endif

/*
Модуль MKS WIFI
*/
#define MKS_WIFI

#ifdef MKS_WIFI

 #define MKS_WIFI_SERIAL_NUM                SERIAL_PORT_2
 #define MKS_WIFI_UART                      USART1
  #undef PLATFORM_M997_SUPPORT

 #define MKS_WIFI_IO0                       PA8
 #define MKS_WIFI_IO4                       PC7
 #define MKS_WIFI_IO_RST                    PA5
#endif


#ifndef XPT2046_X_CALIBRATION
  #define XPT2046_X_CALIBRATION          17880
#endif
#ifndef XPT2046_Y_CALIBRATION
  #define XPT2046_Y_CALIBRATION         -12234
#endif
#ifndef XPT2046_X_OFFSET
  #define XPT2046_X_OFFSET                 -45
#endif
#ifndef XPT2046_Y_OFFSET
  #define XPT2046_Y_OFFSET                  349
#endif


#if HAS_TMC220x
  /**
   * TMC2208/TMC2209 stepper drivers
   */
  //
  // Software serial
  //
  #define X_SERIAL_TX_PIN                   PA6
  #define X_SERIAL_RX_PIN                   PA1

  #define Y_SERIAL_TX_PIN                   PA6
  #define Y_SERIAL_RX_PIN                   PA1

  #define Z_SERIAL_TX_PIN                   PA6
  #define Z_SERIAL_RX_PIN                   PA1

  #define E0_SERIAL_TX_PIN                  PA6
  #define E0_SERIAL_RX_PIN                  PA1

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif