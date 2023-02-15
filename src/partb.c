#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void init() {
    cli();  // clear interrupts

    DDRB &= ~(1<<DDB0); // set B0 as input pin
    DDRB |= (1<<DDB5);  // set B5 as output pin

    // PORTB |= (1 << PORTB0); // enable pull-up resistor on PB0
    TCCR1B |= (1<<ICES1);   // enable interrupt on rising edge
    TIMSK1 |= (1<<ICIE1);   // input capture interrupt
    TIFR1 |= (1<<ICF1);     // input capture flag reset

    sei();  // re-enable interrupts
}

ISR(TIMER1_CAPT_vect) {

        if (PINB & (1<<PINB0)) {

            PORTB |= (1<<PORTB5);       // light on

        } else {

            PORTB &= ~(1<<PORTB5);      // light off

        }

        TCCR1B ^= (1<<ICES1);           // toggle edge detection
        TIFR1 |= (1 << ICF1);           // input capture flag reset

        _delay_ms(150);
}

int main(void) {

    init();
    /* Replace with your application code */
    while(1){
    }
    //_delay_ms(100);

}