/**   LED Blinking in Pattern start from middle to ends   **/
#include "tm4c123gh6pge.h"
#include <stdint.h>
volatile long timer;
volatile int i;
volatile int midleft, midright;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0xFF;
    GPIO_PORTG_DEN_R |= 0xFF;

    midleft = 0x10;
    midright = 0x08;
    while(1)
    {
        for(i=0; i<3; i++)
        {
            GPIO_PORTG_DATA_R = (midleft<<i)+(midright>>i);
            delay(1000000);
        }
        for(i=3; i>0; i--)
        {
            GPIO_PORTG_DATA_R = (midleft<<i)+(midright>>i);
            delay(1000000);
        }
    }
    return 0;
}

void delay(int delayTime)
{
    for(timer=0; timer<delayTime; timer++);
}
