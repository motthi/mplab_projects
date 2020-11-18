
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


unsigned int adconv(){
     unsigned int temp;

     GO_nDONE = 1 ;
     while(GO_nDONE) ;
     temp = ADRESH ;
     temp = ( temp << 8 ) | ADRESL ;

     return temp ;
}


void main(){
     unsigned int num ;
     unsigned int i = 0;

     OSCCON = 0b01110010 ;
     ANSELA = 0b00000000 ;
     ANSELB = 0b00000000 ;
     TRISA  = 0b00000000 ;
     TRISB  = 0b00000000 ;
     PORTA  = 0b00000000 ;
     PORTB  = 0b00000000 ;

     //ADCON1 = 0b10010000;
     //ADCON0 = 0b00100101;
     //__delay_us(5) ;
     
     CCP1CON = 0b00001100;
     CCP2CON = 0b00001100;
     CCP3CON = 0b00001100;
     CCP4CON = 0b00001100;
     
     CCP1SEL = 0;
     CCP2SEL = 0 ;
     PSTR1CON= 0b00000001;
     PSTR2CON= 0b00000001;
     CCPR1L = 0;
     CCPR1H = 0;
     
     CCPTMRS = 0b01010101;
     T4CON   = 0b00000010;
     CCPR2L  = 0 ;
     CCPR2H  = 0 ;
     TMR4    = 0 ;
     PR4     = 124 ;
     TMR4ON  = 1 ;

     
     while(1){
         if(i <= 255){
             CCPR1L = i;
             CCPR2L = i;
             CCPR3L = 255 - i;
             CCPR4L = 255 - i;
             i++;
         }else{
             i = 0;
         }
         __delay_ms(10);
     }
}