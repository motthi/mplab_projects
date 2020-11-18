//http://meideru.com/archives/1649
//http://kuri6005.sakura.ne.jp/pic/index.php?LED%A4%CE%CC%C0%A4%EB%A4%B5%A4%F2%CA%D1%A4%A8%A4%EB%28PWM%29%2816F1827%20XC8%29 LED???????
//

#include <xc.h>

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

#define _XTAL_FREQ 8000000

int main(void) {
    unsigned int dutycycle; 
    OSCCON = 0b01110000; 
    ANSELA = 0b00000000; 
    TRISA = 0b00000000; 
    PORTA = 0b00000000; 

    CCPTMRS = 0b00000000;
    CCP3CON = 0b00001100;
    CCP4CON = 0b00001100;       
    T2CON = 0b00000001;
    PR2 = 165;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
    
    while(1) {
        CCPR3L = 0b01100110;
        CCPR4L = 0b10110011;
        __delay_ms(1000);
        CCPR3L = 0b00011001;
        CCPR4L = 0b00000000;
        __delay_ms(1000);
        CCPR3L = 0b11111110;
        CCPR4L = 0b01100110;
        __delay_ms(1000);
        CCPR3L = 0x00;
        CCPR4L = 0x00;
        __delay_ms(1000);
        CCPR3L = 0b00000000;
        CCPR4L = 0b01100110;
        __delay_ms(1000);
    
    }
}