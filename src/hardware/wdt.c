#include <wdt.h>

// wdt ==  watch dog timer
// should be reset avant que soit passées 4 secondes, else reset du seiko.
// resetWdt() fait chaque seconde dans interruptTime.c
// --> cf chapitre 8.2.1 du doc seiko
// watch dog timer started dans la fonction commence(), cf fichier globalVar.c

// Interrupt flag.
//unsigned short wdtNmiIntInputFlag = WDT_INT_NMI_OFF;	///< Watchdog Timer NMI interrupt flag.

// initialise le watch dog
void initWdt( void )
{
	/// When OSC1 doesn't start, nothing is done.
	if ( CLGOSC_OSC1EN == 0 ) {
		return ;
	}

	/// Stop watchdog Timer.
	stopWdt();

	/// Disable write-protect.
	protectMisc( MSCPROT_PROTECT_OFF );

	/// Set clock source for watchdog Timer.
	WDTCLK_CLKSRC		= 1;	/// - Set clock source(OSC1).
	WDTCLK_CLKDIV		= 0;	/// - Set division ratio for clock source(1/128).
	WDTCLK_DBRUN		= 1;	/// - Clock supplied in DEBUG mode(0:Disable 1:Enable).
	CLGOSC_OSC1SLPC		= 0;	/// - Continue operation state before SLEEP.

	/// Set reset mode, not nmi (non maskable interrupt) mode
	// c-a-d que si le countdown du wdt arrive au bout, on reset le seiko
	WDTCTL_NMIXRST		= 0;

	/// Reset watchdog Timer count.
	WDTCTL_WDTCNTRST	= 1;


	/// Enable write-protect.
	protectMisc( MSCPROT_PROTECT_ON );

	/// Clear Watchdog Timer NMI interrupt flag.
//	wdtNmiIntInputFlag	= WDT_INT_NMI_OFF;
}

// lance le watch dog
void startWdt( void )
{
	/// Disable write-protect.
	protectMisc( MSCPROT_PROTECT_OFF );

	/// Start watchdog Timer.
	WDTCTL_WDTRUN = 1;

	/// Enable write-protect.
	protectMisc( MSCPROT_PROTECT_ON );
}

// arrete le watch dog
void stopWdt( void )
{
	/// Disable write-protect.
	protectMisc( MSCPROT_PROTECT_OFF );

	/// Stop watchdog Timer.
	WDTCTL_WDTRUN = 0xA;

	/// Enable write-protect.
	protectMisc( MSCPROT_PROTECT_ON );
}

// reset le watch dog
// appelée chaque seconde pour prouver au watchdog que le seiko est toujours vivant
// Si cette fonction n'est pas appelée pendant 4 secondes et que le watch dog est actif,
// cela provoque un reset hw
void resetWdt( void )
{
	/// Disable write-protect.
	protectMisc( MSCPROT_PROTECT_OFF );

	/// Reset watchdog Timer count.
	WDTCTL_WDTCNTRST	= 1;

	/// Enable write-protect.
	protectMisc( MSCPROT_PROTECT_ON );
}


//void intWdtNmi( void )
//{
//	/// Set interrupt flag.
//	wdtNmiIntInputFlag = WDT_INT_NMI_ON;
//}
//
//
//int isWdtIntNmi( void )
//{
//	int result = STATUS_NO_OCCURRED;
//
//	if ( wdtNmiIntInputFlag == WDT_INT_NMI_ON ) {
//		result = STATUS_OCCURRED;
//	}
//
//	return result;
//}
