#ifndef DATA_FUSION_H_
#define DATA_FUSION_H_

#define var_ble    4.0f // 2m
#define var_acc    0.01f
#define G_earth    9.77587f
#define max_speed  3.5f
#define float_thres 0.000001
#define tau 0.00001
#define deg2rad  0.01745329f

void Kalman_predict(float *p, float *pos, float *spd, float *a, unsigned long t_ms);

void Kalman_update(float *p, float *pos, float *spd, float *pos_ble);

void Kalman_calibration(float *p, float *spd, float *a, unsigned long t_ms);

void Lagrange_interpolation(int *xin, float *yin, float *yout);

void envelope_integration(float *accel, float *pos, float *v);

void find_max(float *accel, int *maxpos, float *maxvalue);

void find_min(float *accel, int *minpos, float *minvalue);

void bulk_integration(float *accelmax, float *accelmin, int *posmax, int *posmin, int sizeofaccel, float *pos, float *v);

float fir_filtering(float *accin);

void double_integration(float *pmatrix, float *accel, float *speed, float *pos);

void single_integration (float *pmatrix, float *speed, float *pos);

float iir_filtering(float* accin, float *accout);

#endif /* DATA_FUSION_H_ */
