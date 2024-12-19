#ifndef __lcd12832_H__
#define __lcd12832_H__



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
void glcdfill(unsigned char d);         //������ʾd������ֽ������ӳ���
void glcdpos(void);                     //д���ͼ�����ڲ�RAMָ���ӳ���
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
void glcdfill_with_params(unsigned char oddData, unsigned char evenData);
unsigned char key();
void HandleKey();
void DisplayPatterns();
#endif