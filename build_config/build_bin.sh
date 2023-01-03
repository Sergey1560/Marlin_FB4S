#!/bin/bash

PIO_PATH="~/.platformio/penv/bin/pio"
PIO_PARAM="run -s"
PIO_CONFIG_PATH="./build_config"

BIN_DIR="./build_bin"
BIN_F103_DIR="stm32f103_boards"
BIN_F407_DIR="stm32f407_boards"

RN_PATH_F1="./.pio/build/mks_robin_nano_v1v2/Robin_nano35.bin"
RN_PATH_F4="./.pio/build/mks_robin_nano_v1_3_f4/Robin_nano35.bin"

echo "Clean bin dir"
rm -rf ${BIN_DIR}

echo "Mkdir struct"
mkdir ${BIN_DIR}
mkdir -p ${BIN_DIR}/{${BIN_F103_DIR},${BIN_F407_DIR}}
mkdir -p ${BIN_DIR}/${BIN_F103_DIR}/{reborn_v3,robin_nano_v1_1}
mkdir ${BIN_DIR}/${BIN_F103_DIR}/robin_nano_v1_1/{fb_4s,fb4s_all_drv_2208,fb_5,fb5_all_drv_2208}
mkdir ${BIN_DIR}/${BIN_F407_DIR}/{robin_nano_1_3_A4988_TMC,robin_nano_1_3_TMC,robin_nano_s_1_3,robin_nano_s_1_3_with_2209}

echo "STM32F4 Boards"
echo " - Robin Nano 1.3 s"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rn13_s.ini
cp ${RN_PATH_F4}  ${BIN_DIR}/${BIN_F407_DIR}/robin_nano_s_1_3

echo " - Robin Nano 1.3 s + 2209"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rn13_s_2209.ini
cp ${RN_PATH_F4}  ${BIN_DIR}/${BIN_F407_DIR}/robin_nano_s_1_3_with_2209

echo " - Robin Nano 1.3 ALL 2209"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rn13_tmc.ini
cp ${RN_PATH_F4}  ${BIN_DIR}/${BIN_F407_DIR}/robin_nano_1_3_TMC

echo " - Robin Nano 1.3 A4988 + 2209"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rn13_a4988_tmc.ini
cp ${RN_PATH_F4}  ${BIN_DIR}/${BIN_F407_DIR}/robin_nano_1_3_A4988_TMC


echo "STM32F1 Boards"
echo " - Robin Nano 1.1 FB4s stock"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb4_rn_11_a4988.ini
cp ${RN_PATH_F1}  ${BIN_DIR}/${BIN_F103_DIR}/fb_4s

echo " - Robin Nano 1.1 FB4s 2208"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb4_rn_11_2208.ini
cp ${RN_PATH_F1}  ${BIN_DIR}/${BIN_F103_DIR}/fb4s_all_drv_2208

echo " - Robin Nano 1.1 FB5 stock"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rn_11_a4988.ini
cp ${RN_PATH_F1}  ${BIN_DIR}/${BIN_F103_DIR}/fb_5

echo " - Robin Nano 1.1 FB5 2208"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rn_11_2208.ini
cp ${RN_PATH_F1}  ${BIN_DIR}/${BIN_F103_DIR}/fb5_all_drv_2208

echo " - Reborn 3.0"
${PIO_PATH} ${PIO_PARAM} -c ${PIO_CONFIG_PATH}/platformio_fb5_rb_30.ini
cp ${RN_PATH_F1}  ${BIN_DIR}/${BIN_F103_DIR}/reborn_v3

