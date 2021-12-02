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

#if HAS_TFT_LVGL_UI
  #define BUF_SIZE_KB                       14
#endif

#define EXT_EXTRUDER_DRIVER 0 // Если нужен сменный драйвер в слоте второго экструдера как основной экструдер, установить в единицу!

#if EXT_EXTRUDER_DRIVER
  #undef E1_ENABLE_PIN
  #undef E1_STEP_PIN
  #undef E1_DIR_PIN
  #undef E0_ENABLE_PIN
  #undef E0_STEP_PIN
  #undef E0_DIR_PIN

  #define E0_ENABLE_PIN                       PA3
  #define E0_STEP_PIN                         PA6
  #define E0_DIR_PIN                          PA1
#endif
