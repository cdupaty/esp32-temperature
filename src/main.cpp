#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);   // LED bleue intégrée sur la plupart des DevKit V1
}

void loop() {
  digitalWrite(2, HIGH);
  Serial.println("LED ON");
  delay(10);
  digitalWrite(2, LOW);
  Serial.println("LED OFF");
  delay(200);
}