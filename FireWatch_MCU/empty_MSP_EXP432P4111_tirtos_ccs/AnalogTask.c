/*
 * AnalogTask.c
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/ADCBuf.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/ADC.h>
#include "Board.h"

#define ANALOGSTACKSIZE    768
#define ANALOGTASKPRIORITY 3
void AnalogTask(UArg arg0, UArg arg1);
void AnalogTaskCreate(void)
{
    Error_Block Erb_Analog;
    Task_Handle TaskHandle_Analog;
    Task_Params TaskParams_Analog;
    Error_init(&Erb_Analog);
    Task_Params_init(&TaskParams_Analog);
    TaskParams_Analog.priority = 3;
    TaskParams_Analog.stackSize = ANALOGSTACKSIZE;
    TaskHandle_Analog = Task_create(AnalogTask, &TaskParams_Analog, &Erb_Analog);
    if (TaskHandle_Analog == NULL)
    {
        while(1);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
uint16_t sampleBufferOne[SAMPLE_SIZE];
uint16_t sampleBufferTwo[SAMPLE_SIZE];
uint16_t OldAudioData[SAMPLE_SIZE*2];

uint16_t *pFinishBuffer;
uint8_t  OldBufferFillIdx;
uint8_t currentsampling;
uint8_t currentsamplingold;
uint16_t BatteryVoltageSampleCnt = 0;

Semaphore_Handle Analog_SemHandle;
Semaphore_Struct sem_Analog_Struct;
Semaphore_Params sem_Analog_Params;

extern Semaphore_Handle FFTCal_SemHandle;

ADCBuf_Conversion continuousConversion;
ADCBuf_Handle adcBuf;

float BatteryVoltage;
uint8_t switchAnalogchannel;

extern bool Mic_onoff;



static void adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion,
    void *completedADCBuffer, uint32_t completedChannel) {
    //uint_fast16_t i;

    int16_t i;
    uint32_t Sumsample;

    if (BatteryVoltageSampleCnt>=2000)
    {
        BatteryVoltageSampleCnt = 0;
        switchAnalogchannel = 1;
    }
    if (currentsamplingold == currentsampling)
    {
        BatteryVoltageSampleCnt++;

        if (conversion->adcChannel == MSP_EXP432P4011_ADCBUF0CHANNEL1)
        {
            pFinishBuffer = (uint16_t*)sampleBufferOne;
            Sumsample = 0;
            for (i=0; i<SAMPLE_SIZE; i++)
            {
                Sumsample += *(pFinishBuffer++);
            }
            BatteryVoltage = (float)5.3379e-7 * Sumsample;
        }
        else
        {
            if(Mic_onoff)
            {
                // Copy memory
                memcpy(&OldAudioData[0],&OldAudioData[SAMPLE_SIZE], SAMPLE_SIZE*sizeof(uint16_t));
                memcpy(&OldAudioData[SAMPLE_SIZE],completedADCBuffer, SAMPLE_SIZE*sizeof(uint16_t));
                Semaphore_post(FFTCal_SemHandle);
            }
        }
        Semaphore_post(Analog_SemHandle);
    }
}

void AnalogTask(UArg arg0, UArg arg1)
{

    ADCBuf_Params adcBufParams;

    /* Call driver init functions */
    ADCBuf_init();
    //GPIO_init();
    GPIO_setConfig(MSP_EXP432P4011_GPIO_LED7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_OFF);

    /* Set up an ADCBuf peripheral in ADCBuf_RECURRENCE_MODE_CONTINUOUS */
    ADCBuf_Params_init(&adcBufParams);
    adcBufParams.callbackFxn = adcBufCallback;
    adcBufParams.recurrenceMode = ADCBuf_RECURRENCE_MODE_CONTINUOUS;
    adcBufParams.returnMode = ADCBuf_RETURN_MODE_CALLBACK;
    adcBufParams.samplingFrequency = AUDIO_SAMPLE_RATE;
    adcBuf = ADCBuf_open(MSP_EXP432P4011_ADCBUF0, &adcBufParams);
    /* Configure the conversion struct */
    continuousConversion.arg = NULL;
    continuousConversion.adcChannel = MSP_EXP432P4011_ADCBUF0CHANNEL1;
    continuousConversion.sampleBuffer = sampleBufferOne;
    continuousConversion.sampleBufferTwo = sampleBufferTwo;
    continuousConversion.samplesRequestedCount = SAMPLE_SIZE;

    currentsampling = MSP_EXP432P4011_ADCBUF0CHANNEL1;


    if (!adcBuf){
        /* AdcBuf did not open correctly. */
        while(1);
    }
    /* Start converting. */
    if (ADCBuf_convert(adcBuf, &continuousConversion, 1) !=
        ADCBuf_STATUS_SUCCESS) {
        /* Did not start conversion process correctly. */
        while(1);
    }
    currentsamplingold = currentsampling;


    //semaphore
    Semaphore_Params_init(&sem_Analog_Params);
    sem_Analog_Params.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&sem_Analog_Struct, 0, &sem_Analog_Params);
    Analog_SemHandle = Semaphore_handle(&sem_Analog_Struct);


    BatteryVoltageSampleCnt = 0;
    switchAnalogchannel = 0;

    while(1) {
        Semaphore_pend(Analog_SemHandle, BIOS_WAIT_FOREVER);
        // switch to Battery voltage measurement
        // Stop current convert
        switch(currentsampling)
        {
        case MSP_EXP432P4011_ADCBUF0CHANNEL0:

            if (switchAnalogchannel != 0)
            {
                // config measuring battery voltage
                currentsamplingold = currentsampling;
                currentsampling = MSP_EXP432P4011_ADCBUF0CHANNEL1;
                if (ADCBuf_convertCancel(adcBuf) !=
                    ADCBuf_STATUS_SUCCESS) {
                    /* Did not start conversion process correctly. */

                    GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_ON);
                    while(1);
                }
                if (ADCBuf_convertCancel(adcBuf) !=
                    ADCBuf_STATUS_SUCCESS) {
                    /* Did not start conversion process correctly. */

                    GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_OFF);
                    while(1);
                }
                continuousConversion.adcChannel = MSP_EXP432P4011_ADCBUF0CHANNEL1;
                /* Start converting. */
                if (ADCBuf_convert(adcBuf, &continuousConversion, 1) !=
                    ADCBuf_STATUS_SUCCESS) {
                    /* Did not start conversion process correctly. */
                    GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_ON);
                    while(1);
                }
                currentsamplingold = currentsampling;
                switchAnalogchannel = 0;
            }
            // MP3 compression for each granule
            /* TODO */
            // the execution of this function is control by a global variable to on/off. The function only activates when requesting to save energy.


            break;
        case MSP_EXP432P4011_ADCBUF0CHANNEL1:
            // calculate battery voltage

            // Switch back microphone
            // switch back to microphone
            currentsamplingold = currentsampling;
            currentsampling = MSP_EXP432P4011_ADCBUF0CHANNEL0;
            if (ADCBuf_convertCancel(adcBuf) !=
                ADCBuf_STATUS_SUCCESS) {
                /* Did not start conversion process correctly. */
                GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_ON);
                while(1);
            }
            if (ADCBuf_convertCancel(adcBuf) !=
                ADCBuf_STATUS_SUCCESS) {
                /* Did not start conversion process correctly. */
                GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_OFF);
                while(1);
            }
            continuousConversion.adcChannel = MSP_EXP432P4011_ADCBUF0CHANNEL0;
            /* Start converting. */
            if (ADCBuf_convert(adcBuf, &continuousConversion, 1) !=
                ADCBuf_STATUS_SUCCESS) {
                /* Did not start conversion process correctly. */
                GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_ON);
                while(1);
            }
            currentsamplingold = currentsampling;

            break;
        default:
            if (ADCBuf_convertCancel(adcBuf) !=
                ADCBuf_STATUS_SUCCESS) {
                /* Did not start conversion process correctly. */
                while(1);
            }
            /* Start converting. */
            if (ADCBuf_convert(adcBuf, &continuousConversion, 1) !=
                ADCBuf_STATUS_SUCCESS) {
                /* Did not start conversion process correctly. */
                while(1);
            }
            currentsamplingold = currentsampling;
            GPIO_write(MSP_EXP432P4011_GPIO_LED7, Board_GPIO_LED_OFF);

            break;
        }
    }
}
