/**   Code to transmit data from TM4C to RealTerm using UART Module 2
      Port G4-U2Rx(receive),  G5-U2Tx(transmit)                          **/
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
    SYSCTL_RCGCUART_R |= 0x04;              //Providing clock to uart module 2
    SYSCTL_RCGCGPIO_R |= 0x40;              //Providing clock to port g
    GPIO_PORTG_DIR_R |= 0x20;               //Pin 5(Tx) is output and 4(Rx) is input
    GPIO_PORTG_DEN_R |= 0x30;               //Digital data enabled for pin 4,5
    GPIO_PORTG_AFSEL_R |= 0x30;             //Port G pin 4,5 serve as Alternate Function
    GPIO_PORTG_PCTL_R |= 0x110000;          //Port G pin 4,5 serve as U2Rx and U2Tx
    UART2_CTL_R &= 0x00;                    //Disabling UART before programming
    UART2_CTL_R |= 0x300;                   //Enabling TX and RX
    UART2_IBRD_R |= 0x2B;                   //Setting values for 115200 baud rate
    UART2_FBRD_R |= 0x1A;
    UART2_LCRH_R |= 0x70;                   //Data frame of (0x60)8-N-1 and FIFO enable(0x10)
    UART2_CC_R &= 0x00;                     //System clock serves as clock for UART
    UART2_CTL_R |= 0x01;                    //Enabling UART module

    while(1)
    {
        UART2_DR_R |= 0x05;
        delay(1000);
    }
	return 0;
}
