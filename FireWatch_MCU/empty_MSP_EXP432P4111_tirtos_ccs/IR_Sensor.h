/*
 * IR_Sensor.h
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ti/drivers/I2C.h>

#include "Board.h"

#define I2CIR    MSP_EXP432P4011_I2CB3

#define HTPA32x32d_ARRAY_ADDRESS                (0x1A)
#define HTPA32x32d_EEROM_ADDRESS                (0x50)
#define ARRAY_ROW_SIZE                          32
#define HTPA32x32d_PIXEL_ARRAY_ROW_SIZE           32
#define HTPA32x32d_PIXEL_ARRAY_COLUMN_SIZE        32
#define HTPA32x32d_PIXEL_TEMP_CONVERSION          0.1f
#define IR_ARRAY_SIZE                             1024
#define HALFSIZE                                  512
// Register command
#define EEPROM_ACTIVE   (0x01)
#define EEPROM_STANDBY  (0x00)
#define SET_ADDR        (0x09)
#define NORMAL_READ     (0x06)
#define GET_DATA        (0x0B)

#define CONFIG_REG      (0X01)
#define STATUS_REG      (0x02)
#define TRIM_REG1       (0x03)
#define TRIM_REG2       (0x04)
#define TRIM_REG3       (0x05)
#define TRIM_REG4       (0x06)
#define TRIM_REG5       (0x07)
#define TRIM_REG6       (0x08)
#define TRIM_REG7       (0x09)

#define READ_DATA_TOP   (0x0A)
#define READ_DATA_BOT   (0x0B)


#define ARRAY_WAKEUP    (0x01)
#define MBIT_TRIM       (0x2C)
#define BIAS_TRIML      (0x05)
#define BIAS_TRIMR      (0x05)
#define CLK_TRIM        (0x15)
#define BPA_TRIML       (0x0C)
#define BPA_TRIMR       (0x0C)
#define PU_TRIM         (0x88)


#define START_BLOCK0    (0x09)
#define START_BLOCK1    (0x19)
#define START_BLOCK2    (0x29)
#define START_BLOCK3    (0x39)

#define START_OFFSET    (0x0F)
#define ARRAY_SLEEP     (0x00)

//////////////////////////////////////////////////////////////////
bool I2CIRinit();
void IR_Sensor_Init(void);
void IR_Sensor_ReadPixel(float * buf);
void IR_Sensor_read_Ambient_Temp(float * Temperature);




#endif /* IR_SENSOR_H_ */
