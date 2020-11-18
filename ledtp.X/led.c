//https://tool-lab.com/make/macpic-startup-21/ 第21回 プログラム解説 ～ メイン処理 ～

#include <xc.h>

#define _XTAL_FREQ  8000000     // delay用(クロック8MHzで動作時)

// コンフィギュレーション１の設定
#pragma config FOSC = INTOSC    // 内部ｸﾛｯｸを使用する(INTOSC)
#pragma config WDTE = OFF       // ｳｵｯﾁﾄﾞｯｸﾞﾀｲﾏｰ無し(OFF)
#pragma config PWRTE = ON       // 電源ONから64ms後にﾌﾟﾛｸﾞﾗﾑを開始する(ON)
#pragma config MCLRE = OFF      // 外部ﾘｾｯﾄ信号は使用せずにﾃﾞｼﾞﾀﾙ入力(RA5)ﾋﾟﾝとする(OFF)
#pragma config CP = OFF         // ﾌﾟﾛｸﾞﾗﾑﾒﾓﾘｰを保護しない(OFF)
#pragma config CPD = OFF        // ﾃﾞｰﾀﾒﾓﾘｰを保護しない(OFF)
#pragma config BOREN = ON       // 電源電圧降下常時監視機能ON(ON)
#pragma config CLKOUTEN = OFF   // CLKOUTﾋﾟﾝをRA6ﾋﾟﾝで使用する(OFF)
#pragma config IESO = OFF       // 外部・内部ｸﾛｯｸの切替えでの起動はなし(OFF)
#pragma config FCMEN = OFF      // 外部ｸﾛｯｸ監視しない(FCMEN_OFF)

// コンフィギュレーション２の設定
#pragma config WRT = OFF        // Flashﾒﾓﾘｰを保護しない(OFF)
#pragma config PLLEN = OFF      // 動作クロックを32MHzでは動作させない(OFF)
#pragma config STVREN = ON      // スタックがオーバフローやアンダーフローしたらリセットをする(ON)
#pragma config BORV = HI        // 電源電圧降下常時監視電圧(2.5V)設定(HI)
#pragma config LVP = OFF        // 低電圧プログラミング機能使用しない(OFF)

// 指定した時間(num x 10ms)だけウエイトを行う処理関数
void Wait(unsigned int num)
{
     int i ;

     // numで指定した回数だけ繰り返す
     for (i=0 ; i<num ; i++) {
          __delay_ms(10) ;     // 10msプログラムの一時停止
     }
}
// メインの処理関数
void main()
{
     OSCCON = 0b01110010 ;     // 内部クロックは８ＭＨｚとする
     ANSELA = 0b00000000 ;     // AN0-AN4は使用しない全てデジタルI/Oとする
     ANSELB = 0b00000000 ;     // AN5-AN11は使用しない全てデジタルI/Oとする
     TRISA  = 0b00000000 ;     // ピン(RA)は全て出力に割当てる(RA5は入力のみとなる)
     TRISB  = 0b00000000 ;     // ピン(RB)は全て出力に割当てる
     PORTA  = 0b00000000 ;     // RA出力ピンの初期化(全てLOWにする)
     PORTB  = 0b00000000 ;     // RB出力ピンの初期化(全てLOWにする)

     // 約1s毎にLEDの点滅を繰り返す

	while(1) {
          RB4 = 1 ;            // 10番ピン(RB4)にHIGH(5V)を出力する(LED ON)
          RB5 = 0;
          Wait(100) ;          // 1秒ウエイト
          RB4 = 0 ;
          RB5 = 1;// 10番ピン(RB4)にLOW(0V)を出力する(LED OFF)
          Wait(100) ;
          RB5 = 0;
          RB6 = 1;
          Wait(100);
          RB6=0;
          Wait(10);
          RB4=1;
          Wait(5);
          RB4=0;
          RB5=1;
          Wait(5);
          RB5=0;
          RB6=1;
          Wait(5);
          RB6=0;          
          Wait(100);
    }
}