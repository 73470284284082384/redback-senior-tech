# Elderly IoT Sensor Data Collection

This project implements a real-time IoT data collection system for wearable elderly healthcare monitoring. It collects heart rate and motion data using an ESP32 microcontroller and uploads the data to Google Sheets via IFTTT Webhooks.

---

## 💡 Features
- Heart rate monitoring via pulse sensor
- Fall detection and movement analysis via MPU6050 (Accelerometer + Gyroscope)
- Wireless data upload over Wi-Fi
- Logs data to Google Sheets for cloud-based tracking

---

## 🛠 Hardware Requirements
- ESP32 (Wi-Fi enabled)
- Pulse Sensor
- MPU6050 Accelerometer/Gyroscope
- Jumper Wires & Breadboard
- Optional: Battery module for wearable portability

---

## 🔧 Setup Instructions

### 1. Connect the Hardware
- Pulse Sensor to pin 34 (ADC)
- MPU6050 to I2C (SCL: GPIO22, SDA: GPIO21 on ESP32)

### 2. Configure IFTTT
1. Go to [IFTTT](https://ifttt.com/)
2. Create an applet:
   - Trigger: Webhooks → Receive a web request (`YOUR_EVENT_NAME`)
   - Action: Google Sheets → Add row to spreadsheet
3. Copy your IFTTT key and replace it in the code

### 3. Upload Code
- Install libraries:
  - Adafruit_MPU6050
  - Adafruit_Sensor
- Edit Wi-Fi and IFTTT info in the code
- Flash code using Arduino IDE

---

## 📊 Sample Data Output
| Timestamp       | Heart Rate (BPM) | Accel X (m/s²) | Accel Y (m/s²) |
|----------------|------------------|----------------|----------------|
| 2025-04-19 14:22 | 82               | 0.32           | -0.12          |

---

