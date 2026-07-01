#include "mpu6050.h"
#include "esp_log.h"

static const char *TAG = "MPU6050";

// Registers
#define REG_WHO_AM_I      0x75
#define REG_PWR_MGMT_1    0x6B
#define REG_ACCEL_XOUT_H  0x3B
#define REG_GYRO_XOUT_H   0x43
#define REG_TEMP_OUT_H     0x41

static esp_err_t mpu_write(mpu6050_t *mpu, uint8_t reg, uint8_t data)
{
    uint8_t buf[2] = {reg, data};
    return i2c_master_transmit(mpu->dev, buf, 2, -1);
}

static esp_err_t mpu_read(mpu6050_t *mpu, uint8_t reg, uint8_t *data, size_t len)
{
    return i2c_master_transmit_receive(
        mpu->dev,
        &reg,
        1,
        data,
        len,
        -1
    );
}

esp_err_t mpu6050_init(mpu6050_t *mpu, i2c_master_bus_handle_t bus)
{
    i2c_device_config_t cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MPU6050_ADDR,
        .scl_speed_hz = 400000
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &cfg, &mpu->dev));

    uint8_t who = 0;
    mpu_read(mpu, REG_WHO_AM_I, &who, 1);

    ESP_LOGI(TAG, "WHO_AM_I = 0x%02X", who);

    // Accept MPU6050 (0x68) and common compatible variants:
    // MPU6500/MPU6880 (0x70), ICM-20602 (0x12), MPU9250 (0x71, 0x73), etc.
    if (who != 0x68 && who != 0x70 && who != 0x71 && who != 0x73 && who != 0x12 && who != 0x75) {
        ESP_LOGE(TAG, "MPU6050/compatible sensor not found (WHO_AM_I=0x%02X)", who);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Sensor detected (WHO_AM_I=0x%02X)", who);

    // Wake up sensor
    mpu_write(mpu, REG_PWR_MGMT_1, 0x00);

    return ESP_OK;
}

static esp_err_t read_raw(mpu6050_t *mpu, uint8_t reg, mpu6050_raw_t *out)
{
    uint8_t buf[6];

    ESP_ERROR_CHECK(mpu_read(mpu, reg, buf, 6));

    out->x = (int16_t)(buf[0] << 8 | buf[1]);
    out->y = (int16_t)(buf[2] << 8 | buf[3]);
    out->z = (int16_t)(buf[4] << 8 | buf[5]);

    return ESP_OK;
}

esp_err_t mpu6050_read_accel(mpu6050_t *mpu, mpu6050_raw_t *accel)
{
    return read_raw(mpu, REG_ACCEL_XOUT_H, accel);
}

esp_err_t mpu6050_read_gyro(mpu6050_t *mpu, mpu6050_raw_t *gyro)
{
    return read_raw(mpu, REG_GYRO_XOUT_H, gyro);
}

esp_err_t mpu6050_read_temp(mpu6050_t *mpu, float *temp_c)
{
    uint8_t buf[2];
    ESP_ERROR_CHECK(mpu_read(mpu, REG_TEMP_OUT_H, buf, 2));

    int16_t raw = (int16_t)(buf[0] << 8 | buf[1]);
    *temp_c = raw / 340.0f + 36.53f;

    return ESP_OK;
}