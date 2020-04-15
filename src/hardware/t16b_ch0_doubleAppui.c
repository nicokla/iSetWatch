/**********
 * Ce fichier définit les fonctions du timer utilisé pour détecter les doubles appuis
 * ***********/

#include <t16b_ch0_doubleAppui.h>


void initT16bCh0( void )
{
	/// Stop T16bCh0.
	stopT16bCh0();

	/// Set Enable T16B operations.
	T16B0CTL_MODEN		= 1;

	/// Set clock source for T16bCh0.
	T16B0CLK_CLKSRC		= 1;		/// - Set clock source(OSC1).
	T16B0CLK_CLKDIV		= 0x8;		/// - Set division ratio for clock source(f0/256 ---> T = 1/128 secondes ).
	T16B0CLK_DBRUN		= 1;		/// - Clock supplied in DEBUG mode.
	CLGOSC_IOSCSLPC		= 0;		/// - Continue operation state before SLEEP.

	/// Set comparator/capture circuit 0 to comparator mode.
	T16B0CCCTL0_CCMD	= 0;		/// - The operating mode(0=Comparator/1=Capture).

	/// Set MAX counter data.
	//T16B0MC				= 0xFFFF;

	// Clear interrupt flags.
	T16B0INTF_CNTZEROIF	= 1;		/// - Counter zero interrupt flag.

	// Disable interrupts.
	T16B0INTE_CNTZEROIE	= 1;		/// - Counter zero interrupt.

	// Reset counter(global variable).
	presetT16bCh0Count(0xFFFF);

	/// Set count down operation.
	T16B0CTL_CNTMD		= 1;

	/// Set one-shot operation.
	T16B0CTL_ONEST		= 1;

	/// Initialize the interrupt.
	ILVT16B_0			= INTERRUPT_LEVEL3;

	//return STATUS_OK;
}

void startT16bCh0( void )
{
	// Clear interrupt flags.
	T16B0INTF_CNTZEROIF	= 1;		/// - Counter zero interrupt flag.

	// Enable interrupts.
	T16B0INTE_CNTZEROIE	= 1;		/// - Counter zero interrupt.

	// Reset counter(global variable).
	//resetT16bCh0IntCount();

	/// Reset counter.
	//T16B0CTL_PRESET		= 1;

	/// Start counting.
	T16B0CTL_RUN		= 1;
}

void stopT16bCh0( void )
{
	/// Stop counting.
	T16B0CTL_RUN		= 0;
	// Enable interrupts.
	T16B0INTE_CNTZEROIE	= 0;
	// Clear interrupt flags.
	T16B0INTF_CNTZEROIF	= 1;		/// - Counter zero interrupt flag.
}

unsigned short getT16bCh0TimerCount( void )
{
	/// Get comparator count.
	return ( (unsigned short)T16B0TC );
}

void wait_t16b_ch0/*waitAndDo_t16b_ch0*/(unsigned short count){  //, void (* actionAFaire)(void)){
	stopT16bCh0();
	//actionAFaireTimerB0 = actionAFaire;
	presetT16bCh0Count( count ); // en 128 eme de secondes. 13 = 1/10eme de secondes
	startT16bCh0();
}

void presetT16bCh0Count( unsigned short count ) {
	/// Set the initial value to be preset to the counter.
	T16B0MC = count;

	/// Presets the reload data stored in the T16B0CTL_PRESET register to the counter.
	T16B0CTL_PRESET		= 1;

	/// It is confirmed whether the preset finished.
	while ( T16B0CTL_PRESET != 0 ) {
		// wait...
	}
}

void intT16bCh0( void )
{
	/// Check counter zero interrupt flag.
	if ( T16B0INTF_CNTZEROIF == 1 ) {
		/// - Clear flag.
		//T16B0INTF_CMPCAP0IF = 1;
		//T16B0INTF = 0x0001;
		T16B0INTF_CNTZEROIF = 1;
	}
}

