/**   LED Blink Pattern from one direction   **/
#include "tm4c123gh6pge.h"
#include <stdint.h>
volatile long timer;
volatile int i;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0xFF;
    GPIO_PORTG_DEN_R |= 0xFF;

    while(1)
    {
        GPIO_PORTG_DATA_R |= 0x01;
        for(i=0; i<8; i++)
        {
            delay(1000000);
            GPIO_PORTG_DATA_R = (GPIO_PORTG_DATA_R<<1);
        }
    }

    return 0;
}

void delay(int delayTime)
{
    for(timer=0; timer<delayTime; timer++);
}
