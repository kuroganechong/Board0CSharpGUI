#ifndef _GPS_H_
#define _GPS_H_

typedef struct {
    float UTCtime;
    float latitude;
    char NorthOrSouth;
    float longitude;
    char EastOrWest;
    float FixIndicate;
    float SatelliteNum;
    float HDOP;
    float altitude;
    float checkSum;
    float maxLen;

} GPS_t;


//int GPS_readNew(char* buf, GPS_t* output);

#endif  /* #ifndef _GPS_H_ */
