/**
 * Marlin 3D Printer Firmware
 *
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef __STM32F1__

#include "../../inc/MarlinConfig.h"

#if USE_WIRED_EEPROM

#include "../shared/eeprom_api.h"

bool PersistentStore::access_start() {
  DEBUG("EEPROM start");
  #if ENABLED(SPI_EEPROM)
    #if SPI_CHAN_EEPROM1 == 1
      SET_OUTPUT(BOARD_SPI1_SCK_PIN);
      SET_OUTPUT(BOARD_SPI1_MOSI_PIN);
      SET_INPUT(BOARD_SPI1_MISO_PIN);
      SET_OUTPUT(SPI_EEPROM1_CS);
    #endif
    spiInit(0);
  #endif
  
  #if ANY(I2C_EEPROM_AT24C16, SPI_EEPROM_W25Q)
    eeprom_hw_init();
  #endif
  
  return true;
}
bool PersistentStore::access_finish() { 
  #if ANY(I2C_EEPROM_AT24C16, SPI_EEPROM_W25Q)
    eeprom_hw_deinit();
  #endif

  return true;
   }

bool PersistentStore::write_data(int &pos, const uint8_t *value, size_t size, uint16_t *crc) {
  while (size--) {
    uint8_t * const p = (uint8_t * const)pos;
    uint8_t v = *value;
    uint8_t r_val;
    
    DEBUG("Write to : %d val: %0X",pos,v);
    r_val=eeprom_read_byte((uint16_t *)p);
    
    if (v != r_val) {
      DEBUG("Read val: %0X To write val: %0X",r_val,v);
      eeprom_write_byte((uint16_t *)p, v);
      r_val=eeprom_read_byte((uint16_t *)p);
      DEBUG("Read back val: %0X",r_val);
      if (r_val != v) {
        ERROR("Write error");
        SERIAL_ECHO_MSG(STR_ERR_EEPROM_WRITE);
        return true;
      }
    }
    crc16(crc, &v, 1);
    pos++;
    value++;
  };
  return false;
}

bool PersistentStore::read_data(int &pos, uint8_t* value, size_t size, uint16_t *crc, const bool writing/*=true*/) {
  do {
    DEBUG("Read form: %d",pos);
    uint8_t c = eeprom_read_byte((uint16_t*)pos);
    if (writing && value) *value = c;
    crc16(crc, &c, 1);
    pos++;
    value++;
  } while (--size);
  return false;
}

size_t PersistentStore::capacity() { return E2END + 1; }

#endif // USE_WIRED_EEPROM
#endif // __STM32F1__
