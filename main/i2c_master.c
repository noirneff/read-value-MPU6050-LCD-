#include "i2c_master.h"

#include "esp_log.h"

static const char *TAG = "I2C_MASTER";

/* Global Bus Handle */
i2c_master_bus_handle_t i2c_bus_handle = NULL;

esp_err_t i2c_master_init(void)
{
    i2c_master_bus_config_t bus_cfg =
    {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,

        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,

        .glitch_ignore_cnt = 7,

        .flags.enable_internal_pullup = true,
    };

    esp_err_t ret = i2c_new_master_bus(&bus_cfg, &i2c_bus_handle);

    if (ret == ESP_OK)
    {
        ESP_LOGI(TAG, "I2C Master Initialized");
    }
    else
    {
        ESP_LOGE(TAG, "I2C Init Failed (%s)", esp_err_to_name(ret));
    }

    return ret;
}