# Yêu cầu dự án: Đọc dữ liệu MPU6050 và hiển thị lên LCD SSD1306

Sử dụng các kiến thức đã tìm hiểu về GPIO, I2C, IDF SDK trên nền tảng ESP32-S3 để đọc tín hiệu từ cảm biến gia tốc - góc quay MPU6050 (giao tiếp I2C) và hiển thị lên màn hình LCD SSD1306.

## 1. Yêu cầu cụ thể:

### 1.1. Phần cứng & Tài liệu
* Hardware: ESP32-S3 DevKitC v1, cảm biến MPU6050, LCD SSD1306.
* Tài liệu: ESP32-S3 Technical Reference Manual, Register Map MPU6050, Datasheet SSD1306.

### 1.2. Yêu cầu chức năng
Viết code bằng ESP-IDF SDK để cấu hình GPIO, I2C, Task/Interrupt để:
* Đọc dữ liệu thô (Gia tốc & Góc quay & nhiệt độ ) từ cảm biến MPU6050: cycle time 5s.
* Xử lý dữ liệu thô và hiển thị các thông số lên màn hình LCD SSD1306.

### 1.3. Thực nghiệm & Mục tiêu
* Tiến hành viết code, compile (biên dịch) và flash (nạp) chương trình xuống board mạch thực tế.
* Mục tiêu: Kiểm tra khả năng hiểu về giao thức I2C, cách sử dụng ESP-IDF SDK và kỹ năng xử lý, ghép nối dữ liệu trong truyền thông I2C.
