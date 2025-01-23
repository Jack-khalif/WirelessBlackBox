#define VIBRATION_SENSOR_PIN 2 // Change to the pin you connected to

void setup() {
  Serial.begin(115200);
  pinMode(VIBRATION_SENSOR_PIN, INPUT);
}

void loop() {
  int sensorValue = digitalRead(VIBRATION_SENSOR_PIN); // Read the sensor value
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue); // Print the raw sensor value

  // Additional debugging
  if (sensorValue == HIGH) {
    Serial.println("Vibration Detected!");
  } else {
    Serial.println("No Vibration.");
  }

  delay(2000); // Delay for readability
}