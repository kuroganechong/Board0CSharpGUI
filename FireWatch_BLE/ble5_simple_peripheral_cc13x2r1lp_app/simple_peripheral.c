/******************************************************************************

 @file  simple_peripheral.c

 @brief This file contains the Simple Peripheral sample application for use
        with the CC2650 Bluetooth Low Energy Protocol Stack.

 Group: CMCU, LPRF
 Target Device: CC2652

 ******************************************************************************
 
 Copyright (c) 2013-2018, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 Release Name: ble5stack_2_00_00_25
 Release Date: 2018-10-03 16:22:13
 *****************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include <string.h>
#include <ti/sysbios/BIOS.h>
#include <math.h>
#include <ti/sysbios/hal/Hwi.h>
#include <onboard.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PIN.h>
#include <ti/display/Display.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>

#if !(defined __TI_COMPILER_VERSION__)
#include <intrinsics.h>
#endif

#include <ti/drivers/utils/List.h>

#include <icall.h>
#include "util.h"
#include <bcomdef.h>
/* This Header file contains all BLE API and icall structure definition */
#include <icall_ble_api.h>

#include "gapgattserver.h"
#include "gattservapp.h"
#include "devinfoservice.h"
#include "simple_gatt_profile.h"

#ifdef USE_RCOSC
#include <rcosc_calibration.h>
#endif //USE_RCOSC

#include <board.h>
#include <board_key.h>

#include <menu/two_btn_menu.h>

#include <simple_peripheral_menu.h>
#include <simple_peripheral.h>
#include <cc1352uart2spi.h>
#include "SensorStructure.h"
#include <ti/ble5stack/inc/gapbondmgr_internal.h>
#include "GPS.h"
//#include "positioning.h"

#ifdef PTM_MODE
#include "npi_task.h"               // To allow RX event registration
#include "npi_ble.h"                // To enable transmission of messages to UART
#include "icall_hci_tl.h"   // To allow ICall HCI Transport Layer
#endif // PTM_MODE

/*********************************************************************
 * MACROS
 */
//#define DATA_FUSION
#ifndef DATA_FUSION
#define GPS_ONLY
#endif

#define MAX_BLE_CONNS               1
/*********************************************************************
 * TEMPORARY DATA SETUP
 */
uint8_t BLE5sendbuff[SPI_TRANS_LEN];

/*********************************************************************
 * CONSTANTS
 */

// Address mode of the local device
// Note: When using the DEFAULT_ADDRESS_MODE as ADDRMODE_RANDOM or 
// ADDRMODE_RP_WITH_RANDOM_ID, GAP_DeviceInit() should be called with 
// it's last parameter set to a static random address
#define DEFAULT_ADDRESS_MODE                  ADDRMODE_PUBLIC // ADDRMODE_RP_WITH_PUBLIC_ID

// Limited discoverable mode advertises for 30.72s, and then stops
// #define DEFAULT_DISCOVERABLE_MODE              GAP_ADTYPE_FLAGS_LIMITED
// General discoverable mode: advertise indefinitely
#define DEFAULT_DISCOVERABLE_MODE             GAP_ADTYPE_FLAGS_GENERAL

// Minimum connection interval (units of 1.25ms, 80=100ms) for parameter update request
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL     8//37 //17 85 170    8     // default Code 80

// Maximum connection interval (units of 1.25ms, 104=130ms) for  parameter update request
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL     8//37 //17 85 170    8     // default Code 104

// Slave latency to use for parameter update request
#define DEFAULT_DESIRED_SLAVE_LATENCY         0

// Supervision timeout value (units of 10ms, 300=3s) for parameter update request
#define DEFAULT_DESIRED_CONN_TIMEOUT          300   //1000     // default Code 300

// Pass parameter updates to the app for it to decide.
#define DEFAULT_PARAM_UPDATE_REQ_DECISION     GAP_UPDATE_REQ_PASS_TO_APP

// How often to perform periodic event (in ms)
#define SP_PERIODIC_EVT_PERIOD               1000

// How often to read current current RPA (in ms)
#define SP_READ_RPA_EVT_PERIOD               3000

// Delay (in ms) after connection establishment before sending a parameter update request
#define SP_SEND_PARAM_UPDATE_DELAY           500    //6000

#define MCU_PERIODIC_READ                     40

// Task configuration
#define SP_TASK_PRIORITY                     1

#ifndef SP_TASK_STACK_SIZE
#define SP_TASK_STACK_SIZE                   1024
#endif

// Application events
#define SP_STATE_CHANGE_EVT                  0
#define SP_CHAR_CHANGE_EVT                   1
#define SP_KEY_CHANGE_EVT                    2
#define SP_ADV_EVT                           3
#define SP_PAIR_STATE_EVT                    4
#define SP_PASSCODE_EVT                      5
#define SP_PERIODIC_EVT                      6
#define SP_READ_RPA_EVT                      7
#define SP_SEND_PARAM_UPDATE_EVT             8
#define SP_CONN_EVT                          9
#define SP_MCU_TRANS_EVT                     10

#define SP_UART_READ_EVT                     11
#define SP_GPS_DONE_EVT                      12

//#define SP_DELAY_CLK_EVT                     11
//#define SP_SPI_FINISH_EVT                    12
// Following events will be managed by &= and |=
//static uint16_t UserEvents;
#define SP_SPI_FINISH_EVT                    0x0040
#define SBP_SPI_START_EVT                     0x0080
//#define SBP_DELAY_CLK_EVT                     0x0100
//#define SBP_MCU_TRANS_EVT                     0x0200

// Internal Events for RTOS application
#define SP_ICALL_EVT                         ICALL_MSG_EVENT_ID // Event_Id_31
#define SP_QUEUE_EVT                         UTIL_QUEUE_EVENT_ID // Event_Id_30

// Bitwise OR of all RTOS events to pend on
#define SP_ALL_EVENTS                        (SP_ICALL_EVT             | \
                                              SP_QUEUE_EVT)

// Size of string-converted device address ("0xXXXXXXXXXXXX")
#define SP_ADDR_STR_SIZE     15

// Row numbers for two-button menu
#define SP_ROW_SEPARATOR_1   (TBM_ROW_APP + 0)
#define SP_ROW_STATUS_1      (TBM_ROW_APP + 1)
#define SP_ROW_STATUS_2      (TBM_ROW_APP + 2)
#define SP_ROW_CONNECTION    (TBM_ROW_APP + 3)
#define SP_ROW_ADVSTATE      (TBM_ROW_APP + 4)
#define SP_ROW_RSSI          (TBM_ROW_APP + 5)
#define SP_ROW_IDA           (TBM_ROW_APP + 6)
#define SP_ROW_RPA           (TBM_ROW_APP + 7)
#define SP_ROW_DEBUG         (TBM_ROW_APP + 8)

// For storing the active connections
#define SP_RSSI_TRACK_CHNLS        1            // Max possible channels can be GAP_BONDINGS_MAX
#define SP_MAX_RSSI_STORE_DEPTH    5
#define SP_INVALID_HANDLE          0xFFFF
#define RSSI_2M_THRSHLD           -30           
#define RSSI_1M_THRSHLD           -40           
#define RSSI_S2_THRSHLD           -50           
#define RSSI_S8_THRSHLD           -60           
#define SP_PHY_NONE                LL_PHY_NONE  // No PHY set
#define AUTO_PHY_UPDATE            0xFF

// Spin if the expression is not true
#define SIMPLEPERIPHERAL_ASSERT(expr) if (!(expr)) simple_peripheral_spin();

/*********************************************************************
 * TYPEDEFS
 */
// App event passed from stack modules. This type is defined by the application
// since it can queue events to itself however it wants.
typedef struct
{
  uint8_t event;                // event type
  void    *pData;               // pointer to message
} spEvt_t;

// Container to store passcode data when passing from gapbondmgr callback
// to app event. See the pfnPairStateCB_t documentation from the gapbondmgr.h
// header file for more information on each parameter.
typedef struct
{
  uint8_t state;
  uint16_t connHandle;
  uint8_t status;
} spPairStateData_t;

// Container to store passcode data when passing from gapbondmgr callback
// to app event. See the pfnPasscodeCB_t documentation from the gapbondmgr.h
// header file for more information on each parameter.
typedef struct
{
  uint8_t deviceAddr[B_ADDR_LEN];
  uint16_t connHandle;
  uint8_t uiInputs;
  uint8_t uiOutputs;
  uint32_t numComparison;
} spPasscodeData_t;

// Container to store advertising event data when passing from advertising
// callback to app event. See the respective event in GapAdvScan_Event_IDs
// in gap_advertiser.h for the type that pBuf should be cast to.
typedef struct
{
  uint32_t event;
  void *pBuf;
} spGapAdvEventData_t;

// Container to store information from clock expiration using a flexible array
// since data is not always needed
typedef struct
{
  uint8_t event;                //
  uint8_t data[];
} spClockEventData_t;

// List element for parameter update and PHY command status lists
typedef struct
{
  List_Elem elem;
  uint16_t  connHandle;
} spConnHandleEntry_t;

// Connected device information
typedef struct
{
  uint16_t         	    connHandle;                        // Connection Handle
  spClockEventData_t*   pParamUpdateEventData;
  Clock_Struct*    	    pUpdateClock;                      // pointer to clock struct
  int8_t           	    rssiArr[SP_MAX_RSSI_STORE_DEPTH];
  uint8_t          	    rssiCntr;
  int8_t           	    rssiAvg;
  bool             	    phyCngRq;                          // Set to true if PHY change request is in progress
  uint8_t          	    currPhy;
  uint8_t          	    rqPhy;
  uint8_t          	    phyRqFailCnt;                      // PHY change request count
  bool             	    isAutoPHYEnable;                   // Flag to indicate auto phy change
} spConnRec_t;

/*********************************************************************
 * GLOBAL VARIABLES
 */
int32_t currentcommand;
bool    Startcmdset;
uint8_t RequestData;
uint16_t No_repeat;
//TODO
static bool    isconnected = FALSE;
// Display Interface
Display_Handle dispHandle = NULL;

// Task configuration
Task_Struct spTask;
#if defined __TI_COMPILER_VERSION__
#pragma DATA_ALIGN(spTaskStack, 8)
#else
#pragma data_alignment=8
#endif
uint8_t spTaskStack[SP_TASK_STACK_SIZE];

#define GATT_NO_AUTHENTICATION 0

/**********************************************************************
 * APPLICATION OUTDOOR BOARD VARIABLES AND DEFINITIONS
 */
static PIN_Handle GPSPinHandle;
PIN_State GPSPinState;
PIN_Config GPSPinTable[] = {
        Board_GPS_POWER| PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH| PIN_PUSHPULL  | PIN_DRVSTR_MAX,
        Board_GPS_ONOFF| PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL  | PIN_DRVSTR_MAX,
        Board_GPS_WAKE | PIN_GPIO_OUTPUT_DIS| PIN_INPUT_EN | PIN_HYSTERESIS| PIN_NOPULL,
        PIN_TERMINATE
    };
//SPI control Pins
static PIN_Handle Spi_sensorboard_cs_handle;
PIN_State SpiSensorCSPinState;
PIN_Config SpiSensorCSPinTable[] = {
    CC1352R1_LAUNCHXL_SPI1_CSN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MIN,
    CC1352_SPI1_CTS_BLE_EXT| PIN_INPUT_EN       | PIN_PULLUP    | PIN_HYSTERESIS,                             /* Button is active low          */
    PIN_TERMINATE
};
// LED
static PIN_Handle ledPinHandle;
PIN_State ledPinState;
PIN_Config ledPinTable[] = {
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};

uint8_t RxBuffFromComputer[SIMPLEPROFILE_CHAR3_LEN];
uint8_t TxBuffToComputer[SIMPLEPROFILE_CHAR4_LEN];

uint16_t lensend = SIMPLEPROFILE_CHAR4_LEN;
attHandleValueNoti_t noti;
uint16_t Character4handle;
uint16_t connectionHandleSend = 0;
bool starthandleflag = true;
uint8_t status_noti;
uint8 cccValue_char4;

bool isPeriodicDataCollection;
uint8_t PeriodicCollectCnt;
bool   isNewrequestcome;
bool   isAutoSendTriggered;
uint8_t CMDTransmitnumbertemp;
bool   isBLEready = false;
bool   isForwardingFinished;
bool   isSendbackFinished;
bool   isSPItrasferfinished;
bool   Datafusionsendback;
bool   FusionOnOff;
bool   FusionOnOffOld;
bool   isGPSonly = false;
uint8_t SPItrasfercase;
bool   isWaitingforIMU;
int32_t NumberofRemainingdata;

uint8_t     CMDReceivenumber;
uint8_t     CMDReceivenumberOld;
uint8_t     CMDTransmitnumber;
uint8_t     CMDTransmitnumberOld;
uint16_t    Receivevaluetemp;

// SPI
SPI_Handle          handle_spi;
uint8_t             transmitBuffer_spi[SPI_TRANS_LEN];
uint8_t             receiveBuffer_spi[SPI_TRANS_LEN];
SPI_Transaction     Transaction_spi;
bool                transferOK;
// UART--> This is for communicating with GPS
static UART_Handle uartHandle;
static uint8_t uartBuf[4];
static uint16_t uartNum;
static char GPSbuf[800];
static GPS_t GPSinfo;

bool   lineExecuteCall;
uint8_t CMDcnt = 0;     //------------->Command from Computer

//GPS Handle Variables
uint16_t notifyEnable;
//extern int gpsdatacheck;
//extern int GPSconsisent;
int gpsdatacheck = 0;
int GPSconsisent = 0;
//uint8_t CMDReceivenumber;
//uint8_t CMDReceivenumberOld;
//static uint8_t CMDTransmitnumber;
//static uint8_t RxBuffFromComputer[BLE_TRANS_LEN] = {0};
//static uint8_t TxBuffToComputer[BLE_TRANS_LEN] = {0};
static uint8_t CmdSub; // classify IMU data
//for testing GPS
static char bufftest[] = "$GPGGA,181908.01,3404.7048,N,07044.3966,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40";

static float posGPS[2], posFusion[2];
bool gpsCalDone = FALSE;
bool bleSend = FALSE; // if send this spi read to computer
bool imuRequest = FALSE; // a new IMU positioning result is received
bool connectionFlag = FALSE;
bool startHandleFlag;
#ifdef DATA_FUSION
static float speed[2], position[2];
//static point_t pointFusion[2];
static float p_matrix[3], ypr[3];
static float yaw_bias;
extern float var_acc, var_ble;
#endif

/*********************************************************************
 * LOCAL VARIABLES
 */
// Entity ID globally used to check for source and/or destination of messages
static ICall_EntityID selfEntity;

// Event globally used to post local events and pend on system and
// local events.
static ICall_SyncHandle syncEvent;

// Queue object used for app messages
static Queue_Struct appMsgQueue;
static Queue_Handle appMsgQueueHandle;

static Clock_Struct     Mscounter_s;
static Semaphore_Struct Semdelay_s;
static Semaphore_Handle Semdelayhdl;
uint32_t  mstimecnt;
static  volatile bool delaycountstarted;
static  volatile uint32_t Mscounteslapsed;
static  volatile uint32_t Delayduration;
// Clock instance for internal periodic events. Only one is needed since
// GattServApp will handle notifying all connected GATT clients
//static Clock_Struct clkPeriodic;
// Clock instance for RPA read events.
static Clock_Struct clkPeriodic;
static Clock_Struct clkRpaRead;
static Clock_Struct clkUART;
static Clock_Struct clkMcuTransaction;
// Clock instances for internal periodic events.
// Memory to pass periodic event ID to clock handler
spClockEventData_t argPeriodic =
{ .event = SP_PERIODIC_EVT };

// Memory to pass RPA read event ID to clock handler
spClockEventData_t argRpaRead =
{ .event = SP_READ_RPA_EVT };

spClockEventData_t argGPS =
{ .event = SP_GPS_DONE_EVT };

// Memory to pass McuTransaction event ID to clock handler
spClockEventData_t argMcuTransaction =
{ .event = SP_MCU_TRANS_EVT };

// Per-handle connection info
static spConnRec_t connList[MAX_NUM_BLE_CONNS];

// Current connection handle as chosen by menu
static uint16_t menuConnHandle = LINKDB_CONNHANDLE_INVALID;

// List to store connection handles for set phy command status's
static List_List setPhyCommStatList;

// List to store connection handles for queued param updates
static List_List paramUpdateList;

// GAP GATT Attributes
static uint8_t attDeviceName[GAP_DEVICE_NAME_LEN] = "Simple Peripheral";

// Advertisement data
static uint8_t advertData[] =
{
  0x02,   // length of this data
  GAP_ADTYPE_FLAGS,
  DEFAULT_DISCOVERABLE_MODE | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,

  // service UUID, to notify central devices what services are included
  // in this peripheral
  0x03,   // length of this data
  GAP_ADTYPE_16BIT_MORE,      // some of the UUID's, but not all
  LO_UINT16(SIMPLEPROFILE_SERV_UUID),
  HI_UINT16(SIMPLEPROFILE_SERV_UUID)
};

// Scan Response Data
static uint8_t scanRspData[] =
{
  // complete name
  17,   // length of this data
  GAP_ADTYPE_LOCAL_NAME_COMPLETE,
  'S',
  'i',
  'm',
  'p',
  'l',
  'e',
  'T',
  'H',
  'A',
  'N',
  'H',
  'L',
  'U',
  'A',
  'N',
  '8',
  // connection interval range
  5,   // length of this data
  GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE,
  LO_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL),   // 10ms default 100ms
  HI_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL),
  LO_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL),   // 10ms default 1s
  HI_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL),

  // Tx power level
  2,   // length of this data
  GAP_ADTYPE_POWER_LEVEL,
  0       // 0dBm
};

// Advertising handles
static uint8 advHandleLegacy;
static uint8 advHandleLongRange;

// Address mode
static GAP_Addr_Modes_t addrMode = DEFAULT_ADDRESS_MODE;

// Current Random Private Address
static uint8 rpa[B_ADDR_LEN] = {0};

const char *AdvTypeStrings[] = {"Connectable undirected","Connectable directed", "Scannable undirected", "Non-connectable undirected", "Scan response"};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void Num2hex_byte(uint8_t *outbuf, uint8_t val)
{
    uint8_t valtemp;
    valtemp = (val >> 4) & 0x0F;

    if (valtemp < 10)
        valtemp = valtemp + 48;
    else
        valtemp = valtemp + 55;

    outbuf[0] = valtemp;

    valtemp = val & 0x0F;

    if (valtemp < 10)
        valtemp = valtemp + 48;
    else
        valtemp = valtemp + 55;

    outbuf[1] = valtemp;
}

static uint8_t Hex2num_byte(uint8_t *val)
{
    uint8_t temp[2], ret;

    temp[0] = (val[0] >= 65 ? (uint8_t)(val[0] - 55) : (uint8_t)(val[0] - 48));
    temp[1] = (val[1] >= 65 ? (uint8_t)(val[1] - 55) : (uint8_t)(val[1] - 48));
    ret = ((temp[0])<<4)  | temp[1];

    return ret;
}

static void Num2hex_float(uint8_t *outbuf, float val)
{
    uint8_t ByteTemp[4];
    memcpy(ByteTemp, &val, 4);
    Num2hex_byte(&outbuf[0], ByteTemp[0]);
    Num2hex_byte(&outbuf[2], ByteTemp[1]);
    Num2hex_byte(&outbuf[4], ByteTemp[2]);
    Num2hex_byte(&outbuf[6], ByteTemp[3]);
}

static float Hex2num_float(uint8_t *val)
{
    uint8_t ByteTemp[4];
    float ret;

    ByteTemp[0] = Hex2num_byte(&val[0]);
    ByteTemp[1] = Hex2num_byte(&val[2]);
    ByteTemp[2] = Hex2num_byte(&val[4]);
    ByteTemp[3] = Hex2num_byte(&val[6]);
    memcpy(&ret, ByteTemp, 4);

    return ret;
}
//=================Adopted and user funcs==============================
static void UpdateGPSPosition4TxBuffToComputer(void);
static void UpdateGPSPosition4RxBuffomComputer(void);
static void MCUDataTransaction(void);
static void BLESendbackdata(void);
static void SimpleBLEPeripheral_processCharValueChangeEvt(uint8_t paramID);
uint8_t Num2textbyte(uint8_t x);
void Num2textfloat(uint8_t * outbuf, float * inbuf);
static void simpleData_init(void);
bStatus_t GAPRole_GetParameter(uint16_t param, void *pValue);
bStatus_t GAPRole_StartDevice(gapRolesCBs_t *pAppCallbacks);
void GPS_Wakeup(void);
int GPS_readNew(char* buf, GPS_t* output);
int GPS_readNewTest(char* buf, GPS_t* output);
//======================End references from BLE4==============================
static void SimplePeripheral_init( void );
static void SimplePeripheral_taskFxn(UArg a0, UArg a1);

static uint8_t SimplePeripheral_processStackMsg(ICall_Hdr *pMsg);
static uint8_t SimplePeripheral_processGATTMsg(gattMsgEvent_t *pMsg);
static void SimplePeripheral_processGapMessage(gapEventHdr_t *pMsg);
static void SimplePeripheral_advCallback(uint32_t event, void *pBuf, uintptr_t arg);
static void SimplePeripheral_processAdvEvent(spGapAdvEventData_t *pEventData);
static void SimplePeripheral_processAppMsg(spEvt_t *pMsg);
static void SimplePeripheral_processCharValueChangeEvt(uint8_t paramId);
static void SimplePeripheral_performPeriodicTask(void);
static void SimplePeripheral_updateRPA(void);
static void SimplePeripheral_clockHandler(UArg arg);
static void SimplePeripheral_passcodeCb(uint8_t *pDeviceAddr, uint16_t connHandle,
                                        uint8_t uiInputs, uint8_t uiOutputs,
                                        uint32_t numComparison);
static void SimplePeripheral_pairStateCb(uint16_t connHandle, uint8_t state,
                                         uint8_t status);
static void SimplePeripheral_processPairState(spPairStateData_t *pPairState);
static void SimplePeripheral_processPasscode(spPasscodeData_t *pPasscodeData);
static void SimplePeripheral_charValueChangeCB(uint8_t paramId);
static status_t SimplePeripheral_enqueueMsg(uint8_t event, void *pData);
//static void SimplePeripheral_keyChangeHandler(uint8 keys);
static void SimplePeripheral_handleKeys(uint8_t keys);
static void SimplePeripheral_processCmdCompleteEvt(hciEvt_CmdComplete_t *pMsg);
static void SimplePeripheral_initPHYRSSIArray(void);
static void SimplePeripheral_updatePHYStat(uint16_t eventCode, uint8_t *pMsg);
static uint8_t SimplePeripheral_addConn(uint16_t connHandle);
static uint8_t SimplePeripheral_getConnIndex(uint16_t connHandle);
static uint8_t SimplePeripheral_removeConn(uint16_t connHandle);
static void SimplePeripheral_processParamUpdate(uint16_t connHandle);
static status_t SimplePeripheral_startAutoPhyChange(uint16_t connHandle);
static status_t SimplePeripheral_stopAutoPhyChange(uint16_t connHandle);
static status_t SimplePeripheral_setPhy(uint16_t connHandle, uint8_t allPhys,
                                        uint8_t txPhy, uint8_t rxPhy,
                                        uint16_t phyOpts);
static uint8_t SimplePeripheral_clearConnListEntry(uint16_t connHandle);
//static void SimplePeripheral_menuSwitchCb(tbmMenuObj_t* pMenuObjCurr,
//                                          tbmMenuObj_t* pMenuObjNext);
static void SimplePeripheral_connEvtCB(Gap_ConnEventRpt_t *pReport);
static void SimplePeripheral_processConnEvt(Gap_ConnEventRpt_t *pReport);

#ifdef PTM_MODE
void simple_peripheral_handleNPIRxInterceptEvent(uint8_t *pMsg);  // Declaration
static void simple_peripheral_sendToNPI(uint8_t *buf, uint16_t len);  // Declaration
#endif // PTM_MODE

/*********************************************************************
 * EXTERN FUNCTIONS
 */
extern void AssertHandler(uint8 assertCause, uint8 assertSubcause);

/*********************************************************************
 * PROFILE CALLBACKS
 */
// GAP Bond Manager Callbacks
static gapBondCBs_t SimplePeripheral_BondMgrCBs =
{
//     NULL, // SimplePeripheral_passcodeCb, // Passcode callback (not used by application)
//     NULL  // SimplePeripheral_pairStateCb // Pairing / Bonding state Callback (not used by application)
  SimplePeripheral_passcodeCb,       // Passcode callback
  SimplePeripheral_pairStateCb       // Pairing/Bonding state Callback
};

// Simple GATT Profile Callbacks
static simpleProfileCBs_t SimplePeripheral_simpleProfileCBs =
{
  SimplePeripheral_charValueChangeCB // Simple GATT Characteristic value change callback
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/////////////////////////////////////////////////////////////////////////////////////////
void delay_ms(unsigned long num_ms){
    delaycountstarted = true;
    Mscounteslapsed = 0;
    Delayduration = num_ms;
    Semaphore_pend(Semdelayhdl, BIOS_WAIT_FOREVER);
    delaycountstarted = false;
}
/////////////////////////////////////////////////////////////////////////////////////////
void get_ms(unsigned long *count){
    *count = mstimecnt;
}
/////////////////////////////////////////////////////////////////////////////////////////
static void Mscounter_clockHandler(UArg arg){
    mstimecnt++;
    if(delaycountstarted){
        Mscounteslapsed++;
        if(Mscounteslapsed > Delayduration){
            Semaphore_post(Semdelayhdl);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************************
 * @fn      simple_peripheral_spin
 *
 * @brief   Spin forever
 *
 * @param   none
 */
static void simple_peripheral_spin(void)
{
  volatile uint8_t x = 0;

  while(1)
  {
    x++;
  }
}

#ifdef PTM_MODE
/*********************************************************************
* @fn      simple_peripheral_handleNPIRxInterceptEvent
*
* @brief   Intercept an NPI RX serial message and queue for this application.
*
* @param   pMsg - a NPIMSG_msg_t containing the intercepted message.
*
* @return  none.
*/
void simple_peripheral_handleNPIRxInterceptEvent(uint8_t *pMsg)
{
 // Send Command via HCI TL
 HCI_TL_SendToStack(((NPIMSG_msg_t *)pMsg)->pBuf);

 // The data is stored as a message, free this first.
 ICall_freeMsg(((NPIMSG_msg_t *)pMsg)->pBuf);

 // Free container.
 ICall_free(pMsg);
}

/*********************************************************************
* @fn      simple_peripheral_sendToNPI
*
* @brief   Create an NPI packet and send to NPI to transmit.
*
* @param   buf - pointer HCI event or data.
*
* @param   len - length of buf in bytes.
*
* @return  none
*/
static void simple_peripheral_sendToNPI(uint8_t *buf, uint16_t len)
{
 npiPkt_t *pNpiPkt = (npiPkt_t *)ICall_allocMsg(sizeof(npiPkt_t) + len);

 if (pNpiPkt)
 {
   pNpiPkt->hdr.event = buf[0]; //Has the event status code in first byte of payload
   pNpiPkt->hdr.status = 0xFF;
   pNpiPkt->pktLen = len;
   pNpiPkt->pData  = (uint8 *)(pNpiPkt + 1);

   memcpy(pNpiPkt->pData, buf, len);

   // Send to NPI
   // Note: there is no need to free this packet.  NPI will do that itself.
   NPITask_sendToHost((uint8_t *)pNpiPkt);
 }
}
#endif // PTM_MODE

//This callbackfn activates when SPI buffer has received enough SPI_TRANS_LEN data
//It copies receiveBuffer to TxBuffToComputer which will be sent to Central via BLE periodic task
void SpiCallbackfn(SPI_Handle handle, SPI_Transaction *transaction)
{
    if (transaction->count == SPI_TRANS_LEN)
    {
        memcpy(TxBuffToComputer,receiveBuffer_spi,transaction->count);
        PIN_setOutputValue(Spi_sensorboard_cs_handle, CC1352R1_LAUNCHXL_SPI1_CSN, 1);
        //UserEvents |= SP_SPI_FINISH_EVT;
        isSPItrasferfinished = true;
        //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
        //Semaphore_post(sem);
        SimplePeripheral_enqueueMsg(SP_SPI_FINISH_EVT, NULL);
    }
    return;
}
void UART_Write_Callback(UART_Handle handle, void *buffer, size_t size) {
    asm(" NOP");
}

void UART_Read_Callback(UART_Handle handle, void *buffer, size_t size)
{
    SimplePeripheral_enqueueMsg(SP_UART_READ_EVT, NULL);
}

static void SimpleBLEPeripheral_TransmitSensorData(void)
{
    if (connectionFlag && (notifyEnable & GATT_CLIENT_CFG_NOTIFY))
    {
        SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR4, SIMPLEPROFILE_CHAR4_LEN, TxBuffToComputer);
    }
}

static void SimpleBLEPeripheral_ReadSensorPreset(uint8_t cmd) // 0xFF: request IMU, 0xFE: update pos+spd+matrix, 0xFD: update destination
{
    uint8_t temp;

    transmitBuffer_spi[0] = 'S';
    transmitBuffer_spi[SPI_TRANS_LEN-1] = 'X';
    temp = Hex2num_byte(&transmitBuffer_spi[1]);
    temp++;
    Num2hex_byte(&transmitBuffer_spi[1], temp);
    temp = cmd;
    if (temp == 0)
        return;
    Num2hex_byte(&transmitBuffer_spi[212], temp);

    while (PIN_getInputValue(CC1352_SPI1_CTS_BLE_EXT))
    {
        Task_sleep(10000);
    }

    PIN_setOutputValue(Spi_sensorboard_cs_handle, CC1352R1_LAUNCHXL_SPI1_CSN, 0);
    if (SPI_transfer(handle_spi, &Transaction_spi))
    {
        if (temp == 0xFF) // read IMU command
        {
            bleSend = FALSE; // disable BLE sending for this time
        }
        else if (temp == 0xFE || temp == 0xFD) // sent position to backpack
        {
            bleSend = FALSE; // disable BLE sending for this time
        }
        else
        {
            bleSend = TRUE; // enable BLE sending
        }
    }
    else
    {
        bleSend = FALSE; // disable BLE sending for this time
    }
}
/*********************************************************************
 * @fn      SimplePeripheral_createTask
 *
 * @brief   Task creation function for the Simple Peripheral.
 */
void SimplePeripheral_createTask(void)
{
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = spTaskStack;
  taskParams.stackSize = SP_TASK_STACK_SIZE;
  taskParams.priority = SP_TASK_PRIORITY;

  Task_construct(&spTask, SimplePeripheral_taskFxn, &taskParams, NULL);
}
//Simple func to init a buffer array to send to Central
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
void GPS_Wakeup(void)
{
    while (PIN_getInputValue(Board_GPS_WAKE) == 0)
    {
        PIN_setOutputValue(GPSPinHandle, Board_GPS_ONOFF, 0);
        PIN_setOutputValue(ledPinHandle, Board_LED1, 0);
        PIN_setOutputValue(ledPinHandle, Board_LED2, 0);
        delay_ms(100);
        PIN_setOutputValue(GPSPinHandle, Board_GPS_ONOFF, 1);
        PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
        PIN_setOutputValue(ledPinHandle, Board_LED2, 1);
        delay_ms(1000);
        PIN_setOutputValue(GPSPinHandle, Board_GPS_ONOFF, 0);
        PIN_setOutputValue(ledPinHandle, Board_LED1, 0);
        PIN_setOutputValue(ledPinHandle, Board_LED2, 0);
        delay_ms(100);
     }
     PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
     PIN_setOutputValue(ledPinHandle, Board_LED2, 0);
}
//static void simpleData_init(void)
//{
//    // Fill buffer
//                    // start stop
//                   BLE5sendbuff[0] = 83;
//                   BLE5sendbuff[SPI_TRANS_LEN-1] = 88;
//                   // command count
//                   BLE5sendbuff[1] = 0;
//                   BLE5sendbuff[2] = 0;
//
//                   // command sub
//                   //SendCMDcnt_sub = 1;
//                   BLE5sendbuff[3] = 0;
//                   BLE5sendbuff[4] = 0;
//                   // Data
//                   // CO2 sensor
//                   //extern uint16_t CO2val;
//                   uint16_t CO2val = 0xABCD;
//                   BLE5sendbuff[5] = Num2textbyte((CO2val>>12) & 0x000F);
//                   BLE5sendbuff[6] = Num2textbyte((CO2val>>8)  & 0x000F);
//                   BLE5sendbuff[7] = Num2textbyte((CO2val>>4)  & 0x000F);
//                   BLE5sendbuff[8] = Num2textbyte(CO2val & 0x000F);
//                   //extern uint16_t TVOCval;
//                   uint16_t TVOCval = 0x9911;
//                   BLE5sendbuff[9] = Num2textbyte((TVOCval>>12) & 0x000F);
//                   BLE5sendbuff[10] = Num2textbyte((TVOCval>>8)  & 0x000F);
//                   BLE5sendbuff[11] = Num2textbyte((TVOCval>>4)  & 0x000F);
//                   BLE5sendbuff[12] = Num2textbyte(TVOCval & 0x000F);
//                   for(int i=13;i<SPI_TRANS_LEN-1;i++)
//                   {
//                       BLE5sendbuff[i]=1;
//                   }
//    memcpy(TxBuffToComputer,BLE5sendbuff,SPI_TRANS_LEN);
//}
/*********************************************************************
 * @fn      SimplePeripheral_init
 *
 * @brief   Called during initialization and contains application
 *          specific initialization (ie. hardware initialization/setup,
 *          table initialization, power up notification, etc), and
 *          profile initialization/setup.
 */
static void SimplePeripheral_init(void)
{
  // ******************************************************************
  // N0 STACK API CALLS CAN OCCUR BEFORE THIS CALL TO ICall_registerApp
  // ******************************************************************
  // Register the current thread as an ICall dispatcher application
  // so that the application can send and receive messages.
  ICall_registerApp(&selfEntity, &syncEvent);

#ifdef USE_RCOSC
  RCOSC_enableCalibration();
#endif // USE_RCOSC

  // Create an RTOS queue for message from profile to be sent to app.
  appMsgQueueHandle = Util_constructQueue(&appMsgQueue);

  // Create one-shot clock for internal periodic events.
  Util_constructClock(&clkPeriodic, SimplePeripheral_clockHandler,
                      SP_PERIODIC_EVT_PERIOD, 0, false, (UArg)&argPeriodic);
  //User clock
  Util_constructClock(&clkUART, SimplePeripheral_clockHandler,
                        5000, 0, false, (UArg)&argGPS);//10

  Util_constructClock(&clkMcuTransaction, SimplePeripheral_clockHandler,
                      MCU_PERIODIC_READ, 0, false, (UArg)&argMcuTransaction); //
  // semaphore delay
      Semaphore_Params semdelayparam;
      Semaphore_Params_init(&semdelayparam);
      semdelayparam.mode = Semaphore_Mode_BINARY;
      Semaphore_construct(&Semdelay_s, 0, &semdelayparam);
      Semdelayhdl = Semaphore_handle(&Semdelay_s);
  // 1ms clock tick
  Util_constructClock(&Mscounter_s, Mscounter_clockHandler,
                        1, 1, true, NULL);
  delaycountstarted = false;
  Mscounteslapsed = 0;
  Delayduration = 0;
  mstimecnt = 0;

  HCI_EXT_SetTxPowerCmd(HCI_EXT_TX_POWER_5_DBM);
  // Set the Device Name characteristic in the GAP GATT Service
  // For more information, see the section in the User's Guide:
  // http://software-dl.ti.com/lprf/ble5stack-latest/
  GGS_SetParameter(GGS_DEVICE_NAME_ATT, GAP_DEVICE_NAME_LEN, attDeviceName);

  // Configure GAP
  {
    uint16_t paramUpdateDecision = DEFAULT_PARAM_UPDATE_REQ_DECISION;

    // Pass all parameter update requests to the app for it to decide
    GAP_SetParamValue(GAP_PARAM_LINK_UPDATE_DECISION, paramUpdateDecision);
  }

  // Setup the GAP Bond Manager. For more information see the GAP Bond Manager
  // section in the User's Guide:
  // http://software-dl.ti.com/lprf/ble5stack-latest/
  {
    //   uint32_t passkey = 0; // passkey "000000"
    // Don't send a pairing request after connecting; the peer device must
    // initiate pairing
    uint8_t pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
    // Use authenticated pairing: require passcode.
    uint8_t mitm = TRUE;
    // This device only has display capabilities. Therefore, it will display the
    // passcode during pairing. However, since the default passcode is being
    // used, there is no need to display anything.
    uint8_t ioCap = GAPBOND_IO_CAP_DISPLAY_ONLY;
    // Request bonding (storing long-term keys for re-encryption upon subsequent
    // connections without repairing)
    uint8_t bonding = TRUE;

    //GAPBondMgr_SetParameter(GAPBOND_DEFAULT_PASSCODE, sizeof(uint32_t),
    //                            &passkey);
    GAPBondMgr_SetParameter(GAPBOND_PAIRING_MODE, sizeof(uint8_t), &pairMode);
    GAPBondMgr_SetParameter(GAPBOND_MITM_PROTECTION, sizeof(uint8_t), &mitm);
    GAPBondMgr_SetParameter(GAPBOND_IO_CAPABILITIES, sizeof(uint8_t), &ioCap);
    GAPBondMgr_SetParameter(GAPBOND_BONDING_ENABLED, sizeof(uint8_t), &bonding);
  }

  // Initialize GATT attributes
  GGS_AddService(GATT_ALL_SERVICES);           // GAP GATT Service
  GATTServApp_AddService(GATT_ALL_SERVICES);   // GATT Service
  DevInfo_AddService();                        // Device Information Service
  SimpleProfile_AddService(GATT_ALL_SERVICES); // Simple GATT Profile

  // Setup the SimpleProfile Characteristic Values
  // For more information, see the GATT and GATTServApp sections in the User's Guide:
  // http://software-dl.ti.com/lprf/ble5stack-latest/
  {
          uint8_t charValue1 = 1;
          uint8_t charValue2 = 2;
          uint8_t charValue5[SIMPLEPROFILE_CHAR5_LEN] = { 1, 2, 3, 4, 5 };

          SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR1, sizeof(uint8_t),
                                     &charValue1);
          SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR2, sizeof(uint8_t),
                                     &charValue2);
          SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR3, SIMPLEPROFILE_CHAR3_LEN,
                                     spTaskStack);
          SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR4, SIMPLEPROFILE_CHAR4_LEN,
                                     spTaskStack);
          SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR5, SIMPLEPROFILE_CHAR5_LEN,
                                     charValue5);
  }

  // Register callback with SimpleGATTprofile
  //SimpleProfile_RegisterAppCBs(&SimplePeripheral_simpleProfileCBs);
  SimpleProfile_RegisterAppCBs(&SimplePeripheral_simpleProfileCBs);

  // Start the Device; this is from BLE4
  //  VOID GAPRole_StartDevice(&SimpleBLEPeripheral_gapRoleCBs);

  // Start Bond Manager and register callback
  VOID GAPBondMgr_Register(&SimplePeripheral_BondMgrCBs);

  // Register with GAP for HCI/Host messages. This is needed to receive HCI
  // events. For more information, see the HCI section in the User's Guide:
  // http://software-dl.ti.com/lprf/ble5stack-latest/
  GAP_RegisterForMsgs(selfEntity);

  // Register for GATT local events and ATT Responses pending for transmission
  GATT_RegisterForMsgs(selfEntity);

  //HCI_LE_ReadMaxDataLenCmd();//This is from BLE4
  // Set default values for Data Length Extension
  // Extended Data Length Feature is already enabled by default
  {
    // Set initial values to maximum, RX is set to max. by default(251 octets, 2120us)
    // Some brand smartphone is essentially needing 251/2120, so we set them here.
    #define APP_SUGGESTED_PDU_SIZE 251 //default is 27 octets(TX)
    #define APP_SUGGESTED_TX_TIME 2120 //default is 328us(TX)

    // This API is documented in hci.h
    // See the LE Data Length Extension section in the BLE5-Stack User's Guide for information on using this command:
    // http://software-dl.ti.com/lprf/ble5stack-latest/
    HCI_LE_WriteSuggestedDefaultDataLenCmd(APP_SUGGESTED_PDU_SIZE, APP_SUGGESTED_TX_TIME);
  }

  // Initialize GATT Client
   GATT_InitClient();

  // Init key debouncer
 // Board_initKeys(SimplePeripheral_keyChangeHandler);

  // Initialize Connection List
  SimplePeripheral_clearConnListEntry(LINKDB_CONNHANDLE_ALL);

  //Initialize GAP layer for Peripheral role and register to receive GAP events
  GAP_DeviceInit(GAP_PROFILE_PERIPHERAL, selfEntity, addrMode, NULL);

  // Initialize array to store connection handle and RSSI values
  SimplePeripheral_initPHYRSSIArray();

  // The type of display is configured based on the BOARD_DISPLAY_USE...
  // preprocessor definitions
  //dispHandle = Display_open(Display_Type_ANY, NULL);
  //UART_read(uartHandle, uartBuf, 1);

  // Initialize Two-Button Menu module
  //TBM_SET_TITLE(&spMenuMain, "Simple Peripheral");
  //tbm_setItemStatus(&spMenuMain, TBM_ITEM_NONE, TBM_ITEM_ALL);

  //tbm_initTwoBtnMenu(dispHandle, &spMenuMain, 2, SimplePeripheral_menuSwitchCb);
  //Display_printf(dispHandle, SP_ROW_SEPARATOR_1, 0, "====================");

#ifdef PTM_MODE
  // Intercept NPI RX events.
  NPITask_registerIncomingRXEventAppCB(simple_peripheral_handleNPIRxInterceptEvent, INTERCEPT);

  // Register for Command Status information
  HCI_TL_Init(NULL, (HCI_TL_CommandStatusCB_t) simple_peripheral_sendToNPI, NULL, selfEntity);

  // Register for Events
  HCI_TL_getCmdResponderID(ICall_getLocalMsgEntityId(ICALL_SERVICE_CLASS_BLE_MSG, selfEntity));

  // Inform Stack to Initialize PTM
  HCI_EXT_EnablePTMCmd();
#endif // PTM_MODE
  //========================End Sample PeripheralInit=============================
  // Open Pins on board
      //GPSPinHandle = PIN_open(&GPSPinState, GPSPinTable);
      ledPinHandle = PIN_open(&ledPinState, ledPinTable);

      //PIN_setOutputValue(GPSPinHandle, Board_GPS_POWER, 1);

      if(!ledPinHandle) {
            while(1);
      }

     //GPS_Wakeup();
     //GPSinfo.longitude = 0;
     //GPSinfo.latitude = 0;
     //GPSinfo.altitude = 0;
     //GPSinfo.FixIndicate = 0;
     //GPSinfo.UTCtime = 0;
  // SPI initialization

    SPI_Params      spiParams;
    SPI_init();  // Initialize the SPI driver
    SPI_Params_init(&spiParams);  // Initialize SPI parameters
    spiParams.dataSize = 8;       // 8-bit data size
    spiParams.bitRate = 4000000;
    spiParams.mode = SPI_MASTER;//SPI_MASTER;//
    spiParams.transferMode = SPI_MODE_CALLBACK;
    spiParams.transferCallbackFxn = SpiCallbackfn;
    spiParams.frameFormat = SPI_POL0_PHA1;//SPI_POL0_PHA0;

    handle_spi = SPI_open(Board_SPI1, &spiParams);
    if (handle_spi == NULL)
    {
        while(1);
    }
    Transaction_spi.count = SPI_TRANS_LEN;
    Transaction_spi.rxBuf = receiveBuffer_spi;
    Transaction_spi.txBuf = transmitBuffer_spi;

 // UART handles GPS
    UART_Params uartParams;
    UART_init();
    UART_Params_init(&uartParams);
    uartParams.readMode = UART_MODE_CALLBACK;
    uartParams.readCallback = UART_Read_Callback;
    uartParams.writeMode = UART_MODE_CALLBACK;
    uartParams.writeCallback = UART_Write_Callback;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.readTimeout = UART_WAIT_FOREVER;
    uartParams.baudRate = 4800;

    uartHandle = UART_open(Board_UART1, &uartParams);
    if (uartHandle == NULL)
    {
        while(1);
    }

    isPeriodicDataCollection = false;
    PeriodicCollectCnt = 0;
    isNewrequestcome = false;
    isAutoSendTriggered = false;
    isForwardingFinished = true;
    isSendbackFinished  = true;
    isSPItrasferfinished = false;
    Datafusionsendback = false;
    FusionOnOff = true;
    FusionOnOffOld = true;
    isWaitingforIMU = false;
    NumberofRemainingdata = 0;
    SPItrasfercase = 0;
    Spi_sensorboard_cs_handle = PIN_open(&SpiSensorCSPinState, SpiSensorCSPinTable);
    // Chip select
    PIN_setOutputValue(Spi_sensorboard_cs_handle, CC1352R1_LAUNCHXL_SPI1_CSN, 1);

  //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));//Toggle the LED
  // Start periodic timer
    Util_startClock(&clkPeriodic);
  //  PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
    Util_startClock(&clkMcuTransaction);
   // Util_startClock(&clkUART);

    UART_read(uartHandle, uartBuf, 1);
    PIN_setOutputValue(ledPinHandle, Board_LED2, 1);
}

/*********************************************************************
 * @fn      SimplePeripheral_taskFxn
 *
 * @brief   Application task entry point for the Simple Peripheral.
 *
 * @param   a0, a1 - not used.
 */
static void SimplePeripheral_taskFxn(UArg a0, UArg a1)
{
  // Initialize application
  SimplePeripheral_init();

  // Application main loop
  for (;;)
  {
    uint32_t events;

    // Waits for an event to be posted associated with the calling thread.
    // Note that an event associated with a thread is posted when a
    // message is queued to the message receive queue of the thread
    events = Event_pend(syncEvent, Event_Id_NONE, SP_ALL_EVENTS,
                        ICALL_TIMEOUT_FOREVER);

    if (events)
    {
      ICall_EntityID dest;
      ICall_ServiceEnum src;
      ICall_HciExtEvt *pMsg = NULL;

      // Fetch any available messages that might have been sent from the stack
      if (ICall_fetchServiceMsg(&src, &dest,
                                (void **)&pMsg) == ICALL_ERRNO_SUCCESS)
      {
        uint8 safeToDealloc = TRUE;

        if ((src == ICALL_SERVICE_CLASS_BLE) && (dest == selfEntity))
        {
          ICall_Stack_Event *pEvt = (ICall_Stack_Event *)pMsg;

          // Check for BLE stack events first
          if (pEvt->signature != 0xffff)
          {
            // Process inter-task message
            safeToDealloc = SimplePeripheral_processStackMsg((ICall_Hdr *)pMsg);
          }
        }

        if (pMsg && safeToDealloc)
        {
          ICall_freeMsg(pMsg);
        }
      }
     // PIN_setOutputValue(ledPinHandle, Board_LED2, 1);
      // If RTOS queue is not empty, process app message.
      if (events & SP_QUEUE_EVT)
      {
        while (!Queue_empty(appMsgQueueHandle))
        {
          spEvt_t *pMsg = (spEvt_t *)Util_dequeueMsg(appMsgQueueHandle);
          if (pMsg)
          {
            // Process message.
            SimplePeripheral_processAppMsg(pMsg);

            // Free the space from the message.
            ICall_free(pMsg);
          }
        }
      }
    }
  }
}
/*********************************************************************
 * @fn      SimplePeripheral_processAppMsg
 *
 * @brief   Process an incoming callback from a profile.
 *
 * @param   pMsg - message to process
 *
 * @return  None.
 */
static void SimplePeripheral_processAppMsg(spEvt_t *pMsg)
{
  bool dealloc = TRUE;
  int checkGPSread = -1;
  switch (pMsg->event)
  {
    case SP_CHAR_CHANGE_EVT:
      SimplePeripheral_processCharValueChangeEvt(*(uint8_t*)(pMsg->pData));
      break;

    case SP_KEY_CHANGE_EVT:
      //SimplePeripheral_handleKeys(*(uint8_t*)(pMsg->pData));
      break;

    case SP_ADV_EVT:
      SimplePeripheral_processAdvEvent((spGapAdvEventData_t*)(pMsg->pData));
      break;

    case SP_PAIR_STATE_EVT:
      SimplePeripheral_processPairState((spPairStateData_t*)(pMsg->pData));
      break;

    case SP_PASSCODE_EVT:
      SimplePeripheral_processPasscode((spPasscodeData_t*)(pMsg->pData));
      break;

    case SP_SPI_FINISH_EVT:
    {
        //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
        //SimplePeripheral_performPeriodicTask();
        //break;
        if ((TxBuffToComputer[0] == 'S') && (TxBuffToComputer[BLE_TRANS_LEN - 1] == 'X'))
                {
                    CmdSub = Hex2num_byte(&TxBuffToComputer[3]);
                    if (CmdSub == 0x01)
                    {
                        //Num2hex_byte(&TxBuffToComputer[3], 0x21);
                        UpdateGPSPosition4TxBuffToComputer();
//                        PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));
                    }

                }
        //SimpleBLEPeripheral_TransmitSensorData(); // Transfer IMU data to PC via BLE
        SimplePeripheral_performPeriodicTask(); // Transfer IMU data to PC via BLE
        break;
    }
    //TODO

    case SP_PERIODIC_EVT:
    {
//        SimpleBLEPeripheral_ReadSensorPreset(0x01); // collect IMU data via SPI
          // If no active connections
//        if (isconnected == false)
//          {
//            // Stop periodic clock
//            Util_stopClock(&clkPeriodic);
//          }
        //MCUDataTransaction();
        isPeriodicDataCollection = true;
        PeriodicCollectCnt = 0;
        break;
    }

    case SP_MCU_TRANS_EVT:
        {
            // If no active connections
//            if (isconnected == false)
//            {
//              // Stop periodic clock
//              Util_stopClock(&clkMcuTransaction);
//            }
            MCUDataTransaction();
            break;
        }

    case SP_UART_READ_EVT:
//      Util_stopClock(&clkUART);
//      GPSbuf[uartNum] = uartBuf[0];
//      uartNum++;
//      Util_startClock(&clkUART);
//      UART_read(uartHandle, uartBuf, 1);
      break;


    case SP_GPS_DONE_EVT:
//      Util_stopClock(&clkMcuTransaction);
//      //SimpleBLEPeripheral_ReadSensorPreset(0xFF); // request IMU data
//      if (PIN_getInputValue(Board_GPS_WAKE) == 0)
//              GPSconsisent++;
//      if (GPSconsisent>=1000)
//      {
//          GPSconsisent = 0;
//          //GPS_Wakeup();
//      }
//
//      if(uartNum>=80)
//      {
//          PIN_setOutputValue(ledPinHandle, Board_LED1, 0);
//          //checkGPSread = GPS_readNew(GPSbuf, &GPSinfo);    // TODO: GPS read and analysis
////          checkGPSread = GPS_readNewTest(bufftest, &GPSinfo);    // TODO: GPS read and analysis
//          imuRequest = true;
//      }
//      if (checkGPSread >= 0)
//      {
//          gpsCalDone = TRUE;
//          memset(GPSbuf, 0, uartNum);
//          uartNum = 0;
////          if (GPSinfo.FixIndicate > 0)
////              PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
////          else
////              PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
//      }
//
//      Util_startClock(&clkMcuTransaction);
      break;


    case SP_READ_RPA_EVT:
          SimplePeripheral_updateRPA();
          break;

    case SP_SEND_PARAM_UPDATE_EVT:
    {
      // Extract connection handle from data
      uint16_t connHandle = *(uint16_t *)(((spClockEventData_t *)pMsg->pData)->data);

      SimplePeripheral_processParamUpdate(connHandle);

      // This data is not dynamically allocated
      dealloc = FALSE;
      break;
    }

    case SP_CONN_EVT:
      SimplePeripheral_processConnEvt((Gap_ConnEventRpt_t *)(pMsg->pData));
      break;

    default:
      // Do nothing.
      break;
  }

  // Free message data if it exists and we are to dealloc
  if ((dealloc == TRUE) && (pMsg->pData != NULL))
  {
    ICall_free(pMsg->pData);
  }
}

static void UpdateGPSPosition4TxBuffToComputer(void)
{
    #ifdef GPS_ONLY
                if (isGPSonly)
                {
                    if (gpsCalDone) // update position every (SCAN_TIMES_FOR_FUSION) seconds
                    {
                        gpsCalDone = FALSE;
                        posGPS[0] = GPSinfo.latitude;
                        posGPS[1] = GPSinfo.longitude;
                        posFusion[0] = posGPS[0];
                        posFusion[1] = posGPS[1];
                        PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
                    }

                    Num2hex_float(&TxBuffToComputer[125], posFusion[0]);
                    Num2hex_float(&TxBuffToComputer[133], posFusion[1]);
//                    Num2hex_float(&TxBuffToComputer[117], posGPS[0]);
//                    Num2hex_float(&TxBuffToComputer[141], posGPS[1]);

                    Num2hex_float(&TxBuffToComputer[117], GPSinfo.checkSum);
                    Num2hex_float(&TxBuffToComputer[141], GPSinfo.maxLen);
                    Num2hex_float(&TxBuffToComputer[209], GPSinfo.FixIndicate);
                    Num2hex_float(&TxBuffToComputer[217], GPSinfo.SatelliteNum);


                }
    #endif //GPS_ONLY
    #ifdef DATA_FUSION
                if (gpsCalDone) // update position every (SCAN_TIMES_FOR_FUSION) seconds
                {
                    gpsCalDone = FALSE;

                    // read the received data
                    speed[0] = Hex2num_float(&TxBuffToComputer[101]);
                    speed[1] = Hex2num_float(&TxBuffToComputer[109]);
                    position[0] = Hex2num_float(&TxBuffToComputer[125]);
                    position[1] = Hex2num_float(&TxBuffToComputer[133]);
                    p_matrix[0] = Hex2num_float(&TxBuffToComputer[149]);
                    p_matrix[1] = Hex2num_float(&TxBuffToComputer[157]);
                    p_matrix[2] = Hex2num_float(&TxBuffToComputer[165]);

                    posGPS[0] = GPSinfo.latitude;
                    posGPS[1] = GPSinfo.longitude;

                    if (fabs(position[0]) <= 0.01f && fabs(position[1] <= 0.01f)) // finding initial position before imu data come
                    {
//                                posFusion[0] = (pointFusion[0] * 2 + posGPS[0]) / 3;//This is LiYao formula, need to clarify
//                                posFusion[1] = (pointFusion[1] * 2 + posGPS[1]) / 3;
                        posFusion[0] = (posFusion[0] * 2 + posGPS[0]) / 3;
                        posFusion[1] = (posFusion[1] * 2 + posGPS[1]) / 3;
                        Num2hex_float(&TxBuffToComputer[125], posFusion[0]);
                        Num2hex_float(&TxBuffToComputer[133], posFusion[1]);
                    }
                    else
                    {
                        // calculate the received data
                        Kalman_update(p_matrix, position, speed, posGPS);
                        // update the buffer for sending
                        Num2hex_float(&TxBuffToComputer[101], speed[0]);
                        Num2hex_float(&TxBuffToComputer[109], speed[1]);
                        Num2hex_float(&TxBuffToComputer[125], position[0]);
                        Num2hex_float(&TxBuffToComputer[133], position[1]);
                        Num2hex_float(&TxBuffToComputer[149], p_matrix[0]);
                        Num2hex_float(&TxBuffToComputer[157], p_matrix[1]);
                        Num2hex_float(&TxBuffToComputer[165], p_matrix[2]);

                        posFusion[0] = position[0];
                        posFusion[1] = position[1];

                        memcpy(&transmitBuffer_spi[101], &TxBuffToComputer[101], 72);
                        SimpleBLEPeripheral_ReadSensorPreset(0xFE); // update new position to sensor board via SPI
                    }
                }
                Num2hex_float(&TxBuffToComputer[117], posGPS[0]);
                Num2hex_float(&TxBuffToComputer[141], posGPS[1]);
    #endif //DATA_FUSION

}
// TODO
static void BLESendbackdata(void)
{
    //uint8_t connIndex = SimplePeripheral_getConnIndex(connHandle);
    //uint8_t connIndex = SimplePeripheral_getConnIndex(menuConnHandle);
    //bStatus_t status;
    //PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));
    if (starthandleflag)
    {
        // get Character4 handle
        //noti.handle = Character4handle; //it is already the only connected handle
        SimpleProfile_SetParameter(SIMPLEPROFILE_CHAR4, SIMPLEPROFILE_CHAR4_LEN,TxBuffToComputer);
        noti.len = lensend;
        //GAPRole_GetParameter(GAPROLE_CONNHANDLE, &connectionHandleSend);
        starthandleflag = false;
    }

    else
    {
        noti.pValue = (uint8 *)GATT_bm_alloc( connectionHandleSend, ATT_HANDLE_VALUE_NOTI, GATT_MAX_MTU, &lensend );
        if ( noti.pValue != NULL ) //if allocated
        {
            //PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
            //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
            memcpy(noti.pValue,TxBuffToComputer,lensend);
            noti.handle = Character4handle;
            noti.len = lensend;
            // Attempt to send the notification
            status_noti = GATT_Notification( connectionHandleSend, &noti, FALSE);
            if ( status_noti != SUCCESS ) //if noti not sent
            {
                GATT_bm_free( (gattMsg_t *)&noti, ATT_HANDLE_VALUE_NOTI );
                isSendbackFinished = false;
                NumberofRemainingdata++;
                //PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
                //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
            }
            else    //if noti is sent
            {
                asm(" NOP");
                isSendbackFinished = true;
                NumberofRemainingdata = 0;
                //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
            }
        }
        else
        {
            asm(" NOP");
            isSendbackFinished = false;
            NumberofRemainingdata++;
            //PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// SPI communication
//TODO
static void MCUDataTransaction(void)
{
    // skip SPI transfer if the slave is not ready
    uint8_t newValue;
    uint8_t cmdtemp[2];
    bool    cantransfer;
    bool    skiptransfer;
    // LED blinks if success transfer

    //PIN_setOutputValue(ledPinHandle, Board_LED1, 1);
    newValue =  PIN_getInputValue(CC1352_SPI1_CTS_BLE_EXT);
    // check transfer condition
    if(newValue == 0)
    {
        if(isSendbackFinished)
        {
            if (Transaction_spi.status == SPI_TRANSFER_COMPLETED)
                cantransfer = true;
            else if (Transaction_spi.status == SPI_TRANSFER_STARTED)
                cantransfer = false;
            else
            {
                SPI_transferCancel(handle_spi); // cancel current transfer
                cantransfer = true;
            }
        }
        else
            cantransfer = false;
    }
    // TODO
    if(cantransfer)
    {

        // decide transfer case
        if (FusionOnOff)
        { // fusion on, periodic trigger
            if(isPeriodicDataCollection) // time tick requesting IMU for fusion
            {
                SPItrasfercase = 1;
                isPeriodicDataCollection = false;
                PeriodicCollectCnt++;
                isWaitingforIMU = true;
            }
            else if(isNewrequestcome) // forward data
            {
                isNewrequestcome = false;
                SPItrasfercase = 3;
                if(PeriodicCollectCnt < 3)
                {
                    PeriodicCollectCnt++;
                }
            }
            else if (PeriodicCollectCnt == 1)
            {
                SPItrasfercase = 2;
                PeriodicCollectCnt++;
            }
            else if (PeriodicCollectCnt == 2)
            {
                SPItrasfercase = 4;
                PeriodicCollectCnt++;
            }
            else // Do nothing
            {
                SPItrasfercase = 0;
            }
        }
        else
        {
            if(isNewrequestcome) // forward data
            {
                isNewrequestcome = false;
                SPItrasfercase = 3;
            }
            else if(isAutoSendTriggered)
            {
                SPItrasfercase = 5;
            }
            else
            {
                SPItrasfercase = 0;
            }
        }

        // Preparing data to transfer
        skiptransfer = false;

        transmitBuffer_spi[0] = 'S';
        transmitBuffer_spi[UART_RECEIVE_LEN - 1] = 'X';
        switch(SPItrasfercase)
        {
        case 1: // Request IMU data for fusion
            CMDTransmitnumbertemp = CMDTransmitnumberOld--; // reduce
            transmitBuffer_spi[1] = CMDTransmitnumbertemp>>4;
            transmitBuffer_spi[2] = CMDTransmitnumbertemp & 0x0F;
            // Request data
            transmitBuffer_spi[188] = 'F';
            transmitBuffer_spi[189] = 'F';
            break;
        case 2: // Collect IMU data for fusion
            // Dummy data
            CMDTransmitnumbertemp++; // reduce
            transmitBuffer_spi[1] = CMDTransmitnumbertemp>>4;
            transmitBuffer_spi[2] = CMDTransmitnumbertemp & 0x0F;
            // Request data
            transmitBuffer_spi[188] = '8';
            transmitBuffer_spi[189] = '1';
            break;
        case 3: // Forward data form BLE
            CMDTransmitnumberOld = CMDTransmitnumber;
            cmdtemp[0] = RxBuffFromComputer[1];
            cmdtemp[1] = RxBuffFromComputer[2];
            cmdtemp[0] = (cmdtemp[0] >= 65 ? (uint8_t)(cmdtemp[0] - 55) : (uint8_t)(cmdtemp[0] - 48));
            cmdtemp[1] = (cmdtemp[1] >= 65 ? (uint8_t)(cmdtemp[1] - 55) : (uint8_t)(cmdtemp[1] - 48));
            CMDTransmitnumber = (cmdtemp[0]<<4)|(cmdtemp[1]);
            memcpy(transmitBuffer_spi,RxBuffFromComputer,UART_RECEIVE_LEN);
            break;
        case 4: // Send fusion data back MCU
            CMDTransmitnumbertemp = CMDTransmitnumberOld;
            transmitBuffer_spi[1] = CMDTransmitnumbertemp>>4;
            transmitBuffer_spi[2] = CMDTransmitnumbertemp & 0x0F;
            // RequestData
            transmitBuffer_spi[188] = 'F';
            transmitBuffer_spi[189] = 'E';
            break;
        case 5: // Auto collect data without trigger, only for Memory read command
            // dummy data
            CMDTransmitnumbertemp++; // reduce
            transmitBuffer_spi[1] = CMDTransmitnumbertemp>>4;
            transmitBuffer_spi[2] = CMDTransmitnumbertemp & 0x0F;
            // Request data
            transmitBuffer_spi[188] = '8';
            transmitBuffer_spi[189] = '1';
            break;
        default: // Do nothing
            skiptransfer = true;
            break;
        }
        // SPI transfer
        if (!skiptransfer)
        {
            Transaction_spi.count = UART_RECEIVE_LEN;
            PIN_setOutputValue(Spi_sensorboard_cs_handle, CC1352R1_LAUNCHXL_SPI1_CSN, 0);
            transferOK = SPI_transfer(handle_spi, &Transaction_spi);
            //PIN_setOutputValue(ledPinHandle, Board_LED0, !PIN_getOutputValue(Board_LED0));
        }
    }
}

/*********************************************************************
 * @fn      SimplePeripheral_processStackMsg
 *
 * @brief   Process an incoming stack message.
 *
 * @param   pMsg - message to process
 *
 * @return  TRUE if safe to deallocate incoming message, FALSE otherwise.
 */
static uint8_t SimplePeripheral_processStackMsg(ICall_Hdr *pMsg)
{
  // Always dealloc pMsg unless set otherwise
  uint8_t safeToDealloc = TRUE;

  switch (pMsg->event)
  {
    case GAP_MSG_EVENT:
      SimplePeripheral_processGapMessage((gapEventHdr_t*) pMsg);
      break;

    case GATT_MSG_EVENT:
      // Process GATT message
      safeToDealloc = SimplePeripheral_processGATTMsg((gattMsgEvent_t *)pMsg);
      break;

    case HCI_GAP_EVENT_EVENT:
    {
      // Process HCI message
      switch(pMsg->status)
      {
        case HCI_COMMAND_COMPLETE_EVENT_CODE:
        // Process HCI Command Complete Events here
        {
          SimplePeripheral_processCmdCompleteEvt((hciEvt_CmdComplete_t *) pMsg);
          break;
        }

        case HCI_BLE_HARDWARE_ERROR_EVENT_CODE:
          AssertHandler(HAL_ASSERT_CAUSE_HARDWARE_ERROR,0);
          break;

        // HCI Commands Events
        case HCI_COMMAND_STATUS_EVENT_CODE:
        {
          hciEvt_CommandStatus_t *pMyMsg = (hciEvt_CommandStatus_t *)pMsg;
          switch ( pMyMsg->cmdOpcode )
          {
            case HCI_LE_SET_PHY:
            {
              if (pMyMsg->cmdStatus == HCI_ERROR_CODE_UNSUPPORTED_REMOTE_FEATURE)
              {
               // Display_printf(dispHandle, SP_ROW_STATUS_1, 0,
               //         "PHY Change failure, peer does not support this");
              }
              else
              {
               // Display_printf(dispHandle, SP_ROW_STATUS_1, 0,
               //                "PHY Update Status Event: 0x%x",
               //                pMyMsg->cmdStatus);
              }

              SimplePeripheral_updatePHYStat(HCI_LE_SET_PHY, (uint8_t *)pMsg);
              break;
            }

            default:
              break;
          }
          break;
        }

        // LE Events
        case HCI_LE_EVENT_CODE:
        {
          hciEvt_BLEPhyUpdateComplete_t *pPUC =
            (hciEvt_BLEPhyUpdateComplete_t*) pMsg;

          // A Phy Update Has Completed or Failed
          if (pPUC->BLEEventCode == HCI_BLE_PHY_UPDATE_COMPLETE_EVENT)
          {
            if (pPUC->status != SUCCESS)
            {
           //   Display_printf(dispHandle, SP_ROW_STATUS_1, 0,
           //                  "PHY Change failure");
            }
            else
            {
              // Only symmetrical PHY is supported.
              // rxPhy should be equal to txPhy.
            //  Display_printf(dispHandle, SP_ROW_STATUS_2, 0,
           //                  "PHY Updated to %s",
           //                  (pPUC->rxPhy == PHY_UPDATE_COMPLETE_EVENT_1M) ? "1M" :
           //                  (pPUC->rxPhy == PHY_UPDATE_COMPLETE_EVENT_2M) ? "2M" :
           //                  (pPUC->rxPhy == PHY_UPDATE_COMPLETE_EVENT_CODED) ? "CODED" : "Unexpected PHY Value");
            }

            SimplePeripheral_updatePHYStat(HCI_BLE_PHY_UPDATE_COMPLETE_EVENT, (uint8_t *)pMsg);
          }
          break;
        }

        default:
          break;
      }

      break;
    }

    default:
      // do nothing
      break;
  }

#ifdef PTM_MODE
  // Check for NPI Messages
  hciPacket_t *pBuf = (hciPacket_t *)pMsg;

  // Serialized HCI Event
  if (pBuf->hdr.event == HCI_CTRL_TO_HOST_EVENT)
  {
    uint16_t len = 0;

    // Determine the packet length
    switch(pBuf->pData[0])
    {
      case HCI_EVENT_PACKET:
        len = HCI_EVENT_MIN_LENGTH + pBuf->pData[2];
        break;

      case HCI_ACL_DATA_PACKET:
        len = HCI_DATA_MIN_LENGTH + BUILD_UINT16(pBuf->pData[3], pBuf->pData[4]);
        break;

      default:
        break;
    }

    // Send to Remote Host.
    simple_peripheral_sendToNPI(pBuf->pData, len);

    // Free buffers if needed.
    switch (pBuf->pData[0])
    {
      case HCI_ACL_DATA_PACKET:
      case HCI_SCO_DATA_PACKET:
        BM_free(pBuf->pData);
      default:
        break;
    }
  }
#endif // PTM_MODE

  return (safeToDealloc);
}

/*********************************************************************
 * @fn      SimplePeripheral_processGATTMsg
 *
 * @brief   Process GATT messages and events.
 *
 * @return  TRUE if safe to deallocate incoming message, FALSE otherwise.
 */
static uint8_t SimplePeripheral_processGATTMsg(gattMsgEvent_t *pMsg)
{
  if (pMsg->method == ATT_FLOW_CTRL_VIOLATED_EVENT)
  {
    // ATT request-response or indication-confirmation flow control is
    // violated. All subsequent ATT requests or indications will be dropped.
    // The app is informed in case it wants to drop the connection.

    // Display the opcode of the message that caused the violation.
    //Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "FC Violated: %d", pMsg->msg.flowCtrlEvt.opcode);
  }
  else if (pMsg->method == ATT_MTU_UPDATED_EVENT)
  {
    // MTU size updated
    Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "MTU Size: %d", pMsg->msg.mtuEvt.MTU);
  }

  // Free message payload. Needed only for ATT Protocol messages
  GATT_bm_free(&pMsg->msg, pMsg->method);

  // It's safe to free the incoming message
  return (TRUE);
}

/*********************************************************************
 * @fn      SimplePeripheral_processGapMessage
 *
 * @brief   Process an incoming GAP event.
 *
 * @param   pMsg - message to process
 */
static void SimplePeripheral_processGapMessage(gapEventHdr_t *pMsg)
{
  switch(pMsg->opcode)
  {
    case GAP_DEVICE_INIT_DONE_EVENT:
    {
      bStatus_t status = FAILURE;

      gapDeviceInitDoneEvent_t *pPkt = (gapDeviceInitDoneEvent_t *)pMsg;

      if(pPkt->hdr.status == SUCCESS)
      {
        // Store the system ID
        uint8_t systemId[DEVINFO_SYSTEM_ID_LEN];

        // use 6 bytes of device address for 8 bytes of system ID value
        systemId[0] = pPkt->devAddr[0];
        systemId[1] = pPkt->devAddr[1];
        systemId[2] = pPkt->devAddr[2];

        // set middle bytes to zero
        systemId[4] = 0x00;
        systemId[3] = 0x00;

        // shift three bytes up
        systemId[7] = pPkt->devAddr[5];
        systemId[6] = pPkt->devAddr[4];
        systemId[5] = pPkt->devAddr[3];

        // Set Device Info Service Parameter
        DevInfo_SetParameter(DEVINFO_SYSTEM_ID, DEVINFO_SYSTEM_ID_LEN, systemId);

        //Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "Initialized");

        // Setup and start Advertising
        // For more information, see the GAP section in the User's Guide:
        // http://software-dl.ti.com/lprf/ble5stack-latest/

        // Temporary memory for advertising parameters for set #1. These will be copied
        // by the GapAdv module
        GapAdv_params_t advParamLegacy = GAPADV_PARAMS_LEGACY_SCANN_CONN;

        // Create Advertisement set #1 and assign handle
        status = GapAdv_create(&SimplePeripheral_advCallback, &advParamLegacy,
                               &advHandleLegacy);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Load advertising data for set #1 that is statically allocated by the app
        status = GapAdv_loadByHandle(advHandleLegacy, GAP_ADV_DATA_TYPE_ADV,
                                     sizeof(advertData), advertData);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Load scan response data for set #1 that is statically allocated by the app
        status = GapAdv_loadByHandle(advHandleLegacy, GAP_ADV_DATA_TYPE_SCAN_RSP,
                                     sizeof(scanRspData), scanRspData);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Set event mask for set #1
        status = GapAdv_setEventMask(advHandleLegacy,
                                     GAP_ADV_EVT_MASK_START_AFTER_ENABLE |
                                     GAP_ADV_EVT_MASK_END_AFTER_DISABLE |
                                     GAP_ADV_EVT_MASK_SET_TERMINATED);

        // Enable legacy advertising for set #1
        status = GapAdv_enable(advHandleLegacy, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Use long range params to create long range set #2
        GapAdv_params_t advParamLongRange = GAPADV_PARAMS_AE_LONG_RANGE_CONN;

        // Create Advertisement set #2 and assign handle
        status = GapAdv_create(&SimplePeripheral_advCallback, &advParamLongRange,
                               &advHandleLongRange);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Load advertising data for set #2 that is statically allocated by the app
        status = GapAdv_loadByHandle(advHandleLongRange, GAP_ADV_DATA_TYPE_ADV,
                                     sizeof(advertData), advertData);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Load scan response data for set #2 that is statically allocated by the app
        status = GapAdv_loadByHandle(advHandleLongRange, GAP_ADV_DATA_TYPE_SCAN_RSP,
                                     sizeof(scanRspData), scanRspData);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Set event mask for set #2
        status = GapAdv_setEventMask(advHandleLongRange,
                                     GAP_ADV_EVT_MASK_START_AFTER_ENABLE |
                                     GAP_ADV_EVT_MASK_END_AFTER_DISABLE |
                                     GAP_ADV_EVT_MASK_SET_TERMINATED);

        // Enable long range advertising for set #2
        status = GapAdv_enable(advHandleLongRange, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
        SIMPLEPERIPHERAL_ASSERT(status == SUCCESS);

        // Display device address
        //Display_printf(dispHandle, SP_ROW_IDA, 0, "%s Addr: %s",
        //               (addrMode <= ADDRMODE_RANDOM) ? "Dev" : "ID",
        //               Util_convertBdAddr2Str(pPkt->devAddr));

        if (addrMode > ADDRMODE_RANDOM)
        {
          SimplePeripheral_updateRPA();

          // Create one-shot clock for RPA check event.
          Util_constructClock(&clkRpaRead, SimplePeripheral_clockHandler,
                              SP_READ_RPA_EVT_PERIOD, 0, true,
                              (UArg) &argRpaRead);
        }
      }

      break;
    }

    case GAP_LINK_ESTABLISHED_EVENT:
    {
      gapEstLinkReqEvent_t *pPkt = (gapEstLinkReqEvent_t *)pMsg;

      // Display the amount of current connections
      uint8_t numActive = linkDB_NumActive();
      //Display_printf(dispHandle, SP_ROW_STATUS_2, 0, "Num Conns: %d",
      //               (uint16_t)numActive);

      if (pPkt->hdr.status == SUCCESS)
      {
        // Add connection to list and start RSSI
        SimplePeripheral_addConn(pPkt->connectionHandle);

        // Display the address of this connection
        //Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "Connected to %s",
        //               Util_convertBdAddr2Str(pPkt->devAddr));

        // Enable connection selection option
        tbm_setItemStatus(&spMenuMain, SP_ITEM_SELECT_CONN, TBM_ITEM_NONE);

        // Start Periodic Clock.
        Util_startClock(&clkPeriodic);
        isconnected = true;
      }

      if (numActive < MAX_NUM_BLE_CONNS)
      {
        // Start advertising since there is room for more connections
        GapAdv_enable(advHandleLegacy, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
        GapAdv_enable(advHandleLongRange, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
      }
      else
      {
        // Stop advertising since there is no room for more connections
        GapAdv_disable(advHandleLongRange, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
        GapAdv_disable(advHandleLegacy, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
      }
      PIN_setOutputValue(ledPinHandle, Board_LED2, 1);
      break;
    }

    case GAP_LINK_TERMINATED_EVENT:
    {
      gapTerminateLinkEvent_t *pPkt = (gapTerminateLinkEvent_t *)pMsg;

      // Display the amount of current connections
      uint8_t numActive = linkDB_NumActive();
      //Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "Device Disconnected!");
      //Display_printf(dispHandle, SP_ROW_STATUS_2, 0, "Num Conns: %d",
      //               (uint16_t)numActive);

      // Remove the connection from the list and disable RSSI if needed
      SimplePeripheral_removeConn(pPkt->connectionHandle);

      // If no active connections
      if (numActive == 0)
      {
        // Stop periodic clock
        //Util_stopClock(&clkPeriodic);
        Util_stopClock(&clkPeriodic);
        // TODO
                isconnected = false;
                PIN_setOutputValue(ledPinHandle, Board_LED2, 0);
                starthandleflag = true;
        // Disable Connection Selection option
        tbm_setItemStatus(&spMenuMain, TBM_ITEM_NONE, SP_ITEM_SELECT_CONN);
      }

      // Start advertising since there is room for more connections
      GapAdv_enable(advHandleLegacy, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);
      GapAdv_enable(advHandleLongRange, GAP_ADV_ENABLE_OPTIONS_USE_MAX , 0);

      // Clear remaining lines
      //Display_clearLine(dispHandle, SP_ROW_CONNECTION);

      break;
    }

    case GAP_UPDATE_LINK_PARAM_REQ_EVENT:
    {
      gapUpdateLinkParamReqReply_t rsp;

      gapUpdateLinkParamReqEvent_t *pReq = (gapUpdateLinkParamReqEvent_t *)pMsg;

      rsp.connectionHandle = pReq->req.connectionHandle;
      rsp.signalIdentifier = pReq->req.signalIdentifier;

      // Only accept connection intervals with slave latency of 0
      // This is just an example of how the application can send a response
      if(pReq->req.connLatency == 0)
      {
        rsp.intervalMin = pReq->req.intervalMin;
        rsp.intervalMax = pReq->req.intervalMax;
        rsp.connLatency = pReq->req.connLatency;
        rsp.connTimeout = pReq->req.connTimeout;
        rsp.accepted = TRUE;
      }
      else
      {
        rsp.accepted = FALSE;
      }

      // Send Reply
      VOID GAP_UpdateLinkParamReqReply(&rsp);

      break;
    }

    case GAP_LINK_PARAM_UPDATE_EVENT:
    {
      gapLinkUpdateEvent_t *pPkt = (gapLinkUpdateEvent_t *)pMsg;

      // Get the address from the connection handle
      linkDBInfo_t linkInfo;
      linkDB_GetInfo(pPkt->connectionHandle, &linkInfo);

      if(pPkt->status == SUCCESS)
      {
        // Display the address of the connection update
        //Display_printf(dispHandle, SP_ROW_STATUS_2, 0, "Link Param Updated: %s",
        //               Util_convertBdAddr2Str(linkInfo.addr));
      }
      else
      {
        // Display the address of the connection update failure
        //Display_printf(dispHandle, SP_ROW_STATUS_2, 0,
        //               "Link Param Update Failed 0x%x: %s", pPkt->opcode,
        //               Util_convertBdAddr2Str(linkInfo.addr));
      }

      // Check if there are any queued parameter updates
      spConnHandleEntry_t *connHandleEntry = (spConnHandleEntry_t *)List_get(&paramUpdateList);
      if (connHandleEntry != NULL)
      {
        // Attempt to send queued update now
        SimplePeripheral_processParamUpdate(connHandleEntry->connHandle);

        // Free list element
        ICall_free(connHandleEntry);
      }

      break;
    }

    default:
      //Display_clearLines(dispHandle, SP_ROW_STATUS_1, SP_ROW_STATUS_2);
      break;
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_charValueChangeCB
 *
 * @brief   Callback from Simple Profile indicating a characteristic
 *          value change.
 *
 * @param   paramId - parameter Id of the value that was changed.
 *
 * @return  None.
 */
static void SimplePeripheral_charValueChangeCB(uint8_t paramId)
{
  uint8_t *pValue = ICall_malloc(sizeof(uint8_t));

  if (pValue)
  {
    *pValue = paramId;

    if (SimplePeripheral_enqueueMsg(SP_CHAR_CHANGE_EVT, pValue) != SUCCESS)
    {
      ICall_free(pValue);
    }
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_processCharValueChangeEvt
 *
 * @brief   Process a pending Simple Profile characteristic value change
 *          event.
 *
 * @param   paramID - parameter ID of the value that was changed.
 */
// TODO
static void SimplePeripheral_processCharValueChangeEvt(uint8_t paramId)
{
  uint8_t newCMD;
  uint8_t cmdtemp[2];
  //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));

  switch(paramId)
  {
    case SIMPLEPROFILE_CHAR1:
      SimpleProfile_GetParameter(SIMPLEPROFILE_CHAR1, &newCMD);

      //Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "Char 1: %d", (uint16_t)newCMD);
      break;
//TODO
    case SIMPLEPROFILE_CHAR3:
      //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
      SimpleProfile_GetParameter(SIMPLEPROFILE_CHAR3, RxBuffFromComputer);
//      PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));


      // Process new coming data
            isNewrequestcome = true;
            isBLEready = true;
            // On/ Fusion
            cmdtemp[0] = RxBuffFromComputer[188];
            cmdtemp[1] = RxBuffFromComputer[189];
            cmdtemp[0] = (cmdtemp[0] >= 65 ? (uint8_t)(cmdtemp[0] - 55) : (uint8_t)(cmdtemp[0] - 48));
            cmdtemp[1] = (cmdtemp[1] >= 65 ? (uint8_t)(cmdtemp[1] - 55) : (uint8_t)(cmdtemp[1] - 48));
            newCMD = (cmdtemp[0]<<4)|(cmdtemp[1]);

            cmdtemp[0] = RxBuffFromComputer[191];
            FusionOnOff = (cmdtemp[0] >= 65 ? (uint8_t)(cmdtemp[0] - 55) : (uint8_t)(cmdtemp[0] - 48));

            cmdtemp[1] = RxBuffFromComputer[201];
            isGPSonly = (cmdtemp[1] >= 65 ? (uint8_t)(cmdtemp[1] - 55) : (uint8_t)(cmdtemp[1] - 48));

            if(newCMD == 0x58)
                  {
                      FusionOnOffOld = FusionOnOff;
                      FusionOnOff = false;
                      isAutoSendTriggered = true;
                      //PIN_setOutputValue(ledPinHandle, Board_LED1, !PIN_getOutputValue(Board_LED1));
                  }
            else if (newCMD == 0x59)// Abort
                  {
                      isAutoSendTriggered = false;
                      FusionOnOff = FusionOnOffOld;
                  }

      break;

    default:
      // should not reach here!
      break;
  }
}
/*********************************************************************
 * @fn      SimplePeripheral_performPeriodicTask
 *
 * @brief   Perform a periodic application task. This function gets called
 *          every five seconds (SP_PERIODIC_EVT_PERIOD). In this example,
 *          the value of the third characteristic in the SimpleGATTProfile
 *          service is retrieved from the profile, and then copied into the
 *          value of the the fourth characteristic.
 *
 * @param   None.
 *
 * @return  None.
 */
static void SimplePeripheral_performPeriodicTask(void)
{
        uint8_t newValue;
        uint8_t cmdtemp[2];
        uint8_t subcmd;

        cmdtemp[0] = TxBuffToComputer[3];
        cmdtemp[1] = TxBuffToComputer[4];
        subcmd  = (cmdtemp[0]<<4)|(cmdtemp[1]);
        if(subcmd == 0x59)
        {
            isAutoSendTriggered = false;
            FusionOnOff = FusionOnOffOld;
        }
        newValue = 0;
        if (isWaitingforIMU)
        {
            if (subcmd == 1)
            {
                newValue = 1;
                isWaitingforIMU = false;
            }
            else if(SPItrasfercase == 3)
            {
                newValue = 2;
            }
            else if(SPItrasfercase == 5)
            {
                newValue = 2;
            }
        }
        else
        {
            if(SPItrasfercase == 3)
            {
                newValue = 2;
            }
            else if(SPItrasfercase == 5)
            {
                newValue = 2;
            }
        }
        // data in TxBuffToComputer
        // process data
        switch(newValue)
        {
        case 1: // read IMU data
            // trigger fusion calculation
            break;
        case 2: // try to send to station
            // modify
            if(isconnected)
            {
                BLESendbackdata();
            }
            break;
        default:
            break;
        }
}

/*********************************************************************
 * @fn      SimplePeripheral_updateRPA
 *
 * @brief   Read the current RPA from the stack and update display
 *          if the RPA has changed.
 *
 * @param   None.
 *
 * @return  None.
 */
static void SimplePeripheral_updateRPA(void)
{
  uint8_t* pRpaNew;

  // Read the current RPA.
  pRpaNew = GAP_GetDevAddress(FALSE);

  if (memcmp(pRpaNew, rpa, B_ADDR_LEN))
  {
    // If the RPA has changed, update the display
    //Display_printf(dispHandle, SP_ROW_RPA, 0, "RP Addr: %s",
    //               Util_convertBdAddr2Str(pRpaNew));
    memcpy(rpa, pRpaNew, B_ADDR_LEN);
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_clockHandler
 *
 * @brief   Handler function for clock timeouts.
 *
 * @param   arg - event type
 *
 * @return  None.
 */
static void SimplePeripheral_clockHandler(UArg arg)
{
  spClockEventData_t *pData = (spClockEventData_t *)arg;

 if (pData->event == SP_PERIODIC_EVT)
 {
   // Start the next period
   //Util_startClock(&clkPeriodic);
   // Post event to wake up the application
   SimplePeripheral_enqueueMsg(SP_PERIODIC_EVT, NULL);
 }
 else if (pData->event == SP_GPS_DONE_EVT)
   {
     // Post event to wake up the application
     SimplePeripheral_enqueueMsg(SP_GPS_DONE_EVT, NULL);
   }
 else if (pData->event == SP_READ_RPA_EVT)
 {
   // Start the next period
   Util_startClock(&clkRpaRead);

   // Post event to read the current RPA
   SimplePeripheral_enqueueMsg(SP_READ_RPA_EVT, NULL);
 }
 else if (pData->event == SP_SEND_PARAM_UPDATE_EVT)
 {
    // Send message to app
    SimplePeripheral_enqueueMsg(SP_SEND_PARAM_UPDATE_EVT, pData);
 }
 else if (pData->event == SP_MCU_TRANS_EVT)
  {
     Util_startClock(&clkMcuTransaction);
      // Post event to wake up the application
     SimplePeripheral_enqueueMsg(SP_MCU_TRANS_EVT, NULL);
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_keyChangeHandler
 *
 * @brief   Key event handler function
 *
 * @param   keys - bitmap of pressed keys
 *
 * @return  none
 */
/*static void SimplePeripheral_keyChangeHandler(uint8_t keys)
{
  uint8_t *pValue = ICall_malloc(sizeof(uint8_t));

  if (pValue)
  {
    *pValue = keys;

    if(SimplePeripheral_enqueueMsg(SP_KEY_CHANGE_EVT, pValue) != SUCCESS)
    {
      ICall_free(pValue);
    }
  }
}*/

/*********************************************************************
 * @fn      SimplePeripheral_handleKeys
 *
 * @brief   Handles all key events for this device.
 *
 * @param   keys - bit field for key events. Valid entries:
 *                 KEY_LEFT
 *                 KEY_RIGHT
 */
static void SimplePeripheral_handleKeys(uint8_t keys)
{
/*  if (keys & KEY_LEFT)
  {
    // Check if the key is still pressed. Workaround for possible bouncing.
    if (PIN_getInputValue(Board_PIN_BUTTON0) == 0)
    {
      tbm_buttonLeft();
    }
  }
  else if (keys & KEY_RIGHT)
  {
    // Check if the key is still pressed. Workaround for possible bouncing.
    if (PIN_getInputValue(Board_PIN_BUTTON1) == 0)
    {
      tbm_buttonRight();
    }
  }*/
}

/*********************************************************************
 * @fn      SimplePeripheral_doSetConnPhy
 *
 * @brief   Set PHY preference.
 *
 * @param   index - 0: 1M PHY
 *                  1: 2M PHY
 *                  2: 1M + 2M PHY
 *                  3: CODED PHY (Long range)
 *                  4: 1M + 2M + CODED PHY
 *
 * @return  always true
 */
bool SimplePeripheral_doSetConnPhy(uint8 index)
{
  bool status = TRUE;

  static uint8_t phy[] = {
    HCI_PHY_1_MBPS, HCI_PHY_2_MBPS, HCI_PHY_1_MBPS | HCI_PHY_2_MBPS,
    HCI_PHY_CODED, HCI_PHY_1_MBPS | HCI_PHY_2_MBPS | HCI_PHY_CODED,
    AUTO_PHY_UPDATE
  };

  uint8_t connIndex = SimplePeripheral_getConnIndex(menuConnHandle);
  SIMPLEPERIPHERAL_ASSERT(connIndex < MAX_NUM_BLE_CONNS);

  // Set Phy Preference on the current connection. Apply the same value
  // for RX and TX.
  // If auto PHY update is not selected and if auto PHY update is enabled, then
  // stop auto PHY update
  // Note PHYs are already enabled by default in build_config.opt in stack project.
  if(phy[index] != AUTO_PHY_UPDATE)
  {
    // Cancel RSSI reading  and auto phy changing
    SimplePeripheral_stopAutoPhyChange(connList[connIndex].connHandle);

    SimplePeripheral_setPhy(menuConnHandle, 0, phy[index], phy[index], 0);

    Display_printf(dispHandle, SP_ROW_STATUS_1, 0, "PHY preference: %s",
                   TBM_GET_ACTION_DESC(&spMenuConnPhy, index));
  }
  else
  {
    // Start RSSI read for auto PHY update (if it is disabled)
    SimplePeripheral_startAutoPhyChange(menuConnHandle);
  }

  return status;
}
/*********************************************************************
 * @fn      SimplePeripheral_advCallback
 *
 * @brief   GapAdv module callback
 *
 * @param   pMsg - message to process
 */
static void SimplePeripheral_advCallback(uint32_t event, void *pBuf, uintptr_t arg)
{
  spGapAdvEventData_t *pData = ICall_malloc(sizeof(spGapAdvEventData_t));

  if (pData)
  {
    pData->event = event;
    pData->pBuf = pBuf;

    if(SimplePeripheral_enqueueMsg(SP_ADV_EVT, pData) != SUCCESS)
    {
      ICall_free(pData);
    }
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_processAdvEvent
 *
 * @brief   Process advertising event in app context
 *
 * @param   pEventData
 */
static void SimplePeripheral_processAdvEvent(spGapAdvEventData_t *pEventData)
{
  switch (pEventData->event)
  {
    case GAP_EVT_ADV_START_AFTER_ENABLE:
      //Display_printf(dispHandle, SP_ROW_ADVSTATE, 0, "Adv Set %d Enabled",
      //               *(uint8_t *)(pEventData->pBuf));
      break;

    case GAP_EVT_ADV_END_AFTER_DISABLE:
      //Display_printf(dispHandle, SP_ROW_ADVSTATE, 0, "Adv Set %d Disabled",
      //               *(uint8_t *)(pEventData->pBuf));
      break;

    case GAP_EVT_ADV_START:
      break;

    case GAP_EVT_ADV_END:
      break;

    case GAP_EVT_ADV_SET_TERMINATED:
    {
#ifndef Display_DISABLE_ALL
      //GapAdv_setTerm_t *advSetTerm = (GapAdv_setTerm_t *)(pEventData->pBuf);

      //Display_printf(dispHandle, SP_ROW_ADVSTATE, 0, "Adv Set %d disabled after conn %d",
      //               advSetTerm->handle, advSetTerm->connHandle );
#endif
    }
    break;

    case GAP_EVT_SCAN_REQ_RECEIVED:
      break;

    case GAP_EVT_INSUFFICIENT_MEMORY:
      break;

    default:
      break;
  }

  // All events have associated memory to free except the insufficient memory
  // event
  if (pEventData->event != GAP_EVT_INSUFFICIENT_MEMORY)
  {
    ICall_free(pEventData->pBuf);
  }
}


/*********************************************************************
 * @fn      SimplePeripheral_pairStateCb
 *
 * @brief   Pairing state callback.
 *
 * @return  none
 */
static void SimplePeripheral_pairStateCb(uint16_t connHandle, uint8_t state,
                                         uint8_t status)
{
  spPairStateData_t *pData = ICall_malloc(sizeof(spPairStateData_t));

  // Allocate space for the event data.
  if (pData)
  {
    pData->state = state;
    pData->connHandle = connHandle;
    pData->status = status;

    // Queue the event.
    if(SimplePeripheral_enqueueMsg(SP_PAIR_STATE_EVT, pData) != SUCCESS)
    {
      ICall_free(pData);
    }
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_passcodeCb
 *
 * @brief   Passcode callback.
 *
 * @return  none
 */
static void SimplePeripheral_passcodeCb(uint8_t *pDeviceAddr,
                                        uint16_t connHandle,
                                        uint8_t uiInputs,
                                        uint8_t uiOutputs,
                                        uint32_t numComparison)
{
  spPasscodeData_t *pData = ICall_malloc(sizeof(spPasscodeData_t));

  // Allocate space for the passcode event.
  if (pData )
  {
    pData->connHandle = connHandle;
    memcpy(pData->deviceAddr, pDeviceAddr, B_ADDR_LEN);
    pData->uiInputs = uiInputs;
    pData->uiOutputs = uiOutputs;
    pData->numComparison = numComparison;

    // Enqueue the event.
    if(SimplePeripheral_enqueueMsg(SP_PASSCODE_EVT, pData) != SUCCESS)
    {
      ICall_free(pData);
    }
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_processPairState
 *
 * @brief   Process the new paring state.
 *
 * @return  none
 */
static void SimplePeripheral_processPairState(spPairStateData_t *pPairData)
{
  uint8_t state = pPairData->state;
  uint8_t status = pPairData->status;

  switch (state)
  {
    case GAPBOND_PAIRING_STATE_STARTED:
      Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Pairing started");
      break;

    case GAPBOND_PAIRING_STATE_COMPLETE:
      if (status == SUCCESS)
      {
        Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Pairing success");
      }
      else
      {
        Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Pairing fail: %d", status);
      }
      break;

    case GAPBOND_PAIRING_STATE_ENCRYPTED:
      if (status == SUCCESS)
      {
        Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Encryption success");
      }
      else
      {
        Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Encryption failed: %d", status);
      }
      break;

    case GAPBOND_PAIRING_STATE_BOND_SAVED:
      if (status == SUCCESS)
      {
        Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Bond save success");
      }
      else
      {
        Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Bond save failed: %d", status);
      }
      break;

    default:
      break;
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_processPasscode
 *
 * @brief   Process the Passcode request.
 *
 * @return  none
 */
static void SimplePeripheral_processPasscode(spPasscodeData_t *pPasscodeData)
{
  // Display passcode to user
  if (pPasscodeData->uiOutputs != 0)
  {
    Display_printf(dispHandle, SP_ROW_CONNECTION, 0, "Passcode: %d",
                   B_APP_DEFAULT_PASSCODE);
  }

  // Send passcode response
  GAPBondMgr_PasscodeRsp(pPasscodeData->connHandle , SUCCESS,
                         B_APP_DEFAULT_PASSCODE);
}

/*********************************************************************
 * @fn      SimplePeripheral_connEvtCB
 *
 * @brief   Connection event callback.
 *
 * @param pReport pointer to connection event report
 */
static void SimplePeripheral_connEvtCB(Gap_ConnEventRpt_t *pReport)
{
  // Enqueue the event for processing in the app context.
  if(SimplePeripheral_enqueueMsg(SP_CONN_EVT, pReport) != SUCCESS)
  {
    ICall_free(pReport);
  }
}

/*********************************************************************
 * @fn      SimplePeripheral_processConnEvt
 *
 * @brief   Process connection event.
 *
 * @param pReport pointer to connection event report
 */
static void SimplePeripheral_processConnEvt(Gap_ConnEventRpt_t *pReport)
{
    PIN_setOutputValue(ledPinHandle, Board_LED2, 1);
  // Get index from handle
  uint8_t connIndex = SimplePeripheral_getConnIndex(pReport->handle);

  SIMPLEPERIPHERAL_ASSERT(connIndex < MAX_NUM_BLE_CONNS);

  // If auto phy change is enabled
  if (connList[connIndex].isAutoPHYEnable == TRUE)
  {
    // Read the RSSI
    HCI_ReadRssiCmd(pReport->handle);
  }
}


/*********************************************************************
 * @fn      SimplePeripheral_enqueueMsg
 *
 * @brief   Creates a message and puts the message in RTOS queue.
 *
 * @param   event - message event.
 * @param   state - message state.
 */
static status_t SimplePeripheral_enqueueMsg(uint8_t event, void *pData)
{
  uint8_t success;
  spEvt_t *pMsg = ICall_malloc(sizeof(spEvt_t));

  // Create dynamic pointer to message.
  if(pMsg)
  {
    pMsg->event = event;
    pMsg->pData = pData;

    // Enqueue the message.
    success = Util_enqueueMsg(appMsgQueueHandle, syncEvent, (uint8_t *)pMsg);
    return (success) ? SUCCESS : FAILURE;
  }

  return(bleMemAllocError);
}

/*********************************************************************
 * @fn      SimplePeripheral_doSelectConn
 *
 * @brief   Select a connection to communicate with
 *
 * @param   index - item index from the menu
 *
 * @return  always true
 */
bool SimplePeripheral_doSelectConn(uint8_t index)
{
  menuConnHandle = connList[index].connHandle;

  // Set the menu title and go to this connection's context
  TBM_SET_TITLE(&spMenuPerConn, TBM_GET_ACTION_DESC(&spMenuSelectConn, index));

  // Clear non-connection-related message
  Display_clearLine(dispHandle, SP_ROW_CONNECTION);

  tbm_goTo(&spMenuPerConn);

  return (true);
}

/*********************************************************************
 * @fn      SimplePeripheral_addConn
 *
 * @brief   Add a device to the connected device list
 *
 * @return  index of the connected device list entry where the new connection
 *          info is put in.
 *          if there is no room, MAX_NUM_BLE_CONNS will be returned.
 */
static uint8_t SimplePeripheral_addConn(uint16_t connHandle)
{
  uint8_t i;
  uint8_t status = bleNoResources;

  // Try to find an available entry
  for (i = 0; i < MAX_NUM_BLE_CONNS; i++)
  {
    if (connList[i].connHandle == LINKDB_CONNHANDLE_INVALID)
    {
      // Found available entry to put a new connection info in
      connList[i].connHandle = connHandle;

      // Allocate data to send through clock handler
      connList[i].pParamUpdateEventData = ICall_malloc(sizeof(spClockEventData_t) +
                                                       sizeof (uint16_t));
      if(connList[i].pParamUpdateEventData)
      {
        connList[i].pParamUpdateEventData->event = SP_SEND_PARAM_UPDATE_EVT;
        *((uint16_t *)connList[i].pParamUpdateEventData->data) = connHandle;

        // Create a clock object and start
        connList[i].pUpdateClock
          = (Clock_Struct*) ICall_malloc(sizeof(Clock_Struct));

        if (connList[i].pUpdateClock)
        {
          Util_constructClock(connList[i].pUpdateClock,
                              SimplePeripheral_clockHandler,
                              SP_SEND_PARAM_UPDATE_DELAY, 0, true,
                              (UArg) (connList[i].pParamUpdateEventData));
        }
        else
        {
            ICall_free(connList[i].pParamUpdateEventData);
        }
      }
      else
      {
        status = bleMemAllocError;
      }

      // Set default PHY to 1M
      connList[i].currPhy = HCI_PHY_1_MBPS;

      break;
    }
  }

  return status;
}

/*********************************************************************
 * @fn      SimplePeripheral_getConnIndex
 *
 * @brief   Find index in the connected device list by connHandle
 *
 * @return  the index of the entry that has the given connection handle.
 *          if there is no match, MAX_NUM_BLE_CONNS will be returned.
 */
static uint8_t SimplePeripheral_getConnIndex(uint16_t connHandle)
{
  uint8_t i;

  for (i = 0; i < MAX_NUM_BLE_CONNS; i++)
  {
    if (connList[i].connHandle == connHandle)
    {
      return i;
    }
  }

  return(MAX_NUM_BLE_CONNS);
}

/*********************************************************************
 * @fn      SimplePeripheral_getConnIndex
 *
 * @brief   Find index in the connected device list by connHandle
 *
 * @return  SUCCESS if connHandle found valid index or bleInvalidRange
 *          if index wasn't found. LINKDB_CONNHANDLE_ALL will always succeed.
 */
static uint8_t SimplePeripheral_clearConnListEntry(uint16_t connHandle)
{
  uint8_t i;
  // Set to invalid connection index initially
  uint8_t connIndex = MAX_NUM_BLE_CONNS;

  if(connHandle != LINKDB_CONNHANDLE_ALL)
  {
    // Get connection index from handle
    connIndex = SimplePeripheral_getConnIndex(connHandle);
    if(connIndex >= MAX_NUM_BLE_CONNS)
	{
	  return(bleInvalidRange);
	}
  }

  // Clear specific handle or all handles
  for(i = 0; i < MAX_NUM_BLE_CONNS; i++)
  {
    if((connIndex == i) || (connHandle == LINKDB_CONNHANDLE_ALL))
    {
      connList[i].connHandle = LINKDB_CONNHANDLE_INVALID;
      connList[i].currPhy = 0;
      connList[i].phyCngRq = 0;
      connList[i].phyRqFailCnt = 0;
      connList[i].rqPhy = 0;
      memset(connList[i].rssiArr, 0, SP_MAX_RSSI_STORE_DEPTH);
      connList[i].rssiAvg = 0;
      connList[i].rssiCntr = 0;
      connList[i].isAutoPHYEnable = FALSE;
    }
  }

  return(SUCCESS);
}

/*********************************************************************
 * @fn      SimplePeripheral_removeConn
 *
 * @brief   Remove a device from the connected device list
 *
 * @return  index of the connected device list entry where the new connection
 *          info is removed from.
 *          if connHandle is not found, MAX_NUM_BLE_CONNS will be returned.
 */
static uint8_t SimplePeripheral_removeConn(uint16_t connHandle)
{
  uint8_t connIndex = SimplePeripheral_getConnIndex(connHandle);

  if(connIndex != MAX_NUM_BLE_CONNS)
  {
    Clock_Struct* pUpdateClock = connList[connIndex].pUpdateClock;

    if (pUpdateClock != NULL)
    {
      // Stop and destruct the RTOS clock if it's still alive
      if (Util_isActive(pUpdateClock))
      {
        Util_stopClock(pUpdateClock);
      }

      // Destruct the clock object
      Clock_destruct(pUpdateClock);
      // Free clock struct
      ICall_free(pUpdateClock);
      // Free ParamUpdateEventData
      ICall_free(connList[connIndex].pParamUpdateEventData);
    }
    // Stop Auto PHY Change
    SimplePeripheral_stopAutoPhyChange(connHandle);
    // Clear Connection List Entry
    SimplePeripheral_clearConnListEntry(connHandle);
  }

  return connIndex;
}

/*********************************************************************
 * @fn      SimplePeripheral_processParamUpdate
 *
 * @brief   Process a parameters update request
 *
 * @return  None
 */
static void SimplePeripheral_processParamUpdate(uint16_t connHandle)
{
  gapUpdateLinkParamReq_t req;
  uint8_t connIndex;

  req.connectionHandle = connHandle;
  req.connLatency = DEFAULT_DESIRED_SLAVE_LATENCY;
  req.connTimeout = DEFAULT_DESIRED_CONN_TIMEOUT;
  req.intervalMin = DEFAULT_DESIRED_MIN_CONN_INTERVAL;
  req.intervalMax = DEFAULT_DESIRED_MAX_CONN_INTERVAL;

  connIndex = SimplePeripheral_getConnIndex(connHandle);
  SIMPLEPERIPHERAL_ASSERT(connIndex < MAX_NUM_BLE_CONNS);

  // Deconstruct the clock object
  Clock_destruct(connList[connIndex].pUpdateClock);
  // Free clock struct
  ICall_free(connList[connIndex].pUpdateClock);
  connList[connIndex].pUpdateClock = NULL;
  // Free ParamUpdateEventData
  ICall_free(connList[connIndex].pParamUpdateEventData);

  // Send parameter update
  bStatus_t status = GAP_UpdateLinkParamReq(&req);

  // If there is an ongoing update, queue this for when the udpate completes
  if (status == bleAlreadyInRequestedMode)
  {
    spConnHandleEntry_t *connHandleEntry = ICall_malloc(sizeof(spConnHandleEntry_t));
    if (connHandleEntry)
    {
      connHandleEntry->connHandle = connHandle;

      List_put(&paramUpdateList, (List_Elem *)&connHandleEntry);
    }
  }
}

/*********************************************************************
 * @fn      SimpleCentral_processCmdCompleteEvt
 *
 * @brief   Process an incoming OSAL HCI Command Complete Event.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void SimplePeripheral_processCmdCompleteEvt(hciEvt_CmdComplete_t *pMsg)
{
  uint8_t status = pMsg->pReturnParam[0];

  //Find which command this command complete is for
  switch (pMsg->cmdOpcode)
  {
    case HCI_READ_RSSI:
    {
      int8 rssi = (int8)pMsg->pReturnParam[3];  

      // Display RSSI value, if RSSI is higher than threshold, change to faster PHY
      if (status == SUCCESS)
      {
        uint16_t handle = BUILD_UINT16(pMsg->pReturnParam[1], pMsg->pReturnParam[2]);

        uint8_t index = SimplePeripheral_getConnIndex(handle);
        SIMPLEPERIPHERAL_ASSERT(index < MAX_NUM_BLE_CONNS);

        if (rssi != LL_RSSI_NOT_AVAILABLE)
        {
          connList[index].rssiArr[connList[index].rssiCntr++] = rssi;
          connList[index].rssiCntr %= SP_MAX_RSSI_STORE_DEPTH;

          int16_t sum_rssi = 0;
          for(uint8_t cnt=0; cnt<SP_MAX_RSSI_STORE_DEPTH; cnt++)
          {
            sum_rssi += connList[index].rssiArr[cnt];
          }
          connList[index].rssiAvg = (uint32_t)(sum_rssi/SP_MAX_RSSI_STORE_DEPTH);

          uint8_t phyRq = SP_PHY_NONE;
          uint8_t phyRqS = SP_PHY_NONE;
          uint8_t phyOpt = LL_PHY_OPT_NONE;

          if(connList[index].phyCngRq == FALSE)
          {
            if((connList[index].rssiAvg >= RSSI_2M_THRSHLD) &&
            (connList[index].currPhy != HCI_PHY_2_MBPS) &&
                 (connList[index].currPhy != SP_PHY_NONE))
            {
              // try to go to higher data rate
              phyRqS = phyRq = HCI_PHY_2_MBPS;
            }
            else if((connList[index].rssiAvg < RSSI_2M_THRSHLD) &&
                    (connList[index].rssiAvg >= RSSI_1M_THRSHLD) &&
                    (connList[index].currPhy != HCI_PHY_1_MBPS) &&
                    (connList[index].currPhy != SP_PHY_NONE))
            {
              // try to go to legacy regular data rate
              phyRqS = phyRq = HCI_PHY_1_MBPS;
            }
            else if((connList[index].rssiAvg >= RSSI_S2_THRSHLD) &&
                    (connList[index].rssiAvg < RSSI_1M_THRSHLD) &&
                    (connList[index].currPhy != SP_PHY_NONE))
            {
              // try to go to lower data rate S=2(500kb/s)
              phyRqS = HCI_PHY_CODED;
              phyOpt = LL_PHY_OPT_S2;
              phyRq = BLE5_CODED_S2_PHY;
            }
            else if(connList[index].rssiAvg < RSSI_S2_THRSHLD )
            {
              // try to go to lowest data rate S=8(125kb/s)
              phyRqS = HCI_PHY_CODED;
              phyOpt = LL_PHY_OPT_S8;
              phyRq = BLE5_CODED_S8_PHY;
            }
            if((phyRq != SP_PHY_NONE) &&
               // First check if the request for this phy change is already not honored then don't request for change
               (((connList[index].rqPhy == phyRq) &&
                 (connList[index].phyRqFailCnt < 2)) ||
                 (connList[index].rqPhy != phyRq)))
            {
              //Initiate PHY change based on RSSI
              SimplePeripheral_setPhy(connList[index].connHandle, 0,
                                      phyRqS, phyRqS, phyOpt);
              connList[index].phyCngRq = TRUE;

              // If it a request for different phy than failed request, reset the count
              if(connList[index].rqPhy != phyRq)
              {
                // then reset the request phy counter and requested phy
                connList[index].phyRqFailCnt = 0;
              }

              if(phyOpt == LL_PHY_OPT_NONE)
              {
                connList[index].rqPhy = phyRq;
              }
              else if(phyOpt == LL_PHY_OPT_S2)
              {
                connList[index].rqPhy = BLE5_CODED_S2_PHY;
              }
              else
              {
                connList[index].rqPhy = BLE5_CODED_S8_PHY;
              }

            } // end of if ((phyRq != SP_PHY_NONE) && ...
          } // end of if (connList[index].phyCngRq == FALSE)
        } // end of if (rssi != LL_RSSI_NOT_AVAILABLE)

        Display_printf(dispHandle, SP_ROW_RSSI, 0,
                       "RSSI:%d dBm, AVG RSSI:%d dBm",
                       (uint32_t)(rssi),
                       connList[index].rssiAvg);

	  } // end of if (status == SUCCESS)
      break;
    }

    case HCI_LE_READ_PHY:
    {
      if (status == SUCCESS)
      {
        Display_printf(dispHandle, SP_ROW_RSSI + 2, 0, "RXPh: %d, TXPh: %d",
                       pMsg->pReturnParam[3], pMsg->pReturnParam[4]);
      }
      break;
    }

    default:
      break;
  } // end of switch (pMsg->cmdOpcode)
}

/*********************************************************************
* @fn      SimplePeripheral_initPHYRSSIArray
*
* @brief   Initializes the array of structure/s to store data related
*          RSSI based auto PHy change
*
* @param   connHandle - the connection handle
*
* @param   addr - pointer to device address
*
* @return  index of connection handle
*/
static void SimplePeripheral_initPHYRSSIArray(void)
{
  //Initialize array to store connection handle and RSSI values
  memset(connList, 0, sizeof(connList));
  for (uint8_t index = 0; index < MAX_NUM_BLE_CONNS; index++)
  {
    connList[index].connHandle = SP_INVALID_HANDLE;
  }
}
/*********************************************************************
      // Set default PHY to 1M
 * @fn      SimplePeripheral_startAutoPhyChange
 *
 * @brief   Start periodic RSSI reads on a link.
 *
 * @param   connHandle - connection handle of link
 * @param   devAddr - device address
 *
 * @return  SUCCESS: Terminate started
 *          bleIncorrectMode: No link
 *          bleNoResources: No resources
 */
static status_t SimplePeripheral_startAutoPhyChange(uint16_t connHandle)
{
  status_t status = FAILURE;

  // Get connection index from handle
  uint8_t connIndex = SimplePeripheral_getConnIndex(connHandle);
  SIMPLEPERIPHERAL_ASSERT(connIndex < MAX_NUM_BLE_CONNS);

  // Start Connection Event notice for RSSI calculation
  status = Gap_RegisterConnEventCb(SimplePeripheral_connEvtCB, GAP_CB_REGISTER, connHandle);

  // Flag in connection info if successful
  if (status == SUCCESS)
  {
    connList[connIndex].isAutoPHYEnable = TRUE;
  }

  return status;
}

/*********************************************************************
 * @fn      SimplePeripheral_stopAutoPhyChange
 *
 * @brief   Cancel periodic RSSI reads on a link.
 *
 * @param   connHandle - connection handle of link
 *
 * @return  SUCCESS: Operation successful
 *          bleIncorrectMode: No link
 */
static status_t SimplePeripheral_stopAutoPhyChange(uint16_t connHandle)
{
  // Get connection index from handle
  uint8_t connIndex = SimplePeripheral_getConnIndex(connHandle);
  SIMPLEPERIPHERAL_ASSERT(connIndex < MAX_NUM_BLE_CONNS);

  // Stop connection event notice
  Gap_RegisterConnEventCb(NULL, GAP_CB_UNREGISTER, connHandle);

  // Also update the phychange request status for active RSSI tracking connection
  connList[connIndex].phyCngRq = FALSE;
  connList[connIndex].isAutoPHYEnable = FALSE;

  return SUCCESS;
}

/*********************************************************************
 * @fn      SimplePeripheral_setPhy
 *
 * @brief   Call the HCI set phy API and and add the handle to a
 *          list to match it to an incoming command status event
 */
static status_t SimplePeripheral_setPhy(uint16_t connHandle, uint8_t allPhys,
                                        uint8_t txPhy, uint8_t rxPhy,
                                        uint16_t phyOpts)
{
  // Allocate list entry to store handle for command status
  spConnHandleEntry_t *connHandleEntry = ICall_malloc(sizeof(spConnHandleEntry_t));

  if (connHandleEntry)
  {
    connHandleEntry->connHandle = connHandle;

    // Add entry to the phy command status list
    List_put(&setPhyCommStatList, (List_Elem *)connHandleEntry);

    // Send PHY Update
    HCI_LE_SetPhyCmd(connHandle, allPhys, txPhy, rxPhy, phyOpts);
  }

  return SUCCESS;
}

/*********************************************************************
* @fn      SimplePeripheral_updatePHYStat
*
* @brief   Update the auto phy update state machine
*
* @param   connHandle - the connection handle
*
* @return  None
*/
static void SimplePeripheral_updatePHYStat(uint16_t eventCode, uint8_t *pMsg)
{
  uint8_t connIndex;

  switch (eventCode)
  {
    case HCI_LE_SET_PHY:
    {
      // Get connection handle from list
      spConnHandleEntry_t *connHandleEntry =
                           (spConnHandleEntry_t *)List_get(&setPhyCommStatList);

      if (connHandleEntry)
      {
        // Get index from connection handle
        connIndex = SimplePeripheral_getConnIndex(connHandleEntry->connHandle);

        ICall_free(connHandleEntry);

        // Is this connection still valid?
        if (connIndex < MAX_NUM_BLE_CONNS)
        {
          hciEvt_CommandStatus_t *pMyMsg = (hciEvt_CommandStatus_t *)pMsg;

          if (pMyMsg->cmdStatus == HCI_ERROR_CODE_UNSUPPORTED_REMOTE_FEATURE)
          {
            // Update the phychange request status for active RSSI tracking connection
            connList[connIndex].phyCngRq = FALSE;
            connList[connIndex].phyRqFailCnt++;
          }
        }
      }
      break;
    }

    // LE Event - a Phy update has completed or failed
    case HCI_BLE_PHY_UPDATE_COMPLETE_EVENT:
    {
      hciEvt_BLEPhyUpdateComplete_t *pPUC =
                                     (hciEvt_BLEPhyUpdateComplete_t*) pMsg;

      if(pPUC)
      {
        // Get index from connection handle
        connIndex = SimplePeripheral_getConnIndex(pPUC->connHandle);

        // Is this connection still valid?
        if (connIndex < MAX_NUM_BLE_CONNS)
        {
          // Update the phychange request status for active RSSI tracking connection
          connList[connIndex].phyCngRq = FALSE;

          if (pPUC->status == SUCCESS)
          {
            connList[connIndex].currPhy = pPUC->rxPhy;
          }
          if(pPUC->rxPhy != connList[connIndex].rqPhy)
          {
            connList[connIndex].phyRqFailCnt++;
          }
          else
          {
            // Reset the request phy counter and requested phy
            connList[connIndex].phyRqFailCnt = 0;
            connList[connIndex].rqPhy = 0;
          }
        }
      }

      break;
    }

    default:
      break;
  } // end of switch (eventCode)
}

/*********************************************************************
*********************************************************************/
/*********************************************************************
 * @fn      Util_convertBytes2Str
 *
 * @brief   Convert bytes to string. Used to print advertising data.
 *
 *
 * @param   pData - data
 *
 * @return  Adv/Scan data as a string
 */
char *Util_convertBytes2Str(uint8_t *pData, uint8_t length)
{
  uint8_t     charCnt;
  char        hex[] = "0123456789ABCDEF";
  static char str[(3*31)+1];
  char        *pStr = str;

  //*pStr++ = '0';
  //*pStr++ = 'x';

  for (charCnt = 0; charCnt < length; charCnt++)
  {
    *pStr++ = hex[*pData >> 4];
    *pStr++ = hex[*pData++ & 0x0F];
    *pStr++ = ':';
  }
  pStr = NULL;

  return str;
}
/*********************************************************************
 * @fn      GPS_readNew
 *
 * @brief   Handler function for reading GPS signal.
 *
 * @param   buff - input GPS buffer from UART communication
 * @param   output - GPSinfo
 *
 * @return  ret - checking variable.
 */
int GPS_readNew(char* buf, GPS_t* output)
{
    char* GPS_BufferHead;
    char* GPS_BufferTail;
    char* subString;
    char* subStringNext;
    int ret = 0;

    // position data
    if ((GPS_BufferHead = strstr(buf, "$GPGGA,")) != NULL)
    {
        if ((GPS_BufferTail = strstr(GPS_BufferHead, "\r\n")) != NULL && GPS_BufferTail > GPS_BufferHead)
        {
            PIN_setOutputValue(ledPinHandle, Board_LED2, !PIN_getOutputValue(Board_LED2));
            char i, len;
            int val;
            char GPS_Buffer[100];
            char temp[12];
            memcpy(GPS_Buffer, GPS_BufferHead, GPS_BufferTail - GPS_BufferHead);// after this, GPS_Buffer is like this
                                                                                // "$GPGGA,181908.01,3404.7048,N,07044.3966,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40"
            output->checkSum = GPS_BufferTail - GPS_BufferHead;

            //Testing///////////////////
            output->longitude = output->longitude + 1;
            output->altitude = output->altitude + 1;
            output->FixIndicate = output->FixIndicate + 1;
            output->UTCtime = output->UTCtime + 1;
            output->maxLen = 0;
            //////////////////////////////////////////////
            if ((subString = strstr(GPS_Buffer, ",")) == NULL)//This pointer points to the first comma after GGA
             {
                 return -2;
             }
            i = 1;
            subString++;    //pointer subString is supposed to point to the first digit for i==1, if the field is blank, it will point to the next comma
            while ((subStringNext = strstr(subString, ",")) != NULL) //pointer subStringNext points to the next comma
            {
                len = subStringNext - subString;//len >0 if the field is not blank
                switch(i)
                {
                    case 1: // get UTC time
                                                  memcpy(temp, subString, len);//do not read len-1 characters to avoid exception when len = 0, 1
                                                  temp[len] = '\0';//Set the last character at the comma position as Zero
                                                  output->UTCtime = atof(temp);
                                                  break;
                    case 2: // get latitude
                                                  memcpy(temp, subString, len);
                                                  temp[len] = '\0';//Set the last character at the comma position as Zero
                                                  output->latitude = atof(temp) / 100;
                                                  val = (int)output->latitude;
                                                  output->latitude = (float)val + (output->latitude - val) * 100 / 60;
                                                  break;
                    case 3: // get N/S
                                                  memcpy(temp, subString, 1);
                                                  output->NorthOrSouth = (char)temp[0];
                                                  break;
                    case 4: // get longitude
                                                  memcpy(temp, subString, len);
                                                  temp[len] = '\0';
                                                  output->longitude = atof(temp) / 100;
                                                  val = (int)output->longitude;
                                                  output->longitude = (float)val + (output->longitude - val) * 100 / 60;
                                                  break;
                    case 5: // get E/W
                                                  memcpy(temp, subString, 1);
                                                  output->EastOrWest = (char)temp[0];
                                                  break;
                    case 6: // get FixIndicate
                                                  memcpy(temp, subString, len);
                                                  temp[len] = '\0';
                                                  output->FixIndicate = atof(temp);
                                                  break;
                    case 7: // get SatelliteNum
                                                  memcpy(temp, subString, len);
                                                  temp[len] = '\0';
                                                  output->SatelliteNum = atof(temp);
                                                  break;
                    case 8: // get Horizontal Dilution of Precision
                                                  memcpy(temp, subString, len);
                                                  temp[len] = '\0';
                                                  output->HDOP = atof(temp);
                                                  break;
                    case 9: // get altitude
                                                  memcpy(temp, subString, len);
                                                  temp[len] = '\0';
                                                  output->altitude = atof(temp);
                                                  if (output->altitude != 0)
                                                      ret = 1;
                                                  break;
                    default:
                        break;
                }
                if(len>=output->maxLen) output->maxLen = (float)len+ ((float)(i&&0xFF))/100;
//                if(len>=1)
//                {
//                    output->longitude = len;
//                    break;
//                }
                i++;
				subString = subStringNext + 1;//pointer subString is supposed to point to the first digit for next field, if the field is blank, it will point to the next comma

            }
//            output->UTCtime = i;
        }
        else
            return -3;
    }
    else
        return -4;

    return ret;
}
