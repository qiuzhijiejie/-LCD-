#include "LCD1602.h"
#include <REGX52.H>



sbit LCD_RS = P3^0; 
sbit LCD_RW = P3^1;
sbit LCD_EN = P3^2;
sbit   KEY1  = P2^0;	

extern unsigned int i,j,maxSteps;


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







void  Delay(xms)	//@12.000MHz
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


//�ж�æ��æ
void Busy()
{
	unsigned char temp;
	LCD_DataPort=0xff;
	LCD_RS=0;//RW=1,RS=0��״̬
	LCD_RW=1;
	
	do{
		LCD_EN=1;
		temp=LCD_DataPort;
		LCD_EN=0;
	}while(temp&0x80);}/*�Կ�����ÿ�ν��ж�д����֮ǰ�� 
					  ��������ж�д��⣬ȷ��STA7Ϊ0*/



/**
  * @brief  LCD1602д����
  * @param  Command Ҫд�������
  * @retval ��
  */
void LCD_WriteCommand(unsigned char Command) 
{
	Busy();
    LCD_RS = 0; // ѡ��Ϊָ�1Ϊ���ݣ�0Ϊָ��
    LCD_RW = 0; // ѡ��Ϊд�� 1Ϊ����0Ϊд
    LCD_DataPort = Command; // д��ָ�������
    LCD_EN = 1;   // ʹ�ܽ�E��������д��
    Delay(0.1);
    LCD_EN = 0;   // ʹ�ܽ�E���������д��
}



/**
  * @brief  LCD1602д����
  * @param  Data Ҫд�������,����LCD_SetCursor()���ʹ�á�
  * @retval ��
  */
void LCD_WriteData(unsigned char Data) 
{
	Busy();
    LCD_RS = 1; // ѡ��Ϊ���ݣ�1Ϊ���ݣ�0Ϊָ��
    LCD_RW = 0; // ѡ��Ϊд�� 1Ϊ����0Ϊд
    LCD_DataPort = Data; // д��ָ���ݵ�����
    LCD_EN = 1;   // ʹ�ܽ�E��������д��
    Delay(0.1);
    LCD_EN = 0;   // ʹ�ܽ�E���������д��
	Delay(0.1);
  
}



/**
  * @brief  LCD1602��ʼ������
  * @param  ��
  * @retval ��
  */
void LCD_Init() 
{
    LCD_WriteCommand(0x38); // ����16X2��ʾ,5X7����,8λ���ݽӿ� 
    LCD_WriteCommand(0x0c); // ��ʾ��,��꿪,��˸��
    LCD_WriteCommand(0x06); // ������дһ���ַ����ַָ���һ,�ҹ���һ,���治��
    LCD_WriteCommand(0x01); // ��긴λ������
	Delay(1.5); 
}

/**
  * @brief  LCD1602����
  * @param  ��
  * @retval ��
  */
void LCD_Clear() 
{
    Busy();
    LCD_WriteCommand(0x01);
	Delay(1.5);           // �ȴ��������
}


/**
  * @brief  LCD1602���ù��λ��
  * @param  Line ��λ�ã���Χ��1~2
  * @param  Column ��λ�ã���Χ��1~16
  * @retval ��
  */
void LCD_SetCursor(unsigned char Line, unsigned char Column) 
{
	
			if (Line == 1) 
				{
					LCD_WriteCommand(0x80 | (Column - 1)); // ��һ��
				} 
			else  
				{
					LCD_WriteCommand(0x80 | (Column - 1 + 0x40)); // �ڶ���
				}
	
}
	
 
/**
 * @brief LCD1602��ʾ�ַ���
 * @param Line1-2�� Column 1-16�� *String �����ַ�""
 * @retval ��
 */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String) 
{	unsigned char i;		
	LCD_SetCursor(Line, Column);
    for (i = 0; String[i] != '\0'; i++) 
	{
      LCD_WriteData(String[i]);
    }
}


unsigned char LCD_Readdata(void)               //�������ӳ���
{   unsigned char d;
    Busy();                       //HD44780Һ����ʾ������æ���
    LCD_DataPort=0xff;
    LCD_RS=1;                             //RS=1 RW=1 E=�ߵ�ƽ
    LCD_RW=1;
    LCD_EN=1;
    Delay(0.005);
    d=LCD_DataPort;
    LCD_EN=0;
    return d;
}




/**
 * @brief  ��ʾ�ַ�����
 * @param  Line1-2�� Column 1-16�� i�ַ�
 * @retval
 */
void LCD_USER_ShowString(unsigned char Line, unsigned char Column, unsigned char  i) 
{
			
			LCD_SetCursor(Line, Column); // ���
			LCD_WriteData(i );
}


/**
 * @brief  ȫ����ʾHD44780 �����ַ�
 * @param  0x...����16����
 * @retval ��
 */
unsigned int Line,Column;
void HD44780_DisplayChar(unsigned char pattern) {
    for (Line = 1; Line <= 2; Line++) {
        for (Column = 1; Column <= 16; Column++) {
            LCD_USER_ShowString(Line, Column, pattern);
        }
    }
}




// �����Զ����ַ���������LCD1602�ڲ���CGRAM�д����Զ����ַ�
void LCD_USER_SetCustomChar(const char data  *table, unsigned char num) 
{
	
		switch (num) {
        case 1: LCD_WriteCommand(0x40); break;
        case 2: LCD_WriteCommand(0x48); break;
        case 3: LCD_WriteCommand(0x50); break;
        case 4: LCD_WriteCommand(0x58); break;
        case 5: LCD_WriteCommand(0x60); break;
        case 6: LCD_WriteCommand(0x68); break;
        case 7: LCD_WriteCommand(0x70); break;
        case 8: LCD_WriteCommand(0x78); break;
    }
    for (i = 0; i < 8; i++) {
        LCD_WriteData(table[i]);
    }
}



//д��CGRAM
void Write_CGRAM(unsigned char  a[])
{
	unsigned char i=64,k;
	LCD_WriteCommand(0x40);
	for(k=0;k<64;k++)
	 {
	  LCD_WriteData(a[k]);
	 }
}





