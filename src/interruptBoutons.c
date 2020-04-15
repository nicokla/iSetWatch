#include <string.h>
#include <stdio.h>
#include "interruptBoutons.h"
#include "globalVar.h"
#include "interruptTime.h"

#include "lcd8a.h"
#include "backlight.h"
#include "buzzer.h"
#include "t16_ch2_appuiLongBouton.h"
#include "t16_ch1_countdown.h"
#include "t16_ch0_smallDelays.h"
#include "t16b_ch0_doubleAppui.h"

#include "uart.h"
#include "bluetooth.h"
#include "compteur.h"
#include "tennis.h"
#include "chrono.h"
#include "watch.h"
#include "alarm.h"
#include "test.h"

// Lors d'un appui long sur S2 ou S3, lors d'un reglage, on fait en boucle une augmentation (ou diminution)
// de la variable. Cette tempo permet de regler la rapidite de cette augmentation (ou diminution)
#define MILLI_SECONDES_APPUI_LONG 300

//////////////////////////////
// réaction aux interruptions de type bouton


// intPortInput est la fonction de réception des interruptions de type boutons.
// Elle détecte le type d'appui et renvoie ensuite vers les fonctions appropriée selon le type d'appui
void intPortInput( void ) {
	unsigned short int portIntf;

	portIntf = P0INTF;
	// on clear les flags d'interruptions. -->
	P0INTF = portIntf;
	// --> Il peut sembler bizarre de remettre a 1 une variable y etant deja mais si on ne le fait pas l'interruption est renouvellee
	// en boucle infinie.
	// cf documentation , paragraphe 6.6, section "Px Port Interrupt Flag Register"

	SW1EDGE_BUTTON_DOWN=SW1IN_BUTTON_UP;
	SW2EDGE_BUTTON_DOWN=SW2IN_BUTTON_UP;
	SW3EDGE_BUTTON_DOWN=SW3IN_BUTTON_UP;
	SW4EDGE_BUTTON_DOWN=SW4IN_BUTTON_UP;

	if(mode==TEST){}

	else if (caSonne){
		caSonne=0;
		alarmBips5Minutes=0;
		if(estFiniCountDown()){ // ca peut aussi sonner via l'alarme.
			setVarAffValue(&countDownNow.hour,countDownMax.hour.nb); // on remet le compte a rebours au max, a zero il ne sert a rien.
			setVarAffValue(&countDownNow.minute,countDownMax.minute.nb);
			setVarAffValue(&countDownNow.second,countDownMax.second.nb);
		}
	}

	else if(! SW1IN_BUTTON_UP && ! SW2IN_BUTTON_UP && ! SW3IN_BUTTON_UP && ! SW4IN_BUTTON_UP)
		actionTousLesBoutons();

	else {
		// quel bouton ?

		// bouton 1
		if(portIntf & (0x0001 << SW1)){
			if(! SW1IN_BUTTON_UP){ // appui
				waitAndDo2(2, &bouton1AppuiLong );
			} else { // relachement
				if (T16_2CTL_PRUN) { // si c encore running, on a pas appuye assez longtemps pour un appui long, donc appui court
					stopT16Ch2();
					bouton1AppuiCourt();
				}
			}
		}

		// bouton 4
		else if(portIntf & (0x0001 << SW4)){
			if((!SW1IN_BUTTON_UP || !SW2IN_BUTTON_UP || !SW3IN_BUTTON_UP) && ! SW4IN_BUTTON_UP){
				bouton4apresAutre();
			} else {
				switch(mode){
					case TENNIS:
					case TENNIS_END:
					case OAD_UPDATING:
						if(! SW4IN_BUTTON_UP){ // appui
							waitAndDo2(2, &bouton4AppuiLong );
						} else { // relachement
							if (T16_2CTL_PRUN) { // si c encore running, on a pas appuye assez longtemps pour un appui long, donc appui court
								stopT16Ch2();
								bouton4AppuiCourt();
							}
						}
						break;
					default:
						if(! SW4IN_BUTTON_UP) // appui
							bouton4AppuiCourt();
						break;
				}
			}
		}

		// bouton 2 et 3 en meme temps, en appui (not button up = button down)
		else if(! SW2IN_BUTTON_UP && ! SW3IN_BUTTON_UP ){//(portIntf & (0x0001 << SW2)) && (portIntf & (0x0001 << SW3))){
			if (brothersModes(mode,TENNIS) || brothersModes(mode,COMPTEUR)){
				wait_t16b_ch0/*waitAndDo_t16b_ch0*/(13*20);// 2000ms
				actionBoutons2Et3();
			}
		}

		else {
		// boutons 2 isolé,  ou bouton 3 isolé, cas où on peut faire un double appui -->
		// on considere alors que remonter le bouton l'active, mais seulement si
			// �a fait suffisamment longtemps qu'on a fait un double appui
		switch(mode){
		case TENNIS:
		case TENNIS_CHANGE_SIDE:
		case TENNIS_TIE_BREAK:
		case TENNIS_STB:
		case TENNIS_END:
		case COMPTEUR:
		case COMPTEUR_RAZ:
			// si on les relâche en mm temps (appui en mm temps deja traité plus haut), on ne fait rien
			if((portIntf & (0x0001 << SW2)) && (portIntf & (0x0001 << SW3))){
			}

			// bouton 2
			if(portIntf & (0x0001 << SW2) ){ // et pas SW3 // (portIntf & (0x0001 << SW2)) && ! (portIntf & (0x0001 << SW3)
				if(! SW2IN_BUTTON_UP){ // appui
					if(sontActifsAppuisLongs2Et3())
						waitAndDo2(2, &bouton2AppuiLong );
				} else { // relachement
					if (! T16B0CTL_RUN) // si ça ne fait pas trop longtemps qu'on a fait un double appui
						bouton2AppuiCourt();
					//if(sontActifsAppuisLongs2Et3()){
						//if (T16_2CTL_PRUN)
							stopT16Ch2(); // --> si on releve avant les 2 secondes, on arrete l'attente du waitAndDo2
					//}
				}
			}

			// bouton 3
			if(portIntf & (0x0001 << SW3)){ // et pas SW2 // (portIntf & (0x0001 << SW3)) && ! (portIntf & (0x0001 << SW2)
				if(! SW3IN_BUTTON_UP){ // appui
					if(sontActifsAppuisLongs2Et3())
						waitAndDo2(2, &bouton3AppuiLong );
				} else { // relachement
					if (! T16B0CTL_RUN) // si ça ne fait pas trop longtemps qu'on a fait un double appui
						bouton3AppuiCourt();
					//if(sontActifsAppuisLongs2Et3()){
						//if (T16_2CTL_PRUN)
							stopT16Ch2();
					//}
				}
			}
		break;

		default :
			// boutons 2 isolé,  ou bouton 3 isolé, cas où on ne peut pas faire de double appui -->
			// on considere alors que cliquer vers le bas active le bouton
			// bouton 2
			if(portIntf & (0x0001 << SW2)){ // et pas SW3
				if(! SW2IN_BUTTON_UP){ // appui
					bouton2AppuiCourt();
					if(sontActifsAppuisLongs2Et3())
						waitAndDo2(2, &bouton2AppuiLong );
				} else { // relachement
					//if(sontActifsAppuisLongs2Et3()){
						//if (T16_2CTL_PRUN)
							stopT16Ch2();
					//}
				}
			}

			// bouton 3
			else if(portIntf & (0x0001 << SW3)){ // et pas SW2
				if(! SW3IN_BUTTON_UP){ // appui
					bouton3AppuiCourt();
					if(sontActifsAppuisLongs2Et3())
						waitAndDo2(2, &bouton3AppuiLong );
				} else { // relachement
					//if(sontActifsAppuisLongs2Et3()){
						//if (T16_2CTL_PRUN)
							stopT16Ch2();
					//}
				}
			}
		break;
		}

	}
	}
}


// Renvoie vers l'action à faire, qui va différer suivant le mode et le type d'évènement de clic
// (appui long ou court ou double appui, et sur quels boutons)
void faireActionEvenementMode(unsigned char typeEvenement){
	unsigned char modePrinc = modePrincipal(mode);
	switch(modePrinc){
	case WATCH:
		actionModeWatch(typeEvenement);
		break;
	case ALARM:
		actionModeAlarm(typeEvenement);
		break;
	case STOPWATCH_PAUSE:
	case STOPWATCH_RUN :
	case STOPWATCH_LAP :
		actionModeChrono(typeEvenement);
		break;
	case COUNTDOWN:
		actionModeCountdown(typeEvenement);
		break;
	case TENNIS:
	case TENNIS_CHANGE_SIDE :
	case TENNIS_TIE_BREAK :
	case TENNIS_STB :
	case TENNIS_END :
		actionModeTennis(typeEvenement);
		break;
	case COMPTEUR:
		actionModeCompteur(typeEvenement);
		break;
	case TEST_BL:
		actionModeTest(typeEvenement);
		break;
	}
}

// Traitement du cas où on a un appui court sur le bouton 1 (en haut à gauche).
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton1AppuiCourt( void ){
	faireActionEvenementMode(BOUTON1COURT);
}

// Traitement du cas où on a un appui court sur le bouton 2 (en haut à droite).
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton2AppuiCourt( void ){
	faireActionEvenementMode(BOUTON2COURT);
}

// Traitement du cas où on a un appui court sur le bouton 3 (en bas à droite).
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton3AppuiCourt(void){
	faireActionEvenementMode(BOUTON3COURT);
}

// Traitement du cas où on a un appui court sur le bouton 2 (en bas à gauche).
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton4AppuiCourt(void){
	faireActionEvenementMode(BOUTON4COURT);
}

// Traitement du cas où on a un double appui sur le bouton 2 et le bouton 3 (boutons de droites).
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void actionBoutons2Et3(){
	faireActionEvenementMode(BOUTON2ET3);
}

// Traitement du cas où on a un appui sur le bouton 4 après avoir appuyé sur un autre boutons
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton4apresAutre(){
	faireActionEvenementMode(BOUTON4AFTEROTHER);
}

// Traitement du cas où on appui sur tous les boutons --> va en mode de test
void actionTousLesBoutons(){
//	faireActionEvenementMode(BOUTON_ALL);
	stopT16Ch2();
	stopT16Ch1(); // pour eviter que le compte à rebours arrive pendant le mode
	// de test
	watch.activated.nb=0;
	// on pourrait aussi arreter le temps (et le redemarrer à la sortie du mode de test):
	//  arreteTemps() demarreTemps()
	// mais le pb de cette solution est qu'en cas de pb (evenement qui empeche de passer par l'instruction
	// demarrerTemps() ) , le temps est arrêté ce qui est très problématique

	mettreMode(TEST);
	wait_general(1000);
	setLcd8aDisplayState(LCD8A_STATE_ALL_ON);
	waitAndDo(1, &testAffichage1);
}

// Permet de dire si les appuis longs sur les boutons 2 et 3 sont activés ou pas
// Ils sont en particulier activés dans la plupart des modes de réglages :
// heures, minutes, nombre de sets du tennis  .... mais pas secondes, car la specification veux une raz des secondes
// lors d'un clic sur S2 ou S3.
unsigned char sontActifsAppuisLongs2Et3(){
	switch(mode){
	case TENNIS: // --> pour abandon
	case WATCH_HOUR:
	case WATCH_MINUTE:
	//case WATCH_SECOND:
	case WATCH_WEEK:
	case WATCH_DAY:
	case WATCH_MONTH:
	case WATCH_YEAR:
	case ALARM_HOUR:
	case ALARM_MINUTE:
	case COUNTDOWN_HOUR:
	case COUNTDOWN_MINUTE:
	case COUNTDOWN_SECOND:
		return 1;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

// Traitement du cas où on a un appui long sur le bouton 1
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton1AppuiLong(){
	faireActionEvenementMode(BOUTON1LONG);
}

// Traitement du cas où on a un appui long sur le bouton 2
// A part le cas de l'abandon en mode tennis, on execute en boucle l'appui court (pour faire un réglage plus rapide
// des minutes par exemple)
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton2AppuiLong(){
	if(mode == TENNIS){
		faireActionEvenementMode(BOUTON2LONG);//abandon();
	} else {
		while(! SW2IN_BUTTON_UP){ // tant que le bouton est appuye
			wait_general(MILLI_SECONDES_APPUI_LONG);
			bouton2AppuiCourt();
		}
	}
}

// Traitement du cas où on a un appui long sur le bouton 3
// A part le cas de l'abandon en mode tennis, on execute en boucle l'appui court (pour faire un réglage plus rapide
// des minutes par exemple)
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton3AppuiLong(){
	if(mode == TENNIS){
		faireActionEvenementMode(BOUTON3LONG);//abandon();
	} else {
		while(! SW3IN_BUTTON_UP){ // tant que le bouton est appuye
			wait_general(MILLI_SECONDES_APPUI_LONG);
			bouton3AppuiCourt();
		}
	}
}

// Traitement du cas où on a un appui long sur le bouton 4
// Cette fonction pourrait être supprimée en la remplaçant par un appel direct à faireActionEvenementMode
// mais ce n'est pas essentiel
void bouton4AppuiLong(){
	faireActionEvenementMode(BOUTON4LONG);
}

// Initialise les ports correspondant aux boutons.
// Utilise les variables SW1, SW2, SW3 et SW4 qui sont definies dans interruptBoutons.h,
// et qui désignent le routage entre les boutons et les ports réels utilisés.
void initP0(void){
	protectMisc( MSCPROT_PROTECT_OFF );
	PCLK_CLKSRC	= 1;	/// - Set clock source for chattering filter (if =1, it means OSC1).
	//PCLK_CLKDIV	= 0x9;	/// - Set division ratio for clock source (0x9-> 1/512, c-a-d 1/64 secondes, 0xa -> 1/1024, c-a-d 1/32 secondes).
	// Tentative de debug pour le double appui (apres fin de match)
	//On vise 150 ms soit environ 1/8 secondes, donc 8Hz=(32000/4000)Hz, soit un division ratio de 4000, donc 0xC
	// 0xC --> ça ne marche pas bien, il faut appuyer trop longtemps sur les boutons pour les activer.
	// Testons 0xA = 1/32 secondes (facteur 2 par rapport a avant)
	// C'est pas mal mais on manque quand même des clics. Donc restons à 0x9 = 1/64 secondes.
	// tentons un debug au niveau de la fonction intPortInput
	PCLK_CLKDIV	= 0x9;
	protectMisc( MSCPROT_PROTECT_ON );

	// PxMODSEL_PxySEL = 0 :  "general port IO function" et non pas "peripheral io function"
	P0MODSEL &= 0xFFFF ^ (0x0001 << SW1);
	P0MODSEL &= 0xFFFF ^ (0x0001 << SW2);
	P0MODSEL &= 0xFFFF ^ (0x0001 << SW3);
	P0MODSEL &= 0xFFFF ^ (0x0001 << SW4);

	// PxCHATEN_PxyCHATEN = 1 : chattering on
	P0CHATEN |= (0x0001 << SW1);
	P0CHATEN |= (0x0001 << SW2);
	P0CHATEN |= (0x0001 << SW3);
	P0CHATEN |= (0x0001 << SW4);

	// PxINTCTL_PxyEDGE = 1: interrupts on falling edge
	P0INTCTL |= (0x0100 << SW1);
	P0INTCTL |= (0x0100 << SW2);
	P0INTCTL |= (0x0100 << SW3);
	P0INTCTL |= (0x0100 << SW4);

	// PxINTCTL_PxyIE = 0 : disable interrupt (juste pour eviter une interrupt durant l'initialisation des ports)
	P0INTCTL &= 0xFFFF ^ (0x0001 << SW1);
	P0INTCTL &= 0xFFFF ^ (0x0001 << SW2);
	P0INTCTL &= 0xFFFF ^ (0x0001 << SW3);
	P0INTCTL &= 0xFFFF ^ (0x0001 << SW4);

	// PxIOEN_PxyIEN = 1 : input
	P0IOEN |= (0x0100 << SW1);
	P0IOEN |= (0x0100 << SW2);
	P0IOEN |= (0x0100 << SW3);
	P0IOEN |= (0x0100 << SW4);

	// PxIOEN_PxyOEN = 0 : pas output
	P0IOEN &= 0xFFFF ^ (0x0001 << SW1);
	P0IOEN &= 0xFFFF ^ (0x0001 << SW2);
	P0IOEN &= 0xFFFF ^ (0x0001 << SW3);
	P0IOEN &= 0xFFFF ^ (0x0001 << SW4);

	// PxRCTL_PxyREN: active pull-? (up ou down selon PxRCTL_PxyPDPU)
	P0RCTL |= (0x0001 << SW1);
	P0RCTL |= (0x0001 << SW2);
	P0RCTL |= (0x0001 << SW3);
	P0RCTL |= (0x0001 << SW4);

	// PxRCTL_PxyPDPU : pull up au lieu de pull down
	P0RCTL |= (0x0100 << SW1);
	P0RCTL |= (0x0100 << SW2);
	P0RCTL |= (0x0100 << SW3);
	P0RCTL |= (0x0100 << SW4);

	// PxINTF_PxyIF : on clear les flags
	P0INTF |= (0x0001 << SW1);
	P0INTF |= (0x0001 << SW2);
	P0INTF |= (0x0001 << SW3);
	P0INTF |= (0x0001 << SW4);

	// PxINTCTL_PxyIE : enable interrupt.  Normalement ne declenche pas d'interrupt parce qu'on est en falling edge et pull up
	P0INTCTL |= (0x0001 << SW1);
	P0INTCTL |= (0x0001 << SW2);
	P0INTCTL |= (0x0001 << SW3);
	P0INTCTL |= (0x0001 << SW4);// enable interrupts.

	ILVPPORT = INTERRUPT_LEVEL3;
}

