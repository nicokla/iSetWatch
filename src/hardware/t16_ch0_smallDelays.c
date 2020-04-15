#include <t16_ch0_smallDelays.h>
#include <stddef.h>
#include "fileDActions.h"
#include "globalVar.h"
#include "string.h"

//void (*actionAFaireTimer0)(void) = NULL;

void initT16Ch0( void )
{
	/// Check IOSC.
	/*if ( CLGOSC_IOSCEN == 0 ) {
		return STATUS_NG;
	}*/

	/// Stop T16 Ch.0 Timer.
 	stopT16Ch0();

	T16_0CTL_MODEN		= 0;				/// - Stop supplying operating clock

	/// Configure the T16 Ch.0 operating clock.
	T16_0CLK_CLKSRC 	= 1;				/// - Clock source selection(setting OSC1)
	T16_0CLK_CLKDIV 	= 0x8;				/// - Clock division ratio selection(setting f= f_0 /256=128 Hz )
	T16_0CLK_DBRUN = 1;				/// - Clock supplied in DEBUG mode

	/// Enable count operation clock.
	T16_0CTL_MODEN		= 1;				/// - Start supplying operating clock.

	/// Select operation mode.
	T16_0MOD_TRMD		= 1;				/// - Set one shot mode.

	/// initialize interrupt.
	T16_0INTF			= 0x0001;			/// - Clear interrupt flag(T16_0INTF_UFIF = 1).
	T16_0INTE_UFIE		= 0;				/// - Disable interrupt.
	ILVT16_0			= INTERRUPT_LEVEL3;	/// - Set interrupt level-3.

	/// Preset reload data to counter.
	presetT16Ch0CountShortTimes(0xFFFF);

	/// Clear Interruption counter.
	//t16Ch0IntCount		= 0;

	//return STATUS_OK;
}


void startT16Ch0(void)
{
	/// Clear interrupt flag.
	//T16_0INTF_UFIF		= 1;
	T16_0INTF			= 0x0001;
	/// Enable T16 Ch.0 underflow interrupts.
	T16_0INTE_UFIE		= 1;
	/// T16_0CTL.PRUN set 1(timer start).
	T16_0CTL_PRUN		= 1;
}


void stopT16Ch0(void)
{
	/// T16_0CTL.PRUN set 1(timer stop).
	T16_0CTL_PRUN		= 0;
	/// Disble T16 Ch.0 underflow interrupts.
	T16_0INTE_UFIE		= 0;
	/// Clear interrupt flag.
	//T16_0INTF_UFIF		= 1;
	T16_0INTF			= 0x0001;
}

// on peut attendre au max 511 secondes, soit un peu plus de 8 minutes et 30 secondes
// car 2^16/2^7=2^9=512.
// count est en secondes
void waitAndDo(unsigned short count  , void (* actionAFaire)(void)){
	//while ( T16_0CTL_PRUN /*== 1*/ ) { } // tant qu'il est en train de marcher on attend
	stopT16Ch0();
	if( (! fileDActions.estEnTrainDEtreModifiee) && fileDActions.size < MAX_SIZE_FILE_ACTIONS ){
		waitAndDoFile( 128*count , actionAFaire, &fileDActions);// le 128 sert à compenser la fréquence trop grande

//		transfererActionsPasTraitees(); --> pb, le preset et le start y sont conditionnels alors qu'ici non
		// on prefere donc en faire une version optimisee sans passer par le if pour lancer le preset/start:

		// si entre temps des choses ont été mises dans la liste d'actions, on les transfert dans la file
		while(listeDActionsAMettreDansLaFile.iMin != listeDActionsAMettreDansLaFile.iMax && fileDActions.size < MAX_SIZE_FILE_ACTIONS){
			waitAndDoFile(listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMin].attente,
					listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMin].actionAFaire,
					&fileDActions);
			augmenterModulo(listeDActionsAMettreDansLaFile.iMin, 0, TAILLE_FILE_AUX-1);
		}

		presetT16Ch0CountShortTimes( fileDActions.actionAFaireEnPremier->attenteEnPlus );
	}else{
		// si la file est en train d'etre modifiee, on n'y touche pas
		listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMax].attente=128*count;
		listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMax].actionAFaire=actionAFaire;
		augmenterModulo(listeDActionsAMettreDansLaFile.iMax, 0, TAILLE_FILE_AUX-1);
	}
	startT16Ch0();
}

// count est en 128eme de secondes
void waitAndDoShortTimes(unsigned short count, void (* actionAFaire)(void)){
	//while ( T16_0CTL_PRUN /*== 1*/ ) { } // tant qu'il est en train de marcher on attend
	stopT16Ch0();
	waitAndDoFile( count , actionAFaire, &fileDActions);
	presetT16Ch0CountShortTimes( fileDActions.actionAFaireEnPremier->attenteEnPlus );
	startT16Ch0();
}


// count est en 128eme de secondes
void presetT16Ch0CountShortTimes( unsigned short count )
{
	/// Set the initial value to be preset to the counter.
	T16_0TR = count;

	/// Presets the reload data stored in the T16_0TR register to the counter.
	T16_0CTL_PRESET = 1;

	/// It is confirmed whether the preset finished.
	while ( T16_0CTL_PRESET != 0 ) {
		// wait...
	}
}


unsigned short getT16Ch0Count( void )
{
	return ( T16_0TC );
}

void intT16Ch0(void)
{
	/// Check interrupt cause occurrence status.
	if ( T16_0INTF_UFIF == 1 ) {
		/// Clear T16 Ch.0 Interrupt flag.
		//T16_0INTF_UFIF = 1;
		T16_0INTF			= 0x0001;

		if( fileDActions.size > 0 ){
			fileDActions.actionAFaireEnPremier->attenteEnPlus = 0;
			while(fileDActions.size > 0 && fileDActions.actionAFaireEnPremier != NULL ) {
				if(fileDActions.actionAFaireEnPremier->attenteEnPlus == 0){
					fairePuisDefilerUneAction(&fileDActions);
				}else{
					break;
				}
			}
			if(fileDActions.size == 0){
				memset(&(cellsUtilisees[0]),0,MAX_SIZE_FILE_ACTIONS);
			}
		}

		if(fileDActions.size == 0)
			fileDActions.actionAFaireEnPremier = NULL;
		if(fileDActions.actionAFaireEnPremier == NULL)
			fileDActions.size = 0;

		if(fileDActions.size > 0) {// && fileDActions.actionAFaireEnPremier != NULL){
			presetT16Ch0CountShortTimes( fileDActions.actionAFaireEnPremier->attenteEnPlus );
			startT16Ch0();
		}
	}
}
