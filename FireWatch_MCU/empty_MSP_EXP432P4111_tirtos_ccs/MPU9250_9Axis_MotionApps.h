#define MPU9250_DMP_CODE_SIZE       1962    // dmpMemory[]
#define MPU9250_DMP_CONFIG_SIZE     232     // dmpConfig[]
#define MPU9250_DMP_UPDATES_SIZE    140     // dmpUpdates[]

#define quat_res   16384.0f
#define acc_res    16384.0f // unit: G
#define gyro_res   8.192f // ?unit: deg/s
#define mag_res    166.78f // unit: Gauss

#define PI 3.14159265358979f

unsigned char mpu_dmpInitialize();

char mpu_dmpPacketAvailable();

void mpu_dmpGetQuaternion(const unsigned char* packet, float* data);

void mpu_dmpGetGyro(const unsigned char* packet, float* data);

void mpu_dmpGetMag(const unsigned char* packet, float* data);

float mpu_dmpGetMagAngle(float* q, float* mag, float* mag_ref);

void mpu_dmpGetLinearAccel(signed short* accel, float* q, float* data);

void mpu_dmpGetYawPitchRoll(float* q, float* rad);

void mpu_dmpGetLinearAccelInWorld(float* q, float* a);

void mpu_dmpGetLinearAccelInFrame(float bias, float* rad, float* a);

void mpu_dmpGetRawAccel(const unsigned char* packet, float* data);

void mpu_dmpGetYawPitchRollNew(float *p, float *rad);
