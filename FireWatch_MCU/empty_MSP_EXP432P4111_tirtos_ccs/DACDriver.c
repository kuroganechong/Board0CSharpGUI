/*
 * DACDriver.c
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */
#include <stdio.h>
#include <string.h>



#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>

#include "Board.h"
#include "DACDriver.h"

//#define SPICALBACMODEDAC

// global variable
static SPI_Handle  spi_dac;
static uint8_t    dac_transmitBuffer[2];
static uint8_t    dac_receiveBuffer[2];
static SPI_Transaction spi_dac_Transaction;
static bool       transferOK;

static Semaphore_Handle semaphoreHandle_DAC;
static Semaphore_Params semparams_DAC;
static Semaphore_Struct semDACstruct;

static uint8_t EnableVariable;
////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef  SPICALBACMODEDAC
void SpiCallbackfn(SPI_Handle handle, SPI_Transaction *transaction)
{
    Semaphore_post(semaphoreHandle_DAC);
    return;
}
#endif
// Error function when SPI cannot open
static void SpiTransferError()
{
    while (1);  // SPI_open() failed
}

static void Spi_Dac_Transfer()
{
    GPIO_write(MSP_EXP432P4011_SPI_DAC, 0);
    GPIO_write(MSP_EXP432P4011_SPI_LDAC_SYNC, 1);//Disable Output before new stimulation come to DAC chip
    transferOK = SPI_transfer(spi_dac, &spi_dac_Transaction);
    if (!transferOK) {
        SpiTransferError();
    }
#ifdef SPICALBACMODEDAC
    Semaphore_pend(semaphoreHandle_DAC,BIOS_WAIT_FOREVER);
#endif
    GPIO_write(MSP_EXP432P4011_SPI_DAC, 1);
    GPIO_write(MSP_EXP432P4011_SPI_LDAC_SYNC, 0);//Enable Output to sync start stimulating
}
////////////////////////////////////////////////////////////////////////////////////////////////
// Initialize DAC chip. Call this function to start the DAC
void DAC_Init(void)
{
    EnableVariable = 0x40; // disable all channel

    SPI_Params      spi_dac_Params;
    //semaphore
    Semaphore_Params_init(&semparams_DAC);
    semparams_DAC.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&semDACstruct, 0, &semparams_DAC);
    semaphoreHandle_DAC = Semaphore_handle(&semDACstruct);

    // set the chip select pin
    GPIO_setConfig(MSP_EXP432P4011_SPI_DAC, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);
    // Config the Syncrhonised Pin
    GPIO_setConfig(MSP_EXP432P4011_SPI_LDAC_SYNC, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);

    // config the SPI module
    SPI_Params_init(&spi_dac_Params);  // Initialize SPI parameters
    spi_dac_Params.dataSize = 8;       // 8-bit data size
#ifdef SPICALBACMODEDAC
    spi_dac_Params.transferMode = SPI_MODE_CALLBACK;
    spi_dac_Params.transferCallbackFxn = SpiCallbackfn;
#else
    spi_dac_Params.transferMode = SPI_MODE_BLOCKING;
#endif
    spi_dac_Params.bitRate = 9600000;
    spi_dac_Params.mode = SPI_MASTER;
    spi_dac_Params.frameFormat = SPI_POL0_PHA0;
    spi_dac_Params.transferTimeout = 10;
    spi_dac = SPI_open(SPIDAC, &spi_dac_Params);
    if (spi_dac == NULL) {
        SpiTransferError();
    }
    // config SPI transaction structure
    spi_dac_Transaction.count = 2;
    spi_dac_Transaction.txBuf = (void *)&dac_transmitBuffer[0];
    spi_dac_Transaction.rxBuf = (void *)&dac_receiveBuffer[0];
    spi_dac_Transaction.arg = semaphoreHandle_DAC;

    // Writing data to a channel's register causes the DAC output to change
    dac_transmitBuffer[0] = 0x50;
    dac_transmitBuffer[1] = 0x55;
    //dac_transmitBuffer[2] = 0xAA;
    //spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
    // Disable all output
    EnableVariable = 0x40; // disable all channel
    DAC_Set_Floating_All();
    //GPIO_write(MSP_EXP432P4011_SPI_LDAC_SYNC, 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////
// Set amplitude for each channel: the output only affects if the channel already enable, if not there nothing change in the output
void DAC_Set_Value(uint8_t channel, uint16_t value)
{
    uint16_t Temval;
    Temval = 0x0FFF & value; // take least 12 bits
    spi_dac_Transaction.count = 2;

    switch(channel)
    {
    case 1:
        Temval = Temval|0x1000;
        dac_transmitBuffer[0] = Temval>>8;
        dac_transmitBuffer[1] = Temval & 0xFF;
        Spi_Dac_Transfer();

        break;
    case 2:
        Temval = Temval|0x2000;
        dac_transmitBuffer[0] = Temval>>8;
        dac_transmitBuffer[1] = Temval & 0xFF;
        Spi_Dac_Transfer();
        break;
    case 3:
        Temval = Temval|0x3000;
        dac_transmitBuffer[0] = Temval>>8;
        dac_transmitBuffer[1] = Temval & 0xFF;
        Spi_Dac_Transfer();
        break;
    case 4:
        Temval = Temval|0x4000;
        dac_transmitBuffer[0] = Temval>>8;
        dac_transmitBuffer[1] = Temval & 0xFF;
        Spi_Dac_Transfer();
        break;

    default:
        break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
// Set floating channel: set the channel to high impedance state
void DAC_Set_Floating(uint8_t channel)
{
    uint8_t tempval;
    switch (channel)
    {
    case 1:
        tempval = 0b11111011;
        EnableVariable = EnableVariable & tempval;
        break;
    case 2:
        tempval =  0b11110111;
        EnableVariable = EnableVariable & tempval;
        break;
    case 3:
        tempval =  0b11101111;
        EnableVariable = EnableVariable & tempval;
        break;
    case 4:
        tempval =  0b11011111;
        EnableVariable = EnableVariable & tempval;
        break;

    default:
        break;
    }
    dac_transmitBuffer[0] = 0x70;
    dac_transmitBuffer[1] = EnableVariable;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
    // Nop transfer to finish the control
    dac_transmitBuffer[0] = 0x00;
    dac_transmitBuffer[1] = 0x00;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
}
// Set all channels to high impedance state
void DAC_Set_Floating_All()
{
    EnableVariable = 0x40; // disable all
    dac_transmitBuffer[0] = 0x70;
    dac_transmitBuffer[1] = EnableVariable;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();

    // Nop transfer to finish the control
    dac_transmitBuffer[0] = 0x00;
    dac_transmitBuffer[1] = 0x00;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
}

// Enable output for the channel
void DAC_Set_Output(uint8_t channel)
{
    uint8_t tempval;
    switch (channel)
    {
    case 1:
        tempval = 0b00000100;
        EnableVariable = EnableVariable | tempval;
        break;
    case 2:
        tempval = 0b00001000;
        EnableVariable = EnableVariable | tempval;
        break;
    case 3:
        tempval = 0b00010000;
        EnableVariable = EnableVariable | tempval;
        break;
    case 4:
        tempval = 0b00100000;
        EnableVariable = EnableVariable | tempval;
        break;

    default:
        break;
    }
    dac_transmitBuffer[0] = 0x70;
    dac_transmitBuffer[1] = EnableVariable;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
    // Nop transfer to finish the control
    dac_transmitBuffer[0] = 0x00;
    dac_transmitBuffer[1] = 0x00;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
}
// Set output for all channels
void DAC_Set_Broadcast(uint16_t value)
{
    uint16_t valtemp;
    valtemp = 0x0FFF & value;
    valtemp = 0x5000|valtemp;
    dac_transmitBuffer[0] = valtemp>>8;
    dac_transmitBuffer[1] = valtemp & 0xFF;
    spi_dac_Transaction.count = 2;
    Spi_Dac_Transfer();
}








