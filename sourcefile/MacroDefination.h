#ifndef _MACRODEFINATION_H_
#define _MACRODEFINATION_H_

#define _UCA0SPI_			//选择SPI通信模块

//数据类型
#define uchar8 			unsigned char
#define uint16 			unsigned int
#define ushort16		unsigned short
#define ulong32		unsigned long int
#define ulong64		unsigned long long int
#define long32			long int
#define long64			long long int

//SPI管脚定义 (UCA0)
#ifdef _UCA0SPI_
	#define SPISOMI		BIT1		//Data In
	#define SPISIMO		BIT2		//Data Out
	#define SPICLK			BIT4		//Serial Clock Out
#endif

#ifdef _UCB0SPI_
	#define SPISOMI 		BIT6		//Data In
	#define SPISIMO		BIT7		//Data Out
	#define SPICLK			BIT5		//Serial Clock Out
#endif

//OLED管脚定义
#define OLED				P1OUT //SPI 复用端口 P1
#define OLEDDIR		P1DIR
#define LED0				BIT0		//P1.0	单独的发光二极管	设置为输出
#define OLEDSEL		P1SEL
#define OLEDSEL2		P1SEL2

#ifdef _UCA0SPI_
	#define OLED_SCL 	SPICLK		//P1.4	串行输出时钟
	#define OLED_SDA 	SPISIMO	//P1.2	串行输出数据
	#define OLED_RST 	BIT5		//P1.5	复位 设置为输出
	#define OLED_DC 		BIT3		//P1.3	控制输出数据/命令	设置为输出
#endif

#ifdef _UCB0SPI_
	#define OLED_SCL 	SPICLK		//P1.5	串行输出时钟
	#define OLED_SDA 	SPISIMO	//P1.7	串行输出数据
	#define OLED_RST 	BIT4		//P1.4	复位 设置为输出
	#define OLED_DC 		BIT3		//P1.3	控制输出数据/命令	设置为输出
#endif

//OLED常量定义
#define OLED_IMAGE_WHITE		1
#define OLED_IMAGE_BLACK		0
#define OLED_MAX_ROW      		64
#define OLED_MAX_COLUMN  	128

//LED 操作
#define LED_ON 		{OLED |=LED0;}
#define LED_OFF		{OLED &=~LED0;}

#endif
