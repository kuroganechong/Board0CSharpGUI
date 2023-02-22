/* LevyWalkTask.h
Author: Huu Duoc
Date: Jan-16-19
 */

#ifndef LEVYWALKTASK_H_
#define LEVYWALKTASK_H_


#define L_PI 3.14159265358979f

void LevyWalkTaskCreation(void);
float LevyWalk_ForwardVelocityCalculation(void);
float LevyWalk_ForwardVelocityCalculation_Sign(void);
float LevyWalk_AngularVelocityCalculation(void);
float LevyWalk_AngularVelocityCalculation_Sign(void);
float LevyWalk_AngularVelocityCalculation_Version2(void);
void  LevyWalk_AllSpeedCalculation(void);

#endif /* LEVYWALKTASK_H_ */
