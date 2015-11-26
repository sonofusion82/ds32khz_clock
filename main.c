/* 
 * File:   main.c
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on September 20, 2015, 10:32 AM
 */

#ifdef __SDCC
#define NO_BIT_DEFINES
#include <pic16f72.h>
#else
//#define _XTAL_FREQ 20000000
#include <xc.h>
#endif

#include "current_timestamp.h"
#include "time_update.h"
#include "button_update.h"


#ifdef __SDCC

#ifdef __PIC16F876A_H__
static __code unsigned short __at (_CONFIG) config_word = \
    _FOSC_EXTRC & 
    _WDTE_ON & 
    _PWRTE_OFF & 
    _CP_OFF & 
    _BOREN_OFF & 
    _WRT_OFF & 
    _DEBUG_OFF & 
    _LVP_OFF;
#else
static __code unsigned short __at (_CONFIG) config_word = \
    _FOSC_RC & 
    _WDTE_ON & 
    _PWRTE_OFF & 
    _CP_OFF & 
    _BOREN_OFF;
#endif

#else // XC8 config

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#ifdef _PIC16F876A_H_
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator) with 10Kohm and 22uF
//#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = ON       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming))
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
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR disabled)
#endif

#endif /* __SDCC */

/* CONSTANT TABLES */

/* BCD to IO mapping tables */

const unsigned char digit1[10][2] = {
    { 0b00011100, 0b00101100 },  /* 0 */
    { 0b00011000, 0b00000000 },  /* 1 */
    { 0b00010100, 0b00111000 },  /* 2 */
    { 0b00011100, 0b00011000 },  /* 3 */
    { 0b00011000, 0b00010100 },  /* 4 */
    { 0b00001100, 0b00011100 },  /* 5 */
    { 0b00001100, 0b00111100 },  /* 6 */
    { 0b00011100, 0b00000000 },  /* 7 */
    { 0b00011100, 0b00111100 },  /* 8 */
    { 0b00011100, 0b00011100 }   /* 9 */
};

/* digit 2 starts from bit 5 */
const unsigned char digit2[10][2] = {
    { 0b1011, 0b1110 }, /* 0 */
    { 0b0000, 0b0110 }, /* 1 */
    { 0b0111, 0b1100 }, /* 2 */
    { 0b0110, 0b1110 }, /* 3 */
    { 0b1100, 0b0110 }, /* 4 */
    { 0b1110, 0b1010 }, /* 5 */
    { 0b1111, 0b1010 }, /* 6 */
    { 0b0000, 0b1110 }, /* 7 */
    { 0b1111, 0b1110 }, /* 8 */
    { 0b1110, 0b1110 }  /* 9 */
};

const unsigned char digit3[10][2] = {
    { 0b01110, 0b10110 }, /* 0 */
    { 0b01100, 0b00000 }, /* 1 */
    { 0b01010, 0b11100 }, /* 2 */
    { 0b01110, 0b01100 }, /* 3 */
    { 0b01100, 0b01010 }, /* 4 */
    { 0b00110, 0b01110 }, /* 5 */
    { 0b00110, 0b11110 }, /* 6 */
    { 0b01110, 0b00000 }, /* 7 */
    { 0b01110, 0b11110 }, /* 8 */
    { 0b01110, 0b01110 }  /* 9 */
};


const unsigned char digit4[10][2] = {
    { 0b000000, 0b000000 }, /* 0 */
    { 0b110000, 0b000000 }, /* 1 */
    { 0b000000, 0b000000 }, /* 2 */
    { 0b000000, 0b000000 }, /* 3 */
    { 0b000000, 0b000000 }, /* 4 */
    { 0b000000, 0b000000 }, /* 5 */
    { 0b000000, 0b000000 }, /* 6 */
    { 0b000000, 0b000000 }, /* 7 */
    { 0b000000, 0b000000 }, /* 8 */
    { 0b000000, 0b000000 }  /* 9 */
};
 
/* GLOBAL VARIABLES */
volatile unsigned char tmr1_ticked = 0;
unsigned char display[4] = { 0 };
unsigned char display_ticked = 0;
unsigned char low_power_enable = 0;

#define TMR1H_RELOAD 0x80

#ifdef SDCC

// clear watchdog macro
#define CLRWDT()  __asm__( "clrwdt" );
// enable interrupt
#define ei()  (INTCONbits.GIE = 1)

static void interupt_service_routine (void) __interrupt 0
#else
void interrupt interupt_service_routine(void)
#endif
{
    /* only process timer-triggered interrupts */
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        TMR1H = TMR1H_RELOAD;
        PIR1bits.TMR1IF = 0;
        tmr1_ticked = 1;
    }
}

static void init()
{
    /* Initialize GPIOs */
    PORTB = 0;
    TRISB = 0;
    
    ADCON1 = 0x07; /* PCFG3:PCFG0 = 0111 => All Digital Ports */
#if defined(_PIC16F876A_H_) || defined(__PIC16F876A_H__)
    CMCON = 0x07;
#endif
    PORTA = 0;
    TRISA = 0;

    PORTC = 0;
    TRISC = 0b11000111;
    
    /* TIMER 1 setting
     * pre-scale 1:1
     * oscillator disable for DS32KHZ input
     * not sync to internal clock
     * external input
     * timer 1 on
     */
    T1CON = 0b000111;
    TMR1L = 0x00;
    TMR1H = TMR1H_RELOAD;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
 
    ei();
}

#define GET_LOOP_TICK (TMR1L & 0xC0)


static void updateDisplayIOs(unsigned char toggle)
{
    PORTB  = digit1[display[3]][toggle];
    PORTB |= ((digit2[display[2]][toggle] & 0b111) << 5);
    
    PORTCbits.RC3 = (digit2[display[2]][toggle] & 0b1000) ? 1 : 0;
    
    PORTA  = digit3[display[1]][toggle];
    PORTA |= digit4[display[0]][toggle];
    
    /* Blink the center colon LEDs */
    PORTBbits.RB1 = (TMR1H & 0b01000000) ? 0 : 1;
}

static void display_update()
{
    static unsigned char loopTicks = 0;
    static unsigned char loopCount = 0;
    
    /* Display block */
    if (loopTicks != GET_LOOP_TICK)
    {
        loopCount++;
        loopTicks = GET_LOOP_TICK;

        if ((loopCount & 3) == 0)
        {
            PORTCbits.RC4 = 0;

            updateDisplayIOs(1);

            PORTCbits.RC5 = 1;
            
            display_ticked = 1;
        }
        else if ((loopCount & 3) == 2)
        {
            PORTCbits.RC5 = 0;

            updateDisplayIOs(0);

            PORTCbits.RC4 = 1;
            
            display_ticked = 1;
        }
        else if (low_power_enable)
        {
            PORTCbits.RC4 = 0;
            PORTCbits.RC5 = 0;
            PORTB = 0;
            PORTA = 0;
            PORTCbits.RC3 = 0;
        }
        
    }
}

/* Main program loop
 * 
 */
void main()
{
    init();
    
    timestamp = BUILD_TIME_SINCE_MIDNIGHT;
    
    while (1)
    {
        display_update();
        
        switch (button_update(!PORTCbits.RC2))
        {
            // BUTTON_1 adds 1 minute
            case BUTTON_1:
                timestamp += 60;
                tmr1_ticked = 1; // force a time update
                break;

            // BUTTON_2 adds 1 hour
            case BUTTON_2:
                timestamp += 3600L;
                tmr1_ticked = 1; // force a time update
                break;
                
            case BUTTON_NONE:
            default:
                break;
        }
        
        time_update(display);
        
        CLRWDT();
    }
   
    return;
}

