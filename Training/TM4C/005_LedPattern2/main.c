/**   LED Blinking in Pattern from both sides end to middle   **/
#include "tm4c123gh6pge.h"
#include <stdint.h>
volatile long timer;
volatile int i;
volatile long right, left;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0xFF;
    GPIO_PORTG_DEN_R |= 0xFF;
    right = 0x01;
    left = 0x80;

    /**
    while(1)
    {
        for(i=0; i<7; i++)
        {
            GPIO_PORTG_DATA_R = (GPIO_PORTG_DATA_R&=0x00) + GPIO_PORTG_DATA_R+(1<<i)+(1<<(7-i));
            delay(1000000);
        }
    }
    **/
    GPIO_PORTG_DATA_R &= 0x00;
    while(1)
    {
        for(i = 0; i<7; i++)
        {
            GPIO_PORTG_DATA_R = (right<<i) + (left>>i);
            delay(5000000);
        }
    }
    return 0;
}

void delay(int delayTime)
{
    for(timer=0; timer<delayTime; timer++);
}
