#include "stm32c0xx_hal.h"



// ��������
#define LCD_RS_PIN GPIO_PIN_15  // RS �������ӵ� GPIOC �ĵ� 15 ����
#define LCD_RS_PORT GPIOC       // RS �������ڵ� GPIO �˿��� GPIOC

#define LCD_RW_PIN GPIO_PIN_0   // RW �������ӵ� GPIOC �ĵ� 0 ����
#define LCD_RW_PORT GPIOC       // RW �������ڵ� GPIO �˿��� GPIOC

#define LCD_E_PIN  GPIO_PIN_14  // E �������ӵ� GPIOC �ĵ� 14 ����
#define LCD_E_PORT GPIOC        // E �������ڵ� GPIO �˿��� GPIOC

#define LCD_CS1_PIN GPIO_PIN_6  // CS1 �������ӵ� GPIOC �ĵ� 6 ����
#define LCD_CS1_PORT GPIOC      // CS1 �������ڵ� GPIO �˿��� GPIOC

#define LCD_CS2_PIN GPIO_PIN_2  // CS2 �������ӵ� GPIOA �ĵ� 2 ����
#define LCD_CS2_PORT GPIOB      // CS2 �������ڵ� GPIO �˿��� GPIOB



// ��ʼ�� GPIO
void GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ���� GPIOC �� GPIOA ��ʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE(); 
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ���� RS ���� (PC15)
    GPIO_InitStruct.Pin = LCD_RS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_RS_PORT, &GPIO_InitStruct);

    // ���� RW ���� (PA0)
    GPIO_InitStruct.Pin = LCD_RW_PIN;
    HAL_GPIO_Init(LCD_RW_PORT, &GPIO_InitStruct);

    // ���� E ���� (PA14)
    GPIO_InitStruct.Pin = LCD_E_PIN;
    HAL_GPIO_Init(LCD_E_PORT, &GPIO_InitStruct);

    // ���� CS1 ���� (PA3)
    GPIO_InitStruct.Pin = LCD_CS1_PIN;
    HAL_GPIO_Init(LCD_CS1_PORT, &GPIO_InitStruct);

    // ���� CS2 ���� (PA4)
    GPIO_InitStruct.Pin = LCD_CS2_PIN;
    HAL_GPIO_Init(LCD_CS2_PORT, &GPIO_InitStruct);
}



void Lcd12864_BusyL(void) 
{
    uint8_t temp = 0xFF; // ��ʼ������ temp Ϊ 0xFF
	
    HAL_GPIO_WritePin(GPIOC, LCD_CS1_PIN, GPIO_PIN_SET); 	// ʹ��ѡ���ź� CS1
    HAL_GPIO_WritePin(GPIOB, LCD_CS2_PIN, GPIO_PIN_RESET); 	// ����ѡ���ź� CS2
    HAL_GPIO_WritePin(GPIOC, LCD_RS_PIN,  GPIO_PIN_RESET); 	// ���� RS �˿�Ϊ 0��ѡ������Ĵ���
    HAL_GPIO_WritePin(GPIOC, LCD_RW_PIN,  GPIO_PIN_SET); 	// ���� RW �˿�Ϊ 1���л�Ϊ��ȡģʽ
    
    // ��ȡ��������
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
						   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    while ((temp & 0x80) == 0x80) { // ѭ��ֱ��æµ��־λ�����
        HAL_GPIO_WritePin(GPIOC, LCD_E_PIN, GPIO_PIN_SET); // ʹ�� LCD12864���� E �˿���Ϊ�ߵ�ƽ��
        HAL_Delay(1); // �ȴ���ȷ���ź��ȶ�
        temp = GPIOA->IDR; // ��ȡ�������ŵ�״̬�� temp
        HAL_GPIO_WritePin(GPIOC, LCD_E_PIN, GPIO_PIN_RESET); // ���� LCD12864���� E �˿���Ϊ�͵�ƽ��
    }
}


void Lcd12864_BusyR(void) {
    uint8_t temp = 0xFF; // ��ʼ������ temp Ϊ 0xFF
    HAL_GPIO_WritePin(GPIOA, LCD_CS1_PIN, GPIO_PIN_RESET); // ����ѡ���ź� CS1
    HAL_GPIO_WritePin(GPIOA, LCD_CS2_PIN, GPIO_PIN_SET); // ʹ��ѡ���ź� CS2
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_RESET); // ���� RS �˿�Ϊ 0��ѡ������Ĵ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_SET); // ���� WR �˿�Ϊ 1���л�Ϊ��ȡģʽ
    
    // ��ȡ��������
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
						   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    while ((temp & 0x80) == 0x80) { // ѭ��ֱ��æµ��־λ�����
        HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET); // ʹ�� LCD12864���� E �˿���Ϊ�ߵ�ƽ��
        HAL_Delay(1); // �ȴ���ȷ���ź��ȶ�
        temp = GPIOA->IDR; // ��ȡ�������ŵ�״̬�� temp
        HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // ���� LCD12864���� E �˿���Ϊ�͵�ƽ��
    }
}




extern uint8_t column;
extern uint8_t Page;

void SetPage_Column(void) {
    uint8_t x, y;

    // �����е�ַ�ĸ� 2 λѡ������
    switch (column & 0xC0) {
        case 0:
            Lcd12864_BusyL(); // ������벿�� 0-63
            break;
        case 0x40:
            Lcd12864_BusyR(); // �����Ұ벿�� 64-127
            break;
    }

    // �����е�ַ (y)
    y = (column & 0x3F) | 0x40; // ������ 6 λ�������е�ַ��׼ֵ 0x40

    // ����ҳ��ַ (x)
    x = (Page & 0x07) | 0xB8;   // ������ 3 λ������ҳ��ַ��׼ֵ 0xB8

    // ����ҳ��ַ�� LCD
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_RESET); // RS = 0��ѡ������Ĵ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_RESET); // WR = 0��дģʽ
    GPIOA->ODR = x; // ��ҳ��ַд�����ݶ˿�
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET); // ʹ�� LCD
    HAL_Delay(1); // ȷ���ź��ȶ�
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // ���� LCD
    HAL_Delay(1); // ȷ���ź��ȶ�

    // �����е�ַ�� LCD
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_RESET); // RS = 0��ѡ������Ĵ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_RESET); // WR = 0��дģʽ
    GPIOA->ODR = y; // ���е�ַд�����ݶ˿�
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET); // ʹ�� LCD
    HAL_Delay(1); // ȷ���ź��ȶ�
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // ���� LCD
    HAL_Delay(1); // ȷ���ź��ȶ�
}


void WriteCommand_L(uint8_t Command) {
    // �ȴ� LCD ׼����
    Lcd12864_BusyL();
    
    // ѡ�������
    HAL_GPIO_WritePin(GPIOA, LCD_CS1_PIN, GPIO_PIN_SET); // CS1 = 1
    HAL_GPIO_WritePin(GPIOA, LCD_CS2_PIN, GPIO_PIN_RESET); // CS2 = 0
    
    // ������д�����ݶ˿�
    GPIOA->ODR = Command; // ������͵����ݶ˿�

    // ��������
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_RESET); // RS = 0��ѡ������Ĵ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_RESET); // WR = 0��дģʽ
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET); // ʹ�� LCD
    HAL_Delay(1); // �ȴ���ȷ���ź��ȶ�
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // ���� LCD
    HAL_Delay(1); // �ȴ���ȷ���ź��ȶ�
}






void WriteCommand_R(uint8_t Command) {
    // �ȴ� LCD ׼����
    Lcd12864_BusyR();
    
    // ѡ���Ұ���
    HAL_GPIO_WritePin(GPIOA, LCD_CS1_PIN, GPIO_PIN_RESET); // CS1 = 0
    HAL_GPIO_WritePin(GPIOA, LCD_CS2_PIN, GPIO_PIN_SET);   // CS2 = 1
    
    // ������д�����ݶ˿�
    GPIOA->ODR = Command; // ������͵����ݶ˿�

    // ��������
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_RESET); // RS = 0��ѡ������Ĵ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_RESET); // WR = 0��дģʽ
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET);   // ʹ�� LCD
    HAL_Delay(1); // �ȴ���ȷ���ź��ȶ�
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // ���� LCD
    HAL_Delay(1); // �ȴ���ȷ���ź��ȶ�
}




uint8_t ReadDate(void) {
    uint8_t Date;
    
    // ����ҳ���е�ַ
    SetPage_Column();
    
    // ѡ�����ݼĴ���
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_SET); // RS = 1��ѡ�����ݼĴ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_SET); // WR = 1����ģʽ
    
    // �����ݶ˿�����Ϊ����̬����ȡ����ǰ׼����
    GPIOA->ODR = 0xFF; // �������ݶ˿�Ϊ�ߵ�ƽ
    
    // ʹ�� LCD
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET); // E = 1
    HAL_Delay(1); // ȷ���ź��ȶ�
    
    // ��ȡ����
    Date = GPIOA->IDR; // �����ݶ˿ڶ�ȡ����
    
    // ���� LCD
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // E = 0
    
    // ����ѡ���ź�
    HAL_GPIO_WritePin(GPIOA, LCD_CS1_PIN, GPIO_PIN_RESET); // CS1 = 0
    HAL_GPIO_WritePin(GPIOA, LCD_CS2_PIN, GPIO_PIN_RESET); // CS2 = 0
    
    return Date;
}



void WriteDate(uint8_t Date) {
    // ����ҳ���е�ַ
    SetPage_Column();
    
    // ѡ�����ݼĴ���
    HAL_GPIO_WritePin(GPIOA, LCD_RS_PIN, GPIO_PIN_SET); // RS = 1��ѡ�����ݼĴ���
    HAL_GPIO_WritePin(GPIOA, LCD_RW_PIN, GPIO_PIN_RESET); // WR = 0��дģʽ
    
    // ������д�����ݶ˿�
    GPIOA->ODR = Date; // �����ݷ��͵����ݶ˿�
    
    // ʹ�� LCD
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_SET); // E = 1
    HAL_Delay(1); // ȷ���ź��ȶ�
    
    // ���� LCD
    HAL_GPIO_WritePin(GPIOA, LCD_E_PIN, GPIO_PIN_RESET); // E = 0
    
    // ����ѡ���ź�
    HAL_GPIO_WritePin(GPIOA, LCD_CS1_PIN, GPIO_PIN_RESET); // CS1 = 0
    HAL_GPIO_WritePin(GPIOA, LCD_CS2_PIN, GPIO_PIN_RESET); // CS2 = 0
}


void Lcd12864_Init(void) {
    // ��ʼ�� LCD
    // ѡ�������
    HAL_GPIO_WritePin(GPIOA, LCD_CS1_PIN, GPIO_PIN_SET); // CS1 = 1
    HAL_GPIO_WritePin(GPIOA, LCD_CS2_PIN, GPIO_PIN_RESET); // CS2 = 0
    
    // ��ʾ������
    WriteCommand_L(0x3F);
    WriteCommand_R(0x3F);
    
    // ��ʾ��ʼ������
    WriteCommand_L(0xC0);
    WriteCommand_R(0xC0);
    
    // ��ʾ������
    WriteCommand_L(0x3F);
    WriteCommand_R(0x3F);
    
    // ��ʼ�� P1 Ϊ����ģʽ�����谴�����ӵ� P1 ��
    // �� STM32 ������ GPIO Ϊ����ģʽ�Ĵ���Ӧ�� GPIO ��ʼ��ʱ����
    // ������谴��������ĳ�� GPIO �˿ڣ����� GPIOB
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOB_CLK_ENABLE(); // ʹ�� GPIOB ʱ��
    
    GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | 
						   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // ����Ϊ����ģʽ
    GPIO_InitStruct.Pull = GPIO_NOPULL; // ��ʹ����������������
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}



// ���� Page �� column �������ʵ���λ������
extern uint8_t Page;
extern uint8_t column;

void Clear(void) {
    // �����Ļ
    Page = 0;   // ��ʼ��ҳΪ0
    column = 0; // ��ʼ����Ϊ0
    
    for (Page = 0; Page < 8; Page++) {          // ��������ҳ
        for (column = 0; column < 128; column++) { // ����������
            WriteDate(0); // д��0������
        }
    }
}




// ���� Page �� column �������ʵ���λ������
extern uint8_t Page;
extern uint8_t column;

void Showpicture(uint8_t DotByte, uint8_t DotByte1) {
    Page = 0; // ��ʼ��ҳΪ0
    column = 0; // ��ʼ����Ϊ0
    
    for (Page = 0; Page < 8; Page++) { // ��������ҳ
        for (column = 0; column < 128; column++) { // ����������
            WriteDate(DotByte); // д���һ�������ֽ�
            column++; // �кŵ���
            WriteDate(DotByte1); // д��ڶ��������ֽ�
        }
    }
}




