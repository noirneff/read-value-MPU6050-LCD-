#ifndef MPU6050_H
#define MPU6050_H

#include "esp_err.h"
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MPU6050_ADDR 0x68

typedef struct {
    i2c_master_dev_handle_t dev;
} mpu6050_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} mpu6050_raw_t;

esp_err_t mpu6050_init(mpu6050_t *mpu, i2c_master_bus_handle_t bus);
esp_err_t mpu6050_read_accel(mpu6050_t *mpu, mpu6050_raw_t *accel);
esp_err_t mpu6050_read_gyro(mpu6050_t *mpu, mpu6050_raw_t *gyro);
esp_err_t mpu6050_read_temp(mpu6050_t *mpu, float *temp_c);

#ifdef __cplusplus
}
#endif

#endif