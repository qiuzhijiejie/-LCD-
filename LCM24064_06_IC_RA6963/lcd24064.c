#include <INTRINS.H>              
#include <REG52.H>  
#include "lcd24064.h"
#include "picture.h"

bit Log=0;
uchar  group,i,j;
void Locatexy(uchar xa,uchar ya,uchar mode)   
{  uint a=0;
	if(mode)				//Graphic mode   x=0-29  y=0-64    START ADDRESS ??0800
		{
			a=ya*30+xa;	
			WriteCommand((uchar)a,(uchar)(a>>8)+0x08,0x24,2);
		}

	else					//Character mode   x=0-29  y=0-7    START ADDRESS ??0000
		{
			a=ya*30+xa;	
			WriteCommand((uchar)(a),(uchar)(a>>8),0x24,2);
		}

}

/***************************/   
/*LCM READ AND WRITE BUSY CHECK                   
/***************************/ 

void CheckBusy_S0S1()
{uchar b;
	 do	
	{DataBus=0xff;
	 CD=1;
	 _RD=0;
	 b=DataBus;
	  _RD=1;	
	 }
	 while(b&0x03!=0x03);
		
 }

/***************************/   
/*DATA AUTO READ BUSY CHECK                    
/***************************/ 

void CheckBusy_S2()
{uchar b;
	 do	
	{DataBus=0xff;
	 CD=1;
	 _RD=0;
	 b=DataBus;
	 _RD=1;	
	 }
	 while(b&0x03==0);
	 	
}


/***************************/   
/*DATA AUTO WRITE BUSY CHECK                    
/***************************/ 

void CheckBusy_S3()
{uchar b;
	 do	
	{DataBus=0xff;
	 CD=1;
	 _RD=0;
	 b=DataBus;
	 _RD=1;	
	 }
	 while(b&0x08!=0x08);
}


   
/***************************/   
/*WRITE COMMAND         
//    dat1:  parameters 1
//	  dat2:  parameters 2
//	command: command
//parameters_num: parameters  number 
/***************************/   
void WriteCommand( uchar dat1,uchar dat2,uchar command,uchar parameters_num )   
{   
  if((parameters_num==1)|(parameters_num==2))
  	{CheckBusy_S0S1();	
 	 WriteData(dat1);
	}	
  if(parameters_num==2)
  	{CheckBusy_S0S1();	
 	 WriteData(dat2);
	}

	CheckBusy_S3();
 	CD = 1;   
 	DataBus = command; 
 	_WR = 0; 
	_nop_();     
 	_WR  = 1; 
       
}   

   
/***************************/   
/*WRITE DATA                 */   
/***************************/   
void WriteData( uchar DataByte )   
{    
	 CD = 0;   
	 DataBus = DataByte; 
	 _WR = 0;  
	_nop_();    
	 _WR  = 1;   
}   
   
void LcmClear( void )   
{   uint a;
	Locatexy(0,0,Character);
	WriteCommand(0,0,0xb0,0 ); 
	for(a=0;a<8192;a++)
	{
		WriteData( 0 ); 
	}   
	WriteCommand(0,0,0xb2,0 );
}   

void Display_Str(uchar x,uchar y,uchar *ascll)
{
	Locatexy(x,y,Character);
	while(*ascll>0)
	{
		WriteCommand(*ascll-0x20,0,0xc0,1 ); 
		ascll++;
	} 
}


void Display_16_16(uchar x,uchar y,uchar  code *Chinese_character,uchar character_code)
{	uchar k,j;    uint	num=0;
 	num=character_code*0x20;
	Locatexy(x,y,Graphic);
	for(j=0;j<16;j++)
		{ for(k=0;k<2;k++)
			{
				WriteCommand(*(Chinese_character+num),0,0xc0,1 ); 
				num++;
			} 
			y+=1;
			Locatexy(x,y,Graphic);
		}

}

void DisplayDots( uchar DotByte,uchar DotByte1 )   
{ 	uchar k,j;  
	Locatexy(0,0,Graphic);  
 	WriteCommand(0,0,0xb0,0 ); 
	 for(j=0;j<32;j++)   
	 {   
	  for(k=0;k<30;k++)   
		{
			WriteData(DotByte);

		} 
	  for(k=0;k<30;k++)   
		{
			WriteData(DotByte1);

		} 
  	}  
  	WriteCommand(0,0,0xb2,0 ); 
}  

     
void DisplayBMP(uchar x,uchar y,uchar W,uchar H,  uchar code *puts )   
{  	uchar k,j;
	Locatexy(x,y,Graphic); 
      
	for(j=0;j<H;j++)
		{	WriteCommand(0,0,0xb0,0 ); 
		 	for(k=0;k<W/8;k++)
			{
				WriteData(*puts++);

			} 
		WriteCommand(0,0,0xb2,0 ); 
			y+=1;
			Locatexy(x,y,Graphic);
		}  
}   
     
void ReverseDisplayBMP(uchar x,uchar y,uchar W,uchar H,  uchar code *puts )   
{  	uchar k,j;
	Locatexy(x,y,Graphic); 
      
	for(j=0;j<H;j++)
		{	WriteCommand(0,0,0xb0,0 ); 
		 	for(k=0;k<W/8;k++)
			{
				WriteData(~(*puts));
				puts++;
			} 
		WriteCommand(0,0,0xb2,0 ); 
			y+=1;
			Locatexy(x,y,Graphic);
		}  
}  

   
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
 while(Log);
}   




void LcmInit( void )   
{  
 	RESET=0;
 	Delay(50);
	RESET=1;
 	Delay(50);
	WriteCommand(0,0,0x40,2 );   //Set Text Home Address
	WriteCommand(30,0,0x41,2 );    //Set Text Area Width
	WriteCommand(0,0x08,0x42,2 );   //Set Graphic Home Address
	WriteCommand(30,0,0x43,2 );  	//Set Graphic Area Width
	WriteCommand(0,0,0xa7,0);		//Cursor Pattern Select
	WriteCommand(0,0,0x80,0);		//OR mode
	WriteCommand(0,0,0x9c,0);   	//Text on, graphic on
}   
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
void Display_FullCGROM()
{
    uchar x = 0, y = 0;       // ��ʼλ�� (0, 0)
    uchar charCode = 0x01;    // �� CGROM �� 0x01 ��ʼ

    // �������� LCD240128 ��Ļ (30 �� x 16 ��)
    while (y < 16)
    {
        Locatexy(x, y, Character);  // ���ù��λ��

        // ��ʾ��ǰ�� CGROM �ַ�
        WriteCommand(charCode, 0, 0xc0, 1);  // ���͵�ǰ�ַ��Ĵ��뵽 LCD

        // ����λ�ú��ַ�
        x++;             // �ƶ�����һ��
        charCode++;      // ��ʾ��һ���ַ�


        if (x >= 30)
        {
            x = 0;       // �лص� 0
            y++;         // �������ӣ�����
        }


        if (charCode > 0xFF)
        {
            charCode = 0x01;
			break;
        }
		
    }
	
Display_FullCGROM_SpecifiedPositions();

}

void Display_FullCGROM_SpecifiedPositions()
{
    uchar charCode = 0x01;  

    uchar positions[][2] = 
	{
    {7, 4},{0, 5},{0, 6},{0, 7},
	
	};

    uchar num_positions = sizeof(positions) / sizeof(positions[0]); 

    for ( i = 0; i < num_positions; i++)
    {
        uchar x = positions[i][0];
        uchar y = positions[i][1];

        Locatexy(x, y,Character); 
        for ( j = 0; j < 30; j++) // ����ÿ��λ����ʾ����
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
uchar start_x[] = {7, 10};   // ÿ����ʾ����ʼX����
uchar start_y[] = {22, 42};    // ÿ����ʾ����ʼY����
uchar start_code[] = {0, 16};  // ÿ����ʾ����ʼ�ַ�����
uchar count[] = {16, 11};     // ÿ����ʾ���ַ�����
void wordageEng(void)
{  
	
	unsigned char i; 
	
    DisplayBMP(0,0,240,64,BMP0); 
	wordageCha();	
    Delay(100); 
	
	
for ( group = 0; group < 2; group++)  
{
    for ( i = 0; i < count[group]; i++)
    {
        Display_8_16(start_x[group] + i, start_y[group], English_character, start_code[group] + i);
    }
}


}


uchar start_x1[] = {5};   // ÿ����ʾ����ʼX����
uchar start_y1[] = {2};    // ÿ����ʾ����ʼY����
uchar start_code1[] = {0};  // ÿ����ʾ����ʼ�ַ�����
uchar count1[] = {10};     // ÿ����ʾ���ַ�����
void wordageCha(void)
{   
	unsigned char i; 
    Delay(100); 
for ( group = 0; group < 1; group++)  
{
    for ( i = 0; i < count1[group]; i++)
    {
        Display_16_16(start_x1[group] + 2 * i, start_y1[group], Chinese_character, start_code1[group] + i);
    }
}
}


unsigned char ReadKey() 
{
    if (Key == 1)           
	{  
        Delay(1);  
        if (Key == 1) 
		{  
            while (Key == 1); 
            return 1;  
        }
    }
    return 0;  
}