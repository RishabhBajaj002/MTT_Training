


#include "tm4c123gh6pge.h"
#include <stdint.h>
#include <delaym4.h>
#include <80Mhz.h>

int main(void)
{
    //System80Mhz();                                   //Calling function to begin running at 80MHz
    SYSCTL_RCGCGPIO_R|=0x1280;                         //Enable clock to GPIO port H, K, N
    SYSCTL_RCGCPWM_R |= 0x01;                        //Clock provided to PWM Module 0
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
    while(1){                                        //While loop to prevent program from terminating as GPIO pins return to original state after termination
    }
    return 0;
}
