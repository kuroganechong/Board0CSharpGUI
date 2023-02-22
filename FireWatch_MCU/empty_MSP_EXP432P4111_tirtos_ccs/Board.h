//*****************************************************************************
// Board.h
//
// configure the device pins for different signals
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

// This file was automatically generated on 7/11/2018 at 1:28:18 PM
// by TI PinMux version 4.0.1519 
//
//*****************************************************************************
#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* LEDs on MSP_EXP432P401R are active high. */
#define Board_GPIO_LED_OFF (0)
#define Board_GPIO_LED_ON  (1)

#define Board_initADC               ADC_init
#define Board_initADCBuf            ADCBuf_init
#define Board_initGeneral           MSP_EXP432P401R_initGeneral
#define Board_initGPIO              GPIO_init
#define Board_initI2C               I2C_init
#define Board_initPWM               PWM_init
#define Board_initSDSPI             SDSPI_init
#define Board_initSPI               SPI_init
#define Board_initUART              UART_init
#define Board_initWatchdog          Watchdog_init
//spi
/* Board specific I2C addresses */
#define Board_TMP_ADDR              (0x40)
#define Board_RF430CL330_ADDR       (0x28)
#define Board_TPL0401_ADDR          (0x40)


typedef enum Board_ADCName {
    MSP_EXP432P4011_VBAT = 0,
    MSP_EXP432P4011_MIC = 1,
    MSP_EXP432P4011_ADCCOUNT
} Board_ADCName;










/*!
 *  @def    MSP_EXP432P401R_ADCBufName
 *  @brief  Enum of ADCBuf hardware peripherals on the MSP_EXP432P401R dev board
 */
 typedef enum Board_ADCBufName {
    MSP_EXP432P4011_ADCBUF0 = 0,
    Board_ADCBUFCOUNT
 } Board_ADCBufName;

    
/*!
 *  @def    MSP_EXP432P401R_ADCBufChannelName
 *  @brief  Enum of ADCBuf channels on the MSP_EXP432P401R dev board
 */
 typedef enum Board_ADCBuf0ChannelName {
    MSP_EXP432P4011_ADCBUF0CHANNEL1 = 0,
    MSP_EXP432P4011_ADCBUF0CHANNEL0 = 1,
    Board_ADCBUF0CHANNELCOUNT
 } Board_ADCBuf0ChannelName;

/*!
 *  @def    MSP_EXP432P401R_GPIOName
 *  @brief  Enum of GPIO names on the MSP_EXP432P401R dev board
 */
typedef enum Board_GPIOName {
    MSP_EXP432P4011_CO2_RESET = 0,
    MSP_EXP432P4011_CO2_WAKE = 1,
    MSP_EXP432P4011_BLE_EXT = 2,
    MSP_EXP432P4011_INT_IMU = 3,
    MSP_EXP432P4011_GPIO_LED5 = 4,
    MSP_EXP432P4011_GPIO_LED6 = 5,
    MSP_EXP432P4011_GPIO_LED7 = 6,
    MSP_EXP432P4011_SPI_DAC = 7,
    MSP_EXP432P4011_SPI_LDAC_SYNC = 8,
    MSP_EXP432P4011_SPI_FLASH = 9,
    Board_GPIOCOUNT
} Board_GPIOName;

/*!
 *  @def    MSP_EXP432P401R_I2CName
 *  @brief  Enum of I2C names on the MSP_EXP432P401R dev board
 */
typedef enum Board_I2CName {
    MSP_EXP432P4011_I2CB0 = 0,
    MSP_EXP432P4011_I2CB2 = 1,
    MSP_EXP432P4011_I2CB3 = 2,
   Board_I2CCOUNT
} Board_I2CName;

/*!
 *  @def    MSP_EXP432P401R_SPIName
 *  @brief  Enum of SPI names on the MSP_EXP432P401R dev board
 */
typedef enum Board_SPIName {
    MSP_EXP432P4011_SPIA0 = 0,
    MSP_EXP432P4011_SPIA1 = 1,
    MSP_EXP432P4011_SPIA2 = 2,
   Board_SPICOUNT
} Board_SPIName;
    
/*!
 *  @def    MSP_EXP432P401R_TimerName
 *  @brief  Enum of Timer names on the MSP_EXP432P401R dev board
 */
typedef enum Board_TimerName {
    MSP_EXP432P4011_ADCBUF0_TIMER = 0,
   Board_TIMERCOUNT
} Board_TimerName;
    

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
extern void Board_initGeneral(void);


#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
