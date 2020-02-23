/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       Plantsensor.h
 *
 *  @brief      CC1310 LaunchPad Board Specific header file.
 *
 *  NB! This is the board file for CC1310 LaunchPad PCB version 1.0
 *
 *  ============================================================================
 */
#ifndef __Plantsensor_BOARD_H__
#define __Plantsensor_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/** ============================================================================
 *  Includes
 *  ==========================================================================*/
#include <ti/drivers/PIN.h>
#include <driverlib/ioc.h>

/** ============================================================================
 *  Externs
 *  ==========================================================================*/
extern const PIN_Config BoardGpioInitTable[];

/** ============================================================================
 *  Defines
 *  ==========================================================================*/
#define Plantsensor

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>        <pin mapping>   <comments>
 */

/* Discrete outputs */
#define Board_RLED                  IOID_8
//#define Board_GLED                  IOID_7
#define Board_LED_ON                1
#define Board_LED_OFF               0

/* Discrete inputs */
#define Board_BTN1                  PIN_UNASSIGNED
#define Board_BTN2                  PIN_UNASSIGNED

/* UART Board */
#define Board_UART_RX               IOID_1          /* RXD  */
#define Board_UART_TX               IOID_0          /* TXD  */
//#define Board_UART_CTS              IOID_19         /* CTS  */
//#define Board_UART_RTS              IOID_18         /* RTS */

/* SPI Board */
//#define Board_SPI0_MISO             IOID_8          /* RF1.20 */
//#define Board_SPI0_MOSI             IOID_9          /* RF1.18 */
//#define Board_SPI0_CLK              IOID_10         /* RF1.16 */
//#define Board_SPI0_CSN              PIN_UNASSIGNED
//#define Board_SPI1_MISO             PIN_UNASSIGNED
//#define Board_SPI1_MOSI             PIN_UNASSIGNED
//#define Board_SPI1_CLK              PIN_UNASSIGNED
//#define Board_SPI1_CSN              PIN_UNASSIGNED

/* I2C */
#define Board_I2C0_SCL0             IOID_6
#define Board_I2C0_SDA0             IOID_5

/* SPI */
//#define Board_SPI_FLASH_CS          IOID_20
//#define Board_FLASH_CS_ON           0
//#define Board_FLASH_CS_OFF          1

/* Booster pack generic */
#define Board_PWR                   IOID_2
#define Board_PWR_ON                1
#define Board_PWR_OFF               0
#define Board_EN_BYP                IOID_3
#define Board_BYP_ON                0
#define Board_BYP_OFF               1
#define Board_DIO4                  PIN_UNASSIGNED
#define Board_DIO7                  PIN_UNASSIGNED

#define Board_SENSOR_LIGHT          IOID_9
#define Board_SENSOR_SOIL           IOID_10
#define Board_SENSOR_BAT            IOID_11

///* Booster pack LCD (430BOOST - Sharp96 Rev 1.1) */
//#define Board_LCD_CS                IOID_24 // SPI chip select
//#define Board_LCD_EXTCOMIN          IOID_12 // External COM inversion
//#define Board_LCD_ENABLE            IOID_22 // LCD enable
//#define Board_LCD_POWER             IOID_23 // LCD power control
//#define Board_LCD_CS_ON             1
//#define Board_LCD_CS_OFF            0

/* PWM outputs */
#define Board_PWMPIN0               Board_RLED
#define Board_PWMPIN1               PIN_UNASSIGNED
#define Board_PWMPIN2               PIN_UNASSIGNED
#define Board_PWMPIN3               PIN_UNASSIGNED
#define Board_PWMPIN4               PIN_UNASSIGNED
#define Board_PWMPIN5               PIN_UNASSIGNED
#define Board_PWMPIN6               PIN_UNASSIGNED
#define Board_PWMPIN7               PIN_UNASSIGNED

/** ============================================================================
 *  Instance identifiers
 *  ==========================================================================*/
/* Generic SPI instance identifiers */
//#define Board_SPI0                  Plantsensor_SPI0
/* Generic UART instance identifiers */
#define Board_UART                  Plantsensor_UART0
/* Generic Crypto instance identifiers */
#define Board_CRYPTO                Plantsensor_CRYPTO0

#define Board_I2C0                  Plantsensor_I2C0

/* Generic GPTimer instance identifiers */
#define Board_GPTIMER0A             Plantsensor_GPTIMER0A
#define Board_GPTIMER0B             Plantsensor_GPTIMER0B
#define Board_GPTIMER1A             Plantsensor_GPTIMER1A
#define Board_GPTIMER1B             Plantsensor_GPTIMER1B
#define Board_GPTIMER2A             Plantsensor_GPTIMER2A
#define Board_GPTIMER2B             Plantsensor_GPTIMER2B
#define Board_GPTIMER3A             Plantsensor_GPTIMER3A
#define Board_GPTIMER3B             Plantsensor_GPTIMER3B
/* Generic PWM instance identifiers */
#define Board_PWM0                  Plantsensor_PWM0
#define Board_PWM1                  Plantsensor_PWM1
#define Board_PWM2                  Plantsensor_PWM2
#define Board_PWM3                  Plantsensor_PWM3
#define Board_PWM4                  Plantsensor_PWM4
#define Board_PWM5                  Plantsensor_PWM5
#define Board_PWM6                  Plantsensor_PWM6
#define Board_PWM7                  Plantsensor_PWM7

/** ============================================================================
 *  Number of peripherals and their names
 *  ==========================================================================*/

/*!
 *  @def    Plantsensor_I2CName
 *  @brief  Enum of I2C names on the CC2650 dev board
 */
typedef enum Plantsensor_I2CName {
    Plantsensor_I2C0 = 0,

    Plantsensor_I2CCOUNT
} Plantsensor_I2CName;

/*!
 *  @def    Plantsensor_CryptoName
 *  @brief  Enum of Crypto names on the CC2650 dev board
 */
typedef enum Plantsensor_CryptoName {
    Plantsensor_CRYPTO0 = 0,

    Plantsensor_CRYPTOCOUNT
} Plantsensor_CryptoName;


/*!
 *  @def    Plantsensor_SPIName
 *  @brief  Enum of SPI names on the CC2650 dev board
 */
typedef enum Plantsensor_SPIName {
    //Plantsensor_SPI0 = 0,
    //Plantsensor_SPI1,

    Plantsensor_SPICOUNT
} Plantsensor_SPIName;

/*!
 *  @def    Plantsensor_UARTName
 *  @brief  Enum of UARTs on the CC2650 dev board
 */
typedef enum Plantsensor_UARTName {
    Plantsensor_UART0 = 0,

    Plantsensor_UARTCOUNT
} Plantsensor_UARTName;

/*!
 *  @def    Plantsensor_UdmaName
 *  @brief  Enum of DMA buffers
 */
typedef enum Plantsensor_UdmaName {
    Plantsensor_UDMA0 = 0,

    Plantsensor_UDMACOUNT
} Plantsensor_UdmaName;
/*!
 *  @def    Plantsensor_GPTimerName
 *  @brief  Enum of GPTimer parts
 */
typedef enum Plantsensor_GPTimerName
{
    Plantsensor_GPTIMER0A = 0,
    Plantsensor_GPTIMER0B,
    Plantsensor_GPTIMER1A,
    Plantsensor_GPTIMER1B,
    Plantsensor_GPTIMER2A,
    Plantsensor_GPTIMER2B,
    Plantsensor_GPTIMER3A,
    Plantsensor_GPTIMER3B,
    Plantsensor_GPTIMERPARTSCOUNT
} Plantsensor_GPTimerName;

/*!
 *  @def    Plantsensor_GPTimers
 *  @brief  Enum of GPTimers
 */
typedef enum Plantsensor_GPTimers
{
    Plantsensor_GPTIMER0 = 0,
    Plantsensor_GPTIMER1,
    Plantsensor_GPTIMER2,
    Plantsensor_GPTIMER3,
    Plantsensor_GPTIMERCOUNT
} Plantsensor_GPTimers;

/*!
 *  @def    Plantsensor_PWM
 *  @brief  Enum of PWM outputs on the board
 */
typedef enum Plantsensor_PWM
{
    Plantsensor_PWM0 = 0,
    Plantsensor_PWM1,
    Plantsensor_PWM2,
    Plantsensor_PWM3,
    Plantsensor_PWM4,
    Plantsensor_PWM5,
    Plantsensor_PWM6,
    Plantsensor_PWM7,
    Plantsensor_PWMCOUNT
} Plantsensor_PWM;

/*!
 *  @def    Plantsensor_ADCBufName
 *  @brief  Enum of ADCBufs
 */
typedef enum Plantsensor_ADCBufName {
    Plantsensor_ADCBuf0 = 0,
    Plantsensor_ADCBufCOUNT
} Plantsensor_ADCBufName;

/*!
 *  @def    Plantsensor_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum Plantsensor_ADCName {
    Plantsensor_ADC0 = 0,
    Plantsensor_ADC1,
    Plantsensor_ADC2,
    Plantsensor_ADC3,
    Plantsensor_ADC4,
    Plantsensor_ADC5,
    Plantsensor_ADC6,
    Plantsensor_ADC7,
    Plantsensor_ADCDCOUPL,
    Plantsensor_ADCVSS,
    Plantsensor_ADCVDDS,
    Plantsensor_ADCCOUNT
} Plantsensor_ADCName;

/*!
 *  @def    Plantsensor_WatchdogName
 *  @brief  Enum of Watchdogs on the Plantsensor dev board
 */
typedef enum Plantsensor_WatchdogName {
    Plantsensor_WATCHDOG0 = 0,

    Plantsensor_WATCHDOGCOUNT
} Plantsensor_WatchdogName;

#ifdef __cplusplus
}
#endif

#endif /* __Plantsensor_BOARD_H__ */
