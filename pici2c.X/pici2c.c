//http://physicom.digick.jp/?p=5014
//the other http://diy.ease-labs.com/?page_id=1938
//          http://www.geocities.jp/zattouka/GarageHouse/micon/I2C/I2C_1.htm#TEST1


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ  32000000

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
unsigned char data;
unsigned char data_flag = 0;

static void interrupt intr(void) {
    if (SSP1IF == 1) {
        if (SSP1STAT & 0b00010000) {
            RA3 = 1;
        }
        if (SSP1STAT & 0b00001000) {
            RA2 = 1;
        }
        if (SSP1STAT & 0b00000100) {
            RA6 = 1;
        } else {
            RA7 = 1;
        }
        if (SSP1STAT & 0b00000001) {
            RA0 = 1;
        } else {
            RA0 = 0;
        }
        if ((SSP1STAT & 0b00000001) && ((SSP1STAT & 0b00000100) == 0)) {
            data = SSP1BUF;
            data_flag = 1;
        }
        SSP1CON1 = 0b11111110;
        SSP1IF = 0;
        flag = 1;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    OSCCON = 0b11110000;

    ANSELA = 0;
    ANSELB = 0;
    TRISA = 0b00000000;
    TRISB = 0b00010010;
    PORTA = 0b00000000;
    PORTB = 0b00000000;

    SSP1ADD = 1<<1;
    SSP1CON1 = 0b11111110;
    SSP1CON2 = 0b10000001;
    SSP1STAT = 0b00000000;

    PIE1     = 0b00001000;
    INTCON   = 0b11000000;
    
    while (1) {
        RA4 = 0;
        __delay_ms(100);
        RA4 = 1;
        __delay_ms(100);
        if (flag) {
            __delay_ms(1000);
            flag = 0;
        }
        if (data_flag) {
            if (data == 0x30) {
                PORTA = 0b00000001;
            } else if (data == 0x31) {
                PORTA = 0b00000010;
            } else if (data == 0x32) {
                PORTA = 0b00000100;
            } else if (data == 0x33) {
                PORTA = 0b00001000;
            } else {
                PORTA = 0b00001111;
            }
            data_flag = 0;
        }
    }
    return (EXIT_SUCCESS);
}
