#include "pow_wind.h"

void windowp_up()
{
    PORTB = 0x18;
    _delay_ms(100);
    PORTB = 0x0C;
    _delay_ms(100);
    PORTB = 0x06;
    _delay_ms(100);
    PORTB = 0x12;
    _delay_ms(100);
}

void windowd_up()
{
    PORTC = 0x18;
    _delay_ms(100);
    PORTC = 0x0C;
    _delay_ms(100);
    PORTC = 0x06;
    _delay_ms(100);
    PORTC = 0x12;
    _delay_ms(100);
}
