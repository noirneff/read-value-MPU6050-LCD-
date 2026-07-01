#include "i2c_master.h"
#include "mpu6050.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// SSD1306
#include "ssd1306.h"

static const char *TAG = "APP";

static mpu6050_t mpu;
static ssd1306_handle_t oled = NULL;

void app_main(void)
{
    i2c_master_init();

    // MPU6050
    ESP_ERROR_CHECK(mpu6050_init(&mpu, i2c_bus_handle));

    // SSD1306 - sử dụng đúng API của k0i05/esp_ssd1306
    ssd1306_config_t oled_cfg = I2C_SSD1306_128x64_CONFIG_DEFAULT;
    ESP_ERROR_CHECK(ssd1306_init(i2c_bus_handle, &oled_cfg, &oled));

    // Buffer cho mỗi dòng OLED (tối đa 16 ký tự + null)
    char buf[17];

    mpu6050_raw_t accel, gyro;
    float temp_c;

    while (1) {

        mpu6050_read_accel(&mpu, &accel);
        mpu6050_read_gyro(&mpu, &gyro);
        mpu6050_read_temp(&mpu, &temp_c);

        // Xóa toàn bộ màn hình
        ssd1306_clear_display(oled, false);

        // Page 0: AX AY
        snprintf(buf, sizeof(buf), "A %+6d %+6d", accel.x, accel.y);
        ssd1306_display_text(oled, 0, buf, false);

        // Page 1: AZ
        snprintf(buf, sizeof(buf), "Z %+6d", accel.z);
        ssd1306_display_text(oled, 1, buf, false);

        // Page 2: GX GY
        snprintf(buf, sizeof(buf), "G %+6d %+6d", gyro.x, gyro.y);
        ssd1306_display_text(oled, 2, buf, false);

        // Page 3: GZ
        snprintf(buf, sizeof(buf), "Z %+6d", gyro.z);
        ssd1306_display_text(oled, 3, buf, false);

        // Page 5: Temperature
        snprintf(buf, sizeof(buf), "T:%.1f C", temp_c);
        ssd1306_display_text(oled, 5, buf, false);

        ESP_LOGI(TAG, "A:%d,%d,%d G:%d,%d,%d T:%.1fC",
                 accel.x, accel.y, accel.z,
                 gyro.x, gyro.y, gyro.z, temp_c);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}