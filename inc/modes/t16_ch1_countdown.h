#ifndef T16_CH1_H__
#define T16_CH1_H__

#include <init.h>
#include "class/time.h"

extern ShortTime countDownMax;
extern ShortTime countDownNow;
extern unsigned char suivantCountDown[4];
extern long long sec_temp_countDown ;

void initConstantesCountDown();
void prepareDisplayCountDown();
void actionModeCountdown(unsigned char typeEvenement);
unsigned char estFiniCountDown();
extern void initT16Ch1(void);
extern void startT16Ch1(void);
extern void stopT16Ch1(void);
extern void presetT16Ch1Count( );
//extern void waitAndDo1(unsigned short count  , void (* actionAFaire)());
extern unsigned short getT16Ch1Count( void );
extern void intT16Ch1(void)	__attribute__ ((interrupt_handler));
extern void setT16Ch1IntCount( unsigned int count );
extern unsigned int getT16Ch1IntCount( void );


#endif	// T16_CH1_H__
