#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define UBRR_CONST 103

//input na PCINT8



void UART_init(uint16_t ubrr)
{
    // set baudrate in UBRR
    UBRR0L = (uint8_t)(ubrr & 0xFF);
    UBRR0H = (uint8_t)(ubrr >> 8);

    // enable the transmitter and receiver
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void send_char(char a)
{
    //while(!(UCSR0A & (1 >> UDRE0)));
    UDR0 = a;
    //
}

int main(void)
{
    UART_init(UBRR_CONST);
//    DDRB=0xFF;
//    PORTB = 0xFF;


    PCMSK1 |= (1<<PCINT8);
    PCICR |= (1<<PCIE1);

    sei();

    while(1)
    {
        _delay_ms(100);
        PORTB = 0xFF;
        _delay_ms(100);
        PORTB = 0x00;
//        send_char(0x67);
    }
}

ISR(PCINT1_vect){

        send_char(0x61);
}