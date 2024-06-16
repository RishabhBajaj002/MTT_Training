/**   Code to transmit data from TM4C to RealTerm using UART Module 4
      Port J0-U4Rx(receive),  J1-U4Tx(transmit)                          **/
//System clock is at 80MHz
//Value for baud rate: 43.40277,     Integer part: 43,    Fractional part: 5

#include "tm4c123gh6pge.h"
#include <stdint.h>
#include <delaym4.h>
#include <80Mhz.h>
int data;
int sender;
int main(void)
{
    System80Mhz();                          //System running at 80MHz
    SYSCTL_RCGCUART_R |= 0x10;              //Providing clock to uart module 4
    SYSCTL_RCGCGPIO_R |= 0x100;              //Providing clock to port J
    GPIO_PORTJ_DIR_R |= 0x02;               //Pin 1(Tx) is output and 0(Rx) is input
    GPIO_PORTJ_DEN_R |= 0x03;               //Digital data enabled for pin 0,1
    GPIO_PORTJ_AFSEL_R |= 0x03;             //Port J pin 0,1 serve as Alternate Function
    GPIO_PORTJ_PCTL_R |= 0x11;              //Port J pin 0,1 serve as U4Rx and U4Tx
    UART4_CTL_R &= 0x00;                    //Disabling UART before programming
    UART4_CTL_R |= 0x300;                   //Enabling TX and RX
    UART4_IBRD_R |= 0x2B;                   //Setting values for 115200 baud rate
    UART4_FBRD_R |= 0x1A;
    UART4_LCRH_R |= 0x70;                   //Data frame of (0x60)8-N-1 and FIFO enable(0x10)
    UART4_CC_R &= 0x00;                     //System clock serves as clock for UART
    UART4_CTL_R |= 0x01;                    //Enabling UART module

    while(1)
    {
        //if((UART2_DR_R&0xFF) != 0x00)
        data = UART4_DR_R & 0xFF;
        //UART2_DR_R &= 0x00;
        //delay(10);
    }
    return 0;



}
