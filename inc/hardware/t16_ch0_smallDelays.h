#ifndef T16_CH0_H__
#define T16_CH0_H__
// timer 16 bits, channel 0. Cf chapitre 11 de la doc du s15

#include <init.h>

extern void (*actionAFaireTimer0)(void);

void waitShortTimes(unsigned short count); // , void (* actionAFaire)(void));
void waitAndDoShortTimes(unsigned short count, void (* actionAFaire)(void));
void presetT16Ch0CountShortTimes( unsigned short count );
extern void initT16Ch0(void);
extern void startT16Ch0(void);
extern void stopT16Ch0(void);
extern void presetT16Ch0Count( unsigned short count );
extern void waitAndDo(unsigned short count  , void (* actionAFaire)(void));
extern unsigned short getT16Ch0Count( void );
extern void intT16Ch0(void)	__attribute__ ((interrupt_handler));
extern void setT16Ch0IntCount( unsigned int count );
extern unsigned int getT16Ch0IntCount( void );

#endif	// T16_CH0_H__
