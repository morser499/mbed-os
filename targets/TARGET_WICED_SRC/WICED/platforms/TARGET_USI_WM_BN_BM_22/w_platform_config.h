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
 * Defines internal configuration of the BCMUSI22 board
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************
 *  MCU Constants and Options
 *
 *  NOTE: The clock configuration utility from ST is used to calculate these values
 *        http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/utility/stsw-stm32090.zip
 ******************************************************/

/*  CPU clock : 100 MHz */
#define CPU_CLOCK_HZ         ( 100000000 )

/*  Use external crystal */
#define HSE_SOURCE           ( RCC_HSE_ON )

/*  AHB clock  : System clock */
#define AHB_CLOCK_DIVIDER    ( RCC_SYSCLK_Div1 )

/*  APB1 clock : AHB clock / 2 */
#define APB1_CLOCK_DIVIDER   ( RCC_HCLK_Div2 )

/*  APB2 clock : AHB clock / 1 */
#define APB2_CLOCK_DIVIDER   ( RCC_HCLK_Div1 )

/*  PLL source : external crystal */
#define PLL_SOURCE           ( RCC_PLLSource_HSE )
/*
   R << 28 | Q <<24 | P/(2 -1) << 16 | N << 6 | M
*/
/*  PLLM : 13 */
#define PLL_M_CONSTANT       ( 13 )

/*  PLLN : 200 */
#define PLL_N_CONSTANT       ( 200 )

/*  PLLP : 4 */
#define PLL_P_CONSTANT       ( 4 )

/*  PLLQ : 8 */
#define PLL_Q_CONSTANT       ( 8 )

/*  PLLR : 2..7 */
#define PLL_R_CONSTANT       ( 4 )

/*  System clock source  : PLL clock */
#define SYSTEM_CLOCK_SOURCE  ( RCC_SYSCLKSource_PLLCLK )

/*  SysTick clock source : AHB clock  */
#define SYSTICK_CLOCK_SOURCE ( SysTick_CLKSource_HCLK )

/*  Internal flash wait state : 3 cycles */
#define INT_FLASH_WAIT_STATE ( FLASH_Latency_3 )

/*  Internal flash voltage range : 2.7 to 3.6V */
#define PLATFORM_STM32_VOLTAGE_2V7_TO_3V6


#ifdef TARGET_MTB_USI_WM_BN_BM_22
#define HW_REVISION_A0
#else
#define HW_REVISION_A1
#endif
/******************************************************
 *  Wi-Fi Options
 ******************************************************/

/*  No GPIO pins are used to bootstrap Wi-Fi */
/* only support SDIO 
#define WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP
*/

/*  Wi-Fi GPIO0 pin is used for out-of-band interrupt */
#define WICED_WIFI_OOB_IRQ_GPIO_PIN  ( 0 )  /* wwd_SDIO.c */

/*  Wi-Fi reset pin is present */
#define WICED_USE_WIFI_RESET_PIN

#if 0
/*  Wi-Fi power pin is present */
#define WICED_USE_WIFI_POWER_PIN

/* Wi-Fi power pin is active high */
#define WICED_USE_WIFI_POWER_PIN_ACTIVE_HIGH
#endif

#ifndef STM_LSE_OFF
/*  WLAN Powersave Clock Source
 *  The WLAN sleep clock can be driven from one of two sources:
 *  1. external 32K osc - default
 *     - Comment the following directive : WICED_USE_WIFI_32K_CLOCK_MCO
 *  2. WLAN 32K internal oscillator (30% inaccuracy)
 *     - Uncomment the following directive : WICED_USE_WIFI_32K_CLOCK_MCO
 */
#define WICED_USE_WIFI_32K_CLOCK_MCO
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
