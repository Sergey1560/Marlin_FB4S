/**
MKS Robin Nano
U5 W25Q64BV, 16K SERIAL EEPROM: 


*/
#include "../../inc/MarlinConfig.h"

#if ENABLED(SPI_EEPROM_W25Q)

#include "../HAL.h"
#include "../../module/mks_wifi/small_cmsis.h"
#include "../../module/mks_wifi/dwt.h"

#define SPI_DIR_READ  0
#define SPI_DIR_WRITE 1

#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

#define SPI_EEPROM_SIZE 2048
#define SPIFLASH_PAGESIZE 256
#define SPI_TIMEOUT 2000 //таймаут на ожидание опереций 
#define CHECK_TIMEOUT do{if(dwt_get_timeout() == 0){ERROR("Timeout");return 0;}}while(0)

#define SPI2_START  PORTB->BSRR=GPIO_BSRR_BR12
#define SPI2_STOP   PORTB->BSRR=GPIO_BSRR_BS12

volatile uint8_t spi_eeprom[SPI_EEPROM_SIZE];

uint8_t spi_send(uint8_t data);
void spi_read(uint32_t addr, uint8_t *buf, uint32_t len);
void spi_write(uint32_t addr, uint8_t *buf, uint32_t len);
uint8_t spi_read_status(void);


void eeprom_hw_init(void){
    uint32_t tmp;
    uint8_t device_id, manuf_id;
    uint16_t chip_id;
   
/*
SPI2
MISO - PB14 Input floating / Input pull-up
MOSI - PB15 Alternate function push-pull
SCK -  PB13 Alternate function push-pull
CS -   PB12 Out push-pull
*/

    DEBUG("Start SPI");
    
    dwt_init();

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN|RCC_APB2ENR_IOPAEN|RCC_APB2ENR_AFIOEN;

    tmp = PORTB->CRH;
    tmp &= ~(GPIO_CRH_MODE14|GPIO_CRH_CNF14|GPIO_CRH_CNF12|GPIO_CRH_CNF13|GPIO_CRH_CNF14|GPIO_CRH_CNF15);
    tmp |= (GPIO_CRH_MODE12|GPIO_CRH_MODE13|GPIO_CRH_MODE15|GPIO_CRH_CNF13_1|GPIO_CRH_CNF15_1|GPIO_CRH_CNF14_0);
    PORTB->CRH = tmp;

	//CS PIN
	tmp= PORTA->CRL;
	tmp &= ~GPIO_CRL_CNF7;
    tmp |= GPIO_CRL_MODE7;
    PORTA->CRL = tmp;

    PORTA->BSRR = GPIO_BSRR_BS7;

    SPI2_STOP;

    RCC->APB1ENR|= RCC_APB1ENR_SPI2EN;

    SPI2->CR1 = SPI_CR1_SSM|\
                SPI_CR1_SSI|\
                (4 << SPI_CR1_BR_Pos)|\
                SPI_CR1_MSTR;
            
    SPI2->CR1 |= SPI_CR1_SPE;

    //Wake up
    SPI2_START;
    spi_send(W25X_ReleasePowerDown);
    SPI2_STOP;

    for(uint32_t i=0; i<0x1000; i++){NOP;} //3us для выхода из power down

    //Device ID
    SPI2_START;
    spi_send(W25X_DeviceID);
    for(uint32_t i=0; i<3; i++){spi_send(0);}
    device_id = spi_send(0);
    SPI2_STOP;

    //Jedec ID
    SPI2_START;
    spi_send(W25X_JedecDeviceID);
    manuf_id = spi_send(0);
    chip_id = spi_send(0) << 8;
    chip_id |= spi_send(0);
    DEBUG("W25Q Device ID %0X Manuf ID: %0X Chip ID %0X",device_id,manuf_id,chip_id);
    SPI2_STOP;

    spi_read(SPI_EEPROM_OFFSET,(uint8_t *)spi_eeprom,SPI_EEPROM_SIZE);
}

void eeprom_hw_deinit(void){

    DEBUG("Finish SPI");
    //Write Enable
    SPI2_START;
    spi_send(W25X_WriteEnable);
    SPI2_STOP;

    while (spi_read_status() & 1){  //Busy
        NOP;
    }

    //Erase 4K
    SPI2_START;
    spi_send(W25X_SectorErase);
    spi_send((SPI_EEPROM_OFFSET >> 16) & 0xFF);
    spi_send((SPI_EEPROM_OFFSET >> 8) & 0xFF);
    spi_send(SPI_EEPROM_OFFSET & 0xFF);
    SPI2_STOP;

    while (spi_read_status() & 1){  //Busy
        NOP;
    }
    //write
    spi_write(SPI_EEPROM_OFFSET,(uint8_t *)spi_eeprom,SPI_EEPROM_SIZE);
    //deinit spi

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


uint8_t spi_send(uint8_t data){
    while((SPI2->SR & SPI_SR_TXE) == 0){NOP;};
    SPI2->DR = data;
    
    while((SPI2->SR & SPI_SR_RXNE) == 0){NOP;};
    return SPI2->DR;
}


void spi_read(uint32_t addr, uint8_t *buf, uint32_t len){

    if( (len == 0) || (len > SPI_EEPROM_SIZE) ){
        ERROR("Len size error: %d",len);
        return;
    }

    addr &= 0xFFFFFF; //24bit address

    SPI2_START;
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
    SPI2_STOP;
}

void spi_write(uint32_t addr, uint8_t *buf, uint32_t len){

    uint16_t bytes_in_page = SPIFLASH_PAGESIZE - (addr % SPIFLASH_PAGESIZE);
    uint16_t offset = 0;

    addr &= 0xFFFFFF; //24bit address
    
    while (spi_read_status() & 1){  //Busy
        NOP;
    }
        //Write Enable

    while (len > 0){
        uint16_t batch_size = (len <= bytes_in_page) ? len : bytes_in_page;

        SPI2_START;
        spi_send(W25X_WriteEnable);
        SPI2_STOP;

        while (spi_read_status() & 1){  //Busy
            NOP;
        }

        SPI2_START;
        spi_send(W25X_PageProgram);
        spi_send((addr >> 16) & 0xFF);
        spi_send((addr >> 8) & 0xFF);
        spi_send(addr & 0xFF);

        for (uint32_t i = 0; i < batch_size; i++){
            spi_send(((uint8_t*)buf)[offset + i]);
        }
        
        SPI2_STOP;

        //wait till it's programmed
        while (spi_read_status() & 2){  //Busy
            NOP;
        }

        addr += batch_size;
        offset += batch_size;
        len -= batch_size;
        bytes_in_page = SPIFLASH_PAGESIZE;
    }

}


uint8_t spi_read_status(void){
    uint8_t data;
    
    SPI2_START;
    spi_send(W25X_ReadStatusReg);
    data = spi_send(0);
    SPI2_STOP;
    return data;
}


#endif // SPI_EEPROM_W25Q
