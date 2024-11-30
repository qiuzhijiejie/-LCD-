#ifndef LCD12864_H
#define LCD12864_H

#include "stm32c0xx_hal.h"

// LCD �������Ŷ���
#define LCD_CS1_PIN GPIO_PIN_6
#define LCD_CS2_PIN GPIO_PIN_2
#define LCD_RS_PIN GPIO_PIN_15
#define LCD_RW_PIN GPIO_PIN_0
#define LCD_E_PIN  GPIO_PIN_14
#define LCD_DATA_PORT GPIOA // �������ż��趼������GPIOA��

// ��������
void Lcd12864_Init(void);        // ��ʼ�� LCD
void WriteCommand_L(uint8_t Command); // д�����ָ��
void WriteCommand_R(uint8_t Command); // д�Ұ���ָ��
void WriteDate(uint8_t Date);    // д����
uint8_t ReadDate(void);          // ������
void SetPage_Column(void);       // ���ù��λ�ã�ҳ����
void Clear(void);                // ����
void Showpicture(uint8_t DotByte, uint8_t DotByte1); // ��ʾͼ��

#endif // LCD12864_H
