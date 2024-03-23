#include "tm4c123gh6pge.h"
#include <stdint.h>
volatile long timer;
int regOld, regCurrent;
int state, firstToggle;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0x0F;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTG_PDR_R |= 0xF0;
    regOld = 0x00;

    while(1)
    {
        regCurrent = GPIO_PORTG_DATA_R;
        if(((regOld|0x01)==0x01) && (regCurrent|0x01==0x81))
        {
            GPIO_PORTG_DATA_R ^= 0x01;
            regOld = regCurrent;
        }
        else if ((GPIO_PORTG_DATA_R|0x01)==0x01)
        {
            regOld = 0x00;
        }
        delay(700);
    }
    return 0;
}

void delay(int delayTime)
{
    for(timer=0; timer<delayTime; timer++);
}
