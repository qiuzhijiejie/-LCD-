#include "LCD2002.h"
#include <REGX52.H>



sbit LCD_RS = P3^0; 
sbit LCD_RW = P3^1;
sbit LCD_EN = P3^2;
sbit   KEY1  =P2^0;	

unsigned int ReadKey1() // ������⺯��
{
    if (KEY1 == 0) 
	{  // ����������
        Delay(1);  // �򵥵�ȥ��������
        if (KEY1 == 0) 
		{  // ��鰴���Ƿ���Ȼ����
            while (KEY1 == 0);  // �ȴ������ͷ�
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
  * @brief  LCD2002д����
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
  * @brief  LCD2002д����
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
  * @brief  LCD2002������
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
  * @brief  LCD2002��ʼ������
  * @param  ��
  * @retval ��
  */
void LCD_Init() 
{
    LCD_WriteCommand(0x38); // ����20��4��ʾ,5X7����,8λ���ݽӿ� 
    LCD_WriteCommand(0x0c); // ��ʾ��,����,��˸��
//	LCD_WriteCommand(0x0f);//��ʾ��,��꿪.��˸��
    LCD_WriteCommand(0x06); // ������дһ���ַ����ַָ���һ,���ƶ�
    LCD_WriteCommand(0x01); // ��긴λ������
	Delay(0.1); 
}

/**
  * @brief  LCD2002����
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
  * @brief  LCD2002���ù��λ��
  * @param  Line ��λ�ã���Χ��1~2
  * @param  Column ��λ�ã���Χ��1~20
  * @retval ��
  */
void LCD_SetCursor(unsigned int Line, unsigned int Column) 
{
    // ȷ����ֵ��0-19֮��
    if (Column >= 20) Column = 0;
    // ȷ����ֵ��0-2֮��
    Line &= 0x01;  // ���� Y λ���� 0 �� 3 ֮��		
    if (Line == 0) 
    {
        LCD_WriteCommand(0x80 | Column);  // ��һ��
    } 
    else  
    {
        LCD_WriteCommand(0xC0 | Column);  // �ڶ���
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
 * @brief LCD2002��ʾ�ַ���
 * @param Line 0-2�� Column 0-19�� *String �����ַ�""
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


//ÿ��д����ַ� a �ǵ�����
void write_CGROM(unsigned char a)
{
    unsigned char j;
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
    for (j = 1; j < 40; j++) 
    {
        LCD_WriteData(a);    // ��LCDд������ 'a'
        a += 1;              // ����'a'��ͬ������д����һ���ַ�
    }
    
    Delay(1);                // �ٴ���ʱ��ȷ������ȫ��д��
}

/**
 * @brief  ȫ����ʾHD44780 �����ַ�
 * @param  Line 0-3  Column 0-19  ����16����0X...
 * @retval ��
 */
void Write_DDRAM(unsigned char a)
{
    unsigned char j;
    
    LCD_WriteCommand(0x02);  // ����λ���� (���λ�ûص���ʼλ�ã�ͨ����DDRAM����ʼ��ַ)
    Delay(1);               // ��ʱ10����λ (��֮ǰ����ʱ��)

    LCD_WriteCommand(0x80);  // ���ù�굽��1�е���ʼ��ַ (0x80��ӦDDRAM�ĵ�1����ʼ��ַ)
    
    // ���1��д��20����ͬ���ַ�   
    for (j = 0; j < 20; j++) 
    {
        LCD_WriteData(a);    // ���ַ� 'a' д�� LCD ��ʾ���ݴ洢��
    }

    LCD_WriteCommand(0xC0);  // ���ù�굽��2�е���ʼ��ַ (0xC0��ӦDDRAM�ĵ�2����ʼ��ַ)
    
    // ���2��д��20����ͬ���ַ�
    for (j = 0; j < 20; j++) 
    {
        LCD_WriteData(a);    // ���ַ� 'a' д�� LCD ��ʾ���ݴ洢��
    }  
    Delay(1);                // ��ʱ��ȷ��������ȫд��
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
    for (row = 0; row < 2; row++) 
    {
        for (col = 0; col < 20; col++) 
        {
            // ���LCD2002������ʼ��ַ��������
            unsigned char position;
            if (row == 0) 
				{
                position = 0x80 + col;   // ��1�е�ַ 0x80 ��ʼ
				} else //if (row == 1) {
                position = 0xC0 + col;   // ��2�е�ַ 0xC0 ��ʼ

            // ���ù��λ�ò���ʾ�Զ����ַ�
            LCD_WriteCommand(position);
            LCD_WriteData(0x00);  // ��ʾ�洢��CGRAM�еĵ�һ���Զ����ַ�
        }
    }
}

unsigned char data pattern1[8] = {0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15}; 
unsigned char data pattern2[8] = {0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A};	
unsigned char data pattern3[8] = {0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15}; 
unsigned char data pattern4[8] = {0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A}; 
unsigned char data pattern5[8] = {0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00}; 
unsigned char data pattern6[8] = {0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F}; 	
unsigned char data pattern7[8] = {0x00, 0x15, 0x00, 0x15, 0x00, 0x15, 0x00, 0x15}; 
void HandleKey() 
{
	unsigned char mode;
	
		if (ReadKey1()) 
	  {  
		LCD_Clear();
		mode++;
		mode %= 10;			
		switch (mode) 
	  {
        case 0:            
			displayCustomCharacter1(pattern1); 
            break;
        case 1:
            displayCustomCharacter1(pattern2);  
            break;
        case 2:
            displayCustomCharacter1(pattern3); 
            break;
        case 3:
           displayCustomCharacter1(pattern4);  
            break;
        case 4:
            displayCustomCharacter1(pattern5);  
            break;
        case 5:
            displayCustomCharacter1(pattern6);  
            break;
		case 6:
			displayCustomCharacter1(pattern7);
			break;
		case 7:
			write_CGROM(0x21); 
		   break;
		case 8:
			write_CGROM(0xA1); 
		   break;
		case 9:
			Write_DDRAM(0xFF); 
		   break;  
		}
	}
}

void DisplayPatterns() 
{
    static int step = 0; // ��ǰ��ʾͼ������
    switch (step) 
    {
        case 0: displayCustomCharacter1(pattern1);  Delay(80); break;
        case 1: displayCustomCharacter1(pattern2);  Delay(80); break;
        case 2: displayCustomCharacter1(pattern3);  Delay(80); break;
        case 3: displayCustomCharacter1(pattern4);  Delay(80); break;
        case 4: displayCustomCharacter1(pattern5);  Delay(80); break;
        case 5: displayCustomCharacter1(pattern6);  Delay(80); break;
        case 6: displayCustomCharacter1(pattern7);  Delay(80); break;
        case 7: write_CGROM(0x21); Delay(80); break;
        case 8: Write_DDRAM(0xCE); Delay(80); break;
        case 9:	LCD_Clear();LCD_ShowString(1,6,"LCM2002_4");LCD_ShowString(0,2,"YeHuiDisplay.com");Delay(80); break;
    }
    step++;
    if (step > 9) step = 0; // ѭ��
}