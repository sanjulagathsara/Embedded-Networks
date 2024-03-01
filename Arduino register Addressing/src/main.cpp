#include <Arduino.h>

void setup() {
  DDRB |= (1<<5); // Set PB5 as an output
  PORTB |= (1<<5); // Turn the LED on
}

void loop() {
  delay(100);
  PORTB &= (0<<5); // Turn the LED off
  delay(100);
  PORTB |= (1<<5); // Turn the LED on
}