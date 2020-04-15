#include "compteur.h"
#include "globalVar.h"
#include "init.h"
#include "lcd8a.h"
#include "interruptBoutons.h"
#include "buzzer.h"
#include "backlight.h"
#include "varAff.h"
#include "ecranPourClignotements.h"

// Un compteur pour le joueur, un autre pour l'adversaire
VarAff compteur[2];

unsigned char compteurLastPoint;
unsigned char compteurMemoire=0;

// initialisation du compteur, appelée apres un reset du seiko, via la fonction commence()

void initCompteur(){
	setBounds(&compteur[LUI], 0, 99, 0);
	compteur[LUI].type=INT7;
	setPosInt7(&(compteur[LUI]),LUI,0,1); // position 0,0 ; forcé à 2 chiffres

	setBounds(&compteur[MOI], 0, 99, 0);
	compteur[MOI].type=INT7;
	setPosInt7(&(compteur[MOI]),MOI,0,1); // position 1,0 ; forcé à 2 chiffres
}

// action faite dès l'entrée dans le mode COUNTER ou un de ses subModes
void prepareDisplayCompteur(){
	mettreSurEcranForceSymbole(SYMBOL_INDEX_SEPARATION);

	placerDansEcran(&(compteur[MOI]));
	placerDansEcran(&(compteur[LUI]));

	if(mode == COMPTEUR_RAZ){
		mettreAuClignotementTexte(0, "SCORE");
		mettreAuClignotementTexte(1, "  =0 ");
	}
}

// Action à réaliser lors d'un appui sur un bouton quand on est en mode compteur (ou un de ses submodes)

void actionModeCompteur(unsigned char typeEvenement){
	switch(mode){
	case COMPTEUR:
		switch(typeEvenement){
		case BOUTON1COURT:
			lightOn();
		break;
		case BOUTON2COURT:
			if(compteur[LUI].nb<=98){
				augmenterVarAff(&compteur[LUI]);
				compteurLastPoint<<=1;
				if(compteurMemoire<=7){
					compteurMemoire++;
				}
			}
		break;
		case BOUTON3COURT:
			if(compteur[MOI].nb <=98){
				augmenterVarAff(&compteur[MOI]);
				compteurLastPoint<<=1;
				compteurLastPoint|=0x01; //equivalent a +=1 car le bit des unites vaut 0
				if(compteurMemoire<=7){
					compteurMemoire++;
				}
			}
		break;
		case BOUTON4COURT:
		case BOUTON4AFTEROTHER:
			mettreMode(WATCH);
		break;
		case BOUTON1LONG:
			mettreMode(COMPTEUR_RAZ);
		break;
		case BOUTON2ET3:
			if(compteur[MOI].nb > 0 && (compteurLastPoint & 0x01) && compteurMemoire > 0){
				diminuerVarAff(&compteur[MOI]);
				compteurMemoire--;
				compteurLastPoint>>=1;
			} else if (compteur[LUI].nb > 0 && !(compteurLastPoint & 0x01) && compteurMemoire > 0){
				diminuerVarAff(&compteur[LUI]);
				compteurMemoire--;
				compteurLastPoint>>=1;
			}
		break;
		}
	break;

	case COMPTEUR_RAZ:
		switch(typeEvenement){
		case BOUTON1COURT:
			mettreMode(COMPTEUR);
		break;
		case BOUTON2COURT:
		case BOUTON3COURT:
			setVarAffValue(&(compteur[MOI]),0);
			setVarAffValue(&(compteur[LUI]),0);
			compteurMemoire=0;
			compteurLastPoint=0;
			mettreMode(COMPTEUR);
		break;
		case BOUTON4COURT:
			mettreMode(COMPTEUR);
		break;

		}

	break;
	}
}


