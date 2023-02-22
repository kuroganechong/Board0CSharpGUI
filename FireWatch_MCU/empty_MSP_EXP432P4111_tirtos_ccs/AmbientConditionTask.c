/*
 * AmbientConditionTask.c
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */
#include <stdint.h>
#include <stdio.h>
/* For usleep() */
#include <unistd.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/GPIO.h>

#include "AmbientConditionTask.h"
#include "Ambient_sensor.h"
///////////////////////////////////////////////////////////////////////////
// Task parameter
#define AMBIENTCONDITONCALSTACKSIZE    1024
#define AMBIENTTASKPRIORITY     2
//#define IRSAMPLERATEMS     200   // Collect IR data every 200 ms
///////////////////////////////////////////////////////////////////////////
// Prototype
static void PeriodicClockExpired_Ambient(UArg Arg);
void AmbientConditionTask(UArg arg0, UArg arg1);
///////////////////////////////////////////////////////////////////////////
void AmbientConditionTaskCreate(void)
{
    Error_Block Erb_Ambient;
    Task_Handle Ambient_TaskHandle;
    Task_Params Ambient_TaskParams;
    Error_init(&Erb_Ambient);
    Task_Params_init(&Ambient_TaskParams);
    Ambient_TaskParams.priority = AMBIENTTASKPRIORITY;
    Ambient_TaskParams.stackSize = AMBIENTCONDITONCALSTACKSIZE;
    Ambient_TaskHandle = Task_create(AmbientConditionTask, &Ambient_TaskParams, &Erb_Ambient);
    if (Ambient_TaskHandle == NULL)
    {
        while(1);
    }
}
///////////////////////////////////////////////////////////////////////
#define CO2CNT          2//5   //every 5s
#define BASELINECNT     1800 //1800 // every 30 minutes
// Sensor output
float Ambienttemp;
float Humidity;
float AirPressure;
uint16_t CO2val;
uint16_t TVOCval;

// Sensor open status
extern bool isAmbientSensor_open;
extern bool isCO2sensor_open;
// On/off control variables
extern bool Co2Sensor_onoff;
extern bool Ambient_onoff;
extern volatile bool isOldBaselineFound;
volatile bool BaselineReadytoSave;



uint8_t Baselineval[2] = {0,0};
uint8_t BaselinevalOld[2];


// main thread handle
Semaphore_Handle Ambient_SemHandle;

///////////////////////////////////////////////////////////////////////
static void PeriodicClockExpired_Ambient(UArg Arg)
{
    Semaphore_post(Ambient_SemHandle);
}

///////////////////////////////////////////////////////////////////////
void AmbientConditionTask(UArg arg0, UArg arg1)
{
    uint32_t BME280cnt = 0;
    uint32_t CCS811cnt = 0;
    uint32_t co2count = 0;
    BaselineReadytoSave = false;

    Semaphore_Struct SemAmbient_struct;
    Semaphore_Params semparams;

    Clock_Struct ClockAmbient_struct;
    Clock_Params PeriodClockParam;

    uint32_t RawPressure;

    int baselinecnt = 0;
    uint8_t CO2Status;

    bool co2started;

    /* Configure the LED pin */
    GPIO_setConfig(MSP_EXP432P4011_GPIO_LED6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(MSP_EXP432P4011_CO2_WAKE, GPIO_CFG_OUT_OD_NOPULL | GPIO_CFG_OUT_HIGH);
    GPIO_setConfig(MSP_EXP432P4011_CO2_RESET, GPIO_CFG_OUT_OD_NOPULL | GPIO_CFG_OUT_HIGH);//outdoor
    /* Turn on user LED */

    GPIO_write(MSP_EXP432P4011_CO2_RESET, Board_GPIO_LED_OFF);//outdoor
    GPIO_write(MSP_EXP432P4011_CO2_WAKE, Board_GPIO_LED_OFF);
    GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_OFF);

    //semaphore
    Semaphore_Params_init(&semparams);
    semparams.mode = Semaphore_Mode_COUNTING;
    Semaphore_construct(&SemAmbient_struct,0,&semparams);
    Ambient_SemHandle = Semaphore_handle(&SemAmbient_struct);


    // clock param
    Clock_Params_init(&PeriodClockParam);
    PeriodClockParam.startFlag = true;
    PeriodClockParam.period = 1000;// 1Hz data refreshing rate (1s rate)
    Clock_construct(&ClockAmbient_struct,PeriodicClockExpired_Ambient,1,&PeriodClockParam);
    // check connection
    if(!I2CAmbientInit())
    {
        Task_exit();
    }

    if (BME280_Init())
    {
        BME280_read(&Ambienttemp, &Humidity, &AirPressure, &RawPressure);
    }
    if (CCS811_Init())
    {
        co2started = true;
        if (isAmbientSensor_open)
        {
            CCS811_TemperatureUpdate(Ambienttemp, Humidity);//only update to compensate at Reset
        }
        co2count = 0;
    }
    else
    {
        GPIO_write(MSP_EXP432P4011_CO2_RESET, Board_GPIO_LED_ON);//outdoor board only
        GPIO_write(MSP_EXP432P4011_CO2_WAKE, Board_GPIO_LED_ON);
    }

    while(1)
    {
        Semaphore_pend(Ambient_SemHandle, BIOS_WAIT_FOREVER);
        // update baseline
        if(isOldBaselineFound)
        {
            if(isCO2sensor_open)
            {
                isOldBaselineFound = false;
                CCS811_Baseline_Write(BaselinevalOld);
            }
        }

        if (isAmbientSensor_open)
        {
//            GPIO_toggle(MSP_EXP432P4011_GPIO_LED6); //Only CO2 sensor is hard to start, No need to check for Ambient Sensor
            if (Ambient_onoff)
            {
                BME280_read(&Ambienttemp, &Humidity, &AirPressure,&RawPressure);
            }
        }
        else // Try to restart the sensor
        {
            BME280cnt++;
            if(BME280cnt > 30)//60s or 30s if not open then restart
            {
                BME280cnt = 0;
                if (BME280_Init())
                {
                    BME280_read(&Ambienttemp, &Humidity, &AirPressure, &RawPressure);
                }
            }
        }

        if (isCO2sensor_open)
        {
            co2count++;
            GPIO_toggle(MSP_EXP432P4011_GPIO_LED6);//Only CO2 sensor is hard to start, No need to check for Ambient Sensor
            if (Co2Sensor_onoff)
            {
                baselinecnt++;
                if (!co2started)
                {
//                    CCS811_HW_nRESET();
//                    CCS811_SW_Reset();
                    CCS811_Wake();
                    co2started = true;
                }
                if (co2count >= CO2CNT) //#define CO2CNT          2//5   //every 1s or 5s then read 1 time

                {
                    CO2Status = CCS811_Read(&CO2val, &TVOCval);
                    co2count = 0;
                    if (CO2Status != 255)
                    {
                        if (isAmbientSensor_open)
                        {
                            BME280_read(&Ambienttemp, &Humidity, &AirPressure, &RawPressure);
                            CCS811_TemperatureUpdate(Ambienttemp, Humidity);//try not update for compensation
                        }
                    }
                }
                // Baseline store
                if(baselinecnt > BASELINECNT)//#define BASELINECNT     1800 //1800 // every 30 minutes
                {
                    baselinecnt = 0;
                    CCS811_Baseline_Read(Baselineval);
                    BaselineReadytoSave = true; // external
                }
            }
            else
            {
                CCS811_Sleep();
                co2started = false;
                baselinecnt = 0;
            }
        }
        else // Try to restart the sensor
        {
            GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_OFF);//Turn off LED_6 if sensor is NOT started,
            GPIO_write(MSP_EXP432P4011_CO2_WAKE, Board_GPIO_LED_OFF);
            CCS811cnt++;
            if(CCS811cnt>20)//60s or 20s hard reset it if it does not start
            {
                CCS811cnt = 0;
                CCS811_HW_nRESET(); // Hard Reset after 60 seconds
                // CCS811_SW_Reset(); // Software Reset
                if (CCS811_Init())
                {
                    co2started = true;
                    if (isAmbientSensor_open)
                    {
                        CCS811_TemperatureUpdate(Ambienttemp, Humidity);//only update to compensate at Reset
                    }
                    co2count = 0;
                }
                else
                {
                    GPIO_write(MSP_EXP432P4011_CO2_WAKE, Board_GPIO_LED_ON);
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////










