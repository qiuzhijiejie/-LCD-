#include <REGX52.H>
#include "16032.h"
#include "picture.h"
#include <intrins.h>

sbit RS   = P3^0;                    // RS��Ӧ��Ƭ������
sbit RW   = P3^1;                    // RW��Ӧ��Ƭ������
sbit E    = P3^2;                    // E��Ӧ��Ƭ������
sbit KEY=P2^0;			//����

unsigned char Column; //�з����ַָ��(����setLCDCursor�ӳ���)
unsigned char row;    //�з����ַָ��(����setLCDCursor�ӳ���)

void lcdwaitidle(void)       //������æ����ӳ���
{   unsigned char i;
    P1=0xff;
    RS=0;
    RW=1;
    E=1;
    for(i=0;i<20;i++)//���ѭ�������20��  
	{                
        if( (P1&0x80)!= 0x80 )
		{
			break;  //D7=0 �����˳�
		}
	}
    E=0;
}


unsigned char lcdrd(void)  //��Һ����ʾ������������
{   unsigned char d;
    lcdwaitidle();                  
    RS=1;                        
    RW=1;				   //RW 1: read
    E=1;
    _nop_();
    d=P1;
    E=0;
    return d;
}

void lcdwd(unsigned char d) //��Һ����ʾ������д����
{   lcdwaitidle();            
    P1=d;
    RS=1;                   //RS 1:select data write, read       
    RW=0;					//RW 0: write
    E=1;
    _nop_();
    E=0;
}

void lcdwc(unsigned char c)  //��Һ����ʾ��������ָ��
{   lcdwaitidle();           
    P1=c;
    RS=0;           		 //RS 0:select instruction write,        
    RW=0;
    E=1;
    _nop_();
    E=0;
}


void setLCDCursor(void)           //д���ͼ�����ڲ�RAMָ���ӳ���
{   
	lcdwc(0x36);             //��չָ�
    lcdwc((row&0x1f)|0x80);  //����Y��ַ,��Χ��0~31
    lcdwc((Column/16)|0x80); //����X��ַ
    lcdwc(0x30);             //�ָ�Ϊ����ָ�
}

void lcdon(void)    //LCD��ʾ�����ӳ���
{   
	lcdwc(0x30);    //����Ϊ����ָ�
    lcdwc(0x0c);
}

void lcdoff(void)   //LCD��ʾ�ر��ӳ���
{   lcdwc(0x30);    //����Ϊ����ָ�
    lcdwc(0x08);
}

void lcdgraphon(void) //��ͼ������ʾ�����ӳ���
{   lcdwc(0x36);
    lcdwc(0x30);      //�ָ�Ϊ����ָ�
}

void lcdgraphoff(void) //��ͼ������ʾ�ر��ӳ���
{   lcdwc(0x34);
    lcdwc(0x30);       //�ָ�Ϊ����ָ�
}

void lcdreset(void)                     //Һ����ʾ��������ʼ���ӳ���
{   lcdwc(0x33);                        //�ӿ�ģʽ����
    delay3ms();                         //��ʱ3MS
    lcdwc(0x30);                        //����ָ�
    delay3ms();                         //��ʱ3MS
    lcdwc(0x01);                        //����������
    delay3ms();                         //��ʱ3MS
    lcdwc(0x06);                        //��ʾ����ƶ�����
    lcdon();                            //����ʾ
}

void delay3ms(void)                     //��ʱ3MS�ӳ���
{ unsigned char i,j,k;
  for(i=0;i<3;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}



void fillLCD_OddColumn(unsigned char oddData, unsigned char evenData)  
{
    unsigned char i; 
    while (row < 32)   
    {
        setLCDCursor();   
        if (row % 2 == 0)   
        {
            for (i = 0; i < 20; i++)
                lcdwd(evenData);   
        }
        else   
        {
            for (i = 0; i < 20; i++)
                lcdwd(oddData);   
        }
        row++;   
    }
    row = 0;   
}

void fillLCD(unsigned char d) //������ʾd������������ӳ���
{   
	unsigned char i;
    while(row<32)
    {   
		setLCDCursor();
        for(i=0;i<20;i++)
		{
            lcdwd(d);
		}
        row++;
    }
    row=0;
}



void exdelay(void)                      //��ʾ��ʱ�ӳ���
{ unsigned char i,j,k;                  //��ʱԼ300mS
  for(i=0;i<30;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}


void charlcdfill(unsigned int c)//������ʾST7920�ڲ���CGROMA����
{   for(Column=row=0;1;)
    {   putchar(c);                
		c+=1;
        if((Column==0) && (row==0)) break;
    }
}

void Clean(unsigned int c)        
{  
	for(;;)
    {   putchar(c);            
        if((Column==0) && (row==0)) break;
    }
}

void putchar(unsigned int c) //��λд�ַ��ӳ���
{   unsigned char d;
    if(c>128)                 //�ַ������128��ʾΪ����
    {   if( (Column&0x1)==1 ) //д����ʱ,Column�ַ�λ��������λ��,��
        {   lcdwd(' ');       //�Զ�����һ���ո���������ʾ����
            charcursornext(); //���ַ�λ��Ϊ��һ����Чλ��
        }
        charlcdpos();
        if((c&0xff00)==0xff00)//����λ�ֽ�Ϊ0FFH���ʾΪ�Զ����ַ�
            c=0xffff-c;       //��ת��ΪST7920���ַ���
        lcdwd(c/256);         //д��λ�ַ�
        charcursornext();
        lcdwd(c&0xff);        //д��λ�ַ�
        charcursornext();
    }
    else                      //�ַ���С��128��ʾΪASCII�ַ�
    {   charlcdpos();
        if( (Column&0x1)==1 ) //дASCII�ַ�ʱ,Column�ַ�λ��������λ��,��
        {   d=lcdrd();        //����λ�ַ�
            charlcdpos();
            lcdwd(d);         //����д��λ�ַ�
            lcdwd(c);
        }
        else
        {   lcdwd(c);         //дASCII�ַ�ʱ,Column�ַ�λ����ż��λ��,��
            lcdwd(' ');       //ֱ��д��,ͬʱ�Զ�����һ���ո�.
        }
        charcursornext();     //���ַ�λ��Ϊ��һ����Чλ��
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
    Column=cx;                           //�õ�ǰXλ��Ϊcx
    row=cy;                           //�õ�ǰYλ��Ϊcy
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
   x=Column;
   for(ly=0;ly<YSIZE;ly++,row++)
   {  for(Column=x,lx=0;lx<XSIZE;)
      {  if((Column&0x08)==0) setLCDCursor();
         lcdwd(*s);
         s++;
         lx+=8;
         Column+=8;
      }
   }
   Column=x;
}

void putimage(unsigned char code *s)    //��ʾͼ���ӳ���
{   unsigned char XSIZE,YSIZE;
    XSIZE=*s;
    s++;
    YSIZE=*s;
    s++;
    putsizeimage(XSIZE,YSIZE,s);
}

void charlcdpos(void)       //���������(Column,row)�ڲ�RAM��ַ���ӳ���
{   unsigned char ddaddr;
    if(Column>19) Column=0; //�ַ�λ��Column����Ч��ΧΪ(0��19)
    row&=0X1;               //�ַ�λ��row����Ч��ΧΪ(0��1)
    ddaddr=Column/2;
    if(row==0)              //(��һ��)X: ��0----19���ַ�
        lcdwc(ddaddr|0x80); // DDRAM:  80----89H
    else                    //(�ڶ���)X: ��0----19���ַ�
        lcdwc(ddaddr|0x90); //    DDRAM:  90----99H
}

void charcursornext(void)    //���ַ�λ��Ϊ��һ����Чλ���ӳ���
{
    Column++;                //�ַ�λ�ü�1
    if(Column>19) Column=0;  //�ַ�λ��Column����Ч��ΧΪ(0��19)
    if(Column==0)            //�ַ�λ��Column=0��ʾҪ����
    {   row++;               //��λ�ü�1
        row&=0X1;            //�ַ�λ��row����Ч��ΧΪ(0��1)
    }
}

unsigned char ReadKey() //��������
{
    if (KEY == 0) 
		{  // ����������
			exdelay();  // �򵥵�ȥ��������
			if (KEY == 0) 
				{
					while (KEY == 0);  // �ȴ������ͷ�
					return 1;  // ���ذ���������
				}
    }
    return 0;  // ���ذ���û�б�����
}


void HandleKey() 
{
	unsigned char mode;
	
		if (ReadKey()) 
	  {  
		mode++;
		mode %= 7;			
		switch (mode) 
	  {
        case 0:            
			fillLCD_OddColumn(0xAA,0xAA);exdelay(); break;
        case 1:
            fillLCD_OddColumn(0x55,0xAA);exdelay();break;
        case 2:
            fillLCD_OddColumn(0xAA,0x55);exdelay();break;
        case 3:
            fillLCD_OddColumn(0x00,0xFF);exdelay();break;
        case 4:
            fillLCD_OddColumn(0xFF,0x00);exdelay();break;
        case 5:
            fillLCD_OddColumn(0x55,0x55);exdelay();break;
		case 6:
			fillLCD_OddColumn(0xFF,0xFF);exdelay();break;
		}
	}
}

void DisplayPatterns() 
{
    static int step = 0; // ��ǰ��ʾͼ������
    switch (step) 
    {
        case 0: fillLCD_OddColumn(0x00,0xFF);exdelay(); break;
        case 1: fillLCD_OddColumn(0x55,0xAA);exdelay(); break;
        case 2: fillLCD_OddColumn(0xAA,0xAA);exdelay(); break;
        case 3: fillLCD_OddColumn(0xAA,0x55);exdelay(); break;
        case 4: fillLCD_OddColumn(0x55,0x55);exdelay(); break;
        case 5: fillLCD_OddColumn(0xFF,0x00);exdelay(); break;
        case 6: fillLCD_OddColumn(0xFF,0xFF);exdelay(); break;
        case 7: fillLCD_OddColumn(0x00, 0x00);putstrxy(0,0,"�㶫�ǻԿƼ����޹�˾");putstrxy(3,1," LCM16032_03 "); exdelay(); break;
    }
    step++;
    if (step > 7) step = 0; // ѭ��
}