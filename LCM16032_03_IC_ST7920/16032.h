#ifndef __16032_H__
#define __16032_H__

void exsample(void);                    //��ʾ����
void exdelay(void);                     //��ʾ��ʱ�ӳ���
void putchar(unsigned int c);           //��λд�ַ��ӳ���
void putstr(unsigned char code *s);     //��ʾ�ַ����ӳ���,�ַ���Ϊ0ʱ�˳�
void putstrxy(unsigned char cx,unsigned char cy,unsigned char code *s);
void setcharcgram(unsigned char cindex,unsigned char code *s);
                                        //�����Զ����ַ�����
void charcursornext(void);              //���ַ�λ��Ϊ��һ����Чλ���ӳ���
void putimage(unsigned char code *s);   //��ʾͼ���ӳ���
void putsizeimage(unsigned char XSIZE,unsigned char YSIZE,unsigned char code *s);
                                        //��ʾָ����С��ͼ���ӳ���
void charlcdfill(unsigned int c);       //������ʾc������ַ������ӳ���
void fillLCD(unsigned char d);         //������ʾd������ֽ������ӳ���
void setLCDCursor(void);                     //д���ͼ�����ڲ�RAMָ���ӳ���
void charlcdpos(void);                  //����(CXPOS,CYPOS)�ڲ�DDRAM��ַ���ӳ���
void lcdreset(void);                    //Һ����ʾ��������ʼ���ӳ���
void delay3ms(void);                    //��ʱ3MS�ӳ���
void lcdon(void);                       //LCD��ʾ�����ӳ���
void lcdoff(void);                      //LCD��ʾ�ر��ӳ���
void lcdgraphon(void);                  //��ͼ������ʾ�����ӳ���
void lcdgraphoff(void);                 //��ͼ������ʾ�ر��ӳ���
unsigned char lcdrd(void);              //��Һ����ʾ������������
void lcdwd(unsigned char d);            //��ͼ�������ӳ���
void lcdwc(unsigned char c);            //��ָ���ӳ���
void lcdwaitidle(void);                 //������æ����ӳ���
void fillLCD_OddColumn(unsigned char oddData, unsigned char evenData)  ;
unsigned char ReadKey();  
void Clean(unsigned int c) ;       //������ʾST7920�ڲ���CGROMA����

void DisplayPatterns();
void HandleKey() ;
#endif