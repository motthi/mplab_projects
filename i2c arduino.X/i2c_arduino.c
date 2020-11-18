// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//http://www.geocities.jp/zattouka/GarageHouse/micon/MPLAB/16F1827/LEDblink/LEDblink.htm
//http://www.geocities.jp/zattouka/GarageHouse/micon/I2C/I2C_1.htm

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 8000000
#define SND_DATA_LEN 8
#define RCV_DATA_LEN 8

#pragma config FOSC = ECH
#pragma config WDTE = ON
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config CLKOUTEN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON

// CONFIG2
#pragma config WRT = OFF
#pragma config PLLEN = ON
#pragma config STVREN = ON
#pragma config BORV = LO
#pragma config LVP = ON


unsigned char rcv_data[RCV_DATA_LEN] ;
unsigned char snd_data[SND_DATA_LEN] ;
float line_data[8];
unsigned int  rcv_flg ;
unsigned char *Sdtp ;
unsigned char *Rdtp ;
int line = 0;

unsigned int adconv(int i);
void InitI2C_Slave(unsigned int address);
int I2C_ReceiveCheck();
void interrupt InterI2C(void);

int main(int argc, char** argv) {
    unsigned int i;
    
    OSCCON = 0b01110010 ;
    ANSELA = 0b00001111 ;
    ANSELB = 0b11000000 ;
    TRISA  = 0b00011111 ;
    TRISB  = 0b11010010 ;
    PORTA  = 0b00000000 ;
    PORTB  = 0b00000000 ;
    ADCON0 = 0b00000001 ;
    ADCON1 = 0b10010000 ;
    
    InitI2C_Slave(8) ;
    //__delay_ms(2000) ;
    
    
    while(1){
        RB5 = 0;
        for(i = 0 ; i <= 6 ; i++){
            line_data[i] = ((float)adconv(i))/4.7;
            snd_data[i+1] = (int)line_data[i];
            line += (int)line_data[i]/6;
        }
        snd_data[0] = line;
        line = 0;
    }
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