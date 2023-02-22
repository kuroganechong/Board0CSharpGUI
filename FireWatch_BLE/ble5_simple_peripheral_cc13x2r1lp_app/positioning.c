#include <math.h>
#include "positioning.h"

#define PI 3.1416f


char RSSI_compensation(unsigned char id, point_t pcb, point_t beacon, float yaw) // linear compensation
{

    char ret = 0;
    float temp;
    float ang_rad; // must be in [-3.14, 3.14]
    if (id <= 6 && id > 0)
    {
        temp = atan2((beacon.y - pcb.y), (beacon.x - pcb.x)) - 0.5f * PI;
        ang_rad = temp - yaw; // angle start from (pcb-yaw direction) to (pcb-beacon vector direction)

        ang_rad -= 0.4f * PI;
        ang_rad += PI;
        while (ang_rad > PI)
            ang_rad -= 2 * PI;
        while (ang_rad < -PI)
            ang_rad += 2 * PI;
        temp = 0.6f * fabsf(ang_rad);
        ret = (char)(temp + 0.5f);
    }
    return ret;
}

float distance_cal(point_t a, point_t b)
{

    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

float RSSI2radius(unsigned char rssi)
{

    float rawDistance;
    float temp;

    temp = (A - rssi) / (10 * n);
    rawDistance = pow(10, temp);

    if (rawDistance < height)
        return 0.1f;

    return sqrt(pow(rawDistance, 2) - pow(height, 2));
}

unsigned char radius2RSSI(point_t pcb, point_t beacon)
{
    float dist = distance_cal(pcb, beacon);
    dist = sqrt(pow(dist, 2) + pow(height, 2));
    float temp = log10(dist);
    temp = 10 * n * temp;
    unsigned char ret = A - (unsigned char)temp;
    return ret;
}

point_t intersection(circle_t c1, circle_t c2, circle_t c_ref)
{

    if (c1.r < c2.r)
    {
        circle_t c = c1;
        c1 = c2;
        c2 = c;
    }

    float d = distance_cal(c1.center, c2.center); // distance between two centers

    point_t coor;

    // separate or tangent	
    if (d >= c1.r + c2.r || d <= c1.r - c2.r)
    {
        if (d >= c1.r + c2.r)
        {
            coor.x = c1.center.x
                    + (c2.center.x - c1.center.x) * c1.r / (c1.r + c2.r);
            coor.y = c1.center.y
                    + (c2.center.y - c1.center.y) * c1.r / (c1.r + c2.r);
        }
        else
        {
            coor.x = c1.center.x
                    + (c2.center.x - c1.center.x) * c1.r * (d + 2 * c2.r)
                            / (c1.r + c2.r) / d;
            coor.y = c1.center.y
                    + (c2.center.y - c1.center.y) * c1.r * (d + 2 * c2.r)
                            / (c1.r + c2.r) / d;
        }
    }
    // intersectant
    else if (c1.center.y == c2.center.y)
    {
        float a = ((c1.r * c1.r - c2.r * c2.r)
                - (c1.center.x * c1.center.x - c2.center.x * c2.center.x))
                / (2 * c2.center.x - 2 * c1.center.x);
        float t = sqrt(c1.r * c1.r - (a - c1.center.x) * (a - c1.center.x));
        coor.x = a;
        coor.y = c1.center.y + t;
        d = fabsf(distance_cal(coor, c_ref.center) - c_ref.r);
        coor.y = c1.center.y - t;
        if (d < fabsf(distance_cal(coor, c_ref.center) - c_ref.r))
            coor.y = c1.center.y + t;
    }
    else if (c1.center.y != c2.center.y)
    {
        float k, res;
        k = (c1.center.x - c2.center.x) / (c2.center.y - c1.center.y);
        res = ((c1.r * c1.r - c2.r * c2.r)
                - (c1.center.x * c1.center.x - c2.center.x * c2.center.x)
                - (c1.center.y * c1.center.y - c2.center.y * c2.center.y))
                / (c2.center.y - c1.center.y) / 2;
        float a, b, c;
        a = (k * k + 1);
        b = 2 * ((res - c1.center.y) * k - c1.center.x);
        c = (res - c1.center.y) * (res - c1.center.y) - c1.r * c1.r
                + c1.center.x * c1.center.x;
        c = sqrt(b * b - 4 * a * c);
        coor.x = (-b + c) / (2 * a);
        coor.y = k * coor.x + res;
        d = fabsf(distance_cal(coor, c_ref.center) - c_ref.r);
        coor.x = (-b - c) / (2 * a);
        coor.y = k * coor.x + res;
        if (d < fabsf(distance_cal(coor, c_ref.center) - c_ref.r))
        {
            coor.x = (-b + c) / (2 * a);
            coor.y = k * coor.x + res;
        }
    }
    return coor;
}

void get_position(circle_t *circle, point_t *point)
{

    /*c1,c2*/
    point_t p12 = intersection(circle[0], circle[1], circle[2]);
    float weight12 = 1.0f / circle[0].r + 1.0f / circle[1].r;

    /*c1,c3*/
    point_t p13 = intersection(circle[0], circle[2], circle[1]);
    float weight13 = 1.0f / circle[0].r + 1.0f / circle[2].r;

    /*c2,c3*/
    point_t p23 = intersection(circle[1], circle[2], circle[0]);
    float weight23 = 1.0f / circle[1].r + 1.0f / circle[2].r;

    point->x = (p12.x * weight12 + p13.x * weight13 + p23.x * weight23)
            / (weight12 + weight13 + weight23);
    point->y = (p12.y * weight12 + p13.y * weight13 + p23.y * weight23)
            / (weight12 + weight13 + weight23);
}

void weighted_position_4beacons(circle_t *circle, point_t last_pos, point_t *point)
{
    point_t point_tmp, pointCal;
    float p_weight[4], temp;
    circle_t circle_tmp[3];

    circle_tmp[0] = circle[0];
    circle_tmp[1] = circle[1];
    circle_tmp[2] = circle[2];
    //circle_tmp[0].r = RSSI2radius(beaconList[0][1]);
    //circle_tmp[1].center = station[beaconList[1][0]];
    //circle_tmp[1].r = RSSI2radius(beaconList[1][1]);
    //circle_tmp[2].center = station[beaconList[2][0]];
    //circle_tmp[2].r = RSSI2radius(beaconList[2][1]);
    get_position(circle_tmp, &point_tmp);
    temp = distance_cal(point_tmp, last_pos);
    if (temp < 0.5f)
        temp = 0.5;
    p_weight[0] = 1.0f / pow(temp, 2);
    pointCal.x = point_tmp.x * p_weight[0];
    pointCal.y = point_tmp.y * p_weight[0];

    circle_tmp[0] = circle[3];
    //circle_tmp[0].center = station[beaconList[3][0]];
    //circle_tmp[0].r = RSSI2radius(beaconList[3][1]);
    get_position(circle_tmp, &point_tmp);
    temp = distance_cal(point_tmp, last_pos);
    if (temp < 0.5f)
        temp = 0.5;
    p_weight[1] = 1.0f / pow(temp, 2);
    pointCal.x += point_tmp.x * p_weight[1];
    pointCal.y += point_tmp.y * p_weight[1];

    circle_tmp[1] = circle[0];
    //circle_tmp[1].center = station[beaconList[0][0]];
    //circle_tmp[1].r = RSSI2radius(beaconList[0][1]);
    get_position(circle_tmp, &point_tmp);
    temp = distance_cal(point_tmp, last_pos);
    if (temp < 0.5f)
        temp = 0.5;
    p_weight[2] = 1.0f / pow(temp, 2);
    pointCal.x += point_tmp.x * p_weight[2];
    pointCal.y += point_tmp.y * p_weight[2];

    circle_tmp[2] = circle[1];
    //circle_tmp[2].center = station[beaconList[1][0]];
    //circle_tmp[2].r = RSSI2radius(beaconList[1][1]);
    get_position(circle_tmp, &point_tmp);
    temp = distance_cal(point_tmp, last_pos);
    if (temp < 0.5f)
        temp = 0.5;
    p_weight[3] = 1.0f / pow(temp, 2);

    pointCal.x += point_tmp.x * p_weight[3];
    pointCal.y += point_tmp.y * p_weight[3];

    point->x = pointCal.x / (p_weight[0] + p_weight[1] + p_weight[2] + p_weight[3]);
    point->y = pointCal.y / (p_weight[0] + p_weight[1] + p_weight[2] + p_weight[3]);
}
