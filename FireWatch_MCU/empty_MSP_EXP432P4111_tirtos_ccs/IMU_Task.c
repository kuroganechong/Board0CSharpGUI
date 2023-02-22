/*
 * IMU_Task.c
 *
 *  Created on: Mar 9, 2018
 *      Author: liyao
 */
#include <stdint.h>
#include <stdio.h>
#include <math.h>
/* For usleep() */
#include <unistd.h>
#include <stddef.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/I2C.h>
#include "msp.h"
//#include <driverlib.h>
#include <arm_math.h>
#include "arm_const_structs.h"

#include "Board.h"
#include "data_fusion.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "MPU9250_9Axis_MotionApps.h"
#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)
#define DEFAULT_MPU_HZ  (100)

struct rx_s {
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};
static struct hal_s hal = {0};
static signed char gyro_orientation[9] = { 1, 0, 0,
                                           0, 1, 0,
                                           0, 0, 1};


#define I2C_MAX_PACKAGE_LEN 200
#define I2C_INTERRUPT_MODE
//#define COMPASS_ENABLE
#define COMPASS_THRESHOLD 0.6f // 0.15f
// Stimulation channel
#define LEFTSTICHANNEL 0
#define RIGHTSTICHANNEL 3
#define LEFTCERCUSCHANNEL 1
#define RIGHTCERCUSCHANNEL 2

extern Semaphore_Handle Empty_SemHandle;



uint8_t fifoBuffer[48]; // FIFO storage buffer
unsigned long period, current_time, last_time;
float volatile speed[3], position[3];
//float spdmax[2], spdmin[2], positionmax[2], positionmin[2];
float quat_float[4];
float accel_float[3];
signed short accel_raw[3];
int offsetcount = 0;
int accel_offset[3];
float ypr[3];
float p_matrix[3] = {1, 0.04, 0.04};
float accel_cali[3] = {0, 0, 0};
float accel_prev[2];
float speedUpdate[2], positionUpdate[2], p_matrixUpdate[3];
float yaw_bias, mag_angle, mag_float[3], mag_cali_hori[6];
float sin_bias, cos_bias;
float variance = 0.0;
float stdev = 0.0;

float no_motion_threshold = 0.00005f;
volatile float movinggain = 0.5f;
const int zvarsample = 20;
float varz[zvarsample];
const float variancethres = 0.0000035f;
const float yawdriftrate = -0.00004359f;            // Driftrate per 0.01s
extern bool StimulationStartStop;                   // Stimulation Indicator
extern bool ChannelActive[NO_CHANNEL_STI];          // Stimulation Channel Indicator
float stimulationShrinkGain = 0.1f;
float stimulationReGain = 10.0f;
bool  stimulationGainChanged = false;
uint32_t tickCounter = 0;
//IIR filtering - butterworth bandpass filter order 2 - bandpass 0.2Hz to 5Hz
//const double b[5] = {0.0051, 0, -0.0103, 0, 0.0051};
//const double a[5] = {1.0000, -3.7856,  5.3793, -3.4016, 0.8079};
//butterworth filter with cutoff f = 5 Hz
const double b[5] = {0.0000312, 0.0001250, 0.0001874, 0.0001250, 0.0000312};
const double a[5] = {1.0, -3.5897, 4.8513, -2.9241, 0.6630};
uint8_t ivar = 0;
// For Duoc: Omega calculation //
float currentYaw = 0.0f;
float previousYaw = 0.0f;
float omegaBuffer[10];
int omegaIdx = 0;
float omega = 0.0f; // For Duoc: use it for angular speed, radian per second
float absolutespeed = 0.0f; //For Duoc: use it for linear speed, m per second
bool  IMUready = false;
bool ismoving = false;

// IMU data save for further process: 256 data
int16_t IMUdataBlock[1792];
uint8_t IdxRoundBuffer;

uint8_t CntforFlashing = 0;
uint8_t accel_count = 0;
uint32_t Skipcnt = 0;
bool skipflage = FALSE;
bool stable_flag = FALSE;
bool blinkEnable = FALSE;
bool updatePosition = FALSE;
uint32_t mstimecnt;
#ifdef COMPASS_ENABLE
float mag_offset[3], mag_k[3], mag_intensity[2], mag_tmp[4], mag_anchor[4][2], mag_anchor_new[4];
bool new_mag;
bool mag_hori_done = FALSE;
uint8_t mag_anchor_cnt, mag_record_cnt;
static void mag_calibration();
static float Find_nearest_mag_anchor(float angle, uint8_t* pos);
#endif

/*********************************************************************
 * PROFILE CALLBACKS
 */
Semaphore_Handle SemHandle_IMU_Task;    //Task Handler

Semaphore_Handle semaphoreHandle_IMU_driver;        //I2C communication with controller - equal to Semi2chdl
Semaphore_Params semparams_IMU_driver;
Error_Block eb_IMU_driver;

Semaphore_Handle WClocksemaphoreHandle_IMU;         //Clock Semaphore - equal to Semdelayhdl
Semaphore_Params WClocksemparams_IMU;
Error_Block eb_IMU2;

Clock_Handle WaitingClockHandle_IMU;                // CLock Handler - equal to
Clock_Params WaitingClockParam_IMU;
Error_Block eb_IMU1;
//I2C handler - equal to i2c_IMU before
static I2C_Handle      i2c;
static I2C_Transaction i2cTransaction;
static uint8_t         txBuffer[I2C_MAX_PACKAGE_LEN];
static uint8_t         rxBuffer[I2C_MAX_PACKAGE_LEN];
static bool            transactionstatus;
//////////////////////////////////////////////////////////////////////////////////////
// IMU
static int result;
static unsigned char accel_fsr;
unsigned short gyro_rate, gyro_fsr;
static uint32_t  timestamp, timestampold;
       float     imuintperiod;
static uint8_t   imuintcnt;

static struct int_param_s int_param;
short gyro[3], accel[3], sensors;
unsigned char more;
long quat[4];
unsigned long sensor_timestamp;
struct imustruct{
    float acc[3];
    //int16_t qua[4];
}imustruct;

struct imustruct IMUbuff[IMU_BUF_SIZE];
struct imustruct IMUfiltered[IMU_BUF_SIZE];
struct imustruct IMUiirfiltered[IMU_BUF_SIZE];
float IMUAcc[IMU_BUF_SIZE];

float yawbuf[IMU_BUF_SIZE], rollbuf[IMU_BUF_SIZE];
uint16_t  imubuferfil, imufilteredidx, imuiirfilteredidx;
bool readytofilter = false;
bool readytoanalyze = false;
//////////////////////////////////////////////////////////////////////////////////////
uint8_t ledtoglecnt = 0;
//Function declaration
//Data saving
int16_t u16tempval;
int16_t quat_int16[4];
int16_t accel_int16[3];

//static void initgpio(void);
//static void taskinit(void);

static void ClockExpired_IMU(UArg Arg);
void get_ms(unsigned long *count);
void delay_ms(unsigned long num_ms);
int i2c_write(unsigned char slave_addr, unsigned char reg_addr,unsigned char length, const unsigned char *data);
int i2c_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char *data);
static void imuinit(void);
static void tap_cb(unsigned char direction, unsigned char count);
static inline unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);
static inline unsigned short inv_row_2_scale(const signed char *row);
static void run_self_test(void);
void gpioButtonFxn1(uint_least8_t index);
void IMUCalculation();
static float angle_average(float ang1, float ang2, uint8_t num1, uint8_t num2);
static void project_rad(float *rad);


void IMU_Task(UArg arg0, UArg arg1)
{

    IMUready = false;
    //int result;
    Semaphore_Params semparams_IMU_Task;
    Error_Block eb_IMU_Task;
    //semaphore
    Semaphore_Params_init(&semparams_IMU_Task);
    semparams_IMU_Task.mode = Semaphore_Mode_COUNTING;
    SemHandle_IMU_Task = Semaphore_create(0, &semparams_IMU_Task, &eb_IMU_Task);

    /* Configure the LED pin, GPIO initialization */
    GPIO_setConfig(MSP_EXP432P4011_GPIO_LED6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    //GPIO_setConfig(MSP_EXP432P401R_SPI_SIMO, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    //GPIO_setConfig(MSP_EXP432P401R_SPI_SOMI, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_NONE);
    /* Turn on user LED */
    GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_ON);
    // init I2C for IMU at IMUinit

    //semaphore for i2c
    Error_init(&eb_IMU_driver);
    Semaphore_Params_init(&semparams_IMU_driver);
    semparams_IMU_driver.mode = Semaphore_Mode_COUNTING;
    semaphoreHandle_IMU_driver = Semaphore_create(0, &semparams_IMU_driver, &eb_IMU_driver);


    //semaphore for clock
    Error_init(&eb_IMU2);
    Semaphore_Params_init(&WClocksemparams_IMU);
    WClocksemparams_IMU.mode = Semaphore_Mode_BINARY;
    WClocksemaphoreHandle_IMU = Semaphore_create(0, &WClocksemparams_IMU, &eb_IMU2);

    // clock param - for tick measurement and delay_ms
    Error_init(&eb_IMU1);
    Clock_Params_init(&WaitingClockParam_IMU);
    WaitingClockParam_IMU.startFlag = false;
    WaitingClockParam_IMU.period = 0;
    WaitingClockHandle_IMU = Clock_create(ClockExpired_IMU, 1, &WaitingClockParam_IMU, &eb_IMU1);

    sleep(5);

    period = 10;
    last_time = 0;
    current_time = 0;
    imuinit();

    GPIO_setConfig(MSP_EXP432P4011_INT_IMU, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);
    // install Button callback
    GPIO_setCallback(MSP_EXP432P4011_INT_IMU, gpioButtonFxn1);
    /* Enable interrupts */
    GPIO_enableInt(MSP_EXP432P4011_INT_IMU);
    //Turn off LED6 - wait till stable to turn on again
    GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_OFF);
    IMUready = true;
    imubuferfil = 0;
    imuiirfilteredidx = 0;

    IMUready = true;
    IdxRoundBuffer = 0;
    position[0] = 0.0f;
    position[1] = 0.0f;
    speed[0] = 0.0f;
    speed[1] = 0.0f;

    while (1)
    {
        Semaphore_pend(SemHandle_IMU_Task,BIOS_WAIT_FOREVER);
        dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);

        //Quarternion to q14 format and save to buffer
        u16tempval = (quat[0] >> 16);
        quat_float[0] = ((float)u16tempval) / quat_res;
        memcpy(&quat_int16[0],&u16tempval, 2);
        u16tempval = (quat[1] >> 16);
        quat_float[1] = ((float)u16tempval) / quat_res;
        memcpy(&quat_int16[1],&u16tempval, 2);
        u16tempval = (quat[2] >> 16);
        quat_float[2] = ((float)u16tempval) / quat_res;
        memcpy(&quat_int16[2],&u16tempval, 2);
        u16tempval = (quat[3] >> 16);
        quat_float[3] = ((float)u16tempval) / quat_res;
        memcpy(&quat_int16[3],&u16tempval, 2);

        //Cast accel to int16 format and save to buffer
        u16tempval = ((int16_t)accel[0]);
        accel_raw[0] = u16tempval;
        memcpy(&accel_int16[0],&u16tempval, 2);
        u16tempval = ((int16_t)accel[1]);
        accel_raw[1] = u16tempval;
        memcpy(&accel_int16[1],&u16tempval, 2);
        u16tempval = ((int16_t)accel[2]);
        accel_raw[2] = u16tempval;
        memcpy(&accel_int16[2],&u16tempval, 2);

        // Save data to round buffer
        u16tempval = 7 * IdxRoundBuffer;
        memcpy(&IMUdataBlock[u16tempval], &accel_int16[0], 6);
        u16tempval += 3;
        memcpy(&IMUdataBlock[u16tempval] , &quat_int16[0], 8);

        IdxRoundBuffer++;


        //Test blinking
        if(imuintcnt == 100)
        {
            GPIO_toggle(MSP_EXP432P4011_GPIO_LED6);
            imuintcnt = 0;
        }

        //Get current yaw pitch roll
        mpu_dmpGetYawPitchRollNew(quat_float, ypr);
        mpu_dmpGetLinearAccel(accel_raw, quat_float, accel_float);
        mpu_dmpGetLinearAccelInFrame(yaw_bias, ypr, accel_float);
        //Check position validity - 100m area
        if(position[0] > 100 || position[0] < -100)
            position[0] = 0.0f;
        if(position[1] > 100 || position[1] < -100)
            position[1] = 0.0f;
        // Adjust the gain if being stimulated
        if(StimulationStartStop)                // Stimulation is being activated
        {
            if(!stimulationGainChanged)         // Upper - Original Gain value
            {
                if(ChannelActive[LEFTSTICHANNEL] || ChannelActive[RIGHTSTICHANNEL])    // Turning stimulation - to be updated
                {
                    movinggain *= stimulationShrinkGain;
                    stimulationGainChanged = true;          // Adjust down
                }
            }
        }
        else
        {
            if(stimulationGainChanged)
            {
                movinggain *= stimulationReGain;            // Adjust up
                stimulationGainChanged = false;
            }
        }
        // For Duoc: calculate and save current omega to omega buffer
        currentYaw = ypr[0];
        omegaBuffer[omegaIdx] = (currentYaw - previousYaw) * 100;   // * 100 because the differentiation delta t = 0.01s
        // Remove the abnormality due to wrapping
        if(omegaBuffer[omegaIdx] > PI * 100)
            omegaBuffer[omegaIdx] -= 2 * PI * 100;
        if(omegaBuffer[omegaIdx] < -PI * 100)
            omegaBuffer[omegaIdx] += 2 * PI * 100;
        omegaIdx++;
        if (omegaIdx == 10)     //End index reach, revert the beginning index
            omegaIdx = 0;
        previousYaw = currentYaw;
        if(skipflage)
        {

            IMUbuff[imubuferfil].acc[0] = accel_float[0]; //- accel_float_offset[0];
            IMUbuff[imubuferfil].acc[1] = accel_float[1]; //- accel_float_offset[1];
            IMUbuff[imubuferfil].acc[2] = accel_float[2]; //- accel_float_offset[2];

            if(!stable_flag)
            {
                /*if (yaw_bias == 0)
                    yaw_bias = ypr[0];
                else
                    //yaw_bias = angle_average(yaw_bias, ypr[0], 4, 1);
                    yaw_bias = ypr[0];*/
                yaw_bias = ypr[0];
                if (fabsf(ypr[1]) < 0.1 && fabsf(ypr[2]) < 0.1)
                {
                    accel_count++;
                }
                else
                {
                    accel_count--;
                }
                offsetcount ++;
                if(accel_count >= 100)
                {
                    stable_flag = true;
                    GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_ON);
                }
            }
            else
            {
                tickCounter++;
                if (tickCounter == 8258700)             // (360 / -yawDriftrate)/100
                {
                    tickCounter = 0;                    // Restart the counter
                }
                float tempBuffer[33];
                if(readytofilter)
                {
                    // Adjust yaw angle
                    ypr[0] -= tickCounter * yawdriftrate * deg2rad;
                    //filter x accel
                    int i;
                    for(i = 0; i < 33; i++)
                    {
                        if(imubuferfil >= i)
                            tempBuffer[i] = IMUbuff[imubuferfil - i].acc[0];
                        else
                            tempBuffer[i] = IMUbuff[imubuferfil + IMU_BUF_SIZE - i].acc[0];
                    }
                    IMUfiltered[imufilteredidx].acc[0] = fir_filtering(tempBuffer);

                    //filter y accel
                    for(i = 0; i < 33; i++)
                    {
                        if(imubuferfil >= i)
                            tempBuffer[i] = IMUbuff[imubuferfil - i].acc[1];
                        else
                            tempBuffer[i] = IMUbuff[imubuferfil + IMU_BUF_SIZE - i].acc[1];
                    }
                    IMUfiltered[imufilteredidx].acc[1] = fir_filtering(tempBuffer);

                    //filter z accel
                    for(i = 0; i < 33; i++)
                    {
                        if(imubuferfil >= i)
                            tempBuffer[i] = IMUbuff[imubuferfil - i].acc[2];
                        else
                            tempBuffer[i] = IMUbuff[imubuferfil + IMU_BUF_SIZE - i].acc[2];
                    }
                    IMUfiltered[imufilteredidx].acc[2] = fir_filtering(tempBuffer);
                    IMUAcc[imufilteredidx] = sqrt(IMUfiltered[imufilteredidx].acc[0] * IMUfiltered[imufilteredidx].acc[0] +
                                                  IMUfiltered[imufilteredidx].acc[1] * IMUfiltered[imufilteredidx].acc[1] +
                                                  IMUfiltered[imufilteredidx].acc[2] * IMUfiltered[imufilteredidx].acc[2]);
                    yawbuf[imufilteredidx] = ypr[0];
                    rollbuf[imufilteredidx] = ypr[2];


                }
                //calculate variance and position
                if(readytoanalyze)
                {
                    //Get the orientation of 0.1s ago
                    float tempyaw, temproll;      //Previous yaw angle corresponding to the accel variance used in this case
                    int stepback = 10;            //How many stepback to get yaw angle - previous time mark = 0.01 * stepback;
                    if(imufilteredidx >= stepback)
                    {
                        tempyaw = yawbuf[imufilteredidx - stepback];
                        temproll = rollbuf[imufilteredidx - stepback];
                    }

                    else
                    {
                        tempyaw = yawbuf[imufilteredidx + IMU_BUF_SIZE - stepback];
                        temproll = rollbuf[imufilteredidx + IMU_BUF_SIZE - stepback];
                    }

                    //Calculate variance
                    for(ivar = 0; ivar < zvarsample; ivar ++)
                    {
                        if(imufilteredidx >= ivar)
                            varz[ivar] = IMUAcc[imufilteredidx - ivar];
                        else
                            varz[ivar] = IMUAcc[imufilteredidx + IMU_BUF_SIZE - ivar];
                    }
                    arm_var_f32(varz, zvarsample, &variance);
                    stdev = sqrt(variance);
                    if(variance < variancethres)//avoid accumulation of low-value variance - baseline filtering
                    {
                        absolutespeed = 0.0;
                        speed[0] = 0.0;
                        speed[1] = 0.0;
                        speed[2] = 0.0;
                    }
                    else
                    {
                        absolutespeed = stdev * movinggain;
                        speed[0] = stdev * movinggain * cos(tempyaw - yaw_bias) * cos(temproll);
                        speed[1] = stdev * movinggain * sin(tempyaw - yaw_bias) * cos(temproll);
                        speed[2] = stdev * movinggain * sin(temproll);
                    }
                    single_integration(p_matrix,speed,position);
                    //For Duoc: calculate omega here - average of omegabuffer, which means the average omega in the last 0.1s
                    //We can change it if it is too delayed but as usual, response speed costs stability
                    float tempOmega = 0.0f;
                    int i = 0;
                    for (i=0; i<10; i++)
                    {
                        tempOmega += omegaBuffer[i];
                    }
                    omega = tempOmega * 0.1;
                }



            }
            //imuiirfilteredidx++;
            //if(imuiirfilteredidx >= IMU_BUF_SIZE)
            //    imuiirfilteredidx = 0;
            imufilteredidx++;
            if(imufilteredidx >= IMU_BUF_SIZE)
            {
                imufilteredidx = 0;
            }
            if(imufilteredidx > 20)
                readytoanalyze = true;

            imubuferfil++;
            if(imubuferfil >= IMU_BUF_SIZE)
                imubuferfil = 0;
            if(imubuferfil == 33)
                readytofilter = true;

        }
        else
        {
            Skipcnt++;

            if(Skipcnt > 1000) //Wait 10 seconds for stabilization
            {
                skipflage = true;
                //GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_ON);

            }

        }

    }
}
void gpioButtonFxn1(uint_least8_t index)
{
    if(imuintcnt == 0){
        timestamp = mstimecnt;
        // update interrupt period
        imuintperiod = (timestamp - timestampold)*3.90625e-6f;
        timestampold = timestamp;
    }
    imuintcnt++;
    Semaphore_post(SemHandle_IMU_Task);
}
/// i2c
void i2ccallbackFxn(I2C_Handle handle, I2C_Transaction *msg, bool transfer)
{
    transactionstatus = transfer;
    Semaphore_post(semaphoreHandle_IMU_driver);
}
static void imuinit(void){
    timestamp = 0;
    timestampold = 0;
    imuintperiod = 0.01f;
    imuintcnt = 0;
    imubuferfil = 0;
    transactionstatus = false;

    I2C_Params      i2cParams;
    I2C_init();
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2cParams.transferMode = I2C_MODE_CALLBACK;
    i2cParams.transferCallbackFxn = i2ccallbackFxn;
    i2c = I2C_open(MSP_EXP432P4011_I2CB2, &i2cParams);
    if (i2c == NULL) {
        while (1);
    }
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.writeBuf = txBuffer;
    // check chip ID
    unsigned char whoami = 0;
    while(whoami != 0x71){
        i2c_read(0x68, 0x75, 1, &whoami);
        delay_ms(100);
        GPIO_toggle(MSP_EXP432P4011_GPIO_LED6);
    }
    // Configure IMU
    /* Set up gyro.
     * Every function preceded by mpu_ is a driver function and can be found
     * in inv_mpu.h.
     */

    result = mpu_init(&int_param);
    if (result)
        while(1);
    /* Get/set hardware configuration. Start gyro. */
    /* Wake up all sensors. */
    mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    /* Push both gyro and accel data into the FIFO. */
    mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    mpu_set_sample_rate(DEFAULT_MPU_HZ);
    /* Read back configuration in case it was set improperly. */
    mpu_get_sample_rate(&gyro_rate);
    mpu_get_gyro_fsr(&gyro_fsr);
    mpu_get_accel_fsr(&accel_fsr);
    /* Initialize HAL state variables. */
    memset(&hal, 0, sizeof(hal));
    hal.sensors = ACCEL_ON | GYRO_ON;
    //hal.report = PRINT_QUAT;
    /* To initialize the DMP:
     * 1. Call dmp_load_motion_driver_firmware(). This pushes the DMP image in
     *    inv_mpu_dmp_motion_driver.h into the MPU memory.
     * 2. Push the gyro and accel orientation matrix to the DMP.
     * 3. Register gesture callbacks. Don't worry, these callbacks won't be
     *    executed unless the corresponding feature is enabled.
     * 4. Call dmp_enable_feature(mask) to enable different features.
     * 5. Call dmp_set_fifo_rate(freq) to select a DMP output rate.
     * 6. Call any feature-specific control functions.
     *
     * To enable the DMP, just call mpu_set_dmp_state(1). This function can
     * be called repeatedly to enable and disable the DMP at runtime.
     *
     * The following is a short summary of the features supported in the DMP
     * image provided in inv_mpu_dmp_motion_driver.c:
     * DMP_FEATURE_LP_QUAT: Generate a gyro-only quaternion on the DMP at
     * 200Hz. Integrating the gyro data at higher rates reduces numerical
     * errors (compared to integration on the MCU at a lower sampling rate).
     * DMP_FEATURE_6X_LP_QUAT: Generate a gyro/accel quaternion on the DMP at
     * 200Hz. Cannot be used in combination with DMP_FEATURE_LP_QUAT.
     * DMP_FEATURE_TAP: Detect taps along the X, Y, and Z axes.
     * DMP_FEATURE_ANDROID_ORIENT: Google's screen rotation algorithm. Triggers
     * an event at the four orientations where the screen should rotate.
     * DMP_FEATURE_GYRO_CAL: Calibrates the gyro data after eight seconds of
     * no motion.
     * DMP_FEATURE_SEND_RAW_ACCEL: Add raw accelerometer data to the FIFO.
     * DMP_FEATURE_SEND_RAW_GYRO: Add raw gyro data to the FIFO.
     * DMP_FEATURE_SEND_CAL_GYRO: Add calibrated gyro data to the FIFO. Cannot
     * be used in combination with DMP_FEATURE_SEND_RAW_GYRO.
     */
    dmp_load_motion_driver_firmware();
    dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
    dmp_register_tap_cb(tap_cb);
    //Set low pass filter to 10 Hz
    mpu_set_lpf(10);
    //dmp_register_android_orient_cb(android_orient_cb);
    /*
     * Known Bug -
     * DMP when enabled will sample sensor data at 200Hz and output to FIFO at the rate
     * specified in the dmp_set_fifo_rate API. The DMP will then sent an interrupt once
     * a sample has been put into the FIFO. Therefore if the dmp_set_fifo_rate is at 25Hz
     * there will be a 25Hz interrupt from the MPU device.
     *
     * There is a known issue in which if you do not enable DMP_FEATURE_TAP
     * then the interrupts will be at 200Hz even if fifo rate
     * is set at a different rate. To avoid this issue include the DMP_FEATURE_TAP
     */
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL;
    dmp_enable_feature(hal.dmp_features);
    dmp_set_fifo_rate(DEFAULT_MPU_HZ);
    mpu_set_dmp_state(1);
    hal.dmp_on = 1;
    // sefl test
    delay_ms(100);
    //long gyro1[3], accel1[3];
    //result = mpu_run_6500_self_test(gyro1, accel1, 0);
    run_self_test();

}
//IMU functions

/* The following functions must be defined for this platform:
 * i2c_write(unsigned char slave_addr, unsigned char reg_addr,
 *      unsigned char length, unsigned char const *data)
 * i2c_read(unsigned char slave_addr, unsigned char reg_addr,
 *      unsigned char length, unsigned char *data)
 * delay_ms(unsigned long num_ms)
 * get_ms(unsigned long *count)
 * reg_int_cb(void (*cb)(void), unsigned char port, unsigned char pin)
 * labs(long x)
 * fabsf(float x)
 * min(int a, int b)
 */
/////////////////////////////////////////////////////////////////////////////////////////
int i2c_write(unsigned char slave_addr, unsigned char reg_addr,
              unsigned char length, const unsigned char *data)
{
    int i;
    i2cTransaction.slaveAddress = slave_addr;
    i2cTransaction.readCount = 0;
    txBuffer[0] = reg_addr;
    // clone data
    for (i = 0; i<length; i++){
        txBuffer[1 + i] = data[i];
    }
    i2cTransaction.writeCount = length + 1;
    I2C_transfer(i2c, &i2cTransaction);
    delay_ms(1);
    Semaphore_pend(semaphoreHandle_IMU_driver,BIOS_WAIT_FOREVER);
    if (transactionstatus)
        return 0;
    else
        return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////
int i2c_read(unsigned char slave_addr, unsigned char reg_addr,
       unsigned char length, unsigned char *data){
    int i;
    i2cTransaction.slaveAddress = slave_addr;
    txBuffer[0] = reg_addr;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readCount = length;
    I2C_transfer(i2c, &i2cTransaction);
    delay_ms(1);
    Semaphore_pend(semaphoreHandle_IMU_driver,BIOS_WAIT_FOREVER);
    for (i = 0; i<length; i++){
        data[i] = rxBuffer[i];
    }
    if (transactionstatus)
        return 0;
    else
        return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////
void get_ms(unsigned long *count){
    *count = mstimecnt;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
static void tap_cb(unsigned char direction, unsigned char count)
{
    return;
}

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static inline unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}
/////////////////////////////////////////////////////////////////////////////////////////
static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];
    unsigned char i = 0;

    result = mpu_run_6500_self_test(gyro, accel, 0);

    if (result == 0x7) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        // Forced offset here
        //accel[0] = -825;
        //accel[1] = 4513;
        //accel[2] = 2362;
        //gyro[0] = 92130;
        //gyro[1] = 44104;
        //gyro[2] = -86092;

        for(i = 0; i<3; i++) {
            gyro[i] = (long)(gyro[i] * 32.8f); //convert to +-1000dps
            accel[i] *= 2048.f; //convert to +-16G
            accel[i] = accel[i] >> 16;
            gyro[i] = (long)(gyro[i] >> 16);
        }
        // Forced offset here

        mpu_set_gyro_bias_reg(gyro);
        mpu_set_accel_bias_6500_reg(accel);
    }
}
static void ClockExpired_IMU(UArg Arg)
{
    mstimecnt++;
    Semaphore_post(WClocksemaphoreHandle_IMU);
}
void delay_ms(unsigned long num_ms)
{
    Clock_setTimeout(WaitingClockHandle_IMU, num_ms);
    Clock_start(WaitingClockHandle_IMU);
    Semaphore_pend(WClocksemaphoreHandle_IMU,BIOS_WAIT_FOREVER);
}
void IMUCalculation()
{
    float accel_max[5], accel_min[5], accel_interpolated[50], tempAcc[50], vmax[2], vmin[2], positionmax[2], positionmin[2];
    int posmax[5], posmin[5];
    int  i;

    if(ismoving)
        movinggain = 1.0f;
    else
        movinggain = 0.1f;

    //Start with x axis
    //copy to temp buffer
    for (i = 0; i < 50; i++)
    {
        tempAcc[i] = IMUfiltered[i].acc[0] * G_earth;
        if (fabs(tempAcc[i]) < 0.09 )
            tempAcc[i] = 0;
    }
    find_max(tempAcc, posmax, accel_max);
    //interpolation and calculation
    Lagrange_interpolation(posmax, accel_max, accel_interpolated);
    envelope_integration(accel_interpolated, &positionmax[0], &vmax[0]);

    find_min(tempAcc, posmin, accel_min);
    //interpolation and calculation
    Lagrange_interpolation(posmin, accel_min, accel_interpolated);
    envelope_integration(accel_interpolated, &positionmin[0], &vmin[0]);
    //bulk_integration(accel_max, accel_min, posmax, posmin, 5, &position[0], &speed[0]);

    for (i = 0; i < 50; i++)
    {
        tempAcc[i] = IMUfiltered[i].acc[1] * G_earth;
        if (fabs(tempAcc[i]) < 0.09 )
            tempAcc[i] = 0;
    }
    find_max(tempAcc, posmax, accel_max);
    //interpolation and calculation
    Lagrange_interpolation(posmax, accel_max, accel_interpolated);
    envelope_integration(accel_interpolated, &positionmax[1], &vmax[1]);

    find_min(tempAcc, posmin, accel_min);
    //interpolation and calculation
    Lagrange_interpolation(posmin, accel_min, accel_interpolated);
    envelope_integration(accel_interpolated, &positionmin[1], &vmin[1]);
    //bulk_integration(accel_max, accel_min, posmax, posmin, 5, &position[1], &speed[1]);

    //Join the value for the interpolation
    position[0] += movinggain * (positionmax[0] + positionmin[0]) * 0.5;
    position[1] += movinggain * (positionmax[1] + positionmin[1]) * 0.5;
    speed[0] = (vmax[0] + vmin[0]) * movinggain * 0.1;
    speed[1] = (vmax[1] + vmin[1]) * movinggain * 0.1;


}
static float angle_average(float ang1, float ang2, uint8_t num1, uint8_t num2)
{
    float ret;
    if (ang1 * ang2 < 0)
    {
        if (ang1 - ang2 > PI)
            ang2 = ang2 + 2 * PI;
        else if (ang2 - ang1 > PI)
            ang1 = ang1 + 2 * PI;
    }
    ret = (ang1 * num1 + ang2 * num2) / (num1 + num2);
    project_rad(&ret);
    return ret;
}
static void project_rad(float *rad)
{
    float temp = *rad;
    temp += 5 * PI;
    unsigned char n;
    n = (unsigned char)(temp / (2 * PI));
    temp -= (2 * n + 1) * PI;
    *rad = temp;
}
