/*******************************************************************************
*  ＬＣＤモニターのサンプルプログラム                                          *
*                                                                              *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2010-06-23  きむ茶工房(きむしげ)  Create                            *
*  1.10    2015-10-07  きむ茶工房(きむしげ)  MPLAB X・XC8 V1.32用に書換え      *
* ============================================================================ *
*  PIC 12F1822                                                                 *
*  MPLAB X(v2.15)                                                              *
*  MPLAB(R) XC8 C Compiler Version 1.32                                        *
*******************************************************************************/
#include <xc.h>
#include <stdlib.h>
#include "skMonitorLCD.h"


// コンフィギュレーション１の設定
#pragma config FOSC     = INTOSC   // 内部ｸﾛｯｸ使用する(INTOSC)
#pragma config WDTE     = OFF      // ｳｵｯﾁﾄﾞｯｸﾞﾀｲﾏｰ無し(OFF)
#pragma config PWRTE    = ON       // 電源ONから64ms後にﾌﾟﾛｸﾞﾗﾑを開始する(ON)
#pragma config MCLRE    = OFF      // 外部ﾘｾｯﾄ信号は使用せずにﾃﾞｼﾞﾀﾙ入力(RA3)ﾋﾟﾝとする(OFF)
#pragma config CP       = OFF      // ﾌﾟﾛｸﾞﾗﾑﾒﾓﾘｰを保護しない(OFF)
#pragma config CPD      = OFF      // ﾃﾞｰﾀﾒﾓﾘｰを保護しない(OFF)
#pragma config BOREN    = ON       // 電源電圧降下常時監視機能ON(ON)
#pragma config CLKOUTEN = OFF      // CLKOUTﾋﾟﾝをRA4ﾋﾟﾝで使用する(OFF)
#pragma config IESO     = OFF      // 外部・内部ｸﾛｯｸの切替えでの起動はなし(OFF)
#pragma config FCMEN    = OFF      // 外部ｸﾛｯｸ監視しない(OFF)

// コンフィギュレーション２の設定
#pragma config WRT    = OFF        // Flashﾒﾓﾘｰを保護しない(OFF)
#pragma config PLLEN  = OFF        // 動作クロックを32MHzでは動作させない(OFF)
#pragma config STVREN = ON         // スタックがオーバフローやアンダーフローしたらリセットをする(ON)
#pragma config BORV   = HI         // 電源電圧降下常時監視電圧(2.5V)設定(HI)
#pragma config LVP    = OFF        // 低電圧プログラミング機能使用しない(OFF)



/*******************************************************************************
*  メインの処理                                                                *
*******************************************************************************/
void main()
{
     int  i ;
     char s[17] ;

     OSCCON  = 0b01110010 ;   // 内部クロックは8MHzとする
     ANSELA  = 0b00000000 ;   // アナログは使用しない（すべてデジタルI/Oに割当てる）
     TRISA   = 0b00000000 ;   // ピンはRA1(SCL)/RA2(SDA)のみ入力(RA3は入力専用)
     PORTA   = 0b00000000 ;   // 出力ピンの初期化(全てLOWにする)

     // LCDモニターを使用する為の初期化処理
     MonitorInit() ;

     i = 0 ;
     while(1) {
          // ２行目を消す
          MonitorPutc(0x11) ;
          MonitorPuts("                ") ;
          // カーソルを２行目の先頭に移動する
          MonitorPutc(0x11) ;
          // 整数値を文字列に変換してＬＣＤ表示
          itoa(s,i,10) ;
          MonitorPuts(s) ;
          i++ ;
          __delay_ms(1000) ;  // １秒後に繰り返す
     }
}
