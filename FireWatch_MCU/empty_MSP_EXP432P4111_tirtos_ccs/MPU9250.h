#define true   1
#define false  0

#define MPU9250_RA_XG_ST            0x00
#define MPU9250_RA_YG_ST            0x01
#define MPU9250_RA_ZG_ST            0x02
#define MPU9250_RA_XA_ST            0x0D
#define MPU9250_RA_YA_ST            0x0E
#define MPU9250_RA_ZA_ST            0x0F
#define MPU9250_RA_XA_OFFS_H        0x77 //[15:0] XA_OFFS
#define MPU9250_RA_XA_OFFS_L_TC     0x78
#define MPU9250_RA_YA_OFFS_H        0x7A //[15:0] YA_OFFS
#define MPU9250_RA_YA_OFFS_L_TC     0x7B
#define MPU9250_RA_ZA_OFFS_H        0x7D //[15:0] ZA_OFFS
#define MPU9250_RA_ZA_OFFS_L_TC     0x7E
#define MPU9250_RA_XG_OFFS_H        0x13 //[15:0] XG_OFFS
#define MPU9250_RA_XG_OFFS_L_TC     0x14
#define MPU9250_RA_YG_OFFS_H        0x15 //[15:0] YG_OFFS
#define MPU9250_RA_YG_OFFS_L_TC     0x16
#define MPU9250_RA_ZG_OFFS_H        0x17 //[15:0] ZG_OFFS
#define MPU9250_RA_ZG_OFFS_L_TC     0x18
#define MPU9250_RA_SMPLRT_DIV       0x19
#define MPU9250_RA_CONFIG           0x1A
#define MPU9250_RA_GYRO_CONFIG      0x1B
#define MPU9250_RA_ACCEL_CONFIG     0x1C
#define MPU9250_RA_ACCEL_CONFIG2    0x1D
#define MPU9250_RA_LP_ACCEL_ODR     0x1E
#define MPU9250_RA_FIFO_EN          0x23
#define MPU9250_RA_I2C_MST_CTRL     0x24
#define MPU9250_RA_I2C_SLV0_ADDR    0x25
#define MPU9250_RA_I2C_SLV0_REG     0x26
#define MPU9250_RA_I2C_SLV0_CTRL    0x27
#define MPU9250_RA_I2C_SLV1_ADDR    0x28
#define MPU9250_RA_I2C_SLV1_REG     0x29
#define MPU9250_RA_I2C_SLV1_CTRL    0x2A
#define MPU9250_RA_I2C_SLV2_ADDR    0x2B
#define MPU9250_RA_I2C_SLV2_REG     0x2C
#define MPU9250_RA_I2C_SLV2_CTRL    0x2D
#define MPU9250_RA_I2C_SLV3_ADDR    0x2E
#define MPU9250_RA_I2C_SLV3_REG     0x2F
#define MPU9250_RA_I2C_SLV3_CTRL    0x30
#define MPU9250_RA_I2C_SLV4_ADDR    0x31
#define MPU9250_RA_I2C_SLV4_REG     0x32
#define MPU9250_RA_I2C_SLV4_DO      0x33
#define MPU9250_RA_I2C_SLV4_CTRL    0x34
#define MPU9250_RA_I2C_SLV4_DI      0x35
#define MPU9250_RA_I2C_MST_STATUS   0x36
#define MPU9250_RA_INT_PIN_CFG      0x37
#define MPU9250_RA_INT_ENABLE       0x38
#define MPU9250_RA_DMP_INT_STATUS   0x39
#define MPU9250_RA_INT_STATUS       0x3A
#define MPU9250_RA_ACCEL_XOUT_H     0x3B
#define MPU9250_RA_ACCEL_XOUT_L     0x3C
#define MPU9250_RA_ACCEL_YOUT_H     0x3D
#define MPU9250_RA_ACCEL_YOUT_L     0x3E
#define MPU9250_RA_ACCEL_ZOUT_H     0x3F
#define MPU9250_RA_ACCEL_ZOUT_L     0x40
#define MPU9250_RA_TEMP_OUT_H       0x41
#define MPU9250_RA_TEMP_OUT_L       0x42
#define MPU9250_RA_GYRO_XOUT_H      0x43
#define MPU9250_RA_GYRO_XOUT_L      0x44
#define MPU9250_RA_GYRO_YOUT_H      0x45
#define MPU9250_RA_GYRO_YOUT_L      0x46
#define MPU9250_RA_GYRO_ZOUT_H      0x47
#define MPU9250_RA_GYRO_ZOUT_L      0x48
#define MPU9250_RA_EXT_SENS_DATA_00 0x49
#define MPU9250_RA_EXT_SENS_DATA_01 0x4A
#define MPU9250_RA_EXT_SENS_DATA_02 0x4B
#define MPU9250_RA_EXT_SENS_DATA_03 0x4C
#define MPU9250_RA_EXT_SENS_DATA_04 0x4D
#define MPU9250_RA_EXT_SENS_DATA_05 0x4E
#define MPU9250_RA_EXT_SENS_DATA_06 0x4F
#define MPU9250_RA_EXT_SENS_DATA_07 0x50
#define MPU9250_RA_EXT_SENS_DATA_08 0x51
#define MPU9250_RA_EXT_SENS_DATA_09 0x52
#define MPU9250_RA_EXT_SENS_DATA_10 0x53
#define MPU9250_RA_EXT_SENS_DATA_11 0x54
#define MPU9250_RA_EXT_SENS_DATA_12 0x55
#define MPU9250_RA_EXT_SENS_DATA_13 0x56
#define MPU9250_RA_EXT_SENS_DATA_14 0x57
#define MPU9250_RA_EXT_SENS_DATA_15 0x58
#define MPU9250_RA_EXT_SENS_DATA_16 0x59
#define MPU9250_RA_EXT_SENS_DATA_17 0x5A
#define MPU9250_RA_EXT_SENS_DATA_18 0x5B
#define MPU9250_RA_EXT_SENS_DATA_19 0x5C
#define MPU9250_RA_EXT_SENS_DATA_20 0x5D
#define MPU9250_RA_EXT_SENS_DATA_21 0x5E
#define MPU9250_RA_EXT_SENS_DATA_22 0x5F
#define MPU9250_RA_EXT_SENS_DATA_23 0x60
#define MPU9250_RA_I2C_SLV0_DO      0x63
#define MPU9250_RA_I2C_SLV1_DO      0x64
#define MPU9250_RA_I2C_SLV2_DO      0x65
#define MPU9250_RA_I2C_SLV3_DO      0x66
#define MPU9250_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU9250_RA_SIGNAL_PATH_RESET    0x68
#define MPU9250_RA_MOT_DETECT_CTRL      0x69
#define MPU9250_RA_USER_CTRL        0x6A
#define MPU9250_RA_PWR_MGMT_1       0x6B
#define MPU9250_RA_PWR_MGMT_2       0x6C
#define MPU9250_RA_BANK_SEL         0x6D
#define MPU9250_RA_MEM_START_ADDR   0x6E
#define MPU9250_RA_MEM_R_W          0x6F
#define MPU9250_RA_DMP_CFG_1        0x70
#define MPU9250_RA_DMP_CFG_2        0x71
#define MPU9250_RA_FIFO_COUNTH      0x72
#define MPU9250_RA_FIFO_COUNTL      0x73
#define MPU9250_RA_FIFO_R_W         0x74
#define MPU9250_RA_WHO_AM_I         0x75

#define MPU9250_TC_PWR_MODE_BIT     7
#define MPU9250_TC_OFFSET_BIT       6
#define MPU9250_TC_OFFSET_LENGTH     6
#define MPU9250_TC_OTP_BNK_VLD_BIT  0

#define MPU9250_VDDIO_LEVEL_VLOGIC  0
#define MPU9250_VDDIO_LEVEL_VDD     1

#define MPU9250_CFG_EXT_SYNC_SET_BIT    5
#define MPU9250_CFG_EXT_SYNC_SET_LENGTH  3
#define MPU9250_CFG_DLPF_CFG_BIT        2
#define MPU9250_CFG_DLPF_CFG_LENGTH      3

#define MPU9250_EXT_SYNC_DISABLED       0x0
#define MPU9250_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU9250_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU9250_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU9250_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU9250_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU9250_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU9250_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU9250_DLPF_BW_250         0x00
#define MPU9250_DLPF_BW_184         0x01
#define MPU9250_DLPF_BW_92          0x02
#define MPU9250_DLPF_BW_41          0x03
#define MPU9250_DLPF_BW_20          0x04
#define MPU9250_DLPF_BW_10          0x05
#define MPU9250_DLPF_BW_5           0x06

#define MPU9250_GCONFIG_FS_SEL_BIT      4
#define MPU9250_GCONFIG_FS_SEL_LENGTH    2

#define MPU9250_GYRO_FS_250         0x00
#define MPU9250_GYRO_FS_500         0x01
#define MPU9250_GYRO_FS_1000        0x02
#define MPU9250_GYRO_FS_2000        0x03

#define MPU9250_ACONFIG_XA_ST_BIT           7
#define MPU9250_ACONFIG_YA_ST_BIT           6
#define MPU9250_ACONFIG_ZA_ST_BIT           5
#define MPU9250_ACONFIG_AFS_SEL_BIT         4
#define MPU9250_ACONFIG_AFS_SEL_LENGTH       2
#define MPU9250_ACONFIG_ACCEL_HPF_BIT       2
#define MPU9250_ACONFIG_ACCEL_HPF_LENGTH     3

#define MPU9250_ACCEL_FS_2          0x00
#define MPU9250_ACCEL_FS_4          0x01
#define MPU9250_ACCEL_FS_8          0x02
#define MPU9250_ACCEL_FS_16         0x03

#define MPU9250_DHPF_RESET          0x00
#define MPU9250_DHPF_5              0x01
#define MPU9250_DHPF_2P5            0x02
#define MPU9250_DHPF_1P25           0x03
#define MPU9250_DHPF_0P63           0x04
#define MPU9250_DHPF_HOLD           0x07

#define MPU9250_TEMP_FIFO_EN_BIT    7
#define MPU9250_XG_FIFO_EN_BIT      6
#define MPU9250_YG_FIFO_EN_BIT      5
#define MPU9250_ZG_FIFO_EN_BIT      4
#define MPU9250_ACCEL_FIFO_EN_BIT   3
#define MPU9250_SLV2_FIFO_EN_BIT    2
#define MPU9250_SLV1_FIFO_EN_BIT    1
#define MPU9250_SLV0_FIFO_EN_BIT    0

#define MPU9250_MULT_MST_EN_BIT     7
#define MPU9250_WAIT_FOR_ES_BIT     6
#define MPU9250_SLV_3_FIFO_EN_BIT   5
#define MPU9250_I2C_MST_P_NSR_BIT   4
#define MPU9250_I2C_MST_CLK_BIT     3
#define MPU9250_I2C_MST_CLK_LENGTH  4

#define MPU9250_CLOCK_DIV_348       0x0
#define MPU9250_CLOCK_DIV_333       0x1
#define MPU9250_CLOCK_DIV_320       0x2
#define MPU9250_CLOCK_DIV_308       0x3
#define MPU9250_CLOCK_DIV_296       0x4
#define MPU9250_CLOCK_DIV_286       0x5
#define MPU9250_CLOCK_DIV_276       0x6
#define MPU9250_CLOCK_DIV_267       0x7
#define MPU9250_CLOCK_DIV_258       0x8
#define MPU9250_CLOCK_DIV_500       0x9
#define MPU9250_CLOCK_DIV_471       0xA
#define MPU9250_CLOCK_DIV_444       0xB
#define MPU9250_CLOCK_DIV_421       0xC
#define MPU9250_CLOCK_DIV_400       0xD
#define MPU9250_CLOCK_DIV_381       0xE
#define MPU9250_CLOCK_DIV_364       0xF

#define MPU9250_I2C_SLV_RW_BIT      7
#define MPU9250_I2C_SLV_ADDR_BIT    6
#define MPU9250_I2C_SLV_ADDR_LENGTH 7
#define MPU9250_I2C_SLV_EN_BIT      7
#define MPU9250_I2C_SLV_BYTE_SW_BIT 6
#define MPU9250_I2C_SLV_REG_DIS_BIT 5
#define MPU9250_I2C_SLV_GRP_BIT     4
#define MPU9250_I2C_SLV_LEN_BIT     3
#define MPU9250_I2C_SLV_LEN_LENGTH  4

#define MPU9250_I2C_SLV4_RW_BIT         7
#define MPU9250_I2C_SLV4_ADDR_BIT       6
#define MPU9250_I2C_SLV4_ADDR_LENGTH    7
#define MPU9250_I2C_SLV4_EN_BIT         7
#define MPU9250_I2C_SLV4_INT_EN_BIT     6
#define MPU9250_I2C_SLV4_REG_DIS_BIT    5
#define MPU9250_I2C_SLV4_MST_DLY_BIT    4
#define MPU9250_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU9250_MST_PASS_THROUGH_BIT    7
#define MPU9250_MST_I2C_SLV4_DONE_BIT   6
#define MPU9250_MST_I2C_LOST_ARB_BIT    5
#define MPU9250_MST_I2C_SLV4_NACK_BIT   4
#define MPU9250_MST_I2C_SLV3_NACK_BIT   3
#define MPU9250_MST_I2C_SLV2_NACK_BIT   2
#define MPU9250_MST_I2C_SLV1_NACK_BIT   1
#define MPU9250_MST_I2C_SLV0_NACK_BIT   0

#define MPU9250_INTCFG_INT_LEVEL_BIT        7
#define MPU9250_INTCFG_INT_OPEN_BIT         6
#define MPU9250_INTCFG_LATCH_INT_EN_BIT     5
#define MPU9250_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU9250_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU9250_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU9250_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU9250_INTCFG_CLKOUT_EN_BIT        0

#define MPU9250_INTMODE_ACTIVEHIGH  0x00
#define MPU9250_INTMODE_ACTIVELOW   0x01

#define MPU9250_INTDRV_PUSHPULL     0x00
#define MPU9250_INTDRV_OPENDRAIN    0x01

#define MPU9250_INTLATCH_50USPULSE  0x00
#define MPU9250_INTLATCH_WAITCLEAR  0x01

#define MPU9250_INTCLEAR_STATUSREAD 0x00
#define MPU9250_INTCLEAR_ANYREAD    0x01

#define MPU9250_INTERRUPT_FF_BIT            7
#define MPU9250_INTERRUPT_MOT_BIT           6
#define MPU9250_INTERRUPT_ZMOT_BIT          5
#define MPU9250_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU9250_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU9250_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU9250_INTERRUPT_DMP_INT_BIT       1
#define MPU9250_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU9250_DMPINT_5_BIT            5
#define MPU9250_DMPINT_4_BIT            4
#define MPU9250_DMPINT_3_BIT            3
#define MPU9250_DMPINT_2_BIT            2
#define MPU9250_DMPINT_1_BIT            1
#define MPU9250_DMPINT_0_BIT            0

#define MPU9250_MOTION_MOT_XNEG_BIT     7
#define MPU9250_MOTION_MOT_XPOS_BIT     6
#define MPU9250_MOTION_MOT_YNEG_BIT     5
#define MPU9250_MOTION_MOT_YPOS_BIT     4
#define MPU9250_MOTION_MOT_ZNEG_BIT     3
#define MPU9250_MOTION_MOT_ZPOS_BIT     2
#define MPU9250_MOTION_MOT_ZRMOT_BIT    0

#define MPU9250_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU9250_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU9250_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU9250_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU9250_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU9250_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU9250_PATHRESET_GYRO_RESET_BIT    2
#define MPU9250_PATHRESET_ACCEL_RESET_BIT   1
#define MPU9250_PATHRESET_TEMP_RESET_BIT    0

#define MPU9250_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU9250_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU9250_DETECT_FF_COUNT_BIT             3
#define MPU9250_DETECT_FF_COUNT_LENGTH          2
#define MPU9250_DETECT_MOT_COUNT_BIT            1
#define MPU9250_DETECT_MOT_COUNT_LENGTH         2

#define MPU9250_DETECT_DECREMENT_RESET  0x0
#define MPU9250_DETECT_DECREMENT_1      0x1
#define MPU9250_DETECT_DECREMENT_2      0x2
#define MPU9250_DETECT_DECREMENT_4      0x3

#define MPU9250_USERCTRL_DMP_EN_BIT             7
#define MPU9250_USERCTRL_FIFO_EN_BIT            6
#define MPU9250_USERCTRL_I2C_MST_EN_BIT         5
#define MPU9250_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU9250_USERCTRL_DMP_RESET_BIT          3
#define MPU9250_USERCTRL_FIFO_RESET_BIT         2
#define MPU9250_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU9250_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU9250_PWR1_DEVICE_RESET_BIT   7
#define MPU9250_PWR1_SLEEP_BIT          6
#define MPU9250_PWR1_CYCLE_BIT          5
#define MPU9250_PWR1_TEMP_DIS_BIT       3
#define MPU9250_PWR1_CLKSEL_BIT         2
#define MPU9250_PWR1_CLKSEL_LENGTH      3

#define MPU9250_CLOCK_INTERNAL          0x00
#define MPU9250_CLOCK_PLL_XGYRO         0x01
#define MPU9250_CLOCK_PLL_YGYRO         0x02
#define MPU9250_CLOCK_PLL_ZGYRO         0x03
#define MPU9250_CLOCK_PLL_EXT32K        0x04
#define MPU9250_CLOCK_PLL_EXT19M        0x05
#define MPU9250_CLOCK_KEEP_RESET        0x07

#define MPU9250_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU9250_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU9250_PWR2_STBY_XA_BIT            5
#define MPU9250_PWR2_STBY_YA_BIT            4
#define MPU9250_PWR2_STBY_ZA_BIT            3
#define MPU9250_PWR2_STBY_XG_BIT            2
#define MPU9250_PWR2_STBY_YG_BIT            1
#define MPU9250_PWR2_STBY_ZG_BIT            0

#define MPU9250_WAKE_FREQ_1P25      0x0
#define MPU9250_WAKE_FREQ_2P5       0x1
#define MPU9250_WAKE_FREQ_5         0x2
#define MPU9250_WAKE_FREQ_10        0x3

#define MPU9250_BANKSEL_PRFTCH_EN_BIT       6
#define MPU9250_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU9250_BANKSEL_MEM_SEL_BIT         4
#define MPU9250_BANKSEL_MEM_SEL_LENGTH      5

#define MPU9250_WHO_AM_I_BIT        6
#define MPU9250_WHO_AM_I_LENGTH     6

#define MPU9250_DMP_MEMORY_BANKS        8
#define MPU9250_DMP_MEMORY_BANK_SIZE    256
#define MPU9250_DMP_MEMORY_CHUNK_SIZE   16

// SMPLRT_DIV register
void mpu_setRate(unsigned char rate);

// CONFIG register

void mpu_setDLPFMode(unsigned char mode);

// GYRO_CONFIG register
unsigned char mpu_getFullScaleGyroRange();
void mpu_setFullScaleGyroRange(unsigned char range);
// ACCEL_CONFIG register
void mpu_setAccelXSelfTest(char enabled);
void mpu_setAccelYSelfTest(char enabled);
void mpu_setAccelZSelfTest(char enabled);
unsigned char mpu_getFullScaleAccelRange();
void mpu_setFullScaleAccelRange(unsigned char range);
void mpu_setDHPFMode(unsigned char bandwidth);

// I2C_MST_CTRL register
void mpu_setMultiMasterEnabled(char enabled);
void mpu_setWaitForExternalSensorEnabled(char enabled);
void mpu_setSlave3FIFOEnabled(char enabled);
void mpu_setSlaveReadWriteTransitionEnabled(char enabled);
void mpu_setMasterClockSpeed(unsigned char speed);

// I2C_SLV* registers (Slave 0-3)

void mpu_setSlaveAddress(unsigned char num, unsigned char address);
void mpu_setSlaveRegister(unsigned char num, unsigned char reg);
void mpu_setSlaveEnabled(unsigned char num, char enabled);
void mpu_setSlaveWordByteSwap(unsigned char num, char enabled);
void mpu_setSlaveWriteMode(unsigned char num, char mode);
void mpu_setSlaveWordGroupOffset(unsigned char num, char enabled);
void mpu_setSlaveDataLength(unsigned char num, unsigned char length);

// I2C_SLV* registers (Slave 4)

void mpu_setSlave4Address(unsigned char address);
void mpu_setSlave4Register(unsigned char reg);
void mpu_setSlave4OutputByte(unsigned char output);
void mpu_setSlave4Enabled(char enabled);
void mpu_setSlave4InterruptEnabled(char enabled);
void mpu_setSlave4WriteMode(char mode);
void mpu_setSlave4MasterDelay(unsigned char delay);

// INT_PIN_CFG register
void mpu_setInterruptMode(char mode);
void mpu_setInterruptDrive(char drive);
void mpu_setInterruptLatch(char latch);
void mpu_setInterruptLatchClear(char clear);
void mpu_setFSyncInterruptLevel(char level);
void mpu_setFSyncInterruptEnabled(char enabled);
void mpu_setI2CBypassEnabled(char enabled);
void mpu_setClockOutputEnabled(char enabled);

// INT_ENABLE register
void mpu_setIntEnabled(unsigned char enabled);
void mpu_setIntFreefallEnabled(char enabled);
void mpu_setIntMotionEnabled(char enabled);
void mpu_setIntZeroMotionEnabled(char enabled);
void mpu_setIntFIFOBufferOverflowEnabled(char enabled);
void mpu_setIntI2CMasterEnabled(char enabled);
void mpu_setIntDataReadyEnabled(char enabled);

// INT_STATUS register
unsigned char mpu_getIntStatus();
/*
// ACCEL_*OUT_* registers
void mpu_getAcceleration(int* x, int* y, int* z);

// GYRO_*OUT_* registers
void mpu_getRotation(int* x, int* y, int* z);
*/
// I2C_SLV*_DO register
void mpu_setSlaveOutputByte(unsigned char num, unsigned char output);

// I2C_MST_DELAY_CTRL register
void mpu_setExternalShadowDelayEnabled(char enabled);
void mpu_setSlaveDelayEnabled(unsigned char num, char enabled);

// MOT_DETECT_CTRL register
void mpu_setAccelerometerPowerOnDelay(unsigned char delay);
void mpu_setFreefallDetectionCounterDecrement(unsigned char decrement);
void mpu_setMotionDetectionCounterDecrement(unsigned char decrement);

// USER_CTRL register
void mpu_setFIFOEnabled(char enabled);
void mpu_setI2CMasterModeEnabled(char enabled);
void mpu_switchSPIEnabled(char enabled);
void mpu_resetFIFO();
void mpu_resetI2CMaster();
void mpu_resetSensors();

// PWR_MGMT_1 register
void mpu_reset();
void mpu_setSleepEnabled(char enabled);
void mpu_setWakeCycleEnabled(char enabled);
void mpu_setTempSensorEnabled(char enabled);
void mpu_setClockSource(unsigned char source);

// PWR_MGMT_2 register*/
void mpu_setWakeFrequency(unsigned char frequency);
void mpu_setStandbyXAccelEnabled(char enabled);
void mpu_setStandbyYAccelEnabled(char enabled);
void mpu_setStandbyZAccelEnabled(char enabled);
void mpu_setStandbyXGyroEnabled(char enabled);
void mpu_setStandbyYGyroEnabled(char enabled);
void mpu_setStandbyZGyroEnabled(char enabled);

// FIFO_COUNT* registers
unsigned int mpu_getFIFOCount();

// FIFO_R_W register
void mpu_getFIFOBytes(unsigned char *output, unsigned char length);
void mpu_setFIFOByte(unsigned char output);

// WHO_AM_I register
unsigned char mpu_getDeviceID();

// ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========

// XA_OFFS_* registers

int mpu_getXAccelOffset();
void mpu_setXAccelOffset(int offset);

// YA_OFFS_* register

int mpu_getYAccelOffset();
void mpu_setYAccelOffset(int offset);

// ZA_OFFS_* register

int mpu_getZAccelOffset();
void mpu_setZAccelOffset(int offset);

// XG_OFFS_USR* registers

int mpu_getXGyroOffset();
void mpu_setXGyroOffset(int offset);

// YG_OFFS_USR* register

int mpu_getYGyroOffset();
void mpu_setYGyroOffset(int offset);

// ZG_OFFS_USR* register

int mpu_getZGyroOffset();
void mpu_setZGyroOffset(int offset);

// INT_ENABLE register (DMP functions)

void mpu_setIntPLLReadyEnabled(char enabled);
void mpu_setIntDMPEnabled(char enabled);

// DMP_INT_STATUS

char mpu_getDMPInt5Status();
char mpu_getDMPInt4Status();
char mpu_getDMPInt3Status();
char mpu_getDMPInt2Status();
char mpu_getDMPInt1Status();
char mpu_getDMPInt0Status();

// INT_STATUS register (DMP functions)

char mpu_getIntPLLReadyStatus();
char mpu_getIntDMPStatus();

// USER_CTRL register (DMP functions)

void mpu_setDMPEnabled(char enabled);
void mpu_resetDMP();

// BANK_SEL register

void mpu_setMemoryBank(unsigned char bank);

// MEM_START_ADDR register

void mpu_setMemoryStartAddress(unsigned char address);

// MEM_R_W register

unsigned char mpu_readMemoryByte();
void mpu_writeMemoryByte(unsigned char output);
void mpu_readMemoryBlock(unsigned char *output, unsigned int dataSize, unsigned char bank, unsigned char address);
char mpu_writeMemoryBlock(const unsigned char *output, unsigned int dataSize, unsigned char bank, unsigned char address, char verify, char useProgMem);
char mpu_writeProgMemoryBlock(const unsigned char *output, unsigned int dataSize, unsigned char bank, unsigned char address, char verify);
char mpu_writeDMPConfigurationSet(const unsigned char *output, unsigned int dataSize, char useProgMem);
char mpu_writeProgDMPConfigurationSet(const unsigned char *output, unsigned int dataSize);

// DMP_CFG_1 register

unsigned char mpu_getDMPConfig1();
void mpu_setDMPConfig1(unsigned char config);

// DMP_CFG_2 register

unsigned char mpu_getDMPConfig2();
void mpu_setDMPConfig2(unsigned char config);

