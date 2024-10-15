#include <INTRINS.H>        
#include <MATH.H>    
#include <ABSACC.H> 
#include <REGx52.H> 
#include <STDIO.H> 
#include "LCD12864.H"
#include "HANZI.H"



sbit LCD12864_RS = P3^0; 
sbit LCD12864_RW = P3^1;
sbit LCD12864_E  = P3^2;
sbit CS1=P3^3;       	// �����
sbit CS2=P3^4;		 	// �Ұ���
//sbit LCD12864_RST=P3^5;	//��λ
//sbit int0=P2^0;		//�ж�
sbit KEY=P2^0;			//����


//bit loge=0; 


#define uint unsigned int
#define uchar unsigned char

unsigned char column;  //��
unsigned char Page;    //ҳ
unsigned char code BMP3[]; 
unsigned char code BMP4[]; 
unsigned char code font[];
unsigned char code Character[];



uchar ReadKey() //��������
{
    if (KEY == 1) 
		{  // ����������
			Delay(100);  // �򵥵�ȥ��������
			if (KEY == 1) 
				{
					while (KEY == 1);  // �ȴ������ͷ�
					return 1;  // ���ذ���������
				}
    }
    return 0;  // ���ذ���û�б�����
}



void Lcd12864_BusyL(void) // �������
{    
    uchar temp = 0xFF; // ��ʼ������ temp Ϊ 0xFF
    CS1 = 1;          // ʹ��ѡ���ź� CS1
    CS2 = 0;          // ����ѡ���ź� CS2
    LCD12864_RS = 0;  // ���� RS �˿�Ϊ 0��ѡ������Ĵ���
    LCD12864_RW = 1;  // ���� WR �˿�Ϊ 1���л�Ϊ��ȡģʽ
    P1 = 0xFF;        // ���˿�1����Ϊ 0xFF
    
    while ((temp & 0x80) == 0x80) // ѭ��ֱ��æµ��־λ�����
    {
        LCD12864_E = 1;  // ʹ�� LCD12864���� E �˿���Ϊ�ߵ�ƽ��
        //_nop_();         // �ղ���������������ʱ
        temp = P1;       // ��ȡ�˿�1��״̬�� temp
        LCD12864_E = 0;  // ���� LCD12864���� E �˿���Ϊ�͵�ƽ��
    }
}



void Lcd12864_BusyR(void) // ���Ұ���
{
    uchar temp = 0xFF;// ��ʼ������ temp Ϊ 0xFF
    CS1 = 0;          // ����ѡ���ź� CS1
    CS2 = 1;          // ʹ��ѡ���ź� CS2
    LCD12864_RS = 0;  // ���� RS �˿�Ϊ 0��ѡ������Ĵ���
    LCD12864_RW = 1;  // ���� WR �˿�Ϊ 1���л�Ϊ��ȡģʽ
    P1 = 0xFF;        // ���˿�1����Ϊ 0xFF
    
    while ((temp & 0x80) == 0x80) // ѭ��ֱ��æµ��־λ�����
    {
        LCD12864_E = 1;  // ʹ�� LCD12864���� E �˿���Ϊ�ߵ�ƽ��
        //_nop_();         // �ղ���������������ʱ
        temp = P1;       // ��ȡ�˿�1��״̬�� temp
        LCD12864_E = 0;  // ���� LCD12864���� E �˿���Ϊ�͵�ƽ��
    }
}



void SetPage_Column(void)   // ���ù��λ�ã�ҳ����
{   
    unsigned char x, y;

    // �����е�ַ�ĸ� 2 λѡ������
    switch (column & 0xC0)   /*0X1100 0000,���ֵ�6λ����0-63*/
			{
        case 0:    Lcd12864_BusyL(); break;   //0X0000������벿��0-63
        case 0x40: Lcd12864_BusyR(); break;   //0X0100�����Ұ벿��64-127
			}
   
    // �����е�ַ (y)
    y = (column & 0x3f) | 0x40;  //0X0011 1111������ 6 λ�������е�ַ��׼ֵ 0x40

    // ����ҳ��ַ (x)
    x = (Page & 0x07)   | 0xb8;  //0X0000 0111������ 3 λ������ҳ��ַ��׼ֵ 0xb8

    // ����ҳ��ַ�� LCD
    LCD12864_RS = 0;      
    LCD12864_RW = 0;      
    P1 = x;  
    LCD12864_E = 1;   
    //_nop_();   
    LCD12864_E = 0;   
    //_nop_();
    
    // �����е�ַ�� LCD
    LCD12864_RS = 0;      
    LCD12864_RW = 0;      
    P1 = y;  
    LCD12864_E = 1;   
    //_nop_();   
    LCD12864_E = 0;   
    //_nop_();
}


void WriteCommand_L(uint Command)// д��ָ��1-64
{
		  Lcd12864_BusyL();
		  P1 = Command ;   
		  LCD12864_RS = 0;   
		  LCD12864_RW = 0;   
		  LCD12864_E  = 1;   
		  //_nop_();   
		  LCD12864_E  = 0;   
		  //_nop_();
			
}





void WriteCommand_R(uint Command)// д��ָ��65-128
{
		  Lcd12864_BusyR();
		  P1 = Command; 
		  LCD12864_RS = 0;   
		  LCD12864_RW = 0;   
		  LCD12864_E  = 1;   
		  //_nop_();   
		  LCD12864_E  = 0;   
		  //_nop_();
			
}


uchar ReadDate(void)// ������
{	
			uchar Date;
			SetPage_Column();
			LCD12864_RS=1;
			LCD12864_RW=1;
			P1=0xff;
			_nop_(); 
			LCD12864_E=1;
			_nop_();
			Date=P1;
			LCD12864_E=0;
			_nop_();
			CS1=0;
			CS2=0;
			return Date;
}

void WriteDate(uint Date)//д����
{	
			SetPage_Column();
			LCD12864_RS=1;
			LCD12864_RW=0;
			P1 = Date; 
			LCD12864_E=1;
			_nop_(); 
			LCD12864_E=0;
			_nop_();
			CS1=0;
			CS2=0;
}


void Clear(void) // ����
{
		 Page = 0;   
		 column  = 0;   
		 for(Page=0;Page<8;Page++) //ҳ  
		  for(column=0;column<128;column++) //��  
		   WriteDate(0); 
						
}


void Lcd12864_Init(void)//��ʼ��
{
		 WriteCommand_L(0x3f); //��ʾ��
		 WriteCommand_R(0x3f);   
			 
		 WriteCommand_L(0xc0); //��ʾ��ʼ��	P13
		 WriteCommand_R(0xc0);   
			 
		 WriteCommand_L(0x3f); //��ʾ��  
		 WriteCommand_R(0x3f);   
	
		 P1 = 0xFF; // ���谴������P1�ڣ�����Ϊ����
}




void Showpicture(uchar DotByte,uchar DotByte1 ) //������Щλ����д��ָ����ͼ������  
{   
		Page 	= 0;   
		column  = 0;   
			 for(Page=0;Page<8;Page++)//�����أ��� 8 ҳ��ɣ�
			 {   
					for(column=0;column<128;column++) //128 ��  
					{   
					 WriteDate( DotByte );
					 column++;
					 WriteDate( DotByte1 );  
					} 
			
				}   
}





void Showpicture_VerticalWave(uchar DotByte, uchar DotByte1)//�м������߲��˰�
{
    unsigned char i;
    unsigned char mid_col = 64;    // ��Ļ�м���
    unsigned char delay_time = 50; // �ӳ�ʱ�䣬���ڿ��Ʋ����ٶ�

    // ���м������»��Ʋ���ͼ��
    for (i = 0; i < 64; i++) 
    {
        // ���ϻ��Ʋ���ͼ��
        for (Page = 0; Page < 8; Page++) 
        {
            SetPage_Column();
            for ( column = 0; column < 128; column++) 
            {
                // �����ǰ���ڲ�����Χ�ڣ�����ʾ��ͼ��
                if ((column >= mid_col - i) && (column <= mid_col + i)) 
                {
                    WriteDate(DotByte);
                }
                else 
                {
                    WriteDate(0x00); // ��䱳��ɫ
                }
            }
        }
        
        // ���»��Ʋ���ͼ��
        for ( Page = 0; Page < 8; Page++) 
        {
            SetPage_Column();
            for ( column = 0; column < 128; column++) 
            {
                // �����ǰ���ڲ�����Χ�ڣ�����ʾ��ͼ��
                if ((column >= mid_col - i) && (column <= mid_col + i)) 
                {
                    WriteDate(DotByte1);
                }
                else 
                {
                    WriteDate(0x00); // ��䱳��ɫ
                }
            }
        }

        // ����ӳ٣��Ա��Ӿ�Ч������
        Delay(delay_time);
    }

    // �����Ļ����
    for ( Page = 0; Page < 8; Page++) 
    {
        SetPage_Column();
        for (column = 0; column < 128; column++) 
        {
            WriteDate(0); // �������
        }
    }
}







/*�м�������ͬʱչ����Ч��*/
void Showpicture_Advanced(uchar DotByte, uchar DotByte1)
{
    unsigned char col;
    unsigned char mid_col = 64;  // �м��У���ȵ�һ��
    unsigned char delay_time = 1000; // �����ӳ�ʱ�䣬�ӿ��ٶ�

    // ��������ҳ
    for (Page = 0; Page < 8; Page++)
    {
        for (col = 0; col <= mid_col; col++)
        {
            // ͬʱ���м���������һ���ͼ��
            column = mid_col - col;
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);

            column = mid_col + col;
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);
        }

        // Ϊ�˼ӿ��ٶȣ������ӳ�
        Delay(delay_time);
    }

    // �����Ļ����
    for (Page = 0; Page < 8; Page++)
    {
        for (col = 0; col < 128; col++)
        {
            column = col;
            SetPage_Column(); 
            WriteDate(0); // �������
        }
    }
}




/* ���������м�ͬʱ������Ч���������У����𽥼��ٺͼ��� */
void Showpicture_Advanced1(uchar DotByte, uchar DotByte1)
{
    unsigned char col;
    unsigned char mid_col 		= 64;   // �м��У���ȵ�һ��
    unsigned char delay_time 	= 1000; // ��ʼ�ӳ�ʱ��
    unsigned char speed_factor 	= 10;   // ����/��������

    // ���м�������չ����ͼ��
    for (Page = 0; Page < 8; Page++)
    {
        for (col = 0; col <= mid_col; col++)
        {
            // ���м���������չ
            column = mid_col + col; // ���м�������չ
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);

            column = mid_col - col; // ���м�������չ
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);

            // ��̬�����ӳ�ʱ�䣬�𽥼���
            delay_time = delay_time > speed_factor ? delay_time - speed_factor : 1;
            Delay(delay_time);
        }
        // �����ӳ�ʱ����׼����һҳ�Ļ���
        delay_time = 1000;
    }

    // �����Ļ���ݣ����������м����������
    delay_time = 100; // ��С��ʼ�ӳ�ʱ�䣬�ӿ�����ٶ�
    for (Page = 0; Page < 8; Page++)
    {
        for (col = 0; col <= mid_col; col++)
        {
            // ���м��������������
            column = mid_col + col; // ���м�������չ���
            SetPage_Column(); 
            WriteDate(0); // �������

            column = mid_col - col; // ���м�������չ���
            SetPage_Column(); 
            WriteDate(0); // �������

            // ��̬�����ӳ�ʱ�䣬�𽥼���
            delay_time += speed_factor;
            Delay(delay_time);
        }
    }
}





/* ���������м�ͬʱ������Ч����ż���У� */
void Showpicture_Advanced2(uchar DotByte, uchar DotByte1)
{
    unsigned char col;
    unsigned char mid_col = 64;  // �м��У���ȵ�һ��
    unsigned char delay_time = 1000; // �����ӳ�ʱ�䣬�ӿ��ٶ�

    // ��������ҳ
    for (Page = 0; Page < 8; Page+=2)
    {
        for (col = 0; col <= mid_col; col++)
        {
            // ͬʱ����ߺ��ұ����м����ͼ��
            column = col; // ��������м�
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);

            column = 127 - col; // ���ұ����м�
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);
        }

        // Ϊ�˼ӿ��ٶȣ������ӳ�
        Delay(delay_time);
    }

    // �����Ļ����
    for (Page = 0; Page < 8; Page++)
    {
        for (col = 0; col < 128; col++)
        {
            column = col;
            SetPage_Column(); 
            WriteDate(0); // �������
        }
    }
}





/*�м����ĸ������������ң�ͬʱչ����ʮ�ֹ��Ч��*/

void Showpicture_CrossCursorEffect(uchar DotByte, uchar DotByte1)
{
    unsigned char i;
    unsigned char mid_col = 64;  // ��Ļ�м���
    unsigned char mid_Page = 4;  // ��Ļ�м�ҳ
    unsigned char delay_time = 50; // �ӳ�ʱ�䣬���ڿ��ƹ���ƶ��ٶ�

    // ���м����ĸ�����ͬʱ����ͼ��
    for (i = 0; i <= mid_Page; i++)
    {
        // ���ϻ���ͼ��
        Page = mid_Page - i;
        for (column = mid_col - i; column <= mid_col + i; column++)
        {
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);
        }

        // ���»���ͼ��
        Page = mid_Page + i;
        for (column = mid_col - i; column <= mid_col + i; column++)
        {
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);
        }

        // �������ͼ��
        column = mid_col - i;
        for (Page = mid_Page - i; Page <= mid_Page + i; Page++)
        {
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);
        }

        // ���һ���ͼ��
        column = mid_col + i;
        for (Page = mid_Page - i; Page <= mid_Page + i; Page++)
        {
            SetPage_Column(); // ����ҳ����λ��
            WriteDate(DotByte);
            WriteDate(DotByte1);
        }

        // ����ӳ٣��Ա��Ӿ�Ч������
        Delay(delay_time);
    }

    // �����Ļ����
    for (Page = 0; Page < 8; Page++)
    {
        for (column = 0; column < 128; column++)
        {
            SetPage_Column(); 
            WriteDate(0); // �������
        }
    }
}






void LcmPutBMP( uchar *puts )   //��ʾһ��������ͼ��
{   
	 uint X=0;   
	 Page = 0;   
	 column  = 0;   
		 for(Page=0;Page<8;Page++)  //����8ҳ,һҳ8�� 
		 {   
			for(column=0;column<128;column++)//����128�� 
			{   
			 WriteDate( puts[X] );   
			 X++;   
			}   
	 }   
}




unsigned char offset; 
void LcmPutBMPsjw(uchar *puts) //rubbot
{
    uint X = 0;
    int i, j;
    int maxOffset = 8; // ���ƫ����
    unsigned char currentPage;

    for ( offset = 0; offset < maxOffset; offset++) 
    {
        // ÿ�λ���ǰ���´�ͼ����ʼλ�ö�ȡ����
        X = 0;

        // �������е�ҳ��
        for (i = 0; i < 8; i++) 
        {
            currentPage = i;

            // ���õ�ǰҳ����
            SetPage_Column();
            
            // ����һ��ҳ (128��)
            for (j = 0; j < 128; j++) 
            {
                if (currentPage >= offset && currentPage < (8 - offset)) 
                {
                    WriteDate(puts[X]); // д��ͼ������
                } 
                else 
                {
                    WriteDate(0x00); // ��䱳��ɫ
                }
                X++;
            }
        }
        Delay(50); // ���ƽ���Ч�����ٶ�
    }
}

		
void LcmReverseBMPP( unsigned char *puts ) //ȡ��  
{   
 uint X=0;   
 Page = 0;   
 column  = 0;   
 for(Page=0;Page<8;Page++)   
 {   
  for(column=0;column<128;column++)   
  {   
   WriteDate(~puts[X] ); //����  
   X++;   
  }   
 }   
}


//8x8��ͼ��
void Display8_8(uchar C[],uchar i)//iͼ��Ҫ��ʾ����λ��
{
	uchar k,num=0;
	num=i*0x08;
	 for(k=0;k<0x08;k++)
	 {
			WriteDate(C[num+k]);
			column+=0x01;
	 } 

}

//16x16��ͼ��
void Display16_16(uchar F[], uchar i)
{
uchar k=0;
uint	num=0;
 num=i*0x20;//32

	for(k=0;k<0x10;k++)//ǰ16��,�ϰ벿��
	 {
			WriteDate(F[num+k]);
			column+=0x01;
	 } 
		column-=0x10;//�����ƶ�16��λ��,�ص�����ߵ���
		Page+=0x01;   //��һҳ���°벿��
	 
  for(k=16;k<0x20;k++)//��16�У��°벿��
	 {
			WriteDate(F[num+k]);
			column+=0x01;
	 } 
  Page-=0x01; 
  Delay(80); 
}


//3��8��8��
void Display_character()
{ 
		uchar k,c, a=0;//C-ҳ,K-��
		column  = 0;//������߿�ʼ
	 for(c=0;c<8;c++)//��1��ͼ��
	 { 
			Page = c; 
			for(k=0;k<16;k++)
			{ 
				Display8_8(character,0);
			}
			column  = 0;
	 }
  Delay(1500);

 for(c=0;c<8;c++)//��2��ͼ��
	{ 
		Page = c; 
		for(k=0;k<16;k++)
		{ 
			Display8_8(character,1);
		}
			column  = 0;
 }
  Delay(1500);

 for(c=0;c<8;c++)//��3��ͼ��
	{ 
		Page = c; 
		for(k=0;k<16;k++)
		{ 
			Display8_8(character,2);
		}
			column  = 0;
 }
  Delay(1000);

}


//4��16��16�ĺ���
void Display_Chinese()
{
	 uchar a=0;
	 Page 	 = 0;   //��һҳ
	 column  = 0;//������
	 for(a=0;a<8;a++)
		 {
				Display16_16(font,a);/* [font]�Ǵ洢���16x16���ֵ������ݵ����顣
														  a������[font]������ĸ�λ�ÿ�ʼ��ȡ����
															�Ա���ʾ��ȷ�ĺ���*/
		 }
		 
	 Page = 2; //����ҳ�͵���ҳ  
	 column  = 0;
	 for(a=8;a<16;a++)
		 {
				Display16_16(font,a);
		 }
		 
   Page = 4;   
	 column  = 0;
	 for(a=16;a<24;a++)
		 {
				Display16_16(font,a);
		 }

   Page = 6;   
	 column  = 0;
	 for(a=24;a<32;a++)
		 {
				Display16_16(font,a);
		 }

}



void Delay(unsigned int xms) //@12.000MHz
{
    unsigned char i, j;
    while(xms--) // ÿ��ѭ������ 1 ����
    {
        i = 12;    // �ڲ�ѭ������
        j = 169;   // �ڲ�ѭ������
        
        do
        {
            while (--j); // �ڲ���ʱ
        } while (--i); // �ⲿ��ʱ
    }
}


void LcmPutDots( unsigned char DotByte,unsigned char DotByte1 )   
{   
 Page = 0;   
 column  = 0;   
 for(Page=0;Page<8;Page++)   
 {   
  for(column=0;column<128;column++)   
  {   
   WriteDate( DotByte );
   column++;
   WriteDate( DotByte1 );  
  } 
    
 }   
} 

void LcmPutDots1(unsigned char DotByte)
{
    Page = 0;
    column  = 0;
    for(Page = 0; Page < 8; Page++)
    {
        for(column = 0; column< 128; column++)
        {
            WriteDate(DotByte);
        }
    }
}



unsigned char i;
void LcmPutDotsOddColumns(void)//������
{
    unsigned char DotByte9[] = {0x3C, 0x66, 0xC3, 0xC3, 0x3F, 0x03, 0x03, 0xFE}; // ����ʾ�����ݣ����Ի�����������

    for (Page = 0; Page < 8; Page++) // ��������8��ҳ��
    {
        for (column = 1; column < 128; column += 2) // ���������У���ʼ��Ϊ1������Ϊ2
        {
            SetPage_Column(); // ���õ�ǰҳ�������е�λ��

            for (i = 0; i < 8; i++) // д��8���ֽڵ����ݵ���ǰ��
            {
                WriteDate(DotByte9[i]); // д��ÿ�еĵ������ݣ����߸�����Ҫд����������
            }
        }
    }
}




void LcmPutDotsStars(unsigned char pattern)
{
  
    for (Page = 0; Page < 8; Page++) // ��������8��ҳ��
    {
        for (column = 0; column < 128; column++) // ����ÿһ��
        {
            SetPage_Column(); // ���ù��λ��

            if (column % 2 == 0) // ÿ��һ����ʾһ�����ģʽ
            {
                WriteDate(pattern); // ��ʾ������ģʽ
            }
            else
            {
                WriteDate(~pattern); // ��ʾ��ģʽ�������������岼��Ч��
            }
        }
    }
}





/*
void Step(void) interrupt 0 using 0//�ж�
{ _nop_(); 
  _nop_(); 
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_(); 
  _nop_(); 
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  
	if(int0==0)
	loge=!loge;
    while(!int0);
  return;
}
*/