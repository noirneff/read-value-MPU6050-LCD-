idf_component_register(SRCS "mpu6050.c" "i2c_master.c" "main.c"
                       INCLUDE_DIRS "."
                       REQUIRES esp_ssd1306 esp_driver_i2c)
