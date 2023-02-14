#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void init()
{
    cli();  // clear interrupts

    DDRB &= ~(1<<DDB0); // set B0 as input pin
    DDRB |= (1<<DDB4);  // set B4 as output pin

    TCCR1B |= (1<<ICES1);   // enable interrupt on rising edge
    TIFR1 |= (1<<ICF1);     // input capture flag reset
    TIMSK1 |= (1<<ICIE1);   // input capture interrupt

    sei();  // re-enable interrupts
}

ISR(TIMER1_CAPT_vect) {

        if (PINB & (1<<PINB0)) {
            PORTB |= (1<<PORTB4);       // light on
            TCCR1B &= ~(1<<ICES1);      // change to falling edge
        } else {
            PORTB &= ~(1<<PORTB4);      // light off
            TCCR1B |= (1<<ICES1);       // change to rising edge
        }
        _delay_ms(150);
}

int main(void) {
    init();
    /* Replace with your application code */
    while (1) {
    }
    //_delay_ms(100);
}
