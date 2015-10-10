/* 
 * File:   main.c
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on September 20, 2015, 10:32 AM
 */
#define _XTAL_FREQ 1316043

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#ifdef _PIC16F876A_H_
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#endif

#ifdef _PIC16F72_H_
// CONFIG
#pragma config FOSC = RC        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#endif

#include <stdio.h>
#include <stdlib.h>

bit toggle = 0;
unsigned char bitmask = 0x1;

#define TMR1H_RELOAD 0x80

void interrupt interupt_service_routine(void)
{
    // only process timer-triggered interrupts
    //if(PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        TMR1H = TMR1H_RELOAD;
        PIR1bits.TMR1IF = 0;
        toggle = toggle ? 0 : 1;
        
        bitmask <<= 1;
        if (!bitmask)
            bitmask = 1;
    }
}

void init()
{
    PORTB = 0;
    TRISB = 0;
    
    ADCON1 = 0x07; // PCFG3:PCFG0 = 0111 => All Digital Ports
#ifdef _PIC16F876A_H_
    CMCON = 0x07;
#endif
    PORTA = 0;
    TRISA = 0;

    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC3 = 0;
    
    // TIMER 1 setting
    // pre-scale 1:1
    // oscillator disable
    // not sync to internal clock
    // external input
    // timer 1 on
    T1CON = 0x7;
    TMR1L = 0x00;
    TMR1H = TMR1H_RELOAD;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    ei();
}

/* Main program loop
 * 
 */
int main(int argc, char** argv)
{
    init();
    
    static bit commonCathodeToggle = 0;
    
    
    while (1)
    {
        //PORTA = 0x3E;
        //PORTCbits.RC3 = 1;
        //PORTB = 0x4;
        //PORTB = commonCathodeToggle ? 0xAA : 0x55;
        //PORTA = commonCathodeToggle ? 0xAA : 0x55;
        //PORTBbits.RB1 = toggle ? 1 : 0;
        //PORTBbits.RB0 = toggle ? 0 : 1;
        //PORTBbits.RB1 = toggle ? 1 : 0;
        PORTB = bitmask;
        
        
        
        if (commonCathodeToggle)
        {
            PORTCbits.RC4 = 0;
            PORTCbits.RC5 = 1;
            commonCathodeToggle = 0;
        }
        else
        {
            PORTCbits.RC5 = 0;
            PORTCbits.RC4 = 1;
            commonCathodeToggle = 1;
        }
    }
    return (EXIT_SUCCESS);
}

