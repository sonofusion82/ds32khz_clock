/* 
 * File:   button_update.c
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on November 15, 2015, 12:28 AM
 */
#include "button_update.h"

unsigned char button_1_loop = 0;
/*
 * 
 */
unsigned char button_update(unsigned char button1)
{
    unsigned char retval = BUTTON_NONE;

    if (button1 == 1)
    {
        button_1_loop++;
    }
    else if (button1 == 0)
    {
        if (button_1_loop >= BUTTON_SHORT_PRESS_COUNT)
        {
            retval = BUTTON_1;
        }
        button_1_loop = 0;
    }

    return retval;
}
