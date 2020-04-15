#ifndef T16B_CH0_H__
#define T16B_CH0_H__


#include <init.h>


/* --- definition --- */

/// Compare interrupt counter data max.
#define T16B_CH0_INT_CAP_DATA_MAX	( 20 )


/* --- external declaration --- */
extern void initT16bCh0( void );
extern void startT16bCh0( void );
extern void stopT16bCh0( void );
void presetT16bCh0Count( unsigned short count );
void wait_t16b_ch0/*waitAndDo_t16b_ch0*/(unsigned short count);
extern unsigned short getT16bCh0TimerCount( void );
extern void intT16bCh0( void )	__attribute__ ((interrupt_handler));


#endif	// T16B_CH0_H__
