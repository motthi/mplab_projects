/*******************************************************************************
*  �k�b�c���j�^�[�̃T���v���v���O����                                          *
*                                                                              *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2010-06-23  ���ޒ��H�[(���ނ���)  Create                            *
*  1.10    2015-10-07  ���ޒ��H�[(���ނ���)  MPLAB X�EXC8 V1.32�p�ɏ�����      *
* ============================================================================ *
*  PIC 12F1822                                                                 *
*  MPLAB X(v2.15)                                                              *
*  MPLAB(R) XC8 C Compiler Version 1.32                                        *
*******************************************************************************/
#include <xc.h>
#include <stdlib.h>
#include "skMonitorLCD.h"


// �R���t�B�M�����[�V�����P�̐ݒ�
#pragma config FOSC     = INTOSC   // �����ۯ��g�p����(INTOSC)
#pragma config WDTE     = OFF      // �����ޯ����ϰ����(OFF)
#pragma config PWRTE    = ON       // �d��ON����64ms�����۸��т��J�n����(ON)
#pragma config MCLRE    = OFF      // �O��ؾ�ĐM���͎g�p�������޼��ٓ���(RA3)��݂Ƃ���(OFF)
#pragma config CP       = OFF      // ��۸�����ذ��ی삵�Ȃ�(OFF)
#pragma config CPD      = OFF      // �ް���ذ��ی삵�Ȃ�(OFF)
#pragma config BOREN    = ON       // �d���d���~���펞�Ď��@�\ON(ON)
#pragma config CLKOUTEN = OFF      // CLKOUT��݂�RA4��݂Ŏg�p����(OFF)
#pragma config IESO     = OFF      // �O���E�����ۯ��̐ؑւ��ł̋N���͂Ȃ�(OFF)
#pragma config FCMEN    = OFF      // �O���ۯ��Ď����Ȃ�(OFF)

// �R���t�B�M�����[�V�����Q�̐ݒ�
#pragma config WRT    = OFF        // Flash��ذ��ی삵�Ȃ�(OFF)
#pragma config PLLEN  = OFF        // ����N���b�N��32MHz�ł͓��삳���Ȃ�(OFF)
#pragma config STVREN = ON         // �X�^�b�N���I�[�o�t���[��A���_�[�t���[�����烊�Z�b�g������(ON)
#pragma config BORV   = HI         // �d���d���~���펞�Ď��d��(2.5V)�ݒ�(HI)
#pragma config LVP    = OFF        // ��d���v���O���~���O�@�\�g�p���Ȃ�(OFF)



/*******************************************************************************
*  ���C���̏���                                                                *
*******************************************************************************/
void main()
{
     int  i ;
     char s[17] ;

     OSCCON  = 0b01110010 ;   // �����N���b�N��8MHz�Ƃ���
     ANSELA  = 0b00000000 ;   // �A�i���O�͎g�p���Ȃ��i���ׂăf�W�^��I/O�Ɋ����Ă�j
     TRISA   = 0b00000000 ;   // �s����RA1(SCL)/RA2(SDA)�̂ݓ���(RA3�͓��͐�p)
     PORTA   = 0b00000000 ;   // �o�̓s���̏�����(�S��LOW�ɂ���)

     // LCD���j�^�[���g�p����ׂ̏���������
     MonitorInit() ;

     i = 0 ;
     while(1) {
          // �Q�s�ڂ�����
          MonitorPutc(0x11) ;
          MonitorPuts("                ") ;
          // �J�[�\�����Q�s�ڂ̐擪�Ɉړ�����
          MonitorPutc(0x11) ;
          // �����l�𕶎���ɕϊ����Ăk�b�c�\��
          itoa(s,i,10) ;
          MonitorPuts(s) ;
          i++ ;
          __delay_ms(1000) ;  // �P�b��ɌJ��Ԃ�
     }
}
