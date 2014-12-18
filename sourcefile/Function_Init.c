#include <msp430.h>
#include "MacroDefination.h"
#include "FunctionDeclaration.h"
#include "VariableDefination.h"

void init_watchdog(void)
{
	WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
}

void init_clock(void)
{
	DCOCTL = 0x00;                          // Set DCOCLK to 12MHz
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
}

void init_port(void)
{
    OLED = 0x00;			//P1用作OLED控制
    OLEDDIR |=LED0+OLED_RST+OLED_DC;
    OLEDSEL  = SPISOMI+SPISIMO+SPICLK;
    OLEDSEL2= SPISOMI+SPISIMO+SPICLK;
}

void init_spi(void)
{
#ifdef _UCA0SPI_
	UCA0CTL1 |=UCSWRST;
	UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCMODE_0 + UCSYNC;  // 3-pin, 8-bit SPI master
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK作为
	UCA0BR0 |= 0x02;                          // /2
	UCA0BR1 = 0;                              //
	UCA0MCTL = 0;                             // No modulation
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI0 RX interrupt
	IE2 |= UCA0TXIE;
#endif

#ifdef _UCB0SPI_
	UCB0CTL1 |=UCSWRST;			//Enable SW reset
	UCB0CTL0 |= UCCKPL + UCMSB + UCMST + UCMODE_0 + UCSYNC;  // 3-pin, 8-bit SPI master
	UCB0CTL1 |= UCSSEL_2 + UCSWRST;                     // SMCLK作为外围设备时钟
	UCB0BR0 |= 0x02;                          // /2
	UCB0BR1 = 0;                              //
//	UCB0MCTL = 0;                             // No modulation
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCB0RXIE;                          // Enable USCI0 RX interrupt
#endif
}


