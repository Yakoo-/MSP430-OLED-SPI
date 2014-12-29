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

//Delay函数
void Delay_ms(uint16 ms)
{
	uint16 i,j;
	for( i=0;i<ms;i++)
		for(j=0;j<142;j++); //8MHz晶振时  }
}
