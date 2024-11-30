#include <REG52.H>   
#include <INTRINS.H>    
#include <STDIO.H>     
#include <MATH.H>    
#include <ABSACC.H>   
#include "lcd16080.h"
#include "picture.h"

uchar group,i,j;

void Delay(uint MS)   
{   
 unsigned char us,usn;   
 while(MS!=0)   
 {   
  usn = 2; //for 12M    
  while(usn!=0)   
  {   
   us=0xf6;   
   while (us!=0){us--;};   
   usn--;   
  }   
  MS--;   
 }  
}

uint ReadKey1() // ������⺯��
{
    if (LCD_KEY == 1)           
	{  // ����������
        Delay(1);  // �򵥵�ȥ��������
        if (LCD_KEY == 1) 
		{  // ��鰴���Ƿ���Ȼ����
            while (LCD_KEY == 1);  // �ȴ������ͷ�
            return 1;  // ���ذ���������
        }
    }
    return 0;  // ����û�б�����
}

//æ�ź��ж�
void CheckBusy()
{uchar b;
	 do	
	{
		DataBus=0xff;
		 LCD_CD=1;
		 LCD_RD=0;
		 b=DataBus;
		 LCD_RD=1;	
	 }
	 while(b&0x03!=0x03);//Table 6-4 Note1/2
		
 }

//�Զ���æµ�ж� 
void AUTOREAD_CheckBusy()
{
 uchar b;
 do	
 {
	 DataBus=0xff;
	 LCD_CD=1;
	 LCD_RD=0;
	 b=DataBus;
	 LCD_RD=1;	
 }
	 while(b&0x03==0);//Table 6-4 Note3
}
//�Զ�дæµ�ж� 
void AUTOWRITE_CheckBus()
{
	uchar b;
	 do	
	{
		 DataBus=0xff;
		 LCD_CD=1;
		 LCD_RD=0;
		 b=DataBus;
		 LCD_RD=1;	
	 }
	 while(b&0x08!=0x08);
} 

//д����
void WriteData( uchar Data_Byte )   //Table 5-1 
{    
	 LCD_CD = 0;   
	 DataBus = Data_Byte;   
	 LCD_WR = 0;  
	 _nop_();    
	 LCD_WR  = 1;   
}   

/*
д����
dat1: ��һ��Ҫд��������ֽڡ�
dat2: ����еڶ���Ҫд��������ֽڡ�
command: Ҫ���͵������ֽڡ�
parameters_num: ����������ָ��Ҫ���͵������ֽ�����1��2����
*/
void WriteCommand( uchar dat1,uchar dat2,uchar command,uchar parameters_num )   
{   
  if((parameters_num==1)|(parameters_num==2))
  	{
		CheckBusy();	
 	    WriteData(dat1);
	}
	
  if(parameters_num==2)
  	{
		CheckBusy();	
 	    WriteData(dat2);
	}

	AUTOWRITE_CheckBus();//д���æ�ź�
	
 	LCD_CD = 1;   
 	DataBus = command; 
 	LCD_WR = 0; 
	_nop_();     
 	LCD_WR  = 1;      
}

//����
void LcmClear( void )   
{   uint a;
	Locatexy(0,0,Character);
	WriteCommand(0,0,0xb0,0 ); //0xb0:Set Data Auto Write
	for(a=0;a<8192;a++)
	{
		WriteData( 0 ); 
	}   
	WriteCommand(0,0,0xb2,0 );//0xb2:Auto Reset 
}   

/*
���λ�ã�֧��ͼ��ģʽ���ַ�ģʽ
x�����ĺ����꣨��������
y�����������꣨��������
mode������ģʽ��������ͼ��ģʽ�����ַ�ģʽ��
mode = 1��ͼ��ģʽ��
mode = 0���ַ�ģʽ��
*/
void Locatexy(uchar x,uchar y,uchar mode)   
{  uint a=0;
	if(mode)				//Graphic mode   x=0-29  y=0-127    START ADDRESS ��0800
	{
		a=y*30+x;	                       
		WriteCommand((uchar)a,(uchar)(a>>8)+0x08,0x24,2);//a ��һ�� 16 λ��������
//		                                                   �����˸�λ�͵�λ
	}

	else					//Character mode   x=0-29  y=0-15    START ADDRESS ��0000
	{
		a=y*30+x;	                      //0x24-Set Address Pointer-Table 6-6 
		WriteCommand((uchar)(a),(uchar)(a>>8),0x24,2);
	}
}


/*
��Ļ�ϵ�ָ��λ����ʾһ��ASCII�ַ���
x����ʾ�ַ�����LCD�ϵ���ʼ�����ꡣ
y����ʾ�ַ�����LCD�ϵ���ʼ�����ꡣ
ascll��һ��ָ��ASCII�ַ����飨�ַ�������ָ�룬��Ҫ��ʾ���ַ������ݡ�
*/
void Display_Str(uchar x,uchar y,uchar *ascll)
{
	Locatexy(x,y,Character);
	while(*ascll>0)//=!\0
	{
		WriteCommand(*ascll-0x20,0,0xc0,1 );//Table 6-19-Data Write and Increment ADP  
		ascll++;//*ascll - 0x20 ����ת��ΪLCD����ʶ����ַ�����
	} 
	
}
//�ڲ��ֿ�
void Display_FullCGROM()
{
    uchar x = 0, y = 0;       // ��ʼλ�� (0, 0)
    uchar charCode = 0x01;    // �� CGROM �� 0x00 ��ʼ

    // �������� LCD16080 ��Ļ (30 �� x 16 ��)
    while (y < 16)
    {
        Locatexy(x, y, Character);  // ���ù��λ��

        // ��ʾ��ǰ�� CGROM �ַ�
        WriteCommand(charCode, 0, 0xc0, 1);  // ���͵�ǰ�ַ��Ĵ��뵽 LCD

        // ����λ�ú��ַ�
        x++;             // �ƶ�����һ��
        charCode++;      // ��ʾ��һ���ַ�

        // ������ÿ�����һ���ַ���������һ��
        if (x >= 30)
        {
            x = 0;       // �лص� 0
            y++;         // �������ӣ�����
        }

        // ��� charCode ���� 0xFF���ͻص� 0x00������ѭ����ʾ�ַ�
        if (charCode > 0xFF)
        {
            charCode = 0x01;
        }
    }
	Display_FullCGROM_SpecifiedPositions();
}

void Display_FullCGROM_SpecifiedPositions()
{
    uchar charCode = 0x01;  

    uchar positions[][2] = 
	{
    {7, 4}, {0, 5},{0, 6},{0, 7},{0, 8},
	};
    uchar num_positions = sizeof(positions) / sizeof(positions[0]); 

    for ( i = 0; i < num_positions; i++)
    {
        uchar x = positions[i][0];
        uchar y = positions[i][1];

        Locatexy(x, y,Character); 
        for ( j = 0; j < 20; j++) // ����ÿ��λ����ʾ����
        {       
            WriteCommand(charCode, 0, 0xc0, 1);
            charCode++;
            if (charCode > 0xFF)
            {
                charCode = 0x01; 
            }
        }
    }
}


/*
��ʾ16x16����ĺ����ַ�

x���ַ���LCD�ϵ���ʼ������

y���ַ���LCD�ϵ���ʼ������

Chinese_character��ָ���ֿ��еĺ������ݣ��������ݣ���ָ��

character_code����ʾ���ֵ���������룬����ȷ��Ҫ��ʾ�ĺ������ֿ��е�λ��
*/
void Display_16_16(uchar x,uchar y,uchar  code *Chinese_character,uchar character_code)
{	
	//uchar i,j;    
	//uint num=0;
	//num=character_code*0x20;
	//Locatexy(x,y,Graphic);
	//for(j = 0; j < 16; j++)  // ѭ����ʾ16��
	//{
	//	for(i = 0; i < 2; i++)  // ÿ��2���ֽڣ���16��
	//	{
	//		WriteCommand(*(Chinese_character + num), 0, 0xc0, 1);
	//		num++;
	//	}
	//	y += 1;  // �ƶ�����һ��
	//	Locatexy(x, y, Graphic);  // ���¹��λ��
	//}
	
	
	
	uchar j;    // ��ѭ�����Ʊ���
    uint num = 0;  // ƫ������ʼΪ0
    num = character_code * 0x10;  // ÿ���ַ�ռ��16�ֽڣ�8��16��
    
    Locatexy(x, y, Graphic);  // ��λ����ʾ����ʼλ��

    for(j = 0; j < 16; j++)  // ����16�е�ѭ��
    {
        WriteCommand(*(Chinese_character + num), 0, 0xc0, 1);  // д��1���ֽڵĵ�������
        num++;  // �ƶ����ֿ��е���һ���ֽ�
        y += 1;  // �ƶ�����һ��
        Locatexy(x, y, Graphic);  // ���¹��λ��
    }

}
/*
��ʾ8x16�����Ӣ���ַ�

x���ַ���LCD�ϵ���ʼ������

y���ַ���LCD�ϵ���ʼ������

Chinese_character��ָ���ֿ��е�Ӣ�����ݣ��������ݣ���ָ��

character_code����ʾӢ�ĵ���������룬����ȷ��Ҫ��ʾ��Ӣ�����ֿ��е�λ��
*/
void Display_8_16(uchar x, uchar y, uchar code *English_character, uchar character_code)
{
    uchar j;    // ��ѭ�����Ʊ���
    uint num = 0;  // ƫ������ʼΪ0
    num = character_code * 0x10;  // ÿ���ַ�ռ��16�ֽڣ�8��16��
    
    Locatexy(x, y, Graphic);  // ��λ����ʾ����ʼλ��

    for(j = 0; j < 16; j++)  // ����16�е�ѭ��
    {
        WriteCommand(*(English_character + num), 0, 0xc0, 1);  // д��1���ֽڵĵ�������
        num++;  // �ƶ����ֿ��е���һ���ֽ�
        y += 1;  // �ƶ�����һ��
        Locatexy(x, y, Graphic);  // ���¹��λ��
    }
}


/* 
����������LCD��Ļ����ͼ��ģʽ���һ�����ģʽ

DotByte��Ҫ��ʾ�ĵ�һ���ֽ�����(����ģʽ),�������ÿ�е�ǰ30���ֽ�

DotByte1��Ҫ��ʾ�ĵڶ����ֽ�����(����ģʽ),�������ÿ�еĺ�30���ֽ�
*/
void DisplayDots( uchar DotByte,uchar DotByte1 )   
{ 	uchar i,j;  
	Locatexy(0,0,Graphic);  
 	WriteCommand(0,0,0xb0,0 );//Set Data Auto Write  
	for(j = 0; j < 64; j++)  // ѭ��64��
	{
		for(i = 0; i < 30; i++)  // ÿ�е�ǰ30���ֽ�д��DotByte
		{
			WriteData(DotByte);
		}

		for(i = 0; i < 30; i++)  // ÿ�еĺ�30���ֽ�д��DotByte1
		{
			WriteData(DotByte1);
		}
	} 
  	WriteCommand(0,0,0xb2,0 ); //Auto Reset
}  



/* 
����������LCD��Ļ��ָ��λ�û���λͼͼ��
x:ͼ����LCD��Ļ�ϵ���ʼ������
y:ͼ����LCD��Ļ�ϵ���ʼ������
W:ͼ��Ŀ�ȣ�������Ϊ��λ��
H:ͼ��ĸ߶ȣ�������Ϊ��λ��
puts��ָ��λͼͼ�����ݵ�ָ��,������λΪ��λ
*/
void DisplayBMP(uchar x,uchar y,uchar W,uchar H,  uchar code *puts )   
{  	uchar k,j;
	Locatexy(x,y,Graphic); 
		for(j = 0; j < H; j++)  // ����ÿһ��
	{
		WriteCommand(0, 0, 0xb0, 0);  // ���������Զ�д��ģʽ
		for(k = 0; k < W/8; k++)  // ÿ�б���W/8���ֽڣ�8������Ϊ1�ֽڣ�
		{
			WriteData(*puts++);  // ���ֽ�д��ͼ������
		}
		WriteCommand(0, 0, 0xb2, 0);  // �˳������Զ�д��ģʽ
		y += 1;  // �ƶ�����һ��
		Locatexy(x, y, Graphic);  // ���¹��λ��
	}
  
} 
//ͼƬȡ��
void ReverseDisplayBMP(uchar x,uchar y,uchar W,uchar H,  uchar code *puts )   
{  	uchar i,j;
	Locatexy(x,y,Graphic); 
      
	for(j=0;j<H;j++)
		{	WriteCommand(0,0,0xb0,0 ); 
		 	for(i=0;i<W/8;i++)
			{
				WriteData(~(*puts));//ȡ��
				puts++;
			} 
		WriteCommand(0,0,0xb2,0 ); 
			y+=1;
			Locatexy(x,y,Graphic);
		}  
} 


//��ʼ��
void LcmInit( void )   
{  
 	LCD_Reset=0;
 	Delay(50);
	LCD_Reset=1;
 	Delay(50);
	//Set Control Word
	WriteCommand(0,0,0x40,2 );   //Set Text Home Address
	WriteCommand(30,0,0x41,2 );  //Set Text Area   
	WriteCommand(0,0x08,0x42,2 );//Set Graphic Home Address    
	WriteCommand(30,0,0x43,2 );  //Set Graphic Area 
	
	WriteCommand(0,0,0xa7,0);//8-line cursor - Table 6-17
	WriteCommand(0,0,0x80,0);//OR Mode - Table 6-14
	
//	WriteCommand(0,0,0x81,0);//EXOR Mode - Table 6-14
//	WriteCommand(0,0,0x83,0);//AND Mode - Table 6-14
//	WriteCommand(0,0,0x84,0);//Text Attribute Mode - Table 6-14
//	WriteCommand(0,0,0x80,0);//Internal Character Generator Mode - Table 6-14
//	WriteCommand(0,0,0x90,0);//External Character Generator Mode  - Table 6-14
	
	WriteCommand(0,0,0x9c,0);//Text on, Graphic on - Table 6-16 
	
//	WriteCommand(0,0,0x90,0);//Display off
//	WriteCommand(0,0,0x92,0);//Cursor on, Blink off
//	WriteCommand(0,0,0x93,0);//Cursor on, Blink on 
}



uchar start_x[] = {32, 32, 34};  // ÿ����ʾ����ʼX����
uchar start_y[] = {7, 32, 57};  // ÿ����ʾ����ʼY����
uchar start_code[] = {0, 16, 32};  // ÿ����ʾ����ʼ�ַ�����
uchar count[] = {16, 16, 12};  // ÿ����ʾ���ַ�����
void Show_Eng(void)
{   
	unsigned char i;
	DisplayBMP(0,0,160,80,BMP0); 
	for ( group = 0; group < 3; group++)  // ��������ͬ����ʾ����
	{
		for ( i = 0; i < count[group]; i++)
		{
			Display_8_16(start_x[group] + i, start_y[group], EnglishCode, start_code[group] + i);
		}
	}

}
