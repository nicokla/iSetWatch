#ifndef INTERRUPTTIME_H_
#define INTERRUPTTIME_H_

#include "init.h"

extern unsigned short int rtcaIntf;
extern unsigned char caSonne;
extern unsigned char alarmBips5Minutes;

extern unsigned char quarterCount;
extern unsigned char flags;

extern void intRtca(void)	__attribute__ ((interrupt_handler));
void actionSeconde(void);
void appuisLongs(void);
void demarreTemps() ;
void arreteTemps();
void actionMinute();

#endif
