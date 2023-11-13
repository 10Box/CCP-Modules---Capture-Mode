#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    //setting port B to be output
    TRISB = 0x00;
    PORTB = 0x00;
    //setting port D to be output
    TRISD = 0x00;
    PORTD = 0x00;
    //cleating tmr1 module
    TMR1 = 0x00;
    //external clock source : counter mode
    TMR1CS = 1;
    //setting the t1sync to 0 means synchoronize
    T1SYNC = 0;
    T1OSCEN = 1; //this means use RC1 but since proteus is glitching we will be using RC0 in proteus
    //prescaler
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1ON = 1;
    
    //setting RC2 as input to use CCP1 in capture mode 
    TRISC2 = 1;
    //clearing flag
    CCP1IF = 0;
    //Enabling Interrupts
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    // now setting CCP1 to capture mode on every rising edge 0101
    CCP1M0 = 1;
    CCP1M1 = 0;
    CCP1M2 = 1;
    CCP1M3 = 0;
    while(1){
        PORTD = TMR1;
    }
    return;
}

void __interrupt() ISR(){
    if(CCP1IF){
        PORTB = CCPR1;
        CCP1IF = 0;
    }
}