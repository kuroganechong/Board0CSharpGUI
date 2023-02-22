/*
 * DACDriver.h
 *
 *  Created on: Aug 7, 2018
 *      Author: dvthan
 */

#ifndef DACDRIVER_H_
#define DACDRIVER_H_

#define SPIDAC MSP_EXP432P4011_SPIA0

void DAC_Init(void);
void DAC_Set_Value(uint8_t channel, uint16_t value);
void DAC_Set_Floating(uint8_t channel);
void DAC_Set_Floating_All(void);
void DAC_Set_Output(uint8_t channel);
void DAC_Set_Broadcast(uint16_t value);


#endif /* DACDRIVER_H_ */
