/*
 * Copyright (c) 2015-2017 USI Co. Ltd.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of USI Co. Ltd.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of USI Co. Ltd..
 */

/** @file
 * Defines peripherals available for use on BCMUSI22 board
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
/*
BCMUSI22 platform pin definitions ...
+--------------------------------------------------------------------------------------------------------+
| Enum ID       |Pin |   Pin Name on    |    Module     | STM32| Peripheral  |    Board     | Peripheral  |
|               | #  |      Module      |  GPIO Alias   | Port | Available   |  Connection  |   Alias     |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_1  | 74 | UART_CTS         | USART2_CTS    | A  0 | GPIO        |              | WKUP1       |
|               |    |                  |               |      | TIM2_CH1    |              | ADC1_0      |
|               |    |                  |               |      | TIM2_ETR    |              |             |
|               |    |                  |               |      | TIM5_CH1    |              |             |
|               |    |                  |               |      | TIM8_ETR    |              |             |
|               |    |                  |               |      | USART2_CTS  |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_2  | 75 | UART_RTS         | USART2_RTS    | A  1 | GPIO        |              | ADC1_1      |
|               |    |                  |               |      | TIM2_CH2    |              |             |
|               |    |                  |               |      | TIM5_CH2    |              |             |
|               |    |                  |               |      | SPI4_MOSI   |              |             |
|               |    |                  |               |      | USART2_RTS  |              |             |
|               |    |                  |               |      | QSPI1_IO3   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_3  | 76 | UART_TX          | USART2_TX     | A  2 | GPIO        |              | ADC1_2      |
|               |    |                  |               |      | TIM2_CH3    |              |             |
|               |    |                  |               |      | TIM5_CH3    |              |             |
|               |    |                  |               |      | I2S2_CKIN   |              |             |
|               |    |                  |               |      | USART2_TX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_4  | 77 | UART_RX          | USART2_RX     | A  3 | GPIO        |              | ADC1_3      |
|               |    |                  |               |      | TIM2_CH4    |              |             |
|               |    |                  |               |      | TIM5_CH4    |              |             |
|               |    |                  |               |      | I2S2_MCK    |              |             |
|               |    |                  |               |      | USART2_RX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_5  |  2 | M_I2S_WS         | M_I2S3_WS     | A  4 | GPIO        |              | ADC1_4      |
|               |    |                  |               |      | SPI1_NSS    |              |             |
|               |    |                  |               |      | I2S1_WS     |              |             |
|               |    |                  |               |      | SPI3_NSS    |              |             |
|               |    |                  |               |      | I2S3_WS     |              |             |
|               |    |                  |               |      | USART2_CK   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_6  |  8 | MICRO_GPIO_0     | GPIO_0        | A  5 | GPIO        | LED1         | ADC1_5      |
|               |    |                  |               |      | TIM2_CH1    |              |             |
|               |    |                  |               |      | TIM2_ETR    |              |             |
|               |    |                  |               |      | TIM8_CH1N   |              |             |
|               |    |                  |               |      | SPI1_SCK    |              |             |
|               |    |                  |               |      | I2S1_CK     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_7  | 36 | qSPI_IO0         | EXT_QSPI_IO0  | A  6 | GPIO        |              | ADC1_6      |
|               |    |                  |               |      | TIM1_BKIN   |              |             |
|               |    |                  |               |      | TIM3_CH1    |              |             |
|               |    |                  |               |      | TIM8_BKIN   |              |             |
|               |    |                  |               |      | SPI1_MISO   |              |             |
|               |    |                  |               |      | I2S2_MCK    |              |             |
|               |    |                  |               |      | QSPI2_IO0   |              |             |
|               |    |                  |               |      | SDIO_CMD    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_8  | 31 | qSPI_IO1         | EXT_QSPI_IO1  | A  7 | GPIO        |              | ADC1_7      |
|               |    |                  |               |      | TIM1_CH1N   |              |             |
|               |    |                  |               |      | TIM3_CH2    |              |             |
|               |    |                  |               |      | TIM8_CH1N   |              |             |
|               |    |                  |               |      | SPI1_MOSI   |              |             |
|               |    |                  |               |      | I2S1_SD     |              |             |
|               |    |                  |               |      | QSPI2_IO1   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
|               |    |                  | MCO_32K_OUT   | A  8 | GPIO        |              | MCO_32K_OUT |
|               |    |                  |               |      | MCO_1       |              |             |
|               |    |                  |               |      | TIM1_CH1    |              |             |
|               |    |                  |               |      | I2C3_SCL    |              |             |
|               |    |                  |               |      | USART1_CK   |              |             |
|               |    |                  |               |      | USB_FS_SOF  |              |             |
|               |    |                  |               |      | SDIO_D1     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_9  | 39 | MICRO_UART_TX    | USART1_TX     | A  9 | GPIO        |              |             |
|               |    |                  |               |      | TIM1_CH2    |              |             |
|               |    |                  |               |      | I2C3_SMB    |              |             |
|               |    |                  |               |      | USART1_TX   |              |             |
|               |    |                  |               |      | USB_FS_VBUS |              |             |
|               |    |                  |               |      | SDIO_D2     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_10 | 38 | MICRO_UART_RX    | USART1_RX     | A 10 | GPIO        |              |             |
|               |    |                  |               |      | TIM1_CH3    |              |             |
|               |    |                  |               |      | SPI5_MOSI   |              |             |
|               |    |                  |               |      | I2S5_SD     |              |             |
|               |    |                  |               |      | USART1_RX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_11 | 52 | MICRO_USB_HS_DN  | USB_DM        | A 11 | GPIO        |              | USB_DM      |
|               |    |                  |               |      | TIM1_CH4    |              |             |
|               |    |                  |               |      | SPI4_MISO   |              |             |
|               |    |                  |               |      | USART1_CTS  |              |             |
|               |    |                  |               |      | USART6_TX   |              |             |
|               |    |                  |               |      | USB_FS_DM   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_12 | 51 | MICRO_USB_HS_DP  | USB_DP        | A 12 | GPIO        |              | USB_DP      |
|               |    |                  |               |      | TIM1_ETR    |              |             |
|               |    |                  |               |      | SPI5_MISO   |              |             |
|               |    |                  |               |      | USART1_RTS  |              |             |
|               |    |                  |               |      | USART6_RX   |              |             |
|               |    |                  |               |      | USB_FS_DP   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_13 | 44 | MICRO_JTAG_TMS   | SYS_JTMS_SWDIO| A 13 | JTMS-SWDIO  |              | SWDIO       |
|               |    |                  |               |      | GPIO        |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_14 | 40 | MICRO_JTAG_TCK   | SYS_JTCK_SWCLK| A 14 | JTCK-SWCLK  |              | SWCLK       |
|               |    |                  |               |      | GPIO        |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_15 | 43 | JTAG_TDI_GPIO6   | JTDI_GPIO_6   | A 15 | JTDI        |              |             |
|               |    |                  |               |      | GPIO        |              |             |
|               |    |                  |               |      | TIM2_CH1    |              |             |
|               |    |                  |               |      | SPI1_NSS    |              |             |
|               |    |                  |               |      | I2S1_WS     |              |             |
|               |    |                  |               |      | SPI3_NSS    |              |             |
|               |    |                  |               |      | I2S3_WS     |              |             |
|               |    |                  |               |      | USART1_TX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_16 |  7 | MICRO_GPIO_1     | GPIO_1        | B  0 | GPIO        | LED2         | ADC1_8      |
|               |    |                  |               |      | TIM1_CH2N   |              |             |
|               |    |                  |               |      | TIM3_CH3    |              |             |
|               |    |                  |               |      | TIM8_CH2N   |              |             |
|               |    |                  |               |      | SPI5_SCK    |              |             |
|               |    |                  |               |      | I2S5_CK     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_17 |  6 | MICRO_GPIO_2     | GPIO_2        | B  1 | GPIO        |              | ADC1_9      |
|               |    |                  |               |      | TIM1_CH3N   |              |             |
|               |    |                  |               |      | TIM2_CH4    |              |             |
|               |    |                  |               |      | TIM8_CH3N   |              |             |
|               |    |                  |               |      | SPI5_NSS    |              |             |
|               |    |                  |               |      | I2S5_WS     |              |             |
|               |    |                  |               |      | QSPI_CLK    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_18 | 35 | qSPI_CLK         | EXT_SQPI_CLK  | B  2 | GPIO        |              |             |
|               |    |                  |               |      | QSPI_CLK    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_19 | 41 | MICRO_GPIO_4     | JTDO_GPIO_4   | B  3 | JTDO        |              |             |
|               |    |                  |               |      | GPIO        |              |             |
|               |    |                  |               |      | TIM2_CH2    |              |             |
|               |    |                  |               |      | I2C4_SDA    |              |             |
|               |    |                  |               |      | SPI1_SCK    |              |             |
|               |    |                  |               |      | I2S1_CK     |              |             |
|               |    |                  |               |      | SPI3_SCK    |              |             |
|               |    |                  |               |      | I2S3_CK     |              |             |
|               |    |                  |               |      | USART1_RX   |              |             |
|               |    |                  |               |      | I2C2_SDA    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_20 | 42 | MICRO_GPIO_5     | JTRST_GPIO_5  | B  4 | JTRST       |              |             |
|               |    |                  |               |      | GPIO        |              |             |
|               |    |                  |               |      | TIM3_CH1    |              |             |
|               |    |                  |               |      | SPI1_MISO   |              |             |
|               |    |                  |               |      | SPI3_MISO   |              |             |
|               |    |                  |               |      | I2S3ext_SD  |              |             |
|               |    |                  |               |      | I2C3_SDA    |              |             |
|               |    |                  |               |      | SDIO_D0     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_21 |    |                  | SDIO_D3       | B  5 | GPIO        |              | SDIO_D3     |
|               |    |                  |               |      | TIM3_CH2    |              |             |
|               |    |                  |               |      | SPI1_MOSI   |              |             |
|               |    |                  |               |      | I2S1_SD     |              |             |
|               |    |                  |               |      | SPI3_MOSI   |              |             |
|               |    |                  |               |      | I2S3_SD     |              |             |
|               |    |                  |               |      | SDIO_D3     |              |             |
+---------------+----+------------------+----------------------+-------------+--------------+-------------+
| WICED_GPIO_22 |    |                  | BT_REG_ON     | B  6 | GPIO        |              | BT_REG_ON   |
|               |    | /AUTH_SCL        | /AUTH_SCL     |      | TIM4_CH1    |              | /I2C1_SCL   |
|               |    |                  |               |      | I2C1_SCL    |              |             |
|               |    |                  |               |      | USART1_TX   |              |             |
|               |    |                  |               |      | QSPI1_NCS   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_23 |    |                  | WL_REG_ON     | B  7 | GPIO        |              | WL_REG_ON   |
|               |    | /AUTH_SDA        | /AUTH_SDA     |      | TIM4_CH2    |              | /I2C1_SDA   |
|               |    |                  |               |      | I2C1_SDA    |              |             |
|               |    |                  |               |      | USART1_RX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_24 |    |                  | BT_DEV_WKUP   | B  8 | GPIO        |              | BT_DEV_WKUP |
|               |    |                  |               |      | TIM4_CH3    |              |             |
|               |    |                  |               |      | I2C1_SCL    |              |             |
|               |    |                  |               |      | SPI5_MOSI   |              |             |
|               |    |                  |               |      | I2S5_SD     |              |             |
|               |    |                  |               |      | I2C3_SDA    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_25 | 22 | MICRO_SPI_NSS    | SPI2_NSS      | B  9 | GPIO        |              |             |
|               |    |                  |               |      | TIM4_CH4    |              |             |
|               |    |                  |               |      | I2C1_SDA    |              |             |
|               |    |                  |               |      | SPI2_NSS    |              |             |
|               |    |                  |               |      | I2S2_WS     |              |             |
|               |    |                  |               |      | I2C2_SDA    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_26 |  3 | M_I2S_MCK        | M_I2S3_MCK    | B 10 | GPIO        |              |             |
|               |    |                  |               |      | TIM2_CH3    |              |             |
|               |    |                  |               |      | I2C2_SCL    |              |             |
|               |    |                  |               |      | SPI2_SCK    |              |             |
|               |    |                  |               |      | I2S2_CK     |              |             |
|               |    |                  |               |      | I2S3_MCK    |              |             |
|               |    |                  |               |      | USART3_TX   |              |             |
|               |    |                  |               |      | I2C4_SCL    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_28 |  1 | M_I2S_CK         | M_I2S3_CK     | B 12 | GPIO        |              |             |
|               |    |                  |               |      | TIM1_BKIN   |              |             |
|               |    |                  |               |      | I2C2_SMB    |              |             |
|               |    |                  |               |      | SPI2_NSS    |              |             |
|               |    |                  |               |      | I2S2_WS     |              |             |
|               |    |                  |               |      | SPI4_NSS    |              |             |
|               |    |                  |               |      | I2S4_WS     |              |             |
|               |    |                  |               |      | SPI3_SCK    |              |             |
|               |    |                  |               |      | I2S3_CK     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_29 | 24 | MICRO_SPI_CK     | SPI2_SCK      | B 13 | GPIO        |              |             |
|               |    |                  |               |      | TIM1_CH1N   |              |             |
|               |    |                  |               |      | I2C4_SMB    |              |             |
|               |    |                  |               |      | SPI2_SCK    |              |             |
|               |    |                  |               |      | I2S2_CK     |              |             |
|               |    |                  |               |      | SPI4_SCK    |              |             |
|               |    |                  |               |      | I2S4_CK     |              |             |
|               |    |                  |               |      | USART3_CTS  |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_30 | 53 | MICRO_GPIO_7     | GPIO_7        | B 14 | GPIO        |              |             |
|               |    |                  |               |      | TIM1_CH2N   |              |             |
|               |    |                  |               |      | TIM8_CH2N   |              |             |
|               |    |                  |               |      | I2C4_SDA    |              |             |
|               |    |                  |               |      | SPI2_MISO   |              |             |
|               |    |                  |               |      | I2S2ext_SD  |              |             |
|               |    |                  |               |      | USART3_RTS  |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_31 |    |                  | SDIO_CLK      | B 15 | GPIO        |              | SDIO_CK     |
|               |    |                  |               |      | TIM1_CH3N   |              | RTC_REFIN   |
|               |    |                  |               |      | TIM8_CH3N   |              |             |
|               |    |                  |               |      | I2C4_SCL    |              |             |
|               |    |                  |               |      | SPI2_MOSI   |              |             |
|               |    |                  |               |      | I2S2_SD     |              |             |
|               |    |                  |               |      | SDIO_CK     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_32 | 27 | MICRO_WKUP       | MICRO_KWUP    | C  0 | GPIO        |              | WKUP2       |
|               |    |                  |               |      |             |              | ADC1_10     |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_33 |    | WL_HOST_WKUP     | WL_HOST_WKUP  | C  1 | GPIO        |              | WL_HOST_WKUP|
|               |    |                  |               |      |             |              | WKUP3       |
|               |    |                  |               |      |             |              | ADC1_11     |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_34 | 25 | MICRO_SPI_MISO   | SPI2_MISO     | C  2 | GPIO        |              | ADC1_12     |
|               |    |                  |               |      | SPI2_MISO   |              |             |
|               |    |                  |               |      | ADC1_12     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_35 | 23 | MICRO_SPI_MOSI   | SPI2_MOSI     | C  3 | GPIO        |              | ADC1_13     |
|               |    |                  |               |      | SPI2_MOSI   |              |             |
|               |    |                  |               |      | I2S2_SD     |              |             |
|               |    |                  |               |      | ADC1_13     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_36 | 32 | qSPI_IO2         | EXT_QSPI_IO2  | C  4 | GPIO        |              | ADC1_14     |
|               |    |                  |               |      | I2S1_MCK    |              |             |
|               |    |                  |               |      | QSPI2_IO2   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_37 | 34 | qSPI_IO3         | EXT_QSPI_IO3  | C  5 | GPIO        |              | ADC1_15     |
|               |    |                  |               |      | I2C4_SMB    |              |             |
|               |    |                  |               |      | USART3_RX   |              |             |
|               |    |                  |               |      | QSPI2_IO2   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_38 | 10 | AUTH_SCL         | AUTH_SCL      | C  6 | GPIO        |              | I2CFMP1_SCL |
|               |    |                  | /BT_REG_ON    |      | TIM3_CH1    |              | /BT_REG_ON  |
|               |    |                  |               |      | TIM8_CH1    |              |             |
|               |    |                  |               |      | I2C4_SCL    |              |             |
|               |    |                  |               |      | I2S2_MCK    |              |             |
|               |    |                  |               |      | USART6_TX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_39 | 11 | AUTH_SDA         | AUTH_SDA      | C  7 | GPIO        |              | I2CFMP1_SDA |
|               |    |                  | /WL_REG_ON    |      | TIM3_CH2    |              | /WL_REG_ON  |
|               |    |                  |               |      | TIM8_CH2    |              |             |
|               |    |                  |               |      | I2C4_SDA    |              |             |
|               |    |                  |               |      | SPI2_SCK    |              |             |
|               |    |                  |               |      | I2S2_CK     |              |             |
|               |    |                  |               |      | I2S3_MCK    |              |             |
|               |    |                  |               |      | USART6_RX   |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_40 |    |                  | SDIO_D0       | C  8 | GPIO        |              | SDIO_D0     |
|               |    |                  |               |      | TIM3_CH3    |              |             |
|               |    |                  |               |      | TIM8_CH3    |              |             |
|               |    |                  |               |      | USART6_CK   |              |             |
|               |    |                  |               |      | QSPI1_IO1   |              |             |
|               |    |                  |               |      | SDIO_D0     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_41 |    |                  | SDIO_D1       | C  9 | GPIO        |              | SDIO_D1     |
|               |    |                  |               |      | TIM3_CH4    |              | MCO_2       |
|               |    |                  |               |      | TIM8_CH4    |              |             |
|               |    |                  |               |      | I2C3_SDA    |              |             |
|               |    |                  |               |      | I2S2_CKIN   |              |             |
|               |    |                  |               |      | QSPI1_IO0   |              |             |
|               |    |                  |               |      | SDIO_D1     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_42 |    |                  | SDIO_D2       | C 10 | GPIO        |              |             |
|               |    |                  |               |      | SPI3_SCK    |              |             |
|               |    |                  |               |      | I2S3_CK     |              |             |
|               |    |                  |               |      | USART3_TX   |              |             |
|               |    |                  |               |      | QSPI1_IO1   |              |             |
|               |    |                  |               |      | SDIO_D2     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_43 | 33 | EXT_QSPI_NCS     | qSPI_NCS      | C 11 | GPIO        |              |             |
|               |    |                  |               |      | I2S3ext_SD  |              |             |
|               |    |                  |               |      | SPI3_MISO   |              |             |
|               |    |                  |               |      | USART3_RX   |              |             |
|               |    |                  |               |      | QSPI2_NCS   |              |             |
|               |    |                  |               |      | SDIO_D3     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_44 |  4 | M_I2S_SD         | M_I2S3_SD     | C 12 | GPIO        |              |             |
|               |    |                  |               |      | SPI3_MOSI   |              |             |
|               |    |                  |               |      | I2S3_SD     |              |             |
|               |    |                  |               |      | USART3_CK   |              |             |
|               |    |                  |               |      | SDIO_CK     |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_45 |  9 | AUTH_RST         | AUTH_RST      | C 13 | GPIO        |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_46 | 69 |                  | 32K_IN        | C 14 | GPIO        |              | 32K_IN      |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_47 |  5 | MICRO_GPIO_3     | GPIO_3        | C 15 | GPIO        |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
| WICED_GPIO_48 |    | SDIO_CMD         | SDIO_CMD      | D  2 | GPIO        |              | SDIO_CMD    |
|               |    |                  |               |      | SDIO_CMD    |              |             |
|---------------+----+------------------+---------------+------+-------------+--------------+-------------|
Notes
1. These mappings are defined in <WICED-SDK>/platforms/BCMUSI22/platform.c
2. STM32F4xx Datasheet  -> TBD
3. STM32F4xx Ref Manual -> TBD
*/

/******************************************************
 *                   Enumerations
 ******************************************************/

typedef enum
{
    WICED_GPIO_1,
    WICED_GPIO_2,
    WICED_GPIO_3,
    WICED_GPIO_4,
    WICED_GPIO_5,
    WICED_GPIO_6,
    WICED_GPIO_7,
    WICED_GPIO_8,
    WICED_GPIO_9,
    WICED_GPIO_10,
    WICED_GPIO_11,
    WICED_GPIO_12,
    WICED_GPIO_13,
    WICED_GPIO_14,
    WICED_GPIO_15,
    WICED_GPIO_16,
    WICED_GPIO_17,
    WICED_GPIO_18,
    WICED_GPIO_19,
    WICED_GPIO_20,
    WICED_GPIO_21,
    WICED_GPIO_22,
    WICED_GPIO_23,
    WICED_GPIO_24,
    WICED_GPIO_25,
    WICED_GPIO_26,
    WICED_GPIO_27,
    WICED_GPIO_28,
    WICED_GPIO_29,
    WICED_GPIO_30,
    WICED_GPIO_31,
    WICED_GPIO_32,
    WICED_GPIO_33,
    WICED_GPIO_34,
    WICED_GPIO_35,
    WICED_GPIO_36,
    WICED_GPIO_37,
    WICED_GPIO_38,
    WICED_GPIO_39,
    WICED_GPIO_40,
    WICED_GPIO_41,
    WICED_GPIO_42,
    WICED_GPIO_43,
    WICED_GPIO_44,
    WICED_GPIO_45,
    WICED_GPIO_46,
    WICED_GPIO_47,
    WICED_GPIO_48,
    WICED_GPIO_MAX, /* Denotes the total number of GPIO port aliases. Not a valid GPIO alias */
    WICED_GPIO_32BIT = 0x7FFFFFFF,
} wiced_gpio_t;

typedef enum
{
    WICED_SPI_1,
    WICED_SPI_2,
    WICED_SPI_MAX, /* Denotes the total number of SPI port aliases. Not a valid SPI alias */
    WICED_SPI_32BIT = 0x7FFFFFFF,
} wiced_spi_t;

typedef enum
{
    WICED_I2C_1,
#if defined(SPLIT_I2C_CONFIG)
    WICED_I2C_2,
#endif /* SPLIT_I2C_CONFIG */
    WICED_I2C_MAX,
    WICED_I2C_32BIT = 0x7FFFFFFF,
} wiced_i2c_t;

typedef enum
{
    WICED_I2S_1,
    WICED_I2S_MAX, /* Denotes the total number of I2S port aliases.  Not a valid I2S alias */
    WICED_I2S_32BIT = 0x7FFFFFFF
} wiced_i2s_t;

typedef enum
{
    WICED_PWM_1,
    WICED_PWM_2,
    WICED_PWM_3,
    WICED_PWM_4,
    WICED_PWM_5,
    WICED_PWM_6,
    WICED_PWM_7,
    WICED_PWM_8,
    WICED_PWM_9,
    WICED_PWM_MAX, /* Denotes the total number of PWM port aliases. Not a valid PWM alias */
    WICED_PWM_32BIT = 0x7FFFFFFF,
} wiced_pwm_t;

typedef enum
{
	WICED_ADC_0,
    WICED_ADC_1,
    WICED_ADC_2,
    WICED_ADC_3,
    WICED_ADC_MAX, /* Denotes the total number of ADC port aliases. Not a valid ADC alias */
    WICED_ADC_32BIT = 0x7FFFFFFF,
} wiced_adc_t;

typedef enum
{
    WICED_UART_1,
    WICED_UART_2,
    WICED_UART_3,
    WICED_UART_MAX, /* Denotes the total number of UART port aliases. Not a valid UART alias */
    WICED_UART_32BIT = 0x7FFFFFFF,
} wiced_uart_t;

/* Logical Button-ids which map to phyiscal buttons on the board */
typedef enum
{
    PLATFORM_BUTTON_1,
    PLATFORM_BUTTON_2,
    PLATFORM_BUTTON_MAX, /* Denotes the total number of Buttons on the board. Not a valid Button Alias */
} platform_button_t;

/* Logical LED-ids which map to phyiscal gpio LEDs on the board (see platform_gpio_leds[] in platform.c)*/
typedef enum
{
    PLATFORM_LED_1,
    PLATFORM_LED_2,
	PLATFORM_LED_3,
	PLATFORM_LED_4,
    PLATFORM_LED_MAX, /* Denotes the total number of LEDs on the board. Not a valid alias */
} platform_led_t;

/******************************************************
 *                    Constants
 ******************************************************/

#define WICED_PLATFORM_BUTTON_COUNT  ( 2 )

/* UART port used for standard I/O */
#ifdef STDIO_UART_PORT3
#define STDIO_UART ( WICED_UART_3)  // Erick+ for thermal test
#else
#define STDIO_UART ( WICED_UART_1 )
#endif

#define WICED_GPIO_AUTH_RST ( WICED_GPIO_45 )	/* PC13 */

/* external SPI flash */
#define WICED_PLATFORM_INCLUDES_SPI_FLASH
#define WICED_SPI_FLASH_CS ( WICED_GPIO_25 )

/* Components connected to external I/Os */
#define PLATFORM_LED_COUNT               (4)
#define WICED_LED1         ( WICED_GPIO_6 )
#define WICED_LED2         ( WICED_GPIO_16 )
#define WICED_LED3         ( WICED_GPIO_17 )
#define WICED_LED4         ( WICED_GPIO_30 )
// WISE-1530 define
#define	CB_PWR_ON		   (WICED_LED3)
#define	nCB_RESET_OUT	   (WICED_LED4)

#define WICED_LED1_ON_STATE  ( WICED_ACTIVE_HIGH )
#define WICED_LED2_ON_STATE  ( WICED_ACTIVE_HIGH )
#define WICED_LED3_ON_STATE  ( WICED_ACTIVE_HIGH )
#define WICED_LED4_ON_STATE  ( WICED_ACTIVE_HIGH )

#define WICED_PLATFORM_MAX_BUTTON  (1)
#define WICED_BUTTON1      ( WICED_GPIO_32 )
#define WICED_BUTTON2      ( WICED_GPIO_47 )
#define WICED_BUTTON_WKUP  ( WICED_GPIO_32 )
#define WICED_THERMISTOR   ( WICED_GPIO_17 )

/* I/O connection <-> Peripheral Connections */
#define WICED_LED1_JOINS_PWM        ( WICED_PWM_1 )
#define WICED_LED2_JOINS_PWM        ( WICED_PWM_7 )
#define WICED_THERMISTOR_JOINS_ADC  ( WICED_ADC_3 )

/* Bootloader OTA and OTA2 factory reset during settings */
#define PLATFORM_FACTORY_RESET_BUTTON_INDEX     ( PLATFORM_BUTTON_1 )
#define PLATFORM_FACTORY_RESET_TIMEOUT          ( 10000 )

/* Generic button checking defines */
#define PLATFORM_BUTTON_PRESS_CHECK_PERIOD      ( 100 )
#define PLATFORM_BUTTON_PRESSED_STATE           (   0 )

#define PLATFORM_GREEN_LED_INDEX                ( WICED_LED_INDEX_2 )
#define PLATFORM_RED_LED_INDEX                  ( WICED_LED_INDEX_1 )

#ifdef __cplusplus
} /*extern "C" */
#endif
