#include "small_spi.h"
#include "../../inc/MarlinConfig.h"

/*
SPI2
MISO - PB14 Input floating / Input pull-up
MOSI - PB15 Alternate function push-pull
SCK  -  PB13 Alternate function push-pull
W25Q  CS - PB12 Out push-pull
TOUCH CS - PA7
*/

void spi2_init(uint8_t prescaler){
    uint32_t tmp;

    if(prescaler > SPI_FREQ_140Khz){
        prescaler = SPI_FREQ_140Khz;
    }

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

    SPI2_STOP_ALL;

    RCC->APB1ENR|= RCC_APB1ENR_SPI2EN;

    SPI2->CR1 = SPI_CR1_SSM|\
                SPI_CR1_SSI|\
                (prescaler << SPI_CR1_BR_Pos)|\
                SPI_CR1_MSTR;
            
    SPI2->CR1 |= SPI_CR1_SPE;
}

uint8_t spi_send(uint8_t data){
    while((SPI2->SR & SPI_SR_TXE) == 0){NOP;};
    SPI2->DR = data;
    
    while((SPI2->SR & SPI_SR_RXNE) == 0){NOP;};
    return SPI2->DR;
}
