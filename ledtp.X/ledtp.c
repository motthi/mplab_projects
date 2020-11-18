// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

void Wait(unsigned int num)
{
     int i ;

     // num�Ŏw�肵���񐔂����J��Ԃ�
     for (i=0 ; i<num ; i++) {
          __delay_ms(10) ;     // 10ms�v���O�����̈ꎞ��~
     }
}
// ���C���̏����֐�
void main()
{
     OSCCON = 0b01110010 ;     // �����N���b�N�͂W�l�g���Ƃ���
     ANSELA = 0b00000000 ;     // AN0-AN4�͎g�p���Ȃ��S�ăf�W�^��I/O�Ƃ���
     ANSELB = 0b00000000 ;     // AN5-AN11�͎g�p���Ȃ��S�ăf�W�^��I/O�Ƃ���
     TRISA  = 0b00000000 ;     // �s��(RA)�͑S�ďo�͂Ɋ����Ă�(RA5�͓��݂͂̂ƂȂ�)
     TRISB  = 0b00000000 ;     // �s��(RB)�͑S�ďo�͂Ɋ����Ă�
     PORTA  = 0b00000000 ;     // RA�o�̓s���̏�����(�S��LOW�ɂ���)
     PORTB  = 0b00000000 ;     // RB�o�̓s���̏�����(�S��LOW�ɂ���)

     // ��1s����LED�̓_�ł��J��Ԃ�

	while(1) {
          RB4 = 1 ;            // 10�ԃs��(RB4)��HIGH(5V)���o�͂���(LED ON)
          Wait(100) ;          // 1�b�E�G�C�g
          RB4 = 0 ;            // 10�ԃs��(RB4)��LOW(0V)���o�͂���(LED OFF)
          Wait(100) ;
    }
}