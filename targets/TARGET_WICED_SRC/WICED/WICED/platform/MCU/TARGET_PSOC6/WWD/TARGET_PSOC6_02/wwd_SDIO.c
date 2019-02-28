/*
 * $ Copyright Cypress Semiconductor $
 */

/** @file
 * Defines WWD SDIO functions for PSoC 6 MCU
 */

#include <string.h> /* For memcpy */
#include "wwd_platform_common.h"
#include "wwd_bus_protocol.h"
#include "wwd_assert.h"
#include "platform/wwd_platform_interface.h"
#include "platform/wwd_sdio_interface.h"
#include "platform/wwd_bus_interface.h"
#include "RTOS/wwd_rtos_interface.h"
#include "network/wwd_network_constants.h"
#include "w_platform_cmsis.h"
#include "w_platform_peripheral.h"
#include "w_platform_config.h"
#include "wwd_rtos_isr.h"
#include "cy_sd_host.h"
#include "cy_scb_uart.h"



/******************************************************
 *                      Macros
 ******************************************************/

#define VERIFY_SDIF_API_RESULT( x ) \
    { \
        en_sdio_result_t api_result; \
        api_result = (x); \
        if ( api_result != Ok ) \
        { \
            wiced_assert( "command failed", ( 0 == 1 )); \
            return WWD_SDIO_BUS_UP_FAIL; \
        } \
    }

/******************************************************
 *             Constants
 ******************************************************/

#define BUS_LEVEL_MAX_RETRIES                (5)

#ifndef SDIO_ENUMERATION_TIMEOUT_MS
#define SDIO_ENUMERATION_TIMEOUT_MS          (500)
#endif

/*TODO: Move these to the platform file so that a user can easily change them*/
#define WICED_SDHC_PORT                     (P2_0_PORT)
#define WICED_SDHC_BLOCK                    (SDHC0)
#define WIFI_RESET_PORT                     (P2_0_PORT)

#define WIFI_RESET_PIN                       (P2_6_NUM)
#define WICED_SDHC_CARD_CMD_NUM              (P2_4_NUM)
#define WICED_SDHC_CLK_CARD_NUM              (P2_5_NUM)
#define WICED_SDHC_CARD_DAT_3TO00_NUM        (P2_0_NUM)
#define WICED_SDHC_CARD_DAT_3TO01_NUM        (P2_1_NUM)
#define WICED_SDHC_CARD_DAT_3TO02_NUM        (P2_2_NUM)
#define WICED_SDHC_CARD_DAT_3TO03_NUM        (P2_3_NUM)

#define WICED_SDHC_CMD_HSIOM                 (P2_4_SDHC0_CARD_CMD)
#define WICED_SDHC_CLK_HSIOM                 (P2_5_SDHC0_CLK_CARD)
#define WICED_SDHC_DAT0_HSIOM                (P2_0_SDHC0_CARD_DAT_3TO00)
#define WICED_SDHC_DAT1_HSIOM                (P2_1_SDHC0_CARD_DAT_3TO01)
#define WICED_SDHC_DAT2_HSIOM                (P2_2_SDHC0_CARD_DAT_3TO02)
#define WICED_SDHC_DAT3_HSIOM                (P2_3_SDHC0_CARD_DAT_3TO03)

/******************************************************
 *             Structures
 ******************************************************/
wwd_result_t host_transfer_complete(void);
/******************************************************
 *             Variables
 ******************************************************/

#ifndef WICED_PLATFORM_DOESNT_USE_TEMP_DMA_BUFFER
ALIGNED_PRE(32) static uint8_t temp_dma_buffer[MAX(2*1024, WICED_LINK_MTU+64)] ALIGNED(32);
#endif

static host_semaphore_type_t        sdio_transfer_finished_semaphore;
cy_stc_sd_host_context_t SDIF0_context;

/******************************************************
 *             Static Function Declarations
 ******************************************************/

/******************************************************
 *             Function definitions
 ******************************************************/

#ifndef  WICED_DISABLE_MCU_POWERSAVE
static void sdio_oob_irq_handler( void* arg )
{
    UNUSED_PARAMETER(arg);
    WWD_BUS_STATS_INCREMENT_VARIABLE( oob_intrs );
    platform_mcu_powersave_exit_notify( );
    wwd_thread_notify_IRQHandler( );
}

wwd_result_t host_enable_oob_interrupt( void )
{
    /* TODO: Setup WiFi OOB interrupt GPIO pin (if required) for PSoC 6 */
    platform_gpio_init( &wifi_sdio_pins[WWD_PIN_SDIO_OOB_IRQ], INPUT_HIGH_IMPEDANCE );
    platform_gpio_irq_enable( &wifi_sdio_pins[WWD_PIN_SDIO_OOB_IRQ], IRQ_TRIGGER_RISING_EDGE, sdio_oob_irq_handler, 0 );
    return WWD_SUCCESS;
}

uint8_t host_platform_get_oob_interrupt_pin( void )
{
    /* TODO: Setup WiFi OOB interrupt GPIO pin (if required) for PSoC 6 */
    return WICED_WIFI_OOB_IRQ_GPIO_PIN;
}
#endif /* ifndef  WICED_DISABLE_MCU_POWERSAVE */

wwd_result_t host_platform_bus_init( void )
{

    wwd_result_t                    result = WWD_SUCCESS;
    cy_stc_sd_host_init_config_t    hostConfig;

    hostConfig.dmaType = CY_SD_HOST_DMA_SDMA;
    hostConfig.emmc = false;
    hostConfig.enableLedControl = false;


    platform_mcu_powersave_disable();

#ifdef WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_0
    /* TODO: Setup GPIO pin (if required) to put WLAN module into SDIO mode on PSoC 6 */
    platform_gpio_init( &wifi_control_pins[WWD_PIN_BOOTSTRAP_0], OUTPUT_PUSH_PULL );
    platform_gpio_output_low( &wifi_control_pins[WWD_PIN_BOOTSTRAP_0] );
#endif
#ifdef WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_1
    /* TODO: Setup GPIO pin (if required) to put WLAN module into SDIO mode on PSoC 6 */
    platform_gpio_init( &wifi_control_pins[WWD_PIN_BOOTSTRAP_1], OUTPUT_PUSH_PULL );
    platform_gpio_output_low( &wifi_control_pins[WWD_PIN_BOOTSTRAP_1] );
#endif

    (void)host_rtos_init_semaphore( &sdio_transfer_finished_semaphore );

    /*This is for WiFi reset pin, and will put part in reset*/
    Cy_GPIO_Pin_FastInit(WIFI_RESET_PORT, WIFI_RESET_PIN, CY_GPIO_DM_STRONG, 0, P2_6_GPIO);

    /*Enable SDHC block*/
    (void)Cy_SD_Host_Enable(WICED_SDHC_BLOCK);

    /* Connect SD Host SDHC function to pins */
    Cy_GPIO_SetHSIOM(WICED_SDHC_PORT, WICED_SDHC_CLK_CARD_NUM, WICED_SDHC_CMD_HSIOM);
    Cy_GPIO_SetHSIOM(WICED_SDHC_PORT, WICED_SDHC_CARD_CMD_NUM, WICED_SDHC_CLK_HSIOM);
    Cy_GPIO_SetHSIOM(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO00_NUM, WICED_SDHC_DAT0_HSIOM);
    Cy_GPIO_SetHSIOM(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO01_NUM, WICED_SDHC_DAT1_HSIOM);
    Cy_GPIO_SetHSIOM(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO02_NUM, WICED_SDHC_DAT2_HSIOM);
    Cy_GPIO_SetHSIOM(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO03_NUM, WICED_SDHC_DAT3_HSIOM);

    /* Configure pins for SDHC operation */
    Cy_GPIO_SetDrivemode(WICED_SDHC_PORT, WICED_SDHC_CLK_CARD_NUM, CY_GPIO_DM_STRONG);
    Cy_GPIO_SetDrivemode(WICED_SDHC_PORT, WICED_SDHC_CARD_CMD_NUM, CY_GPIO_DM_STRONG);
    Cy_GPIO_SetDrivemode(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO00_NUM, CY_GPIO_DM_STRONG);
    Cy_GPIO_SetDrivemode(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO01_NUM, CY_GPIO_DM_STRONG);
    Cy_GPIO_SetDrivemode(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO02_NUM, CY_GPIO_DM_STRONG);
    Cy_GPIO_SetDrivemode(WICED_SDHC_PORT, WICED_SDHC_CARD_DAT_3TO03_NUM, CY_GPIO_DM_STRONG);

    /* Configure SD Host to operate */
    (void) Cy_SD_Host_Init(WICED_SDHC_BLOCK, &hostConfig, &SDIF0_context);

    /*Only enable the Card and SDMA interrupt*/
    WICED_SDHC_BLOCK->CORE.NORMAL_INT_SIGNAL_EN_R =  (CY_SD_HOST_CARD_INTERRUPT | CY_SD_HOST_DMA_INTERRUPT);
    WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_EN_R = 0xffff;

    /*Don't enable any error interrupts for now*/
    WICED_SDHC_BLOCK->CORE.ERROR_INT_SIGNAL_EN_R = 0x0000;
    WICED_SDHC_BLOCK->CORE.ERROR_INT_STAT_EN_R = 0xffff;

    /*Clear all interrupts*/
    WICED_SDHC_BLOCK->CORE.ERROR_INT_STAT_R = 0xffff;
    WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R = 0xffff;

    /*Enable SDHC interrupt*/
    NVIC_EnableIRQ(sdhc_0_interrupt_general_IRQn);

    SDIF0_context.cardType = CY_SD_HOST_SDIO;

    /* Set the host bus width to 4 bit */
    (void)Cy_SD_Host_SetHostBusWidth(WICED_SDHC_BLOCK, CY_SD_HOST_BUS_WIDTH_4_BIT);

    /* Change the host SD clock to 400 kHz */
    //(void)Cy_SD_Host_SdCardChangeClock(WICED_SDHC_BLOCK, 400UL * 1000UL);
    WICED_SDHC_BLOCK->CORE.CLK_CTRL_R              = 0x7d0d;

    /* WiFi out of reset */
    Cy_GPIO_Write( WIFI_RESET_PORT,WIFI_RESET_PIN, 1 );

    /* Wait for WiFi chip to be ready */
    Cy_SysLib_Delay(1000);

    platform_mcu_powersave_enable();

    return result;
}

wwd_result_t host_platform_sdio_enumerate( void )
{
    wwd_result_t result;
    uint32_t       loop_count = 0;
    uint32_t       data = 0;

    loop_count = 0;
    do
    {
        /* Send CMD0 to set it to idle state */
        host_platform_sdio_transfer( BUS_WRITE, SDIO_CMD_0, SDIO_BYTE_MODE, SDIO_1B_BLOCK, 0, 0, 0, NO_RESPONSE, NULL );

        /* CMD5. */
        host_platform_sdio_transfer( BUS_READ, SDIO_CMD_5, SDIO_BYTE_MODE, SDIO_1B_BLOCK, 0, 0, 0, NO_RESPONSE, NULL );

        /* Send CMD3 to get RCA. */
        result = host_platform_sdio_transfer( BUS_READ, SDIO_CMD_3, SDIO_BYTE_MODE, SDIO_1B_BLOCK, 0, 0, 0, RESPONSE_NEEDED, &data );
        loop_count++;
        if ( loop_count >= (uint32_t) SDIO_ENUMERATION_TIMEOUT_MS )
        {
            return WWD_TIMEOUT;
        }
    } while ( ( result != WWD_SUCCESS ) && ( host_rtos_delay_milliseconds( (uint32_t) 1 ), ( 1 == 1 ) ) );
    /* If you're stuck here, check the platform matches your hardware */

    /* Send CMD7 with the returned RCA to select the card */
    host_platform_sdio_transfer( BUS_WRITE, SDIO_CMD_7, SDIO_BYTE_MODE, SDIO_1B_BLOCK, data, 0, 0, RESPONSE_NEEDED, NULL );
    return WWD_SUCCESS;
}

wwd_result_t host_platform_bus_deinit( void )
{
    return WWD_SUCCESS;
}

wwd_result_t host_platform_sdio_transfer( wwd_bus_transfer_direction_t direction, sdio_command_t command, sdio_transfer_mode_t mode, sdio_block_size_t block_size, uint32_t argument, /*@null@*/ uint32_t* data, uint16_t data_size, sdio_response_needed_t response_expected, /*@out@*/ /*@null@*/ uint32_t* response )
{
    wwd_result_t result = WWD_SUCCESS;
    uint16_t attempts = 0, loop_attempts = 0;

    cy_stc_sd_host_cmd_config_t cmd;
    cy_stc_sd_host_data_config_t dat;
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;

    wiced_assert("Bad args", !((command == SDIO_CMD_53) && (data == NULL)));

    /* Initialize data constants*/
    dat.autoCommand         = CY_SD_HOST_AUTO_CMD_NONE;
    dat.dataTimeout         = 0x0d;
    dat.enableIntAtBlockGap = false;
    dat.enReliableWrite     = false;
    dat.enableDma           = true;

    /*Clear out the response*/
    if ( response != NULL )
    {
        *response = 0;
    }

    platform_mcu_powersave_disable();

restart:
    ++attempts;

    /*  Add SDIO Error Handling
     *  SDIO write timeout is expected when doing first write to register after KSO bit disable (as it goes to AOS core).
     *  This timeout, however, triggers an error state in the hardware.  So, check for the error and then recover from it
     *  as needed via reset issuance.  This is the only time known that a write timeout occurs.
     */

    /* first clear out the command complete and transfer complete statuses */
    WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R = (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE);

    /* Check if an error occurred on any previous transactions */
    if( WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R & CY_SD_HOST_ERR_INTERRUPT )
    {
        /* Reset the block if there was an error.  Note a full reset usually
         * requires more time, but this short version is working quite well and
         * successfully clears out the error state.
         */
        WICED_SDHC_BLOCK->CORE.ERROR_INT_STAT_R = 0xffff;
        WICED_SDHC_BLOCK->CORE.SW_RST_R = 0x06;
        Cy_SysLib_DelayUs(1);
        WICED_SDHC_BLOCK->CORE.SW_RST_R = 0x00;
    }

    /* Check if we've tried too many times */
    if (attempts >= (uint16_t)10*BUS_LEVEL_MAX_RETRIES)
    {
        result = WWD_SDIO_RETRIES_EXCEEDED;
        goto exit;
    }

    /* Prepare the data transfer register */
    if ( command == SDIO_CMD_53 )
    {

        cmd.commandIndex                    = (uint32_t)53;
        cmd.commandArgument                 = (uint32_t)argument;
        cmd.enableCrcCheck                  = true;
        cmd.enableAutoResponseErrorCheck    = false;
        cmd.respType                        = CY_SD_HOST_RESPONSE_LEN_48;
        cmd.enableIdxCheck                  = true;
        cmd.dataPresent                     = true;
        cmd.cmdType                         = CY_SD_HOST_CMD_NORMAL;

        dat.data                            = data;

        if( mode == SDIO_BLOCK_MODE )
        {
              dat.blockSize         = block_size;
              dat.numberOfBlock     = (uint16_t)( data_size + block_size - 1 ) / block_size;
        }
        else
        {
                dat.blockSize       = data_size;
                dat.numberOfBlock   = 1;
        }


        dat.read           = ( direction == BUS_WRITE ) ? false : true;


#ifndef WICED_PLATFORM_DOESNT_USE_TEMP_DMA_BUFFER
        if (( direction == BUS_READ ) && ( mode == SDIO_BLOCK_MODE ))
        {
            /* In this mode, we may be reading more than the requested size to round
             * up to the nearest multiple of block size. So, providing temp buffer
             * instead of the original buffer to avoid memory corruption
             */
            dat.data       = (uint32_t *)temp_dma_buffer;
        }
#endif
       /*Enable XFER Done interrupt, and clear CMD and XFER Complete*/
            //TDU might not need the clear anymore since I'm resetting
       SDHC0->CORE.NORMAL_INT_STAT_R = (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE);
       SDHC0->CORE.NORMAL_INT_SIGNAL_EN_R  |= CY_SD_HOST_XFER_COMPLETE;

       ret = Cy_SD_Host_InitDataTransfer(WICED_SDHC_BLOCK, &dat);
       if ( ret != CY_SD_HOST_SUCCESS )
       {
           goto restart;
       }

       ret = Cy_SD_Host_SendCommand(WICED_SDHC_BLOCK, &cmd);
       if ( ret != CY_SD_HOST_SUCCESS )
       {
           goto restart;
       }

       loop_attempts = 0;
       while(!(SDHC0->CORE.NORMAL_INT_STAT_R & CY_SD_HOST_CMD_COMPLETE ) && (loop_attempts < 1000))
       {
           Cy_SysLib_DelayUs(1);
           loop_attempts++;
       }

       if(!(SDHC0->CORE.NORMAL_INT_STAT_R & CY_SD_HOST_CMD_COMPLETE ))
       {
           goto restart;
       }

       /*Wait for the transfer to complete*/
       result = host_rtos_get_semaphore( &sdio_transfer_finished_semaphore, 40, WICED_TRUE );

       if(result != WWD_SUCCESS)
       {
           goto restart;
       }

       /*Clear Command and XFER Complete Interrupts*/
       //TDU there is really no need to clear the transfer complete since it is cleared in the ISR
       SDHC0->CORE.NORMAL_INT_STAT_R = (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE);
       /*Disable XFER Complete Interrupt*/
       SDHC0->CORE.NORMAL_INT_SIGNAL_EN_R  &= (uint16_t)~CY_SD_HOST_XFER_COMPLETE;


#ifndef WICED_PLATFORM_DOESNT_USE_TEMP_DMA_BUFFER
        if (( direction == BUS_READ ) && ( mode == SDIO_BLOCK_MODE ))
        {
            memcpy( data, temp_dma_buffer, (size_t) data_size );
        }
#endif
    }
    /*Just a command is sent*/
    else
    {

        if(command == 0)
        {
            cmd.commandIndex                    = (uint32_t)0;
            cmd.commandArgument                 = (uint32_t)argument;
            cmd.enableCrcCheck                  = false;
            cmd.enableAutoResponseErrorCheck    = false;
            cmd.respType                        = CY_SD_HOST_RESPONSE_NONE;
            cmd.enableIdxCheck                  = false;
            cmd.dataPresent                     = false;
            cmd.cmdType                         = CY_SD_HOST_CMD_NORMAL;
        }
        else if(command == 3)
        {
            cmd.commandIndex                    = (uint32_t)3;
            cmd.commandArgument                 = (uint32_t)argument;
            cmd.enableCrcCheck                  = true;
            cmd.enableAutoResponseErrorCheck    = false;
            cmd.respType                        = CY_SD_HOST_RESPONSE_LEN_48;
            cmd.enableIdxCheck                  = true;
            cmd.dataPresent                     = false;
            cmd.cmdType                         = CY_SD_HOST_CMD_NORMAL;
        }

        else if(command == 5)
        {
            cmd.commandIndex                    = (uint32_t)5;
            cmd.commandArgument                 = (uint32_t)argument;
            cmd.enableCrcCheck                  = false;
            cmd.enableAutoResponseErrorCheck    = false;
            cmd.respType                        = CY_SD_HOST_RESPONSE_LEN_48;
            cmd.enableIdxCheck                  = false;
            cmd.dataPresent                     = false;
            cmd.cmdType                         = CY_SD_HOST_CMD_NORMAL;
        }

        /*Note this command sets the transfer complete flag*/
        else if(command == 7)
        {
            cmd.commandIndex                    = (uint32_t)7;
            cmd.commandArgument                 = (uint32_t)argument;
            cmd.enableCrcCheck                  = true;
            cmd.enableAutoResponseErrorCheck    = false;
            cmd.respType                        = CY_SD_HOST_RESPONSE_LEN_48B;
            cmd.enableIdxCheck                  = true;
            cmd.dataPresent                     = false;
            cmd.cmdType                         = CY_SD_HOST_CMD_NORMAL;
        }

        else if(command == 52)
        {
            cmd.commandIndex                    = (uint32_t)52;
            cmd.commandArgument                 = (uint32_t)argument;
            cmd.enableCrcCheck                  = true;
            cmd.enableAutoResponseErrorCheck    = false;
            cmd.respType                        = CY_SD_HOST_RESPONSE_LEN_48;
            cmd.enableIdxCheck                  = true;
            cmd.dataPresent                     = false;
            cmd.cmdType                         = CY_SD_HOST_CMD_NORMAL;
        }
        else
        {
            goto restart;
        }

        ret = Cy_SD_Host_SendCommand(WICED_SDHC_BLOCK, &cmd);
        if ( ret != CY_SD_HOST_SUCCESS )
        {
            goto restart;
        }

        loop_attempts = 0;
        while(!(SDHC0->CORE.NORMAL_INT_STAT_R & CY_SD_HOST_CMD_COMPLETE ) && (loop_attempts < 1000))
        {
            Cy_SysLib_DelayUs(1);
            loop_attempts++;
        }

        if(!(SDHC0->CORE.NORMAL_INT_STAT_R & CY_SD_HOST_CMD_COMPLETE ))
        {
            goto restart;
        }

        /*Clear the status*/
        SDHC0->CORE.NORMAL_INT_STAT_R = (CY_SD_HOST_CMD_COMPLETE);
    }

    if (( response != NULL ) && ( response_expected == RESPONSE_NEEDED))
    {
        Cy_SD_Host_GetResponse(WICED_SDHC_BLOCK, response, 0u);
    }

    result = WWD_SUCCESS;

exit:
    platform_mcu_powersave_enable();
    return result;
}

wwd_result_t host_platform_enable_high_speed_sdio( void )
{
    platform_mcu_powersave_disable();
    /* set fast clock */
    Cy_SD_Host_SetSdClkDiv( WICED_SDHC_BLOCK, 0x2 );
    Cy_SD_Host_SetBusSpeedMode( WICED_SDHC_BLOCK, CY_SD_HOST_BUS_SPEED_SDR12_5, (cy_stc_sd_host_context_t const *)&SDIF0_context );
    platform_mcu_powersave_enable();

    return WWD_SUCCESS;
}

wwd_result_t host_platform_bus_enable_interrupt( void )
{

    WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_EN_R |= (uint16_t)CY_SD_HOST_CARD_INTERRUPT;
    return  WWD_SUCCESS;
}

wwd_result_t host_platform_bus_disable_interrupt( void )
{
    WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_EN_R &= (uint16_t)~CY_SD_HOST_CARD_INTERRUPT;
    return  WWD_SUCCESS;
}

#ifdef WICED_PLATFORM_MASKS_BUS_IRQ
wwd_result_t host_platform_unmask_sdio_interrupt( void )
{
    return host_platform_bus_enable_interrupt();
}
#endif

void host_platform_bus_buffer_freed( wwd_buffer_dir_t direction )
{
    UNUSED_PARAMETER( direction );
}

/******************************************************
 *             IRQ Handler Definitions
 ******************************************************/

WWD_RTOS_DEFINE_ISR( SD_IRQ )
{
    uint16_t status;
    uint32_t address;

    status = WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R;

    /*Todo: Add in error handling probably just set the semaphore, and then set an error flag*/
    /*Card Interrupt*/
    if(status & CY_SD_HOST_CARD_INTERRUPT)
    {
        host_platform_bus_disable_interrupt();
       wwd_thread_notify_IRQHandler( );
    }

    /*SDMA Interrupt*/
    if(status & CY_SD_HOST_DMA_INTERRUPT)
    {
        WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R = CY_SD_HOST_DMA_INTERRUPT;
        /*Yes, you have to write the register back to itself to get it working again*/
        address = WICED_SDHC_BLOCK->CORE.ADMA_SA_LOW_R;
        WICED_SDHC_BLOCK->CORE.ADMA_SA_LOW_R = address;

    }

    /*Transfer complete*/
    if(status & CY_SD_HOST_XFER_COMPLETE)
    {
        WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R = CY_SD_HOST_XFER_COMPLETE;
        host_rtos_set_semaphore( &sdio_transfer_finished_semaphore, WICED_TRUE );
    }
    /*This read is to ensure the interrupt statues have been cleared*/
    status = WICED_SDHC_BLOCK->CORE.NORMAL_INT_STAT_R;
    NVIC_ClearPendingIRQ(sdhc_0_interrupt_general_IRQn);
    WWD_BUS_STATS_INCREMENT_VARIABLE( sdio_intrs );
}

/******************************************************
 *             IRQ Handler Mapping
 ******************************************************/
WWD_RTOS_MAP_ISR(SD_IRQ, sdhc_0_interrupt_general_IRQHandler)

