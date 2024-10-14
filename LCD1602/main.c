#include <REGX52.H>
#include "LCD1602.h"

sbit LCD_RS = P3^0; 
sbit LCD_RW = P3^1;
sbit LCD_EN = P3^2;
sbit   KEY  = P2^0;	



unsigned char mode=0;


unsigned char row, col;
void displayCustomCharacter()
{
    // �����Զ����ַ���ÿ���ַ�ռ8�ֽڣ�16���Ʊ�ʾ (�Լ򵥵�Ц��Ϊ��)
//unsigned char customChar[8] = {0x00, 0x0A, 0x1F, 0x11, 0x0A, 0x0E, 0x00, 0x00};
unsigned char customChar7[8] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00}; // ���ľ���
unsigned char pattern2[8] = {0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A}; // �෴�����̸���ʽ

    // ���Զ����ַ�����д��CGRAM
    Write_CGRAM(pattern2);
		
    // ���ù��λ�õ�LCD�ϵ�ĳ���ط�������ʾ�Զ����ַ�
        for (  row = 0; row < 2; row++) {
			for (  col = 0; col < 16; col++) {
     // ���ù��λ�ã�ÿ�е�ַ��ͬ
    unsigned char position = 0x80 + (row * 0x40) + col;  // 0x80 �ǵ�һ����ʼ��ַ, 0xC0 �ǵڶ�����ʼ��ַ
    LCD_WriteCommand(position);
    LCD_WriteData(0x00);      // ��ʾ�洢��CGRAM�еĵ�һ���Զ����ַ�
	}	
		}	
}





unsigned char row, col;
void displayCustomCharacter1()
{
    // �����Զ����ַ���ÿ���ַ�ռ8�ֽڣ�16���Ʊ�ʾ (�Լ򵥵�Ц��Ϊ��)

unsigned char pattern1[8] = {0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15}; // ���̸���ʽ


    // ���Զ����ַ�����д��CGRAM
    Write_CGRAM(pattern1);
		
    // ���ù��λ�õ�LCD�ϵ�ĳ���ط�������ʾ�Զ����ַ�
        for (  row = 0; row < 2; row++) {
			for (  col = 0; col < 16; col++) {
     // ���ù��λ�ã�ÿ�е�ַ��ͬ
    unsigned char position = 0x80 + (row * 0x40) + col;  // 0x80 �ǵ�һ����ʼ��ַ, 0xC0 �ǵڶ�����ʼ��ַ
    LCD_WriteCommand(position);
    LCD_WriteData(0x00);      // ��ʾ�洢��CGRAM�еĵ�һ���Զ����ַ�
	}	
		}	
}


int main() 
{

	LCD_Init(); // ��ʼ��LCD1602
	LCD_Clear();
	     
			displayCustomCharacter();
			Delay(50);
            displayCustomCharacter1();  
            Delay(50);
            HD44780_DisplayChar(0x48);  
            Delay(50);
            HD44780_DisplayChar(0x4b);  
			Delay(50);
            HD44780_DisplayChar(0x5d);  
			Delay(50);
            HD44780_DisplayChar(0x23);  
			Delay(50);
		    HD44780_DisplayChar(0xff); 
			Delay(50);
            HD44780_DisplayChar(0x24); 
	
		while (1) 
	{

			//����1
			if (ReadKey1()) {
			mode++;
			mode %= 8; // ȷ�� mode ��ֵ�� 0 ��  ֮��ѭ��
			//LCD_Clear(); 
				
				
		// ֱ�Ӹ��� mode ��ֵ��ʾͼ�������ٵȴ�ͼ�����	
		switch (mode) {
        case 1:
            
			displayCustomCharacter();
            break;
        case 2:
             displayCustomCharacter1();  
            break;
        case 3:
            HD44780_DisplayChar(0x48);  
            break;
        case 4:
            HD44780_DisplayChar(0x4b);  
            break;
        case 5:
            HD44780_DisplayChar(0x5d);  
            break;
        case 6:
            HD44780_DisplayChar(0x23);  
            break;
		case 7:
		    HD44780_DisplayChar(0xff); 
			break;
        default:
            HD44780_DisplayChar(0x24);  
            break;
    }


	}
			

		
	



}

	}

