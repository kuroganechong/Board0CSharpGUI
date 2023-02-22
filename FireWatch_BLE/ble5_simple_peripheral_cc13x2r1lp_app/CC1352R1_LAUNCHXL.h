/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
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
/** ===========================================================================
 *  @file       CC1352R1_LAUNCHXL.h
 *
 *  @brief      CC1352R1_LAUNCHXL Board Specific header file.
 *
 *  The CC1352R1_LAUNCHXL header file should be included in an application as
 *  follows:
 *  @code
 *  #include "CC1352R1_LAUNCHXL.h"
 *  @endcode
 *
 *  ===========================================================================
 */
#ifndef __CC1352R1_LAUNCHXL_BOARD_H__
#define __CC1352R1_LAUNCHXL_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <ti/drivers/PIN.h>
#include <ti/devices/cc13x2_cc26x2/driverlib/ioc.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Defines */
//#define CC1352R1_LAUNCHXL

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>         <pin mapping>   <comments>
 */

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>                  <pin mapping>
 */
/* Analog Capable DIOs */
#define CC1352R1_LAUNCHXL_DIO23_ANALOG          PIN_UNASSIGNED//IOID_23
#define CC1352R1_LAUNCHXL_DIO24_ANALOG          PIN_UNASSIGNED//IOID_24
#define CC1352R1_LAUNCHXL_DIO25_ANALOG          PIN_UNASSIGNED//IOID_25
#define CC1352R1_LAUNCHXL_DIO26_ANALOG          PIN_UNASSIGNED//IOID_26
#define CC1352R1_LAUNCHXL_DIO27_ANALOG          PIN_UNASSIGNED//IOID_27
#define CC1352R1_LAUNCHXL_DIO28_ANALOG          PIN_UNASSIGNED//IOID_28
#define CC1352R1_LAUNCHXL_DIO29_ANALOG          PIN_UNASSIGNED//IOID_29

/* Antenna switch */
#define CC1352R1_LAUNCHXL_DIO30_RF_SUB1GHZ      IOID_30

/* Digital IOs */
#define CC1352R1_LAUNCHXL_DIO12                 IOID_12
#define CC1352R1_LAUNCHXL_DIO15                 IOID_15
#define CC1352R1_LAUNCHXL_DIO16_TDO             IOID_16
#define CC1352R1_LAUNCHXL_DIO17_TDI             IOID_17
#define CC1352R1_LAUNCHXL_DIO21                 IOID_21
#define CC1352R1_LAUNCHXL_DIO22                 IOID_22

/* Discrete Inputs */
#define CC1352R1_LAUNCHXL_PIN_BTN1              PIN_UNASSIGNED//IOID_15
#define CC1352R1_LAUNCHXL_PIN_BTN2              PIN_UNASSIGNED//IOID_14

/* GPIO */
#define CC1352R1_LAUNCHXL_GPIO_LED_ON           1
#define CC1352R1_LAUNCHXL_GPIO_LED_OFF          0

/* I2C */
#define CC1352R1_LAUNCHXL_I2C0_SCL0             PIN_UNASSIGNED//IOID_4
#define CC1352R1_LAUNCHXL_I2C0_SDA0             PIN_UNASSIGNED//IOID_5


/* LEDs */
#define CC1352R1_LAUNCHXL_PIN_LED_ON            1
#define CC1352R1_LAUNCHXL_PIN_LED_OFF           0
#define Board_LED1                              IOID_6
#define Board_LED2                              IOID_7

/* PWM Outputs */
#define CC1352R1_LAUNCHXL_PWMPIN0               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN1               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN2               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN3               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN4               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN5               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN6               PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_PWMPIN7               PIN_UNASSIGNED

/* SPI */
#define CC1352R1_LAUNCHXL_SPI_FLASH_CS          PIN_UNASSIGNED//IOID_20
#define CC1352R1_LAUNCHXL_FLASH_CS_ON           0
#define CC1352R1_LAUNCHXL_FLASH_CS_OFF          1

/* SPI Board */
#define CC1352R1_LAUNCHXL_SPI0_MISO             IOID_8          /* RF1.20 */
#define CC1352R1_LAUNCHXL_SPI0_MOSI             IOID_9          /* RF1.18 */
#define CC1352R1_LAUNCHXL_SPI0_CLK              IOID_10         /* RF1.16 */
#define CC1352R1_LAUNCHXL_SPI0_CSN              PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_SPI1_MISO             IOID_20//PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_SPI1_MOSI             IOID_21//PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_SPI1_CLK              IOID_19//PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_SPI1_CSN              IOID_18//PIN_UNASSIGNED
#define CC1352_SPI1_CTS_BLE_EXT                 IOID_22        //Board_SPI0_CTS

/* UART Board */
#define CC1352R1_LAUNCHXL_UART0_RX              PIN_UNASSIGNED//IOID_12         /* RXD */
#define CC1352R1_LAUNCHXL_UART0_TX              PIN_UNASSIGNED//IOID_13         /* TXD */
#define CC1352R1_LAUNCHXL_UART0_CTS             IOID_19         /* CTS */
#define CC1352R1_LAUNCHXL_UART0_RTS             IOID_18         /* RTS */
#define CC1352R1_LAUNCHXL_UART1_RX              IOID_24//PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_UART1_TX              IOID_27//PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_UART1_CTS             PIN_UNASSIGNED
#define CC1352R1_LAUNCHXL_UART1_RTS             PIN_UNASSIGNED
#define Board_GPS_POWER                         IOID_11
#define Board_GPS_RESET                         IOID_28
#define Board_GPS_ONOFF                         IOID_26
#define Board_GPS_WAKE                          IOID_25
/* For backward compatibility */
//#define CC1352R1_LAUNCHXL_UART_RX               CC1352R1_LAUNCHXL_UART0_RX
//#define CC1352R1_LAUNCHXL_UART_TX               CC1352R1_LAUNCHXL_UART0_TX
//#define CC1352R1_LAUNCHXL_UART_CTS              CC1352R1_LAUNCHXL_UART0_CTS
//#define CC1352R1_LAUNCHXL_UART_RTS              CC1352R1_LAUNCHXL_UART0_RTS

#define Board_KEY_SELECT                    PIN_UNASSIGNED
#define Board_KEY_UP                        PIN_UNASSIGNED
#define Board_KEY_DOWN                      PIN_UNASSIGNED
#define Board_KEY_LEFT                      PIN_UNASSIGNED
#define Board_KEY_RIGHT                     PIN_UNASSIGNED
#define Board_PIN_BUTTON0                   PIN_UNASSIGNED
#define Board_PIN_BUTTON1                   PIN_UNASSIGNED

//==================================================================================//

#define Board_init()             CC1352R1_LAUNCHXL_initGeneral()
#define Board_initGeneral()      CC1352R1_LAUNCHXL_initGeneral()
#define Board_shutDownExtFlash() CC1352R1_LAUNCHXL_shutDownExtFlash()
#define Board_wakeUpExtFlash()   CC1352R1_LAUNCHXL_wakeUpExtFlash()

/* These #defines allow us to reuse TI-RTOS across other device families */

#define Board_ADC0              CC1352R1_LAUNCHXL_ADC0
#define Board_ADC1              CC1352R1_LAUNCHXL_ADC1

#define Board_ADCBUF0           CC1352R1_LAUNCHXL_ADCBUF0
#define Board_ADCBUF0CHANNEL0   CC1352R1_LAUNCHXL_ADCBUF0CHANNEL0
#define Board_ADCBUF0CHANNEL1   CC1352R1_LAUNCHXL_ADCBUF0CHANNEL1

#define Board_ECDH0             CC1352R1_LAUNCHXL_ECDH0
#define Board_ECDSA0            CC1352R1_LAUNCHXL_ECDSA0
#define Board_ECJPAKE0          CC1352R1_LAUNCHXL_ECJPAKE0
#define Board_AESCCM0           CC1352R1_LAUNCHXL_AESCCM0
#define Board_AESGCM0           CC1352R1_LAUNCHXL_AESGCM0
#define Board_AESCBC0           CC1352R1_LAUNCHXL_AESCBC0
#define Board_AESCTR0           CC1352R1_LAUNCHXL_AESCTR0
#define Board_AESECB0           CC1352R1_LAUNCHXL_AESECB0
#define Board_SHA20             CC1352R1_LAUNCHXL_SHA20

#define Board_DIO12             CC1352R1_LAUNCHXL_DIO12
#define Board_DIO15             CC1352R1_LAUNCHXL_DIO15
#define Board_DIO16_TDO         CC1352R1_LAUNCHXL_DIO16_TDO
#define Board_DIO17_TDI         CC1352R1_LAUNCHXL_DIO17_TDI
#define Board_DIO21             CC1352R1_LAUNCHXL_DIO21
#define Board_DIO22             CC1352R1_LAUNCHXL_DIO22

#define Board_DIO23_ANALOG      CC1352R1_LAUNCHXL_DIO23_ANALOG
#define Board_DIO24_ANALOG      CC1352R1_LAUNCHXL_DIO24_ANALOG
#define Board_DIO25_ANALOG      CC1352R1_LAUNCHXL_DIO25_ANALOG
#define Board_DIO26_ANALOG      CC1352R1_LAUNCHXL_DIO26_ANALOG
#define Board_DIO27_ANALOG      CC1352R1_LAUNCHXL_DIO27_ANALOG
#define Board_DIO28_ANALOG      CC1352R1_LAUNCHXL_DIO28_ANALOG
#define Board_DIO29_ANALOG      CC1352R1_LAUNCHXL_DIO29_ANALOG
#define Board_DIO30_RFSW        CC1352R1_LAUNCHXL_DIO30_RF_SUB1GHZ

/*
 *  Board_RF_SUB1GHZ is the name generated by SysConfig. Define it
 *  here so that RF callback function can reference it.
 */
#define Board_RF_SUB1GHZ        CC1352R1_LAUNCHXL_DIO30_RF_SUB1GHZ

#define Board_GPIO_BUTTON0      CC1352R1_LAUNCHXL_GPIO_S1
#define Board_GPIO_BUTTON1      CC1352R1_LAUNCHXL_GPIO_S2
#define Board_GPIO_BTN1         CC1352R1_LAUNCHXL_GPIO_S1
#define Board_GPIO_BTN2         CC1352R1_LAUNCHXL_GPIO_S2
#define Board_GPIO_LED0         CC1352R1_LAUNCHXL_GPIO_LED_RED
#define Board_GPIO_LED1         CC1352R1_LAUNCHXL_GPIO_LED_GREEN
#define Board_GPIO_LED2         CC1352R1_LAUNCHXL_GPIO_LED_RED
#define Board_GPIO_RLED         CC1352R1_LAUNCHXL_GPIO_LED_RED
#define Board_GPIO_GLED         CC1352R1_LAUNCHXL_GPIO_LED_GREEN
#define Board_GPIO_LED_ON       CC1352R1_LAUNCHXL_GPIO_LED_ON
#define Board_GPIO_LED_OFF      CC1352R1_LAUNCHXL_GPIO_LED_OFF
#define Board_GPIO_TMP116_EN    CC1352R1_LAUNCHXL_GPIO_TMP116_EN

#define Board_GPTIMER0A         CC1352R1_LAUNCHXL_GPTIMER0A
#define Board_GPTIMER0B         CC1352R1_LAUNCHXL_GPTIMER0B
#define Board_GPTIMER1A         CC1352R1_LAUNCHXL_GPTIMER1A
#define Board_GPTIMER1B         CC1352R1_LAUNCHXL_GPTIMER1B
#define Board_GPTIMER2A         CC1352R1_LAUNCHXL_GPTIMER2A
#define Board_GPTIMER2B         CC1352R1_LAUNCHXL_GPTIMER2B
#define Board_GPTIMER3A         CC1352R1_LAUNCHXL_GPTIMER3A
#define Board_GPTIMER3B         CC1352R1_LAUNCHXL_GPTIMER3B

#define Board_I2C0              CC1352R1_LAUNCHXL_I2C0
#define Board_I2C_TMP           Board_I2C0

#define Board_NVSINTERNAL       CC1352R1_LAUNCHXL_NVSCC26XX0
#define Board_NVSINTERNAL1      CC1352R1_LAUNCHXL_NVSCC26XX1
#define Board_NVSEXTERNAL       CC1352R1_LAUNCHXL_NVSSPI25X0

//#define Board_PIN_BUTTON0       CC1352R1_LAUNCHXL_PIN_BTN1
//#define Board_PIN_BUTTON1       CC1352R1_LAUNCHXL_PIN_BTN2
#define Board_PIN_BTN1          CC1352R1_LAUNCHXL_PIN_BTN1
#define Board_PIN_BTN2          CC1352R1_LAUNCHXL_PIN_BTN2
#define Board_PIN_LED0          Board_LED1
#define Board_PIN_LED1          Board_LED2
#define Board_PIN_LED2          Board_LED1
#define Board_PIN_RLED          Board_LED1
#define Board_PIN_GLED          Board_LED2

#define Board_PWM0              CC1352R1_LAUNCHXL_PWM0
#define Board_PWM1              CC1352R1_LAUNCHXL_PWM1
#define Board_PWM2              CC1352R1_LAUNCHXL_PWM2
#define Board_PWM3              CC1352R1_LAUNCHXL_PWM3
#define Board_PWM4              CC1352R1_LAUNCHXL_PWM4
#define Board_PWM5              CC1352R1_LAUNCHXL_PWM5
#define Board_PWM6              CC1352R1_LAUNCHXL_PWM6
#define Board_PWM7              CC1352R1_LAUNCHXL_PWM7

#define Board_SD0               CC1352R1_LAUNCHXL_SDSPI0

#define Board_SPI0              CC1352R1_LAUNCHXL_SPI0
#define Board_SPI1              CC1352R1_LAUNCHXL_SPI1
#define Board_SPI_FLASH_CS      CC1352R1_LAUNCHXL_SPI_FLASH_CS
#define Board_FLASH_CS_ON       0
#define Board_FLASH_CS_OFF      1

#define Board_SPI_MASTER        CC1352R1_LAUNCHXL_SPI0
#define Board_SPI_SLAVE         CC1352R1_LAUNCHXL_SPI0
#define Board_SPI_MASTER_READY  CC1352R1_LAUNCHXL_SPI_MASTER_READY
#define Board_SPI_SLAVE_READY   CC1352R1_LAUNCHXL_SPI_SLAVE_READY

#define Board_UART0             CC1352R1_LAUNCHXL_UART0
#define Board_UART1             CC1352R1_LAUNCHXL_UART1

#define Board_WATCHDOG0         CC1352R1_LAUNCHXL_WATCHDOG0
/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
void CC1352R1_LAUNCHXL_initGeneral(void);

/*!
 *  @brief  Shut down the external flash present on the board files
 *
 *  This function bitbangs the SPI sequence necessary to turn off
 *  the external flash on LaunchPads.
 */
void CC1352R1_LAUNCHXL_shutDownExtFlash(void);

/*!
 *  @brief  Wake up the external flash present on the board files
 *
 *  This function toggles the chip select for the amount of time needed
 *  to wake the chip up.
 */
void CC1352R1_LAUNCHXL_wakeUpExtFlash(void);

/*!
 *  @def    CC1352R1_LAUNCHXL_ADCBufName
 *  @brief  Enum of ADCs
 */
typedef enum CC1352R1_LAUNCHXL_ADCBufName {
    CC1352R1_LAUNCHXL_ADCBUF0 = 0,

    CC1352R1_LAUNCHXL_ADCBUFCOUNT
} CC1352R1_LAUNCHXL_ADCBufName;

/*!
 *  @def    CC1352R1_LAUNCHXL_ADCBuf0SourceName
 *  @brief  Enum of ADCBuf channels
 */
typedef enum CC1352R1_LAUNCHXL_ADCBuf0ChannelName {
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL0 = 0,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL1,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL2,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL3,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL4,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL5,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNEL6,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNELVDDS,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNELDCOUPL,
    CC1352R1_LAUNCHXL_ADCBUF0CHANNELVSS,

    CC1352R1_LAUNCHXL_ADCBUF0CHANNELCOUNT
} CC1352R1_LAUNCHXL_ADCBuf0ChannelName;

/*!
 *  @def    CC1352R1_LAUNCHXL_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum CC1352R1_LAUNCHXL_ADCName {
    CC1352R1_LAUNCHXL_ADC0 = 0,
    CC1352R1_LAUNCHXL_ADC1,
    CC1352R1_LAUNCHXL_ADC2,
    CC1352R1_LAUNCHXL_ADC3,
    CC1352R1_LAUNCHXL_ADC4,
    CC1352R1_LAUNCHXL_ADC5,
    CC1352R1_LAUNCHXL_ADC6,
    CC1352R1_LAUNCHXL_ADCDCOUPL,
    CC1352R1_LAUNCHXL_ADCVSS,
    CC1352R1_LAUNCHXL_ADCVDDS,

    CC1352R1_LAUNCHXL_ADCCOUNT
} CC1352R1_LAUNCHXL_ADCName;

/*!
 *  @def    CC1352R1_LAUNCHXL_ECDHName
 *  @brief  Enum of ECDH names
 */
typedef enum CC1352R1_LAUNCHXL_ECDHName {
    CC1352R1_LAUNCHXL_ECDH0 = 0,

    CC1352R1_LAUNCHXL_ECDHCOUNT
} CC1352R1_LAUNCHXL_ECDHName;

/*!
 *  @def    CC1352R1_LAUNCHXL_ECDSAName
 *  @brief  Enum of ECDSA names
 */
typedef enum CC1352R1_LAUNCHXL_ECDSAName {
    CC1352R1_LAUNCHXL_ECDSA0 = 0,

    CC1352R1_LAUNCHXL_ECDSACOUNT
} CC1352R1_LAUNCHXL_ECDSAName;

/*!
 *  @def    CC1352R1_LAUNCHXL_ECJPAKEName
 *  @brief  Enum of ECJPAKE names
 */
typedef enum CC1352R1_LAUNCHXL_ECJPAKEName {
    CC1352R1_LAUNCHXL_ECJPAKE0 = 0,

    CC1352R1_LAUNCHXL_ECJPAKECOUNT
} CC1352R1_LAUNCHXL_ECJPAKEName;

/*!
 *  @def    CC1352R1_LAUNCHXL_AESCCMName
 *  @brief  Enum of AESCCM names
                CC1352R1_LAUNCHXL_AESCCM0 = 0 \\ BLE
                CC1352R1_LAUNCHXL_AESCCM1 = 1 \\ TIMAC
                etc...
 */
typedef enum CC1352R1_LAUNCHXL_AESCCMName {
    CC1352R1_LAUNCHXL_AESCCM0 = 0,

    CC1352R1_LAUNCHXL_AESCCMCOUNT
} CC1352R1_LAUNCHXL_AESCCMName;

/*!
 *  @def    CC1352R1_LAUNCHXL_AESGCMName
 *  @brief  Enum of AESGCM names
 */
typedef enum CC1352R1_LAUNCHXL_AESGCMName {
    CC1352R1_LAUNCHXL_AESGCM0 = 0,

    CC1352R1_LAUNCHXL_AESGCMCOUNT
} CC1352R1_LAUNCHXL_AESGCMName;

/*!
 *  @def    CC1352R1_LAUNCHXL_AESCBCName
 *  @brief  Enum of AESCBC names
 */
typedef enum CC1352R1_LAUNCHXL_AESCBCName {
    CC1352R1_LAUNCHXL_AESCBC0 = 0,

    CC1352R1_LAUNCHXL_AESCBCCOUNT
} CC1352R1_LAUNCHXL_AESCBCName;

/*!
 *  @def    CC1352R1_LAUNCHXL_AESCTRName
 *  @brief  Enum of AESCTR names
 */
typedef enum CC1352R1_LAUNCHXL_AESCTRName {
    CC1352R1_LAUNCHXL_AESCTR0 = 0,

    CC1352R1_LAUNCHXL_AESCTRCOUNT
} CC1352R1_LAUNCHXL_AESCTRName;

/*!
 *  @def    CC1352R1_LAUNCHXL_AESECBName
 *  @brief  Enum of AESECB names
 */
typedef enum CC1352R1_LAUNCHXL_AESECBName {
    CC1352R1_LAUNCHXL_AESECB0 = 0,

    CC1352R1_LAUNCHXL_AESECBCOUNT
} CC1352R1_LAUNCHXL_AESECBName;

/*!
 *  @def    CC1352R1_LAUNCHXL_SHA2Name
 *  @brief  Enum of SHA2 names
 */
typedef enum CC1352R1_LAUNCHXL_SHA2Name {
    CC1352R1_LAUNCHXL_SHA20 = 0,

    CC1352R1_LAUNCHXL_SHA2COUNT
} CC1352R1_LAUNCHXL_SHA2Name;

/*!
 *  @def    CC1352R1_LAUNCHXL_GPIOName
 *  @brief  Enum of GPIO names
 */
typedef enum CC1352R1_LAUNCHXL_GPIOName {
    CC1352R1_LAUNCHXL_GPIO_S1 = 0,
    CC1352R1_LAUNCHXL_GPIO_S2,
    CC1352R1_LAUNCHXL_SPI_MASTER_READY,
    CC1352R1_LAUNCHXL_SPI_SLAVE_READY,
    CC1352R1_LAUNCHXL_GPIO_LED_GREEN,
    CC1352R1_LAUNCHXL_GPIO_LED_RED,
    CC1352R1_LAUNCHXL_GPIO_TMP116_EN,
    CC1352R1_LAUNCHXL_GPIO_SPI_FLASH_CS,
    CC1352R1_LAUNCHXL_SDSPI_CS,
    CC1352R1_LAUNCHXL_GPIO_LCD_CS,
    CC1352R1_LAUNCHXL_GPIO_LCD_POWER,
    CC1352R1_LAUNCHXL_GPIO_LCD_ENABLE,
    CC1352R1_LAUNCHXL_GPIOCOUNT
} CC1352R1_LAUNCHXL_GPIOName;

/*!
 *  @def    CC1352R1_LAUNCHXL_GPTimerName
 *  @brief  Enum of GPTimer parts
 */
typedef enum CC1352R1_LAUNCHXL_GPTimerName {
    CC1352R1_LAUNCHXL_GPTIMER0A = 0,
    CC1352R1_LAUNCHXL_GPTIMER0B,
    CC1352R1_LAUNCHXL_GPTIMER1A,
    CC1352R1_LAUNCHXL_GPTIMER1B,
    CC1352R1_LAUNCHXL_GPTIMER2A,
    CC1352R1_LAUNCHXL_GPTIMER2B,
    CC1352R1_LAUNCHXL_GPTIMER3A,
    CC1352R1_LAUNCHXL_GPTIMER3B,

    CC1352R1_LAUNCHXL_GPTIMERPARTSCOUNT
} CC1352R1_LAUNCHXL_GPTimerName;

/*!
 *  @def    CC1352R1_LAUNCHXL_GPTimers
 *  @brief  Enum of GPTimers
 */
typedef enum CC1352R1_LAUNCHXL_GPTimers {
    CC1352R1_LAUNCHXL_GPTIMER0 = 0,
    CC1352R1_LAUNCHXL_GPTIMER1,
    CC1352R1_LAUNCHXL_GPTIMER2,
    CC1352R1_LAUNCHXL_GPTIMER3,

    CC1352R1_LAUNCHXL_GPTIMERCOUNT
} CC1352R1_LAUNCHXL_GPTimers;

/*!
 *  @def    CC1352R1_LAUNCHXL_I2CName
 *  @brief  Enum of I2C names
 */
typedef enum CC1352R1_LAUNCHXL_I2CName {
    CC1352R1_LAUNCHXL_I2C0 = 0,

    CC1352R1_LAUNCHXL_I2CCOUNT
} CC1352R1_LAUNCHXL_I2CName;

/*!
 *  @def    CC1352R1_LAUNCHXL_NVSName
 *  @brief  Enum of NVS names
 */
typedef enum CC1352R1_LAUNCHXL_NVSName {
#if !defined(NO_OSAL_SNV)
#ifndef Board_EXCLUDE_NVS_INTERNAL_FLASH
    CC1352R1_LAUNCHXL_NVSCC26XX0 = 0,
#endif
#endif // NO_OSAL_SNV
#ifdef OAD_ONCHIP
    CC1352R1_LAUNCHXL_NVSCC26XX1,
#endif //OAD_ONCHIP    
#ifdef NVSSPI
#ifndef Board_EXCLUDE_NVS_EXTERNAL_FLASH
    CC1352R1_LAUNCHXL_NVSSPI25X0,
#endif
#endif // NVSSPI
    CC1352R1_LAUNCHXL_NVSCOUNT
} CC1352R1_LAUNCHXL_NVSName;

/*!
 *  @def    CC1352R1_LAUNCHXL_PWM
 *  @brief  Enum of PWM outputs
 */
typedef enum CC1352R1_LAUNCHXL_PWMName {
    CC1352R1_LAUNCHXL_PWM0 = 0,
    CC1352R1_LAUNCHXL_PWM1,
    CC1352R1_LAUNCHXL_PWM2,
    CC1352R1_LAUNCHXL_PWM3,
    CC1352R1_LAUNCHXL_PWM4,
    CC1352R1_LAUNCHXL_PWM5,
    CC1352R1_LAUNCHXL_PWM6,
    CC1352R1_LAUNCHXL_PWM7,

    CC1352R1_LAUNCHXL_PWMCOUNT
} CC1352R1_LAUNCHXL_PWMName;

/*!
 *  @def    CC1352R1_LAUNCHXL_SDName
 *  @brief  Enum of SD names
 */
typedef enum CC1352R1_LAUNCHXL_SDName {
    CC1352R1_LAUNCHXL_SDSPI0 = 0,

    CC1352R1_LAUNCHXL_SDCOUNT
} CC1352R1_LAUNCHXL_SDName;

/*!
 *  @def    CC1352R1_LAUNCHXL_SPIName
 *  @brief  Enum of SPI names
 */
typedef enum CC1352R1_LAUNCHXL_SPIName {
    CC1352R1_LAUNCHXL_SPI0 = 0,
    CC1352R1_LAUNCHXL_SPI1,

    CC1352R1_LAUNCHXL_SPICOUNT
} CC1352R1_LAUNCHXL_SPIName;

/*!
 *  @def    CC1352R1_LAUNCHXL_UARTName
 *  @brief  Enum of UARTs
 */
typedef enum CC1352R1_LAUNCHXL_UARTName {
    CC1352R1_LAUNCHXL_UART0 = 0,
    CC1352R1_LAUNCHXL_UART1,

    CC1352R1_LAUNCHXL_UARTCOUNT
} CC1352R1_LAUNCHXL_UARTName;

/*!
 *  @def    CC1352R1_LAUNCHXL_UDMAName
 *  @brief  Enum of DMA buffers
 */
typedef enum CC1352R1_LAUNCHXL_UDMAName {
    CC1352R1_LAUNCHXL_UDMA0 = 0,

    CC1352R1_LAUNCHXL_UDMACOUNT
} CC1352R1_LAUNCHXL_UDMAName;

/*!
 *  @def    CC1352R1_LAUNCHXL_WatchdogName
 *  @brief  Enum of Watchdogs
 */
typedef enum CC1352R1_LAUNCHXL_WatchdogName {
    CC1352R1_LAUNCHXL_WATCHDOG0 = 0,

    CC1352R1_LAUNCHXL_WATCHDOGCOUNT
} CC1352R1_LAUNCHXL_WatchdogName;

/*!
 *  @def    CC1352R1_LAUNCHXL_TRNGName
 *  @brief  Enum of TRNG names on the board
 */
typedef enum CC1352R1_LAUNCHXL_TRNGName {
    CC1352R1_LAUNCHXL_TRNG0 = 0,
    CC1352R1_LAUNCHXL_TRNGCOUNT
} CC1352R1_LAUNCHXL_TRNGName;

#ifdef __cplusplus
}
#endif

#endif /* __CC1352R1_LAUNCHXL_BOARD_H__ */
