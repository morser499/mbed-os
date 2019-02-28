/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 * Defines internal configuration of the CYW943012P6EVB_01 board
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *  MCU Constants and Options
 ******************************************************/

/* CPU clock : 100 MHz */
/* CLK_HF[0]:CLK_FAST is setup in Cy_SystemInit() in peripheral library */
#define CPU_CLOCK_HZ         ( 100000000 )

/******************************************************
 *  Wi-Fi Options
 ******************************************************/

/* GPIO pins are used to bootstrap WiFi to SDIO or gSPI mode */
//#define WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_1    /* WiFi chip is configured for SDIO mode in CYW943012P6EVB_01 board */

/*  WiFi GPIO pin used for out-of-band interrupt */
//#define WICED_WIFI_OOB_IRQ_GPIO_PIN  ( 0 )    /* WiFi chip is not configured for GPIO OOB IRQ in CYW943012P6EVB_01 board */

/* The wifi power and reset pin are configured in wwd_sdio.c */
/* WiFi power pin is present */
//#define WICED_USE_WIFI_POWER_PIN    /* WiFi chip is powered by external source and be controlled by CYW943012P6EVB_01 board */

/* WiFi reset pin is present */
//#define WICED_USE_WIFI_RESET_PIN

/* WiFi power pin is active high */
//#define WICED_USE_WIFI_POWER_PIN_ACTIVE_HIGH    /* WiFi chip is powered by external power source in CYW943012P6EVB_01 board */

/*  WLAN Powersave Clock Source
 *  The WLAN sleep clock can be driven from one of two sources:
 *  1. MCO (MCU Clock Output) - default
 *  2. WLAN 32K internal oscillator (30% inaccuracy)
 *     - Comment the following directive : WICED_USE_WIFI_32K_CLOCK_MCO
 */

//#define WICED_USE_WIFI_32K_CLOCK_MCO  /* CYW943012P6EVB_01 board supplies the 32K clock */

/*  OTA */
//#define PLATFORM_HAS_OTA /* OTA support is not enabled for CYW943012P6EVB_01 board */
/*  WICED Resources uses a filesystem */
#ifndef WWD_DIRECT_RESOURCES
#define USES_RESOURCE_FILESYSTEM
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
