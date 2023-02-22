/*
 * IMU_driver.h
 *
 *  Created on: Mar 9, 2018
 *      Author: liyao
 */

#ifndef IMU_DRIVER_H_
#define IMU_DRIVER_H_

#define addr 0x68
#include <ti/drivers/I2C.h>
////////////////////////////////////////////////////////////////////////////////////////

void readRegister (unsigned char thisRegister, unsigned char *result);

void readRegBit(unsigned char thisRegister, unsigned char bitNum, unsigned char *result);

void readRegBits(unsigned char thisRegister, unsigned char bitStart, unsigned char length, unsigned char *result);

void readRegisters(unsigned char thisRegister, unsigned char BytesToRead, unsigned char *result);

void writeRegister(unsigned char thisRegister, unsigned char thisValue);

void writeRegBit(unsigned char thisRegister, unsigned char bitNum, char thisValue);

void writeRegBits(unsigned char thisRegister, unsigned char bitStart, unsigned char length, unsigned char thisValue);

void writeRegWord(unsigned char thisRegister, unsigned short int thisValue);

void writeRegisters(unsigned char thisRegister, unsigned char BytesToWrite, unsigned char *thisValue);

// prototype
void delay_ms(unsigned long num_ms);

int i2ctransaction_IMU(I2C_Transaction *msg);

int Sensors_I2C_ReadRegister(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, unsigned char *RegisterValue);

int Sensors_I2C_WriteRegister(unsigned char Address, unsigned char RegisterAddr, unsigned short RegisterLen, const unsigned char *RegisterValue);

////////////////////////////////////////////////////////////////////////////////////////


#endif /* IMU_DRIVER_H_ */
