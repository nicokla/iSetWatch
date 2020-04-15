/************
 * Ce fichier définit le mode du compte à rebours (countdown)
 ************ */

#include <t16_ch1_countdown.h>
#include "globalVar.h"
#include "init.h"
#include "lcd8a.h"
#include "class/time.h"
#include "string.h"
#include "interruptTime.h"
#include "interruptBoutons.h"
#include "buzzer.h"
#include "backlight.h"
#include "tennis.h"
#include "class/ecranPourClignotements.h"
#include "watch.h"

// temps present du compte à rebours
ShortTime countDownNow;

// maximum du compte à rebours
ShortTime countDownMax;

//
unsigned char suivantCountDown[4];

// sert à faire clignoter les deux points (vaut à chaque demi-seconde, alternativement 0 ou 1)
unsigned char secondePile=1;

long long sec_temp_countDown = 0;

// initialise les positions des varAff du compte à rebours (secondes, minutes, ...)
void initConstantesCountDown(){
	//stopT16Ch1();
	// count = nb de secondes à attendre
	//presetT16Ch1Count();

	initTimeShort(&countDownNow);
	initTimeShort(&countDownMax);
	countDownNow.second.nb=10;
	countDownMax.second.nb=10;

	countDownNow.hour.type=INT7;
	setPosInt7(&(countDownNow.hour),0,0,1); // position 0,0 ; forcé à 2 chiffres

	countDownNow.minute.type=INT7;
	setPosInt7(&(countDownNow.minute),1,0,1);

	countDownNow.second.type=INT7;
	setPosInt7(&(countDownNow.second),1,1,1);

	suivantCountDown[COUNTDOWN & MASQUE_SUB] = COUNTDOWN_HOUR;
	suivantCountDown[COUNTDOWN_HOUR & MASQUE_SUB] = COUNTDOWN_MINUTE;
	suivantCountDown[COUNTDOWN_MINUTE & MASQUE_SUB] = COUNTDOWN_SECOND;
	suivantCountDown[COUNTDOWN_SECOND & MASQUE_SUB] = COUNTDOWN;
}

// fonction appelée à l'entrée dans le mode COUNTDOWN (ou un de ses sous-modes)
void prepareDisplayCountDown(){
	placerDansEcran(&(deuxPointsSecondes));
	setVarAffValue(&deuxPointsSecondes,secondePile);

	mettreSurEcranTexte(0, "TIMER");
	if(mode!=COUNTDOWN)
		mettreSurEcranTexte(1, "  SET");

	placerDansEcran(&(countDownNow.hour));
	placerDansEcran(&(countDownNow.minute));
	placerDansEcran(&(countDownNow.second));
}

// Action lors de l'appui sur un ou des boutons
void actionModeCountdown(unsigned char typeEvenement){
	if(mode != COUNTDOWN){// mode!=modePrincipal(mode)){
		switch(typeEvenement){
		case BOUTON2COURT:
			augmenterVarAff(currentVarAff);
			break;
		case BOUTON3COURT:
			diminuerVarAff(currentVarAff);
			break;
		case BOUTON1COURT:
			if(suivantCountDown[mode & MASQUE_SUB] == COUNTDOWN){
				countDownMax.hour.nb=countDownNow.hour.nb;
				countDownMax.second.nb=countDownNow.second.nb;
				countDownMax.minute.nb=countDownNow.minute.nb;
			}
			mettreMode(suivantCountDown[mode & MASQUE_SUB]);
			break;
		case BOUTON4COURT:
			countDownMax.hour.nb=countDownNow.hour.nb;
			countDownMax.second.nb=countDownNow.second.nb;
			countDownMax.minute.nb=countDownNow.minute.nb;
			mettreMode(COUNTDOWN);
			break;
		}
	}

	else{ // if (mode == COUNTDOWN)
		switch(typeEvenement){
		case BOUTON1COURT:
			lightOn();
			break;
		case BOUTON4COURT:
			desactiverDisplayTimeShort(&countDownNow);
			mettreMode(TENNIS+tennisMode[0]);
			break;
		case BOUTON4AFTEROTHER:
			mettreMode(WATCH);
			break;
		case BOUTON1LONG:
			if(! T16_1CTL_PRUN){
				setVarAffValue(&countDownNow.hour,countDownMax.hour.nb);
				setVarAffValue(&countDownNow.minute,countDownMax.minute.nb);
				setVarAffValue(&countDownNow.second,countDownMax.second.nb);

				mettreMode(COUNTDOWN_HOUR);
			}
			break;
		case BOUTON2COURT:
			if(T16_1CTL_PRUN)
				stopT16Ch1();
			else
				startT16Ch1();
			out_bz_short();
			break;
		case BOUTON3COURT:
			if(! T16_1CTL_PRUN){
				setVarAffValue(&countDownNow.hour,countDownMax.hour.nb);
				setVarAffValue(&countDownNow.minute,countDownMax.minute.nb);
				setVarAffValue(&countDownNow.second,countDownMax.second.nb);
				secondePile=1;
			}
			break;
		}
	}
}

// initialise le timer du compte à rebours
void initT16Ch1( void )
{
 	stopT16Ch1();

	T16_1CTL_MODEN		= 0;				/// - Stop supplying operating clock

	/// Configure the T16 Ch.0 operating clock.
	T16_1CLK_CLKSRC 	= 1;				/// - Clock source selection(setting OSC1)
	T16_1CLK_CLKDIV 	= 0x8;				/// - Clock division ratio selection(setting f= f_0 /256=128 Hz )
	T16_1CLK_DBRUN = 1;				/// - Clock supplied in DEBUG mode

	/// Enable count operation clock.
	T16_1CTL_MODEN		= 1;				/// - Start supplying operating clock.

	/// Select operation mode.
	T16_1MOD_TRMD		= 0;				/// - Set repeat mode.

	/// initialize interrupt.
	T16_1INTF			= 0x0001;			/// - Clear interrupt flag(T16_1INTF_UFIF = 1).
	T16_1INTE_UFIE		= 0;				/// - Disable interrupt.
	ILVT16_1			= INTERRUPT_LEVEL3;	/// - Set interrupt level-3.

	/// Preset reload data to counter.
	presetT16Ch1Count(0xFFFF);
}

// demarre le compte à rebours
void startT16Ch1(void)
{
	/// Clear interrupt flag.
	//T16_1INTF_UFIF		= 1;
	T16_1INTF			= 0x0001;
	/// Enable T16 Ch.0 underflow interrupts.
	T16_1INTE_UFIE		= 1;
	/// T16_1CTL.PRUN set 1(timer start).
	T16_1CTL_PRUN		= 1;
}

// arrete le compte à rebours
void stopT16Ch1(void)
{
	/// T16_1CTL.PRUN set 1(timer stop).
	T16_1CTL_PRUN		= 0;
	/// Disble T16 Ch.0 underflow interrupts.
	T16_1INTE_UFIE		= 0;
	/// Clear interrupt flag.
	//T16_1INTF_UFIF		= 1;
	T16_1INTF			= 0x0001;
}

// Précise l'écart de temps entre chaque interruptions générée par le timer : une demi seconde
// car on doit aussi faire clignoter les deux points
void presetT16Ch1Count( )//unsigned short count )
{
	/// Set the initial value to be preset to the counter.
	T16_1TR = 64 ; // le 128 représente 1 seconde, le 64 signifie une demi-seconde, pour clignotements

	/// Presets the reload data stored in the T16_1TR register to the counter.
	T16_1CTL_PRESET = 1;

	/// It is confirmed whether the preset finished.
	while ( T16_1CTL_PRESET != 0 ) {
		// wait...
	}
}

// renvoie si la valeur du compteur du timer (entre 64 et zéro)
// en pratique on ne s'intéresse pas à la valeur
// on peut quand même éventuellement s'interesser à si elle fait zéro ou non
unsigned short getT16Ch1Count( void )
{
	return ( T16_1TC );
}

// renvoie 1 seulement si le countDown est fini (il faut alors faire sonner le buzzer)
unsigned char estFiniCountDown(){
	return countDownNow.second.nb == 0 && countDownNow.minute.nb == 0 && countDownNow.hour.nb == 0 ;
}

// interruption touchée chaque demi-seconde si le compte à rebours est en marche.
// Diminue les secondes du compte à rebours à chaque fois que secondePile vaut 1
void intT16Ch1(void)
{
	/// Check interrupt cause occurrence status.
	if ( T16_1INTF_UFIF == 1 ) {
		//T16_1INTF_UFIF = 1;
		T16_1INTF			= 0x0001;

		secondePile=1-secondePile;
		if(mode == COUNTDOWN)
			setVarAffValue(&deuxPointsSecondes,secondePile);
		//setSymbole(SYMBOL_INDEX_2PTS2,secondePile);

		if(secondePile){
			if(! estFiniCountDown()){
				diminueSecondes(&countDownNow, 1 );
			}

			if (estFiniCountDown()) {
				stopT16Ch1();
				caSonne = COUNTDOWN;
				sec_temp_countDown = totalSecond(&watch.shortTime);
			}
		}

	}
}
