// ------------------------------- IR SENSOR TASK ------------------------------- //
// Initial Author: DUNG VAN THAN
// Edited by: NGUYEN HUU DUOC
// Date: 23-MAR-2019
// ------------------------------------------------------------------------------ //
// The current IR sensor

// ----------------------------- LIBARIES ------------------------------ //
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
#include "Board.h"
#include "IR_Sensor.h"
#include "HumanDetection.h"

// ----------------------------- PARAMETERS TO CREATE TASK ------------------------------ //
// Task parameter
#define IRTASKSTACKSIZE    35000; // Huu Duoc: 31724 // => This number is used in my version which use HOG for feature extraction // 4098 => This is A. Than's number
#define IRTASKPRIORITY     2
#define IRSAMPLERATEMS     500   // Collect IR data every 500 ms
// Task functions
void IRSensorTask(UArg arg0, UArg arg1);
static void PeriodicClockExpired_IR(UArg Arg);
void IR_Sensor_OutdoorRotate(void);
// Creation Functions
void IRSensorTaskCreate(void)
{
    Error_Block Erb_IR;
    Task_Handle PeriTaskHandle_IR;
    Task_Params PeriodicTaskParams_IR;
    Error_init(&Erb_IR);
    Task_Params_init(&PeriodicTaskParams_IR);
    PeriodicTaskParams_IR.priority = IRTASKPRIORITY;
    PeriodicTaskParams_IR.stackSize = IRTASKSTACKSIZE;
    PeriTaskHandle_IR = Task_create(IRSensorTask, &PeriodicTaskParams_IR, &Erb_IR);
    if (PeriTaskHandle_IR == NULL)
    {
        while(1);
    }
}
// ----------------------------- GLOABAL VARIABLES ------------------------------ //
// IR Image storing variables
float IR_Image[IR_ARRAY_SIZE];
float Ambient_Temp;
float IR_Image0[IR_ARRAY_SIZE]; // This IR_Image0 is the rotated image (due to the board's rotation) => Read it first then rotate and we will have a correct Image
float IR_Image1[IR_ARRAY_SIZE]; // These variables: IR_Image1 and Ambient_Temp1 are used to store the IR data for Flash
float Ambient_Temp1;            // saving purpose.
bool  volatile humandetected;
extern bool isDatawriting;
// IR Task checking variables
bool  IR_ImageUpdated;
extern bool IRSensor_onoff;
extern bool gIRsensorOk;
// IR Image sending to GUI variables
float IR_ImagetoSend[IR_ARRAY_SIZE]; // Variables to make sure one completed image is sent
volatile bool IsIRImageCompletelySent;
volatile float SVM_Threshold; // This threshold is used to balance the trade-off between Precision and Recall => We will tune it using the GUI, the final value will be send to
                              // the wireless board
volatile bool IsOnBoardHumanDetection; // This variable is used to allow the human detection process happens on-board
volatile float HumanDetection_Score;
// ----------------------------- SEMAPHORE ------------------------------ //
Semaphore_Handle SemHandle_IR;
// ----------------------------- CLOCK FUNCTIONS ------------------------------ //
static void PeriodicClockExpired_IR(UArg Arg)
{
    if(IRSensor_onoff)
    {
        Semaphore_post(SemHandle_IR);
    }
}
// --------------------------- FLASH MEMORY ---------------------------- //
// HuuDuoc: This part is developed for the purpose of using in demonstration where images collected during navigation is saved into Flash
extern float Flash_FrameNumberArray[3];
extern float Flash_IR_Image[IR_ARRAY_SIZE*3];
extern bool  Flash_ShouldWeSave;
extern uint8_t Flash_Counter;
extern bool  Flash_IsFlashBeingWritten;
extern bool  Flash_IsItTimeToSaveFlash;
extern float FrameNumberSendBack;
extern Semaphore_Handle Empty_SemHandle;
// --------------------------- FIRE SPOT DETECTION  ---------------------------- //
float FireWatch_Threshold = 120.0;
float FireWatch_Variable  = 0.0;
uint32_t FireWatch_Count = 0;
bool FireWatch_Detected = false;
// ----------------------------- IR SENSOR MAIN FUNCTION ------------------------------ //
void IRSensorTask(UArg arg0, UArg arg1)
{
    // Variable supporting for flash saving
    uint32_t Flash_Temp1 = 0;
    uint32_t Flash_Temp2 = 0;

    // Clock variables
    Clock_Struct Period_Clk_IR_struct;
    Clock_Params PeriodClockParam_IR;

    // Semaphore variables
    Semaphore_Struct semaphore_IR_task_struct;
    Semaphore_Params semparams_IR;

    // GPIO indicators
    GPIO_setConfig(MSP_EXP432P4011_GPIO_LED5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(MSP_EXP432P4011_GPIO_LED5, Board_GPIO_LED_ON); // Turn on user LED

    // Semaphore creation
    Semaphore_Params_init(&semparams_IR);
    semparams_IR.mode = Semaphore_Mode_COUNTING;
    Semaphore_construct(&semaphore_IR_task_struct, 0, &semparams_IR);
    SemHandle_IR = Semaphore_handle(&semaphore_IR_task_struct);

    // Clock parameters
    Clock_Params_init(&PeriodClockParam_IR);
    PeriodClockParam_IR.startFlag = true;
    PeriodClockParam_IR.period = IRSAMPLERATEMS;// 2Hz data refreshing rate
    Clock_construct(&Period_Clk_IR_struct,PeriodicClockExpired_IR,1,&PeriodClockParam_IR);

    // IR Sensor Task
    if(!I2CIRinit())
    {
        Task_exit();
    }
    else
    {
        IR_Sensor_Init();
        IR_Sensor_read_Ambient_Temp(&Ambient_Temp);
        IR_Sensor_ReadPixel(IR_Image);
        GPIO_write(MSP_EXP432P4011_GPIO_LED5, Board_GPIO_LED_OFF);

        IsIRImageCompletelySent = true;

        // Initially assign the variable "humandetected"
        humandetected = false;

        // Initially assign the threshold for support vector machine
        SVM_Threshold = 0.0;

        // Human detection on-board is NOT allowed in the beginning
        IsOnBoardHumanDetection = false;

        while(1)
        {
            Semaphore_pend(SemHandle_IR, BIOS_WAIT_FOREVER);
            if(gIRsensorOk)
            {
                // Read IR sensor
                IR_Sensor_read_Ambient_Temp(&Ambient_Temp);
                IR_Sensor_ReadPixel(IR_Image0);

                // Fire Spot Detection
                FireWatch_Detected = false;
                for (FireWatch_Count = 0; FireWatch_Count <= 1023; FireWatch_Count++)
                {
                    FireWatch_Variable = IR_Image0[FireWatch_Count];
                    if (FireWatch_Variable >= FireWatch_Threshold)
                    {
                        FireWatch_Detected = true;
                        break;
                    }
                }

                // Rotate IR Image
                IR_Sensor_OutdoorRotate();
                IR_ImageUpdated = true;
                if (IsOnBoardHumanDetection)
                {
                    HumanDetection_Score = ishumandetected();
                }
                else
                {
                    HumanDetection_Score = 1111; // This number will be transferred to the GUI as an indicator of prohibit of the on-board human detection process
                }
                if (Flash_ShouldWeSave == true)
                {
                    if (Flash_IsFlashBeingWritten == false)
                    {
                        Flash_Temp2 = 0;
                        for (Flash_Temp1 = Flash_Counter*1024; Flash_Temp1 < (Flash_Counter + 1)*1024; Flash_Temp1++)
                        {
                            Flash_IR_Image[Flash_Temp1] = IR_Image[Flash_Temp2];
                            Flash_Temp2++;
                        }
                        Flash_FrameNumberArray[Flash_Counter] = FrameNumberSendBack; // Note: There will be, of course, certain of delay between this Frame and the image, when preparing the video, this should be taken into account

                        if (Flash_Counter == 2)
                        {
                            Flash_Counter = 0;
                            Flash_IsFlashBeingWritten = true; // Temporarily do not IR images are written into Flash_IR_Image[] to avoid overwritten
                            Flash_IsItTimeToSaveFlash = true;
                        }
                        else
                        {
                            Flash_Counter++;
                        }
                    }
                }
                if (IsIRImageCompletelySent)
                {
                    // Only update an image (to send) after the previous image is completely sent
                    // The image for human dection is still being captured
                    memcpy(IR_ImagetoSend, IR_Image, sizeof(float)*IR_ARRAY_SIZE);
                    IsIRImageCompletelySent = false;
                }
            }
        }
    }
}

void IR_Sensor_OutdoorRotate(void)
{
    // This function is used to rotate the image
    uint16_t i, j, curPix;
    uint16_t i1, j1, curPix1;

    for (curPix=0; curPix < IR_ARRAY_SIZE; curPix++)
    {
        i = curPix/32;
        j = curPix - 32*i;
        // Rotate 90deg Rightwards
        i1 = j;
        j1 = 31 - i;
        curPix1 = 32*i1 + j1;
        IR_Image[curPix1] = IR_Image0[curPix];
    }
}













