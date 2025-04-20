
#include <WiFi.h>
 #include <HTTPClient.h>
 #include <Wire.h>
 #include <Adafruit_MPU6050.h>
 #include <Adafruit_Sensor.h>
 
 
 const char* WIFI_SSID = "YOUR_WIFI_SSID";
 const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
 
 
 const char* IFTTT_EVENT = "YOUR_EVENT_NAME";
 const char* IFTTT_KEY = "YOUR_IFTTT_KEY";
 const String IFTTT_URL = "https://maker.ifttt.com/trigger/" + String(IFTTT_EVENT) + "/with/key/" + String(IFTTT_KEY);
 
 
 const int PULSE_PIN = 34;  
 
 
 Adafruit_MPU6050 mpu;
 
 
 void connectToWiFi() {
   Serial.print("Connecting to WiFi: ");
   Serial.println(WIFI_SSID);
 
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   int attempts = 0;
 
   while (WiFi.status() != WL_CONNECTED && attempts < 20) {
     delay(500);
     Serial.print(".");
     attempts++;
   }
 
   if (WiFi.status() == WL_CONNECTED) {
     Serial.println("\n✅ WiFi connected.");
     Serial.print("IP address: ");
     Serial.println(WiFi.localIP());
   } else {
     Serial.println("\n❌ Failed to connect to WiFi.");
   }
 }
 
 
 void initMPU6050() {
   if (!mpu.begin()) {
     Serial.println("❌ Failed to find MPU6050 sensor. Check wiring!");
     while (1) delay(10);
   }
 
   
   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
   mpu.setGyroRange(MPU6050_RANGE_500_DEG);
   mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
 
   Serial.println("✅ MPU6050 initialized.");
 }
 
 void setup() {
   Serial.begin(115200);
   connectToWiFi();
   initMPU6050();
   pinMode(PULSE_PIN, INPUT);
 }
 
 void loop() {
   
   int rawPulseValue = analogRead(PULSE_PIN);
   float heartRate = map(rawPulseValue, 0, 4095, 60, 120); 

   sensors_event_t accel, gyro, temp;
   mpu.getEvent(&accel, &gyro, &temp);
   float accelX = accel.acceleration.x;
   float accelY = accel.acceleration.y;
   float accelZ = accel.acceleration.z;
 
   
   Serial.println("---- Sensor Readings ----");
   Serial.printf("Heart Rate: %.2f BPM\n", heartRate);
   Serial.printf("Accel X: %.2f | Y: %.2f | Z: %.2f (m/s²)\n", accelX, accelY, accelZ);
 
   
   String jsonPayload = String("{\"value1\":\"") + heartRate +
                        "\",\"value2\":\"" + accelX +
                       "\",\"value3\":\"" + accelY + "\"}";
 
   
   if (WiFi.status() == WL_CONNECTED) {
     HTTPClient http;
     http.begin(IFTTT_URL);
     http.addHeader("Content-Type", "application/json");
 
     int responseCode = http.POST(jsonPayload);
 
     if (responseCode > 0) {
       Serial.print("✅ Data sent to IFTTT. Response Code: ");
       Serial.println(responseCode);
     } else {
       Serial.print("❌ Failed to send data. HTTP error: ");
       Serial.println(responseCode);
     }
 
     http.end();
   } else {
     Serial.println("❌ WiFi not connected.");
   }
 
   delay(10000); 
 }
 