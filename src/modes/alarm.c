#include "globalVar.h"
#include "lcd8a.h"
#include "time.h"
#include "ecranPourClignotements.h"
#include "varAff.h"
#include "interruptBoutons.h"
#include "chrono.h"
#include "buzzer.h"
#include "backlight.h"
#include "watch.h"

//ShortTime alarme;
unsigned char suivantAlarme[3];

// initialisation
void initConstantesAlarme(){
	//initTime(&alarme);

	watch.shortTimeAlarm.hour.type=INT7;
	setPosInt7(&(watch.shortTimeAlarm.hour),0,0,1); // position 0,0 ; forcé à 2 chiffres

	watch.shortTimeAlarm.minute.type=INT7;
	setPosInt7(&(watch.shortTimeAlarm.minute),1,0,1);

#ifdef NEW_SCREEN
	watch.shortTimeAlarm.pm.type=BOOL;
	setPosBool(&(watch.shortTimeAlarm.pm), SYMBOL_INDEX_PM, 0, 0);
#else
	watch.shortTimeAlarm.pm.type=BOOL;
	setPosBool(&(watch.shortTimeAlarm.pm), SYMBOL_INDEX_PM, SYMBOL_INDEX_AM, 1);
#endif

	watch.activated.type=BOOL;
	setPosBool(&(watch.activated), SYMBOL_INDEX_ALARM, 0, 0);

	suivantAlarme[ALARM & MASQUE_SUB]=ALARM_HOUR;
	suivantAlarme[ALARM_HOUR & MASQUE_SUB]=ALARM_MINUTE;
	suivantAlarme[ALARM_MINUTE & MASQUE_SUB]=WATCH;
}

// entrée dans le mode : on prépare l'écran, etc.
void prepareDisplayAlarme(){
	placerDansEcran(&(watch.activated));
	placerDansEcran(&(watch.shortTimeAlarm.hour));
	placerDansEcran(&(watch.shortTimeAlarm.minute));
	if(! watch.shortTimeAlarm.is24HMode.nb){
		placerDansEcran(&(watch.shortTimeAlarm.pm));
	}

	//afficherTexteSur14Seg("ALARM", 0);
	mettreSurEcranTexte(0, "ALARM");
//	if(mode != ALARM)
//		mettreSurEcranTexte(1, "  SET");
}

// action a faire renvoie 1 ssi l'alarme doit se declencher
unsigned char alarmeDeclenchee(){
	return
	(watch.shortTime.hour.nb == watch.shortTimeAlarm.hour.nb) &&
	(watch.shortTime.minute.nb == watch.shortTimeAlarm.minute.nb) &&
	(watch.shortTime.second.nb==0)	&&
	watch.activated.nb;
}

// action à réaliser en mode alarme
void actionModeAlarm(unsigned char typeEvenement){

	if(mode != ALARM){
		switch(typeEvenement){
		case BOUTON2COURT:
			if(mode == ALARM_HOUR)
				augmenteHeures(&watch.shortTimeAlarm,0);  // pour le changement am/pm si necessaire
			else
				augmenterVarAff(currentVarAff);
			break;
		case BOUTON3COURT:
			if(mode == ALARM_HOUR)
				diminueHeures(&watch.shortTimeAlarm,0);  // pour le changement am/pm si necessaire
			else
				diminuerVarAff(currentVarAff);
			break;
		case BOUTON1COURT:
			if(suivantAlarme[mode & MASQUE_SUB]==WATCH){
				setVarAffValue(&watch.activated,1);
				bipBip(2);
			}
			mettreMode(suivantAlarme[mode & MASQUE_SUB]);
			break;
		case BOUTON4COURT:
			setVarAffValue(&watch.activated,1);
			bipBip(2);
			mettreMode(WATCH);
			break;
		}
	}

	else{ // if (mode == ALARM)
		switch(typeEvenement){
		case BOUTON1COURT:
			lightOn();
			break;
		case BOUTON2COURT:
		case BOUTON3COURT:
			augmenterVarAff(&watch.activated);
			if(watch.activated.nb){
				bipBip(2);
			} else {
				out_bz();
			}
			break;
		case BOUTON4COURT:
			mettreMode(STOPWATCH_PAUSE+chronoMode.nb);
			break;
		case BOUTON1LONG:
			mettreMode(suivantAlarme[mode & MASQUE_SUB]);
			break;
		}
	}
}

