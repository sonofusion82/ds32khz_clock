/* 
 * File:   main.c
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on September 20, 2015, 10:32 AM
 */
#define _XTAL_FREQ 20000000

#include <xc.h>

#include "current_timestamp.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#ifdef _PIC16F876A_H_
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator) with 10Kohm and 22uF
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
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
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT enabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const unsigned char digit1[10][2] = {
    { 0b00011100, 0b00101100 },  // 0
    { 0b00011000, 0b00000000 },  // 1
    { 0b00010100, 0b00111000 },  // 2
    { 0b00011100, 0b00011000 },  // 3
    { 0b00011000, 0b00010100 },  // 4
    { 0b00001100, 0b00011100 },  // 5
    { 0b00001100, 0b00111100 },  // 6
    { 0b00011100, 0b00000000 },  // 7
    { 0b00011100, 0b00111100 },  // 8
    { 0b00011100, 0b00011100 }   // 9
};

// digit 2 starts from bit 5
const unsigned char digit2[10][2] = {
    { 0b1011, 0b1110 }, // 0  
    { 0b0000, 0b0110 }, // 1
    { 0b0111, 0b1100 }, // 2
    { 0b0110, 0b1110 }, // 3
    { 0b1100, 0b0110 }, // 4
    { 0b1110, 0b1010 }, // 5
    { 0b1111, 0b1010 }, // 6
    { 0b0000, 0b1110 }, // 7
    { 0b1111, 0b1110 }, // 8
    { 0b1110, 0b1110 }  // 9
};

const unsigned char digit3[10][2] = {
    { 0b0111, 0b1011 }, // 0
    { 0b0110, 0b0000 }, // 1
    { 0b0101, 0b1110 }, // 2
    { 0b0111, 0b0110 }, // 3
    { 0b0110, 0b0101 }, // 4
    { 0b0011, 0b0111 }, // 5
    { 0b0011, 0b1111 }, // 6
    { 0b0111, 0b0000 }, // 7
    { 0b0111, 0b1111 }, // 8
    { 0b0111, 0b0111 }  // 9
};


const unsigned char digit4[10][2] = {
    { 0b00000, 0b00000 }, // 0
    { 0b11000, 0b00000 }, // 1
    { 0b00000, 0b00000 }, // 2
    { 0b00000, 0b00000 }, // 3
    { 0b00000, 0b00000 }, // 4
    { 0b00000, 0b00000 }, // 5
    { 0b00000, 0b00000 }, // 6
    { 0b00000, 0b00000 }, // 7
    { 0b00000, 0b00000 }, // 8
    { 0b00000, 0b00000 }  // 9
};

bit toggle = 0;
bit low_power_enable = 0;

#define TMR1H_RELOAD 0x80

void interrupt interupt_service_routine(void)
{
    // only process timer-triggered interrupts
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        TMR1H = TMR1H_RELOAD;
        PIR1bits.TMR1IF = 0;
        toggle = 1;
    }
}

void init()
{
    // Initialize GPIOs
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
    // oscillator disable for DS32KHZ input
    // not sync to internal clock
    // external input
    // timer 1 on
    T1CON = 0b000111;
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
    
    unsigned char loopCount = 0;
    unsigned long timestamp = BUILD_TIME_SINCE_MIDNIGHT;
    unsigned char display[4] = { 0 };
    unsigned char hours = 0;
    unsigned char minutes = 0;
    //unsigned char seconds = 0;
    
    low_power_enable = 0;
    
#define GET_LOOP_TICK (TMR1L & 0xC0)
    unsigned char loopTicks = GET_LOOP_TICK;
    
    while (1)
    {
        if (toggle)
        {
            toggle = 0;
            timestamp++;
            
            hours   = (timestamp / 3600);
            minutes = (timestamp - (hours * 3600)) / 60;
            
            // display in 12 hour format
            if (hours > 12)
                hours = hours - 12;
            
            display[0] = hours / 10;
            display[1] = hours % 10;
            display[2] = minutes / 10;
            display[3] = minutes % 10;
            
            //low_power_enable = (seconds >= 30) ? 1 : 0;
        }
        
        if (loopTicks != GET_LOOP_TICK)
        {
            loopCount++;
            loopTicks = GET_LOOP_TICK;
            
            if ((loopCount & 3) == 0)
            {
                PORTCbits.RC4 = 0;

                PORTB = digit1[display[3]][1];
                PORTB |= ((digit2[display[2]][1] & 0b111) << 5);
                PORTCbits.RC3 = (digit2[display[2]][1] & 0b1000) ? 1 : 0;
                PORTA  = digit3[display[1]][1] << 1;
                PORTA |= digit4[display[0]][1] << 1;
                
                PORTCbits.RC5 = 1;
            }
            else if ((loopCount & 3) == 2)
            {
                PORTCbits.RC5 = 0;

                PORTB  = digit1[display[3]][0];
                PORTB |= ((digit2[display[2]][0] & 0b111) << 5);
                PORTCbits.RC3 = (digit2[display[2]][0] & 0b1000) ? 1 : 0;
                PORTA  = digit3[display[1]][0] << 1;
                PORTA |= digit4[display[0]][0] << 1;
                
                PORTCbits.RC4 = 1;
            }
            else if (low_power_enable)
            {
                PORTB = 0;
                PORTA = 0;
                PORTCbits.RC3 = 0;
            }

            // Blink the center colon LEDs
            PORTBbits.RB1 = (TMR1H & 0b01000000) ? 0 : 1;
        }
    }
    return (EXIT_SUCCESS);
}

