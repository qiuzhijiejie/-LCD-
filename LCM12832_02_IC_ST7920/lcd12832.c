#include <INTRINS.H>   
#include <reg52.h>
#include "lcd12832.h"
#include "picture.h"
sbit RS   = P3^0;             
sbit RW   = P3^1;                  
sbit E    = P3^2;              
sbit KEY     = P2^0; 

unsigned char ROW,COL;             
        

void charlcdfill(unsigned int c)        //������ʾA�����ASCII�ַ��ӳ���
{   for(ROW=COL=0;1;)
    {   putchar(c);                     //��λд�ַ�
        if((ROW==0) && (COL==0)) break;
    }
}

void putchar(unsigned int c)            //��λд�ַ��ӳ���
{   unsigned char d;
    if(c>128)                           //�ַ������128��ʾΪ����
    {   if( (ROW&0x1)==1 )            //д����ʱ,ROW�ַ�λ��������λ��,��
        {   lcdwd(' ');                 //�Զ�����һ���ո���������ʾ����
            charcursornext();           //���ַ�λ��Ϊ��һ����Чλ��
        }
        charlcdpos();
        if((c&0xff00)==0xff00)          //����λ�ֽ�Ϊ0FFH���ʾΪ�Զ����ַ�
            c=0xffff-c;                 //��ת��ΪST7920���ַ���
        lcdwd(c/256);                   //д��λ�ַ�
        charcursornext();
        lcdwd(c&0xff);                  //д��λ�ַ�
        charcursornext();
    }
    else                                //�ַ���С��128��ʾΪASCII�ַ�
    {   charlcdpos();
        if( (ROW&0x1)==1 )            //дASCII�ַ�ʱ,ROW�ַ�λ��������λ��,��
        {   d=lcdrd();                  //����λ�ַ�
            charlcdpos();
            lcdwd(d);                   //����д��λ�ַ�
            lcdwd(c);
        }
        else
        {   lcdwd(c);                   //дASCII�ַ�ʱ,ROW�ַ�λ����ż��λ��,��
            lcdwd(' ');                 //ֱ��д��,ͬʱ�Զ�����һ���ո�.
        }
        charcursornext();               //���ַ�λ��Ϊ��һ����Чλ��
    }
}

void putstr(unsigned char code *s)      //��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
{   unsigned int c;
    while(1)
    {   c=*s;
        s++;
        if(c==0) break;
        if(c<128)
            putchar(c);
        else
        {   putchar(c*256+*s);
            s++;
        }
    }
}

void putstrxy(unsigned char cx,unsigned char cy,unsigned char code *s)
{                                       //��(cx,cy)�ַ�λ��д�ַ����ӳ���
    ROW=cx;                           //�õ�ǰXλ��Ϊcx
    COL=cy;                           //�õ�ǰYλ��Ϊcy
    putstr(s);
}

void setcharcgram(unsigned char cindex,unsigned char code *s)
{   unsigned char i;
    lcdwc(0x34);                        //����ָ�,ͼ��ģʽ�ر�
    lcdwc(0x02);                        //SR=0 ����CGRAM
    lcdwc(0x30);                        //�ָ�Ϊ����ָ�
    lcdwc( ((cindex&0x3)<<4) | 0x40);   //����CGRAM��ַ
    for(i=0;i<32;i++,s++)               //д��������
        lcdwd(*s);
}

void putsizeimage(unsigned char XSIZE,unsigned char YSIZE,unsigned char code *s)
{  unsigned char lx,ly,x;
   x=ROW;
   for(ly=0;ly<YSIZE;ly++,COL++)
   {  for(ROW=x,lx=0;lx<XSIZE;)
      {  if((ROW&0x08)==0) glcdpos();
         lcdwd(*s);
         s++;
         lx+=8;
         ROW+=8;
      }
   }
   ROW=x;
}

void putimage(unsigned char code *s)    //��ʾͼ���ӳ���
{   unsigned char XSIZE,YSIZE;
    XSIZE=*s;
    s++;
    YSIZE=*s;
    s++;
    putsizeimage(XSIZE,YSIZE,s);
}

void charlcdpos(void)                   //���������(ROW,COL)�ڲ�RAM��ַ���ӳ���
{  unsigned char ddaddr;
   ROW&=0xf;                          //Xλ�÷�Χ(0��15)
   ddaddr=ROW/2;
    if(COL==0)                        //(��һ��)X: ��0----15���ַ�
        lcdwc(ddaddr|0x80);             //    DDRAM:  80----87H
    else if(COL==1)                   //(�ڶ���)X: ��0----19���ַ�
        lcdwc(ddaddr|0x90);             //    DDRAM:  90----07H
    else if(COL==2)                   //(������)X: ��0----19���ַ�
        lcdwc(ddaddr|0x88);             //    DDRAM:  88----8FH
    else                                //(������)X: ��0----19���ַ�
        lcdwc(ddaddr|0x98);             //    DDRAM:  98----9FH
}

void charcursornext(void)               //���ַ�λ��Ϊ��һ����Чλ���ӳ���
{
    ROW++;                            //�ַ�λ�ü�1
    ROW&=0x0f;                        //�ַ�λ��ROW����Ч��ΧΪ(0��15)
    if(ROW==0)                        //�ַ�λ��ROW=0��ʾҪ����
    {   COL++;                        //��λ�ü�1
        COL&=0X3;                     //�ַ�λ��COL����Ч��ΧΪ(0��3)
    }
}

void lcdreset(void)                     //Һ����ʾ��������ʼ���ӳ���
{   lcdwc(0x33);                        //�ӿ�ģʽ����
    delay3ms();                         //��ʱ3MS
    lcdwc(0x30);                        //����ָ�
    delay3ms();                         //��ʱ3MS
    lcdwc(0x30);                        //�ظ��ͻ���ָ�
    delay3ms();                         //��ʱ3MS
    lcdwc(0x01);                        //����������
    delay3ms();                         //��ʱ3MS
    lcdon();                            //����ʾ
}
void delay3ms(void)                     //��ʱ3MS�ӳ���
{ unsigned char i,j,k;
  for(i=0;i<3;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}

void glcdpos(void)                      //д���ͼ�����ڲ�RAMָ���ӳ���
{   
    lcdwc(0x36);                        //��չָ�
    lcdwc((COL & 0x1F) | 0x80);       //��Y��ַ (Y��Χ������ 0~31)
    lcdwc((ROW / 16) | 0x80);         //��X��ַ (ɾ���� COL �� 32 ����߼�)
    lcdwc(0x30);                        //�ָ�Ϊ����ָ�
}

void lcdon(void)                        //LCD��ʾ�����ӳ���
{   lcdwc(0x30);                        //����Ϊ����ָ�
    lcdwc(0x0c);
}

void lcdoff(void)                       //LCD��ʾ�ر��ӳ���
{   lcdwc(0x30);                        //����Ϊ����ָ�
    lcdwc(0x08);
}

void lcdgraphon(void)                  //��ͼ������ʾ�����ӳ���
{   lcdwc(0x36);
    lcdwc(0x30);                        //�ָ�Ϊ����ָ�
}

void lcdgraphoff(void)                  //��ͼ������ʾ�ر��ӳ���
{   lcdwc(0x34);
    lcdwc(0x30);                        //�ָ�Ϊ����ָ�
}

unsigned char lcdrd(void)               //��Һ����ʾ������������
{   unsigned char d;
    lcdwaitidle();                      //ST7920Һ����ʾ������æ���
    RS=1;                            //RS=1 RW=1 E=������
    RW=1;
    E=1;
    _nop_();
    d=P1;
    E=0;
    return d;
}

void lcdwd(unsigned char d)             //��Һ����ʾ������д����
{   lcdwaitidle();                      //ST7920Һ����ʾ������æ���
    P1=d;
    RS=1;                            //RS=1 RW=0 E=������
    RW=0;
    E=1;
    _nop_();
    E=0;
}

void lcdwc(unsigned char c)             //��Һ����ʾ��������ָ��
{   lcdwaitidle();                      //ST7920Һ����ʾ������æ���
    P1=c;
    RS=0;                            //RS=0 RW=0 E=������
    RW=0;
    E=1;
    _nop_();
    E=0;
}

void lcdwaitidle(void)                  //������æ����ӳ���
{   unsigned char i;
    P1=0xff;
    RS=0;
    RW=1;
    E=1;
    for(i=0;i<20;i++)                   //
        if( (P1&0x80) != 0x80 ) break;  //D7=0 �����˳�
    E=0;
}

void exdelay(void)                      //��ʾ��ʱ�ӳ���
{ unsigned char i,j,k;                  //��ʱԼ300mS
  for(i=0;i<30;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}



void glcdfill(unsigned char d)          //������ʾd������������ӳ���
{   unsigned char i;
    ROW=0;
    COL=0;
    while(COL<32)
    {   glcdpos();
        for(i=0;i<16;i++)
            lcdwd(d);
        COL++;
    }
    COL=0;
}

void glcdfill_with_params(unsigned char oddData, unsigned char evenData)
{
    unsigned char i;
    ROW = 0;
    COL = 0;

    while (COL < 32)  // ������Ļ�� 32 ��
    {
        glcdpos();  // ���õ�ǰ�е���ʾ��ַ

        for (i = 0; i < 16; i++)  // ������ǰ�е�16�ֽ�
        {
            if (COL % 2 == 0)  // ż����
            {
                lcdwd(evenData);  // д��ż��������
            }
            else  // ������
            {
                lcdwd(oddData);  // д������������
            }
        }

        COL++;  // �л�����һ��
    }
    COL = 0;  // ���� Y ����
}

unsigned char key()
{
	if(KEY==0)
	{
		exdelay();
		while(KEY==0);
		return 1;
	}
	return 0;
}

void HandleKey() 
{
	unsigned char mode;
	
		if (key()) 
	  {  
		mode++;
		mode %= 7;			
		switch (mode) 
	  {
        case 0:            
			glcdfill_with_params(0xAA,0xAA);break;
        case 1:
            glcdfill_with_params(0x55,0xAA);break;
        case 2:
            glcdfill_with_params(0xAA,0x55);break;
        case 3:
            glcdfill_with_params(0x00,0xFF);break;
        case 4:
            glcdfill_with_params(0xFF,0x00);break;
        case 5:
            glcdfill_with_params(0x55,0x55);break;
		case 6:
			glcdfill_with_params(0xFF,0xFF);break;

		}
	}
}

void DisplayPatterns() 
{
    static int step = 0; // ��ǰ��ʾͼ������
    switch (step) 
    {
        case 0: glcdfill_with_params(0x00,0xFF); exdelay(); break;
        case 1: glcdfill_with_params(0x55,0xAA); exdelay(); break;
        case 2: glcdfill_with_params(0xAA,0xAA); exdelay(); break;
        case 3: glcdfill_with_params(0xAA,0x55); exdelay(); break;
        case 4: glcdfill_with_params(0x55,0x55); exdelay(); break;
        case 5: glcdfill_with_params(0xFF,0x00); exdelay(); break;
        case 6: glcdfill_with_params(0xFF,0xFF); exdelay(); break;
        case 7: lcdreset();charlcdfill(' ');putstrxy(0,0,"�ǻԿƼ����޹�˾");putstrxy(2,1,"LCM12832_02 "); exdelay(); 
    }
    step++;
    if (step > 7) step = 0; // ѭ��
}
