#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Wi-Fi credentials
const char* ssid = "Plugins-viva_la_vida";
const char* password = "2024jacktothetop";

WiFiClient client;

unsigned long myChannelNumber = 2815888; 
const char * myWriteAPIKey = "WY85K02HNOQUDD3M"; 

// Pin Definitions
#define DHTPIN 5
#define VIBRATION_SENSOR_PIN 2
#define BUZZER_PIN 14

// Thresholds
#define TEMP_THRESHOLD 35
#define HUMIDITY_THRESHOLD 70
#define ACCEL_THRESHOLD 15  // Acceleration threshold in m/s^2 (e.g., a crash)
#define TILT_THRESHOLD 30   // Tilt threshold in degrees

// DHT22 sensor setup
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// MPU6050 setup
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBRATION_SENSOR_PIN, INPUT);

  Serial.println("Vehicle Monitoring System Initialized!");

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    delay(5000);
  }
  Serial.println("Connected to WiFi!");

  ThingSpeak.begin(client);

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  Serial.println("MPU6050 Initialized!");
}

void loop() {
  // Read DHT22 data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  
// Read the state of the SW420 vibration sensor
  int vibrationState = digitalRead(VIBRATION_SENSOR_PIN);

  // Check for valid readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read MPU6050 data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print MPU6050 readings
  Serial.print("Acceleration X: "); Serial.println(a.acceleration.x);
  Serial.print("Acceleration Y: "); Serial.println(a.acceleration.y);
  Serial.print("Acceleration Z: "); Serial.println(a.acceleration.z);

  Serial.print("Gyro X: "); Serial.println(g.gyro.x);
  Serial.print("Gyro Y: "); Serial.println(g.gyro.y);
  Serial.print("Gyro Z: "); Serial.println(g.gyro.z);

  float tilt = atan2(a.acceleration.y, a.acceleration.x) * (180 / PI);  // Calculate tilt angle in degrees

  // Logic for buzzer - only activate when thresholds are exceeded
  if (abs(a.acceleration.x) > ACCEL_THRESHOLD || abs(a.acceleration.y) > ACCEL_THRESHOLD || abs(a.acceleration.z) > ACCEL_THRESHOLD) {
    Serial.println("Accident detected! Triggering alert...");
    tone(BUZZER_PIN, 1000, 3000);  // Activate buzzer
  }
  if (abs(tilt) > TILT_THRESHOLD) {
    Serial.println("Tilt detected! Triggering alert...");
    tone(BUZZER_PIN, 2000, 3000);  // Activate buzzer
  }

  if (temperature > TEMP_THRESHOLD || humidity > HUMIDITY_THRESHOLD) {
    Serial.println("High temp/humidity detected! Triggering alert...");
    tone(BUZZER_PIN, 1500, 3000);  // Activate buzzer
  }

  // Send data to ThingSpeak regardless of alerts
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, a.acceleration.x);  // Acceleration X
  ThingSpeak.setField(4, a.acceleration.y);  // Acceleration Y
  ThingSpeak.setField(5, a.acceleration.z);  // Acceleration Z
  ThingSpeak.setField(6, tilt);              // Tilt angle
  ThingSpeak.setField(7, vibrationState);    // Vibration sensor state





  int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (responseCode == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Failed to update channel. HTTP error code " + String(responseCode));
  }

  delay(20000);  // Wait 20 seconds between updates (this can be adjusted based on your needs)
}
