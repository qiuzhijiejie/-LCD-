#include "reg51.h"
#include "picture.h"
#include "242oled.h"
 unsigned char  *point1;
 unsigned char  *point2;
 unsigned char  *point3;

sbit   KEY1  = P2^0;
unsigned char ACK=0;
unsigned char code OLED_init_cmd[25]=
{
       0xAE,//�ر���ʾ
       0xD5,//����ʱ�ӷ�Ƶ����,��Ƶ��
       0x80,  //[3:0],��Ƶ����;[7:4],��Ƶ��
       0xA8,//��������·��
       0X3F,//Ĭ��(1/64)
       0xD3,//������ʾƫ��
       0X00,//Ĭ��Ϊ0
       0x40,//������ʾ��ʼ�� [5:0],����.
       0x8D,//��ɱ�����
       0x10,//bit2������/�ر�
       0x20,//�����ڴ��ַģʽ
       0x02,//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
       0xA1,//���ض�������,bit0:0,0->0;1,0->127;  A1
       0xC8,//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·�� (C0 ��ת��ʾ) C8	   
       0xDA,//����COMӲ����������
       0x12,//[5:4]����  	   
       0x81,//�Աȶ�����
       0xf0,//1~255;Ĭ��0X7F (��������,Խ��Խ��)	   
       0xD9,//����Ԥ�������
       0x71,//[3:0],PHASE 1;[7:4],PHASE 2;	   
       0xDB,//����VCOMH ��ѹ����
       0x00,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;   
       0xA4,//ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)   
       0xA6,//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ      
       0xAF,//������ʾ   
};


void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;
  }
}

void delay_ms(unsigned int _ms_time)
  {
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
  }

//д��  ���SDA���ߣ��Եȴ����豸����Ӧ��
void IIC_write(unsigned char date)
{
	unsigned char i, temp;
	temp = date;		
	for(i=0; i<8; i++)
	{	
		IIC_SCK_0;
		if ((temp&0x80)==0)
          IIC_SDA_0;
         else 
		  IIC_SDA_1;
		temp = temp << 1;	//����250ns��ʱ
		IIC_SCK_1;	
	}
	IIC_SCK_0;	
	
	IIC_SDA_1;	
	IIC_SCK_1;	
	 ACK =0;
	IIC_SCK_0;	
}
//�����ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ�ı仯����Ϊ�����ź�
void IIC_start()
{
	IIC_SDA_1;
	
	IIC_SCK_1;
					   //���в��������ͷ�SCL	
	IIC_SDA_0;
	
	IIC_SCK_0;
	
    IIC_write(0x78);
        
}

//ֹͣ�ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ�ı仯����Ϊֹͣ�ź�
void IIC_stop()
{
	IIC_SDA_0;
	
	IIC_SCK_1;
	
	IIC_SDA_1;
	
}

void OLED_send_cmd(unsigned char o_command)
  {
    
    IIC_start();
    IIC_write(0x00); 
    IIC_write(o_command);
    IIC_stop();
    
  }
  
void OLED_send_data(unsigned char o_data)
  { 
    IIC_start();
    IIC_write(0x40);
    IIC_write(o_data);
    IIC_stop();
   }
  
void Column_set(unsigned char column)
  {
    column+=OLED_COLUMN_OFFSET;
    OLED_send_cmd(0x10|(column>>4));    //�����е�ַ��λ
    OLED_send_cmd(0x00|(column&0x0f));   //�����е�ַ��λ  
    	 
  }
  
void Page_set(unsigned char page)
  {
    OLED_send_cmd(0xb0+page);
  }
  
void OLED_clear(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
          Page_set(page);
          Column_set(0);	  
          for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
            {
              OLED_send_data(0x00);
            }
      }
  }

    
 void OLED_fullROW(unsigned char Data)
{
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
        Page_set(page);
        Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(Data);
          }
      }
  } 
  
  
 void OLED_full(void)
{
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
        Page_set(page);
        Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(0xff);
          }
      }
  } 


void OLED_fullCOL(unsigned char oddData, unsigned char evenData)
{
    unsigned char page, column;
    for (page = 0; page < OLED_PAGE_NUMBER; page++) // page loop
    { 
        Page_set(page);
        Column_set(0);  
        for (column = 0; column < OLED_COLUMN_NUMBER; column++) // column loop
        {
            // �ж��к�����������ż��
            if (column % 2 == 0)
            {
                OLED_send_data(oddData); // ż������
            }
            else
            {
                OLED_send_data(evenData); // ��������
            }
        }
    }
}

void OLED_init(void)
  {
    unsigned char i;
    for(i=0;i<25;i++)
      {
        OLED_send_cmd(OLED_init_cmd[i]);
      }
  }

void Picture_display(const unsigned char *ptr_pic)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)        //page loop
      { 
	Page_set(page);
	Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(*ptr_pic++);
          }
      }
  }
void Picture_ReverseDisplay(const unsigned char *ptr_pic)
{
    unsigned char page,column,dis_data;
    for(page=0;page<OLED_PAGE_NUMBER;page++)        //page loop
      { 
	Page_set(page);
	Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            dis_data=*ptr_pic++;
            dis_data=~dis_data;
            OLED_send_data(dis_data);
          }
      }
  }

void IO_init(void)
{
  P2|=0xFF;                        
  

}
 unsigned int ReadKey1() // ������⺯��
{
    if (KEY1 == 0) 
	{  // ����������
        delay_ms(1);  // �򵥵�ȥ��������
        if (KEY1 == 0) 
		{  // ��鰴���Ƿ���Ȼ����
            while (KEY1 == 0);  // �ȴ������ͷ�
            return 1;  // ���ذ���������
        }
    }
    return 0;  // ����û�б�����
}



void display1(void)
{	
		point1= &picture_tab1[0];
		Picture_display(point1);
		delay_ms(1);		
		Picture_ReverseDisplay(point1);	 
		delay_ms(1);
}	

void display2(void){	
		point2= &picture_tab2[0];//logo
		Picture_display(point2);
		delay_ms(1);		
		Picture_ReverseDisplay(point2);	 
		delay_ms(1);  	
}

void display3(void)
{
		point3= &picture_tab3[0];
		Picture_display(point3);
		delay_ms(1);		
		Picture_ReverseDisplay(point3);	 
		delay_ms(1);  	
}