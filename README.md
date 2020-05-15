# Marlin 3D Printer Firmware for Flying Bear 4S

## Версия с тестовой поддержкой WIFI модуля

Это конфигурация [официального Marlin](https://github.com/MarlinFirmware/Marlin) для принтера Flying Bear Ghost 4S.
Эта ветка содержит код для работы с WIFI модулем, установленным в FB4S. Загрузка файлов через стандартный plugin в Cura.

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
* Работает только с картами стандарта SDHC и новее. Это все карты от 4Гб и больше.
* Отображение состояния принтера (печатает, не печатает) в Cura
* Все остальное, что не в указано в "работает"

## Как работает, как настроить

### Как собрать прошивку самому

Видео Дмитрия Соркина [youtube](https://www.youtube.com/watch?v=HirIZk0rWOQ)

Нужная плата, robin nano, уже выбрана в качестве платы по-умолчанию. В меню Platformio можно не выбирать плату, а нажать Build на самом верху. Или использовать сочетание клавиш Ctrl+Alt+B.

После компиляции, готовая прошивка лежит в .pio/build/mks_robin_nano/Robin_nano35.bin

### Что нужно настроить

Нужно настроить направления движения по осям под свои драйвера в файле [Configuration.h](./Marlin/Configuration.h) (параметры INVERT_?_DIR, строка 1071). По умолчанию стоят настройки под драйвера 2208.

### Если нет желания самому собирать прошивку

Готовые файлы лежат в папке firmware.

Если вы используете драйвера 2208, или аналогичные, прошивка в папке 2208 [Robin_nano35.bin](./firmware/2208/Robin_nano35.bin)

Если вы используете стандартные драйвера, прошивка в папке std [Robin_nano35.bin](./firmware/std/Robin_nano35.bin)

Отличия сборок только в инвертировании осей.

### Настройки WIFI, если вы используете готовую прошивку

Если модуль уже был настроен, то возможно никакая настройка не понадобится. Если модуль не был настроен, либо по какой-то причине не смог подключиться к сети, то он запустится в режиме точки доступа с именем сети MKSWIFI??? (вместо ? будут произвольные символы). Подключитесь к этой сети, откройте страницу по адресу 192.168.4.1 и установите нужные настройки.

### Настройки WIFI, если вы собираете прошивку сами

В файле [mks_wifi_settings.h](./Marlin/src/module/mks_wifi/mks_wifi_settings.h)

Для того, чтобы эти настройки применялись при включении, "MKS_WIFI_ENABLED_WIFI_CONFIG" должен быть раскоментирован. Если закоментировать "#define MKS_WIFI_ENABLED_WIFI_CONFIG", при запуске настройки ESP модулю отправляться не будут

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

В качестве места хренения EEPROM в Marlin доступны несколько вариантов:

* SD карта. Этот вариант наиболее предпочтительный, если нет осознанного желания хранить EEPROM где-то еще.

Для включения в [Configuration.h](./Marlin/Configuration.h) в разделе EEPROM должно быть включено SDCARD_EEPROM_EMULATION и отключены другие опции хранения. Пример:

```C
#define EEPROM_SETTINGS     // Persistent storage with M500 and M501
#define EEPROM_CHITCHAT       // Give feedback on EEPROM commands. Disable to save PROGMEM.
#if ENABLED(EEPROM_SETTINGS)
#define SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
//#define USE_WIRED_EEPROM    1
//#define I2C_EEPROM_AT24C16
//#define E2END (2*1024 - 1)
#define EEPROM_AUTO_INIT  // Init EEPROM automatically on any errors.
#endif
```

* I2C EEPROM Для включения нужно включить I2C_EEPROM_AT24C16 и установить USE_WIRED_EEPROM и задать размер EEPROM в E2END, а остальные опции отключить. Пример:

```C
#define EEPROM_SETTINGS     // Persistent storage with M500 and M501
#define EEPROM_CHITCHAT       // Give feedback on EEPROM commands. Disable to save PROGMEM.
#if ENABLED(EEPROM_SETTINGS)
#undef SDCARD_EEPROM_EMULATION
#undef USE_REAL_EEPROM
#undef FLASH_EEPROM_EMULATION
#undef SRAM_EEPROM_EMULATION
#define USE_WIRED_EEPROM    1
#define I2C_EEPROM_AT24C16
#define E2END (2*1024 - 1)
#define EEPROM_AUTO_INIT  // Init EEPROM automatically on any errors.
#endif
```

При первом включении все содержимое AT24C16 будет переписано. Память не быстрая, поэтому процесс занимает до 10 секунд. В дальнейшем в память пишутся только измененные значения, поэтому работает быстрее.

* SPI_EEPROM  Хранение в памяти подключенной по SPI. Этот вариант пока не работает.
* FLASH_EEPROM_EMULATION Это хранение EEPROM в flash памяти STM32. Этот вариант не работает.
* SRAM_EEPROM_EMULATION  Этот вариант не работает.

### Работа с Octoprint

При работе с Octoprint через Uart возможны проблемы при печати. Рекомендуется, увеличить буферы команд в настройках Marlin [Configuration_adv.h](./Marlin/Configuration_adv.h):

```C
#define MAX_CMD_SIZE 96 //Максимальный размер команды
#define BUFSIZE 32 //Количество команд, которые стоят в плане.
#define TX_BUFFER_SIZE 256 //Размер буфера для отправки
#define RX_BUFFER_SIZE 2048 //Размер буфера для приема
```

Процесс получения данных и UART организован следующим образом:

* используется аппаратный UART STM32
* включено прерывание по приему каждого байта, используется библиотека libmaple, файл .platformio/packages/framework-arduinoststm32-maple/STM32F1/system/libmaple/usart_private.h:

```C
__weak void __irq_usart1(void) {
    usart_irq(&usart1_rb, &usart1_wb, USART1_BASE);
}
```

В обработчике usart_irq (в файле .platformio/packages/framework-arduinoststm32-maple/STM32F1/system/libmaple/usart_private.h) пришедший байт помещается в буфер функцией

```C
rb_push_insert(rb, (uint8)regs->DR);
```

rb имеет тип структуры ring_buffer:

```C
typedef struct ring_buffer {
    volatile uint8 *buf; /**< Buffer items are stored into */
    volatile uint16 head;         /**< Index of the next item to remove */
    volatile uint16 tail;         /**< Index where the next item will get inserted */
    volatile uint16 size;         /**< Buffer capacity minus one */
} ring_buffer;
```

Сам приемный буфер и его размер задается в .platformio/packages/framework-arduinoststm32-maple/STM32F1/system/libmaple/include/libmaple/usart.h:

```C
typedef struct usart_dev {
    usart_reg_map *regs;             /**< Register map */
    ring_buffer *rb;                 /**< RX ring buffer */
    ring_buffer *wb;                 /**< TX ring buffer */
    uint32 max_baud;                 /**< @brief Deprecated.
                                      * Maximum baud rate. */
    uint8 rx_buf[USART_RX_BUF_SIZE]; /**< @brief Deprecated.
                                      * Actual RX buffer used by rb.
                                      * This field will be removed in
                                      * a future release. */
    uint8 tx_buf[USART_TX_BUF_SIZE]; /**< Actual TX buffer used by wb */
    rcc_clk_id clk_id;               /**< RCC clock information */
    nvic_irq_num irq_num;            /**< USART NVIC interrupt */
} usart_dev;
```

Размер массива задан при помощи USART_RX_BUF_SIZE и USART_TX_BUF_SIZE:

```C
#ifndef USART_RX_BUF_SIZE
#define USART_RX_BUF_SIZE               64
#endif

#ifndef USART_TX_BUF_SIZE
#define USART_TX_BUF_SIZE               64
#endif
```

Для успешной работы Octoprint возможно имеет смысл увеличить эти значения. Например до 1024. Это предположение не тестировалось на практике. Возможно, одновременно с увеличением размера буферов в драйвере поможет и увеличение скорости UART до 250000.

* Marlin периодически проверяет, есть ли у драйвера в буфере данные, забирает их оттуда и складывает в свой буфер, который задан RX_BUFFER_SIZE.
