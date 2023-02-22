/*
 * IR_Sensor.c
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/BIOS.h>
#include "IR_Sensor.h"
//////////////////////////////////////////////////////////////////////////////////////////
// Global variable
static I2C_Handle i2c_IRS;
static I2C_Params params_IRS;

static Semaphore_Handle semaphoreHandle_IRS;
static Semaphore_Handle WClocksemaphoreHandle_IRS;
static Clock_Handle WaitingClockHandle_IRS;

static Semaphore_Params semparams_IRS;
static Semaphore_Struct semaphoreStruct_IRS;
static Clock_Params WaitingClockParam_IRS;
static Clock_Struct WaitingClockStruct_IRS;
static Semaphore_Params WClocksemparams_IRS;
static Semaphore_Struct WClocksemaphoreStruct_IRS;

bool gIRsensorOk;
extern bool  IR_ImageUpdated;
static I2C_Transaction i2cTransaction_IRS;

//////////////////////////////////////////////////////////////////////////////////////////
// Callback function
// I2C callback
static void callbackFxn_IRS(I2C_Handle handle, I2C_Transaction *msg, Bool transfer) {
   if (msg->arg != NULL) {
       Semaphore_post((Semaphore_Handle)(msg->arg));
   }
}
// clock callback for delay function
static void ClockExpired_IRS(UArg Arg)
{
    Semaphore_post(WClocksemaphoreHandle_IRS);
}
// Delay function using time: not actual a delay
static void DelayMsClock_IRS(uint32_t DelayTime)
{
    Clock_setTimeout(WaitingClockHandle_IRS, DelayTime);
    Clock_start(WaitingClockHandle_IRS);
    Semaphore_pend(WClocksemaphoreHandle_IRS,BIOS_WAIT_FOREVER);
}
// I2C transfer function
static bool i2cdatatransfer_IRS()
{
    bool status_ir;
    status_ir = I2C_transfer(i2c_IRS, &i2cTransaction_IRS);
    if (!status_ir) {
        gIRsensorOk = false;
        return status_ir;
    }
    Semaphore_pend(semaphoreHandle_IRS,BIOS_WAIT_FOREVER);
    // wait 1ms after each transfer
    DelayMsClock_IRS(1);
    gIRsensorOk = true;
    return status_ir;
}
//////////////////////////////////////////////////////////////////////////////////////////
static unsigned char i2cwriteBuffer_IRS[4];
static unsigned char i2creadBuffer_IRS[258];
// Calibraiton data

#define NROFTAELEMENTS  7
#define NROFADELEMENTS  57
#define TABLEOFFSET     1024
#define DeltaX  0.01f    // 1/100.0f
#define DeltaY  0.015625f    // 1/64.0f

static const uint16_t TempTable[NROFADELEMENTS][NROFTAELEMENTS]  ={
                        {   0x0000, 0x0000, 1210,   1841,   2175,   2427,   2638    },
                        {   0x0000, 0x0000, 1586,   2001,   2282,   2508,   2703    },
                        {   0x0000, 1222,   1810,   2132,   2377,   2582,   2765    },
                        {   0x0000, 1592,   1976,   2244,   2462,   2651,   2822    },
                        {   1321,   1814,   2111,   2343,   2540,   2716,   2877    },
                        {   1643,   1979,   2226,   2431,   2612,   2776,   2929    },
                        {   1850,   2114,   2327,   2512,   2679,   2833,   2978    },
                        {   2008,   2228,   2417,   2586,   2741,   2887,   3026    },
                        {   2138,   2329,   2499,   2655,   2800,   2939,   3071    },
                        {   2250,   2419,   2574,   2719,   2856,   2988,   3115    },
                        {   2348,   2500,   2643,   2779,   2909,   3035,   3157    },
                        {   2436,   2575,   2708,   2836,   2959,   3080,   3198    },
                        {   2516,   2645,   2769,   2890,   3008,   3123,   3237    },
                        {   2590,   2709,   2826,   2941,   3054,   3165,   3275    },
                        {   2658,   2770,   2881,   2990,   3098,   3205,   3312    },
                        {   2722,   2828,   2933,   3037,   3141,   3244,   3347    },
                        {   2782,   2882,   2982,   3082,   3182,   3282,   3382    },
                        {   2839,   2934,   3029,   3125,   3222,   3319,   3416    },
                        {   2893,   2983,   3075,   3167,   3260,   3354,   3449    },
                        {   2944,   3030,   3118,   3207,   3297,   3389,   3481    },
                        {   2993,   3075,   3160,   3246,   3334,   3422,   3512    },
                        {   3039,   3119,   3201,   3284,   3369,   3455,   3543    },
                        {   3084,   3161,   3240,   3320,   3403,   3487,   3572    },
                        {   3127,   3201,   3278,   3356,   3436,   3518,   3601    },
                        {   3169,   3240,   3314,   3390,   3468,   3548,   3630    },
                        {   3209,   3278,   3350,   3424,   3500,   3578,   3658    },
                        {   3248,   3315,   3385,   3457,   3531,   3607,   3685    },
                        {   3286,   3351,   3418,   3488,   3561,   3636,   3712    },
                        {   3322,   3385,   3451,   3519,   3590,   3663,   3738    },
                        {   3358,   3419,   3483,   3550,   3619,   3691,   3764    },
                        {   3392,   3452,   3514,   3580,   3647,   3717,   3790    },
                        {   3426,   3484,   3545,   3609,   3675,   3743,   3814    },
                        {   3458,   3515,   3575,   3637,   3702,   3769,   3839    },
                        {   3490,   3545,   3604,   3665,   3728,   3794,   3863    },
                        {   3521,   3575,   3632,   3692,   3754,   3819,   3887    },
                        {   3551,   3604,   3660,   3719,   3780,   3844,   3910    },
                        {   3581,   3633,   3687,   3745,   3805,   3868,   3933    },
                        {   3610,   3661,   3714,   3770,   3829,   3891,   3955    },
                        {   3638,   3688,   3740,   3796,   3854,   3914,   3977    },
                        {   3666,   3715,   3766,   3820,   3877,   3937,   3999    },
                        {   3693,   3741,   3791,   3845,   3901,   3959,   4021    },
                        {   3720,   3767,   3816,   3869,   3924,   3982,   4042    },
                        {   3746,   3792,   3841,   3892,   3946,   4003,   4063    },
                        {   3772,   3817,   3865,   3915,   3969,   4025,   4083    },
                        {   3797,   3841,   3888,   3938,   3991,   4046,   4104    },
                        {   3822,   3865,   3912,   3961,   4012,   4067,   4124    },
                        {   3846,   3889,   3934,   3983,   4034,   4087,   4144    },
                        {   3870,   3912,   3957,   4004,   4055,   4108,   4163    },
                        {   3893,   3935,   3979,   4026,   4075,   4128,   4182    },
                        {   3917,   3957,   4001,   4047,   4096,   4147,   4201    },
                        {   3939,   3979,   4022,   4068,   4116,   4167,   4220    },
                        {   3962,   4001,   4043,   4088,   4136,   4186,   4239    },
                        {   3984,   4023,   4064,   4109,   4156,   4205,   4257    },
                        {   4006,   4044,   4085,   4129,   4175,   4224,   4275    },
                        {   4027,   4065,   4105,   4148,   4194,   4243,   4293    },
                        {   4048,   4085,   4125,   4168,   4213,   4261,   4311    },
                        {   4069,   4106,   4145,   4187,   4232,   4279,   4329    }};

static const uint16_t XTATemps[NROFTAELEMENTS]  = {2782,   2882,   2982,   3082,   3182,   3282,   3382};
static const uint16_t YADValues[NROFADELEMENTS] = {0,  64, 128,    192,    256,    320,    384,    448,    512,    576,
                                            640, 704,    768,    832,    896,    960,    1024,   1088,   1152,   1216,
                                            1280,    1344,   1408,   1472,   1536,   1600,   1664,   1728,   1792,   1856,
                                            1920,    1984,   2048,   2112,   2176,   2240,   2304,   2368,   2432,   2496,
                                            2560,    2624,   2688,   2752,   2816,   2880,   2944,   3008,   3072,   3136,
                                            3200,    3264,   3328,   3392,   3456,   3520,   3584};
#define PCSCALEVAL 1.0e8f


static uint16_t PTATValueAv;

static uint16_t VDDmeasureAv;
static uint16_t VDDCalib;
static float    VddScGrad;
static float    VddScOff;


static uint16_t ArrayOffset_top[128];
static uint16_t ArrayOffset_bot[128];

static int16_t  VddCompGradTop[128];
static int16_t  VddCompGradBot[128];
static int16_t  VddCompOffTop[128];
static int16_t  VddCompOffBot[128];

static float Ta;

static float gradScale;                 //calib

static float PTATGradient;                 //calib
static float PTATOffset;                   //calib

static int16_t   ThGrad_top[HALFSIZE];      //calib
static int16_t   ThGrad_bot[HALFSIZE];      //calib

static int16_t ThOffset_top[HALFSIZE];    //calib
static int16_t ThOffset_bot[HALFSIZE];    //calib

static float PCOverPixC_top[HALFSIZE];     // PCSCALEVAL/PixCij  --> calibration data
static float PCOverPixC_bot[HALFSIZE];     // PCSCALEVAL/PixCij  --> calibration data
static uint16_t TN;

static uint8_t commandconvert[4];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interpolate pixel temperature from calibration data
static float IR_Interpolation(float Tambient, float difftemp)
{
    uint16_t i, IdxTa0,IdxTa1,IdxTa, IdxAd0,IdxAd1,IdxAd;
    float Yval0, Yval1;
    float Temval;
    // find Ta location
    IdxTa0 = 0;
    IdxTa1 = NROFTAELEMENTS - 1;
    IdxTa = (IdxTa0 + IdxTa1)>>1;

    IdxAd0 = 0;
    IdxAd1 = NROFADELEMENTS - 1;
    IdxAd = (IdxAd0 + IdxAd1)>>1;

    difftemp = difftemp + TABLEOFFSET;
    for (i = 0;i<7;i++)
    {
        if (Tambient >= (float)XTATemps[IdxTa])
        {
            IdxTa0 = IdxTa;
        }
        else
        {
            IdxTa1 =  IdxTa;
        }
        IdxTa = (IdxTa0 + IdxTa1)>>1;

        if (difftemp >= (float)YADValues[IdxAd])
        {
            IdxAd0 = IdxAd;
        }
        else
        {
            IdxAd1 =  IdxAd;
        }
        IdxAd = (IdxAd0 + IdxAd1)>>1;
    }
    Yval0 = (float)TempTable[IdxAd][IdxTa] + (Tambient - (float)XTATemps[IdxTa])*DeltaX*((float)TempTable[IdxAd][IdxTa + 1] - (float)TempTable[IdxAd][IdxTa] );
    Yval1 = (float)TempTable[IdxAd+1][IdxTa] + (Tambient - (float)XTATemps[IdxTa])*DeltaX*((float)TempTable[IdxAd+1][IdxTa + 1] - (float)TempTable[IdxAd+1][IdxTa] );

    Temval = Yval0 + (Yval1 - Yval0)*(difftemp - YADValues[IdxAd])*DeltaY;
    return Temval;
}
//////////////////////////////////////////////////////////////////////////////
// Read calibration data from chip internal memory
static void IR_GetCalib_Data()
{
    // local variable
    float caltemp;
    float PixCmin;                      //calib-temporary
    float PixCmax;                      //calib-temporary
    uint16_t GlobalGain;                //calib-temporary
    uint8_t epsilon;                   //calib-temporary
    uint16_t Pij_top[HALFSIZE];        //calib-temporary
    uint16_t Pij_bot[HALFSIZE];        //calib-temporary
    uint16_t i,j;
    // get data
    i2cTransaction_IRS.slaveAddress = HTPA32x32d_EEROM_ADDRESS;

// Read PixCmin
    // set Address
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = 0x00;
    i2cwriteBuffer_IRS[1] = 0x00;
    gIRsensorOk = i2cdatatransfer_IRS();

    i2cTransaction_IRS.writeCount = 0;
    i2cTransaction_IRS.readCount = 256;
    gIRsensorOk = i2cdatatransfer_IRS();
    // assign PixCmin value
    memcpy((uint8_t *)(&PixCmin), &i2creadBuffer_IRS[0], 4);

//  Read PixCmax
    memcpy((uint8_t *)(&PixCmax), &i2creadBuffer_IRS[4], 4);
// Read gradScale
    gradScale = 1.0f/((float)(((int32_t)1)<<i2creadBuffer_IRS[8]));

    TN =   (((uint16_t)i2creadBuffer_IRS[12])<<8)|(uint16_t)i2creadBuffer_IRS[11];
    epsilon = i2creadBuffer_IRS[13];
    VDDCalib = (((uint16_t)i2creadBuffer_IRS[39])<<8)|(uint16_t)i2creadBuffer_IRS[38];
    memcpy((uint8_t *)(&PTATGradient), &i2creadBuffer_IRS[52], 4);
    memcpy((uint8_t *)(&PTATOffset), &i2creadBuffer_IRS[56], 4);

    VddScGrad = 1.0f/((float)(((int32_t)1)<<i2creadBuffer_IRS[78]));
    VddScOff = 1.0f/((float)(((int32_t)1)<<i2creadBuffer_IRS[79]));
    GlobalGain = (((uint16_t)i2creadBuffer_IRS[86])<<8)|(uint16_t)i2creadBuffer_IRS[85];

    // VddCompGradTop , VddCompGradBot
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = 0x03;
    i2cwriteBuffer_IRS[1] = 0x40;
    gIRsensorOk = i2cdatatransfer_IRS();
    i2cTransaction_IRS.writeCount = 0;
    i2cTransaction_IRS.readCount = 256;
    gIRsensorOk = i2cdatatransfer_IRS();
    memcpy(VddCompGradTop,i2creadBuffer_IRS,256);

    gIRsensorOk = i2cdatatransfer_IRS();
    memcpy(VddCompGradBot,i2creadBuffer_IRS,256);

    gIRsensorOk = i2cdatatransfer_IRS();
    memcpy(VddCompOffTop,i2creadBuffer_IRS,256);

    gIRsensorOk = i2cdatatransfer_IRS();
    memcpy(VddCompOffBot,i2creadBuffer_IRS,256);

    // ThGrad
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = 0x07;
    i2cwriteBuffer_IRS[1] = 0x40;
    gIRsensorOk = i2cdatatransfer_IRS();
    i2cTransaction_IRS.writeCount = 0;
    i2cTransaction_IRS.readCount = 256;
    for (j= 0;j<4;j++)
    {
        gIRsensorOk = i2cdatatransfer_IRS();
        memcpy(&ThGrad_top[128*j],i2creadBuffer_IRS,256);
    }
    for (j= 0;j<4;j++)
    {
        gIRsensorOk = i2cdatatransfer_IRS();
        memcpy(&ThGrad_bot[128*j],i2creadBuffer_IRS,256);
    }
    // ThOffset
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = 0x0F;
    i2cwriteBuffer_IRS[1] = 0x40;
    gIRsensorOk = i2cdatatransfer_IRS();
    i2cTransaction_IRS.writeCount = 0;
    i2cTransaction_IRS.readCount = 256;
    for (j= 0;j<4;j++)
    {
        gIRsensorOk = i2cdatatransfer_IRS();
        memcpy(&ThOffset_top[128*j],i2creadBuffer_IRS,256);
    }
    for (j= 0;j<4;j++)
    {
        gIRsensorOk = i2cdatatransfer_IRS();
        memcpy(&ThOffset_bot[128*j],i2creadBuffer_IRS,256);
    }
    // Pij
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = 0x17;
    i2cwriteBuffer_IRS[1] = 0x40;
    gIRsensorOk = i2cdatatransfer_IRS();
    i2cTransaction_IRS.writeCount = 0;
    i2cTransaction_IRS.readCount = 256;
    for (j= 0;j<4;j++)
    {
        gIRsensorOk = i2cdatatransfer_IRS();
        memcpy(&Pij_top[128*j],i2creadBuffer_IRS,256);
    }
    for (j= 0;j<4;j++)
    {
        gIRsensorOk = i2cdatatransfer_IRS();
        memcpy(&Pij_bot[128*j],i2creadBuffer_IRS,256);
    }

// calculate PCOverPixC
    for (i=0;i<HALFSIZE;i++)
    {
        caltemp = (((float)Pij_top[i])*(PixCmax-PixCmin)/65535.0f + PixCmin)*((float)epsilon)*((float)GlobalGain)/(1.0e6f);
        PCOverPixC_top[i] = PCSCALEVAL/caltemp;
        caltemp = (((float)Pij_bot[i])*(PixCmax-PixCmin)/65535.0f + PixCmin)*((float)epsilon)*((float)GlobalGain)/(1.0e6f);
        PCOverPixC_bot[i] = PCSCALEVAL/caltemp;
    }

}
//////////////////////////////////////////////////////////////////////////////
// Initialize the IR sensor
static void IR_Setting_Up()
{
    // get data
    i2cTransaction_IRS.slaveAddress = HTPA32x32d_ARRAY_ADDRESS;
    // ARRAY wake up
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = CONFIG_REG;
    i2cwriteBuffer_IRS[1] = ARRAY_WAKEUP;
    gIRsensorOk = i2cdatatransfer_IRS();
    // Set trim register
    i2cwriteBuffer_IRS[0] = TRIM_REG1;
    i2cwriteBuffer_IRS[1] = MBIT_TRIM;
    gIRsensorOk = i2cdatatransfer_IRS();

    i2cwriteBuffer_IRS[0] = TRIM_REG2;
    i2cwriteBuffer_IRS[1] = BIAS_TRIML;
    gIRsensorOk = i2cdatatransfer_IRS();


    i2cwriteBuffer_IRS[0] = TRIM_REG3;
    i2cwriteBuffer_IRS[1] = BIAS_TRIMR;
    gIRsensorOk = i2cdatatransfer_IRS();


    i2cwriteBuffer_IRS[0] = TRIM_REG4;
    i2cwriteBuffer_IRS[1] = CLK_TRIM;
    gIRsensorOk = i2cdatatransfer_IRS();

    i2cwriteBuffer_IRS[0] = TRIM_REG5;
    i2cwriteBuffer_IRS[1] = BPA_TRIML;
    gIRsensorOk = i2cdatatransfer_IRS();

    i2cwriteBuffer_IRS[0] = TRIM_REG6;
    i2cwriteBuffer_IRS[1] = BPA_TRIMR;
    gIRsensorOk = i2cdatatransfer_IRS();

    i2cwriteBuffer_IRS[0] = TRIM_REG7;
    i2cwriteBuffer_IRS[1] = PU_TRIM;
    gIRsensorOk = i2cdatatransfer_IRS();

    //i2cwriteBuffer[0] = CONFIG_REG;
    //i2cwriteBuffer[1] = START_BLOCK0;
    //i2ctransaction();
}
//////////////////////////////////////////////////////////////////////////////
// I2C initialization: call this function first
bool I2CIRinit()
{
    //semaphore
    Semaphore_Params_init(&semparams_IRS);
    semparams_IRS.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&semaphoreStruct_IRS, 0, &semparams_IRS);
    semaphoreHandle_IRS = Semaphore_handle(&semaphoreStruct_IRS);

    //semaphore
    Semaphore_Params_init(&WClocksemparams_IRS);
    WClocksemparams_IRS.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&WClocksemaphoreStruct_IRS, 0, &WClocksemparams_IRS);
    WClocksemaphoreHandle_IRS = Semaphore_handle(&WClocksemaphoreStruct_IRS);

    // clock param
    Clock_Params_init(&WaitingClockParam_IRS);
    WaitingClockParam_IRS.startFlag = false;
    WaitingClockParam_IRS.period = 0;
    Clock_construct(&WaitingClockStruct_IRS,ClockExpired_IRS, 1, &WaitingClockParam_IRS);
    WaitingClockHandle_IRS = Clock_handle(&WaitingClockStruct_IRS);


    // Open I2C
    I2C_Params_init(&params_IRS);
    params_IRS.transferMode  = I2C_MODE_CALLBACK;
    params_IRS.transferCallbackFxn = (I2C_CallbackFxn)callbackFxn_IRS;
    params_IRS.bitRate  = I2C_400kHz;
    i2c_IRS = I2C_open(I2CIR, &params_IRS);
    if (!i2c_IRS) {
        return false;
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////
void IR_Sensor_Init()
{

    i2cTransaction_IRS.readBuf = i2creadBuffer_IRS;
    i2cTransaction_IRS.writeBuf = i2cwriteBuffer_IRS;
    i2cTransaction_IRS.slaveAddress = HTPA32x32d_ARRAY_ADDRESS;
    i2cTransaction_IRS.arg = semaphoreHandle_IRS;
/****************************************************************************************/
    DelayMsClock_IRS(1);

    commandconvert[0] = START_BLOCK0;
    commandconvert[1] = START_BLOCK1;
    commandconvert[2] = START_BLOCK2;
    commandconvert[3] = START_BLOCK3;
    // Read IR sensor calibration data
    IR_GetCalib_Data();
    // Set ADC
    DelayMsClock_IRS(1);
    IR_Setting_Up();
}
//////////////////////////////////////////////////////////////////////////////
// Read pixel value from the sensor
void IR_Sensor_ReadPixel(float * buf)
{
    uint32_t i, j, idxtem, idxtem1;
    uint32_t Ptatvaltemp;
    float TaGradscale;
    float PTATVddScaleGrad;
    float VddVddScOff;
    float pixvaltemp;
    bool StatusCheck = true;

    PTATVddScaleGrad = PTATValueAv*VddScGrad;

    TaGradscale = PTATValueAv*gradScale;
    VddVddScOff = ((float)VDDmeasureAv - (float)VDDCalib)*VddScOff;

    i2cTransaction_IRS.slaveAddress = HTPA32x32d_ARRAY_ADDRESS;
    // trigger convert
    Ptatvaltemp  = 0;
    for (j = 0; j < 4; j++)
    {
        IR_ImageUpdated = false;
        i2cTransaction_IRS.writeCount = 2;
        i2cTransaction_IRS.readCount = 0;
        i2cwriteBuffer_IRS[0] = CONFIG_REG;
        i2cwriteBuffer_IRS[1] = commandconvert[j];
        i2cdatatransfer_IRS();
        // wait 30ms
//        DelayMsClock_IRS(30);
        DelayMsClock_IRS(5);
        // Read status
        i2cTransaction_IRS.writeCount = 1;
        i2cTransaction_IRS.readCount = 1;
        i2cwriteBuffer_IRS[0] = STATUS_REG;
        StatusCheck = true;
        while(StatusCheck)
        {
            i2cdatatransfer_IRS();
            if ((i2creadBuffer_IRS[0] & 0x01) != 0)
            {
                // read data top
                i2cTransaction_IRS.writeCount = 1;
                i2cTransaction_IRS.readCount = 258;
                i2cwriteBuffer_IRS[0] = READ_DATA_TOP;
                i2cdatatransfer_IRS();

                // assign value for PTAT and offset
                Ptatvaltemp += (((uint16_t)i2creadBuffer_IRS[0])<<8)|(uint16_t)i2creadBuffer_IRS[1];

                for (i = 0; i<128; i++)
                {
                    idxtem = 128*j + i;
                    pixvaltemp = (float)((((uint16_t)i2creadBuffer_IRS[2*i+2])<<8)|(uint16_t)i2creadBuffer_IRS[2*i+3]);
                    // calculate temperature
                    pixvaltemp = pixvaltemp - ((float)ThGrad_top[idxtem])*TaGradscale - (float)ThOffset_top[idxtem] - (float)ArrayOffset_top[i];
                    // vdd offset
                    pixvaltemp = pixvaltemp - ( ((float)VddCompGradTop[i]*PTATVddScaleGrad + VddCompOffTop[i]  )*VddVddScOff );

                    pixvaltemp = pixvaltemp*PCOverPixC_top[idxtem];

                    //  interpolation to get true temperature value
                    buf[idxtem] = IR_Interpolation(Ta, pixvaltemp)*HTPA32x32d_PIXEL_TEMP_CONVERSION - 273.15;
                    //PixTemperature[idxtem] = IR_Interpolation(Ta, pixvaltemp)*HTPA32x32d_PIXEL_TEMP_CONVERSION - 273.15;
                }

                // read data bottom
                i2cTransaction_IRS.writeCount = 1;
                i2cTransaction_IRS.readCount = 258;
                i2cwriteBuffer_IRS[0] = READ_DATA_BOT;
                i2cdatatransfer_IRS();

                // assign value for PTAT and offset
                Ptatvaltemp += (((uint16_t)i2creadBuffer_IRS[0])<<8)|(uint16_t)i2creadBuffer_IRS[1];

                for (i = 0; i<128; i++)
                {
                    idxtem  = idxtem = 128*j + i;
                    idxtem1 = 1024 - 128*j  - (i/32 + 1)*32 + (i % 32);
                    pixvaltemp = (float)((((uint16_t)i2creadBuffer_IRS[2*i+2])<<8)|(uint16_t)i2creadBuffer_IRS[2*i+3]);
                    // calculate temperature
                    pixvaltemp = pixvaltemp - ((float)ThGrad_bot[idxtem])*TaGradscale - (float)ThOffset_bot[idxtem] - (float)ArrayOffset_bot[i];
                    // vdd offset
                    pixvaltemp = pixvaltemp - ( ((float)VddCompGradBot[i]*PTATVddScaleGrad + VddCompOffBot[i]  )*VddVddScOff );

                    pixvaltemp = pixvaltemp*PCOverPixC_bot[idxtem];

                    //  interpolation to get true temperature value
                    buf[idxtem1] = IR_Interpolation(Ta, pixvaltemp)*HTPA32x32d_PIXEL_TEMP_CONVERSION - 273.15;
                    //PixTemperature[idxtem1] = IR_Interpolation(Ta, pixvaltemp)*HTPA32x32d_PIXEL_TEMP_CONVERSION - 273.15;
                }
                // calculate Ta for next conversion
                StatusCheck = false;
            }
        }
    }
    PTATValueAv = (uint16_t)(Ptatvaltemp>>3);
    Ta = ((float)PTATValueAv)*PTATGradient + PTATOffset;
    //memcpy(buf,PixTemperature, IR_ARRAY_SIZE*sizeof(float));

}
// Read ambient temperature of the sensor
void IR_Sensor_read_Ambient_Temp(float * Temperature)
{

    uint32_t vddtemp;
    // read offset
    uint32_t i;
    bool StatusCheck = true;
    bool IRcommunicateok;

    i2cTransaction_IRS.slaveAddress = HTPA32x32d_ARRAY_ADDRESS;
    // ARRAY wake up
    i2cTransaction_IRS.writeCount = 2;
    i2cTransaction_IRS.readCount = 0;
    i2cwriteBuffer_IRS[0] = CONFIG_REG;
    i2cwriteBuffer_IRS[1] = START_OFFSET;
    IRcommunicateok = i2cdatatransfer_IRS();
    if(IRcommunicateok)
    {
        // wait 30ms
        DelayMsClock_IRS(30);
        // Read status
        i2cTransaction_IRS.writeCount = 1;
        i2cTransaction_IRS.readCount = 1;
        i2cwriteBuffer_IRS[0] = STATUS_REG;
        while(StatusCheck)
        {
            if(i2cdatatransfer_IRS())
            {
                if ((i2creadBuffer_IRS[0] & 0x01) != 0)
                {
                    // read data
                    i2cTransaction_IRS.writeCount = 1;
                    i2cTransaction_IRS.readCount = 258;
                    // read top
                    i2cwriteBuffer_IRS[0] = READ_DATA_TOP;
                    IRcommunicateok = i2cdatatransfer_IRS();
                    // assign value for PTAT and offset
                    vddtemp = (uint32_t)((((uint16_t)i2creadBuffer_IRS[0])<<8)|(uint16_t)i2creadBuffer_IRS[1]);
                    for (i = 0; i<128; i++)
                    {
                        ArrayOffset_top[i] = (((uint16_t)i2creadBuffer_IRS[2*i+2])<<8)|(uint16_t)i2creadBuffer_IRS[2*i+3];
                    }
                    // read bottom
                    i2cwriteBuffer_IRS[0] = READ_DATA_BOT;
                    IRcommunicateok = i2cdatatransfer_IRS();
                    // assign value for PTAT and offset
                    vddtemp += (uint32_t)((((uint16_t)i2creadBuffer_IRS[0])<<8)|(uint16_t)i2creadBuffer_IRS[1]);
                    for (i = 0; i<128; i++)
                    {
                        ArrayOffset_bot[i] = (((uint16_t)i2creadBuffer_IRS[2*i+2])<<8)|(uint16_t)i2creadBuffer_IRS[2*i+3];
                    }
                    VDDmeasureAv = (uint16_t)(vddtemp >> 1);
                    StatusCheck = false;
                }
            }
            else
            {
                StatusCheck = false;
            }
        }
        *Temperature = (Ta*HTPA32x32d_PIXEL_TEMP_CONVERSION - 273.15);
    }
}
