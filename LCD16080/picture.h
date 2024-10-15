#ifndef __picture_H__
#define __picture_H__
extern unsigned int code picture [];
extern unsigned int code picture2[];
extern unsigned int code picture3[];
extern unsigned int code picture4[];
extern unsigned int code picture5[];
extern unsigned int code picture6[];
unsigned char code Img_sunman_32[];

unsigned char code EnglishCharDot[];
unsigned char code EnglishCode[];
unsigned int  code ChineseCode[];
unsigned char code ChineseCharDot[];


#endif




#if 0
//SMG240128A��׼ͼ�ε�����Һ����ʾģ�����չ��ʾ����[C51�������][MCS51ģ����߷�ʽ]
//Ӧ�ò�Ʒ: SMG240128A��׼ͼ�ε�����Һ����ʾģ��
//  ����ʾ����������SMG240128AҺ����ʾģ����MCS51ϵ�е�Ƭ������MCS51ģ����ߵ�
//Ӳ�����߷�ʽ��
//  ����ʾ�������T6963C����оƬ��MCS51ģ����߷�ʽ�ӳ���,T6963C����оƬ��240128
//Һ����ʾģ��Ļ����ӳ���,240128ϵ�л�ͼ�ӳ���,240128ϵ��ͼ���ӳ���,240128ϵ
//�о�����Ӣ���ֿ��ӳ���,�Լ�SMG240128ϵ�б�׼ͼ�ε�����Һ����ʾ����չ��ʾ�ӳ���.
//  ����ʾ������Ϊ,��240��X128�еĵ���Һ����ʾ��������,ͼƬ��ʾ,Ӣ���ַ�����ʾ,����
//�ַ�����ʾ,������ʾ�ַ���,���ƾ���,д��,����ֱ��,ȫ����ʾ.
//-------------------------------------------------------------------------------
//��������: 2009.08.17
//�������: VW For Windows
//Ӳ������: AT89C52 MCU,MCS-51ϵ�� MCU,etc.
//������: �ҽ���(chujianjun@sunman.cn),̷��(tanchao@sunman.cn).
//����֧��: �绰(0731-84167806,84167807),����(0731-84167807),��ַ(www.sunman.cn)
//��Ȩ��Ϣ: ��ɳ̫���˵������޹�˾��Ȩ����,ת����ָ������.
//�ο���ҳ: http:/www.sunman.cn/lcm/product/SMG240128A.html
//-------------------------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
//����Ϊ��ʾ����ĺ�������
void exsample(void);                    //��ʾ����
void exdelay(void);                     //��ʾ��ʱ�ӳ���
void putchar(unsigned int c);           //��λд�ַ��ӳ���
void putstr(unsigned char code *s);     //��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
unsigned char code *getchinesecodepos(unsigned int ac);
unsigned char code *getenglishcodepos(unsigned char ac);
void putimage(unsigned char code *s);   //��ʾͼ���ӳ���
void putsizeimage(unsigned char XSIZE,unsigned char YSIZE,unsigned char code *s);
                                        //��ʾָ����С��ͼ���ӳ���
void point(bit b);
void line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b);
void lineto(unsigned char x1,unsigned char y1,bit b);//����(XPOS,YPOS)-(X1,Y1)��ֱ��
void rect(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b);
void lcdfill(unsigned char d);          //������ʾd������ֽ������ӳ���
void lcdpos(void);                      //���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
void lcdreset(void);                    //Һ����ʾ��������ʼ���ӳ���
void lcdwd(unsigned char d);            //��ͼ�������ӳ���
unsigned char lcdrd(void);              //��ͼ�������ӳ���
void lcdwc(unsigned char c);            //��ָ���ӳ���
void lcdwc2(unsigned char c,unsigned char d);//��2�ֽ�ָ���ӳ���
void lcdwc3(unsigned char c,unsigned char d1,unsigned char d2);//��3�ֽ�ָ���ӳ���
unsigned char lcdrdata(void);           //�������ӳ���
void lcdwdata(unsigned char d);         //�������ӳ���
void lcdwaitidle(void);                 //æ����ӳ���
//-------------------------------------------------------------------------------
//SMG240128A��Ʒ����˵������ʾ����
//PIN1: FG   [�����]-------------------VSS
//PIN2: VSS  [��Դ��]-------------------VSS
//PIN3: VDD  [��Դ����]-----------------VDD(+5V)
//PIN4: Vo   [LCD ƫѹ����]-------------��10K�Ŀɵ�����2K���赽VSS��VEE
//                                      Vo=VEEʱΪ��ʾ����
//PIN5: WR   [д�ź� ����Ч]------------P3.1
//PIN6: RD   [���ź� ����Ч]------------P3.2
//PIN7: CE   [ʹ���ź� ����Ч]----------P3.3
//PIN8: CD   [����/����ѡ��ˣ�H/L��]---P3.0
//PIN9: NC   [�ս�]---------------------������
//PIN10:RST  [��λ�� ����Ч]------------VDD
//PIN11:D0   [Data I/O]-----------------P1.0
//PIN12:D1   [Data I/O]-----------------P1.1
//PIN13:D2   [Data I/O]-----------------P1.2
//PIN14:D3   [Data I/O]-----------------P1.3
//PIN15:D4   [Data I/O]-----------------P1.4
//PIN16:D5   [Data I/O]-----------------P1.5
//PIN17:D6   [Data I/O]-----------------P1.6
//PIN18:D7   [Data I/O]-----------------P1.7
//PIN19:FS   [�������]-----------------VSS
//PIN20:VEE  [LCD��ѹ���]--------------�ṩҺ������ѹ.
//PIN21:BLA  [����Դ����]---------------��ʹ��˵����.
//PIN22:BLK  [����Դ����]---------------VSS
//ע:8031�ľ���Ƶ��Ϊ12MHz.
//��μ�http://download.sunman.cn/lcm/product/1/SMG240128A.pdf
//-------------------------------------------------------------------------------
//����Ϊ��Ʒ�ӿ���������ʾ�����е�Ԥ����
//�û��ڱ�дӦ�ó���ʱ,�谴�Լ���ʵ��Ӳ�����������¶���
sbit CDPIN=P3^0;                        // C/D��Ӧ��Ƭ������
sbit CEPIN=P3^3;                        // CE��Ӧ��Ƭ������
sbit WRPIN=P3^1;                        // WR��Ӧ��Ƭ������
sbit RDPIN=P3^2;                        // RD��Ӧ��Ƭ������
//-------------------------------------------------------------------------------
//����XPOS,YPOS��������ָʾ��ǰ�������λ�õ�Ԥ����
//�û��ڱ�дӦ�ó���ʱ,�谴�Լ���ʵ�����������Ҫ�����¶���
unsigned char XPOS;                     //�з���LCD����λ��ָ��
unsigned char YPOS;                     //�з���LCD����λ��ָ��
bit CharImageReverse;                   //�ַ���ͼ�εķ��Կ���,0(������ʾ),1(����)

#define XDOTS   240                     //ͼ�οռ�X�����С
#define YDOTS   128                     //ͼ�οռ�X�����С
//-------------------------------------------------------------------------------
//����Ϊ�������Ӣ���ֿ�
//ʵ��ʹ��ʱ�������Sunman�������Ӣ���ַ������������.exe�Զ����ɵ�charlib.c��
//�ļ����滻�ò���
//�������Ӣ���ַ��ⳣ������
#define ENGLISHCHARNUMBER  8       //�����Ӣ���ַ����е�Ӣ���ַ��ĸ���
#define CHINESECHARNUMBER  11      //����������ַ����е������ַ��ĸ���
#define ENGLISHCHARSIZE    8       //Ӣ���ַ�X������ʾ��ĸ���
#define CHINESECHARSIZE    16      //�����ַ�X������Ӣ���ַ�Y������ʾ��ĸ���
#define ENGLISHCHARDOTSIZE 16      //����Ӣ���ַ�������ֽ���
#define CHINESECHARDOTSIZE 32      //���������ַ�������ֽ���

unsigned char code EnglishCode[]={
0x2e,    //�ַ�001:[.]
0x41,    //�ַ�002:[A]
0x43,    //�ַ�003:[C]
0x4d,    //�ַ�004:[M]
0x4e,    //�ַ�005:[N]
0x53,    //�ַ�006:[S]
0x55,    //�ַ�007:[U]
0x57     //�ַ�003:[W]
};

unsigned int code ChineseCode[]={
0xb3a4,  //�ַ�001:[��]
0xb5e7,  //�ַ�002:[��]
0xb9ab,  //�ַ�003:[��]
0xc8cb,  //�ַ�004:[��]
0xc9b3,  //�ַ�005:[ɳ]
0xcbbe,  //�ַ�006:[˾]
0xccab,  //�ַ�007:[̫]
0xcfde,  //�ַ�008:[��]
0xd1f4,  //�ַ�009:[��]
0xd3d0,  //�ַ�010:[��]
0xd7d3   //�ַ�011:[��]
};

unsigned char code EnglishCharDot[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   //�ַ�001:[.]
0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,
0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,   //�ַ�002:[A]
0x24,0x3c,0x44,0x42,0x42,0xe7,0x00,0x00,
0x00,0x00,0x00,0x3e,0x42,0x42,0x80,0x80,   //�ַ�003:[C]
0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00,
0x00,0x00,0x00,0xee,0x6c,0x6c,0x6c,0x6c,   //�ַ�004:[M]
0x54,0x54,0x54,0x54,0x54,0xd6,0x00,0x00,
0x00,0x00,0x00,0xc7,0x62,0x62,0x52,0x52,   //�ַ�005:[N]
0x4a,0x4a,0x4a,0x46,0x46,0xe2,0x00,0x00,
0x00,0x00,0x00,0x3e,0x42,0x42,0x40,0x20,   //�ַ�006:[S]
0x18,0x04,0x02,0x42,0x42,0x7c,0x00,0x00,
0x00,0x00,0x00,0xe7,0x42,0x42,0x42,0x42,   //�ַ�007:[U]
0x42,0x42,0x42,0x42,0x42,0x3c,0x00,0x00,
0x00,0x00,0x00,0xd6,0x92,0x92,0x92,0x92,   //�ַ�003:[W]
0xaa,0xaa,0x6c,0x44,0x44,0x44,0x00,0x00
};

unsigned char code ChineseCharDot[]={
0x08,0x00,0x08,0x10,0x08,0x20,0x08,0x40,   //�ַ�001:[��]
0x09,0x80,0x0e,0x00,0x08,0x00,0xff,0xfe,
0x0a,0x00,0x09,0x00,0x08,0x80,0x08,0x40,
0x09,0x30,0x0a,0x1c,0x0c,0x08,0x08,0x00,
0x01,0x00,0x01,0x00,0x01,0x00,0x3f,0xf8,   //�ַ�002:[��]
0x21,0x08,0x21,0x08,0x3f,0xf8,0x21,0x08,
0x21,0x08,0x21,0x08,0x3f,0xf8,0x21,0x08,
0x01,0x02,0x01,0x02,0x00,0xfe,0x00,0x00,
0x00,0x00,0x04,0x40,0x06,0x40,0x04,0x40,   //�ַ�003:[��]
0x08,0x20,0x08,0x10,0x10,0x18,0x22,0x0e,
0x43,0x04,0x02,0x00,0x04,0x20,0x08,0x10,
0x11,0xf8,0x3f,0x18,0x10,0x10,0x00,0x00,
0x01,0x00,0x01,0x80,0x01,0x00,0x01,0x00,   //�ַ�004:[��]
0x01,0x00,0x01,0x00,0x02,0x80,0x02,0x80,
0x04,0x80,0x04,0x40,0x08,0x60,0x08,0x30,
0x10,0x18,0x20,0x0e,0x40,0x04,0x00,0x00,
0x20,0x40,0x10,0x40,0x10,0x40,0x01,0x50,   //�ַ�005:[ɳ]
0x41,0x48,0x2a,0x44,0x0a,0x42,0x14,0x40,
0x10,0x44,0x20,0x44,0xe0,0x08,0x20,0x10,
0x20,0x20,0x20,0xc0,0x23,0x00,0x2c,0x00,
0x00,0x00,0x3f,0xfc,0x00,0x04,0x00,0x04,   //�ַ�006:[˾]
0x7f,0xe4,0x00,0x04,0x00,0x04,0x3f,0xc4,
0x20,0x44,0x20,0x44,0x3f,0xc4,0x20,0x44,
0x20,0x04,0x00,0x14,0x00,0x08,0x00,0x00,
0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,   //�ַ�007:[̫]
0x7f,0xfe,0x01,0x00,0x01,0x00,0x01,0x00,
0x02,0x80,0x02,0x40,0x04,0x20,0x05,0x10,
0x08,0x98,0x10,0xcc,0x20,0x86,0x40,0x04,
0x00,0x00,0xfb,0xf8,0x92,0x08,0x93,0xf8,   //�ַ�008:[��]
0xa2,0x08,0xa2,0x08,0x93,0xf8,0x8a,0x80,
0x8a,0x48,0xaa,0x50,0x92,0x20,0x82,0x20,
0x82,0x10,0x82,0x8e,0x83,0x04,0x82,0x00,
0x00,0x00,0x7d,0xfc,0x45,0x04,0x49,0x04,   //�ַ�009:[��]
0x49,0x04,0x51,0x04,0x49,0xfc,0x45,0x04,
0x45,0x04,0x45,0x04,0x69,0x04,0x51,0x04,
0x41,0xfc,0x41,0x04,0x40,0x00,0x40,0x00,
0x01,0x00,0x01,0x00,0x7f,0xfe,0x02,0x00,   //�ַ�010:[��]
0x04,0x00,0x0f,0xf0,0x18,0x10,0x28,0x10,
0x4f,0xf0,0x88,0x10,0x08,0x10,0x0f,0xf0,
0x08,0x10,0x08,0x90,0x08,0x70,0x08,0x20,
0x00,0x00,0x3f,0xf0,0x00,0x20,0x00,0x40,   //�ַ�011:[��]
0x00,0x80,0x01,0x00,0x01,0x00,0x01,0x04,
0xff,0xfe,0x01,0x00,0x01,0x00,0x01,0x00,
0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00
};
//-------------------------------------------------------------------------------
//����ΪͼƬ��������
//ʵ��ʹ��ʱ�������SUNMANͼ�ε������������.EXE�Զ����ɵ�imagelib.c�ļ����滻��
//����
unsigned char code Img_sunman_32[]={32,32,
0x00,0x0f,0xf0,0x00,
0x00,0x7f,0xfe,0x00,
0x01,0xf0,0x0f,0x80,
0x03,0xc0,0x03,0xc0,
0x07,0x0f,0xf0,0xe0,
0x0e,0x3f,0xfc,0x70,
0x1c,0xfe,0x7f,0x38,
0x39,0xfc,0x3f,0x9c,
0x33,0xfc,0x3f,0xcc,
0x73,0xfe,0x7f,0xce,
0x67,0xff,0xff,0xe6,
0x67,0xe7,0xe7,0xe6,
0xcf,0xe3,0xc7,0xf3,
0xcf,0xe1,0x87,0xff,
0xcf,0xe4,0x27,0xff,
0xc0,0x06,0x60,0x03,
0xc0,0x07,0xe0,0x03,
0xff,0xe7,0xe7,0xf3,
0xff,0xe7,0xe7,0xf3,
0xcf,0xe7,0xe7,0xf3,
0x67,0xe7,0xe7,0xe6,
0x67,0xff,0xff,0xe6,
0x73,0xff,0xff,0xce,
0x33,0xff,0xff,0xcc,
0x39,0xff,0xff,0x9c,
0x1c,0xff,0xff,0x38,
0x0e,0x3f,0xfc,0x70,
0x07,0x0f,0xf0,0xe0,
0x03,0xc0,0x03,0xc0,
0x01,0xf0,0x0f,0x80,
0x00,0x7f,0xfe,0x00,
0x00,0x0f,0xf0,0x00
};
//-------------------------------------------------------------------------------

void main(void)
{   while(1)
    {   lcdreset();                     //��ʼ��Һ����ʾ������
        exsample();                     //��ʾ����
    }
}
void exsample(void)                     //��ʾ����
{
//0.��ʾǰ��׼��,��LCDҺ����ʾȫ�����
    CharImageReverse=0;                 //���Թر�
    lcdfill(0);                         //����

//1.ͼƬ����: ��(16,48)λ����ʾ32����SUNMANͼ��
    XPOS=16;
    YPOS=48;
    putimage(Img_sunman_32);            //д���ݵ���ǰLCDRAM��ַ��
    exdelay();                          //��ʱԼ600mS

//2.�ַ�������: ��(84,48)λ����ʾ"WWW.SUNMAN.CN"�ַ���.
    XPOS=84;
    YPOS=48;
    putstr("WWW.SUNMAN.CN");
    exdelay();                          //��ʱԼ600mS

//3.�ַ�������: ��(48,64)λ����ʾ"��ɳ̫���˵������޹�˾"�ַ���.
    XPOS=48;
    YPOS=64;
    putstr("��ɳ̫���˵������޹�˾");
    exdelay();                          //��ʱԼ600mS

//3.���Բ���: ��(48,64)λ�÷���"��ɳ̫���˵������޹�˾"�ַ���.
    XPOS=48;
    YPOS=64;
    CharImageReverse=1;
    putstr("��ɳ̫���˵������޹�˾");
    CharImageReverse=0;
    exdelay();                          //��ʱԼ600mS

//3.��ͼ����: RECT(15,47)-(224,80),������.
    rect(15,47,224,80,1);
    exdelay();                          //��ʱԼ600mS

//4.��ͼ����: point(15,85),����.
    XPOS=15;
    YPOS=85;
    point(1);
    exdelay();                          //��ʱԼ600mS

//5.��ͼ����: line(15,85)-(119,120),����.
    line(15,85,119,120,1);
    exdelay();                          //��ʱԼ600mS

//6.��ͼ����: lineto(224,85),����.
    lineto(224,85,1);
    exdelay();                          //��ʱԼ600mS

//7.��ͼ����: lineto(15,85),����.
    lineto(15,85,1);
    exdelay();                          //��ʱԼ600mS

//8.ȫ������: ���������ȫ����ʾ.
    lcdfill(0);                        //ȫ��
    exdelay();                          //��ʱԼ600mS

}
void exdelay(void)                      //��ʾ��ʱ�ӳ���
{ unsigned char i,j,k;                  //��ʱԼ600mS
  for(i=0;i<60;i++)
    for(j=0;j<64;j++)
      for(k=0;k<51;k++);
}
//-------------------------------------------------------------------------------
//����putcharΪ�ַ�����Ļ����ӳ���,putstrΪ�ַ�����������ӳ���,getchinesecodepos,
//getenglishcodeposΪ�ַ�����ĸ����ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void putchar(unsigned int c).
//����:��(XPOS,YPOS)λ��д�����ַ�����,��c>128 ��ʾΪ�����ַ�,����Ϊ�����ַ�
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void putchar(unsigned int c)            //��λд�ַ��ӳ���
{   if(c>128)
        putsizeimage(CHINESECHARSIZE,CHINESECHARSIZE,getchinesecodepos(c));
    else
        putsizeimage(ENGLISHCHARSIZE,CHINESECHARSIZE,getenglishcodepos(c));
}
//-------------------------------------------------------------------------------
//�ӳ�������:void putstr(unsigned char code *s).
//����:д�ַ�������,��*s=0 ��ʾ�ַ�������.
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char code *getchinesecodepos(unsigned char ac).
//����:���ݵ�ǰ�����ַ���������õ���ǰ�����ַ�����ֿ����λ��.
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
unsigned char code *getchinesecodepos(unsigned int ac)
{   unsigned int min,max,mid,midc;
    min=0;
    max=CHINESECHARNUMBER-1;
    while(1)
    {   if(max-min<2)
        {   if(ChineseCode[min]==ac)
                mid=min;
            else if(ChineseCode[max]==ac)
                mid=max;
            else
                mid=0;
            break;
        }
        mid=(max+min)/2;
        midc=ChineseCode[mid];
        if(midc==ac)
            break;
        else if(midc>ac)
            max=mid-1;
        else
            min=mid+1;
    }
    return ChineseCharDot+mid*CHINESECHARDOTSIZE;
}
//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char code *getenglishcodepos(unsigned char ac).
//����:���ݵ�ǰASCII�ַ���������õ���ǰASCII�ַ�����ֿ����λ��.
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
unsigned char code *getenglishcodepos(unsigned char ac)
{   unsigned char min,max,mid,midc;
    min=0;
    max=ENGLISHCHARNUMBER-1;
    while(1)
    {   if(max-min<2)
        {   if(EnglishCode[min]==ac)
                mid=min;
            else if(EnglishCode[max]==ac)
                mid=max;
            else
                mid=0;
            break;
        }
        mid=(max+min)/2;
        midc=EnglishCode[mid];
        if(midc==ac)
            break;
        else if(midc>ac)
            max=mid-1;
        else
            min=mid+1;
    }
    return EnglishCharDot+mid*ENGLISHCHARDOTSIZE;
}
//-------------------------------------------------------------------------------
//����putsizeimageΪͼ�ζ���Ļ����ӳ���,putimageΪͼ�ζ���������ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void putsizeimage(unsigned char XSIZE,unsigned YSIZE,
//                             unsigned char code *s)
//����:��(XPOS,YPOS)λ�û���XSIZE�м�YISZE�е����ͼ��*S.
//�޸�����:2009.8.17
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void putsizeimage(unsigned char XSIZE,unsigned char YSIZE,unsigned char code *s)
{  unsigned char k,lx,ly,a1,a2,x,Lcd_Mask;
   k=XPOS&0x7;
   XSIZE+=k;
   x=XPOS;
   s--;
   for(ly=0;ly<YSIZE;ly++,YPOS++)
   {  for(XPOS=x,lx=k;lx<XSIZE;)
      {  unsigned char p;
         a1=*s;
         s++;
         a2=*s;
         if(CharImageReverse)
         {   a1=~a1;
             a2=~a2;
         }
         for(p=0;p<k;p++)
         {  a2>>=1;
            if((a1&0x1)==1)
               a2+=0x80;
            a1>>=1;
         }
         if((k==0) && (XSIZE<lx+8))
         {   lcdpos();
             lx+=8;
             XPOS+=8;
         }
         else
         {   lcdpos();
             a1=lcdrd();
             lcdpos();
             lx+=8;
             XPOS+=8;
             Lcd_Mask=0xff;
             p=XSIZE&0x7;
             while(p>0)
             {   Lcd_Mask>>=1;
                 XPOS--;
                 p--;
             }
             p=0xff;
             while(XSIZE<lx)
             {   lx--;
                 XPOS--;
                 p<<=1;
             }
             Lcd_Mask&=p;
             a2&=Lcd_Mask;
             a2|=a1&(~Lcd_Mask);
         }
         lcdwd(a2);
      }
      if((k!=0) && (XSIZE&0x7 != 0) && (k >= XSIZE&0x7)) s--;
   }
   if(XDOTS-x < XSIZE-k)
       XPOS=0;
   else
       YPOS-=YSIZE;
}
//-------------------------------------------------------------------------------
//�ӳ�������:void putimage(unsigned char code *s).
//����:��(XPOS,YPOS)λ�û���XSIZE[*s]�м�YISZE[*(s+1)]�е����ͼ��[*(s+2)].
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void putimage(unsigned char code *s)    //��ʾͼ���ӳ���
{   unsigned char XSIZE,YSIZE;
    XSIZE=*s;
    s++;
    YSIZE=*s;
    s++;
    putsizeimage(XSIZE,YSIZE,s);
}
//-------------------------------------------------------------------------------
//����pointΪ��ͼ�����Ļ����ӳ���,line,lineto,rectΪ��ͼ�����������ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void point(bit b).
//����:��b��������(XPOS,YPOS)λ�û��Ƶ�.
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void point(bit b)
{   unsigned char i,Lcd_Mask,j;
    Lcd_Mask=0x80;
    i=XPOS&0x7;
    while(i>0)
    {   Lcd_Mask>>=1;
        i--;
    }
    lcdpos();
    j=lcdrd();
    lcdpos();
    if(b)
        lcdwd(j|Lcd_Mask);
    else
        lcdwd(j&(~Lcd_Mask));
}
//-------------------------------------------------------------------------------
//�ӳ�������:void line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)��ֱ��
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void line(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
{   unsigned char dx,dy;
    unsigned int dk;
    XPOS=x0;
    YPOS=y0;
    point(b);
    dx=(x1>=x0)?x1-x0:x0-x1;
    dy=(y1>=y0)?y1-y0:y0-y1;
    if(dx==dy)
    {   while(XPOS!=x1)
        {   if(x1>x0) XPOS++;else XPOS--;
            if(y1>y0) YPOS++;else YPOS--;
            point(b);
        }
    }
    else if (dx>dy)
    {   dk=dy;
        dy=0;
        while(XPOS!=x1)
        {   if(x1>x0) XPOS++;else XPOS--;
            dy++;
            if(y1>y0) YPOS=y0+(dk*dy+dx/2)/dx;else YPOS=y0-(dk*dy+dx/2)/dx;
            point(b);
        }
    }
    else
    {   dk=dx;
        dx=0;
        while(YPOS!=y1)
        {   if(y1>y0) YPOS++;else YPOS--;
            dx++;
            if(x1>x0) XPOS=x0+(dk*dx+dy/2)/dy;else XPOS=x0-(dk*dx+dy/2)/dy;
            point(b);
        }
    }
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lineto(unsigned char x1,unsigned char y1,bit b)
//����:��b�����ݻ���(XPOS,YPOS)-(x1,y1)��ֱ��
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lineto(unsigned char x1,unsigned char y1,bit b)//����(XPOS,YPOS)-(X1,Y1)��ֱ��
{   line(XPOS,YPOS,x1,y1,b);
}
//-------------------------------------------------------------------------------
//�ӳ�������:void rect(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
//����:��b�����ݻ���(x0,y0)-(x1,y1)�ľ���
//�޸�����:2009.8.18
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void rect(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,bit b)
{   line(x0,y0,x1,y0,b);
    line(x1,y0,x1,y1,b);
    line(x1,y1,x0,y1,b);
    line(x0,y1,x0,y0,b);
}
//-------------------------------------------------------------------------------
//����lcdfill,lcdpos,lcdresetΪT6963��Ӳ���ӿڵ�240128Һ����ʾģ��Ļ����ӳ���
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdfill(unsigned char d).
//����:������ʾd��ʾ���ֽ�����.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdfill(unsigned char d)           //������ʾd������ֽ������ӳ���
{   unsigned char i,j;
    lcdwc3(0x24,0,0);                   //�����ڲ�RAM��ַΪ0
    for(i=0;i<128;i++)    //128��
        for(j=0;j<30;j++)               //30���ֽ����ݹ�240��
            lcdwd(d);                   //��ͼ������
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdpos(void).
//����:���������(XPOS,YPOS)λ�ö�Ӧ���ڲ�RAM��ַ.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdpos(void)                       //���������(XPOS,YPOS)�ڲ�RAM��ַ���ӳ���
{  unsigned int CurrentAddress;
   CurrentAddress=YPOS*30;              //LCDRAM��ַ=30*YPOS+(XPOS/8)
   CurrentAddress+=XPOS/8;
   lcdwc3(0x24,CurrentAddress&0xff,CurrentAddress/256);
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdreset(void)
//����:Һ����ʾ��������ʼ��
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdreset(void)                     //Һ����ʾ��������ʼ���ӳ���
{   lcdwc(0x80);                        //OR MODE
    lcdwc(0x98);                        //ͼ��ģʽ��
    lcdwc3(0x42,0,0);                   //����ͼ����ʾ���׵�ַΪ0
    lcdwc3(0x43,30,0);                  //����ͼ����ʾ�����Ϊ30�ֽڹ�240��
}
//-------------------------------------------------------------------------------
//����lcdwd,lcdrd,lcdwc,lcdwc2,lcdwc3ΪT6963C��Ӳ���ӿ�[MCS51ģ����߽ӿڷ�ʽ]��
//    �����ӳ���;lcdwdata,lcdrdata,lcdwaitidleΪ�ڲ��ӳ���.
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwd(unsigned char d).
//����:��Һ����ʾ������дͼ������.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwd(unsigned char d)             //��ͼ�������ӳ���
{   lcdwc2(0xc0,d);
}
//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char lcdrd(void).
//����:��Һ����ʾ�������ж�ͼ������.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
unsigned char lcdrd(void)               //��ͼ�������ӳ���
{   lcdwc(0xc1);                        //�Ͷ�ͼ������ָ��
    return lcdrdata();                  //������
}
//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc(unsigned char c).
//����:��Һ����ʾ��������ָ��.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc(unsigned char c)             //��ָ���ӳ���
{   lcdwaitidle();                      //���Һ����ʾ�������Ƿ����
    P1=c;
    CDPIN=1;                            //CD=1 CE=0 WR=0
    CEPIN=0;
    WRPIN=0;
    _nop_();
    WRPIN=1;
    CEPIN=1;
}
//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc2(unsigned char c,unsigned char d).
//����:��Һ����ʾ��������2�ֽ�ָ��.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc2(unsigned char c,unsigned char d) //��2�ֽ�ָ���ӳ���
{   lcdwdata(d);                        //��ָ�����
    lcdwc(c);                           //��ָ����
}
//-------------------------------------------------------------------------------
//�ӳ�������:lcdwc3(unsigned char c,unsigned char d1,unsigned char d2).
//����:��Һ����ʾ��������3�ֽ�ָ��.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwc3(unsigned char c,unsigned char d1,unsigned char d2) //��3�ֽ�ָ���ӳ���
{   lcdwdata(d1);                        //��ָ�����1
    lcdwdata(d2);                        //��ָ�����2
    lcdwc(c);                            //��ָ����
}
//-------------------------------------------------------------------------------
//�ӳ�������:unsigned char lcdrdata(void).
//����:��Һ����ʾ�������ж�����.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
unsigned char lcdrdata(void)            //�������ӳ���
{   unsigned char d;
    lcdwaitidle();                      //���Һ����ʾ�������Ƿ����
    P1=0xff;
    CDPIN=0;                            //CD=0 CE=0 RD=0
    CEPIN=0;
    RDPIN=0;
    _nop_();
    d=P1;
    RDPIN=1;
    CEPIN=1;
    return d;
}
//-------------------------------------------------------------------------------
//�ӳ�������:void lcdwdata(unsigned char d).
//����:��Һ����ʾ������������.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwdata(unsigned char d)          //�������ӳ���
{   lcdwaitidle();                      //���Һ����ʾ�������Ƿ����
    P1=d;
    CDPIN=0;                            //CD=0 CE=0 WR=0
    CEPIN=0;
    WRPIN=0;
    _nop_();
    WRPIN=1;
    CEPIN=1;
}
//-------------------------------------------------------------------------------
//�ӳ�������:voidlcdwaitidle(void).
//����:æ���,�ڶ�Һ����ʾ������������ÿһ��ָ��֮ǰ,����Һ����ʾ���Ƿ����.
//�޸�����:2009.08.07
//�޸���:chujianjun@sunman.cn,tanchao@sunman.cn
//-------------------------------------------------------------------------------
void lcdwaitidle(void)                  //æ����ӳ���
{   unsigned char i,d;
    P1=0xff;
    CDPIN=1;                            //CD=1 CE=0 RD=0
    CEPIN=0;
    for(i=0;i<20;i++)                   //
    {   RDPIN=0;
        _nop_();
        d=P1;
        RDPIN=1;
        if( (d&0x3) == 0x3 ) break;     //D0D1=11 �����˳�
    }
    CEPIN=1;
}

#endif 0