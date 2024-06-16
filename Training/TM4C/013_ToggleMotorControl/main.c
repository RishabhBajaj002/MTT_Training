

#include "tm4c123gh6pge.h"
#include <stdint.h>
#include <delaym4.h>
#include <80Mhz.h>
int oldState, currState, timeCount;

int main(void)
{
    //System80Mhz();                                   //Calling function to begin running at 80MHz
    SYSCTL_RCGCGPIO_R|=0x12C0;                         //Enable clock to GPIO port H, K, N
    SYSCTL_RCGCPWM_R |= 0x01;                        //Clock provided to PWM Module 0
    GPIO_PORTG_DIR_R |= 0x0F;
    GPIO_PORTG_DEN_R |= 0xFF;
    GPIO_PORTG_PDR_R |= 0xF0;
    GPIO_PORTH_DIR_R |= 0xFF;                        //Port H enabled for output
    GPIO_PORTK_DIR_R |= 0xFF;
    GPIO_PORTN_DIR_R |= 0xFF;
    GPIO_PORTH_DEN_R |= 0xFF;                        //Digital data for Port G enabled
    GPIO_PORTK_DEN_R |= 0xFF;
    GPIO_PORTN_DEN_R |= 0xFF;
    GPIO_PORTN_DATA_R |= 0x00;
    GPIO_PORTK_DATA_R &= 0x00;
    GPIO_PORTH_AFSEL_R |= 0x80;                      //Port H pin 7 functions as AFSEL(Alternate Function Select)
    GPIO_PORTH_PCTL_R|=0x40000000;                   //Register to provide AFSEL. Writing 4 in pin 7 fields enables it as M0PWM7
    PWM0_ENABLE_R |= 0xFF;                           //Setting 1 allows to PWM to pass to respective port. 1 in 0th bit enables M0PWM7
    PWM0_3_LOAD_R |= 0x18F;                          //Value of 399(18F) is loaded
    PWM0_3_CMPA_R |= 0x63;                           //Compare A value of 199(C7) is loaded
    PWM0_3_GENB_R |= 0x8C;                           //Written to go high on load, low on compare A down match(8C for high on load, low on A match down)
    PWM0_3_CTL_R |= 0x01;                            //For Module 0, Gen 3, Count Down method and Block enable is specified
    oldState = 0;                                           //Setting old state as 0 initially, because no input is given
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
                GPIO_PORTK_DATA_R ^= 0x08;                      //Change state of led using XOR, low->high or high->low
                GPIO_PORTG_DATA_R ^= 0x01;
            }
            oldState=currState;                                 //Makes the old state current one after toggle->wont toggle until next rising edge
            timeCount++;                                        //Increments timeCount in main code, it will run continuously and wont check i/p until limit

            //Any code here will run with every iteration of while(1) loop and wont stop or be skipped even in case of checking i/p or toggle
        }
    return 0;
}
