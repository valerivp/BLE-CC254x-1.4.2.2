/******************************************************************************

 @file  hal_board_cfg_nano.h

 @brief Declarations for the HAL configuration abstraction of a Universal Boot
        Loader for an 8051-based SOC using the USB transport by MSD.

 Group: WCS, BTS
 Target Device: CC2540, CC2541

 ******************************************************************************
 
 Copyright (c) 2011-2016, Texas Instruments Incorporated
 All rights reserved.

 IMPORTANT: Your use of this Software is limited to those specific rights
 granted under the terms of a software license agreement between the user
 who downloaded the software, his/her employer (which must be your employer)
 and Texas Instruments Incorporated (the "License"). You may not use this
 Software unless you agree to abide by the terms of the License. The License
 limits your use, and you acknowledge, that the Software may not be modified,
 copied or distributed unless embedded on a Texas Instruments microcontroller
 or used solely and exclusively in conjunction with a Texas Instruments radio
 frequency transceiver, which is integrated into your product. Other than for
 the foregoing purpose, you may not use, reproduce, copy, prepare derivative
 works of, modify, distribute, perform, display or sell this Software and/or
 its documentation for any purpose.

 YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
 PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
 INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
 NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
 TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
 NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
 LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
 INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
 OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
 OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
 (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

 Should you have any questions regarding your right to use this Software,
 contact Texas Instruments Incorporated at www.TI.com.

 ******************************************************************************
 Release Name: ble_sdk_1.4.2.2
 Release Date: 2016-06-09 06:57:10
 *****************************************************************************/
#ifndef HAL_BOARD_CFG_NANO_H
#define HAL_BOARD_CFG_NANO_H

/* ------------------------------------------------------------------------------------------------
 *                                           Includes
 * ------------------------------------------------------------------------------------------------
 */

#include "hal_mcu.h"

/* ------------------------------------------------------------------------------------------------
 *                                          Clock Speed
 * ------------------------------------------------------------------------------------------------
 */

#define OSC32K_CRYSTAL_INSTALLED  FALSE

/* 32 kHz clock source select in CLKCONCMD */
#if !defined (OSC32K_CRYSTAL_INSTALLED) || (defined (OSC32K_CRYSTAL_INSTALLED) && (OSC32K_CRYSTAL_INSTALLED == TRUE))
#define OSC_32KHZ  0x00 /* external 32 KHz xosc */
#else
#define OSC_32KHZ  0x80 /* internal 32 KHz rcosc */
#endif

/* ------------------------------------------------------------------------------------------------
 *                                           Constants
 * ------------------------------------------------------------------------------------------------
 */

// Flash is partitioned into 8 banks of 32 KB or 16 pages.
#define HAL_FLASH_PAGE_PER_BANK    16
// Flash is constructed of 128 pages of 2 KB.
#define HAL_FLASH_PAGE_SIZE        2048
#define HAL_FLASH_WORD_SIZE        4

// CODE banks get mapped into the XDATA range 8000-FFFF.
#define HAL_FLASH_PAGE_MAP         0x8000

// Re-defining Z_EXTADDR_LEN here so as not to include a Z-Stack .h file.
#define HAL_FLASH_IEEE_SIZE        8
#define HAL_FLASH_LOCK_BITS        16
#define HAL_FLASH_IEEE_PAGE        127
#define HAL_FLASH_IEEE_OSET       (HAL_FLASH_PAGE_SIZE - HAL_FLASH_LOCK_BITS - HAL_FLASH_IEEE_SIZE)
#define HAL_INFOP_IEEE_OSET        0xC

#define HAL_NV_DMA_CH              0
#define HAL_NV_DMA_GET_DESC()      HAL_DMA_GET_DESC0()
#define HAL_NV_DMA_SET_ADDR(a)     HAL_DMA_SET_ADDR_DESC0((a))

/* ------------------------------------------------------------------------------------------------
 *                                            Macros
 * ------------------------------------------------------------------------------------------------
 */

#define PREFETCH_ENABLE()     st( FCTL = 0x08; )
#define PREFETCH_DISABLE()    st( FCTL = 0x04; )

#define HAL_BOARD_INIT()  \
{ \
  IEN0 = 0;  \
  IEN1 = 0;  \
  IEN2 = 0;  \
  \
  CLKCONCMD = 0x80;  /* Select 32-kHz RC OSC & 32-MHz clk src. */\
  /* No dummy wait here - safe to assume 32-kHz calibration finishes before WatchDog is used. */\
  \
  PREFETCH_ENABLE();  \
  MCU_IO_INPUT_P0_PULLDOWN(0,0);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,1);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,2);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,3);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,4);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,5);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,6);                              \
  MCU_IO_INPUT_P0_PULLDOWN(0,7);                              \
  \
  MCU_IO_INPUT_P1_PULLDOWN(1,1);                              \
  MCU_IO_INPUT_P1_PULLDOWN(1,2);                              \
  MCU_IO_INPUT_P1_PULLDOWN(1,3);                              \
  MCU_IO_INPUT_P1_PULLDOWN(1,4);                              \
  MCU_IO_INPUT_P1_PULLDOWN(1,5);                              \
  MCU_IO_INPUT_P1_PULLDOWN(1,6);                              \
  MCU_IO_INPUT_P1_PULLDOWN(1,7);                              \
  \
  MCU_IO_INPUT_P2_PULLDOWN(2,3);                              \
  MCU_IO_INPUT_P2_PULLDOWN(2,4);                              \
  P2INP |= 0x6;                                               \
}

#define MCU_IO_INPUT_P0_PULLDOWN(port, pin)  st( P0SEL &= ~BV(pin); \
                                              P0DIR &= ~BV(pin); \
                                              P0INP &= ~BV(pin); \
                                              P2INP |= BV(port + 5); \
                                             )
#define MCU_IO_INPUT_P1_PULLDOWN(port, pin)  st( P1SEL &= ~BV(pin); \
                                              P1DIR &= ~BV(pin); \
                                              P1INP &= ~BV(pin); \
                                              P2INP |= BV(port + 5); \
                                             )
#define MCU_IO_INPUT_P2_PULLDOWN(port, pin)  st( P2SEL &= ~BV(pin); \
                                              P2DIR &= ~BV(pin); \
                                              P2INP &= ~BV(pin); \
                                              P2INP |= BV(port + 5); \
                                             )

/* ----------- Minimum safe bus voltage ---------- */

// Vdd/3 / Internal Reference X ENOB --> (Vdd / 3) / 1.15 X 127
#define VDD_2_0  74   // 2.0 V required to safely read/write internal flash.

#define VDD_MIN_RUN   VDD_2_0
#define VDD_MIN_NV   (VDD_2_0+4)  // 5% margin over minimum to survive a page erase and compaction.
#define VDD_MIN_XNV  (VDD_2_7+5)  // 5% margin over minimum to survive a page erase and compaction.

#endif
/*******************************************************************************************************
*/
