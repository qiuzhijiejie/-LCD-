#include <INTRINS.H>        
#include <MATH.H>    
#include <ABSACC.H> 
#include <REG52.H> 
#include <STDIO.H> 
#include "LCD12864.H"
#include "HANZI.H"
#include "intrins.h"

#define uint unsigned int
#define uchar unsigned char


sbit KEY = P2^0;  // ��������
uchar mode = 0;  // ģʽ����



unsigned char code BMP3[]; 
unsigned char code BMP4[]; 
unsigned char code font[];
unsigned char code Character[];

void  main(void)
{
	 Delay(20); 
//	 IE=0x81;     //�����ж�ʹ�ܼĴ��� IE ��ֵΪ 0x81��
	 IP=0x01;     //�����ж����ȼ��Ĵ��� IP ��ֵΪ 0x01
	 TCON=0x01;   //���ö�ʱ��/���������ƼĴ��� TCON ��ֵΪ 0x01
//	 int0=1;      //��INT0��������Ϊ�ߵ�ƽ���Ա������������ж�
	 Lcd12864_Init();
	 Clear();
	 
 
while(1)
{
	
	//��������
    if (ReadKey()) {
    mode++;
    mode %= 9; // ȷ�� mode ��ֵ�� 0 �� 8 ֮��ѭ��
	Clear(); 
    // ֱ�Ӹ��� mode ��ֵ��ʾͼ�������ٵȴ�ͼ�����
    switch (mode) {
        case 0:
        LcmPutDots1(0x98);
        break;
    case 1:
		LcmPutBMP(BMP6); 
        break;
    case 2:
        LcmPutDots1(0xaa);//ż���� 
        break;
    case 3:
        LcmPutDotsOddColumns();//������  
        break;
    case 4:
        LcmPutBMP(BMP9); 
        break;
    case 5:
        LcmPutDotsStars(0x42);//�����岼 
        break;
    case 6:
        LcmPutDotsStars(0xaa);//��ż
        break;
    case 7:
        LcmPutDotsStars(0xa7);  
        break;
	case 8:
        LcmPutBMP(BMP7);  
        break;

    }
}


//LcmPutDotsOddColumns();//������

//LcmPutDotsStars(0x42);//�����岼

//LcmPutDotsStars(0xaa);//��ż

//LcmPutDotsStars(0x55);//��ż

//LcmPutDots1(0xaa);//ż����

//LcmPutDots1(0x55);//������



//Showpicture_VerticalWave(0xAA, 0x55);  // �м������߲��˰㣨�磩
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_Advanced(0x80, 0x40);  // �������м���������
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_Advanced(0x18, 0x3C);  // �������м���������
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_Advanced(0xAA, 0x55);  // �������м���������
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_Advanced(0x18, 0x3C);  // 4��һ��λ
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_Advanced1(0x18, 0x3C);  // �𽥼��ٺͼ���
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_Advanced2(0x80, 0x40);  // ż�����������м���
//Delay(500);  // ͣ��500ms
//Clear();

//Showpicture_CrossCursorEffect(0x80, 0x40);  // �������������������������
//Delay(500);  // ͣ��500ms
//Clear();

//LcmPutBMP(BMP6);  // 
//Delay(500);  // ͣ��500ms
//Clear();

//LcmPutBMP(BMP4);  // 
//Delay(500);  // ͣ��500ms
//Clear();

//LcmPutBMP(BMP5);  // ÷��
//Delay(500);  // ͣ��500ms
//Clear();


//LcmPutBMP(BMP6);
//Delay(500);
//LcmPutBMP(BMP7);//ST��˾
//Delay(500);
//LcmPutBMP(BMP9);



}
}