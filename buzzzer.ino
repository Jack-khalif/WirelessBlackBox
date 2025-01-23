// Define the pin for the buzzer
#define BUZZER_PIN 14

void setup() {
  // Initialize the buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Turn the buzzer on
  digitalWrite(BUZZER_PIN, LOW);
  delay(5000); // Wait for 5 second
  
  // Turn the buzzer off
  digitalWrite(BUZZER_PIN, LOW);
  delay(2000); // Wait for 1 second
}
