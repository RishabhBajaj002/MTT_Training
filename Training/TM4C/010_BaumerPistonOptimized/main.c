/*   Taking Input from Baumer to Control Piston   */
#include "tm4c123gh6pge.h"
#include <stdint.h>

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x0800;
    GPIO_PORTM_DEN_R |= 0xFF;
    GPIO_PORTM_DIR_R |= 0x0F;

    while(1)
    {
        GPIO_PORTM_DIR_R = ((~GPIO_PORTM_DIR_R)>>4);
    }
    return 0;
}
