/***********
 * Ce fichier définit le mode de test
 * **********/

#include "boot.h"
#include "test.h"
#include "interruptBoutons.h"
#include "buzzer.h"
#include "backlight.h"
#include "globalVar.h"
#include "uart.h"
#include "bluetooth.h"
#include "lcd8a.h"
#include "t16_ch0_smallDelays.h"
#include "ecranPourClignotements.h"
#include "iSetService.h"
#include <string.h>
#include "wdt.h"
#include "fileDActions.h"

char motTest[10];
unsigned char compteurTest=0;

VarAff versionWatch;
VarAff subVersionWatch;
VarAff versionBle;
VarAff subVersionBle;

// fréquences min, cntr ou max : texte affiché
char texteFreq[4][5]={"     "," MIN ","CNTR "," MAX "};

// variable varAff dont le champ ".nb" valant 0 (pas d'émission), 1, 2 ou 3 (de basse à haute fréquence).
// peut etre reglé avec s2 et S3 lors du mode de test pour tester l'émission du CC
// a haute, moyenne et basse frequence
VarAff freqTestBl;

// adresse mac en tant que texte
char macTexte[22]="MAC-AA-BB-CC-DD-EE-FF"; // 22 dont un pour le '\0' de la fin

// adresse mac en tant que nombre
unsigned char macNb[6];

// version soft du seiko. Initialisé en fonction des valeurs
//SW_SEIKO_VERSION_NUMBER
//et
//SW_SEIKO_SUBVERSION_NUMBER
// definies dans globalVar.h
unsigned char swVersion[3];

// variables permettant de notigier qu'on a reçu respectivement l'adresse mac et la sw version du CC
unsigned char blMACTestTerminated;
unsigned char blSwRevTestTerminated;

unsigned char sortieAuto = 1;

// fonction permettant de coder mettreMacNbDansMacTexte
// marche si a est compris entre 0 et F inclus
char toTxt(unsigned char a){
	if(a<=9){
		return (0x30+a);
	} else if(a>=0x0A && a<=0x0F){
		return (a - 0x0A + 0x41); // + 0x37
	} else
		return (' ');
}

// mets l'adresse mac sous forme texte pour pouvoir la faire défiler à l'écran lorsqu'on la reçois.
void mettreMacNbDansMacTexte(){
	unsigned char i=0;
	for(i=0; i<=5; i++){
		macTexte[3*i+4]=toTxt((macNb[i] & 0xF0) >> 4);
		macTexte[3*i+5]=toTxt(macNb[i] & 0x0F);
	}
	macTexte[21]=0x00;
}

// initialise les positions et valeurs des variables utilisées dans le mode de test
void initConstantesTest(){
	versionWatch.type=INT7;
	versionWatch.nb=SW_SEIKO_VERSION_NUMBER;
	setPosInt7(&(versionWatch),0,0,0); // position 0,0 ; pas forcé à 2 chiffres

	subVersionWatch.type=INT7;
	subVersionWatch.nb=SW_SEIKO_SUBVERSION_NUMBER;
	setPosInt7(&(subVersionWatch),0,1,0);

	versionBle.type=INT7;
	versionBle.nb=1;
	setPosInt7(&(versionBle),1,0,0);

	subVersionBle.type=INT7;
	subVersionBle.nb=0;
	setPosInt7(&(subVersionBle),1,1,0);

	freqTestBl.type=STR;
	setBounds(&freqTestBl, 0, 3, 0);
	setPosString(&freqTestBl, &(texteFreq[0][0]), 0);
}

// action appelée à chaque fois qu'on entre dans le mode de test
void prepareDisplayTestBl(){
	mettreSurEcranForceSymbole(SYMBOL_INDEX_SEPARATION);

	blSwRevTestTerminated=0;
	blMACTestTerminated=0;

	placerDansEcran(&(versionWatch));
	placerDansEcran(&(subVersionWatch));
	mettreAuDefilement(1,macTexte);

	placerDansEcran(&(freqTestBl));
	//currentVarAff=&freqTestBl;

	// Activation de RTC1S sur P04, cf spec W15 paragraphe 9.2, et 6.7.1 (dernier tableau)
	// sera défait à la sortie du mode de test par la ligne :
	// mettrePortP0yEnBouton(4);
	P0IOEN_P04IEN=0;
	P0IOEN_P04OEN=1;
	P0MODSEL_P04SEL	=0;
	P0FNCSEL_P04MUX=0;
	P0MODSEL_P04SEL	=1;

	reset_radio();

	sndData[0]=0;
	sendUartData(CC254X_MAC_ADDRESS, sndData, 1);

	sortieAuto=1;
//	waitAndDo(6, &endModeTest);
}

void endModeTest(){
	sndData[0]=4; // arret du test
	sendUartData(RADIO_TESTS, sndData, 1);
	wait_general(4000);
	reset_radio();

	// on arrete le temps
	RTCCTL_RTCRUN = 0;
	// start le watch dog timer --> le temps est arrete donc il va declencher un reset dans 4 secondes
	// il y aura alors un appel à reset_radio() (reset hw du CC)
	initWdt();
	startWdt();
}

void cancelSortieAuto(){
	if(sortieAuto){
		enleverUneAction(&fileDActions, &endModeTest, 0 );
		sortieAuto=0;
	}
}

// actions à faire en cas d'appui sur un bouton en mode de test
void actionModeTest(unsigned char typeEvenement){
	if(mode ==TEST_BL ){
		switch(typeEvenement){
		case BOUTON2COURT:
			cancelSortieAuto();
			augmenterVarAff(currentVarAff);
			if(freqTestBl.nb==0)
				sndData[0]=4;
			else
				sndData[0]=freqTestBl.nb;
			sendUartData(RADIO_TESTS, sndData, 1);
			break;
		case BOUTON3COURT:
			cancelSortieAuto();
			diminuerVarAff(currentVarAff);
			if(freqTestBl.nb==0)
				sndData[0]=4;
			else
				sndData[0]=freqTestBl.nb;
			sendUartData(RADIO_TESTS, sndData, 1);
			break;

		default : // bouton 1 ou 4
				endModeTest();
			break;
		}
	}
}


void sequenceTest(){
	setLcd8aDisplayState(LCD8A_STATE_ALL_ON);
	out_bz_long();
	wait_general(6000); 	// attente 1.5s
	setLcd8aDisplayState(LCD8A_STATE_ALL_OFF);
	wait_general(2000);	// attente 1/2 s
}

// action faite lors de l'appui sur tous les boutons.
void testAffichage1(){
	unsigned char i;

	sequenceTest();
	lightOnSimple();
	for (i=1; i<=2; i++){
		sequenceTest();
	}
	lightOff();

	setLcd8aDisplayState(LCD8A_STATE_NORMAL);
	clearLcd();
	wait_general(100);
	mettreMode(TEST_BL);
}
