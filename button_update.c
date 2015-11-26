/* 
 * File:   button_update.c
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on November 15, 2015, 12:28 AM
 */
#include "button_update.h"

unsigned short button_1_loop = 0;
unsigned char button_1_state = 0;
/*
 * 
 */
unsigned char button_update(unsigned char button1)
{
    unsigned char retval = BUTTON_NONE;

    if (button_1_loop < 0xFFFF)
    {
        button_1_loop++;
    }
    
    //printf("%d %d %d\n", button_1_state, button_1_loop, button1);

    switch (button_1_state)
    {
        case 0:
            if (button1 == 1)
            {
                button_1_state = 1;
                button_1_loop = 1;
            }
            break;

        case 1:
            if (button1 == 1)
            {
                if (button_1_loop == BUTTON_SHORT_PRESS_COUNT)
                {
                    button_1_state = 2;
                    button_1_loop = 0;
                    retval = BUTTON_1;
                }
            }
            else
            {
                button_1_state = 0;
            }
            break;

        case 2:
            if (button1 == 0)
            {
                button_1_state = 3;
                button_1_loop = 1;
            }
            else if (button_1_loop == BUTTON_LONG_PRESS_COUNT)
            {
                button_1_loop = 0;
                retval = BUTTON_2;
            }
            break;

        case 3:
            if (button1 == 0)
            {
                if (button_1_loop == BUTTON_DEASSERT_COUNT)
                {
                    button_1_state = 0;
                    button_1_loop = 1;
                }
            }
            else
            {
                button_1_state = 2;
            }
            break;
    }

    return retval;
}
