#ifndef SMALL_CMSIS_H
#define SMALL_CMSIS_H

#include "mks_wifi.h"

#define     __IO    volatile             /*!< Defines 'read / write' permissions */

typedef struct
{
  __IO uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  __IO uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  __IO uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  __IO uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  __IO uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  __IO uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  __IO uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

typedef struct
{
  __IO uint32_t ISR;
  __IO uint32_t IFCR;
} DMA_TypeDef;

typedef struct
{
  __IO uint32_t CCR;
  __IO uint32_t CNDTR;
  __IO uint32_t CPAR;
  __IO uint32_t CMAR;
} DMA_Channel_TypeDef;


#define PERIPH_BASE           0x40000000U /*!< Peripheral base address in the alias region */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000U)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000U)
#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800U)
#define DMA1_BASE             (AHBPERIPH_BASE + 0x00000000U)
#define DMA1_Channel5_BASE    (AHBPERIPH_BASE + 0x00000058U)


#define USART1              ((USART_TypeDef *)USART1_BASE)
#define DMA1                ((DMA_TypeDef *)DMA1_BASE)

#define DMA1_Channel5       ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE)


/******************************************************************************/
/*                                                                            */
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for USART_SR register  *******************/
#define USART_SR_PE_Pos                     (0U)                               
#define USART_SR_PE_Msk                     (0x1U << USART_SR_PE_Pos)          /*!< 0x00000001 */
#define USART_SR_PE                         USART_SR_PE_Msk                    /*!< Parity Error */
#define USART_SR_FE_Pos                     (1U)                               
#define USART_SR_FE_Msk                     (0x1U << USART_SR_FE_Pos)          /*!< 0x00000002 */
#define USART_SR_FE                         USART_SR_FE_Msk                    /*!< Framing Error */
#define USART_SR_NE_Pos                     (2U)                               
#define USART_SR_NE_Msk                     (0x1U << USART_SR_NE_Pos)          /*!< 0x00000004 */
#define USART_SR_NE                         USART_SR_NE_Msk                    /*!< Noise Error Flag */
#define USART_SR_ORE_Pos                    (3U)                               
#define USART_SR_ORE_Msk                    (0x1U << USART_SR_ORE_Pos)         /*!< 0x00000008 */
#define USART_SR_ORE                        USART_SR_ORE_Msk                   /*!< OverRun Error */
#define USART_SR_IDLE_Pos                   (4U)                               
#define USART_SR_IDLE_Msk                   (0x1U << USART_SR_IDLE_Pos)        /*!< 0x00000010 */
#define USART_SR_IDLE                       USART_SR_IDLE_Msk                  /*!< IDLE line detected */
#define USART_SR_RXNE_Pos                   (5U)                               
#define USART_SR_RXNE_Msk                   (0x1U << USART_SR_RXNE_Pos)        /*!< 0x00000020 */
#define USART_SR_RXNE                       USART_SR_RXNE_Msk                  /*!< Read Data Register Not Empty */
#define USART_SR_TC_Pos                     (6U)                               
#define USART_SR_TC_Msk                     (0x1U << USART_SR_TC_Pos)          /*!< 0x00000040 */
#define USART_SR_TC                         USART_SR_TC_Msk                    /*!< Transmission Complete */
#define USART_SR_TXE_Pos                    (7U)                               
#define USART_SR_TXE_Msk                    (0x1U << USART_SR_TXE_Pos)         /*!< 0x00000080 */
#define USART_SR_TXE                        USART_SR_TXE_Msk                   /*!< Transmit Data Register Empty */
#define USART_SR_LBD_Pos                    (8U)                               
#define USART_SR_LBD_Msk                    (0x1U << USART_SR_LBD_Pos)         /*!< 0x00000100 */
#define USART_SR_LBD                        USART_SR_LBD_Msk                   /*!< LIN Break Detection Flag */
#define USART_SR_CTS_Pos                    (9U)                               
#define USART_SR_CTS_Msk                    (0x1U << USART_SR_CTS_Pos)         /*!< 0x00000200 */
#define USART_SR_CTS                        USART_SR_CTS_Msk                   /*!< CTS Flag */

/*******************  Bit definition for USART_DR register  *******************/
#define USART_DR_DR_Pos                     (0U)                               
#define USART_DR_DR_Msk                     (0x1FFU << USART_DR_DR_Pos)        /*!< 0x000001FF */
#define USART_DR_DR                         USART_DR_DR_Msk                    /*!< Data value */

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_DIV_Fraction_Pos          (0U)                               
#define USART_BRR_DIV_Fraction_Msk          (0xFU << USART_BRR_DIV_Fraction_Pos) /*!< 0x0000000F */
#define USART_BRR_DIV_Fraction              USART_BRR_DIV_Fraction_Msk         /*!< Fraction of USARTDIV */
#define USART_BRR_DIV_Mantissa_Pos          (4U)                               
#define USART_BRR_DIV_Mantissa_Msk          (0xFFFU << USART_BRR_DIV_Mantissa_Pos) /*!< 0x0000FFF0 */
#define USART_BRR_DIV_Mantissa              USART_BRR_DIV_Mantissa_Msk         /*!< Mantissa of USARTDIV */

/******************  Bit definition for USART_CR1 register  *******************/
#define USART_CR1_SBK_Pos                   (0U)                               
#define USART_CR1_SBK_Msk                   (0x1U << USART_CR1_SBK_Pos)        /*!< 0x00000001 */
#define USART_CR1_SBK                       USART_CR1_SBK_Msk                  /*!< Send Break */
#define USART_CR1_RWU_Pos                   (1U)                               
#define USART_CR1_RWU_Msk                   (0x1U << USART_CR1_RWU_Pos)        /*!< 0x00000002 */
#define USART_CR1_RWU                       USART_CR1_RWU_Msk                  /*!< Receiver wakeup */
#define USART_CR1_RE_Pos                    (2U)                               
#define USART_CR1_RE_Msk                    (0x1U << USART_CR1_RE_Pos)         /*!< 0x00000004 */
#define USART_CR1_RE                        USART_CR1_RE_Msk                   /*!< Receiver Enable */
#define USART_CR1_TE_Pos                    (3U)                               
#define USART_CR1_TE_Msk                    (0x1U << USART_CR1_TE_Pos)         /*!< 0x00000008 */
#define USART_CR1_TE                        USART_CR1_TE_Msk                   /*!< Transmitter Enable */
#define USART_CR1_IDLEIE_Pos                (4U)                               
#define USART_CR1_IDLEIE_Msk                (0x1U << USART_CR1_IDLEIE_Pos)     /*!< 0x00000010 */
#define USART_CR1_IDLEIE                    USART_CR1_IDLEIE_Msk               /*!< IDLE Interrupt Enable */
#define USART_CR1_RXNEIE_Pos                (5U)                               
#define USART_CR1_RXNEIE_Msk                (0x1U << USART_CR1_RXNEIE_Pos)     /*!< 0x00000020 */
#define USART_CR1_RXNEIE                    USART_CR1_RXNEIE_Msk               /*!< RXNE Interrupt Enable */
#define USART_CR1_TCIE_Pos                  (6U)                               
#define USART_CR1_TCIE_Msk                  (0x1U << USART_CR1_TCIE_Pos)       /*!< 0x00000040 */
#define USART_CR1_TCIE                      USART_CR1_TCIE_Msk                 /*!< Transmission Complete Interrupt Enable */
#define USART_CR1_TXEIE_Pos                 (7U)                               
#define USART_CR1_TXEIE_Msk                 (0x1U << USART_CR1_TXEIE_Pos)      /*!< 0x00000080 */
#define USART_CR1_TXEIE                     USART_CR1_TXEIE_Msk                /*!< PE Interrupt Enable */
#define USART_CR1_PEIE_Pos                  (8U)                               
#define USART_CR1_PEIE_Msk                  (0x1U << USART_CR1_PEIE_Pos)       /*!< 0x00000100 */
#define USART_CR1_PEIE                      USART_CR1_PEIE_Msk                 /*!< PE Interrupt Enable */
#define USART_CR1_PS_Pos                    (9U)                               
#define USART_CR1_PS_Msk                    (0x1U << USART_CR1_PS_Pos)         /*!< 0x00000200 */
#define USART_CR1_PS                        USART_CR1_PS_Msk                   /*!< Parity Selection */
#define USART_CR1_PCE_Pos                   (10U)                              
#define USART_CR1_PCE_Msk                   (0x1U << USART_CR1_PCE_Pos)        /*!< 0x00000400 */
#define USART_CR1_PCE                       USART_CR1_PCE_Msk                  /*!< Parity Control Enable */
#define USART_CR1_WAKE_Pos                  (11U)                              
#define USART_CR1_WAKE_Msk                  (0x1U << USART_CR1_WAKE_Pos)       /*!< 0x00000800 */
#define USART_CR1_WAKE                      USART_CR1_WAKE_Msk                 /*!< Wakeup method */
#define USART_CR1_M_Pos                     (12U)                              
#define USART_CR1_M_Msk                     (0x1U << USART_CR1_M_Pos)          /*!< 0x00001000 */
#define USART_CR1_M                         USART_CR1_M_Msk                    /*!< Word length */
#define USART_CR1_UE_Pos                    (13U)                              
#define USART_CR1_UE_Msk                    (0x1U << USART_CR1_UE_Pos)         /*!< 0x00002000 */
#define USART_CR1_UE                        USART_CR1_UE_Msk                   /*!< USART Enable */

/******************  Bit definition for USART_CR2 register  *******************/
#define USART_CR2_ADD_Pos                   (0U)                               
#define USART_CR2_ADD_Msk                   (0xFU << USART_CR2_ADD_Pos)        /*!< 0x0000000F */
#define USART_CR2_ADD                       USART_CR2_ADD_Msk                  /*!< Address of the USART node */
#define USART_CR2_LBDL_Pos                  (5U)                               
#define USART_CR2_LBDL_Msk                  (0x1U << USART_CR2_LBDL_Pos)       /*!< 0x00000020 */
#define USART_CR2_LBDL                      USART_CR2_LBDL_Msk                 /*!< LIN Break Detection Length */
#define USART_CR2_LBDIE_Pos                 (6U)                               
#define USART_CR2_LBDIE_Msk                 (0x1U << USART_CR2_LBDIE_Pos)      /*!< 0x00000040 */
#define USART_CR2_LBDIE                     USART_CR2_LBDIE_Msk                /*!< LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL_Pos                  (8U)                               
#define USART_CR2_LBCL_Msk                  (0x1U << USART_CR2_LBCL_Pos)       /*!< 0x00000100 */
#define USART_CR2_LBCL                      USART_CR2_LBCL_Msk                 /*!< Last Bit Clock pulse */
#define USART_CR2_CPHA_Pos                  (9U)                               
#define USART_CR2_CPHA_Msk                  (0x1U << USART_CR2_CPHA_Pos)       /*!< 0x00000200 */
#define USART_CR2_CPHA                      USART_CR2_CPHA_Msk                 /*!< Clock Phase */
#define USART_CR2_CPOL_Pos                  (10U)                              
#define USART_CR2_CPOL_Msk                  (0x1U << USART_CR2_CPOL_Pos)       /*!< 0x00000400 */
#define USART_CR2_CPOL                      USART_CR2_CPOL_Msk                 /*!< Clock Polarity */
#define USART_CR2_CLKEN_Pos                 (11U)                              
#define USART_CR2_CLKEN_Msk                 (0x1U << USART_CR2_CLKEN_Pos)      /*!< 0x00000800 */
#define USART_CR2_CLKEN                     USART_CR2_CLKEN_Msk                /*!< Clock Enable */

#define USART_CR2_STOP_Pos                  (12U)                              
#define USART_CR2_STOP_Msk                  (0x3U << USART_CR2_STOP_Pos)       /*!< 0x00003000 */
#define USART_CR2_STOP                      USART_CR2_STOP_Msk                 /*!< STOP[1:0] bits (STOP bits) */
#define USART_CR2_STOP_0                    (0x1U << USART_CR2_STOP_Pos)       /*!< 0x00001000 */
#define USART_CR2_STOP_1                    (0x2U << USART_CR2_STOP_Pos)       /*!< 0x00002000 */

#define USART_CR2_LINEN_Pos                 (14U)                              
#define USART_CR2_LINEN_Msk                 (0x1U << USART_CR2_LINEN_Pos)      /*!< 0x00004000 */
#define USART_CR2_LINEN                     USART_CR2_LINEN_Msk                /*!< LIN mode enable */

/******************  Bit definition for USART_CR3 register  *******************/
#define USART_CR3_EIE_Pos                   (0U)                               
#define USART_CR3_EIE_Msk                   (0x1U << USART_CR3_EIE_Pos)        /*!< 0x00000001 */
#define USART_CR3_EIE                       USART_CR3_EIE_Msk                  /*!< Error Interrupt Enable */
#define USART_CR3_IREN_Pos                  (1U)                               
#define USART_CR3_IREN_Msk                  (0x1U << USART_CR3_IREN_Pos)       /*!< 0x00000002 */
#define USART_CR3_IREN                      USART_CR3_IREN_Msk                 /*!< IrDA mode Enable */
#define USART_CR3_IRLP_Pos                  (2U)                               
#define USART_CR3_IRLP_Msk                  (0x1U << USART_CR3_IRLP_Pos)       /*!< 0x00000004 */
#define USART_CR3_IRLP                      USART_CR3_IRLP_Msk                 /*!< IrDA Low-Power */
#define USART_CR3_HDSEL_Pos                 (3U)                               
#define USART_CR3_HDSEL_Msk                 (0x1U << USART_CR3_HDSEL_Pos)      /*!< 0x00000008 */
#define USART_CR3_HDSEL                     USART_CR3_HDSEL_Msk                /*!< Half-Duplex Selection */
#define USART_CR3_NACK_Pos                  (4U)                               
#define USART_CR3_NACK_Msk                  (0x1U << USART_CR3_NACK_Pos)       /*!< 0x00000010 */
#define USART_CR3_NACK                      USART_CR3_NACK_Msk                 /*!< Smartcard NACK enable */
#define USART_CR3_SCEN_Pos                  (5U)                               
#define USART_CR3_SCEN_Msk                  (0x1U << USART_CR3_SCEN_Pos)       /*!< 0x00000020 */
#define USART_CR3_SCEN                      USART_CR3_SCEN_Msk                 /*!< Smartcard mode enable */
#define USART_CR3_DMAR_Pos                  (6U)                               
#define USART_CR3_DMAR_Msk                  (0x1U << USART_CR3_DMAR_Pos)       /*!< 0x00000040 */
#define USART_CR3_DMAR                      USART_CR3_DMAR_Msk                 /*!< DMA Enable Receiver */
#define USART_CR3_DMAT_Pos                  (7U)                               
#define USART_CR3_DMAT_Msk                  (0x1U << USART_CR3_DMAT_Pos)       /*!< 0x00000080 */
#define USART_CR3_DMAT                      USART_CR3_DMAT_Msk                 /*!< DMA Enable Transmitter */
#define USART_CR3_RTSE_Pos                  (8U)                               
#define USART_CR3_RTSE_Msk                  (0x1U << USART_CR3_RTSE_Pos)       /*!< 0x00000100 */
#define USART_CR3_RTSE                      USART_CR3_RTSE_Msk                 /*!< RTS Enable */
#define USART_CR3_CTSE_Pos                  (9U)                               
#define USART_CR3_CTSE_Msk                  (0x1U << USART_CR3_CTSE_Pos)       /*!< 0x00000200 */
#define USART_CR3_CTSE                      USART_CR3_CTSE_Msk                 /*!< CTS Enable */
#define USART_CR3_CTSIE_Pos                 (10U)                              
#define USART_CR3_CTSIE_Msk                 (0x1U << USART_CR3_CTSIE_Pos)      /*!< 0x00000400 */
#define USART_CR3_CTSIE                     USART_CR3_CTSIE_Msk                /*!< CTS Interrupt Enable */

/******************  Bit definition for USART_GTPR register  ******************/
#define USART_GTPR_PSC_Pos                  (0U)                               
#define USART_GTPR_PSC_Msk                  (0xFFU << USART_GTPR_PSC_Pos)      /*!< 0x000000FF */
#define USART_GTPR_PSC                      USART_GTPR_PSC_Msk                 /*!< PSC[7:0] bits (Prescaler value) */
#define USART_GTPR_PSC_0                    (0x01U << USART_GTPR_PSC_Pos)      /*!< 0x00000001 */
#define USART_GTPR_PSC_1                    (0x02U << USART_GTPR_PSC_Pos)      /*!< 0x00000002 */
#define USART_GTPR_PSC_2                    (0x04U << USART_GTPR_PSC_Pos)      /*!< 0x00000004 */
#define USART_GTPR_PSC_3                    (0x08U << USART_GTPR_PSC_Pos)      /*!< 0x00000008 */
#define USART_GTPR_PSC_4                    (0x10U << USART_GTPR_PSC_Pos)      /*!< 0x00000010 */
#define USART_GTPR_PSC_5                    (0x20U << USART_GTPR_PSC_Pos)      /*!< 0x00000020 */
#define USART_GTPR_PSC_6                    (0x40U << USART_GTPR_PSC_Pos)      /*!< 0x00000040 */
#define USART_GTPR_PSC_7                    (0x80U << USART_GTPR_PSC_Pos)      /*!< 0x00000080 */

#define USART_GTPR_GT_Pos                   (8U)                               
#define USART_GTPR_GT_Msk                   (0xFFU << USART_GTPR_GT_Pos)       /*!< 0x0000FF00 */
#define USART_GTPR_GT                       USART_GTPR_GT_Msk                  /*!< Guard time value */


/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for DMA_ISR register  ********************/
#define DMA_ISR_GIF1_Pos                    (0U)                               
#define DMA_ISR_GIF1_Msk                    (0x1U << DMA_ISR_GIF1_Pos)         /*!< 0x00000001 */
#define DMA_ISR_GIF1                        DMA_ISR_GIF1_Msk                   /*!< Channel 1 Global interrupt flag */
#define DMA_ISR_TCIF1_Pos                   (1U)                               
#define DMA_ISR_TCIF1_Msk                   (0x1U << DMA_ISR_TCIF1_Pos)        /*!< 0x00000002 */
#define DMA_ISR_TCIF1                       DMA_ISR_TCIF1_Msk                  /*!< Channel 1 Transfer Complete flag */
#define DMA_ISR_HTIF1_Pos                   (2U)                               
#define DMA_ISR_HTIF1_Msk                   (0x1U << DMA_ISR_HTIF1_Pos)        /*!< 0x00000004 */
#define DMA_ISR_HTIF1                       DMA_ISR_HTIF1_Msk                  /*!< Channel 1 Half Transfer flag */
#define DMA_ISR_TEIF1_Pos                   (3U)                               
#define DMA_ISR_TEIF1_Msk                   (0x1U << DMA_ISR_TEIF1_Pos)        /*!< 0x00000008 */
#define DMA_ISR_TEIF1                       DMA_ISR_TEIF1_Msk                  /*!< Channel 1 Transfer Error flag */
#define DMA_ISR_GIF2_Pos                    (4U)                               
#define DMA_ISR_GIF2_Msk                    (0x1U << DMA_ISR_GIF2_Pos)         /*!< 0x00000010 */
#define DMA_ISR_GIF2                        DMA_ISR_GIF2_Msk                   /*!< Channel 2 Global interrupt flag */
#define DMA_ISR_TCIF2_Pos                   (5U)                               
#define DMA_ISR_TCIF2_Msk                   (0x1U << DMA_ISR_TCIF2_Pos)        /*!< 0x00000020 */
#define DMA_ISR_TCIF2                       DMA_ISR_TCIF2_Msk                  /*!< Channel 2 Transfer Complete flag */
#define DMA_ISR_HTIF2_Pos                   (6U)                               
#define DMA_ISR_HTIF2_Msk                   (0x1U << DMA_ISR_HTIF2_Pos)        /*!< 0x00000040 */
#define DMA_ISR_HTIF2                       DMA_ISR_HTIF2_Msk                  /*!< Channel 2 Half Transfer flag */
#define DMA_ISR_TEIF2_Pos                   (7U)                               
#define DMA_ISR_TEIF2_Msk                   (0x1U << DMA_ISR_TEIF2_Pos)        /*!< 0x00000080 */
#define DMA_ISR_TEIF2                       DMA_ISR_TEIF2_Msk                  /*!< Channel 2 Transfer Error flag */
#define DMA_ISR_GIF3_Pos                    (8U)                               
#define DMA_ISR_GIF3_Msk                    (0x1U << DMA_ISR_GIF3_Pos)         /*!< 0x00000100 */
#define DMA_ISR_GIF3                        DMA_ISR_GIF3_Msk                   /*!< Channel 3 Global interrupt flag */
#define DMA_ISR_TCIF3_Pos                   (9U)                               
#define DMA_ISR_TCIF3_Msk                   (0x1U << DMA_ISR_TCIF3_Pos)        /*!< 0x00000200 */
#define DMA_ISR_TCIF3                       DMA_ISR_TCIF3_Msk                  /*!< Channel 3 Transfer Complete flag */
#define DMA_ISR_HTIF3_Pos                   (10U)                              
#define DMA_ISR_HTIF3_Msk                   (0x1U << DMA_ISR_HTIF3_Pos)        /*!< 0x00000400 */
#define DMA_ISR_HTIF3                       DMA_ISR_HTIF3_Msk                  /*!< Channel 3 Half Transfer flag */
#define DMA_ISR_TEIF3_Pos                   (11U)                              
#define DMA_ISR_TEIF3_Msk                   (0x1U << DMA_ISR_TEIF3_Pos)        /*!< 0x00000800 */
#define DMA_ISR_TEIF3                       DMA_ISR_TEIF3_Msk                  /*!< Channel 3 Transfer Error flag */
#define DMA_ISR_GIF4_Pos                    (12U)                              
#define DMA_ISR_GIF4_Msk                    (0x1U << DMA_ISR_GIF4_Pos)         /*!< 0x00001000 */
#define DMA_ISR_GIF4                        DMA_ISR_GIF4_Msk                   /*!< Channel 4 Global interrupt flag */
#define DMA_ISR_TCIF4_Pos                   (13U)                              
#define DMA_ISR_TCIF4_Msk                   (0x1U << DMA_ISR_TCIF4_Pos)        /*!< 0x00002000 */
#define DMA_ISR_TCIF4                       DMA_ISR_TCIF4_Msk                  /*!< Channel 4 Transfer Complete flag */
#define DMA_ISR_HTIF4_Pos                   (14U)                              
#define DMA_ISR_HTIF4_Msk                   (0x1U << DMA_ISR_HTIF4_Pos)        /*!< 0x00004000 */
#define DMA_ISR_HTIF4                       DMA_ISR_HTIF4_Msk                  /*!< Channel 4 Half Transfer flag */
#define DMA_ISR_TEIF4_Pos                   (15U)                              
#define DMA_ISR_TEIF4_Msk                   (0x1U << DMA_ISR_TEIF4_Pos)        /*!< 0x00008000 */
#define DMA_ISR_TEIF4                       DMA_ISR_TEIF4_Msk                  /*!< Channel 4 Transfer Error flag */
#define DMA_ISR_GIF5_Pos                    (16U)                              
#define DMA_ISR_GIF5_Msk                    (0x1U << DMA_ISR_GIF5_Pos)         /*!< 0x00010000 */
#define DMA_ISR_GIF5                        DMA_ISR_GIF5_Msk                   /*!< Channel 5 Global interrupt flag */
#define DMA_ISR_TCIF5_Pos                   (17U)                              
#define DMA_ISR_TCIF5_Msk                   (0x1U << DMA_ISR_TCIF5_Pos)        /*!< 0x00020000 */
#define DMA_ISR_TCIF5                       DMA_ISR_TCIF5_Msk                  /*!< Channel 5 Transfer Complete flag */
#define DMA_ISR_HTIF5_Pos                   (18U)                              
#define DMA_ISR_HTIF5_Msk                   (0x1U << DMA_ISR_HTIF5_Pos)        /*!< 0x00040000 */
#define DMA_ISR_HTIF5                       DMA_ISR_HTIF5_Msk                  /*!< Channel 5 Half Transfer flag */
#define DMA_ISR_TEIF5_Pos                   (19U)                              
#define DMA_ISR_TEIF5_Msk                   (0x1U << DMA_ISR_TEIF5_Pos)        /*!< 0x00080000 */
#define DMA_ISR_TEIF5                       DMA_ISR_TEIF5_Msk                  /*!< Channel 5 Transfer Error flag */
#define DMA_ISR_GIF6_Pos                    (20U)                              
#define DMA_ISR_GIF6_Msk                    (0x1U << DMA_ISR_GIF6_Pos)         /*!< 0x00100000 */
#define DMA_ISR_GIF6                        DMA_ISR_GIF6_Msk                   /*!< Channel 6 Global interrupt flag */
#define DMA_ISR_TCIF6_Pos                   (21U)                              
#define DMA_ISR_TCIF6_Msk                   (0x1U << DMA_ISR_TCIF6_Pos)        /*!< 0x00200000 */
#define DMA_ISR_TCIF6                       DMA_ISR_TCIF6_Msk                  /*!< Channel 6 Transfer Complete flag */
#define DMA_ISR_HTIF6_Pos                   (22U)                              
#define DMA_ISR_HTIF6_Msk                   (0x1U << DMA_ISR_HTIF6_Pos)        /*!< 0x00400000 */
#define DMA_ISR_HTIF6                       DMA_ISR_HTIF6_Msk                  /*!< Channel 6 Half Transfer flag */
#define DMA_ISR_TEIF6_Pos                   (23U)                              
#define DMA_ISR_TEIF6_Msk                   (0x1U << DMA_ISR_TEIF6_Pos)        /*!< 0x00800000 */
#define DMA_ISR_TEIF6                       DMA_ISR_TEIF6_Msk                  /*!< Channel 6 Transfer Error flag */
#define DMA_ISR_GIF7_Pos                    (24U)                              
#define DMA_ISR_GIF7_Msk                    (0x1U << DMA_ISR_GIF7_Pos)         /*!< 0x01000000 */
#define DMA_ISR_GIF7                        DMA_ISR_GIF7_Msk                   /*!< Channel 7 Global interrupt flag */
#define DMA_ISR_TCIF7_Pos                   (25U)                              
#define DMA_ISR_TCIF7_Msk                   (0x1U << DMA_ISR_TCIF7_Pos)        /*!< 0x02000000 */
#define DMA_ISR_TCIF7                       DMA_ISR_TCIF7_Msk                  /*!< Channel 7 Transfer Complete flag */
#define DMA_ISR_HTIF7_Pos                   (26U)                              
#define DMA_ISR_HTIF7_Msk                   (0x1U << DMA_ISR_HTIF7_Pos)        /*!< 0x04000000 */
#define DMA_ISR_HTIF7                       DMA_ISR_HTIF7_Msk                  /*!< Channel 7 Half Transfer flag */
#define DMA_ISR_TEIF7_Pos                   (27U)                              
#define DMA_ISR_TEIF7_Msk                   (0x1U << DMA_ISR_TEIF7_Pos)        /*!< 0x08000000 */
#define DMA_ISR_TEIF7                       DMA_ISR_TEIF7_Msk                  /*!< Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_IFCR register  *******************/
#define DMA_IFCR_CGIF1_Pos                  (0U)                               
#define DMA_IFCR_CGIF1_Msk                  (0x1U << DMA_IFCR_CGIF1_Pos)       /*!< 0x00000001 */
#define DMA_IFCR_CGIF1                      DMA_IFCR_CGIF1_Msk                 /*!< Channel 1 Global interrupt clear */
#define DMA_IFCR_CTCIF1_Pos                 (1U)                               
#define DMA_IFCR_CTCIF1_Msk                 (0x1U << DMA_IFCR_CTCIF1_Pos)      /*!< 0x00000002 */
#define DMA_IFCR_CTCIF1                     DMA_IFCR_CTCIF1_Msk                /*!< Channel 1 Transfer Complete clear */
#define DMA_IFCR_CHTIF1_Pos                 (2U)                               
#define DMA_IFCR_CHTIF1_Msk                 (0x1U << DMA_IFCR_CHTIF1_Pos)      /*!< 0x00000004 */
#define DMA_IFCR_CHTIF1                     DMA_IFCR_CHTIF1_Msk                /*!< Channel 1 Half Transfer clear */
#define DMA_IFCR_CTEIF1_Pos                 (3U)                               
#define DMA_IFCR_CTEIF1_Msk                 (0x1U << DMA_IFCR_CTEIF1_Pos)      /*!< 0x00000008 */
#define DMA_IFCR_CTEIF1                     DMA_IFCR_CTEIF1_Msk                /*!< Channel 1 Transfer Error clear */
#define DMA_IFCR_CGIF2_Pos                  (4U)                               
#define DMA_IFCR_CGIF2_Msk                  (0x1U << DMA_IFCR_CGIF2_Pos)       /*!< 0x00000010 */
#define DMA_IFCR_CGIF2                      DMA_IFCR_CGIF2_Msk                 /*!< Channel 2 Global interrupt clear */
#define DMA_IFCR_CTCIF2_Pos                 (5U)                               
#define DMA_IFCR_CTCIF2_Msk                 (0x1U << DMA_IFCR_CTCIF2_Pos)      /*!< 0x00000020 */
#define DMA_IFCR_CTCIF2                     DMA_IFCR_CTCIF2_Msk                /*!< Channel 2 Transfer Complete clear */
#define DMA_IFCR_CHTIF2_Pos                 (6U)                               
#define DMA_IFCR_CHTIF2_Msk                 (0x1U << DMA_IFCR_CHTIF2_Pos)      /*!< 0x00000040 */
#define DMA_IFCR_CHTIF2                     DMA_IFCR_CHTIF2_Msk                /*!< Channel 2 Half Transfer clear */
#define DMA_IFCR_CTEIF2_Pos                 (7U)                               
#define DMA_IFCR_CTEIF2_Msk                 (0x1U << DMA_IFCR_CTEIF2_Pos)      /*!< 0x00000080 */
#define DMA_IFCR_CTEIF2                     DMA_IFCR_CTEIF2_Msk                /*!< Channel 2 Transfer Error clear */
#define DMA_IFCR_CGIF3_Pos                  (8U)                               
#define DMA_IFCR_CGIF3_Msk                  (0x1U << DMA_IFCR_CGIF3_Pos)       /*!< 0x00000100 */
#define DMA_IFCR_CGIF3                      DMA_IFCR_CGIF3_Msk                 /*!< Channel 3 Global interrupt clear */
#define DMA_IFCR_CTCIF3_Pos                 (9U)                               
#define DMA_IFCR_CTCIF3_Msk                 (0x1U << DMA_IFCR_CTCIF3_Pos)      /*!< 0x00000200 */
#define DMA_IFCR_CTCIF3                     DMA_IFCR_CTCIF3_Msk                /*!< Channel 3 Transfer Complete clear */
#define DMA_IFCR_CHTIF3_Pos                 (10U)                              
#define DMA_IFCR_CHTIF3_Msk                 (0x1U << DMA_IFCR_CHTIF3_Pos)      /*!< 0x00000400 */
#define DMA_IFCR_CHTIF3                     DMA_IFCR_CHTIF3_Msk                /*!< Channel 3 Half Transfer clear */
#define DMA_IFCR_CTEIF3_Pos                 (11U)                              
#define DMA_IFCR_CTEIF3_Msk                 (0x1U << DMA_IFCR_CTEIF3_Pos)      /*!< 0x00000800 */
#define DMA_IFCR_CTEIF3                     DMA_IFCR_CTEIF3_Msk                /*!< Channel 3 Transfer Error clear */
#define DMA_IFCR_CGIF4_Pos                  (12U)                              
#define DMA_IFCR_CGIF4_Msk                  (0x1U << DMA_IFCR_CGIF4_Pos)       /*!< 0x00001000 */
#define DMA_IFCR_CGIF4                      DMA_IFCR_CGIF4_Msk                 /*!< Channel 4 Global interrupt clear */
#define DMA_IFCR_CTCIF4_Pos                 (13U)                              
#define DMA_IFCR_CTCIF4_Msk                 (0x1U << DMA_IFCR_CTCIF4_Pos)      /*!< 0x00002000 */
#define DMA_IFCR_CTCIF4                     DMA_IFCR_CTCIF4_Msk                /*!< Channel 4 Transfer Complete clear */
#define DMA_IFCR_CHTIF4_Pos                 (14U)                              
#define DMA_IFCR_CHTIF4_Msk                 (0x1U << DMA_IFCR_CHTIF4_Pos)      /*!< 0x00004000 */
#define DMA_IFCR_CHTIF4                     DMA_IFCR_CHTIF4_Msk                /*!< Channel 4 Half Transfer clear */
#define DMA_IFCR_CTEIF4_Pos                 (15U)                              
#define DMA_IFCR_CTEIF4_Msk                 (0x1U << DMA_IFCR_CTEIF4_Pos)      /*!< 0x00008000 */
#define DMA_IFCR_CTEIF4                     DMA_IFCR_CTEIF4_Msk                /*!< Channel 4 Transfer Error clear */
#define DMA_IFCR_CGIF5_Pos                  (16U)                              
#define DMA_IFCR_CGIF5_Msk                  (0x1U << DMA_IFCR_CGIF5_Pos)       /*!< 0x00010000 */
#define DMA_IFCR_CGIF5                      DMA_IFCR_CGIF5_Msk                 /*!< Channel 5 Global interrupt clear */
#define DMA_IFCR_CTCIF5_Pos                 (17U)                              
#define DMA_IFCR_CTCIF5_Msk                 (0x1U << DMA_IFCR_CTCIF5_Pos)      /*!< 0x00020000 */
#define DMA_IFCR_CTCIF5                     DMA_IFCR_CTCIF5_Msk                /*!< Channel 5 Transfer Complete clear */
#define DMA_IFCR_CHTIF5_Pos                 (18U)                              
#define DMA_IFCR_CHTIF5_Msk                 (0x1U << DMA_IFCR_CHTIF5_Pos)      /*!< 0x00040000 */
#define DMA_IFCR_CHTIF5                     DMA_IFCR_CHTIF5_Msk                /*!< Channel 5 Half Transfer clear */
#define DMA_IFCR_CTEIF5_Pos                 (19U)                              
#define DMA_IFCR_CTEIF5_Msk                 (0x1U << DMA_IFCR_CTEIF5_Pos)      /*!< 0x00080000 */
#define DMA_IFCR_CTEIF5                     DMA_IFCR_CTEIF5_Msk                /*!< Channel 5 Transfer Error clear */
#define DMA_IFCR_CGIF6_Pos                  (20U)                              
#define DMA_IFCR_CGIF6_Msk                  (0x1U << DMA_IFCR_CGIF6_Pos)       /*!< 0x00100000 */
#define DMA_IFCR_CGIF6                      DMA_IFCR_CGIF6_Msk                 /*!< Channel 6 Global interrupt clear */
#define DMA_IFCR_CTCIF6_Pos                 (21U)                              
#define DMA_IFCR_CTCIF6_Msk                 (0x1U << DMA_IFCR_CTCIF6_Pos)      /*!< 0x00200000 */
#define DMA_IFCR_CTCIF6                     DMA_IFCR_CTCIF6_Msk                /*!< Channel 6 Transfer Complete clear */
#define DMA_IFCR_CHTIF6_Pos                 (22U)                              
#define DMA_IFCR_CHTIF6_Msk                 (0x1U << DMA_IFCR_CHTIF6_Pos)      /*!< 0x00400000 */
#define DMA_IFCR_CHTIF6                     DMA_IFCR_CHTIF6_Msk                /*!< Channel 6 Half Transfer clear */
#define DMA_IFCR_CTEIF6_Pos                 (23U)                              
#define DMA_IFCR_CTEIF6_Msk                 (0x1U << DMA_IFCR_CTEIF6_Pos)      /*!< 0x00800000 */
#define DMA_IFCR_CTEIF6                     DMA_IFCR_CTEIF6_Msk                /*!< Channel 6 Transfer Error clear */
#define DMA_IFCR_CGIF7_Pos                  (24U)                              
#define DMA_IFCR_CGIF7_Msk                  (0x1U << DMA_IFCR_CGIF7_Pos)       /*!< 0x01000000 */
#define DMA_IFCR_CGIF7                      DMA_IFCR_CGIF7_Msk                 /*!< Channel 7 Global interrupt clear */
#define DMA_IFCR_CTCIF7_Pos                 (25U)                              
#define DMA_IFCR_CTCIF7_Msk                 (0x1U << DMA_IFCR_CTCIF7_Pos)      /*!< 0x02000000 */
#define DMA_IFCR_CTCIF7                     DMA_IFCR_CTCIF7_Msk                /*!< Channel 7 Transfer Complete clear */
#define DMA_IFCR_CHTIF7_Pos                 (26U)                              
#define DMA_IFCR_CHTIF7_Msk                 (0x1U << DMA_IFCR_CHTIF7_Pos)      /*!< 0x04000000 */
#define DMA_IFCR_CHTIF7                     DMA_IFCR_CHTIF7_Msk                /*!< Channel 7 Half Transfer clear */
#define DMA_IFCR_CTEIF7_Pos                 (27U)                              
#define DMA_IFCR_CTEIF7_Msk                 (0x1U << DMA_IFCR_CTEIF7_Pos)      /*!< 0x08000000 */
#define DMA_IFCR_CTEIF7                     DMA_IFCR_CTEIF7_Msk                /*!< Channel 7 Transfer Error clear */

/*******************  Bit definition for DMA_CCR register   *******************/
#define DMA_CCR_EN_Pos                      (0U)                               
#define DMA_CCR_EN_Msk                      (0x1U << DMA_CCR_EN_Pos)           /*!< 0x00000001 */
#define DMA_CCR_EN                          DMA_CCR_EN_Msk                     /*!< Channel enable */
#define DMA_CCR_TCIE_Pos                    (1U)                               
#define DMA_CCR_TCIE_Msk                    (0x1U << DMA_CCR_TCIE_Pos)         /*!< 0x00000002 */
#define DMA_CCR_TCIE                        DMA_CCR_TCIE_Msk                   /*!< Transfer complete interrupt enable */
#define DMA_CCR_HTIE_Pos                    (2U)                               
#define DMA_CCR_HTIE_Msk                    (0x1U << DMA_CCR_HTIE_Pos)         /*!< 0x00000004 */
#define DMA_CCR_HTIE                        DMA_CCR_HTIE_Msk                   /*!< Half Transfer interrupt enable */
#define DMA_CCR_TEIE_Pos                    (3U)                               
#define DMA_CCR_TEIE_Msk                    (0x1U << DMA_CCR_TEIE_Pos)         /*!< 0x00000008 */
#define DMA_CCR_TEIE                        DMA_CCR_TEIE_Msk                   /*!< Transfer error interrupt enable */
#define DMA_CCR_DIR_Pos                     (4U)                               
#define DMA_CCR_DIR_Msk                     (0x1U << DMA_CCR_DIR_Pos)          /*!< 0x00000010 */
#define DMA_CCR_DIR                         DMA_CCR_DIR_Msk                    /*!< Data transfer direction */
#define DMA_CCR_CIRC_Pos                    (5U)                               
#define DMA_CCR_CIRC_Msk                    (0x1U << DMA_CCR_CIRC_Pos)         /*!< 0x00000020 */
#define DMA_CCR_CIRC                        DMA_CCR_CIRC_Msk                   /*!< Circular mode */
#define DMA_CCR_PINC_Pos                    (6U)                               
#define DMA_CCR_PINC_Msk                    (0x1U << DMA_CCR_PINC_Pos)         /*!< 0x00000040 */
#define DMA_CCR_PINC                        DMA_CCR_PINC_Msk                   /*!< Peripheral increment mode */
#define DMA_CCR_MINC_Pos                    (7U)                               
#define DMA_CCR_MINC_Msk                    (0x1U << DMA_CCR_MINC_Pos)         /*!< 0x00000080 */
#define DMA_CCR_MINC                        DMA_CCR_MINC_Msk                   /*!< Memory increment mode */

#define DMA_CCR_PSIZE_Pos                   (8U)                               
#define DMA_CCR_PSIZE_Msk                   (0x3U << DMA_CCR_PSIZE_Pos)        /*!< 0x00000300 */
#define DMA_CCR_PSIZE                       DMA_CCR_PSIZE_Msk                  /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CCR_PSIZE_0                     (0x1U << DMA_CCR_PSIZE_Pos)        /*!< 0x00000100 */
#define DMA_CCR_PSIZE_1                     (0x2U << DMA_CCR_PSIZE_Pos)        /*!< 0x00000200 */

#define DMA_CCR_MSIZE_Pos                   (10U)                              
#define DMA_CCR_MSIZE_Msk                   (0x3U << DMA_CCR_MSIZE_Pos)        /*!< 0x00000C00 */
#define DMA_CCR_MSIZE                       DMA_CCR_MSIZE_Msk                  /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CCR_MSIZE_0                     (0x1U << DMA_CCR_MSIZE_Pos)        /*!< 0x00000400 */
#define DMA_CCR_MSIZE_1                     (0x2U << DMA_CCR_MSIZE_Pos)        /*!< 0x00000800 */

#define DMA_CCR_PL_Pos                      (12U)                              
#define DMA_CCR_PL_Msk                      (0x3U << DMA_CCR_PL_Pos)           /*!< 0x00003000 */
#define DMA_CCR_PL                          DMA_CCR_PL_Msk                     /*!< PL[1:0] bits(Channel Priority level) */
#define DMA_CCR_PL_0                        (0x1U << DMA_CCR_PL_Pos)           /*!< 0x00001000 */
#define DMA_CCR_PL_1                        (0x2U << DMA_CCR_PL_Pos)           /*!< 0x00002000 */

#define DMA_CCR_MEM2MEM_Pos                 (14U)                              
#define DMA_CCR_MEM2MEM_Msk                 (0x1U << DMA_CCR_MEM2MEM_Pos)      /*!< 0x00004000 */
#define DMA_CCR_MEM2MEM                     DMA_CCR_MEM2MEM_Msk                /*!< Memory to memory mode */

/******************  Bit definition for DMA_CNDTR  register  ******************/
#define DMA_CNDTR_NDT_Pos                   (0U)                               
#define DMA_CNDTR_NDT_Msk                   (0xFFFFU << DMA_CNDTR_NDT_Pos)     /*!< 0x0000FFFF */
#define DMA_CNDTR_NDT                       DMA_CNDTR_NDT_Msk                  /*!< Number of data to Transfer */

/******************  Bit definition for DMA_CPAR  register  *******************/
#define DMA_CPAR_PA_Pos                     (0U)                               
#define DMA_CPAR_PA_Msk                     (0xFFFFFFFFU << DMA_CPAR_PA_Pos)   /*!< 0xFFFFFFFF */
#define DMA_CPAR_PA                         DMA_CPAR_PA_Msk                    /*!< Peripheral Address */

/******************  Bit definition for DMA_CMAR  register  *******************/
#define DMA_CMAR_MA_Pos                     (0U)                               
#define DMA_CMAR_MA_Msk                     (0xFFFFFFFFU << DMA_CMAR_MA_Pos)   /*!< 0xFFFFFFFF */
#define DMA_CMAR_MA                         DMA_CMAR_MA_Msk                    /*!< Memory Address */


#endif