//*****************************************************************************
// Board.c
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
#ifndef DeviceFamily_MSP432P401x
#define DeviceFamily_MSP432P401x
#endif



#include <stdbool.h>
#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerMSP432.h>

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/rom.h>
#include <ti/devices/msp432p4xx/driverlib/rom_map.h>
#include <ti/devices/msp432p4xx/driverlib/adc14.h>
#include <ti/devices/msp432p4xx/driverlib/dma.h>
#include <ti/devices/msp432p4xx/driverlib/gpio.h>
#include <ti/devices/msp432p4xx/driverlib/i2c.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>
#include <ti/devices/msp432p4xx/driverlib/pmap.h>
#include <ti/devices/msp432p4xx/driverlib/ref_a.h>
#include <ti/devices/msp432p4xx/driverlib/spi.h>
#include <ti/devices/msp432p4xx/driverlib/timer_a.h>
#include <ti/devices/msp432p4xx/driverlib/timer32.h>
#include <ti/devices/msp432p4xx/driverlib/uart.h>
#include <ti/devices/msp432p4xx/driverlib/wdt_a.h>



#include "Board.h"
/*
 *  =============================== ADC ===============================
 */
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCMSP432.h>


/* ADC objects */
ADCMSP432_Object adcMSP432Objects[MSP_EXP432P4011_ADCCOUNT];

/* ADC configuration structure */
const ADCMSP432_HWAttrsV1 adcMSP432HWAttrs[MSP_EXP432P4011_ADCCOUNT] = {
    {
        .adcPin = ADCMSP432_P5_4_A1,
        .refVoltage = ADCMSP432_REF_VOLTAGE_INT_2_5V,
        .resolution = ADC_14BIT
    },
    {
        .adcPin = ADCMSP432_P5_5_A0,
        .refVoltage = ADCMSP432_REF_VOLTAGE_INT_2_5V,
        .resolution = ADC_14BIT
    },
};

const ADC_Config ADC_config[MSP_EXP432P4011_ADCCOUNT] = {
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[MSP_EXP432P4011_VBAT],
        .hwAttrs = &adcMSP432HWAttrs[MSP_EXP432P4011_VBAT]
    },
    {
        .fxnTablePtr = &ADCMSP432_fxnTable,
        .object = &adcMSP432Objects[MSP_EXP432P4011_MIC],
        .hwAttrs = &adcMSP432HWAttrs[MSP_EXP432P4011_MIC]
    }
};

const uint_least8_t ADC_count = MSP_EXP432P4011_ADCCOUNT;


/*
 *  =============================== ADCBuf ===============================
 */
#include <ti/drivers/ADCBuf.h>
#include <ti/drivers/adcbuf/ADCBufMSP432.h>

/* ADCBuf objects */
ADCBufMSP432_Object adcbufMSP432Objects[Board_ADCBUFCOUNT];

/* ADCBuf configuration structure */
ADCBufMSP432_Channels adcBuf0MSP432Channels[Board_ADCBUF0CHANNELCOUNT] = {
    {
        .adcPin = ADCBufMSP432_P5_4_A1,
        .refSource = ADCBufMSP432_VREFPOS_INTBUF_VREFNEG_VSS,
        .refVoltage = 2500000,//REF_A_VREF2_5V,
    },
    {
        .adcPin = ADCBufMSP432_P5_5_A0,
        .refSource = ADCBufMSP432_VREFPOS_INTBUF_VREFNEG_VSS,
        .refVoltage = 2500000,//REF_A_VREF2_5V,
    },
};

/* ADC configuration structure */
const ADCBufMSP432_HWAttrs adcbufMSP432HWAttrs[Board_ADCBUFCOUNT] = {
    {
        .intPriority =  ~0,
        .channelSetting = adcBuf0MSP432Channels,
        .adcTimerTriggerSource = ADCBufMSP432_TIMERA1_CAPTURECOMPARE2
    }
};

const ADCBuf_Config ADCBuf_config[Board_ADCBUFCOUNT] = {
    {
        .fxnTablePtr = &ADCBufMSP432_fxnTable,
        .object = &adcbufMSP432Objects[MSP_EXP432P4011_ADCBUF0],
        .hwAttrs = &adcbufMSP432HWAttrs[MSP_EXP432P4011_ADCBUF0]
    },
};

const uint_least8_t ADCBuf_count = Board_ADCBUFCOUNT;

/*
 *  =============================== DMA ===============================
 */
#include <ti/drivers/dma/UDMAMSP432.h>

#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_ALIGN(dmaControlTable, 256)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=256
#elif defined(__GNUC__)
__attribute__ ((aligned (256)))
#endif
static DMA_ControlTable dmaControlTable[8];

/*
 *  ======== dmaErrorHwi ========
 *  This is the handler for the uDMA error interrupt.
 */
static void dmaErrorHwi(uintptr_t arg)
{
    int status = MAP_DMA_getErrorStatus();
    MAP_DMA_clearErrorStatus();

    /* Suppress unused variable warning */
    (void)status;

    while (1);
}

UDMAMSP432_Object udmaMSP432Object;

const UDMAMSP432_HWAttrs udmaMSP432HWAttrs = {
    .controlBaseAddr = (void *)dmaControlTable,
    .dmaErrorFxn = (UDMAMSP432_ErrorFxn)dmaErrorHwi,
    .intNum = INT_DMA_ERR,
    .intPriority = (~0)
};

const UDMAMSP432_Config UDMAMSP432_config = {
    .object = &udmaMSP432Object,
    .hwAttrs = &udmaMSP432HWAttrs
};


/*
 *  ======== MSP_EXP432P401R_initGeneral ========
 */
void MSP_EXP432P401R_initGeneral(void)
{
    Power_init();
}

/*
 *  =============================== GPIO ===============================
 */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOMSP432.h>

/*
 * Array of Pin configurations
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in MSP_EXP432P401R.h
 * NOTE: Pins not used for interrupts should be placed at the end of the
 *       array.  Callback entries can be omitted from callbacks array to
 *       reduce memory usage.
 *       This table is corelated with the defined number as: typedef enum Board_GPIOName in Board.h
 */
GPIO_PinConfig gpioPinConfigs[] = {
    //GPIOMSP432_P1_4 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_NONE,//Change from INT to RESET
    GPIOMSP432_P1_4 | GPIO_CFG_OUT_OD_NOPULL | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,//Change from INT to RESET//0
    GPIOMSP432_P1_5 | GPIO_CFG_OUT_OD_NOPULL | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_LOW,//1
    GPIOMSP432_P3_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,
    GPIOMSP432_P3_5 | GPIO_CFG_IN_NOPULL | GPIO_CFG_IN_INT_FALLING,                     //3
    GPIOMSP432_P8_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    GPIOMSP432_P8_1 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  //5
    GPIOMSP432_P4_7 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,
    GPIOMSP432_P1_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH, //7
    GPIOMSP432_P7_3 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,
    GPIOMSP432_P2_0 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_LOW | GPIO_CFG_OUT_HIGH,  //9
};

/*
 * Array of callback function pointers
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in MSP_EXP432P401R.h
 * NOTE: Pins not used for interrupts can be omitted from callbacks array to
 *       reduce memory usage (if placed at end of gpioPinConfigs array).
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL,
    NULL
};

const GPIOMSP432_Config GPIOMSP432_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = sizeof(gpioPinConfigs)/sizeof(GPIO_PinConfig),
    .numberOfCallbacks = sizeof(gpioCallbackFunctions)/sizeof(GPIO_CallbackFxn),
    .intPriority = (~0)
};
/*
 *  =============================== I2C ===============================
 */
#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CMSP432.h>

I2CMSP432_Object i2cMSP432Objects[Board_I2CCOUNT];

const I2CMSP432_HWAttrsV1 i2cMSP432HWAttrs[Board_I2CCOUNT] = {
    {
        .baseAddr = EUSCI_B0_BASE,
        .intNum = INT_EUSCIB0,
        .intPriority = (~0),
        .clockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
        .dataPin = I2CMSP432_P1_6_UCB0SDA,
        .clkPin = I2CMSP432_P1_7_UCB0SCL,
    },
    {
        .baseAddr = EUSCI_B2_BASE,
        .intNum = INT_EUSCIB2,
        .intPriority = (~0),
        .clockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
        .dataPin = I2CMSP432_P3_6_UCB2SDA,
        .clkPin = I2CMSP432_P3_7_UCB2SCL,
    },
    {
        .baseAddr = EUSCI_B3_BASE,
        .intNum = INT_EUSCIB3,
        .intPriority = (~0),
        .clockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
        .dataPin = I2CMSP432_P6_6_UCB3SDA,
        .clkPin = I2CMSP432_P6_7_UCB3SCL,
    },
};

const I2C_Config I2C_config[Board_I2CCOUNT] = {
    {
        .fxnTablePtr = &I2CMSP432_fxnTable,
        .object = &i2cMSP432Objects[MSP_EXP432P4011_I2CB0],
        .hwAttrs = &i2cMSP432HWAttrs[MSP_EXP432P4011_I2CB0]
    },
    {
        .fxnTablePtr = &I2CMSP432_fxnTable,
        .object = &i2cMSP432Objects[MSP_EXP432P4011_I2CB2],
        .hwAttrs = &i2cMSP432HWAttrs[MSP_EXP432P4011_I2CB2]
    },
    {
        .fxnTablePtr = &I2CMSP432_fxnTable,
        .object = &i2cMSP432Objects[MSP_EXP432P4011_I2CB3],
        .hwAttrs = &i2cMSP432HWAttrs[MSP_EXP432P4011_I2CB3]
    },
};

const uint_least8_t I2C_count = Board_I2CCOUNT;
/*
 *  =============================== Power ===============================
 */
const PowerMSP432_ConfigV1 PowerMSP432_config = {
    .policyInitFxn = &PowerMSP432_initPolicy,
    .policyFxn = &PowerMSP432_sleepPolicy,
    .initialPerfLevel = 2,
    .enablePolicy = true,
    .enablePerf = true,
    .enableParking = true
};

/*
 *  =============================== SPI ===============================
 */
#include <ti/drivers/SPI.h>
#include <ti/drivers/spi/SPIMSP432DMA.h>

/* SPI objects */
SPIMSP432DMA_Object spiMSP432DMAObjects[Board_SPICOUNT];

/* SPI configuration structure */
const SPIMSP432DMA_HWAttrsV1 spiMSP432DMAHWAttrs[Board_SPICOUNT] = {
    {
        .baseAddr = EUSCI_A0_BASE,
        .bitOrder = EUSCI_A_SPI_MSB_FIRST,
        .clockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK,
        .defaultTxBufValue = 0,
        .dmaIntNum = INT_DMA_INT1,
        .intPriority = (~0),
        .rxDMAChannelIndex = DMA_CH1_EUSCIA0RX,
        .txDMAChannelIndex = DMA_CH0_EUSCIA0TX,
        .clkPin = SPIMSP432DMA_P1_1_UCA0CLK,
        .simoPin = SPIMSP432DMA_P1_3_UCA0SIMO,
        .somiPin = SPIMSP432DMA_P1_2_UCA0SOMI,
        .stePin = SPIMSP432DMA_P1_0_UCA0STE,
        .pinMode = EUSCI_SPI_3PIN
    },
    {
        .baseAddr = EUSCI_A1_BASE,
        .bitOrder = EUSCI_A_SPI_MSB_FIRST,
        .clockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK,
        .defaultTxBufValue = 0,
        .dmaIntNum = INT_DMA_INT2,
        .intPriority = (~0),
        .rxDMAChannelIndex = DMA_CH3_EUSCIA1RX,
        .txDMAChannelIndex = DMA_CH2_EUSCIA1TX,
        .clkPin = SPIMSP432DMA_P2_1_UCA1CLK,
        .simoPin = SPIMSP432DMA_P2_3_UCA1SIMO,
        .somiPin = SPIMSP432DMA_P2_2_UCA1SOMI,
        .stePin = SPIMSP432DMA_P2_0_UCA1STE,
        .pinMode = EUSCI_SPI_3PIN
    },
    {
        .baseAddr = EUSCI_A2_BASE,
        .bitOrder = EUSCI_A_SPI_MSB_FIRST,
        .clockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK,
        .defaultTxBufValue = 0,
        .dmaIntNum = INT_DMA_INT3,
        .intPriority = (~0),
        .rxDMAChannelIndex = DMA_CH5_EUSCIA2RX,
        .txDMAChannelIndex = DMA_CH4_EUSCIA2TX,
        .clkPin = SPIMSP432DMA_P3_3_UCA2CLK,
        .simoPin = SPIMSP432DMA_P3_1_UCA2SIMO,
        .somiPin = SPIMSP432DMA_P3_2_UCA2SOMI,
        .stePin = SPIMSP432DMA_P3_4_UCA2STE,
        .pinMode = EUSCI_SPI_4PIN_UCxSTE_ACTIVE_LOW
    },
};

const SPI_Config SPI_config[Board_SPICOUNT] = {
    {
        .fxnTablePtr = &SPIMSP432DMA_fxnTable,
        .object = &spiMSP432DMAObjects[MSP_EXP432P4011_SPIA0],
        .hwAttrs = &spiMSP432DMAHWAttrs[MSP_EXP432P4011_SPIA0]
    },
    {
        .fxnTablePtr = &SPIMSP432DMA_fxnTable,
        .object = &spiMSP432DMAObjects[MSP_EXP432P4011_SPIA1],
        .hwAttrs = &spiMSP432DMAHWAttrs[MSP_EXP432P4011_SPIA1]
    },
    {
        .fxnTablePtr = &SPIMSP432DMA_fxnTable,
        .object = &spiMSP432DMAObjects[MSP_EXP432P4011_SPIA2],
        .hwAttrs = &spiMSP432DMAHWAttrs[MSP_EXP432P4011_SPIA2]
    },
};

const uint_least8_t SPI_count = Board_SPICOUNT;
/*
 *  =============================== Timer ===============================
 */
#include <ti/drivers/Timer.h>
#include <ti/drivers/timer/TimerMSP432.h>

TimerMSP432_Object timerMSP432Objects[Board_TIMERCOUNT];

const TimerMSP432_HWAttrs timerMSP432HWAttrs[Board_TIMERCOUNT] = {
    {        
        .timerBaseAddress = TIMER_A1_BASE,
        .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
        .intNum = INT_TA1_0,
        .intPriority = ~0
    },
};

const Timer_Config Timer_config[Board_TIMERCOUNT] = {
    {
        .fxnTablePtr = &TimerMSP432_Timer_A_fxnTable,
        .object = &timerMSP432Objects[MSP_EXP432P4011_ADCBUF0_TIMER],
        .hwAttrs = &timerMSP432HWAttrs[MSP_EXP432P4011_ADCBUF0_TIMER]
    },
};

const uint_least8_t Timer_count = Board_TIMERCOUNT;
