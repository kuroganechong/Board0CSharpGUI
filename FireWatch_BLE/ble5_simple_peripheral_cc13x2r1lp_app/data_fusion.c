#include "data_fusion.h"
#include "math.h"

/*
 * p_matrix = [ p0   0  p2   0,
 *               0  p0   0  p2,
 *              p2   0  p1   0,
 *               0  p2   0  p1 ]
 */
float var_ble = 4.0f; // 2m
float var_acc = 0.01f;

void Kalman_predict(float *p, float *pos, float *spd, float *a, unsigned long t_ms)
{
	float pa, pb, pc;
	float qa, qb, qc;
	float va, vb, vratio;
	if (t_ms > 25)
        t_ms = 10;
	float t = (float)(t_ms) / 1000;
	a[0] = a[0] * G_earth;
	a[1] = a[1] * G_earth;
	va = spd[0];
	vb = spd[1];
	spd[0] = spd[0] + t * a[0];
	spd[1] = spd[1] + t * a[1];
	vratio = sqrt(spd[0] * spd[0] + spd[1] * spd[1]) / max_speed;
	if (vratio > 1) // walking velocity cannot be larger than max velocity
	{
	    spd[0] = spd[0] / vratio;
	    spd[1] = spd[1] / vratio;
	}
	va = (va + spd[0]) / 2;
	vb = (vb + spd[1]) / 2;
	pos[0] = pos[0] + t * va + 0.5f * t * t * a[0];
	pos[1] = pos[1] + t * vb + 0.5f * t * t * a[1];

	qa = 0.25f * t * t * t * t * var_acc;
	qb = t * t * var_acc;
	qc = 0.5f *t * t * t * var_acc;
	pa = p[0] + 2 * p[2] * t + p[1] * t * t + qa;
	pb = p[1] + qb;
	pc = p[2] + p[1] * t + qc;
	p[0] = pa;
	p[1] = pb;
	p[2] = pc;
}

void Kalman_update(float *p, float *pos, float *spd, float *pos_ble)
{
	float pa, pb, pc, temp;
	temp = p[0] + var_ble;

	pos[0] = pos[0] + p[0] * (pos_ble[0] - pos[0]) / temp;
	pos[1] = pos[1] + p[0] * (pos_ble[1] - pos[1]) / temp;
	if (spd[0] * spd[0] + spd[1] * spd[1] > 0.01f) // speed larger than 0.1m/s
	{
		spd[0] = spd[0] + p[2] * (pos_ble[0] - pos[0]) / temp;
		spd[1] = spd[1] + p[2] * (pos_ble[1] - pos[1]) / temp;
	}
	pa = (p[0] * var_ble) / temp;
	pb = p[1] - (p[2] * p[2]) / temp;
	pc = (p[2] * var_ble) / temp;
	p[0] = pa;
	p[1] = pb;
	p[2] = pc;

}

void Kalman_calibration(float *p, float *spd, float *a, unsigned long t_ms)
{
    float pa, pb, pc;
    float qa, qb, qc;
    if (t_ms > 25)
        t_ms = 10;
    float t = (float)(t_ms) / 1000;

    spd[0] = 0;
    spd[1] = 0;
    a[0] = 0;
    a[1] = 0;

    qa = 0.25f * t * t * t * t * var_acc;
    qb = t * t * var_acc;
    qc = 0.5f *t * t * t * var_acc;
    pa = p[0] + 2 * p[2] * t + p[1] * t * t + qa;
    pb = p[1] + qb;
    pc = p[2] + p[1] * t + qc;
    p[0] = pa;
    p[1] = 0.01;
    p[2] = pc * sqrt(0.01 / pb);
}

