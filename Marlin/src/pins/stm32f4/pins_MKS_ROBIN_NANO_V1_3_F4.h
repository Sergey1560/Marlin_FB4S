/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2021 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * MKS Robin nano V1.3 (STM32F407VET6) board pin assignments
 * https://github.com/makerbase-mks/MKS-Robin-Nano-V1.X/tree/master/hardware
 */

#define ALLOW_STM32DUINO
#include "env_validate.h"

#define BOARD_INFO_NAME "MKS Robin Nano V1.3"

//
// EEPROM
// Use one of these or SDCard-based Emulation will be used
//
#if NO_EEPROM_SELECTED
  //#define SRAM_EEPROM_EMULATION                 // Use BackSRAM-based EEPROM emulation
  //#define FLASH_EEPROM_EMULATION                // Use Flash-based EEPROM emulation
#endif

#define LED_PIN                             PB1

#include "../stm32f1/pins_MKS_ROBIN_NANO_common.h"

#define PRINTER_NAME_FB5

// Если нужен сменный драйвер в слоте второго экструдера как основной экструдер, нужно раскоментировать этот параметр
//#define EXT_EXTRUDER_DRIVER

// repined e1 driver to Z axis
  #undef E1_ENABLE_PIN
  #undef E1_STEP_PIN
  #undef E1_DIR_PIN
  #undef X_ENABLE_PIN
  #undef X_STEP_PIN
  #undef X_DIR_PIN

  #define X_ENABLE_PIN                       PA3
  #define X_STEP_PIN                         PA6
  #define X_DIR_PIN                          PA1

#ifdef EXT_EXTRUDER_DRIVER

  #undef E0_ENABLE_PIN
  #undef E0_STEP_PIN
  #undef E0_DIR_PIN

  #define E0_ENABLE_PIN                       PA3
  #define E0_STEP_PIN                         PA6
  #define E0_DIR_PIN                          PA1
#endif

 #define FIL_RUNOUT_LEVEL  LOW

 #if HAS_FSMC_TFT
    #undef TFT_BUFFER_SIZE
    #define TFT_BUFFER_SIZE                  480*30
#endif

/*
Модуль MKS WIFI
*/
#define MKS_WIFI

#ifdef MKS_WIFI

 #define MKS_WIFI_SERIAL_NUM                SERIAL_PORT_2
 #define MKS_WIFI_UART                      USART1
  #undef PLATFORM_M997_SUPPORT

 #define MKS_WIFI_IO0                       PC13
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
