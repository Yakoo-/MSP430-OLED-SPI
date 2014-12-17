#include <msp430.h>
#include "MacroDefination.h"
#include "FunctionDeclaration.h"
#include "VariableDefination.h"

//SPI 发送程序
void SPI_Send_Byte(uchar8 data)
{
	while (!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = data;
	while (!(IFG2 & UCA0TXIFG));
}
//OLED主界面
void Figure_Main(void)
{
	OLED_P8x16Str(0, 0, (uchar8*)"Hello! Yakoo~");
	OLED_P8x16Str(0, 1, (uchar8*)"Hello! Yakoo~");
	OLED_P8x16Str(0, 2, (uchar8*)"Hello! Yakoo~");
	OLED_P8x16Str(0, 3, (uchar8*)"Hello! Yakoo~");
}
