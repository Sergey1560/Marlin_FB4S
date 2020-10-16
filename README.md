# Marlin 3D Printer Firmware for Flying Bear 4S and 5

Это конфигурация [официального Marlin](https://github.com/MarlinFirmware/Marlin) для принтера Flying Bear Ghost 4S и 5 (плата MKS Robin Nano 1.x).

Эта ветка содержит дополнительный код для работы с модулем [MKS WIFI](https://github.com/makerbase-mks/MKS-WIFI), установленным в FB4S и FB5. Загрузка файлов через стандартный plugin в Cura.

Прошивка работает на принтерах Flying Bear Ghost 4S и 5. Экран работает. WIFI работает.

## MKS WIFI модуль

### Работает

* Отображение температуры в Cura
* Просмотр содержимого SD карты
* Удаление файлов с SD карты
* Загрузка файлов на SD карту
* Автоматический запуск печати при загрузке файла.
* Настройка WIFI модуля (сеть и пароль)

### Не работает

* **Имена файлов на русском** Переименуйте файл в Cura
* Работает только с картами стандарта SD card v2.0 и новее. Это все карты от 1Гб и больше.
* Отображение состояния принтера (печатает, не печатает) в Cura

## Как работает, как настроить

### Варианты прошивки

Если вас устраивает типовой вариант конфигурации, можно взять готовые файлы прошивки можно в разделе [Releases](https://github.com/Sergey1560/Marlin_FB4S/releases)

Вернуть стандартную прошивку можно в любой момент. Просто запишите ее на SD и включите принтер.

Для настройки под свои нужды, прошивку нужно собрать самостоятельно.

### Первое, что нужно сделать, после прошивки

Первое, что нужно сделать после прошивки, это проинициализировать EEPROM (память внутри принтера), сбросив настройки по-умолчанию. После прошивки там находится мусор, который может привести к совершенно необъяснимому поведению.

Делается это через меню Configuration -> Advanced settings -> Initialize eeprom.

### Как собрать прошивку самому

[Видео](https://www.youtube.com/watch?v=HirIZk0rWOQ) Дмитрия Соркина

Нужная плата, Robin Nano, уже выбрана в качестве платы по-умолчанию. В меню Platformio можно не выбирать плату, а использовать сочетание клавиш Ctrl+Alt+B.

После компиляции, готовая прошивка лежит в .pio/build/mks_robin_nano35/Robin_nano35.bin

На SD карту нужно записывать именно Robin_nano35.bin, а не firmaware.bin

### Что нужно настроить, если собираете сами

Нужно настроить направления движения по осям под свои драйвера в файле [Configuration.h](./Marlin/Configuration.h) (параметры INVERT_?_DIR, строка 1125).

По умолчанию стоят настройки под драйвера 2208/2209 на всех осях. В файле [Configuration.h](./Marlin/Configuration.h) уже есть несколько готовых наборов настроек:

* ALL_DRV_2208 - если установлены драйвера TMC 2208 или TMC 2209 на всех осях
* FB_4S_STOCK - если установлены драйвера A4988 на всех осях. Это конфигурация для FB4S с стандартными драйверами.
* FB_5_STOCK - конфигурация для FB 5 (2208 на осях X,Y и A4988 на Z,E)

В строке 1098 нужно выбрать только один из вариантов:

```C
#define ALL_DRV_2208
//#define FB_4S_STOCK
//#define FB_5_STOCK
```

### Настройки WIFI, если вы используете готовую прошивку

Настройки сети хранятся в самом ESP-модуле. Есть несколько вариантов настройки:

* Если модуль уже был настроен, то возможно никакая настройка не понадобится
* Если модуль не был настроен, либо по какой-то причине не смог подключиться к сети, то он запустится в режиме точки доступа с именем сети MKSWIFI??? (вместо ? будут произвольные символы). Подключитесь к этой сети, откройте страницу по адресу 192.168.4.1 и установите нужные настройки сети.
* Если вы собираете прошивку сами, есть возможность передать модулю настройки при запуске. Для этого в файле [mks_wifi_settings.h](./Marlin/src/module/mks_wifi/mks_wifi_settings.h) можно задать параметры WIFI сети.
Для того, чтобы эти настройки применялись при включении, "MKS_WIFI_ENABLED_WIFI_CONFIG" должен быть включен.

### Состояние WIFI

При успешном подключении к сети (или создании сети в режиме точки доступа) в стандартный UART, который выведен на USB разъем принтера, будет выведен IP адрес и название сети, а так же IP адрес будет отображен на экране принтера.

### Как понять, что WIFI работает

При включении принтера, на экране отобразится статус "WIFI init"

Если ESP модулю удалось подключиться к сети, на экране будет IP адрес.

При старте передачи файла отображается "Upload file", в процессе загрузки отображается прогресс в процентах.

Если файл успешно принят отобразится "Upload done" и **прозвучит один звуковой сигнал**

Если во время приема файла были ошибки, отобразится надпись "Upload Failed" и **прозвучит три звуковых сигнала**

### Отключение кода связанного с WIFI модулем

Для отключения всего кода, который связан с WIFI модулем нужно в файле [Marlin/src/pins/stm32f1/pins_MKS_ROBIN_NANO.h](./Marlin/src/pins/stm32f1/pins_MKS_ROBIN_NANO.h) отключить "#define MKS_WIFI". После этого в коде останутся только несколько незначительных изменений, которые не должны влиять на стабильность работы. Если нужен абсолютно чистый код, без каких либо изменений, взять его можно из [оффициального репозитория Marlin](https://github.com/MarlinFirmware/Marlin) и использовать файлы [Configuration.h](./Marlin/Configuration.h) и [Configuration_adv.h](./Marlin/Configuration_adv.h) как образец.

### BLTouch

В прошивке по-умолчанию включена поддержка Bltouch. Парковка стола по оси Z настроена по стандартному концевику (а не по датчику), поэтому если у вас нет датчика, то мешать это не будет. Просто не трогайте настройки Z Offset (должно быть 0).

Прошивка настроена на подключение датчика к разъему ZMax (концевик датчика) и PB2 (управление сервой). Подробнее о [подключении Bltouch](https://sergey1560.github.io/fb4s_howto/bltouch/).

### Драйвера TMC2209

По-умолчанию прошивка настроена на работу с драйверами шаговых двигателей без программного управления. В случае применения драйвером TMC 2209 или TMC 2208 можно включить управление по UART. Подробнее о [настройке и подключении](https://sergey1560.github.io/fb4s_howto/tmc_uart/).

### EEPROM

На FB4S установлена плата [MKS Robin Nano v.1.1](https://fbghost.info/bin/view/Main/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%B8%D0%BA%D0%B0%20%2F%20%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%B8%D0%BA%D0%B0/%D0%A3%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D1%8F%D1%8E%D1%89%D0%B0%D1%8F%20%D0%BF%D0%BB%D0%B0%D1%82%D0%B0/MKS%20Robin%20Nano%20V1.1/). На плате установленно 2 микросхемы флеш памяти: AT24C16 (2кб, подключена по I2C) и W25Q64 (подключена по SPI).

Размер данных, которые сохраняются в EEPROM зависит от включенных опций. При сохранении настроек командой M500, в ответе есть размер сохраняемых данных.

В качестве места хранения EEPROM в Marlin доступны несколько вариантов:

* SD карта
* I2C EEPROM. Этот вариант не используется, драйвер отключен.
* SPI_EEPROM. Хранение в W25Q64BV подключенной по SPI. Этот вариант используется по-умолчанию.
* FLASH_EEPROM_EMULATION. Это хранение EEPROM в flash памяти STM32. Этот вариант не работает.
* SRAM_EEPROM_EMULATION.  Этот вариант не работает.

Для включения в [Configuration.h](./Marlin/Configuration.h) в разделе EEPROM нужно указать нужный define. Возможные варианты указаны в комментарии. Пример:

```C
#if ENABLED(EEPROM_SETTINGS)
/*
MKS Robin EEPROM:
EEPROM_SD
EEPROM_W25Q
*/
#define EEPROM_W25Q

#if ENABLED(EEPROM_W25Q)
#undef SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
#undef I2C_EEPROM_AT24C16
#define SPI_EEPROM_W25Q
#define SPI_EEPROM
#define SPI_EEPROM_OFFSET 0x700000
#define USE_WIRED_EEPROM    1
#define MARLIN_EEPROM_SIZE  2048
#endif

#if ENABLED(EEPROM_SD)
#define SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
#undef I2C_EEPROM_AT24C16
#undef SPI_EEPROM_W25Q
#undef USE_WIRED_EEPROM
#define MARLIN_EEPROM_SIZE  4096
#endif

#define EEPROM_AUTO_INIT  // Init EEPROM automatically on any errors.
#endif
```

Для изменения места хранения EEPROM нужно заменить "#define EEPROM_W25Q" на другой вариант.

### Загрузка прошивки по WIFI

Есть возможность отправлять прошивку на принтер через WIFI. Для этого в файле [platformio.ini](./platformio.ini) в разделе [env:mks_robin_nano35] нужно указать IP адрес принтера в опции upload_flags.

Передача файла происходит при помощи curl, поэтому надо или добавить curl в $PATH, либо указать полный путь в файле [mks_robin_nano35.py](./buildroot/share/PlatformIO/scripts/mks_robin_nano35.py) в строке 43.

После настройки, для отправки прошивки на принтер, в меню platformio нужно выбрать Upload или нажать Ctrl+Alt+U.

После успешной передачи файла принтер перезагрузится автоматически.

## Выбор графического интерфейса

В коде Marlin есть 3 варианта графического интерфейса, которые работают на FB4S и FB5. Для выбора интерфейса нужно выбрать тип экрана и тип интерфейса в [Configuration.h](./Marlin/Configuration.h), в разделе Graphical TFTs (около 2270 строки).

Для экрана на FB4S и FB5 тип экрана - MKS_ROBIN_TFT35:

```
/**
 * TFT Type - Select your Display type
 *
 * Available options are:
 *   MKS_TS35_V2_0,
 *   MKS_ROBIN_TFT24, MKS_ROBIN_TFT28, MKS_ROBIN_TFT32, MKS_ROBIN_TFT35,
 *   MKS_ROBIN_TFT43, MKS_ROBIN_TFT_V1_1R
 *   TFT_TRONXY_X5SA, ANYCUBIC_TFT35, LONGER_LK_TFT28
 *   TFT_GENERIC
 *
 * For TFT_GENERIC, you need to configure these 3 options:
 *   Driver:     TFT_DRIVER
 *               Current Drivers are: AUTO, ST7735, ST7789, ST7796, R61505, ILI9328, ILI9341, ILI9488
 *   Resolution: TFT_WIDTH and TFT_HEIGHT
 *   Interface:  TFT_INTERFACE_FSMC or TFT_INTERFACE_SPI
 */
#define MKS_ROBIN_TFT35
```

Есть 3 варианта интерфейса, которые можно выбрать:

* Классический Marlin, "текстовый" интерфейс. Включение:

```
#define TFT_CLASSIC_UI
```

* Новый, графический интерфейс, расчитанные под тач-экраны:

```
#define TFT_COLOR_UI
```

* Графический интерфейс от MKS. [Подробнее](https://sergey1560.github.io/fb4s_howto/mks_ui/) про сборку этого варианта.

## WIFI модуль, отправка команд и файлов

Для отправки команд и файлов на принтер не обязательно использовать Cura. Для отправки можно использовать простые инструменты - curl и netcat.

Для отправки команд используется tcp socket на порт 8080. Пример с netcat:

```
nc 192.168.0.105 8080
```

Вместо netcat можно использовать telnet.

Можно отправлять g-код команды, и получать ответ.

Для отправки файлов можно воспользоваться curl:

```
curl -v -H "Content-Type:application/octet-stream" http://192.168.0.105/upload?X-Filename=sd_file.gcode --data-binary @local_file.gcode
```

* *sd_file.gcode* - имя файла под которым будет сохранение на sd карте
* *local_file.gcode* - имя файла для отправки

В данном примере на принтер с IP 192.168.0.105 будет отправлен файл local_file.gcode, который будет сохранен на sd карте под именем sd_file.gcode
