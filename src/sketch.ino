/* I2C Example. */

#include "led.h"

void updateLED();
void sleep(float seconds);
const int delay_interval = 10;

LED led(11);
bool is_master;

void setup() {
  pinMode(7, INPUT);
  is_master = digitalRead(7);

  led.setBrightness(100);
  led.setAnimation(true);
  led.flash(is_master ? 10 : 5);
  sleep(5);
}

void loop() {
  sleep(1);
}

void updateLED() {
  static unsigned long last_update = millis() - 1;
  float elapsed = (millis() - last_update) / 1000.f;
  led.update(elapsed);
  last_update = millis();
}

// Pause the program, but continue updating the display
void sleep(float seconds) {
  unsigned long target = millis() + (seconds * 1000);
  while (millis() < target) {
    updateLED();
    delay(delay_interval);
  }
}

