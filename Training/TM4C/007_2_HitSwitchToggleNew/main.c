/**   Toggles Led using hit switch with smart delay, remaining code is unaffected. Input is positive edge triggered   **/
#include "tm4c123gh6pge.h"                                  //Including main headers
#include <stdint.h>
int oldState, currState, timeCount;                         //Declaring global variables, current and old state describe input state

int main(void)
{
    SYSCTL_RCGCGPIO_R |= 0x40;                              //Initializing register states as i/p and o/p and enabling digital values
    GPIO_PORTG_DIR_R |= 0x0F;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTG_PDR_R |= 0xF0;                               //Setting pull-down resistors to input values
    oldState = 0;                                           //Setting old state as 0 initially, because no input is given
    timeCount = 1000;                                       //Decides how much smart delay

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
            GPIO_PORTG_DATA_R ^= 0x01;                      //Change state of led using XOR, low->high or high->low
        }
        oldState=currState;                                 //Makes the old state current one after toggle->wont toggle until next rising edge
        timeCount++;                                        //Increments timeCount in main code, it will run continuously and wont check i/p until limit

        //Any code here will run with every iteration of while(1) loop and wont stop or be skipped even in case of checking i/p or toggle
    }
    return 0;
}
