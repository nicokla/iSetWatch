#ifndef T16B_CH1_H__
#define T16B_CH1_H__

#include <init.h>
#include "varAff.h"

extern VarAff compteurSecondes;
extern void (*actionAFaireTimerB1)(void);

extern void initCompteurSecondes();
extern void initT16bCh1( void );
extern void startT16bCh1( void );
extern void stopT16bCh1( void );
void presetT16bCh1Count( unsigned short count );
void wait_t16b_ch1/*waitAndDo_t16b_ch0*/(unsigned short count);
extern unsigned short getT16bCh1TimerCount( void );
extern void intT16bCh1( void )	__attribute__ ((interrupt_handler));
void waitAndDoShortTimesT16B1(unsigned short count, void (* actionAFaire)(void));
void stopSecondsInterrupts();
void startSecondsInterrupts(unsigned char duree, void (* actionAFaire)(void));
void afficheSecondesQuiPassent();
//void afficheEcranClignotementSpecial();

#endif	// T16B_CH1_H__
