#ifndef SMALL_CMSIS_H
#define SMALL_CMSIS_H

#include "mks_wifi.h"

#define     __IO    volatile             /*!< Defines 'read / write' permissions */
#define     __I     volatile const       /*!< Defines 'read only' permissions */

typedef struct
{
  __IO uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  Control Register */
  __IO uint32_t CYCCNT;                 /*!< Offset: 0x004 (R/W)  Cycle Count Register */
  __IO uint32_t CPICNT;                 /*!< Offset: 0x008 (R/W)  CPI Count Register */
  __IO uint32_t EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
  __IO uint32_t SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
  __IO uint32_t LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
  __IO uint32_t FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
  __I  uint32_t PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
  __IO uint32_t COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
  __IO uint32_t MASK0;                  /*!< Offset: 0x024 (R/W)  Mask Register 0 */
  __IO uint32_t FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
       uint32_t RESERVED0[1U];
  __IO uint32_t COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
  __IO uint32_t MASK1;                  /*!< Offset: 0x034 (R/W)  Mask Register 1 */
  __IO uint32_t FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
       uint32_t RESERVED1[1U];
  __IO uint32_t COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
  __IO uint32_t MASK2;                  /*!< Offset: 0x044 (R/W)  Mask Register 2 */
  __IO uint32_t FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
       uint32_t RESERVED2[1U];
  __IO uint32_t COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
  __IO uint32_t MASK3;                  /*!< Offset: 0x054 (R/W)  Mask Register 3 */
  __IO uint32_t FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
} DWT_Type;


typedef struct
{
  __IO uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __IO  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IO uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IO uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} CoreDebug_Type;


typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;


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

typedef struct
{
  __IO uint32_t POWER;
  __IO uint32_t CLKCR;
  __IO uint32_t ARG;
  __IO uint32_t CMD;
  __I uint32_t RESPCMD;
  __I uint32_t RESP1;
  __I uint32_t RESP2;
  __I uint32_t RESP3;
  __I uint32_t RESP4;
  __IO uint32_t DTIMER;
  __IO uint32_t DLEN;
  __IO uint32_t DCTRL;
  __I uint32_t DCOUNT;
  __I uint32_t STA;
  __IO uint32_t ICR;
  __IO uint32_t MASK;
  uint32_t  RESERVED0[2];
  __I uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  __IO uint32_t FIFO;
} SDIO_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;


} RCC_TypeDef;

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t OAR1;
  __IO uint32_t OAR2;
  __IO uint32_t DR;
  __IO uint32_t SR1;
  __IO uint32_t SR2;
  __IO uint32_t CCR;
  __IO uint32_t TRISE;
} I2C_TypeDef;

typedef struct
{
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t RESERVED0;
  __IO uint32_t MAPR2;  
} AFIO_TypeDef;

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SR;
  __IO uint32_t DR;
  __IO uint32_t CRCPR;
  __IO uint32_t RXCRCR;
  __IO uint32_t TXCRCR;
  __IO uint32_t I2SCFGR;
  __IO uint32_t I2SPR;
} SPI_TypeDef;


#define PERIPH_BASE           0x40000000U /*!< Peripheral base address in the alias region */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000U)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000U)
//#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800U)
#define DMA1_N_BASE             (AHBPERIPH_BASE + 0x00000000U)
#define DMA1_Channel5_BASE    (AHBPERIPH_BASE + 0x00000058U)
#define DMA2_N_BASE             (AHBPERIPH_BASE + 0x00000400U)
#define DMA2_Channel4_BASE    (AHBPERIPH_BASE + 0x00000444U)
#define SDIO_BASE             (PERIPH_BASE + 0x00018000U)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x00005400U)
#define PORTA_BASE            (APB2PERIPH_BASE + 0x00000800U)
#define PORTB_BASE            (APB2PERIPH_BASE + 0x00000C00U)
#define PORTC_BASE            (APB2PERIPH_BASE + 0x00001000U)
#define AFIOBASE              (APB2PERIPH_BASE + 0x00000000U)
#define CoreDebug_BASE        (0xE000EDF0UL)  /*!< Core Debug Base Address */
#define DWT_BASE              (0xE0001000UL)  /*!< DWT Base Address */
#define SPI_2_BASE             (APB1PERIPH_BASE + 0x00003800U)

#define RCC                   ((RCC_TypeDef *)RCC_BASE)
#define SDIO                  ((SDIO_TypeDef *)SDIO_BASE)
#define USART1                ((USART_TypeDef *)USART1_BASE)
#define DMA1_N                  ((DMA_TypeDef *)DMA1_N_BASE)
#define DMA1_Channel5         ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE)
#define DMA2_Channel4         ((DMA_Channel_TypeDef *)DMA2_Channel4_BASE)
#define DMA2_N                  ((DMA_TypeDef *)DMA2_N_BASE)
#define I2C1                  ((I2C_TypeDef *)I2C1_BASE)
#define PORTA                 ((GPIO_TypeDef *)PORTA_BASE)
#define PORTB                 ((GPIO_TypeDef *)PORTB_BASE)
#define PORTC                 ((GPIO_TypeDef *)PORTC_BASE)
#define AFIO                  ((AFIO_TypeDef *)AFIOBASE)
#define CoreDebug             ((CoreDebug_Type *)CoreDebug_BASE)   /*!< Core Debug configuration struct */
#define DWT                   ((DWT_Type       *)     DWT_BASE      )   /*!< DWT configuration struct */
#define SPI_2                  ((SPI_TypeDef *)SPI_2_BASE)

/******************************************************************************/
/*                                                                            */
/*                             DMA Controller                                 */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for DMA_ISR register  ********************/

#define DMA_ISR_GIF1_Pos                    (0U)                               
#define DMA_ISR_GIF1_Msk                    (0x1U << DMA_ISR_GIF1_Pos)         /*!< 0x00000001 */
//#define DMA_ISR_GIF1                        DMA_ISR_GIF1_Msk                   /*!< Channel 1 Global interrupt flag */
#define DMA_ISR_TCIF1_Pos                   (1U)                               
#define DMA_ISR_TCIF1_Msk                   (0x1U << DMA_ISR_TCIF1_Pos)        /*!< 0x00000002 */
//#define DMA_ISR_TCIF1                       DMA_ISR_TCIF1_Msk                  /*!< Channel 1 Transfer Complete flag */
#define DMA_ISR_HTIF1_Pos                   (2U)                               
#define DMA_ISR_HTIF1_Msk                   (0x1U << DMA_ISR_HTIF1_Pos)        /*!< 0x00000004 */
//#define DMA_ISR_HTIF1                       DMA_ISR_HTIF1_Msk                  /*!< Channel 1 Half Transfer flag */
#define DMA_ISR_TEIF1_Pos                   (3U)                               
#define DMA_ISR_TEIF1_Msk                   (0x1U << DMA_ISR_TEIF1_Pos)        /*!< 0x00000008 */
//#define DMA_ISR_TEIF1                       DMA_ISR_TEIF1_Msk                  /*!< Channel 1 Transfer Error flag */
#define DMA_ISR_GIF2_Pos                    (4U)                               
#define DMA_ISR_GIF2_Msk                    (0x1U << DMA_ISR_GIF2_Pos)         /*!< 0x00000010 */
//#define DMA_ISR_GIF2                        DMA_ISR_GIF2_Msk                   /*!< Channel 2 Global interrupt flag */
#define DMA_ISR_TCIF2_Pos                   (5U)                               
#define DMA_ISR_TCIF2_Msk                   (0x1U << DMA_ISR_TCIF2_Pos)        /*!< 0x00000020 */
//#define DMA_ISR_TCIF2                       DMA_ISR_TCIF2_Msk                  /*!< Channel 2 Transfer Complete flag */
#define DMA_ISR_HTIF2_Pos                   (6U)                               
#define DMA_ISR_HTIF2_Msk                   (0x1U << DMA_ISR_HTIF2_Pos)        /*!< 0x00000040 */
//#define DMA_ISR_HTIF2                       DMA_ISR_HTIF2_Msk                  /*!< Channel 2 Half Transfer flag */
#define DMA_ISR_TEIF2_Pos                   (7U)                               
#define DMA_ISR_TEIF2_Msk                   (0x1U << DMA_ISR_TEIF2_Pos)        /*!< 0x00000080 */
//#define DMA_ISR_TEIF2                       DMA_ISR_TEIF2_Msk                  /*!< Channel 2 Transfer Error flag */
#define DMA_ISR_GIF3_Pos                    (8U)                               
#define DMA_ISR_GIF3_Msk                    (0x1U << DMA_ISR_GIF3_Pos)         /*!< 0x00000100 */
//#define DMA_ISR_GIF3                        DMA_ISR_GIF3_Msk                   /*!< Channel 3 Global interrupt flag */
#define DMA_ISR_TCIF3_Pos                   (9U)                               
#define DMA_ISR_TCIF3_Msk                   (0x1U << DMA_ISR_TCIF3_Pos)        /*!< 0x00000200 */
//#define DMA_ISR_TCIF3                       DMA_ISR_TCIF3_Msk                  /*!< Channel 3 Transfer Complete flag */
#define DMA_ISR_HTIF3_Pos                   (10U)                              
#define DMA_ISR_HTIF3_Msk                   (0x1U << DMA_ISR_HTIF3_Pos)        /*!< 0x00000400 */
//#define DMA_ISR_HTIF3                       DMA_ISR_HTIF3_Msk                  /*!< Channel 3 Half Transfer flag */
#define DMA_ISR_TEIF3_Pos                   (11U)                              
#define DMA_ISR_TEIF3_Msk                   (0x1U << DMA_ISR_TEIF3_Pos)        /*!< 0x00000800 */
//#define DMA_ISR_TEIF3                       DMA_ISR_TEIF3_Msk                  /*!< Channel 3 Transfer Error flag */
#define DMA_ISR_GIF4_Pos                    (12U)                              
#define DMA_ISR_GIF4_Msk                    (0x1U << DMA_ISR_GIF4_Pos)         /*!< 0x00001000 */
//#define DMA_ISR_GIF4                        DMA_ISR_GIF4_Msk                   /*!< Channel 4 Global interrupt flag */
#define DMA_ISR_TCIF4_Pos                   (13U)                              
#define DMA_ISR_TCIF4_Msk                   (0x1U << DMA_ISR_TCIF4_Pos)        /*!< 0x00002000 */
#define DMA_N_ISR_TCIF4                       DMA_ISR_TCIF4_Msk                  /*!< Channel 4 Transfer Complete flag */
#define DMA_ISR_HTIF4_Pos                   (14U)                              
#define DMA_ISR_HTIF4_Msk                   (0x1U << DMA_ISR_HTIF4_Pos)        /*!< 0x00004000 */
//#define DMA_ISR_HTIF4                       DMA_ISR_HTIF4_Msk                  /*!< Channel 4 Half Transfer flag */
#define DMA_ISR_TEIF4_Pos                   (15U)                              
#define DMA_ISR_TEIF4_Msk                   (0x1U << DMA_ISR_TEIF4_Pos)        /*!< 0x00008000 */
#define DMA_N_ISR_TEIF4                       DMA_ISR_TEIF4_Msk                  /*!< Channel 4 Transfer Error flag */
#define DMA_ISR_GIF5_Pos                    (16U)                              
#define DMA_ISR_GIF5_Msk                    (0x1U << DMA_ISR_GIF5_Pos)         /*!< 0x00010000 */
//#define DMA_ISR_GIF5                        DMA_ISR_GIF5_Msk                   /*!< Channel 5 Global interrupt flag */
#define DMA_ISR_TCIF5_Pos                   (17U)                              
#define DMA_ISR_TCIF5_Msk                   (0x1U << DMA_ISR_TCIF5_Pos)        /*!< 0x00020000 */
//#define DMA_ISR_TCIF5                       DMA_ISR_TCIF5_Msk                  /*!< Channel 5 Transfer Complete flag */
#define DMA_ISR_HTIF5_Pos                   (18U)                              
#define DMA_ISR_HTIF5_Msk                   (0x1U << DMA_ISR_HTIF5_Pos)        /*!< 0x00040000 */
//#define DMA_ISR_HTIF5                       DMA_ISR_HTIF5_Msk                  /*!< Channel 5 Half Transfer flag */
#define DMA_ISR_TEIF5_Pos                   (19U)                              
#define DMA_ISR_TEIF5_Msk                   (0x1U << DMA_ISR_TEIF5_Pos)        /*!< 0x00080000 */
//#define DMA_ISR_TEIF5                       DMA_ISR_TEIF5_Msk                  /*!< Channel 5 Transfer Error flag */
#define DMA_ISR_GIF6_Pos                    (20U)                              
#define DMA_ISR_GIF6_Msk                    (0x1U << DMA_ISR_GIF6_Pos)         /*!< 0x00100000 */
//#define DMA_ISR_GIF6                        DMA_ISR_GIF6_Msk                   /*!< Channel 6 Global interrupt flag */
#define DMA_ISR_TCIF6_Pos                   (21U)                              
#define DMA_ISR_TCIF6_Msk                   (0x1U << DMA_ISR_TCIF6_Pos)        /*!< 0x00200000 */
//#define DMA_ISR_TCIF6                       DMA_ISR_TCIF6_Msk                  /*!< Channel 6 Transfer Complete flag */
#define DMA_ISR_HTIF6_Pos                   (22U)                              
#define DMA_ISR_HTIF6_Msk                   (0x1U << DMA_ISR_HTIF6_Pos)        /*!< 0x00400000 */
//#define DMA_ISR_HTIF6                       DMA_ISR_HTIF6_Msk                  /*!< Channel 6 Half Transfer flag */
#define DMA_ISR_TEIF6_Pos                   (23U)                              
#define DMA_ISR_TEIF6_Msk                   (0x1U << DMA_ISR_TEIF6_Pos)        /*!< 0x00800000 */
//#define DMA_ISR_TEIF6                       DMA_ISR_TEIF6_Msk                  /*!< Channel 6 Transfer Error flag */
#define DMA_ISR_GIF7_Pos                    (24U)                              
#define DMA_ISR_GIF7_Msk                    (0x1U << DMA_ISR_GIF7_Pos)         /*!< 0x01000000 */
//#define DMA_ISR_GIF7                        DMA_ISR_GIF7_Msk                   /*!< Channel 7 Global interrupt flag */
#define DMA_ISR_TCIF7_Pos                   (25U)                              
#define DMA_ISR_TCIF7_Msk                   (0x1U << DMA_ISR_TCIF7_Pos)        /*!< 0x02000000 */
//#define DMA_ISR_TCIF7                       DMA_ISR_TCIF7_Msk                  /*!< Channel 7 Transfer Complete flag */
#define DMA_ISR_HTIF7_Pos                   (26U)                              
#define DMA_ISR_HTIF7_Msk                   (0x1U << DMA_ISR_HTIF7_Pos)        /*!< 0x04000000 */
//#define DMA_ISR_HTIF7                       DMA_ISR_HTIF7_Msk                  /*!< Channel 7 Half Transfer flag */
#define DMA_ISR_TEIF7_Pos                   (27U)                              
#define DMA_ISR_TEIF7_Msk                   (0x1U << DMA_ISR_TEIF7_Pos)        /*!< 0x08000000 */
//#define DMA_ISR_TEIF7                       DMA_ISR_TEIF7_Msk                  /*!< Channel 7 Transfer Error flag */


/*******************  Bit definition for DMA_IFCR register  *******************/
#define DMA_IFCR_CGIF1_Pos                  (0U)                               
#define DMA_IFCR_CGIF1_Msk                  (0x1U << DMA_IFCR_CGIF1_Pos)       /*!< 0x00000001 */
//#define DMA_IFCR_CGIF1                      DMA_IFCR_CGIF1_Msk                 /*!< Channel 1 Global interrupt clear */
#define DMA_IFCR_CTCIF1_Pos                 (1U)                               
#define DMA_IFCR_CTCIF1_Msk                 (0x1U << DMA_IFCR_CTCIF1_Pos)      /*!< 0x00000002 */
//#define DMA_IFCR_CTCIF1                     DMA_IFCR_CTCIF1_Msk                /*!< Channel 1 Transfer Complete clear */
#define DMA_IFCR_CHTIF1_Pos                 (2U)                               
#define DMA_IFCR_CHTIF1_Msk                 (0x1U << DMA_IFCR_CHTIF1_Pos)      /*!< 0x00000004 */
//#define DMA_IFCR_CHTIF1                     DMA_IFCR_CHTIF1_Msk                /*!< Channel 1 Half Transfer clear */
#define DMA_IFCR_CTEIF1_Pos                 (3U)                               
#define DMA_IFCR_CTEIF1_Msk                 (0x1U << DMA_IFCR_CTEIF1_Pos)      /*!< 0x00000008 */
//#define DMA_IFCR_CTEIF1                     DMA_IFCR_CTEIF1_Msk                /*!< Channel 1 Transfer Error clear */
#define DMA_IFCR_CGIF2_Pos                  (4U)                               
#define DMA_IFCR_CGIF2_Msk                  (0x1U << DMA_IFCR_CGIF2_Pos)       /*!< 0x00000010 */
//#define DMA_IFCR_CGIF2                      DMA_IFCR_CGIF2_Msk                 /*!< Channel 2 Global interrupt clear */
#define DMA_IFCR_CTCIF2_Pos                 (5U)                               
#define DMA_IFCR_CTCIF2_Msk                 (0x1U << DMA_IFCR_CTCIF2_Pos)      /*!< 0x00000020 */
//#define DMA_IFCR_CTCIF2                     DMA_IFCR_CTCIF2_Msk                /*!< Channel 2 Transfer Complete clear */
#define DMA_IFCR_CHTIF2_Pos                 (6U)                               
#define DMA_IFCR_CHTIF2_Msk                 (0x1U << DMA_IFCR_CHTIF2_Pos)      /*!< 0x00000040 */
//#define DMA_IFCR_CHTIF2                     DMA_IFCR_CHTIF2_Msk                /*!< Channel 2 Half Transfer clear */
#define DMA_IFCR_CTEIF2_Pos                 (7U)                               
#define DMA_IFCR_CTEIF2_Msk                 (0x1U << DMA_IFCR_CTEIF2_Pos)      /*!< 0x00000080 */
//#define DMA_IFCR_CTEIF2                     DMA_IFCR_CTEIF2_Msk                /*!< Channel 2 Transfer Error clear */
#define DMA_IFCR_CGIF3_Pos                  (8U)                               
#define DMA_IFCR_CGIF3_Msk                  (0x1U << DMA_IFCR_CGIF3_Pos)       /*!< 0x00000100 */
//#define DMA_IFCR_CGIF3                      DMA_IFCR_CGIF3_Msk                 /*!< Channel 3 Global interrupt clear */
#define DMA_IFCR_CTCIF3_Pos                 (9U)                               
#define DMA_IFCR_CTCIF3_Msk                 (0x1U << DMA_IFCR_CTCIF3_Pos)      /*!< 0x00000200 */
//#define DMA_IFCR_CTCIF3                     DMA_IFCR_CTCIF3_Msk                /*!< Channel 3 Transfer Complete clear */
#define DMA_IFCR_CHTIF3_Pos                 (10U)                              
#define DMA_IFCR_CHTIF3_Msk                 (0x1U << DMA_IFCR_CHTIF3_Pos)      /*!< 0x00000400 */
//#define DMA_IFCR_CHTIF3                     DMA_IFCR_CHTIF3_Msk                /*!< Channel 3 Half Transfer clear */
#define DMA_IFCR_CTEIF3_Pos                 (11U)                              
#define DMA_IFCR_CTEIF3_Msk                 (0x1U << DMA_IFCR_CTEIF3_Pos)      /*!< 0x00000800 */
//#define DMA_IFCR_CTEIF3                     DMA_IFCR_CTEIF3_Msk                /*!< Channel 3 Transfer Error clear */
#define DMA_IFCR_CGIF4_Pos                  (12U)                              
#define DMA_IFCR_CGIF4_Msk                  (0x1U << DMA_IFCR_CGIF4_Pos)       /*!< 0x00001000 */
#define DMA_N_IFCR_CGIF4                      DMA_IFCR_CGIF4_Msk                 /*!< Channel 4 Global interrupt clear */
#define DMA_IFCR_CTCIF4_Pos                 (13U)                              
#define DMA_IFCR_CTCIF4_Msk                 (0x1U << DMA_IFCR_CTCIF4_Pos)      /*!< 0x00002000 */
#define DMA_N_IFCR_CTCIF4                     DMA_IFCR_CTCIF4_Msk                /*!< Channel 4 Transfer Complete clear */
#define DMA_IFCR_CHTIF4_Pos                 (14U)                              
#define DMA_IFCR_CHTIF4_Msk                 (0x1U << DMA_IFCR_CHTIF4_Pos)      /*!< 0x00004000 */
#define DMA_N_IFCR_CHTIF4                     DMA_IFCR_CHTIF4_Msk                /*!< Channel 4 Half Transfer clear */
#define DMA_IFCR_CTEIF4_Pos                 (15U)                              
#define DMA_IFCR_CTEIF4_Msk                 (0x1U << DMA_IFCR_CTEIF4_Pos)      /*!< 0x00008000 */
#define DMA_N_IFCR_CTEIF4                     DMA_IFCR_CTEIF4_Msk                /*!< Channel 4 Transfer Error clear */
#define DMA_IFCR_CGIF5_Pos                  (16U)                              
#define DMA_IFCR_CGIF5_Msk                  (0x1U << DMA_IFCR_CGIF5_Pos)       /*!< 0x00010000 */
//#define DMA_IFCR_CGIF5                      DMA_IFCR_CGIF5_Msk                 /*!< Channel 5 Global interrupt clear */
#define DMA_IFCR_CTCIF5_Pos                 (17U)                              
#define DMA_IFCR_CTCIF5_Msk                 (0x1U << DMA_IFCR_CTCIF5_Pos)      /*!< 0x00020000 */
//#define DMA_IFCR_CTCIF5                     DMA_IFCR_CTCIF5_Msk                /*!< Channel 5 Transfer Complete clear */
#define DMA_IFCR_CHTIF5_Pos                 (18U)                              
#define DMA_IFCR_CHTIF5_Msk                 (0x1U << DMA_IFCR_CHTIF5_Pos)      /*!< 0x00040000 */
//#define DMA_IFCR_CHTIF5                     DMA_IFCR_CHTIF5_Msk                /*!< Channel 5 Half Transfer clear */
#define DMA_IFCR_CTEIF5_Pos                 (19U)                              
#define DMA_IFCR_CTEIF5_Msk                 (0x1U << DMA_IFCR_CTEIF5_Pos)      /*!< 0x00080000 */
//#define DMA_IFCR_CTEIF5                     DMA_IFCR_CTEIF5_Msk                /*!< Channel 5 Transfer Error clear */
#define DMA_IFCR_CGIF6_Pos                  (20U)                              
#define DMA_IFCR_CGIF6_Msk                  (0x1U << DMA_IFCR_CGIF6_Pos)       /*!< 0x00100000 */
//#define DMA_IFCR_CGIF6                      DMA_IFCR_CGIF6_Msk                 /*!< Channel 6 Global interrupt clear */
#define DMA_IFCR_CTCIF6_Pos                 (21U)                              
#define DMA_IFCR_CTCIF6_Msk                 (0x1U << DMA_IFCR_CTCIF6_Pos)      /*!< 0x00200000 */
//#define DMA_IFCR_CTCIF6                     DMA_IFCR_CTCIF6_Msk                /*!< Channel 6 Transfer Complete clear */
#define DMA_IFCR_CHTIF6_Pos                 (22U)                              
#define DMA_IFCR_CHTIF6_Msk                 (0x1U << DMA_IFCR_CHTIF6_Pos)      /*!< 0x00400000 */
//#define DMA_IFCR_CHTIF6                     DMA_IFCR_CHTIF6_Msk                /*!< Channel 6 Half Transfer clear */
#define DMA_IFCR_CTEIF6_Pos                 (23U)                              
#define DMA_IFCR_CTEIF6_Msk                 (0x1U << DMA_IFCR_CTEIF6_Pos)      /*!< 0x00800000 */
//#define DMA_IFCR_CTEIF6                     DMA_IFCR_CTEIF6_Msk                /*!< Channel 6 Transfer Error clear */
#define DMA_IFCR_CGIF7_Pos                  (24U)                              
#define DMA_IFCR_CGIF7_Msk                  (0x1U << DMA_IFCR_CGIF7_Pos)       /*!< 0x01000000 */
//#define DMA_IFCR_CGIF7                      DMA_IFCR_CGIF7_Msk                 /*!< Channel 7 Global interrupt clear */
#define DMA_IFCR_CTCIF7_Pos                 (25U)                              
#define DMA_IFCR_CTCIF7_Msk                 (0x1U << DMA_IFCR_CTCIF7_Pos)      /*!< 0x02000000 */
//#define DMA_IFCR_CTCIF7                     DMA_IFCR_CTCIF7_Msk                /*!< Channel 7 Transfer Complete clear */
#define DMA_IFCR_CHTIF7_Pos                 (26U)                              
#define DMA_IFCR_CHTIF7_Msk                 (0x1U << DMA_IFCR_CHTIF7_Pos)      /*!< 0x04000000 */
//#define DMA_IFCR_CHTIF7                     DMA_IFCR_CHTIF7_Msk                /*!< Channel 7 Half Transfer clear */
#define DMA_IFCR_CTEIF7_Pos                 (27U)                              
#define DMA_IFCR_CTEIF7_Msk                 (0x1U << DMA_IFCR_CTEIF7_Pos)      /*!< 0x08000000 */
//#define DMA_IFCR_CTEIF7                     DMA_IFCR_CTEIF7_Msk                /*!< Channel 7 Transfer Error clear */


/*******************  Bit definition for DMA_CCR register   *******************/
#define DMA_CCR_EN_Pos                      (0U)                               
#define DMA_CCR_EN_Msk                      (0x1U << DMA_CCR_EN_Pos)           /*!< 0x00000001 */
//#define DMA_CCR_EN                          DMA_CCR_EN_Msk                     /*!< Channel enable */
#define DMA_CCR_TCIE_Pos                    (1U)                               
#define DMA_CCR_TCIE_Msk                    (0x1U << DMA_CCR_TCIE_Pos)         /*!< 0x00000002 */
//#define DMA_CCR_TCIE                        DMA_CCR_TCIE_Msk                   /*!< Transfer complete interrupt enable */
#define DMA_CCR_HTIE_Pos                    (2U)                               
#define DMA_CCR_HTIE_Msk                    (0x1U << DMA_CCR_HTIE_Pos)         /*!< 0x00000004 */
//#define DMA_CCR_HTIE                        DMA_CCR_HTIE_Msk                   /*!< Half Transfer interrupt enable */
#define DMA_CCR_TEIE_Pos                    (3U)                               
#define DMA_CCR_TEIE_Msk                    (0x1U << DMA_CCR_TEIE_Pos)         /*!< 0x00000008 */
//#define DMA_CCR_TEIE                        DMA_CCR_TEIE_Msk                   /*!< Transfer error interrupt enable */
#define DMA_CCR_DIR_Pos                     (4U)                               
#define DMA_CCR_DIR_Msk                     (0x1U << DMA_CCR_DIR_Pos)          /*!< 0x00000010 */
//#define DMA_CCR_DIR                         DMA_CCR_DIR_Msk                    /*!< Data transfer direction */
#define DMA_CCR_CIRC_Pos                    (5U)                               
#define DMA_CCR_CIRC_Msk                    (0x1U << DMA_CCR_CIRC_Pos)         /*!< 0x00000020 */
//#define DMA_CCR_CIRC                        DMA_CCR_CIRC_Msk                   /*!< Circular mode */
#define DMA_CCR_PINC_Pos                    (6U)                               
#define DMA_CCR_PINC_Msk                    (0x1U << DMA_CCR_PINC_Pos)         /*!< 0x00000040 */
//#define DMA_CCR_PINC                        DMA_CCR_PINC_Msk                   /*!< Peripheral increment mode */
#define DMA_CCR_MINC_Pos                    (7U)                               
#define DMA_CCR_MINC_Msk                    (0x1U << DMA_CCR_MINC_Pos)         /*!< 0x00000080 */
//#define DMA_CCR_MINC                        DMA_CCR_MINC_Msk                   /*!< Memory increment mode */

#define DMA_CCR_PSIZE_Pos                   (8U)                               
#define DMA_CCR_PSIZE_Msk                   (0x3U << DMA_CCR_PSIZE_Pos)        /*!< 0x00000300 */
//#define DMA_CCR_PSIZE                       DMA_CCR_PSIZE_Msk                  /*!< PSIZE[1:0] bits (Peripheral size) */
#define DMA_CCR_PSIZE_0                     (0x1U << DMA_CCR_PSIZE_Pos)        /*!< 0x00000100 */
#define DMA_CCR_PSIZE_1                     (0x2U << DMA_CCR_PSIZE_Pos)        /*!< 0x00000200 */

#define DMA_CCR_MSIZE_Pos                   (10U)                              
#define DMA_CCR_MSIZE_Msk                   (0x3U << DMA_CCR_MSIZE_Pos)        /*!< 0x00000C00 */
//#define DMA_CCR_MSIZE                       DMA_CCR_MSIZE_Msk                  /*!< MSIZE[1:0] bits (Memory size) */
#define DMA_CCR_MSIZE_0                     (0x1U << DMA_CCR_MSIZE_Pos)        /*!< 0x00000400 */
#define DMA_CCR_MSIZE_1                     (0x2U << DMA_CCR_MSIZE_Pos)        /*!< 0x00000800 */

#define DMA_CCR_PL_Pos                      (12U)                              
#define DMA_CCR_PL_Msk                      (0x3U << DMA_CCR_PL_Pos)           /*!< 0x00003000 */
//#define DMA_CCR_PL                          DMA_CCR_PL_Msk                     /*!< PL[1:0] bits(Channel Priority level) */
#define DMA_CCR_PL_0                        (0x1U << DMA_CCR_PL_Pos)           /*!< 0x00001000 */
#define DMA_CCR_PL_1                        (0x2U << DMA_CCR_PL_Pos)           /*!< 0x00002000 */

#if 0
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

/******************************************************************************/
/*                                                                            */
/*                          SD host Interface                                 */
/*                                                                            */
/******************************************************************************/

/******************  Bit definition for SDIO_POWER register  ******************/
#define SDIO_POWER_PWRCTRL_Pos              (0U)                               
#define SDIO_POWER_PWRCTRL_Msk              (0x3U << SDIO_POWER_PWRCTRL_Pos)   /*!< 0x00000003 */
#define SDIO_POWER_PWRCTRL                  SDIO_POWER_PWRCTRL_Msk             /*!< PWRCTRL[1:0] bits (Power supply control bits) */
#define SDIO_POWER_PWRCTRL_0                (0x1U << SDIO_POWER_PWRCTRL_Pos)   /*!< 0x01 */
#define SDIO_POWER_PWRCTRL_1                (0x2U << SDIO_POWER_PWRCTRL_Pos)   /*!< 0x02 */

/******************  Bit definition for SDIO_CLKCR register  ******************/
#define SDIO_CLKCR_CLKDIV_Pos               (0U)                               
#define SDIO_CLKCR_CLKDIV_Msk               (0xFFU << SDIO_CLKCR_CLKDIV_Pos)   /*!< 0x000000FF */
#define SDIO_CLKCR_CLKDIV                   SDIO_CLKCR_CLKDIV_Msk              /*!< Clock divide factor */
#define SDIO_CLKCR_CLKEN_Pos                (8U)                               
#define SDIO_CLKCR_CLKEN_Msk                (0x1U << SDIO_CLKCR_CLKEN_Pos)     /*!< 0x00000100 */
#define SDIO_CLKCR_CLKEN                    SDIO_CLKCR_CLKEN_Msk               /*!< Clock enable bit */
#define SDIO_CLKCR_PWRSAV_Pos               (9U)                               
#define SDIO_CLKCR_PWRSAV_Msk               (0x1U << SDIO_CLKCR_PWRSAV_Pos)    /*!< 0x00000200 */
#define SDIO_CLKCR_PWRSAV                   SDIO_CLKCR_PWRSAV_Msk              /*!< Power saving configuration bit */
#define SDIO_CLKCR_BYPASS_Pos               (10U)                              
#define SDIO_CLKCR_BYPASS_Msk               (0x1U << SDIO_CLKCR_BYPASS_Pos)    /*!< 0x00000400 */
#define SDIO_CLKCR_BYPASS                   SDIO_CLKCR_BYPASS_Msk              /*!< Clock divider bypass enable bit */

#define SDIO_CLKCR_WIDBUS_Pos               (11U)                              
#define SDIO_CLKCR_WIDBUS_Msk               (0x3U << SDIO_CLKCR_WIDBUS_Pos)    /*!< 0x00001800 */
#define SDIO_CLKCR_WIDBUS                   SDIO_CLKCR_WIDBUS_Msk              /*!< WIDBUS[1:0] bits (Wide bus mode enable bit) */
#define SDIO_CLKCR_WIDBUS_0                 (0x1U << SDIO_CLKCR_WIDBUS_Pos)    /*!< 0x0800 */
#define SDIO_CLKCR_WIDBUS_1                 (0x2U << SDIO_CLKCR_WIDBUS_Pos)    /*!< 0x1000 */

#define SDIO_CLKCR_NEGEDGE_Pos              (13U)                              
#define SDIO_CLKCR_NEGEDGE_Msk              (0x1U << SDIO_CLKCR_NEGEDGE_Pos)   /*!< 0x00002000 */
#define SDIO_CLKCR_NEGEDGE                  SDIO_CLKCR_NEGEDGE_Msk             /*!< SDIO_CK dephasing selection bit */
#define SDIO_CLKCR_HWFC_EN_Pos              (14U)                              
#define SDIO_CLKCR_HWFC_EN_Msk              (0x1U << SDIO_CLKCR_HWFC_EN_Pos)   /*!< 0x00004000 */
#define SDIO_CLKCR_HWFC_EN                  SDIO_CLKCR_HWFC_EN_Msk             /*!< HW Flow Control enable */

/*******************  Bit definition for SDIO_ARG register  *******************/
#define SDIO_ARG_CMDARG_Pos                 (0U)                               
#define SDIO_ARG_CMDARG_Msk                 (0xFFFFFFFFU << SDIO_ARG_CMDARG_Pos) /*!< 0xFFFFFFFF */
#define SDIO_ARG_CMDARG                     SDIO_ARG_CMDARG_Msk                /*!< Command argument */

/*******************  Bit definition for SDIO_CMD register  *******************/
#define SDIO_CMD_CMDINDEX_Pos               (0U)                               
#define SDIO_CMD_CMDINDEX_Msk               (0x3FU << SDIO_CMD_CMDINDEX_Pos)   /*!< 0x0000003F */
#define SDIO_CMD_CMDINDEX                   SDIO_CMD_CMDINDEX_Msk              /*!< Command Index */

#define SDIO_CMD_WAITRESP_Pos               (6U)                               
#define SDIO_CMD_WAITRESP_Msk               (0x3U << SDIO_CMD_WAITRESP_Pos)    /*!< 0x000000C0 */
#define SDIO_CMD_WAITRESP                   SDIO_CMD_WAITRESP_Msk              /*!< WAITRESP[1:0] bits (Wait for response bits) */
#define SDIO_CMD_WAITRESP_0                 (0x1U << SDIO_CMD_WAITRESP_Pos)    /*!< 0x0040 */
#define SDIO_CMD_WAITRESP_1                 (0x2U << SDIO_CMD_WAITRESP_Pos)    /*!< 0x0080 */

#define SDIO_CMD_WAITINT_Pos                (8U)                               
#define SDIO_CMD_WAITINT_Msk                (0x1U << SDIO_CMD_WAITINT_Pos)     /*!< 0x00000100 */
#define SDIO_CMD_WAITINT                    SDIO_CMD_WAITINT_Msk               /*!< CPSM Waits for Interrupt Request */
#define SDIO_CMD_WAITPEND_Pos               (9U)                               
#define SDIO_CMD_WAITPEND_Msk               (0x1U << SDIO_CMD_WAITPEND_Pos)    /*!< 0x00000200 */
#define SDIO_CMD_WAITPEND                   SDIO_CMD_WAITPEND_Msk              /*!< CPSM Waits for ends of data transfer (CmdPend internal signal) */
#define SDIO_CMD_CPSMEN_Pos                 (10U)                              
#define SDIO_CMD_CPSMEN_Msk                 (0x1U << SDIO_CMD_CPSMEN_Pos)      /*!< 0x00000400 */
#define SDIO_CMD_CPSMEN                     SDIO_CMD_CPSMEN_Msk                /*!< Command path state machine (CPSM) Enable bit */
#define SDIO_CMD_SDIOSUSPEND_Pos            (11U)                              
#define SDIO_CMD_SDIOSUSPEND_Msk            (0x1U << SDIO_CMD_SDIOSUSPEND_Pos) /*!< 0x00000800 */
#define SDIO_CMD_SDIOSUSPEND                SDIO_CMD_SDIOSUSPEND_Msk           /*!< SD I/O suspend command */
#define SDIO_CMD_ENCMDCOMPL_Pos             (12U)                              
#define SDIO_CMD_ENCMDCOMPL_Msk             (0x1U << SDIO_CMD_ENCMDCOMPL_Pos)  /*!< 0x00001000 */
#define SDIO_CMD_ENCMDCOMPL                 SDIO_CMD_ENCMDCOMPL_Msk            /*!< Enable CMD completion */
#define SDIO_CMD_NIEN_Pos                   (13U)                              
#define SDIO_CMD_NIEN_Msk                   (0x1U << SDIO_CMD_NIEN_Pos)        /*!< 0x00002000 */
#define SDIO_CMD_NIEN                       SDIO_CMD_NIEN_Msk                  /*!< Not Interrupt Enable */
#define SDIO_CMD_CEATACMD_Pos               (14U)                              
#define SDIO_CMD_CEATACMD_Msk               (0x1U << SDIO_CMD_CEATACMD_Pos)    /*!< 0x00004000 */
#define SDIO_CMD_CEATACMD                   SDIO_CMD_CEATACMD_Msk              /*!< CE-ATA command */

/*****************  Bit definition for SDIO_RESPCMD register  *****************/
#define SDIO_RESPCMD_RESPCMD_Pos            (0U)                               
#define SDIO_RESPCMD_RESPCMD_Msk            (0x3FU << SDIO_RESPCMD_RESPCMD_Pos) /*!< 0x0000003F */
#define SDIO_RESPCMD_RESPCMD                SDIO_RESPCMD_RESPCMD_Msk           /*!< Response command index */

/******************  Bit definition for SDIO_RESP0 register  ******************/
#define SDIO_RESP0_CARDSTATUS0_Pos          (0U)                               
#define SDIO_RESP0_CARDSTATUS0_Msk          (0xFFFFFFFFU << SDIO_RESP0_CARDSTATUS0_Pos) /*!< 0xFFFFFFFF */
#define SDIO_RESP0_CARDSTATUS0              SDIO_RESP0_CARDSTATUS0_Msk         /*!< Card Status */

/******************  Bit definition for SDIO_RESP1 register  ******************/
#define SDIO_RESP1_CARDSTATUS1_Pos          (0U)                               
#define SDIO_RESP1_CARDSTATUS1_Msk          (0xFFFFFFFFU << SDIO_RESP1_CARDSTATUS1_Pos) /*!< 0xFFFFFFFF */
#define SDIO_RESP1_CARDSTATUS1              SDIO_RESP1_CARDSTATUS1_Msk         /*!< Card Status */

/******************  Bit definition for SDIO_RESP2 register  ******************/
#define SDIO_RESP2_CARDSTATUS2_Pos          (0U)                               
#define SDIO_RESP2_CARDSTATUS2_Msk          (0xFFFFFFFFU << SDIO_RESP2_CARDSTATUS2_Pos) /*!< 0xFFFFFFFF */
#define SDIO_RESP2_CARDSTATUS2              SDIO_RESP2_CARDSTATUS2_Msk         /*!< Card Status */

/******************  Bit definition for SDIO_RESP3 register  ******************/
#define SDIO_RESP3_CARDSTATUS3_Pos          (0U)                               
#define SDIO_RESP3_CARDSTATUS3_Msk          (0xFFFFFFFFU << SDIO_RESP3_CARDSTATUS3_Pos) /*!< 0xFFFFFFFF */
#define SDIO_RESP3_CARDSTATUS3              SDIO_RESP3_CARDSTATUS3_Msk         /*!< Card Status */

/******************  Bit definition for SDIO_RESP4 register  ******************/
#define SDIO_RESP4_CARDSTATUS4_Pos          (0U)                               
#define SDIO_RESP4_CARDSTATUS4_Msk          (0xFFFFFFFFU << SDIO_RESP4_CARDSTATUS4_Pos) /*!< 0xFFFFFFFF */
#define SDIO_RESP4_CARDSTATUS4              SDIO_RESP4_CARDSTATUS4_Msk         /*!< Card Status */

/******************  Bit definition for SDIO_DTIMER register  *****************/
#define SDIO_DTIMER_DATATIME_Pos            (0U)                               
#define SDIO_DTIMER_DATATIME_Msk            (0xFFFFFFFFU << SDIO_DTIMER_DATATIME_Pos) /*!< 0xFFFFFFFF */
#define SDIO_DTIMER_DATATIME                SDIO_DTIMER_DATATIME_Msk           /*!< Data timeout period. */

/******************  Bit definition for SDIO_DLEN register  *******************/
#define SDIO_DLEN_DATALENGTH_Pos            (0U)                               
#define SDIO_DLEN_DATALENGTH_Msk            (0x1FFFFFFU << SDIO_DLEN_DATALENGTH_Pos) /*!< 0x01FFFFFF */
#define SDIO_DLEN_DATALENGTH                SDIO_DLEN_DATALENGTH_Msk           /*!< Data length value */

/******************  Bit definition for SDIO_DCTRL register  ******************/
#define SDIO_DCTRL_DTEN_Pos                 (0U)                               
#define SDIO_DCTRL_DTEN_Msk                 (0x1U << SDIO_DCTRL_DTEN_Pos)      /*!< 0x00000001 */
#define SDIO_DCTRL_DTEN                     SDIO_DCTRL_DTEN_Msk                /*!< Data transfer enabled bit */
#define SDIO_DCTRL_DTDIR_Pos                (1U)                               
#define SDIO_DCTRL_DTDIR_Msk                (0x1U << SDIO_DCTRL_DTDIR_Pos)     /*!< 0x00000002 */
#define SDIO_DCTRL_DTDIR                    SDIO_DCTRL_DTDIR_Msk               /*!< Data transfer direction selection */
#define SDIO_DCTRL_DTMODE_Pos               (2U)                               
#define SDIO_DCTRL_DTMODE_Msk               (0x1U << SDIO_DCTRL_DTMODE_Pos)    /*!< 0x00000004 */
#define SDIO_DCTRL_DTMODE                   SDIO_DCTRL_DTMODE_Msk              /*!< Data transfer mode selection */
#define SDIO_DCTRL_DMAEN_Pos                (3U)                               
#define SDIO_DCTRL_DMAEN_Msk                (0x1U << SDIO_DCTRL_DMAEN_Pos)     /*!< 0x00000008 */
#define SDIO_DCTRL_DMAEN                    SDIO_DCTRL_DMAEN_Msk               /*!< DMA enabled bit */

#define SDIO_DCTRL_DBLOCKSIZE_Pos           (4U)                               
#define SDIO_DCTRL_DBLOCKSIZE_Msk           (0xFU << SDIO_DCTRL_DBLOCKSIZE_Pos) /*!< 0x000000F0 */
#define SDIO_DCTRL_DBLOCKSIZE               SDIO_DCTRL_DBLOCKSIZE_Msk          /*!< DBLOCKSIZE[3:0] bits (Data block size) */
#define SDIO_DCTRL_DBLOCKSIZE_0             (0x1U << SDIO_DCTRL_DBLOCKSIZE_Pos) /*!< 0x0010 */
#define SDIO_DCTRL_DBLOCKSIZE_1             (0x2U << SDIO_DCTRL_DBLOCKSIZE_Pos) /*!< 0x0020 */
#define SDIO_DCTRL_DBLOCKSIZE_2             (0x4U << SDIO_DCTRL_DBLOCKSIZE_Pos) /*!< 0x0040 */
#define SDIO_DCTRL_DBLOCKSIZE_3             (0x8U << SDIO_DCTRL_DBLOCKSIZE_Pos) /*!< 0x0080 */

#define SDIO_DCTRL_RWSTART_Pos              (8U)                               
#define SDIO_DCTRL_RWSTART_Msk              (0x1U << SDIO_DCTRL_RWSTART_Pos)   /*!< 0x00000100 */
#define SDIO_DCTRL_RWSTART                  SDIO_DCTRL_RWSTART_Msk             /*!< Read wait start */
#define SDIO_DCTRL_RWSTOP_Pos               (9U)                               
#define SDIO_DCTRL_RWSTOP_Msk               (0x1U << SDIO_DCTRL_RWSTOP_Pos)    /*!< 0x00000200 */
#define SDIO_DCTRL_RWSTOP                   SDIO_DCTRL_RWSTOP_Msk              /*!< Read wait stop */
#define SDIO_DCTRL_RWMOD_Pos                (10U)                              
#define SDIO_DCTRL_RWMOD_Msk                (0x1U << SDIO_DCTRL_RWMOD_Pos)     /*!< 0x00000400 */
#define SDIO_DCTRL_RWMOD                    SDIO_DCTRL_RWMOD_Msk               /*!< Read wait mode */
#define SDIO_DCTRL_SDIOEN_Pos               (11U)                              
#define SDIO_DCTRL_SDIOEN_Msk               (0x1U << SDIO_DCTRL_SDIOEN_Pos)    /*!< 0x00000800 */
#define SDIO_DCTRL_SDIOEN                   SDIO_DCTRL_SDIOEN_Msk              /*!< SD I/O enable functions */

/******************  Bit definition for SDIO_DCOUNT register  *****************/
#define SDIO_DCOUNT_DATACOUNT_Pos           (0U)                               
#define SDIO_DCOUNT_DATACOUNT_Msk           (0x1FFFFFFU << SDIO_DCOUNT_DATACOUNT_Pos) /*!< 0x01FFFFFF */
#define SDIO_DCOUNT_DATACOUNT               SDIO_DCOUNT_DATACOUNT_Msk          /*!< Data count value */

/******************  Bit definition for SDIO_STA register  ********************/
#define SDIO_STA_CCRCFAIL_Pos               (0U)                               
#define SDIO_STA_CCRCFAIL_Msk               (0x1U << SDIO_STA_CCRCFAIL_Pos)    /*!< 0x00000001 */
#define SDIO_STA_CCRCFAIL                   SDIO_STA_CCRCFAIL_Msk              /*!< Command response received (CRC check failed) */
#define SDIO_STA_DCRCFAIL_Pos               (1U)                               
#define SDIO_STA_DCRCFAIL_Msk               (0x1U << SDIO_STA_DCRCFAIL_Pos)    /*!< 0x00000002 */
#define SDIO_STA_DCRCFAIL                   SDIO_STA_DCRCFAIL_Msk              /*!< Data block sent/received (CRC check failed) */
#define SDIO_STA_CTIMEOUT_Pos               (2U)                               
#define SDIO_STA_CTIMEOUT_Msk               (0x1U << SDIO_STA_CTIMEOUT_Pos)    /*!< 0x00000004 */
#define SDIO_STA_CTIMEOUT                   SDIO_STA_CTIMEOUT_Msk              /*!< Command response timeout */
#define SDIO_STA_DTIMEOUT_Pos               (3U)                               
#define SDIO_STA_DTIMEOUT_Msk               (0x1U << SDIO_STA_DTIMEOUT_Pos)    /*!< 0x00000008 */
#define SDIO_STA_DTIMEOUT                   SDIO_STA_DTIMEOUT_Msk              /*!< Data timeout */
#define SDIO_STA_TXUNDERR_Pos               (4U)                               
#define SDIO_STA_TXUNDERR_Msk               (0x1U << SDIO_STA_TXUNDERR_Pos)    /*!< 0x00000010 */
#define SDIO_STA_TXUNDERR                   SDIO_STA_TXUNDERR_Msk              /*!< Transmit FIFO underrun error */
#define SDIO_STA_RXOVERR_Pos                (5U)                               
#define SDIO_STA_RXOVERR_Msk                (0x1U << SDIO_STA_RXOVERR_Pos)     /*!< 0x00000020 */
#define SDIO_STA_RXOVERR                    SDIO_STA_RXOVERR_Msk               /*!< Received FIFO overrun error */
#define SDIO_STA_CMDREND_Pos                (6U)                               
#define SDIO_STA_CMDREND_Msk                (0x1U << SDIO_STA_CMDREND_Pos)     /*!< 0x00000040 */
#define SDIO_STA_CMDREND                    SDIO_STA_CMDREND_Msk               /*!< Command response received (CRC check passed) */
#define SDIO_STA_CMDSENT_Pos                (7U)                               
#define SDIO_STA_CMDSENT_Msk                (0x1U << SDIO_STA_CMDSENT_Pos)     /*!< 0x00000080 */
#define SDIO_STA_CMDSENT                    SDIO_STA_CMDSENT_Msk               /*!< Command sent (no response required) */
#define SDIO_STA_DATAEND_Pos                (8U)                               
#define SDIO_STA_DATAEND_Msk                (0x1U << SDIO_STA_DATAEND_Pos)     /*!< 0x00000100 */
#define SDIO_STA_DATAEND                    SDIO_STA_DATAEND_Msk               /*!< Data end (data counter, SDIDCOUNT, is zero) */
#define SDIO_STA_STBITERR_Pos               (9U)                               
#define SDIO_STA_STBITERR_Msk               (0x1U << SDIO_STA_STBITERR_Pos)    /*!< 0x00000200 */
#define SDIO_STA_STBITERR                   SDIO_STA_STBITERR_Msk              /*!< Start bit not detected on all data signals in wide bus mode */
#define SDIO_STA_DBCKEND_Pos                (10U)                              
#define SDIO_STA_DBCKEND_Msk                (0x1U << SDIO_STA_DBCKEND_Pos)     /*!< 0x00000400 */
#define SDIO_STA_DBCKEND                    SDIO_STA_DBCKEND_Msk               /*!< Data block sent/received (CRC check passed) */
#define SDIO_STA_CMDACT_Pos                 (11U)                              
#define SDIO_STA_CMDACT_Msk                 (0x1U << SDIO_STA_CMDACT_Pos)      /*!< 0x00000800 */
#define SDIO_STA_CMDACT                     SDIO_STA_CMDACT_Msk                /*!< Command transfer in progress */
#define SDIO_STA_TXACT_Pos                  (12U)                              
#define SDIO_STA_TXACT_Msk                  (0x1U << SDIO_STA_TXACT_Pos)       /*!< 0x00001000 */
#define SDIO_STA_TXACT                      SDIO_STA_TXACT_Msk                 /*!< Data transmit in progress */
#define SDIO_STA_RXACT_Pos                  (13U)                              
#define SDIO_STA_RXACT_Msk                  (0x1U << SDIO_STA_RXACT_Pos)       /*!< 0x00002000 */
#define SDIO_STA_RXACT                      SDIO_STA_RXACT_Msk                 /*!< Data receive in progress */
#define SDIO_STA_TXFIFOHE_Pos               (14U)                              
#define SDIO_STA_TXFIFOHE_Msk               (0x1U << SDIO_STA_TXFIFOHE_Pos)    /*!< 0x00004000 */
#define SDIO_STA_TXFIFOHE                   SDIO_STA_TXFIFOHE_Msk              /*!< Transmit FIFO Half Empty: at least 8 words can be written into the FIFO */
#define SDIO_STA_RXFIFOHF_Pos               (15U)                              
#define SDIO_STA_RXFIFOHF_Msk               (0x1U << SDIO_STA_RXFIFOHF_Pos)    /*!< 0x00008000 */
#define SDIO_STA_RXFIFOHF                   SDIO_STA_RXFIFOHF_Msk              /*!< Receive FIFO Half Full: there are at least 8 words in the FIFO */
#define SDIO_STA_TXFIFOF_Pos                (16U)                              
#define SDIO_STA_TXFIFOF_Msk                (0x1U << SDIO_STA_TXFIFOF_Pos)     /*!< 0x00010000 */
#define SDIO_STA_TXFIFOF                    SDIO_STA_TXFIFOF_Msk               /*!< Transmit FIFO full */
#define SDIO_STA_RXFIFOF_Pos                (17U)                              
#define SDIO_STA_RXFIFOF_Msk                (0x1U << SDIO_STA_RXFIFOF_Pos)     /*!< 0x00020000 */
#define SDIO_STA_RXFIFOF                    SDIO_STA_RXFIFOF_Msk               /*!< Receive FIFO full */
#define SDIO_STA_TXFIFOE_Pos                (18U)                              
#define SDIO_STA_TXFIFOE_Msk                (0x1U << SDIO_STA_TXFIFOE_Pos)     /*!< 0x00040000 */
#define SDIO_STA_TXFIFOE                    SDIO_STA_TXFIFOE_Msk               /*!< Transmit FIFO empty */
#define SDIO_STA_RXFIFOE_Pos                (19U)                              
#define SDIO_STA_RXFIFOE_Msk                (0x1U << SDIO_STA_RXFIFOE_Pos)     /*!< 0x00080000 */
#define SDIO_STA_RXFIFOE                    SDIO_STA_RXFIFOE_Msk               /*!< Receive FIFO empty */
#define SDIO_STA_TXDAVL_Pos                 (20U)                              
#define SDIO_STA_TXDAVL_Msk                 (0x1U << SDIO_STA_TXDAVL_Pos)      /*!< 0x00100000 */
#define SDIO_STA_TXDAVL                     SDIO_STA_TXDAVL_Msk                /*!< Data available in transmit FIFO */
#define SDIO_STA_RXDAVL_Pos                 (21U)                              
#define SDIO_STA_RXDAVL_Msk                 (0x1U << SDIO_STA_RXDAVL_Pos)      /*!< 0x00200000 */
#define SDIO_STA_RXDAVL                     SDIO_STA_RXDAVL_Msk                /*!< Data available in receive FIFO */
#define SDIO_STA_SDIOIT_Pos                 (22U)                              
#define SDIO_STA_SDIOIT_Msk                 (0x1U << SDIO_STA_SDIOIT_Pos)      /*!< 0x00400000 */
#define SDIO_STA_SDIOIT                     SDIO_STA_SDIOIT_Msk                /*!< SDIO interrupt received */
#define SDIO_STA_CEATAEND_Pos               (23U)                              
#define SDIO_STA_CEATAEND_Msk               (0x1U << SDIO_STA_CEATAEND_Pos)    /*!< 0x00800000 */
#define SDIO_STA_CEATAEND                   SDIO_STA_CEATAEND_Msk              /*!< CE-ATA command completion signal received for CMD61 */

/*******************  Bit definition for SDIO_ICR register  *******************/
#define SDIO_ICR_CCRCFAILC_Pos              (0U)                               
#define SDIO_ICR_CCRCFAILC_Msk              (0x1U << SDIO_ICR_CCRCFAILC_Pos)   /*!< 0x00000001 */
#define SDIO_ICR_CCRCFAILC                  SDIO_ICR_CCRCFAILC_Msk             /*!< CCRCFAIL flag clear bit */
#define SDIO_ICR_DCRCFAILC_Pos              (1U)                               
#define SDIO_ICR_DCRCFAILC_Msk              (0x1U << SDIO_ICR_DCRCFAILC_Pos)   /*!< 0x00000002 */
#define SDIO_ICR_DCRCFAILC                  SDIO_ICR_DCRCFAILC_Msk             /*!< DCRCFAIL flag clear bit */
#define SDIO_ICR_CTIMEOUTC_Pos              (2U)                               
#define SDIO_ICR_CTIMEOUTC_Msk              (0x1U << SDIO_ICR_CTIMEOUTC_Pos)   /*!< 0x00000004 */
#define SDIO_ICR_CTIMEOUTC                  SDIO_ICR_CTIMEOUTC_Msk             /*!< CTIMEOUT flag clear bit */
#define SDIO_ICR_DTIMEOUTC_Pos              (3U)                               
#define SDIO_ICR_DTIMEOUTC_Msk              (0x1U << SDIO_ICR_DTIMEOUTC_Pos)   /*!< 0x00000008 */
#define SDIO_ICR_DTIMEOUTC                  SDIO_ICR_DTIMEOUTC_Msk             /*!< DTIMEOUT flag clear bit */
#define SDIO_ICR_TXUNDERRC_Pos              (4U)                               
#define SDIO_ICR_TXUNDERRC_Msk              (0x1U << SDIO_ICR_TXUNDERRC_Pos)   /*!< 0x00000010 */
#define SDIO_ICR_TXUNDERRC                  SDIO_ICR_TXUNDERRC_Msk             /*!< TXUNDERR flag clear bit */
#define SDIO_ICR_RXOVERRC_Pos               (5U)                               
#define SDIO_ICR_RXOVERRC_Msk               (0x1U << SDIO_ICR_RXOVERRC_Pos)    /*!< 0x00000020 */
#define SDIO_ICR_RXOVERRC                   SDIO_ICR_RXOVERRC_Msk              /*!< RXOVERR flag clear bit */
#define SDIO_ICR_CMDRENDC_Pos               (6U)                               
#define SDIO_ICR_CMDRENDC_Msk               (0x1U << SDIO_ICR_CMDRENDC_Pos)    /*!< 0x00000040 */
#define SDIO_ICR_CMDRENDC                   SDIO_ICR_CMDRENDC_Msk              /*!< CMDREND flag clear bit */
#define SDIO_ICR_CMDSENTC_Pos               (7U)                               
#define SDIO_ICR_CMDSENTC_Msk               (0x1U << SDIO_ICR_CMDSENTC_Pos)    /*!< 0x00000080 */
#define SDIO_ICR_CMDSENTC                   SDIO_ICR_CMDSENTC_Msk              /*!< CMDSENT flag clear bit */
#define SDIO_ICR_DATAENDC_Pos               (8U)                               
#define SDIO_ICR_DATAENDC_Msk               (0x1U << SDIO_ICR_DATAENDC_Pos)    /*!< 0x00000100 */
#define SDIO_ICR_DATAENDC                   SDIO_ICR_DATAENDC_Msk              /*!< DATAEND flag clear bit */
#define SDIO_ICR_STBITERRC_Pos              (9U)                               
#define SDIO_ICR_STBITERRC_Msk              (0x1U << SDIO_ICR_STBITERRC_Pos)   /*!< 0x00000200 */
#define SDIO_ICR_STBITERRC                  SDIO_ICR_STBITERRC_Msk             /*!< STBITERR flag clear bit */
#define SDIO_ICR_DBCKENDC_Pos               (10U)                              
#define SDIO_ICR_DBCKENDC_Msk               (0x1U << SDIO_ICR_DBCKENDC_Pos)    /*!< 0x00000400 */
#define SDIO_ICR_DBCKENDC                   SDIO_ICR_DBCKENDC_Msk              /*!< DBCKEND flag clear bit */
#define SDIO_ICR_SDIOITC_Pos                (22U)                              
#define SDIO_ICR_SDIOITC_Msk                (0x1U << SDIO_ICR_SDIOITC_Pos)     /*!< 0x00400000 */
#define SDIO_ICR_SDIOITC                    SDIO_ICR_SDIOITC_Msk               /*!< SDIOIT flag clear bit */
#define SDIO_ICR_CEATAENDC_Pos              (23U)                              
#define SDIO_ICR_CEATAENDC_Msk              (0x1U << SDIO_ICR_CEATAENDC_Pos)   /*!< 0x00800000 */
#define SDIO_ICR_CEATAENDC                  SDIO_ICR_CEATAENDC_Msk             /*!< CEATAEND flag clear bit */

/******************  Bit definition for SDIO_MASK register  *******************/
#define SDIO_MASK_CCRCFAILIE_Pos            (0U)                               
#define SDIO_MASK_CCRCFAILIE_Msk            (0x1U << SDIO_MASK_CCRCFAILIE_Pos) /*!< 0x00000001 */
#define SDIO_MASK_CCRCFAILIE                SDIO_MASK_CCRCFAILIE_Msk           /*!< Command CRC Fail Interrupt Enable */
#define SDIO_MASK_DCRCFAILIE_Pos            (1U)                               
#define SDIO_MASK_DCRCFAILIE_Msk            (0x1U << SDIO_MASK_DCRCFAILIE_Pos) /*!< 0x00000002 */
#define SDIO_MASK_DCRCFAILIE                SDIO_MASK_DCRCFAILIE_Msk           /*!< Data CRC Fail Interrupt Enable */
#define SDIO_MASK_CTIMEOUTIE_Pos            (2U)                               
#define SDIO_MASK_CTIMEOUTIE_Msk            (0x1U << SDIO_MASK_CTIMEOUTIE_Pos) /*!< 0x00000004 */
#define SDIO_MASK_CTIMEOUTIE                SDIO_MASK_CTIMEOUTIE_Msk           /*!< Command TimeOut Interrupt Enable */
#define SDIO_MASK_DTIMEOUTIE_Pos            (3U)                               
#define SDIO_MASK_DTIMEOUTIE_Msk            (0x1U << SDIO_MASK_DTIMEOUTIE_Pos) /*!< 0x00000008 */
#define SDIO_MASK_DTIMEOUTIE                SDIO_MASK_DTIMEOUTIE_Msk           /*!< Data TimeOut Interrupt Enable */
#define SDIO_MASK_TXUNDERRIE_Pos            (4U)                               
#define SDIO_MASK_TXUNDERRIE_Msk            (0x1U << SDIO_MASK_TXUNDERRIE_Pos) /*!< 0x00000010 */
#define SDIO_MASK_TXUNDERRIE                SDIO_MASK_TXUNDERRIE_Msk           /*!< Tx FIFO UnderRun Error Interrupt Enable */
#define SDIO_MASK_RXOVERRIE_Pos             (5U)                               
#define SDIO_MASK_RXOVERRIE_Msk             (0x1U << SDIO_MASK_RXOVERRIE_Pos)  /*!< 0x00000020 */
#define SDIO_MASK_RXOVERRIE                 SDIO_MASK_RXOVERRIE_Msk            /*!< Rx FIFO OverRun Error Interrupt Enable */
#define SDIO_MASK_CMDRENDIE_Pos             (6U)                               
#define SDIO_MASK_CMDRENDIE_Msk             (0x1U << SDIO_MASK_CMDRENDIE_Pos)  /*!< 0x00000040 */
#define SDIO_MASK_CMDRENDIE                 SDIO_MASK_CMDRENDIE_Msk            /*!< Command Response Received Interrupt Enable */
#define SDIO_MASK_CMDSENTIE_Pos             (7U)                               
#define SDIO_MASK_CMDSENTIE_Msk             (0x1U << SDIO_MASK_CMDSENTIE_Pos)  /*!< 0x00000080 */
#define SDIO_MASK_CMDSENTIE                 SDIO_MASK_CMDSENTIE_Msk            /*!< Command Sent Interrupt Enable */
#define SDIO_MASK_DATAENDIE_Pos             (8U)                               
#define SDIO_MASK_DATAENDIE_Msk             (0x1U << SDIO_MASK_DATAENDIE_Pos)  /*!< 0x00000100 */
#define SDIO_MASK_DATAENDIE                 SDIO_MASK_DATAENDIE_Msk            /*!< Data End Interrupt Enable */
#define SDIO_MASK_STBITERRIE_Pos            (9U)                               
#define SDIO_MASK_STBITERRIE_Msk            (0x1U << SDIO_MASK_STBITERRIE_Pos) /*!< 0x00000200 */
#define SDIO_MASK_STBITERRIE                SDIO_MASK_STBITERRIE_Msk           /*!< Start Bit Error Interrupt Enable */
#define SDIO_MASK_DBCKENDIE_Pos             (10U)                              
#define SDIO_MASK_DBCKENDIE_Msk             (0x1U << SDIO_MASK_DBCKENDIE_Pos)  /*!< 0x00000400 */
#define SDIO_MASK_DBCKENDIE                 SDIO_MASK_DBCKENDIE_Msk            /*!< Data Block End Interrupt Enable */
#define SDIO_MASK_CMDACTIE_Pos              (11U)                              
#define SDIO_MASK_CMDACTIE_Msk              (0x1U << SDIO_MASK_CMDACTIE_Pos)   /*!< 0x00000800 */
#define SDIO_MASK_CMDACTIE                  SDIO_MASK_CMDACTIE_Msk             /*!< Command Acting Interrupt Enable */
#define SDIO_MASK_TXACTIE_Pos               (12U)                              
#define SDIO_MASK_TXACTIE_Msk               (0x1U << SDIO_MASK_TXACTIE_Pos)    /*!< 0x00001000 */
#define SDIO_MASK_TXACTIE                   SDIO_MASK_TXACTIE_Msk              /*!< Data Transmit Acting Interrupt Enable */
#define SDIO_MASK_RXACTIE_Pos               (13U)                              
#define SDIO_MASK_RXACTIE_Msk               (0x1U << SDIO_MASK_RXACTIE_Pos)    /*!< 0x00002000 */
#define SDIO_MASK_RXACTIE                   SDIO_MASK_RXACTIE_Msk              /*!< Data receive acting interrupt enabled */
#define SDIO_MASK_TXFIFOHEIE_Pos            (14U)                              
#define SDIO_MASK_TXFIFOHEIE_Msk            (0x1U << SDIO_MASK_TXFIFOHEIE_Pos) /*!< 0x00004000 */
#define SDIO_MASK_TXFIFOHEIE                SDIO_MASK_TXFIFOHEIE_Msk           /*!< Tx FIFO Half Empty interrupt Enable */
#define SDIO_MASK_RXFIFOHFIE_Pos            (15U)                              
#define SDIO_MASK_RXFIFOHFIE_Msk            (0x1U << SDIO_MASK_RXFIFOHFIE_Pos) /*!< 0x00008000 */
#define SDIO_MASK_RXFIFOHFIE                SDIO_MASK_RXFIFOHFIE_Msk           /*!< Rx FIFO Half Full interrupt Enable */
#define SDIO_MASK_TXFIFOFIE_Pos             (16U)                              
#define SDIO_MASK_TXFIFOFIE_Msk             (0x1U << SDIO_MASK_TXFIFOFIE_Pos)  /*!< 0x00010000 */
#define SDIO_MASK_TXFIFOFIE                 SDIO_MASK_TXFIFOFIE_Msk            /*!< Tx FIFO Full interrupt Enable */
#define SDIO_MASK_RXFIFOFIE_Pos             (17U)                              
#define SDIO_MASK_RXFIFOFIE_Msk             (0x1U << SDIO_MASK_RXFIFOFIE_Pos)  /*!< 0x00020000 */
#define SDIO_MASK_RXFIFOFIE                 SDIO_MASK_RXFIFOFIE_Msk            /*!< Rx FIFO Full interrupt Enable */
#define SDIO_MASK_TXFIFOEIE_Pos             (18U)                              
#define SDIO_MASK_TXFIFOEIE_Msk             (0x1U << SDIO_MASK_TXFIFOEIE_Pos)  /*!< 0x00040000 */
#define SDIO_MASK_TXFIFOEIE                 SDIO_MASK_TXFIFOEIE_Msk            /*!< Tx FIFO Empty interrupt Enable */
#define SDIO_MASK_RXFIFOEIE_Pos             (19U)                              
#define SDIO_MASK_RXFIFOEIE_Msk             (0x1U << SDIO_MASK_RXFIFOEIE_Pos)  /*!< 0x00080000 */
#define SDIO_MASK_RXFIFOEIE                 SDIO_MASK_RXFIFOEIE_Msk            /*!< Rx FIFO Empty interrupt Enable */
#define SDIO_MASK_TXDAVLIE_Pos              (20U)                              
#define SDIO_MASK_TXDAVLIE_Msk              (0x1U << SDIO_MASK_TXDAVLIE_Pos)   /*!< 0x00100000 */
#define SDIO_MASK_TXDAVLIE                  SDIO_MASK_TXDAVLIE_Msk             /*!< Data available in Tx FIFO interrupt Enable */
#define SDIO_MASK_RXDAVLIE_Pos              (21U)                              
#define SDIO_MASK_RXDAVLIE_Msk              (0x1U << SDIO_MASK_RXDAVLIE_Pos)   /*!< 0x00200000 */
#define SDIO_MASK_RXDAVLIE                  SDIO_MASK_RXDAVLIE_Msk             /*!< Data available in Rx FIFO interrupt Enable */
#define SDIO_MASK_SDIOITIE_Pos              (22U)                              
#define SDIO_MASK_SDIOITIE_Msk              (0x1U << SDIO_MASK_SDIOITIE_Pos)   /*!< 0x00400000 */
#define SDIO_MASK_SDIOITIE                  SDIO_MASK_SDIOITIE_Msk             /*!< SDIO Mode Interrupt Received interrupt Enable */
#define SDIO_MASK_CEATAENDIE_Pos            (23U)                              
#define SDIO_MASK_CEATAENDIE_Msk            (0x1U << SDIO_MASK_CEATAENDIE_Pos) /*!< 0x00800000 */
#define SDIO_MASK_CEATAENDIE                SDIO_MASK_CEATAENDIE_Msk           /*!< CE-ATA command completion signal received Interrupt Enable */

/*****************  Bit definition for SDIO_FIFOCNT register  *****************/
#define SDIO_FIFOCNT_FIFOCOUNT_Pos          (0U)                               
#define SDIO_FIFOCNT_FIFOCOUNT_Msk          (0xFFFFFFU << SDIO_FIFOCNT_FIFOCOUNT_Pos) /*!< 0x00FFFFFF */
#define SDIO_FIFOCNT_FIFOCOUNT              SDIO_FIFOCNT_FIFOCOUNT_Msk         /*!< Remaining number of words to be written to or read from the FIFO */

/******************  Bit definition for SDIO_FIFO register  *******************/
#define SDIO_FIFO_FIFODATA_Pos              (0U)                               
#define SDIO_FIFO_FIFODATA_Msk              (0xFFFFFFFFU << SDIO_FIFO_FIFODATA_Pos) /*!< 0xFFFFFFFF */
#define SDIO_FIFO_FIFODATA                  SDIO_FIFO_FIFODATA_Msk             /*!< Receive and transmit FIFO data */


/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)                               
#define I2C_CR1_PE_Msk                      (0x1U << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)                               
#define I2C_CR1_SMBUS_Msk                   (0x1U << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)                               
#define I2C_CR1_SMBTYPE_Msk                 (0x1U << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)                               
#define I2C_CR1_ENARP_Msk                   (0x1U << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)                               
#define I2C_CR1_ENPEC_Msk                   (0x1U << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)                               
#define I2C_CR1_ENGC_Msk                    (0x1U << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)                               
#define I2C_CR1_NOSTRETCH_Msk               (0x1U << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)                               
#define I2C_CR1_START_Msk                   (0x1U << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)                               
#define I2C_CR1_STOP_Msk                    (0x1U << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)                              
#define I2C_CR1_ACK_Msk                     (0x1U << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)                              
#define I2C_CR1_POS_Msk                     (0x1U << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)                              
#define I2C_CR1_PEC_Msk                     (0x1U << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)                              
#define I2C_CR1_ALERT_Msk                   (0x1U << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)                              
#define I2C_CR1_SWRST_Msk                   (0x1U << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */

/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)                               
#define I2C_CR2_FREQ_Msk                    (0x3FU << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_FREQ_0                      (0x01U << I2C_CR2_FREQ_Pos)        /*!< 0x00000001 */
#define I2C_CR2_FREQ_1                      (0x02U << I2C_CR2_FREQ_Pos)        /*!< 0x00000002 */
#define I2C_CR2_FREQ_2                      (0x04U << I2C_CR2_FREQ_Pos)        /*!< 0x00000004 */
#define I2C_CR2_FREQ_3                      (0x08U << I2C_CR2_FREQ_Pos)        /*!< 0x00000008 */
#define I2C_CR2_FREQ_4                      (0x10U << I2C_CR2_FREQ_Pos)        /*!< 0x00000010 */
#define I2C_CR2_FREQ_5                      (0x20U << I2C_CR2_FREQ_Pos)        /*!< 0x00000020 */

#define I2C_CR2_ITERREN_Pos                 (8U)                               
#define I2C_CR2_ITERREN_Msk                 (0x1U << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)                               
#define I2C_CR2_ITEVTEN_Msk                 (0x1U << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)                              
#define I2C_CR2_ITBUFEN_Msk                 (0x1U << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)                              
#define I2C_CR2_DMAEN_Msk                   (0x1U << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)                              
#define I2C_CR2_LAST_Msk                    (0x1U << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */

/*******************  Bit definition for I2C_OAR1 register  *******************/
#define I2C_OAR1_ADD1_7                     0x000000FEU             /*!< Interface Address */
#define I2C_OAR1_ADD8_9                     0x00000300U             /*!< Interface Address */

#define I2C_OAR1_ADD0_Pos                   (0U)                               
#define I2C_OAR1_ADD0_Msk                   (0x1U << I2C_OAR1_ADD0_Pos)        /*!< 0x00000001 */
#define I2C_OAR1_ADD0                       I2C_OAR1_ADD0_Msk                  /*!< Bit 0 */
#define I2C_OAR1_ADD1_Pos                   (1U)                               
#define I2C_OAR1_ADD1_Msk                   (0x1U << I2C_OAR1_ADD1_Pos)        /*!< 0x00000002 */
#define I2C_OAR1_ADD1                       I2C_OAR1_ADD1_Msk                  /*!< Bit 1 */
#define I2C_OAR1_ADD2_Pos                   (2U)                               
#define I2C_OAR1_ADD2_Msk                   (0x1U << I2C_OAR1_ADD2_Pos)        /*!< 0x00000004 */
#define I2C_OAR1_ADD2                       I2C_OAR1_ADD2_Msk                  /*!< Bit 2 */
#define I2C_OAR1_ADD3_Pos                   (3U)                               
#define I2C_OAR1_ADD3_Msk                   (0x1U << I2C_OAR1_ADD3_Pos)        /*!< 0x00000008 */
#define I2C_OAR1_ADD3                       I2C_OAR1_ADD3_Msk                  /*!< Bit 3 */
#define I2C_OAR1_ADD4_Pos                   (4U)                               
#define I2C_OAR1_ADD4_Msk                   (0x1U << I2C_OAR1_ADD4_Pos)        /*!< 0x00000010 */
#define I2C_OAR1_ADD4                       I2C_OAR1_ADD4_Msk                  /*!< Bit 4 */
#define I2C_OAR1_ADD5_Pos                   (5U)                               
#define I2C_OAR1_ADD5_Msk                   (0x1U << I2C_OAR1_ADD5_Pos)        /*!< 0x00000020 */
#define I2C_OAR1_ADD5                       I2C_OAR1_ADD5_Msk                  /*!< Bit 5 */
#define I2C_OAR1_ADD6_Pos                   (6U)                               
#define I2C_OAR1_ADD6_Msk                   (0x1U << I2C_OAR1_ADD6_Pos)        /*!< 0x00000040 */
#define I2C_OAR1_ADD6                       I2C_OAR1_ADD6_Msk                  /*!< Bit 6 */
#define I2C_OAR1_ADD7_Pos                   (7U)                               
#define I2C_OAR1_ADD7_Msk                   (0x1U << I2C_OAR1_ADD7_Pos)        /*!< 0x00000080 */
#define I2C_OAR1_ADD7                       I2C_OAR1_ADD7_Msk                  /*!< Bit 7 */
#define I2C_OAR1_ADD8_Pos                   (8U)                               
#define I2C_OAR1_ADD8_Msk                   (0x1U << I2C_OAR1_ADD8_Pos)        /*!< 0x00000100 */
#define I2C_OAR1_ADD8                       I2C_OAR1_ADD8_Msk                  /*!< Bit 8 */
#define I2C_OAR1_ADD9_Pos                   (9U)                               
#define I2C_OAR1_ADD9_Msk                   (0x1U << I2C_OAR1_ADD9_Pos)        /*!< 0x00000200 */
#define I2C_OAR1_ADD9                       I2C_OAR1_ADD9_Msk                  /*!< Bit 9 */

#define I2C_OAR1_ADDMODE_Pos                (15U)                              
#define I2C_OAR1_ADDMODE_Msk                (0x1U << I2C_OAR1_ADDMODE_Pos)     /*!< 0x00008000 */
#define I2C_OAR1_ADDMODE                    I2C_OAR1_ADDMODE_Msk               /*!< Addressing Mode (Slave mode) */

/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)                               
#define I2C_OAR2_ENDUAL_Msk                 (0x1U << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)                               
#define I2C_OAR2_ADD2_Msk                   (0x7FU << I2C_OAR2_ADD2_Pos)       /*!< 0x000000FE */
#define I2C_OAR2_ADD2                       I2C_OAR2_ADD2_Msk                  /*!< Interface address */

/********************  Bit definition for I2C_DR register  ********************/
#define I2C_DR_DR_Pos             (0U)                                         
#define I2C_DR_DR_Msk             (0xFFU << I2C_DR_DR_Pos)                     /*!< 0x000000FF */
#define I2C_DR_DR                 I2C_DR_DR_Msk                                /*!< 8-bit Data Register         */

/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)                               
#define I2C_SR1_SB_Msk                      (0x1U << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)                               
#define I2C_SR1_ADDR_Msk                    (0x1U << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)                               
#define I2C_SR1_BTF_Msk                     (0x1U << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)                               
#define I2C_SR1_ADD10_Msk                   (0x1U << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)                               
#define I2C_SR1_STOPF_Msk                   (0x1U << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)                               
#define I2C_SR1_RXNE_Msk                    (0x1U << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)                               
#define I2C_SR1_TXE_Msk                     (0x1U << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)                               
#define I2C_SR1_BERR_Msk                    (0x1U << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)                               
#define I2C_SR1_ARLO_Msk                    (0x1U << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)                              
#define I2C_SR1_AF_Msk                      (0x1U << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)                              
#define I2C_SR1_OVR_Msk                     (0x1U << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)                              
#define I2C_SR1_PECERR_Msk                  (0x1U << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)                              
#define I2C_SR1_TIMEOUT_Msk                 (0x1U << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)                              
#define I2C_SR1_SMBALERT_Msk                (0x1U << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)                               
#define I2C_SR2_MSL_Msk                     (0x1U << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)                               
#define I2C_SR2_BUSY_Msk                    (0x1U << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)                               
#define I2C_SR2_TRA_Msk                     (0x1U << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)                               
#define I2C_SR2_GENCALL_Msk                 (0x1U << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)                               
#define I2C_SR2_SMBDEFAULT_Msk              (0x1U << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)                               
#define I2C_SR2_SMBHOST_Msk                 (0x1U << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)                               
#define I2C_SR2_DUALF_Msk                   (0x1U << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)                               
#define I2C_SR2_PEC_Msk                     (0xFFU << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */

/*******************  Bit definition for I2C_CCR register  ********************/
#define I2C_CCR_CCR_Pos                     (0U)                               
#define I2C_CCR_CCR_Msk                     (0xFFFU << I2C_CCR_CCR_Pos)        /*!< 0x00000FFF */
#define I2C_CCR_CCR                         I2C_CCR_CCR_Msk                    /*!< Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CCR_DUTY_Pos                    (14U)                              
#define I2C_CCR_DUTY_Msk                    (0x1U << I2C_CCR_DUTY_Pos)         /*!< 0x00004000 */
#define I2C_CCR_DUTY                        I2C_CCR_DUTY_Msk                   /*!< Fast Mode Duty Cycle */
#define I2C_CCR_FS_Pos                      (15U)                              
#define I2C_CCR_FS_Msk                      (0x1U << I2C_CCR_FS_Pos)           /*!< 0x00008000 */
#define I2C_CCR_FS                          I2C_CCR_FS_Msk                     /*!< I2C Master Mode Selection */

/******************  Bit definition for I2C_TRISE register  *******************/
#define I2C_TRISE_TRISE_Pos                 (0U)                               
#define I2C_TRISE_TRISE_Msk                 (0x3FU << I2C_TRISE_TRISE_Pos)     /*!< 0x0000003F */
#define I2C_TRISE_TRISE                     I2C_TRISE_TRISE_Msk                /*!< Maximum Rise Time in Fast/Standard mode (Master mode) */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_CRL register  *******************/
#define GPIO_CRL_MODE_Pos                    (0U)                              
#define GPIO_CRL_MODE_Msk                    (0x33333333U << GPIO_CRL_MODE_Pos) /*!< 0x33333333 */
#define GPIO_CRL_MODE                        GPIO_CRL_MODE_Msk                 /*!< Port x mode bits */

#define GPIO_CRL_MODE0_Pos                   (0U)                              
#define GPIO_CRL_MODE0_Msk                   (0x3U << GPIO_CRL_MODE0_Pos)      /*!< 0x00000003 */
#define GPIO_CRL_MODE0                       GPIO_CRL_MODE0_Msk                /*!< MODE0[1:0] bits (Port x mode bits, pin 0) */
#define GPIO_CRL_MODE0_0                     (0x1U << GPIO_CRL_MODE0_Pos)      /*!< 0x00000001 */
#define GPIO_CRL_MODE0_1                     (0x2U << GPIO_CRL_MODE0_Pos)      /*!< 0x00000002 */

#define GPIO_CRL_MODE1_Pos                   (4U)                              
#define GPIO_CRL_MODE1_Msk                   (0x3U << GPIO_CRL_MODE1_Pos)      /*!< 0x00000030 */
#define GPIO_CRL_MODE1                       GPIO_CRL_MODE1_Msk                /*!< MODE1[1:0] bits (Port x mode bits, pin 1) */
#define GPIO_CRL_MODE1_0                     (0x1U << GPIO_CRL_MODE1_Pos)      /*!< 0x00000010 */
#define GPIO_CRL_MODE1_1                     (0x2U << GPIO_CRL_MODE1_Pos)      /*!< 0x00000020 */

#define GPIO_CRL_MODE2_Pos                   (8U)                              
#define GPIO_CRL_MODE2_Msk                   (0x3U << GPIO_CRL_MODE2_Pos)      /*!< 0x00000300 */
#define GPIO_CRL_MODE2                       GPIO_CRL_MODE2_Msk                /*!< MODE2[1:0] bits (Port x mode bits, pin 2) */
#define GPIO_CRL_MODE2_0                     (0x1U << GPIO_CRL_MODE2_Pos)      /*!< 0x00000100 */
#define GPIO_CRL_MODE2_1                     (0x2U << GPIO_CRL_MODE2_Pos)      /*!< 0x00000200 */

#define GPIO_CRL_MODE3_Pos                   (12U)                             
#define GPIO_CRL_MODE3_Msk                   (0x3U << GPIO_CRL_MODE3_Pos)      /*!< 0x00003000 */
#define GPIO_CRL_MODE3                       GPIO_CRL_MODE3_Msk                /*!< MODE3[1:0] bits (Port x mode bits, pin 3) */
#define GPIO_CRL_MODE3_0                     (0x1U << GPIO_CRL_MODE3_Pos)      /*!< 0x00001000 */
#define GPIO_CRL_MODE3_1                     (0x2U << GPIO_CRL_MODE3_Pos)      /*!< 0x00002000 */

#define GPIO_CRL_MODE4_Pos                   (16U)                             
#define GPIO_CRL_MODE4_Msk                   (0x3U << GPIO_CRL_MODE4_Pos)      /*!< 0x00030000 */
#define GPIO_CRL_MODE4                       GPIO_CRL_MODE4_Msk                /*!< MODE4[1:0] bits (Port x mode bits, pin 4) */
#define GPIO_CRL_MODE4_0                     (0x1U << GPIO_CRL_MODE4_Pos)      /*!< 0x00010000 */
#define GPIO_CRL_MODE4_1                     (0x2U << GPIO_CRL_MODE4_Pos)      /*!< 0x00020000 */

#define GPIO_CRL_MODE5_Pos                   (20U)                             
#define GPIO_CRL_MODE5_Msk                   (0x3U << GPIO_CRL_MODE5_Pos)      /*!< 0x00300000 */
#define GPIO_CRL_MODE5                       GPIO_CRL_MODE5_Msk                /*!< MODE5[1:0] bits (Port x mode bits, pin 5) */
#define GPIO_CRL_MODE5_0                     (0x1U << GPIO_CRL_MODE5_Pos)      /*!< 0x00100000 */
#define GPIO_CRL_MODE5_1                     (0x2U << GPIO_CRL_MODE5_Pos)      /*!< 0x00200000 */

#define GPIO_CRL_MODE6_Pos                   (24U)                             
#define GPIO_CRL_MODE6_Msk                   (0x3U << GPIO_CRL_MODE6_Pos)      /*!< 0x03000000 */
#define GPIO_CRL_MODE6                       GPIO_CRL_MODE6_Msk                /*!< MODE6[1:0] bits (Port x mode bits, pin 6) */
#define GPIO_CRL_MODE6_0                     (0x1U << GPIO_CRL_MODE6_Pos)      /*!< 0x01000000 */
#define GPIO_CRL_MODE6_1                     (0x2U << GPIO_CRL_MODE6_Pos)      /*!< 0x02000000 */

#define GPIO_CRL_MODE7_Pos                   (28U)                             
#define GPIO_CRL_MODE7_Msk                   (0x3U << GPIO_CRL_MODE7_Pos)      /*!< 0x30000000 */
#define GPIO_CRL_MODE7                       GPIO_CRL_MODE7_Msk                /*!< MODE7[1:0] bits (Port x mode bits, pin 7) */
#define GPIO_CRL_MODE7_0                     (0x1U << GPIO_CRL_MODE7_Pos)      /*!< 0x10000000 */
#define GPIO_CRL_MODE7_1                     (0x2U << GPIO_CRL_MODE7_Pos)      /*!< 0x20000000 */

#define GPIO_CRL_CNF_Pos                     (2U)                              
#define GPIO_CRL_CNF_Msk                     (0x33333333U << GPIO_CRL_CNF_Pos) /*!< 0xCCCCCCCC */
#define GPIO_CRL_CNF                         GPIO_CRL_CNF_Msk                  /*!< Port x configuration bits */

#define GPIO_CRL_CNF0_Pos                    (2U)                              
#define GPIO_CRL_CNF0_Msk                    (0x3U << GPIO_CRL_CNF0_Pos)       /*!< 0x0000000C */
#define GPIO_CRL_CNF0                        GPIO_CRL_CNF0_Msk                 /*!< CNF0[1:0] bits (Port x configuration bits, pin 0) */
#define GPIO_CRL_CNF0_0                      (0x1U << GPIO_CRL_CNF0_Pos)       /*!< 0x00000004 */
#define GPIO_CRL_CNF0_1                      (0x2U << GPIO_CRL_CNF0_Pos)       /*!< 0x00000008 */

#define GPIO_CRL_CNF1_Pos                    (6U)                              
#define GPIO_CRL_CNF1_Msk                    (0x3U << GPIO_CRL_CNF1_Pos)       /*!< 0x000000C0 */
#define GPIO_CRL_CNF1                        GPIO_CRL_CNF1_Msk                 /*!< CNF1[1:0] bits (Port x configuration bits, pin 1) */
#define GPIO_CRL_CNF1_0                      (0x1U << GPIO_CRL_CNF1_Pos)       /*!< 0x00000040 */
#define GPIO_CRL_CNF1_1                      (0x2U << GPIO_CRL_CNF1_Pos)       /*!< 0x00000080 */

#define GPIO_CRL_CNF2_Pos                    (10U)                             
#define GPIO_CRL_CNF2_Msk                    (0x3U << GPIO_CRL_CNF2_Pos)       /*!< 0x00000C00 */
#define GPIO_CRL_CNF2                        GPIO_CRL_CNF2_Msk                 /*!< CNF2[1:0] bits (Port x configuration bits, pin 2) */
#define GPIO_CRL_CNF2_0                      (0x1U << GPIO_CRL_CNF2_Pos)       /*!< 0x00000400 */
#define GPIO_CRL_CNF2_1                      (0x2U << GPIO_CRL_CNF2_Pos)       /*!< 0x00000800 */

#define GPIO_CRL_CNF3_Pos                    (14U)                             
#define GPIO_CRL_CNF3_Msk                    (0x3U << GPIO_CRL_CNF3_Pos)       /*!< 0x0000C000 */
#define GPIO_CRL_CNF3                        GPIO_CRL_CNF3_Msk                 /*!< CNF3[1:0] bits (Port x configuration bits, pin 3) */
#define GPIO_CRL_CNF3_0                      (0x1U << GPIO_CRL_CNF3_Pos)       /*!< 0x00004000 */
#define GPIO_CRL_CNF3_1                      (0x2U << GPIO_CRL_CNF3_Pos)       /*!< 0x00008000 */

#define GPIO_CRL_CNF4_Pos                    (18U)                             
#define GPIO_CRL_CNF4_Msk                    (0x3U << GPIO_CRL_CNF4_Pos)       /*!< 0x000C0000 */
#define GPIO_CRL_CNF4                        GPIO_CRL_CNF4_Msk                 /*!< CNF4[1:0] bits (Port x configuration bits, pin 4) */
#define GPIO_CRL_CNF4_0                      (0x1U << GPIO_CRL_CNF4_Pos)       /*!< 0x00040000 */
#define GPIO_CRL_CNF4_1                      (0x2U << GPIO_CRL_CNF4_Pos)       /*!< 0x00080000 */

#define GPIO_CRL_CNF5_Pos                    (22U)                             
#define GPIO_CRL_CNF5_Msk                    (0x3U << GPIO_CRL_CNF5_Pos)       /*!< 0x00C00000 */
#define GPIO_CRL_CNF5                        GPIO_CRL_CNF5_Msk                 /*!< CNF5[1:0] bits (Port x configuration bits, pin 5) */
#define GPIO_CRL_CNF5_0                      (0x1U << GPIO_CRL_CNF5_Pos)       /*!< 0x00400000 */
#define GPIO_CRL_CNF5_1                      (0x2U << GPIO_CRL_CNF5_Pos)       /*!< 0x00800000 */

#define GPIO_CRL_CNF6_Pos                    (26U)                             
#define GPIO_CRL_CNF6_Msk                    (0x3U << GPIO_CRL_CNF6_Pos)       /*!< 0x0C000000 */
#define GPIO_CRL_CNF6                        GPIO_CRL_CNF6_Msk                 /*!< CNF6[1:0] bits (Port x configuration bits, pin 6) */
#define GPIO_CRL_CNF6_0                      (0x1U << GPIO_CRL_CNF6_Pos)       /*!< 0x04000000 */
#define GPIO_CRL_CNF6_1                      (0x2U << GPIO_CRL_CNF6_Pos)       /*!< 0x08000000 */

#define GPIO_CRL_CNF7_Pos                    (30U)                             
#define GPIO_CRL_CNF7_Msk                    (0x3U << GPIO_CRL_CNF7_Pos)       /*!< 0xC0000000 */
#define GPIO_CRL_CNF7                        GPIO_CRL_CNF7_Msk                 /*!< CNF7[1:0] bits (Port x configuration bits, pin 7) */
#define GPIO_CRL_CNF7_0                      (0x1U << GPIO_CRL_CNF7_Pos)       /*!< 0x40000000 */
#define GPIO_CRL_CNF7_1                      (0x2U << GPIO_CRL_CNF7_Pos)       /*!< 0x80000000 */

/*******************  Bit definition for GPIO_CRH register  *******************/
#define GPIO_CRH_MODE_Pos                    (0U)                              
#define GPIO_CRH_MODE_Msk                    (0x33333333U << GPIO_CRH_MODE_Pos) /*!< 0x33333333 */
#define GPIO_CRH_MODE                        GPIO_CRH_MODE_Msk                 /*!< Port x mode bits */

#define GPIO_CRH_MODE8_Pos                   (0U)                              
#define GPIO_CRH_MODE8_Msk                   (0x3U << GPIO_CRH_MODE8_Pos)      /*!< 0x00000003 */
#define GPIO_CRH_MODE8                       GPIO_CRH_MODE8_Msk                /*!< MODE8[1:0] bits (Port x mode bits, pin 8) */
#define GPIO_CRH_MODE8_0                     (0x1U << GPIO_CRH_MODE8_Pos)      /*!< 0x00000001 */
#define GPIO_CRH_MODE8_1                     (0x2U << GPIO_CRH_MODE8_Pos)      /*!< 0x00000002 */

#define GPIO_CRH_MODE9_Pos                   (4U)                              
#define GPIO_CRH_MODE9_Msk                   (0x3U << GPIO_CRH_MODE9_Pos)      /*!< 0x00000030 */
#define GPIO_CRH_MODE9                       GPIO_CRH_MODE9_Msk                /*!< MODE9[1:0] bits (Port x mode bits, pin 9) */
#define GPIO_CRH_MODE9_0                     (0x1U << GPIO_CRH_MODE9_Pos)      /*!< 0x00000010 */
#define GPIO_CRH_MODE9_1                     (0x2U << GPIO_CRH_MODE9_Pos)      /*!< 0x00000020 */

#define GPIO_CRH_MODE10_Pos                  (8U)                              
#define GPIO_CRH_MODE10_Msk                  (0x3U << GPIO_CRH_MODE10_Pos)     /*!< 0x00000300 */
#define GPIO_CRH_MODE10                      GPIO_CRH_MODE10_Msk               /*!< MODE10[1:0] bits (Port x mode bits, pin 10) */
#define GPIO_CRH_MODE10_0                    (0x1U << GPIO_CRH_MODE10_Pos)     /*!< 0x00000100 */
#define GPIO_CRH_MODE10_1                    (0x2U << GPIO_CRH_MODE10_Pos)     /*!< 0x00000200 */

#define GPIO_CRH_MODE11_Pos                  (12U)                             
#define GPIO_CRH_MODE11_Msk                  (0x3U << GPIO_CRH_MODE11_Pos)     /*!< 0x00003000 */
#define GPIO_CRH_MODE11                      GPIO_CRH_MODE11_Msk               /*!< MODE11[1:0] bits (Port x mode bits, pin 11) */
#define GPIO_CRH_MODE11_0                    (0x1U << GPIO_CRH_MODE11_Pos)     /*!< 0x00001000 */
#define GPIO_CRH_MODE11_1                    (0x2U << GPIO_CRH_MODE11_Pos)     /*!< 0x00002000 */

#define GPIO_CRH_MODE12_Pos                  (16U)                             
#define GPIO_CRH_MODE12_Msk                  (0x3U << GPIO_CRH_MODE12_Pos)     /*!< 0x00030000 */
#define GPIO_CRH_MODE12                      GPIO_CRH_MODE12_Msk               /*!< MODE12[1:0] bits (Port x mode bits, pin 12) */
#define GPIO_CRH_MODE12_0                    (0x1U << GPIO_CRH_MODE12_Pos)     /*!< 0x00010000 */
#define GPIO_CRH_MODE12_1                    (0x2U << GPIO_CRH_MODE12_Pos)     /*!< 0x00020000 */

#define GPIO_CRH_MODE13_Pos                  (20U)                             
#define GPIO_CRH_MODE13_Msk                  (0x3U << GPIO_CRH_MODE13_Pos)     /*!< 0x00300000 */
#define GPIO_CRH_MODE13                      GPIO_CRH_MODE13_Msk               /*!< MODE13[1:0] bits (Port x mode bits, pin 13) */
#define GPIO_CRH_MODE13_0                    (0x1U << GPIO_CRH_MODE13_Pos)     /*!< 0x00100000 */
#define GPIO_CRH_MODE13_1                    (0x2U << GPIO_CRH_MODE13_Pos)     /*!< 0x00200000 */

#define GPIO_CRH_MODE14_Pos                  (24U)                             
#define GPIO_CRH_MODE14_Msk                  (0x3U << GPIO_CRH_MODE14_Pos)     /*!< 0x03000000 */
#define GPIO_CRH_MODE14                      GPIO_CRH_MODE14_Msk               /*!< MODE14[1:0] bits (Port x mode bits, pin 14) */
#define GPIO_CRH_MODE14_0                    (0x1U << GPIO_CRH_MODE14_Pos)     /*!< 0x01000000 */
#define GPIO_CRH_MODE14_1                    (0x2U << GPIO_CRH_MODE14_Pos)     /*!< 0x02000000 */

#define GPIO_CRH_MODE15_Pos                  (28U)                             
#define GPIO_CRH_MODE15_Msk                  (0x3U << GPIO_CRH_MODE15_Pos)     /*!< 0x30000000 */
#define GPIO_CRH_MODE15                      GPIO_CRH_MODE15_Msk               /*!< MODE15[1:0] bits (Port x mode bits, pin 15) */
#define GPIO_CRH_MODE15_0                    (0x1U << GPIO_CRH_MODE15_Pos)     /*!< 0x10000000 */
#define GPIO_CRH_MODE15_1                    (0x2U << GPIO_CRH_MODE15_Pos)     /*!< 0x20000000 */

#define GPIO_CRH_CNF_Pos                     (2U)                              
#define GPIO_CRH_CNF_Msk                     (0x33333333U << GPIO_CRH_CNF_Pos) /*!< 0xCCCCCCCC */
#define GPIO_CRH_CNF                         GPIO_CRH_CNF_Msk                  /*!< Port x configuration bits */

#define GPIO_CRH_CNF8_Pos                    (2U)                              
#define GPIO_CRH_CNF8_Msk                    (0x3U << GPIO_CRH_CNF8_Pos)       /*!< 0x0000000C */
#define GPIO_CRH_CNF8                        GPIO_CRH_CNF8_Msk                 /*!< CNF8[1:0] bits (Port x configuration bits, pin 8) */
#define GPIO_CRH_CNF8_0                      (0x1U << GPIO_CRH_CNF8_Pos)       /*!< 0x00000004 */
#define GPIO_CRH_CNF8_1                      (0x2U << GPIO_CRH_CNF8_Pos)       /*!< 0x00000008 */

#define GPIO_CRH_CNF9_Pos                    (6U)                              
#define GPIO_CRH_CNF9_Msk                    (0x3U << GPIO_CRH_CNF9_Pos)       /*!< 0x000000C0 */
#define GPIO_CRH_CNF9                        GPIO_CRH_CNF9_Msk                 /*!< CNF9[1:0] bits (Port x configuration bits, pin 9) */
#define GPIO_CRH_CNF9_0                      (0x1U << GPIO_CRH_CNF9_Pos)       /*!< 0x00000040 */
#define GPIO_CRH_CNF9_1                      (0x2U << GPIO_CRH_CNF9_Pos)       /*!< 0x00000080 */

#define GPIO_CRH_CNF10_Pos                   (10U)                             
#define GPIO_CRH_CNF10_Msk                   (0x3U << GPIO_CRH_CNF10_Pos)      /*!< 0x00000C00 */
#define GPIO_CRH_CNF10                       GPIO_CRH_CNF10_Msk                /*!< CNF10[1:0] bits (Port x configuration bits, pin 10) */
#define GPIO_CRH_CNF10_0                     (0x1U << GPIO_CRH_CNF10_Pos)      /*!< 0x00000400 */
#define GPIO_CRH_CNF10_1                     (0x2U << GPIO_CRH_CNF10_Pos)      /*!< 0x00000800 */

#define GPIO_CRH_CNF11_Pos                   (14U)                             
#define GPIO_CRH_CNF11_Msk                   (0x3U << GPIO_CRH_CNF11_Pos)      /*!< 0x0000C000 */
#define GPIO_CRH_CNF11                       GPIO_CRH_CNF11_Msk                /*!< CNF11[1:0] bits (Port x configuration bits, pin 11) */
#define GPIO_CRH_CNF11_0                     (0x1U << GPIO_CRH_CNF11_Pos)      /*!< 0x00004000 */
#define GPIO_CRH_CNF11_1                     (0x2U << GPIO_CRH_CNF11_Pos)      /*!< 0x00008000 */

#define GPIO_CRH_CNF12_Pos                   (18U)                             
#define GPIO_CRH_CNF12_Msk                   (0x3U << GPIO_CRH_CNF12_Pos)      /*!< 0x000C0000 */
#define GPIO_CRH_CNF12                       GPIO_CRH_CNF12_Msk                /*!< CNF12[1:0] bits (Port x configuration bits, pin 12) */
#define GPIO_CRH_CNF12_0                     (0x1U << GPIO_CRH_CNF12_Pos)      /*!< 0x00040000 */
#define GPIO_CRH_CNF12_1                     (0x2U << GPIO_CRH_CNF12_Pos)      /*!< 0x00080000 */

#define GPIO_CRH_CNF13_Pos                   (22U)                             
#define GPIO_CRH_CNF13_Msk                   (0x3U << GPIO_CRH_CNF13_Pos)      /*!< 0x00C00000 */
#define GPIO_CRH_CNF13                       GPIO_CRH_CNF13_Msk                /*!< CNF13[1:0] bits (Port x configuration bits, pin 13) */
#define GPIO_CRH_CNF13_0                     (0x1U << GPIO_CRH_CNF13_Pos)      /*!< 0x00400000 */
#define GPIO_CRH_CNF13_1                     (0x2U << GPIO_CRH_CNF13_Pos)      /*!< 0x00800000 */

#define GPIO_CRH_CNF14_Pos                   (26U)                             
#define GPIO_CRH_CNF14_Msk                   (0x3U << GPIO_CRH_CNF14_Pos)      /*!< 0x0C000000 */
#define GPIO_CRH_CNF14                       GPIO_CRH_CNF14_Msk                /*!< CNF14[1:0] bits (Port x configuration bits, pin 14) */
#define GPIO_CRH_CNF14_0                     (0x1U << GPIO_CRH_CNF14_Pos)      /*!< 0x04000000 */
#define GPIO_CRH_CNF14_1                     (0x2U << GPIO_CRH_CNF14_Pos)      /*!< 0x08000000 */

#define GPIO_CRH_CNF15_Pos                   (30U)                             
#define GPIO_CRH_CNF15_Msk                   (0x3U << GPIO_CRH_CNF15_Pos)      /*!< 0xC0000000 */
#define GPIO_CRH_CNF15                       GPIO_CRH_CNF15_Msk                /*!< CNF15[1:0] bits (Port x configuration bits, pin 15) */
#define GPIO_CRH_CNF15_0                     (0x1U << GPIO_CRH_CNF15_Pos)      /*!< 0x40000000 */
#define GPIO_CRH_CNF15_1                     (0x2U << GPIO_CRH_CNF15_Pos)      /*!< 0x80000000 */

/*!<******************  Bit definition for GPIO_IDR register  *******************/
#define GPIO_IDR_IDR0_Pos                    (0U)                              
#define GPIO_IDR_IDR0_Msk                    (0x1U << GPIO_IDR_IDR0_Pos)       /*!< 0x00000001 */
#define GPIO_IDR_IDR0                        GPIO_IDR_IDR0_Msk                 /*!< Port input data, bit 0 */
#define GPIO_IDR_IDR1_Pos                    (1U)                              
#define GPIO_IDR_IDR1_Msk                    (0x1U << GPIO_IDR_IDR1_Pos)       /*!< 0x00000002 */
#define GPIO_IDR_IDR1                        GPIO_IDR_IDR1_Msk                 /*!< Port input data, bit 1 */
#define GPIO_IDR_IDR2_Pos                    (2U)                              
#define GPIO_IDR_IDR2_Msk                    (0x1U << GPIO_IDR_IDR2_Pos)       /*!< 0x00000004 */
#define GPIO_IDR_IDR2                        GPIO_IDR_IDR2_Msk                 /*!< Port input data, bit 2 */
#define GPIO_IDR_IDR3_Pos                    (3U)                              
#define GPIO_IDR_IDR3_Msk                    (0x1U << GPIO_IDR_IDR3_Pos)       /*!< 0x00000008 */
#define GPIO_IDR_IDR3                        GPIO_IDR_IDR3_Msk                 /*!< Port input data, bit 3 */
#define GPIO_IDR_IDR4_Pos                    (4U)                              
#define GPIO_IDR_IDR4_Msk                    (0x1U << GPIO_IDR_IDR4_Pos)       /*!< 0x00000010 */
#define GPIO_IDR_IDR4                        GPIO_IDR_IDR4_Msk                 /*!< Port input data, bit 4 */
#define GPIO_IDR_IDR5_Pos                    (5U)                              
#define GPIO_IDR_IDR5_Msk                    (0x1U << GPIO_IDR_IDR5_Pos)       /*!< 0x00000020 */
#define GPIO_IDR_IDR5                        GPIO_IDR_IDR5_Msk                 /*!< Port input data, bit 5 */
#define GPIO_IDR_IDR6_Pos                    (6U)                              
#define GPIO_IDR_IDR6_Msk                    (0x1U << GPIO_IDR_IDR6_Pos)       /*!< 0x00000040 */
#define GPIO_IDR_IDR6                        GPIO_IDR_IDR6_Msk                 /*!< Port input data, bit 6 */
#define GPIO_IDR_IDR7_Pos                    (7U)                              
#define GPIO_IDR_IDR7_Msk                    (0x1U << GPIO_IDR_IDR7_Pos)       /*!< 0x00000080 */
#define GPIO_IDR_IDR7                        GPIO_IDR_IDR7_Msk                 /*!< Port input data, bit 7 */
#define GPIO_IDR_IDR8_Pos                    (8U)                              
#define GPIO_IDR_IDR8_Msk                    (0x1U << GPIO_IDR_IDR8_Pos)       /*!< 0x00000100 */
#define GPIO_IDR_IDR8                        GPIO_IDR_IDR8_Msk                 /*!< Port input data, bit 8 */
#define GPIO_IDR_IDR9_Pos                    (9U)                              
#define GPIO_IDR_IDR9_Msk                    (0x1U << GPIO_IDR_IDR9_Pos)       /*!< 0x00000200 */
#define GPIO_IDR_IDR9                        GPIO_IDR_IDR9_Msk                 /*!< Port input data, bit 9 */
#define GPIO_IDR_IDR10_Pos                   (10U)                             
#define GPIO_IDR_IDR10_Msk                   (0x1U << GPIO_IDR_IDR10_Pos)      /*!< 0x00000400 */
#define GPIO_IDR_IDR10                       GPIO_IDR_IDR10_Msk                /*!< Port input data, bit 10 */
#define GPIO_IDR_IDR11_Pos                   (11U)                             
#define GPIO_IDR_IDR11_Msk                   (0x1U << GPIO_IDR_IDR11_Pos)      /*!< 0x00000800 */
#define GPIO_IDR_IDR11                       GPIO_IDR_IDR11_Msk                /*!< Port input data, bit 11 */
#define GPIO_IDR_IDR12_Pos                   (12U)                             
#define GPIO_IDR_IDR12_Msk                   (0x1U << GPIO_IDR_IDR12_Pos)      /*!< 0x00001000 */
#define GPIO_IDR_IDR12                       GPIO_IDR_IDR12_Msk                /*!< Port input data, bit 12 */
#define GPIO_IDR_IDR13_Pos                   (13U)                             
#define GPIO_IDR_IDR13_Msk                   (0x1U << GPIO_IDR_IDR13_Pos)      /*!< 0x00002000 */
#define GPIO_IDR_IDR13                       GPIO_IDR_IDR13_Msk                /*!< Port input data, bit 13 */
#define GPIO_IDR_IDR14_Pos                   (14U)                             
#define GPIO_IDR_IDR14_Msk                   (0x1U << GPIO_IDR_IDR14_Pos)      /*!< 0x00004000 */
#define GPIO_IDR_IDR14                       GPIO_IDR_IDR14_Msk                /*!< Port input data, bit 14 */
#define GPIO_IDR_IDR15_Pos                   (15U)                             
#define GPIO_IDR_IDR15_Msk                   (0x1U << GPIO_IDR_IDR15_Pos)      /*!< 0x00008000 */
#define GPIO_IDR_IDR15                       GPIO_IDR_IDR15_Msk                /*!< Port input data, bit 15 */

/*******************  Bit definition for GPIO_ODR register  *******************/
#define GPIO_ODR_ODR0_Pos                    (0U)                              
#define GPIO_ODR_ODR0_Msk                    (0x1U << GPIO_ODR_ODR0_Pos)       /*!< 0x00000001 */
#define GPIO_ODR_ODR0                        GPIO_ODR_ODR0_Msk                 /*!< Port output data, bit 0 */
#define GPIO_ODR_ODR1_Pos                    (1U)                              
#define GPIO_ODR_ODR1_Msk                    (0x1U << GPIO_ODR_ODR1_Pos)       /*!< 0x00000002 */
#define GPIO_ODR_ODR1                        GPIO_ODR_ODR1_Msk                 /*!< Port output data, bit 1 */
#define GPIO_ODR_ODR2_Pos                    (2U)                              
#define GPIO_ODR_ODR2_Msk                    (0x1U << GPIO_ODR_ODR2_Pos)       /*!< 0x00000004 */
#define GPIO_ODR_ODR2                        GPIO_ODR_ODR2_Msk                 /*!< Port output data, bit 2 */
#define GPIO_ODR_ODR3_Pos                    (3U)                              
#define GPIO_ODR_ODR3_Msk                    (0x1U << GPIO_ODR_ODR3_Pos)       /*!< 0x00000008 */
#define GPIO_ODR_ODR3                        GPIO_ODR_ODR3_Msk                 /*!< Port output data, bit 3 */
#define GPIO_ODR_ODR4_Pos                    (4U)                              
#define GPIO_ODR_ODR4_Msk                    (0x1U << GPIO_ODR_ODR4_Pos)       /*!< 0x00000010 */
#define GPIO_ODR_ODR4                        GPIO_ODR_ODR4_Msk                 /*!< Port output data, bit 4 */
#define GPIO_ODR_ODR5_Pos                    (5U)                              
#define GPIO_ODR_ODR5_Msk                    (0x1U << GPIO_ODR_ODR5_Pos)       /*!< 0x00000020 */
#define GPIO_ODR_ODR5                        GPIO_ODR_ODR5_Msk                 /*!< Port output data, bit 5 */
#define GPIO_ODR_ODR6_Pos                    (6U)                              
#define GPIO_ODR_ODR6_Msk                    (0x1U << GPIO_ODR_ODR6_Pos)       /*!< 0x00000040 */
#define GPIO_ODR_ODR6                        GPIO_ODR_ODR6_Msk                 /*!< Port output data, bit 6 */
#define GPIO_ODR_ODR7_Pos                    (7U)                              
#define GPIO_ODR_ODR7_Msk                    (0x1U << GPIO_ODR_ODR7_Pos)       /*!< 0x00000080 */
#define GPIO_ODR_ODR7                        GPIO_ODR_ODR7_Msk                 /*!< Port output data, bit 7 */
#define GPIO_ODR_ODR8_Pos                    (8U)                              
#define GPIO_ODR_ODR8_Msk                    (0x1U << GPIO_ODR_ODR8_Pos)       /*!< 0x00000100 */
#define GPIO_ODR_ODR8                        GPIO_ODR_ODR8_Msk                 /*!< Port output data, bit 8 */
#define GPIO_ODR_ODR9_Pos                    (9U)                              
#define GPIO_ODR_ODR9_Msk                    (0x1U << GPIO_ODR_ODR9_Pos)       /*!< 0x00000200 */
#define GPIO_ODR_ODR9                        GPIO_ODR_ODR9_Msk                 /*!< Port output data, bit 9 */
#define GPIO_ODR_ODR10_Pos                   (10U)                             
#define GPIO_ODR_ODR10_Msk                   (0x1U << GPIO_ODR_ODR10_Pos)      /*!< 0x00000400 */
#define GPIO_ODR_ODR10                       GPIO_ODR_ODR10_Msk                /*!< Port output data, bit 10 */
#define GPIO_ODR_ODR11_Pos                   (11U)                             
#define GPIO_ODR_ODR11_Msk                   (0x1U << GPIO_ODR_ODR11_Pos)      /*!< 0x00000800 */
#define GPIO_ODR_ODR11                       GPIO_ODR_ODR11_Msk                /*!< Port output data, bit 11 */
#define GPIO_ODR_ODR12_Pos                   (12U)                             
#define GPIO_ODR_ODR12_Msk                   (0x1U << GPIO_ODR_ODR12_Pos)      /*!< 0x00001000 */
#define GPIO_ODR_ODR12                       GPIO_ODR_ODR12_Msk                /*!< Port output data, bit 12 */
#define GPIO_ODR_ODR13_Pos                   (13U)                             
#define GPIO_ODR_ODR13_Msk                   (0x1U << GPIO_ODR_ODR13_Pos)      /*!< 0x00002000 */
#define GPIO_ODR_ODR13                       GPIO_ODR_ODR13_Msk                /*!< Port output data, bit 13 */
#define GPIO_ODR_ODR14_Pos                   (14U)                             
#define GPIO_ODR_ODR14_Msk                   (0x1U << GPIO_ODR_ODR14_Pos)      /*!< 0x00004000 */
#define GPIO_ODR_ODR14                       GPIO_ODR_ODR14_Msk                /*!< Port output data, bit 14 */
#define GPIO_ODR_ODR15_Pos                   (15U)                             
#define GPIO_ODR_ODR15_Msk                   (0x1U << GPIO_ODR_ODR15_Pos)      /*!< 0x00008000 */
#define GPIO_ODR_ODR15                       GPIO_ODR_ODR15_Msk                /*!< Port output data, bit 15 */

/******************  Bit definition for GPIO_BSRR register  *******************/
#define GPIO_BSRR_BS0_Pos                    (0U)                              
#define GPIO_BSRR_BS0_Msk                    (0x1U << GPIO_BSRR_BS0_Pos)       /*!< 0x00000001 */
#define GPIO_BSRR_BS0                        GPIO_BSRR_BS0_Msk                 /*!< Port x Set bit 0 */
#define GPIO_BSRR_BS1_Pos                    (1U)                              
#define GPIO_BSRR_BS1_Msk                    (0x1U << GPIO_BSRR_BS1_Pos)       /*!< 0x00000002 */
#define GPIO_BSRR_BS1                        GPIO_BSRR_BS1_Msk                 /*!< Port x Set bit 1 */
#define GPIO_BSRR_BS2_Pos                    (2U)                              
#define GPIO_BSRR_BS2_Msk                    (0x1U << GPIO_BSRR_BS2_Pos)       /*!< 0x00000004 */
#define GPIO_BSRR_BS2                        GPIO_BSRR_BS2_Msk                 /*!< Port x Set bit 2 */
#define GPIO_BSRR_BS3_Pos                    (3U)                              
#define GPIO_BSRR_BS3_Msk                    (0x1U << GPIO_BSRR_BS3_Pos)       /*!< 0x00000008 */
#define GPIO_BSRR_BS3                        GPIO_BSRR_BS3_Msk                 /*!< Port x Set bit 3 */
#define GPIO_BSRR_BS4_Pos                    (4U)                              
#define GPIO_BSRR_BS4_Msk                    (0x1U << GPIO_BSRR_BS4_Pos)       /*!< 0x00000010 */
#define GPIO_BSRR_BS4                        GPIO_BSRR_BS4_Msk                 /*!< Port x Set bit 4 */
#define GPIO_BSRR_BS5_Pos                    (5U)                              
#define GPIO_BSRR_BS5_Msk                    (0x1U << GPIO_BSRR_BS5_Pos)       /*!< 0x00000020 */
#define GPIO_BSRR_BS5                        GPIO_BSRR_BS5_Msk                 /*!< Port x Set bit 5 */
#define GPIO_BSRR_BS6_Pos                    (6U)                              
#define GPIO_BSRR_BS6_Msk                    (0x1U << GPIO_BSRR_BS6_Pos)       /*!< 0x00000040 */
#define GPIO_BSRR_BS6                        GPIO_BSRR_BS6_Msk                 /*!< Port x Set bit 6 */
#define GPIO_BSRR_BS7_Pos                    (7U)                              
#define GPIO_BSRR_BS7_Msk                    (0x1U << GPIO_BSRR_BS7_Pos)       /*!< 0x00000080 */
#define GPIO_BSRR_BS7                        GPIO_BSRR_BS7_Msk                 /*!< Port x Set bit 7 */
#define GPIO_BSRR_BS8_Pos                    (8U)                              
#define GPIO_BSRR_BS8_Msk                    (0x1U << GPIO_BSRR_BS8_Pos)       /*!< 0x00000100 */
#define GPIO_BSRR_BS8                        GPIO_BSRR_BS8_Msk                 /*!< Port x Set bit 8 */
#define GPIO_BSRR_BS9_Pos                    (9U)                              
#define GPIO_BSRR_BS9_Msk                    (0x1U << GPIO_BSRR_BS9_Pos)       /*!< 0x00000200 */
#define GPIO_BSRR_BS9                        GPIO_BSRR_BS9_Msk                 /*!< Port x Set bit 9 */
#define GPIO_BSRR_BS10_Pos                   (10U)                             
#define GPIO_BSRR_BS10_Msk                   (0x1U << GPIO_BSRR_BS10_Pos)      /*!< 0x00000400 */
#define GPIO_BSRR_BS10                       GPIO_BSRR_BS10_Msk                /*!< Port x Set bit 10 */
#define GPIO_BSRR_BS11_Pos                   (11U)                             
#define GPIO_BSRR_BS11_Msk                   (0x1U << GPIO_BSRR_BS11_Pos)      /*!< 0x00000800 */
#define GPIO_BSRR_BS11                       GPIO_BSRR_BS11_Msk                /*!< Port x Set bit 11 */
#define GPIO_BSRR_BS12_Pos                   (12U)                             
#define GPIO_BSRR_BS12_Msk                   (0x1U << GPIO_BSRR_BS12_Pos)      /*!< 0x00001000 */
#define GPIO_BSRR_BS12                       GPIO_BSRR_BS12_Msk                /*!< Port x Set bit 12 */
#define GPIO_BSRR_BS13_Pos                   (13U)                             
#define GPIO_BSRR_BS13_Msk                   (0x1U << GPIO_BSRR_BS13_Pos)      /*!< 0x00002000 */
#define GPIO_BSRR_BS13                       GPIO_BSRR_BS13_Msk                /*!< Port x Set bit 13 */
#define GPIO_BSRR_BS14_Pos                   (14U)                             
#define GPIO_BSRR_BS14_Msk                   (0x1U << GPIO_BSRR_BS14_Pos)      /*!< 0x00004000 */
#define GPIO_BSRR_BS14                       GPIO_BSRR_BS14_Msk                /*!< Port x Set bit 14 */
#define GPIO_BSRR_BS15_Pos                   (15U)                             
#define GPIO_BSRR_BS15_Msk                   (0x1U << GPIO_BSRR_BS15_Pos)      /*!< 0x00008000 */
#define GPIO_BSRR_BS15                       GPIO_BSRR_BS15_Msk                /*!< Port x Set bit 15 */

#define GPIO_BSRR_BR0_Pos                    (16U)                             
#define GPIO_BSRR_BR0_Msk                    (0x1U << GPIO_BSRR_BR0_Pos)       /*!< 0x00010000 */
#define GPIO_BSRR_BR0                        GPIO_BSRR_BR0_Msk                 /*!< Port x Reset bit 0 */
#define GPIO_BSRR_BR1_Pos                    (17U)                             
#define GPIO_BSRR_BR1_Msk                    (0x1U << GPIO_BSRR_BR1_Pos)       /*!< 0x00020000 */
#define GPIO_BSRR_BR1                        GPIO_BSRR_BR1_Msk                 /*!< Port x Reset bit 1 */
#define GPIO_BSRR_BR2_Pos                    (18U)                             
#define GPIO_BSRR_BR2_Msk                    (0x1U << GPIO_BSRR_BR2_Pos)       /*!< 0x00040000 */
#define GPIO_BSRR_BR2                        GPIO_BSRR_BR2_Msk                 /*!< Port x Reset bit 2 */
#define GPIO_BSRR_BR3_Pos                    (19U)                             
#define GPIO_BSRR_BR3_Msk                    (0x1U << GPIO_BSRR_BR3_Pos)       /*!< 0x00080000 */
#define GPIO_BSRR_BR3                        GPIO_BSRR_BR3_Msk                 /*!< Port x Reset bit 3 */
#define GPIO_BSRR_BR4_Pos                    (20U)                             
#define GPIO_BSRR_BR4_Msk                    (0x1U << GPIO_BSRR_BR4_Pos)       /*!< 0x00100000 */
#define GPIO_BSRR_BR4                        GPIO_BSRR_BR4_Msk                 /*!< Port x Reset bit 4 */
#define GPIO_BSRR_BR5_Pos                    (21U)                             
#define GPIO_BSRR_BR5_Msk                    (0x1U << GPIO_BSRR_BR5_Pos)       /*!< 0x00200000 */
#define GPIO_BSRR_BR5                        GPIO_BSRR_BR5_Msk                 /*!< Port x Reset bit 5 */
#define GPIO_BSRR_BR6_Pos                    (22U)                             
#define GPIO_BSRR_BR6_Msk                    (0x1U << GPIO_BSRR_BR6_Pos)       /*!< 0x00400000 */
#define GPIO_BSRR_BR6                        GPIO_BSRR_BR6_Msk                 /*!< Port x Reset bit 6 */
#define GPIO_BSRR_BR7_Pos                    (23U)                             
#define GPIO_BSRR_BR7_Msk                    (0x1U << GPIO_BSRR_BR7_Pos)       /*!< 0x00800000 */
#define GPIO_BSRR_BR7                        GPIO_BSRR_BR7_Msk                 /*!< Port x Reset bit 7 */
#define GPIO_BSRR_BR8_Pos                    (24U)                             
#define GPIO_BSRR_BR8_Msk                    (0x1U << GPIO_BSRR_BR8_Pos)       /*!< 0x01000000 */
#define GPIO_BSRR_BR8                        GPIO_BSRR_BR8_Msk                 /*!< Port x Reset bit 8 */
#define GPIO_BSRR_BR9_Pos                    (25U)                             
#define GPIO_BSRR_BR9_Msk                    (0x1U << GPIO_BSRR_BR9_Pos)       /*!< 0x02000000 */
#define GPIO_BSRR_BR9                        GPIO_BSRR_BR9_Msk                 /*!< Port x Reset bit 9 */
#define GPIO_BSRR_BR10_Pos                   (26U)                             
#define GPIO_BSRR_BR10_Msk                   (0x1U << GPIO_BSRR_BR10_Pos)      /*!< 0x04000000 */
#define GPIO_BSRR_BR10                       GPIO_BSRR_BR10_Msk                /*!< Port x Reset bit 10 */
#define GPIO_BSRR_BR11_Pos                   (27U)                             
#define GPIO_BSRR_BR11_Msk                   (0x1U << GPIO_BSRR_BR11_Pos)      /*!< 0x08000000 */
#define GPIO_BSRR_BR11                       GPIO_BSRR_BR11_Msk                /*!< Port x Reset bit 11 */
#define GPIO_BSRR_BR12_Pos                   (28U)                             
#define GPIO_BSRR_BR12_Msk                   (0x1U << GPIO_BSRR_BR12_Pos)      /*!< 0x10000000 */
#define GPIO_BSRR_BR12                       GPIO_BSRR_BR12_Msk                /*!< Port x Reset bit 12 */
#define GPIO_BSRR_BR13_Pos                   (29U)                             
#define GPIO_BSRR_BR13_Msk                   (0x1U << GPIO_BSRR_BR13_Pos)      /*!< 0x20000000 */
#define GPIO_BSRR_BR13                       GPIO_BSRR_BR13_Msk                /*!< Port x Reset bit 13 */
#define GPIO_BSRR_BR14_Pos                   (30U)                             
#define GPIO_BSRR_BR14_Msk                   (0x1U << GPIO_BSRR_BR14_Pos)      /*!< 0x40000000 */
#define GPIO_BSRR_BR14                       GPIO_BSRR_BR14_Msk                /*!< Port x Reset bit 14 */
#define GPIO_BSRR_BR15_Pos                   (31U)                             
#define GPIO_BSRR_BR15_Msk                   (0x1U << GPIO_BSRR_BR15_Pos)      /*!< 0x80000000 */
#define GPIO_BSRR_BR15                       GPIO_BSRR_BR15_Msk                /*!< Port x Reset bit 15 */

/*******************  Bit definition for GPIO_BRR register  *******************/
#define GPIO_BRR_BR0_Pos                     (0U)                              
#define GPIO_BRR_BR0_Msk                     (0x1U << GPIO_BRR_BR0_Pos)        /*!< 0x00000001 */
#define GPIO_BRR_BR0                         GPIO_BRR_BR0_Msk                  /*!< Port x Reset bit 0 */
#define GPIO_BRR_BR1_Pos                     (1U)                              
#define GPIO_BRR_BR1_Msk                     (0x1U << GPIO_BRR_BR1_Pos)        /*!< 0x00000002 */
#define GPIO_BRR_BR1                         GPIO_BRR_BR1_Msk                  /*!< Port x Reset bit 1 */
#define GPIO_BRR_BR2_Pos                     (2U)                              
#define GPIO_BRR_BR2_Msk                     (0x1U << GPIO_BRR_BR2_Pos)        /*!< 0x00000004 */
#define GPIO_BRR_BR2                         GPIO_BRR_BR2_Msk                  /*!< Port x Reset bit 2 */
#define GPIO_BRR_BR3_Pos                     (3U)                              
#define GPIO_BRR_BR3_Msk                     (0x1U << GPIO_BRR_BR3_Pos)        /*!< 0x00000008 */
#define GPIO_BRR_BR3                         GPIO_BRR_BR3_Msk                  /*!< Port x Reset bit 3 */
#define GPIO_BRR_BR4_Pos                     (4U)                              
#define GPIO_BRR_BR4_Msk                     (0x1U << GPIO_BRR_BR4_Pos)        /*!< 0x00000010 */
#define GPIO_BRR_BR4                         GPIO_BRR_BR4_Msk                  /*!< Port x Reset bit 4 */
#define GPIO_BRR_BR5_Pos                     (5U)                              
#define GPIO_BRR_BR5_Msk                     (0x1U << GPIO_BRR_BR5_Pos)        /*!< 0x00000020 */
#define GPIO_BRR_BR5                         GPIO_BRR_BR5_Msk                  /*!< Port x Reset bit 5 */
#define GPIO_BRR_BR6_Pos                     (6U)                              
#define GPIO_BRR_BR6_Msk                     (0x1U << GPIO_BRR_BR6_Pos)        /*!< 0x00000040 */
#define GPIO_BRR_BR6                         GPIO_BRR_BR6_Msk                  /*!< Port x Reset bit 6 */
#define GPIO_BRR_BR7_Pos                     (7U)                              
#define GPIO_BRR_BR7_Msk                     (0x1U << GPIO_BRR_BR7_Pos)        /*!< 0x00000080 */
#define GPIO_BRR_BR7                         GPIO_BRR_BR7_Msk                  /*!< Port x Reset bit 7 */
#define GPIO_BRR_BR8_Pos                     (8U)                              
#define GPIO_BRR_BR8_Msk                     (0x1U << GPIO_BRR_BR8_Pos)        /*!< 0x00000100 */
#define GPIO_BRR_BR8                         GPIO_BRR_BR8_Msk                  /*!< Port x Reset bit 8 */
#define GPIO_BRR_BR9_Pos                     (9U)                              
#define GPIO_BRR_BR9_Msk                     (0x1U << GPIO_BRR_BR9_Pos)        /*!< 0x00000200 */
#define GPIO_BRR_BR9                         GPIO_BRR_BR9_Msk                  /*!< Port x Reset bit 9 */
#define GPIO_BRR_BR10_Pos                    (10U)                             
#define GPIO_BRR_BR10_Msk                    (0x1U << GPIO_BRR_BR10_Pos)       /*!< 0x00000400 */
#define GPIO_BRR_BR10                        GPIO_BRR_BR10_Msk                 /*!< Port x Reset bit 10 */
#define GPIO_BRR_BR11_Pos                    (11U)                             
#define GPIO_BRR_BR11_Msk                    (0x1U << GPIO_BRR_BR11_Pos)       /*!< 0x00000800 */
#define GPIO_BRR_BR11                        GPIO_BRR_BR11_Msk                 /*!< Port x Reset bit 11 */
#define GPIO_BRR_BR12_Pos                    (12U)                             
#define GPIO_BRR_BR12_Msk                    (0x1U << GPIO_BRR_BR12_Pos)       /*!< 0x00001000 */
#define GPIO_BRR_BR12                        GPIO_BRR_BR12_Msk                 /*!< Port x Reset bit 12 */
#define GPIO_BRR_BR13_Pos                    (13U)                             
#define GPIO_BRR_BR13_Msk                    (0x1U << GPIO_BRR_BR13_Pos)       /*!< 0x00002000 */
#define GPIO_BRR_BR13                        GPIO_BRR_BR13_Msk                 /*!< Port x Reset bit 13 */
#define GPIO_BRR_BR14_Pos                    (14U)                             
#define GPIO_BRR_BR14_Msk                    (0x1U << GPIO_BRR_BR14_Pos)       /*!< 0x00004000 */
#define GPIO_BRR_BR14                        GPIO_BRR_BR14_Msk                 /*!< Port x Reset bit 14 */
#define GPIO_BRR_BR15_Pos                    (15U)                             
#define GPIO_BRR_BR15_Msk                    (0x1U << GPIO_BRR_BR15_Pos)       /*!< 0x00008000 */
#define GPIO_BRR_BR15                        GPIO_BRR_BR15_Msk                 /*!< Port x Reset bit 15 */

/******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_LCKR_LCK0_Pos                   (0U)                              
#define GPIO_LCKR_LCK0_Msk                   (0x1U << GPIO_LCKR_LCK0_Pos)      /*!< 0x00000001 */
#define GPIO_LCKR_LCK0                       GPIO_LCKR_LCK0_Msk                /*!< Port x Lock bit 0 */
#define GPIO_LCKR_LCK1_Pos                   (1U)                              
#define GPIO_LCKR_LCK1_Msk                   (0x1U << GPIO_LCKR_LCK1_Pos)      /*!< 0x00000002 */
#define GPIO_LCKR_LCK1                       GPIO_LCKR_LCK1_Msk                /*!< Port x Lock bit 1 */
#define GPIO_LCKR_LCK2_Pos                   (2U)                              
#define GPIO_LCKR_LCK2_Msk                   (0x1U << GPIO_LCKR_LCK2_Pos)      /*!< 0x00000004 */
#define GPIO_LCKR_LCK2                       GPIO_LCKR_LCK2_Msk                /*!< Port x Lock bit 2 */
#define GPIO_LCKR_LCK3_Pos                   (3U)                              
#define GPIO_LCKR_LCK3_Msk                   (0x1U << GPIO_LCKR_LCK3_Pos)      /*!< 0x00000008 */
#define GPIO_LCKR_LCK3                       GPIO_LCKR_LCK3_Msk                /*!< Port x Lock bit 3 */
#define GPIO_LCKR_LCK4_Pos                   (4U)                              
#define GPIO_LCKR_LCK4_Msk                   (0x1U << GPIO_LCKR_LCK4_Pos)      /*!< 0x00000010 */
#define GPIO_LCKR_LCK4                       GPIO_LCKR_LCK4_Msk                /*!< Port x Lock bit 4 */
#define GPIO_LCKR_LCK5_Pos                   (5U)                              
#define GPIO_LCKR_LCK5_Msk                   (0x1U << GPIO_LCKR_LCK5_Pos)      /*!< 0x00000020 */
#define GPIO_LCKR_LCK5                       GPIO_LCKR_LCK5_Msk                /*!< Port x Lock bit 5 */
#define GPIO_LCKR_LCK6_Pos                   (6U)                              
#define GPIO_LCKR_LCK6_Msk                   (0x1U << GPIO_LCKR_LCK6_Pos)      /*!< 0x00000040 */
#define GPIO_LCKR_LCK6                       GPIO_LCKR_LCK6_Msk                /*!< Port x Lock bit 6 */
#define GPIO_LCKR_LCK7_Pos                   (7U)                              
#define GPIO_LCKR_LCK7_Msk                   (0x1U << GPIO_LCKR_LCK7_Pos)      /*!< 0x00000080 */
#define GPIO_LCKR_LCK7                       GPIO_LCKR_LCK7_Msk                /*!< Port x Lock bit 7 */
#define GPIO_LCKR_LCK8_Pos                   (8U)                              
#define GPIO_LCKR_LCK8_Msk                   (0x1U << GPIO_LCKR_LCK8_Pos)      /*!< 0x00000100 */
#define GPIO_LCKR_LCK8                       GPIO_LCKR_LCK8_Msk                /*!< Port x Lock bit 8 */
#define GPIO_LCKR_LCK9_Pos                   (9U)                              
#define GPIO_LCKR_LCK9_Msk                   (0x1U << GPIO_LCKR_LCK9_Pos)      /*!< 0x00000200 */
#define GPIO_LCKR_LCK9                       GPIO_LCKR_LCK9_Msk                /*!< Port x Lock bit 9 */
#define GPIO_LCKR_LCK10_Pos                  (10U)                             
#define GPIO_LCKR_LCK10_Msk                  (0x1U << GPIO_LCKR_LCK10_Pos)     /*!< 0x00000400 */
#define GPIO_LCKR_LCK10                      GPIO_LCKR_LCK10_Msk               /*!< Port x Lock bit 10 */
#define GPIO_LCKR_LCK11_Pos                  (11U)                             
#define GPIO_LCKR_LCK11_Msk                  (0x1U << GPIO_LCKR_LCK11_Pos)     /*!< 0x00000800 */
#define GPIO_LCKR_LCK11                      GPIO_LCKR_LCK11_Msk               /*!< Port x Lock bit 11 */
#define GPIO_LCKR_LCK12_Pos                  (12U)                             
#define GPIO_LCKR_LCK12_Msk                  (0x1U << GPIO_LCKR_LCK12_Pos)     /*!< 0x00001000 */
#define GPIO_LCKR_LCK12                      GPIO_LCKR_LCK12_Msk               /*!< Port x Lock bit 12 */
#define GPIO_LCKR_LCK13_Pos                  (13U)                             
#define GPIO_LCKR_LCK13_Msk                  (0x1U << GPIO_LCKR_LCK13_Pos)     /*!< 0x00002000 */
#define GPIO_LCKR_LCK13                      GPIO_LCKR_LCK13_Msk               /*!< Port x Lock bit 13 */
#define GPIO_LCKR_LCK14_Pos                  (14U)                             
#define GPIO_LCKR_LCK14_Msk                  (0x1U << GPIO_LCKR_LCK14_Pos)     /*!< 0x00004000 */
#define GPIO_LCKR_LCK14                      GPIO_LCKR_LCK14_Msk               /*!< Port x Lock bit 14 */
#define GPIO_LCKR_LCK15_Pos                  (15U)                             
#define GPIO_LCKR_LCK15_Msk                  (0x1U << GPIO_LCKR_LCK15_Pos)     /*!< 0x00008000 */
#define GPIO_LCKR_LCK15                      GPIO_LCKR_LCK15_Msk               /*!< Port x Lock bit 15 */
#define GPIO_LCKR_LCKK_Pos                   (16U)                             
#define GPIO_LCKR_LCKK_Msk                   (0x1U << GPIO_LCKR_LCKK_Pos)      /*!< 0x00010000 */
#define GPIO_LCKR_LCKK                       GPIO_LCKR_LCKK_Msk                /*!< Lock key */

/*----------------------------------------------------------------------------*/


/******************  Bit definition for AFIO_MAPR2 register  ******************/


#define AFIO_MAPR2_FSMC_NADV_REMAP_Pos       (10U)                             
#define AFIO_MAPR2_FSMC_NADV_REMAP_Msk       (0x1U << AFIO_MAPR2_FSMC_NADV_REMAP_Pos) /*!< 0x00000400 */
#define AFIO_MAPR2_FSMC_NADV_REMAP           AFIO_MAPR2_FSMC_NADV_REMAP_Msk    /*!< FSMC NADV remapping */

/* Debug Exception and Monitor Control Register Definitions */
#define CoreDebug_DEMCR_TRCENA_Pos         24U                                            /*!< CoreDebug DEMCR: TRCENA Position */
#define CoreDebug_DEMCR_TRCENA_Msk         (1UL << CoreDebug_DEMCR_TRCENA_Pos)            /*!< CoreDebug DEMCR: TRCENA Mask */

#define DWT_CTRL_CYCCNTENA_Pos              0U                                         /*!< DWT CTRL: CYCCNTENA Position */
#define DWT_CTRL_CYCCNTENA_Msk             (0x1UL /*<< DWT_CTRL_CYCCNTENA_Pos*/)       /*!< DWT CTRL: CYCCNTENA Mask */

/******************************************************************************/
/*                                                                            */
/*                        Serial Peripheral Interface                         */
/*                                                                            */
/******************************************************************************/
/*
 * @brief Specific device feature definitions (not present on all devices in the STM32F1 serie)
 */
#define SPI_I2S_SUPPORT       /*!< I2S support */
/*******************  Bit definition for SPI_CR1 register  ********************/
#define SPI_CR1_CPHA_Pos                    (0U)                               
#define SPI_CR1_CPHA_Msk                    (0x1U << SPI_CR1_CPHA_Pos)         /*!< 0x00000001 */
#define SPI_N_CR1_CPHA                        SPI_CR1_CPHA_Msk                   /*!< Clock Phase */
#define SPI_CR1_CPOL_Pos                    (1U)                               
#define SPI_CR1_CPOL_Msk                    (0x1U << SPI_CR1_CPOL_Pos)         /*!< 0x00000002 */
#define SPI_N_CR1_CPOL                        SPI_CR1_CPOL_Msk                   /*!< Clock Polarity */
#define SPI_CR1_MSTR_Pos                    (2U)                               
#define SPI_CR1_MSTR_Msk                    (0x1U << SPI_CR1_MSTR_Pos)         /*!< 0x00000004 */
#define SPI_N_CR1_MSTR                        SPI_CR1_MSTR_Msk                   /*!< Master Selection */

#define SPI_CR1_BR_Pos                      (3U)                               
#define SPI_CR1_BR_Msk                      (0x7U << SPI_CR1_BR_Pos)           /*!< 0x00000038 */
#define SPI_N_CR1_BR                          SPI_CR1_BR_Msk                     /*!< BR[2:0] bits (Baud Rate Control) */
#define SPI_N_CR1_BR_0                        (0x1U << SPI_CR1_BR_Pos)           /*!< 0x00000008 */
#define SPI_N_CR1_BR_1                        (0x2U << SPI_CR1_BR_Pos)           /*!< 0x00000010 */
#define SPI_N_CR1_BR_2                        (0x4U << SPI_CR1_BR_Pos)           /*!< 0x00000020 */

#define SPI_CR1_SPE_Pos                     (6U)                               
#define SPI_CR1_SPE_Msk                     (0x1U << SPI_CR1_SPE_Pos)          /*!< 0x00000040 */
#define SPI_N_CR1_SPE                         SPI_CR1_SPE_Msk                    /*!< SPI Enable */
#define SPI_CR1_LSBFIRST_Pos                (7U)                               
#define SPI_CR1_LSBFIRST_Msk                (0x1U << SPI_CR1_LSBFIRST_Pos)     /*!< 0x00000080 */
//#define SPI_CR1_LSBFIRST                    SPI_CR1_LSBFIRST_Msk               /*!< Frame Format */
#define SPI_CR1_SSI_Pos                     (8U)                               
#define SPI_CR1_SSI_Msk                     (0x1U << SPI_CR1_SSI_Pos)          /*!< 0x00000100 */
#define SPI_N_CR1_SSI                         SPI_CR1_SSI_Msk                    /*!< Internal slave select */
#define SPI_CR1_SSM_Pos                     (9U)                               
#define SPI_CR1_SSM_Msk                     (0x1U << SPI_CR1_SSM_Pos)          /*!< 0x00000200 */
#define SPI_N_CR1_SSM                         SPI_CR1_SSM_Msk                    /*!< Software slave management */
#define SPI_CR1_RXONLY_Pos                  (10U)                              
#define SPI_CR1_RXONLY_Msk                  (0x1U << SPI_CR1_RXONLY_Pos)       /*!< 0x00000400 */
//#define SPI_CR1_RXONLY                      SPI_CR1_RXONLY_Msk                 /*!< Receive only */
#define SPI_CR1_DFF_Pos                     (11U)                              
#define SPI_CR1_DFF_Msk                     (0x1U << SPI_CR1_DFF_Pos)          /*!< 0x00000800 */
//#define SPI_CR1_DFF                         SPI_CR1_DFF_Msk                    /*!< Data Frame Format */
#define SPI_CR1_CRCNEXT_Pos                 (12U)                              
#define SPI_CR1_CRCNEXT_Msk                 (0x1U << SPI_CR1_CRCNEXT_Pos)      /*!< 0x00001000 */
//#define SPI_CR1_CRCNEXT                     SPI_CR1_CRCNEXT_Msk                /*!< Transmit CRC next */
#define SPI_CR1_CRCEN_Pos                   (13U)                              
#define SPI_CR1_CRCEN_Msk                   (0x1U << SPI_CR1_CRCEN_Pos)        /*!< 0x00002000 */
//#define SPI_CR1_CRCEN                       SPI_CR1_CRCEN_Msk                  /*!< Hardware CRC calculation enable */
#define SPI_CR1_BIDIOE_Pos                  (14U)                              
#define SPI_CR1_BIDIOE_Msk                  (0x1U << SPI_CR1_BIDIOE_Pos)       /*!< 0x00004000 */
//#define SPI_CR1_BIDIOE                      SPI_CR1_BIDIOE_Msk                 /*!< Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE_Pos                (15U)                              
#define SPI_CR1_BIDIMODE_Msk                (0x1U << SPI_CR1_BIDIMODE_Pos)     /*!< 0x00008000 */
//#define SPI_CR1_BIDIMODE                    SPI_CR1_BIDIMODE_Msk               /*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define SPI_CR2_RXDMAEN_Pos                 (0U)                               
#define SPI_CR2_RXDMAEN_Msk                 (0x1U << SPI_CR2_RXDMAEN_Pos)      /*!< 0x00000001 */
//#define SPI_CR2_RXDMAEN                     SPI_CR2_RXDMAEN_Msk                /*!< Rx Buffer DMA Enable */
#define SPI_CR2_TXDMAEN_Pos                 (1U)                               
#define SPI_CR2_TXDMAEN_Msk                 (0x1U << SPI_CR2_TXDMAEN_Pos)      /*!< 0x00000002 */
//#define SPI_CR2_TXDMAEN                     SPI_CR2_TXDMAEN_Msk                /*!< Tx Buffer DMA Enable */
#define SPI_CR2_SSOE_Pos                    (2U)                               
#define SPI_CR2_SSOE_Msk                    (0x1U << SPI_CR2_SSOE_Pos)         /*!< 0x00000004 */
//#define SPI_CR2_SSOE                        SPI_CR2_SSOE_Msk                   /*!< SS Output Enable */
#define SPI_CR2_ERRIE_Pos                   (5U)                               
#define SPI_CR2_ERRIE_Msk                   (0x1U << SPI_CR2_ERRIE_Pos)        /*!< 0x00000020 */
//#define SPI_CR2_ERRIE                       SPI_CR2_ERRIE_Msk                  /*!< Error Interrupt Enable */
#define SPI_CR2_RXNEIE_Pos                  (6U)                               
#define SPI_CR2_RXNEIE_Msk                  (0x1U << SPI_CR2_RXNEIE_Pos)       /*!< 0x00000040 */
//#define SPI_CR2_RXNEIE                      SPI_CR2_RXNEIE_Msk                 /*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE_Pos                   (7U)                               
#define SPI_CR2_TXEIE_Msk                   (0x1U << SPI_CR2_TXEIE_Pos)        /*!< 0x00000080 */
//#define SPI_CR2_TXEIE                       SPI_CR2_TXEIE_Msk                  /*!< Tx buffer Empty Interrupt Enable */

/********************  Bit definition for SPI_SR register  ********************/
#define SPI_SR_RXNE_Pos                     (0U)                               
#define SPI_SR_RXNE_Msk                     (0x1U << SPI_SR_RXNE_Pos)          /*!< 0x00000001 */
#define SPI_N_SR_RXNE                         SPI_SR_RXNE_Msk                    /*!< Receive buffer Not Empty */
#define SPI_SR_TXE_Pos                      (1U)                               
#define SPI_SR_TXE_Msk                      (0x1U << SPI_SR_TXE_Pos)           /*!< 0x00000002 */
#define SPI_N_SR_TXE                          SPI_SR_TXE_Msk                     /*!< Transmit buffer Empty */
#define SPI_SR_CHSIDE_Pos                   (2U)                               
#define SPI_SR_CHSIDE_Msk                   (0x1U << SPI_SR_CHSIDE_Pos)        /*!< 0x00000004 */
//#define SPI_SR_CHSIDE                       SPI_SR_CHSIDE_Msk                  /*!< Channel side */
#define SPI_SR_UDR_Pos                      (3U)                               
#define SPI_SR_UDR_Msk                      (0x1U << SPI_SR_UDR_Pos)           /*!< 0x00000008 */
//#define SPI_SR_UDR                          SPI_SR_UDR_Msk                     /*!< Underrun flag */
#define SPI_SR_CRCERR_Pos                   (4U)                               
#define SPI_SR_CRCERR_Msk                   (0x1U << SPI_SR_CRCERR_Pos)        /*!< 0x00000010 */
//#define SPI_SR_CRCERR                       SPI_SR_CRCERR_Msk                  /*!< CRC Error flag */
#define SPI_SR_MODF_Pos                     (5U)                               
#define SPI_SR_MODF_Msk                     (0x1U << SPI_SR_MODF_Pos)          /*!< 0x00000020 */
//#define SPI_SR_MODF                         SPI_SR_MODF_Msk                    /*!< Mode fault */
#define SPI_SR_OVR_Pos                      (6U)                               
#define SPI_SR_OVR_Msk                      (0x1U << SPI_SR_OVR_Pos)           /*!< 0x00000040 */
//#define SPI_SR_OVR                          SPI_SR_OVR_Msk                     /*!< Overrun flag */
#define SPI_SR_BSY_Pos                      (7U)                               
#define SPI_SR_BSY_Msk                      (0x1U << SPI_SR_BSY_Pos)           /*!< 0x00000080 */
#define SPI_N_SR_BSY                          SPI_SR_BSY_Msk                     /*!< Busy flag */

/********************  Bit definition for SPI_DR register  ********************/
#define SPI_DR_DR_Pos                       (0U)                               
#define SPI_DR_DR_Msk                       (0xFFFFU << SPI_DR_DR_Pos)         /*!< 0x0000FFFF */
#define SPI_DR_DR                           SPI_DR_DR_Msk                      /*!< Data Register */

/*******************  Bit definition for SPI_CRCPR register  ******************/
#define SPI_CRCPR_CRCPOLY_Pos               (0U)                               
#define SPI_CRCPR_CRCPOLY_Msk               (0xFFFFU << SPI_CRCPR_CRCPOLY_Pos) /*!< 0x0000FFFF */
#define SPI_CRCPR_CRCPOLY                   SPI_CRCPR_CRCPOLY_Msk              /*!< CRC polynomial register */


#endif