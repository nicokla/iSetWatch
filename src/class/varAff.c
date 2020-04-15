#include "varAff.h"
#include "lcd8a.h"
#include "ecranPourClignotements.h"
#include <string.h>
#include "tennis.h"
#include "globalVar.h"
//#include "math.h"
#include "bluetooth.h"
#include "watch.h"

VarAff enModif;

////////////////////////////



////////////////////////////

// pas trop utilisé à priori
void dispNb(unsigned char a,unsigned char b,ChiffresAff * c){
	ecran.aff14Seg[a].contenu.lettres[b]=(c->tabNb[a][b]%10)+0x30; // conversion en char
	afficherChiffreSur14Seg(a,b,
			(c->tabNb[a][b])%10);
}

// pas trop utilisé à priori
void disp2Nb(unsigned char b, ChiffresAff * c ){
	dispNb(0,b,c);
	dispNb(1,b,c);
}

// on utilise celui là
void dispAllTabNb(ChiffresAff * c){
	unsigned char j, max;

	ecran.aff14Seg[0].type=CHIFFRES;
	ecran.aff14Seg[1].type=CHIFFRES;

	max=numManche();

	for(j=0;j<=max && j<5;j++){
		disp2Nb(j, c);
	}
	for(;j<5;j++){
		ecran.aff14Seg[0].contenu.lettres[j]=' ';
		effacer14Seg(0,j);
		ecran.aff14Seg[1].contenu.lettres[j]=' ';
		effacer14Seg(1,j);
	}
}

// et on utilise celui là aussi
void setTabNb(unsigned char a, unsigned char b, unsigned char n, ChiffresAff * c){
	c->tabNb[a][b]=n;
	dispNb(a,b,c);
}

// pas trop utilisé à priori
void mettreSurEcranTabNb(unsigned char a, unsigned char b, ChiffresAff * c){
	ecran.aff14Seg[a].contenu.lettres[b]=(c->tabNb[a][b]%10)+0x30;
}

// pas trop utilisé à priori
void mettreSurEcranTabNbAll(ChiffresAff * c){
	unsigned char i, max;
	ecran.aff14Seg[0].type=CHIFFRES;
	ecran.aff14Seg[1].type=CHIFFRES;
	max = numManche();
	for(i=0;i<=max && i<5;i++){
		(ecran.aff14Seg[0].contenu.lettres)[i]=( ( ((c->tabNb)[0][i]) % 10) + 0x30 );
		(ecran.aff14Seg[1].contenu.lettres)[i]=( ( ((c->tabNb)[1][i]) % 10) + 0x30 );
	}
	for(;i<5;i++){
		ecran.aff14Seg[0].contenu.lettres[i]=' ';
		ecran.aff14Seg[1].contenu.lettres[i]=' ';
	}
}


///////////////////////////////
void placerDansEcran(VarAff * varAff){
	switch(varAff->type){
	case INT7:
		 mettreSurEcranNombre7Seg(
				 varAff->contenu.int7Seg.x,
				 varAff->contenu.int7Seg.y,
				 &(varAff->nb),
				 varAff->contenu.int7Seg.que2Chiffres);
		break;
	case INT14:
		mettreSurEcranNombre14Seg(
				varAff->contenu.int14Seg.x,
				&(varAff->nb),
				varAff->contenu.int14Seg.que2Chiffres);
		break;
	case BOOL:
		mettreSurEcranPasForceSymbole(
			varAff->contenu.boolAff.index,//SYMBOL_INDEX_PM pour pm/am cf setPosBool dans watch.c
			&(varAff->nb),
			0);
		if(varAff->contenu.boolAff.index_contraire_used)
			mettreSurEcranPasForceSymbole(
				varAff->contenu.boolAff.index_contraire,//SYMBOL_INDEX_AM pour pm/am cf setPosBool dans watch.c
				&(varAff->nb),
				1);
		break;
	case STR:
		mettreSurEcranTexte(
				varAff->contenu.stringChoice.zone14Seg,
				varAff->contenu.stringChoice.textes + (5 * (varAff->nb-varAff->min)));
		break;
	case SPECIAL1:
		commentPlacerDansEcranScoreJeu(&varAff->contenu.varAffSpecial1);
		break;
	case SPECIAL2:
		commentPlacerDansEcranBlMode();
		break;
	case SPECIAL3:
		commentPlacerDansEcran24HMode();
		break;
	case PLUSIEURS_CHIFFRES:
		mettreSurEcranTabNbAll(&(varAff->contenu.chiffresAff));
		break;
	case UNDEFINED:
		break;
	}
	varAff->toDisplayIfChanged=1;
}

void afficherVarAff(VarAff * varAff){
	switch (varAff->type){
	case INT7:
		if(varAff->contenu.int7Seg.que2Chiffres)
			afficherNbA2ChiffresSur7Seg(varAff->nb,varAff->contenu.int7Seg.x, 2*varAff->contenu.int7Seg.y+1);
		else
			afficherNbSur7Seg(varAff->nb,varAff->contenu.int7Seg.x, 2*varAff->contenu.int7Seg.y+1);
		break;
	case INT14:
		if(varAff->contenu.int14Seg.que2Chiffres)
			afficherNbA2ChiffresSur14Seg(varAff->nb,varAff->contenu.int14Seg.x, 4);
		else
			afficherNbSur14Seg(varAff->nb,varAff->contenu.int14Seg.x, 4);
		break;
	case BOOL:
		setSymbole(varAff->contenu.boolAff.index,varAff->nb);
		if(varAff->contenu.boolAff.index_contraire_used)
			setSymbole(varAff->contenu.boolAff.index_contraire,1-varAff->nb);
		break;
	case STR:
		afficherTexteSur14Seg(varAff->contenu.stringChoice.textes+5*(varAff->nb-varAff->min), varAff->contenu.stringChoice.zone14Seg);
		break;
	case PLUSIEURS_CHIFFRES:
		dispAllTabNb(&(varAff->contenu.chiffresAff));
		break;
//	case SPECIAL:
//		(*(varAff->contenu.varAffSpecial.commentAfficherVarAff))(
//				varAff->contenu.varAffSpecial.x,
//				varAff->contenu.varAffSpecial.y,
//				(varAff->nb));
//		break;
	case SPECIAL1:
		commentAfficherScoreJeu(varAff);
		break;
	case SPECIAL2:
//		commentAfficherBlMode(varAff);
		commentPlacerDansEcranBlMode();
		break;
	case SPECIAL3:
		commentAfficher24HMode();
		break;
	case UNDEFINED:
		break;
	}
}

void displayIfNecessary(VarAff * varAff){
	if(varAff->toDisplayIfChanged){
		if(varAff->type==STR && ecran.quiClignote.les14Seg[varAff->contenu.stringChoice.zone14Seg])
			placerDansEcran(varAff);
		afficherVarAff(varAff);
	}
}

// si varAff == &bluetoothMode, utiliser preferentiellement augmenterBluetoothMode()
// afin de garantir qu'on reset le CC si on met bluetoothMode à BL_OFF
void augmenterVarAff(VarAff * varAff){
	if(varAff->nb < varAff->max)
		setVarAffValue(varAff, varAff->nb+1);
	else
		setVarAffValue(varAff, varAff->min);

// lignes equivalentes :
	// augmenterModulo(varAff->nb, varAff->min, varAff->max);
	//displayIfNecessary(varAff);
}

// si varAff == &bluetoothMode, utiliser preferentiellement diminuerBluetoothMode()
// afin de garantir qu'on reset le CC si on met bluetoothMode à BL_OFF
void diminuerVarAff(VarAff * varAff){
	if(varAff->nb > varAff->min)
		setVarAffValue(varAff, varAff->nb-1);
	else
		setVarAffValue(varAff, varAff->max);

	// lignes equivalentes :
	//diminuerModulo(varAff->nb, varAff->min, varAff->max);
	//displayIfNecessary(varAff);
}

// si varAff == &bluetoothMode, utiliser preferentiellement setBluetoothModeValue()
// afin de garantir qu'on reset le CC si on met bluetoothMode à BL_OFF
void setVarAffValue(VarAff * varAff, unsigned char nb){
	//if(nb >= varAff->min && nb <= varAff->max)
		varAff->nb=nb;

		// On utilise tellement cette fonction que ça ralentirait potentiellement le programme
		// même de ne faire qu'un if, donc on fait une fonction specialement pour bluetoothMode.
//		if(varAff == &bluetoothMode){
//			if(bluetoothMode.nb==BL_OFF){
//				reset_radio();
//			}
//		}

		displayIfNecessary(varAff);
}


// 3 fonctions suivantes : plus possible si on veut garder de manière absolue
// la modularité du programme
// en particulier pour l'augmentation/diminution de bluetoothMode
// qui devrait alors se faire avec diminuerVarAff/augmenterVarAff
void setBluetoothModeValue(unsigned char nb){
	//if(nb >= varAff->min && nb <= varAff->max)
		bluetoothMode.nb=nb;

		// reset_radio() mets environ 1 seconde à se faire
		if(bluetoothMode.nb==BL_OFF){
			reset_radio();
		}

		commentPlacerDansEcranBlMode();
		// Alternatives plus lentes car passant par des conditions avant de l'appeler:
		//displayIfNecessary(&bluetoothMode);
		//afficherVarAff(&bluetoothMode);
}

void augmenterBluetoothMode(){
	if(bluetoothMode.nb < bluetoothMode.max)
		setBluetoothModeValue(bluetoothMode.nb+1);
	else
		setBluetoothModeValue(bluetoothMode.min);
}

void diminuerBluetoothMode(){
	if(bluetoothMode.nb > bluetoothMode.min)
		setBluetoothModeValue(bluetoothMode.nb-1);
	else
		setBluetoothModeValue(bluetoothMode.max);
}



void setVarAffValueWithPointer(VarAff * varAff, void * nb){
	if(varAff->type != PLUSIEURS_CHIFFRES)
		varAff->nb = * ((unsigned char *)nb);
	else{
		ScoreUpdate * s = (ScoreUpdate *) nb;
		varAff->contenu.chiffresAff.tabNb[LUI][0]=s->bit.counter1  ;
		varAff->contenu.chiffresAff.tabNb[MOI][0]=s->bit.partner1 ;
		varAff->contenu.chiffresAff.tabNb[LUI][1]=s->bit.counter2  ;
		varAff->contenu.chiffresAff.tabNb[MOI][1]=s->bit.partner2 ;
		varAff->contenu.chiffresAff.tabNb[LUI][2]=s->bit.counter3  ;
		varAff->contenu.chiffresAff.tabNb[MOI][2]=s->bit.partner3 ;
		varAff->contenu.chiffresAff.tabNb[LUI][3]=s->bit.counter4  ;
		varAff->contenu.chiffresAff.tabNb[MOI][3]=s->bit.partner4 ;
		varAff->contenu.chiffresAff.tabNb[LUI][4]=s->bit.counter5  ;
		varAff->contenu.chiffresAff.tabNb[MOI][4]=s->bit.partner5 ;
	}

	displayIfNecessary(varAff);
}

//void setType(VarAff* varAff, TypeVarAff type){
//	varAff->type=type;
//}

void setBounds(VarAff* varAff,  unsigned char min, unsigned char max, unsigned char initValue){
	varAff->min=min;
	varAff->max=max;
	varAff->nb=initValue;
}

void setPosBool(VarAff* varAff, unsigned char index, unsigned char index_contraire, unsigned char index_contraire_used){
	varAff->contenu.boolAff.index=index;
	varAff->contenu.boolAff.index_contraire_used=index_contraire_used;
	varAff->contenu.boolAff.index_contraire=index_contraire;
}

//void setPosBoolClignote(VarAff* varAff, unsigned char index){
//	varAff->contenu.boolAff.index=index;
//	varAff->contenu.boolAff.clignote=1;
//}


void setPosInt7(VarAff* varAff, unsigned char x, unsigned char y, unsigned char que2Chiffres){
	varAff->contenu.int7Seg.que2Chiffres=que2Chiffres;
	varAff->contenu.int7Seg.x=x;
	varAff->contenu.int7Seg.y=y;
}

void setPosInt14(VarAff* varAff, unsigned char x, unsigned char que2Chiffres){
	varAff->contenu.int14Seg.que2Chiffres=que2Chiffres;
	varAff->contenu.int14Seg.x=x;
}

void setPosString(VarAff* varAff, char * textes, unsigned char zone14Seg){
	varAff->contenu.stringChoice.textes=textes;
	varAff->contenu.stringChoice.zone14Seg=zone14Seg;
}

/////////////////////////////////


