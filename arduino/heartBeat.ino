const int sensorPin = 2; // KY-002 sensor connected to digital pin 2
int sensorValue = 0;
unsigned long vibrationStart = 0;
unsigned long vibrationDuration = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
  pinMode(sensorPin, INPUT); // Set the sensor pin as an input
}

void loop() {
  sensorValue = digitalRead(sensorPin); // Read the value from the sensor

  if (sensorValue == HIGH) {
    if (vibrationStart == 0) {
      vibrationStart = millis(); // Record the start time of the vibration
    }
  } else {
    if (vibrationStart != 0) {
      vibrationDuration = millis() - vibrationStart; // Calculate the duration of the vibration
      float vibrationFrequency = 1000.0 / vibrationDuration; // Frequency in Hz
      Serial.print("Vibration Detected! Duration: ");
      Serial.print(vibrationDuration);
      Serial.print(" ms, Frequency: ");
      Serial.print(vibrationFrequency);
      Serial.println(" Hz");
      vibrationStart = 0; // Reset the start time
    }
  }
}
