/**********
 * Ce fichier définit les fonctions du timer utilisé pour détecter les appuis longs
 * ***********/

#include <t16_ch2_appuiLongBouton.h>
#include <stddef.h>

void (*actionAFaireTimer2)(void) = NULL;

void initT16Ch2( void )
{
	/// Check IOSC.
	/*if ( CLGOSC_IOSCEN == 0 ) {
		return STATUS_NG;
	}*/

	/// Stop T16 Ch.0 Timer.
 	stopT16Ch2();

	T16_2CTL_MODEN		= 0;				/// - Stop supplying operating clock

	/// Configure the T16 Ch.0 operating clock.
	T16_2CLK_CLKSRC 	= 1;				/// - Clock source selection(setting OSC1)
	T16_2CLK_CLKDIV 	= 0x8;				/// - Clock division ratio selection(setting f= f_0 /256=128 Hz )
	T16_2CLK_DBRUN = 1;				/// - Clock supplied in DEBUG mode

	/// Enable count operation clock.
	T16_2CTL_MODEN		= 1;				/// - Start supplying operating clock.

	/// Select operation mode.
	T16_2MOD_TRMD		= 1;				/// - Set one shot mode.

	/// initialize interrupt.
	T16_2INTF			= 0x0001;			/// - Clear interrupt flag(T16_2INTF_UFIF = 1).
	T16_2INTE_UFIE		= 0;				/// - Disable interrupt.
	ILVT16_2			= INTERRUPT_LEVEL3;	/// - Set interrupt level-3.

	/// Preset reload data to counter.
	presetT16Ch2Count(0xFFFF);

	/// Clear Interruption counter.
	//t16Ch2IntCount		= 0;

	//return STATUS_OK;
}


void startT16Ch2(void)
{
	/// Clear interrupt flag.
	//T16_2INTF_UFIF		= 1;
	T16_2INTF			= 0x0001;
	/// Enable T16 Ch.0 underflow interrupts.
	T16_2INTE_UFIE		= 1;
	/// T16_2CTL.PRUN set 1(timer start).
	T16_2CTL_PRUN		= 1;
}


void stopT16Ch2(void)
{
	/// T16_2CTL.PRUN set 1(timer stop).
	T16_2CTL_PRUN		= 0;
	/// Disble T16 Ch.0 underflow interrupts.
	T16_2INTE_UFIE		= 0;
	/// Clear interrupt flag.
	//T16_2INTF_UFIF		= 1;
	T16_2INTF			= 0x0001;
}

void waitAndDo2(unsigned short count  , void * actionAFaire){
	//while ( T16_2CTL_PRUN /*== 1*/ ) { } // tant qu'il est en train de marcher on attend
	stopT16Ch2();
	actionAFaireTimer2 = actionAFaire;
	presetT16Ch2Count( count );
	startT16Ch2();
}

// count = nb de secondes à attendre
void presetT16Ch2Count( unsigned short count )
{
	/// Set the initial value to be preset to the counter.
	T16_2TR = 128 * count; // le 128 sert à compenser la fréquence trop grande

	/// Presets the reload data stored in the T16_2TR register to the counter.
	T16_2CTL_PRESET = 1;

	/// It is confirmed whether the preset finished.
	while ( T16_2CTL_PRESET != 0 ) {
		// wait...
	}
}


unsigned short getT16Ch2Count( void )
{
	return ( T16_2TC );
}

void intT16Ch2(void)
{
	/// Check interrupt cause occurrence status.
	if ( T16_2INTF_UFIF == 1 ) {
		/// Clear T16 Ch.0 Interrupt flag.
		//T16_2INTF_UFIF = 1;
		T16_2INTF			= 0x0001;

		(*actionAFaireTimer2)();
		actionAFaireTimer2=NULL;
	}
}
