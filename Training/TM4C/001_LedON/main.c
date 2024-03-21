/**     LED BLINK CODE     **/
#include "tm4c123gh6pge.h"
#include <stdint.h>
volatile long i;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0xFF;
    GPIO_PORTG_DEN_R |= 0xFF;

    while(1)
    {
        GPIO_PORTG_DATA_R &= 0x00;
        delay(1000000);
        GPIO_PORTG_DATA_R |= 0xFF;
        delay(1000000);
    }
	return 0;
}

void delay(int delayTime)
{
    for(i=0; i<delayTime; i++);
}
