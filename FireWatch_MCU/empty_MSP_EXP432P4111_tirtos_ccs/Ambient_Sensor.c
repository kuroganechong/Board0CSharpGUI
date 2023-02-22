/*
 * Ambient_Sensor.c
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

//#include "msp.h"
//#include <arm_math.h>
//#include "arm_const_structs.h"
#include <math.h>
#include "Ambient_Sensor.h"
// Sensor open status
bool isAmbientSensor_open;
bool isCO2sensor_open;


static I2C_Handle i2c;
static I2C_Params params;

static Semaphore_Struct semaphore_bme_struct;
static Semaphore_Handle semaphoreHandle_bme;
static Semaphore_Params semparams_bme;
//Error_Block eb_bme;

static Clock_Struct WaitingClockStruct_bme;
static Clock_Handle WaitingClockHandle_bme;
static Clock_Params WaitingClockParam_bme;
//Error_Block eb_bme1;

static Semaphore_Struct WClocksemaphore_bme_struct;
static Semaphore_Handle WClocksemaphoreHandle_bme;
static Semaphore_Params WClocksemparams_bme;
//Error_Block eb_bme2;
/***********************************************************************************************/
static unsigned char i2cwriteBuffer[6];
static unsigned char i2creadBuffer[32];

// calibration data
static uint16_t dig_T1;
static int16_t dig_T2;
static int16_t dig_T3;

static uint16_t dig_P1;
static int16_t dig_P2;
static int16_t dig_P3;
static int16_t dig_P4;
static int16_t dig_P5;
static int16_t dig_P6;
static int16_t dig_P7;
static int16_t dig_P8;
static int16_t dig_P9;

static uint8_t dig_H1;
static int16_t dig_H2;
static uint8_t dig_H3;
static int16_t dig_H4;
static int16_t dig_H5;
static int8_t dig_H6;

/***********************************************************************************************/
static bool status_amb;
static I2C_Transaction i2cTransaction_bme;

static void callbackFxn_bme(I2C_Handle handle, I2C_Transaction *msg, Bool transfer) {
   if (msg->arg != NULL) {
       Semaphore_post((Semaphore_Handle)(msg->arg));
   }
}
static void errorfunction_bme()
{
    isAmbientSensor_open = false;
}
static void errorfunction_ccs()
{
    isCO2sensor_open = false;
}

static void ClockExpired_bme(UArg Arg)
{
    Semaphore_post(WClocksemaphoreHandle_bme);
}
static void DelayMsClock_bme(uint32_t DelayTime)
{
    Clock_setTimeout(WaitingClockHandle_bme, DelayTime);
    Clock_start(WaitingClockHandle_bme);
    Semaphore_pend(WClocksemaphoreHandle_bme,BIOS_WAIT_FOREVER);
}
static void i2ctransaction_bme()
{
    status_amb = I2C_transfer(i2c, &i2cTransaction_bme);
    if (!status_amb) {
        errorfunction_bme();
    }
    Semaphore_pend(semaphoreHandle_bme,BIOS_WAIT_FOREVER);
    // wait 1ms after each transfer
    DelayMsClock_bme(10);
}

bool I2CAmbientInit()
{
    //semaphore
    //Error_init(&eb_bme);
    Semaphore_Params_init(&semparams_bme);
    semparams_bme.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&semaphore_bme_struct, 0, &semparams_bme);
    semaphoreHandle_bme = Semaphore_handle(&semaphore_bme_struct);

    //semaphore
    //Error_init(&eb_bme2);
    Semaphore_Params_init(&WClocksemparams_bme);
    WClocksemparams_bme.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&WClocksemaphore_bme_struct, 0, &WClocksemparams_bme);
    WClocksemaphoreHandle_bme = Semaphore_handle(&WClocksemaphore_bme_struct);

    // clock param
    //Error_init(&eb_bme1);
    Clock_Params_init(&WaitingClockParam_bme);
    WaitingClockParam_bme.startFlag = false;
    WaitingClockParam_bme.period = 0;

    Clock_construct(&WaitingClockStruct_bme, ClockExpired_bme, 1, &WaitingClockParam_bme);
    WaitingClockHandle_bme = Clock_handle(&WaitingClockStruct_bme);

    // Open I2C
    I2C_Params_init(&params);
    params.transferMode  = I2C_MODE_CALLBACK;
    params.transferCallbackFxn = (I2C_CallbackFxn)callbackFxn_bme;
    params.bitRate  = I2C_400kHz;

    i2cTransaction_bme.readBuf = i2creadBuffer;
    i2cTransaction_bme.writeBuf = i2cwriteBuffer;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cTransaction_bme.arg = semaphoreHandle_bme;

    i2c = I2C_open(I2CAMBIENT, &params);
    if (!i2c) {
        return false;
    }
    return true;
}


bool BME280_Init()
{
    // check chip ID
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = CHIP_ID; // check chip id
    i2ctransaction_bme();
    if(i2creadBuffer[0] == 0x60)
    {
        isAmbientSensor_open = true;
    }
    else
    {
        isAmbientSensor_open = false;
        return isAmbientSensor_open;
    }


/****************************************************************************************/
    DelayMsClock_bme(10);

    // Read IR sensor calibration data
    BME280_GetCalib_Data();
    // config sensor run in force mode
    // Change the sensor to sleep mode
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = CTRL_MEASURE; // Ctrl measure register
    i2cwriteBuffer[1] = 0x00; // force to sleep mode
    i2ctransaction_bme();
    // Write config register
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = 0x77;
    i2cwriteBuffer[0] = CONFIG_REG; // Config register
    i2cwriteBuffer[1] = 0x00;  // Standby = 0.5ms, no filter , no spi
    i2ctransaction_bme();
    // Set control humidity
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = CTRL_HUM; // Ctrl_hum
    i2cwriteBuffer[1] = 0x01;  // oversampling x1
    i2ctransaction_bme();
    // Set ctrl measure
/*
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = CTRL_MEASURE; // Ctrl_meas
    i2cwriteBuffer[1] = 0x6D;  // oversampling x1 force mode, 0x01101101
    i2ctransaction_bme();*/
    return isAmbientSensor_open;


}
/****************************************************************************************/
void BME280_GetCalib_Data()
{
    uint16_t valtemp;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.readCount = 26;
    i2cwriteBuffer[0] = CALIBDATA0;
    //i2cwriteBuffer[1] = 0;
    i2ctransaction_bme();
    // fill calibration data
    memcpy((uint8_t *)&dig_T1,(uint8_t *)&i2creadBuffer[0],2);
    memcpy((uint8_t *)&dig_T2,(uint8_t *)&i2creadBuffer[2],2);
    memcpy((uint8_t *)&dig_T3,(uint8_t *)&i2creadBuffer[4],2);

    memcpy((uint8_t *)&dig_P1,(uint8_t *)&i2creadBuffer[6],2);
    memcpy((uint8_t *)&dig_P2,(uint8_t *)&i2creadBuffer[8],2);
    memcpy((uint8_t *)&dig_P3,(uint8_t *)&i2creadBuffer[10],2);
    memcpy((uint8_t *)&dig_P4,(uint8_t *)&i2creadBuffer[12],2);
    memcpy((uint8_t *)&dig_P5,(uint8_t *)&i2creadBuffer[14],2);
    memcpy((uint8_t *)&dig_P6,(uint8_t *)&i2creadBuffer[16],2);
    memcpy((uint8_t *)&dig_P7,(uint8_t *)&i2creadBuffer[18],2);
    memcpy((uint8_t *)&dig_P8,(uint8_t *)&i2creadBuffer[20],2);
    memcpy((uint8_t *)&dig_P9,(uint8_t *)&i2creadBuffer[22],2);



    memcpy((uint8_t *)&dig_H1,(uint8_t *)&i2creadBuffer[25],1);

    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.readCount = 7;
    i2cwriteBuffer[0] = CALIBDATA1;
    //i2cwriteBuffer[1] = 0;
    i2ctransaction_bme();
    memcpy((uint8_t *)&dig_H2,(uint8_t *)&i2creadBuffer[0],2);
    memcpy((uint8_t *)&dig_H3,(uint8_t *)&i2creadBuffer[2],1);

    valtemp = (((uint16_t)i2creadBuffer[3]) << 4) + ((uint16_t)(i2creadBuffer[4] & 0x0F));
    if (valtemp > 32767)
    {
        dig_H4 = (int16_t)((int32_t)65536 - (int32_t)valtemp);
    }
    else
    {
        dig_H4 = (int16_t)valtemp;
    }

    valtemp = (((uint16_t)i2creadBuffer[5]) << 4) + ((uint16_t)(i2creadBuffer[4] & 0xF0)>>4);
    if (valtemp > 32767)
    {
        dig_H5 = (int16_t)((int32_t)65536 - (int32_t)valtemp);
    }
    else
    {
        dig_H5 = (int16_t)valtemp;
    }
    memcpy((uint8_t *)&dig_H6,(uint8_t *)&i2creadBuffer[6],1);
}

void BME280_read(float * Temperature, float *Humidityout, float *Airpressure, uint32_t *u32Pressure)
{
   ///////////////////////////////////////////////////////////////////////////////////////////////////
    bool checkloop;
    int32_t  t_var1, t_var2, t_fine;
    int32_t  T;
    int64_t var1, var2, p_acc;
    int32_t var4;
    int32_t adc_T, adc_P, adc_H;
    uint32_t valtemp;
    uint32_t Pressure;
    uint32_t Humidity;
    float RH, Ta, Tc, Pws, Pws1;

    // force conversion
    // Set ctrl measure
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = CTRL_MEASURE; // Ctrl_meas
    i2cwriteBuffer[1] = 0x29; //2D // oversampling x1 force mode, 0x001010101
    i2ctransaction_bme();
    // waiting for conversion finish
    DelayMsClock_bme(9); // 9ms
    // check the status
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = STATUS_REG; // Measurement mode
    checkloop = true;
    while(checkloop)
    {
        i2ctransaction_bme();
        if ((i2creadBuffer[0] & 0x09) == 0)
        {
            checkloop = false;
            // calculation
            i2cTransaction_bme.writeCount = 1;
            i2cTransaction_bme.readCount = 8;
            i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
            i2cwriteBuffer[0] = DATAOUT_OFFSET; // Measurement mode
            i2ctransaction_bme();
            valtemp = ((uint32_t)i2creadBuffer[0]<<12)|((uint32_t)i2creadBuffer[1]<<4)|((uint32_t)i2creadBuffer[2]>>4);
            adc_P = (int32_t)valtemp;
            valtemp = ((uint32_t)i2creadBuffer[3]<<12)|((uint32_t)i2creadBuffer[4]<<4)|((uint32_t)i2creadBuffer[5]>>4);
            adc_T = (int32_t)valtemp;
            valtemp = ((uint32_t)i2creadBuffer[6]<<8) |((uint32_t)i2creadBuffer[7]);
            adc_H = (int32_t)valtemp;

            t_var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
            t_var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

            t_fine = t_var1 + t_var2;

            T = (t_fine * 5 + 128) >> 8;
            // Pressure


            var1 = ((int64_t)t_fine) - 128000;
            var2 = var1 * var1 * (int64_t)dig_P6;
            var2 = var2 + ((var1 * (int64_t)dig_P5)<<17);
            var2 = var2 + (((int64_t)dig_P4)<<35);
            var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
            var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
            if (var1 == 0)
            {
                p_acc = 0; // avoid exception caused by division by zero
            }
            else
            {
                p_acc = 1048576 - adc_P;
                p_acc = (((p_acc<<31) - var2)*3125)/var1;
                var1 = (((int64_t)dig_P9) * (p_acc>>13) * (p_acc>>13)) >> 25;
                var2 = (((int64_t)dig_P8) * p_acc) >> 19;
                p_acc = ((p_acc + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);

            }

            Pressure = (uint32_t)p_acc;
            //t_fine = t_fine - TEMPATURESELFHEATING*5120;
            var4= (t_fine - ((int32_t)76800));
            var4= (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * var4)) +
            ((int32_t)16384)) >> 15) * (((((((var4* ((int32_t)dig_H6)) >> 10) * (((var4* ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
            ((int32_t)dig_H2) + 8192) >> 14));
            var4= (var4- (((((var4>> 15) * (var4>> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
            var4= (var4< 0 ? 0 : var4);
            var4= (var4> 419430400 ? 419430400 : var4);
            Humidity = (uint32_t)(var4>>12);
        }
    }
    //return
    Ta = T*0.01f;
    RH = Humidity*9.765625e-4f;


    Tc = (Ta - TEMPATURESELFHEATING);
    *Temperature = Tc;
    *Airpressure    = Pressure*3.90625e-3f;
    // Offset humidity

    // Pws = 6.116441*10^((7.591386*Ta)/(Ta+240.7263));
    if(Ta < 50.0f)
    {
        Pws = 7.591386f*Ta/(Ta + 240.7263f);
        Pws =  powf(10.0f, Pws); // 10^(7.591386f*AH/(AH + 240.7263f))
        Pws = Pws* 6.116441f;
    }
    else
    {
        Pws = 7.337936f*Ta/(Ta + 229.3975f);
        Pws =  powf(10.0f, Pws); // 10^(7.591386f*AH/(AH + 240.7263f))
        Pws = Pws* 6.004918f;
    }
    if(Tc < 50.0f)
    {
        Pws1 = 7.591386f*Tc/(Tc + 240.7263f);
        Pws1 =  powf(10.0f, Pws1); // 10^(7.591386f*T/(T + 240.7263f))
        Pws1 = Pws1* 6.116441f;
    }
    else
    {
        Pws1 = 7.337936f*Tc/(Tc + 229.3975f);
        Pws1 =  powf(10.0f, Pws1); // 10^(7.591386f*T/(T + 240.7263f))
        Pws1 = Pws1* 6.004918f;
    }

    RH = RH * Pws / Pws1;

    if (RH > 100.0f)
    {
        RH = 100.0f;
    }

    *Humidityout = RH;
    *u32Pressure = Pressure;
   ///////////////////////////////////////////////////////////////////////////////////////////////////
    /*

    bool checkloop;
    int32_t valtemp, adc_P, adc_T, adc_H, t_fine;
    double var1;
    double var2;
    double temperature;
    double temperature_min = -40;
    double temperature_max = 85;
    double var3;
    double pressure;
    double pressure_min = 30000.0;
    double pressure_max = 110000.0;
    double var4;
    double var5;
    double var6;
    double humidity;
    double humidity_min = 0.0;
    double humidity_max = 100.0;

    // force conversion
    // Set ctrl measure
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = CTRL_MEASURE; // Ctrl_meas
    i2cwriteBuffer[1] = 0x25; //2D // oversampling x1 force mode, 0x00100101
    i2ctransaction_bme();
    // waiting for conversion finish
    DelayMsClock_bme(100); // 100ms
    // check the status
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
    i2cwriteBuffer[0] = STATUS_REG; // Measurement mode
    checkloop = true;
    while(checkloop)
    {
        i2ctransaction_bme();
        if ((i2creadBuffer[0] & 0x09) == 0)
        {
            checkloop = false;
            // calculation
            i2cTransaction_bme.writeCount = 1;
            i2cTransaction_bme.readCount = 8;
            i2cTransaction_bme.slaveAddress = BME280_ADDRESS;
            i2cwriteBuffer[0] = DATAOUT_OFFSET; // Measurement mode
            i2ctransaction_bme();
            DelayMsClock_bme(1);
            i2ctransaction_bme();


            valtemp = ((uint32_t)i2creadBuffer[0]<<12)|((uint32_t)i2creadBuffer[1]<<4)|((uint32_t)i2creadBuffer[2]>>4);
            adc_P = (int32_t)valtemp;
            valtemp = ((uint32_t)i2creadBuffer[3]<<12)|((uint32_t)i2creadBuffer[4]<<4)|((uint32_t)i2creadBuffer[5]>>4);
            adc_T = (int32_t)valtemp;
            valtemp = ((uint32_t)i2creadBuffer[6]<<8) |((uint32_t)i2creadBuffer[7]);
            adc_H = (int32_t)valtemp;

            var1 = ((double)adc_T) / 16384.0 - ((double)dig_T1) / 1024.0;
            var1 = var1 * ((double)dig_T2);
            var2 = (((double)adc_T) / 131072.0 - ((double)dig_T1) / 8192.0);
            var2 = (var2 * var2) * ((double)dig_T3);
            t_fine = (int32_t)(var1 + var2);
            temperature = (var1 + var2) / 5120.0;

            if (temperature < temperature_min)
                temperature = temperature_min;
            else if (temperature > temperature_max)
                temperature = temperature_max;


            // Pressure
            var1 = ((double)t_fine / 2.0) - 64000.0;
            var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
            var2 = var2 + var1 * ((double)dig_P5) * 2.0;
            var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
            var3 = ((double)dig_P3) * var1 * var1 / 524288.0;
            var1 = (var3 + ((double)dig_P2) * var1) / 524288.0;
            var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);
            // avoid exception caused by division by zero
            if (var1) {
                pressure = 1048576.0 - (double) adc_P;
                pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;
                var1 = ((double)dig_P9) * pressure * pressure / 2147483648.0;
                var2 = pressure * ((double)dig_P8) / 32768.0;
                pressure = pressure + (var1 + var2 + ((double)dig_P7)) / 16.0;

                if (pressure < pressure_min)
                    pressure = pressure_min;
                else if (pressure > pressure_max)
                    pressure = pressure_max;
            } else { // Invalid case
                pressure = pressure_min;
            }

            var1 = ((double)t_fine) - 76800.0;
            var2 = (((double)dig_H4) * 64.0 + (((double)dig_H5) / 16384.0) * var1);
            var3 = adc_H - var2;
            var4 = ((double)dig_H2) / 65536.0;
            var5 = (1.0 + (((double)dig_H3) / 67108864.0) * var1);
            var6 = 1.0 + (((double)dig_H6) / 67108864.0) * var1 * var5;
            var6 = var3 * var4 * (var5 * var6);
            humidity = var6 * (1.0 - ((double)dig_H1) * var6 / 524288.0);

            if (humidity > humidity_max)
                humidity = humidity_max;
            else if (humidity < humidity_min)
                humidity = humidity_min;

        }
    }
    //return
    *Temperature = (float) temperature;
    *Humidityout = (float) humidity;
    *Airpressure = (float) pressure;
    *u32Pressure = (uint32_t)pressure*256.0;*/
}

bool CCS811_Init() // must call after BME280_Init()
{
    DelayMsClock_bme(5000);
    // read harward ID
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = HW_ID_REG; // Ctrl_hum
    //i2cwriteBuffer[1] = 0x01;  // oversampling x1
    i2ctransaction_bme();
    if (i2creadBuffer[0] != 0x81)
    {
        errorfunction_ccs();
        return isCO2sensor_open;
    }
    // delay 50ms for loading program

    // read status
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = CCS811_STATUS_REG;
    i2ctransaction_bme();
    if (i2creadBuffer[0] & 0x10 == 0)
    {
        errorfunction_bme();
        return isCO2sensor_open;
    }
    // write APP_START
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = APP_START_REG; // Ctrl_hum
    //i2cwriteBuffer[1] = 0x01;  // oversampling x1
    i2ctransaction_bme();
    // read status
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = CCS811_STATUS_REG; // Ctrl_hum
    //i2cwriteBuffer[1] = 0x01;  // oversampling x1
    i2ctransaction_bme();
    if (i2creadBuffer[0] & 0x80 == 0)
    {
        errorfunction_bme();
        return isCO2sensor_open;
    }
    // Write drive mode and interrupt mode
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = MEAS_MODE_REG;
    i2cwriteBuffer[1] = DRIVE_MODE_1SEC;//DRIVE_MODE_10SEC;
    i2ctransaction_bme();

    isCO2sensor_open = true;
    return isCO2sensor_open;
}
void CCS811_Sleep(void)
{
    // Write drive mode and interrupt mode
   i2cTransaction_bme.readCount = 0;
   i2cTransaction_bme.writeCount = 2;
   i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
   i2cwriteBuffer[0] = MEAS_MODE_REG;
   i2cwriteBuffer[1] = DRIVE_MODE_IDLE;//DRIVE_MODE_1SEC;//DRIVE_MODE_10SEC;
   i2ctransaction_bme();
}
void CCS811_Wake(void)
{
    // Write drive mode and interrupt mode
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 2;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = MEAS_MODE_REG;
    i2cwriteBuffer[1] = DRIVE_MODE_1SEC;//DRIVE_MODE_10SEC;
    i2ctransaction_bme();
}
void CCS811_SW_Reset(void)
{
    // Write drive mode and interrupt mode
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 4;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = 0x11;
    i2cwriteBuffer[1] = 0xE5;//DRIVE_MODE_1SEC;//DRIVE_MODE_10SEC;
    i2cwriteBuffer[2] = 0x72;
    i2cwriteBuffer[3] = 0x8A;
    i2ctransaction_bme();
}
void CCS811_HW_nRESET(void)
{
    // Write drive mode and interrupt mode
    GPIO_write(MSP_EXP432P4011_CO2_RESET, Board_GPIO_LED_OFF);//outdoor
    DelayMsClock_bme(10);
    GPIO_write(MSP_EXP432P4011_CO2_RESET, Board_GPIO_LED_ON);//outdoor
    DelayMsClock_bme(10);
}
uint8_t CCS811_Read(uint16_t *CO2val, uint16_t *TVOCval)
{
    uint8_t Error = 255;
    // read status
    i2cTransaction_bme.readCount = 1;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = CCS811_STATUS_REG; // Ctrl_hum
    //i2cwriteBuffer[1] = 0x01;  // oversampling x1
    i2ctransaction_bme();
    if ((i2creadBuffer[0] & 0x08) != 0)
    {
        // data ready
        i2cTransaction_bme.readCount = 6;
        i2cTransaction_bme.writeCount = 1;
        i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
        i2cwriteBuffer[0] = ALG_RESULT_DATA; // Ctrl_hum
        //i2cwriteBuffer[1] = 0x01;  // oversampling x1
        i2ctransaction_bme();
        // assign value
        Error = i2creadBuffer[5];

        *CO2val = ((uint16_t)i2creadBuffer[0]<<8)|((uint16_t)i2creadBuffer[1]);
        *TVOCval =  ((uint16_t)i2creadBuffer[2]<<8)|((uint16_t)i2creadBuffer[3]);

    }
    return Error;
}

void CCS811_TemperatureUpdate(float Temperature, float Humidity)
{
    // convert temperature and humidity to fraction data
    uint16_t humiditytemp;
    uint16_t temperaturetemp;

    humiditytemp = (uint16_t)(Humidity*512.0f);
    temperaturetemp = (uint16_t)((Temperature+25.0f)*512.0f);
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 5;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = ENV_DATA;
    i2cwriteBuffer[1] = humiditytemp>>8;
    i2cwriteBuffer[2] = humiditytemp & 0xFF;
    i2cwriteBuffer[3] = temperaturetemp>>8;
    i2cwriteBuffer[4] = temperaturetemp & 0xFF;
    i2ctransaction_bme();

}

void CCS811_Baseline_Read(uint8_t * buff)
{
    i2cTransaction_bme.readCount = 2;
    i2cTransaction_bme.writeCount = 1;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = BASELINE;
    i2ctransaction_bme();
    // copy data output
    buff[0] = i2creadBuffer[0];
    buff[1] = i2creadBuffer[1];
}
void CCS811_Baseline_Write(uint8_t * buff)
{
    i2cTransaction_bme.readCount = 0;
    i2cTransaction_bme.writeCount = 3;
    i2cTransaction_bme.slaveAddress = CCS_811_ADDRESS;
    i2cwriteBuffer[0] = BASELINE;
    i2cwriteBuffer[1] = buff[0];
    i2cwriteBuffer[2] = buff[1];
    i2ctransaction_bme();
}



