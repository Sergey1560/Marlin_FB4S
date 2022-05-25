<p align="center"><img src="buildroot/share/pixmaps/logo/marlin-outrun-nf-500.png" height="250" alt="MarlinFirmware's logo" /></p>

<h1 align="center">Marlin 3D Printer Firmware</h1>

<p align="center">
    <a href="/LICENSE"><img alt="GPL-V3.0 License" src="https://img.shields.io/github/license/marlinfirmware/marlin.svg"></a>
    <a href="https://github.com/MarlinFirmware/Marlin/graphs/contributors"><img alt="Contributors" src="https://img.shields.io/github/contributors/marlinfirmware/marlin.svg"></a>
    <a href="https://github.com/MarlinFirmware/Marlin/releases"><img alt="Last Release Date" src="https://img.shields.io/github/release-date/MarlinFirmware/Marlin"></a>
    <a href="https://github.com/MarlinFirmware/Marlin/actions"><img alt="CI Status" src="https://github.com/MarlinFirmware/Marlin/actions/workflows/test-builds.yml/badge.svg"></a>
    <a href="https://github.com/sponsors/thinkyhead"><img alt="GitHub Sponsors" src="https://img.shields.io/github/sponsors/thinkyhead?color=db61a2"></a>
    <br />
    <a href="https://twitter.com/MarlinFirmware"><img alt="Follow MarlinFirmware on Twitter" src="https://img.shields.io/twitter/follow/MarlinFirmware?style=social&logo=twitter"></a>
</p>

* [FB4S_WIFI](https://github.com/Sergey1560/Marlin_FB4S/tree/FB4S_WIFI) - основная ветка. Эта ветка содержит дополнительный код для работы с модулем [MKS WIFI](https://github.com/makerbase-mks/MKS-WIFI), установленным в FB4S и FB5. Загрузка файлов через стандартный plugin в Cura. Классический интерфейс Color UI.
* [vanilla_fb_2.0.x](https://github.com/Sergey1560/Marlin_FB4S/tree/vanilla_fb_2.0.x) - ветка на основе 2.0.x ветки Marlin. Никаких изменений в коде. Все изменения только в файлах конфигурации, под платы robin nano и принтеры Flying Bear. Классический интерфейс Color UI. WIFI модуль не работает.
* [MKS_UI](https://github.com/Sergey1560/Marlin_FB4S/tree/MKS_UI) - ветка на основе 2.0.x ветки Marlin. В коде есть очень небольшое изменение размера буфера, для сборки на STM32F1. На STM32F4 никаких изменений в коде нет. Все изменения только в файлах конфигурации, под платы robin nano и принтеры Flying Bear. Интерфейс MKS UI. WIFI модуль работает.

Если у вас есть какие-то вопросы по настройке прошивки или по ее использованию, вы можете задать свой вопрос в [telegram группе](https://t.me/Ghostbustersss).

## MKS WIFI модуль

В данной ветке WIFI модуль не работает.

### Варианты прошивки

Для настройки под свои нужды, прошивку нужно собрать самостоятельно.

Все настройки для плат Robin Nano v1.1(1.2) уже сделаны, можно ничего не менять.

Плата Robin Nano-s v1.3 и Robin Nano v1.3  сделана на другом микроконтроллере (stm32f407), поэтому для сборки прошивки под эту плату нужно изменить:

* В файле Marlin/Configuration.h параметр MOTHERBOARD:

```C
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_MKS_ROBIN_NANO_V1_3_F4
#endif
```

  Platform|MCU|Example Boards
  --------|---|-------
  [Arduino AVR](https://www.arduino.cc/)|ATmega|RAMPS, Melzi, RAMBo
  [Teensy++ 2.0](https://www.microchip.com/en-us/product/AT90USB1286)|AT90USB1286|Printrboard
  [Arduino Due](https://www.arduino.cc/en/Guide/ArduinoDue)|SAM3X8E|RAMPS-FD, RADDS, RAMPS4DUE
  [ESP32](https://github.com/espressif/arduino-esp32)|ESP32|FYSETC E4, E4d@BOX, MRR
  [LPC1768](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc1700-cortex-m3/512-kb-flash-64-kb-sram-ethernet-usb-lqfp100-package:LPC1768FBD100)|ARM® Cortex-M3|MKS SBASE, Re-ARM, Selena Compact
  [LPC1769](https://www.nxp.com/products/processors-and-microcontrollers/arm-microcontrollers/general-purpose-mcus/lpc1700-cortex-m3/512-kb-flash-64-kb-sram-ethernet-usb-lqfp100-package:LPC1769FBD100)|ARM® Cortex-M3|Smoothieboard, Azteeg X5 mini, TH3D EZBoard
  [STM32F103](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html)|ARM® Cortex-M3|Malyan M200, GTM32 Pro, MKS Robin, BTT SKR Mini
  [STM32F401](https://www.st.com/en/microcontrollers-microprocessors/stm32f401.html)|ARM® Cortex-M4|ARMED, Rumba32, SKR Pro, Lerdge, FYSETC S6
  [STM32F7x6](https://www.st.com/en/microcontrollers-microprocessors/stm32f7x6.html)|ARM® Cortex-M7|The Borg, RemRam V1
  [SAMD51P20A](https://www.adafruit.com/product/4064)|ARM® Cortex-M4|Adafruit Grand Central M4
  [Teensy 3.5](https://www.pjrc.com/store/teensy35.html)|ARM® Cortex-M4|
  [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)|ARM® Cortex-M4|
  [Teensy 4.0](https://www.pjrc.com/store/teensy40.html)|ARM® Cortex-M7|
  [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)|ARM® Cortex-M7|
  Linux Native|x86/ARM/etc.|Raspberry Pi

В меню Platformio можно не выбирать плату, а использовать для сборки сочетание клавиш Ctrl+Alt+B.

После компиляции, готовая прошивка лежит в .pio/build/mks_robin_nano35/Robin_nano35.bin для плат Robin Nano v1.1(1.2) и в .pio/build/mks_robin_nano_v1_3/Robin_nano35.bin для плат Robin Nano-s v1.3 и Robin Nano v1.3

На SD карту нужно записывать именно Robin_nano35.bin, а не firmaware.bin

### Что нужно настроить

- [Marlin Documentation](https://marlinfw.org) - Official Marlin documentation
- [Marlin Discord](https://discord.gg/n5NJ59y) - Discuss issues with Marlin users and developers
- Facebook Group ["Marlin Firmware"](https://www.facebook.com/groups/1049718498464482/)
- RepRap.org [Marlin Forum](https://forums.reprap.org/list.php?415)
- Facebook Group ["Marlin Firmware for 3D Printers"](https://www.facebook.com/groups/3Dtechtalk/)
- [Marlin Configuration](https://www.youtube.com/results?search_query=marlin+configuration) on YouTube

Для удобства, в файле [Configuration.h](./Marlin/Configuration.h) уже есть готовые наборы настроек для всех типовых конфигураций.

Для плат Robin Nano v1.1(1.2):

* ALL_DRV_2208 - 4 драйвера TMC 2208/2209
* FB_4S_STOCK - 4 драйвера A4988. Это конфигурация для FB4S с стандартными драйверами.
* FB_5_STOCK - 2 TMC 2208 (на осях X,Y) и 2 A4988 (на осях Z,E)

Для плат Robin Nano v1.3:

 - Scott Lahteine [[@thinkyhead](https://github.com/thinkyhead)] - USA - Project Maintainer &nbsp; [💸 Donate](https://www.thinkyhead.com/donate-to-marlin)
 - Roxanne Neufeld [[@Roxy-3D](https://github.com/Roxy-3D)] - USA
 - Keith Bennett [[@thisiskeithb](https://github.com/thisiskeithb)] - USA &nbsp; [💸 Donate](https://github.com/sponsors/thisiskeithb)
 - Peter Ellens [[@ellensp](https://github.com/ellensp)] - New Zealand
 - Victor Oliveira [[@rhapsodyv](https://github.com/rhapsodyv)] - Brazil
 - Chris Pepper [[@p3p](https://github.com/p3p)] - UK
 - Jason Smith [[@sjasonsmith](https://github.com/sjasonsmith)] - USA
 - Luu Lac [[@shitcreek](https://github.com/shitcreek)] - USA
 - Bob Kuhn [[@Bob-the-Kuhn](https://github.com/Bob-the-Kuhn)] - USA
 - Erik van der Zalm [[@ErikZalm](https://github.com/ErikZalm)] - Netherlands &nbsp; [💸 Donate](https://flattr.com/submit/auto?user_id=ErikZalm&url=https://github.com/MarlinFirmware/Marlin&title=Marlin&language=&tags=github&category=software)

В строке 1322 нужно выбрать только один из вариантов:

```C
#define ALL_DRV_2208
//#define FB_4S_STOCK
//#define FB_5_STOCK
//#define FB_5_NANO_S_V1_3
//#define FB_5_NANO_V1_3_4TMC
//#define FB_5_NANO_V1_3
```
