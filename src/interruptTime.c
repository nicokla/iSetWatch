#include <string.h>
#include "interruptTime.h"
#include "globalVar.h"
#include "init.h"
#include "interruptBoutons.h"

#include "lcd8a.h"
#include "backlight.h"
#include "buzzer.h"

#include "bluetooth.h"
#include "uart.h"
#include "tennis.h"
#include "chrono.h"
#include "time.h"
#include "alarm.h"
#include "watch.h"
#include "wdt.h"
#include "t16_ch1_countdown.h"

#include "ecranPourClignotements.h"

unsigned short int rtcaIntf;
unsigned char caSonne = 0;
unsigned char alarmBips5Minutes=0;
long long sec_temp_alarm=0;

unsigned char quarterCount = 0;
unsigned char flags=0;
unsigned char flagsChrono=0;

///////////////////
// reactions aux interruptions temporelles

// Fonction appelée lors d'une interruption de real-time clock
void intRtca( void ) {
	rtcaIntf = RTCINTF;
	RTCINTF = rtcaIntf;

	////////////////////////////////////////
	// actions chrono
	flagsChrono=(unsigned char) ((rtcaIntf & 0x7000) >> 8);

	if(mode == STOPWATCH_RUN){
		switch(flagsChrono){
		case 0x10:
			ecran.aff14Seg[1].contenu.lettres[4]=RTCSWCTL_BCD100 +0x30;
			afficherChiffreSur14Seg(1,4,RTCSWCTL_BCD100);
			break;
		case 0x30 :// dixiemes de secondes
		case 0x70 :// secondes
			ecran.aff14Seg[1].contenu.lettres[4]=RTCSWCTL_BCD100 +0x30;
			afficherChiffreSur14Seg(1,4,RTCSWCTL_BCD100);
			ecran.aff14Seg[1].contenu.lettres[3]=RTCSWCTL_BCD10 +0x30;
			afficherChiffreSur14Seg(1,3,RTCSWCTL_BCD10);
			//setSymbole(SYMBOL_INDEX_2PTS2, RTCSWCTL_BCD10<5);
			switch(RTCSWCTL_BCD10){
				case 0:
					setSymbole(SYMBOL_INDEX_2PTS2,1);
					break;
				case 5:
					setSymbole(SYMBOL_INDEX_2PTS2, 0);
					break;
			}
			break;
		}
	}

	// a faire pas seulement en mode STOPWATCH_RUN.
	if (flagsChrono == 0x70)
			augmenteSecondes(&chrono, 1);

	//////////////////////////////////
	// quart de seconde
	flags=(unsigned char) (rtcaIntf & 0x00FC);
	if(flags){//rtcaIntf & 0x0004){
		//quarterCount=(quarterCount < 3) ? quarterCount+1 : 0;
		switch(flags){
		case 0xFC: // jour
		case 0x7C: // heure
		case 0x3C: // minute
		case 0x1C: // seconde
			putHardwareTimeInAbstractTime(&watch, flags ); // affichage de watch
		case 0x0C : // demi-secondes
			afficheEcranClignotement(flags & 0x10);
		case 0x04: // quarts de secondes
			afficheDefilementAll(); // on a flags donc au minimum
			break;
		}
	}

	if(flags & 0x10) // secondes hors l'affichage de watch
		actionSeconde();
}

// Actions réalisées chaque secondes
void actionSeconde(void){
	//augmenteSecondes(&watch.shortTime);
//	putHardwareTimeInAbstractTime(&watch, flags );

	// on reset le watchdog timer
	resetWdt();

	if (alarmeDeclenchee()) {
		caSonne = ALARM;
		sec_temp_alarm = totalSecond(&watch.shortTime);
		// on retient la seconde du declenchement de l'alarme pour faire l'arret auto au bout de 15 sec
		// et pour faire le redemarrage de l'alarme au bout de 5, 10 et 15 minutes (si l'alarme n'est pas arretee par bouton)
	}

	if (caSonne != 0){
		bipBip(2);

		if(caSonne == ALARM){
			if(differenceSecondGen(totalSecond(&watch.shortTime),sec_temp_alarm)>=17 ){
				caSonne=0; // on arrete la sonnerie
				alarmBips5Minutes=1; // on amorce une attente pour les minutes 5, 10, et 15 apres le declenchement normal de l'alarme
			}
		}
		else if(caSonne == COUNTDOWN){
			if(differenceSecondGen(totalSecond(&watch.shortTime),sec_temp_countDown)>=10 ){
				caSonne=0; // on arrete la sonnerie
				setVarAffValue(&countDownNow.hour,countDownMax.hour.nb); // on remet le compte a rebours au max, a zero il ne sert a rien.
				setVarAffValue(&countDownNow.minute,countDownMax.minute.nb);
				setVarAffValue(&countDownNow.second,countDownMax.second.nb);
			}
		}
	}

	switch(mode){
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER :
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE :
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER :
		if(! countDownPairingStopped )
			actionSecondeBluetoothWaitConnexion();
		break;
	}

	// action minute
	if (watch.shortTime.second.nb==0){//rtcaIntf & 0x0020) {
		actionMinute();
	}

}

// Actions réalisées chaque minutes
void actionMinute(){
	// !! attention si le match n'est pas fini mais que les joueurs veulent le reprendre
	// un autre jour, on ne peut pas faire ça.
	// solution ? --> supposer que si aucun point n'est joué pendant 5 ou 10 min, c'est que
	// les joueurs sont partis et recommenceront apres.
	// Donc on arrete d'incrementer le temps du tennis dans ce cas, et dès qu'un nouveau point est compté,
	// on reprend le comptage du temps du tennis.
	if(tennisCommence()){
		if(tennisOntLAirDEtreEnTrainDeJouer)
			tennisSetMinutes[numManche()]++;

		// timeout
#ifdef MODE_DEBUG_BLUETOOTH
		if(differenceMinuteGen(totalMinute(&watch.shortTime),tennisLastPointChangeMinute) >= 2)
#else
		if(differenceMinuteGen(totalMinute(&watch.shortTime),tennisLastPointChangeMinute) >= TIME_OUT_BLUETOOTH)
#endif
		{
			tennisOntLAirDEtreEnTrainDeJouer=0;
			if(mode != TENNIS_SETTING_BLUETOOTH){
				if(bluetoothMode.nb){
//					setVarAffValue(&bluetoothMode,BL_OFF);
					setBluetoothModeValue(BL_OFF);
				}
			}
		}
	}

	if(watch.activated.nb && alarmBips5Minutes){
		// si l'alarme n'a pas ete arretee par bouton et qu'on est entre 0 et 15 minutes apres l'alarme
		short aa = differenceMinute(&watch.shortTime, &watch.shortTimeAlarm);
		if( aa == 5 || aa == 10 || aa == 15 ){
			caSonne=ALARM; // on active la sonnerie
			sec_temp_alarm=totalSecond(&watch.shortTime);
		}
		if(aa==15){
			alarmBips5Minutes=0;
		}
	}
}

// Démarrage du real time clock
void demarreTemps() {
	RTCCTL_RTCRUN = 0;
	ILVRTCA_0 = INTERRUPT_LEVEL3;

	RTCINTF_1_32SECIF=1;
	RTCINTF_1_8SECIF=1;
	RTCINTF_1_4SECIF=1;
	RTCINTF_1_2SECIF=1;
	RTCINTF_1SECIF=1;
	RTCINTF_1MINIF	=1;
	RTCINTF_1HURIF=1;
	RTCINTF_1DAYIF=1;
	RTCINTF_ALARMIF=1;

//	RTCINTE_1_32SECIE=0;
//	RTCINTE_1_8SECIE=0;
	RTCINTE_1_4SECIE=1; // quart de secondes
	RTCINTE_1_2SECIE=0;
	RTCINTE_1SECIE=0; // secondes
//	RTCINTE_1MINIE	=0;
//	RTCINTE_1HURIE=0;
//	RTCINTE_1DAYIE=0;
//	RTCINTE_ALARMIE=0;

	RTCCTL_RTCRUN = 1;
}

// Arret du real time clock
void arreteTemps(){
	RTCCTL_RTCRUN = 0;

	RTCINTF_1_32SECIF=1;
	RTCINTF_1_8SECIF=1;
	RTCINTF_1_4SECIF=1;
	RTCINTF_1_2SECIF=1;
	RTCINTF_1SECIF=1;
	RTCINTF_1MINIF	=1;
	RTCINTF_1HURIF=1;
	RTCINTF_1DAYIF=1;
	RTCINTF_ALARMIF=1;

	RTCINTE_1_32SECIE=0;
	RTCINTE_1_8SECIE=0;
	RTCINTE_1_4SECIE=0;
	RTCINTE_1_2SECIE=0;
	RTCINTE_1SECIE=0;
	RTCINTE_1MINIE	=0;
	RTCINTE_1HURIE=0;
	RTCINTE_1DAYIE=0;
	RTCINTE_ALARMIE=0;

	RTCCTL_RTCRUN = 1;
}
