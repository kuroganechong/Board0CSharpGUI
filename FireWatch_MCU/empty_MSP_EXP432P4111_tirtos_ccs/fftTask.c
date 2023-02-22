/*
 * fftTask.c
 *
 *  Created on: Jan 31, 2018
 *      Author: dvthan
 */

#include <stdint.h>
#include <stdio.h>
/* For usleep() */
#include <unistd.h>
#include <stdbool.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/GPIO.h>
//#include <ti/drivers/UART.h>

#include "msp.h"
#include <arm_math.h>
#include "arm_const_structs.h"

#include "Board.h"
//#define NODOMINANTFREQUENCY (10)

extern Semaphore_Handle Empty_SemHandle;
extern uint16_t OldAudioData[2*SAMPLE_SIZE];


uint8_t AnalogChannel; // 4- BatVoltage, 3-MIC right, 2- MIC left
float BatteryVoltage;
float SoundDominantFreq[NODOMINANTFREQUENCY];
float SoundAmpDomninant[NODOMINANTFREQUENCY];
float SoundRMSsave[NODOMINANTFREQUENCY*2 + 1];
float TotalRMSSoundPower;
float AverageVal;




float hann[FFT_SIZE];
uint32_t fftSize = FFT_SIZE;
uint32_t FrequencySize = FFT_SIZE/2;
uint8_t ifftFlag = 0;
volatile arm_status status;

float Buffer_In_Data[FFT_SIZE];
float Buffer_Out_Complex[FFT_SIZE];
float Buffer_Magnitude_Real[FFT_SIZE/2];


//float Buff_Mic[FFT_SIZE];



Semaphore_Handle FFTCal_SemHandle;


void fftTask(UArg arg0, UArg arg1)
{
    Semaphore_Params FFTCalsemparams;
    Error_Block FFTCaleb;

    float scaleval;
    float Frequency_Resolution;

    int n;
    uint8_t startflag = 1;
    //float ThreshTemp;

    float Voltemp;
    uint32_t maxfrequencyIdx;
    float MaxAmplitude;
    float AverageVoltTemp;


    //semaphore
    Semaphore_Params_init(&FFTCalsemparams);
    Error_init(&FFTCaleb);

    FFTCalsemparams.mode = Semaphore_Mode_BINARY;
    FFTCal_SemHandle = Semaphore_create(0, &FFTCalsemparams, &FFTCaleb);
    ///////////////////////////////////////////////////////////////////////
    // Initialize Hann Window
    for (n = 0; n < FFT_SIZE; n++)
    {
        hann[n] = (0.5 - 0.5 * cosf((2*PI*n)/(FFT_SIZE-1)));
    }
    ///////////////////////////////////////////////////////////////////////
    while(1)
    {
        Semaphore_pend(FFTCal_SemHandle, BIOS_WAIT_FOREVER);
        // FFT calculation
        // calculate dominant frequency
        scaleval = 2.0f/FFT_SIZE;
        Frequency_Resolution = ((float)AUDIO_SAMPLE_RATE)/FFT_SIZE;
        // copy data to buffer
        AverageVoltTemp = 0.0f;
        for (n = 0; n < FFT_SIZE; n++)
        {
            Voltemp =  1.5259e-4f*((float)OldAudioData[n]);
            Buffer_In_Data[n] = Voltemp;
            AverageVoltTemp += Voltemp;
        }
        AverageVoltTemp =  AverageVoltTemp/FFT_SIZE;
        if (startflag != 0)
        {
            AverageVal = AverageVoltTemp;
            startflag = 0;
        }
        else
        {
            AverageVal = AverageVal*0.8f + 0.2f*AverageVoltTemp;
        }

        // offset to average value
        for (n = 0; n < FFT_SIZE; n++)
        {
            //Buff_Mic[n] = (Buffer_In_Data[n]-AverageVal);
            Buffer_In_Data[n] = (Buffer_In_Data[n]-AverageVal)*hann[n] ;
        }
        // find RMS value of signal

        arm_rms_f32(Buffer_In_Data, fftSize,&TotalRMSSoundPower);
        // shift Sound RMS to left
        for (n = 0; n<(NODOMINANTFREQUENCY*2); n++)
        {
            SoundRMSsave[n] = SoundRMSsave[n + 1];
        }
        SoundRMSsave[NODOMINANTFREQUENCY*2] = TotalRMSSoundPower;

        // FFT calculation
        for (n = 0; n < FFT_SIZE; n++)
        {
            Buffer_In_Data[n] = Buffer_In_Data[n]*hann[n] ;
        }
        arm_rfft_fast_instance_f32 Instance_Real;
        status = arm_rfft_fast_init_f32(&Instance_Real, fftSize);
        arm_rfft_fast_f32(&Instance_Real, Buffer_In_Data, Buffer_Out_Complex, ifftFlag);
        // Calculate magnitude of FFT complex output
        for (n = 0; n < FFT_SIZE; n+=2)
        {
           Buffer_Magnitude_Real[n/2] = (float)(sqrtf((Buffer_Out_Complex[n] * Buffer_Out_Complex[n]) +
                                       (Buffer_Out_Complex[n+1] * Buffer_Out_Complex[n+1]))*scaleval);

        }
        // find first 10 dominant frequency
        for (n = 0; n<NODOMINANTFREQUENCY; n++)
        {
            arm_max_f32(Buffer_Magnitude_Real,FrequencySize,&MaxAmplitude,&maxfrequencyIdx);
            // fill data
            SoundAmpDomninant[n] = MaxAmplitude;
            SoundDominantFreq[n] = maxfrequencyIdx*Frequency_Resolution;
            Buffer_Magnitude_Real[maxfrequencyIdx] = 0.0f;
        }
        // calculate
    }


}


