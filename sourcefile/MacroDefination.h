#ifndef _MACRODEFINATION_H_
#define _MACRODEFINATION_H_

#define _UCA0SPI_			//ѡ��SPIͨ��ģ��

//��������
#define uchar8 			unsigned char
#define uint16 			unsigned int
#define ushort16		unsigned short
#define ulong32		unsigned long int
#define ulong64		unsigned long long int
#define long32			long int
#define long64			long long int

//SPI�ܽŶ��� (UCA0)
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

//OLED�ܽŶ���
#define OLED				P1OUT //SPI ���ö˿� P1
#define OLEDDIR		P1DIR
#define LED0				BIT0		//P1.0	�����ķ��������	����Ϊ���
#define OLEDSEL		P1SEL
#define OLEDSEL2		P1SEL2

#ifdef _UCA0SPI_
	#define OLED_SCL 	SPICLK		//P1.4	�������ʱ��
	#define OLED_SDA 	SPISIMO	//P1.2	�����������
	#define OLED_RST 	BIT5		//P1.5	��λ ����Ϊ���
	#define OLED_DC 		BIT3		//P1.3	�����������/����	����Ϊ���
#endif

#ifdef _UCB0SPI_
	#define OLED_SCL 	SPICLK		//P1.5	�������ʱ��
	#define OLED_SDA 	SPISIMO	//P1.7	�����������
	#define OLED_RST 	BIT4		//P1.4	��λ ����Ϊ���
	#define OLED_DC 		BIT3		//P1.3	�����������/����	����Ϊ���
#endif

//OLED��������
#define OLED_IMAGE_WHITE		1
#define OLED_IMAGE_BLACK		0
#define OLED_MAX_ROW      		64
#define OLED_MAX_COLUMN  	128

//LED ����
#define LED_ON 		{OLED |=LED0;}
#define LED_OFF		{OLED &=~LED0;}

#endif
