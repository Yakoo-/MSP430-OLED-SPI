#include <msp430.h>
#include "MacroDefination.h"
#include "FunctionDeclaration.h"
#include "VariableDefination.h"

extern const uchar8 Font_6x8[][6];
extern const uchar8 Font_8x16[];

//OLEDд����
void OLED_WrDat(uchar8 Data)
{
    OLED  |= OLED_DC;
    SPI_Send_Byte(Data);
}

//OLEDд����
void OLED_WrCmd(uchar8 Cmd)
{
    OLED &= ~OLED_DC;
    SPI_Send_Byte(Cmd);
}


/*****************************************************************************
 �� �� ��  : OLED_SetPos
 ��������  : ��������
 �������  : uchar8 ucIdxX
             uchar8 ucIdxY
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
void OLED_SetPos(uchar8 ucIdxX, uchar8 ucIdxY)
{
    OLED_WrCmd(0xb0 + ucIdxY);
    OLED_WrCmd(((ucIdxX & 0xf0) >> 4) | 0x10);
    OLED_WrCmd((ucIdxX & 0x0f) | 0x00);
}

/*****************************************************************************
 �� �� ��  : OLED_Fill
 ��������  : ��ȫ��д��ͬһ���ַ�����
             �� OLED_Fill(0x01);    ����ĳһλ0Ϊ���� 1Ϊ��
            ------------------------------------------------------
                                ��128��
					1				1				1
              ��  	0				0                0
              8   	0           0                0
              ��  	0     ����0     ��������   0
              ��  	0           0                0
              ��  	0           0                0
              ��  	0           0                0
              8   	0           0                0
              ҳ  	1           1                1
              64  0           0                0
              ��  	.			.                .
					.           .    ��������    .
					.           .                .
					.           .                .
					0           0                0
            ------------------------------------------------------
 �������  : uchar8 ucData
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
void OLED_Fill(uchar8 ucData)
{
    uchar8 ucPage,ucColumn;

    for(ucPage = 0; ucPage < 8; ucPage++)
    {
        OLED_WrCmd(0xb0 + ucPage);  //0xb0+0~7��ʾҳ0~7
        OLED_WrCmd(0x00);           //0x00+0~16��ʾ��128�зֳ�16�����ַ��ĳ���еĵڼ���
        OLED_WrCmd(0x10);           //0x10+0~16��ʾ��128�зֳ�16�����ַ���ڵڼ���
        for(ucColumn = 0; ucColumn < 128; ucColumn++)
        {
            OLED_WrDat(ucData);
        }
    }
}

void SetStartColumn(uchar8 ucData)
{
    OLED_WrCmd(0x00+ucData % 16);   // Set Lower Column Start Address for Page Addressing Mode
                                   // Default => 0x00
    OLED_WrCmd(0x10+ucData / 16);   // Set Higher Column Start Address for Page Addressing Mode
                                   // Default => 0x10
}

void SetAddressingMode(uchar8 ucData)
{
    OLED_WrCmd(0x20);        // Set Memory Addressing Mode
    OLED_WrCmd(ucData);      // Default => 0x02
                            // 0x00 => Horizontal Addressing Mode
                            // 0x01 => Vertical Addressing Mode
                            // 0x02 => Page Addressing Mode
}

void SetColumnAddress(uchar8 a, uchar8 b)
{
    OLED_WrCmd(0x21);        // Set Column Address
    OLED_WrCmd(a);           // Default => 0x00 (Column Start Address)
    OLED_WrCmd(b);           // Default => 0x7F (Column End Address)
}

void SetPageAddress(uchar8 a, uchar8 b)
{
    OLED_WrCmd(0x22);        // Set Page Address
    OLED_WrCmd(a);           // Default => 0x00 (Page Start Address)
    OLED_WrCmd(b);           // Default => 0x07 (Page End Address)
}

void SetStartLine(uchar8 ucData)
{
    OLED_WrCmd(0x40|ucData); // Set Display Start Line
                            // Default => 0x40 (0x00)
}

void SetContrastControl(uchar8 ucData)
{
    OLED_WrCmd(0x81);        // Set Contrast Control
    OLED_WrCmd(ucData);      // Default => 0x7F
}

void SetChargePump(uchar8 ucData)
{
    OLED_WrCmd(0x8D);        // Set Charge Pump
    OLED_WrCmd(0x10|ucData); // Default => 0x10
                            // 0x10 (0x00) => Disable Charge Pump
                            // 0x14 (0x04) => Enable Charge Pump
}

void SetSegmentRemap(uchar8 ucData)
{
    OLED_WrCmd(0xA0|ucData); // Set Segment Re-Map
                            // Default => 0xA0
                            // 0xA0 (0x00) => Column Address 0 Mapped to SEG0
                            // 0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

void SetEntireDisplay(uchar8 ucData)
{
    OLED_WrCmd(0xA4|ucData); // Set Entire Display On / Off
                            // Default => 0xA4
                            // 0xA4 (0x00) => Normal Display
                            // 0xA5 (0x01) => Entire Display On
}

void SetInverseDisplay(uchar8 ucData)
{
    OLED_WrCmd(0xA6|ucData); // Set Inverse Display On/Off
                            // Default => 0xA6
                            // 0xA6 (0x00) => Normal Display
                            // 0xA7 (0x01) => Inverse Display On
}

void SetMultiplexRatio(uchar8 ucData)
{
    OLED_WrCmd(0xA8);        // Set Multiplex Ratio
    OLED_WrCmd(ucData);      // Default => 0x3F (1/64 Duty)
}

void SetDisplayOnOff(uchar8 ucData)
{
    OLED_WrCmd(0xAE|ucData); // Set Display On/Off
                            // Default => 0xAE
                            // 0xAE (0x00) => Display Off
                            // 0xAF (0x01) => Display On
}

void SetStartPage(uchar8 ucData)
{
    OLED_WrCmd(0xB0|ucData); // Set Page Start Address for Page Addressing Mode
                            // Default => 0xB0 (0x00)
}

void SetCommonRemap(uchar8 ucData)
{
    OLED_WrCmd(0xC0|ucData); // Set COM Output Scan Direction
                            // Default => 0xC0
                            // 0xC0 (0x00) => Scan from COM0 to 63
                            // 0xC8 (0x08) => Scan from COM63 to 0
}

void SetDisplayOffset(uchar8 ucData)
{
    OLED_WrCmd(0xD3);        // Set Display Offset
    OLED_WrCmd(ucData);      // Default => 0x00
}

void SetDisplayClock(uchar8 ucData)
{
    OLED_WrCmd(0xD5);        // Set Display Clock Divide Ratio / Oscillator Frequency
    OLED_WrCmd(ucData);      // Default => 0x80
                            // D[3:0] => Display Clock Divider
                            // D[7:4] => Oscillator Frequency
}

void SetPrechargePeriod(uchar8 ucData)
{
    OLED_WrCmd(0xD9);        // Set Pre-Charge Period
    OLED_WrCmd(ucData);      // Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
                            // D[3:0] => Phase 1 Period in 1~15 Display Clocks
                            // D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

void SetCommonConfig(uchar8 ucData)
{
    OLED_WrCmd(0xDA);        // Set COM Pins Hardware Configuration
    OLED_WrCmd(0x02|ucData); // Default => 0x12 (0x10)
                            // Alternative COM Pin Configuration
                            // Disable COM Left/Right Re-Map
}

void SetVCOMH(uchar8 ucData)
{
    OLED_WrCmd(0xDB);        // Set VCOMH Deselect Level
    OLED_WrCmd(ucData);      // Default => 0x20 (0.77*VCC)
}

void SetNop(void)
{
    OLED_WrCmd(0xE3);        // Command for No Operation
}

/*****************************************************************************
 �� �� ��  : OLED_Init
 ��������  : OOLED��ʼ��
 �������  : void
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
void OLED_Init(void)
{
    uchar8 i;

    OLED |=OLED_SCL;
    OLED &=~OLED_RST;

    for(i = 0; i < 100; i++)
    {
        _nop();            //���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���
    }

    OLED |=OLED_RST;

    SetDisplayOnOff(0x00);     // Display Off (0x00/0x01)
    SetDisplayClock(0x80);     // Set Clock as 100 Frames/Sec
    SetMultiplexRatio(0x3F);   // 1/64 Duty (0x0F~0x3F)
    SetDisplayOffset(0x00);    // Shift Mapping RAM Counter (0x00~0x3F)
    SetStartLine(0x00);        // Set Mapping RAM Display Start Line (0x00~0x3F)
    SetChargePump(0x04);       // Enable Embedded DC/DC Converter (0x00/0x04)
    SetAddressingMode(0x02);   // Set Page Addressing Mode (0x00/0x01/0x02)
    SetSegmentRemap(0x01);     // Set SEG/Column Mapping     0x00���ҷ��� 0x01����
    SetCommonRemap(0x08);      // Set COM/Row Scan Direction 0x00���·��� 0x08����
    SetCommonConfig(0x10);     // Set Sequential Configuration (0x00/0x10)
    SetContrastControl(0xCF);  // Set SEG Output Current
    SetPrechargePeriod(0xF1);  // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    SetVCOMH(0x40);            // Set VCOM Deselect Level
    SetEntireDisplay(0x00);    // Disable Entire Display On (0x00/0x01)
    SetInverseDisplay(0x00);   // Disable Inverse Display On (0x00/0x01)
    SetDisplayOnOff(0x01);     // Display On (0x00/0x01)
    OLED_Fill(0x00);            // ��ʼ����
    OLED_SetPos(0,0);

    return;
}

/*****************************************************************************
 �� �� ��  : OLED_P6x8Char
 ��������  : ��ʾһ��6x8��׼ASCII�ַ�
 �������  : uchar8 ucIdxX  ��ʾ�ĺ�����0~122
             uchar8 ucIdxY  ҳ��Χ0��7
             uchar8 ucData  ��ʾ���ַ�
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
void OLED_P6x8Char(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucData)
{
    uchar8 i, ucDataTmp;

    ucDataTmp = ucData-32;
    if(ucIdxX > 122)
    {
        ucIdxX = 0;
        ucIdxY++;
    }

    OLED_SetPos(ucIdxX, ucIdxY);

    for(i = 0; i < 6; i++)
    {
        OLED_WrDat(Font_6x8[ucDataTmp][i]);
    }
}

/*****************************************************************************
 �� �� ��  : OLED_P6x8Str
 ��������  : д��һ��6x8��׼ASCII�ַ���
 �������  : uchar8 ucIdxX       ��ʾ�ĺ�����0~122
             uchar8 ucIdxY       ҳ��Χ0��7
             uchar8 ucDataStr[]  ��ʾ���ַ���
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
void OLED_P6x8Str(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucDataStr[])
{
    uchar8 i, j, ucDataTmp;

    for (j = 0; ucDataStr[j] != '\0'; j++)
    {
        ucDataTmp = ucDataStr[j] - 32;
        if(ucIdxX > 122)
        {
            ucIdxX = 0;
            ucIdxY++;
        }

        OLED_SetPos(ucIdxX,ucIdxY);

        for(i = 0; i < 6; i++)
        {
            OLED_WrDat(Font_6x8[ucDataTmp][i]);
        }
        ucIdxX += 6;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : OLED_P8x16Str
 ��������  : д��һ��8x16��׼ASCII�ַ���
 �������  : uchar8 ucIdxX       Ϊ��ʾ�ĺ�����0~120
             uchar8 ucIdxY       Ϊҳ��Χ0��3
             uchar8 ucDataStr[]  Ҫ��ʾ���ַ���
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
void OLED_P8x16Str(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucDataStr[])
{
    uchar8 i, j, ucDataTmp;

    ucIdxY <<= 1;

    for (j = 0; ucDataStr[j] != '\0'; j++)
    {
        ucDataTmp = ucDataStr[j] - 32;
        if(ucIdxX > 120)
        {
            ucIdxX = 0;
            ucIdxY += 2;
        }
        OLED_SetPos(ucIdxX, ucIdxY);

        for(i = 0; i < 8; i++)
        {
            OLED_WrDat(Font_8x16[(ucDataTmp << 4) + i]);
        }

        OLED_SetPos(ucIdxX, ucIdxY + 1);

        for(i = 0; i < 8; i++)
        {
            OLED_WrDat(Font_8x16[(ucDataTmp << 4) + i + 8]);
        }
        ucIdxX += 8;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : OLED_P14x16Str
 ��������  : д��һ��14x16�������ַ������ַ���������躬�д��֣�
 �������  : uchar8 ucIdxX       Ϊ��ʾ�ĺ�����0~114
             uchar8 ucIdxY       Ϊҳ��Χ0��3
             uchar8 ucDataStr[]  Ҫ��ʾ�������ַ���
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
/*
void OLED_P14x16Str(uchar8 ucIdxX,uchar8 ucIdxY,uchar8 ucDataStr[])
{
    uchar8 i, j;
    ushort16 usAddress;

    ucIdxY <<= 1;

    j = 0;
    while(ucDataStr[j] != '\0')
    {
        i = 0;
        usAddress = 1;
        while(F14x16_Idx[i] > 127)
        {
            if(F14x16_Idx[i] == ucDataStr[j])
            {
                if(F14x16_Idx[i + 1] == ucDataStr[j + 1])
                {
                    usAddress = i * 14;
                    break;
                }
            }
            i += 2;
        }

        if(ucIdxX > 114)
        {
            ucIdxX = 0;
            ucIdxY += 2;
        }

        if(usAddress != 1)// ��ʾ����
        {
            OLED_SetPos(ucIdxX, ucIdxY);
            for(i = 0; i < 14; i++)
            {
                OLED_WrDat(F14x16[usAddress]);
                usAddress++;
            }

            OLED_SetPos(ucIdxX,ucIdxY + 1);
            for(i = 0;i < 14;i++)
            {
                OLED_WrDat(F14x16[usAddress]);
                usAddress++;
            }

            j += 2;
        }
        else              //��ʾ�հ��ַ�
        {
            OLED_SetPos(ucIdxX,ucIdxY);
            for(i = 0;i < 14;i++)
            {
                OLED_WrDat(0);
            }

            OLED_SetPos(ucIdxX,ucIdxY + 1);
            for(i = 0;i < 14;i++)
            {
                OLED_WrDat(0);
            }

            j++;
        }

        ucIdxX += 14;
    }

    return;
}
*/
/*****************************************************************************
 �� �� ��  : OLED_PXx16MixStr
 ��������  : ���14x16���ֺ��ַ�����ַ��� ���ַ���������躬�д��֣�
 �������  : uchar8 ucIdxX       Ϊ��ʾ�ĺ�����0~114
             uchar8 ucIdxY       Ϊҳ��Χ0��3
             uchar8 ucDataStr[]  Ҫ��ʾ�������ַ���
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
/*
void OLED_PXx16MixStr(uchar8 ucIdxX, uchar8 ucIdxY, uchar8 ucDataStr[])
{
    uchar8 ucTmpStr[3];
    uchar8 i = 0;

    while(ucDataStr[i] != '\0')
    {
        if(ucDataStr[i] > 127)
        {
            ucTmpStr[0] = ucDataStr[i];
            ucTmpStr[1] = ucDataStr[i + 1];
            ucTmpStr[2] = '\0';          //����Ϊ�����ֽ�
            OLED_P14x16Str(ucIdxX, ucIdxY, ucTmpStr);  //��ʾ����
            ucIdxX += 14;
            i += 2;
        }
        else
        {
            ucTmpStr[0] = ucDataStr[i];
            ucTmpStr[1] = '\0';          //��ĸռһ���ֽ�
            OLED_P8x16Str(ucIdxX, ucIdxY, ucTmpStr);  //��ʾ��ĸ
            ucIdxX += 8;
            i += 1;
        }
    }

    return;
}
*/
/*****************************************************************************
 �� �� ��  : OLED_PrintChar
 ��������  : ��һ��Char����ת����3λ��������ʾ
 �������  : uchar8 ucIdxX    ucIdxX�ķ�ΧΪ0��122
             uchar8 ucIdxY    ucIdxY�ķ�ΧΪ0��7
             char cData      cDataΪ��Ҫת����ʾ����ֵ -128~127
 �������  : none
 �� �� ֵ  : none
*****************************************************************************/
void OLED_PrintChar(uchar8 ucIdxX, uchar8 ucIdxY, signed char cData)
{
    ushort16 i, j, k, usData;

    if(cData < 0)
    {
        OLED_P6x8Char(ucIdxX, ucIdxY, '-');
        usData = (ushort16)(-cData);
    }
    else
    {
        OLED_P6x8Char(ucIdxX, ucIdxY, '+');
        usData = (ushort16)cData;
    }
    i = usData / 100;
    j = (usData % 100) / 10;
    k = usData % 10;

    OLED_P6x8Char(ucIdxX+6, ucIdxY, i+48);
    OLED_P6x8Char(ucIdxX+12, ucIdxY, j+48);
    OLED_P6x8Char(ucIdxX+18, ucIdxY, k+48);

    return;
}

/*****************************************************************************
 �� �� ��  : OLED_PrintShort
 ��������  : ��һ��Short����ת����5λ��������ʾ
 �������  : uchar8 ucIdxX ucIdxX�ķ�ΧΪ0��120
             uchar8 ucIdxY ucIdxYΪҳ�ķ�Χ0��7
             SHORT16 sData  sDataΪ��Ҫת����ʾ����ֵ
 �������  : none
 �� �� ֵ  : none
*****************************************************************************/
void OLED_PrintShort(uchar8 ucIdxX, uchar8 ucIdxY, short sData)
{
    ushort16 i, j, k, l, m, usData;
    if(sData < 0)
    {
        OLED_P6x8Char(ucIdxX,ucIdxY,'-');
        usData = (ushort16)(-sData);
    }
    else
    {
        OLED_P6x8Char(ucIdxX,ucIdxY,'+');
        usData = (ushort16)sData;
    }

    l = usData / 10000;
    m = (usData % 10000) /1000;
    i = (usData % 1000) / 100;
    j = (usData % 100) / 10;
    k = usData % 10;
    OLED_P6x8Char(ucIdxX+6, ucIdxY, l+48);
    OLED_P6x8Char(ucIdxX+12, ucIdxY, m+48);
    OLED_P6x8Char(ucIdxX+18, ucIdxY, i+48);
    OLED_P6x8Char(ucIdxX+24, ucIdxY, j+48);
    OLED_P6x8Char(ucIdxX+30, ucIdxY, k+48);

    return;
}

/*****************************************************************************
 �� �� ��  : OLED_PrintImage
 ��������  : ��ͼ����ʾ����
 �������  : uchar8 *pucTable     ��άͼ������ĵ�ַ
             ushort16 usRowNum    ��άͼ�������1~64
             ushort16 usColumnNum ��άͼ�������1~128
 �������  : none
 �� �� ֵ  : none
*****************************************************************************/
void OLED_PrintImage(uchar8 *pucTable, ushort16 usRowNum, ushort16 usColumnNum)
{
    uchar8 ucData;
    ushort16 i,j,k,m,n;
    ushort16 usRowTmp;

    m = usRowNum >> 3;   //����ͼƬ������8λΪһ������������
    n = usRowNum % 8;    //����������ʣ�µ�����

    for(i = 0; i < m; i++) //��������ɨ��
    {
        OLED_SetPos(0,(uchar8)i);
        usRowTmp = i << 3;    //���㵱ǰ�����е��±�
        for(j = 0; j < usColumnNum; j++) //��ɨ��
        {
            ucData = 0;
            for(k = 0; k < 8; k++) //��i���ж���8��ɨ��
            {
                ucData = ucData >> 1;
                if((pucTable + (usRowTmp + k) * usColumnNum)[j] == OLED_IMAGE_WHITE)
                {
                    ucData = ucData | 0x80;
                }

            }
            OLED_WrDat(ucData);
        }
    }

    OLED_SetPos(0,(uchar8)i); //����ʣ�µ�����ʾ����ʼ����
    usRowTmp = i << 3;       //���㵱ǰ�����е��±�
    for(j = 0; j < usColumnNum; j++) //��ɨ��
    {
        ucData = 0;
        for(k = 0; k < n; k++) //��ʣ�µ���ɨ��
        {
            ucData = ucData >> 1;
            if((pucTable + (usRowTmp + k) * usColumnNum)[j] == OLED_IMAGE_WHITE)
            {
                ucData = ucData | 0x80;
            }

        }
        ucData = ucData >> (8 - n);
        OLED_WrDat(ucData);
    }

    return;
}

