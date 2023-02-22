/*
 * Ambient_sensor.h
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */

#ifndef AMBIENT_SENSOR_H_
#define AMBIENT_SENSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/I2C.h>
#include "Board.h"

/////////////////////////////////////////////////////////
// temperature correction due to self heating
#define TEMPATURESELFHEATING     4.5 // deg C
/////////////////////////////////////////////////////////

#define BME280
#define I2CAMBIENT    MSP_EXP432P4011_I2CB0
#define BME280_ADDRESS  (0x77)

#define CONFIG_REG      0xF5
#define CTRL_MEASURE    0xF4
#define CTRL_HUM        0xF2
#define STATUS_REG      0xF3
#define DATAOUT_OFFSET  0xF7
#define CALIBDATA0      0x88
#define CALIBDATA1      0xE1
#define CHIP_ID         0xD0
#define RESET_REG       0xE0

#define CCS811_STATUS_REG   0x00
#define MEAS_MODE_REG       0x01
#define ALG_RESULT_DATA     0x02
#define ENV_DATA            0x05
#define NTC_REG             0x06
#define THRESHOLDS          0x10
#define BASELINE            0x11
#define HW_ID_REG           0x20
#define ERROR_ID_REG        0xE0
#define APP_START_REG       0xF4
#define SW_RESET            0xFF
#define CCS_811_ADDRESS     0x5B
#define GPIO_WAKE           0x5
#define DRIVE_MODE_IDLE     0x0
#define DRIVE_MODE_1SEC     0x10
#define DRIVE_MODE_10SEC    0x20
#define DRIVE_MODE_60SEC    0x30
#define INTERRUPT_DRIVEN    0x8
#define THRESHOLDS_ENABLED  0x4


bool BME280_Init(void);
void BME280_read(float * Temperature, float *Humidity, float *Airpressure,  uint32_t *u32Pressure);
void BME280_GetCalib_Data(void);
bool I2CAmbientInit(void);
bool CCS811_Init(void);
uint8_t CCS811_Read(uint16_t *CO2val, uint16_t *TVOCval);
void CCS811_TemperatureUpdate(float Temperature, float Humidity);
void CCS811_Sleep(void);
void CCS811_Wake(void);
void CCS811_SW_Reset(void);
void CCS811_HW_nRESET(void);
void CCS811_Baseline_Read(uint8_t * buff);
void CCS811_Baseline_Write(uint8_t * buff);



#endif /* AMBIENT_SENSOR_H_ */
