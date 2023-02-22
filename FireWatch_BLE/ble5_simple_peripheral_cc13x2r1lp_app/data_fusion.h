#ifndef DATA_FUSION_H_
#define DATA_FUSION_H_

#define G_earth    9.8f
#define max_speed  0.6f

void Kalman_predict(float *p, float *pos, float *spd, float *a, unsigned long t_ms);

void Kalman_update(float *p, float *pos, float *spd, float *pos_ble);

void Kalman_calibration(float *p, float *spd, float *a, unsigned long t_ms);


#endif /* DATA_FUSION_H_ */
