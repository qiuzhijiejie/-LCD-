/**
  ******************************************************************************
  * @file    VK2C22.c
  * @author  kevin_guo
  * @version V1.2
  * @date    10-09-2024
  * @brief   This file contains all the VK2C22 functions. 
	*          ���ļ������� VK2C22
  ******************************************************************************
  * @attention
  ******************************************************************************
  */	
/* Includes ------------------------------------------------------------------*/
#include "VK2C22_IO_I2C.h"
  
/* extern variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define VK2C22_CLK 100 //SCL�ź���Ƶ��,��delay_nusʵ�� 50->10kHz 10->50kHz 5->100kHz
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
unsigned char VK2C22_maxcom;//VK2C22��4com
unsigned char VK2C22_readbuf[20];
/* Private function prototypes -----------------------------------------------*/
void VK2C22_I2C_WRCmd(unsigned char Cmd);
void VK2C22_I2C_WRDat(unsigned char Addr,unsigned char *Databuf,unsigned char cnt);
void VK2C22_I2C_RDDat(unsigned char Addr,unsigned char *Databuf,unsigned char cnt);
void VK2C22_InitSequence(void);
/* Private function ----------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Delay_nuS
* Description    : ��ʱ1uS����,ȡ���ڵ�Ƭ����Ƶ
* Input          : n->��ʱʱ��nuS
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_nuS(unsigned int n)	   
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
* Function Name  : Delay_nmS
* Description    : ��ʱ1mS����
* Input          : n->��ʱʱ��nmS
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_nmS(unsigned long int n)
{
	while(n--)
	{
		Delay_nuS(1000);
	}
}
/*******************************************************************************
* Function Name  : WriteCmdVK2C22
* Description    : д���VK2C22
* Input          : cmd-Ҫд�������
* Output         : None
* Return         : None
*******************************************************************************/
void  WriteCmdVK2C22(unsigned char Cmd)
{
	VK2C22_I2C_WRCmd(Cmd);
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
unsigned char WritenDataVK2C22(unsigned char Addr,unsigned char *Databuf,unsigned char Cnt)
{
  VK2C22_I2C_WRDat(Addr,Databuf,Cnt);
	return 0;
}
/*******************************************************************************
* Function Name  : ReadnData
* Description    : ����ʾRAM��������ݵ�
* Input          : Addr-��ram����ʼ��ַ
*                : VKL144C_readbuf->��ram������buffer
*                : Cnt->��ram�����ݸ���
* Output         : None
* Return         : 0-ok 1-fail
*******************************************************************************/
unsigned char  ReadnDataVK2C22(unsigned char Addr,unsigned char *Databuf,unsigned char Cnt)
{
  VK2C22_I2C_RDDat(Addr,Databuf,Cnt);
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
* Function Name  : Enter_PowerOff
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
* Function Name  : Exit_PowerOff
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
* Function Name  : VK2C22_InitSequence
* Description    : ��ʼ������
* Input          ��None 
* Output         : None
* Return         : None
*******************************************************************************/
void VK2C22_InitSequence(void)
{	
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
	//�ϵ����ʾ������0
	VK2C22_DisAll(0x00);	
	while(1)
	{			
		VK2C22_DisAll(0xff);			//LCDȫ��
		Delay_nmS(3000);					//��ʱ1S
	
		VK2C22_DisAll(0x00);			//LCDȫ��
		Delay_nmS(3000);					//��ʱ1S
		
		//LCD����
		VK2C22_DisAll(0xAA);			
		ReadnDataVK2C22(0,VK2C22_readbuf,22);	//����RAM����
		Delay_nmS(1500);					//��ʱ
		VK2C22_DisAll(0x55);			
		ReadnDataVK2C22(0,VK2C22_readbuf,22);	//����RAM����
		Delay_nmS(1500);					//��ʱ

		//����
		VK2C22_DisAll(0x00);			//LCDȫ��		
		VK2C22_Enter_PowerOff();	//�������ģʽ
		Delay_nmS(5000);					//��ʱ5S		
		VK2C22_Exit_PowerOff();	//�˳�����ģʽ
		
		VK2C22_DisAll(0x00);			//LCDȫ��
		Delay_nmS(500);					  //��ʱ
		for(VK2C22_segi=0;VK2C22_segi<VK2C22_SEGNUM;VK2C22_segi++)//seg
		{
			for(VK2C22_comi=0;VK2C22_comi<VK2C22_maxcom;VK2C22_comi++)//com
			{
				VK2C22_DisDotOn(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	//LCD�������
				Delay_nmS(300);				//��ʱ300mS
				VK2C22_DisDotOff(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	  //������ϵ����������ʵ�ֵ�����������δ���˳�����
			}
		}
		
		VK2C22_DisAll(0xff);			//LCDȫ��
		Delay_nmS(500);					  //��ʱ
		for(VK2C22_segi=0;VK2C22_segi<VK2C22_SEGNUM;VK2C22_segi++)//seg
		{
			for(VK2C22_comi=0;VK2C22_comi<VK2C22_maxcom;VK2C22_comi++)//com
			{
				if(VK2C22_maxcom==8)
					VK2C22_DisDotOff(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	//LCD����ر�
				else
					VK2C22_DisDotOff(VK2C22_segtab[VK2C22_segi],VK2C22_comi);	//LCD����ر�
				Delay_nmS(300);				//��ʱ300mS
				VK2C22_DisDotOn(VK2C22_segtab[VK2C22_segi],VK2C22_comi);  //������ϵ���رպ���ʵ�ֵ���رգ����δ���˳��ر�
			}
		}
		Delay_nmS(1000);					  //��ʱ
	}
}
/************************END OF FILE****/
