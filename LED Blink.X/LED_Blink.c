#include <xc.h>

#define _XTAL_FREQ  8000000     // delay?(????8MHz????)

// ???????????????
#pragma config FOSC = INTOSC    // ???????????(INTOSC)
#pragma config WDTE = OFF       // ???????????????(OFF)
#pragma config PWRTE = ON       // ??ON??64ms??????????????(ON)
#pragma config MCLRE = OFF      // ??????????????????????(RA5)??????(OFF)
#pragma config CP = OFF         // ?????????????????(OFF)
#pragma config CPD = OFF        // ??????????????(OFF)
#pragma config BOREN = ON       // ????????????ON(ON)
#pragma config CLKOUTEN = OFF   // CLKOUT????RA6????????(OFF)
#pragma config IESO = OFF       // ????????????????????(OFF)
#pragma config FCMEN = OFF      // ???????????(FCMEN_OFF)

// ???????????????
#pragma config WRT = OFF        // Flash??????????(OFF)
#pragma config PLLEN = OFF      // ???????32MHz????????(OFF)
#pragma config STVREN = ON      // ?????????????????????????????(ON)
#pragma config BORV = HI        // ????????????(2.5V)??(HI)
#pragma config LVP = OFF        // ?????????????????(OFF)

// ??????(num x 10ms)?????????????
void Wait(unsigned int num)
{
     int i ;

     // num?????????????
     for (i=0 ; i<num ; i++) {
          __delay_ms(10) ;     // 10ms??????????
     }
}
// ????????
void main()
{
     OSCCON = 0b01110010 ;     // ??????????????
     ANSELA = 0b00000000 ;     // AN0-AN4????????????I/O???
     ANSELB = 0b00000000 ;     // AN5-AN11????????????I/O???
     TRISA  = 0b00000000 ;     // ??(RA)??????????(RA5????????)
     TRISB  = 0b00000000 ;     // ??(RB)??????????
     PORTA  = 0b00000000 ;     // RA????????(??LOW???)
     PORTB  = 0b00000000 ;     // RB????????(??LOW???)

     // ?1s??LED????????

	while(1) {
          RA1 = 1 ;            // 10???(RB4)?HIGH(5V)?????(LED ON)
          Wait(100) ;          // 1?????
          RA1 = 0 ;            // 10???(RB4)?LOW(0V)?????(LED OFF)
          Wait(100) ;
    }
}
