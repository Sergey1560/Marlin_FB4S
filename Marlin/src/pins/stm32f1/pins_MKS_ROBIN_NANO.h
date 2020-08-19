#pragma once

#ifndef __STM32F1__
  #error "Oops! Select an STM32F1 board in 'Tools > Board.'"
#elif HOTENDS > 2 || E_STEPPERS > 2
  #error "MKS Robin nano supports up to 2 hotends / E-steppers. Comment out this line to continue."
#endif

#define BOARD_INFO_NAME "MKS Robin Nano"

#define DISABLE_DEBUG
#undef JTAGSWD_DISABLE

/*
Управление подсветкой платой в разъеме второго экструдера
Управление ногой En
https://easyeda.com/sst78rust/fb4s-led-control
*/
#define CASE_LED_INSTEAD_E1

#define ENABLE_SPI2

/* 
Концевики
*/
#define X_STOP_PIN                          PA15
#define Y_STOP_PIN                          PA12
#define Z_MIN_PIN                           PA11

/*
BlTouch
*/
//#define Z_MAX_PIN                           PC4
#define SERVO0_PIN                          PB2   
#define BL_TOUCH_Z_PIN                      PC4

/*
Датчик окончания филамента
*/
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                    PA4   // MT_DET
#endif


//
// Steppers
//
#define X_ENABLE_PIN                        PE4
#define X_STEP_PIN                          PE3
#define X_DIR_PIN                           PE2

#define Y_ENABLE_PIN                        PE1
#define Y_STEP_PIN                          PE0
#define Y_DIR_PIN                           PB9

#define Z_ENABLE_PIN                        PB8
#define Z_STEP_PIN                          PB5
#define Z_DIR_PIN                           PB4

#define E0_ENABLE_PIN                       PB3
#define E0_STEP_PIN                         PD6
#define E0_DIR_PIN                          PD3

#ifdef CASE_LED_INSTEAD_E1
  #define LED_CASE_PIN                      PA3
#else
 #define E1_ENABLE_PIN                      PA3
 #define E1_STEP_PIN                        PA6
 #define E1_DIR_PIN                         PA1
#endif

#define HEATER_1_PIN                        PB0
//
// Temperature Sensors
//
#define TEMP_0_PIN                          PC1   // TH1
#define TEMP_BED_PIN                        PC0   // TB1

//Дополнительный термистор на корпусе
#if TEMP_SENSOR_CHAMBER > 0
  #define TEMP_CHAMBER_PIN                    PC2
#endif

//
// Heaters / Fans
//
#define HEATER_0_PIN                      PC3
#define HEATER_BED_PIN                    PA0

#define FAN1_PIN                          PB0
#define FAN_PIN                           PB1   

/*
Управление питанием
*/
#define SUICIDE_PIN                       PE5   
#define SUICIDE_PIN_INVERTING false

/*
Кнопка экстренной остановки
*/
//#define KILL_PIN                          PA2   // Enable MKSPWC support ROBIN NANO v1.2 ONLY
//#define KILL_PIN_INVERTING true                 // Enable MKSPWC support ROBIN NANO v1.2 ONLY

#define PWR_DET_PIN                         PA2
#define MT_DET_1_PIN                        PA4
#define MT_DET_2_PIN                        PE6
#define MT_DET_PIN_INVERTING false

#define WIFI_IO0_PIN                        PC13

//
// SD Card
//
#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION              ONBOARD
#endif

#define SDIO_SUPPORT
#define SDIO_CLOCK                          4500000// 4.5 MHz
#define SD_DETECT_PIN                       PD12
#define ONBOARD_SD_CS_PIN                   PC11

//
// LCD / Controller
//
#define BEEPER_PIN                          PC5

#if ENABLED(FSMC_GRAPHICAL_TFT)
  #define LCD_USE_DMA_FSMC 
  #define FSMC_DMA_DEV DMA2
  #define FSMC_DMA_CHANNEL DMA_CH5  
  
  #define FSMC_CS_PIN                       PD7   // NE4
  #define FSMC_RS_PIN                       PD11  // A0

  //#define LCD_RESET_PIN                     PC6   // FSMC_RST
  //#define NO_LCD_REINIT
  #define LCD_BACKLIGHT_PIN                 PD13

  #if ENABLED(TOUCH_BUTTONS)
    #define TOUCH_CS_PIN                    PA7   // SPI2_NSS
    #define TOUCH_SCK_PIN                   PB13  // SPI2_SCK
    #define TOUCH_MISO_PIN                  PB14  // SPI2_MISO
    #define TOUCH_MOSI_PIN                  PB15  // SPI2_MOSI
  #endif
#endif

#if ENABLED(TFT_LVGL_UI_FSMC)

  #define FSMC_CS_PIN                       PD7   // NE4
  #define FSMC_RS_PIN                       PD11  // A0

  #define TOUCH_CS_PIN                      PA7   // SPI2_NSS
  #define TOUCH_SCK_PIN                     PB13  // SPI2_SCK
  #define TOUCH_MISO_PIN                    PB14  // SPI2_MISO
  #define TOUCH_MOSI_PIN                    PB15  // SPI2_MOSI

  #define LCD_BACKLIGHT_PIN                 PD13

#endif

/*
Модуль MKS WIFI
*/
#define MKS_WIFI

#ifdef MKS_WIFI
 #undef PLATFORM_M997_SUPPORT

 #define MKS_WIFI_IO0                       PA8
 #define MKS_WIFI_IO4                       PC7
 #define MKS_WIFI_IO_RST                    PA5
#endif

#define SPI_FLASH
#if ENABLED(SPI_FLASH)
  #define W25QXX_CS_PIN                     PB12
  #define W25QXX_MOSI_PIN                   PB15
  #define W25QXX_MISO_PIN                   PB14
  #define W25QXX_SCK_PIN                    PB13
#endif

#if HAS_TMC220x
  /**
   * TMC2208/TMC2209 stepper drivers
   */
  //
  // Software serial
  //
  // #define X_SERIAL_TX_PIN                   PC7
  // #define X_SERIAL_RX_PIN                   PC7

  // #define Y_SERIAL_TX_PIN                   PD2
  // #define Y_SERIAL_RX_PIN                   PD2

  // #define Z_SERIAL_TX_PIN                   PC12
  // #define Z_SERIAL_RX_PIN                   PC12

  #define E0_SERIAL_TX_PIN                  PA6
  #define E0_SERIAL_RX_PIN                  PA6

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif

