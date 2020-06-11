#ifndef SMALL_SPI_H
#define SMALL_SPI_H

#include "../HAL.h"
#include "../../module/mks_wifi/small_cmsis.h"

#define SPI_FREQ_18Mhz    (uint8_t)0
#define SPI_FREQ_9Mhz     (uint8_t)1
#define SPI_FREQ_4_5Mhz   (uint8_t)2
#define SPI_FREQ_2_25Mhz  (uint8_t)3
#define SPI_FREQ_1_125Mhz (uint8_t)4
#define SPI_FREQ_560KHz   (uint8_t)5
#define SPI_FREQ_280KHz   (uint8_t)6
#define SPI_FREQ_140Khz   (uint8_t)7

#define SPI_DIR_READ  0
#define SPI_DIR_WRITE 1

#define W25Q_START      do{PORTB->BSRR=GPIO_BSRR_BR12;PORTA->BSRR=GPIO_BSRR_BS7;}while(0)
#define W25Q_STOP       PORTB->BSRR=GPIO_BSRR_BS12

#define TOUCH_CS_START  do{PORTB->BSRR=GPIO_BSRR_BS12;PORTA->BSRR=GPIO_BSRR_BR7;}while(0)
#define TOUCH_CS_STOP   PORTA->BSRR=GPIO_BSRR_BS7

#define SPI2_STOP_ALL   do{PORTB->BSRR=GPIO_BSRR_BS12;PORTA->BSRR=GPIO_BSRR_BS7;}while(0)


uint8_t spi_send(uint8_t data);
void spi_read(uint32_t addr, uint8_t *buf, uint32_t len);
void spi_write(uint32_t addr, uint8_t *buf, uint32_t len);
void spi2_init(uint8_t prescaler);


#endif