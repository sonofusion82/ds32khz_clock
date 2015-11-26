/* 
 * File:   button_update.h
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on November 15, 2015, 12:29 AM
 */

#ifndef BUTTON_UPDATE_H
#define	BUTTON_UPDATE_H

#ifdef	__cplusplus
extern "C" {
#endif

enum button_ids
{
    BUTTON_NONE,
    BUTTON_1,
    BUTTON_2
};

#define BUTTON_DEASSERT_COUNT    50
#define BUTTON_SHORT_PRESS_COUNT 200
#define BUTTON_LONG_PRESS_COUNT  3000

unsigned char button_update(unsigned char button1);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_UPDATE_H */

