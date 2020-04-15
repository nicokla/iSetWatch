#ifndef T16_CH2_H__
#define T16_CH2_H__
// timer 16 bits, channel 0. Cf chapitre 11 de la doc du s15

#include <init.h>

extern void (*actionAFaireTimer2)(void);

extern void initT16Ch2(void);
extern void startT16Ch2(void);
extern void stopT16Ch2(void);
extern void presetT16Ch2Count( unsigned short count );
extern void waitAndDo2(unsigned short count  , void * actionAFaire);
extern unsigned short getT16Ch2Count( void );
extern void intT16Ch2(void)	__attribute__ ((interrupt_handler));
extern void setT16Ch2IntCount( unsigned int count );
extern unsigned int getT16Ch2IntCount( void );

#endif	// T16_CH2_H__
