#include "LCD4004.h"
#include <REGX52.H>



sbit LCD_RS = P3^0; //�Ĵ���ѡ����
sbit LCD_RW = P3^1;//��/д��(R/W)
sbit LCD_EN = P3^2;//ʹ����(EN)
sbit  KEY1  =P2^0;	


unsigned int i,j,Line,Column,row, col;


unsigned int ReadKey1() 
{
    if (KEY1 == 0) 
	{  
        Delay(1);  
        if (KEY1 == 0) 
		{  
            while (KEY1 == 0);  
            return 1;  
        }
    }
    return 0;  
}





void  Delay(xms)	//@12.000MHz
{
	while(xms--)
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}
	}



void Busy()
{
	unsigned char temp;
	LCD_DataPort=0xff;
	LCD_RS=0;//��״̬
	LCD_EN=0;
	LCD_RW=1;//��
	do
	{
		LCD_EN=1;
		temp=LCD_DataPort;
		LCD_EN=0;
	}
	while(temp&0x80);
}					  /*�Կ�����ÿ�ν��ж�д����֮ǰ�� 
					  ��������ж�д��⣬ȷ��STA7Ϊ0*/



/**
  * @brief  LCD4004д����
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
  * @brief  LCD4004д����
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

}


/**
  * @brief  LCD4004������
  * @param  Data Ҫд�������,����LCD_SetCursor()���ʹ�á�
  * @retval ��
  */
void LCD_ReadData(unsigned char Data) 
{
	Busy();
    LCD_RS = 1; // ѡ��Ϊ���ݣ�1Ϊ���ݣ�0Ϊָ��
    LCD_RW = 1; // ѡ��Ϊд�� 1Ϊ����0Ϊд
	LCD_EN = 1;   // ʹ�ܽ�E��������д��

	Delay(0.1);
    LCD_DataPort = Data; // д��ָ���ݵ�����
    LCD_EN = 0;   // ʹ�ܽ�E���������д��

}



/**
  * @brief  LCD4004��ʼ������
  * @param  ��
  * @retval ��
  */
void LCD_Init() 
{
    LCD_WriteCommand(0x38); // ����40��4��ʾ,5X7����,8λ���ݽӿ� 
    LCD_WriteCommand(0x0c); // ��ʾ��,����,��˸��
//	LCD_WriteCommand(0x0f);//��ʾ��,��꿪.��˸��
    LCD_WriteCommand(0x06); // ������дһ���ַ����ַָ���һ,���ƶ�
    LCD_WriteCommand(0x01); // ��긴λ������
	Delay(0.1); 


}

/**
  * @brief  LCD4004����
  * @param  ��
  * @retval ��
  */
void LCD_Clear() 
{
    Busy();
    LCD_WriteCommand(0x01);
	Delay(0.1);           // �ȴ��������
}


/**
  * @brief  LCD4004���ù��λ��
  * @param  Line ��λ�ã���Χ��0~3
  * @param  Column ��λ�ã���Χ��1~40
  * @retval ��
  */
void LCD_SetCursor(unsigned int Line, unsigned int Column) 
{
    // ȷ����ֵ��0-39֮��
    if (Column >= 40) Column = 0;
    // ȷ����ֵ��0-3֮��
    Line &= 0x03;  // ���� Y λ���� 0 �� 3 ֮��	
    if (Line == 0) 
    {
        LCD_WriteCommand(0x80 | Column);  // ��һ��
    } 
    else if (Line == 1) 
    {
        LCD_WriteCommand(0xC0 | Column);  // �ڶ���
    } 
    else if (Line == 2) 
    {
        LCD_WriteCommand(0x80 | (Column + 40));  // ������
    } 
    else 
    {
        LCD_WriteCommand(0xC0 | (Column + 40));  // ������
    }
}
	
 


unsigned char LCD_Readdata(void)               //�������ӳ���
{   unsigned char d;
    Busy();                       //AIP31066Һ����ʾ������æ���
    LCD_DataPort=0xff;
    LCD_RS=1;                             //RS=1 RW=1 E=�ߵ�ƽ
    LCD_RW=1;
    LCD_EN=1;

    Delay(0.005);
    d=LCD_DataPort;
    LCD_EN=0;

    return d;
}



// 
/**
 * @brief  ��ʾ�ַ�����
 * @param  Line0-3�� Column 0-19�� i�ַ�
 * @retval
 */
void LCD_USER_ShowString(unsigned char Line, unsigned char Column, unsigned char  i) 
{			
	LCD_SetCursor(Line, Column); // ���
	LCD_WriteData(i);
}



/**
 * @brief LCD4004��ʾ�ַ���
 * @param Line 0-3�� Column 0-39�� *String �����ַ�""
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



void write_CGROM(unsigned char a)//LCD�ڲ��̻���ģ�洢�����ڲ����г����ַ�
{
    unsigned char j,k=a;
    LCD_WriteCommand(0x02);  // ����λ���� (���λ�ûص���ʼλ�ã�ͨ����DDRAM����ʼ��ַ)
    Delay(1);                // ��ʱһ��ʱ�䣬ȷ��������Ч
    LCD_WriteCommand(0x80);  // ���ù�굽��1�е���ʼ��ַ (0x80��ӦDDRAM�ĵ�1����ʼ��ַ)
    
    // ���1��д��40���ַ�����
    for (j = 0; j < 40; j++) 
    {
        LCD_WriteData(a);    // ��LCDд������ 'a'
        a += 1;              // ����'a'���Ա���һ���ַ���'a'����һ��ֵ
    }

    LCD_WriteCommand(0xC0);  // ���ù�굽��2�е���ʼ��ַ (0xC0��ӦDDRAM�ĵ�2����ʼ��ַ)
    
    // ���2��д��40���ַ�����
    for (j = 0; j < 40; j++) 
    {
        LCD_WriteData(a);    // ��LCDд������ 'a'
        a += 1;              // ����'a'��ͬ������д����һ���ַ�
    }
    
    Delay(1);                // �ٴ���ʱ��ȷ������ȫ��д��
	
}



/**
 * @brief  ȫ����ʾAIP31066 �����ַ�
 * @param  Line 0-3  Column 0-39  ����16����0X...
 * @retval ��
 */
void Write_DDRAM(unsigned char a)//�����Ĵ����ʾ���ַ�����
{
    unsigned char j;
    
    LCD_WriteCommand(0x02); // ����λ����(���λ�ûص���ʼλ�ã�ͨ����DDRAM����ʼ��ַ)

    Delay(1);               // ��ʱ10����λ (��֮ǰ����ʱ��)

    LCD_WriteCommand(0x80);  // ���ù�굽��1�е���ʼ��ַ (0x80��ӦDDRAM�ĵ�1����ʼ��ַ)
    
    // ���1��д��40����ͬ���ַ�   
    for (j = 0; j <40; j++) 
    {
        LCD_WriteData(a);    // ���ַ� 'a' д�� LCD ��ʾ���ݴ洢��
    }

    LCD_WriteCommand(0xC0);  // ���ù�굽��2�е���ʼ��ַ (0xC0��ӦDDRAM�ĵ�2����ʼ��ַ)
    
    // ���2��д��40����ͬ���ַ�
    for (j = 0; j < 40; j++) 
    {
        LCD_WriteData(a);    // ���ַ� 'a' д�� LCD ��ʾ���ݴ洢��
    }  
}


// �� LCD �� CGRAM д���Զ����ַ�����
void Write_CGRAM(unsigned char a[])
{
    unsigned char k;
    
    // �������� 0x40��ѡ�� CGRAM ��ַ
    LCD_WriteCommand(0x40); 
    
    // ���Զ����ַ�����д�� CGRAM
    for(k = 0; k < 64; k++)
    {
        LCD_WriteData(a[k]);  // д���ַ�����
    }

}

   

void displayCustomCharacter1(const unsigned char pattern[8]) 
{
    unsigned char row, col;

    // ���Զ����ַ�����д��CGRAM
    Write_CGRAM(pattern);

    // ����LCD��ÿһ�к�ÿһ�У���ʾ�Զ����ַ�
    for (row = 0; row < 4; row++) 
    {
        for (col = 0; col < 40; col++) 
        {
            // ���LCD2004������ʼ��ַ��������
            unsigned char position;
            if (row == 0) 
            {
                position = 0x80 + col;   // ��1�е�ַ 0x80 ��ʼ
            } 
            else if (row == 1)
            {
                position = 0xC0 + col;   // ��2�е�ַ 0xC0 ��ʼ
            } 
            else if (row == 2) 
            {
                position = 0x94 + col;   // ��3�е�ַ 0x94 ��ʼ
            } 
            else 
            {
                position = 0xD4 + col;   // ��4�е�ַ 0xD4 ��ʼ
            }

            // ���ù��λ�ò���ʾ�Զ����ַ�
            LCD_WriteCommand(position);
            LCD_WriteData(0x00);  // ��ʾ�洢��CGRAM�еĵ�һ���Զ����ַ�
        }
    }
}
