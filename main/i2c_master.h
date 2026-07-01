#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include "driver/i2c_master.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* I2C Pin Configuration */
#define I2C_MASTER_SCL_IO      GPIO_NUM_9
#define I2C_MASTER_SDA_IO      GPIO_NUM_8

/* I2C Clock */
#define I2C_MASTER_FREQ_HZ     400000

/* Bus Handle */
extern i2c_master_bus_handle_t i2c_bus_handle;

/**
 * @brief Initialize I2C Master Bus
 *
 * @return ESP_OK if success
 */
esp_err_t i2c_master_init(void);

#ifdef __cplusplus
}
#endif

#endif