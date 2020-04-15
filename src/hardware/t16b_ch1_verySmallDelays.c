#include <t16b_ch1_verySmallDelays.h>
#include <stddef.h>
#include "ecranPourClignotements.h"
#include "interruptTime.h"
#include "varAff.h"

void (*actionAFaireTimerB1)(void) = NULL;
void (*actionAFaireFinale)(void) = NULL;
unsigned char clignotementOn;
VarAff compteurSecondes;
unsigned char modeOuOnDecompte;

// Utilisée seulement lors de l'oad updating pour l'instant. Permet de faire défiler les secondes
// sans avoir à passer par interruptTime.c
void initCompteurSecondes(){
	compteurSecondes.type=INT7;
	setBounds(&compteurSecondes, 0 , 255 , 255);
	setPosInt7(&compteurSecondes,1,1,1);
	//compteurSecondes.toDisplayIfChanged=1;
}

// initialise le timer
void initT16bCh1( void )
{
	/// Stop T16bCh1.
	stopT16bCh1();

	/// Set Enable T16B operations.
	T16B1CTL_MODEN		= 1;

	/// Set clock source for T16bCh1.
	T16B1CLK_CLKSRC		= 1;		/// - Set clock source(OSC1).
	T16B1CLK_CLKDIV		= 0x8;		/// - Set division ratio for clock source(f0/256 ---> T = 1/128 secondes ).
	T16B1CLK_DBRUN		= 1;		/// - Clock supplied in DEBUG mode.
	CLGOSC_IOSCSLPC		= 0;		/// - Continue operation state before SLEEP.

	/// Set comparator/capture circuit 0 to comparator mode.
	T16B1CCCTL0_CCMD	= 0;		/// - The operating mode(0=Comparator/1=Capture).

	/// Set MAX counter data.
	//T16B1MC				= 0xFFFF;

	// Clear interrupt flags.
	T16B1INTF_CNTZEROIF	= 1;		/// - Counter zero interrupt flag.

	// Disable interrupts.
	T16B1INTE_CNTZEROIE	= 1;		/// - Counter zero interrupt.

	// Reset counter(global variable).
	presetT16bCh1Count(0xFFFF);

	/// Set count down operation.
	T16B1CTL_CNTMD		= 1;

	/// One shot mode
	T16B1CTL_ONEST		= 1;

	/// Initialize the interrupt.
	ILVT16B_1			= INTERRUPT_LEVEL3;

	//return STATUS_OK;
}

// Start le timer
void startT16bCh1( void )
{
	// Clear interrupt flags.
	T16B1INTF_CNTZEROIF	= 1;		/// - Counter zero interrupt flag.

	// Enable interrupts.
	T16B1INTE_CNTZEROIE	= 1;		/// - Counter zero interrupt.

	// Reset counter(global variable).
	//resetT16bCh1IntCount();

	/// Reset counter.
	//T16B1CTL_PRESET		= 1;

	/// Start counting.
	T16B1CTL_RUN		= 1;
}

// Stop le timer
void stopT16bCh1( void )
{
	/// Stop counting.
	T16B1CTL_RUN		= 0;
	// Enable interrupts.
	T16B1INTE_CNTZEROIE	= 0;
	// Clear interrupt flags.
	T16B1INTF_CNTZEROIF	= 1;		/// - Counter zero interrupt flag.
}

// Renvoie le nombre dans le timer
unsigned short getT16bCh1TimerCount( void )
{
	/// Get comparator count.
	return ( (unsigned short)T16B1TC );
}

// Lance une attente, mais sans régler actionAFaireTimerB1
// Pas utilisée en pratique
void wait_t16b_ch1/*waitAndDo_t16b_ch1*/(unsigned short count){  //, void (* actionAFaire)(void)){
	stopT16bCh1();
	//actionAFaireTimerB0 = actionAFaire;
	presetT16bCh1Count( count ); // en 128 eme de secondes. 13 = 1/10eme de secondes
	startT16bCh1();
}

// Compteur généraliste pour de courtes durées
// (count est en 128 eme de secondes)
void waitAndDoShortTimesT16B1(unsigned short count, void (* actionAFaire)(void)){
	//while ( T16_0CTL_PRUN /*== 1*/ ) { } // tant qu'il est en train de marcher on attend
	stopT16bCh1();
	T16B1CTL_ONEST		= 1;	/// One-shot mode
	actionAFaireTimerB1 = actionAFaire;
	presetT16bCh1Count( count );
	startT16bCh1();
}

//void afficheEcranClignotementSpecial(){
//	clignotementOn=1-clignotementOn;
//	afficheEcranClignotement(clignotementOn);
//}

// Utilisée seulement lors de l'oad updating pour l'instant. Permet de faire défiler les secondes
// sans avoir à passer par interruptTime.c
void afficheSecondesQuiPassent(){
	//diminuerVarAff(&compteurSecondes);
	compteurSecondes.nb --;
	if(compteurSecondes.nb==0){
		stopSecondsInterrupts();
		(*actionAFaireFinale)();
	} else if (modeOuOnDecompte != mode){
		stopSecondsInterrupts();
	}
}

// void (* actionAFaire)(void)
//void startSecondsInterrupts(unsigned char a, unsigned char b, unsigned char duree){

// Utilisée seulement lors de l'oad updating pour l'instant. Permet de faire défiler les secondes
// sans avoir à passer par interruptTime.c
void startSecondsInterrupts(unsigned char duree, void (* actionAFaire)(void)){
	stopT16bCh1();
	T16B1CTL_ONEST		= 0;	/// Repeat mode --> les clignotements sont en continue
	// tant qu'on ne les a pas arrêtés
	clignotementOn=(flags & 0x10)>>4;
	setVarAffValue(&compteurSecondes,duree);
	setPosInt7(&compteurSecondes, 1, 1, 1);
	actionAFaireTimerB1 = &afficheSecondesQuiPassent;
	actionAFaireFinale=actionAFaire;
	modeOuOnDecompte=mode;
	presetT16bCh1Count(128); // 1 seconde
	startT16bCh1();
}

// Utilisée seulement lors de l'oad updating pour l'instant. Permet de faire défiler les secondes
// sans avoir à passer par interruptTime.c
void stopSecondsInterrupts(){
	stopT16bCh1();
	T16B1CTL_ONEST		= 1;	/// One-shot mode (normal)
}

// Fixe la durée avant de lancer le décompte
void presetT16bCh1Count( unsigned short count )
{
	/// Set the initial value to be preset to the counter.
	T16B1MC = count;

	/// Presets the reload data stored in the T16B1CTL_PRESET register to the counter.
	T16B1CTL_PRESET		= 1;

	/// It is confirmed whether the preset finished.
	while ( T16B1CTL_PRESET != 0 ) {
		// wait...
	}
}

// arrivée de l'interruption lorsque le timer touche zéro.
// Il fait alors l'action actionAFaireTimerB1(), réglée auparavant via l'appel de waitAndDoShortTimesT16B1
void intT16bCh1( void )
{
	/// Check counter zero interrupt flag.
	if ( T16B1INTF_CNTZEROIF == 1 ) {
		/// - Clear flag.
		//T16B1INTF_CMPCAP0IF = 1;
		//T16B1INTF = 0x0001;
		T16B1INTF_CNTZEROIF = 1;
		if(actionAFaireTimerB1 != NULL)
			(*actionAFaireTimerB1)();
	}
}

