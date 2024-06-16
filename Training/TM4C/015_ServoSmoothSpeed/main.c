
#include "tm4c123gh6pge.h"
#include <stdint.h>
int i;
int val;
int timer;
int servoTimer;
int ctr = 0;
int temp;
int main(void)
{
    SYSCTL_RCGCGPIO_R|=0x40;                         //Enable clock to GPIO port G
    SYSCTL_RCGCPWM_R |= 0x02;                        //Clock provided to PWM Module 1;
    SYSCTL_RCC_R |= 0x140000;                       //Enable PWMDIV and Divide it by 8 to get 250KHz
    GPIO_PORTG_DIR_R |= 0xFF;                        //Port G enabled for output
    GPIO_PORTG_DEN_R |= 0xFF;                        //Digital data for Port G enabled
    GPIO_PORTG_AFSEL_R |= 0x04;                      //Port G pin 2 functions as AFSEL(Alternate Function Select)
    GPIO_PORTG_PCTL_R|=0x500;                        //Register to provide AFSEL. Writing 5 in pin 2 fields enables it as M1PWM0
    PWM1_ENABLE_R |= 0xFF;                           //Setting 1 allows to PWM to pass to respective port. 1 in 0th bit enables M1PWM0
    PWM1_0_LOAD_R |= 0x2F5;                           //Value for 330Hz
    PWM1_0_GENA_R |= 0x8C;                           //Written to go high on load, low on compare A down match(8C for high on load, low on A match down)
    PWM1_0_CTL_R |= 0x01;                            //For Module 1, Gen 0, Count Down method and Block enable is specified
    while(1)
    {
        PWM1_0_CMPA_R &= 0x00;
        PWM1_0_CMPA_R |= 0x80;                          //Value for 83% duty cycle, 180 degrees
        delay(2000000);
        for(servoTimer = 10; servoTimer>0; servoTimer--)
        {
            PWM1_0_CMPA_R += 0xA;
            delay((4000*servoTimer));
        }
        PWM1_0_CMPA_R &= 0x00;
        PWM1_0_CMPA_R |= 0x230;
        delay(10);
        PWM1_0_CMPA_R &= 0x00;
        PWM1_0_CMPA_R |= 0x170;

        for(servoTimer = 1; servoTimer<10; servoTimer++)
        {
            PWM1_0_CMPA_R += 0xA;
            delay((15000*servoTimer));
        }
    delay(2000000);
    }
}

void delay(int timer)
{
    for(i = 0; i<timer; i++);
}
