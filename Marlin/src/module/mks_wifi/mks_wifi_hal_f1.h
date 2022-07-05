#ifndef MKS_WIFI_HAL_F1_H
#define MKS_WIFI_HAL_F1_H

#define DMA_TIMEOUT 0x1ffffff
#define ESP_PACKET_SIZE     1024

#define DMA_CONF    (unsigned int)(DMA_CCR_PL|DMA_CCR_MINC|DMA_CCR_TEIE|DMA_CCR_TCIE)
#define DMA_CLEAR   (unsigned int)(DMA_IFCR_CGIF5|DMA_IFCR_CTEIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTCIF5)

void mks_wifi_hw_prepare(unsigned int buf, unsigned int count);
void mks_wifi_empty_uart(void);
void mks_wifi_hw_restore(void);
void mks_wifi_disable_dma(void);
void mks_wifi_sys_rst(void);
void wd_reset(void);
void mks_wifi_hw_deinit_sd(void);

#ifdef MAPLE_STM32F1
void NVIC_SetPriority(int IRQn, unsigned int priority);
void NVIC_EnableIRQ(int IRQn);
void NVIC_DisableIRQ(int IRQn);
#endif

#endif