//#include <Arduino.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
//#include "../lib/print-to-serial-master/src/uart.h"
//
//#define BAUD_RATE 9600
//
//void init() {
//    cli();  // clear interrupts
//
//    DDRB &= ~(1<<DDB0); // set B0 as input pin
//    DDRB |= (1<<DDB4);  // set B4 as output pin
//
//    TCCR1B |= (1<<ICES1);   // enable interrupt on rising edge
//    //PORTB |= (1 << PORTB0); // enable pull-up resistor on PB0
//    TIFR1 |= (1<<ICF1);     // input capture flag reset
//    TIMSK1 |= (1<<ICIE1);   // input capture interrupt
//
//    sei();  // re-enable interrupts
//}
//
//ISR(TIMER1_CAPT_vect) {
//
//    if (PINB & (1<<PINB0)) {
//        PORTB |= (1<<PORTB4);       // light on
//        TCCR1B &= ~(1<<ICES1);      // change to falling edge
//    } else {
//        PORTB &= ~(1<<PORTB4);      // light off
//        TCCR1B |= (1<<ICES1);       // change to rising edge
//    }
//
//    TIFR1 |= (1 << ICF1);
//
//    _delay_ms(150);
//}
//
//int main(void) {
//
//    UART_init(9600);
//    init();
//    /* Replace with your application code */
//    while(1){
//    }
//    //_delay_ms(100);
//
//}
//
//
//// until part b
////int main(void) {
////
////    // initialize int to track sequence status
////    int sequence = 1;
////
////    // start with B1 LED active
////    PORTB |= (1<<PORTB1);
////
////    while(1) {
////
////        if ((PIND & (1<<PIND7)) && (sequence % 4 == 0)) {
////            sequence = 1;   // reset int
////            PORTB &= ~(1<<PORTB4);
////            PORTB |= (1<<PORTB1);
////        } else if ((PIND & (1<<PIND7)) && (sequence % 4 == 1)) {
////            sequence++;
////            PORTB &= ~(1<<PORTB1);
////            PORTB |= (1<<PORTB2);
////        } else if ((PIND & (1<<PIND7)) && (sequence % 4 == 2)) {
////            sequence++;
////            PORTB &= ~(1<<PORTB2);
////            PORTB |= (1<<PORTB3);
////        } else if ((PIND & (1<<PIND7)) && (sequence % 4 == 3)) {
////            sequence++;
////            PORTB &= ~(1<<PORTB3);
////            PORTB |= (1<<PORTB4);
////        }
////
////        _delay_ms(150);
////    }
////}