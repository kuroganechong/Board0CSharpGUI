// ------------------------------- SIMULATION TASK ------------------------------- //
// Author: Dung Van Than
// Date: Aug-2018
// ------------------------------------------------------------------------------ //
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/SPI.h>
#include "Board.h"
#include "DACDriver.h"

//----------------------------------- DEFINITIONS OF STACK AND PRIORITY ----------------------------------//
#define STIMULATIONTASKSTACKSIZE 1024 // 1024 => This number is decided by A.Than
#define STIMULATIONTASKPRIORITY 5

//----------------------------------- PROTOTYPE ----------------------------------//
void StimulationTask(UArg arg0, UArg arg1);
static void PeriodicClockExpired_Stimuli(UArg Arg);

//----------------------------------- GLOBAL VARIABLE ----------------------------------//
volatile uint32_t StimulateDuration[NO_CHANNEL_STI];
volatile uint32_t StimulatePeriod[NO_CHANNEL_STI];
volatile uint32_t ActiveTime1[NO_CHANNEL_STI];
volatile uint32_t ZeroTime1[NO_CHANNEL_STI];
volatile uint32_t ZeroTime2[NO_CHANNEL_STI];
volatile uint16_t  ChannelAmplitude[NO_CHANNEL_STI];
volatile bool     ChannelActive[NO_CHANNEL_STI];
volatile bool     StimulationStartStop;
volatile bool     StimulationTrigger;
extern Semaphore_Handle Empty_SemHandle;

// ------------------------------ VARIABLE FOR ON-BOARD NAVIGATION --------------------------//
extern Semaphore_Handle LevyWalk_SemHandle;
// ------------- Variable to handle a long steering stimulus
extern volatile bool LevyWalk_IsLongStimulusHandleStarted;
extern volatile bool LevyWalk_IsLongStimulusBeingChecked;
extern volatile uint32_t LevyWalk_TimeofStimulusForSteering;
extern volatile uint32_t LevyWalk_TimeafterLongStimulus;
extern volatile uint32_t LevyWalk_ThresholdOfLongStimulus;
extern volatile uint32_t LevyWalk_ThresholdOfLongStimulusForward;
extern volatile uint32_t LevyWalk_ThresholdOfLongStimulusFreeWalk0;
// ------------ Variable to handle the forward stimulation
extern volatile bool LevyWalk_IsForwardTriggeredAlready;
extern volatile bool LevyWalk_ShouldCheckTheForwardSpeed;
extern volatile uint32_t LevyWalk_TimeafterForwardStimulus;
extern volatile uint32_t LevyWalk_TimeafterAngleSmallerThanThreshold;
extern volatile uint32_t LevyWalk_DurationToCheckSpeed;
extern volatile uint32_t LevyWalk_ThresholdOfTimeForwardWhenSpeedIsSmall;
extern volatile uint32_t LevyWalk_ThresholdOfTimeFreeWalkWhenSpeedIsSmall;
// ---------------- Variables to control the control rate
extern uint32_t LevyWalk_ControlRate;
extern bool     LevyWalk_TimeForExecute;
extern uint32_t LevyWalk_ControlCount;
extern uint32_t LevyWalk_TemporalVariableToTestSpeed;
// ---------------- Variables to handle to reduction of number of stimulation
extern volatile uint32_t  LevyWalk_TimeCounterForFreeWalkAfterSteering;
extern bool LevyWalk_StartCoutingTimeForFreeWalkAfterSteering;
//----------------------------------- SEMAPHORE VARIABLE ----------------------------------//
static Semaphore_Handle Stimuli_SemHandle;
static Semaphore_Struct Stimuli_SemStruct;
static Clock_Struct PeriodClockstruct;
// ----------------------------------- OTHER VARIABLES ---------------------------------- //
uint32_t TimeCntMilisecond; // Timer used for Flash Saving
extern uint8_t RequestData;

//----------------------------------- TASK CREATION ----------------------------------//
void StimulationTaskCreation(void)
{
    Error_Block Erb_stimuli;
    Task_Handle TaskHandle_stimuli;
    Task_Params TaskParams_stimuli;
    Error_init(&Erb_stimuli);
    Task_Params_init(&TaskParams_stimuli);
    TaskParams_stimuli.priority = STIMULATIONTASKPRIORITY;
    TaskParams_stimuli.stackSize = STIMULATIONTASKSTACKSIZE;
    TaskHandle_stimuli= Task_create(StimulationTask, &TaskParams_stimuli, &Erb_stimuli);
    if (TaskHandle_stimuli == NULL)
    {
        while(1);
    }
}

//----------------------------------- MAIN FUNTION ----------------------------------//
void StimulationTask(UArg arg0, UArg arg1)
{
    // Initialize all hardware
    GPIO_init();
    I2C_init();
    SPI_init();

    // Initialize Stimulation channels
    //    uint8_t  ChannelMapping[NO_CHANNEL_STI] = {1,2,4,3};//Indoor board: this correction was because Indoor board has a mistake in placing pin 3 and 4
    uint8_t  ChannelMapping[NO_CHANNEL_STI] = {1,2,3,4};//Outdoor board: when Than routed this board: he corrected this
    int32_t i;
    uint32_t StimulateDurationCnt[NO_CHANNEL_STI];
    uint32_t StimulatePeriodCnt[NO_CHANNEL_STI];
    bool     Booltemp;
    bool     StimulationStartStopOld;
    uint8_t  ChannelState[NO_CHANNEL_STI];     // 0-disable(high impedance), 1- [1,0], 2-[0,0], 3-[0-1], 4-[1,1]
    uint8_t  ChannelStateOld[NO_CHANNEL_STI];  // 0-disable(high impedance), 1- [1,0], 2-[0,0], 3-[0-1], 4-[1,1]
    uint32_t Time1val[NO_CHANNEL_STI];
    uint32_t Time2val[NO_CHANNEL_STI];
    uint32_t Time3val[NO_CHANNEL_STI]; // period
    bool     ChannelRunning[NO_CHANNEL_STI];

    // Initialize Semaphore
    Semaphore_Params semparams_Sti;
    Semaphore_Params_init(&semparams_Sti);
    semparams_Sti.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&Stimuli_SemStruct, 0, &semparams_Sti);
    Stimuli_SemHandle = Semaphore_handle(&Stimuli_SemStruct);

    // Initialize Clock
    Clock_Params PeriodClockParam_Sti;
    Clock_Params_init(&PeriodClockParam_Sti);
    PeriodClockParam_Sti.startFlag = true;
    PeriodClockParam_Sti.period = 1;// 1000Hz data refreshing rate
    Clock_construct(&PeriodClockstruct, PeriodicClockExpired_Stimuli, 1, &PeriodClockParam_Sti);

    // Initialize the DAC driver
    DAC_Init();

    // Reset variables
    for (i = 0; i< NO_CHANNEL_STI; i++)
    {
        StimulateDurationCnt[i] = 0;
        StimulatePeriodCnt[i] = 0;
        ChannelActive[i] = true;
        ChannelState[i] = 0;
    }
    StimulationStartStopOld = StimulationStartStop;
    TimeCntMilisecond = 0;

    while(1)
    {
        Semaphore_pend(Stimuli_SemHandle, BIOS_WAIT_FOREVER);
        if (StimulationTrigger) // Reset the stimulation
        {
            StimulationTrigger = false;
            StimulationStartStopOld = !StimulationStartStop;
            for (i = 0; i< NO_CHANNEL_STI; i++)
            {
                StimulateDurationCnt[i] = 0;
                StimulatePeriodCnt[i] = 0;
            }
        }
        // calculate switching time
        for ( i = 0; i < NO_CHANNEL_STI; i++ )
        {
            Time1val[i] = ZeroTime1[i] ;
            Time2val[i] = ZeroTime1[i] + ActiveTime1[i];
            Time3val[i] = ZeroTime1[i] + ZeroTime2[i] + ActiveTime1[i];
        }
        // Change DAC state
        if(StimulationStartStop) // True start stimulation
        {
            // checking for expire of stimulation duration
            for (i = 0; i< NO_CHANNEL_STI; i++)
            {
                // increase all counter
                StimulateDurationCnt[i]++;
                StimulatePeriodCnt[i]++;
                // switch state
                if(ChannelActive[i])
                {
                    // Checking for channel state
                    if(StimulateDurationCnt[i] >= StimulateDuration[i]) // Channel expires
                    {
                        ChannelRunning[i]= false; // de-active the channel
                        ChannelStateOld[i] = ChannelState[i];
                        ChannelState[i] = 0; // floating state
                    }
                    else
                    {
                        ChannelRunning[i] = true;
                        if(StimulatePeriodCnt[i] >= Time3val[i]) // period expires
                        {
                            // reset period counter
                            StimulatePeriodCnt[i] = 0;
                        }

                        if(StimulatePeriodCnt[i] >= Time2val[i]) // zero stage 2
                        {
                            ChannelStateOld[i] = ChannelState[i];
                            ChannelState[i] = 3;
                        }
                        else
                        {
                            if(StimulatePeriodCnt[i] >= Time1val[i]) // active stage
                            {
                                ChannelStateOld[i] = ChannelState[i];
                                ChannelState[i] = 2;
                            }
                            else // zero stat 1
                            {
                                ChannelStateOld[i] = ChannelState[i];
                                ChannelState[i] = 1;// set state [1,0]
                            }
                        }

                    }
                }
                else
                {
                    ChannelStateOld[i] = ChannelState[i];
                    ChannelState[i] = 0; // floating state
                }
            }
            // Update output
            for (i = 0; i< NO_CHANNEL_STI; i++)
            {   // update
                if (ChannelStateOld[i] != ChannelState[i])
                {
                    // Switch state
                    switch(ChannelState[i])
                    {
                    case 1: //zero state
                    case 3:
                        DAC_Set_Value(ChannelMapping[i], 0);
                        // set channel output
                        DAC_Set_Output(ChannelMapping[i]);
                        break;

                    case 2: //active state
                        // set channel output
                        DAC_Set_Value(ChannelMapping[i], ChannelAmplitude[i]);
                        // set channel output
                        DAC_Set_Output(ChannelMapping[i]);
                        break;

                    default: // floating state
                        // enter high impedance state
                        DAC_Set_Floating(ChannelMapping[i]);
                        break;
                    }
                }
            }
            // if all channels are deactive, stop the stimulation and wait for it becomes active again
            Booltemp = false;
            for (i = 0; i<NO_CHANNEL_STI; i++)
            {
                Booltemp |= ChannelRunning[i];
            }
            StimulationStartStopOld = StimulationStartStop;
            if (Booltemp == false)
            {
                StimulationStartStop = false; //stop stimulation
            }
        }
        else // stop stimulation
        {
            if (StimulationStartStopOld != StimulationStartStop)
            {
                StimulationStartStopOld = StimulationStartStop;
                // reset all counter
                for (i = 0; i< NO_CHANNEL_STI; i++)
                {
                    StimulateDurationCnt[i] = 0;
                    StimulatePeriodCnt[i] = 0;
                }
                // All channels enter high impedance state
                DAC_Set_Floating_All();
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
static void PeriodicClockExpired_Stimuli(UArg Arg)
{
    TimeCntMilisecond++; // Timer For Flash Saving

    // Inside this if-statement is the process related to Navigation - LevyWalk
    if ((RequestData == 0x45) || (RequestData == 0x40))
    {
        LevyWalk_TemporalVariableToTestSpeed++; // Dev - Temporal variable to test the calculated speed

           // -------------- Handler of long steering stimulus
           if (LevyWalk_IsLongStimulusBeingChecked)
           {
               // Explain: When the variable LevyWalk_IsLongStimulusBeingChecked is enabled (when the angle of the cockroach > angle threshold), the timer variable LevyWalk_TimeofStimulusForSteering
               //          will be started counted
               LevyWalk_TimeofStimulusForSteering++;
               if (LevyWalk_IsLongStimulusHandleStarted)
               {
                   // Explain: When a long stimulus is recorded, the variable LevyWalk_IsLongStimulusHandleStarted becomes true (See LevyWalkTask.c).
                   //          Since then, the variable LevyWalk_TimeafterLongStimulus is started for counting; it is used to handle the event of forward stimulation and
                   //          free walking after a long steering stimulus is recorded.
                   LevyWalk_TimeafterLongStimulus++;
               }
           }

           // -------------- Handler of long steering stimulus
           if (LevyWalk_ShouldCheckTheForwardSpeed)
           {
               LevyWalk_TimeafterAngleSmallerThanThreshold++;
           }
           if (LevyWalk_IsForwardTriggeredAlready)
           {
               LevyWalk_TimeafterForwardStimulus++;
           }

           // --------------- Periodic loop of LevyWalk to manipulate the execution rate
           if (LevyWalk_TimeForExecute == false)
           {
               LevyWalk_ControlCount++;
               if (LevyWalk_ControlCount > LevyWalk_ControlRate)
               {
                   LevyWalk_TimeForExecute = true;
               }
           }
    }
    Semaphore_post(Stimuli_SemHandle);
}
