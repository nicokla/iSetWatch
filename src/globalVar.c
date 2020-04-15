/***********************
 * Ce fichier contient la fonction mettreMode(unsigned char m).
 * Il contient aussi la fonction d'initialisation commence().
 **************************/
#include "boot.h"
#include "stdlib.h"
#include "globalVar.h"
#include "string.h"
#include "init.h"

#include "ecranPourClignotements.h"
#include "varAff.h"
#include "fileDActions.h"

#include "interruptTime.h"
#include "interruptBoutons.h"

#include "lcd8a.h"
#include "clg.h"
#include "buzzer.h"
#include "backlight.h"
#include "t16_ch0_smallDelays.h"
#include "t16_ch2_appuiLongBouton.h"
#include "t16b_ch0_doubleAppui.h"
#include "t16b_ch1_verySmallDelays.h"

#include "bluetooth.h"
#include "tennis.h"
#include "compteur.h"
#include "uart.h"
#include "alarm.h"
#include "chrono.h"
#include "watch.h"
#include "test.h"
#include "t16_ch1_countdown.h"
#include "wdt.h"

///////////////////////////////////////////

// Tentative pour voir la valeur des variables cachées de malloc
// En pratique quand j'ai fait un "Add expression" ça a arrêté le debug, donc impossible
// de voir les valeurs. --> parce qu'elles sont dans un fichier précompilé par Epson et non un fichier source
//extern unsigned char *ansi_ucStartAlloc;   /* allocate area, start address */
//extern unsigned char *ansi_ucEndAlloc;     /* allocate area, end address   */
//extern unsigned char *ansi_ucNxtAlcP;      /* next allocate address        */
//extern unsigned char *ansi_ucTblPtr;       /* next address for table       */
//extern unsigned long ansi_ulRow;           /* table count   */


// advantageChar sert a afficher Ad quand il y a advantage lors du match de tennis
unsigned char advantageChar[2] = {0x77, 0x1F}; // Ad pour 7 seg, deja dans nb7seg
char noYes[2][5] = {"   NO", "  YES" };

// le decalage (taille de MASQUE_SUB).
// Si il est mauvais, sera de toute façon calculé dans initSuivants
// --> A utiliser seulement si on veut changer la gestion des modes et/ou factoriser le code différemment
// Pour l'instant, on utilise seulement MASQUE_PRINCIPAL et MASQUE_SUB
// cf globalVar.h
//unsigned char decalage=DECALAGE;

// Le mode de la montre
unsigned char mode = WATCH;
// Le mode avant le dernier changement de mode
unsigned char avantChangementMode = WATCH;

// variable servant pendant les réglages, c'est elle qu'on augmente ou diminue avec s2 et s3
// cf fonction designeVariableSiModeDeReglage, puis dans les actionModes...
// par exemple dans actionModeWatch, dans le case default (tous les modes sauf WATCH et WATCH_SECOND)
// l'appuis sur S2 fait : augmenterVarAff(currentVarAff);
// ce qui permet de factoriser le code pour les modes de réglage
VarAff * currentVarAff;

// Variable expliquant que WATCH est suivi par ALARM, qui est suivi par CHRONO, etc.
// Bien initialisée (dans initSuivants()) mais pas utilisée systématiquement dans la pratique
// --> pourrait être supprimée par la suite, mais je l'ai gardé au cas où on voudrait factoriser un peu plus le code
//unsigned char suivantModePrincipal[8];

// Variable visant les tableaux qui décrivent l'enchainement des sous-modes (par exemple
// pour watch, le réglage des heures, puis des minutes, puis des secondes, etc.)
// Bien initialisée (dans initSuivants()) mais pas utilisé dans la pratique
// --> pourrait être supprimée par la suite, mais je l'ai gardé au cas où on voudrait factoriser un peu plus le code
//unsigned char * suivantSubModes[8];

// une eventuelle idée pour changer la façon dont est gérée sauvegardeMode(),
// c-a-d la sauvagarde du subMode, qui en pratique ne sert que pour le chrono et le tennis.
// --> pourrait être supprimée par la suite, mais je l'ai gardé au cas où on voudrait factoriser un peu plus le code
//unsigned char sauvegardeSubModes[8];

// Dynamic allocation boundaries
// END_data = approximately 0xD00
// lastAdress is supposed to be maximum 0xFBF
// En pratique ça marche à 0xE80
// --> voir defines dans globalVar.h pour remplacer ça
//unsigned long firstAdressOccupiedForDynamicAllocation = (unsigned long)&__END_data + (unsigned long)1;
//unsigned long lastAdressOccupiedForDynamicAllocation = (unsigned long)0xE80;

///////////////////////////////////////////

// Cette fonction initialise tout au démarrage de la montre
// a = 1 ssi on initialise l'heure et l'alarme
void commence(unsigned char a){
	// pour debug
	dbrun(); // utile seulement quand on debug la montre

	initBacklight();
	initP0(); // boutons

	// Osc1
	startClgOSC1();
	switchClgSystemClockOSC1();
	stopClgIOSC();

	//lcd
	initSymbolesPositions(); // tres important, definit les zones ou sont les pins relies aux segments du lcd
	initLcd8a();
	onLcd8aDisplay();
	viderEcran();
	clearLcd( );

	initT16Ch0(); // timer pour attentes petites
	initT16Ch1();
	initT16Ch2();
	initT16bCh0();
	initT16bCh1();
	initCompteurSecondes();

	init_bz(); // bip-bips

	// Fonction abandonnée mais on la garde en commentaire au cas où on voudrait
	// factoriser d'avantage le code par la suite :
//	initSuivants();

	initChrono(); // chrono
	initConstantesCountDown();
	initTennis();
	initCompteur();
	initConstantesTest();
	initConstantesBluetooth();

	// Uart and bluetooth
	initFout();
	initDiversBluetooth();
	wait_s();

	initUart() ;
	startUart();
	reset_radio();

	if(a){
		initTime(&watch);
	}
	initConstantesMontre();
	initConstantesAlarme();

	// test --> no finally safer, on laisse le memset
//	wait_general(1000);
//	memset((void *)INIT_MALLOC_START, 0x00, //(unsigned int)(0xFB3 - INIT_MALLOC_START) + 1);
//			(unsigned int)(INIT_MALLOC_END - INIT_MALLOC_START) + 1);
//	wait_general(1000);
	// end test

//	ansi_InitMalloc(INIT_MALLOC_START,	INIT_MALLOC_END);
	// less than 0xFBF !!! (S1C17W15 technical manual not ok)
	// 0xE80
	// (unsigned long)&__END_data+0x101);

	initFileDActions(&fileDActions);

#ifdef MODE_DEBUG_BLUETOOTH
	//bluetoothMode==BL_COMPTEUR; // BL_PARTNER
	mettreMode(TENNIS);
#else
	mettreMode(WATCH);
#endif

	// init le watch dog timer
#ifdef WATCH_DOG_ACTIF
	initWdt();
#endif

	// on lance les interruptions de temps le plus tard possible pour ne pas avoir de pb
	demarreTemps();

	// start le watch dog timer
#ifdef WATCH_DOG_ACTIF
	startWdt();
#endif
}


// Cette fonction active des registres permettant d'avoir les circuits du seiko actifs lors des debugs.
void dbrun(void){
	WDTCLK_DBRUN=1;
	SVDCLK_DBRUN=1;
	T16_0CLK_DBRUN	=1;
	T16_1CLK_DBRUN=1;
	T16_2CLK_DBRUN=1;
	PCLK_DBRUN=1;
	UA0CLK_DBRUN=1;
	UA1CLK_DBRUN=1;
	I2C0CLK_DBRUN=1;
	T16B0CLK_DBRUN=1;
	T16B1CLK_DBRUN=1;
	SNDCLK_DBRUN=1;
	LCD8CLK_DBRUN=1;
	RFC0CLK_DBRUN=1;
	RFC1CLK_DBRUN=1;
	RFC2CLK_DBRUN=1;
	RFC3CLK_DBRUN=1;
}

// Permet de détecter si deux modes ont le même mode principal
unsigned char brothersModes(unsigned char a, unsigned char b){
	return ((a & MASQUE_PRINCIPAL) == (b & MASQUE_PRINCIPAL));//a>>5 == b>>5 );
}

// Fonction initialisant les transitions entre modes principaux
// et les pointeurs vers les tableaux des transitions entre subModes
// Fonction à décommenter et utiliser si on veut encore davantage factoriser le code.
//void initSuivants(){
//	unsigned char i=MASQUE_SUB;
//
//	decalage=0;
//	while(i>0){
//		i = i>>1;
//		decalage++;
//	}
//	suivantModePrincipal[WATCH >> decalage] = ALARM ;
//	suivantModePrincipal[ALARM >> decalage] = STOPWATCH_PAUSE ;
//	suivantModePrincipal[STOPWATCH_PAUSE >> decalage] = COUNTDOWN ;
//	suivantModePrincipal[COUNTDOWN >> decalage] = TENNIS ;
//	suivantModePrincipal[TENNIS >> decalage] = COMPTEUR ;
//	suivantModePrincipal[COMPTEUR >> decalage] = WATCH ;
//
//	suivantSubModes[WATCH >> decalage]=&(suivantMontre[0]);
//	suivantSubModes[ALARM >> decalage]=&(suivantAlarme[0]);
//	suivantSubModes[COUNTDOWN >> decalage] = &(suivantCountDown[0]);
//	suivantSubModes[TENNIS >> decalage]=&(suivantTennis[0]);
//}

// Retourne le mode principal d'un mode. Par exemple si on est dans le reglage des minutes, c-a-d
// le mode WATCH_MINUTE == 0x02, ça va nous renvoyer WATCH
// en faisant un masque avec MASQUE_PRINCIPAL == 0xE0.
unsigned char modePrincipal(unsigned char m){
	switch(m){
	case STOPWATCH_RUN :
	case STOPWATCH_LAP :
	case TENNIS_CHANGE_SIDE :
	case TENNIS_TIE_BREAK :
	case TENNIS_STB:
	case TENNIS_END :
	case TEST_BL :
		return m;
		break;
	default :
		return (m & MASQUE_PRINCIPAL);
		break;
	}
	return (m & MASQUE_PRINCIPAL); // default
}


// utile pour tennis et chrono uniquement où on veut
// que le subMode soit accessible au cas où on quitte le mode
// puis qu'on y revient
void sauvegardeMode(){
	switch(mode){
		case TENNIS_END:
		case TENNIS_CHANGE_SIDE:
		case TENNIS_TIE_BREAK:
//		case TENNIS_STB :
		case TENNIS:
			tennisMode[0] = mode-TENNIS;
		break;
		case STOPWATCH_PAUSE:
		case STOPWATCH_RUN:
		case STOPWATCH_LAP:
			chronoMode.toDisplayIfChanged=0;
			setVarAffValue(&chronoMode,mode-STOPWATCH_PAUSE);
		break;
	}
}

// Permet de mettre dans currentVarAff la bonne variable (NULL si on est pas dans un mode de reglage,
// sinon la variable a regler).
void designeVariableSiModeDeReglage(){
	// on clear l'ancienne
	currentVarAff=NULL;

	// on designe si on est dans un mode de reglage la nouvelle
	switch(mode){
	case WATCH_HOUR:
		currentVarAff=&(watch.shortTime.hour);
		break;
	case WATCH_MINUTE:
		currentVarAff=&(watch.shortTime.minute);
		break;
	case WATCH_SECOND:
		currentVarAff=&(watch.shortTime.second);
		break;
	case WATCH_WEEK:
		currentVarAff=&(watch.dayOfWeek);
		break;
	case WATCH_DAY:
		currentVarAff=&watch.dayOfMonth;
		break;
	case WATCH_MONTH:
		currentVarAff=&watch.month;
		break;
	case WATCH_YEAR:
		currentVarAff=&watch.year;
		break;
	case WATCH_24HMODE:
		currentVarAff=&watch.shortTime.is24HMode;
		break;

	case ALARM_MINUTE:
		currentVarAff=&(watch.shortTimeAlarm.minute);
		break;
	case ALARM_HOUR:
		currentVarAff=&(watch.shortTimeAlarm.hour);
		break;

	case COUNTDOWN_HOUR:
		currentVarAff=&countDownNow.hour;
		break;
	case COUNTDOWN_MINUTE:
		currentVarAff=&countDownNow.minute;
		break;
	case COUNTDOWN_SECOND:
		currentVarAff=&countDownNow.second;
		break;

	case TENNIS_SETTING_INITIAL_SERVER:
		currentVarAff=&jeSuisAuService0;
		break;
	case TENNIS_SETTING_NB_GAME_PER_SET:
		currentVarAff=&nbJeuxGagnantsUneManche;
		break;
	case TENNIS_SETTING_NB_SET_PER_MATCH:
		currentVarAff=&nbManchesGagnantes;
		break;
	case TENNIS_SETTING_ADVANTAGE:
		currentVarAff=&avantageActive;
		break;
	case TENNIS_SETTING_TIE_BREAK:
		currentVarAff=&tbActive;
		break;
	case TENNIS_SETTING_SUPER_TIE_BREAK:
		currentVarAff=&stbActive;
		break;
	case TENNIS_SETTING_TIE_BREAK_TYPE:
		currentVarAff=&tbType;
		break;

	case TENNIS_SETTING_BLUETOOTH:
		currentVarAff=&bluetoothMode;
		break;

  case TEST_BL:
  	currentVarAff=&freqTestBl;
  	break;

//  case OAD_CHOICE:
//  	currentVarAff=&shouldStartOad;
//		break;

//  default :
//  	currentVarAff=NULL;
//  	break;
	}

	// si on en a designé une on la fait clignoter
	if(currentVarAff != NULL){
		mettreAuClignotementVarAff(currentVarAff);
		currentVarAff->toDisplayIfChanged=1;
	}

}

// Quand on quitte les modes alarm, watch, chrono et countdown, il faut que le passage du temps
// ne soit plus affiché à l'écran. On mets donc à zéro les booléens toDisplayIfChanged des variables varAff
// concernees . Cette fonction est appelée dans mettreMode.
void prepareEndOfDisplay(unsigned char m){
	// surtout garder bluetoothMode avec toDisplayIfChanged à 1 ! --> comme ça reset_radio() automatique, cf
	// fonction setVarAffValue --> displayIfNecessary --> afficherVarAff --> commentAfficherBlMode
	unsigned char modePrincipalAncien = modePrincipal(m);

	switch(modePrincipalAncien){
	case WATCH:
		desactiverDisplayTime(&watch);
		deuxPointsSecondes.toDisplayIfChanged=0;
		break;
	case ALARM:
		desactiverDisplayTime(&watch);
		break;
	case COUNTDOWN:
		desactiverDisplayTimeShort(&countDownNow);
		deuxPointsSecondes.toDisplayIfChanged=0;
		break;
	case STOPWATCH_PAUSE:
	case STOPWATCH_RUN:
	case STOPWATCH_LAP:
		desactiverDisplayTimeShort(&chrono);
		deuxPointsSecondes.toDisplayIfChanged=0;
		break;
	}

	if(avantChangementMode == OAD_UPDATING && mode != OAD_UPDATING)
		stopSecondsInterrupts();
}

// Dans certaines transitions de modes, le buzzer doit sonner une ou plusieurs fois.
// Ceci est géré par cette fonction.
void buzzIfNecessary(){
	// petit ou grand bip
	if(mode==WATCH)
		out_bz_long();
	else if (mode == modePrincipal(mode) && ( ! brothersModes(mode, avantChangementMode) ) ){
		// si le mode d'arrivee est principal, autre que watch, et pas frere du mode de depart, on bip short
		out_bz_short();
	}
	if(mode == TENNIS_END && modePrincipal(avantChangementMode) == TENNIS)
		bipBip(3);
}

// Fonction réalisant les transitions entre les modes
void mettreMode(unsigned char m){
	avantChangementMode = mode;

	/////////////////////
	mode = m;

	buzzIfNecessary();
	sauvegardeMode();

	// on vide puis rempli l'ecran abstrait (non hardware)
	viderEcran();
	prepareEndOfDisplay(avantChangementMode); // on desactive les "toDisplayIfChanged" de l'ancien mode

	prepareDisplay();
	commentPlacerDansEcranBlMode(); // on affiche toujours le symbole bluetooth si necessaire

	// doit etre appele apres viderEcran, car la variable en cours de reglage doit clignoter
	designeVariableSiModeDeReglage();

	// on efface l'ancien ecran hardware, puis on affiche le nouvel ecran hardware
	// a partir du contenu de l'ecran abstrait
	if(! brothersModes(mode,avantChangementMode)){
		clearLcd();
	}
	afficheEcranAll();
}

// La fonction prepareDisplay est la fonction appelée à chaque fois qu'on entre dans un mode.
// Les fonctions appelées via prepareDisplay servent principalement à préparer l'affichage
// (ce pour quoi prepareDisplay a été créé au départ), mais pas uniquement en fait.
void prepareDisplay(){
	unsigned char a=modePrincipal(mode);
	switch(a){
	case WATCH:
		prepareDisplayMontre();
	break;
	case ALARM:
		prepareDisplayAlarme();
	break;
	case STOPWATCH_PAUSE:
	case STOPWATCH_RUN :
	case STOPWATCH_LAP :
		prepareDisplayChrono();
	break;
	case COUNTDOWN:
		prepareDisplayCountDown();
	break;
	case TENNIS:
	case TENNIS_CHANGE_SIDE :
	case TENNIS_TIE_BREAK :
	case TENNIS_STB :
	case TENNIS_END :
		prepareDisplayTennis(mode);
	break;
	case COMPTEUR:
		prepareDisplayCompteur();
	break;
	case TEST_BL:
		prepareDisplayTestBl();
	break;
	}
}


// Permet d'attendre un certain nombre de millisecondes
// Maximum : signed int --> 2^15-1 = 32767 --> 32767/4 = un peu plus de 8000ms = 8s
void wait_general(int a){
	int i,j;
//	for (i = 0; i < a ; i++) {
//		for(j=0; j < 16; j++){ }
//		// 1ms = 32 * 1 / 32000 s, because frequency is 32000Hz with CLK1
//		// but each cycle has two operations : compare, increment, so 16 and not 32
//	}
	for (i = 0; i <= a; i++) { /* 1sec */
		for (j = 0; j <= 5; j++) { /* 1msec */
			j++;
		};
		i++;
	};
}

// Permet d'attendre 200 millisecondes (s pour short)
void wait_s(){
	wait_general(200);
}

// Permet d'attendre une demi-seconde (m pour middle ou mean)
void wait_m(){
	wait_general(500);
}

// Permet d'attendre 1 seconde (l pour long)
void wait_l(){
	wait_general(1000);
}


