#include <msp430.h>
#include "MacroDefination.h"
#include "FunctionDeclaration.h"
#include "VariableDefination.h"

extern const uchar8 Font_6x8[][6];
extern const uchar8 Font_8x16[];

//OLED写数据
void OLED_WrDat(uchar8 Data)
{
    OLED  |= OLED_DC;
    SPI_Send_Byte(Data);
}

//OLED写命令
void OLED_WrCmd(uchar8 Cmd)
{
    OLED &= ~OLED_DC;
    SPI_Send_Byte(Cmd);
}


/*****************************************************************************
 函 数 名  : OLED_SetPos
 功能描述  : 设置坐标
 输入参数  : uchar8 ucIdxX
             uchar8 ucIdxY
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
void OLED_SetPos(uchar8 ucIdxX, uchar8 ucIdxY)
{
    OLED_WrCmd(0xb0 + ucIdxY);
    OLED_WrCmd(((ucIdxX & 0xf0) >> 4) | 0x10);
    OLED_WrCmd((ucIdxX & 0x0f) | 0x00);
}

/*****************************************************************************
 函 数 名  : OLED_Fill
 功能描述  : 对全屏写入同一个字符函数
             如 OLED_Fill(0x01);    对于某一位0为不亮 1为亮
            ------------------------------------------------------
                                共128列
					1				1				1
              共  	0				0                0
              8   	0           0                0
              组  	0     ……0     …………   0
              字  	0           0                0
              符  	0           0                0
              即  	0           0                0
              8   	0           0                0
              页  	1           1                1
              64  0           0                0
              行  	.			.                .
					.           .    …………    .
					.           .                .
					.           .                .
					0           0                0
            ------------------------------------------------------
 输入参数  : uchar8 ucData
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
void OLED_Fill(uchar8 ucData)
{
    uchar8 ucPage,ucColumn;

    for(ucPage = 0; ucPage < 8; ucPage++)
    {
        OLED_WrCmd(0xb0 + ucPage);  //0xb0+0~7表示页0~7
        OLED_WrCmd(0x00);           //0x00+0~16表示将128列分成16组其地址在某组中的第几列
        OLED_WrCmd(0x10);           //0x10+0~16表示将128列分成16组其地址所在第几组
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
 函 数 名  : OLED_Init
 功能描述  : OOLED初始化
 输入参数  : void
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
void OLED_Init(void)
{
    uchar8 i;

    OLED |=OLED_SCL;
    OLED &=~OLED_RST;

    for(i = 0; i < 100; i++)
    {
        _nop();            //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕
    }

    OLED |=OLED_RST;

    SetDisplayOnOff(0x00);     // Display Off (0x00/0x01)
    SetDisplayClock(0x80);     // Set Clock as 100 Frames/Sec
    SetMultiplexRatio(0x3F);   // 1/64 Duty (0x0F~0x3F)
    SetDisplayOffset(0x00);    // Shift Mapping RAM Counter (0x00~0x3F)
    SetStartLine(0x00);        // Set Mapping RAM Display Start Line (0x00~0x3F)
    SetChargePump(0x04);       // Enable Embedded DC/DC Converter (0x00/0x04)
    SetAddressingMode(0x02);   // Set Page Addressing Mode (0x00/0x01/0x02)
    SetSegmentRemap(0x01);     // Set SEG/Column Mapping     0x00左右反置 0x01正常
    SetCommonRemap(0x08);      // Set COM/Row Scan Direction 0x00上下反置 0x08正常
    SetCommonConfig(0x10);     // Set Sequential Configuration (0x00/0x10)
    SetContrastControl(0xCF);  // Set SEG Output Current
    SetPrechargePeriod(0xF1);  // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    SetVCOMH(0x40);            // Set VCOM Deselect Level
    SetEntireDisplay(0x00);    // Disable Entire Display On (0x00/0x01)
    SetInverseDisplay(0x00);   // Disable Inverse Display On (0x00/0x01)
    SetDisplayOnOff(0x01);     // Display On (0x00/0x01)
    OLED_Fill(0x00);            // 初始清屏
    OLED_SetPos(0,0);

    return;
}

/*****************************************************************************
 函 数 名  : OLED_P6x8Char
 功能描述  : 显示一个6x8标准ASCII字符
 输入参数  : uchar8 ucIdxX  显示的横坐标0~122
             uchar8 ucIdxY  页范围0～7
             uchar8 ucData  显示的字符
 输出参数  : NONE
 返 回 值  : NONE
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
 函 数 名  : OLED_P6x8Str
 功能描述  : 写入一组6x8标准ASCII字符串
 输入参数  : uchar8 ucIdxX       显示的横坐标0~122
             uchar8 ucIdxY       页范围0～7
             uchar8 ucDataStr[]  显示的字符串
 输出参数  : NONE
 返 回 值  : NONE
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
 函 数 名  : OLED_P8x16Str
 功能描述  : 写入一组8x16标准ASCII字符串
 输入参数  : uchar8 ucIdxX       为显示的横坐标0~120
             uchar8 ucIdxY       为页范围0～3
             uchar8 ucDataStr[]  要显示的字符串
 输出参数  : NONE
 返 回 值  : NONE
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
 函 数 名  : OLED_P14x16Str
 功能描述  : 写入一组14x16的中文字符串（字符串表格中需含有此字）
 输入参数  : uchar8 ucIdxX       为显示的横坐标0~114
             uchar8 ucIdxY       为页范围0～3
             uchar8 ucDataStr[]  要显示的中文字符串
 输出参数  : NONE
 返 回 值  : NONE
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

        if(usAddress != 1)// 显示汉字
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
        else              //显示空白字符
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
 函 数 名  : OLED_PXx16MixStr
 功能描述  : 输出14x16汉字和字符混合字符串 （字符串表格中需含有此字）
 输入参数  : uchar8 ucIdxX       为显示的横坐标0~114
             uchar8 ucIdxY       为页范围0～3
             uchar8 ucDataStr[]  要显示的中文字符串
 输出参数  : NONE
 返 回 值  : NONE
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
            ucTmpStr[2] = '\0';          //汉字为两个字节
            OLED_P14x16Str(ucIdxX, ucIdxY, ucTmpStr);  //显示汉字
            ucIdxX += 14;
            i += 2;
        }
        else
        {
            ucTmpStr[0] = ucDataStr[i];
            ucTmpStr[1] = '\0';          //字母占一个字节
            OLED_P8x16Str(ucIdxX, ucIdxY, ucTmpStr);  //显示字母
            ucIdxX += 8;
            i += 1;
        }
    }

    return;
}
*/
/*****************************************************************************
 函 数 名  : OLED_PrintChar
 功能描述  : 将一个Char型数转换成3位数进行显示
 输入参数  : uchar8 ucIdxX    ucIdxX的范围为0～122
             uchar8 ucIdxY    ucIdxY的范围为0～7
             char cData      cData为需要转化显示的数值 -128~127
 输出参数  : none
 返 回 值  : none
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
 函 数 名  : OLED_PrintShort
 功能描述  : 将一个Short型数转换成5位数进行显示
 输入参数  : uchar8 ucIdxX ucIdxX的范围为0～120
             uchar8 ucIdxY ucIdxY为页的范围0～7
             SHORT16 sData  sData为需要转化显示的数值
 输出参数  : none
 返 回 值  : none
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
 函 数 名  : OLED_PrintImage
 功能描述  : 将图像显示出来
 输入参数  : uchar8 *pucTable     二维图像数组的地址
             ushort16 usRowNum    二维图像的行数1~64
             ushort16 usColumnNum 二维图像的列数1~128
 输出参数  : none
 返 回 值  : none
*****************************************************************************/
void OLED_PrintImage(uchar8 *pucTable, ushort16 usRowNum, ushort16 usColumnNum)
{
    uchar8 ucData;
    ushort16 i,j,k,m,n;
    ushort16 usRowTmp;

    m = usRowNum >> 3;   //计算图片行数以8位为一组完整的组数
    n = usRowNum % 8;    //计算分完组后剩下的行数

    for(i = 0; i < m; i++) //完整组行扫描
    {
        OLED_SetPos(0,(uchar8)i);
        usRowTmp = i << 3;    //计算当前所在行的下标
        for(j = 0; j < usColumnNum; j++) //列扫描
        {
            ucData = 0;
            for(k = 0; k < 8; k++) //在i组中对这8行扫描
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

    OLED_SetPos(0,(uchar8)i); //设置剩下的行显示的起始坐标
    usRowTmp = i << 3;       //计算当前所在行的下标
    for(j = 0; j < usColumnNum; j++) //列扫描
    {
        ucData = 0;
        for(k = 0; k < n; k++) //对剩下的行扫描
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

