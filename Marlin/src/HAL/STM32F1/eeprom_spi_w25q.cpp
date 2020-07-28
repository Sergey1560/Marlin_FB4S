/**
MKS Robin Nano
U5 W25Q64BV, 16K SERIAL EEPROM: 


*/
#include "../../inc/MarlinConfig.h"

#if ENABLED(SPI_EEPROM_W25Q)

#include "w25q64.h"

void eeprom_init(void){
    DEBUG("Start EEPROM");
    w25q_init();
    w25q_read(SPI_EEPROM_OFFSET,(uint8_t *)spi_eeprom,SPI_EEPROM_SIZE);
}

void eeprom_hw_deinit(void){
    DEBUG("Finish EEPROM");
    w25q_write_enable();
    w25q_sector_erase(SPI_EEPROM_OFFSET);
    //write
    w25q_write(SPI_EEPROM_OFFSET,(uint8_t *)spi_eeprom,SPI_EEPROM_SIZE);
}

void eeprom_write_byte(uint8_t *pos, unsigned char value){
    uint16_t addr=(unsigned)pos;

    if(addr < SPI_EEPROM_SIZE){
        spi_eeprom[addr]=value;
    }else{
        ERROR("Write out of SPI size: %d %d",addr,SPI_EEPROM_SIZE);
    }
}

uint8_t eeprom_read_byte(uint8_t *pos) {
    uint16_t addr=(unsigned)pos;

    if(addr < SPI_EEPROM_SIZE){
        return spi_eeprom[addr];
    }else{
        ERROR("Read out of SPI size: %d %d",addr,SPI_EEPROM_SIZE);
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
