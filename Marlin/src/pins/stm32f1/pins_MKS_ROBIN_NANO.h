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
#define Z_MAX_PIN                           PC4

/*
BlTouch
*/
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
#define TEMP_1_PIN                          PC2   // TH2
#define TEMP_BED_PIN                        PC0   // TB1

//Дополнительный термистор на корпусе
#if TEMP_SENSOR_CHAMBER > 0
  #define TEMP_CHAMBER_PIN                    PC2
#endif

//
// Heaters / Fans
//
#ifndef HEATER_0_PIN
  #define HEATER_0_PIN                      PC3
#endif

#if HOTENDS == 1
  #ifndef FAN1_PIN
    #define FAN1_PIN                        PB0
  #endif
#else
  #ifndef HEATER_1_PIN
    #define HEATER_1_PIN                    PB0
  #endif
#endif

#ifndef FAN_PIN
  #define FAN_PIN                           PB1   // FAN
#endif

#ifndef HEATER_BED_PIN
  #define HEATER_BED_PIN                    PA0
#endif

//
// Thermocouples
//
//#define MAX6675_SS_PIN                    PE5   // TC1 - CS1
//#define MAX6675_SS_PIN                    PE6   // TC2 - CS2

/*
Управление питанием
*/
#define SUICIDE_PIN                       PE5   
#define SUICIDE_PIN_INVERTING             false

/*
Кнопка экстренной остановки
*/
//#define KILL_PIN                          PA2   // Enable MKSPWC support ROBIN NANO v1.2 ONLY
//#define KILL_PIN_INVERTING                true  // Enable MKSPWC support ROBIN NANO v1.2 ONLY
//#define LED_PIN                           PB2

#define MT_DET_1_PIN                        PA4
#define MT_DET_2_PIN                        PE6
#define MT_DET_PIN_INVERTING               false

#define WIFI_IO0_PIN                        PC13

//
// SD Card
//
#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION              ONBOARD
#endif

#define SDIO_SUPPORT
#define SDIO_CLOCK                       4500000  // 4.5 MHz
#define SD_DETECT_PIN                       PD12
#define ONBOARD_SD_CS_PIN                   PC11

//
// LCD / Controller
//
#define BEEPER_PIN                          PC5

/**
 * Note: MKS Robin TFT screens use various TFT controllers.
 * If the screen stays white, disable 'LCD_RESET_PIN'
 * to let the bootloader init the screen.
 */

// Shared FSMC Configs
#if HAS_FSMC_TFT
  #define FSMC_CS_PIN                       PD7   // NE4
  #define FSMC_RS_PIN                       PD11  // A0

  #define TOUCH_CS_PIN                      PA7   // SPI2_NSS
  #define TOUCH_SCK_PIN                     PB13  // SPI2_SCK
  #define TOUCH_MISO_PIN                    PB14  // SPI2_MISO
  #define TOUCH_MOSI_PIN                    PB15  // SPI2_MOSI

  #define LCD_RESET_PIN                     PC6   // FSMC_RST
  #define LCD_BACKLIGHT_PIN                 PD13

  #define TFT_RESET_PIN                     PC6   // FSMC_RST
  #define TFT_BACKLIGHT_PIN                 PD13

  #define LCD_USE_DMA_FSMC                        // Use DMA transfers to send data to the TFT
  #define FSMC_CS_PIN                       PD7
  #define FSMC_RS_PIN                       PD11
  #define FSMC_DMA_DEV                      DMA2
  #define FSMC_DMA_CHANNEL               DMA_CH5

  #define TOUCH_BUTTONS_HW_SPI
  #define TOUCH_BUTTONS_HW_SPI_DEVICE          2
#endif

// LVGL Configs
#if ENABLED(TFT_LVGL_UI_FSMC)

  #define XPT2046_X_CALIBRATION            17880
  #define XPT2046_Y_CALIBRATION           -12234
  #define XPT2046_X_OFFSET                   -45
  #define XPT2046_Y_OFFSET                   349

// Emulated DOGM Configs
#elif ENABLED(FSMC_GRAPHICAL_TFT)

  #define DOGLCD_MOSI                       -1    // prevent redefine Conditionals_post.h
  #define DOGLCD_SCK                        -1

  #ifndef GRAPHICAL_TFT_UPSCALE
    #define GRAPHICAL_TFT_UPSCALE              3
  #endif
  #ifndef TFT_WIDTH
    #define TFT_WIDTH                        480
  #endif
  #ifndef TFT_PIXEL_OFFSET_X
    #define TFT_PIXEL_OFFSET_X                48
  #endif
  #ifndef TFT_HEIGHT
    #define TFT_HEIGHT                       320
  #endif
  #ifndef TFT_PIXEL_OFFSET_Y
    #define TFT_PIXEL_OFFSET_Y                32
  #endif

  #ifndef XPT2046_X_CALIBRATION
    #define XPT2046_X_CALIBRATION          12149
  #endif
  #ifndef XPT2046_Y_CALIBRATION
    #define XPT2046_Y_CALIBRATION          -8746
  #endif
  #ifndef XPT2046_X_OFFSET
    #define XPT2046_X_OFFSET                 -35
  #endif
  #ifndef XPT2046_Y_OFFSET
    #define XPT2046_Y_OFFSET                 256
  #endif

#elif ENABLED(TFT_320x240)                        // TFT32/28
  #define TFT_RESET_PIN                     PC6
  #define TFT_BACKLIGHT_PIN                 PD13

  #define LCD_USE_DMA_FSMC                        // Use DMA transfers to send data to the TFT
  #define FSMC_CS_PIN                       PD7
  #define FSMC_RS_PIN                       PD11
  #define FSMC_DMA_DEV                      DMA2
  #define FSMC_DMA_CHANNEL               DMA_CH5

  #define XPT2046_X_CALIBRATION           -12246
  #define XPT2046_Y_CALIBRATION             9453
  #define XPT2046_X_OFFSET                   360
  #define XPT2046_Y_OFFSET                   -22

  #define TOUCH_CS_PIN                      PA7   // SPI2_NSS
  #define TOUCH_SCK_PIN                     PB13  // SPI2_SCK
  #define TOUCH_MISO_PIN                    PB14  // SPI2_MISO
  #define TOUCH_MOSI_PIN                    PB15  // SPI2_MOSI

  #define TFT_DRIVER                     ILI9341
  #define TFT_BUFFER_SIZE                  14400

  // YV for normal screen mounting
  //#define ILI9341_ORIENTATION  ILI9341_MADCTL_MY | ILI9341_MADCTL_MV
  // XV for 180° rotated screen mounting
  #define ILI9341_ORIENTATION  ILI9341_MADCTL_MX | ILI9341_MADCTL_MV

#elif ENABLED(TFT_480x320)
  #define XPT2046_X_CALIBRATION            17880
  #define XPT2046_Y_CALIBRATION           -12234
  #define XPT2046_X_OFFSET                   -45
  #define XPT2046_Y_OFFSET                   349

  #define TFT_DRIVER                     ILI9488
  #define TFT_BUFFER_SIZE                  320*15
  #define ILI9488_ORIENTATION               ILI9488_MADCTL_MX | ILI9488_MADCTL_MV
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

#define HAS_SPI_FLASH                          1
#define SPI_FLASH_SIZE                 0x1000000  // 16MB
#if HAS_SPI_FLASH
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
  #define X_SERIAL_TX_PIN                   PA6
  #define X_SERIAL_RX_PIN                   PA1

  #define Y_SERIAL_TX_PIN                   PA6
  #define Y_SERIAL_RX_PIN                   PA1

  #define Z_SERIAL_TX_PIN                   PA6
  #define Z_SERIAL_RX_PIN                   PA1

  #define E0_SERIAL_TX_PIN                  PA6
  #define E0_SERIAL_RX_PIN                  PA1

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200
#endif

