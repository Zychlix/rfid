#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

#define LC_PIN_A (1<<3)
#define LC_PIN_B (1<<4)
#define LED_PIN (1<<0)
#define START_BIT_DURATION 50

#define HALF_BIT_DURATION 10

void delay_cycles(uint8_t n){
    uint8_t start = TCNT0;
    uint16_t current = TCNT0;
    while(current-start<n)
    {
        current = TCNT0;
    };
}


void init_timer()
{
    TCCR0A = 0;
    TCCR0B = 0b10;
    GTCCR = 0;
}



void set_led(uint8_t state)
{
    if(state)
    {
        PORTB |= LED_PIN;
    }
    else
    {
        PORTB &= ~LED_PIN;
    }
}

void load_enable()
{
    DDRB |= LC_PIN_A | LC_PIN_B;
    set_led(1);

}

void load_disable()
{
    DDRB &=~(LC_PIN_A | LC_PIN_B);
    set_led(0);
}

void start_bit(){
    load_enable();
    delay_cycles(START_BIT_DURATION);
}

void bit_zero(){
    load_disable();
    delay_cycles(HALF_BIT_DURATION);
    load_enable();
    delay_cycles(HALF_BIT_DURATION);
}

void bit_one(){
    load_enable();
    delay_cycles(HALF_BIT_DURATION);
    load_disable();
    delay_cycles(HALF_BIT_DURATION);
}

int main(void)
{
    DDRB = 1;

    _delay_ms(100);
//    set_led(1);

    init_timer();

    while(1)
    {
        _delay_ms(10);
//        load_enable();
//        _delay_ms(1);
//        load_disable();
//        _delay_ms(1);
//        set_led(TCNT0);
        start_bit();
        for (uint8_t i = 0; i < 8; ++i) {
            bit_zero();
//            bit_one();
        }
        load_disable();

    }

}
