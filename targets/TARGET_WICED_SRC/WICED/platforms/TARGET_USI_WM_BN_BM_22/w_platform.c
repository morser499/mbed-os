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
 * Defines board support package for BCMUSI22 WM-BN-BM-22 common portion for V1.0 and V1.1
  */
#include "w_platform.h"
#include "w_platform_config.h"
#include "w_platform_init.h"
#include "w_platform_isr.h"
#include "w_platform_peripheral.h"
#include "w_platform_bluetooth.h"
#include "wwd_platform_common.h"
#include "wwd_rtos_isr.h"
#include "wiced_defaults.h"
#include "wiced_platform.h"
#include "w_platform_mfi.h"
#include "w_platform_button.h"
#include "w_gpio_button.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/

/******************************************************
 *               Variable Definitions
 ******************************************************/

/* GPIO pin table. Used by WICED/platform/MCU/wiced_platform_common.c */
const platform_gpio_t platform_gpio_pins[] =
{
    [WICED_GPIO_1]  = { GPIOA,  0 },
    [WICED_GPIO_2]  = { GPIOA,  1 },
    [WICED_GPIO_3]  = { GPIOA,  2 },
    [WICED_GPIO_4]  = { GPIOA,  3 },
    [WICED_GPIO_5]  = { GPIOA,  4 },
    [WICED_GPIO_6]  = { GPIOA,  5 },
    [WICED_GPIO_7]  = { GPIOA,  6 },
    [WICED_GPIO_8]  = { GPIOA,  7 },
    [WICED_GPIO_9]  = { GPIOA,  9 },
    [WICED_GPIO_10] = { GPIOA, 10 },
    [WICED_GPIO_11] = { GPIOA, 11},
    [WICED_GPIO_12] = { GPIOA, 12},
    [WICED_GPIO_13] = { GPIOA, 13 },
    [WICED_GPIO_14] = { GPIOA, 14 },
    [WICED_GPIO_15] = { GPIOA, 15 },
    [WICED_GPIO_16] = {GPIOB,  0},
    [WICED_GPIO_17] = {GPIOB,  1},
    [WICED_GPIO_18] = {GPIOB,  2},
    [WICED_GPIO_19] = {GPIOB,  3},
    [WICED_GPIO_20] = {GPIOB,  4},
    [WICED_GPIO_21] = {GPIOB,  5},
    [WICED_GPIO_22] = {GPIOB,  6},
    [WICED_GPIO_23] = {GPIOB,  7},
    [WICED_GPIO_24] = {GPIOB,  8},
    [WICED_GPIO_25] = {GPIOB,  9},
    [WICED_GPIO_26] = {GPIOB, 10},
    [WICED_GPIO_27] = {GPIOB, 11},
    [WICED_GPIO_28] = {GPIOB, 12},
    [WICED_GPIO_29] = {GPIOB, 13},
    [WICED_GPIO_30] = {GPIOB, 14},
    [WICED_GPIO_31] = {GPIOB, 15},
    [WICED_GPIO_32] = {GPIOC,  0},
    [WICED_GPIO_33] = {GPIOC,  1},
    [WICED_GPIO_34] = {GPIOC,  2},
    [WICED_GPIO_35] = {GPIOC,  3},
    [WICED_GPIO_36] = {GPIOC,  4},
    [WICED_GPIO_37] = {GPIOC,  5},
    [WICED_GPIO_38] = {GPIOC,  6},
    [WICED_GPIO_39] = {GPIOC,  7},
    [WICED_GPIO_40] = {GPIOC,  8},
    [WICED_GPIO_41] = {GPIOC,  9},
    [WICED_GPIO_42] = {GPIOC, 10},
    [WICED_GPIO_43] = {GPIOC, 11},
    [WICED_GPIO_44] = {GPIOC, 12},
    [WICED_GPIO_45] = {GPIOC, 13},
    [WICED_GPIO_46] = {GPIOC, 14},
    [WICED_GPIO_47] = {GPIOC, 15},
    [WICED_GPIO_48] = {GPIOD,  2},
};

/* ADC peripherals. Used WICED/platform/MCU/wiced_platform_common.c */
const platform_adc_t platform_adc_peripherals[] =
{
	[WICED_ADC_0] = {ADC1, ADC_Channel_6, RCC_APB2Periph_ADC1, 1, &platform_gpio_pins[WICED_GPIO_7]},
    [WICED_ADC_1] = {ADC1, ADC_Channel_7, RCC_APB2Periph_ADC1, 1, &platform_gpio_pins[WICED_GPIO_8]},
    [WICED_ADC_2] = {ADC1, ADC_Channel_14, RCC_APB2Periph_ADC1, 1, &platform_gpio_pins[WICED_GPIO_36]},
    [WICED_ADC_3] = {ADC1, ADC_Channel_15, RCC_APB2Periph_ADC1, 1, &platform_gpio_pins[WICED_GPIO_37]},
};

/* PWM peripherals. Used by WICED/platform/MCU/wiced_platform_common.c */
const platform_pwm_t platform_pwm_peripherals[] =
{
    [WICED_PWM_1]  = {TIM2, 1, RCC_APB1Periph_TIM2, GPIO_AF_TIM2, &platform_gpio_pins[WICED_GPIO_6]},
/* TIM8_CH1N */
    [WICED_PWM_2]  = {TIM2, 2, RCC_APB1Periph_TIM2, GPIO_AF_TIM2, &platform_gpio_pins[WICED_GPIO_19]},
    [WICED_PWM_3]  = {TIM2, 3, RCC_APB1Periph_TIM2, GPIO_AF_TIM2, &platform_gpio_pins[WICED_GPIO_26] },
    [WICED_PWM_4]  = {TIM3, 1, RCC_APB1Periph_TIM3, GPIO_AF_TIM3, &platform_gpio_pins[WICED_GPIO_38] },
    [WICED_PWM_5]  = {TIM3, 2, RCC_APB1Periph_TIM3, GPIO_AF_TIM3, &platform_gpio_pins[WICED_GPIO_39] }, /* or TIM8/Ch2,                     */
    [WICED_PWM_6]  = {TIM3, 3, RCC_APB1Periph_TIM3, GPIO_AF_TIM3, &platform_gpio_pins[WICED_GPIO_16] }, /* TIM8_CH2N */
    [WICED_PWM_7]  = {TIM3, 4, RCC_APB1Periph_TIM3, GPIO_AF_TIM3, &platform_gpio_pins[WICED_GPIO_17] }, /* TIM1 CH3N, TIM8_CH3N */
    [WICED_PWM_8]  = {TIM4, 4, RCC_APB1Periph_TIM4, GPIO_AF_TIM4, &platform_gpio_pins[WICED_GPIO_25] },
};

/* I2C peripherals. Used by WICED/platform/MCU/wiced_platform_common.c */
const platform_i2c_t platform_i2c_peripherals[] =
{
#if defined(HW_REVISION_A0)
    [WICED_I2C_1] =
    {	/* conflick with I2S and SPI or JTAG TDO, SPI1_SCK */
        .port                    = I2C2,
        .pin_scl                 = &platform_gpio_pins[WICED_GPIO_26],	// B10	MI2S_MCK
#if 0
        .pin_sda                 = &platform_gpio_pins[WICED_GPIO_19], // B4 GPIO4 change JR13 to 2-3
#else
        .pin_sda                 = &platform_gpio_pins[WICED_GPIO_25],	// B9	SPI_NSS
#endif
        .peripheral_clock_reg    = RCC_APB1Periph_I2C2,
        .tx_dma                  = DMA1,
        .tx_dma_peripheral_clock = RCC_AHB1Periph_DMA1,
        .tx_dma_stream           = DMA1_Stream7,
        .rx_dma_stream           = DMA1_Stream2,
        .tx_dma_stream_id        = 7,
        .rx_dma_stream_id        = 2,
        .tx_dma_channel          = DMA_Channel_7,
        .rx_dma_channel          = DMA_Channel_7,
#if !defined(SPLIT_I2C_CONFIG)
        .gpio_af                 = GPIO_AF_I2C2,
#else
        .gpio_af                 = GPIO_AF_EVENTOUT,
	    .gpio_af_scl             = GPIO_AF_I2C2,
        .gpio_af_sda             = GPIO_AF9_I2C2
#endif /* !defined(SPLIT_I2C_CONFIG) */
    },
#endif /* HW_REVISION_A0 */
#if defined(HW_REVISION_A1)
    [WICED_I2C_1] =
    {
        .port                    = I2C1,
        .pin_scl                 = &platform_gpio_pins[WICED_GPIO_22], // B6
        .pin_sda                 = &platform_gpio_pins[WICED_GPIO_23], // B7
        .peripheral_clock_reg    = RCC_APB1Periph_I2C1,
        .tx_dma                  = DMA1,
        .tx_dma_peripheral_clock = RCC_AHB1Periph_DMA1,
        .tx_dma_stream           = DMA1_Stream7,
        .rx_dma_stream           = DMA1_Stream0,
        .tx_dma_stream_id        = 7,
        .rx_dma_stream_id        = 0,
        .tx_dma_channel          = DMA_Channel_1,
        .rx_dma_channel          = DMA_Channel_1,
        .gpio_af                 = GPIO_AF_I2C1,
    },
#if defined(SPLIT_I2C_CONFIG)
    [WICED_I2C_2] =
    {	/* conflick with I2S and SPI or JTAG TDO, SPI1_SCK */
        .port                    = I2C2,
        .pin_scl                 = &platform_gpio_pins[WICED_GPIO_26],	// B10	MI2S_MCK
#if 0
        .pin_sda                 = &platform_gpio_pins[WICED_GPIO_19], // B4 GPIO4 change JR13 to 2-3
#else	
        .pin_sda                 = &platform_gpio_pins[WICED_GPIO_25],	// B9	SPI_NSS
#endif	
        .peripheral_clock_reg    = RCC_APB1Periph_I2C2,
        .tx_dma                  = DMA1,
        .tx_dma_peripheral_clock = RCC_AHB1Periph_DMA1,
        .tx_dma_stream           = DMA1_Stream7,
        .rx_dma_stream           = DMA1_Stream2,
        .tx_dma_stream_id        = 7,
        .rx_dma_stream_id        = 2,
        .tx_dma_channel          = DMA_Channel_7,
        .rx_dma_channel          = DMA_Channel_7,
        .gpio_af                 = GPIO_AF_EVENTOUT,
	.gpio_af_scl             = GPIO_AF_I2C2,
        .gpio_af_sda             = GPIO_AF9_I2C2
    },
#endif /* !defined(SPLIT_I2C_CONFIG) */
#endif /* HW_REVISION_A1 */
};

#if defined(HW_REVISION_A1)
/* MFI-related variables */
const wiced_i2c_device_t WISE_1530_I2C1 =
{
    .port          = WICED_I2C_1,
    .address       = 0xA0,
    .address_width = I2C_ADDRESS_WIDTH_7BIT,
    .speed_mode    = I2C_STANDARD_SPEED_MODE,
};

const platform_mfi_auth_chip_t platform_auth_chip =
{
    .i2c_device = &WISE_1530_I2C1,
    .reset_pin  = WICED_GPIO_AUTH_RST	    /* WICED_GPIO_45 */
};
#endif /* HW_REVISION_A1 */

/* PWM peripherals. Used by WICED/platform/MCU/wiced_platform_common.c */
const platform_spi_t platform_spi_peripherals[] =
{
    [WICED_SPI_1]  =
    { /* SPI1_NSS  WICED_GPIO_5/15 = M_I2S_WS/GPIO_6 */
        .port                  = SPI1,
        .gpio_af               = GPIO_AF_SPI1,
        .peripheral_clock_reg  = RCC_APB2Periph_SPI1,
        .peripheral_clock_func = RCC_APB2PeriphClockCmd,
        .pin_mosi              = &platform_gpio_pins[WICED_GPIO_8],
        .pin_miso              = &platform_gpio_pins[WICED_GPIO_7],
        .pin_clock             = &platform_gpio_pins[WICED_GPIO_19], /* GPIO_4 change JR13 to 2-3 to used the H_TDO */
        //.pin_clock             = &platform_gpio_pins[WICED_GPIO_6], /* SPI1_SCK : GPIO_0 */
        .tx_dma =
        {
            .controller        = DMA2,
            .stream            = DMA2_Stream5,
            .channel           = DMA_Channel_3,
            .irq_vector        = DMA2_Stream5_IRQn,
            .complete_flags    = DMA_HISR_TCIF5,
            .error_flags       = ( DMA_HISR_TEIF5 | DMA_HISR_FEIF5 | DMA_HISR_DMEIF5 ),
        },
        .rx_dma =
        {
            .controller        = DMA2,
            .stream            = DMA2_Stream0,
            .channel           = DMA_Channel_3,
            .irq_vector        = DMA2_Stream0_IRQn,
            .complete_flags    = DMA_LISR_TCIF0,
            .error_flags       = ( DMA_LISR_TEIF0 | DMA_LISR_FEIF0 | DMA_LISR_DMEIF0 ),
        },
    },
    [WICED_SPI_2]  =
    { /* SPI2_NSS WICED_GPIO_25 : WICED_GPIO_28=MI2S_CK */
        .port                  = SPI2,
        .gpio_af               = GPIO_AF_SPI2,
        .peripheral_clock_reg  = RCC_APB1Periph_SPI2,
        .peripheral_clock_func = RCC_APB1PeriphClockCmd,
        .pin_mosi              = &platform_gpio_pins[WICED_GPIO_35],
        .pin_miso              = &platform_gpio_pins[WICED_GPIO_34],
        .pin_clock             = &platform_gpio_pins[WICED_GPIO_29],
        .tx_dma =
        {
            .controller        = DMA1,
            .stream            = DMA1_Stream4,
            .channel           = DMA_Channel_0,
            .irq_vector        = DMA1_Stream4_IRQn,
            .complete_flags    = DMA_HISR_TCIF4,
            .error_flags       = ( DMA_HISR_TEIF4 | DMA_HISR_FEIF4 | DMA_HISR_DMEIF4 ),
        },
        .rx_dma =
        {
            .controller        = DMA1,
            .stream            = DMA1_Stream3,
            .channel           = DMA_Channel_0,
            .irq_vector        = DMA1_Stream3_IRQn,
            .complete_flags    = DMA_LISR_TCIF3,
            .error_flags       = ( DMA_LISR_TEIF3 | DMA_LISR_FEIF3 | DMA_LISR_DMEIF3 ),
        },
    }
};

/* UART peripherals and runtime drivers. Used by WICED/platform/MCU/wiced_platform_common.c */
const platform_uart_t platform_uart_peripherals[] =
{
    [WICED_UART_1] =
    {
        .port               = USART1,
        .tx_pin             = &platform_gpio_pins[WICED_GPIO_9 ],
        .rx_pin             = &platform_gpio_pins[WICED_GPIO_10],
        .cts_pin            = NULL,
        .rts_pin            = NULL,
        .tx_dma_config =
        {
            .controller     = DMA2,
            .stream         = DMA2_Stream7,
            .channel        = DMA_Channel_4,
            .irq_vector     = DMA2_Stream7_IRQn,
            .complete_flags = DMA_HISR_TCIF7,
            .error_flags    = ( DMA_HISR_TEIF7 | DMA_HISR_FEIF7 ),
        },
        .rx_dma_config =
        {
            .controller     = DMA2,
            .stream         = DMA2_Stream2,
            .channel        = DMA_Channel_4,
            .irq_vector     = DMA2_Stream2_IRQn,
            .complete_flags = DMA_LISR_TCIF2,
            .error_flags    = ( DMA_LISR_TEIF2 | DMA_LISR_FEIF2 | DMA_LISR_DMEIF2 ),
        },
    },
    [WICED_UART_2] =
    {
        .port               = USART2,
        .tx_pin             = &platform_gpio_pins[WICED_GPIO_3],
        .rx_pin             = &platform_gpio_pins[WICED_GPIO_4],
        .cts_pin            = &platform_gpio_pins[WICED_GPIO_1],
        .rts_pin            = &platform_gpio_pins[WICED_GPIO_2],
        .tx_dma_config =
        {
            .controller     = DMA1,
            .stream         = DMA1_Stream6,
            .channel        = DMA_Channel_4,
            .irq_vector     = DMA1_Stream6_IRQn,
            .complete_flags = DMA_HISR_TCIF6,
            .error_flags    = ( DMA_HISR_TEIF6 | DMA_HISR_FEIF6 ),
        },
        .rx_dma_config =
        {
            .controller     = DMA1,
            .stream         = DMA1_Stream5,
            .channel        = DMA_Channel_4,
            .irq_vector     = DMA1_Stream5_IRQn,
            .complete_flags = DMA_HISR_TCIF5,
            .error_flags    = ( DMA_HISR_TEIF5 | DMA_HISR_FEIF5 | DMA_HISR_DMEIF5 ),
        },
    },
    [WICED_UART_3] =
    {
        .port               = USART3,
        .tx_pin             = &platform_gpio_pins[WICED_GPIO_26],
        .rx_pin             = &platform_gpio_pins[WICED_GPIO_43],
        .cts_pin            = NULL,
        .rts_pin            = NULL,
        .tx_dma_config =
        {
            .controller     = DMA1,
            .stream         = DMA1_Stream3,
            .channel        = DMA_Channel_4,
            .irq_vector     = DMA1_Stream3_IRQn,
            .complete_flags = DMA_LISR_TCIF3, //DMA_HISR_TCIF6,
            .error_flags    = (DMA_LISR_TCIF3 | DMA_LISR_FEIF3), //( DMA_HISR_TEIF6 | DMA_HISR_FEIF6 ),
        },
        .rx_dma_config =
        {
            .controller     = DMA1,
            .stream         = DMA1_Stream1,
            .channel        = DMA_Channel_4,
            .irq_vector     = DMA1_Stream1_IRQn,
            .complete_flags = DMA_LISR_TCIF1,
            .error_flags    = ( DMA_LISR_TEIF1 | DMA_LISR_FEIF1 | DMA_LISR_DMEIF1 ),
        },
    },
};
platform_uart_driver_t platform_uart_drivers[WICED_UART_MAX];

/* SPI flash. Exposed to the applications through include/wiced_platform.h */
#if defined ( WICED_PLATFORM_INCLUDES_SPI_FLASH )
const wiced_spi_device_t wiced_spi_flash =
{
    .port        = WICED_SPI_2,
    .chip_select = WICED_SPI_FLASH_CS,
    .speed       = 20000000,
    .mode        = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_HIGH | SPI_NO_DMA | SPI_MSB_FIRST),
    .bits        = 8
};
#endif

/* UART standard I/O configuration */
#ifndef WICED_DISABLE_STDIO
static const platform_uart_config_t stdio_config =
{
    .baud_rate    = 115200,
    .data_width   = DATA_WIDTH_8BIT,
    .parity       = NO_PARITY,
    .stop_bits    = STOP_BITS_1,
    .flow_control = FLOW_CONTROL_DISABLED,
};
#endif

/* Wi-Fi control pins. Used by WICED/platform/MCU/wwd_platform_common.c
 * SDIO: WWD_PIN_BOOTSTRAP[1:0] = b'00
 * gSPI: WWD_PIN_BOOTSTRAP[1:0] = b'01
 */
const platform_gpio_t wifi_control_pins[] =
{
#if defined ( WICED_USE_WIFI_POWER_PIN )
    [WWD_PIN_POWER      ] = { GPIOB,  0 },
#endif
#if defined ( WICED_USE_WIFI_RESET_PIN )
#if defined(HW_REVISION_A0)
    [WWD_PIN_RESET      ] = { GPIOB,  7 },
#endif /* HW_REVISION_A0 */
#if defined(HW_REVISION_A1)
    [WWD_PIN_RESET      ] = { GPIOC,  7 },
#endif /* HW_REVISION_A1 */
#endif
#if defined ( WICED_USE_WIFI_32K_CLOCK_MCO )
    [WWD_PIN_32K_CLK    ] = { GPIOA,  8 },
#endif
#ifdef WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_0
    [WWD_PIN_BOOTSTRAP_0] = { GPIOB,  0 },
#endif
#ifdef WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_1
    [WWD_PIN_BOOTSTRAP_1] = { GPIOB,  1 },
#endif
};

/* Wi-Fi SDIO bus pins. Used by WICED/platform/MCU/STM32F4xx/WWD/wwd_SDIO.c */
const platform_gpio_t wifi_sdio_pins[] =
{
    [WWD_PIN_SDIO_OOB_IRQ] = { GPIOC,  1 }, /* 33 */
    [WWD_PIN_SDIO_CLK    ] = { GPIOB, 15 }, /* 31 */
    [WWD_PIN_SDIO_CMD    ] = { GPIOD,  2 }, /* 50 */
    [WWD_PIN_SDIO_D0     ] = { GPIOC,  8 }, /* 40 */
    [WWD_PIN_SDIO_D1     ] = { GPIOC,  9 }, /* 41 */
    [WWD_PIN_SDIO_D2     ] = { GPIOC, 10 }, /* 42 */
    [WWD_PIN_SDIO_D3     ] = { GPIOB,  5 }, /* 21 */
};

/* Bluetooth control pins. Used by libraries/bluetooth/internal/bus/UART/bt_bus.c */
const platform_gpio_t* wiced_bt_control_pins[] =
{
    /* Reset pin unavailable */
#if defined(HW_REVISION_A0)
    [WICED_BT_PIN_POWER      ] = &platform_gpio_pins[WICED_GPIO_22 ],
#endif /* HW_REVISION_A0 */
#if defined(HW_REVISION_A1)
    [WICED_BT_PIN_POWER      ] = &platform_gpio_pins[WICED_GPIO_38 ],
#endif /* HW_REVISION_A1 */
    [WICED_BT_PIN_HOST_WAKE  ] = &platform_gpio_pins[WICED_GPIO_32 ], /* need H/W BT_HOST_WAKE_UP (P.12) to MICRO_HOST_WKUP (P.27) */
    [WICED_BT_PIN_DEVICE_WAKE] = &platform_gpio_pins[WICED_GPIO_24 ],
    [WICED_BT_PIN_RESET      ] = NULL,
};

/* used by libraries/bluetooth/.../bt_bus.c libraries/bt_audio/wiced_bt.c */
const platform_gpio_t* wiced_bt_uart_pins[] =
{
    [WICED_BT_PIN_UART_TX ] = &platform_gpio_pins[WICED_GPIO_3 ],
    [WICED_BT_PIN_UART_RX ] = &platform_gpio_pins[WICED_GPIO_4 ],
    [WICED_BT_PIN_UART_CTS] = &platform_gpio_pins[WICED_GPIO_1 ],
    [WICED_BT_PIN_UART_RTS] = &platform_gpio_pins[WICED_GPIO_2 ],
};

const platform_uart_t*        wiced_bt_uart_peripheral = &platform_uart_peripherals[WICED_UART_2];
platform_uart_driver_t*       wiced_bt_uart_driver     = &platform_uart_drivers[WICED_UART_2];

/* Bluetooth UART configuration. Used by libraries/bluetooth/internal/bus/UART/bt_bus.c */
const platform_uart_config_t wiced_bt_uart_config =
{
    .baud_rate    = 115200,
    .data_width   = DATA_WIDTH_8BIT,
    .parity       = NO_PARITY,
    .stop_bits    = STOP_BITS_1,
    .flow_control = FLOW_CONTROL_DISABLED,
};

/*BT chip specific configuration information*/
const platform_bluetooth_config_t wiced_bt_config =
{
    .patchram_download_mode      = PATCHRAM_DOWNLOAD_MODE_MINIDRV_CMD,
    .patchram_download_baud_rate = 115200,
    .featured_baud_rate          = 115200
};


gpio_button_t platform_gpio_buttons[] =
{
#ifdef WICED_BUTTON1
    [PLATFORM_BUTTON_1] =
    {
        .polarity   = WICED_ACTIVE_HIGH,
        .gpio       = WICED_BUTTON1,
        .trigger    = IRQ_TRIGGER_BOTH_EDGES,
    },
#endif
#ifdef WICED_BUTTON2
    [PLATFORM_BUTTON_2] =
    {
        .polarity   = WICED_ACTIVE_HIGH,
        .gpio       = WICED_BUTTON2,
        .trigger    = IRQ_TRIGGER_BOTH_EDGES,
    },
#endif
};

const wiced_gpio_t platform_gpio_leds[PLATFORM_LED_COUNT] =
{
     [WICED_LED_INDEX_1] = WICED_LED1,
     [WICED_LED_INDEX_2] = WICED_LED2,
	 [WICED_LED_INDEX_3] = CB_PWR_ON,
	 [WICED_LED_INDEX_4] = nCB_RESET_OUT,
};

/******************************************************
 *               Function Definitions
 ******************************************************/

void platform_init_peripheral_IRQHandler_priorities( void )
{
    /* Interrupt priority setup. Called by WICED/platform/MCU/STM32F2xx/platform_init.c */
    NVIC_SetPriority( RTC_WKUP_IRQn    ,  1 ); /* RTC Wake-up event   */
    NVIC_SetPriority( SDIO_IRQn        ,  2 ); /* WLAN SDIO           */
    NVIC_SetPriority( DMA2_Stream3_IRQn,  3 ); /* WLAN SDIO DMA       */
    NVIC_SetPriority( USART1_IRQn      ,  6 ); /* WICED_UART_1        */
    NVIC_SetPriority( USART2_IRQn      ,  6 ); /* WICED_UART_2        */
    NVIC_SetPriority( USART3_IRQn      ,  6 ); /* WICED_UART_2        */
    NVIC_SetPriority( DMA2_Stream7_IRQn,  7 ); /* WICED_UART_1 TX DMA */
    NVIC_SetPriority( DMA2_Stream2_IRQn,  7 ); /* WICED_UART_1 RX DMA */
    NVIC_SetPriority( DMA1_Stream6_IRQn,  7 ); /* WICED_UART_2 TX DMA */
    NVIC_SetPriority( DMA1_Stream5_IRQn,  7 ); /* WICED_UART_2 RX DMA */
    NVIC_SetPriority( DMA1_Stream3_IRQn,  7 ); /* WICED_UART_3 TX DMA */
    NVIC_SetPriority( DMA1_Stream1_IRQn,  7 ); /* WICED_UART_3 RX DMA */
    NVIC_SetPriority( DMA2_Stream0_IRQn,  7 ); /* SPI1 RX DMA        */
    NVIC_SetPriority( DMA1_Stream3_IRQn,  7 ); /* SPI2 RX DMA        */
    NVIC_SetPriority( EXTI0_IRQn       , 14 ); /* GPIO                */
    NVIC_SetPriority( EXTI1_IRQn       , 14 ); /* GPIO                */
    NVIC_SetPriority( EXTI2_IRQn       , 14 ); /* GPIO                */
    NVIC_SetPriority( EXTI3_IRQn       , 14 ); /* GPIO                */
    NVIC_SetPriority( EXTI4_IRQn       , 14 ); /* GPIO                */
    NVIC_SetPriority( EXTI9_5_IRQn     , 14 ); /* GPIO                */
    NVIC_SetPriority( EXTI15_10_IRQn   , 14 ); /* GPIO                */
}

/* LEDs on this platform are active HIGH */
platform_result_t platform_led_set_state(int led_index, int off_on )
{
    if ((led_index >= 0) && (led_index < PLATFORM_LED_COUNT))
    {
        switch (off_on)
        {
            case WICED_LED_OFF:
                platform_gpio_output_low( &platform_gpio_pins[platform_gpio_leds[led_index]] );
                break;
            case WICED_LED_ON:
                platform_gpio_output_high( &platform_gpio_pins[platform_gpio_leds[led_index]] );
                break;
        }
        return PLATFORM_SUCCESS;
    }
    return PLATFORM_BADARG;
}

void platform_led_init( void )
{
    /* Initialise LEDs and turn off by default */
    platform_gpio_init( &platform_gpio_pins[platform_gpio_leds[WICED_LED_INDEX_1]], OUTPUT_PUSH_PULL );
    platform_led_set_state(WICED_LED_INDEX_1, WICED_LED_OFF);
#ifdef WICED_LED2
    platform_gpio_init( &platform_gpio_pins[platform_gpio_leds[WICED_LED_INDEX_2]], OUTPUT_PUSH_PULL );
    platform_led_set_state(WICED_LED_INDEX_2, WICED_LED_OFF);
#endif
#ifdef WICED_LED3
    platform_gpio_init( &platform_gpio_pins[platform_gpio_leds[WICED_LED_INDEX_3]], OUTPUT_PUSH_PULL );
    platform_led_set_state(WICED_LED_INDEX_3, WICED_LED_ON);
#endif
#ifdef WICED_LED4
    platform_gpio_init( &platform_gpio_pins[platform_gpio_leds[WICED_LED_INDEX_4]], OUTPUT_PUSH_PULL );
    platform_led_set_state(WICED_LED_INDEX_4, WICED_LED_OFF);
#endif
}

void platform_init_external_devices( void )
{
    /* Initialise LEDs and turn off by default */
    platform_led_init();

    /* Initialise buttons to input by default */
#ifdef WICED_BUTTON1
    platform_gpio_init( &platform_gpio_pins[WICED_BUTTON1], INPUT_PULL_UP );
#endif
#ifdef WICED_BUTTON2
    platform_gpio_init( &platform_gpio_pins[WICED_BUTTON2], INPUT_PULL_UP );
#endif

#ifndef WICED_DISABLE_STDIO
    /* Initialise UART standard I/O */
    platform_stdio_init( &platform_uart_drivers[STDIO_UART], &platform_uart_peripherals[STDIO_UART], &stdio_config );
#endif
}

uint32_t  platform_get_button_press_time ( int button_index, int led_index, uint32_t max_time )
{
    int             button_gpio;
    uint32_t        button_press_timer = 0;
    int             led_state = 0;

    /* Initialize input */
    button_gpio     = platform_gpio_buttons[button_index].gpio;
    platform_gpio_init( &platform_gpio_pins[ button_gpio ], INPUT_PULL_UP );

    while ( (PLATFORM_BUTTON_PRESSED_STATE == platform_gpio_input_get(&platform_gpio_pins[ button_gpio ])) )
    {
        /* wait a bit */
        host_rtos_delay_milliseconds( PLATFORM_BUTTON_PRESS_CHECK_PERIOD );

        /* Toggle LED */
        platform_led_set_state(led_index, (led_state == 0) ? WICED_LED_OFF : WICED_LED_ON);
        led_state ^= 0x01;

        /* keep track of time */
        button_press_timer += PLATFORM_BUTTON_PRESS_CHECK_PERIOD;
        if ((max_time > 0) && (button_press_timer >= max_time))
        {
            break;
        }
    }

     /* turn off the LED */
    platform_led_set_state(led_index, WICED_LED_OFF );

    return button_press_timer;
}

uint32_t  platform_get_factory_reset_button_time ( uint32_t max_time )
{
    return platform_get_button_press_time ( PLATFORM_FACTORY_RESET_BUTTON_INDEX, PLATFORM_RED_LED_INDEX, max_time );
}
