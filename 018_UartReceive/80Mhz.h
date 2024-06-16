/*-----------------------------------------------------------------------------------------------------------------------*/
/*                                             																			 */
/*                                                                                                                       */
/*                                            																		     */
/*																														 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*      MIT   TECH   TEAM  ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> M4 Cortex Library (80Mhz.h)              			     */												   
/*                                     29/11/2014      																	 */
/*                                            																			 */
/*                                            																	         */
/*                                            																			 */
/*                                            																			 */
/*                                            																		     */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*                                            																			 */
/*-----------------------------------------------------------------------------------------------------------------------*/
#define true 1
#define false 0

void System80Mhz()
{
	/*
SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
delay(10000);
SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
delay(10000);
SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
delay(10000);
SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
delay(10000);
SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
delay(10000);
SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
delay(10000);
SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
delay(10000);
SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
delay(10000);
SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (4<<22);      // configure for 80 MHz clock
delay(10000);
while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
delay(10000);
SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
delay(10000);
SYSCTL_SYSPROP_R = SYSCTL_SYSPROP_FPU;

NVIC_EN0_R=0x00;
NVIC_EN1_R=0x00;
NVIC_EN2_R=0x00;
NVIC_EN3_R=0x00;*/
	 // 0) configure the system to use RCC2 for advanced features
	  //    such as 400 MHz PLL and non-integer System Clock Divisor
	  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
	  delay(1000);
	  // 1) bypass PLL while initializing
	  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
	  delay(1000);
	  // 2) select the crystal value and oscillator source
	  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
	  delay(1000);
	  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
	  delay(1000);
	  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
	  delay(1000);
	  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
	  delay(1000);
	  // 3) activate PLL by clearing PWRDN
	  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
	  delay(1000);
	  // 4) set the desired system divider and the system divider least significant bit
	  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
	  delay(1000);
	  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
	                  + (4<<22);      // configure for 80 MHz clock
	  // 5) wait for the PLL to lock by polling PLLLRIS
	  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){

	};
	  // 6) enable use of PLL by clearing BYPASS
	  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
	  delay(1000);
	  NVIC_EN0_R=0x00;
	  NVIC_EN1_R=0x00;
	  NVIC_EN2_R=0x00;
	  NVIC_EN3_R=0x00;
	  delay(1000);
	  	delay(1000);
}
