#include "watch.h"
#include "time.h"
#include "ecranPourClignotements.h"
#include "varAff.h"
#include "globalVar.h"
#include "init.h"
#include "lcd8a.h"
#include "alarm.h"
#include "interruptBoutons.h"
#include "buzzer.h"
#include "backlight.h"
#include "interruptTime.h"
#include "t16b_ch1_verySmallDelays.h"
#include "rtca.h"

// La structure contenant le temps
Time watch;

// La structure contenant les deux points clignotants chaque secondes
VarAff deuxPointsSecondes;

// Les textes à afficher lors du changement de jour
// Le premier jour est dimanche pour être en compatibilité avec les variables bas niveau du seiko
char jours[7][5]=
{"  SUN", "  MON", 	"  TUE", "  WED", "  THU", "  FRI", "  SAT"}; // dimanche d'abord, cf manuel du w15 chap 9-11

// Les mois
// On part de 1 pour être en compatibilité avec les variables bas niveau du seiko
char mois[13][5]=
{"-----", "  JAN", "  FEB", "  MAR", "  APR", "  MAY", "  JUN", "  JUL", "  AUG", "  SEP", "  OCT", "  NOV", "  DEC"};
// commence par 1 au lieu de 0 car c'est
// pour rester compatible avec le temps interne au seiko si on veut y revenir

// Le texte à afficher lors du reglage 12H/24H
char texte24HMode[2][5] = {"  12H", "  24H"};

// La longueur des mois
unsigned char longueursDesMois[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//l'ordre dans lequel s'enchainent les modes de réglages de la montre est défini dans ce tableau.
unsigned char suivantMontre[9];

/////////////////////

// Permet le passage de 12H a 24H en mode de reglage de ce parametre
// On ne peut pas juste utiliser augmenterVarAff(&currentVarAff) comme dans les autres modes de reglages
// car ici il n'y a pas seulement un texte à modifier mais aussi un symbole
// (--> cas particulier, tout comme la variable bluetoothMode)
void commentAfficher24HMode(){//unsigned char a, unsigned char b, unsigned char n){
#ifdef NEW_SCREEN
	setSymbole(SYMBOL_INDEX_24HMODE,watch.shortTime.is24HMode.nb);
	if(mode == WATCH_24HMODE)
		afficherTexteSur14Seg(&(texte24HMode[0][0])
				+5*watch.shortTime.is24HMode.nb,
				0);
#endif
}

// Ici on place juste dans l'écran "abstrait" la variable lors du mode de réglage du mode 12H/24H
// Mais on ne l'affiche pas sur l'écran réel
void commentPlacerDansEcran24HMode(){
#ifdef NEW_SCREEN
	if(mode == WATCH_24HMODE){
		ecran.aff14Seg[0].type=SPECIAL3_14;
	}
	mettreSurEcranPasForceSymbole(SYMBOL_INDEX_24HMODE, &(watch.shortTime.is24HMode.nb), 0);
#endif
}


/////////////////////////////////////////////

// A l'initialisation de la montre(fonction commence()), on appelle cette fonction qui
//  définit les varAff utiles pour la montre, comme les secondes, les heures, ...
// (leurs types, leur placement dans l'écran)
// Par exemple pour les secondes
//watch.shortTime.second.type=INT7;
//setPosInt7(&(watch.shortTime.second),1,1,1);
// signifie que la variable sera affichée sur des 7 segments, en bas à droite, et qu'elle sera forcée à deux chiffres,
// même si elle vaut strictement moins que 10.
void initConstantesMontre(){
	//initTime(&watch);

	watch.activated.type=BOOL;
	setPosBool(&(watch.activated), SYMBOL_INDEX_ALARM, 0, 0);

	watch.dayOfMonth.type=INT14;
	setPosInt14(&(watch.dayOfMonth),1,1);

	watch.dayOfWeek.type=STR;
	setPosString(&(watch.dayOfWeek),&(jours[0][0]),0);

	watch.shortTime.hour.type=INT7;
	setPosInt7(&(watch.shortTime.hour),0,0,1); // position 0,0 ; forcé à 2 chiffres

#ifdef NEW_SCREEN
	watch.shortTime.is24HMode.type=SPECIAL3;
	//setPosString(&(watch.shortTime.is24HMode),&(texte24HMode[0][0]),0);
#else
	watch.shortTime.is24HMode.type=STR;
	setPosString(&(watch.shortTime.is24HMode),&(texte24HMode[0][0]),0);
#endif

	watch.shortTime.minute.type=INT7;
	setPosInt7(&(watch.shortTime.minute),1,0,1);

	watch.month.type=STR;
	setPosString(&(watch.month),&(mois[1][0]),0);

#ifdef NEW_SCREEN
	watch.shortTime.pm.type=BOOL;
	setPosBool(&(watch.shortTime.pm), SYMBOL_INDEX_PM, 0, 0);
#else
	watch.shortTime.pm.type=BOOL;
	setPosBool(&(watch.shortTime.pm), SYMBOL_INDEX_PM, SYMBOL_INDEX_AM, 1);
#endif

	watch.shortTime.second.type=INT7;
	setPosInt7(&(watch.shortTime.second),1,1,1);

	watch.year.type=INT14;
	setPosInt14(&(watch.year),1,1);

	setBounds(&deuxPointsSecondes,0,1,1);
	deuxPointsSecondes.type=BOOL;
	//deuxPointsSecondes.contenu.boolAff.index=SYMBOL_INDEX_2PTS2;
	setPosBool(&deuxPointsSecondes, SYMBOL_INDEX_2PTS2, 0, 0);

	suivantMontre[WATCH & MASQUE_SUB]=WATCH_HOUR;
	suivantMontre[WATCH_HOUR & MASQUE_SUB]=WATCH_MINUTE;
	suivantMontre[WATCH_MINUTE & MASQUE_SUB]=WATCH_SECOND;
	suivantMontre[WATCH_SECOND & MASQUE_SUB]=WATCH_WEEK;
	suivantMontre[WATCH_WEEK & MASQUE_SUB]=WATCH_DAY;
	suivantMontre[WATCH_DAY & MASQUE_SUB]=WATCH_MONTH;
	suivantMontre[WATCH_MONTH & MASQUE_SUB]=WATCH_YEAR;
	suivantMontre[WATCH_YEAR & MASQUE_SUB]=WATCH_24HMODE;
	suivantMontre[WATCH_24HMODE & MASQUE_SUB]=WATCH;
}

// Ici c'est une fonction qui est appelée dès qu'on entre dans le mode WATCH, ou un de ses subModes.
// Elle va placer les bonnes varAff à l'écran avec la fonction placerDansEcran,
// et elle va aussi activer les booléens "toDisplayIfChanged" des varAff de la montre (secondes, minutes, ...) .
void prepareDisplayMontre(){
//	if(mode == modePrincipal(mode)){
//	// on affiche le symbole bluetooth si on est connecté
//		commentPlacerDansEcranBlMode(&bluetoothMode);
//	}

	// en revenant à la montre, on efface le 20 de 2014, car il ne fait partie d'aucun VarAff
	if(avantChangementMode == WATCH_YEAR){
		effacer14Seg(1,1);
		effacer14Seg(1,2);
	}

#ifdef NEW_SCREEN
	placerDansEcran(&(watch.shortTime.is24HMode));
#endif

	placerDansEcran(&(deuxPointsSecondes));
	mettreAuClignotementVarAff(&(deuxPointsSecondes));

	placerDansEcran(&(watch.activated));
	placerDansEcran(&(watch.shortTime.hour));
	placerDansEcran(&(watch.shortTime.minute));
	placerDansEcran(&(watch.shortTime.second));
	if(! watch.shortTime.is24HMode.nb){
		placerDansEcran(&(watch.shortTime.pm));
	}
	if(mode == WATCH_24HMODE)
		watch.shortTime.pm.toDisplayIfChanged=1;

	if(mode != WATCH_YEAR && mode != WATCH_MONTH && mode != WATCH_24HMODE){
		placerDansEcran(&(watch.dayOfMonth));
		placerDansEcran(&(watch.dayOfWeek));
	} else if(mode == WATCH_YEAR || mode == WATCH_MONTH){
		placerDansEcran(&(watch.year));
		placerDansEcran(&(watch.month));
		afficherChiffreSur14Seg(1, 1, 2); // 2 de 2014
		afficherChiffreSur14Seg(1, 2, 0);	// 0 de 2014
	}else {// if mode == watch24Hmode
		placerDansEcran(&(watch.shortTime.is24HMode));
	}
}

// Cette fonction sert pendant le réglage de l'heure.
// On va utiliser les varAff contenue dans la structure Time pour faire les modifs ,
// puis on va immédiatement les transférer dans les registres du real-time clock
// C'est plus simple que le faire directement sur les registres car tout est géré rigoureusement dans la structure Time.
void putAbstractTimeInHardwareTimeSmall(){
//	setRtcaAlarmHour( t->shortTimeAlarm.hour.nb );
//	setRtcaAlarmMinute( t->shortTimeAlarm.minute.nb );
//	setRtcaAlarmIndicator( t->shortTimeAlarm.pm.nb );
//	RTCINTF_ALARMIF = 1;
//	RTCINTE_ALARMIE = t->activated.nb;

	switch(mode){
	case WATCH_24HMODE:
		setRtca24hMode(  watch.shortTime.is24HMode.nb );
		break;
	case WATCH_YEAR:
		setRtcaYear( watch.year.nb );
		break;
	case WATCH_MONTH:
		setRtcaMonth( watch.month.nb );
		break;
	case WATCH_DAY:
		setRtcaDay( watch.dayOfMonth.nb );
		break;
	case WATCH_WEEK :
		setRtcaWeek( watch.dayOfWeek.nb );
		break;
	case WATCH_HOUR:
		setRtcaHour( watch.shortTime.hour.nb  );
		setRtcaIndicator( watch.shortTime.pm.nb );
		break;
	case WATCH_MINUTE:
		setRtcaMinute( watch.shortTime.minute.nb );
		break;
	case WATCH_SECOND:
		setRtcaSecond( watch.shortTime.second.nb );
		break;
	}
}

// Ici la montre choisit les actions à réaliser en fonctions du clic que l'utilisateur a fait.
void actionModeWatch(unsigned char typeEvenement){
	switch(mode){
	case WATCH:
		switch(typeEvenement){
		case BOUTON1COURT:
			lightOn();
			break;
		case BOUTON4COURT:
			mettreMode(ALARM);
			break;
		case BOUTON1LONG:
			mettreMode(WATCH_HOUR);
			break;
		}
			break;

		case WATCH_SECOND:
				switch(typeEvenement){
				case BOUTON2COURT:
				case BOUTON3COURT:
					//RTCCTL_RTCRUN = 0;
					RTCCTL_RTCRST=1;
					setVarAffValue(&watch.shortTime.second, 0);
					putAbstractTimeInHardwareTimeSmall();
					//RTCCTL_RTCRUN = 1;
					break;
				case BOUTON1COURT:
					if(suivantMontre[mode & MASQUE_SUB] == WATCH){
						putAbstractTimeInHardwareTime(&watch);
					}
					mettreMode(suivantMontre[mode & MASQUE_SUB]);
					break;
				case BOUTON4COURT:
					putAbstractTimeInHardwareTime(&watch);
					mettreMode(WATCH);//modePrincipal(mode));
					break;
				}
		break;

	default :
		switch(typeEvenement){
		case BOUTON2COURT:
			if(mode == WATCH_24HMODE)
				changeAll24HMode();
			else if(mode == WATCH_HOUR)
				augmenteHeures(&watch.shortTime,0); // pour le changement am/pm si necessaire
			else
				augmenterVarAff(currentVarAff);
			putAbstractTimeInHardwareTimeSmall();
			break;
		case BOUTON3COURT:
			if(mode == WATCH_24HMODE)
				changeAll24HMode();
			else if(mode == WATCH_HOUR)
				diminueHeures(&watch.shortTime,0);  // pour le changement am/pm si necessaire
			else
				diminuerVarAff(currentVarAff);
			putAbstractTimeInHardwareTimeSmall(&watch);
			break;
		case BOUTON1COURT:
			if(suivantMontre[mode & MASQUE_SUB] == WATCH){
				putAbstractTimeInHardwareTime(&watch);
			}
			mettreMode(suivantMontre[mode & MASQUE_SUB]);
			break;
		case BOUTON4COURT:
			putAbstractTimeInHardwareTime(&watch);
			mettreMode(WATCH);//modePrincipal(mode));
			break;
		}
		break;

	}
}



