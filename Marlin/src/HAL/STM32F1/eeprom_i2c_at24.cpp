/**
 
AT24C16, 16K SERIAL EEPROM: 
Internally organized with 128 pages of 16 bytes each (2048 bytes)

16K requires an 11-bit data word address for random word addressing.

The 16K does not use any device address bits but instead the 3 bits are used for mem-
ory page addressing. These page addressing bits on the 4K, 8K and 16K devices
should be considered the most significant bits of the data word address which follows.
The A0, A1 and A2 pins are no connect.

*/
#include "../../inc/MarlinConfig.h"

#if ENABLED(I2C_EEPROM_AT24C16)

#include "../HAL.h"
#include "../../module/mks_wifi/small_cmsis.h"
#include "../../module/mks_wifi/dwt.h"

#define DEV_ADDR  0xA0
#define FSMC_DISABLE  RCC->AHBENR &= ~RCC_AHBENR_FSMCEN  //Конфликт на ноге FSMC_NADV с I2C. На время передачи приходится отключать FSMC
#define FSMC_RESTORE  RCC->AHBENR |= RCC_AHBENR_FSMCEN;

#define I2C_TIMEOUT 2000 //таймаут на ожидание опереций I2C. 

#define CHECK_TIMEOUT do{if(dwt_get_timeout() == 0){ERROR("Timeout");return 0;}}while(0)

static bool waitSRBitSet(uint32_t Bit);
static uint8_t i2c_write(const uint8_t hw_adr, uint8_t *data, uint32_t len);
static uint8_t i2c_read(const uint8_t hw_adr, uint16_t addr, uint8_t *data, uint32_t len);

void eeprom_hw_deinit(void){
  DEBUG("Finish I2C");
}

void eeprom_init(void){
/*
PB6 SCL Alternate function open drain
PB7 SDA Alternate function open drain
*/
  DEBUG("Init I2C");
  dwt_init();

  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN|RCC_APB2ENR_AFIOEN;
  PORTB->CRL |= (GPIO_CRL_MODE6|GPIO_CRL_MODE7|GPIO_CRL_CNF6|GPIO_CRL_CNF7);
  
  AFIO->MAPR2 |= AFIO_MAPR2_FSMC_NADV_REMAP; //Remap по факту не работает, бит не устанавливается.
  RCC->APB1ENR|= RCC_APB1ENR_I2C1EN;

  I2C1->CR1 = I2C_CR1_SWRST;
  I2C1->CR1 = 0;  
  
  //Тактовая 72Mhz, PCLK 36Mhz
  I2C1->CCR = (180  << I2C_CCR_CCR_Pos);
  I2C1->CR2 = (36 << I2C_CR2_FREQ_Pos);
  I2C1->TRISE = 37;
  I2C1->CR1 = I2C_CR1_PE;
}

void eeprom_write_byte(uint8_t *pos, unsigned char value){
  uint8_t data[2];

  FSMC_DISABLE;

  data[0]=(uint8_t)((unsigned)pos % 256);
  data[1]=(uint8_t)(value);
  
  if(!i2c_write((DEV_ADDR+(uint8_t)(((unsigned)pos/256)<<1)),data,2)){
    ERROR("write failed");
  }
  safe_delay(20);	//Задержка на время пока eeprom пишет.
  FSMC_RESTORE;
}

uint8_t eeprom_read_byte(uint8_t *pos) {
  uint8_t data;

  FSMC_DISABLE;
  
  if(!i2c_read(DEV_ADDR, (uint16_t)((unsigned)pos), &data, 1)){
    ERROR("read failed");
    data=0;
  }
  
  safe_delay(1); //небольшая пауза перед включением FSMC, чтобы состояние STOP успело выставиться на линии.
  FSMC_RESTORE;
  return data;
}

void eeprom_read_block(void *__dst, const void *__src, size_t __n){
  ERROR("Call to missing function");
};

void eeprom_update_block(const void *__src, void *__dst, size_t __n){
  ERROR("Call to missing function");
};

static uint8_t i2c_write(const uint8_t hw_adr, uint8_t *data, uint32_t len){
    
    //DEBUG("i2c write at %d val %0X",data[0],data[1]);    
    
    dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait busy");
    while(I2C1->SR2 & I2C_SR2_BUSY) {CHECK_TIMEOUT;};
    

    I2C1->CR1 = I2C_CR1_PE | I2C_CR1_START;
    dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait SB");
    while(!(I2C1->SR1 & I2C_SR1_SB)) {CHECK_TIMEOUT;};
    I2C1->DR = (hw_adr & 0xFE);
    
    if(!waitSRBitSet(I2C_SR1_ADDR)) return false;
    (void)I2C1->SR2;
    
    while(len--){
      if(!waitSRBitSet(I2C_SR1_TXE)) return false;
      I2C1->DR = *data++;    
    }
    
    dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait BTF");
    while(!((I2C1->SR1 & I2C_SR1_TXE) && (I2C1->SR1 & I2C_SR1_BTF))) {CHECK_TIMEOUT;};   
    I2C1->CR1 = I2C_CR1_PE | I2C_CR1_STOP;
    
    return 1;
  }
  
static uint8_t i2c_read(const uint8_t hw_adr, uint16_t addr, uint8_t *data, uint32_t len){

		dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait busy");
    while(I2C1->SR2 & I2C_SR2_BUSY) {CHECK_TIMEOUT;}; 
    
    //Запись адреса
    I2C1->CR1 = I2C_CR1_PE | I2C_CR1_START;
    
    dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait SB");
    while(!(I2C1->SR1 & I2C_SR1_SB)) {CHECK_TIMEOUT;};  //Условие старт

    
    I2C1->DR = ((hw_adr & 0xFE) + ((addr/256) << 1));
    if(!waitSRBitSet(I2C_SR1_ADDR)) return false; //i2c адрес отправлен
    I2C1->SR2;
    
    if(!waitSRBitSet(I2C_SR1_TXE)) return false;
    I2C1->DR = addr%256;                         //адрес в памяти отправлен
    
    dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait BTF");
    while(!((I2C1->SR1 & I2C_SR1_TXE) && (I2C1->SR1 & I2C_SR1_BTF))) {CHECK_TIMEOUT;};   

    //Чтение
    I2C1->CR1 = I2C_CR1_PE | I2C_CR1_START | I2C_CR1_ACK;
    
    dwt_settimeout(I2C_TIMEOUT);
    //DEBUG("Wait SB");
    while(!(I2C1->SR1 & I2C_SR1_SB)) {CHECK_TIMEOUT;};
    I2C1->DR = hw_adr|1;      

    if(!waitSRBitSet(I2C_SR1_ADDR)) return false;
    I2C1->SR2;
    I2C1->CR1 = I2C_CR1_PE | I2C_CR1_STOP;
        
    if(!waitSRBitSet(I2C_SR1_RXNE)) return false;        
    *data = I2C1->DR;
        
    return true;
  }
  

static bool waitSRBitSet(uint32_t Bit){
    uint32_t sr;
    
    dwt_settimeout(I2C_TIMEOUT);
    do{
      sr = I2C1->SR1;
      if(sr & ( I2C_SR1_AF | I2C_SR1_ARLO | I2C_SR1_BERR)){
        I2C1->CR1 = I2C_CR1_PE | I2C_CR1_STOP;
        I2C1->SR1 = 0;
        ERROR("I2C Error flag %0X",sr);
        return false;
      }  
      if(dwt_get_timeout() == 0){
        ERROR("Timeout %0X",Bit);
        return false;
      }

    }while(!(sr & Bit));
    
    return true;
};


#endif // I2C_EEPROM
