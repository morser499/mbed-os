/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 * Declares ISR prototypes for PSoC 6 MCU family
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

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
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/
extern void NMIException           ( void );  // 2  Non Maskable Interrupt
extern void HardFaultException     ( void );  // 3  Hard Fault interrupt
extern void MemManageException     ( void );  // 4  Memory Management Fault interrupt
extern void BusFaultException      ( void );  // 5  Bus Fault interrupt
extern void UsageFaultException    ( void );  // 6  Usage Fault interrupt
extern void SVC_Handler            ( void );  // 11 SVC interrupt
extern void DebugMon_Handler       ( void );  // 12 Debug Monitor interrupt
extern void PendSV_Handler         ( void );  // 14 PendSV interrupt
extern void SysTick_Handler        ( void );  // 15 Sys Tick Interrupt

/* External interrupts                                           Power Mode  Description                                           */
extern void ioss_interrupts_gpio_0_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #0                                */
extern void ioss_interrupts_gpio_1_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #1                                */
extern void ioss_interrupts_gpio_2_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #2                                */
extern void ioss_interrupts_gpio_3_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #3                                */
extern void ioss_interrupts_gpio_4_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #4                                */
extern void ioss_interrupts_gpio_5_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #5                                */
extern void ioss_interrupts_gpio_6_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #6                                */
extern void ioss_interrupts_gpio_7_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #7                                */
extern void ioss_interrupts_gpio_8_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #8                                */
extern void ioss_interrupts_gpio_9_IRQHandler      ( void ); /* DeepSleep   GPIO Port Interrupt #9                                */
extern void ioss_interrupts_gpio_10_IRQHandler     ( void ); /* DeepSleep   GPIO Port Interrupt #10                               */
extern void ioss_interrupts_gpio_11_IRQHandler     ( void ); /* DeepSleep   GPIO Port Interrupt #11                               */
extern void ioss_interrupts_gpio_12_IRQHandler     ( void ); /* DeepSleep   GPIO Port Interrupt #12                               */
extern void ioss_interrupts_gpio_13_IRQHandler     ( void ); /* DeepSleep   GPIO Port Interrupt #13                               */
extern void ioss_interrupts_gpio_14_IRQHandler     ( void ); /* DeepSleep   GPIO Port Interrupt #14                               */
extern void ioss_interrupt_gpio_IRQHandler         ( void ); /* DeepSleep   GPIO All Ports                                        */
extern void ioss_interrupt_vdd_IRQHandler          ( void ); /* DeepSleep   GPIO Supply Detect Interrupt                          */
extern void lpcomp_interrupt_IRQHandler            ( void ); /* DeepSleep   Low Power Comparator Interrupt                        */
extern void scb_8_interrupt_IRQHandler             ( void ); /* DeepSleep   Serial Communication Block #8 (DeepSleep capable)     */
extern void srss_interrupt_mcwdt_0_IRQHandler      ( void ); /* DeepSleep   Multi Counter Watchdog Timer interrupt                */
extern void srss_interrupt_mcwdt_1_IRQHandler      ( void ); /* DeepSleep   Multi Counter Watchdog Timer interrupt                */
extern void srss_interrupt_backup_IRQHandler       ( void ); /* DeepSleep   Backup domain interrupt                               */
extern void srss_interrupt_IRQHandler              ( void ); /* DeepSleep   Other combined Interrupts for SRSS (LVD, WDT, CLKCAL) */
extern void cpuss_interrupts_ipc_0_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #0        */
extern void cpuss_interrupts_ipc_1_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #1        */
extern void cpuss_interrupts_ipc_2_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #2        */
extern void cpuss_interrupts_ipc_3_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #3        */
extern void cpuss_interrupts_ipc_4_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #4        */
extern void cpuss_interrupts_ipc_5_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #5        */
extern void cpuss_interrupts_ipc_6_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #6        */
extern void cpuss_interrupts_ipc_7_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #7        */
extern void cpuss_interrupts_ipc_8_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #8        */
extern void cpuss_interrupts_ipc_9_IRQHandler      ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #9        */
extern void cpuss_interrupts_ipc_10_IRQHandler     ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #10       */
extern void cpuss_interrupts_ipc_11_IRQHandler     ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #11       */
extern void cpuss_interrupts_ipc_12_IRQHandler     ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #12       */
extern void cpuss_interrupts_ipc_13_IRQHandler     ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #13       */
extern void cpuss_interrupts_ipc_14_IRQHandler     ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #14       */
extern void cpuss_interrupts_ipc_15_IRQHandler     ( void ); /* DeepSleep   CPUSS Inter Process Communication Interrupt #15       */
extern void scb_0_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #0                         */
extern void scb_1_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #1                         */
extern void scb_2_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #2                         */
extern void scb_3_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #3                         */
extern void scb_4_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #4                         */
extern void scb_5_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #5                         */
extern void scb_6_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #6                         */
extern void scb_7_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #7                         */
extern void scb_9_interrupt_IRQHandler             ( void ); /* Active      Serial Communication Block #9                         */
extern void scb_10_interrupt_IRQHandler            ( void ); /* Active      Serial Communication Block #10                         */
extern void scb_11_interrupt_IRQHandler            ( void ); /* Active      Serial Communication Block #11                         */
extern void scb_12_interrupt_IRQHandler            ( void ); /* Active      Serial Communication Block #12                         */
extern void csd_interrupt_IRQHandler               ( void ); /* Active      CSD (CapSense) interrupt                              */
extern void cpuss_interrupts_dmac_0_IRQHandler     ( void ); /* Active      CPUSS DMAC, Channel #1                                */
extern void cpuss_interrupts_dmac_1_IRQHandler     ( void ); /* Active      CPUSS DMAC, Channel #2                                */
extern void cpuss_interrupts_dmac_2_IRQHandler     ( void ); /* Active      CPUSS DMAC, Channel #3                                */
extern void cpuss_interrupts_dmac_3_IRQHandler     ( void ); /* Active      CPUSS DMAC, Channel #4                                */
extern void cpuss_interrupts_dw0_0_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #0                         */
extern void cpuss_interrupts_dw0_1_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #1                         */
extern void cpuss_interrupts_dw0_2_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #2                         */
extern void cpuss_interrupts_dw0_3_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #3                         */
extern void cpuss_interrupts_dw0_4_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #4                         */
extern void cpuss_interrupts_dw0_5_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #5                         */
extern void cpuss_interrupts_dw0_6_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #6                         */
extern void cpuss_interrupts_dw0_7_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #7                         */
extern void cpuss_interrupts_dw0_8_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #8                         */
extern void cpuss_interrupts_dw0_9_IRQHandler      ( void ); /* Active      CPUSS DataWire #0, Channel #9                         */
extern void cpuss_interrupts_dw0_10_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #10                        */
extern void cpuss_interrupts_dw0_11_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #11                        */
extern void cpuss_interrupts_dw0_12_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #12                        */
extern void cpuss_interrupts_dw0_13_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #13                        */
extern void cpuss_interrupts_dw0_14_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #14                        */
extern void cpuss_interrupts_dw0_15_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_16_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_17_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_18_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_19_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_20_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_21_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_22_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_23_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_24_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_25_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_26_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_27_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw0_28_IRQHandler     ( void ); /* Active      CPUSS DataWire #0, Channel #15                        */
extern void cpuss_interrupts_dw1_0_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #0                         */
extern void cpuss_interrupts_dw1_1_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #1                         */
extern void cpuss_interrupts_dw1_2_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #2                         */
extern void cpuss_interrupts_dw1_3_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #3                         */
extern void cpuss_interrupts_dw1_4_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #4                         */
extern void cpuss_interrupts_dw1_5_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #5                         */
extern void cpuss_interrupts_dw1_6_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #6                         */
extern void cpuss_interrupts_dw1_7_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #7                         */
extern void cpuss_interrupts_dw1_8_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #8                         */
extern void cpuss_interrupts_dw1_9_IRQHandler      ( void ); /* Active      CPUSS DataWire #1, Channel #9                         */
extern void cpuss_interrupts_dw1_10_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #10                        */
extern void cpuss_interrupts_dw1_11_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #11                        */
extern void cpuss_interrupts_dw1_12_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #12                        */
extern void cpuss_interrupts_dw1_13_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #13                        */
extern void cpuss_interrupts_dw1_14_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #14                        */
extern void cpuss_interrupts_dw1_15_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_16_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_17_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_18_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_19_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_20_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_21_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_22_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_23_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_24_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_25_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_26_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_27_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_dw1_28_IRQHandler     ( void ); /* Active      CPUSS DataWire #1, Channel #15                        */
extern void cpuss_interrupts_fault_0_IRQHandler    ( void ); /* Active      CPUSS Fault Structure Interrupt #0                    */
extern void cpuss_interrupts_fault_1_IRQHandler    ( void ); /* Active      CPUSS Fault Structure Interrupt #1                    */
extern void cpuss_interrupt_crypto_IRQHandler      ( void ); /* Active      CRYPTO Accelerator Interrupt                          */
extern void cpuss_interrupt_fm_IRQHandler          ( void ); /* Active      FLASH Macro Interrupt                                 */
extern void cpuss_interrupts_cm4_fp_IRQHandler     ( void );
extern void cpuss_interrupts_cm0_cti_0_IRQHandler  ( void ); /* Active      CM0+ CTI #0                                           */
extern void cpuss_interrupts_cm0_cti_1_IRQHandler  ( void ); /* Active      CM0+ CTI #1                                           */
extern void cpuss_interrupts_cm4_cti_0_IRQHandler  ( void ); /* Active      CM4 CTI #0                                            */
extern void cpuss_interrupts_cm4_cti_1_IRQHandler  ( void ); /* Active      CM4 CTI #1                                            */
extern void tcpwm_0_interrupts_0_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #0                                  */
extern void tcpwm_0_interrupts_1_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #1                                  */
extern void tcpwm_0_interrupts_2_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #2                                  */
extern void tcpwm_0_interrupts_3_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #3                                  */
extern void tcpwm_0_interrupts_4_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #4                                  */
extern void tcpwm_0_interrupts_5_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #5                                  */
extern void tcpwm_0_interrupts_6_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #6                                  */
extern void tcpwm_0_interrupts_7_IRQHandler        ( void ); /* Active      TCPWM #0, Counter #7                                  */
extern void tcpwm_1_interrupts_0_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #0                                  */
extern void tcpwm_1_interrupts_1_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #1                                  */
extern void tcpwm_1_interrupts_2_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #2                                  */
extern void tcpwm_1_interrupts_3_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #3                                  */
extern void tcpwm_1_interrupts_4_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #4                                  */
extern void tcpwm_1_interrupts_5_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #5                                  */
extern void tcpwm_1_interrupts_6_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #6                                  */
extern void tcpwm_1_interrupts_7_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #7                                  */
extern void tcpwm_1_interrupts_8_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #8                                  */
extern void tcpwm_1_interrupts_9_IRQHandler        ( void ); /* Active      TCPWM #1, Counter #9                                  */
extern void tcpwm_1_interrupts_10_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #10                                 */
extern void tcpwm_1_interrupts_11_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #11                                 */
extern void tcpwm_1_interrupts_12_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #12                                 */
extern void tcpwm_1_interrupts_13_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #13                                 */
extern void tcpwm_1_interrupts_14_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #14                                 */
extern void tcpwm_1_interrupts_15_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #15                                 */
extern void tcpwm_1_interrupts_16_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #16                                 */
extern void tcpwm_1_interrupts_17_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #17                                 */
extern void tcpwm_1_interrupts_18_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #18                                 */
extern void tcpwm_1_interrupts_19_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #19                                 */
extern void tcpwm_1_interrupts_20_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #20                                 */
extern void tcpwm_1_interrupts_21_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #21                                 */
extern void tcpwm_1_interrupts_22_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #22                                 */
extern void tcpwm_1_interrupts_23_IRQHandler       ( void ); /* Active      TCPWM #1, Counter #23                                 */
extern void pass_interrupt_sar_IRQHandler          ( void ); /* Active      SAR ADC interrupt                                     */
extern void audioss_0_interrupt_i2s_IRQHandler     ( void ); /* Active      I2S Audio interrupt                                   */
extern void audioss_0_interrupt_pdm_IRQHandler     ( void ); /* Active      PDM/PCM Audio interrupt                               */
extern void audioss_1_interrupt_i2s_IRQHandler     ( void ); /* Active      I2S Audio interrupt                                   */
extern void profile_interrupt_IRQHandler           ( void ); /* Active      Energy Profiler interrupt                             */
extern void smif_interrupt_IRQHandler              ( void ); /* Active      Serial Memory Interface interrupt                     */
extern void usb_interrupt_hi_IRQHandler            ( void ); /* Active      USB Interrupt                                         */
extern void usb_interrupt_med_IRQHandler           ( void ); /* Active      USB Interrupt                                         */
extern void usb_interrupt_lo_IRQHandler            ( void ); /* Active      USB Interrupt                                         */
extern void sdhc_0_interrupt_wakeup_IRQHandler     ( void );
extern void sdhc_0_interrupt_general_IRQHandler    ( void );
extern void sdhc_1_interrupt_wakeup_IRQHandler     ( void );
extern void sdhc_1_interrupt_general_IRQHandler    ( void );
#ifdef __cplusplus
} /* extern "C" */
#endif

