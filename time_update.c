/* 
 * File:   time_update.c
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on November 15, 2015, 12:07 AM
 */

extern volatile unsigned char tmr1_ticked;
extern unsigned char display_ticked;
extern unsigned char low_power_enable;
unsigned char hours = 0;
unsigned char minutes = 0;
unsigned long timestamp = 0;
unsigned int temp = 0;

/* unsigned char to 2 byte BCD
 * 
 * NOTE: it assumes n is less than 100
 */
void toBcd(unsigned char n, unsigned char* bcd)
{
    unsigned char x = 0;
    while (n >= 10)
    {
        n -= 10;
        x++;
    }
    bcd[0] = x;
    bcd[1] = n;
}

    
/* Update time
 */
void time_update(unsigned char *bcdTime)
{
    static unsigned char state = 0;
    unsigned long temp32;
    
    /* Clock calculation block
     * Uses a state machine to break the operation into smaller chunks to
     * fix display flickering when calculation took too long and it impacts
     * the display refresh periods
     */
    if (display_ticked)
    {
        display_ticked = 0;

        switch (state)
        {
            default:
            case 0:
                if (tmr1_ticked)
                {
                    tmr1_ticked = 0;

                    timestamp++;
                    // 24 hour wrap around
                    // 60 * 60 * 24
                    if (timestamp >= 86400L)
                    {
                        timestamp = 0;
                    }
                    
                    state = 1;
                }
                break;
                
            case 1:
                temp32 = timestamp;
                hours = 0;
                while (temp32 >= 3600)
                {
                    hours++;
                    temp32 -= 3600;
                }
                temp = temp32;
                state = 2;
                break;

            case 2:
                minutes = 0;
                while (temp >= 60)
                {
                    minutes++;
                    temp -= 60;
                }
                state = 3;
                break;

            case 3:
                /* low power mode between 12am to 5am */
                /*if (hours < 5)
                {
                    low_power_enable = 1;
                }*/
                /* display in 12 hour format */
                if (hours > 12)
                {
                    hours = hours - 12;
                }
                toBcd(hours, &bcdTime[0]);
                state = 4;
                break;
                
            case 4:
                toBcd(minutes, &bcdTime[2]);
                state = 0;
                break;
        }
    }
}


