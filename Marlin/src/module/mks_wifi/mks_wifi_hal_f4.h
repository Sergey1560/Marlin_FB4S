#ifndef MKS_WIFI_HAL_F4_H
#define MKS_WIFI_HAL_F4_H

#include "../../MarlinCore.h"

#define DMA_TIMEOUT 0x1ffffff
#define ESP_PACKET_SIZE     1024

#define DMA_CONF			((uint32_t)( (0x04 << DMA_SxCR_CHSEL_Pos) | \
										 (0x00 << DMA_SxCR_MBURST_Pos)| \
										 (0x00 << DMA_SxCR_PBURST_Pos)| \
										 (0x00 << DMA_SxCR_DBM_Pos)   | \
										 (0x00 << DMA_SxCR_PL_Pos)	  | \
										 (0x00 << DMA_SxCR_PINCOS_Pos)| \
										 (0x00 << DMA_SxCR_MSIZE_Pos) | \
										 (0x00 << DMA_SxCR_PSIZE_Pos) | \
										 (0x01 << DMA_SxCR_MINC_Pos)  | \
										 (0x00 << DMA_SxCR_PINC_Pos)  | \
										 (0x00 << DMA_SxCR_CIRC_Pos)  | \
										 (0x01 << DMA_SxCR_TCIE_Pos)  | \
										 (0x01 << DMA_SxCR_TEIE_Pos)  | \
										 (0x00 << DMA_SxCR_PFCTRL_Pos)))

#define DMA_S5_CLEAR            (uint32_t)(DMA_HIFCR_CTCIF5 | DMA_HIFCR_CTEIF5 | DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CFEIF5 | DMA_HIFCR_CHTIF5)


void mks_wifi_hw_prepare(unsigned int buf, unsigned int count);
void mks_wifi_hw_restore(void);
void mks_wifi_sys_rst(void);
void wd_reset(void);
void mks_wifi_empty_uart(void);
void mks_wifi_disable_dma(void);
void mks_wifi_hw_deinit_sd(void);

#endif