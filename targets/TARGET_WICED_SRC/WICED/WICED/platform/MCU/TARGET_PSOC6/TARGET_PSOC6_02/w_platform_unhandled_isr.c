/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 * Defines PSoC 6 default unhandled ISR and default mappings to unhandled ISR
 */
#include <stdint.h>
#include "w_platform_cmsis.h"
#include "w_platform_assert.h"
#include "w_platform_constants.h"
#include "w_platform_isr.h"
#include "w_platform_isr_interface.h"
#include "wwd_rtos.h"
#include "w_platform_peripheral.h"

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

extern void UnhandledInterrupt( void );

/******************************************************
 *               Variable Definitions
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

PLATFORM_DEFINE_ISR( UnhandledInterrupt )
{
    uint32_t active_interrupt_vector = (uint32_t) ( SCB->ICSR & 0x3fU );

    /* This variable tells you which interrupt vector is currently active */
    (void)active_interrupt_vector;
    WICED_TRIGGER_BREAKPOINT( );

    /* reset the processor immediately if not debug */
    platform_mcu_reset( );

    while( 1 )
    {
    }
}

/******************************************************
 *          Default IRQ Handler Declarations
 ******************************************************/
PLATFORM_SET_DEFAULT_ISR( NMIException           , UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR( HardFaultException     , UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR( MemManageException     , UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR( BusFaultException      , UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR( UsageFaultException    , UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR( DebugMonitor           , UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_0_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_1_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_2_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_3_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_4_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_5_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_6_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_7_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_8_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_9_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_10_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_11_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_12_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_13_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupts_gpio_14_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupt_gpio_IRQn_Handler         ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(ioss_interrupt_vdd_IRQn_Handler          ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(lpcomp_interrupt_IRQn_Handler            ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_8_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(srss_interrupt_mcwdt_0_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(srss_interrupt_mcwdt_1_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(srss_interrupt_backup_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(srss_interrupt_IRQn_Handler              ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_0_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_1_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_2_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_3_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_4_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_5_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_6_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_7_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_8_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_9_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_10_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_11_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_12_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_13_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_14_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_ipc_15_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_0_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_1_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_2_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_3_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_4_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_5_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_6_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_7_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_9_interrupt_IRQn_Handler             ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_10_interrupt_IRQn_Handler            ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_11_interrupt_IRQn_Handler            ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(scb_12_interrupt_IRQn_Handler            ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(csd_interrupt_IRQn_Handler               ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dmac_0_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dmac_1_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dmac_2_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dmac_3_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_0_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_1_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_2_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_3_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_4_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_5_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_6_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_7_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_8_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_9_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_10_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_11_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_12_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_13_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_14_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_15_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_16_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_17_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_18_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_19_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_20_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_21_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_22_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_23_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_24_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_25_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_26_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_27_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw0_28_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_0_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_1_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_2_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_3_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_4_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_5_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_6_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_7_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_8_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_9_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_10_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_11_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_12_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_13_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_14_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_15_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_16_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_17_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_18_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_19_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_20_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_21_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_22_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_23_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_24_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_25_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_26_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_27_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_dw1_28_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_fault_0_IRQn_Handler    ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_fault_1_IRQn_Handler    ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupt_crypto_IRQn_Handler      ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupt_fm_IRQn_Handler          ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_cm4_fp_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_cm0_cti_0_IRQn_Handler  ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_cm0_cti_1_IRQn_Handler  ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_cm4_cti_0_IRQn_Handler  ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(cpuss_interrupts_cm4_cti_1_IRQn_Handler  ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_0_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_1_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_2_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_3_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_4_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_5_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_6_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_0_interrupts_7_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_0_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_1_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_2_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_3_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_4_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_5_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_6_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_7_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_8_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_9_IRQn_Handler        ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_10_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_11_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_12_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_13_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_14_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_15_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_16_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_17_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_18_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_19_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_20_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_21_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_22_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(tcpwm_1_interrupts_23_IRQn_Handler       ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(pass_interrupt_sar_IRQn_Handler          ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(audioss_0_interrupt_i2s_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(audioss_0_interrupt_pdm_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(audioss_1_interrupt_i2s_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(profile_interrupt_IRQn_Handler           ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(smif_interrupt_IRQn_Handler              ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(usb_interrupt_hi_IRQn_Handler            ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(usb_interrupt_med_IRQn_Handler           ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(usb_interrupt_lo_IRQn_Handler            ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(sdhc_0_interrupt_wakeup_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(sdhc_0_interrupt_general_IRQn_Handler    ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(sdhc_1_interrupt_wakeup_IRQn_Handler     ,  UnhandledInterrupt )
PLATFORM_SET_DEFAULT_ISR(sdhc_1_interrupt_general_IRQn_Handler    ,  UnhandledInterrupt )
