/*
 * Copyright (c) 2014-2017 USI Co. Ltd.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of USI Co. Ltd.;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of USI Co. Ltd..
 */

/** @file
 *
 *  BCM43438 NVRAM variables for WM-BN-BM-22 USI SiP
 *	    20150421
 *
 */

#ifndef INCLUDED_NVRAM_IMAGE_H_
#define INCLUDED_NVRAM_IMAGE_H_

#include <string.h>
#include <stdint.h>
#include "../generated_mac_address.txt"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Character array of NVRAM image
 */

static const char wifi_nvram_image[] =
        "manfid=0x2d0"                                                      "\x00"
        "prodid=0x0727"                                                     "\x00"
        "vendid=0x14e4"                                                     "\x00"
        "devid=0x43e2"                                                      "\x00"
        "boardtype=0x0727"                                                  "\x00"
        "boardrev=0x1101"                                                   "\x00"
        "boardnum=22"                                                       "\x00"
        "xtalfreq=37400"			                            "\x00"
        "sromrev=11"                                                        "\x00"
        "boardflags=0x00404201"                                             "\x00"
        "boardflags3=0x08000000"		                             "\x00"
        "wl0id=0x431b"				                             "\x00"
        NVRAM_GENERATED_MAC_ADDRESS                                          "\x00"
        "nocrc=1"                                                            "\x00"
        "ag0=255"                                                            "\x00"
        "aa2g=1"                                                             "\x00"
        "ccode=ALL"                                                         "\x00"
        //#Antenna diversity
#ifdef WIFI_ANT_DIV_ENABLE
        "swdiv_en=1"                                                         "\x00"
        "swdiv_gpio=1"                                                       "\x00"
        "swdiv_gpio_1=2"                                                     "\x00"
#endif
        "pa0itssit=0x20"                                                     "\x00"
        "extpagain2g=0"                                                      "\x00"
        //#PA parameters for 2.4GHz, measured at CHIP OUTPUT
        "pa2ga0=-109,7058,-755"						    "\x00"
        "AvVmid_c0=0x0,0xc8"                                                 "\x00"
        "cckpwroffset0=5"                                                    "\x00"
        //# PPR params
        "maxp2ga0=70"							    "\x00"
        "txpwrbckof=6"                                                       "\x00"
        "cckbw202gpo=0x4444"						    "\x00"
        "legofdmbw202gpo=0x88888888"					    "\x00"
        "mcsbw202gpo=0x88888888"					    "\x00"
        "propbw202gpo=0xdd"                                                  "\x00"
        //# OFDM IIR :
        "ofdmdigfilttype=18"                                                 "\x00"
        "ofdmdigfilttypebe=18"                                               "\x00"
        //# PAPD mode:
        "papdmode=1"                                                         "\x00"
        "papdvalidtest=1"                                                    "\x00"
        "pacalidx2g=42"							    "\x00"
        "papdepsoffset=-22"						    "\x00"
        "papdendidx=58"							    "\x00"
        "deadman_to=0xffffffff"                                              "\x00"
        //# muxenab: 0x1 for UART enable, 0x2 for GPIOs, 0x8 for JTAG
        "muxenab=0x11"                                                        "\x00"
        //# CLDO PWM voltage settings - 0x4 - 1.1 volt
        //#cldo_pwm=0x4                                                      "\x00"
        //#VCO freq 326.4MHz
        "spurconfig=0x3"                                                     "\x00"
        "\x00\x00";

#ifdef __cplusplus
} /* extern "C" */
#endif

#else /* ifndef INCLUDED_NVRAM_IMAGE_H_ */

#error Wi-Fi NVRAM image included twice

#endif /* ifndef INCLUDED_NVRAM_IMAGE_H_ */
