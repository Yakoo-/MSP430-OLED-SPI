/*               G    电源地
               VCC  接5V或3.3v电源
               UCA0：									UCB0：
               D0   P1.4（SCLK）				P1.5 SCLK
               D1   P1.2（MOSI）				P1.7 MOSI
               RST  P1.5								P1.4
               DC   P1.3								P1.3
               CS   默认选中，可不接
**/

#include <msp430.h>
#include "MacroDefination.h"
#include "FunctionDeclaration.h"
#include "VariableDefination.h"


void main(void)
{
	init_watchdog();
	init_clock();
	init_port();
	init_spi();
	OLED_Init();
    LED_ON;
	Figure_Main();
	while(1)
		{
			Delay_ms(1000);
			LED_OFF;
			Delay_ms(1000);
			LED_ON;
		}
}
