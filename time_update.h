/* 
 * File:   time_update.h
 * Author: YewMing, Chen (fusion82@gmail.com)
 *
 * Created on November 15, 2015, 12:09 AM
 */

#ifndef TIME_UPDATE_H
#define	TIME_UPDATE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
extern unsigned char hours;
extern unsigned char minutes;
extern unsigned char seconds;

void time_update(unsigned char *bcdTime);

void incrementMinute();
void incrementHour();

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_UPDATE_H */

