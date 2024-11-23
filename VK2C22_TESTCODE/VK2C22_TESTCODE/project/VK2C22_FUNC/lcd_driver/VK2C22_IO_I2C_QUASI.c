/**
  ******************************************************************************
  * @file    VK2C22.c
  * @author  kevin_guo
  * @version V1.2
  * @date    10-11-2024
  * @brief   This file contains all the VK2C22 functions. 
	*          ���ļ������� VK2C22
  ******************************************************************************
  * @attention
  ******************************************************************************
  */	
/* Includes ------------------------------------------------------------------*/
#include "VK2C22_IO_I2C_QUASI.h"
  
/* extern variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define VK2C22_CLK 10 //SCL�ź���Ƶ��,��delay_nusʵ�� 50->10kHz 10->50kHz 5->100kHz
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//segtab[]�����Ӧʵ�ʵ�оƬ��LCD���ߣ����߼�-VK2C22�ο���·
//4com 
//VK2C22A
//unsigned char VK2C22_segtab[VK2C22_SEGNUM]={
//	0,1,2,3,4,5,6,7,8,9,						//SEG0-SEG9
//	10,11,12,13,14,15,16,17,18,19,	//SEG10-SEG19
//	20,21,22,23,24,25,26,27,28,29,	//SEG20-SEG29
//	30,31,32,33,34,35,36,37,38,39,  //SEG30-SEG39
//	40,41,42,43,									  //SEG40-SEG43
//};
//VK2C22B 
unsigned char VK2C22_segtab[VK2C22_SEGNUM]={
	0,1,2,3,4,5,6,7,8,9,						//SEG0-SEG9
	10,11,12,13,14,15,16,17,18,19,	//SEG10-SEG19
	20,21,22,23,24,25,26,27,28,29,	//SEG20-SEG29
	30,31,32,33,34,35,36,37,38,39,  //SEG30-SEG39
};
//����LCDʵ��ֻ����SEG10��SEG21ʹ����������
//.h�ļ�����VK2C22_SEGNUM=12
//const unsigned char VK2C22_segtab[VK2C22_SEGNUM]={	
//	10,11,12,13,14,15,16,17,18,19,	//SEG10-SEG19
//	20,21,													//SEG20-SEG21
//};
//VK2C22_dispram��ӦоƬ����ʾRAM
//4com
unsigned char VK2C22_dispram[VK2C22_SEGNUM/2];//4COMʱÿ���ֽ����ݶ�Ӧ2��SEG
//��Ӧ����VK2C22_segtab[VK2C22_SEGNUM]
//��ʾRAM bufferΪ8λ��Ӧ2��SEG��bit7/bit3->com3,bit6/bit2->com2,bit5/bit1->com1,bit4/bit0->com0
unsigned char VK2C22_segi,VK2C22_comi;
unsigned char VK2C22_maxcom;//������com����4com
unsigned char VK2C22_readbuf[22];
/* Private function prototypes -----------------------------------------------*/
void VK2C22_InitSequence(void);
/* Private function ----------------------------------------------------------*/
/*******************************************************************************
* Function Name  : delay_nus
* Description    : ��ʱ1uS����
* Input          : n->��ʱʱ��nuS
* Output         : None
* Return         : None
*******************************************************************************/
void delay_nus(unsigned int n)	   
{
	unsigned char i;
	while(n--)
	{
		i=10;
		while(i--)
		{//nopָ����ݵ�Ƭ������Ӧ���޸�
			__nop();
		}
	}
}
/*******************************************************************************
* Function Name  : delay_nms
* Description    : ��ʱ1mS����
* Input          : n->��ʱʱ��nmS
* Output         : None
* Return         : None
*******************************************************************************/
void delay_nms(unsigned long int n)
{
	while(n--)
	{
		delay_nus(1000);
	}
}
/*******************************************************************************
* Function Name  : I2CStart
* Description    : ʱ���߸�ʱ���������ɸߵ��͵����䣬��ʾI2C��ʼ�ź�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_I2CStart( void )
{
  VK2C22_SCL_H();
  VK2C22_SDA_H();
  delay_nus(VK2C22_CLK);
  VK2C22_SDA_L();
  delay_nus(VK2C22_CLK);
}
/*******************************************************************************
* Function Name  : I2CStop
* Description    : ʱ���߸�ʱ���������ɵ͵��ߵ����䣬��ʾI2Cֹͣ�ź�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_I2CStop( void )
{
  VK2C22_SCL_H();
  VK2C22_SDA_L();
  delay_nus(VK2C22_CLK);
  VK2C22_SDA_H();
  delay_nus(VK2C22_CLK);
}
/*******************************************************************************
* Function Name  : I2CSlaveAck
* Description    : I2C�ӻ��豸Ӧ���ѯ
* Input          : None
* Output         : None
* Return         : 0-ok 1-fail
*******************************************************************************/
unsigned char VK2C22_I2CSlaveAck( void )
{
  unsigned int TimeOut;
  unsigned char RetValue;
	
  VK2C22_SCL_L();
  delay_nus(VK2C22_CLK);
  VK2C22_SCL_H();//��9��sclk������
  TimeOut = 10000;
  while( TimeOut-- > 0 )
  {
    if( VK2C22_GET_SDA()!=0 )//��ȡack
    {
      RetValue = 1;
    }
    else
    {
      RetValue = 0;
      break;
    }
  } 
	VK2C22_SCL_L(); 
  
  return RetValue;
}
/*******************************************************************************
* Function Name  : I2CSendAck
* Description    : I2C��������ACK
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_I2CSendAck( void )
{
  VK2C22_SCL_L();
  VK2C22_SDA_L();
  delay_nus(VK2C22_CLK*2);
  VK2C22_SCL_H();
  delay_nus(VK2C22_CLK*2);
  VK2C22_SCL_L();
  VK2C22_SDA_H();
}
/*******************************************************************************
* Function Name  : I2CSendNAck
* Description    : I2C��������NACK
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_I2CSendNAck( void )
{
  VK2C22_SCL_L();
  VK2C22_SDA_H();
  delay_nus(VK2C22_CLK);
  VK2C22_SCL_H();
  delay_nus(VK2C22_CLK);
}
/*******************************************************************************
* Function Name  : I2CWriteByte
* Description    : I2Cдһ�ֽ�����,�������͸�λ
* Input          : byte-Ҫд�������
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_I2CWriteByte( unsigned char byte )
{
	unsigned char i=8;
	while (i--)
	{ 
		VK2C22_SCL_L();
		if(byte&0x80)
			VK2C22_SDA_H();
		else
			VK2C22_SDA_L();
		byte<<=1; 
		delay_nus(VK2C22_CLK);
		VK2C22_SCL_H();     
		delay_nus(VK2C22_CLK);
	}
}

/*******************************************************************************
* Function Name  : WriteCmd
* Description    : д1�ֽ�����
* Input          : cmd-Ҫд�������
* Output         : None
* Return         : 0-ok 1-fail
*******************************************************************************/
unsigned char WriteCmdVK2C22(unsigned char cmd)
{
	VK2C22_I2CStart();

	VK2C22_I2CWriteByte( VK2C22_ADDRWR|0x00 );
	if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop(); 
		return 0;   
	}
	VK2C22_I2CWriteByte( cmd );
	if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop(); 
		return 0;   
	}
  VK2C22_I2CStop();
 
  return 0;    //���ز����ɰܱ�־
}
/*******************************************************************************
* Function Name  : I2CRDDatByte
* Description    : I2C��һ�ֽ�����,�������͵�λ
* Input          : None
* Output         : None
* Return         : ������1�ֽ�����
*******************************************************************************/
unsigned char VK2C22_I2CRDDat( void )
{
	unsigned char i,RetValue,bit;
	
	RetValue=0;	
  for( i=0; i<8; i++ )
  {
		VK2C22_SCL_H(); 
    delay_nus(VK2C22_CLK);
    if( 1 == VK2C22_GET_SDA() )
      bit = 0X01;
    else
      bit = 0x00;
      
    RetValue = (RetValue<<1)|bit;
    VK2C22_SCL_L();
    delay_nus(VK2C22_CLK);
	}
  
  return RetValue;
}
/*******************************************************************************
* Function Name  : WritenData
* Description    : д������ݵ���ʾRAM
* Input          : Addr-д��ram����ʼ��ַ
*                : Databuf->д��ram������bufferָ��
*                : Cnt->д��ram�����ݸ���
* Output         : None
* Return         : 0-ok 1-fail
*******************************************************************************/
unsigned char  WritenDataVK2C22(unsigned char Addr,unsigned char *Databuf,unsigned char Cnt)
{
	unsigned char n;
	
	//START�ź�	
	VK2C22_I2CStart(); 									
	//SLAVE��ַ
	VK2C22_I2CWriteByte(VK2C22_ADDRWR); 	
	if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop();													
		return 0;										
	}
	//��ʾRAM��ʼ��ַ
	VK2C22_I2CWriteByte(Addr); 						
	if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop();													
		return 0;
	}
	//����Cnt�����ݵ���ʾRAM
	for(n=0;n<Cnt;n++)
	{ 
		VK2C22_I2CWriteByte(*Databuf++);
		if( VK2C22_I2CSlaveAck()==1 )
		{
			VK2C22_I2CStop();													
			return 0;
		}
	}
	//STOP�ź�
	 VK2C22_I2CStop();											
	 return 0;    
}
/*******************************************************************************
* Function Name  : ReadnData
* Description    : ����ʾRAM���������
* Input          : Addr-��ram����ʼ��ַ
*                : Databuf->��ram������bufferָ��
*                : Cnt->��ram�����ݸ���
* Output         : None
* Return         : 0-ok 1-fail
*******************************************************************************/
unsigned char  ReadnDataVK2C22(unsigned char Addr,unsigned char *Databuf,unsigned char Cnt)
{
	unsigned char n;
	
	//START�ź�	
	VK2C22_I2CStart(); 									
	//SLAVE��ַд
	VK2C22_I2CWriteByte(VK2C22_ADDRWR); 	
	if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop();													
		return 0;										
	}                        
	//��ʾRAM��ʼ��ַ
	VK2C22_I2CWriteByte(Addr); 						
	if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop();													
		return 0;
	}
	
	//STOP�ź�
	VK2C22_I2CStop();	
	//START�ź�	
	VK2C22_I2CStart(); 									
	//SLAVE��ַ��
	VK2C22_I2CWriteByte(VK2C22_ADDRRD); 	
		if( 1 == VK2C22_I2CSlaveAck() )
	{
		VK2C22_I2CStop();													
		return 0;										
	}  
	//��Cnt�����ݵ���ʾRAM
	for(n=0;n<Cnt-1;n++)
	{ 
		*Databuf++=VK2C22_I2CRDDat();
		VK2C22_I2CSendAck();
	}
	*Databuf++=VK2C22_I2CRDDat();
	VK2C22_I2CSendNAck();
	//STOP�ź�
	VK2C22_I2CStop();											
	 return 0;    
}
/*******************************************************************************
* Function Name  : VK2C22_DisAll
* Description    : ����SEG��ʾͬһ�����ݣ�bit7/bit3-COM3 bit6/bit2-COM2 bit5/bit1-COM1 bit4/bit0-COM0
* 					     : ���磺0xffȫ�� 0x00ȫ�� 0x55�������� 0xaa�������� 0x33�������� 
* Input          ��dat->д��ram������(1���ֽ����ݶ�Ӧ2��SEG)  
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_DisAll(unsigned char dat)
{
	unsigned char segi;
	
	for(segi=0;segi<22;segi++)
	{
		VK2C22_dispram[segi]=dat;
	}
	WritenDataVK2C22(0,VK2C22_dispram,22);//������8bit���ݶ�Ӧ2��SEG��ÿ8bit���ݵ�ַ��1��ÿ8λ����1��ACK	
}
/*******************************************************************************
* Function Name  : DisSegComOn
* Description    : ����1����(1��seg��1��com�����Ӧ����ʾ��)
* Input          ��seg->���Ӧ��seg��  
* 		           ��com->���Ӧcom��  
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_DisDotOn(unsigned char seg,unsigned char com)
{
	unsigned char addrbit,tempdat;
	
  if(seg%2==0)
			addrbit=(1<<com);//������8λ���ݵ�4bit��Ч��ÿ8bit���ݵ�ַ��1��ÿ8λ����1��ACK
		else
			addrbit=(1<<(4+com));//������8λ���ݸ�4bit��Ч��ÿ8bit���ݵ�ַ��1��ÿ8λ����1��ACK
		tempdat=VK2C22_dispram[seg/2]|addrbit;
	  VK2C22_dispram[seg/2]=tempdat;
		WritenDataVK2C22(seg/2,&tempdat,1);	
}
/*******************************************************************************
* Function Name  : DisSegComOff
* Description    : �ر�1����(1��seg��1��com�����Ӧ����ʾ��)
* Input          ��seg->���Ӧ��seg��  
* 		           ��com->���Ӧcom��  
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_DisDotOff(unsigned char seg,unsigned char com)
{
	unsigned char addrbit,tempdat;
  
	if(seg%2==0)
			addrbit=(1<<com);//������8λ���ݵ�4bit��Ч��ÿ8bit���ݵ�ַ��1��ÿ8λ����1��ACK
		else
			addrbit=(1<<(4+com));//������8λ���ݸ�4bit��Ч��ÿ8bit���ݵ�ַ��1��ÿ8λ����1��ACK
		tempdat=VK2C22_dispram[seg/2]&~addrbit;
	  VK2C22_dispram[seg/2]=tempdat;
		WritenDataVK2C22(seg/2,&tempdat,1);
	
}
/*******************************************************************************
* Function Name  : Enter_Standby
* Description    : �������͹���ģʽ,��������ʾ
* Input          ��None 
* Output         : None
* Return         : 0-ok 1-fail
*******************************************************************************/
void VK2C22_Enter_PowerOff(void)
{		
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_2|F_80HZ|RCOFF_LCDOFF);  //ģʽ����  1/2 Bais 1/4 Duty֡Ƶ��80Hz,�ڲ�ϵͳ��������lcd����ʾ
	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_3|F_80HZ|RCOFF_LCDOFF);  //ģʽ����  1/3 Bais 1/4 Duty֡Ƶ��80Hz,�ڲ�ϵͳ��������lcd����ʾ
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_2|F_160HZ|RCOFF_LCDOFF); //ģʽ����  1/2 Bais 1/4 Duty֡Ƶ��160Hz,�ڲ�ϵͳ��������lcd����ʾ
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_3|F_160HZ|RCOFF_LCDOFF); //ģʽ����  1/3 Bais 1/4 Duty֡Ƶ?60Hz,�ڲ�ϵͳ��������lcd����ʾ
}
/*******************************************************************************
* Function Name  : Exit_Standby
* Description    : �˳�����͹���ģʽ
* Input          ��None 
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_Exit_PowerOff(void)
{	
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_2|F_80HZ|RCON_LCDON);  //ģʽ����  1/2 Bais 1/4 Duty֡Ƶ��80Hz,�ڲ�ϵͳ��������lcd����ʾ
	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_3|F_80HZ|RCON_LCDON);  //ģʽ����  1/3 Bais 1/4 Duty֡Ƶ��80Hz,�ڲ�ϵͳ��������lcd����ʾ
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_2|F_160HZ|RCON_LCDON); //ģʽ����  1/2 Bais 1/4 Duty֡Ƶ��160Hz,�ڲ�ϵͳ��������lcd����ʾ
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_3|F_160HZ|RCON_LCDON); //ģʽ����  1/3 Bais 1/4 Duty֡Ƶ?60Hz,�ڲ�ϵͳ��������lcd����ʾ
}

/*******************************************************************************
* Function Name  : Lowlevel_Init
* Description    : ����ͨ����GPIO
* Input          ��None 
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_Lowlevel_Init(void)
{
	//ͨ���ߵ�ƽ��ͬ������ӵ�ƽת����·
	//�˺������ݿͻ���Ƭ������Ӧ���޸�	
	GPIO_SetMode(VK2C22_SCL_PORT, VK2C22_SCL_PIN, GPIO_MODE_OUTPUT);
	GPIO_SetMode(VK2C22_SDA_PORT, VK2C22_SDA_PIN, GPIO_MODE_QUASI);
	
  //I2C���߿���Ϊ�ߵ�ƽ		
	VK2C22_SCL_H();  
	VK2C22_SDA_H(); 	
}
/*******************************************************************************
* Function Name  : Init
* Description    : ��ʼ������
* Input          ��None 
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_InitSequence(void)
{	
	//�ܽ����ø��ݿͻ���Ƭ������Ӧ���޸�
	VK2C22_Lowlevel_Init();
	//1/4 Duty
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_2|F_80HZ|RCON_LCDON);  //ģʽ����  1/2 Bais 1/4 Duty֡Ƶ��80Hz,�ڲ�ϵͳ��������lcd����ʾ
	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_3|F_80HZ|RCON_LCDON);  //ģʽ����  1/3 Bais 1/4 Duty֡Ƶ��80Hz,�ڲ�ϵͳ��������lcd����ʾ
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_2|F_160HZ|RCON_LCDON); //ģʽ����  1/2 Bais 1/4 Duty֡Ƶ��160Hz,�ڲ�ϵͳ��������lcd����ʾ
//	WriteCmdVK2C22(VK2C22_MODESET|BIAS_1_3|F_160HZ|RCON_LCDON); //ģʽ����  1/3 Bais 1/4 Duty֡Ƶ?60Hz,�ڲ�ϵͳ��������lcd����ʾ
	VK2C22_maxcom=4;
	WriteCmdVK2C22(VK2C22_BLINKSET|BLINK_OFF); 		//��˸�ر�	
//	WriteCmdVK2C22(VK2C22_BLINKSET|BLINK_2HZ); 		//��˸2HZ
//	WriteCmdVK2C22(VK2C22_BLINKSET|BLINK_1HZ); 		//��˸1HZ
//	WriteCmdVK2C22(VK2C22_BLINKSET|BLINK_0D5HZ); 	//��˸0.5HZ
	//SEG/VLCD���ý���ΪVLCD���ڲ���ѹ�������ܹر�,VLCD��VDD�̽�VR=0ƫ�õ�ѹ=VDD
//	WriteCmdVK2C22(VK2C22_IVASET|VLCDSEL_IVAOFF_R0); 
	//SEG/VLCD���ý���ΪVLCD���ڲ���ѹ�������ܹر�,VLCD��VDD���ӵ���VR>0ƫ�õ�ѹ=VLCD
//	WriteCmdVK2C22(VK2C22_IVASET|VLCDSEL_IVAOFF_R1); 
	//SEG/VLCD���ý���ΪSEG���ڲ�ƫ�õ�ѹ������1/3bias=0.652VDD 1/4bias=0.714VDD
	WriteCmdVK2C22(VK2C22_IVASET|SEGSEL_IVA02H);	 
}
/*******************************************************************************
* Function Name  : Init
* Description    : ��ʼ������
* Input          ��None 
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_Init(void)
{	
	//�ܽ����ø��ݿͻ���Ƭ������Ӧ���޸�
	VK2C22_Lowlevel_Init();
	//��ʼ��ʱ��
	VK2C22_InitSequence();
}

/*******************************************************************************
* Function Name  : test_Main
* Description    : ����������
* Input          ��None 
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_Main(void)
{	
	VK2C22_Init();
	VK2C22_DisAll(0x00);
	while(1)
	{
		VK2C22_DisAll(0xff);			//LCDȫ��
		delay_nms(3000);					//��ʱ1S
	
		VK2C22_DisAll(0x00);			//LCDȫ��
		delay_nms(3000);					//��ʱ1S
		
		//LCD����
		VK2C22_DisAll(0xAA);			
		ReadnDataVK2C22(0,VK2C22_readbuf,22);	//����RAM����
		delay_nms(1500);					//��ʱ
		VK2C22_DisAll(0x55);			
		ReadnDataVK2C22(0,VK2C22_readbuf,22);	//����RAM����
		delay_nms(1500);					//��ʱ
		
		//����
		VK2C22_DisAll(0x00);			//LCDȫ��		
		VK2C22_Enter_PowerOff();	//�������ģʽ
		delay_nms(5000);					//��ʱ5S		
		VK2C22_Exit_PowerOff();	//�˳�����ģʽ
		
		VK2C22_DisAll(0x00);			//LCDȫ��
		delay_nms(500);					  //��ʱ
		for(VK2C22_segi=0;VK2C22_segi<VK2C22_SEGNUM;VK2C22_segi++)//seg
		{
			for(VK2C22_comi=0;VK2C22_comi<VK2C22_maxcom;VK2C22_comi++)//com
			{
					VK2C22_DisDotOn(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	//LCD�������
				delay_nms(300);				//��ʱ300mS
				VK2C22_DisDotOff(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	  //������ϵ����������ʵ�ֵ�����������δ���˳�����
			}
		}
		
		VK2C22_DisAll(0xff);			//LCDȫ��
		delay_nms(500);					  //��ʱ
		for(VK2C22_segi=0;VK2C22_segi<VK2C22_SEGNUM;VK2C22_segi++)//seg
		{
			for(VK2C22_comi=0;VK2C22_comi<VK2C22_maxcom;VK2C22_comi++)//com
			{
					VK2C22_DisDotOff(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	//LCD����ر�
				delay_nms(300);				//��ʱ300mS
				VK2C22_DisDotOn(VK2C22_segtab[VK2C22_segi],VK2C22_comi);  //������ϵ���رպ���ʵ�ֵ���رգ����δ���˳��ر�
			}
		}
		delay_nms(1000);					  //��ʱ
	}
}
/************************END OF FILE****/
