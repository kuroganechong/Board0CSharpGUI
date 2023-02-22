#include "data_fusion.h"
#include "math.h"

/*
 * p_matrix = [ p0   0  p2   0,
 *               0  p0   0  p2,
 *              p2   0  p1   0,
 *               0  p2   0  p1 ]
 */
//TODO: check var_acc before use
void Kalman_predict(float *p, float *pos, float *spd, float *a, unsigned long t_ms)
{
	float pa, pb, pc;
	//float qa, qb, qc;
	float va, vb, vtotal;
	float postemp;
	if (t_ms > 25)
        t_ms = 10;
	float t = (float)(t_ms) / 1000;
	//a[0] = a[0] * G_earth;
	//a[1] = a[1] * G_earth;
	//va = spd[0];
	//vb = spd[1];
	//spd[0] = spd[0] + t * a[0];
	//spd[1] = spd[1] + t * a[1];
	//vtotal = sqrt(spd[0] * spd[0] + spd[1] * spd[1]);
	/*if (vtotal > max_speed) // walking velocity cannot be larger than max velocity
	{
	    spd[0] = spd[0] * max_speed / vtotal;
	    spd[1] = spd[1] * max_speed / vtotal;
	}*/
	//va = (va + spd[0]) / 2;
	//vb = (vb + spd[1]) / 2;
	va = spd[0];
	vb = spd[1];
	postemp = pos[0];
	postemp += t*va;
	pos[0] = postemp;
    postemp = pos[1];
    postemp += t*va;
    pos[1] = postemp;
	//pos[0] = pos[0] + t * va ;
	//pos[1] = pos[1] + t * vb;
	//LiYao version
	/*
	qa = 0.25f * t * t * t * t * var_acc;
	qb = t * t * var_acc;
	qc = 0.5f *t * t * t * var_acc;
	pa = p[0] + 2 * p[2] * t + p[1] * t * t + qa;
	pb = p[1] + qb;
	pc = p[2] + p[1] * t + qc;*/

	//Long version - only take p[0]
	pa = p[0] + t * t * var_acc;
	pb = 0;
	pc = 0;
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
	//LiYao's version
	/*
	if (spd[0] * spd[0] + spd[1] * spd[1] > 0.01f) // speed larger than 0.1m/s
	{
		spd[0] = spd[0] + p[2] * (pos_ble[0] - pos[0]) / temp;
		spd[1] = spd[1] + p[2] * (pos_ble[1] - pos[1]) / temp;
	}
	pa = (p[0] * var_ble) / temp;
	pb = p[1] - (p[2] * p[2]) / temp;
	pc = (p[2] * var_ble) / temp;*/

	//Long's version - only take p[0]
	pa = (p[0] * var_ble) / temp;
	pb = 0;
	pc = 0;
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

void Lagrange_interpolation(int *xin, float *yin, float *yout) //for 4 data points only - skip coz so many error here
{
    int i, j, k;
    float num = 1.0, de = 1.0;
    double temp;
    for(k = 0; k < 50; k++)
    {

        if(k == xin[0])
            yout[k] = yin[0];
        else if (k == xin[1])
            yout[k] = yin[1];
        else if (k == xin[2])
            yout[k] = yin[2];
        else if (k == xin[3])
            yout[k] = yin[3];
        else if (k == xin[4])
            yout[k] = yin[4];
        else
        {
            yout[k] = 0.0;
            temp = 0.0;
            for(i = 0; i < 5; i ++)
            {
                for(j = 0; j < 5; j ++)
                {
                    if(j != i)
                    {
                        num *= (k - xin[j]);
                        de *= (xin[i] - xin[j]);
                    }
                }
                temp += num * yin[i] / de;
                if(temp < float_thres)
                    temp = 0;
                yout[k] += (float)temp;
                num = 1.0;
                de = 1.0;
            }
        }

    }
}
void envelope_integration(float *accel, float *pos, float *v)
{
    float prevspd, t, postemp, vtemp;
    vtemp = 0;
    prevspd = vtemp;
    postemp = *pos;
    int i;
    t = 0.01;
    for(i = 0; i < 49; i++)
    {

        vtemp += 0.5 * (accel[i] + accel[i + 1]) * t;
        if (fabs(vtemp) > max_speed)
        {
            if(vtemp > 0)
                vtemp = max_speed;
            else
                vtemp = - max_speed;
        }
        postemp += 0.5 * (prevspd + vtemp) * t;
        prevspd = vtemp;
    }
    *pos += postemp;
    *v = vtemp;
}
//Input array size 50, output value maximum at each 10-value interval and their position
void find_max(float *accel, int *maxpos, float *maxvalue)
{
    int i, index, tempp;
    float tempv;
    for(i = 0; i < 5; i++)
    {
        tempp = 10 * i;
        index = 0;
        tempv = accel[10 * i];
        for(index = 0; index < 10; index ++)
        {
            if(accel[10 * i + index] > tempv)
            {
                tempv = accel[10 * i + index];
                tempp = 10 * i + index;
            }
        }
        maxvalue[i] = tempv;
        maxpos[i] = tempp;
    }

}

void find_min(float *accel, int *minpos, float *minvalue)
{
    int i, index, tempp;
    float tempv;
    for(i = 0; i < 5; i++)
    {
        tempp = 10 * i;
        index = 0;
        tempv = accel[10 * i];
        for(index = 0; index < 10; index ++)
        {
            if(accel[10 * i + index] < tempv)
            {
                tempv = accel[10 * i + index];
                tempp = 10 * i + index;
            }
        }
        minvalue[i] = tempv;
        minpos[i] = tempp;
    }

}
void bulk_integration(float *accelmax, float *accelmin, int *posmax, int *posmin, int sizeofaccel, float *pos, float *v)
{
    double tempvmax, prevvmax, tempvmin, prevvmin, temppmax, temppmin;
    float t = 0.01; //( 0.01ms)

    int i;
    tempvmax = 0.0f;
    prevvmax = 0.0f;
    tempvmin = 0.0f;
    prevvmin = 0.0f;
    temppmax = 0.0f;
    temppmin = 0.0f;
    //First segment
    tempvmax += 0.5 * accelmax[0] * t * posmax[0];
    if (fabs(tempvmax) > max_speed)
    {
        if(tempvmax > 0)
            tempvmax = max_speed;
        else
            tempvmax = - max_speed;
    }

    temppmax += 0.5 * (tempvmax + prevvmax) * t * posmax[0];
    prevvmax = tempvmax;

    tempvmin += 0.5 * accelmin[0] * t * posmin[0];
    if (fabs(tempvmin) > max_speed)
    {
        if(tempvmin > 0)
            tempvmin = max_speed;
        else
            tempvmin = - max_speed;
    }
    temppmin += 0.5 * (tempvmin + prevvmin) * t * (posmin[0]);
    prevvmin = tempvmin;
    //Middle segments
    for(i = 0; i < (sizeofaccel - 1); i++ )
    {
        tempvmax += 0.5 * (accelmax[i] + accelmax[i+1]) * t * (posmax[i+1] - posmax[i]);
        if (fabs(tempvmax) > max_speed)
        {
            if(tempvmax > 0)
                tempvmax = max_speed;
            else
                tempvmax = - max_speed;
        }
        temppmax += 0.5 * (tempvmax + prevvmax) * t * (posmax[i+1] - posmax[i]);
        prevvmax = tempvmax;

        tempvmin += 0.5 * (accelmin[i] + accelmin[i+1]) * t * (posmin[i+1] - posmin[i]);
        if (fabs(tempvmin) > max_speed)
        {
            if(tempvmin > 0)
                tempvmin = max_speed;
            else
                tempvmin = - max_speed;
        }
        temppmin += 0.5 * (tempvmin + prevvmin) * t * (posmin[i+1] - posmin[i]);
        prevvmin = tempvmin;
    }
    //Last segment
    tempvmax += 0.5 * accelmax[sizeofaccel - 1] * t * (49 - posmax[sizeofaccel - 1]);
    if (fabs(tempvmax) > max_speed)
    {
        if(tempvmax > 0)
            tempvmax = max_speed;
        else
            tempvmax = - max_speed;
    }
    temppmax += 0.5 * (tempvmax + prevvmax) * t;
    prevvmax = tempvmax;

    tempvmin += 0.5 * accelmin[sizeofaccel - 1] * t * (49 - posmin[sizeofaccel - 1]);
    if (fabs(tempvmin) > max_speed)
    {
        if(tempvmin > 0)
            tempvmin = max_speed;
        else
            tempvmin = - max_speed;
    }
    temppmin += 0.5 * (tempvmin + prevvmin) * t;
    prevvmin = tempvmin;

    *pos += (float)((temppmax + temppmin) * 0.5);
    *v += (float)((tempvmax + tempvmin) * 0.5);

}
float fir_filtering(float *accin)
{
    // Order 20
    //const double coefficient[21] = {-6.21115458751030e-19, -0.00212227114882539, -0.00632535399151418, -0.0116118103776210, -0.0123546567489824,
    //                                4.19252934656945e-18, 0.0317744975585673, 0.0814359075642177, 0.137493781701943, 0.182125490388735, 0.199168830106960,
    //                                0.182125490388735, 0.137493781701943, 0.0814359075642177, 0.0317744975585673, 4.19252934656945e-18,
    //                                -0.0123546567489824, -0.0116118103776210, -0.00632535399151418, -0.00212227114882539, -6.21115458751030e-19};

    // Order 50
    const double coefficient[33] = { -0.00152884475502033,   -0.00190413765156085,    -0.00251201020053917,    -0.00315172285923541,
                                     -0.00338157483002662,   -0.00256899869677061,    1.43303986898520e-18,     0.00497037076557457,
                                     0.0127558532986817,      0.0233996310513060,     0.0364901801525690,       0.0511553725692717,
                                     0.0661431077396454,      0.0799794721992498,     0.0911792726013163,       0.0984722196424889,
                                     0.101003617946099,       0.0984722196424889,     0.0911792726013163,       0.0799794721992498,
                                     0.0661431077396454,      0.0511553725692717,     0.0364901801525690,       0.0233996310513060,
                                     0.0127558532986817,      0.00497037076557457,    1.43303986898520e-18,    -0.00256899869677061,
                                     -0.00338157483002662,    -0.00315172285923541,    -0.00251201020053917,    -0.00190413765156085,    -0.00152884475502033};
    double temp;
    int count;
    for(count = 0; count <33; count ++)
    {
        temp += coefficient[count] * accin[count];

    }
    temp = (float) temp;
    return temp;
}
void double_integration(float *pmatrix, float *accel, float *speed, float *pos)
{
    float a, v, p, vold, t;
    float qa, qb, qc, pa, pb, pc;
    t = 0.01;//modify it with time stamp
    //a = *accel * G_earth;
    a = *accel;
    vold = *speed;
    p = *pos;
    if(fabs(vold) > max_speed)
    {
        if(vold > 0)
            vold = max_speed;
        else
            vold = - max_speed;
    }
    //if(fabs(a) > 0.05)//Baseline screening
    //{

        v = vold + a * t;
        p += 0.5 * a * t * t + vold * t;
    //}
    qa = 0.25f * t * t * t * t * var_acc;
    qb = t * t * var_acc;
    qc = 0.5f *t * t * t * var_acc;
    pa = pmatrix[0] + 2 * pmatrix[2] * t + pmatrix[1] * t * t + qa;
    pb = pmatrix[1] + qb;
    pc = pmatrix[2] + pmatrix[1] * t + qc;
    pmatrix[0] = pa;
    pmatrix[1] = pb;
    pmatrix[2] = pc;
    *speed = v;
    *pos = p;
}

void single_integration (float *p, float *spd, float *pos)
{
    float vX, vY, vZ, pX, pY, pZ;
    float pa, pb, pc;
    float t = 0.01;
    vX = spd[0];
    vY = spd[1];
    vZ = spd[2];
    pX = pos[0];
    pY = pos[1];
    pZ = pos[2];
    pos[0] = pX + vX * t;
    pos[1] = pY + vY * t;
    pos[2] = pZ + vZ * t;
    //pos[0] = pos[0] + vX * t;
    //pos[1] = pos[1] + vY * t;

    pa = p[0] + t * t * var_acc;
    pb = 0;
    pc = 0;
    p[0] = pa;
    p[1] = pb;
    p[2] = pc;
}
float iir_filtering(float* accin, float *accout)
{
    //butterworth filter with cutoff f = 5 Hz
    const double b[5] = {0.0000312, 0.0001250, 0.0001874, 0.0001250, 0.0000312};
    const double a[5] = {1.0, -3.5897, 4.8513, -2.9241, 0.6630};

    //butterworth band pass filter with band pass 0.2Hz to 5Hz
    //const double b[5] = {0.0051, 0, -0.0103, 0, 0.0051};
    //const double a[5] = {1.0000, -3.7856,  5.3793, -3.4016, 0.8079};

    //butterworth band pass filter with order 4, band pass 0.25Hz to 5Hz
    //const double b[9] = {0.0000267, 0, -0.0001069, 0, 0.0001604, 0, -0.0001069, 0, 0.0000267};
    //const double a[9] = {1.0000,   -7.6024,   25.2972,  -48.1237,   57.2447,  -43.6019,   20.7669,   -5.6549,    0.6740};

    double result = 0.0;
    result = accin[0] * b[0] + accin[1] * b[1] + accin[2] * b[2] + accin[3] * b[3] + accin[4] * b[4];
    result = result - accout[0] * a[1] - accout[1] * a[2] - accout[2] * a[3] - accout[3] * a[4];

    return (float)result;

}
