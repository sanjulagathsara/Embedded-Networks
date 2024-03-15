// Gathsara J.A.S
// Start a timer with 1ms resolution and another timer with 1us resolution
// Print a value every 100ms


#include <Arduino.h>

volatile uint16_t milliseconds = 0;
volatile uint8_t microseconds = 0;

void initTimer1() {
    // Configure Timer1 for 1ms interrupts

    TCCR1B |= (1 << WGM12);  // CTC mode
    OCR1A = 249;  // Timer1 CTC match value for 1ms at 16MHz with prescaler 64
    TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 compare match A interrupt
    TCCR1B |= (1 << CS11) | (1 << CS10);  // Start Timer1 with prescaler 64
}

void delay_ms(uint16_t ms) {
    uint16_t start_ms = milliseconds;
    while (milliseconds - start_ms < ms);
}

void initTimer2() {
    // Configure Timer2 for 1us interrupts

    TCCR2A = 0;  // Clear Timer2 control registers
    TCCR2B = 0;
    TCNT2 = 0;  // Initialize Timer2 counter
    OCR2A = 15;  // Timer2 CTC match value for 1us at 16MHz with prescaler 8
    TCCR2A |= (1 << WGM21);  // CTC mode
    TIMSK2 |= (1 << OCIE2A);  // Enable Timer2 compare match A interrupt
    TCCR2B |= (1 << CS21);  // Start Timer2 with prescaler 8
}

void delay_us(int us) {
    uint8_t start_us = microseconds;
    while (microseconds - start_us < us);
}

ISR(TIMER1_COMPA_vect) {
    milliseconds++;
}

ISR(TIMER2_COMPA_vect) {
    microseconds++;
}

void setup() {
    // Initialize Serial
    Serial.begin(9600);

    // Initialize Timers
    initTimer1();
    initTimer2();
}

void loop() {
    static uint8_t counter = 0;
    static uint16_t value = 0;

    delay_ms(20); // Delay 20ms

    value++;
    counter++;

    if (counter >= 5) { // Print every 100ms
        Serial.println(value);
        counter = 0;
    }
}
