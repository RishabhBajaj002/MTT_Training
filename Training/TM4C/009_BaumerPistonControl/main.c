/*   Taking Input from Baumer to Control Piston   */
#include "tm4c123gh6pge.h"
#include <stdint.h>

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x0800;
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0xFF;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTM_DEN_R |= 0xFF;
    GPIO_PORTM_DIR_R |= 0x0F;

    while(1)
    {
        if(((~GPIO_PORTM_DATA_R)&0x80)==0x80)
        {
            GPIO_PORTM_DATA_R |= 0x08;
            GPIO_PORTG_DATA_R |= 0x0F;
        }
        else
        {
            GPIO_PORTM_DATA_R &= 0xF0;
            GPIO_PORTG_DATA_R &= 0x00;
        }
    }
	return 0;
}
