/*
 * SensorStructure.h
 *
 *  Created on: Nov 8, 2017
 *      Author: dvthan
 */

#ifndef SENSORSTRUCTURE_H_
#define SENSORSTRUCTURE_H_

typedef struct
{
  //uint8_t  useOrByPass;
  //uint16_t CMDCount;
  //uint8_t  wInterface;
  //uint8_t  address;
  //uint16_t writeCount;
  //uint16_t readCount;
  //uint8_t  writeBuffer[16];
    uint8_t  writeBuffer[240];
} UartReceive_t;

typedef struct{
    //uint16_t CMDCount;
    //uint16_t BufferLength;
    uint8_t  TxBuffer[240];
} sensorTx_t;

typedef struct{
    //uint16_t CMDCount;
    //uint8_t  wInterface;
    //uint8_t  address;
    //uint16_t writeCount;
    //uint16_t readCount;
    //uint8_t  writeBuffer[16];
    uint8_t  writeBuffer[240];
} sensorRx_t;

typedef struct{
    uint32_t Counter;
    int16_t accX;
    int16_t accY;
    int16_t accZ;
    int16_t accTemp;
    uint32_t AverageLight;
    uint16_t CO2val;
    uint16_t Tvocval;
    uint32_t PressureVal;
    int32_t  TempratureVal;
    uint32_t HumidityVal;
} sensor_t;


#endif /* SENSORSTRUCTURE_H_ */
