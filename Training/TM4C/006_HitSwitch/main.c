/**   Hit Switch to Control Led: Pressed = ON, Release = OFF   **/
#include "tm4c123gh6pge.h"
#include <stdint.h>

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0x0F;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTG_PDR_R |= 0xF0;

    while(1)
    {
        if(GPIO_PORTG_DATA_R==0x80)
        {
            GPIO_PORTG_DATA_R |= 0x08;
        }
        else
        {
            GPIO_PORTG_DATA_R &= 0xF0;
        }
    }
	return 0;
}
