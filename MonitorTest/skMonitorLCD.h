/*******************************************************************************
*  skMonitorLCD.h - Ｉ２Ｃ通信を行う関数のインクルードファイル                 *
*               (PIC 12F1822 16F182x 16F193x 18F25K22)                         *
*                                                                              *
* ============================================================================ *
*   VERSION  DATE        BY             CHANGE/COMMENT                         *
* ---------------------------------------------------------------------------- *
*   3.01     2015-10-07  きむ茶工房     MPLAB X・XC8 V1.32用に書換え           *
*******************************************************************************/
#ifndef _SKMONITORLCD_H_
#define _SKMONITORLCD_H_

#ifndef _XTAL_FREQ
 // Unless already defined assume 8MHz system frequency
 // This definition is required to calibrate __delay_us() and __delay_ms()
 #define _XTAL_FREQ 8000000 // 使用するPIC等により動作周波数値を設定する
#endif
#define BAUDRATE      51    // 9600bps(8MHz=51)(4MHz=25)(16MHz=103)
#define MONITOR_PIN   RA2   // モニタ出力するピンの番号を設定する


void MonitorInit() ;
void MonitorPutc(unsigned char c) ;
void MonitorPuts(const char * s) ;
void MonitorPutb(unsigned char c) ;
void MonitorPutd(unsigned char c) ;
void MonitorPuth(unsigned char c) ;
void MonitorCls(int num) ;

#endif
