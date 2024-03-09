#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  DDRB |= (1<<5); // Set PB5 as an output
  PORTB |= (1<<5); // Turn the LED on


  TCCR1A = 0; // Set entire TCCR1A register to 0
  TCCR1B = 0; // Same for TCCR1B
  TCNT1  = 0; // Initialize counter value to 0


  // Set compare match register for 1hz increments
  OCR1A = 15624/10; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  

  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // enable global interrupts
  sei();


}

ISR(TIMER1_COMPA_vect){
  PORTB ^= (1<<PORTB5); // Toggle the  LED
}

void loop() {
  // No loop here
}