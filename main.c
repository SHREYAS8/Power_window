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
    cont.lock = 0;
    cont.up_p = 0;
    cont.down_p = 0;
    cont.up_d = 0;
    cont.down_d = 0;

    while(1)
    {
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

        if(PIND & (1<<PD7))
            cont.up_d = 1;
        else
            cont.up_d = 0;

        if(PINB & (1<<PB0))
            cont.down_d = 1;
        else
            cont.down_d = 0;

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
    return 0;
}

void config_switch()
{
    CLR_BIT(DDRC,PC5);  // Child Lock
    CLR_BIT(DDRD,PD7);  // window driver up/ down
    CLR_BIT(DDRD,PB0);
    CLR_BIT(DDRD,PD0);  // window passenger up/ down
    CLR_BIT(DDRD,PD1);
}

void config_Stepper()
{
    SET_BIT(DDRC,PC4);  // Setting pins as output for stepper motor
    SET_BIT(DDRC,PC3);
    SET_BIT(DDRC,PC2);
    SET_BIT(DDRC,PC1);

    SET_BIT(DDRB,PB4);
    SET_BIT(DDRB,PB3);
    SET_BIT(DDRB,PB2);
    SET_BIT(DDRB,PB1);
}
