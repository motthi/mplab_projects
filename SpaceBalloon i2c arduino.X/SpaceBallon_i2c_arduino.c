// PIC16F1827 Configuration Bit Settings

//http://www.geocities.jp/zattouka/GarageHouse/micon/MPLAB/16F1827/LEDblink/LEDblink.htm
//http://www.geocities.jp/zattouka/GarageHouse/micon/I2C/I2C_1.htm

/*
 * RA0 LED
 * RA1 LED
 * RA2 LED
 * RA3 Analog
 * RA4
 * RA5 //only Input
 * RA6
 * RA7
 * 
 * RB0
 * RB1 SDA
 * RB2 Switch A AN10
 * RB3 Switch B AN9
 * RB4 SCL
 * RB5 LED
 * RB6 LED
 * RB7 LED
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 8000000
#define SND_DATA_LEN 8
#define RCV_DATA_LEN 8

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

unsigned char rcv_data[RCV_DATA_LEN] ;
unsigned char snd_data[SND_DATA_LEN] ;
unsigned int  rcv_flg ;
unsigned char *Sdtp ;
unsigned char *Rdtp ;

void InitI2C_Slave(unsigned int address);
int I2C_ReceiveCheck();
void interrupt InterI2C(void);
unsigned int adconv(int i);

int main(int argc, char** argv) {    
    OSCCON = 0b01110010 ;
    ANSELA = 0b00001000 ;
    ANSELB = 0b01100000 ;
    TRISA  = 0b00001000 ;
    TRISB  = 0b00010010 ;
    PORTA  = 0b00000000 ;
    PORTB  = 0b00000000 ;
    ADCON0 = 0b00000001 ;
    ADCON1 = 0b10010000 ;
    
    InitI2C_Slave(7) ;
    __delay_ms(2000) ;
    
    int porta = 0;
    int portb = 0;
    int ans;
    float analog;
    
    while(1){
        ans = I2C_ReceiveCheck();
        if(ans != 0){
            if(rcv_data[0] == 1){
                porta = (int)rcv_data[1];
            }else if(rcv_data[0] == 2){
                portb = (int)rcv_data[1] << 5;
           }else if(rcv_data[0] == 3){
               analog = (float)adconv(3)/4.0;
               snd_data[0] = (int)(analog);
           }else if(rcv_data[0] == 4){
               snd_data[0] = (int)(RB2 + 10 * RB3);
           }
        }
        PORTA = porta;
        PORTB = portb;
        __delay_ms(1);
    }
}

void InitI2C_Slave(unsigned int address){
     SSP1STAT= 0b10000000 ;
     SSP1CON1= 0b00100110 ;
     SSP1CON2bits.SEN  = 1;
//   SSP1CON2bits.GCEN = 1;
     SSP1ADD = address<<1 ;
     SSP1MSK = 0b11111110 ;
     SSP1IE = 1 ;
     BCL1IE = 1 ;
     PEIE   = 1 ;
     GIE    = 1 ; 
     SSP1IF = 0 ;
     BCL1IF = 0 ;
     rcv_flg = 0;
}

void interrupt InterI2C( void ){
     char x ;

     if (SSP1IF == 1) {
          if (SSP1STATbits.R_nW == 0) {
               if (SSP1STATbits.D_nA == 0) {
                    Rdtp = (char *)rcv_data ;
                    x = SSP1BUF ;
                    rcv_flg = 0 ;
               } else {
                    *Rdtp = SSP1BUF ;
                    Rdtp++ ;
                    rcv_flg++ ;
               }
               SSP1IF = 0 ;
               SSP1CON1bits.CKP = 1 ;
          } else {
               if (SSP1STATbits.BF == 1) {
                    Sdtp = (char *)snd_data ;
                    x = SSP1BUF ;
                    while((SSP1CON1bits.CKP)|(SSP1STATbits.BF)) ;
                    SSP1BUF = *Sdtp ;
                    Sdtp++ ;
                    SSP1IF = 0 ;
                    SSP1CON1bits.CKP = 1 ;
               } else {
                    if (SSP1CON2bits.ACKSTAT==0) {
                         while((SSP1CON1bits.CKP)|(SSP1STATbits.BF)) ;
                         SSP1BUF = *Sdtp ;
                         Sdtp++ ;
                         SSP1IF = 0 ;
                         SSP1CON1bits.CKP = 1 ;
                    } else {
                         SSP1IF = 0 ;
                    }
               }
          }
     }
     if (BCL1IF == 1) {
          BCL1IF = 0 ;
     }
}

int I2C_ReceiveCheck(){
     int ans ;
     ans = 0 ;
     if (rcv_flg != 0) {
          if ((SSP1STATbits.S==0)&&(SSP1STATbits.P==1)) {
               ans = rcv_flg ;
               rcv_flg = 0 ;
          }
     }
     return(ans) ;
}

unsigned int adconv(int i){
    unsigned int temp;
    ADCON0 = 0b00000001 + (i << 2);
    __delay_us(20);
    
    GO_nDONE = 1;
    while(GO_nDONE);
    temp = ADRESH;
    temp = (temp << 8) | ADRESL;
    return temp;
}