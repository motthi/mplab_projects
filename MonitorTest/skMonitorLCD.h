/*******************************************************************************
*  skMonitorLCD.h - �h�Q�b�ʐM���s���֐��̃C���N���[�h�t�@�C��                 *
*               (PIC 12F1822 16F182x 16F193x 18F25K22)                         *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   3.01     2015-10-07  ���ޒ��H�[     MPLAB X�EXC8 V1.32�p�ɏ�����           *
*******************************************************************************/
#ifndef _SKMONITORLCD_H_
#define _SKMONITORLCD_H_

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 8000000 // �g�p����PIC���ɂ�蓮����g���l��ݒ肷��
#endif
#define BAUDRATE      51    // 9600bps(8MHz=51)(4MHz=25)(16MHz=103)
#define MONITOR_PIN   RA2   // ���j�^�o�͂���s���̔ԍ���ݒ肷��


void MonitorInit() ;
void MonitorPutc(unsigned char c) ;
void MonitorPuts(const char * s) ;
void MonitorPutb(unsigned char c) ;
void MonitorPutd(unsigned char c) ;
void MonitorPuth(unsigned char c) ;
void MonitorCls(int num) ;

#endif
