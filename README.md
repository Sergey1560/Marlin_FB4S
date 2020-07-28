# Marlin 3D Printer Firmware for Flying Bear 4S

## Версия поддержкой WIFI модуля

Это конфигурация [официального Marlin](https://github.com/MarlinFirmware/Marlin) для принтера Flying Bear Ghost 4S (плата MKS Robin Nano).
Эта ветка содержит код для работы с модулем [MKS WIFI](https://github.com/makerbase-mks/MKS-WIFI), установленным в FB4S. Загрузка файлов через стандартный plugin в Cura.
Код работы с экраном взят из репозитория [inib/Marlin](https://github.com/inib/Marlin)

В ветке [FB4S_Config](https://github.com/Sergey1560/Marlin_FB4S/tree/FB4S_Config) находится вариант с минимальными изменениями в коде Marlin (только работа с экраном и конфигурация)

## Что работает, что не работает

### Работает

* Отображение температуры в Cura
* Просмотр содержимого SD карты
* Удаление файлов с SD карты
* Загрузка файлов на SD карту
* Автоматический запуск печати при загрузке файла.
* Настройка WIFI модуля (сеть и пароль)

### Не работает (совсем)

* **Имена файлов на русском** Переименуйте файл в Cura
* Работает только с картами стандарта SD card v2.0 и новее. Это все карты от 1Гб и больше.
* Отображение состояния принтера (печатает, не печатает) в Cura

## Как работает, как настроить

### Как собрать прошивку самому

Видео Дмитрия Соркина [youtube](https://www.youtube.com/watch?v=HirIZk0rWOQ)

Нужная плата, robin nano, уже выбрана в качестве платы по-умолчанию. В меню Platformio можно не выбирать плату, а нажать Build на самом верху. Или использовать сочетание клавиш Ctrl+Alt+B.

После компиляции, готовая прошивка лежит в .pio/build/mks_robin_nano/Robin_nano35.bin

### Что нужно настроить

Нужно настроить направления движения по осям под свои драйвера в файле [Configuration.h](./Marlin/Configuration.h) (параметры INVERT_?_DIR, строка 1071). По умолчанию стоят настройки под драйвера 2208. В файле [Configuration.h](./Marlin/Configuration.h) уже есть готовые настройки для стандартных драйверов (A4988) и для драйверов 2208/2209. В строке 1110 достаточно выбрать один из вариантов:

```C
#define ALL_DRV_2208
//#define ALL_DRV_A4988
```

### Если нет желания самому собирать прошивку

Готовые файлы лежат в папке firmware.

Если вы используете драйвера 2208 или 2209, прошивка в папке firmware/2208 [Robin_nano35.bin](./firmware/2208/Robin_nano35.bin)

Если вы используете стандартные драйвера, прошивка в папке firmware/std [Robin_nano35.bin](./firmware/std/Robin_nano35.bin)

Отличия сборок только в инвертировании осей.

### Настройки WIFI, если вы используете готовую прошивку

Если модуль уже был настроен, то возможно никакая настройка не понадобится. Если модуль не был настроен, либо по какой-то причине не смог подключиться к сети, то он запустится в режиме точки доступа с именем сети MKSWIFI??? (вместо ? будут произвольные символы). Подключитесь к этой сети, откройте страницу по адресу 192.168.4.1 и установите нужные настройки.

### Настройки WIFI, если вы собираете прошивку сами

В файле [mks_wifi_settings.h](./Marlin/src/module/mks_wifi/mks_wifi_settings.h)

Для того, чтобы эти настройки применялись при включении, "MKS_WIFI_ENABLED_WIFI_CONFIG" должен быть раскомментирован. Если закомментировать "#define MKS_WIFI_ENABLED_WIFI_CONFIG", при запуске настройки ESP модулю отправляться не будут

### Диагностика WIFI

При успешном подключении к сети (или создании сети в режиме точки доступа) в стандартный UART, который выведен на USB разъем принтера, будет выведен IP адрес и название сети. Если у модуля ESP есть какие-то настройки сети, но подключиться к ней он не смог, то модуль перейдет в режим точки доступа, и выдаст в UART название точки доступа и свой IP. На попытки подключения к сети уходит несколько минут.

IP адрес так же будет на экране.

### Как понять, что оно работает

При включении принтера, на экране отобразится статус "WIFI init"

Если ESP модулю удалось подключиться к сети, на экране будет IP адрес.

При старте передачи файла отображается "Upload file", в процессе загрузки отображается прогресс в процентах.

Если файл успешно принят отобразится "Upload done" и **прозвучит один звуковой сигнал**

Если во время приема файла были ошибки, отобразится надпись "Upload Failed" и **прозвучит три звуковых сигнала**

### EEPROM

На FB4S установлена плата [MKS Robin Nano v.1.1](https://fbghost.info/bin/view/Main/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%B8%D0%BA%D0%B0%20%2F%20%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%B8%D0%BA%D0%B0/%D0%A3%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D1%8F%D1%8E%D1%89%D0%B0%D1%8F%20%D0%BF%D0%BB%D0%B0%D1%82%D0%B0/MKS%20Robin%20Nano%20V1.1/). На плате установленно 2 микросхемы флеш памяти: AT24C16 (2кб) подключена по I2C и W25Q64 подключена по SPI.

Размер данных, которые сохраняются в EEPROM зависит от включенных опций. При сохранении настроек командой M500, в ответе есть размер сохраняемых данных.

В качестве места хранения EEPROM в Marlin доступны несколько вариантов:

* SD карта. Этот вариант наиболее предпочтительный, если нет осознанного желания хранить EEPROM где-то еще.
* I2C EEPROM. Хранение в AT24C16 подключенной по I2C. При первом включении все содержимое AT24C16 будет переписано. Память не быстрая, поэтому процесс занимает до 10 секунд. В дальнейшем в память пишутся только измененные значения, поэтому работает быстрее.
* SPI_EEPROM. Хранение в W25Q64BV подключенной по SPI.
* FLASH_EEPROM_EMULATION. Это хранение EEPROM в flash памяти STM32. Этот вариант не работает.
* SRAM_EEPROM_EMULATION.  Этот вариант не работает.

Для включения в [Configuration.h](./Marlin/Configuration.h) в разделе EEPROM нужно указать нужный define. Возможные варианты указаны в комментарии. Пример:

```C
#if ENABLED(EEPROM_SETTINGS)
/*
MKS Robin EEPROM:
EEPROM_SD
EEPROM_AT24C16
EEPROM_W25Q
*/
#define EEPROM_SD

#if ENABLED(EEPROM_AT24C16)
#undef SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
#define I2C_EEPROM_AT24C16
#define USE_WIRED_EEPROM    1
#define E2END (2*1024 - 1)
#endif

#if ENABLED(EEPROM_W25Q)
#undef SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
#undef I2C_EEPROM_AT24C16
#define SPI_EEPROM_W25Q
#define SPI_EEPROM_OFFSET 0x700000
#define USE_WIRED_EEPROM    1
#define E2END (2*1024 - 1)
#endif

#if ENABLED(EEPROM_SD)
#define SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
#undef I2C_EEPROM_AT24C16
#undef SPI_EEPROM_W25Q
#undef USE_WIRED_EEPROM
#endif

#define EEPROM_AUTO_INIT  // Init EEPROM automatically on any errors.
#endif
```

Для изменения места хранения EEPROM например на SPI флеш, надо заменить "#define EEPROM_SD" на "#define EEPROM_W25Q"

### Загрузка прошивки по WIFI

Есть возможность отправлять прошивку на принтер через WIFI. Для этого в файле [platformio.ini](./platformio.ini) в разделе [env:mks_robin_nano] нужно указать IP адрес принтера в опции upload_flags (строка 499).

Передача файла происходит при помощи curl, поэтому надо или добавить curl в $PATH, либо указать полный путь в файле [mks_robin_nano.py](./buildroot/share/PlatformIO/scripts/mks_robin_nano.py) в строке 48.

После настройки, для отправки прошивки на принтер, в меню platformio нужно выбрать Upload или нажать Ctrl+Alt+U.

После успешной передачи файла принтер перезагрузится автоматически.
