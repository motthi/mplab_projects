/*******************************************************************************
*  slave.c - �h�Q�b�ʐM�̃X���[�u�ł̃e�X�g                                    *
*                                                                              *
*  �}�X�^�[����P�o�C�g��M���A���̃f�[�^�Ɂ{�P�V�����ă}�X�^�[�ɑ��M����      *
*  ��M�����f�[�^�͂P�o�C�g���ɂk�b�c���j�^�[�ɕ\������                        *
*  �R���p�C������ɂ�skI2Cslave.c��skMonitorLCD.c�̃��C�u�������K�v            *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2012-01-05  ���ޒ��H�[(���ނ���)  Create                            *
* ============================================================================ *
*  PIC 12F1822                                                                 *
*  HI-TECH C Compiler for PIC10/12/16 MCUs Version 9.80 in Lite mode           *
*******************************************************************************/
#include <pic.h>
#include <htc.h>                        // delay�p�ɕK�v
#include "skI2Cslave.h"                 // I2C�֐����C�u�����p

#define _XTAL_FREQ   8000000            // delay�p�ɕK�v(�N���b�N8MHz���w��)

// �R���t�B�M�����[�V�����P�̐ݒ�
// CLKOUT��݂�RA4��݂Ŏg�p����(CLKOUTEN_OFF)�F�����ۯ��g�p����(INTIO)
// �O���ۯ��Ď����Ȃ�(FCMEN_OFF)�F�O���E�����ۯ��̐ؑւ��ł̋N���͂Ȃ�(IESO_OFF)
// �d���d���~���펞�Ď��@�\ON(BOREN_ON)�F�����ޯ����ϰ����(WDTE_OFF)
// �d��ON����64ms�����۸��т��J�n����(PWRTEN_ON)
// �O��ؾ�ĐM���͎g�p�������޼��ٓ���(RA3)��݂Ƃ���(MCLRE_OFF)
// ��۸�����ذ��ی삵�Ȃ�(CP_OFF)�F�ް���ذ��ی삵�Ȃ�(CPD_OFF)
CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
// �R���t�B�M�����[�V�����Q�̐ݒ�
// ����N���b�N��32MHz�ł͓��삳���Ȃ�(PLLEN_OFF)
// �X�^�b�N���I�[�o�t���[��A���_�[�t���[�����烊�Z�b�g������(STVREN_ON)
// ��d���v���O���~���O�@�\�g�p���Ȃ�(LVP_OFF)
// Flash��ذ��ی삵�Ȃ�(WRT_OFF)�F�d���d���~���펞�Ď��d��(2.5V)�ݒ�(BORV_25)
CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_25 & LVP_OFF);

/*******************************************************************************
*  ���C���̏���                                                                *
*******************************************************************************/
void main()
{
     int ans ;

     OSCCON  = 0b01110010 ;   // �����N���b�N��8�l�g���Ƃ���
     ANSELA  = 0b00000000 ;   // �A�i���O�g�p���Ȃ�(���ׂăf�W�^��I/O�Ɋ����Ă�)
     TRISA   = 0b00001110 ;   // �s����RA1(SCL)/RA2(SDA)�̂ݓ���(RA3�͓��͐�p)
     PORTA   = 0b00000000 ;   // �o�̓s���̏�����(�S��LOW�ɂ���)

     InitI2C_Slave(8) ;       // �X���[�u���[�h�ł̏������A�}�C�A�h���X��8�Ƃ���

     __delay_ms(2000) ;


     while(1) {
          ans = I2C_ReceiveCheck() ;              // ��M��Ԃ̃`�F�b�N
          if (ans != 0) {
                snd_data[0] = rcv_data[0]+0x11 ;   // ���M�f�[�^���Z�b�g����
          }
     }
}
