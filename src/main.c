#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../lib/print-to-serial-master/src/uart.h"

#define BAUD_RATE 9600
#define BAUD_PRESCALER (((16000000UL / (BAUD_RATE * 16UL))) - 1)
volatile int time_down = -1;
volatile int time_up = -1;
volatile int prev_char = -1;
volatile int char_index = 0;
volatile int encoding[5] = {-1, -1, -1, -1, -1};
volatile int looped = 0;
char* inp = "Translate to Morse";

void init() {
    cli();  // clear interrupts

    // configure input and outputs
    DDRB &= ~(1<<DDB0); // set B0 as input pin
    DDRB |= (1<<DDB3);  // set B3 as output pin (dot)
    DDRB |= (1<<DDB4);  // set B4 as output pin (dash)

    // set up interrupt for button click
    TCCR1B |= (1<<ICES1);   // enable interrupt on rising edge
    TIMSK1 |= (1<<ICIE1);   // input capture interrupt
    TIFR1 |= (1<<ICF1);     // input capture flag reset
    TCCR1B |= (1<<ICNC1);

    // pre-scale timer1 by 1024
    TCCR1B |= (1<<CS10);
    TCCR1B &= ~(1<<CS11);
    TCCR1B |= (1<<CS12);

    sei();  // re-enable interrupts
}

void print_morse() {

    if (encoding[0] == 0 && encoding[1] == -1 && encoding[2] == -1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("E");
    } else if (encoding[0] == 0 && encoding[1] == 0 && encoding[2] == -1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("I");
    } else if (encoding[0] == 0 && encoding[1] == 0 && encoding[2] == 0 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("S");
    } else if (encoding[0] == 0 && encoding[1] == 0 && encoding[2] == 0 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("H");
    } else if (encoding[0] == 0 && encoding[1] == 1 && encoding[2] == -1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("A");
    } else if (encoding[0] == 0 && encoding[1] == 1 && encoding[2] == 0 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("R");
    } else if (encoding[0] == 0 && encoding[1] == 1 && encoding[2] == 0 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("L");
    } else if (encoding[0] == 0 && encoding[1] == 1 && encoding[2] == 1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("W");
    } else if (encoding[0] == 0 && encoding[1] == 1 && encoding[2] == 1 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("P");
    } else if (encoding[0] == 0 && encoding[1] == 1 && encoding[2] == 1 && encoding[3] == 1 && encoding[4] == -1) {
        UART_putstring("J");
    } else if (encoding[0] == 0 && encoding[1] == 0 && encoding[2] == 1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("U");
    } else if (encoding[0] == 0 && encoding[1] == 0 && encoding[2] == 1 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("F");
    } else if (encoding[0] == 0 && encoding[1] == 0 && encoding[2] == 0 && encoding[3] == 1 && encoding[4] == -1) {
        UART_putstring("V");
    } else if (encoding[0] == 1 && encoding[1] == -1 && encoding[2] == -1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("T");
    } else if (encoding[0] == 1 && encoding[1] == 1 && encoding[2] == -1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("M");
    } else if (encoding[0] == 1 && encoding[1] == 1 && encoding[2] == 1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("O");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == -1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("N");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == 1 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("K");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == 1 && encoding[3] == 1 && encoding[4] == -1) {
        UART_putstring("Y");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == 1 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("C");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == 0 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("D");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == 0 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("B");
    } else if (encoding[0] == 1 && encoding[1] == 0 && encoding[2] == 0 && encoding[3] == 1 && encoding[4] == -1) {
        UART_putstring("X");
    } else if (encoding[0] == 1 && encoding[1] == 1 && encoding[2] == 0 && encoding[3] == -1 && encoding[4] == -1) {
        UART_putstring("G");
    } else if (encoding[0] == 1 && encoding[1] == 1 && encoding[2] == 0 && encoding[3] == 1 && encoding[4] == -1) {
        UART_putstring("Q");
    } else if (encoding[0] == 1 && encoding[1] == 1 && encoding[2] == 0 && encoding[3] == 0 && encoding[4] == -1) {
        UART_putstring("Z");
    } else {
        UART_putstring("?");
    }

    encoding[0] = -1;
    encoding[1] = -1;
    encoding[2] = -1;
    encoding[3] = -1;
    encoding[4] = -1;
    char_index = 0;
}



void dot_detect() {
    if (char_index < 5) {
        encoding[char_index] = 0;
        char_index++;
    }

    PORTB |= (1<<PORTB3);
    _delay_ms(50);
    PORTB &= ~(1<<PORTB3);
}

void dash_detect() {
    if (char_index < 5) {
        encoding[char_index] = 1;
        char_index++;
    }

    PORTB |= (1<<PORTB4);
    _delay_ms(50);
    PORTB &= ~(1<<PORTB4);
}

ISR(TIMER1_OVF_vect) {
    looped++;
    UART_putstring("loop");
}


ISR(TIMER1_CAPT_vect) {

    if (PINB & (1<<PINB0)) {
        time_down = TCNT1;

        int32_t diff = time_down - prev_char;
        if (diff < 0) {
            diff += 63536;
            looped = 0;
        }

        if (diff > 9375 && char_index != 0) {
            //UART_putstring("_");
            print_morse();
        }
    } else {
        time_up = TCNT1;

        int32_t diff = time_up - time_down;

        if (diff < 0) {
            diff += 63536;
            looped = 0;
        }

        if (diff > 470 && diff < 3125) {
            //UART_putstring(".");
            dot_detect();
        } else if (diff >= 3125 && diff <= 9375) {
            //UART_putstring("-");
            dash_detect();
        }

        prev_char = TCNT1;
    }

    TCCR1B ^= (1<<ICES1);           // toggle edge detection
    TIFR1 |= (1 << ICF1);           // input capture flag reset
}

int main(void) {

    UART_init(BAUD_PRESCALER);
    init();
    /* Replace with your application code */
    while(1){
    }
    //_delay_ms(100);

}


//part a
//int main(void) {
//
//    // initialize int to track sequence status
//    int sequence = 1;
//
//    // start with B1 LED active
//    PORTB |= (1<<PORTB1);
//
//    while(1) {
//
//        if ((PIND & (1<<PIND7)) && (sequence % 4 == 0)) {
//            sequence = 1;   // reset int
//            PORTB &= ~(1<<PORTB4);
//            PORTB |= (1<<PORTB1);
//        } else if ((PIND & (1<<PIND7)) && (sequence % 4 == 1)) {
//            sequence++;
//            PORTB &= ~(1<<PORTB1);
//            PORTB |= (1<<PORTB2);
//        } else if ((PIND & (1<<PIND7)) && (sequence % 4 == 2)) {
//            sequence++;
//            PORTB &= ~(1<<PORTB2);
//            PORTB |= (1<<PORTB3);
//        } else if ((PIND & (1<<PIND7)) && (sequence % 4 == 3)) {
//            sequence++;
//            PORTB &= ~(1<<PORTB3);
//            PORTB |= (1<<PORTB4);
//        }
//
//        _delay_ms(150);
//    }
//}