#include <REGX52.H>
#include "intrins.h"
#include "lcd12864.h"
#include "picture.h"
sbit CS   =P3^0;  //Ƭѡ
sbit STD  =P3^1;  //��������
sbit SCLK =P3^2;  //����ʱ��
sbit KEY1 = P2^0;

unsigned char i,X,Y,XPosition,YPosition,FCHARBUF;

unsigned int ReadKey1() // ������⺯��
{
    if (KEY1 == 1)           
	{  // ����������
        Delay(1);  // �򵥵�ȥ��������
        if (KEY1 == 1) 
		{  // ��鰴���Ƿ���Ȼ����
            while (KEY1 == 1);  // �ȴ������ͷ�
            return 1;  // ���ذ���������
        }
    }
    return 0;  // ����û�б�����
}


void Delay(unsigned char xms)	//@12.000MHz
{
	while(xms--){
	unsigned char data i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}
}

/**
 * @brief  һλ����(bit d)ͨ�����ŷ��͵�Һ����ʾ������
 * @param  
 * @retval None
 */

void Trans_Bit(bit d)  // ��һλ���ݴ��䵽Һ����ʾ������
{
   STD = d;       // �Ƚ������ bit ���� d �͵��������� STDPIN ��
   //_nop_();          
   SCLK = 1;      // ��ʱ������ SCLKPIN �øߣ���ʼһ��ʱ�����ڣ�
   //_nop_();        
   SCLK = 0;      // ��ʱ������ SCLKPIN �õͣ�������������½��أ�
   //_nop_();       
   SCLK = 1;      // ��ʱ������ SCLKPIN �øߣ�׼����һ�����ݴ��䣩
}



/**
  * @brief  ��LCD12864��һ�ֽ���ʾ����/ָ��  
  * @param  d
  * @retval None
  */

void Trans_Byte(unsigned char d)
{
    unsigned char i;
    for(i = 0; i < 8; i++)//һ���ֽ�
    {
        if((d & 0x80) == 0x80)//��������ֽڵ����λ
            Trans_Bit(1);
        else
            Trans_Bit(0);
        d <<= 1;  // ���ƺ�ֵ
    }            
}



/**
  * @brief  ��LCD12864дָ��  
  * @param  None
  * @retval None
  */
void Write_Command(unsigned char e)
{
    CS = 1; //11111 00 0    // ����Ƭѡ�ź�
    Trans_Byte(0xf8);      // ���Ϳ����ֽ�,����ͬ�� P26 P10
    Trans_Byte(e & 0xf0);  // ��������ĸ���λ
    Trans_Byte((e & 0x0f) << 4); // ��������ĵ���λ
    CS = 0;                // ȡ��Ƭѡ�ź�
}



/**
  * @brief  ��LCD12864д����  
  * @param  
  * @retval None
  */
void Write_Data(unsigned char e)
{
    CS = 1;  //11111 01 0   // ����Ƭѡ�ź�
    Trans_Byte(0xfa);      // ���Ϳ����ֽڣ�����ͬ�� 	P26 P10
    Trans_Byte(e & 0xf0);  // �������ݵĸ���λ
    Trans_Byte((e & 0x0f) << 4); // �������ݵĵ���λ
    CS = 0;                // ȡ��Ƭѡ�ź�
}



/**
  * @brief  ��LCD12864��״̬  
  * @param  
  * @retval None
  */
void Write_Status(unsigned char e)
{
    CS = 1;  //11111 10 0   // ����Ƭѡ�ź�
    Trans_Byte(0xfc);      // ���Ϳ����ֽڣ�����ͬ�� 	P26 P10
    Trans_Byte(e & 0xf0);  // �������ݵĸ���λ
    Trans_Byte((e & 0x0f) << 4); // �������ݵĵ���λ
    CS = 0;   
}


/**
  * @brief  ��LCD12864������  
  * @param  
  * @retval None
  */
void Read_Data(unsigned char e)
{
	CS=1;   //0x11111 11 0
    Trans_Byte(0xfc);      // ���Ϳ����ֽڣ�����ͬ�� 	P26 P10
    Trans_Byte(e & 0xf0);  // �������ݵĸ���λ
    Trans_Byte((e & 0x0f) << 4); // �������ݵĵ���λ
    CS = 0;   
}


/**
  * @brief  ��LCD12864ͼ����ʾ��
  * @param  None
  * @retval None
  */
void  Graphic_Display_ON(void)
{           //0x0011 0110
	Write_Command(0x36);  //P17
	Write_Command(0x30);  //�ָ�Ϊ����ָ� P16
}
	

/**
  * @brief  ��LCD12864ͼ����ʾ��
  * @param  None
  * @retval None
  */
void  Graphic_Display_OFF(void)
{ 			//0x0011 0100
	Write_Command(0x34);  //P17
	Write_Command(0x30);  //�ָ�Ϊ����ָ�
}	

/**
  * @brief  ��ʾ��
  * @param  None
  * @retval None
  */
void  Display_ON(void)
{
	Write_Command(0x30);
	Write_Command(0x0c);//P20
}		  //0x0000 1100

/**
  * @brief  ��ʾ��
  * @param  None
  * @retval None
  */
void  Display_OFF(void)
{
	Write_Command(0x30);
	Write_Command(0x08);//P20
}		  //0x0000 1000


/**
  * @brief  ���׹�
  * @param  None
  * @retval None
  */
void  Versawhite_off(void)
{
	Write_Command(0x30);
	Write_Command(0x0e);//P20
}          //0x0000 1110


/**
  * @brief  ���׿�
  * @param  None
  * @retval None
  */
void  Versawhite_on(void)
{
	Write_Command(0x30);
	Write_Command(0x0f);//P20
}         //0x0000 1111


/**
  * @brief  ��ʾ���
  * @param  None
  * @retval None
  */

void Display_Clear(void)
{
	Write_Command(0x30);
	Write_Command(0x01);//P19
}	     //0x0000 0001
 

/**
  * @brief  ���ص���ʼλ
  * @param  None
  * @retval None
  */
void Return_Home(void)
{
	Write_Command(0x30);
	Write_Command(0x02);//P19
}         //0x0000 0010



/**
  * @brief  ���û�ͼ�����ڲ�RAMָ��
  * @param  None
  * @retval None
  */

void Set_DrawingPosition(void)
{    
	Write_Command(0x36);//��ͼָ��
	Write_Command((YPosition&0x1f)| 0x80);//0x1f->>0-31,����y���ַ 	P24
	if(YPosition>=32)//�°���
		Write_Command((XPosition/16+8) | 0x80);//����x���ַ
	else
		Write_Command((XPosition/16) | 0x80);
	
	Write_Command(0x30);//�ָ�����ָ��
}




/**
  * @brief  ��Ļ���Ϊĳ���ֽ����� DATA
  * @param  DATA
  * @retval None
  */
void FillScreen(unsigned char DATA)  // ������ʾָ�����ֽ�����
{
	unsigned char i;
	YPosition=0;XPosition=0;
    while (YPosition < 64)  // �������е�Y������
    {         
        Set_DrawingPosition();  // ���õ�ǰ�Ļ�ͼλ��
        for (i = 1; i <16; i++)  // ���һ���е�18���ֽ�����
        {
            Write_Data(DATA);  // ��ָ�����ֽ�����д�뵽��ǰ��ͼλ��
        }
        YPosition++;  // �ƶ�����һ��
    }   
    YPosition = 0;  // ��ɺ�Y��λ������
}

	


/**
  * @brief  ��Ļ��ʼ��
  * @param  None
  * @retval None
  */
 void Lcd12864spi_init(void)
{

	Write_Command(0x30);
	Delay(1);
	Write_Command(0x30);
	Delay(1);
	Write_Command(0x08);
	Delay(1);
	Write_Command(0x10);
	Delay(1);
	Write_Command(0x0c);
	Delay(1);
	Write_Command(0x01);
	Delay(1);
	Write_Command(0x06);

}

/**
  * @brief  ��Ļ�����ʾ�ַ���
  * @param  None
  * @retval None
  */

void moveToNextCharPosition(void)  // �ƶ���굽��һ���ַ�λ��
{
	
    X++;                       // �ַ�λ�ü�1
    X &= 0x0F;                 // ����CXPOS��0��15�ķ�Χ��

    if (X == 0)                // ���CXPOSΪ0����ʾ��Ҫ����
    {   
        Y++;                   // ��λ�ü�1
        Y &= 0x3;             // ����CYPOS��0��3�ķ�Χ��
    }
}





/**
  * @brief  �����ַ������LCD�ڲ�RAM�ĵ�ַ
  * @param  None
  * @retval None
  */
void setLcdCursorPosition(void)  
{
	unsigned char addDDRAM;
	X &= 0xF;// ������0-15�� 
	addDDRAM = X / 2;//ÿ�����ַ�����һ�� DDRAM ��Ԫ
	if (Y == 0) Write_Command(addDDRAM | 0x80);// DDRAM��ַ:80H-87H
	else if (Y == 1) Write_Command(addDDRAM | 0x90);// DDRAM��ַ:90H-97H
	else if (Y == 2) Write_Command(addDDRAM | 0x88);// DDRAM��ַ:88H-8FH
	else if (Y == 3) Write_Command(addDDRAM | 0x98);// DDRAM��ַ:98H-9FH
}	



/**
  * @brief  ����ͼ������
  * @param  imageData[] ͼ������
  * @retval None
  */
void drawimge(unsigned char code *imgeData)
{
    unsigned char width, height;
    
    // ��ȡͼ��Ŀ��
    width = *imgeData;
    imgeData++;  // ָ����ǰ�ƶ���ָ��ͼ��߶�
    
    // ��ȡͼ��ĸ߶�
    height = *imgeData;
    imgeData++;  // ָ����ǰ�ƶ���ָ��ʵ��ͼ������
    
    // ��ʾͼ��
    drawImageWithSize(width, height, imgeData);
}


//                                    128                  64
void drawImageWithSize(unsigned char width, unsigned char height, unsigned char code *imgeData)
{
    unsigned char pixelX, pixelY, x;
     x = XPosition;  // ���浱ǰXλ��

    // ����ͼ��ĸ߶ȣ�������ʾ��
    for (pixelY = 0; pixelY < height; pixelY++, YPosition++)  // ÿ�α���һ�У�GYPOS����һ��
    {
        // ����ͼ��Ŀ��
        for (XPosition = x, pixelX = 0; pixelX < width;)
        {	if ((XPosition & 0x08) == 0) Set_DrawingPosition();  // ����λ�����ù��
            Write_Data(*imgeData);                   // ��ʾ��ǰ�ֽڵ�ͼ������
            imgeData++;                         // �ƶ�����һ���ֽ�
            pixelX += 8;                         // Xλ��ÿ���ƶ�8�����أ�ÿ���ֽ�8���أ�
            XPosition += 8;                          // �����X�����ƶ�8������
        }
    }

    XPosition = x;  // �ָ�X�������ʼλ��
}


/**
  * @brief  �Զ����ַ�(����ͼ��)д��LCD12864���ַ����� RAM
  * @param  charindex:0-7,pattern[] ͼ������
  * @retval None
  */
void setchartoCGRAM(unsigned char charindex ,unsigned char code *pattern)
{
	unsigned char i;
	 // �л�����չָ������� CGRAM
    Write_Command(0x34);  // ������չָ���ͼ��ģʽ�ر�
    Write_Command(0x02);  // ���� SR = 0������ CGRAM
    Write_Command(0x30);  // ���ػ���ָ�
	
	// ���� CGRAM ��ַ (�� 2 λȡ�� charIndex������ 0x40 �ϲ�)
	Write_Command(((charindex &0x3)<<4) |0x40);//�O��CGRAMλַ,P21
	for(i=0;i<32;i++)
		Write_Data(*pattern); // д�벢�ƶ�����һ���ֽ�
	
}



/**
 * @brief ��ָ���� (cx, cy) λ����ʾ�ַ���
 * @param x 0-4 �ַ���X����λ��
 * @param y 0-4 �ַ���Y����λ��
 * @param s Ҫ��ʾ���ַ���
 */
void DisplaystringAtposition(unsigned char x ,unsigned char y ,unsigned char code*s)
{
	X=x;
	Y=y;
	DisplayString(s);
}

       


/**
 * @brief ��ʾ�ַ�����ֱ�������ַ���Ϊ0
 * @param str Ҫ��ʾ���ַ���
 */
void DisplayString(unsigned char code *str) 
{
    unsigned int charCode;

    while (1) 
    {
        charCode = *str;  // ��ȡ��ǰ�ַ�
        str++;  // �ƶ�����һ���ַ�

        if (charCode == 0) break;  // ����ַ���Ϊ0�������ַ�����ʾ

        if (charCode < 128)
        {
            putchar(charCode);  // ��ʾASCII�ַ�
        }
        else
        {
            // ������չ�ַ�����λ�͵�λ�ֽ���ϣ�
            putchar(charCode * 256 + *str);
            str++;  // ������һ���ַ�����λ�ֽڣ�
        }
    }
}


/**
 * @brief ��ʾ�ַ���LCD��Ļ�ϣ��������ַ����ͺ��Զ�����
 *
 * �ú���������LCD����ʾ�ַ���֧��ASCII�ַ��ͺ��ֵ���ʾ���������ַ�λ�õĶ��롣
 * ���ں��֣��ַ������128�������Զ����������ֽڲ����ݵ�ǰ���λ�ý��ж��룻
 * ����ASCII�ַ����ַ���С��128�������������λ�û�����ʵ��Ķ��벹�䡣
 * 
 * @param c Ҫ��ʾ���ַ���������ASCII�ַ������ַ���
 * 
 * @note 
 * - �����ַ������128����ռ�����ֽڣ����ֽں͵��ֽڣ����ú������Զ��ֶ���ʾ��
 * - �Զ����ַ��ĸ��ֽ�Ϊ0xFF��ת��ΪST7920���������ַ����ʽ��
 */
void putchar(unsigned int c) 
{
    if (c > 128) // �ַ������128��ʾΪ����
    {
        if ((X & 0x1) == 1) // ���CXPOS�ַ�λ��������λ��
        {
            Write_Data(' '); // �Զ�����һ���ո����
            moveToNextCharPosition(); // ���ַ�λ��Ϊ��һ����Чλ��
        }
        setLcdCursorPosition(); // �����ַ�λ��
        if ((c & 0xff00) == 0xff00) // �����λ�ֽ�Ϊ0xFF��ʾ�Զ����ַ�
        {
            c = 0xffff - c; // ת��ΪST7920���ַ���
        }
        Write_Data(c / 256); // 256д��λ�ַ�
        moveToNextCharPosition(); // ���ַ�λ��Ϊ��һ����Чλ��
        Write_Data(c & 0xff); // д��λ�ַ�
        moveToNextCharPosition(); // ���ַ�λ��Ϊ��һ����Чλ��
    }
    else // �ַ���С��128��ʾΪASCII�ַ�
    {
        setLcdCursorPosition(); // �����ַ�λ��
        if ((X& 0x1) == 1) // ���CXPOS�ַ�λ��������λ��
        {
            Write_Data(FCHARBUF); // ����д��λ�ַ�����������
            Write_Data(c); // д��ǰ�ַ�
        }
        else // ���CXPOS�ַ�λ����ż��λ��
        {
            Write_Data(c); // ֱ��д��ǰ�ַ�
            FCHARBUF = c; // ���浱ǰ�ַ�����λ�ַ��������
            Write_Data(' '); // �Զ�����һ���ո�
        }
        moveToNextCharPosition(); // ���ַ�λ��Ϊ��һ����Чλ��
    }
}



/**
 * @brief ������LCD��Ļ�����ָ����ASCII�ַ�
 * �ú�������LCD��ÿ���ַ�λ����ʾ�ɲ��� `c` �����ASCII�ַ���
 * ��ͨ��ѭ������ַ�������Ļ����ʾ��ֱ�����ص���ʼλ�ã�0,0�����Ӷ����������Ļ����䡣
 * @param c Ҫ��ʾ��ASCII�ַ�
 */
void charlcdfill(unsigned int c) // ������ʾָ��ASCII�ַ����ӳ���
{   
    for (X = Y = 0; 1;) // ��ʼ��X��Y����Ϊ0,0������ʼ����ѭ��
    {   
        putchar(c); // ����putchar�������ڵ�ǰλ����ʾ�ַ�
        if ((X == 0) && (Y == 0)) break; // ����Ѿ����ص���Ļ��ʼλ��(0,0)�����˳�ѭ��
    }
}





 
void FillScreenWithPattern(unsigned char pattern)
{    
    unsigned char x, y;

    for (y = 0; y < 64; y++) // ����Y���64��λ�ã�0-63������Ļ�߶�Ϊ64����
    {
        YPosition = y;         // ����Y��λ��
        Set_DrawingPosition(); // ���õ�ǰ�Ļ�ͼλ��

        for (x = 0; x < 16; x++) // ����X���16��λ�ã�ÿ��16�ֽڣ�
        {
            Write_Data(pattern); // �ڵ�ǰXλ����ʾ�����ͼ������
        }
    }
    YPosition = 0; // ��ɺ�Y��λ������
}



//���
void FillCheckerboardPattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y���64��λ��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X���16���ֽ�
        {
            if (y % 2 == 0)   // ż������ʾ0xAA
            {
                Write_Data(0x55);
            }
            else  // ��������ʾ0x55
            {
                Write_Data(0xaa);
            }
        }
    }
}
void ReverseFillCheckerboardPattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y���64��λ��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X���16���ֽ�
        {
            if (y % 2 == 0)   // ż������ʾ0xAA
            {
                Write_Data(0xaa);
            }
            else  // ��������ʾ0x55
            {
                Write_Data(0x55);
            }
        }
    }
}

//��ֱ����ͼ��
void FillVerticalStripePattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X��
        {
            Write_Data(0xaa);  // ÿ���ֽ��ϰ벿��ȫ�����°벿��ȫ��
        }           //1010 1010
    }               //0x55->01010 01010
}
void ReverseFillVerticalStripePattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X��
        {
            Write_Data(0x55);  // ÿ���ֽ��ϰ벿��ȫ�����°벿��ȫ��
        }           //1010 1010
    }               //0x55->01010 01010
}


//ˮƽ����ͼ��
void FillHorizontalStripePattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X��
        {
            if (y % 2 == 0)  // ż������ʾȫ��
            {
                Write_Data(0xFF);
            }
            else  // ��������ʾȫ��
            {
                Write_Data(0x00);
            }
        }
    }
}
void ReverseFillHorizontalStripePattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X��
        {
            if (y % 2 == 0)  // ż������ʾȫ��
            {
                Write_Data(0x00);
            }
            else  // ��������ʾȫ��
            {
                Write_Data(0xff);
            }
        }
    }
}

//б��ͼ��
void FillDiagonalLinePattern(void)
{
    unsigned char x, y;

    for (y = 0; y < 64; y++)  // ����Y��
    {
        YPosition = y;
        Set_DrawingPosition();

        for (x = 0; x < 16; x++)  // ����X��
        {
            Write_Data(1 << (y % 8));  
        }
    }

}




