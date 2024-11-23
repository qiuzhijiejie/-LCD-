#ifndef __LCD4004_H__
#define __LCD4004_H__
#define LCD_DataPort P1  

void Delay(xms);
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Init();
void LCD_Clear();
void LCD_SetCursor(unsigned int Line, unsigned int Column);
void LCD_ShowString(unsigned char Line, unsigned char Column, char* String);
void LCD_USER_ShowString(unsigned char Line, unsigned char Column, unsigned char i);
void Busy();
unsigned int ReadKey1();
unsigned char LCD_Readdata(void) ;
void displayCustomCharacter1(const unsigned char pattern[8]) ;
void write_CGROM(unsigned char a);
void Write_DDRAM(unsigned char a);
void Write_CGRAM(unsigned char a[]);
#endif


