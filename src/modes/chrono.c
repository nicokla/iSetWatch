#include "modes/chrono.h"
#include "class/time.h"
#include "globalVar.h"
#include "init.h"
#include "lcd8a.h"
#include "interruptBoutons.h"
#include "buzzer.h"
#include "backlight.h"
#include "class/ecranPourClignotements.h"
#include <string.h>

char texteChrono[3][5]={" STOP", "     ", "  LAP"};
VarAff chronoMode;
ShortTime chrono;

// Fonction d'initialisation du chronomètre
void initChrono(void){
	RTCSWCTL_SWRUN=0;

	RTCSWCTL_BCD10 = 0;
	RTCSWCTL_BCD100 = 0;

	RTCINTF_SW100IF=1;
	RTCINTF_SW10IF=1;
	RTCINTF_SW1IF=1;
	RTCINTE_SW100IE=1;
	RTCINTE_SW10IE=1;
	RTCINTE_SW1IE=1;

	initTimeShort(&chrono);

	chrono.hour.type=INT7;
	setPosInt7(&(chrono.hour),0,0,1); // position 0,0 ; forcé à 2 chiffres

	chrono.minute.type=INT7;
	setPosInt7(&(chrono.minute),1,0,1);

	chrono.second.type=INT7;
	setPosInt7(&(chrono.second),1,1,1);

	chronoMode.type=STR;
	setBounds(&chronoMode, 0, 2, 0);
	setPosString(&chronoMode,&(texteChrono[0][0]),0);

	razChrono();
}

// Ici on prepare le display du chronometre
void prepareDisplayChrono(){
	placerDansEcran(&(chrono.hour));
	placerDansEcran(&(chrono.minute));
	placerDansEcran(&(chrono.second));
	if(chronoMode.nb != STOPWATCH_RUN)
		placerDansEcran(&(chronoMode));

	ecran.aff14Seg[1].type=LETTRES;
	memset(ecran.aff14Seg[1].contenu.lettres,' ',5);
	ecran.aff14Seg[1].contenu.lettres[3]=RTCSWCTL_BCD10 +0x30; // conversion en char
	ecran.aff14Seg[1].contenu.lettres[4]=RTCSWCTL_BCD100 +0x30; // conversion en char

	chronoMode.toDisplayIfChanged=1;
	if(mode == STOPWATCH_LAP){
		chrono.hour.toDisplayIfChanged=0;
		chrono.minute.toDisplayIfChanged=0;
		chrono.second.toDisplayIfChanged=0;
	}
}

// remise a zero du chronometre
void razChrono(){
	setVarAffValue(&chrono.hour,0);
	setVarAffValue(&chrono.minute,0);
	setVarAffValue(&chrono.second,0);

	RTCSWCTL_SWRST = 1; // attention cette ligne annule probablement les interruptions des 10emes et des 100emes de secondes
	RTCSWCTL_BCD10 = 0;
	RTCSWCTL_BCD100 = 0;
	RTCINTE_SW100IE=1;
	RTCINTE_SW10IE=1;
	RTCINTE_SW1IE=1;
}

// depart du chronometre
void startChrono(){
	setVarAffValue(&chronoMode, STOPWATCH_RUN -  STOPWATCH_PAUSE);

	RTCINTF_SW100IF=1;
	RTCINTF_SW10IF=1;
	RTCINTF_SW1IF=1;
	RTCINTE_SW100IE=1;
	RTCINTE_SW10IE=1;
	RTCINTE_SW1IE=1;
	RTCSWCTL_SWRUN=1 ;
}

// Actions à réaliser lors d'un clic si on est en mode chronometre
void actionModeChrono(unsigned char typeEvenement){
	switch(mode){
	case STOPWATCH_PAUSE :
		switch(typeEvenement){
		case BOUTON2COURT:
			mettreModeRunFaster();
		break;
		case BOUTON3COURT:
			out_bz_short();
			// debut bricolage
			ecran.aff14Seg[1].contenu.lettres[3]=0+0x30;
			ecran.aff14Seg[1].contenu.lettres[4]=0+0x30;
			afficher14Seg(1);
			// fin bricolage
			razChrono();
		break;
		case BOUTON4COURT:
			// Plus utilisé mais on le garde au cas où on voudrait davantage factoriser le code :
//			mettreMode(suivantModePrincipal[mode>>decalage]);
			mettreMode(COUNTDOWN);
		break;

		case BOUTON4AFTEROTHER:
			mettreMode(WATCH);
		break;
		case BOUTON1COURT:
			lightOn();
		break;

		}
	break;

	case STOPWATCH_RUN :
		switch(typeEvenement){
		case BOUTON2COURT:
			mettreModePauseFaster();
		break;
		case BOUTON3COURT:
			mettreModeLapFaster();
		break;
		case BOUTON4COURT:
			mettreMode(COUNTDOWN);
		break;
		case BOUTON4AFTEROTHER:
			mettreMode(WATCH);
		break;
		case BOUTON1COURT:
			lightOn();
		break;
		}
	break;

	case STOPWATCH_LAP :
		switch(typeEvenement){
		case BOUTON2COURT:
			mettreModePauseFaster();
		break;
		case BOUTON3COURT:
			mettreModeLapFaster();
		break;
		case BOUTON4COURT:
			mettreMode(COUNTDOWN);
		break;
		case BOUTON4AFTEROTHER:
			mettreMode(WATCH);
		break;
		case BOUTON1COURT:
			lightOn();
		break;
		}
	break;
	}
}

// Permet de mettre en pause très rapidement,
// en sautant toutes les fonctions abstraites mais lentes
// On l'a fait pour que la réactivité du chrono soit meilleure
void mettreModePauseFaster(){
	RTCSWCTL_SWRUN=0 ;
	mode = STOPWATCH_PAUSE;
	//chronoMode.nb=0;//mode-STOPWATCH_PAUSE;
	setVarAffValue(&chronoMode,0);
	placerDansEcran(&(chronoMode));
	ecran.aff14Seg[1].contenu.lettres[3]=RTCSWCTL_BCD10 +0x30; // conversion en char
	ecran.aff14Seg[1].contenu.lettres[4]=RTCSWCTL_BCD100 +0x30;
	afficherChiffreSur14Seg(1,3,RTCSWCTL_BCD10);
	afficherChiffreSur14Seg(1,4,RTCSWCTL_BCD100);
	chrono.hour.toDisplayIfChanged=1; // au cas où raz
	chrono.minute.toDisplayIfChanged=1; // au cas où raz
	chrono.second.toDisplayIfChanged=1; // au cas où raz
	afficherVarAff(&(chrono.hour));
	afficherVarAff(&(chrono.minute));
	afficherVarAff(&(chrono.second));
	out_bz_short();
}

// Permet de mettre en mode lap très rapidement
void mettreModeLapFaster(){
	out_bz_short();
	mode = STOPWATCH_LAP;
	//chronoMode.nb=mode-STOPWATCH_PAUSE;
	setVarAffValue(&chronoMode,mode-STOPWATCH_PAUSE);
	placerDansEcran(&(chronoMode));
	//ecran.aff14Seg[1].contenu.lettres[3]=RTCSWCTL_BCD10 +0x30;
	//ecran.aff14Seg[1].contenu.lettres[4]=RTCSWCTL_BCD100 +0x30;
	afficherChiffreSur14Seg(1,3,RTCSWCTL_BCD10);
	afficherChiffreSur14Seg(1,4,RTCSWCTL_BCD100);
	chrono.hour.toDisplayIfChanged=0;
	chrono.minute.toDisplayIfChanged=0;
	chrono.second.toDisplayIfChanged=0;
	afficherVarAff(&(chrono.hour));
	afficherVarAff(&(chrono.minute));
	afficherVarAff(&(chrono.second));
}

// Permet de démarrer le chrono très rapidement
void mettreModeRunFaster(){
	startChrono();
	ecran.aff14Seg[0].type=RIEN;
	mode = STOPWATCH_RUN;
	setVarAffValue(&chronoMode,mode-STOPWATCH_PAUSE);
	//chronoMode.nb=mode-STOPWATCH_PAUSE;
	chrono.hour.toDisplayIfChanged=1;
	chrono.minute.toDisplayIfChanged=1;
	chrono.second.toDisplayIfChanged=1;
	out_bz_short();
}
