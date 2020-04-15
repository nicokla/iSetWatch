/*****************
 * Ce fichier définie ce qui est nécessaire pour faire fonctionner le mode TENNIS.
 * Il est très lié au fichier bluetooth.c car celui-ci concerne aussi le mode TENNIS.
 * *****************/

#include "tennis.h"
#include "globalVar.h"
#include "init.h"
#include "lcd8a.h"
#include "uart.h"
#include "bluetooth.h"
#include "buzzer.h"
#include "string.h"
#include "interruptBoutons.h"
#include "backlight.h"
#include "ecranPourClignotements.h"
#include "t16_ch0_smallDelays.h"
#include "t16b_ch1_verySmallDelays.h"
#include "watch.h"
#include "iSetService.h"
#include "que.h"
#include "fileDActions.h"

///////////////////////////////
// 1.2) variables du tennis

// sert à la fin du match de tennis
// (deux 7 segments clignotent avec des 8 dedans) car ce qui clignote doit être pointé
unsigned char quatreVingtHuit=88;

// permet de savoir si le score du tennis est ou pas à zéro
// dès qu'on commence le match, cette variable est mise à zéro
unsigned char tennisAZero=1;

// permet à la montre d'arreter le chrono du match de tennis si ça fait tres longtemps qu'aucun point
// n'a été marqué (30 minutes)
unsigned char tennisOntLAirDEtreEnTrainDeJouer;

// précise le nombre de minutes depuis lequel aucun point n'a été marqué
unsigned short tennisLastPointChangeMinute;

// Minute où le match a commencé
unsigned short tennisStartingMinute;
unsigned short dureeDuMatchEnMinutes=0;
unsigned short minuteDeFinDuMatch=0;

// chrono de la durée du match de tennis, juste pour l'affichage de l'ecran de fin
unsigned char tennisMinute=0;
unsigned char tennisHour=0;

// duree de chaque set en minutes
unsigned short tennisSetMinutes[5];

// nombre de score sauvegardes pour savoir si on peut ou pas reculer le score (vaut au maximum
// NB_TOUR_SAUVEGARDES_MAX)
unsigned char nbScoresSauvegardes=0;

// statistiques du match : services gagnants, perdants, et jeux blancs
unsigned char servGagn[NB_TOUR_SAUVEGARDES_MAX+1][2][5];
unsigned char servPerd[NB_TOUR_SAUVEGARDES_MAX+1][2][5];
unsigned char jeuxBlancs[NB_TOUR_SAUVEGARDES_MAX+1][2][5];

// score des manches
// il y a la dimension de taille NB_TOUR_SAUVEGARDES_MAX+1, car il faut aussi sauvegarder les points précédents.
// La plupart du temps on s'intéresse à scoreManche[0] qui est un tableau de taille [2][5]
// représentant le score actuel des manches
// La même remarque vaut pour les autres variables ayant comme première dimension
// NB_TOUR_SAUVEGARDES_MAX+1
unsigned char scoreManche[NB_TOUR_SAUVEGARDES_MAX+1][2][5];

// nombre de manches gagnées par chaque joueur.
// l'indice 0 représente le haut de l'écran, donc l'autre joueur
// l'indice 1 représente le joueur qui porte la montre
// C'est pour ça qu'on a dans globalVar.h :
//#define MOI 1 // comme bas
//#define LUI 0 // comme haut
unsigned char nbManches[NB_TOUR_SAUVEGARDES_MAX+1][2]; // = scorePartie

// serveur au début d'un tie-break (utile seulement si on est dans un tie-break,
// sert à mettre en application une règle que j'ai oublié mais qui est peu importante.
unsigned char serveurDebutTb[1+NB_TOUR_SAUVEGARDES_MAX];

// permet de savoir si il y a un changement de côté à ce point là
unsigned char chgtDeCoteEnCours[1+NB_TOUR_SAUVEGARDES_MAX];

// permet de se souvenir si on était en tie-break ou pas au dernier point.
// dans ce cas tennisMode vaut TENNIS_TIE_BREAK-TENNIS == 3.
// la valeur de tennisMode est sauvegardée lors de changeMode, grâce à l'appel
// de la fonction sauvegardeMode()
unsigned char tennisMode[NB_TOUR_SAUVEGARDES_MAX+1];

// score du jeu. On remarque ici qu'il y a NB_TOUR_SAUVEGARDES_MAX
// au lieu de NB_TOUR_SAUVEGARDES_MAX + 1
// comme premiere dimension. C'est en fait volontaire car pour les scores du jeu, on utilise une varAff,
// définie un peu plus bas : scoreJeu0
// Ceci est dû au fait qu'il faut afficher le "Ad" dans le cas où scoreJeu vaut 50.
// ceci est géré en ayant créé un type de varAff spécial appelé SPECIAL1, qui est le type de scoreJeu0
unsigned char scoreJeu[NB_TOUR_SAUVEGARDES_MAX][2]; // avantage = 50

// pour savoir si je suis au service ou si c'est l'adversaire
unsigned char jeSuisAuService[NB_TOUR_SAUVEGARDES_MAX];

// pour savoir si un des joueurs a abandonné
unsigned char abandonne[2];

// score de la manche actuelle
VarAff scoreManche0;//[5]; // existe pour l'affichage mais les vrais nb ne sont pas dedans

// score du jeu actuel
VarAff scoreJeu0[2]; // avantage = 50

// service ce tour-ci
VarAff jeSuisAuService0;

// Variables de réglages du match :
VarAff nbManchesGagnantes; // (1 2 ou 3)
VarAff nbJeuxGagnantsUneManche; //(3 a 6)
VarAff avantageActive; //(par defaut active, ie si 40/40, on ne gagne pas apres, il faut d'abord passer par l'avantage)
VarAff tbActive; //(a 7 ou pas de jeu decisif. Par defaut a 7. Attention si il n'y a pas de jeu decisif, pb d'affichage possible si les scores depassent dix jeux, sauf eventuellement si c'est le dernier set.)
VarAff stbActive; //(a 10, pour les doubles, compte pour 1 manche entiere.)
VarAff tbType; //tbType sert juste dans le cas pour enfant des tie-breaks raccourcis

// ordre des sous-modes du tennis (reglage de remise à zéro,
// puis du nombre de sets, puis du nombre de jeux, etc.
unsigned char suivantTennis[17];

// affichages divers pours des réglages liés au tennis
char typeTbTexte[4][5]={"  4-4","  3-3","  5-5","  4-4"};
char bluetoothStrings[3][5]={"  OFF", "COUNT", "PARTN"};
ChiffresAff * c0=&(scoreManche0.contenu.chiffresAff);

// initialisation du mode tennis
void initTennis(void){
	// Initialisation du matchUUID � la production de la montre
	// pour que le serveur reconnaisse un matchUUID invalide
	// et en cr�e un nouveau
	memset(&matchUUID,0,4);

	peerConnected=0;

//	setBounds(&searchOtherDevice, 0, 1, 0);
//	searchOtherDevice.type=BOOL;
//	setPosBoolClignote(&searchOtherDevice, SYMBOL_INDEX_BT);

	scoreManche0.type=PLUSIEURS_CHIFFRES;
	scoreManche0.contenu.chiffresAff.tabNb[0]=&(scoreManche[0][0][0]);
	scoreManche0.contenu.chiffresAff.tabNb[1]=&(scoreManche[0][1][0]);

	setBounds(&(scoreJeu0[0]), 0, 50, 0);
	scoreJeu0[0].type=SPECIAL1;
	scoreJeu0[0].contenu.varAffSpecial1.x=0;
	scoreJeu0[0].contenu.varAffSpecial1.y=0;

	setBounds(&(scoreJeu0[1]), 0, 50, 0);
	scoreJeu0[1].type=SPECIAL1;
	scoreJeu0[1].contenu.varAffSpecial1.x=1;
	scoreJeu0[1].contenu.varAffSpecial1.y=0;

	setBounds(&jeSuisAuService0, 0, 1, MOI);
	jeSuisAuService0.type=BOOL;
	setPosBool(&jeSuisAuService0, SYMBOL_INDEX_SERVER2, SYMBOL_INDEX_SERVER1, 1);

	setBounds(&nbManchesGagnantes, 2, 3, 3);
	nbManchesGagnantes.type=INT7;
	setPosInt7(&nbManchesGagnantes, 0, 0, 0);

	setBounds(&nbJeuxGagnantsUneManche, 3, 6, 6);
	nbJeuxGagnantsUneManche.type=INT7;
	setPosInt7(&nbJeuxGagnantsUneManche, 0, 0, 0);

	setBounds(&avantageActive, 0, 1, 1);
	avantageActive.type=STR;
	setPosString(&avantageActive, &(noYes[0][0]), 1 );

	setBounds(&tbActive, 0, 1, 1);
	tbActive.type=STR;
	setPosString(&(tbActive), &(noYes[0][0]), 1 );

	setBounds(&stbActive, 0, 1, 0);
	stbActive.type=STR;
	setPosString(&(stbActive), &(noYes[0][0]), 1);

	setBounds(&tbType, TB_TYPE_NORMAL, TB_TYPE_EARLY, TB_TYPE_NORMAL); // 0 1 0
	tbType.type=STR;
	setPosString(&tbType, &(typeTbTexte[0][0]), 1);

	razTennis();

	suivantTennis[TENNIS_SETTING_BLUETOOTH & MASQUE_SUB]=TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER;
	suivantTennis[TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER & MASQUE_SUB]=TENNIS;
	suivantTennis[TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE & MASQUE_SUB]=
		TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER;
	suivantTennis[TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER & MASQUE_SUB]=TENNIS;

	suivantTennis[TENNIS & MASQUE_SUB]=TENNIS_SETTING_RAZ;
	suivantTennis[TENNIS_SETTING_RAZ & MASQUE_SUB]=TENNIS_SETTING_INITIAL_SERVER;
	suivantTennis[TENNIS_SETTING_INITIAL_SERVER & MASQUE_SUB]=TENNIS_SETTING_NB_SET_PER_MATCH;
	suivantTennis[TENNIS_SETTING_NB_SET_PER_MATCH & MASQUE_SUB]=TENNIS_SETTING_NB_GAME_PER_SET;
	suivantTennis[TENNIS_SETTING_NB_GAME_PER_SET & MASQUE_SUB]=TENNIS_SETTING_ADVANTAGE;
	suivantTennis[TENNIS_SETTING_ADVANTAGE & MASQUE_SUB]=TENNIS_SETTING_TIE_BREAK;
	suivantTennis[TENNIS_SETTING_TIE_BREAK & MASQUE_SUB]=TENNIS_SETTING_SUPER_TIE_BREAK; // ou bien tie_b_type
	suivantTennis[TENNIS_SETTING_TIE_BREAK_TYPE & MASQUE_SUB]=TENNIS_SETTING_SUPER_TIE_BREAK;
	suivantTennis[TENNIS_SETTING_SUPER_TIE_BREAK & MASQUE_SUB]=TENNIS;

}

// Remise à zéro du score du tennis
void razTennis(){
	scoreUpdate.bit.gameOver=0;
	tennisAZero=1;
	memset(abandonne,0,2);
	memset(&scoreUpdate,0,sizeof(ScoreUpdate));
	memset(tennisSetMinutes,0,5*sizeof(short));
	tennisHour=0;
	tennisMinute=0;
	nbScoresSauvegardes=0;
	memset(servPerd,0,2*5*(NB_TOUR_SAUVEGARDES_MAX+1));
	memset(servGagn,0,2*5*(NB_TOUR_SAUVEGARDES_MAX+1));
	memset(jeuxBlancs,0,2*5*(NB_TOUR_SAUVEGARDES_MAX+1));

	memset(scoreManche,0,2*5*(NB_TOUR_SAUVEGARDES_MAX+1));
	displayIfNecessary(&scoreManche0);

	memset(nbManches,0,2*(NB_TOUR_SAUVEGARDES_MAX+1));
	memset(serveurDebutTb,0,(NB_TOUR_SAUVEGARDES_MAX+1));
	memset(chgtDeCoteEnCours,0,(NB_TOUR_SAUVEGARDES_MAX+1));
	memset(scoreJeu,0,2*(NB_TOUR_SAUVEGARDES_MAX));
	memset(jeSuisAuService,0,(NB_TOUR_SAUVEGARDES_MAX));
	setVarAffValue(&scoreJeu0[0],0);
	setVarAffValue(&scoreJeu0[1],0);

//	if(bluetoothMode.nb == BL_COUNTER)
//		setVarAffValue(&jeSuisAuService0, MOI);
//	if(bluetoothMode.nb == BL_PARTNER)
//		setVarAffValue(&jeSuisAuService0, LUI);

	//	scoreManche0 pour l'affichage ?

	memset(tennisMode,0,(NB_TOUR_SAUVEGARDES_MAX+1));
	if(mode == TENNIS_END){
		mettreMode(TENNIS);
	}

	if(bluetoothMode.nb == BL_COUNTER){
		sndScoreBluetooth200Ms();
	}
}

// permet de preparer sur l'écran SW les éléments communs à tous les sous-modes du tennis :
// le score du jeu (0 15 30 40 ad), et qui est au service.
void tennisBasePrepareDisplay(){
	placerDansEcran(&(scoreJeu0[MOI]));
	placerDansEcran(&(scoreJeu0[LUI]));
	placerDansEcran(&(jeSuisAuService0));
}

// fonction permettant d'avoir un pointeur vers une fonction sans arguments pour faire un waitAndDo()
void mettreModeTennis(){
	mettreMode(TENNIS);
}

// fonction appelée à chaque entrée dans un mode sous-mode du TENNIS
void prepareDisplayTennis(unsigned char m){
	unsigned char gagnant;
//	unsigned char i;

	mettreSurEcranForceSymbole(SYMBOL_INDEX_SEPARATION);

	switch(m){

	case TENNIS :
		tennisBasePrepareDisplay();
		placerDansEcran(&(scoreManche0));
//		placerDansEcran(&bluetoothMode); // --> fait dans tous les modes (cf mettreMode()), plus la peine de le refaire
		break;

	case TENNIS_SETTING_INITIAL_SERVER :
		mettreSurEcranTexte(0, "SERVR");
		break;

	case TENNIS_SETTING_NB_GAME_PER_SET :
		mettreSurEcranTexte(0, "NGAME");
		break;

	case TENNIS_SETTING_NB_SET_PER_MATCH :
		mettreSurEcranTexte(0, " NSET");
		break;

	case TENNIS_SETTING_ADVANTAGE :
		mettreAuDefilement(0, "ADVANTAGE");
		break;

	case TENNIS_SETTING_TIE_BREAK :
		mettreAuDefilement(0, "TIE-BREAK");
		break;

	case TENNIS_SETTING_SUPER_TIE_BREAK :
		mettreAuDefilement(0, "SUPER TIE-BREAK");
		break;

	case TENNIS_SETTING_BLUETOOTH :
//		setVarAffValue(&bluetoothMode,BL_OFF);
		setBluetoothModeValue(BL_OFF);
//		reset_radio(); // --> maintenant fait automatiquement setVarAffValue(&bluetoothMode,BL_OFF);
//		placerDansEcran(&bluetoothMode);
		mettreAuDefilement(0, "BLUETOOTH");
		break;

	case TENNIS_SETTING_RAZ  :
		tennisBasePrepareDisplay();
		mettreAuClignotementTexte(0, "SCORE");
		mettreAuClignotementTexte(1, "  =0 ");
		break;

	case TENNIS_SETTING_TIE_BREAK_TYPE :
		if(nbJeuxGagnantsUneManche.nb==4)
			setPosString(&tbType, &(typeTbTexte[0][0]), 1);
		else if (nbJeuxGagnantsUneManche.nb==5)
			setPosString(&tbType, &(typeTbTexte[2][0]), 1);
		mettreAuDefilement(0, "TIE-BREAK");
		break;

	case TENNIS_CHANGE_SIDE :
		bipBip(2);
		tennisBasePrepareDisplay();
		mettreAuClignotementTexte(0, " CHGE");
		mettreAuClignotementTexte(1, " SIDE");
		waitAndDo(4, &actionFinClignotementChangeSide); // !!
//		placerDansEcran(&bluetoothMode); // --> automatique
		break;

	case TENNIS_TIE_BREAK:
		mettreSurEcranTexte(0, " TBRK");
		//mettreAuClignotementTexte(0, " TBRK");
		tennisBasePrepareDisplay();
		waitAndDo(4, &actionFinClignotementTbOuStb);
//		placerDansEcran(&bluetoothMode); // --> automatique
		break;

	case TENNIS_STB:
		mettreSurEcranTexte(0, "SUTBK");
		tennisBasePrepareDisplay();
		waitAndDo(4, &actionFinClignotementTbOuStb);
		//placerDansEcran(&bluetoothMode); // --> automatique
		break;

	case TENNIS_END:
		tennisOntLAirDEtreEnTrainDeJouer=0;

//		for(i=0; i<5; i++){
//			tennisHour += (unsigned char) (tennisSetMinutes[i] / 60);
//			tennisMinute +=(unsigned char) ( tennisSetMinutes[i] % 60 );
//		}

		// la condition permet d'eviter le cas où on arrive là depuis un autre mode
		// condition equivalente pour l'instant mais plus sensible aux changements de spec donc non utilisé :
		// if(avantChangementMode != COUNTDOWN)
		// --> pb, si on est en mode partner, et qu'on est en countdown quand on reçoit le score, ça coince.
		if(flagEndMatchNow) {
			flagEndMatchNow=0;
			minuteDeFinDuMatch = totalMinute(&watch.shortTime);
			dureeDuMatchEnMinutes = (differenceMinuteGen(minuteDeFinDuMatch, tennisStartingMinute));
		}

		tennisHour = (unsigned char) (dureeDuMatchEnMinutes / 60);
		tennisMinute = (unsigned char) (dureeDuMatchEnMinutes % 60);

		if(abandonne[MOI])
			gagnant=LUI;
		else if (abandonne[LUI])
			gagnant=MOI;
		else{
			if(nbManches[0][MOI]>nbManches[0][LUI])
				gagnant=MOI;
			else
				gagnant=LUI;
		}
		mettreSurEcranNombre7Seg(1-gagnant, 0, &tennisHour, 0);
		mettreSurEcranNombre7Seg(1-gagnant, 1, &tennisMinute, 1);

		if(abandonne[MOI] || abandonne[LUI]){
			mettreAuDefilement(1-gagnant, "ABANDON");
			ecran.aff14Seg[gagnant].type=RIEN;
		} else {
			dispAllTabNb(c0); // score des sets
		}

		mettreAuClignotementNombre7Seg(gagnant, 0, &quatreVingtHuit, 1);
//		placerDansEcran(&bluetoothMode); // --> fait automatiquement pour tous les modes maintenant
		break;

	case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE:
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER:
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER:
		prepareDisplayBluetoothPairing();
		break;

	case TENNIS_BLUETOOTH_CONNEXION_ABORTED :
		// Show failure
		memset(nomPeer, 0, 20);
		memcpy(nomPeer, "PAIRING FAILED", 15);
		mettreAuClignotementDefilement(0, nomPeer);

		// Deconnecte tout
		peerConnected=0;
		//setVarAffValue(&bluetoothMode,BL_OFF);
		setBluetoothModeValue(BL_OFF);
		countDownPairingStopped=1;
//		reset_radio(); --> now automatically done when we do setVarAffValue(&bluetoothMode,BL_OFF);
	break;

//	case OAD_CHOICE :
//		mettreAuDefilement(0, "OAD NEEDS UPDATE");
//		break;

	case OAD_UPDATING:
		askOadToStart();
		mettreAuDefilement(0, "CC UPDATING");
		ecran.aff7Seg[0][0].type=TOURNANT;
		startSecondsInterrupts(255, &mettreModeTennis);
		break;

	case OAD_END:
		wait_general(200);
		reset_radio();
		switch(oadUpdateSuccessfull){
		case 0:
			mettreAuDefilement(0, "FW UPDATE FAILED");
			break;
		case 1:
			mettreAuDefilement(0, "FW UPDATE OK");
			break;
		}
		waitAndDo(8, &mettreModeTennis);
		break;

	default:
		break;
	}
}

// actions faites après chaque update de score chez le counter.
void actionsCounterApresUpdateScore(){
		if(mode ==TENNIS_END){
			scoreUpdate.bit.gameOver=1;
		} else {
			scoreUpdate.bit.gameOver=0;
		}

		if(! searchOtherDevice)
			sndScoreBluetooth200Ms();

		if(mode ==TENNIS_END){
			wait_general(500); // wait 150ms
			sndStatistics();
		}
}

// mets le mode de setting bluetooth sauf si le CC est en OAD (update sw par bluetooth)
// dans ce cas on affiche un countdown de 90 secondes et on affiche "update sw" ou quelque chose comme ça
// ceci est fait en faisant mettreMode(OAD_CHOICE); (si on choisit ensuite now au lieu de later)
void mettreModeTennisSettingBluetoothConditionnally(){
	if(checkIfImageB()){
		mettreMode(TENNIS_SETTING_BLUETOOTH);
	} else {
		//reset_radio();
		//mettreMode(OAD_CHOICE);
		mettreMode(OAD_UPDATING);
	}
}

// On entre dans cette fonction quand on touche aux boutons et qu'on est dans un des subModes du tennis
//, TENNIS lui même y compris bien entendu
void actionModeTennis(unsigned char typeEvenement){
	switch(mode){
	case TENNIS_SETTING_INITIAL_SERVER :
	case TENNIS_SETTING_NB_GAME_PER_SET :
	case TENNIS_SETTING_NB_SET_PER_MATCH :
	case TENNIS_SETTING_ADVANTAGE :
	case TENNIS_SETTING_TIE_BREAK :
	case TENNIS_SETTING_SUPER_TIE_BREAK :
	case TENNIS_SETTING_TIE_BREAK_TYPE :
		switch(typeEvenement){
		case BOUTON2COURT:
				augmenterVarAff(currentVarAff);
			break;
		case BOUTON3COURT:
				diminuerVarAff(currentVarAff);
			break;
		case BOUTON1COURT:
			if(mode==TENNIS_SETTING_TIE_BREAK){
				if(tbActive.nb && ! avantageActive.nb &&  (nbJeuxGagnantsUneManche.nb==4 || nbJeuxGagnantsUneManche.nb==5) && nbManchesGagnantes.nb==2 ) {
					mettreMode(TENNIS_SETTING_TIE_BREAK_TYPE);
				} else {
					setVarAffValue(&tbType,0);
					mettreMode(TENNIS_SETTING_SUPER_TIE_BREAK);//suivantTennis[mode & MASQUE_SUB]);//
				}
			}
			else{
				if(suivantTennis[mode & MASQUE_SUB] == TENNIS){
					if(bluetoothMode.nb == BL_COUNTER){
						sndScoreBluetooth200Ms();
					}
				}
				mettreMode(suivantTennis[mode & MASQUE_SUB]);
			}
			break;
		case BOUTON4COURT:
			if(bluetoothMode.nb == BL_COUNTER){
				sndScoreBluetooth200Ms();
			}
			mettreMode(TENNIS+tennisMode[0]);
			break;
		}
	break;

//		case OAD_CHOICE:
//			switch(typeEvenement){
//					case BOUTON2COURT:
//							augmenterVarAff(currentVarAff);
//						break;
//					case BOUTON3COURT:
//							diminuerVarAff(currentVarAff);
//						break;
//					case BOUTON1COURT:
//					case BOUTON4COURT:
//						if(shouldStartOad.nb){
//							mettreMode(OAD_UPDATING);
//						} else {
//							mettreMode(TENNIS);
//						}
//						break;
//			}
//			break;

		case TENNIS_SETTING_RAZ  :
			switch(typeEvenement){
			case BOUTON2COURT:
			case BOUTON3COURT:
				razTennis();
				if(bluetoothMode.nb == BL_COUNTER){
					sndScoreBluetooth200Ms();
				}
				break;
			case BOUTON1COURT:
					mettreMode(suivantTennis[mode & MASQUE_SUB]);
				break;
			case BOUTON4COURT:
				if(bluetoothMode.nb == BL_COUNTER){
					sndScoreBluetooth200Ms();
				}
				mettreMode(TENNIS+tennisMode[0]);
				break;
			}
			break;

	case TENNIS:
		switch(typeEvenement){
			case BOUTON2LONG:
				if(bluetoothMode.nb != BL_PARTNER){
					abandon(MOI);
				}
				if (bluetoothMode.nb == BL_COUNTER)
					actionsCounterApresUpdateScore();
				break;
			case BOUTON3LONG:
				if(bluetoothMode.nb != BL_PARTNER){
					abandon(LUI);
				}
				if (bluetoothMode.nb == BL_COUNTER)
					actionsCounterApresUpdateScore();
				break;
			case BOUTON1COURT:
					lightOn();
			break;
			case BOUTON2COURT:
				if(bluetoothMode.nb != BL_PARTNER){
					augmenterScore(LUI);
				}
				if (bluetoothMode.nb == BL_COUNTER)
					actionsCounterApresUpdateScore();
			break;
			case BOUTON3COURT:
				if(bluetoothMode.nb != BL_PARTNER){
					augmenterScore(MOI);
				}
				if (bluetoothMode.nb == BL_COUNTER)
					actionsCounterApresUpdateScore();
			break;
			case BOUTON4COURT:
				mettreMode(COMPTEUR);
			break;
			case BOUTON2ET3 :
				if(bluetoothMode.nb != BL_PARTNER)
					loadOldSit();
				if(bluetoothMode.nb == BL_COUNTER)
					sndScoreBluetooth200Ms();
			break;
			case BOUTON4AFTEROTHER :
				mettreMode(WATCH);
			break;
			case BOUTON1LONG:
				mettreMode(suivantTennis[TENNIS & MASQUE_SUB]);
			break;
			case BOUTON4LONG:
				flushRcvData(); 	// flush le buffer UART
				tennisLastPointChangeMinute=totalMinute(&watch.shortTime);
				mettreModeTennisSettingBluetoothConditionnally();
			break;
		}
		break;


		case TENNIS_CHANGE_SIDE:
//			stopT16Ch0();
			//mettreMode(TENNIS);
//			actionFinClignotementChangeSide();
			enleverUneAction(&fileDActions, &actionFinClignotementChangeSide, 1 );
		break;

		case TENNIS_TIE_BREAK :
//			stopT16Ch0();
			//mettreMode(TENNIS);
//			actionFinClignotementTbOuStb();
			enleverUneAction(&fileDActions, &actionFinClignotementTbOuStb, 1 );
		break;

		case TENNIS_STB :
//			stopT16Ch0();
			//mettreMode(TENNIS);
//			actionFinClignotementTbOuStb();
			enleverUneAction(&fileDActions, &actionFinClignotementTbOuStb, 1 );
		break;

		case TENNIS_END :
			switch(typeEvenement){
			case BOUTON4LONG:
				razTennis(); // because if we are in TENNIS_END,
				//then starting a connection sous-entends qu'on va commencer une nouvelle partie.
				mettreModeTennisSettingBluetoothConditionnally();
			break;
			case BOUTON4COURT:
				mettreMode(COMPTEUR);
			break;
			case BOUTON2ET3 :
				if(bluetoothMode.nb != BL_PARTNER)
					loadOldSit();
				if(bluetoothMode.nb == BL_COUNTER)
					sndScoreBluetooth200Ms();
			break;
			case BOUTON4AFTEROTHER :
				mettreMode(WATCH);
			break;
			case BOUTON1LONG:
				razTennis();
				//arret_ble();
				//reset_radio();
				//setVarAffValue(&bluetoothMode,BL_OFF);
				//mettreMode(TENNIS); --> maintenant fait dans razTennis automatiquement si on est en mode TENNIS_END.
			break;
			}
		break;

		case TENNIS_SETTING_BLUETOOTH :
			switch(typeEvenement){
			case BOUTON2COURT:
				augmenterVarAff(currentVarAff);
				break;
			case BOUTON3COURT:
				diminuerVarAff(currentVarAff);
				break;
			case BOUTON1COURT:
				reset_radio();
				switch(bluetoothMode.nb){
				case BL_OFF:
					mettreMode(TENNIS);
				break;
				case BL_COUNTER :
#ifdef CC_DEBUGGER_BLOCKING_RESET
						mettreMode(TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER);
						ISET_FINS(sndData[0], CONN_SETUP_NEW, TRUE);
						ISET_FINS(sndData[0], CONN_SETUP_PEER_STATUS, 	NOT_A_PEER_STATUS_UPDATE);
						ISET_FINS(sndData[0], CONN_SETUP_PEER_MODE, 	COUNTER_MODE);
						sendUartData(CONNECTION_SETUP, sndData, 1);
#else
						mettreMode(TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE);
						ISET_FINS(sndData[0], CONN_SETUP_NEW, TRUE);
						ISET_FINS(sndData[0], CONN_SETUP_PEER_STATUS, 	NOT_A_PEER_STATUS_UPDATE);
						ISET_FINS(sndData[0], CONN_SETUP_PEER_MODE, 	SMARTPHONE_MODE);
						sendUartData(CONNECTION_SETUP, sndData, 1);
#endif
						break;
				case BL_PARTNER :
						mettreMode(TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER);
						ISET_FINS(sndData[0], CONN_SETUP_NEW, TRUE);
						ISET_FINS(sndData[0], CONN_SETUP_PEER_STATUS, 	NOT_A_PEER_STATUS_UPDATE);
						ISET_FINS(sndData[0], CONN_SETUP_PEER_MODE, 	PARTNER_MODE);
						sendUartData(CONNECTION_SETUP, sndData, 1);
					break;
				}
				break;
			case BOUTON4COURT:
//				reset_radio();
				finirPairing();
				mettreMode(TENNIS+tennisMode[0]);
				break;
			}
		break;

		case TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER:
		case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER:
			switch(typeEvenement){
			case BOUTON1COURT:
			case BOUTON4COURT:
				finirPairing();
			break;
			}
		break;


		case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE:
			switch(typeEvenement){
			case BOUTON1COURT:
				actionMettreModeSuivantPairing();
			break;
			case BOUTON4COURT:
				finirPairing();
			break;
//			case BOUTON2COURT:
//			case BOUTON3COURT:
//				setVarAffValue(&btConnexionTimeLeft,btConnexionTimeLeft.max);
//			break;
			}
		break;

		case TENNIS_BLUETOOTH_CONNEXION_ABORTED:
			// quel que soit le bouton :
			endTheScreenOfSetupAborted();
			break;

		case OAD_END:
			mettreMode(TENNIS); // quel que soit le bouton
			break;
		case OAD_UPDATING:
			// on ne fait rien quand l'utilisateur clique sur un bouton dans ce mode
			// sauf si c'est tout les boutons (mais pas traité ici, le code est dans interruptBoutons.c)
			// --> changement, S4 long peut aussi sortir du mode et resetter le CC (safe de resetter un CC en OAD ?)
			if(typeEvenement == BOUTON4LONG){
				oadUpdateSuccessfull=0;
				reset_radio();
				mettreMode(OAD_END);
			}
			break;
	}

}

// défini la façon d'augmenter le score du jeu
unsigned char suivant(unsigned char a){
	switch(a){
		case 0:
			return 15;
		break;
		case 15:
			return 30;
		break;
		case 30:
			return 40;
		break;
		case 40:
			return 50; // advantage
		break;
		case 50:
			return 60; // jeu gagne
		break;
	}
	return 99; // si l'entree est non conforme (n'appartient pas a 0, 15, 30, 40, 50). A priori ne doit pas arriver.
}

// renvoie 1 si un tie-break est en cours, 0 sinon
unsigned char tbEnCours(){
	unsigned char max=numManche();
	if(tbType.nb == TB_TYPE_NORMAL){
		return (tbActive.nb &&
				scoreManche[0][MOI][max] ==  nbJeuxGagnantsUneManche.nb &&
				scoreManche[0][LUI][max] ==  nbJeuxGagnantsUneManche.nb ) ;
	} else if(tbType.nb == TB_TYPE_EARLY){
		return (tbActive.nb &&
			    scoreManche[0][MOI][max] ==  nbJeuxGagnantsUneManche.nb - 1 &&
				scoreManche[0][LUI][max] ==  nbJeuxGagnantsUneManche.nb - 1 ) ;
	} else {
		return 0;
	}
}

// renvoie 1 si un super-tie-break est en cours, 0 sinon
unsigned char stbEnCours(){
	return (stbActive.nb && (nbManches[0][MOI]==(nbManchesGagnantes.nb-1)) && (nbManches[0][LUI]==(nbManchesGagnantes.nb-1)));
}

// renvoie le numéro de la manche actuelle, allant de 0 à 4 et pas de 1 à 5 (convention meilleure pour les indices des
unsigned char numManche(){
	unsigned char result;
	unsigned char resultCalcul2;
	unsigned char a1;
	unsigned char a2;

	a1=nbManches[0][LUI];
	a2=nbManches[0][MOI];
	if(a1>=nbManchesGagnantes.nb)
		a1=nbManchesGagnantes.nb - 1;
	if(a2>=nbManchesGagnantes.nb)
		a2=nbManchesGagnantes.nb - 1;
	result = a1+a2 ;

	//////////////////////////:
	// tentatives presque equivalentes que les lignes precedentes mais abandonnees, car ne traitent pas tout les cas ou autre pb
//	if(matchFini()){
//		if(! abandonne[0] && ! abandonne[1])
//			return (result - 1); // on reste bloqué à la dernière manche

	// cas impossible (parfois touché en fin de partie non abandonnée mais on force à rester au dernier set)
//		if(result >= 2*nbManchesGagnantes.nb - 1  ){
//			result=2*nbManchesGagnantes.nb - 2 ;
//		}
/////////////////////////////////////

		// on ne peut pas etre apres resultCalcul2, le premier 0/0 qu'il y a (sinon il y aurait un trou).
		// si il n'y a pas de premier 0/0 (5eme set deja entamé), on va éviter d'augmente à 5 (c'est numéroté de 0 à 4).
		// la plupart du temps le vrai resultat vaut (resultatCalcul2 - 1), sauf si on est en debut de set.
		resultCalcul2=0;
		while( ( ! (scoreManche[0][MOI][resultCalcul2]==0 && scoreManche[0][LUI][resultCalcul2]==0) ) && resultCalcul2+1 < 5){
			resultCalcul2++;
		}

		if(result <= resultCalcul2){
			return result ;
		}else{
			return resultCalcul2;
		}
}

// renvoie 1 ssi le match est terminé
unsigned char matchFini(){
	switch(bluetoothMode.nb){
	case BL_OFF :
	case BL_COUNTER :
		scoreUpdate.bit.gameOver =
					(nbManches[0][MOI] == nbManchesGagnantes.nb) ||
					(nbManches[0][LUI] == nbManchesGagnantes.nb) ||
					abandonne[0] ||
					abandonne[1];
		return scoreUpdate.bit.gameOver;
		break;
	case BL_PARTNER :
		return scoreUpdate.bit.gameOver;
		break;
	default :
		return scoreUpdate.bit.gameOver;
		break;
	}
	return scoreUpdate.bit.gameOver; // never reached because all values of bluetoothMode.nb have been tested
}

// Renvoie 1 si un match est en cours.
unsigned char matchEnCours(){
	return (tennisCommence() && (tennisMode[0] != TENNIS_END - TENNIS));
}

// Renvoie 1 ssi un changement de côté doit être fait.
unsigned char chgtCote(){
	if(tbEnCours() || stbEnCours())
		return (chgtCoteTb());
	else //if (scoreJeu0[0].nb==0 && scoreJeu0[1].nb==0)
		return (chgtCoteHorsTb());
	//else
		//return 0;
}

// pendant un tie-break, renvoie 1 ssi un chgt de cote doit etre fait
unsigned char chgtCoteTb(){
	unsigned char a = scoreJeu0[MOI].nb + scoreJeu0[LUI].nb;
	return (a%6==0 && a!=0);
}

// Hors d'un tie-break, renvoie 1 ssi un chgt de cote doit etre fait
unsigned char chgtCoteHorsTb(){
	unsigned char s=0;
	unsigned char i=numManche();
	s+=scoreManche[0][MOI][i];
	s+=scoreManche[0][LUI][i];
	if(scoreJeu0[MOI].nb !=0 || scoreJeu0[LUI].nb != 0){ // si on est pas dans un debut de jeu
		return 0;
	}
	else{
		if(s==0 && i > 0){ // debut de manche, pas la premiere
			return (((scoreManche[0][MOI][i-1] + scoreManche[0][LUI][i-1]) % 2) == 1); // nombre de jeux de la manche tout juste finie impair
		}
		else{
			return (s%2==1);
		}
	}
}

// règle la valeur d'une manche.
// Elle est en fait nécessaire seulement car on n'a pas une varAff par manche comme pour le score du jeu
//void setScoreMancheValue(unsigned char tour,unsigned char joueur,unsigned char manche,unsigned char nb){
//	scoreManche[tour][joueur][manche]=nb;
//	if(tour == 0)
//		dispNb(joueur,manche,c0);
//}

// sauvegarde le score pour ensuite pouvoir revenir en arriere (loadSit) quand on appuiera sur S2+S3
void saveSit(){
	unsigned char manche, tour, joueur;

	// L'indice plus proche de zéro est le tour le plus récent
	for(tour=NB_TOUR_SAUVEGARDES_MAX;tour>0; tour--){
		chgtDeCoteEnCours[tour]=chgtDeCoteEnCours[tour-1];
		tennisMode[tour]=tennisMode[tour-1]; // ??
		serveurDebutTb[tour]=serveurDebutTb[tour-1];
		for(joueur=0; joueur<=1; joueur++){
			nbManches[tour][joueur]=nbManches[tour-1][joueur];
			for(manche=0; manche<=4; manche++){
//				setScoreMancheValue(tour, joueur, manche, scoreManche[tour-1][joueur][manche]);
				scoreManche[tour][joueur][manche]=scoreManche[tour-1][joueur][manche];
				servGagn[tour][joueur][manche]=servGagn[tour-1][joueur][manche];
				servPerd[tour][joueur][manche]=servPerd[tour-1][joueur][manche];
				jeuxBlancs[tour][joueur][manche]=jeuxBlancs[tour-1][joueur][manche];
			}
		}
	}

	for(tour=NB_TOUR_SAUVEGARDES_MAX-1;tour>0; tour--){
		jeSuisAuService[tour]=jeSuisAuService[tour-1];
//			tennisMode[tour]=tennisMode[tour-1]; ??
		for(joueur=0; joueur<=1; joueur++){
			scoreJeu[tour][joueur]=scoreJeu[tour-1][joueur];
		}
	}
	scoreJeu[0][0]=scoreJeu0[0].nb; // avantage = 50
	scoreJeu[0][1]=scoreJeu0[1].nb;
	jeSuisAuService[0] = jeSuisAuService0.nb;

	if(nbScoresSauvegardes<NB_TOUR_SAUVEGARDES_MAX){
		nbScoresSauvegardes++;
	}
}

// charge le score précédent (fonction appelee lors d'un double appui)
void loadOldSit(){
	unsigned char manche, tour, joueur, max;
	out_bz_long();

	nbManches[0][MOI]=nbManches[1][MOI];
	nbManches[0][LUI]=nbManches[1][LUI];
	for(manche=0; manche<5; manche++){
						scoreManche[0][MOI][manche]=scoreManche[1][MOI][manche];
						scoreManche[0][LUI][manche]=scoreManche[1][LUI][manche];
	}
	max=numManche();

	tennisOntLAirDEtreEnTrainDeJouer=1;
	if(nbScoresSauvegardes>0){
		abandonne[0]=abandonne[1]=0; // on revient en arriere donc on ne peut pas avoir abandonné l'etape d'avant
		for(tour=0;tour<NB_TOUR_SAUVEGARDES_MAX; tour++){
			tennisMode[tour]=tennisMode[tour+1]; // ??
			chgtDeCoteEnCours[tour]=chgtDeCoteEnCours[tour+1];
			serveurDebutTb[tour]=serveurDebutTb[tour+1];
			for(joueur=0; joueur<=1; joueur++){
				nbManches[tour][joueur]=nbManches[tour+1][joueur];
			}
			for(joueur=0; joueur<=1; joueur++){
				for(manche=0; manche<5; manche++){
//					setScoreMancheValue(tour, joueur, manche, scoreManche[tour+1][joueur][manche]);
					scoreManche[tour][joueur][manche]=scoreManche[tour+1][joueur][manche];

					// ces 2 lignes ont ete commentees car à la fin on fait mettreMode(TENNIS).
//					if(tour == 0 && manche<=max)
//						dispNb(joueur,tour,c0);
					servGagn[tour][joueur][manche]=servGagn[tour+1][joueur][manche];
					servPerd[tour][joueur][manche]=servPerd[tour+1][joueur][manche];
					jeuxBlancs[tour][joueur][manche]=jeuxBlancs[tour+1][joueur][manche];
				}
			}
		}

		setVarAffValue(&(scoreJeu0[0]),scoreJeu[0][0]);
		setVarAffValue(&(scoreJeu0[1]),scoreJeu[0][1]);
		setVarAffValue(&(jeSuisAuService0),jeSuisAuService[0]);
		for(tour=0;tour<NB_TOUR_SAUVEGARDES_MAX-1; tour++){
			jeSuisAuService[tour]=jeSuisAuService[tour+1];
//			tennisMode[tour]=tennisMode[tour+1]; ??
			for(joueur=0; joueur<=1; joueur++){
				scoreJeu[tour][joueur]=scoreJeu[tour+1][joueur];
			}
		}

		nbScoresSauvegardes--;
	}


	// si tennis_end avant, on passe en TENNIS :
	// en fait on a enlevé la condition car en reculant on ne peut qu'etre en mode TENNIS.
	// car tennis_end est impossible apres avoir reculé,
	// et que les tennis_tie_break et tout ça ne servent qu'à l'affichage (les conditions pour les points ne dependent
	// pas du mode, on détecte à chaque fois si on est en tie-break ou pas de maniere rigoureuse en fonction du score)
	// et le mode tennis est à chaque fois remis au bout de 4 secondes en cas de tie-break ou super tie break, ou chgt de coté.

	//if(mode==TENNIS_END){
		mettreMode(TENNIS);//+tennisMode[0]);
	//}
}

//////////////////////////////////////////////
// Tennis functions

// mets à jour les services gagnants
void majServiceGagnant(unsigned char joueur){
	// stats
	// si le joueur auquel on ajoute un point (joueur=MOI=1 ou LUI=0) est
	// le joueur au service (c'est moi ssi jeSuisAuService0.nb = 1)
	if(jeSuisAuService0.nb == joueur){
		servGagn[0][joueur][numManche()]++;
	} else {
		servPerd[0][1-joueur][numManche()]++;
	}
}

// augmente le score du joueur
// joueur peut valoir MOI =1 car en bas de l'écran, ou LUI = 0 car en haut de l'écran, cf defines dans globalVar.h.
void augmenterScore(unsigned char joueur){
	unsigned char max; // max sert à stocker le numManche();,avant increment de nbManches
	out_bz_short();
	saveSit();

	tennisLastPointChangeMinute=totalMinute(&watch.shortTime);
	tennisOntLAirDEtreEnTrainDeJouer=1;
	max=numManche();

	if(tennisAZero){
		tennisAZero=0;
		tennisStartingMinute=totalMinute(&watch.shortTime);
		if(bluetoothMode.nb==BL_COUNTER)
		{
			ISET_FINS(sndData[0], CONN_SETUP_NEW, TRUE);
			ISET_FINS(sndData[0], CONN_SETUP_PEER_STATUS, 	NOT_A_PEER_STATUS_UPDATE);
			ISET_FINS(sndData[0], CONN_SETUP_PEER_MODE, 	SMARTPHONE_MODE);
			sendUartData(CONNECTION_SETUP, sndData, 1);
		} else if(bluetoothMode.nb==BL_PARTNER)
		{
			ISET_FINS(sndData[0], CONN_SETUP_NEW, TRUE);
			ISET_FINS(sndData[0], CONN_SETUP_PEER_STATUS, 	NOT_A_PEER_STATUS_UPDATE);
			ISET_FINS(sndData[0], CONN_SETUP_PEER_MODE, 	PARTNER_MODE);
			sendUartData(CONNECTION_SETUP, sndData, 1);
		}
	}

	if(!matchFini()){
		if (stbEnCours()){ // cas stb
			augmenterVarAff(&scoreJeu0[joueur]);
			if(scoreJeu0[joueur].nb>=10 && (scoreJeu0[joueur].nb>=scoreJeu0[1-joueur].nb + 2)){ // fin du stb
				setTabNb(joueur, max, scoreManche[0][joueur][max]+1, c0);
				majServiceGagnant(joueur);
				nbManches[0][joueur]++;
			} else { // le stb continue
				if((scoreJeu0[joueur].nb+scoreJeu0[1-joueur].nb)%2==1){
					augmenterVarAff(&(jeSuisAuService0));
					out_bz_short();
				}
			}
		} else { // fin cas stb
			if(tbEnCours()){ // cas tb
				augmenterVarAff(&scoreJeu0[joueur]);
				if(scoreJeu0[joueur].nb>=7 && (scoreJeu0[joueur].nb >= scoreJeu0[1-joueur].nb+2)){ // fin du tb
					// on augmente le score du jeu :
					setTabNb(joueur, max, scoreManche[0][joueur][max]+1,c0);
					majServiceGagnant(joueur);
					if(scoreJeu0[1-joueur].nb==0){
						jeuxBlancs[0][joueur][max]++;
					}
					nbManches[0][joueur]++;
					if(! matchFini())
						dispAllTabNb(c0);
					setVarAffValue(&scoreJeu0[joueur],0);
					setVarAffValue(&scoreJeu0[1-joueur],0);
					setVarAffValue(&jeSuisAuService0,1-serveurDebutTb[0]);
					out_bz_short();
				} else{ // le tb continue
					if((scoreJeu0[joueur].nb+scoreJeu0[1-joueur].nb)%2==1){
						augmenterVarAff(&jeSuisAuService0);
						out_bz_short();
					}
				}
			} else { // fin cas tb
				if(scoreJeu0[1-joueur].nb==50){
					setVarAffValue(&(scoreJeu0[1-joueur]),40);
				} else if(scoreJeu0[joueur].nb <= 30){
					setVarAffValue(&(scoreJeu0[joueur]), suivant(scoreJeu0[joueur].nb));
				} else {// if (scoreJeu0[joueur].nb==40 || scoreJeu0[joueur].nb==50) && (scoreJeu0[joueur].nb < 50)
					if(avantageActive.nb && scoreJeu0[joueur].nb == 40 && scoreJeu0[1-joueur].nb==40){
						setVarAffValue(&(scoreJeu0[joueur]),50);
					} else { // either i have 40 and (not avantageActive), either i have 50 and avantageActive. So i win the game
						if(scoreJeu0[1-joueur].nb==0){
							jeuxBlancs[0][joueur][max]++;
						}
						setVarAffValue(&(scoreJeu0[joueur]),0);
						setVarAffValue(&(scoreJeu0[1-joueur]),0);
						majServiceGagnant(joueur); // doit etre avant
						// la ligne augmenterVarAff(&jeSuisAuService0)
						augmenterVarAff(&jeSuisAuService0);

						// on augmente le score du jeu :
						setTabNb(joueur, max, scoreManche[0][joueur][max]+1,c0);

						// do i win the set ?
						 // if (! tbActive) : more or equal to 6 and with an advance of two games
						// same rule if tbActive : if we are 6/5 we don't win, we win if 7/5 or 6/4. But here 8/6 is not reachable because if 6/6, tb.
						// the case 7/6 was already treated above in the function
						if(scoreManche[0][joueur][max] >= nbJeuxGagnantsUneManche.nb && scoreManche[0][joueur][max] >= 2+scoreManche[0][1-joueur][numManche()]){
							nbManches[0][joueur]++;
							if(! matchFini())
								dispAllTabNb(c0);
						}
						out_bz_short();
					}
				}
			}
		}
	}

	if(matchFini()){
		flagEndMatchNow=1;
		mettreMode(TENNIS_END);
	}

	else if(chgtCote())
		mettreMode(TENNIS_CHANGE_SIDE);

	else if(tbCommence()){
		mettreMode(TENNIS_TIE_BREAK);
		serveurDebutTb[0] = jeSuisAuService0.nb;
	}

	else if(stbCommence()){
		mettreMode(TENNIS_STB);
		serveurDebutTb[0] = jeSuisAuService0.nb;
	}

}


// pour savoir si le match a commence. Si c'est le cas le chrono represente le temps du tennis.
unsigned char tennisCommence(){
	return ( scoreJeu0[MOI].nb || scoreJeu0[LUI].nb || scoreManche[0][MOI][0] || scoreManche[0][LUI][0] ) ;
}

// pour savoir si un tie-break a commencé
unsigned char tbCommence(){
	return (tbEnCours() &&
					scoreJeu0[0].nb==0 &&
					scoreJeu0[1].nb==0);
}

// pour savoir si un super-tie-break a commencé
unsigned char stbCommence(){
	return (stbEnCours() &&
					scoreJeu0[0].nb==0 &&
					scoreJeu0[1].nb==0);
}

// apres avoir clignoté qu'il fallait changé de côté, il faut revenir au bout de 4 secondes automatiquement en mode TENNIS
// Ceci est fait grace à un waitAndDo, avec comme fonction finale un pointeur vers actionFinClignotementChangeSide
void actionFinClignotementChangeSide(){
	if(brothersModes(mode,TENNIS)){
		if(matchFini()){
			flagEndMatchNow=1;
			mettreMode(TENNIS_END);
		}
		else if(tbCommence())
			mettreMode(TENNIS_TIE_BREAK);
		else if (stbCommence())
			mettreMode(TENNIS_STB);
		else
			mettreMode(TENNIS);
	}
}

// semblable à la fonction précédente, mais pour le cas du tie-break ou du super-tie-break.
void actionFinClignotementTbOuStb(){
	tennisMode[0] = 0;
	if(brothersModes(mode,TENNIS)){
		mettreMode(TENNIS);
	}
}

// Affiche le score du jeu. Si on est à 50, on affiche Ad (advantage)
void commentAfficherScoreJeu(VarAff * v){//unsigned char a, unsigned char b, unsigned char n){
	if(v->nb!=50)
		afficherNbSur7Seg(v->nb, v->contenu.varAffSpecial1.x, 1);
	else{
		afficherSeqSur7Seg(v->contenu.varAffSpecial1.x, 0, advantageChar[0]);
		afficherSeqSur7Seg(v->contenu.varAffSpecial1.x, 1, advantageChar[1]);
	}
}

// Place dans l'écran SW le score du jeu. Si on est à 50, on affiche Ad (advantage)
void commentPlacerDansEcranScoreJeu(VarAffSpecial1 * v){
	ecran.aff7Seg[v->x][v->y].type=SPECIAL1_7;
	//ecran.lesVarAff7Seg[v->x][v->y]=v;
}

// permet de faire abandonner un joueur
// cette fonction est appelée en cas d'appui long sur S2 ou S3 quand on est en mode tennis.
void abandon(unsigned char joueur){
	saveSit();
	tennisLastPointChangeMinute=totalMinute(&watch.shortTime);
	tennisOntLAirDEtreEnTrainDeJouer=0; // fin de match

	abandonne[joueur]=1;

	flagEndMatchNow=1;
	mettreMode(TENNIS_END);
}

