/*
 * Copyright (c) 2016-2018, Texas Instruments Incorporated
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

/*
 *  ======== main_tirtos.c ========
 */
#include <stdint.h>
/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>

/* Example/Board Header files */
#include "Board.h"
#include "StimulationTask.h"
#include "LevyWalkTask.h"
#include "IRSensorTask.h"
#include "AmbientConditionTask.h"
#include "AnalogTask.h"
#include "IMU_Task.h"
#include "fftTask.h"

extern void *mainThread(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE    25576  //1024 is the number selected by A.Than  //4096 is working fine until the presence of Flash Saving
#define IMUTASKSTACKSIZE   4096
#define FFTCOMPUTATIONSTACKSIZE 800

// ------------------------------ MAIN FILE --------------------------------- //
int main(void)
{
    pthread_t           thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

    /* Call driver init functions */
    Board_initGeneral();

    /* Set priority and stack size attributes */
    pthread_attr_init(&attrs);
    priParam.sched_priority = 1;

    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        /* pthread_attr_setdetachstate() failed */
        while (1);
    }

    pthread_attr_setschedparam(&attrs, &priParam);

    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* pthread_attr_setstacksize() failed */
        while (1);
    }

    retc = pthread_create(&thread, &attrs, mainThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1);
    }
    // --------------------- PRIORITY --------------------- //
    // Stimulation  = 5
    // IMU          = 4
    // Analog       = 3
    // Ambient      = 2
    // IR           = 2
    // FFT          = 1
    // Levy         = 1
    // SPI          = 1

    // ------------ Stimulation Task ------------------------//
        StimulationTaskCreation(); // Highest Priority = 5;

    // -------------- IMU Task ----------------//
    Error_Block Erb_IMU;
    Task_Handle TaskHandle_IMUTask;
    Task_Params TaskParams_IMUTask;
    Error_init(&Erb_IMU);
    Task_Params_init(&TaskParams_IMUTask);
    TaskParams_IMUTask.priority = 4;  // Priority = 4;
    TaskParams_IMUTask.stackSize = IMUTASKSTACKSIZE;
    TaskHandle_IMUTask = Task_create(IMU_Task, &TaskParams_IMUTask, &Erb_IMU);
    if (TaskHandle_IMUTask == NULL)
    {
       while(1);
    }

    // -------------- Analog Task ----------------//
    AnalogTaskCreate(); // Priority = 3;

    // ------------ IR Task ------------------------ //
    IRSensorTaskCreate(); // Priority = 2; // Thanh enable

    // -------------- Ambient Condition Task ----------------//
    //AmbientConditionTaskCreate(); // Priority = 2;

    // ------------ Levy Walk Task ------------------------//
    LevyWalkTaskCreation(); // Priority = 1;

    // -------------- FFT Computation Task ----------------//
    /*Error_Block Erb_fft;
    Task_Handle TaskHandle_fft;
    Task_Params TaskParams_fft;
    Error_init(&Erb_fft);
    Task_Params_init(&TaskParams_fft);
    TaskParams_fft.priority = 1;   // Priority = 1
    TaskParams_fft.stackSize = FFTCOMPUTATIONSTACKSIZE;
    TaskHandle_fft= Task_create(fftTask, &TaskParams_fft, &Erb_fft);
    if (TaskHandle_fft == NULL)
    {
        while(1);
    }*/

    // -------------- Start the BIOS ----------------//
    BIOS_start();

    return (0);
}
