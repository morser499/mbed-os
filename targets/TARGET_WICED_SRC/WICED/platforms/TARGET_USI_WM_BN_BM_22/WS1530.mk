#
# Copyright (c) 2014-2017 USI Co. Ltd.
# All Rights Reserved.
#
# This is UNPUBLISHED PROPRIETARY SOURCE CODE of USI Co. Ltd.;
# the contents of this file may not be disclosed to third parties, copied
# or duplicated in any form, in whole or in part, without the prior
# written permission of USI Co. Ltd..
#
NAME := Platform_WISE0_1530

WLAN_CHIP            := 43438
WLAN_CHIP_REVISION   := A1
WLAN_CHIP_FAMILY     := 4343x
HOST_MCU_FAMILY      := STM32F4xx
HOST_MCU_VARIANT     := STM32F412
HOST_MCU_PART_NUMBER := STM32F412xG

PLATFORM_SUPPORTS_BUTTONS := 0

# BCM943438WCD1
BT_CHIP          := 43438
BT_CHIP_REVISION := A1
BT_CHIP_XTAL_FREQUENCY := 37_4MHz

INTERNAL_MEMORY_RESOURCES = $(ALL_RESOURCES)

ifndef BUS
BUS := SDIO
endif

EXTRA_TARGET_MAKEFILES +=  $(MAKEFILES_PATH)/standard_platform_targets.mk

VALID_BUSES := SDIO
PLAT_ARMCM4 += WISE_1530

# enable BT application for WISE-1530 platfrom
ifneq ($(filter BCM9$(WLAN_CHIP)%,$(VALID_PLATFORMS)),)
$(eval VALID_PLATFORMS += $(PLATFORM))
endif # check valid platforms

# Set the WIFI firmware in multi application file system to point to firmware
#ifeq ($(NO_WIFI_FIRMWARE),)
#MULTI_APP_WIFI_FIRMWARE   := resources/firmware/$(WLAN_CHIP)/$(WLAN_CHIP)$(WLAN_CHIP_REVISION)$(WLAN_CHIP_BIN_TYPE).bin
#endif

ifeq ($(MULTI_APP_WIFI_FIRMWARE),)
GLOBAL_DEFINES          += WWD_DIRECT_RESOURCES
else
# Setting some internal build parameters
WIFI_FIRMWARE           := $(MULTI_APP_WIFI_FIRMWARE)
WIFI_FIRMWARE_LOCATION 	:= WIFI_FIRMWARE_IN_MULTI_APP
GLOBAL_DEFINES          += WIFI_FIRMWARE_IN_MULTI_APP
endif

GLOBAL_DEFINES += WICED_DCT_INCLUDE_BT_CONFIG

# Global includes
GLOBAL_INCLUDES  := .
GLOBAL_INCLUDES  += $(SOURCE_ROOT)libraries/inputs/gpio_button

# Global defines
GLOBAL_DEFINES += HSE_VALUE=26000000
# ENABLE Antenna diversity
# GLOBAL_DEFINES += WIFI_ANT_DIV_ENABLE
# no external 32K
# GLOBAL_DEFINES += STM_LSE_OFF
# GLOBAL_DEFINES += SLOW_SDIO_CLOCK
GLOBAL_DEFINES += $$(if $$(NO_CRLF_STDIO_REPLACEMENT),,CRLF_STDIO_REPLACEMENT)
GLOBAL_DEFINES += SFLASH_SUPPORT_MACRONIX_PARTS

# Components
$(NAME)_COMPONENTS += drivers/spi_flash \
                      inputs/gpio_button

# Source files
$(NAME)_SOURCES := platform.c

# WICED APPS
# APP0 and FILESYSTEM_IMAGE are reserved main app and resources file system
# FR_APP := resources/sflash/snip_ota_fr-BCM943362WCD6.stripped.elf
# DCT_IMAGE :=
# OTA_APP :=
# FILESYSTEM_IMAGE :=
# WIFI_FIRMWARE :=
# APP0 :=
# APP1 :=
# APP2 :=

# WICED APPS LOOKUP TABLE
APPS_LUT_HEADER_LOC := 0x0000
APPS_START_SECTOR := 1

ifneq ($(APP),bootloader)
ifneq ($(MAIN_COMPONENT_PROCESSING),1)
$(info +-----------------------------------------------------------------------------------------------------+ )
$(info | IMPORTANT NOTES                                                                                     | )
$(info +-----------------------------------------------------------------------------------------------------+ )
$(info | Wi-Fi MAC Address                                                                                   | )
$(info |    The target Wi-Fi MAC address is defined in <WICED-SDK>/generated_mac_address.txt                 | )
$(info |    Ensure each target device has a unique address.                                                  | )
$(info +-----------------------------------------------------------------------------------------------------+ )
$(info | MCU & Wi-Fi Power Save                                                                              | )
$(info |    It is *critical* that applications using WICED Powersave API functions connect an accurate 32kHz | )
$(info |    reference clock to the sleep clock input pin of the WLAN chip. Please read the WICED Powersave   | )
$(info |    Application Note located in the documentation directory if you plan to use powersave features.   | )
$(info +-----------------------------------------------------------------------------------------------------+ )
endif
endif
