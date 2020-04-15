#include "bluetooth.h"
#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "globalVar.h"
#include "lcd8a.h"
#include "interruptBoutons.h"
#include "interruptTime.h"
#include "init.h"
#include "lcd8a.h"
#include "tennis.h"
#include "watch.h"
#include "time.h"
#include "t16_ch0_smallDelays.h"
#include "buzzer.h"
#include "backlight.h"
#include "test.h"
#include "t16b_ch1_verySmallDelays.h"

#include "varAff.h"
#include "ecranPourClignotements.h"

#include "iSetService.h"
#include "que.h"


/////////////////////////////////
//VarAff searchOtherDevice;
unsigned char flagEndMatchNow;
unsigned char searchOtherDevice=0;
unsigned char oadUpdateSuccessfull;
unsigned char matchUUID[4];

MatchSetup matchSetup;
ScoreUpdate scoreUpdate;
MatchStatistics stats;

// pendant le match sera mis à BL_PARTNER ou BL_COUNTER si une deconnexion involontaire intervient
//unsigned char blModeAvantDeconnexion=BL_OFF;

unsigned char countDownPairingStopped;

// Variable où on précise si le pairing s'est bien passé
unsigned char peerConnected=0; // used as a bool (could be used as an integer if multiple connexion become possible)

//unsigned char autreMontreWantedConnected=0; // used as a bool (could be used as an integer if multiple connexion become possible)
//unsigned char phoneWantedConnected=0; // same comment as partnerConnecte

// Noms à afficher à la fin du pairing.
char nomPeer[20]="NAME PHONE";//"YOUR WATCH    ";
char nomDeCetteMontre[20]="MY WATCH";//"MY WATCH      ";

// le chiffre 1 est mis là car pour mettre un nombre sur l'écran on utilise un pointeur sur ce nombre
// (cf arguments de mettreSurEcranNombre)
// Le un est affiché lors de la fin d'un pairing
unsigned char chiffreUn=1;

// Acknowledgement apres un reset sw du CC
unsigned char ack=0;

// Cette variable dit si on est en bluetooth off (cas où bluetoothMode.nb==BL_OFF==0),
// ou bien counter (BL_COUNTER)
// ou bien partner (BL_PARTNER).
// A mettre a jour avec setVarAffValue(&bluetoothMode, ...), car si on fait directement
// bluetoothMode.nb = ..., le changement n'est pas affiché à l'écran.
VarAff bluetoothMode;

// Textes à afficher pendant le pairing
char pairingTxtPartner[20] = "SEARCH COUNTER";//"PAIRING";
char pairingTxtCounterPartner[20] = "SEARCH PARTNER";//"PAIRING";
char pairingTxtCounterSmartphone[13]= "SEARCH PHONE";

// update oad now or later (0 == later, 1== now)
char laterOrNow[2][5] = {"LATER", "  NOW" };

//////////////////////

// un time-out qui décroit pendant le pairing
VarAff btConnexionTimeLeft;

// vaut 0 ou 1 si on veut lancer l'update oad maintenant ou plus tard
VarAff shouldStartOad;

// Variable utilisée pour éviter que le counter envoie des frames trop rapidement au partner, ce
// qui risquerait de faire bugger la transmission.
unsigned char doitEnvoyerScoreBluetooth=0;

void traiterTrameRecue(iSetFrameBuffer_t *frameBuffer);
void rcvTennisScoreFromBluetooth(unsigned char *ptr);
void sndTennisScoreWithBluetooth();
void finirPairing();

//////////////////:

void askOadToStart(){
	reset_radio();
	askOadToStartWithoutReset();
}


void askOadToStartWithoutReset(){
	 sndData[0]=versionWatch.nb;
	 sndData[1]=subVersionWatch.nb;
	 sendUartData(SEIKO_SW_VERSION, sndData, 2);
}

////////////////////////////

// Le réglage de blMode implique à la fois un changement de texte et un changement de symbole,
// D'où cette fonction spéciale
//void commentAfficherBlMode(VarAff* v){//unsigned char a, unsigned char b, unsigned char n){
//	if(v->nb==BL_OFF){
//		reset_radio();
//	}
//
//	if(mode == TENNIS_SETTING_BLUETOOTH){
//		afficherTexteSur14Seg(&(bluetoothStrings[0][0])+5*v->nb, v->contenu.varAffSpecial2.x);
//		mettreAuClignotementPasForceSymbole(SYMBOL_INDEX_S1, &(bluetoothMode.nb), 0);
//		depile(&ecran.quiClignote, SYMBOL_INDEX_BT);
//		setSymbole(SYMBOL_INDEX_BT, v->nb);
//		searchOtherDevice=0;
//	}
//	else{
//		if( ! searchOtherDevice ){
//			depile(&ecran.quiClignote, SYMBOL_INDEX_BT);
//			setSymbole(SYMBOL_INDEX_BT, v->nb);
//		} else {
//			mettreAuClignotementForceSymbole(SYMBOL_INDEX_BT);
//		}
//	}
//}

// Fonction appelee a chaque fois qu'on modifie bluetoothMode, juste apres l'avoir modifié avec
// setVarAffValue.
// Le réglage de blMode implique à la fois un changement de texte et un changement de symbole,
// D'où cette fonction spéciale
// Pour simplifier on plot directement les donnees au lieu d'attendre afficheEcranAll()
void commentPlacerDansEcranBlMode(){
	if(mode == TENNIS_SETTING_BLUETOOTH){
		ecran.aff14Seg[bluetoothMode.contenu.varAffSpecial2.x].type=SPECIAL2_14;
		afficherTexteSur14Seg(&(bluetoothStrings[0][0])+5*bluetoothMode.nb, bluetoothMode.contenu.varAffSpecial2.x);
		mettreAuClignotementPasForceSymbole(SYMBOL_INDEX_S1, &(bluetoothMode.nb), 0);
		depile(&ecran.quiClignote, SYMBOL_INDEX_BT);
		setSymbole(SYMBOL_INDEX_BT, bluetoothMode.nb);
		searchOtherDevice=0;
	}
	else{
		if( ! searchOtherDevice ){
			depile(&ecran.quiClignote, SYMBOL_INDEX_BT);
			mettreSurEcranPasForceSymbole(SYMBOL_INDEX_BT, &(bluetoothMode.nb), 0);
			setSymbole(SYMBOL_INDEX_BT, bluetoothMode.nb);
		} else {
			mettreAuClignotementForceSymbole(SYMBOL_INDEX_BT);
		}
	}
}




/////////////////////////

// On se prepare à envoyer la trame de match setup.
void setMatchSetup(){
	matchSetup.bit.advantage=avantageActive.nb;
	matchSetup.bit.isShortMatch=tbType.nb;
	matchSetup.bit.matchFormat=nbManchesGagnantes.nb-2;
	matchSetup.bit.nGame=nbJeuxGagnantsUneManche.nb-3;
	matchSetup.bit.counterServes=jeSuisAuService0.nb; // car je est le counter
	matchSetup.bit.stb=stbActive.nb;
	matchSetup.bit.tb=tbActive.nb;
	memcpy(matchSetup.bit.matchUUID,matchUUID,4);
}

// On réceptionne la trame de match setup
void getMatchSetup(){
	avantageActive.nb=matchSetup.bit.advantage;
	tbType.nb=matchSetup.bit.isShortMatch;
	nbManchesGagnantes.nb=matchSetup.bit.matchFormat+2;
	nbJeuxGagnantsUneManche.nb=matchSetup.bit.nGame+3;

	if(bluetoothMode.nb == BL_PARTNER)
		setVarAffValue(&jeSuisAuService0, ! matchSetup.bit.counterServes);
	else // BL_COUNTER
		setVarAffValue(&jeSuisAuService0, matchSetup.bit.counterServes);

	stbActive.nb=matchSetup.bit.stb;
	tbActive.nb=matchSetup.bit.tb;

	// si les match UUID sont differents, on remplace l'ancien par le nouveau et
	// on raz le score pour recommencer une nouvelle partie.
	if(matchUUID[0] != matchSetup.bit.matchUUID[0] ||
	   matchUUID[1] != matchSetup.bit.matchUUID[1] ||
	   matchUUID[2] != matchSetup.bit.matchUUID[2] ||
	   matchUUID[3] != matchSetup.bit.matchUUID[3])
	{
		memcpy(matchUUID,matchSetup.bit.matchUUID,4);
		razTennis();
	}

	if(bluetoothMode.nb == BL_COUNTER){
		//wait_general(2000);
		//actionsCounterApresUpdateScore();
//		sndTennisScoreWithBluetooth();
		sndScoreBluetooth200Ms();
	}
}

// On réceptionne la trame de matchSetup
void storeMatchSetup(unsigned char *data){
	memcpy(matchSetup.reg, data, LENGTH_MATCH_SETUP);
	getMatchSetup();
}

// on envoie la trame de matchSetup
void sndMatchSetup(){
	setMatchSetup();
	memcpy(&sndData[0], matchSetup.reg, LENGTH_MATCH_SETUP); // retrieve matchSetup data
	sendUartData(MATCH_PARAMETERS, sndData, LENGTH_MATCH_SETUP);
}

/////////////////////////
// Initalisations

// permet d'avoir l'horloge clk1 sur le port FOUT
void initFout(void){
	P1IOEN_P16IEN=0;
	P1IOEN_P16OEN=1;

	P1MODSEL_P16SEL=0;

	P1FNCSEL_P16MUX=0; // Ici le port P16 sert pour FOUT, donc 0 (cf doc partie 6.7.2)

	P1MODSEL_P16SEL=1;

	CLGFOUT_FOUTSRC = 0x1;
	CLGFOUT_FOUTDIV = 0x0;
	CLGFOUT_FOUTEN = 1;
}

// réveille le CC juste avant de lui envoyer une trame
void wakeup_ble(){
	int i;
	P3IOEN_P32IEN=0;
	P3IOEN_P32OEN=1;

	CC254X_WAKEUP=1;
	// wait 1ms
	for( i=1 ;i<=64; i++){ }
	CC254X_WAKEUP=0;
//	mettreSurEcranForceSymbole(SYMBOL_INDEX_BT);
}

// Reset SW du CC
void arret_ble(){
	//desactiverBit(btSymbol);
	sndData[0]=0x02; // watch_cmd.ble_mode = 0
	sendUartData(BLE_CMD, sndData, 1);

	wait_general(250);

	if(ack){ // rien à faire
		ack=0;
	} else { // il y a eu un pb
		reset_radio();
	}
}

// Initialise les ports de wake-up et de reset du CC,
// cf premiere slide de la spec excel
void initDiversBluetooth(){
	//P31 output a 0
	P3IOEN_P31IEN=0;
	P3IOEN_P31OEN=1;
	P3DAT_P31OUT=0;

	// P32 input --> attention le port de wake-up est aussi utilisé en lecture
	P3IOEN_P32IEN=1;
	P3IOEN_P32OEN=0;

	//P02 output a 0
	P0IOEN_P02IEN=0;
	P0IOEN_P02OEN=1;
	P0DAT_P02OUT=0;
}

// Reset HW du CC
void reset_radio(){
	P3IOEN_P32IEN=0;
	P3IOEN_P32OEN=1;

	// reset cheap TI actif
	CC254X_RESET=0;
	CC254X_WAKEUP=0;

	// attends 100ms
	wait_general(100);

	// reset cheap TI inactif
	CC254X_RESET=1;

	tail = 0;
	head=0;
	peerConnected=0;
//	setVarAffValue(&bluetoothMode,BL_OFF); // --> non crée parfois une boucle infinie
	searchOtherDevice=0;

	// attends 1.1s par précaution, pour laisser le temps nécessaire au CC pour se réinitialiser
	wait_general(1100);
}

// Initialise la connexion
// N'est plus appelée aujourd'hui, peut être supprimé mais à garder quelques temps au cas où
void initConnexion(){
	peerConnected=0; // used as a bool (could be used as an integer if multiple connexion become possible)
//	typeConnexion=1;
}


///////////////////////////////////////

// Initialise les variables de la bluetooth.
void initConstantesBluetooth(){
	setBounds(&shouldStartOad,  0, 1, 1);
	shouldStartOad.type=STR;
	setPosString(&shouldStartOad, &(laterOrNow[0][0]), 1 );

	setBounds(&btConnexionTimeLeft,  0, 60, 60);
	btConnexionTimeLeft.type=INT7;
	setPosInt7(&btConnexionTimeLeft, 1, 1, 1);

	setBounds(&(bluetoothMode), 0, 2, 0);
	bluetoothMode.type=SPECIAL2;
	bluetoothMode.contenu.varAffSpecial2.x=1;
	bluetoothMode.contenu.varAffSpecial2.y=2;
	bluetoothMode.toDisplayIfChanged=1;

	memset(nomPeer,' ',20);
	strcpy(nomPeer,"NOM PHONE");

	memset(nomDeCetteMontre,' ',20);
	strcpy(nomDeCetteMontre,"MA MONTRE");
}

// Fonction appelée à l'entrée dans les modes
// TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE
// TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER
// et TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER
void prepareDisplayBluetoothPairing(){
	unsigned char *textAuDefilement;

	mettreAuClignotementForceSymbole(SYMBOL_INDEX_BT);

	if(! peerConnected){
		countDownPairingStopped=0;
		setPosInt7(&btConnexionTimeLeft, 0, 1, 1);
		placerDansEcran(&btConnexionTimeLeft);

		ecran.aff7Seg[1][0].type=TOURNANT;
//		mettreAuClignotementTexte(1, "PHONE");
		switch(mode){
			case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE:
				btConnexionTimeLeft.nb=15;
				textAuDefilement = pairingTxtCounterSmartphone;
				break;
			case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER:
				btConnexionTimeLeft.nb=30;
				textAuDefilement = pairingTxtCounterPartner;
				break;
			case TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER:
			default:
				btConnexionTimeLeft.nb=45;
				textAuDefilement = pairingTxtPartner;
				break;
		}
		mettreAuDefilement(0, textAuDefilement);

	} else {
//		if(mode == TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE){
//			peerConnected=0;
//		}
		countDownPairingStopped=1;
		mettreSurEcranNombre7Seg(0, 0, &chiffreUn, 0);
//		mettreAuClignotementDefilement(0, nomPeer);
		waitAndDo(1,&mettreModeTennis);
	}
}


///////////////////////////////

// envoi le score du bluetooth ssi un temps suffisant a passé depuis le dernier envoi de score
// cela évite ainsi des envois qui se succèderai trop rapidement.
// Cette fonction est appelée par sndScoreBluetooth200Ms(), voir explications dans le commentaire de
// sndScoreBluetooth200Ms()
void sndTennisScoreWithBluetoothConditionnally(){
	if(doitEnvoyerScoreBluetooth){
		// Send score
		// 100 --> 100/128 secondes, environ 0.8 secondes
		waitAndDoShortTimesT16B1(100, sndTennisScoreWithBluetoothConditionnally);
		sndTennisScoreWithBluetooth();
		doitEnvoyerScoreBluetooth=0;
	}
}

// envoie le score du tennis
void sndTennisScoreWithBluetooth(){
	scoreUpdate.bit.counterAbandon=abandonne[MOI];
	scoreUpdate.bit.partnerAbandon=abandonne[LUI];

	scoreUpdate.bit.counter1=scoreManche[0][MOI][0]  ;
	scoreUpdate.bit.partner1=scoreManche[0][LUI][0] ;
	scoreUpdate.bit.counter2=scoreManche[0][MOI][1] ;
	scoreUpdate.bit.partner2=scoreManche[0][LUI][1] ;
	scoreUpdate.bit.counter3=scoreManche[0][MOI][2]  ;
	scoreUpdate.bit.partner3=scoreManche[0][LUI][2] ;
	scoreUpdate.bit.counter4=scoreManche[0][MOI][3]  ;
	scoreUpdate.bit.partner4=scoreManche[0][LUI][3] ;
	scoreUpdate.bit.counter5=scoreManche[0][MOI][4]  ;
	scoreUpdate.bit.partner5=scoreManche[0][LUI][4] ;

	scoreUpdate.bit.currentGameScorePartner=scoreJeu0[LUI].nb;
	scoreUpdate.bit.currentGameScoreCounter=scoreJeu0[MOI].nb;
	scoreUpdate.bit.counterAuService=jeSuisAuService0.nb; // car je suis le counter
	scoreUpdate.bit.changeSide=chgtDeCoteEnCours[0];
	scoreUpdate.bit.setsWonByCounter=nbManches[0][MOI];
	scoreUpdate.bit.setsWonByPartner = nbManches[0][LUI];

	if(matchFini())
		scoreUpdate.bit.gameOver = 1;
	else
		scoreUpdate.bit.gameOver = 0;

	if (chgtCote())
		scoreUpdate.bit.changeSide=1 ;
	else
		scoreUpdate.bit.changeSide=0 ;

	if(tbCommence())
		scoreUpdate.bit.tieBreak=1 ;
	else
		scoreUpdate.bit.tieBreak=0 ;

	if(stbCommence())
		scoreUpdate.bit.superTieBreak =1;
	else
		scoreUpdate.bit.superTieBreak=0;

	memcpy(sndData,scoreUpdate.reg,LENGTH_SCORE_UPDATE);

	sendUartData(SCORE_UPDATE, sndData, LENGTH_SCORE_UPDATE);

	// !!! pour test debug scoreStatistics ou matchSetup
//	wait_general(400);
//	sndMatchSetup();
//	sndStatistics();
	// !!! fin du test
}

// reçois le score du tennis
void rcvTennisScoreFromBluetooth(unsigned char *ptr){
	tennisOntLAirDEtreEnTrainDeJouer=1;

  memcpy(scoreUpdate.reg,ptr,LENGTH_SCORE_UPDATE);

  abandonne[LUI] = scoreUpdate.bit.counterAbandon;
	abandonne[MOI] = scoreUpdate.bit.partnerAbandon;

//  scoreManche[0][LUI][0]=scoreUpdate.bit.counter1  ;
//  scoreManche[0][MOI][0]=scoreUpdate.bit.partner1 ;
//  scoreManche[0][LUI][1]=scoreUpdate.bit.counter2  ;
//  scoreManche[0][MOI][1]=scoreUpdate.bit.partner2 ;
//  scoreManche[0][LUI][2]=scoreUpdate.bit.counter3  ;
//  scoreManche[0][MOI][2]=scoreUpdate.bit.partner3 ;
//  scoreManche[0][LUI][3]=scoreUpdate.bit.counter4  ;
//  scoreManche[0][MOI][3]=scoreUpdate.bit.partner4 ;
//  scoreManche[0][LUI][4]=scoreUpdate.bit.counter5  ;
//  scoreManche[0][MOI][4]=scoreUpdate.bit.partner5 ;
//  afficherVarAff(scoreManche0);
	setVarAffValueWithPointer(&scoreManche0, &scoreUpdate);

	setVarAffValue(&scoreJeu0[MOI],scoreUpdate.bit.currentGameScorePartner);
	setVarAffValue(&scoreJeu0[LUI],scoreUpdate.bit.currentGameScoreCounter);
	setVarAffValue(&jeSuisAuService0,! scoreUpdate.bit.counterAuService); // car je suis le partner
	chgtDeCoteEnCours[0]=scoreUpdate.bit.changeSide ;
	nbManches[0][LUI]=scoreUpdate.bit.setsWonByCounter;
	nbManches[0][MOI]=scoreUpdate.bit.setsWonByPartner;

	if(scoreUpdate.bit.gameOver){//matchFini()){
		flagEndMatchNow=1;
		tennisOntLAirDEtreEnTrainDeJouer=0;
		mettreMode(TENNIS_END);
	}	else if(scoreUpdate.bit.changeSide){//chgtCote())
		mettreMode(TENNIS_CHANGE_SIDE);
	}	else if(scoreUpdate.bit.tieBreak){//tbCommence()){
		mettreMode(TENNIS_TIE_BREAK);
		serveurDebutTb[0] = jeSuisAuService0.nb;
	}	else if(scoreUpdate.bit.superTieBreak){//stbCommence()){
		mettreMode(TENNIS_STB);
		serveurDebutTb[0] = jeSuisAuService0.nb;
	}	else {
		mettreMode(TENNIS);
		}
}


// envoie les statistiques
void sndStatistics(){
	// Code de debug de Jean-Christophe
	//memset((char *)&stats.bit.matchUUID[0], 0xAB, 4);
	memcpy((char *)&stats.bit.matchUUID[0],&matchUUID,4);

	stats.bit.counterAbandonStats=abandonne[MOI];
	stats.bit.partnerAbandonStats=abandonne[LUI];
	stats.bit.matchDateYear  = watch.year.nb;
	stats.bit.matchDateMonth = watch.month.nb;
	stats.bit.matchDateDay = watch.dayOfMonth.nb;
	stats.bit.setsCounter= nbManches[0][MOI];
	stats.bit.setsPartner=nbManches[0][LUI];

		stats.bit.setScoreCounter1=scoreManche[0][MOI][0];
		stats.bit.setScorePartner1=scoreManche[0][LUI][0];
		stats.bit.setTime1 = tennisSetMinutes[0];
		stats.bit.setSceGagnantCounter1 =servGagn[0][MOI][0]  ;
		stats.bit.setSceGagnantPartner1 = servGagn[0][LUI][0] ;
		stats.bit.setScePerdantCounter1 = servPerd[0][MOI][0] ;
		stats.bit.setScePerdantPartner1 = servPerd[0][LUI][0] ;
		stats.bit.setJeuxBlancsCounter1 =  jeuxBlancs[0][MOI][0] ;
		stats.bit.setJeuxBlancsPartner1 =  jeuxBlancs[0][LUI][0] ;

		stats.bit.setScoreCounter2=scoreManche[0][MOI][1];
		stats.bit.setScorePartner2=scoreManche[0][LUI][1];
		stats.bit.setTime2 = tennisSetMinutes[1];
		stats.bit.setSceGagnantCounter2 =servGagn[0][MOI][1]  ;
		stats.bit.setSceGagnantPartner2 = servGagn[0][LUI][1] ;
		stats.bit.setScePerdantCounter2 = servPerd[0][MOI][1] ;
		stats.bit.setScePerdantPartner2 = servPerd[0][LUI][1] ;
		stats.bit.setJeuxBlancsCounter2 =  jeuxBlancs[0][MOI][1] ;
		stats.bit.setJeuxBlancsPartner2 =  jeuxBlancs[0][LUI][1] ;

		stats.bit.setScoreCounter3=scoreManche[0][MOI][2];
		stats.bit.setScorePartner3=scoreManche[0][LUI][2];
		stats.bit.setTime3 = tennisSetMinutes[2];
		stats.bit.setSceGagnantCounter3 =servGagn[0][MOI][2]  ;
		stats.bit.setSceGagnantPartner3 = servGagn[0][LUI][2] ;
		stats.bit.setScePerdantCounter3 = servPerd[0][MOI][2] ;
		stats.bit.setScePerdantPartner3 = servPerd[0][LUI][2] ;
		stats.bit.setJeuxBlancsCounter3 =  jeuxBlancs[0][MOI][2] ;
		stats.bit.setJeuxBlancsPartner3 =  jeuxBlancs[0][LUI][2] ;

		stats.bit.setScoreCounter4=scoreManche[0][MOI][3];
		stats.bit.setScorePartner4=scoreManche[0][LUI][3];
		stats.bit.setTime4 = tennisSetMinutes[3];
		stats.bit.setSceGagnantCounter4 =servGagn[0][MOI][3]  ;
		stats.bit.setSceGagnantPartner4 = servGagn[0][LUI][3] ;
		stats.bit.setScePerdantCounter4 = servPerd[0][MOI][3] ;
		stats.bit.setScePerdantPartner4 = servPerd[0][LUI][3] ;
		stats.bit.setJeuxBlancsCounter4 =  jeuxBlancs[0][MOI][3] ;
		stats.bit.setJeuxBlancsPartner4 =  jeuxBlancs[0][LUI][3] ;

		stats.bit.setScoreCounter5=scoreManche[0][MOI][4];
		stats.bit.setScorePartner5=scoreManche[0][LUI][4];
		stats.bit.setTime5 = tennisSetMinutes[4];
		stats.bit.setSceGagnantCounter5 =servGagn[0][MOI][4]  ;
		stats.bit.setSceGagnantPartner5 = servGagn[0][LUI][4] ;
		stats.bit.setScePerdantCounter5 = servPerd[0][MOI][4] ;
		stats.bit.setScePerdantPartner5 = servPerd[0][LUI][4] ;
		stats.bit.setJeuxBlancsCounter5 =  jeuxBlancs[0][MOI][4] ;
		stats.bit.setJeuxBlancsPartner5 =  jeuxBlancs[0][LUI][4] ;

	memcpy(sndData, (const char *) stats.reg, LENGTH_STATISTICS);
	sendUartData(MATCH_STATISTICS, sndData, LENGTH_STATISTICS);
}

// reçois les statistiques
void receiveStatistics(){
	//TODO
}

// envoie la requete de l'adresse mac
void sndRequeteMac(){
	sndData[0]=0; // read operation
	sendUartData(CC254X_MAC_ADDRESS, sndData, 1);
}

// envoie la requete de la version soft du CC
void sndRequeteSwVersion(){
	sndData[0]=0; // read operation
	sendUartData(CC254X_SW_VERSION, sndData, 1);
}

// envoie la requete de l'alias
void sndRequeteAlias(){
	sndData[0]=0; // read operation
	sendUartData(CC254X_ALIAS, sndData, 1);
}


///////////////////////

// Envoi le score du bluetooth a condition qu'un score n'ai pas été envoyé dans les 800 (anciennement 200) dernieres
// millisecondes. Dans le cas contraire, mets doitEnvoyerScoreBluetooth à 1, ce qui aura pour effet à la fin du run,
// d'envoyer le score du bluetooth avec sndTennisScoreWithBluetoothConditionnally.
// Dans la pratique, afin de limiter la frequence des envois, on utilise donc sndScoreBluetooth200Ms au lieu de
// sndTennisScoreWithBluetooth
void sndScoreBluetooth200Ms(){
	if(T16B1CTL_RUN && actionAFaireTimerB1==sndTennisScoreWithBluetoothConditionnally)
		doitEnvoyerScoreBluetooth=1;
	else{
		//le seiko va envoyer le score ssi il y a eu un clic dans l'intervalle.
		doitEnvoyerScoreBluetooth=0;
		// 100 --> 100/128 secondes, environ 0.8 secondes
		waitAndDoShortTimesT16B1(100, sndTennisScoreWithBluetoothConditionnally);
		sndTennisScoreWithBluetooth();
	}
}


// On a besoin pour faire un waitAndDo d'avoir un pointeur de type (void *) void fonction (void)
// c'est a dire un pointeur vers une fonction sans entrée.
// D'où la création de cette fonction.
void actionApresMontrerCounterAuPartner(){
	mettreMode(TENNIS);
}


////////////////////////


// Cette fonction est appelée chaque seconde si on est en mode de pairing.
// elle permet de diminuer le compteur du pairing s'il est en route.
void actionSecondeBluetoothWaitConnexion(){
	if(btConnexionTimeLeft.nb>0){
		//diminuerVarAff(&btConnexionTimeLeft);
		diminuerModulo(btConnexionTimeLeft.nb, btConnexionTimeLeft.min, btConnexionTimeLeft.max);
		// if(bluetoothMode.nb==BL_COUNTER)
		displayIfNecessary(&btConnexionTimeLeft);
	} else if(btConnexionTimeLeft.nb==0){
		actionMettreModeSuivantPairing();
	}
}

////////////////////////////////////////////

// Cette fonction est juste là pour pouvoir faire un waitAndDo avec donc un pointeur vers cette fonction,
// qui est bien une fonction sans entrée
void actionMettreModeTennis(){
	mettreMode(TENNIS);
}

// Cette fonction mets le mode suivant dans le pairing.
// Par exemple, si on est en counter, après le pairing avec le smartphone, on passe au pairing avec le partner.
void actionMettreModeSuivantPairing(){
	switch(mode){
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE:
		peerConnected=0;
		mettreMode(TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER);

		// Reset CC to start as a Counter now
		reset_radio();

		// Send command to CC
		ISET_FINS(sndData[0], CONN_SETUP_NEW, TRUE);
		ISET_FINS(sndData[0], CONN_SETUP_PEER_STATUS, 	NOT_A_PEER_STATUS_UPDATE);
		ISET_FINS(sndData[0], CONN_SETUP_PEER_MODE, 	COUNTER_MODE);
		sendUartData(CONNECTION_SETUP, sndData, 1);
		break;
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER:
	case TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER:
		finirPairing();
		break;
	}
}

// Cette fonction est appelée dans un waitAndDo, qui exige d'avoir un pointeur vers une fonction sans entrée
void endTheScreenOfSetupAborted(){
	mettreMode(TENNIS_SETTING_BLUETOOTH);
}

// Fonction de traitement des trames reçues du CC
void traiterTrameRecue(iSetFrameBuffer_t *frameBuffer)
{
unsigned char *ptr;
iSet_setupStatus status;
unsigned char peerStatus;
unsigned char peerMode;
unsigned char oadFlag;

ptr = frameBuffer->buffer;

switch(frameBuffer->cmd){ // switch sur l' Id de la trame
	case CC254X_OAD_STATUS:
		oadFlag=ISET_FEXT(*ptr, OAD);
		switch(oadFlag){
		case OAD_NEEDS_UPDATE :
			mettreMode(OAD_UPDATING);

			// Lancer la sequence de demarrage sur la target
			waitAndDoShortTimes(64, askOadToStartWithoutReset); // 64/128 --> une demi-seconde
			break;
//		case OAD_PROFILE_STARTED :
//			mettreMode(OAD_UPDATING);
//			break;
		case OAD_UPGRADE_SUCCESS :
			oadUpdateSuccessfull=1;
			mettreMode(OAD_END);
			break;
		case OAD_UPGRADE_FAILURE :
			oadUpdateSuccessfull=0;
			mettreMode(OAD_END);
			break;
		}
		break;

	case BLE_CMD :
		break;

	case BLE_REPORT :
		ack=1;
		break;

	case MATCH_PARAMETERS :
		// Store parameters sent by remote
		storeMatchSetup(ptr);
		break;

	case MATCH_PARAMETERS_REQUEST :
		// Send parameters to remote
		sndMatchSetup();
		break;

	case MATCH_STATISTICS:
		receiveStatistics(); // TODO
		break;

	case MATCH_STATISTICS_REQUEST:
		sndStatistics();
		break;

	case CONNECTION_SETUP :
		// connected ou disconnected --> cf iSetService.h :
//    NOT_A_PEER_STATUS_UPDATE = 0,
//    PEER_CONNECTED,
//    PEER_DISCONNECTED,
//    PEER_STATUS_NOT_USED
		peerStatus = ISET_FEXT(*ptr, CONN_SETUP_PEER_STATUS);

		// partner, smartphone ou counter --> cf iSetService.h :
		//    RETAIN_CURRENT_MODE = 0,
//    PARTNER_MODE, 				// PARTNER_MODE can
//    SMARTPHONE_MODE,    		// SMARTPHONE is COUNTER_PERIPHERAL -> First setup mode as COUNTER
//    COUNTER_MODE,       		// COUNTER_MODE is second counter mode as central
		peerMode = ISET_FEXT(*ptr, CONN_SETUP_PEER_MODE);

		// successfull ou aborted --> cf iSetService.h :
//    NOT_A_STATUS_UPDATE = 0,
//    SETUP_SUCCESSFULL,
//    SETUP_ABORDED
		status = ISET_FEXT(*ptr, CONN_SETUP_STATUS);

		if(NOT_A_STATUS_UPDATE!=status)
			viderEcran();  // Clear countdown and stuff like that

		if(peerStatus == PEER_CONNECTED)
		{
			peerConnected=1;
			searchOtherDevice=0;
			mettreSurEcranForceSymbole(SYMBOL_INDEX_BT);
			commentPlacerDansEcranBlMode();
			wait_general(500);
			sndScoreBluetooth200Ms();
		}
		else if(PEER_DISCONNECTED==peerStatus) // Normal game state, just a connection status update
		{
			peerConnected=0;
			searchOtherDevice=1;
			commentPlacerDansEcranBlMode();
		}

		// Check if we have a status update
		if(SETUP_SUCCESSFULL == status)
		{
			// these lines are a debug
			peerConnected=1;
			mettreSurEcranForceSymbole(SYMBOL_INDEX_BT);
			// the previous lines are a debug

			memcpy(nomPeer, ptr+1, 19);
			nomPeer[20]='\0';
			waitAndDo(7, &finirPairing);
		}
		else if(SETUP_ABORDED == status)
		{
			// On mets le mode d'aborted
			mettreMode(TENNIS_BLUETOOTH_CONNEXION_ABORTED);

			// On attend pour que l'utilisateur voie bien l'aborted. Si il clique quelque part on sort de cet ecran.
			waitAndDo(4, &endTheScreenOfSetupAborted);
			return;
		}

		if(NOT_A_STATUS_UPDATE != status )
		{
			// Display pairing stuff
			prepareDisplayBluetoothPairing();
		}

		afficheEcranAll();
		break;

	case SCORE_UPDATE :
		if (bluetoothMode.nb==BL_PARTNER)
		{
			tennisLastPointChangeMinute=totalMinute(&watch.shortTime);
			tennisOntLAirDEtreEnTrainDeJouer=1;
			rcvTennisScoreFromBluetooth(ptr);
			if( ! tennisCommence()) {// si le score est nul
				memset(tennisSetMinutes,0,5*sizeof(short));
				tennisStartingMinute=totalMinute(&watch.shortTime);
				tennisHour=0;
				tennisMinute=0;
				nbScoresSauvegardes=0;
			}
		}
		break;

	  case CC254X_MAC_ADDRESS:
		  memcpy(macNb,ptr,6);
		  mettreMacNbDansMacTexte();

		  if(mode==TEST_BL)
		  {
				mettreAuDefilement(1,macTexte);
				blSwRevTestTerminated = 1;

				// Now retrieve  SW version
				sendUartData(CC254X_SW_VERSION, sndData, 1);
		  }

		break;

	 case CC254X_SW_VERSION :
		 memcpy(swVersion,ptr,3);
		 if(mode==TEST_BL)
		 {
			placerDansEcran(&(versionBle));
			placerDansEcran(&(subVersionBle));
			setVarAffValue(&versionBle,swVersion[0]);
			setVarAffValue(&subVersionBle,swVersion[1]);
			blMACTestTerminated = 1;
		 }
		 waitAndDo(5, &endModeTest);
		break;

	 case SEIKO_SW_VERSION :
		 sndData[0]=versionWatch.nb;
		 sndData[1]=subVersionWatch.nb;
		 sendUartData(SEIKO_SW_VERSION, sndData, 2);
		break;

//	case KEEP_ALIVE:
	case NOT_A_VALID_CMD :
		break;

//	case CC254X_ALIAS:
//		break;

	default:
		break;
	}
}


///////////////////////////////////////

// Cette fonction est appelée quand pendingBuffQue a été rempli par ExtractFrame de la nouvelle trame.
// Dans ce cas ParseFrame appelle traiterTrameRecue.
void ParseFrame(void)
{
	iSetFrameBuffer_t *buffer = NULL;

	// Scan through buffers in queue and process available ones
	if((QUE_Handle)(buffer=QUE_dequeue(&pendingBuffQue))
			!=&pendingBuffQue)
	{
		traiterTrameRecue((iSetFrameBuffer_t*)buffer);
		// Put back buffer in free queue
        QUE_enqueue(&freeBuffQue, (QUE_Handle)buffer);
	}
}

// Termine le pairing
void finirPairing(){
	// Pour qu'il n'y ait pas la mise à BL_OFF si on ne met pas de point rapidement :
	tennisLastPointChangeMinute=totalMinute(&watch.shortTime);

    if( ! peerConnected) {
//    	reset_radio(); --> now automatically done at the beginning of setVarAffValue(&bluetoothMode,0);
//    	setVarAffValue(&bluetoothMode,BL_OFF);
    	setBluetoothModeValue(BL_OFF);
    }

    else if(bluetoothMode.nb == BL_COUNTER){ // && peerConnected puisqu'on a le else
    	sndTennisScoreWithBluetooth();
    }

    mettreMode(TENNIS);
}


