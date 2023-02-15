#include <Arduino.h>
#include <avr/io.h>
#include <ctype.h>
#include <util/delay.h>
#include "../lib/print-to-serial-master/src/uart.h"

void init() {

    cli();  // clear interrupts

    // configure outputs
    DDRB |= (1<<DDB2);  // set B2 as output pin (space)
    DDRB |= (1<<DDB3);  // set B3 as output pin (dot)
    DDRB |= (1<<DDB4);  // set B4 as output pin (dash)

    sei();  // re-enable interrupts

}

void dot() {
    PORTB |= (1<<PORTB3);
    _delay_ms(300);
    PORTB &= ~(1<<PORTB3);
    _delay_ms(200);
}

void dash() {
    PORTB |= (1<<PORTB4);
    _delay_ms(600);
    PORTB &= ~(1<<PORTB4);
    _delay_ms(200);
}

void space() {
    PORTB |= (1<<PORTB2);
    _delay_ms(300);
    PORTB &= ~(1<<PORTB2);
    _delay_ms(200);
}

void to_morse(char c) {

    int l = tolower(c);

    switch(l) {
        case 'a':
            dot();
            dash();
            break;
        case 'b':
            dash();
            dot();
            dot();
            dot();
            break;
        case 'c':
            dash();
            dot();
            dash();
            dot();
            break;
        case 'd':
            dash();
            dot();
            dot();
            break;
        case 'e':
            dot();
            break;
        case 'f':
            dot();
            dot();
            dash();
            dot();
            break;
        case 'g':
            dash();
            dash();
            dot();
            break;
        case 'h':
            dot();
            dot();
            dot();
            dot();
            break;
        case 'i':
            dot();
            dot();
            break;
        case 'j':
            dot();
            dash();
            dash();
            dash();
            break;
        case 'k':
            dash();
            dot();
            dash();
            break;
        case 'l':
            dot();
            dash();
            dot();
            dot();
            break;
        case 'm':
            dash();
            dash();
            break;
        case 'n':
            dash();
            dot();
            break;
        case 'o':
            dash();
            dash();
            dash();
            break;
        case 'p':
            dot();
            dash();
            dash();
            dot();
            break;
        case 'q':
            dash();
            dash();
            dot();
            dash();
            break;
        case 'r':
            dot();
            dash();
            dot();
            break;
        case 's':
            dot();
            dot();
            dot();
            break;
        case 't':
            dash();
            break;
        case 'u':
            dot();
            dot();
            dash();
            break;
        case 'v':
            dot();
            dot();
            dot();
            dash();
            break;
        case 'w':
            dot();
            dash();
            dash();
            break;
        case 'x':
            dash();
            dot();
            dot();
            dash();
            break;
        case 'y':
            dash();
            dot();
            dash();
            dash();
            break;
        case 'z':
            dash();
            dash();
            dot();
            dot();
            break;
        case ' ':
            space();
            break;
        default:
            break;
    }

}



int main(void) {

    init();

    char* inp = "ESE";

    for (int i = 0; inp[i] != '\0'; i++) {
        char c = inp[i];
        to_morse(c);
        _delay_ms(400);
    }
}

