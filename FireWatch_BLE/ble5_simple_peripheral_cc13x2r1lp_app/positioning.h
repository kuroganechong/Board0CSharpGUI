#ifndef _POSITIONING_H_
#define _POSITIONING_H_

#define A 210 // -46dB
#define n 1.99f // delta/[10*lg(2)]
#define height 0.1f

typedef struct {
	float x;
	float y;
} point_t;

typedef struct {
	point_t center;
	float r;
} circle_t;

char RSSI_compensation(unsigned char id, point_t pcb, point_t beacon, float yaw);

float distance_cal(point_t a, point_t b);

float RSSI2radius(unsigned char rssi);

unsigned char radius2RSSI(point_t pcb, point_t beacon);

void get_position(circle_t *circle, point_t *point);

void weighted_position_4beacons(circle_t *circle, point_t last_pos, point_t *point);

#endif  /* #ifndef _POSITIONING_H_ */
