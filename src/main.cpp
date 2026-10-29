#include <Arduino.h>

const uint8_t LED_PIN = 2;               // LED bleue intégrée du DevKit V1
const uint32_t PERIOD_US_H = 20000;       // période etat H
const uint32_t PERIOD_US_L = 200000;       // période etat L
hw_timer_t *timer = nullptr;
volatile bool ledState = false;

// ISR exécutée à chaque alarme du timer (en IRAM)
void IRAM_ATTR onTimer() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
  if (ledState ==true ) timerAlarmWrite(timer, PERIOD_US_H, true); 
  else timerAlarmWrite(timer, PERIOD_US_L, true); 
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  timer = timerBegin(0, 80, true);               // timer 0, prescaler 80 : 80 MHz / 80 = 1 MHz (1 tick = 1 µs)
  timerAttachInterrupt(timer, &onTimer, true);   // associe l'ISR (interruption sur front)
  timerAlarmWrite(timer, PERIOD_US_L, true);       // alarme toutes les 500 ms, auto-reload
  timerAlarmEnable(timer);                       // active l'alarme
}

void loop() {
  // vide : tout est géré par l'interruption
}