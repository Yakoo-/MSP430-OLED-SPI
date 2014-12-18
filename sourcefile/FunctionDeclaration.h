#ifndef	_FUNCTIONDECLARATION_H_
#define	_FUNCTIONDECLARATION_H_

//Function_Init.c
void init_watchdog(void);
void init_clock(void);
void init_port(void);
void init_spi(void);

//Function_User.c
void SPI_Send_Byte(uchar8);
void Figure_Main(void);
void Delay_ms(uint16);

//Function_Driver_OLED.c
void OLED_WrDat(uchar8 ucData);		//д����
void OLED_WrCmd(uchar8 ucCmd);	//дָ��
void OLED_SetPos(uchar8 ucIdxX, uchar8 ucIdxY);		//��������
void OLED_Fill(uchar8 data);		//ȫ������ͬһ�ַ�
void OLED_Init(void);	//OLED��ʼ��
void OLED_P6x8Char(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucData);
void OLED_P6x8Str(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucDataStr[]);
void OLED_P8x16Str(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucDataStr[]);
void SetStartColumn(uchar8 ucData);
void SetAddressingMode(uchar8 ucData);
void SetColumnAddress(uchar8 a, uchar8 b);
void SetPageAddress(uchar8 a, uchar8 b);
void SetStartLine(uchar8 d);
void SetContrastControl(uchar8 d);
void SetChargePump(uchar8 d);
void SetSegmentRemap(uchar8 d);
void SetEntireDisplay(uchar8 d);
void SetInverseDisplay(uchar8 d);
void SetMultiplexRatio(uchar8 d);
void SetDisplayOnOff(uchar8 d);
void SetStartPage(uchar8 d);
void SetCommonRemap(uchar8 d);
void SetDisplayOffset(uchar8 d);
void SetDisplayClock(uchar8 d);
void SetPrechargePeriod(uchar8 d);
void SetCommonConfig(uchar8 d);
void SetVCOMH(uchar8 d);
void SetNop(void);


#endif
