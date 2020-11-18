/*
 * File:   pwm_FullBrdige.c
 * Author: k1100
 *
 * Created on 2018/04/18, 11:34
 */
//http://www.picfun.com/f1/f11.html

#include <xc.h>

#define _XTAL_FREQ 8000000

#pragma config FOSC = INTOSC
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config CLKOUTEN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF

#pragma config WRT = OFF
#pragma config PLLEN = OFF
#pragma config STVREN = ON
#pragma config BORV = HI
#pragma config LVP = OFF


void main(void) {
    unsigned int i = 0;
    
     OSCCON = 0b01110010;
     ANSELA = 0b00000000;
     ANSELB = 0b00001000;
     TRISA  = 0b00000000;
     TRISB  = 0b00001000;
     PORTA  = 0b00000000;
     PORTB  = 0b00000000;
     
     CCPTMRS = 0b00000000;
     CCP1CON = 0b01001100;
     CCP2SEL = 0;
     PSTR2CON= 0b00000011;
     T4CON   = 0b00000010;
     TMR4    = 0;
     PR4     = 124;
     TMR4ON = 1;
     CCPR1L = 0;
     CCPR1H = 0;
     
     while(1){
         if(i <= 255){
             CCPR1L = i;
             i++;
         }else{
             i = 0;
         }
     }
     
    return;
}
