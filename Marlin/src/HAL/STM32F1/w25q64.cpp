#include "w25q64.h"

volatile uint8_t *spi_eeprom=shared_mem;

volatile uint32_t spi_cr;

void w25q_set_spi_speed(void){

    spi_cr = SPI2->CR1;
    spi2_init(SPI_FREQ_18Mhz);

}

void w25q_restore_spi_speed(void){

    spi2_init(SPI_FREQ_280KHz);

}


void w25q_init(void){
    uint8_t device_id, manuf_id;
    uint16_t chip_id;

    dwt_init();

    spi2_init(SPI_FREQ_4_5Mhz);

    //Wake up
    W25Q_START;
    spi_send(W25X_ReleasePowerDown);
    W25Q_STOP;

    for(uint32_t i=0; i<0x1000; i++){NOP;} //3us для выхода из power down

    //Device ID
    W25Q_START;
    spi_send(W25X_DeviceID);
    for(uint32_t i=0; i<3; i++){spi_send(0);}
    device_id = spi_send(0);
    W25Q_STOP;

    //Jedec ID
    W25Q_START;
    spi_send(W25X_JedecDeviceID);
    manuf_id = spi_send(0);
    chip_id = spi_send(0) << 8;
    chip_id |= spi_send(0);
    DEBUG("W25Q Device ID %0X Manuf ID: %0X Chip ID %0X",device_id,manuf_id,chip_id);
    W25Q_STOP;
}

void w25q_read(uint32_t addr, uint8_t *buf, uint32_t len){

    if( (len == 0) || (len > SPI_EEPROM_SIZE) ){
        ERROR("Len size error: %d",len);
        return;
    }

    addr &= 0xFFFFFF; //24bit address

    W25Q_START;
    if(len == 1){
        spi_send(W25X_ReadData);
        spi_send((addr >> 16) & 0xFF);
        spi_send((addr >> 8) & 0xFF);
        spi_send(addr & 0xFF);
    }else{
        spi_send(W25X_FastReadData);
        spi_send((addr >> 16) & 0xFF);
        spi_send((addr >> 8) & 0xFF);
        spi_send(addr & 0xFF);
        spi_send(0);
    }

    while (len--){
        *buf++ = spi_send(0);
    }
    W25Q_STOP;
}

void w25q_write(uint32_t addr, uint8_t *buf, uint32_t len){

    uint16_t bytes_in_page = SPIFLASH_PAGESIZE - (addr % SPIFLASH_PAGESIZE);
    uint16_t offset = 0;

    addr &= 0xFFFFFF; //24bit address
    
    while (w25q_read_status() & 1){  //Busy
        NOP;
    }
        //Write Enable

    while (len > 0){
        uint16_t batch_size = (len <= bytes_in_page) ? len : bytes_in_page;

        W25Q_START;
        spi_send(W25X_WriteEnable);
        W25Q_STOP;

        while (w25q_read_status() & 1){  //Busy
            NOP;
        }

        W25Q_START;
        spi_send(W25X_PageProgram);
        spi_send((addr >> 16) & 0xFF);
        spi_send((addr >> 8) & 0xFF);
        spi_send(addr & 0xFF);

        for (uint32_t i = 0; i < batch_size; i++){
            spi_send(((uint8_t*)buf)[offset + i]);
        }
        
        W25Q_STOP;

        //wait till it's programmed
        while (w25q_read_status() & 2){  //Busy
            NOP;
        }

        addr += batch_size;
        offset += batch_size;
        len -= batch_size;
        bytes_in_page = SPIFLASH_PAGESIZE;
    }

}


uint8_t w25q_read_status(void){
    uint8_t data;
    
    W25Q_START;
    spi_send(W25X_ReadStatusReg);
    data = spi_send(0);
    W25Q_STOP;
    return data;
}

void w25q_write_enable(void){
    //Write Enable
    W25Q_START;
    spi_send(W25X_WriteEnable);
    W25Q_STOP;

    while (w25q_read_status() & 1){  //Busy
        NOP;
    }
}


void w25q_sector_erase(uint32_t addr){

    //Erase 4K
    W25Q_START;
    spi_send(W25X_SectorErase);
    spi_send((addr >> 16) & 0xFF);
    spi_send((addr >> 8) & 0xFF);
    spi_send(addr & 0xFF);
    W25Q_STOP;

    while (w25q_read_status() & 1){  //Busy
        NOP;
    }

}
