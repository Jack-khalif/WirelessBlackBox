# WirelessBlackBox
A Vehicle Monitoring and Accident Detection System using ESP32, DHT22, MPU6050, and SW420 sensors. Logs real-time data to ThingSpeak and triggers alerts for accidents and hazardous conditions.

## **Overview**
This project implements a Vehicle Monitoring and Accident Detection System using an ESP32 microcontroller, multiple sensors, and ThingSpeak integration. It monitors environmental conditions, vehicle dynamics, and logs real-time data to the cloud, while triggering alerts for accidents or hazardous conditions.

## **Features**
1. **Environmental Monitoring**
   - Detects temperature and humidity using the DHT22 sensor.
2. **Accident Detection**
   - Identifies tilt, acceleration, and vibrations using the MPU6050 and SW420 sensors.
3. **Cloud Logging**
   - Sends data to ThingSpeak for remote monitoring and visualization.
4. **Alert System**
   - Triggers buzzer alerts when thresholds are exceeded.

## **Hardware Components**
- **ESP32 DevKit V1**
- **DHT22 Sensor** (Temperature and Humidity)
- **SW420 Vibration Sensor**
- **MPU6050 Accelerometer and Gyroscope**
- **Buzzer**

## **How It Works**
1. **Initialization**:
   - Connects to Wi-Fi and initializes sensors.
2. **Data Collection**:
   - Reads temperature, humidity, acceleration, tilt, and vibration state.
3. **Alerts**:
   - Activates buzzer for potential crashes or hazardous conditions.
4. **Cloud Logging**:
   - Sends collected data to ThingSpeak for analysis and visualization.

## **Setup Instructions**
### **1. Hardware Connections**
- Connect:
  - **DHT22 sensor** to GPIO 5.
  - **SW420 vibration sensor** to GPIO 2.
  - **Buzzer** to GPIO 14.
  - **MPU6050** to I2C (SDA to GPIO 21, SCL to GPIO 22).

### **2. Software Setup**
- Install required libraries:
  - `WiFi`
  - `ThingSpeak`
  - `DHT`
  - `Adafruit_MPU6050`
- Configure Wi-Fi credentials in the code.
- Replace `myChannelNumber` and `myWriteAPIKey` with your ThingSpeak channel details.

### **3. Upload Code**
- Use Arduino IDE or PlatformIO to upload the code.

### **4. Run**
- Power the ESP32 and monitor behavior via Serial Monitor or ThingSpeak.

## **Future Improvements**
- Add GPS tracking for accident location.
- Integrate GSM for SMS alerts to emergency contacts.
- Implement offline data storage for black-box functionality.

## **License**
[MIT License](LICENSE)

