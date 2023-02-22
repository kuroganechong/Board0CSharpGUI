#include "IMU_driver.h"

void readRegister (unsigned char thisRegister, unsigned char *result)
{
    Sensors_I2C_ReadRegister(addr, thisRegister, 1, result);
}

void readRegBit(unsigned char thisRegister, unsigned char bitNum, unsigned char *result) 
{
  readRegister(thisRegister, result);
  *result = (*result >> bitNum) & 0x01;
}

void readRegBits(unsigned char thisRegister, unsigned char bitStart, unsigned char length, unsigned char *result) 
{
  unsigned char mask;
  readRegister(thisRegister, result);
  mask = ((0x01 << length) - 1);
  *result >>= (bitStart - length + 1);
  *result = *result & mask;
}

void readRegisters(unsigned char thisRegister, unsigned char BytesToRead, unsigned char *result) 
{
  Sensors_I2C_ReadRegister(addr, thisRegister, BytesToRead, result);
}

void writeRegister(unsigned char thisRegister, unsigned char thisValue)
{
  Sensors_I2C_WriteRegister(addr, thisRegister, 1, &thisValue);
}

void writeRegBit(unsigned char thisRegister, unsigned char bitNum, char thisValue)
{
  unsigned char result;
  readRegister(thisRegister, &result);
  result = (thisValue != 0) ? (result | (0x01 << bitNum)) : (result & (~(0x01 << bitNum)));
  writeRegister(thisRegister, result);
}

void writeRegBits(unsigned char thisRegister, unsigned char bitStart, unsigned char length, unsigned char thisValue) 
{
  unsigned char mask;
  unsigned char result;
  readRegister(thisRegister, &result);
  mask = ((0x01 << length) - 0x01) << (bitStart - length + 1);
  thisValue <<= (bitStart - length + 1); // shift data into correct position
  thisValue &= mask; // zero all non-important bits in data
  result &= ~(mask); // zero all important bits in existing uint8_t
  result |= thisValue; // combine data with existing uint8_t
  writeRegister(thisRegister, result);
}

void writeRegWord(unsigned char thisRegister, unsigned short int thisValue) 
{
  unsigned char temp[2];
  temp[0] = (unsigned char)(thisValue >> 8);
  temp[1] = (unsigned char)(thisValue);
  Sensors_I2C_WriteRegister(addr, thisRegister, 2, temp);
}

void writeRegisters(unsigned char thisRegister, unsigned char BytesToWrite, unsigned char *thisValue) 
{
  Sensors_I2C_WriteRegister(addr, thisRegister, BytesToWrite, thisValue);
}
