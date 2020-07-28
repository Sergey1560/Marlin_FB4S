#ifndef W25Q_HAL_H
#define W25Q_HAL_H
#include "../../inc/MarlinConfig.h"
#include "small_spi.h"
#include "../../module/mks_wifi/dwt.h"
#include "../../module/shared_mem/shared_mem.h"

#define SPI_HI_SPEED 	SPI_FREQ_18Mhz
#define SPI_LOW_SPEED  	SPI_FREQ_1_125Mhz

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

#define SPI_EEPROM_SIZE   MARLIN_EEPROM_SIZE

#define SPIFLASH_PAGESIZE 256
#define SPI_TIMEOUT 2000 //таймаут на ожидание опереций 
#define CHECK_TIMEOUT do{if(dwt_get_timeout() == 0){ERROR("Timeout");return 0;}}while(0)

extern volatile uint8_t *spi_eeprom;

void w25q_init(void);
void w25q_read(uint32_t addr, uint8_t *buf, uint32_t len);
void w25q_write(uint32_t addr, uint8_t *buf, uint32_t len);
uint8_t w25q_read_status(void);
void w25q_write_enable(void);
void w25q_sector_erase(uint32_t addr);

void w25q_set_spi_speed(void);
void w25q_restore_spi_speed(void);

#endif