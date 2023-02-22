// ------------------------------- LEVY WALK TASK ------------------------------- //
// Author: Huu Duoc Nguyen
// Date: 11-JULY-2019
// Note 1: This task is used for automatic navigation. The name has not been changed yet
// Note 2: All distances, coordinates, positions are measured in mm. There will be
//         some conversions from other units to mm through the code.
// Note 3: In this navigation process, the constrain in locomotion of the cockroach is ignored.
//         The process could be consider as a point to point navigation process or the roach is a
//         point-mass. The locomotion constraint could be included in future version.
// ------------------------------------------------------------------------------ //

// IMPORTANT: REVISE RAND(TIME(NULL))

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/SPI.h>
#include "Board.h"
#include "LevyWalkTask.h"

//////// ------------------ INITIAL DEFINATION ----------------------- /////////////
#define LEVYWALKTASKSTACKSIZE 18432 // 10240 This Stack should be checked to effectively use the memory
#define LEVYWALKTASKPRIORITY 2
void LevyWalkTask(UArg arg0, UArg arg1);

//////// ------------------ NECESSARY VARIABLES ----------------------- /////////
// ---------------- Semaphore and Clock Variables
Semaphore_Handle LevyWalk_SemHandle;
Semaphore_Struct sem_LevyWalk_Struct;
// ---------------- Variables to control the control rate
uint32_t LevyWalk_ControlRate    = 250; // Control Rate (ms). The position is sent to the board at the interval of 30ms. The navigation will be periodically executed based on the control rate
bool     LevyWalk_TimeForExecute = false;
uint32_t LevyWalk_ControlCount   = 0;
// --------------- Variables for the location of the cockroach
volatile float LevyWalk_RobotPos[4];
volatile float LevyWalk_AngleThreshold = 20;   // The threshold of angle to decide a steering (degree)
uint32_t LevyWalk_Turn = 0; // This variable is used to to indicate the appropriate electrical signal
uint32_t LevyWalk_TurnPrevious = 0;
volatile float LevyWalk_DistanceThreshold = 100; // Unit here is mm
volatile float LevyWalk_TargetToTest[2] = {0.0, 0.0};
volatile bool  LevyWalk_IsReached       = false;
volatile bool  LevyWalk_IsTheRoachConfined = false;
// ------------- Variable to handle a long steering stimulus
volatile bool LevyWalk_IsLongStimulusHandleStarted = false; // This and the following variables handle the long stimulus situation => Forward motion then free walking
volatile bool LevyWalk_IsLongStimulusBeingChecked  = false;
volatile uint32_t LevyWalk_TimeofStimulusForSteering  = 0; // This variable stores the time counting after a steering stimulus is triggered
volatile uint32_t LevyWalk_TimeafterLongStimulus      = 0; // This variable stores the time counting to handle the forward and free walking motion after a long stimulus is discovered
volatile uint32_t LevyWalk_ThresholdOfLongStimulus         = 5000; // 5s - Variable to indicate how long should a steering stimulus be to be justified as a long stimulus
volatile uint32_t LevyWalk_ThresholdOfLongStimulusForward  = 1000; // 1s - Variable to indicate the duration for a forward stimulation when a long steering stimulus is recorded
volatile uint32_t LevyWalk_ThresholdOfLongStimulusFreeWalk = 2000; // 2s - Variable to indicate the duration for a free walk after the above forward stimulation
volatile uint32_t LevyWalk_ReactionTime                    = 2000; // This variable indicates the time spending before the start estimating the roach's speed during stimulation
// ------------ Variable to handle the forward stimulation
// Note: This forward stimulation is triggered when:
//       (1) the angle between the cockroach's orientation and the target is smaller than a certain threshold
//       (2) the forward velocity of the cockroach is smaller than a certain threshold
volatile bool LevyWalk_IsForwardTriggeredAlready    = false; // This variable indicate the forward motion is already triggered
volatile bool LevyWalk_ShouldCheckTheForwardSpeed   = false; // This variable indicate that we should periodically check the forward speed
volatile uint32_t LevyWalk_TimeafterForwardStimulus = 0;     // This variable stores the time counting after a forward stimulation is triggered
volatile uint32_t LevyWalk_TimeafterAngleSmallerThanThreshold = 0; // This variable stores the time counting after we find the calculated angle < pre-defined threshold. This timer is used to periodically check the forward speed
volatile uint32_t LevyWalk_DurationToCheckSpeed                      = 1000; // 3 seconds // 20-Feb - To make things simple, this variable is used for both cases: free walk and under-stimulation
volatile uint32_t LevyWalk_DurationToCheckSpeed_FreeWalk             = 3000;
volatile uint32_t LevyWalk_DurationToCheckForwardSpeed               = 5000;
volatile uint32_t LevyWalk_DurationToCheckSpeed_Stimulation          = 500;
volatile uint32_t LevyWalk_ThresholdOfTimeForwardWhenSpeedIsSmall    = 1000; // 1 second
volatile uint32_t LevyWalk_ThresholdOfTimeFreeWalkWhenSpeedIsSmall   = 2000; // 2 seconds
volatile float    LevyWalk_ForwardVelocity = 0.0;
volatile float    LevyWalk_AngularVelocity = 0.0;
volatile float    LevyWalk_ForwardVelocity_Vicon = 0.0;
volatile float    LevyWalk_AngularVelocity_Vicon = 0.0;
volatile float    LevyWalk_ForwardVelocity_IMU = 0.0;
volatile float    LevyWalk_AngularVelocity_IMU = 0.0;
volatile bool     LevyWalk_UseIMU_LinearSpeed  = false;
volatile bool     LevyWalk_UseIMU_AngularSpeed = false;
volatile float    LevyWalk_ThresholdOfForwardVelocity = 15.0;  // This and angular speed are the numbers where we say the cockroach is standing still mm/s
volatile float    LevyWalk_ThresholdOfAngularVelocity = 10.0; // degree/s
volatile float    LevyWalk_TimeStoreToCalculateSpeed  = 0.2;
volatile float    LevyWalk_SpeedArray_X[300];
volatile float    LevyWalk_SpeedArray_Y[300];
volatile float    LevyWalk_SpeedArray_Z[300];
volatile uint32_t LevyWalk_SpeedArray_T[300];
volatile float    LevyWalk_SpeedArray_XHead[300];
volatile float    LevyWalk_SpeedArray_YHead[300];
volatile float    LevyWalk_SpeedArray_ZHead[300];
volatile uint32_t LevyWalk_SpeedCount = 0;
volatile bool     LevyWalk_SpeedFlag_Linear  = false; // These flags are used to indicate if there are enough data point to receive a trust calculated speed: false means untrusted - true means trusted
volatile bool     LevyWalk_SpeedFlag_Angular = false;
volatile bool     LevyWalk_SpeedFlag_Linear_IMU    = false; // These flags are used to indicate if there are enough data point to receive a trust calculated speed: false means untrusted - true means trusted
volatile bool     LevyWalk_SpeedFlag_Angular_IMU   = false;
volatile bool     LevyWalk_SpeedFlag_Linear_Vicon  = false; // These flags are used to indicate if there are enough data point to receive a trust calculated speed: false means untrusted - true means trusted
volatile bool     LevyWalk_SpeedFlag_Angular_Vicon = false;
volatile bool     LevyWalk_UseEscapeMode     = true;
volatile uint32_t LevyWalk_AngularSpeedMethod = 1;
uint32_t          LevyWalk_TemporalVariableToTestSpeed = 0;
// ---------------- Variables for stimulation
volatile bool     LevyWalk_LeftChannelActive[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_LeftDuration[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_LeftPeriod[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_LeftActiveTime1[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_LeftZeroTime1[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_LeftZeroTime2[NO_CHANNEL_STI];
volatile uint16_t LevyWalk_LeftChannelAmplitude[NO_CHANNEL_STI];
// ----------------- Variables for stimulation
volatile bool     LevyWalk_RightChannelActive[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_RightDuration[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_RightPeriod[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_RightActiveTime1[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_RightZeroTime1[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_RightZeroTime2[NO_CHANNEL_STI];
volatile uint16_t LevyWalk_RightChannelAmplitude[NO_CHANNEL_STI];
// ----------------- Variables for stimulation
volatile bool     LevyWalk_ForwardChannelActive[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_ForwardDuration[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_ForwardPeriod[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_ForwardActiveTime1[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_ForwardZeroTime1[NO_CHANNEL_STI];
volatile uint32_t LevyWalk_ForwardZeroTime2[NO_CHANNEL_STI];
volatile uint16_t LevyWalk_ForwardChannelAmplitude[NO_CHANNEL_STI];
// ------------------- Variables which used to be inside "while(1)" -------------------- //
// Variables for the roach navigation
float LevyWalk_RobotHead[2];
float LevyWalk_RobotTail[2];
float LevyWalk_Target[16]        = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // This is the target assigned by GUI (8 points)
float LevyWalk_Target_Current[2] = {0.0, 0.0};
uint32_t LevyWalk_Tagert_Order = 1;
float LevyWalk_Distance     = 0.0;
bool  LevyWalk_IsNavigated  = true;
float LevyWalk_MarkerTest   = 0.0;
// This variable is used for debugging purpose
float Testing = 0.0;
// Necessary variables
uint32_t i = 0;
// Variable to reduce the number of stimulations
volatile bool     LevyWalk_EnableTheFreeWalkingAfterStimulation     = false;
volatile uint32_t LevyWalk_TimeCounterForFreeWalkAfterSteering      = 0;
bool              LevyWalk_StartCoutingTimeForFreeWalkAfterSteering = false;
volatile uint32_t LevyWalk_ThresholdForFreeWalkAfterSteering        = 2000;
volatile uint32_t LevyWalk_ThresholdofFinalPartForLongStimulus      = 2000;
// Variable to count the number of zero velocity
uint32_t LevyWalk_NumberAngularSpeed = 0;
uint32_t LevyWalk_NumberLinearSpeed = 0;
/////// -------------------- VARIABLES FROM OTHER FILES --------------------------------/////////////
extern uint32_t StimulateDuration[NO_CHANNEL_STI];
extern uint32_t StimulatePeriod[NO_CHANNEL_STI];
extern uint32_t ActiveTime1[NO_CHANNEL_STI];
extern uint32_t ZeroTime1[NO_CHANNEL_STI];
extern uint32_t ZeroTime2[NO_CHANNEL_STI];
extern uint16_t ChannelAmplitude[NO_CHANNEL_STI];
extern bool     StimulationStartStop;
extern bool     StimulationTrigger;
extern bool     ChannelActive[NO_CHANNEL_STI];
////// --------------------- VARIABLES FROM IMU -------------------------- //////
extern volatile float omega; // rad/s
extern volatile float absolutespeed; // m/s
//////// ------------------ NECESSARY FUNCTIONS ----------------------- /////////
void LevyWalk_GenerateLevyTarget(float *LevyWalk_CurrentPostion, float *LevyWalk_NewTarget);
void LevyWalk_Navigation(float *LevyWalk_CurrentHead, float *LevyWalk_CurrentPostion, float *LevyWalk_CurrentTarget);
float LevyWalk_DotProduct(float *A, float *B);
float LevyWalk_Norm(float *A);
float LevyWalk_CrossProduct(float *A, float *B);
float LevyWalk_DistanceCalculation(float *A, float *B);
void  LevyWalk_Stimulation(uint32_t Stimulation_Side);
int32_t LevyWalk_Steering(float *Position_Head, float *Position_Target);
void LevyWalk_StopStimulus(void);
void LevyWalk_LeftStimulus(void);
void LevyWalk_RightStimulus(void);
void LevyWalk_ForwardStimulus(void);
void LevyWalk_SetStimulation(void);
bool LevyWalk_CompareFloat(float f1, float f2);
void LevyWalk_NavigateTowardTarget(void);
float LevyWalk_ForwardVelocityCalculation(void);
float LevyWalk_ForwardVelocityCalculation_Sign(void);
float LevyWalk_AngularVelocityCalculation(void);
float LevyWalk_AngularVelocityCalculation_Sign(void);
float LevyWalk_AngularVelocityCalculation_Version2(void);
void  LevyWalk_AllSpeedCalculation(void);
//////// ------------------ FUNCTION TO CREATE LEVY WALK TASK----------------------- ////////
void LevyWalkTaskCreation(void)
{
    Error_Block Erb_LevyWalk;
    Task_Handle TaskHandle_LevyWalk;
    Task_Params TaskParams_LevyWalk;
    Error_init(&Erb_LevyWalk);
    Task_Params_init(&TaskParams_LevyWalk);
    TaskParams_LevyWalk.priority = LEVYWALKTASKPRIORITY;
    TaskParams_LevyWalk.stackSize = LEVYWALKTASKSTACKSIZE;
    TaskHandle_LevyWalk = Task_create(LevyWalkTask, &TaskParams_LevyWalk, &Erb_LevyWalk);
    if (TaskHandle_LevyWalk == NULL)
    {
        while(1);
    }
}


//////// ------------------ MAIN FUNCTION----------------------- ////////
void LevyWalkTask(UArg arg0, UArg arg1)
{
    // Semaphore creation for Levy Walk
    Semaphore_Params sem_LevyWalk_Params;
    Semaphore_Params_init(&sem_LevyWalk_Params);
    sem_LevyWalk_Params.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&sem_LevyWalk_Struct, 0, &sem_LevyWalk_Params);
    LevyWalk_SemHandle = Semaphore_handle(&sem_LevyWalk_Struct);

    // Necessary variables
    i = 0;
    // Variables for the roach navigation
    LevyWalk_Distance    = 0.0;
    LevyWalk_IsNavigated = true;
    LevyWalk_MarkerTest  = 0.0;
    // This variable is used for debugging purpose
    Testing = 0.0;

    // Prepare all parameters, especially global parameters, for navigation
    LevyWalk_IsLongStimulusHandleStarted = false;
    LevyWalk_IsLongStimulusBeingChecked  = false;
    LevyWalk_ShouldCheckTheForwardSpeed  = false;
    LevyWalk_IsForwardTriggeredAlready   = false;
    LevyWalk_IsNavigated                 = true;
    LevyWalk_TimeofStimulusForSteering   = 0;
    LevyWalk_TimeafterLongStimulus       = 0;
    LevyWalk_TimeafterForwardStimulus    = 0;
    LevyWalk_TimeafterAngleSmallerThanThreshold       = 0;
    LevyWalk_TimeCounterForFreeWalkAfterSteering      = 0;
    LevyWalk_StartCoutingTimeForFreeWalkAfterSteering = false;

    // Set stimulation parameters
    LevyWalk_SetStimulation();

    while(1)
    {
        Semaphore_pend(LevyWalk_SemHandle, BIOS_WAIT_FOREVER);

        // Extract Position of the cockroach
        LevyWalk_RobotHead[0] = LevyWalk_RobotPos[0]; // X Position
        LevyWalk_RobotHead[1] = LevyWalk_RobotPos[1]; // Y Position
        LevyWalk_RobotTail[0] = LevyWalk_RobotPos[2]; // X Position
        LevyWalk_RobotTail[1] = LevyWalk_RobotPos[3]; // Y Position

        LevyWalk_MarkerTest = LevyWalk_DistanceCalculation(LevyWalk_RobotHead, LevyWalk_RobotTail);
        // ------------- CHECK IF MARKERS OF THE ROACH ARE MISSING ------------------- //
        if (LevyWalk_CompareFloat(LevyWalk_MarkerTest, 0.0))
        {
            // There is marker missing
            // Reset all variables regarding the navigation process when makers are missing
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
        }
        else
        {
            // Note: If there is no missing marker, the navigation process is started
            // Note the "LevyWalk_Distance" is calculated based on the roach's tail because it seems like the roach rotates about its tail when being stimulated
            LevyWalk_Distance = LevyWalk_DistanceCalculation(LevyWalk_RobotTail, LevyWalk_Target_Current);
            if (LevyWalk_Distance <= LevyWalk_DistanceThreshold)
            {
                if (LevyWalk_IsTheRoachConfined == false)
                {
                    LevyWalk_Tagert_Order++;
                    if (LevyWalk_Tagert_Order > 8)
                    {
                        LevyWalk_Tagert_Order = 1;
                    }
                    switch (LevyWalk_Tagert_Order)
                    {
                    case 1:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[0];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[1];
                        break;
                    case 2:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[2];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[3];
                        break;
                    case 3:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[4];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[5];
                        break;
                    case 4:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[6];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[7];
                        break;
                    case 5:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[8];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[9];
                        break;
                    case 6:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[10];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[11];
                        break;
                    case 7:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[12];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[13];
                        break;
                    case 8:
                        LevyWalk_Target_Current[0] = LevyWalk_Target[14];
                        LevyWalk_Target_Current[1] = LevyWalk_Target[15];
                        break;
                    }
                }
                else
                {
                    // Confine the roach in the first target
                    LevyWalk_Target_Current[0] = LevyWalk_Target[0];
                    LevyWalk_Target_Current[1] = LevyWalk_Target[1];
                }
                // The insect has reached the target
                // Reset all variable regarding to navigation process of the cockroach
                LevyWalk_IsReached = true; // The LevyWalk_IsReached here is just a variable for communication purpose (its logical correction will be tested later)
                LevyWalk_Turn                        = 0;     // Stop the navigation
                LevyWalk_TurnPrevious                = 0;
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
            }
            else
            {
                if (LevyWalk_IsTheRoachConfined == true)
                {
                    // Confine the roach in the first target
                    LevyWalk_Target_Current[0] = LevyWalk_Target[0];
                    LevyWalk_Target_Current[1] = LevyWalk_Target[1];
                }
                LevyWalk_IsReached = false; // The LevyWalk_IsReached here is just a variable for communication purpose (its logical correction will be tested later)
                LevyWalk_NavigateTowardTarget();
            }
        }

        // ---------------------- INITIATION AND HALTING OF ELECTRICAL STIMULUS --------------------------//
        // The stimulating side and stimulus's parameters will be decided by the variables "LevyWalk_Turn"
        LevyWalk_Stimulation(LevyWalk_Turn);
        LevyWalk_TargetToTest[0] = LevyWalk_Target_Current[0];
        LevyWalk_TargetToTest[1] = LevyWalk_Target_Current[1];
        // Testing = 0.0; // => This line is used for debugging purpose
        // Note: Actually, I used to think that right after a target is generated the navigation function should be called;
        //       however, the program should only handle one navigate step at a time => The navigation will be done in the
        //       next interval
        // ---------------------- START THE TIMER TO COUNT FOR THE NEXT EXECUTION OF LEVYWALK --------------- //
        LevyWalk_ControlCount   = 0;
        LevyWalk_TimeForExecute = false;
        // Note: In the previous version, when the navigation processed is done on GUI, there was no this timer.
        //       This timer is used to handle the (on-board) control rate of the navigation process. Notice that the control rate is different with the communication rate
        //       between the GUI (Central) and the wireless board. At default, the communication rate is set at >= 30 ms to avoid overloading the central board.
    }
}

void LevyWalk_NavigateTowardTarget(void)
{
   // Explain: When the insect has not reached the target so we have to navigate it based on the following process
   // ********************* Handler of long steering stimulus
   // Note: The handler of long stimulus is modified a bit. The freewalking will be allowed before the forward walking.
   //       This modification is used to reduce the number of consecutive stimulation.
   //       In addition, after the forward walking, the insect will be allow to move freely for awhile
   if (LevyWalk_IsLongStimulusBeingChecked)
   {
       // Note: The variable LevyWalk_IsLongStimulusBeingChecked is enabled when a steering stimulation is triggered. It indicates that we should start checking if the steering stimulus
       //       is longer than a certain threshold which, as we believe, point out an presence of the obstacle collision.
       // Note: Of course, such obstacle collision indicator is not correct (ex. when the cockroach simply just does not want to turn, the steering stimulus will be long also).
       //       More investigations and researches should be conducted to overcome this problem.
       if (!LevyWalk_IsLongStimulusHandleStarted) // This variable is LevyWalk_IsLongStimulusHandleStarted flipped when the stimulus is longer than a pre-defined threshold
       {
           // Explain: When the steering stimulus is longer than an threshold, we firstly trigger the forward motion then let the cockroach walk freely. The durations for this forward
           //          and free walk motion are pre-determined.
           if (LevyWalk_TimeofStimulusForSteering >= LevyWalk_ThresholdOfLongStimulus) // There is a long stimulus => Handle now
           {
               // Note: In the very 1st version, we use temporal variable - long stimulus - as an indicator to release the stimulation
               //       In this version, we will use angular speed to do that. For the purpose of time saving, the program structure will
               //       be kept, the new code will be inputed to make a suitable adjustment
               // Speed checking
               // Explain: If the cockroach does not turn when being stimulated, we release the stimulation then trigger forward motion

               // 201005: All Speeds Are Calculated
               LevyWalk_AllSpeedCalculation();

               if (LevyWalk_SpeedFlag_Angular == true)
               {
                   if (fabs(LevyWalk_AngularVelocity) <= LevyWalk_ThresholdOfAngularVelocity)
                   {
                       LevyWalk_NumberAngularSpeed++;
                       // This if-statement is similar with the situation of a long stimulation
                       LevyWalk_Turn                        = 0; // Free  walking is allowed
                       LevyWalk_TimeafterLongStimulus       = 0; // Timer to control the period including forward motion and free walking
                       LevyWalk_IsLongStimulusHandleStarted = true;
                       LevyWalk_IsNavigated                 = false; // No more navigation process when a long stimulus is recorded
                   }
               }
               else
               {
                   LevyWalk_AngularVelocity = NAN;
               }
               LevyWalk_TimeofStimulusForSteering = 0; // To reset the variable and make a new loop of speed checking
               LevyWalk_ThresholdOfLongStimulus = LevyWalk_DurationToCheckSpeed_Stimulation; // The roach is let some time to reaction ("LevyWalk_ReactionTime") before its speed is checked. This line is to remove that period and let the periodic speed check happens
           }
       }
       else
       {
           // Explain: This "else" statement is executed when the variable LevyWalk_IsLongStimulusHandleStarted become true which means a long steering stimulus is already recorded.
           if (LevyWalk_TimeafterLongStimulus >= LevyWalk_ThresholdOfLongStimulusFreeWalk)
           {
               // Explain: To handle a long steering stimulus, firstly the cockroach is stimulated to move forward (two cerci are stimulated). The statement "LevyWalk_TimeafterLongStimulus >= LevyWalk_ThresholdOfLongStimulusForward"
               //          indicates that this cercal stimulation should be finished now (it is enough time spent for the forward stimulation).
               if (LevyWalk_UseEscapeMode == true)
               {
                   LevyWalk_Turn = 3; // Forward motion is started
               }
               else
               {
                   LevyWalk_Turn = 0;
               }
               if (LevyWalk_TimeafterLongStimulus >= (LevyWalk_ThresholdOfLongStimulusForward + LevyWalk_ThresholdOfLongStimulusFreeWalk))
               {
                   LevyWalk_Turn = 0; // Free walking is allowed another time
                   if (LevyWalk_TimeafterLongStimulus >= LevyWalk_ThresholdOfLongStimulusForward + LevyWalk_ThresholdOfLongStimulusFreeWalk + LevyWalk_ThresholdofFinalPartForLongStimulus)
                   {
                       // Explain: After the free walking, the handler for a long stimulus is completed.
                       //         Now the two following variables are assign as false so in the next control interval, the process can go to the navigation process
                       LevyWalk_IsLongStimulusBeingChecked  = false;
                       LevyWalk_IsLongStimulusHandleStarted = false;
                   }
                   else
                   {
                      // Explain: This "else" is to make the program is clear to read. When the time spending for handling a long steering stimulus has not passed, we are still keeping the two following variables be true.
                      LevyWalk_IsLongStimulusBeingChecked  = true;
                      LevyWalk_IsLongStimulusHandleStarted = true;
                   }
               }
               else
               {
                   // Explain: This "else" is to make the program is clear to read. When the time spending for handling a long steering stimulus has not passed, we are still keeping the two following variables be true.
                   LevyWalk_IsLongStimulusBeingChecked  = true;
                   LevyWalk_IsLongStimulusHandleStarted = true;
               }
           }
           else
           {
               // Explain: This "else" is used to make the program is clear to read. If the variable LevyWalk_TimeafterLongStimulus indicates that it still not exceed the duration we should spend for forward stimulation,
               //          we should keep the LevyWalk_Turn = 0
               LevyWalk_Turn = 0;
           }
           LevyWalk_IsNavigated = false; // Ignore the navigation process (The navigation process is the process in which the cockroach position is used to calculate the relative angle between its orientation and target)
       }
   }
   // ********************* Handler of forward motion
   // Note: What is this handler?
   //       This handler is used when: (1) the angle between the cockroach's orientation and the target is smaller than a certain threshold and (2) the forward velocity of the cockroach smaller than a certain threshold
   //                                  which indicates the cockroach is standing still
   // Explain: We have this handler because we want to take advantage of the cockroach own-will motion. This handler will be much simpler if we just assume the cockroach always walk or we always stimulate the forward motion
   //          when the relative angle is smaller than a pre-defined threshold
   if (LevyWalk_IsForwardTriggeredAlready) // The forward motion has been already triggered ((1) and (2) are both correct)
   {
       if (LevyWalk_TimeafterForwardStimulus >= LevyWalk_ThresholdOfTimeForwardWhenSpeedIsSmall)
       {
           // Explain: If the time spending for the forward stimulation exceed the pre-defined threshold, we turn off the stimulation and let the roach move freely
           LevyWalk_Turn = 0;
           if (LevyWalk_TimeafterForwardStimulus >= (LevyWalk_ThresholdOfTimeForwardWhenSpeedIsSmall + LevyWalk_ThresholdOfTimeFreeWalkWhenSpeedIsSmall))
           {
               // Explain: If the time spending for the free walking is over, we disable the handler and let the navigation process to happens in the next control interval
               LevyWalk_IsForwardTriggeredAlready  = false;
           }
       }
       else
       {
           if (LevyWalk_UseEscapeMode == true)
           {
               LevyWalk_Turn = 3;
           }
           else
           {
               LevyWalk_Turn = 0;
           }
           LevyWalk_IsForwardTriggeredAlready = true;
       }
       LevyWalk_ShouldCheckTheForwardSpeed = false; // When the forward handler is happens, the timer to manipulate forward speed checking is disabled.
       LevyWalk_IsNavigated                = false; // The navigation process is skipped when handling the forward motion
   }
   // ********************* Navigation process
   if (LevyWalk_IsNavigated)
   {
       // It seems like the roach rotates about its tail when being stimulated
       LevyWalk_Navigation(LevyWalk_RobotHead, LevyWalk_RobotTail, LevyWalk_Target_Current);
       // The following line of code could be enable if the assumption the roach rotating about its middle point (when being stimulated) is made
       // LevyWalk_Navigation(LevyWalk_RobotHead, LevyWalk_RobotBody, LevyWalk_Target);
   }
   LevyWalk_IsNavigated = true; // This line of code is only to make sure the navigation is always ready for the next control interval. It will be disable (in the next control interval) depending on the two handlers
}
void LevyWalk_Navigation(float *LevyWalk_CurrentHead, float *LevyWalk_CurrentPostion, float *LevyWalk_CurrentTarget)
{
    // --------------------- Note for the navigation process --------------------- //
    // There are basically two approaches for this navigation process:
    // 1st - Obstacle detection and avoidance is excluded
    // 2nd - Obstacle detection and avoidance is included
    // This code will deal with the second approach => The more difficult approach. So we have the navigation rules are:
    // 1 - If angle > Threshold => Steer the roach. If the steering stimulus > Certain period => Halt the stimulus and
    //     trigger the cercal stimulation
    // 2 - If angle < Threshold => There are two approaches:
    //     2.1 - Let the roach move freely
    //     2.2 - Let the roach move freely, meanwhile velocity will be monitored. If Velocity < Threshold => Cercal stimulation
    //     2.3 - Trigger cercal stimulation
    // This code will choose the approach 2.2
    float   VectorPosition_Head[3]   = {0.0, 0.0, 0.0};
    float   VectorPosition_Target[3] = {0.0, 0.0, 0.0};
    float   Angle = 0.0;
    float   AngleToCompare = 0.0;
    int32_t Turn = 0;
    // Calculate Vector Position-Head
    VectorPosition_Head[0] = LevyWalk_CurrentHead[0] - LevyWalk_CurrentPostion[0];
    VectorPosition_Head[1] = LevyWalk_CurrentHead[1] - LevyWalk_CurrentPostion[1];
    // Calculate Vector Position-Target
    VectorPosition_Target[0] = LevyWalk_CurrentTarget[0] - LevyWalk_CurrentPostion[0];
    VectorPosition_Target[1] = LevyWalk_CurrentTarget[1] - LevyWalk_CurrentPostion[1];
    // Calculate the angle between two vector => To steering decision
    Angle = LevyWalk_DotProduct(VectorPosition_Head, VectorPosition_Target)/(LevyWalk_Norm(VectorPosition_Head)*LevyWalk_Norm(VectorPosition_Target));
    Angle = acos(Angle);
    Angle = Angle*(180.0/L_PI);
    AngleToCompare = LevyWalk_AngleThreshold;
    // Steering decision
    if (Angle >= AngleToCompare)
    {
        // Steering to reduce the angle value
        Turn = LevyWalk_Steering(VectorPosition_Head, VectorPosition_Target);
        if (Turn != LevyWalk_Turn) // Have to change the stimulation; otherwise the stimulation will be held
        {
            // Steering to the left side  => Turn = 1;
            // Steering to the right side => Turn = 2;
            LevyWalk_Turn = Turn;
            LevyWalk_TurnPrevious = LevyWalk_Turn;
            // These two variables are used to handle the long stimulus (presence of obstacle)
            LevyWalk_TimeofStimulusForSteering   = 0;
            LevyWalk_IsLongStimulusBeingChecked  = true;
            LevyWalk_IsLongStimulusHandleStarted = false;
            LevyWalk_ThresholdOfLongStimulus = LevyWalk_DurationToCheckSpeed_Stimulation + LevyWalk_ReactionTime; // We let the cockroach some time to react before periodically measure its speed
        }
        // When we decide to steer the roach, the variables regarding the forward motion trigger will be disabled
        LevyWalk_IsForwardTriggeredAlready  = false;
        LevyWalk_ShouldCheckTheForwardSpeed = false;
    }
    else
    {
        LevyWalk_IsLongStimulusBeingChecked = false; // To make sure that that when the angle is smaller than threshold, the program does not fall into the handler of steering
        // Explain: There are three approaches when the angle is smaller than the pre-defined threshold. The approach used in this code will be 2.2. The forward velocity calculation is conducted based on the locational data collected using Vicon
        if (LevyWalk_ShouldCheckTheForwardSpeed == false)
        {
            // Explain: The following steps are used to handle the forward motion when the angle between the roach's orientation and target smaller than a certain threshold
            // Step 1: - Turn off the navigation
            //         - Turn the variable LevyWalk_ShouldCheckTheForwardSpeed to true so that the velocity will be checked periodically
            LevyWalk_Turn                               = 0;    // Turn off stimulation
            LevyWalk_TimeafterAngleSmallerThanThreshold = 0;    // Reset the timer that periodically check the velocity
            LevyWalk_ShouldCheckTheForwardSpeed         = true; // This variable enable allow the above timer to work (See StimulationTask.c)
            LevyWalk_IsForwardTriggeredAlready          = false;
            LevyWalk_DurationToCheckForwardSpeed        = LevyWalk_DurationToCheckSpeed_FreeWalk;
            // Explain: Right after the cockroach's angle to the target is smaller than the threshold, we will:
            //          - Turn off the stimulation and let the roach move freely for a while
            //          - This part is to reduce the number of stimulation which cause the roach being overstimulated
            if ((LevyWalk_EnableTheFreeWalkingAfterStimulation == true) && ((LevyWalk_TurnPrevious == 2) || (LevyWalk_TurnPrevious == 1)))
            {
                LevyWalk_DurationToCheckForwardSpeed = LevyWalk_DurationToCheckSpeed_FreeWalk + LevyWalk_ThresholdForFreeWalkAfterSteering;
            }
            LevyWalk_TurnPrevious = LevyWalk_Turn;
        }
        else
        {
            if (LevyWalk_TimeafterAngleSmallerThanThreshold >= LevyWalk_DurationToCheckForwardSpeed)
            {
                LevyWalk_DurationToCheckForwardSpeed = LevyWalk_DurationToCheckSpeed_FreeWalk;
                // Explain: The linear speed is checked here right here
                // There is one point we should notice here, this speed check is done when angle is smaller than the threshold.
                // That means, the cockroach is facing the target, therefore, we should only check the linear velocity,
                // If the cockroach turning in this period, when its angle become bigger than the angular threshold, it will be steered.
                // Therefore, we do not check the angular velocity

                // 201005: All Speeds Are Calculated
                LevyWalk_AllSpeedCalculation();

                if (LevyWalk_SpeedFlag_Linear == false)
                {
                    LevyWalk_ForwardVelocity = NAN;
                    LevyWalk_TimeafterAngleSmallerThanThreshold = 0;
                    LevyWalk_ShouldCheckTheForwardSpeed         = true; // This variable enable allow the above timer to work (See StimulationTask.c)
                    LevyWalk_Turn = 0;
                    LevyWalk_IsForwardTriggeredAlready = false;
                }
                else
                {
                    if (LevyWalk_ForwardVelocity <= LevyWalk_ThresholdOfForwardVelocity)
                    {
                        LevyWalk_NumberLinearSpeed++;
                        // Explain: If the forward velocity is smaller than a certain threshold, we stop the periodic checking, turn the variable LevyWalk_IsForwardTriggeredAlready to true to enable the handler
                        LevyWalk_ShouldCheckTheForwardSpeed = false; // When we have to handle the forward motion, we stop the periodic velocity measurement
                        if (LevyWalk_UseEscapeMode == true)
                        {
                            LevyWalk_Turn = 3;
                        }
                        else
                        {
                            LevyWalk_Turn = 0;
                        }
                        LevyWalk_TimeafterForwardStimulus   = 0;
                        LevyWalk_IsForwardTriggeredAlready  = true;
                    }
                    else
                    {
                        LevyWalk_TimeafterAngleSmallerThanThreshold = 0;
                        LevyWalk_ShouldCheckTheForwardSpeed         = true; // This variable enable allow the above timer to work (See StimulationTask.c)
                        LevyWalk_Turn = 0;
                        LevyWalk_IsForwardTriggeredAlready = false;
                    }
                }
            }
        }
        // Explain: The following lines are to make sure the handler of long steering stimulus will not affect the handler of forward motion checking
        LevyWalk_IsLongStimulusBeingChecked  = false;
        LevyWalk_IsLongStimulusHandleStarted = false;
    }
    return;
}
int32_t LevyWalk_Steering(float *Position_Head, float *Position_Target)
{
    float TurningDirection = 0.0;
    int32_t Turn = 0;
    TurningDirection = LevyWalk_CrossProduct(Position_Target, Position_Head);
    if (TurningDirection > 0)
    {
        Turn = 2; // Steering to right side
    }
    else
    {
        Turn = 1; // Steering to left side
    }
    return Turn;
}

float LevyWalk_DistanceCalculation(float *A, float *B)
{
    float result = 0.0;
    result = sqrt(pow(A[0] - B[0], 2) + pow(A[1] - B[1], 2));
    return result;
}
float LevyWalk_CrossProduct(float *A, float *B)
{
    // This Cross Product is used for two 3x1 vectors
    // A x B = (a2b3  -   a3b2,     a3b1   -   a1b3,     a1b2   -   a2b1)
    // Only the third value is taken into account => To decide which direction the cockroach should turn toward
    float result = 0.0;
    result = A[0]*B[1] - A[1]*B[0];
    return result;
}
float LevyWalk_DotProduct(float *A, float *B)
{
    // This Dot Product is used for two 3x1 vectors
    float result = 0.0;
    result = A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
    return result;
}
float LevyWalk_Norm(float *A)
{
    // This Norm function is used for one 3x1 vector
    float result = 0.0;
    result = sqrt(pow(A[0], 2) +  pow(A[1], 2) +  pow(A[2], 2));
    return result;
}
bool LevyWalk_CompareFloat(float f1, float f2)
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

void  LevyWalk_AllSpeedCalculation(void)
{
    // --------------------------------- Angular Speed
    LevyWalk_SpeedFlag_Angular = false; // Initially set the speed flag is false to say there is not enough data points to accurately calculate speed
    switch (LevyWalk_AngularSpeedMethod)
    {
    case 1:
        LevyWalk_AngularVelocity = LevyWalk_AngularVelocityCalculation_Sign();
        break;
    case 2:
        LevyWalk_AngularVelocity = LevyWalk_AngularVelocityCalculation_Version2();
        break;
    }
    LevyWalk_AngularVelocity_Vicon   = LevyWalk_AngularVelocity;
    LevyWalk_SpeedFlag_Angular_Vicon = LevyWalk_SpeedFlag_Angular;

    // 200929 - Place Long Angular Speed Here - IMU
    // We use Long's IMU for the speed calculation
    LevyWalk_SpeedFlag_Angular     = true;
    LevyWalk_AngularVelocity       = fabs(omega*(180.0/L_PI)); // To convert from rad/s to degree/s
    LevyWalk_AngularVelocity_IMU   = LevyWalk_AngularVelocity;
    LevyWalk_SpeedFlag_Angular_IMU = LevyWalk_SpeedFlag_Angular;

    // The program allows user to select the speed estimation method
    if (LevyWalk_UseIMU_AngularSpeed == true)
    {
        LevyWalk_AngularVelocity   = LevyWalk_AngularVelocity_IMU;
        LevyWalk_SpeedFlag_Angular = LevyWalk_SpeedFlag_Angular_IMU;
    }
    else
    {
        LevyWalk_AngularVelocity   = LevyWalk_AngularVelocity_Vicon;
        LevyWalk_SpeedFlag_Angular = LevyWalk_SpeedFlag_Angular_Vicon;
    }

    // ----------------------------------- Forward Speed
    LevyWalk_SpeedFlag_Linear  = false; // Initially set the speed flag is false to say there is not enough data points to accurately calculate speed
    LevyWalk_ForwardVelocity   = LevyWalk_ForwardVelocityCalculation_Sign();
    LevyWalk_ForwardVelocity_Vicon  = LevyWalk_ForwardVelocity;
    LevyWalk_SpeedFlag_Linear_Vicon = LevyWalk_SpeedFlag_Linear;

    // If the velocity is undefined => Freewalk is allowed (because we are not sure how should we stimulate the roach)
    // 200929 - Place Long Linear Speed Here - IMU
    LevyWalk_SpeedFlag_Linear = true;
    LevyWalk_ForwardVelocity  = fabs(absolutespeed)*1000; // To convert from m/s to mm/s
    LevyWalk_ForwardVelocity_IMU  = LevyWalk_ForwardVelocity;
    LevyWalk_SpeedFlag_Linear_IMU = LevyWalk_SpeedFlag_Linear;

    // The program allows user to select the speed estimation method
    if (LevyWalk_UseIMU_LinearSpeed == true)
    {
        LevyWalk_ForwardVelocity  = LevyWalk_ForwardVelocity_IMU;
        LevyWalk_SpeedFlag_Linear = LevyWalk_SpeedFlag_Linear_IMU;
    }
    else
    {
        LevyWalk_ForwardVelocity   = LevyWalk_ForwardVelocity_Vicon;
        LevyWalk_SpeedFlag_Linear = LevyWalk_SpeedFlag_Linear_Vicon;
    }

    return;
}

float LevyWalk_ForwardVelocityCalculation(void)
{
    // Sign of Linear and Angular speeds calculated here is not taken into account
    // Moving average method is used to calculate forward velocity
    // The calculation is explained as follow:
    // - Step1: From the current location (SpeedCount - 1) to location SpeedCount (1 full round of the array[*]), we calculate all velocities
    // - Step2: The sum of all velocities within the Window time (LevyWalk_TimeStoreToCalculateSpeed) is determined
    // - Step3: Dividing the sum by number of elements in the Window (Moving average), we have the velocity representing the speed of the current location
    // If there is not enough data points, the SpeedFlag will be assigned as false, this assignment would make the system wait for the next time-out to calculate the speed
    // Note: The reason of [*] is that there could be a chance the array has been full in previous loops; the windows, thus, needs to cover the last elements
    float ForwardVelocity = 0.0;
    float ForwardVelocity_TempX, ForwardVelocity_TempY, ForwardVelocity_Temp;
    float Time_Delta;
    int32_t ForwardVelocity_i, SubVariable_i, SubVariable_iplusone;
    uint32_t Count = 0;
    uint32_t CurrentLocation;
    // Current position inside the array of the current frame
    if (LevyWalk_SpeedCount == 0)
    {
        CurrentLocation = 299;
    }
    else
    {
        CurrentLocation = LevyWalk_SpeedCount - 1;
    }
    // First loop: From the current location to the 0 position of the array
    for (ForwardVelocity_i = (int32_t)CurrentLocation - 1; ForwardVelocity_i >= 0; ForwardVelocity_i--)
    {
        if (LevyWalk_SpeedArray_T[ForwardVelocity_i] != 0)
        {
            Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[ForwardVelocity_i]); // 0.01 is the sampling rate of Vicon
            if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
            {
                Count++;
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[ForwardVelocity_i + 1] - LevyWalk_SpeedArray_T[ForwardVelocity_i]); // 0.01 is the sampling rate of Vicon
                ForwardVelocity_TempX =   LevyWalk_SpeedArray_X[ForwardVelocity_i + 1] - LevyWalk_SpeedArray_X[ForwardVelocity_i];
                ForwardVelocity_TempY =   LevyWalk_SpeedArray_Y[ForwardVelocity_i + 1] - LevyWalk_SpeedArray_Y[ForwardVelocity_i];
                ForwardVelocity_Temp  =   sqrt(pow(ForwardVelocity_TempX, 2) +  pow(ForwardVelocity_TempY, 2));
                ForwardVelocity_Temp  =   ForwardVelocity_Temp/Time_Delta;
                ForwardVelocity       =   ForwardVelocity + ForwardVelocity_Temp;
            }
            else
            {
                if (Count > 0)
                {
                    // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                    ForwardVelocity = ForwardVelocity/((float)Count);
                    LevyWalk_SpeedFlag_Linear = true;
                }
                else
                {
                    LevyWalk_SpeedFlag_Linear = false;
                }
                break;
            }
        }
    }
    // Second loop: From the 0 position of the array to the other side of the array
    // This if-statement means that the windows may need to cover the last elements to get fulfilled
    if ( LevyWalk_SpeedFlag_Linear == false)
    {
        if (LevyWalk_SpeedArray_T[ForwardVelocity_i] != 0)
        {
            for (ForwardVelocity_i = 299; ForwardVelocity_i > CurrentLocation; ForwardVelocity_i--)
            {
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[ForwardVelocity_i]); // 0.01 is the sampling rate of Vicon
                if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
                {
                    Count++;
                    if (ForwardVelocity_i == 299)
                    {
                        SubVariable_iplusone = 0;
                        SubVariable_i        = ForwardVelocity_i;
                    }
                    else
                    {
                        SubVariable_iplusone = ForwardVelocity_i + 1;
                        SubVariable_i        = ForwardVelocity_i;
                    }
                    Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[SubVariable_iplusone] - LevyWalk_SpeedArray_T[SubVariable_i]); // 0.01 is the sampling rate of Vicon
                    ForwardVelocity_TempX =   LevyWalk_SpeedArray_X[SubVariable_iplusone] - LevyWalk_SpeedArray_X[SubVariable_i];
                    ForwardVelocity_TempY =   LevyWalk_SpeedArray_Y[SubVariable_iplusone] - LevyWalk_SpeedArray_Y[SubVariable_i];
                    ForwardVelocity_Temp  =   sqrt(pow(ForwardVelocity_TempX, 2) +  pow(ForwardVelocity_TempY, 2));
                    ForwardVelocity_Temp  =   ForwardVelocity_Temp/Time_Delta;
                    ForwardVelocity       =   ForwardVelocity + ForwardVelocity_Temp;
                }
                else
                {
                    if (Count > 0)
                    {
                        // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                        ForwardVelocity = ForwardVelocity/((float)Count);
                        LevyWalk_SpeedFlag_Linear = true;
                    }
                    else
                    {
                        LevyWalk_SpeedFlag_Linear = false;
                    }
                    break;
                }
            }
        }
    }
    if ((isinf(ForwardVelocity)) || (isinf(-ForwardVelocity)) || (isnan(ForwardVelocity)))
    {
        LevyWalk_SpeedFlag_Linear = false;
    }
    return ForwardVelocity;
}
float LevyWalk_ForwardVelocityCalculation_Sign(void)
{
    // Previous version: the speed is calculated by dist/(time interval). We are using average speed within a time window => Fluctuation might cause noise and
    // return an wrongly (higher) estimated speed. In this version: Speed = sqrt(Vx^2 + Vy^2). Because sign is taken in to account for Vx and Vy => We might be able to
    // remove noise caused by fluctuation.
    // The following are the description of the previous calculation
    //      Moving average method is used to calculate forward velocity
    //      The calculation is explained as follow:
    //      - Step1: From the current location (SpeedCount - 1) to location SpeedCount (1 full round of the array[*]), we calculate all velocities
    //      - Step2: The sum of all velocities within the Window time (LevyWalk_TimeStoreToCalculateSpeed) is determined
    //      - Step3: Dividing the sum by number of elements in the Window (Moving average), we have the velocity representing the speed of the current location
    //      If there is not enough data points, the SpeedFlag will be assigned as false, this assignment would make the system wait for the next time-out to calculate the speed
    //      Note: The reason of [*] is that there could be a chance the array has been full in previous loops; the windows, thus, needs to cover the last elements
    float ForwardVelocity = 0.0;
    float ForwardVelocity_TempX, ForwardVelocity_TempY;
    float ForwardVelocity_X = 0.0;
    float ForwardVelocity_Y = 0.0;
    float Time_Delta;
    int32_t ForwardVelocity_i, SubVariable_i, SubVariable_iplusone;
    uint32_t Count = 0;
    uint32_t CurrentLocation;
    // Current position inside the array of the current frame
    if (LevyWalk_SpeedCount == 0)
    {
        CurrentLocation = 299;
    }
    else
    {
        CurrentLocation = LevyWalk_SpeedCount - 1;
    }
    // First loop: From the current location to the 0 position of the array
    for (ForwardVelocity_i = (int32_t)CurrentLocation - 1; ForwardVelocity_i >= 0; ForwardVelocity_i--)
    {
        if (LevyWalk_SpeedArray_T[ForwardVelocity_i] != 0)
        {
            Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[ForwardVelocity_i]); // 0.01 is the sampling rate of Vicon
            if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
            {
                Count++;
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[ForwardVelocity_i + 1] - LevyWalk_SpeedArray_T[ForwardVelocity_i]); // 0.01 is the sampling rate of Vicon
                ForwardVelocity_TempX =   LevyWalk_SpeedArray_X[ForwardVelocity_i + 1] - LevyWalk_SpeedArray_X[ForwardVelocity_i];
                ForwardVelocity_TempY =   LevyWalk_SpeedArray_Y[ForwardVelocity_i + 1] - LevyWalk_SpeedArray_Y[ForwardVelocity_i];
                // Temporary Vx and Vy
                ForwardVelocity_TempX =   ForwardVelocity_TempX/Time_Delta;
                ForwardVelocity_TempY =   ForwardVelocity_TempY/Time_Delta;
                // Sum of Vx and Vy
                ForwardVelocity_X = ForwardVelocity_X + ForwardVelocity_TempX;
                ForwardVelocity_Y = ForwardVelocity_Y + ForwardVelocity_TempY;
            }
            else
            {
                if (Count > 0)
                {
                    // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                    ForwardVelocity_X = ForwardVelocity_X/((float)Count);
                    ForwardVelocity_Y = ForwardVelocity_Y/((float)Count);
                    ForwardVelocity   = sqrt(pow(ForwardVelocity_X, 2) +  pow(ForwardVelocity_Y, 2));
                    LevyWalk_SpeedFlag_Linear = true;
                }
                else
                {
                    LevyWalk_SpeedFlag_Linear = false;
                    ForwardVelocity = NAN;
                }
                break;
            }
        }
    }
    // Second loop: From the 0 position of the array to the other side of the array
    // This if-statement means that the windows may need to cover the last elements to get fulfilled
    if ( LevyWalk_SpeedFlag_Linear == false)
    {
        if (LevyWalk_SpeedArray_T[ForwardVelocity_i] != 0)
        {
            for (ForwardVelocity_i = 299; ForwardVelocity_i > CurrentLocation; ForwardVelocity_i--)
            {
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[ForwardVelocity_i]); // 0.01 is the sampling rate of Vicon
                if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
                {
                    Count++;
                    if (ForwardVelocity_i == 299)
                    {
                        SubVariable_iplusone = 0;
                        SubVariable_i        = ForwardVelocity_i;
                    }
                    else
                    {
                        SubVariable_iplusone = ForwardVelocity_i + 1;
                        SubVariable_i        = ForwardVelocity_i;
                    }
                    Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[SubVariable_iplusone] - LevyWalk_SpeedArray_T[SubVariable_i]); // 0.01 is the sampling rate of Vicon
                    ForwardVelocity_TempX =   LevyWalk_SpeedArray_X[SubVariable_iplusone] - LevyWalk_SpeedArray_X[SubVariable_i];
                    ForwardVelocity_TempY =   LevyWalk_SpeedArray_Y[SubVariable_iplusone] - LevyWalk_SpeedArray_Y[SubVariable_i];
                    // Temporary Vx and Vy
                    ForwardVelocity_TempX =   ForwardVelocity_TempX/Time_Delta;
                    ForwardVelocity_TempY =   ForwardVelocity_TempY/Time_Delta;
                    // Sum of Vx and Vy
                    ForwardVelocity_X = ForwardVelocity_X + ForwardVelocity_TempX;
                    ForwardVelocity_Y = ForwardVelocity_Y + ForwardVelocity_TempY;
                }
                else
                {
                    if (Count > 0)
                    {
                        // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                        ForwardVelocity_X = ForwardVelocity_X/((float)Count);
                        ForwardVelocity_Y = ForwardVelocity_Y/((float)Count);
                        ForwardVelocity   = sqrt(pow(ForwardVelocity_X, 2) +  pow(ForwardVelocity_Y, 2));
                        LevyWalk_SpeedFlag_Linear = true;
                    }
                    else
                    {
                        LevyWalk_SpeedFlag_Linear = false;
                        ForwardVelocity = NAN;
                    }
                    break;
                }
            }
        }
    }
    if ((isinf(ForwardVelocity_X)) || (isinf(-ForwardVelocity_X)) || (isnan(ForwardVelocity_X) || (isinf(ForwardVelocity_Y)) || (isinf(-ForwardVelocity_Y)) || (isnan(ForwardVelocity_Y))))
    {
        LevyWalk_SpeedFlag_Linear = false;
        ForwardVelocity = NAN;
    }
    return ForwardVelocity;
}
float LevyWalk_AngularVelocityCalculation(void)
{
    // Read description as Version 2 to see the differences
    // Sign of Linear and Angular speeds calculated here is not taken into account
    // Moving average method is used to calculate angular velocity
    float AngularVelocity = 0.0;
    float AngularVelocity_HeadX1, AngularVelocity_HeadY1, AngularVelocity_TailX1, AngularVelocity_TailY1; // AngularVelocity_TailZ1 AngularVelocity_HeadZ1;
    float AngularVelocity_HeadX2, AngularVelocity_HeadY2, AngularVelocity_TailX2, AngularVelocity_TailY2; // AngularVelocity_TailZ2 AngularVelocity_HeadZ2;
    float AngularVelocity_Temp;
    float Time_Delta;
    int32_t AngularVelocity_i, SubVariable_i, SubVariable_iplusone;
    uint32_t Count = 0;
    float    VectorPosition_Head[3]   = {0.0, 0.0, 0.0};
    float    VectorPosition_Target[3] = {0.0, 0.0, 0.0};
    float    Angle;
    uint32_t CurrentLocation;
    // Current position inside the array of the current frame
    if (LevyWalk_SpeedCount == 0)
    {
        CurrentLocation = 299;
    }
    else
    {
        CurrentLocation = LevyWalk_SpeedCount - 1;
    }
    // First loop: From the current location to the 0 position of the array
    for (AngularVelocity_i = (int32_t)CurrentLocation - 1; AngularVelocity_i >= 0; AngularVelocity_i--)
    {
        if (LevyWalk_SpeedArray_T[AngularVelocity_i] != 0)
        {
            Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
            if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
            {
                Count++;
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[AngularVelocity_i + 1] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
                // Head of the "current" frame
                AngularVelocity_HeadX1 = LevyWalk_SpeedArray_XHead[AngularVelocity_i + 1];
                AngularVelocity_HeadY1 = LevyWalk_SpeedArray_YHead[AngularVelocity_i + 1];
                //AngularVelocity_HeadZ1 = LevyWalk_SpeedArray_ZHead[AngularVelocity_i + 1];
                // Tail of the "current" frame
                AngularVelocity_TailX1 = LevyWalk_SpeedArray_X[AngularVelocity_i + 1];
                AngularVelocity_TailY1 = LevyWalk_SpeedArray_Y[AngularVelocity_i + 1];
                //AngularVelocity_TailZ1 = LevyWalk_SpeedArray_Z[AngularVelocity_i + 1];
                // Head of the "previous" frame
                AngularVelocity_HeadX2 = LevyWalk_SpeedArray_XHead[AngularVelocity_i];
                AngularVelocity_HeadY2 = LevyWalk_SpeedArray_YHead[AngularVelocity_i];
                //AngularVelocity_HeadZ2 = LevyWalk_SpeedArray_ZHead[AngularVelocity_i];
                // Tail of the "previous" frame
                AngularVelocity_TailX2 = LevyWalk_SpeedArray_X[AngularVelocity_i];
                AngularVelocity_TailY2 = LevyWalk_SpeedArray_Y[AngularVelocity_i];
                //AngularVelocity_TailZ2 = LevyWalk_SpeedArray_Z[AngularVelocity_i];
                // Make two positions have the same tail location
                AngularVelocity_HeadX2 = AngularVelocity_HeadX2 + (AngularVelocity_TailX1 - AngularVelocity_TailX2);
                AngularVelocity_HeadY2 = AngularVelocity_HeadY2 + (AngularVelocity_TailY1 - AngularVelocity_TailY2);
                //AngularVelocity_HeadZ2 = AngularVelocity_HeadZ2 + (AngularVelocity_TailZ1 - AngularVelocity_TailZ2);
                // The following lines is inherited from the angle calculation of the navigation program
                // Position = Tail1/Head = Head1/Target = Head2
                // Calculate Vector Position-Head
                VectorPosition_Head[0] = AngularVelocity_HeadX1 - AngularVelocity_TailX1;
                VectorPosition_Head[1] = AngularVelocity_HeadY1 - AngularVelocity_TailY1;
                // VectorPosition_Head[2] = AngularVelocity_HeadZ1 - AngularVelocity_TailZ1;
                // Calculate Vector Position-Target
                VectorPosition_Target[0] = AngularVelocity_HeadX2 - AngularVelocity_TailX1;
                VectorPosition_Target[1] = AngularVelocity_HeadY2 - AngularVelocity_TailY1;
                //VectorPosition_Target[2] = AngularVelocity_HeadZ2 - AngularVelocity_TailZ1;
                // Angle Calculation
                Angle = LevyWalk_DotProduct(VectorPosition_Head, VectorPosition_Target)/(LevyWalk_Norm(VectorPosition_Head)*LevyWalk_Norm(VectorPosition_Target));
                // The following if-statement handle cases in which above calculated > 1 and < -1 because of number transmission
                if (Angle > 1.0)
                {
                    Angle = 1.0;
                }
                else
                {
                    if (Angle < -1.0)
                    {
                        Angle = -1.0;
                    }
                }
                Angle = acos(Angle); // 0 to pi
                Angle = Angle*(180.0/L_PI);
                // Cumulation of the speed
                AngularVelocity_Temp  =   Angle/Time_Delta;
                AngularVelocity       =   AngularVelocity + AngularVelocity_Temp;
            }
            else
            {
                if (Count > 0)
                {
                    // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                    AngularVelocity = AngularVelocity/((float)Count);
                    LevyWalk_SpeedFlag_Angular = true;
                }
                else
                {
                    LevyWalk_SpeedFlag_Linear = false;
                }
                break;
            }
        }
    }
    // Second loop: From the 0 position of the array to the other side of the array
    // This if-statement means that the windows may need to cover the last elements to get fulfilled
    if (LevyWalk_SpeedFlag_Angular == false)
    {
        if (LevyWalk_SpeedArray_T[AngularVelocity_i] != 0)
        {
            for (AngularVelocity_i = 299; AngularVelocity_i > CurrentLocation; AngularVelocity_i--)
            {
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
                if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
                {
                    Count++;
                    if (AngularVelocity_i == 299)
                    {
                        SubVariable_iplusone = 0;
                        SubVariable_i        = AngularVelocity_i;
                    }
                    else
                    {
                        SubVariable_iplusone = AngularVelocity_i + 1;
                        SubVariable_i        = AngularVelocity_i;
                    }
                    Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[SubVariable_iplusone] - LevyWalk_SpeedArray_T[SubVariable_i]); // 0.01 is the sampling rate of Vicon
                    // Head of the "current" frame
                    AngularVelocity_HeadX1 = LevyWalk_SpeedArray_XHead[SubVariable_iplusone];
                    AngularVelocity_HeadY1 = LevyWalk_SpeedArray_YHead[SubVariable_iplusone];
                    //AngularVelocity_HeadZ1 = LevyWalk_SpeedArray_ZHead[SubVariable_iplusone];
                    // Tail of the "current" frame
                    AngularVelocity_TailX1 = LevyWalk_SpeedArray_X[SubVariable_iplusone];
                    AngularVelocity_TailY1 = LevyWalk_SpeedArray_Y[SubVariable_iplusone];
                    //AngularVelocity_TailZ1 = LevyWalk_SpeedArray_Z[SubVariable_iplusone];
                    // Head of the "previous" frame
                    AngularVelocity_HeadX2 = LevyWalk_SpeedArray_XHead[SubVariable_i];
                    AngularVelocity_HeadY2 = LevyWalk_SpeedArray_YHead[SubVariable_i];
                    //AngularVelocity_HeadZ2 = LevyWalk_SpeedArray_ZHead[SubVariable_i];
                    // Tail of the "previous" frame
                    AngularVelocity_TailX2 = LevyWalk_SpeedArray_X[SubVariable_i];
                    AngularVelocity_TailY2 = LevyWalk_SpeedArray_Y[SubVariable_i];
                    //AngularVelocity_TailZ2 = LevyWalk_SpeedArray_Z[SubVariable_i];
                    // Make two positions have the same tail location
                    AngularVelocity_HeadX2 = AngularVelocity_HeadX2 + (AngularVelocity_TailX1 - AngularVelocity_TailX2);
                    AngularVelocity_HeadY2 = AngularVelocity_HeadY2 + (AngularVelocity_TailY1 - AngularVelocity_TailY2);
                    //AngularVelocity_HeadZ2 = AngularVelocity_HeadZ2 + (AngularVelocity_TailZ1 - AngularVelocity_TailZ2);
                    // The following lines is inherited from the angle calculation of the navigation program
                    // Position = Tail1/Head = Head1/Target = Head2
                    // Calculate Vector Position-Head
                    VectorPosition_Head[0] = AngularVelocity_HeadX1 - AngularVelocity_TailX1;
                    VectorPosition_Head[1] = AngularVelocity_HeadY1 - AngularVelocity_TailY1;
                    //VectorPosition_Head[2] = AngularVelocity_HeadZ1 - AngularVelocity_TailZ1;
                    // Calculate Vector Position-Target
                    VectorPosition_Target[0] = AngularVelocity_HeadX2 - AngularVelocity_TailX1;
                    VectorPosition_Target[1] = AngularVelocity_HeadY2 - AngularVelocity_TailY1;
                    //VectorPosition_Target[2] = AngularVelocity_HeadZ2 - AngularVelocity_TailZ1;
                    // Angle Calculation
                    Angle = LevyWalk_DotProduct(VectorPosition_Head, VectorPosition_Target)/(LevyWalk_Norm(VectorPosition_Head)*LevyWalk_Norm(VectorPosition_Target));
                    // The following if-statement handle cases in which above calculated > 1 and < -1 because of number transmission
                    if (Angle > 1.0)
                    {
                        Angle = 1.0;
                    }
                    else
                    {
                        if (Angle < -1.0)
                        {
                            Angle = -1.0;
                        }
                    }
                    Angle = acos(Angle); // 0 to pi
                    Angle = Angle*(180.0/L_PI);
                    // Cumulation of the speed
                    AngularVelocity_Temp  =   Angle/Time_Delta;
                    AngularVelocity       =   AngularVelocity + AngularVelocity_Temp;
                }
                else
                {
                    if (Count > 0)
                    {
                        // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                        AngularVelocity = AngularVelocity/((float)Count);
                        LevyWalk_SpeedFlag_Angular = true;
                    }
                    else
                    {
                        LevyWalk_SpeedFlag_Linear = false;
                    }
                    break;
                }
            }
        }
    }
    if ((isinf(AngularVelocity)) || (isinf(-AngularVelocity)) || (isnan(AngularVelocity)))
    {
        LevyWalk_SpeedFlag_Angular = false;
    }
    return AngularVelocity;
}
float LevyWalk_AngularVelocityCalculation_Sign(void)
{
    // Sign is taken into account
    // Moving average method is used to calculate angular velocity
    float AngularVelocity = 0.0;
    float AngularVelocity_HeadX1, AngularVelocity_HeadY1, AngularVelocity_TailX1, AngularVelocity_TailY1; // AngularVelocity_TailZ1 AngularVelocity_HeadZ1;
    float AngularVelocity_HeadX2, AngularVelocity_HeadY2, AngularVelocity_TailX2, AngularVelocity_TailY2; // AngularVelocity_TailZ2 AngularVelocity_HeadZ2;
    float AngularVelocity_Temp;
    float Time_Delta;
    int32_t AngularVelocity_i, SubVariable_i, SubVariable_iplusone;
    uint32_t Count = 0;
    float    VectorPosition_Head[3]   = {0.0, 0.0, 0.0};
    float    VectorPosition_Target[3] = {0.0, 0.0, 0.0};
    float    Angle;
    float    Sign;
    uint32_t CurrentLocation;
    // Current position inside the array of the current frame
    if (LevyWalk_SpeedCount == 0)
    {
        CurrentLocation = 299;
    }
    else
    {
        CurrentLocation = LevyWalk_SpeedCount - 1;
    }
    // First loop: From the current location to the 0 position of the array
    for (AngularVelocity_i = (int32_t)CurrentLocation - 1; AngularVelocity_i >= 0; AngularVelocity_i--)
    {
        if (LevyWalk_SpeedArray_T[AngularVelocity_i] != 0)
        {
            Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
            if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
            {
                Count++;
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[AngularVelocity_i + 1] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
                // Head of the "current" frame
                AngularVelocity_HeadX1 = LevyWalk_SpeedArray_XHead[AngularVelocity_i + 1];
                AngularVelocity_HeadY1 = LevyWalk_SpeedArray_YHead[AngularVelocity_i + 1];
                //AngularVelocity_HeadZ1 = LevyWalk_SpeedArray_ZHead[AngularVelocity_i + 1];
                // Tail of the "current" frame
                AngularVelocity_TailX1 = LevyWalk_SpeedArray_X[AngularVelocity_i + 1];
                AngularVelocity_TailY1 = LevyWalk_SpeedArray_Y[AngularVelocity_i + 1];
                //AngularVelocity_TailZ1 = LevyWalk_SpeedArray_Z[AngularVelocity_i + 1];
                // Head of the "previous" frame
                AngularVelocity_HeadX2 = LevyWalk_SpeedArray_XHead[AngularVelocity_i];
                AngularVelocity_HeadY2 = LevyWalk_SpeedArray_YHead[AngularVelocity_i];
                //AngularVelocity_HeadZ2 = LevyWalk_SpeedArray_ZHead[AngularVelocity_i];
                // Tail of the "previous" frame
                AngularVelocity_TailX2 = LevyWalk_SpeedArray_X[AngularVelocity_i];
                AngularVelocity_TailY2 = LevyWalk_SpeedArray_Y[AngularVelocity_i];
                //AngularVelocity_TailZ2 = LevyWalk_SpeedArray_Z[AngularVelocity_i];
                // Make two positions have the same tail location
                AngularVelocity_HeadX2 = AngularVelocity_HeadX2 + (AngularVelocity_TailX1 - AngularVelocity_TailX2);
                AngularVelocity_HeadY2 = AngularVelocity_HeadY2 + (AngularVelocity_TailY1 - AngularVelocity_TailY2);
                //AngularVelocity_HeadZ2 = AngularVelocity_HeadZ2 + (AngularVelocity_TailZ1 - AngularVelocity_TailZ2);
                // The following lines is inherited from the angle calculation of the navigation program
                // Position = Tail1/Head = Head1/Target = Head2
                // Calculate Vector Position-Head
                VectorPosition_Head[0] = AngularVelocity_HeadX1 - AngularVelocity_TailX1;
                VectorPosition_Head[1] = AngularVelocity_HeadY1 - AngularVelocity_TailY1;
                // VectorPosition_Head[2] = AngularVelocity_HeadZ1 - AngularVelocity_TailZ1;
                // Calculate Vector Position-Target
                VectorPosition_Target[0] = AngularVelocity_HeadX2 - AngularVelocity_TailX1;
                VectorPosition_Target[1] = AngularVelocity_HeadY2 - AngularVelocity_TailY1;
                //VectorPosition_Target[2] = AngularVelocity_HeadZ2 - AngularVelocity_TailZ1;
                // Angle Calculation
                Angle = LevyWalk_DotProduct(VectorPosition_Head, VectorPosition_Target)/(LevyWalk_Norm(VectorPosition_Head)*LevyWalk_Norm(VectorPosition_Target));
                // Sign Calculation
                Sign  = LevyWalk_CrossProduct(VectorPosition_Head, VectorPosition_Target);
                if (Sign < 0)
                {
                    Sign = -1.0;
                }
                else
                {
                    Sign = 1.0;
                }
                // The following if-statement handle cases in which above calculated > 1 and < -1 because of number transmission
                if (Angle > 1.0)
                {
                    Angle = 1.0;
                }
                else
                {
                    if (Angle < -1.0)
                    {
                        Angle = -1.0;
                    }
                }
                Angle = acos(Angle); // 0 to pi
                Angle = Sign*Angle*(180.0/L_PI);
                // Cumulation of the speed
                AngularVelocity_Temp  =   Angle/Time_Delta;
                AngularVelocity       =   AngularVelocity + AngularVelocity_Temp;
            }
            else
            {
                if (Count > 0)
                {
                    // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                    AngularVelocity = AngularVelocity/((float)Count);
                    LevyWalk_SpeedFlag_Angular = true;
                }
                else
                {
                    LevyWalk_SpeedFlag_Linear = false;
                    AngularVelocity = NAN;
                }
                break;
            }
        }
    }
    // Second loop: From the 0 position of the array to the other side of the array
    // This if-statement means that the windows may need to cover the last elements to get fulfilled
    if (LevyWalk_SpeedFlag_Angular == false)
    {
        if (LevyWalk_SpeedArray_T[AngularVelocity_i] != 0)
        {
            for (AngularVelocity_i = 299; AngularVelocity_i > CurrentLocation; AngularVelocity_i--)
            {
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
                if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
                {
                    Count++;
                    if (AngularVelocity_i == 299)
                    {
                        SubVariable_iplusone = 0;
                        SubVariable_i        = AngularVelocity_i;
                    }
                    else
                    {
                        SubVariable_iplusone = AngularVelocity_i + 1;
                        SubVariable_i        = AngularVelocity_i;
                    }
                    Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[SubVariable_iplusone] - LevyWalk_SpeedArray_T[SubVariable_i]); // 0.01 is the sampling rate of Vicon
                    // Head of the "current" frame
                    AngularVelocity_HeadX1 = LevyWalk_SpeedArray_XHead[SubVariable_iplusone];
                    AngularVelocity_HeadY1 = LevyWalk_SpeedArray_YHead[SubVariable_iplusone];
                    //AngularVelocity_HeadZ1 = LevyWalk_SpeedArray_ZHead[SubVariable_iplusone];
                    // Tail of the "current" frame
                    AngularVelocity_TailX1 = LevyWalk_SpeedArray_X[SubVariable_iplusone];
                    AngularVelocity_TailY1 = LevyWalk_SpeedArray_Y[SubVariable_iplusone];
                    //AngularVelocity_TailZ1 = LevyWalk_SpeedArray_Z[SubVariable_iplusone];
                    // Head of the "previous" frame
                    AngularVelocity_HeadX2 = LevyWalk_SpeedArray_XHead[SubVariable_i];
                    AngularVelocity_HeadY2 = LevyWalk_SpeedArray_YHead[SubVariable_i];
                    //AngularVelocity_HeadZ2 = LevyWalk_SpeedArray_ZHead[SubVariable_i];
                    // Tail of the "previous" frame
                    AngularVelocity_TailX2 = LevyWalk_SpeedArray_X[SubVariable_i];
                    AngularVelocity_TailY2 = LevyWalk_SpeedArray_Y[SubVariable_i];
                    //AngularVelocity_TailZ2 = LevyWalk_SpeedArray_Z[SubVariable_i];
                    // Make two positions have the same tail location
                    AngularVelocity_HeadX2 = AngularVelocity_HeadX2 + (AngularVelocity_TailX1 - AngularVelocity_TailX2);
                    AngularVelocity_HeadY2 = AngularVelocity_HeadY2 + (AngularVelocity_TailY1 - AngularVelocity_TailY2);
                    //AngularVelocity_HeadZ2 = AngularVelocity_HeadZ2 + (AngularVelocity_TailZ1 - AngularVelocity_TailZ2);
                    // The following lines is inherited from the angle calculation of the navigation program
                    // Position = Tail1/Head = Head1/Target = Head2
                    // Calculate Vector Position-Head
                    VectorPosition_Head[0] = AngularVelocity_HeadX1 - AngularVelocity_TailX1;
                    VectorPosition_Head[1] = AngularVelocity_HeadY1 - AngularVelocity_TailY1;
                    //VectorPosition_Head[2] = AngularVelocity_HeadZ1 - AngularVelocity_TailZ1;
                    // Calculate Vector Position-Target
                    VectorPosition_Target[0] = AngularVelocity_HeadX2 - AngularVelocity_TailX1;
                    VectorPosition_Target[1] = AngularVelocity_HeadY2 - AngularVelocity_TailY1;
                    //VectorPosition_Target[2] = AngularVelocity_HeadZ2 - AngularVelocity_TailZ1;
                    // Angle Calculation
                    Angle = LevyWalk_DotProduct(VectorPosition_Head, VectorPosition_Target)/(LevyWalk_Norm(VectorPosition_Head)*LevyWalk_Norm(VectorPosition_Target));
                    // Sign Calculation
                    Sign  = LevyWalk_CrossProduct(VectorPosition_Head, VectorPosition_Target);
                    if (Sign < 0)
                    {
                        Sign = -1.0;
                    }
                    else
                    {
                        Sign = 1.0;
                    }
                    // The following if-statement handle cases in which above calculated > 1 and < -1 because of number transmission
                    if (Angle > 1.0)
                    {
                        Angle = 1.0;
                    }
                    else
                    {
                        if (Angle < -1.0)
                        {
                            Angle = -1.0;
                        }
                    }
                    Angle = acos(Angle); // 0 to pi
                    Angle = Sign*Angle*(180.0/L_PI);
                    // Cumulation of the speed
                    AngularVelocity_Temp  =   Angle/Time_Delta;
                    AngularVelocity       =   AngularVelocity + AngularVelocity_Temp;
                }
                else
                {
                    if (Count > 0)
                    {
                        // This if-statement to eliminate the situation in which we have only one data point to calculate velocity
                        AngularVelocity = AngularVelocity/((float)Count);
                        LevyWalk_SpeedFlag_Angular = true;
                    }
                    else
                    {
                        LevyWalk_SpeedFlag_Linear = false;
                        AngularVelocity = NAN;
                    }
                    break;
                }
            }
        }
    }
    if ((isinf(AngularVelocity)) || (isinf(-AngularVelocity)) || (isnan(AngularVelocity)))
    {
        LevyWalk_SpeedFlag_Angular = false;
        AngularVelocity = NAN;
    }
    return AngularVelocity;
}
float LevyWalk_AngularVelocityCalculation_Version2(void)
{
    // Description:
    // The problem with Version 1 of Angular Velocity Calculation is that when the object rotates with small angular velocity, the difference of two consecutive steps
    // (0.04s) is extremely small, there for the calculation of rotating angle during this period may lead to zero. In details, when locational data is transfered from
    // Vicon to the wireless board, the accuracy of the number is not hold (only two decimal is transferred down), this makes the dot product possibly result in a-near-plus/minus
    // -one number, and the calculated angle correspondingly become zeros. As an results, the sum to calculate average velocity is also zero.
    // Sign of Linear and Angular speeds calculated here is not taken into account
    // Moving average method is used to calculate angular velocity
    float AngularVelocity = 0.0;
    float AngularVelocity_HeadX1, AngularVelocity_HeadY1, AngularVelocity_TailX1, AngularVelocity_TailY1; // AngularVelocity_TailZ1 AngularVelocity_HeadZ1;
    float AngularVelocity_HeadX2, AngularVelocity_HeadY2, AngularVelocity_TailX2, AngularVelocity_TailY2; // AngularVelocity_TailZ2 AngularVelocity_HeadZ2;
    float Time_Delta;
    int32_t  LocationOfWindowsTime;
    int32_t AngularVelocity_i;
    float    VectorPosition_Head[3]   = {0.0, 0.0, 0.0};
    float    VectorPosition_Target[3] = {0.0, 0.0, 0.0};
    float    Angle;
    uint32_t CurrentLocation;
    // Current position inside the array of the current frame
    if (LevyWalk_SpeedCount == 0)
    {
        CurrentLocation = 299;
    }
    else
    {
        CurrentLocation = LevyWalk_SpeedCount - 1;
    }
    // First loop: From the current location to the 0 position of the array
    for (AngularVelocity_i = (int32_t)CurrentLocation - 1; AngularVelocity_i >= 0; AngularVelocity_i--)
    {
        if (LevyWalk_SpeedArray_T[AngularVelocity_i] != 0)
        {
            Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
            if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
            {
                // Do Nothing
            }
            else
            {
                LocationOfWindowsTime = AngularVelocity_i + 1;
                LevyWalk_SpeedFlag_Angular = true;
                break;
            }
        }
    }
    // Second loop: From the 0 position of the array to the other side of the array
    // This if-statement means that the windows may need to cover the last elements to get fulfilled
    if (LevyWalk_SpeedFlag_Angular == false)
    {
        if (LevyWalk_SpeedArray_T[AngularVelocity_i] != 0)
        {
            for (AngularVelocity_i = 299; AngularVelocity_i > CurrentLocation; AngularVelocity_i--)
            {
                Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[AngularVelocity_i]); // 0.01 is the sampling rate of Vicon
                if (Time_Delta <= LevyWalk_TimeStoreToCalculateSpeed)
                {
                    // Do nothing
                }
                else
                {
                    if (AngularVelocity_i == 299)
                    {
                        LocationOfWindowsTime = 0;
                    }
                    else
                    {
                        LocationOfWindowsTime = AngularVelocity_i + 1;
                    }
                    LevyWalk_SpeedFlag_Angular = true;
                    break;
                }
            }
        }
    }
    // Calculation of velocity
    if ((LevyWalk_SpeedFlag_Angular == true) && (LocationOfWindowsTime != CurrentLocation))
    {
        Time_Delta = 0.01*(float)(LevyWalk_SpeedArray_T[CurrentLocation] - LevyWalk_SpeedArray_T[LocationOfWindowsTime]); // 0.01 is the sampling rate of Vicon
       // Head of the "current" frame
       AngularVelocity_HeadX1 = LevyWalk_SpeedArray_XHead[CurrentLocation];
       AngularVelocity_HeadY1 = LevyWalk_SpeedArray_YHead[CurrentLocation];
       //AngularVelocity_HeadZ1 = LevyWalk_SpeedArray_ZHead[SubVariable_iplusone];
       // Tail of the "current" frame
       AngularVelocity_TailX1 = LevyWalk_SpeedArray_X[CurrentLocation];
       AngularVelocity_TailY1 = LevyWalk_SpeedArray_Y[CurrentLocation];
       //AngularVelocity_TailZ1 = LevyWalk_SpeedArray_Z[SubVariable_iplusone];
       // Head of the "previous" frame
       AngularVelocity_HeadX2 = LevyWalk_SpeedArray_XHead[LocationOfWindowsTime];
       AngularVelocity_HeadY2 = LevyWalk_SpeedArray_YHead[LocationOfWindowsTime];
       //AngularVelocity_HeadZ2 = LevyWalk_SpeedArray_ZHead[SubVariable_i];
       // Tail of the "previous" frame
       AngularVelocity_TailX2 = LevyWalk_SpeedArray_X[LocationOfWindowsTime];
       AngularVelocity_TailY2 = LevyWalk_SpeedArray_Y[LocationOfWindowsTime];
       //AngularVelocity_TailZ2 = LevyWalk_SpeedArray_Z[SubVariable_i];
       // Make two positions have the same tail location
       AngularVelocity_HeadX2 = AngularVelocity_HeadX2 + (AngularVelocity_TailX1 - AngularVelocity_TailX2);
       AngularVelocity_HeadY2 = AngularVelocity_HeadY2 + (AngularVelocity_TailY1 - AngularVelocity_TailY2);
       //AngularVelocity_HeadZ2 = AngularVelocity_HeadZ2 + (AngularVelocity_TailZ1 - AngularVelocity_TailZ2);
       // The following lines is inherited from the angle calculation of the navigation program
       // Position = Tail1/Head = Head1/Target = Head2
       // Calculate Vector Position-Head
       VectorPosition_Head[0] = AngularVelocity_HeadX1 - AngularVelocity_TailX1;
       VectorPosition_Head[1] = AngularVelocity_HeadY1 - AngularVelocity_TailY1;
       //VectorPosition_Head[2] = AngularVelocity_HeadZ1 - AngularVelocity_TailZ1;
       // Calculate Vector Position-Target
       VectorPosition_Target[0] = AngularVelocity_HeadX2 - AngularVelocity_TailX1;
       VectorPosition_Target[1] = AngularVelocity_HeadY2 - AngularVelocity_TailY1;
       //VectorPosition_Target[2] = AngularVelocity_HeadZ2 - AngularVelocity_TailZ1;
       // Angle Calculation
       Angle = LevyWalk_DotProduct(VectorPosition_Head, VectorPosition_Target)/(LevyWalk_Norm(VectorPosition_Head)*LevyWalk_Norm(VectorPosition_Target));
       // The following if-statement handle cases in which above calculated > 1 and < -1 because of number transmission
       if (Angle > 1.0)
       {
           Angle = 1.0;
       }
       else
       {
           if (Angle < -1.0)
           {
               Angle = -1.0;
           }
       }
       Angle = acos(Angle); // 0 to pi
       Angle = Angle*(180.0/L_PI);
       // Cumulation of the speed
       AngularVelocity =   Angle/Time_Delta;
    }
    else
    {
        LevyWalk_SpeedFlag_Angular = false;
    }
    if ((isinf(AngularVelocity)) || (isinf(-AngularVelocity)) || (isnan(AngularVelocity)))
    {
        LevyWalk_SpeedFlag_Angular = false;
    }
    return AngularVelocity;
}

void LevyWalk_SetStimulation(void)
{
    // Note: The configuration of stimulation Pins is
    // P2 - P3: Forward
    // P1 - P2: Steer to right
    // P3 - P4: Steer to left
    // ----------------- After manually tune the stimulation parameters, input the appropriate numbers into the following variables
    // ++++++++++++++++ Forward stimulation
    uint32_t Forward_On1        = 12;
    uint32_t Forward_Off1       = 0;
    uint32_t Forward_On2        = 12;
    uint32_t Forward_Off2       = 0;
    float    Forward_fAmplitude = 6.5;
    // ++++++++++++++++ Left stimulation => Steer to left side
    uint32_t Left_On1        = 12;
    uint32_t Left_Off1       = 0;
    uint32_t Left_On2        = 12;
    uint32_t Left_Off2       = 0;
    float    Left_fAmplitude = 6.5;
    // ++++++++++++++++ Right stimulation => Steer to right side
    uint32_t Right_On1        = 12;
    uint32_t Right_Off1       = 0;
    uint32_t Right_On2        = 12;
    uint32_t Right_Off2       = 0;
    float    Right_fAmplitude = 6.5;
    // -----------------------------------------------------------------------------------------------------------------------------
    uint32_t Duration = 30000; // 30s => But it will be halted using variables handling a long stimulus
    int i;
    // Initially set stimulation parameters
    // SERIOUS NOTE: With the outdoor board, the combination of Pin 2 (Channel 1) and 3 (Channel 2) (in code) for forward motion will create physical output at pin 2 and 4 !!!
    //               The real reason is not investigated. However, the combination of Pin 2 (Channel 1) and 4 (Channel 3) (in code) will create physical output at pin 2 and 3 !!!!!
    // Variables for stimulation
    for (i = 0; i <= 3; i++)
    {
        LevyWalk_LeftChannelActive[i] = false;
        LevyWalk_LeftDuration[i] = 0;
        LevyWalk_LeftPeriod[i] = 0;
        LevyWalk_LeftActiveTime1[i] = 0;
        LevyWalk_LeftZeroTime1[i] = 0;
        LevyWalk_LeftZeroTime2[i] = 0;
        LevyWalk_LeftChannelAmplitude[i] = 0;
        // Variables for stimulation
        LevyWalk_RightChannelActive[i] = false;
        LevyWalk_RightDuration[i] = 0;
        LevyWalk_RightPeriod[i] = 0;
        LevyWalk_RightActiveTime1[i] = 0;
        LevyWalk_RightZeroTime1[i] = 0;
        LevyWalk_RightZeroTime2[i] = 0;
        LevyWalk_RightChannelAmplitude[i] = 0;
        // Variables for stimulation
        LevyWalk_ForwardChannelActive[i] = false;
        LevyWalk_ForwardDuration[i] = 0;
        LevyWalk_ForwardPeriod[i] = 0;
        LevyWalk_ForwardActiveTime1[i] = 0;
        LevyWalk_ForwardZeroTime1[i] = 0;
        LevyWalk_ForwardZeroTime2[i] = 0;
        LevyWalk_ForwardChannelAmplitude[i] = 0;
    }
    // The following part is the set up for forward stimulation: P2 and P3 => Channel 1 and 2
    LevyWalk_ForwardChannelActive[1]     = true;
    LevyWalk_ForwardDuration[1]          = Duration;
    LevyWalk_ForwardPeriod[1]            = Forward_On1 + Forward_Off1 + Forward_On2 + Forward_Off2;
    LevyWalk_ForwardActiveTime1[1]       = Forward_On2;
    LevyWalk_ForwardZeroTime1[1]         = Forward_On1 + Forward_Off1;
    LevyWalk_ForwardZeroTime2[1]         = Forward_Off2;
    LevyWalk_ForwardChannelAmplitude[1]  = (uint16_t)(Forward_fAmplitude*136.5333);
    // ------------- Pin 2
    LevyWalk_ForwardChannelActive[2]     = true;
    LevyWalk_ForwardDuration[2]          = Duration;
    LevyWalk_ForwardPeriod[2]            = Forward_On1 + Forward_Off1 + Forward_On2 + Forward_Off2;
    LevyWalk_ForwardActiveTime1[2]       = Forward_On1;
    LevyWalk_ForwardZeroTime1[2]         = 0;
    LevyWalk_ForwardZeroTime2[2]         = Forward_Off1 + Forward_On2 + Forward_Off2;
    LevyWalk_ForwardChannelAmplitude[2]  = (uint16_t)(Forward_fAmplitude*136.5333);
    // The following part is the set up for left stimulation: P3 and P4 => Channel 2 and Channel 3
    // ------------- Channel 2
    LevyWalk_LeftChannelActive[2]    = true;
    LevyWalk_LeftDuration[2]         = Duration;
    LevyWalk_LeftPeriod[2]           = Left_On1 + Left_Off1 + Left_On2 + Left_Off2;
    LevyWalk_LeftActiveTime1[2]      = Left_On2;
    LevyWalk_LeftZeroTime1[2]        = Left_On1 + Left_Off1;
    LevyWalk_LeftZeroTime2[2]        = Left_Off2;
    LevyWalk_LeftChannelAmplitude[2] = (uint16_t)(Left_fAmplitude*136.5333);
    // ------------- Channel 3
    LevyWalk_LeftChannelActive[3]    = true;
    LevyWalk_LeftDuration[3]         = Duration;
    LevyWalk_LeftPeriod[3]           = Left_On1 + Left_Off1 + Left_On2 + Left_Off2;
    LevyWalk_LeftActiveTime1[3]      = Left_On1;
    LevyWalk_LeftZeroTime1[3]        = 0;
    LevyWalk_LeftZeroTime2[3]        = Left_Off1 + Left_On2 + Left_Off2;
    LevyWalk_LeftChannelAmplitude[3] = (uint16_t)(Left_fAmplitude*136.5333);
    // The following part is the set up for right stimulation: P1 and P2 => Channel 0 and Channel 1
    // ------------- Channel 0
    LevyWalk_RightChannelActive[0]    = true;
    LevyWalk_RightDuration[0]         = Duration;
    LevyWalk_RightPeriod[0]           = Right_On1 + Right_Off1 + Right_On2 + Right_Off2;
    LevyWalk_RightActiveTime1[0]      = Right_On2;
    LevyWalk_RightZeroTime1[0]        = Right_On1 + Right_Off1;
    LevyWalk_RightZeroTime2[0]        = Right_Off2;
    LevyWalk_RightChannelAmplitude[0] = (uint16_t)(Right_fAmplitude*136.5333);
    // ------------- Channel 1
    LevyWalk_RightChannelActive[1]    = true;
    LevyWalk_RightDuration[1]         = Duration;
    LevyWalk_RightPeriod[1]           = Right_On1 + Right_Off1 + Right_On2 + Right_Off2;
    LevyWalk_RightActiveTime1[1]      = Right_On1;
    LevyWalk_RightZeroTime1[1]        = 0;
    LevyWalk_RightZeroTime2[1]        = Right_Off1 + Right_On2 + Right_Off2;
    LevyWalk_RightChannelAmplitude[1] = (uint16_t)(Right_fAmplitude*136.5333);
}
void LevyWalk_Stimulation(uint32_t Stimulation_Side)
{
    // Assume that the implanting process is correct that:
    // P4-P3 => Steering to Left
    // P1-P2 => Steering to Right
    // P2-P3 => Forwardly transport
    switch(Stimulation_Side)
    {
    case 0: // Stop the stimulation
        LevyWalk_StopStimulus();
        break;
    case 1: // Steer to the left side
        LevyWalk_LeftStimulus();
        break;
    case 2: // Steer to the right side
        LevyWalk_RightStimulus();
        break;
    case 3: // Push the roach forward
        LevyWalk_ForwardStimulus();
        break;
    default:
        break;
    }
}
void LevyWalk_StopStimulus(void)
{
    StimulationTrigger   = true;
    StimulationStartStop = false;
}
void LevyWalk_LeftStimulus(void)
{
    // Assume that the implanting process is correct that:
    // P4-P3 => Steering to Left
    // P1-P2 => Steering to Right
    // P2-P3 => Forwardly transport
    // -------------- Channel 0
    ChannelActive[0]     = LevyWalk_LeftChannelActive[0];
    StimulateDuration[0] = LevyWalk_LeftDuration[0];
    StimulatePeriod[0]   = LevyWalk_LeftPeriod[0];
    ActiveTime1[0]       = LevyWalk_LeftActiveTime1[0];
    ZeroTime1[0]         = LevyWalk_LeftZeroTime1[0];
    ZeroTime2[0]         = LevyWalk_LeftZeroTime2[0];
    ChannelAmplitude[0]  = LevyWalk_LeftChannelAmplitude[0];
    // -------------- Channel 1
    ChannelActive[1]     = LevyWalk_LeftChannelActive[1];
    StimulateDuration[1] = LevyWalk_LeftDuration[1];
    StimulatePeriod[1]   = LevyWalk_LeftPeriod[1];
    ActiveTime1[1]       = LevyWalk_LeftActiveTime1[1];
    ZeroTime1[1]         = LevyWalk_LeftZeroTime1[1];
    ZeroTime2[1]         = LevyWalk_LeftZeroTime2[1];
    ChannelAmplitude[1]  = LevyWalk_LeftChannelAmplitude[1];
    // -------------- Channel 2
    ChannelActive[2]     = LevyWalk_LeftChannelActive[2];
    StimulateDuration[2] = LevyWalk_LeftDuration[2];
    StimulatePeriod[2]   = LevyWalk_LeftPeriod[2];
    ActiveTime1[2]       = LevyWalk_LeftActiveTime1[2];
    ZeroTime1[2]         = LevyWalk_LeftZeroTime1[2];
    ZeroTime2[2]         = LevyWalk_LeftZeroTime2[2];
    ChannelAmplitude[2]  = LevyWalk_LeftChannelAmplitude[2];
    // -------------- Channel 3
    ChannelActive[3]     = LevyWalk_LeftChannelActive[3];
    StimulateDuration[3] = LevyWalk_LeftDuration[3];
    StimulatePeriod[3]   = LevyWalk_LeftPeriod[3];
    ActiveTime1[3]       = LevyWalk_LeftActiveTime1[3];
    ZeroTime1[3]         = LevyWalk_LeftZeroTime1[3];
    ZeroTime2[3]         = LevyWalk_LeftZeroTime2[3];
    ChannelAmplitude[3]  = LevyWalk_LeftChannelAmplitude[3];
    StimulationTrigger   = true;
    StimulationStartStop = true;
}
void LevyWalk_RightStimulus(void)
{
    // Assume that the implanting process is correct that:
    // P4-P3 => Steering to Left
    // P1-P2 => Steering to Right
    // P2-P3 => Forwardly transport
    // -------------- Channel 0
    ChannelActive[0]     = LevyWalk_RightChannelActive[0];
    StimulateDuration[0] = LevyWalk_RightDuration[0];
    StimulatePeriod[0]   = LevyWalk_RightPeriod[0];
    ActiveTime1[0]       = LevyWalk_RightActiveTime1[0];
    ZeroTime1[0]         = LevyWalk_RightZeroTime1[0];
    ZeroTime2[0]         = LevyWalk_RightZeroTime2[0];
    ChannelAmplitude[0]  = LevyWalk_RightChannelAmplitude[0];
    // -------------- Channel 1
    ChannelActive[1]     = LevyWalk_RightChannelActive[1];
    StimulateDuration[1] = LevyWalk_RightDuration[1];
    StimulatePeriod[1]   = LevyWalk_RightPeriod[1];
    ActiveTime1[1]       = LevyWalk_RightActiveTime1[1];
    ZeroTime1[1]         = LevyWalk_RightZeroTime1[1];
    ZeroTime2[1]         = LevyWalk_RightZeroTime2[1];
    ChannelAmplitude[1]  = LevyWalk_RightChannelAmplitude[1];
    // -------------- Channel 2
    ChannelActive[2]     = LevyWalk_RightChannelActive[2];
    StimulateDuration[2] = LevyWalk_RightDuration[2];
    StimulatePeriod[2]   = LevyWalk_RightPeriod[2];
    ActiveTime1[2]       = LevyWalk_RightActiveTime1[2];
    ZeroTime1[2]         = LevyWalk_RightZeroTime1[2];
    ZeroTime2[2]         = LevyWalk_RightZeroTime2[2];
    ChannelAmplitude[2]  = LevyWalk_RightChannelAmplitude[2];
    // -------------- Channel 3
    ChannelActive[3]     = LevyWalk_RightChannelActive[3];
    StimulateDuration[3] = LevyWalk_RightDuration[3];
    StimulatePeriod[3]   = LevyWalk_RightPeriod[3];
    ActiveTime1[3]       = LevyWalk_RightActiveTime1[3];
    ZeroTime1[3]         = LevyWalk_RightZeroTime1[3];
    ZeroTime2[3]         = LevyWalk_RightZeroTime2[3];
    ChannelAmplitude[3]  = LevyWalk_RightChannelAmplitude[3];
    StimulationTrigger   = true;
    StimulationStartStop = true;
}
void LevyWalk_ForwardStimulus(void)
{
    // Assume that the implanting process is correct that:
    // P4-P3 => Steering to Left
    // P1-P2 => Steering to Right
    // P2-P3 => Forwardly transport
    // -------------- Channel 0
    ChannelActive[0]     = LevyWalk_ForwardChannelActive[0];
    StimulateDuration[0] = LevyWalk_ForwardDuration[0];
    StimulatePeriod[0]   = LevyWalk_ForwardPeriod[0];
    ActiveTime1[0]       = LevyWalk_ForwardActiveTime1[0];
    ZeroTime1[0]         = LevyWalk_ForwardZeroTime1[0];
    ZeroTime2[0]         = LevyWalk_ForwardZeroTime2[0];
    ChannelAmplitude[0]  = LevyWalk_ForwardChannelAmplitude[0];
    // -------------- Channel 1
    ChannelActive[1]     = LevyWalk_ForwardChannelActive[1];
    StimulateDuration[1] = LevyWalk_ForwardDuration[1];
    StimulatePeriod[1]   = LevyWalk_ForwardPeriod[1];
    ActiveTime1[1]       = LevyWalk_ForwardActiveTime1[1];
    ZeroTime1[1]         = LevyWalk_ForwardZeroTime1[1];
    ZeroTime2[1]         = LevyWalk_ForwardZeroTime2[1];
    ChannelAmplitude[1]  = LevyWalk_ForwardChannelAmplitude[1];
    // -------------- Channel 2
    ChannelActive[2]     = LevyWalk_ForwardChannelActive[2];
    StimulateDuration[2] = LevyWalk_ForwardDuration[2];
    StimulatePeriod[2]   = LevyWalk_ForwardPeriod[2];
    ActiveTime1[2]       = LevyWalk_ForwardActiveTime1[2];
    ZeroTime1[2]         = LevyWalk_ForwardZeroTime1[2];
    ZeroTime2[2]         = LevyWalk_ForwardZeroTime2[2];
    ChannelAmplitude[2]  = LevyWalk_ForwardChannelAmplitude[2];
    // -------------- Channel 3
    ChannelActive[3]     = LevyWalk_ForwardChannelActive[3];
    StimulateDuration[3] = LevyWalk_ForwardDuration[3];
    StimulatePeriod[3]   = LevyWalk_ForwardPeriod[3];
    ActiveTime1[3]       = LevyWalk_ForwardActiveTime1[3];
    ZeroTime1[3]         = LevyWalk_ForwardZeroTime1[3];
    ZeroTime2[3]         = LevyWalk_ForwardZeroTime2[3];
    ChannelAmplitude[3]  = LevyWalk_ForwardChannelAmplitude[3];
    StimulationTrigger   = true;
    StimulationStartStop = true;
}
