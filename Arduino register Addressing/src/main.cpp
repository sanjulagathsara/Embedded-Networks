#include <Arduino.h>

void setup() {
  DDRB |= (1<<5); // Set PB5 as an output
  PORTB |= (1<<5); // Turn the LED on
}

void loop() {

  PORTB = 0b00000000; // Turn the LED off
  delay(1000);
  PORTB = 0b00100000; // Turn the LED on
  delay(1000);

}