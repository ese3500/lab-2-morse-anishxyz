#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void) {

    while(1) {
        // PORTB |= (1<<PORTB4);
        PORTB |= (1<<PORTB3);
        PORTB |= (1<<PORTB2);
        PORTB |= (1<<PORTB1);

        if (PIND & (1<<PIND7)) {
            PORTB |= (1<<PORTB4);
        } else {
            PORTB &= ~(1<<PORTB4);
        }

    }
}