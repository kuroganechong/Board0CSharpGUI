// ------------------------------------------------------ EMPTY ------------------------------------------------ //
// Description: Communication between the bluetooth chip and the main chip
// ----- Header
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <math.h>
#include "Board.h"
#include "ext_flash.h"
#include "IR_Sensor.h"
#include "LevyWalkTask.h"
#include "HumanDetection.h" //Thanh
// ----- Define
#define UART_RECEIVE_LEN (256)
#define SPI_TRANS_LEN     (240)
#define STATEVARIABLESTARTADD 0x1FF000
#define STATEVARIABLESTOPADD  0x1FFFFF
#define STATEVARIABLEOFFSET   0
#define STATEVARIABLESTEP   32
// ---------------------- SEMAPHORE OF EMPTY ------------------------ //
Semaphore_Handle Empty_SemHandle;
Semaphore_Struct Empty_SemStruct;
// ---------------------- VARIABLES TO HANDLE DATA TRANSMISSION ------------------------ //
static SPI_Handle      handle_spi_ble;
static uint8_t         transmitBuffer_spi_ble[SPI_TRANS_LEN];
static uint8_t         transmitBuffer_spi_ble_buff[SPI_TRANS_LEN];
static uint8_t         receiveBuffer_spi_ble[SPI_TRANS_LEN];
static uint8_t         receiveBuffer_spi_ble_cpy[SPI_TRANS_LEN];
static uint16_t        correctedbufferfillidx;
static uint16_t        SPIreceivelength;
static SPI_Transaction Transaction_spi_ble;
static bool            transferOK_ble;
static bool            isbufferempty;
static bool            NewDatacome;
static bool            isTransferdone;
// ---------------------- VARIABLES TO HANDLE DATA LOGGING  ------------------------ //
// HuuDuoc: One Sector is 4K bytes
//          A. Than is writing to each sector. Managing using page will be better but not necessary at the moment
//          Therefore, there will be three images stored at each sector. We have 511 Sectors => 1533 images (512 sectors but the last sector is used for state variables)
//          If the sampling rate of IR camera is 0.5s => 766s => 12.8 minutes
// Data Log Structure
struct datalog {
        uint32_t LogNumber;                 // 4 bytes
        uint32_t LogTime;                   // 4 bytes
        uint8_t  IRpixel[IR_ARRAY_SIZE*3];  // 3072 bytes
        float    FrameNumber[3];            // 12 bytes
        // Total 3092 bytes
}datalog;
static struct datalog Datalogstruct;
extern uint32_t TimeCntMilisecond;
float Flash_FrameNumberArray[3];
float Flash_IR_Image[IR_ARRAY_SIZE*3];
bool  Flash_ShouldWeSave           = false;
bool  Flash_IsFlashBeingWritten    = false;
bool  Flash_IsItTimeToSaveFlash    = false;
bool  Flash_IsFlashWrittingStarted = false; // This variable is controlled by the GUI and for the demonstration (Oct-2020) it is used allong with the navigation
bool  Flash_ShouldWeSave_Previous  = false;
uint8_t Flash_Counter = 0;
#define SAVEDATAKEY    0xA5 // State variables need to store for power up 32 bytes, 1 byte to check the consistency of the data preventing uncompleted data during save
struct statevariable{
    uint8_t CCS811Baseline[2];
    uint8_t Reserved[29];
    uint8_t DataConsistencyCheck;
}statevariable;
static uint32_t Latestlognumber;
static uint32_t freeaddressfordatasaving;
bool isFlashOK;
static struct statevariable savestatevariable;
static struct datalog DatalogstructReadBack;
// ---------------------- VARIABLES FOR STIMULATION  ------------------------ //
extern uint32_t StimulateDuration[NO_CHANNEL_STI];
extern uint32_t StimulatePeriod[NO_CHANNEL_STI];
extern uint32_t ActiveTime1[NO_CHANNEL_STI];
extern uint32_t ZeroTime1[NO_CHANNEL_STI];
extern uint32_t ZeroTime2[NO_CHANNEL_STI];
extern uint16_t ChannelAmplitude[NO_CHANNEL_STI];
extern bool     StimulationStartStop;
extern bool     StimulationTrigger;
extern bool     ChannelActive[NO_CHANNEL_STI];
// ---------------------- VARIABLES FOR AMBIENT AND CO2  ------------------------ //
bool Co2Sensor_onoff;
bool Ambient_onoff;
bool Mic_onoff;
volatile bool isOldBaselineFound;
extern volatile bool BaselineReadytoSave;
extern uint8_t Baselineval[2];
extern uint8_t BaselinevalOld[2];
extern float Ambienttemp;
extern float Humidity;
extern float AirPressure;
uint16_t CO2val;
uint16_t TVOCval;
// ---------------------- VARIABLES FOR IR CAMERA  ------------------------ //
// Variable for IR sensor: IR Image - Variable to ensure only one completed image is sent
bool         IRSensor_onoff;
extern bool  gIRsensorOk;
extern bool  IR_ImageUpdated;
extern float IR_Image[IR_ARRAY_SIZE];
extern float Ambient_Temp;
extern float IR_Image1[IR_ARRAY_SIZE];
extern float Ambient_Temp1;
extern float IR_ImagetoSend[IR_ARRAY_SIZE]; // Variables to make sure one completed image is sent
extern volatile bool IsIRImageCompletelySent;
extern volatile bool  humandetected;
extern float HumanDetection_Score;
bool StreamImage;
extern bool IsOnBoardHumanDetection;
extern uint32_t HuuDuoc_PixelInRange;
extern float HumanDetection_MinOfRange;
extern float HumanDetection_MaxOfRange;
extern float HumanDetection_MinOfPixels;
extern float HumanDetection_MaxOfPixels;
// ---------------------- VARIABLES FOR BATTERY ------------------------ //
extern float BatteryVoltage;
// ---------------------- REQUEST DATA ------------------------ //
uint8_t RequestData;
// ---------------------------------------------- EXTERNAL SEMARPHORE ------------------------------ //
extern Semaphore_Handle Ambient_SemHandle;
extern Semaphore_Handle Analog_SemHandle;
extern Semaphore_Handle SemHandle_IR;
// ----------------------- IMU LONG ------------------- //
extern float quat_float[4];
extern float accel_float[3];
extern float yaw_bias, mag_angle;
extern signed short accel_raw[3];
float accel_check[3];
extern float ypr[3];
extern float mag_cali_hori[6];
extern float speed[3], position[3], p_matrix[3];
extern float speedUpdate[2], positionUpdate[2], p_matrixUpdate[3];
extern bool updatePosition;
extern float movinggain;
uint32_t tempGain;
extern int16_t IMUdataBlock[1792];
extern uint8_t IdxRoundBuffer;
extern bool  IMUready;
extern volatile float omega; // rad/s
extern volatile float absolutespeed; // m/s
// --------------------------- FIRE SPOT DETECTION  ---------------------------- //
extern float FireWatch_Threshold;
extern float FireWatch_Variable;
extern uint8_t FireWatch_Count;
extern bool FireWatch_Detected;
// ---------------------------------------------- NECESSARY FUNCTIONS ------------------------------ //
// Function related to Flash
static bool StatevariableRead(uint8_t * Buff);
static bool StatevariableSave(void);
static void  FindLatestLogNumber(uint32_t *outlognumber, uint32_t* nextfreeaddress);
static void Savecurrentdata(void);
static bool Writedatatomemory(void);
static bool Readdatafrommemory(uint8_t* buff);
static bool Readdatafrommemoryatsector(uint16_t sector, uint8_t* buff);
// Other functions
void Num2textfloat(uint8_t * outbuf, float * inbuf);
uint8_t Num2textbyte(uint8_t x);
float Hex2num_float(uint8_t *val);
float DistanceCalculation(float *A, float *B);
bool CompareFloat(float f1, float f2);

// ---------------------------------------------- SPI FUNCTIONS ------------------------------ //
void SpiCallbackfn_ble(SPI_Handle handle, SPI_Transaction *transaction)
{
    SPIreceivelength = transaction->count;
    // Transfer done
    isTransferdone = true;
    GPIO_write(MSP_EXP432P4011_BLE_EXT, Board_GPIO_LED_ON); // Not ready
    GPIO_toggle(MSP_EXP432P4011_GPIO_LED5);
    Semaphore_post(Empty_SemHandle);
    return;
}
// ------------------------ VARIABLES FOR AUTOMATIC NAVIGATION ---------------- //
// Note: Due to the inherit from LevyWalk, all variables are named started with "LevyWalk"
extern Semaphore_Handle LevyWalk_SemHandle;
extern uint32_t LevyWalk_ControlRate;
extern bool     LevyWalk_TimeForExecute;
extern uint32_t LevyWalk_ControlCount;
extern uint32_t LevyWalk_Turn;
extern uint32_t LevyWalk_TurnPrevious;
extern float LevyWalk_Target[16];
extern float LevyWalk_Target_Current[2];
extern uint32_t LevyWalk_Tagert_Order;
extern volatile float LevyWalk_RobotPos[4];
volatile float        LevyWalk_RobotPos_Sub[6];
extern volatile float LevyWalk_AngleThreshold;
extern volatile float LevyWalk_DistanceThreshold;
extern volatile uint32_t LevyWalk_ReactionTime;
extern volatile uint32_t LevyWalk_ThresholdOfLongStimulus;
extern volatile uint32_t LevyWalk_ThresholdOfLongStimulusForward;
extern volatile uint32_t LevyWalk_ThresholdOfLongStimulusFreeWalk;
extern volatile uint32_t LevyWalk_DurationToCheckSpeed;
extern volatile uint32_t LevyWalk_DurationToCheckSpeed_FreeWalk;
extern volatile uint32_t LevyWalk_DurationToCheckSpeed_Stimulation;
extern volatile float    LevyWalk_ThresholdOfForwardVelocity;
extern volatile float    LevyWalk_ThresholdOfAngularVelocity;
extern volatile float    LevyWalk_TimeStoreToCalculateSpeed;
extern volatile uint32_t LevyWalk_ThresholdOfTimeForwardWhenSpeedIsSmall;
extern volatile uint32_t LevyWalk_ThresholdOfTimeFreeWalkWhenSpeedIsSmall;
extern volatile float    LevyWalk_SpeedArray_X[300];
extern volatile float    LevyWalk_SpeedArray_Y[300];
extern volatile float    LevyWalk_SpeedArray_Z[300];
extern volatile float    LevyWalk_SpeedArray_XHead[300];
extern volatile float    LevyWalk_SpeedArray_YHead[300];
extern volatile float    LevyWalk_SpeedArray_ZHead[300];
extern volatile uint32_t LevyWalk_SpeedArray_T[300];
extern volatile uint32_t LevyWalk_SpeedCount;
extern volatile bool     LevyWalk_SpeedFlag_Linear;
extern volatile bool     LevyWalk_SpeedFlag_Angular;
extern volatile float    LevyWalk_ForwardVelocity;
extern volatile float    LevyWalk_AngularVelocity;
extern volatile float    LevyWalk_ForwardVelocity_Vicon;
extern volatile float    LevyWalk_AngularVelocity_Vicon;
extern volatile float    LevyWalk_ForwardVelocity_IMU;
extern volatile float    LevyWalk_AngularVelocity_IMU;
extern volatile bool     LevyWalk_UseIMU_LinearSpeed;
extern volatile bool     LevyWalk_UseIMU_AngularSpeed;
extern uint32_t          LevyWalk_TemporalVariableToTestSpeed;
extern volatile uint32_t LevyWalk_AngularSpeedMethod;
extern volatile bool     LevyWalk_UseEscapeMode;
extern volatile float LevyWalk_TargetToTest[2];
extern volatile bool  LevyWalk_IsReached;
extern volatile bool  LevyWalk_IsTheRoachConfined;
uint8_t LevyWalk_SubVariable1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t LevyWalk_SubVariable2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
float   LevyWalk_SubVariable3    = 0.0;
float   LevyWalk_SubVariable4    = 0.0;
float  *LevyWalk_SubVariable_Pointer;
float  *LevyWalk_SubVariable_Pointer2;
uint32_t LevyWalk_SubVariable5   = 0;
uint32_t LevyWalk_SubVariable6   = 0;
// Variables for stimulation
extern volatile bool     LevyWalk_LeftChannelActive[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_LeftDuration[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_LeftPeriod[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_LeftActiveTime1[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_LeftZeroTime1[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_LeftZeroTime2[NO_CHANNEL_STI];
extern volatile uint16_t LevyWalk_LeftChannelAmplitude[NO_CHANNEL_STI];
// Variables for stimulation
extern volatile bool     LevyWalk_RightChannelActive[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_RightDuration[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_RightPeriod[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_RightActiveTime1[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_RightZeroTime1[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_RightZeroTime2[NO_CHANNEL_STI];
extern volatile uint16_t LevyWalk_RightChannelAmplitude[NO_CHANNEL_STI];
// Variables for stimulation
extern volatile bool     LevyWalk_ForwardChannelActive[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_ForwardDuration[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_ForwardPeriod[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_ForwardActiveTime1[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_ForwardZeroTime1[NO_CHANNEL_STI];
extern volatile uint32_t LevyWalk_ForwardZeroTime2[NO_CHANNEL_STI];
extern volatile uint16_t LevyWalk_ForwardChannelAmplitude[NO_CHANNEL_STI];
// Variable for handler the reduction of stimulation
extern volatile bool     LevyWalk_EnableTheFreeWalkingAfterStimulation;
extern volatile uint32_t LevyWalk_ThresholdForFreeWalkAfterSteering;
extern volatile uint32_t LevyWalk_ThresholdofFinalPartForLongStimulus;
// Variable to reset navigation
extern bool LevyWalk_IsLongStimulusHandleStarted; // The variable to indicate that long stimulus is being handled
extern bool LevyWalk_IsLongStimulusBeingChecked;  // The variable to indicate that long stimulus is being monitored
extern bool LevyWalk_IsNavigated;                 // Enable navigation process
extern bool LevyWalk_IsForwardTriggeredAlready;   // The variable to indicate that forward stimulation has been already started
extern bool LevyWalk_ShouldCheckTheForwardSpeed;
extern uint32_t LevyWalk_TimeafterForwardStimulus;
extern uint32_t LevyWalk_TimeofStimulusForSteering;
extern uint32_t LevyWalk_TimeafterLongStimulus;
extern uint32_t LevyWalk_TimeafterAngleSmallerThanThreshold;
extern uint32_t LevyWalk_TimeCounterForFreeWalkAfterSteering;
extern bool LevyWalk_StartCoutingTimeForFreeWalkAfterSteering;
// Variable to count the number of zero velocity
extern uint32_t LevyWalk_NumberAngularSpeed;
extern uint32_t LevyWalk_NumberLinearSpeed;
extern float LevyWalk_Target_Current[2];
// --------------------------- Other variables
uint16_t RequestDataSendBack = 0;
float    FrameNumberSendBack = 0.0;
// ------------------------------- MAIN THREAD ----------------------------------- //
void *mainThread(void *arg0)
{
    // ---------------------- Necessary variables
    uint32_t i,jj;

    // ---------------------- Variables for sending and receiving
    uint16_t FillIndex;
    uint8_t CMDcnt, CMDcntold;
    bool isspiframestarted;
    uint8_t * pbuffertransmit;
    uint8_t * pbufferreceive;
    uint32_t SendCMDcnt, SendCMDcnt_sub;
    uint16_t IRpartcnt;
    uint8_t  pixeltempu8;
    float    pixeltempf;
    SendCMDcnt = 1;

    // ------------------- Variables related to Flash saving
    int32_t CurrentFlashByte, CurrentFlashByteOld, CurrentFrameNo, CurrentFlashByteoffset, CurrentFlashByteoffsetold;
    uint8_t *sendbyte;
    uint32_t numberbytealreadysent;
    bool IRSensor_onoff_old  = false;
    bool Co2Sensor_onoff_old = false;
    IRSensor_onoff = true; // Turn on IR sensor
    Co2Sensor_onoff = false; // Although Ambient code is already disabled, this variable is kept here as I am still blur about the Baseline saving that related to Flash

    // -------------------- Variables for forward velocity calculation
    // Note: These variables are used to skip the missing marker
    float RobotHead[2] = {0.0, 0.0};
    float RobotTail[2] = {0.0, 0.0};
    float MarkerTest   = 0.0;

    // --------------------- Semaphore Creation
    Semaphore_Params semparams_Empty;
    Semaphore_Params_init(&semparams_Empty);
    semparams_Empty.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&Empty_SemStruct,0,  &semparams_Empty );
    Empty_SemHandle = Semaphore_handle(&Empty_SemStruct);

    // ---------------------- Configure the LED pin
    GPIO_setConfig(MSP_EXP432P4011_GPIO_LED5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(MSP_EXP432P4011_BLE_EXT, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);
    GPIO_write(MSP_EXP432P4011_GPIO_LED5, Board_GPIO_LED_ON);

    //---------------------- SPI to communicate with BLE
    SPI_Params      spiParams_ble;
    SPI_Params_init(&spiParams_ble);  // Initialize SPI parameters
    spiParams_ble.dataSize = 8;       // 8-bit data size
    spiParams_ble.bitRate = 4000000;
    spiParams_ble.mode = SPI_SLAVE;
    spiParams_ble.transferMode = SPI_MODE_CALLBACK;
    spiParams_ble.transferCallbackFxn = SpiCallbackfn_ble;
    spiParams_ble.frameFormat = SPI_POL0_PHA1;
    spiParams_ble.transferTimeout = 2000;
    handle_spi_ble = SPI_open(MSP_EXP432P4011_SPIA2, &spiParams_ble);
    if (handle_spi_ble == NULL)
    {
        while(1);
    }
    Transaction_spi_ble.count = SPI_TRANS_LEN;
    Transaction_spi_ble.rxBuf = receiveBuffer_spi_ble;
    Transaction_spi_ble.txBuf = transmitBuffer_spi_ble;
    transferOK_ble = SPI_transfer(handle_spi_ble, &Transaction_spi_ble);
    GPIO_write(MSP_EXP432P4011_BLE_EXT, Board_GPIO_LED_OFF); // ready
    isTransferdone = false;
    isbufferempty = true;
    SPIreceivelength = 0;

    // ----------------------- Prepare the Flash Memory
    savestatevariable.DataConsistencyCheck = SAVEDATAKEY;
    for (i = 0; i < 29; i++)
    {
        savestatevariable.Reserved[i] = 0xFF;
    }
    Latestlognumber = 0;
    if (!extFlashTest())
    {
        isFlashOK = false;
        GPIO_write(MSP_EXP432P4011_GPIO_LED5, Board_GPIO_LED_ON);
        GPIO_write(MSP_EXP432P4011_GPIO_LED6, Board_GPIO_LED_OFF);
        IRSensor_onoff = false;
        Co2Sensor_onoff = false;
        Ambient_onoff = false;
        // This loop is to stop the project to run if we can not open Flash
        while(1)
        {
            GPIO_toggle(MSP_EXP432P4011_GPIO_LED5);
            GPIO_toggle(MSP_EXP432P4011_GPIO_LED6);
            sleep(1);
        }
    }
    else
    {
        isFlashOK = true;
        extFlashOpen();
        isOldBaselineFound = StatevariableRead((uint8_t *) &savestatevariable); // Read baseline
        if (isOldBaselineFound)
        {
            if(savestatevariable.DataConsistencyCheck == SAVEDATAKEY)
            {
                memcpy(BaselinevalOld,savestatevariable.CCS811Baseline, 2);
            }
            else
            {
                isOldBaselineFound = false;
            }
        }
        FindLatestLogNumber(&Latestlognumber,&freeaddressfordatasaving); // Read lasted log number
    }
    CurrentFlashByte       = -1; // max number
    CurrentFlashByteOld    = 0;
    CurrentFlashByteoffset = 0;
    CurrentFrameNo = 0;
    // ----------------------------------- Set stimulation parameters
    for (i = 0; i<NO_CHANNEL_STI; i++ )
    {
        StimulateDuration[i]  = 10000;
        StimulatePeriod[i] = 50;
        ActiveTime1[i] = 10;
        ZeroTime1[i] = 10;
        ZeroTime2[i] = 30;
        ChannelAmplitude[i] = 500 + 100*i;
        ChannelActive[i] = true;
    }

    // ----------------------------------- Turn on sensors
    IRSensor_onoff   = true;
    Co2Sensor_onoff  = true;
    Ambient_onoff    = true;

    SendCMDcnt = 1;

    while (1) {
        Semaphore_pend(Empty_SemHandle, BIOS_WAIT_FOREVER);
        // -------------------------------------------------- HANLE THE SPI COMMUNICATION ------------------------------- //
        if (isTransferdone)
        {
            isTransferdone = false;
            // Switch receive buffer
            if(Transaction_spi_ble.rxBuf == receiveBuffer_spi_ble)
            {
                Transaction_spi_ble.rxBuf = receiveBuffer_spi_ble_cpy;
                // Preparing transmitBuffer_spi_ble
                pbufferreceive = receiveBuffer_spi_ble;
            }
            else
            {
                Transaction_spi_ble.rxBuf = receiveBuffer_spi_ble;
                // Preparing transmitBuffer_spi_ble_buff
                pbufferreceive = receiveBuffer_spi_ble_cpy;
            }

            if(pbufferreceive[0] != 'S') // Reset SPI transfer if wrong data is received
            {// Cancel the SPI causes hard fault, no solution
                // Data correction
                if(SPIreceivelength > SPI_TRANS_LEN)
                {
                    SPIreceivelength = SPI_TRANS_LEN;
                }
                isspiframestarted = false;
                for(i = 0; i< SPIreceivelength; i++)
                {
                    if(pbufferreceive[i] == 'S')
                    {
                        correctedbufferfillidx = 0;
                        isspiframestarted = true;
                    }
                    if(isspiframestarted)
                    {
                        pbufferreceive[correctedbufferfillidx++] = pbufferreceive[i];
                    }
                }
            }
            NewDatacome = true;
            if(SPIreceivelength > 0)
            {
                // Switch transmit buffer
                if(Transaction_spi_ble.txBuf == transmitBuffer_spi_ble)
                {
                    Transaction_spi_ble.txBuf = transmitBuffer_spi_ble_buff;
                    // Preparing transmitBuffer_spi_ble
                    pbuffertransmit = transmitBuffer_spi_ble;
                }
                else
                {
                    Transaction_spi_ble.txBuf = transmitBuffer_spi_ble;
                    // Preparing transmitBuffer_spi_ble_buff
                    pbuffertransmit = transmitBuffer_spi_ble_buff;
                }
                isbufferempty = true;
            }
            // Copy new data to transmit buffer
            transferOK_ble = SPI_transfer(handle_spi_ble, &Transaction_spi_ble);
            GPIO_write(MSP_EXP432P4011_BLE_EXT, Board_GPIO_LED_OFF); // ready
        }

        // ---------------- PROCESSING THE NEW DATA RECEIVED FROM THE COMMUNICATION -----------------------------//
        if(NewDatacome)
        {
            // Check data to make sure the received data is correct, if not reset the SPI data transfer.
            NewDatacome = false;
            if(pbufferreceive[0] == 'S')
            {
                // Update new control value
                for (i=0; i<SPI_TRANS_LEN; i++)
                {
                    pbufferreceive[i] = (pbufferreceive[i] >= 65 ? (uint8_t)(pbufferreceive[i] - 55) : (uint8_t)(pbufferreceive[i] - 48));
                }
                // Command number
                CMDcntold = CMDcnt;
                CMDcnt = (pbufferreceive[1]<<4)|pbufferreceive[2];
                if(CMDcnt != CMDcntold)
                {
                    // Checking for requested data
                    RequestData = (((uint8_t)pbufferreceive[188])<<4)  | (((uint8_t)pbufferreceive[189]));
                    RequestDataSendBack = (uint16_t)RequestData;
                    switch(RequestData)
                    {
                    case 0:
                        // CASE 0: This case is used to manually on/off/adjust stimulation
                        FillIndex = 2;
                        for (jj = 0; jj<4; jj++)
                        {
                            ChannelActive[jj] = pbufferreceive[FillIndex+1];

                            StimulateDuration[jj] = (((uint32_t)pbufferreceive[FillIndex+2])<<28) | (((uint32_t)pbufferreceive[FillIndex+3])<<24) |
                                                    (((uint32_t)pbufferreceive[FillIndex+4])<<20) | (((uint32_t)pbufferreceive[FillIndex+5])<<16)
                                                  | (((uint32_t)pbufferreceive[FillIndex+6])<<12) | (((uint32_t)pbufferreceive[FillIndex+7])<<8)  |
                                                    (((uint32_t)pbufferreceive[FillIndex+8])<<4)  | (((uint32_t)pbufferreceive[FillIndex+9]));

                            StimulatePeriod[jj] =  (((uint32_t)pbufferreceive[FillIndex+10])<<28) | (((uint32_t)pbufferreceive[FillIndex+11])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+12])<<20) | (((uint32_t)pbufferreceive[FillIndex+13])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+14])<<12) | (((uint32_t)pbufferreceive[FillIndex+15])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+16])<<4)  | (((uint32_t)pbufferreceive[FillIndex+17]));

                            ActiveTime1[jj]     =  (((uint32_t)pbufferreceive[FillIndex+18])<<28) | (((uint32_t)pbufferreceive[FillIndex+19])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+20])<<20) | (((uint32_t)pbufferreceive[FillIndex+21])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+22])<<12) | (((uint32_t)pbufferreceive[FillIndex+23])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+24])<<4)  | (((uint32_t)pbufferreceive[FillIndex+25]));

                            ZeroTime1[jj]    =  (((uint32_t)pbufferreceive[FillIndex+26])<<28) | (((uint32_t)pbufferreceive[FillIndex+27])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+28])<<20) | (((uint32_t)pbufferreceive[FillIndex+29])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+30])<<12) | (((uint32_t)pbufferreceive[FillIndex+31])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+32])<<4)  | (((uint32_t)pbufferreceive[FillIndex+33]));

                            ZeroTime2[jj]    =  (((uint32_t)pbufferreceive[FillIndex+34])<<28) | (((uint32_t)pbufferreceive[FillIndex+35])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+36])<<20) | (((uint32_t)pbufferreceive[FillIndex+37])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+38])<<12) | (((uint32_t)pbufferreceive[FillIndex+39])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+40])<<4)  | (((uint32_t)pbufferreceive[FillIndex+41]));

                            ChannelAmplitude[jj] =(((uint32_t)pbufferreceive[FillIndex+42])<<12) | (((uint32_t)pbufferreceive[FillIndex+43])<<8)  |
                                                (((uint32_t)pbufferreceive[FillIndex+44])<<4)  | (((uint32_t)pbufferreceive[FillIndex+45]));


                            FillIndex += 45;
                        }
                        StimulationTrigger   = true;
                        StimulationStartStop = pbufferreceive[183];

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x50:
                        // CASE 50: This case is used to update navigational parameters
                        FillIndex = 3;
                        for (i = 0; i <= 17; i++)
                        {
                            LevyWalk_SubVariable3 = 0;
                            LevyWalk_SubVariable3 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1])<<24) |
                                    (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<16)
                                    | (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<8)  |
                                    (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7]));
                            switch (i)
                            {
                                case 0:
                                    LevyWalk_AngleThreshold    = ((float)LevyWalk_SubVariable3);
                                    break;
                                case 1:
                                    LevyWalk_DistanceThreshold = ((float)LevyWalk_SubVariable3)*10.0; // Convert to mm
                                    break;
                                case 2:
                                    LevyWalk_ThresholdOfTimeForwardWhenSpeedIsSmall  = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 3:
                                    LevyWalk_ThresholdOfTimeFreeWalkWhenSpeedIsSmall = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 4:
                                    LevyWalk_ThresholdOfLongStimulus         = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 5:
                                    LevyWalk_ThresholdOfLongStimulusForward  = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 6:
                                    LevyWalk_ThresholdOfLongStimulusFreeWalk = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 7:
                                    LevyWalk_ControlRate = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 8:
                                    LevyWalk_DurationToCheckSpeed      = (uint32_t)LevyWalk_SubVariable3;
                                    LevyWalk_DurationToCheckSpeed_FreeWalk    = LevyWalk_DurationToCheckSpeed;
                                    LevyWalk_DurationToCheckSpeed_Stimulation = LevyWalk_DurationToCheckSpeed;
                                    break;
                                case 9:
                                    LevyWalk_ThresholdOfForwardVelocity = ((float)LevyWalk_SubVariable3)/100.0*10.0; // Convert to mm/s
                                    break;
                                case 10:
                                    LevyWalk_TimeStoreToCalculateSpeed  = ((float)LevyWalk_SubVariable3)/100.0;
                                    break;
                                case 11:
                                    if (LevyWalk_SubVariable3 == 1)
                                     {
                                        LevyWalk_EnableTheFreeWalkingAfterStimulation = false;
                                     }
                                     else
                                     {
                                         LevyWalk_EnableTheFreeWalkingAfterStimulation = true;
                                     }
                                     break;
                                case 12:
                                    LevyWalk_ThresholdForFreeWalkAfterSteering = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 13:
                                    LevyWalk_ThresholdofFinalPartForLongStimulus = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 14:
                                    LevyWalk_ThresholdOfAngularVelocity = ((float)LevyWalk_SubVariable3)/100.0;
                                    break;
                                case 15:
                                    if (LevyWalk_SubVariable3 == 1)
                                     {
                                        LevyWalk_UseEscapeMode = false;
                                     }
                                     else
                                     {
                                         LevyWalk_UseEscapeMode = true;
                                     }
                                    break;
                                case 16:
                                    LevyWalk_ReactionTime  = (uint32_t)LevyWalk_SubVariable3;
                                    break;
                                case 17:
                                    if (LevyWalk_SubVariable3 == 1)
                                     {
                                        LevyWalk_AngularSpeedMethod = 1;
                                     }
                                     else
                                     {
                                         LevyWalk_AngularSpeedMethod = 2;
                                     }
                                    break;
                            }
                        }
                        LevyWalk_UseIMU_LinearSpeed  = pbufferreceive[190];
                        LevyWalk_UseIMU_AngularSpeed = pbufferreceive[191];
                        // This line is input to re-use the structure of long-stimulus checking to check the angular speed
                        // Once the stimulation is on, the speed will be checked at every LevyWalk_DurationToCheckSpeed_Stimulation
                        // To do this, we take advantage of the old program in which the navigational program takes action when the stimulus lasts longer than
                        // LevyWalk_ThresholdOfLongStimulus
                        LevyWalk_ThresholdOfLongStimulus = LevyWalk_DurationToCheckSpeed_Stimulation + LevyWalk_ReactionTime;
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x51:
                        // CASE 51: This case is used to update targets
                        FillIndex = 3;
                        for (i = 0; i <= 15; i++)
                        {
                            LevyWalk_SubVariable6 = 0;
                            LevyWalk_SubVariable6 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                    (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                    | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                    (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1]));

                            // LevyWalk_Target[i] = ((float)LevyWalk_SubVariable3)*10; // Convert to mm
                            LevyWalk_SubVariable_Pointer2 = &LevyWalk_SubVariable6;
                            LevyWalk_Target[i]  = *LevyWalk_SubVariable_Pointer2;
                            LevyWalk_Target[i]  = LevyWalk_Target[i]*10.0;
                        }
                        LevyWalk_Target_Current[0] = LevyWalk_Target[0];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[1];
                        LevyWalk_Tagert_Order = 1;
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x80:
                        // CASE 80: This case is used to indicate which sensor data will be streamed to the user GUI
                        IRSensor_onoff  = pbufferreceive[184];
                        Co2Sensor_onoff = pbufferreceive[185];
                        Ambient_onoff   = pbufferreceive[187];

                        // Long's IMU Gain
                        tempGain = (((uint32_t)pbufferreceive[190])<<16) | (((uint32_t)pbufferreceive[191])<<8) |
                                   (((uint32_t)pbufferreceive[192])<<4)  | (((uint32_t)pbufferreceive[193]));
                        movinggain = ((float)(tempGain))/100;

                        // Should we stream image and should we proceed with onboard human detection
                        StreamImage = pbufferreceive[194];
                        IsOnBoardHumanDetection = pbufferreceive[195];

                        // These are variables used for the human detection
                        FillIndex = 196;
                        i = 0;
                        LevyWalk_SubVariable6 = 0;
                        LevyWalk_SubVariable6 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1]));
                        LevyWalk_SubVariable_Pointer2 = &LevyWalk_SubVariable6;
                        HumanDetection_MinOfRange = *LevyWalk_SubVariable_Pointer2;

                        FillIndex = 204;
                        LevyWalk_SubVariable6 = 0;
                        LevyWalk_SubVariable6 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1]));
                        LevyWalk_SubVariable_Pointer2 = &LevyWalk_SubVariable6;
                        HumanDetection_MaxOfRange  = *LevyWalk_SubVariable_Pointer2;

                        FillIndex = 212;
                        LevyWalk_SubVariable6 = 0;
                        LevyWalk_SubVariable6 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1]));
                        LevyWalk_SubVariable_Pointer2 = &LevyWalk_SubVariable6;
                        HumanDetection_MinOfPixels  = *LevyWalk_SubVariable_Pointer2;

                        FillIndex = 220;
                        LevyWalk_SubVariable6 = 0;
                        LevyWalk_SubVariable6 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1]));
                        LevyWalk_SubVariable_Pointer2 = &LevyWalk_SubVariable6;
                        HumanDetection_MaxOfPixels  = *LevyWalk_SubVariable_Pointer2;

                        FillIndex = 228;
                        LevyWalk_SubVariable6 = 0;
                        LevyWalk_SubVariable6 = (((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1]));
                        LevyWalk_SubVariable_Pointer2 = &LevyWalk_SubVariable6;
                        FireWatch_Threshold  = *LevyWalk_SubVariable_Pointer2;


                        // In default, the human detection on board will be prohibited in all cases because it takes a lot of time to process
                        // Reset all the navigational variable to prepare for the next navigation
                        LevyWalk_TurnPrevious                = 0;
                        LevyWalk_Turn                        = 0;     // Stop the navigation
                        LevyWalk_IsLongStimulusHandleStarted = false; // The variable to indicate that long stimulus is being handled
                        LevyWalk_IsLongStimulusBeingChecked  = false; // The variable to indicate that long stimulus is being monitored
                        LevyWalk_IsNavigated                 = true;  // Enable navigation process
                        LevyWalk_IsForwardTriggeredAlready   = false; // The variable to indicate that forward stimulation has been already started
                        LevyWalk_ShouldCheckTheForwardSpeed  = false;
                        LevyWalk_TimeafterForwardStimulus    = 0;
                        LevyWalk_TimeofStimulusForSteering   = 0;
                        LevyWalk_TimeafterLongStimulus       = 0;
                        LevyWalk_TimeafterAngleSmallerThanThreshold       = 0;
                        LevyWalk_TimeCounterForFreeWalkAfterSteering      = 0;
                        LevyWalk_StartCoutingTimeForFreeWalkAfterSteering = false;
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x40: // ----------------------------------- AUTOMATIC NAVIGATION --------------------------------------- //
                        // CASE 40: This case is used to update the cockroach's position recorded from Vicon and allow the automatic navigation to happen
                        //          The sampling rate to the navigation is depended on the setup on the GUI
                        // Note: - In this program, there is only one cockroach being navigated at a time.
                        //       - The cockroach position starts from byte 203 (C)
                        // Enale or Disable Flash
                        Flash_IsFlashWrittingStarted = pbufferreceive[190];
                        LevyWalk_IsTheRoachConfined  = pbufferreceive[191];
                        if (Flash_IsFlashWrittingStarted == true)
                        {
                            if (Flash_ShouldWeSave_Previous == false)
                            {
                                Flash_ShouldWeSave = true;
                                Flash_ShouldWeSave_Previous = true;
                                Flash_IsFlashBeingWritten = false;
                                Flash_IsItTimeToSaveFlash = false;
                                Flash_Counter = 0;
                            }
                        }
                        else
                        {
                            Flash_ShouldWeSave = false;
                            Flash_ShouldWeSave_Previous = false;
                            Flash_IsFlashBeingWritten = false;
                            Flash_IsItTimeToSaveFlash = false;
                        }
                        // Locational Data Reading
                        FillIndex = 11;
                        for (i = 0; i <= 5; i++)
                        {
                            LevyWalk_SubVariable5 = 0.0;
                            LevyWalk_SubVariable5 = ((((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1])));
                            LevyWalk_SubVariable_Pointer = &LevyWalk_SubVariable5;
                            LevyWalk_RobotPos_Sub[i]  = *LevyWalk_SubVariable_Pointer;
                        }
                        // Input the roach's position into three arrays of speed for the forward speed calculation
                        LevyWalk_RobotPos[0] = LevyWalk_RobotPos_Sub[0];
                        LevyWalk_RobotPos[1] = LevyWalk_RobotPos_Sub[1];
                        LevyWalk_RobotPos[2] = LevyWalk_RobotPos_Sub[3];
                        LevyWalk_RobotPos[3] = LevyWalk_RobotPos_Sub[4];
                        RobotHead[0] = LevyWalk_RobotPos[0]; // X Position
                        RobotHead[1] = LevyWalk_RobotPos[1]; // Y Position
                        RobotTail[0] = LevyWalk_RobotPos[2]; // X Position
                        RobotTail[1] = LevyWalk_RobotPos[3]; // Y Position
                        MarkerTest = DistanceCalculation(RobotHead, RobotTail);
                        if (CompareFloat(MarkerTest, 0.0) == false)
                        {
                            if (LevyWalk_SpeedCount > 299)
                            {
                                LevyWalk_SpeedCount = 0;
                            }
                            LevyWalk_SpeedArray_XHead[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[0];
                            LevyWalk_SpeedArray_YHead[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[1];
                            LevyWalk_SpeedArray_ZHead[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[2];
                            LevyWalk_SpeedArray_X[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[3];
                            LevyWalk_SpeedArray_Y[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[4];
                            LevyWalk_SpeedArray_Z[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[5];
                            FillIndex = 3;
                            LevyWalk_SpeedArray_T[LevyWalk_SpeedCount] =  (((uint32_t)pbufferreceive[FillIndex+0])<<28) | (((uint32_t)pbufferreceive[FillIndex+1])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+2])<<20) | (((uint32_t)pbufferreceive[FillIndex+3])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+4])<<12) | (((uint32_t)pbufferreceive[FillIndex+5])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+6])<<4)  | (((uint32_t)pbufferreceive[FillIndex+7]));
                            LevyWalk_SpeedCount++;
                        }
                        FrameNumberSendBack = (float)((((uint32_t)pbufferreceive[FillIndex+0])<<28) | (((uint32_t)pbufferreceive[FillIndex+1])<<24) |
                                (((uint32_t)pbufferreceive[FillIndex+2])<<20) | (((uint32_t)pbufferreceive[FillIndex+3])<<16)
                              | (((uint32_t)pbufferreceive[FillIndex+4])<<12) | (((uint32_t)pbufferreceive[FillIndex+5])<<8)  |
                                (((uint32_t)pbufferreceive[FillIndex+6])<<4)  | (((uint32_t)pbufferreceive[FillIndex+7])));
                        // Call semaphore of LevyWalk every pre-defined interval
                        if (LevyWalk_TimeForExecute)
                        {
                            Semaphore_post(LevyWalk_SemHandle);
                        }
                        break;
                    case 0x41: // ----------------------------------- AUTOMATIC NAVIGATION --------------------------------------- //
                        // CASE 41: This case is used to prepare left stimulation parameter for the cockroach
                        FillIndex = 2;
                        for (jj = 0; jj<4; jj++)
                        {
                            LevyWalk_LeftChannelActive[jj] = pbufferreceive[FillIndex+1];
                            LevyWalk_LeftDuration[jj] = (((uint32_t)pbufferreceive[FillIndex+2])<<28) | (((uint32_t)pbufferreceive[FillIndex+3])<<24) |
                                                    (((uint32_t)pbufferreceive[FillIndex+4])<<20) | (((uint32_t)pbufferreceive[FillIndex+5])<<16)
                                                  | (((uint32_t)pbufferreceive[FillIndex+6])<<12) | (((uint32_t)pbufferreceive[FillIndex+7])<<8)  |
                                                    (((uint32_t)pbufferreceive[FillIndex+8])<<4)  | (((uint32_t)pbufferreceive[FillIndex+9]));

                            LevyWalk_LeftPeriod[jj] =  (((uint32_t)pbufferreceive[FillIndex+10])<<28) | (((uint32_t)pbufferreceive[FillIndex+11])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+12])<<20) | (((uint32_t)pbufferreceive[FillIndex+13])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+14])<<12) | (((uint32_t)pbufferreceive[FillIndex+15])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+16])<<4)  | (((uint32_t)pbufferreceive[FillIndex+17]));

                            LevyWalk_LeftActiveTime1[jj] =  (((uint32_t)pbufferreceive[FillIndex+18])<<28) | (((uint32_t)pbufferreceive[FillIndex+19])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+20])<<20) | (((uint32_t)pbufferreceive[FillIndex+21])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+22])<<12) | (((uint32_t)pbufferreceive[FillIndex+23])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+24])<<4)  | (((uint32_t)pbufferreceive[FillIndex+25]));

                            LevyWalk_LeftZeroTime1[jj] =  (((uint32_t)pbufferreceive[FillIndex+26])<<28) | (((uint32_t)pbufferreceive[FillIndex+27])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+28])<<20) | (((uint32_t)pbufferreceive[FillIndex+29])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+30])<<12) | (((uint32_t)pbufferreceive[FillIndex+31])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+32])<<4)  | (((uint32_t)pbufferreceive[FillIndex+33]));

                            LevyWalk_LeftZeroTime2[jj] =  (((uint32_t)pbufferreceive[FillIndex+34])<<28) | (((uint32_t)pbufferreceive[FillIndex+35])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+36])<<20) | (((uint32_t)pbufferreceive[FillIndex+37])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+38])<<12) | (((uint32_t)pbufferreceive[FillIndex+39])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+40])<<4)  | (((uint32_t)pbufferreceive[FillIndex+41]));
                            LevyWalk_LeftChannelAmplitude[jj] =(((uint32_t)pbufferreceive[FillIndex+42])<<12) | (((uint32_t)pbufferreceive[FillIndex+43])<<8)  |
                                                (((uint32_t)pbufferreceive[FillIndex+44])<<4)  | (((uint32_t)pbufferreceive[FillIndex+45]));

                            FillIndex += 45;
                        }
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x42: // ----------------------------------- AUTOMATIC NAVIGATION --------------------------------------- //
                        // CASE 42: This case is used to prepare right stimulation parameter for the cockroach
                        FillIndex = 2;
                        for (jj = 0; jj<4; jj++)
                        {
                            LevyWalk_RightChannelActive[jj] = pbufferreceive[FillIndex+1];
                            LevyWalk_RightDuration[jj] = (((uint32_t)pbufferreceive[FillIndex+2])<<28) | (((uint32_t)pbufferreceive[FillIndex+3])<<24) |
                                                    (((uint32_t)pbufferreceive[FillIndex+4])<<20) | (((uint32_t)pbufferreceive[FillIndex+5])<<16)
                                                  | (((uint32_t)pbufferreceive[FillIndex+6])<<12) | (((uint32_t)pbufferreceive[FillIndex+7])<<8)  |
                                                    (((uint32_t)pbufferreceive[FillIndex+8])<<4)  | (((uint32_t)pbufferreceive[FillIndex+9]));

                            LevyWalk_RightPeriod[jj] =  (((uint32_t)pbufferreceive[FillIndex+10])<<28) | (((uint32_t)pbufferreceive[FillIndex+11])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+12])<<20) | (((uint32_t)pbufferreceive[FillIndex+13])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+14])<<12) | (((uint32_t)pbufferreceive[FillIndex+15])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+16])<<4)  | (((uint32_t)pbufferreceive[FillIndex+17]));

                            LevyWalk_RightActiveTime1[jj] =  (((uint32_t)pbufferreceive[FillIndex+18])<<28) | (((uint32_t)pbufferreceive[FillIndex+19])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+20])<<20) | (((uint32_t)pbufferreceive[FillIndex+21])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+22])<<12) | (((uint32_t)pbufferreceive[FillIndex+23])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+24])<<4)  | (((uint32_t)pbufferreceive[FillIndex+25]));

                            LevyWalk_RightZeroTime1[jj] =  (((uint32_t)pbufferreceive[FillIndex+26])<<28) | (((uint32_t)pbufferreceive[FillIndex+27])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+28])<<20) | (((uint32_t)pbufferreceive[FillIndex+29])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+30])<<12) | (((uint32_t)pbufferreceive[FillIndex+31])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+32])<<4)  | (((uint32_t)pbufferreceive[FillIndex+33]));

                            LevyWalk_RightZeroTime2[jj] =  (((uint32_t)pbufferreceive[FillIndex+34])<<28) | (((uint32_t)pbufferreceive[FillIndex+35])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+36])<<20) | (((uint32_t)pbufferreceive[FillIndex+37])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+38])<<12) | (((uint32_t)pbufferreceive[FillIndex+39])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+40])<<4)  | (((uint32_t)pbufferreceive[FillIndex+41]));
                            LevyWalk_RightChannelAmplitude[jj] =(((uint32_t)pbufferreceive[FillIndex+42])<<12) | (((uint32_t)pbufferreceive[FillIndex+43])<<8)  |
                                                (((uint32_t)pbufferreceive[FillIndex+44])<<4)  | (((uint32_t)pbufferreceive[FillIndex+45]));

                            FillIndex += 45;
                        }
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x43:  // ----------------------------------- AUTOMATIC NAVIGATION --------------------------------------- //
                        // CASE 43: This case is used to prepare forward stimulation parameter for the cockroach
                        FillIndex = 2;
                        for (jj = 0; jj<4; jj++)
                        {

                            LevyWalk_ForwardChannelActive[jj] = pbufferreceive[FillIndex+1];
                            LevyWalk_ForwardDuration[jj] = (((uint32_t)pbufferreceive[FillIndex+2])<<28) | (((uint32_t)pbufferreceive[FillIndex+3])<<24) |
                                                    (((uint32_t)pbufferreceive[FillIndex+4])<<20) | (((uint32_t)pbufferreceive[FillIndex+5])<<16)
                                                  | (((uint32_t)pbufferreceive[FillIndex+6])<<12) | (((uint32_t)pbufferreceive[FillIndex+7])<<8)  |
                                                    (((uint32_t)pbufferreceive[FillIndex+8])<<4)  | (((uint32_t)pbufferreceive[FillIndex+9]));

                            LevyWalk_ForwardPeriod[jj] =  (((uint32_t)pbufferreceive[FillIndex+10])<<28) | (((uint32_t)pbufferreceive[FillIndex+11])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+12])<<20) | (((uint32_t)pbufferreceive[FillIndex+13])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+14])<<12) | (((uint32_t)pbufferreceive[FillIndex+15])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+16])<<4)  | (((uint32_t)pbufferreceive[FillIndex+17]));

                            LevyWalk_ForwardActiveTime1[jj]     =  (((uint32_t)pbufferreceive[FillIndex+18])<<28) | (((uint32_t)pbufferreceive[FillIndex+19])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+20])<<20) | (((uint32_t)pbufferreceive[FillIndex+21])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+22])<<12) | (((uint32_t)pbufferreceive[FillIndex+23])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+24])<<4)  | (((uint32_t)pbufferreceive[FillIndex+25]));

                            LevyWalk_ForwardZeroTime1[jj]    =  (((uint32_t)pbufferreceive[FillIndex+26])<<28) | (((uint32_t)pbufferreceive[FillIndex+27])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+28])<<20) | (((uint32_t)pbufferreceive[FillIndex+29])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+30])<<12) | (((uint32_t)pbufferreceive[FillIndex+31])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+32])<<4)  | (((uint32_t)pbufferreceive[FillIndex+33]));

                            LevyWalk_ForwardZeroTime2[jj]    =  (((uint32_t)pbufferreceive[FillIndex+34])<<28) | (((uint32_t)pbufferreceive[FillIndex+35])<<24) |
                                                  (((uint32_t)pbufferreceive[FillIndex+36])<<20) | (((uint32_t)pbufferreceive[FillIndex+37])<<16)
                                                | (((uint32_t)pbufferreceive[FillIndex+38])<<12) | (((uint32_t)pbufferreceive[FillIndex+39])<<8)  |
                                                  (((uint32_t)pbufferreceive[FillIndex+40])<<4)  | (((uint32_t)pbufferreceive[FillIndex+41]));

                            LevyWalk_ForwardChannelAmplitude[jj] =(((uint32_t)pbufferreceive[FillIndex+42])<<12) | (((uint32_t)pbufferreceive[FillIndex+43])<<8)  |
                                                (((uint32_t)pbufferreceive[FillIndex+44])<<4)  | (((uint32_t)pbufferreceive[FillIndex+45]));

                            FillIndex += 45;
                        }
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    case 0x45:// ----------------------------------- AUTOMATIC NAVIGATION --------------------------------------- //
                        // This case is used to test speed and choose correct thresholds
                        FillIndex = 11;
                        for (i = 0; i <= 5; i++)
                        {
                            LevyWalk_SubVariable5 = 0.0;
                            LevyWalk_SubVariable5 = ((((uint32_t)pbufferreceive[i*8 + FillIndex + 6])<<28) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 7])<<24) |
                                                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 4])<<20) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 5])<<16)
                                                                | (((uint32_t)pbufferreceive[i*8 + FillIndex + 2])<<12) | (((uint32_t)pbufferreceive[i*8 + FillIndex + 3])<<8)  |
                                                                (((uint32_t)pbufferreceive[i*8 + FillIndex + 0])<<4)  | (((uint32_t)pbufferreceive[i*8 + FillIndex + 1])));
                            LevyWalk_SubVariable_Pointer = &LevyWalk_SubVariable5;
                            LevyWalk_RobotPos_Sub[i]  = *LevyWalk_SubVariable_Pointer;
                        }
                        // Input the roach's position into three arrays of speed for the forward speed calculation
                        LevyWalk_RobotPos[0] = LevyWalk_RobotPos_Sub[0];
                        LevyWalk_RobotPos[1] = LevyWalk_RobotPos_Sub[1];
                        LevyWalk_RobotPos[2] = LevyWalk_RobotPos_Sub[3];
                        LevyWalk_RobotPos[3] = LevyWalk_RobotPos_Sub[4];
                        RobotHead[0] = LevyWalk_RobotPos[0]; // X Position
                        RobotHead[1] = LevyWalk_RobotPos[1]; // Y Position
                        RobotTail[0] = LevyWalk_RobotPos[2]; // X Position
                        RobotTail[1] = LevyWalk_RobotPos[3]; // Y Position
                        MarkerTest = DistanceCalculation(RobotHead, RobotTail);
                        if (CompareFloat(MarkerTest, 0.0) == false)
                        {
                            if (LevyWalk_SpeedCount > 299)
                            {
                                LevyWalk_SpeedCount = 0;
                            }
                            LevyWalk_SpeedArray_XHead[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[0];
                            LevyWalk_SpeedArray_YHead[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[1];
                            LevyWalk_SpeedArray_ZHead[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[2];
                            LevyWalk_SpeedArray_X[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[3];
                            LevyWalk_SpeedArray_Y[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[4];
                            LevyWalk_SpeedArray_Z[LevyWalk_SpeedCount] = LevyWalk_RobotPos_Sub[5];
                            FillIndex = 3;
                            LevyWalk_SpeedArray_T[LevyWalk_SpeedCount] =  (((uint32_t)pbufferreceive[FillIndex+0])<<28) | (((uint32_t)pbufferreceive[FillIndex+1])<<24) |
                                                   (((uint32_t)pbufferreceive[FillIndex+2])<<20) | (((uint32_t)pbufferreceive[FillIndex+3])<<16)
                                                 | (((uint32_t)pbufferreceive[FillIndex+4])<<12) | (((uint32_t)pbufferreceive[FillIndex+5])<<8)  |
                                                   (((uint32_t)pbufferreceive[FillIndex+6])<<4)  | (((uint32_t)pbufferreceive[FillIndex+7]));
                            LevyWalk_SpeedCount++;
                        }
                        // These lines are used to test the linear and angular velocity
                        if (LevyWalk_TemporalVariableToTestSpeed >= LevyWalk_DurationToCheckSpeed)
                        {

                            LevyWalk_SpeedFlag_Linear = false; // Initially set the speed flag is false to say there is not enough data points to accurately calculate speed
                            LevyWalk_ForwardVelocity = LevyWalk_ForwardVelocityCalculation_Sign();
                            if (LevyWalk_SpeedFlag_Linear == false)
                            {
                                LevyWalk_ForwardVelocity = NAN;
                            }
                            LevyWalk_SpeedFlag_Angular = false; // Initially set the speed flag is false to say there is not enough data points to accurately calculate speed
                            LevyWalk_AngularVelocity = LevyWalk_AngularVelocityCalculation_Sign();
                            if (LevyWalk_SpeedFlag_Angular == false)
                            {
                                LevyWalk_AngularVelocity = NAN;
                            }
                            LevyWalk_ForwardVelocity_Vicon = LevyWalk_ForwardVelocity;
                            LevyWalk_AngularVelocity_Vicon = LevyWalk_AngularVelocity;

                            // 200929: We now will calculate the speed using Long's IMU
                            LevyWalk_SpeedFlag_Linear  = true;
                            LevyWalk_ForwardVelocity   = fabs(absolutespeed)*1000; // To convert from m/s to mm/s
                            LevyWalk_SpeedFlag_Angular = true;
                            LevyWalk_AngularVelocity   = fabs(omega*(180.0/L_PI)); // To convert from rad/s to degree/s
                            LevyWalk_ForwardVelocity_IMU = LevyWalk_ForwardVelocity;
                            LevyWalk_AngularVelocity_IMU = LevyWalk_AngularVelocity;

                            LevyWalk_TemporalVariableToTestSpeed = 0;
                        }
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        break;
                    case 0x49:
                        LevyWalk_Tagert_Order = 1;
                        StimulationTrigger   = true;
                        StimulationStartStop = false;
                        // Reset all the navigational variable to prepare for the next navigation
                        LevyWalk_TurnPrevious                = 0;
                        LevyWalk_Turn                        = 0;     // Stop the navigation
                        LevyWalk_IsLongStimulusHandleStarted = false; // The variable to indicate that long stimulus is being handled
                        LevyWalk_IsLongStimulusBeingChecked  = false; // The variable to indicate that long stimulus is being monitored
                        LevyWalk_IsNavigated                 = true;  // Enable navigation process
                        LevyWalk_IsForwardTriggeredAlready   = false; // The variable to indicate that forward stimulation has been already started
                        LevyWalk_ShouldCheckTheForwardSpeed  = false;
                        LevyWalk_TimeafterForwardStimulus    = 0;
                        LevyWalk_TimeofStimulusForSteering   = 0;
                        LevyWalk_TimeafterLongStimulus       = 0;
                        LevyWalk_TimeafterAngleSmallerThanThreshold       = 0;
                        LevyWalk_TimeCounterForFreeWalkAfterSteering      = 0;
                        LevyWalk_StartCoutingTimeForFreeWalkAfterSteering = false;

                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;

                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        break;
                    case 0x58: // Read Data From Flash
                        // Turn off variables that allow the Flash Saving Process
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        SendCMDcnt = 0x58; // To prepare data for flash saving
                        // Storage current state of all sensors then turn them off
                        IRSensor_onoff_old  = IRSensor_onoff;
                        Co2Sensor_onoff_old = Co2Sensor_onoff;
                        IRSensor_onoff      = false;
                        Co2Sensor_onoff     = false;
                        // Start the Flash reading if CurrentFlashByte is negative (I have not understood this part yet)
                        if (CurrentFlashByte < 0)
                        {
                            CurrentFlashByte       = 0;
                            CurrentFrameNo         = 0;
                            CurrentFlashByteoffset = 0;
                        }
                        sleep(1);
                        break;
                    case 0x59:
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;
                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        // Restore all the sensor operation
                        IRSensor_onoff  = IRSensor_onoff_old;
                        Co2Sensor_onoff = Co2Sensor_onoff_old;
                        // Post semaphore to restore the task
                        Semaphore_post(Analog_SemHandle);
                        Semaphore_post(SemHandle_IR);
                        SendCMDcnt = 1;
                        break;
                    default:
                        // Reset counter of speed = 0
                        LevyWalk_NumberAngularSpeed = 0;
                        LevyWalk_NumberLinearSpeed  = 0;
                        // This part is to only allow Flash Saving Work at 0x40 (Demonstration purpose - Oct 2020)
                        Flash_ShouldWeSave = false;
                        Flash_ShouldWeSave_Previous = false;
                        Flash_IsFlashBeingWritten = false;
                        Flash_IsItTimeToSaveFlash = false;
                        LevyWalk_Tagert_Order = 1;
                        break;
                    }
                }
            }
        }
        // ----------------------------------------------- PREPARATION OF TRANSMISSION DATA ----------------------------- //
        if (isbufferempty)
        {
            switch (SendCMDcnt)
            {
            case 1:
                // ------------ Fill buffer
                // Start and Stop characters S-X
                pbuffertransmit[0] = 83;
                pbuffertransmit[SPI_TRANS_LEN-  1] = 88;
                // Command Count
                pbuffertransmit[1] = Num2textbyte((CMDcnt>>4) & 0x0F);
                pbuffertransmit[2] = Num2textbyte(CMDcnt & 0x0F);
                // Command Sub
                SendCMDcnt_sub = 1;
                pbuffertransmit[3] = Num2textbyte((SendCMDcnt_sub>>4) & 0x0F);
                pbuffertransmit[4] = Num2textbyte(SendCMDcnt_sub & 0x0F);

                // Data
                // Note: Environmental data will no be streamed back in the experiment
                // Sending back the Request Data
                pbuffertransmit[9]  = Num2textbyte((RequestDataSendBack>>12) & 0x000F);
                pbuffertransmit[10] = Num2textbyte((RequestDataSendBack>>8)  & 0x000F);
                pbuffertransmit[11] = Num2textbyte((RequestDataSendBack>>4)  & 0x000F);
                pbuffertransmit[12] = Num2textbyte(RequestDataSendBack & 0x000F);

                // Calculated linear velocity 13-20
                LevyWalk_SubVariable4 = LevyWalk_ForwardVelocity_IMU;
                Num2textfloat(&pbuffertransmit[13], &LevyWalk_SubVariable4);

                // Calculated angular velocity 21-28
                LevyWalk_SubVariable4 = fabs(LevyWalk_AngularVelocity_IMU);
                Num2textfloat(&pbuffertransmit[21], &LevyWalk_SubVariable4);

                // Battery voltage --------------- 29-36
                Num2textfloat(&pbuffertransmit[29], &BatteryVoltage);

                // Navigation command for Automatic Navigation
                RequestDataSendBack = LevyWalk_Turn; // This variable is used to to indicate the appropriate electrical signal
                pbuffertransmit[41] = Num2textbyte((RequestDataSendBack>>12) & 0x000F);
                pbuffertransmit[42] = Num2textbyte((RequestDataSendBack>>8)  & 0x000F);
                pbuffertransmit[43] = Num2textbyte((RequestDataSendBack>>4)  & 0x000F);
                pbuffertransmit[44] = Num2textbyte(RequestDataSendBack & 0x000F);

                // Sending back Fire Spot Detection
                if (FireWatch_Detected)
                {
                    FrameNumberSendBack = 2.0;
                    FireWatch_Detected  = false;
                }
                else
                {
                    FrameNumberSendBack = 0.0;
                }
                Num2textfloat(&pbuffertransmit[45], &FrameNumberSendBack);

                // Number of angular speed = 0 69-76
                LevyWalk_SubVariable4 = (float)(LevyWalk_NumberAngularSpeed);
                Num2textfloat(&pbuffertransmit[69], &LevyWalk_SubVariable4);

                // Number of linear speed = 0 77-84
                LevyWalk_SubVariable4 = (float)(LevyWalk_NumberLinearSpeed);
                Num2textfloat(&pbuffertransmit[77], &LevyWalk_SubVariable4);

                // Long's IMU Information
                Num2textfloat(&pbuffertransmit[85],  &ypr[0]);
                Num2textfloat(&pbuffertransmit[93],  &ypr[1]);
                Num2textfloat(&pbuffertransmit[101], &ypr[2]);
                Num2textfloat(&pbuffertransmit[109], &yaw_bias);
                accel_check[0] = (float)accel_raw[0];
                accel_check[1] = (float)accel_raw[1];
                accel_check[2] = (float)accel_raw[2];
                Num2textfloat(&pbuffertransmit[117], &accel_float[0]);
                Num2textfloat(&pbuffertransmit[125], &accel_float[1]);
                Num2textfloat(&pbuffertransmit[133], &accel_float[2]);
                Num2textfloat(&pbuffertransmit[141], &speed[0]);
                Num2textfloat(&pbuffertransmit[149], &speed[1]);
                Num2textfloat(&pbuffertransmit[157], &speed[2]);

                // Speed calculated using IMU
                LevyWalk_SubVariable4 = (float)omega;
                Num2textfloat(&pbuffertransmit[221], &LevyWalk_SubVariable4);
                LevyWalk_SubVariable4 = (float)absolutespeed;
                Num2textfloat(&pbuffertransmit[229], &LevyWalk_SubVariable4);

                // Angular Speed and Linear Speed for Navigation
                // Calculated linear velocity 53-60
                LevyWalk_SubVariable4 = LevyWalk_ForwardVelocity_Vicon;
                Num2textfloat(&pbuffertransmit[53], &LevyWalk_SubVariable4);
                // Calculated angular velocity 61-68
                LevyWalk_SubVariable4 = fabs(LevyWalk_AngularVelocity_Vicon);
                Num2textfloat(&pbuffertransmit[61], &LevyWalk_SubVariable4);

                // Human Detection score and number of pixel in a given range
                Num2textfloat(&pbuffertransmit[165], &HumanDetection_Score);
                LevyWalk_SubVariable4 = (float)(HuuDuoc_PixelInRange);
                Num2textfloat(&pbuffertransmit[173], &LevyWalk_SubVariable4);

                // Navigation Target
                LevyWalk_SubVariable4 = LevyWalk_Target_Current[0];
                Num2textfloat(&pbuffertransmit[181], &LevyWalk_SubVariable4);
                LevyWalk_SubVariable4 = LevyWalk_Target_Current[1];
                Num2textfloat(&pbuffertransmit[189], &LevyWalk_SubVariable4);

                // Allow the IR image to be streamed
                if (StreamImage == true)
                {
                    SendCMDcnt = 5;
                    IRpartcnt  = 0;
                }

                isbufferempty = false; // Buffer filled
                break;
            case 5:
                // ---- IR image ----- //
                // Fill buffer
                // Start stop
                pbuffertransmit[0] = 83;
                pbuffertransmit[SPI_TRANS_LEN-1] = 88;
                // Command count
                pbuffertransmit[1] = Num2textbyte((CMDcnt>>4) & 0x0F);
                pbuffertransmit[2] = Num2textbyte(CMDcnt & 0x0F);
                // Command sub
                SendCMDcnt_sub = 5;
                pbuffertransmit[3] = Num2textbyte((SendCMDcnt_sub>>4) & 0x0F);
                pbuffertransmit[4] = Num2textbyte(SendCMDcnt_sub & 0x0F);
                FillIndex = 5;
                for (jj = 0; jj<112; jj++)
                {
                    if (IRpartcnt < 1024)
                    {
                        pixeltempf = IR_ImagetoSend[IRpartcnt];
                        //pixeltempf = 10.0f*(IR_ImagetoSend[IRpartcnt] - 15.0f); // Fire Watch
                        if (pixeltempf <= 0.0f)
                            pixeltempf = 0.0f;
                        if (pixeltempf > 255.0f)
                            pixeltempf = 255.0f;
                        pixeltempu8 = (uint8_t)pixeltempf;
                        pbuffertransmit[FillIndex] = Num2textbyte((pixeltempu8>>4) & 0x0F);
                        pbuffertransmit[FillIndex + 1] = Num2textbyte(pixeltempu8 & 0x0F);
                        IRpartcnt++;
                    }
                    else
                    {
                        SendCMDcnt = 1;
                    }

                    FillIndex += 2;
                }
                pbuffertransmit[SPI_TRANS_LEN-5] = Num2textbyte((IRpartcnt>>12) & 0x0F);
                pbuffertransmit[SPI_TRANS_LEN-4] = Num2textbyte((IRpartcnt>>8) & 0x0F);
                pbuffertransmit[SPI_TRANS_LEN-3] = Num2textbyte((IRpartcnt>>4) & 0x0F);
                pbuffertransmit[SPI_TRANS_LEN-2] = Num2textbyte(IRpartcnt & 0x0F);
                if (SendCMDcnt == 1)
                {
                    // The Image has been sent completely so the variable must be flipped to announce the IR_Sensor Task
                    // that it can update another image (to send) now
                    IsIRImageCompletelySent = true;
                }
                // Buffer filled
                isbufferempty = false;
                break;
            case 0x58: // Read Data From The Flash Memory
                pbuffertransmit[0] = 83;
                pbuffertransmit[SPI_TRANS_LEN-1] = 88;
                pbuffertransmit[1] = Num2textbyte((CMDcnt>>4) & 0x0F);
                pbuffertransmit[2] = Num2textbyte(CMDcnt & 0x0F);
                if (isFlashOK == false)
                {
                    // Flash is failed to open so 0x59 is returned
                    // This number is used to indicate the GUI that either it is failed to open Flash or Flash reading is finished
                    SendCMDcnt_sub = 0x59;
                    pbuffertransmit[3] = Num2textbyte((SendCMDcnt_sub>>4) & 0x0F);
                    pbuffertransmit[4] = Num2textbyte(SendCMDcnt_sub & 0x0F);
                }
                else
                {
                    // Flash is open successfully, we proceed with the Flash reading process
                    SendCMDcnt_sub = 0x58;
                    pbuffertransmit[3] = Num2textbyte((SendCMDcnt_sub>>4) & 0x0F);
                    pbuffertransmit[4] = Num2textbyte(SendCMDcnt_sub & 0x0F);
                    // Flash data
                    if(CMDcnt != CMDcntold)
                    {
                        CurrentFlashByteOld = CurrentFlashByte;
                        CurrentFlashByteoffsetold = CurrentFlashByteoffset;
                    }
                    else
                    {
                        // Resend the data
                        CurrentFlashByte = CurrentFlashByteOld;
                        CurrentFlashByteoffset = CurrentFlashByteoffsetold;
                    }
                    // Data
                    FillIndex = 5;
                    sendbyte = (uint8_t *)&DatalogstructReadBack;
                    for (jj = 0; jj < 112; jj++)
                    {
                        uint32_t fillidxf;
                        uint8_t*  byteval0;
                        if ( CurrentFlashByte >= 0)
                        {
                            if(CurrentFlashByte >= (CurrentFrameNo * sizeof(datalog) ))
                            {
                                // Read next data
                                isFlashOK = Readdatafrommemoryatsector(CurrentFrameNo, (uint8_t*)&DatalogstructReadBack);
                                CurrentFrameNo++;
                                CurrentFlashByteoffset = CurrentFlashByte;
                            }
                            if ( CurrentFlashByte < (511*sizeof(datalog)))
                            {
                                fillidxf = CurrentFlashByte - CurrentFlashByteoffset;
                                byteval0 = sendbyte + fillidxf;
                                pbuffertransmit[FillIndex]     = Num2textbyte(((*byteval0)>>4) & 0x0F);
                                pbuffertransmit[FillIndex + 1] = Num2textbyte((*byteval0) & 0x0F);
                                CurrentFlashByte++;
                                numberbytealreadysent = CurrentFlashByte;
                            }
                            else // Finish all data reset
                            {
                                CurrentFlashByte = -1;
                                SendCMDcnt = 0x59; // Release send cmd to system and terminate autoload
                            }
                            FillIndex += 2;
                        }
                    }
                    pbuffertransmit[SPI_TRANS_LEN-9] = Num2textbyte((numberbytealreadysent>>28) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-8] = Num2textbyte((numberbytealreadysent>>24) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-7] = Num2textbyte((numberbytealreadysent>>20) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-6] = Num2textbyte((numberbytealreadysent>>16) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-5] = Num2textbyte((numberbytealreadysent>>12) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-4] = Num2textbyte((numberbytealreadysent>>8) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-3] = Num2textbyte((numberbytealreadysent>>4) & 0x0F);
                    pbuffertransmit[SPI_TRANS_LEN-2] = Num2textbyte(numberbytealreadysent & 0x0F);
                }
                isbufferempty = false;
                Semaphore_post(Empty_SemHandle);
                break;
            case 0x59:
                // This is the termination of Flash Reading
                pbuffertransmit[0] = 83;
                pbuffertransmit[SPI_TRANS_LEN-1] = 88;
                pbuffertransmit[1] = Num2textbyte((CMDcnt>>4) & 0x0F);
                pbuffertransmit[2] = Num2textbyte(CMDcnt & 0x0F);
                SendCMDcnt_sub = 0x59;
                pbuffertransmit[3] = Num2textbyte((SendCMDcnt_sub>>4) & 0x0F);
                pbuffertransmit[4] = Num2textbyte(SendCMDcnt_sub & 0x0F);;
                Co2Sensor_onoff = Co2Sensor_onoff_old;
                IRSensor_onoff  = IRSensor_onoff_old;
                Semaphore_post(Analog_SemHandle);
                Semaphore_post(SemHandle_IR);
                isbufferempty = false;
                SendCMDcnt = 1;
                break;
            default:
                SendCMDcnt = 1;
                break;
            }

        }

        // -------------------------------------- BASE LINE FOR CO2 SENSOR ----------------------------------- //
        // Read the stable baseline in flash memory and assign to "BaselinevalOld[2]" and status flag "isOldBaselineFound"
        // only call this function when flash is okay
        // The stable baseline is stored in the last sector of the flash memory
        if(BaselineReadytoSave)
        {
            BaselineReadytoSave = false;
            if(isFlashOK)
            {
                // Read back last state variable
                isFlashOK = StatevariableRead((uint8_t *) &savestatevariable);
                // Assign data value
                savestatevariable.DataConsistencyCheck = SAVEDATAKEY;
                memcpy(savestatevariable.CCS811Baseline, Baselineval, 2);
                isFlashOK = StatevariableSave();
            }
        }

        // ------------------------------------ STORE DATA IN FLASH ------------------------------------------------- //
        if (Flash_IsItTimeToSaveFlash == true)
        {
            Flash_IsItTimeToSaveFlash = false;
            Savecurrentdata();
        }
    }
}
// ----------------------------------- FUNCTION TO HANDLES READING AND WRITTING ------------------------------------------ //
static bool StatevariableRead(uint8_t * Buff)
{
    /*
     * CCS811BaselineRead
     * Read the stable baseline in flash memory and assign to "BaselinevalOld[2]" and status flag "isOldBaselineFound"
     * only call this function when flash is ok
     * The stable baseline is stored in last sector of the flash memory
     * */
    int i;
    uint32_t offsetadd;
    uint32_t offsetadd0;
    struct statevariable statevariabletemp;

    bool baselinereadstatus = false;
    ///
    statevariabletemp.DataConsistencyCheck = SAVEDATAKEY;
    for (i = 0; i < 29; i++)
    {
        statevariabletemp.Reserved[i] = 0xFF;
    }

    offsetadd0 = STATEVARIABLESTARTADD + STATEVARIABLEOFFSET;
    offsetadd = offsetadd0;
    while(1)
    {
        memcpy(Buff, (uint8_t*)&statevariabletemp,STATEVARIABLESTEP);
        if (extFlashRead(offsetadd, STATEVARIABLESTEP, (uint8_t*) &statevariabletemp))
        {
           if(statevariabletemp.DataConsistencyCheck != SAVEDATAKEY) // meet the blank space
           {
               if(offsetadd != offsetadd0)
               {
                   baselinereadstatus = true;
               }
               else
               {
                   baselinereadstatus = false;
               }
               break;
           }
           offsetadd = offsetadd + STATEVARIABLESTEP;
           if(offsetadd >= STATEVARIABLESTOPADD)
           {
               baselinereadstatus = false;
               break;
           }

        }
        else
        {
           baselinereadstatus = false;
           break;
        }
    }
    return baselinereadstatus;
}
static bool StatevariableSave(void)
{
    uint32_t offsetadd, offsetadd0;
    int16_t  Flashreadtemp;
    bool flashstatus;
    ///
    struct statevariable statevariabletemp;

    offsetadd0 = STATEVARIABLESTARTADD + STATEVARIABLEOFFSET;
    offsetadd = offsetadd0;

    // find start point at the end of the sector
    while(1)
    {
        if (extFlashRead(offsetadd, STATEVARIABLESTEP, (uint8_t*) &statevariabletemp))
        {
            // blank space
            memcpy((uint8_t*)&Flashreadtemp, statevariabletemp.CCS811Baseline, 2);

            if ((Flashreadtemp == -1)&&(statevariabletemp.DataConsistencyCheck == 0xFF))
            {
                flashstatus = true;
                break;
            }
            offsetadd = offsetadd + STATEVARIABLESTEP;
            if(offsetadd > STATEVARIABLESTOPADD) // end of sector, need to clear all the sector and fill from start, statevariabletemp contain the latest value
            {
                // erase the sector
                offsetadd = offsetadd0;
                if(extFlashErase(offsetadd, STATEVARIABLESTEP))
                {
                    // write the last value first
                    if( extFlashWrite(offsetadd, STATEVARIABLESTEP, (uint8_t *)&statevariabletemp))
                    {
                        offsetadd = offsetadd + STATEVARIABLESTEP;
                        flashstatus = true;
                    }
                    else
                    {
                        flashstatus = false;
                    }
                    break;
                }
                else // failed to erase
                {
                    flashstatus = false;
                    break;
                }
            }
        }
        else
        {
            flashstatus = false;
            break;
        }
    }
    // write baseline value to the flash
    if(flashstatus)
    {
        // write the last value first
        flashstatus = extFlashWrite(offsetadd, STATEVARIABLESTEP, (uint8_t *)&savestatevariable);
    }
    return flashstatus;
}
#define DATALOG_START_ADDRESS   0x000000
#define DATALOG_STOP_ADDRESS    0x1FEFFF
#define DATALOG_STEP_SIZE       0x001000
static void  FindLatestLogNumber(uint32_t *outlognumber, uint32_t *nextfreeaddress)
{
    uint32_t foundlognumber, foundlognumberold;

    uint32_t offsetadd = DATALOG_START_ADDRESS;
    uint32_t availadd;
    bool looptemp = true;
    foundlognumber = 0;
    availadd = DATALOG_START_ADDRESS;
    while (looptemp)
    {
        availadd = offsetadd;
        foundlognumberold = foundlognumber;
        if (extFlashRead(offsetadd, 4, (uint8_t*) &foundlognumber))
        {
            if(foundlognumber == 0xffffffff)
            { // found free location
                looptemp = false;
            }
            else
            {
                if(foundlognumber < foundlognumberold) // new value is smaller than the old one
                {
                    looptemp = false;
                }
            }
        }
        else
        {
            looptemp = false;
            isFlashOK = false;
        }
        offsetadd += DATALOG_STEP_SIZE;

        if(offsetadd > DATALOG_STOP_ADDRESS)
        {
            // wind up
            availadd = DATALOG_START_ADDRESS;
            // cannot find the log data
            looptemp = false;
        }
    }
    // return
    *outlognumber = foundlognumberold;
    *nextfreeaddress = availadd;
}
static void Savecurrentdata(void)
{
    uint16_t i;
    float  fpixelvaltemp;
    Flash_IsFlashBeingWritten = true; // Prevent data to be overwritten in to Flash_IR_Image and Flash_FrameNumberArray
    // ---------- Prepare data to save into Flash
    Datalogstruct.LogTime = TimeCntMilisecond;
    // Three Frame Numbers
    Datalogstruct.FrameNumber[0] = Flash_FrameNumberArray[0];
    Datalogstruct.FrameNumber[1] = Flash_FrameNumberArray[1];
    Datalogstruct.FrameNumber[2] = Flash_FrameNumberArray[2];
    // IR pixel: temperature 15 - 40.6 / resolution 0.1 degree C
    for (i = 0; i < IR_ARRAY_SIZE*3; i++)
    {
        fpixelvaltemp = Flash_IR_Image[i] - 15.0f;
        if(fpixelvaltemp < 0.0f)
        {
            fpixelvaltemp = 0.0f;
        }
        else if(fpixelvaltemp >= 25.6f)
        {
            fpixelvaltemp = 25.5f;
        }
        fpixelvaltemp = fpixelvaltemp*10;

        Datalogstruct.IRpixel[i] = (uint8_t)fpixelvaltemp;
    }
    // --------- Write to Flash
    if (isFlashOK)
    {
        isFlashOK = Writedatatomemory();
    }
    Flash_IsFlashBeingWritten = false; // Allow the IR_SensorTask to keep store the captured IR Image and Frame Number into the two corresponding array
}
static bool Writedatatomemory(void)
{
    bool flashstatus;
    FindLatestLogNumber(&Latestlognumber, &freeaddressfordatasaving);
    Datalogstruct.LogNumber = Latestlognumber + 1;
    // erase the free data sector
    if(extFlashErase(freeaddressfordatasaving, 2))
    {
        // write the last value first
        flashstatus =  extFlashWrite(freeaddressfordatasaving, sizeof(datalog), (uint8_t *)&Datalogstruct);
    }
    else // failed to erase
    {
        flashstatus = false;
    }
    return flashstatus;
}
static bool Readdatafrommemory(uint8_t* buff)
{
    uint32_t offset;
    bool flashstatus;
    FindLatestLogNumber(&Latestlognumber,&freeaddressfordatasaving);
    offset = 0;
    if(freeaddressfordatasaving > 0)
    {
        offset = freeaddressfordatasaving - DATALOG_STEP_SIZE;
    }
    flashstatus = extFlashRead(offset, sizeof(datalog), (uint8_t*) buff);
    return flashstatus;
}
static bool Readdatafrommemoryatsector(uint16_t sector, uint8_t* buff)
{
    uint32_t offset;
    bool flashstatus;
    if(sector > 510)
    {
        sector = 510;
    }
    offset = sector * DATALOG_STEP_SIZE;
    flashstatus = extFlashRead(offset, sizeof(datalog), (uint8_t*) buff);
    return flashstatus;
}
// ----------------------------------- FUNCTION TO HANDLES READING AND WRITTING ------------------------------------------ //
float DistanceCalculation(float *A, float *B)
{
    float result = 0.0;
    result = sqrt(pow(A[0] - B[0], 2) + pow(A[1] - B[1], 2));
    return result;
}
bool CompareFloat(float f1, float f2)
{
    float precision = 0.00001;
    if (((f1 - precision) < f2) && ((f1 + precision) > f2))
    {
        return true;
    }
    else
    {
        return false;
    }
}
uint8_t Num2textbyte(uint8_t x)
{
    uint8_t valtemp;
    if (x<10)
    {
        valtemp = x + 48;
    }
    else
    {
        valtemp = x + 55;
    }
    return valtemp;
}
void Num2textfloat(uint8_t * outbuf, float * inbuf)
{
    uint8_t ByteTemp[4];
    memcpy(ByteTemp, inbuf, 4);
    outbuf[0] = Num2textbyte((ByteTemp[0]>>4) & 0x0F);
    outbuf[1] = Num2textbyte(ByteTemp[0] & 0x0F);
    outbuf[2] = Num2textbyte((ByteTemp[1]>>4) & 0x0F);
    outbuf[3] = Num2textbyte(ByteTemp[1] & 0x0F);
    outbuf[4] = Num2textbyte((ByteTemp[2]>>4) & 0x0F);
    outbuf[5] = Num2textbyte(ByteTemp[2] & 0x0F);
    outbuf[6] = Num2textbyte((ByteTemp[3]>>4) & 0x0F);
    outbuf[7] = Num2textbyte(ByteTemp[3] & 0x0F);
}
float Hex2num_float(uint8_t *val)
{
    uint8_t ByteTemp[4];
    float ret;

    ByteTemp[0] = (((uint8_t)val[0])<<4)  | ((uint8_t)val[1]);
    ByteTemp[1] = (((uint8_t)val[2])<<4)  | ((uint8_t)val[3]);
    ByteTemp[2] = (((uint8_t)val[4])<<4)  | ((uint8_t)val[5]);
    ByteTemp[3] = (((uint8_t)val[6])<<4)  | ((uint8_t)val[7]);
    memcpy(&ret, ByteTemp, 4);

    return ret;
}
