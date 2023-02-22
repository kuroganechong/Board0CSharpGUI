//#include<stdlib.h>
#include<string.h>
#include "MPU9250.h"
#include "IMU_driver.h"

// note: DMP code memory blocks defined at end of header file

// SMPLRT_DIV register
void mpu_setRate(unsigned char rate) {
    writeRegister(MPU9250_RA_SMPLRT_DIV, rate);
}

// CONFIG register

void mpu_setDLPFMode(unsigned char mode) {
    writeRegBits(MPU9250_RA_CONFIG, MPU9250_CFG_DLPF_CFG_BIT, MPU9250_CFG_DLPF_CFG_LENGTH, mode);
}

// GYRO_CONFIG register
unsigned char mpu_getFullScaleGyroRange() {
    unsigned char buffer;
    readRegBits(MPU9250_RA_GYRO_CONFIG, MPU9250_GCONFIG_FS_SEL_BIT, MPU9250_GCONFIG_FS_SEL_LENGTH, &buffer);
    return buffer;
}
void mpu_setFullScaleGyroRange(unsigned char range) {
    writeRegBits(MPU9250_RA_GYRO_CONFIG, MPU9250_GCONFIG_FS_SEL_BIT, MPU9250_GCONFIG_FS_SEL_LENGTH, range);
}

// ACCEL_CONFIG register
void mpu_setAccelXSelfTest(char enabled) {
    writeRegBit(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_XA_ST_BIT, enabled);
}
void mpu_setAccelYSelfTest(char enabled) {
    writeRegBit(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_YA_ST_BIT, enabled);
}
void mpu_setAccelZSelfTest(char enabled) {
    writeRegBit(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_ZA_ST_BIT, enabled);
}
unsigned char mpu_getFullScaleAccelRange() {
    unsigned char buffer;
    readRegBits(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_AFS_SEL_BIT, MPU9250_ACONFIG_AFS_SEL_LENGTH, &buffer);
    return buffer;
}
void mpu_setFullScaleAccelRange(unsigned char range) {
    writeRegBits(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_AFS_SEL_BIT, MPU9250_ACONFIG_AFS_SEL_LENGTH, range);
}
void mpu_setDHPFMode(unsigned char bandwidth) {
    writeRegBits(MPU9250_RA_ACCEL_CONFIG, MPU9250_ACONFIG_ACCEL_HPF_BIT, MPU9250_ACONFIG_ACCEL_HPF_LENGTH, bandwidth);
}

// I2C_MST_CTRL register
void mpu_setMultiMasterEnabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_MST_CTRL, MPU9250_MULT_MST_EN_BIT, enabled);
}
void mpu_setWaitForExternalSensorEnabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_MST_CTRL, MPU9250_WAIT_FOR_ES_BIT, enabled);
}
void mpu_setSlave3FIFOEnabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_MST_CTRL, MPU9250_SLV_3_FIFO_EN_BIT, enabled);
}
void mpu_setSlaveReadWriteTransitionEnabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_MST_CTRL, MPU9250_I2C_MST_P_NSR_BIT, enabled);
}
void mpu_setMasterClockSpeed(unsigned char speed) {
    writeRegBits(MPU9250_RA_I2C_MST_CTRL, MPU9250_I2C_MST_CLK_BIT, MPU9250_I2C_MST_CLK_LENGTH, speed);
}

// I2C_SLV* registers (Slave 0-3)

void mpu_setSlaveAddress(unsigned char num, unsigned char address) {
    if (num > 3) return;
    writeRegister(MPU9250_RA_I2C_SLV0_ADDR + num*3, address);
}
void mpu_setSlaveRegister(unsigned char num, unsigned char reg) {
    if (num > 3) return;
    writeRegister(MPU9250_RA_I2C_SLV0_REG + num*3, reg);
}
void mpu_setSlaveEnabled(unsigned char num, char enabled) {
    if (num > 3) return;
    writeRegBit(MPU9250_RA_I2C_SLV0_CTRL + num*3, MPU9250_I2C_SLV_EN_BIT, enabled);
}
void mpu_setSlaveWordByteSwap(unsigned char num, char enabled) {
    if (num > 3) return;
    writeRegBit(MPU9250_RA_I2C_SLV0_CTRL + num*3, MPU9250_I2C_SLV_BYTE_SW_BIT, enabled);
}
void mpu_setSlaveWriteMode(unsigned char num, char mode) {
    if (num > 3) return;
    writeRegBit(MPU9250_RA_I2C_SLV0_CTRL + num*3, MPU9250_I2C_SLV_REG_DIS_BIT, mode);
}
void mpu_setSlaveWordGroupOffset(unsigned char num, char enabled) {
    if (num > 3) return;
    writeRegBit(MPU9250_RA_I2C_SLV0_CTRL + num*3, MPU9250_I2C_SLV_GRP_BIT, enabled);
}
void mpu_setSlaveDataLength(unsigned char num, unsigned char length) {
    if (num > 3) return;
    writeRegBits(MPU9250_RA_I2C_SLV0_CTRL + num*3, MPU9250_I2C_SLV_LEN_BIT, MPU9250_I2C_SLV_LEN_LENGTH, length);
}

// I2C_SLV* registers (Slave 4)

void mpu_setSlave4Address(unsigned char address) {
    writeRegister(MPU9250_RA_I2C_SLV4_ADDR, address);
}
void mpu_setSlave4Register(unsigned char reg) {
    writeRegister(MPU9250_RA_I2C_SLV4_REG, reg);
}
void mpu_setSlave4OutputByte(unsigned char output) {
    writeRegister(MPU9250_RA_I2C_SLV4_DO, output);
}
void mpu_setSlave4Enabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_SLV4_CTRL, MPU9250_I2C_SLV4_EN_BIT, enabled);
}
void mpu_setSlave4InterruptEnabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_SLV4_CTRL, MPU9250_I2C_SLV4_INT_EN_BIT, enabled);
}
void mpu_setSlave4WriteMode(char mode) {
    writeRegBit(MPU9250_RA_I2C_SLV4_CTRL, MPU9250_I2C_SLV4_REG_DIS_BIT, mode);
}
void mpu_setSlave4MasterDelay(unsigned char delay) {
    writeRegBits(MPU9250_RA_I2C_SLV4_CTRL, MPU9250_I2C_SLV4_MST_DLY_BIT, MPU9250_I2C_SLV4_MST_DLY_LENGTH, delay);
}

// INT_PIN_CFG register
void mpu_setInterruptMode(char mode) {
   writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_INT_LEVEL_BIT, mode);
}
void mpu_setInterruptDrive(char drive) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_INT_OPEN_BIT, drive);
}
void mpu_setInterruptLatch(char latch) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_LATCH_INT_EN_BIT, latch);
}
void mpu_setInterruptLatchClear(char clear) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_INT_RD_CLEAR_BIT, clear);
}
void mpu_setFSyncInterruptLevel(char level) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_FSYNC_INT_LEVEL_BIT, level);
}
void mpu_setFSyncInterruptEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_FSYNC_INT_EN_BIT, enabled);
}
void mpu_setI2CBypassEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}
void mpu_setClockOutputEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_PIN_CFG, MPU9250_INTCFG_CLKOUT_EN_BIT, enabled);
}

// INT_ENABLE register
void mpu_setIntEnabled(unsigned char enabled) {
    writeRegister(MPU9250_RA_INT_ENABLE, enabled);
}
void mpu_setIntFreefallEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_FF_BIT, enabled);
}
void mpu_setIntMotionEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_MOT_BIT, enabled);
}
void mpu_setIntZeroMotionEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_ZMOT_BIT, enabled);
}
void mpu_setIntFIFOBufferOverflowEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_FIFO_OFLOW_BIT, enabled);
}
void mpu_setIntI2CMasterEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_I2C_MST_INT_BIT, enabled);
}
void mpu_setIntDataReadyEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_DATA_RDY_BIT, enabled);
}

// INT_STATUS register
unsigned char mpu_getIntStatus() {
    unsigned char buffer;
    readRegister(MPU9250_RA_INT_STATUS, &buffer);
    return buffer;
}
/*
// ACCEL_*OUT_* registers
void mpu_getAcceleration(int* x, int* y, int* z) {
    readRegisters(MPU9250_RA_ACCEL_XOUT_H, 6, buffer);
    *x = (((int)buffer[0]) << 8) | buffer[1];
    *y = (((int)buffer[2]) << 8) | buffer[3];
    *z = (((int)buffer[4]) << 8) | buffer[5];
}

// GYRO_*OUT_* registers
void mpu_getRotation(int* x, int* y, int* z) {
    readRegisters(MPU9250_RA_GYRO_XOUT_H, 6, buffer);
    *x = (((int)buffer[0]) << 8) | buffer[1];
    *y = (((int)buffer[2]) << 8) | buffer[3];
    *z = (((int)buffer[4]) << 8) | buffer[5];
}
*/
// I2C_SLV*_DO register
void mpu_setSlaveOutputByte(unsigned char num, unsigned char output) {
    if (num > 3) return;
    writeRegister(MPU9250_RA_I2C_SLV0_DO + num, output);
}

// I2C_MST_DELAY_CTRL register
void mpu_setExternalShadowDelayEnabled(char enabled) {
    writeRegBit(MPU9250_RA_I2C_MST_DELAY_CTRL, MPU9250_DELAYCTRL_DELAY_ES_SHADOW_BIT, enabled);
}
void mpu_setSlaveDelayEnabled(unsigned char num, char enabled) {
    writeRegBit(MPU9250_RA_I2C_MST_DELAY_CTRL, num, enabled);
}

// MOT_DETECT_CTRL register
void mpu_setAccelerometerPowerOnDelay(unsigned char delay) {
    writeRegBits(MPU9250_RA_MOT_DETECT_CTRL, MPU9250_DETECT_ACCEL_ON_DELAY_BIT, MPU9250_DETECT_ACCEL_ON_DELAY_LENGTH, delay);
}
void mpu_setFreefallDetectionCounterDecrement(unsigned char decrement) {
    writeRegBits(MPU9250_RA_MOT_DETECT_CTRL, MPU9250_DETECT_FF_COUNT_BIT, MPU9250_DETECT_FF_COUNT_LENGTH, decrement);
}
void mpu_setMotionDetectionCounterDecrement(unsigned char decrement) {
    writeRegBits(MPU9250_RA_MOT_DETECT_CTRL, MPU9250_DETECT_MOT_COUNT_BIT, MPU9250_DETECT_MOT_COUNT_LENGTH, decrement);
}

// USER_CTRL register
void mpu_setFIFOEnabled(char enabled) {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_FIFO_EN_BIT, enabled);
}
void mpu_setI2CMasterModeEnabled(char enabled) {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_I2C_MST_EN_BIT, enabled);
}
void mpu_switchSPIEnabled(char enabled) {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_I2C_IF_DIS_BIT, enabled);
}
void mpu_resetFIFO() {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_FIFO_RESET_BIT, true);
}
void mpu_resetI2CMaster() {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_I2C_MST_RESET_BIT, true);
}
void mpu_resetSensors() {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_SIG_COND_RESET_BIT, true);
}

// PWR_MGMT_1 register
void mpu_reset() {
    writeRegBit(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_DEVICE_RESET_BIT, true);
}
void mpu_setSleepEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_SLEEP_BIT, enabled);
}
void mpu_setWakeCycleEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_CYCLE_BIT, enabled);
}
void mpu_setTempSensorEnabled(char enabled) {
    // 1 is actually disabled here
    writeRegBit(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_TEMP_DIS_BIT, !enabled);
}
void mpu_setClockSource(unsigned char source) {
    writeRegBits(MPU9250_RA_PWR_MGMT_1, MPU9250_PWR1_CLKSEL_BIT, MPU9250_PWR1_CLKSEL_LENGTH, source);
}

// PWR_MGMT_2 register*/
void mpu_setWakeFrequency(unsigned char frequency) {
    writeRegBits(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_LP_WAKE_CTRL_BIT, MPU9250_PWR2_LP_WAKE_CTRL_LENGTH, frequency);
}
void mpu_setStandbyXAccelEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_STBY_XA_BIT, enabled);
}
void mpu_setStandbyYAccelEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_STBY_YA_BIT, enabled);
}
void mpu_setStandbyZAccelEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_STBY_ZA_BIT, enabled);
}
void mpu_setStandbyXGyroEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_STBY_XG_BIT, enabled);
}
void mpu_setStandbyYGyroEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_STBY_YG_BIT, enabled);
}
void mpu_setStandbyZGyroEnabled(char enabled) {
    writeRegBit(MPU9250_RA_PWR_MGMT_2, MPU9250_PWR2_STBY_ZG_BIT, enabled);
}

// FIFO_COUNT* registers
unsigned int mpu_getFIFOCount() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_FIFO_COUNTH, 2, buffer);
    return (((unsigned int)buffer[0]) << 8) | buffer[1];
}

// FIFO_R_W register
void mpu_getFIFOBytes(unsigned char *output, unsigned char length) {
    readRegisters(MPU9250_RA_FIFO_R_W, length, output);
}
void mpu_setFIFOByte(unsigned char output) {
    writeRegister(MPU9250_RA_FIFO_R_W, output);
}

// WHO_AM_I register
unsigned char mpu_getDeviceID() {
    unsigned char buffer;
    readRegBits(MPU9250_RA_WHO_AM_I, MPU9250_WHO_AM_I_BIT, MPU9250_WHO_AM_I_LENGTH, &buffer);
    return buffer;
}

// ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========

// XA_OFFS_* registers

int mpu_getXAccelOffset() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_XA_OFFS_H, 2, buffer);
    return (((int)buffer[0]) << 8) | buffer[1];
}
void mpu_setXAccelOffset(int offset) {
    writeRegWord(MPU9250_RA_XA_OFFS_H, offset);
}

// YA_OFFS_* register

int mpu_getYAccelOffset() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_YA_OFFS_H, 2, buffer);
    return (((int)buffer[0]) << 8) | buffer[1];
}
void mpu_setYAccelOffset(int offset) {
    writeRegWord(MPU9250_RA_YA_OFFS_H, offset);
}

// ZA_OFFS_* register

int mpu_getZAccelOffset() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_ZA_OFFS_H, 2, buffer);
    return (((int)buffer[0]) << 8) | buffer[1];
}
void mpu_setZAccelOffset(int offset) {
    writeRegWord(MPU9250_RA_ZA_OFFS_H, offset);
}

// XG_OFFS_USR* registers

int mpu_getXGyroOffset() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_XG_OFFS_H, 2, buffer);
    return (((int)buffer[0]) << 8) | buffer[1];
}
void mpu_setXGyroOffset(int offset) {
    writeRegWord(MPU9250_RA_XG_OFFS_H, offset);
}

// YG_OFFS_USR* register

int mpu_getYGyroOffset() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_YG_OFFS_H, 2, buffer);
    return (((int)buffer[0]) << 8) | buffer[1];
}
void mpu_setYGyroOffset(int offset) {
    writeRegWord(MPU9250_RA_YG_OFFS_H, offset);
}

// ZG_OFFS_USR* register

int mpu_getZGyroOffset() {
    unsigned char buffer[2];
    readRegisters(MPU9250_RA_ZG_OFFS_H, 2, buffer);
    return (((int)buffer[0]) << 8) | buffer[1];
}
void mpu_setZGyroOffset(int offset) {
    writeRegWord(MPU9250_RA_ZG_OFFS_H, offset);
}

// INT_ENABLE register (DMP functions)

void mpu_setIntPLLReadyEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_PLL_RDY_INT_BIT, enabled);
}
void mpu_setIntDMPEnabled(char enabled) {
    writeRegBit(MPU9250_RA_INT_ENABLE, MPU9250_INTERRUPT_DMP_INT_BIT, enabled);
}

// DMP_INT_STATUS

char mpu_getDMPInt5Status() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_DMP_INT_STATUS, MPU9250_DMPINT_5_BIT, &buffer);
    return buffer;
}
char mpu_getDMPInt4Status() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_DMP_INT_STATUS, MPU9250_DMPINT_4_BIT, &buffer);
    return buffer;
}
char mpu_getDMPInt3Status() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_DMP_INT_STATUS, MPU9250_DMPINT_3_BIT, &buffer);
    return buffer;
}
char mpu_getDMPInt2Status() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_DMP_INT_STATUS, MPU9250_DMPINT_2_BIT, &buffer);
    return buffer;
}
char mpu_getDMPInt1Status() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_DMP_INT_STATUS, MPU9250_DMPINT_1_BIT, &buffer);
    return buffer;
}
char mpu_getDMPInt0Status() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_DMP_INT_STATUS, MPU9250_DMPINT_0_BIT, &buffer);
    return buffer;
}

// INT_STATUS register (DMP functions)

char mpu_getIntPLLReadyStatus() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_INT_STATUS, MPU9250_INTERRUPT_PLL_RDY_INT_BIT, &buffer);
    return buffer;
}
char mpu_getIntDMPStatus() {
    unsigned char buffer;
    readRegBit(MPU9250_RA_INT_STATUS, MPU9250_INTERRUPT_DMP_INT_BIT, &buffer);
    return buffer;
}

// USER_CTRL register (DMP functions)

void mpu_setDMPEnabled(char enabled) {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_DMP_EN_BIT, enabled);
}
void mpu_resetDMP() {
    writeRegBit(MPU9250_RA_USER_CTRL, MPU9250_USERCTRL_DMP_RESET_BIT, true);
}

// BANK_SEL register

void mpu_setMemoryBank(unsigned char bank) {
    bank &= 0x1F;
    writeRegister(MPU9250_RA_BANK_SEL, bank);
}

// MEM_START_ADDR register

void mpu_setMemoryStartAddress(unsigned char address) {
    writeRegister(MPU9250_RA_MEM_START_ADDR, address);
}

// MEM_R_W register

unsigned char mpu_readMemoryByte() {
    unsigned char buffer;
    readRegister(MPU9250_RA_MEM_R_W, &buffer);
    return buffer;
}
void mpu_writeMemoryByte(unsigned char output) {
    writeRegister(MPU9250_RA_MEM_R_W, output);
}
void mpu_readMemoryBlock(unsigned char *output, unsigned int dataSize, unsigned char bank, unsigned char address) {
    unsigned char chunkSize;
	unsigned int i;
	mpu_setMemoryBank(bank);
    mpu_setMemoryStartAddress(address);
    for (i = 0; i < dataSize;) {
        // determine correct chunk size according to bank position and data size
        chunkSize = MPU9250_DMP_MEMORY_CHUNK_SIZE;

        // make sure we don't go past the data size
        if (i + chunkSize > dataSize) chunkSize = dataSize - i;

        // make sure this chunk doesn't go past the bank boundary (256 bytes)
        if (chunkSize > 256 - address) chunkSize = 256 - address;

        // read the chunk of data as specified
        readRegisters(MPU9250_RA_MEM_R_W, chunkSize, output + i);
        
        // increase byte index by [chunkSize]
        i += chunkSize;

        // uint8_t automatically wraps to 0 at 256
        address += chunkSize;

        // if we aren't done, update bank (if necessary) and address
        if (i < dataSize) {
            if (address == 0) bank++;
            mpu_setMemoryBank(bank);
            mpu_setMemoryStartAddress(address);
        }
    }
}
char mpu_writeMemoryBlock(const unsigned char *output, unsigned int dataSize, unsigned char bank, unsigned char address, char verify, char useProgMem) {
    unsigned char chunkSize;
    unsigned char verifyBuffer[MPU9250_DMP_MEMORY_CHUNK_SIZE];
    unsigned char progBuffer[MPU9250_DMP_MEMORY_CHUNK_SIZE];
    unsigned int i;
    unsigned char j;
	mpu_setMemoryBank(bank);
    mpu_setMemoryStartAddress(address);
    for (i = 0; i < dataSize;) {
        // determine correct chunk size according to bank position and data size
        chunkSize = MPU9250_DMP_MEMORY_CHUNK_SIZE;

        // make sure we don't go past the data size
        if (i + chunkSize > dataSize) chunkSize = dataSize - i;

        // make sure this chunk doesn't go past the bank boundary (256 bytes)
        if (chunkSize > 256 - address) chunkSize = 256 - address;
        
        if (useProgMem) {
            // write the chunk of data as specified
            for (j = 0; j < chunkSize; j++)
                progBuffer[j] = *((unsigned char *)(output + i + j));
        } else {
            // write the chunk of data as specified
            for (j = 0; j < chunkSize; j++)
                progBuffer[j] = output[i + j];
        }

        writeRegisters(MPU9250_RA_MEM_R_W, chunkSize, progBuffer);

        // verify data if needed
        if (verify) {
            mpu_setMemoryBank(bank);
            mpu_setMemoryStartAddress(address);
            readRegisters(MPU9250_RA_MEM_R_W, chunkSize, verifyBuffer);
            if (memcmp(progBuffer, verifyBuffer, chunkSize) != 0) {
                return false; 
            }
        }

        // increase byte index by [chunkSize]
        i += chunkSize;

        // uint8_t automatically wraps to 0 at 256
        address += chunkSize;

        // if we aren't done, update bank (if necessary) and address
        if (i < dataSize) {
            if (address == 0) bank++;
            mpu_setMemoryBank(bank);
            mpu_setMemoryStartAddress(address);
        }
    }
    return true;
}
char mpu_writeProgMemoryBlock(const unsigned char *output, unsigned int dataSize, unsigned char bank, unsigned char address, char verify) {
    return mpu_writeMemoryBlock(output, dataSize, bank, address, verify, true);
}
char mpu_writeDMPConfigurationSet(const unsigned char *output, unsigned int dataSize, char useProgMem) {
    unsigned char progBuffer[8];
	unsigned char success, special;
    unsigned int i, j;
	unsigned char bank, offset, length;
    // config set data is a long string of blocks with the following structure:
    // [bank] [offset] [length] [byte[0], byte[1], ..., byte[length]]
    for (i = 0; i < dataSize;) {
        if (useProgMem) {
            bank = *((unsigned char *)(output + i++));
            offset = *((unsigned char *)(output + i++));
            length = *((unsigned char *)(output + i++));
        } else {
            bank = output[i++];
            offset = output[i++];
            length = output[i++];
        }

        // write data or perform special action
        if (length > 0) {
            // regular block of data to write
            if (useProgMem) {
                //if (sizeof(progBuffer) < length) progBuffer = (unsigned char *)realloc(progBuffer, length);
                for (j = 0; j < length; j++)
                    progBuffer[j] = *((unsigned char *)(output + i + j));
            } else {
                for (j = 0; j < length; j++)
                    progBuffer[j] = output[i + j];
            }
            success = mpu_writeMemoryBlock(progBuffer, length, bank, offset, 1, 0);
            i += length;
        } else {
            if (useProgMem) {
                special = *((unsigned char *)(output + i++));
            } else {
                special = output[i++];
            }
            if (special == 0x01) {
                writeRegister(MPU9250_RA_INT_ENABLE, 0x32);  // single operation
                success = true;
            } else {
                // unknown special command
                success = false;
            }
        }       
        if (!success) {
            return false; 
        }
    }
    return true;
}
char mpu_writeProgDMPConfigurationSet(const unsigned char *output, unsigned int dataSize) {
    return mpu_writeDMPConfigurationSet(output, dataSize, true);
}

// DMP_CFG_1 register

unsigned char mpu_getDMPConfig1() {
    unsigned char buffer;
    readRegister(MPU9250_RA_DMP_CFG_1, &buffer);
    return buffer;
}
void mpu_setDMPConfig1(unsigned char config) {
    writeRegister(MPU9250_RA_DMP_CFG_1, config);
}

// DMP_CFG_2 register

unsigned char mpu_getDMPConfig2() {
    unsigned char buffer;
    readRegister(MPU9250_RA_DMP_CFG_2, &buffer);
    return buffer;
}
void mpu_setDMPConfig2(unsigned char config) {
    writeRegister(MPU9250_RA_DMP_CFG_2, config);
}

