//http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q14170641009
//http://meideru.com/archives/1649

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 32000000

#pragma config FOSC = INTOSC
#pragma config CLKOUTEN = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config MCLRE = ON
#pragma config WDTE = OFF
#pragma config CPD = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config PLLEN = OFF
#pragma config STVREN = ON
#pragma config WRT = OFF
#pragma config BORV = HI
#pragma config LVP = OFF

unsigned char flag = 0;
unsigned char data1;
unsigned char data2;
unsigned char data_flag = 0;
unsigned char buf=0;

volatile char data[3];

void interrupt intr(void) {
    static int cnt = 0;
    if (SSP1IF == 1) {
        SSP1IF = 0;	//
        if (SSP1STATbits.BF == 1 &&	SSP1STATbits.R_nW == 0){
            if (SSP1STATbits.D_nA){
                data[cnt] = SSP1BUF;
                cnt++;
                if (cnt == 3){
                    cnt = 0;
                    data_flag = 1;
                }
            }else{
                buf = SSP1BUF;
                cnt = 0;
            }
        SSP1CON1bits.CKP = 1;
        }
    }
}

void InitI2C_Slave(int address){
    //i2c
    SSP1ADD = address << 1;
    SSP1CON1 = 0b00110110;
    SSP1CON2 = 0b00000001;
    SSP1CON3 = 0b00000000;
    SSP1STAT = 0b00000000;

    //interrupt
    PIE1 = 0b00001000;
    INTCON = 0b11000000;
}

int main(int argc, char** argv) {
    OSCCON = 0b01110010;
    ANSELA = 0;
    ANSELB = 0;
    TRISA = 0b00000000;
    TRISB = 0b00000000;
    PORTA = 0b00000000;
    PORTB = 0b00000000;

    InitI2C_Slave(8);

    //pwm
    CCPTMRS = 0b00000000;
    CCP3CON = 0b00001100;
    CCP4CON = 0b00001100;
    
    PR2 = 255;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;

    while (1){
        PORTA = 0b00000000;
        if(data[2] == 0){
            PORTA = 0b00000010;
            CCPR3L = data[1];
            CCPR4L = 0;
        }else if(data[2] == 1){
            PORTA = 0b00000010;
            CCPR3L = data[1];
            CCPR4L = 0;            
        }else if(data[2] == 2 || data[2] == 3){
            PORTA = 0b00000001;
            CCPR3L = 0;
            CCPR4L = data[1];
        }else{
            CCPR3L = 0;     
            CCPR4L = 0;
        }
         
        __delay_ms(10);
    }
    return (EXIT_SUCCESS);
}