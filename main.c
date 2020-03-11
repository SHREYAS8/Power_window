/*
Name : Shreyas C N
Employee ID : 142897
Version : 1.0v
 */

#include "pow_wind.h"

int main(void)
{
    config_switch();
    config_Stepper();

    uint8_t count1 = 0;
    uint8_t count2 = 0;
    uint16_t ADC_val;

    cont.lock = 0;
    cont.up_p = 0;
    cont.down_p = 0;
    cont.up_d = 0;
    cont.down_d = 0;

    ADMUX&=0x00;
    ADMUX|= (1<<REFS0);
    ADCSRA|= (1<< ADEN);

    while(1)
    {
        ADCSRA|= (1<<ADSC);
        while(ADCSRA & (1<<ADSC));
        ADC_val = ADC;

        if(PINC & (1<<PC6))
            cont.lock = 1;
        else
            cont.lock = 0;

        if(PIND & (1<<PD0))
            cont.up_p = 1;
        else
            cont.up_p = 0;

        if(PIND & (1<<PD1))
            cont.down_p = 1;
        else
            cont.down_p = 0;

        if(PINC & (1<<PC3))
            cont.up_d = 1;
        else
            cont.up_d = 0;

        if(PINC & (1<<PC4))
            cont.down_d = 1;
        else
            cont.down_d = 0;

        if(ADC_val < 314)
        {
            if(cont.up_d == 1 && count1 < 6)
            {
                windowd_up();
                count1++;
            }
            else if(cont.down_d == 1 && count1 > 0)
            {
                windowd_down();
                count1--;
            }

            if(cont.lock == 0)
            {
                if(cont.up_p == 1 && count2 < 6)
                {
                    windowp_up();
                    count2++;
                }

                else if(cont.down_p == 1 && count2 > 0)
                {
                    windowp_down();
                    count2--;
                }
            }
        }

        else if(ADC_val > 314 && ADC_val < 728) // obstacle
        {
            while(count1 > 0)
            {
                windowd_down();
                count1--;
            }
            while(count2 > 0)
            {
                windowp_down();
                count2--;
            }
        }
        else // rain
        {
            while(count1 < 6)
            {
                windowd_up();
                count1++;
            }
            while(count2 < 6)
            {
                windowp_up();
                count2++;
            }
        }
    }
    return 0;
}

void config_switch()
{
    CLR_BIT(DDRC,PC6);  // Child Lock
    CLR_BIT(DDRD,PD7);  // window driver up/ down
    CLR_BIT(DDRD,PB0);
    CLR_BIT(DDRD,PD0);  // window passenger up/ down
    CLR_BIT(DDRD,PD1);
    CLR_BIT(DDRC,PC0);  // Obstacle and rain detection
}

void config_Stepper()
{
    SET_BIT(DDRD,PD7);  // Setting pins as output for stepper motor
    SET_BIT(DDRD,PD5);
    SET_BIT(DDRB,PB7);
    SET_BIT(DDRB,PB6);

    SET_BIT(DDRB,PB3);
    SET_BIT(DDRB,PB2);
    SET_BIT(DDRB,PB1);
    SET_BIT(DDRB,PB0);
}
