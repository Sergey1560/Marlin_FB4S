# Marlin 3D Printer Firmware for Flying Bear 4S and 5

Это конфигурация [официального Marlin](https://github.com/MarlinFirmware/Marlin) для принтера Flying Bear Ghost 4S и 5. На данный момент поддерживаются платы MKS Robin Nano 1.x, MKS Robin Nano v2, MKS Robin Nano-s v1.3, MKS Robin Nano v1.3

![MKS UI](https://github.com/makerbase-mks/Mks-Robin-Nano-Marlin2.0-Firmware/blob/master/Images/MKS_Robin_Nano_printing.png)

В данном репозитории есть несколько веток:

* [FB4S_WIFI](https://github.com/Sergey1560/Marlin_FB4S/tree/FB4S_WIFI) - основная ветка. Эта ветка содержит дополнительный код для работы с модулем [MKS WIFI](https://github.com/makerbase-mks/MKS-WIFI), установленным в FB4S и FB5. Загрузка файлов через стандартный plugin в Cura. Классический интерфейс Color UI.
* [vanilla_fb_2.0.x](https://github.com/Sergey1560/Marlin_FB4S/tree/vanilla_fb_2.0.x) - ветка на основе 2.0.x ветки Marlin. Никаких изменений в коде. Все изменения только в файлах конфигурации, под платы robin nano и принтеры Flying Bear. Классический интерфейс Color UI. WIFI модуль не работает.
* [MKS_UI](https://github.com/Sergey1560/Marlin_FB4S/tree/MKS_UI) - ветка на основе 2.0.x ветки Marlin. В коде есть очень небольшое изменение размера буфера, для сборки на STM32F1. На STM32F4 никаких изменений в коде нет. Все изменения только в файлах конфигурации, под платы robin nano и принтеры Flying Bear. Интерфейс MKS UI. WIFI модуль работает.

Если у вас есть какие-то вопросы по настройке прошивки или по ее использованию, вы можете задать свой вопрос в [telegram группе](https://t.me/Ghostbustersss).

## MKS WIFI модуль

В данной ветке WIFI модуль работает.

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

* В файле platformio.ini в параметре default_envs указать mks_robin_nano_v1_3_f4

В меню Platformio можно не выбирать плату, а использовать для сборки сочетание клавиш Ctrl+Alt+B.

После компиляции, готовая прошивка лежит в .pio/build/mks_robin_nano35/Robin_nano35.bin для плат Robin Nano v1.1(1.2) и в .pio/build/mks_robin_nano_v1_3/Robin_nano35.bin для плат Robin Nano-s v1.3 и Robin Nano v1.3

На SD карту нужно записывать именно Robin_nano35.bin, а не firmaware.bin

### Что нужно настроить

Нужно настроить направления движения по осям под свои драйвера в файле [Configuration.h](./Marlin/Configuration.h) (параметры INVERT_?_DIR, строка 1373).

Для удобства, в файле [Configuration.h](./Marlin/Configuration.h) уже есть готовые наборы настроек для всех типовых конфигураций.

Для плат Robin Nano v1.1(1.2):

* ALL_DRV_2208 - 4 драйвера TMC 2208/2209
* FB_4S_STOCK - 4 драйвера A4988. Это конфигурация для FB4S с стандартными драйверами.
* FB_5_STOCK - 2 TMC 2208 (на осях X,Y) и 2 A4988 (на осях Z,E)

Для плат Robin Nano v1.3:

* FB_5_NANO_S_V1_3 - для платы Robin Nano-S v1.3
* FB_5_NANO_V1_3_4TMC - Robin Nano v1.3 c 4 драйверами TMC 2208/2209
* FB_5_NANO_V1_3 - Robin Nano v1.3 c 2 драйверами TMC 2208/2209 и 2 драйверами A4988

В строке 1322 нужно выбрать только один из вариантов:

```C
#define ALL_DRV_2208
//#define FB_4S_STOCK
//#define FB_5_STOCK
//#define FB_5_NANO_S_V1_3
//#define FB_5_NANO_V1_3_4TMC
//#define FB_5_NANO_V1_3
```
