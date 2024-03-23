/**   Hit Switch to Toggle Led on each press   **/
#include "tm4c123gh6pge.h"
#include <stdint.h>
volatile long timer;
int regOld, regNew;
int state;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTG_DIR_R |= 0x0F;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTG_PDR_R |= 0xF0;
    regOld = 0x00;
    state = 0;

    while(1)
    {
        regNew = GPIO_PORTG_DATA_R;
        delay(1300);
        if(((regOld|0x01)==0x01) && ((regNew|0x01)==0x81))
        {
            if(state==0)
            {
                GPIO_PORTG_DATA_R |= 0x01;
                state = 1;
            }
            else
            {
                GPIO_PORTG_DATA_R &= 0xF0;
                state = 0;
            }
            regOld = regNew;
        }
        else if((GPIO_PORTG_DATA_R|0x01)==0x01)
        {
            regOld = 0x00;
        }
    }
    return 0;
}

void delay(int delayTime)
{
    for(timer=0; timer<delayTime; timer++);
}


