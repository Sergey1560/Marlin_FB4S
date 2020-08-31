/**
MKS Robin Nano
U5 W25Q64BV, 16K SERIAL EEPROM: 


*/
#include "../../inc/MarlinConfig.h"

#if ENABLED(SPI_EEPROM_W25Q)
#include "../../libs/W25Qxx.h"

W25QXXFlash W25QXX;
uint8_t spi_eeprom[MARLIN_EEPROM_SIZE];


void eeprom_init(void){
    DEBUG("Start EEPROM");
    W25QXX.init(SPI_QUARTER_SPEED);
    W25QXX.SPI_FLASH_BufferRead((uint8_t *)spi_eeprom,SPI_EEPROM_OFFSET,MARLIN_EEPROM_SIZE);
}

void eeprom_hw_deinit(void){
    DEBUG("Finish EEPROM");
    W25QXX.SPI_FLASH_WriteEnable();
    W25QXX.SPI_FLASH_SectorErase(SPI_EEPROM_OFFSET);
    //write
    W25QXX.SPI_FLASH_BufferWrite((uint8_t *)spi_eeprom,SPI_EEPROM_OFFSET,MARLIN_EEPROM_SIZE);
}

void eeprom_write_byte(uint8_t *pos, unsigned char value){
    uint16_t addr=(unsigned)pos;

    if(addr < MARLIN_EEPROM_SIZE){
        spi_eeprom[addr]=value;
    }else{
        ERROR("Write out of SPI size: %d %d",addr,MARLIN_EEPROM_SIZE);
    }
}

uint8_t eeprom_read_byte(uint8_t *pos) {
    uint16_t addr=(unsigned)pos;

    if(addr < MARLIN_EEPROM_SIZE){
        return spi_eeprom[addr];
    }else{
        ERROR("Read out of SPI size: %d %d",addr,MARLIN_EEPROM_SIZE);
        return 0;
    }
}

void eeprom_read_block(void *__dst, const void *__src, size_t __n){
  ERROR("Call to missing function");
};

void eeprom_update_block(const void *__src, void *__dst, size_t __n){
  ERROR("Call to missing function");
};

#endif // SPI_EEPROM_W25Q
