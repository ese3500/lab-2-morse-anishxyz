#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void init() {
    cli();  // clear interrupts

    DDRB &= ~(1<<DDB0); // set B0 as input pin
    DDRB |= (1<<DDB5);  // set B5 as output pin

    PCICR |= (1 << PCIE0); // Enable Pin Change Interrupt 0
    PCMSK0 |= (1 << PCINT0); // Enable interrupt on PB0

    sei();  // re-enable interrupts
}

ISR(PCINT0_vect) {
    if (PINB & (1 << PINB0)) {
        PORTB |= (1 << PINB5); // Set PB5 high
    }
    else {
        PORTB &= ~(1 << PINB5); // Set PB5 low
    }
}


int main(void) {

    init();
    /* Replace with your application code */
    while(1){
    }
    //_delay_ms(100);

}