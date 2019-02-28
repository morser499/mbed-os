/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 * Defines PSoC 6-specific WWD platform functions
 */
#include <stdint.h>
#include <string.h>
#include "w_platform_peripheral.h"
#include "w_platform_config.h"
#include "wwd_constants.h"
#include "wwd_platform_common.h"
#include "platform/wwd_platform_interface.h"

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

/******************************************************
 *               Function Definitions
 ******************************************************/

wwd_result_t host_platform_init_wlan_powersave_clock( void )
{
    return WWD_SUCCESS;
}
