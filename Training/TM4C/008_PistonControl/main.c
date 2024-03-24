/**   Controlling Piston Board using MCM   **/
#include "tm4c123gh6pge.h"
#include <stdint.h>
int oldState, currState, timeCount;

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x0800;
    SYSCTL_RCGCGPIO_R |= 0x40;
    GPIO_PORTM_DIR_R |= 0xFF;
    GPIO_PORTM_DEN_R |= 0xFF;
    GPIO_PORTM_PDR_R |= 0xFF;
    GPIO_PORTG_DIR_R |= 0x0F;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTG_PDR_R |= 0xF0;
    oldState = 0;
    timeCount = 1000;

    while(1)
    {
        if(timeCount==1000)                                 //Only checks for input state change periodically, lets other code run
        {
            if((GPIO_PORTG_DATA_R&0x80)==0x80)              //If GPIO 7th bit is high -> input is given
                currState = 1;                              //Sets current state of input as high
            else
                currState = 0;                              //Otherwise sets current state as low -> no input has been given
            timeCount=0;                                    //After checking for input, resets counter and wont check until counter reaches limit(1000)
        }

        if((oldState==0) && (currState==1))                 //If old state was low(no press) and current state is high(pressed)
        {
            GPIO_PORTM_DATA_R ^= 0xFF;                      //Change state of led using XOR, low->high or high->low
        }
        oldState=currState;                                 //Makes the old state current one after toggle->wont toggle until next rising edge
        timeCount++;
    }
    return 0;
}


