#ifndef WDT_H__
#define WDT_H__

#include <init.h>

// Watchdog Timer NMI interrupt flag.
#define WDT_INT_NMI_OFF				( 0 )			///< Watchdog Timer NMI interrupt.
#define WDT_INT_NMI_ON				( 1 )			///< No Watchdog Timer NMI interrupt.


/* --- external declaration --- */
extern void initWdt( void );
extern void startWdt( void );
extern void stopWdt( void );
extern void resetWdt( void );
//extern void intWdtNmi( void )	__attribute__ ((interrupt_handler));
//extern int isWdtIntNmi( void );


#endif	// WDT_H__
