#ifndef ECRAN_H_
#define ECRAN_H_

// pour clignotement ou bien choses ne bougeant pas en fonction des clics
#include "lcd8a.h"
#include "varAff.h"

typedef struct Symbole_ {
	unsigned char * contenu;
	unsigned char prendreLeContraire; // bool
	unsigned char forcerA1;
//	unsigned char forcerA0;
} Symbole;

typedef enum {
	RIEN=0x00, // inutile avec mustBeDisplayed
	ONE_NB,
	CHIFFRES,
	LETTRES,
	DEFILEMENT,
	SPECIAL2_14,
	SPECIAL3_14
}TypeAff14Seg;

typedef struct {
	char txt[SIZE_MAX_DEFILEMENT];
	char pos;
}Defilement;

typedef struct{
	unsigned char * nb;
	unsigned char que2Chiffres;
}NombreToDisplay;

typedef union { //union { // union est plus optimisé au niveau mémoire, mais il y a plus de risque de problèmes
	NombreToDisplay nbToDisplay;
  char lettres[5]; // if NULL, nothing is displayed
  Defilement defilement;
} ContenuAff14Seg;

typedef struct Aff14Seg_{
	TypeAff14Seg type;
	ContenuAff14Seg contenu; // si defilement, pas utilisé, car c'est automatiquement dans defilementTxt
} Aff14Seg;

typedef enum {
	RIEN_7=0x00,
	NB,
	TOURNANT,
	SPECIAL1_7
}TypeAff7Seg;

typedef union {
	NombreToDisplay nbToDisplay;
	unsigned char tournant;
} ContenuAff7Seg;

typedef struct Aff7Seg_{
	TypeAff7Seg type;
	ContenuAff7Seg contenu; //  unsigned char * ? Si NULL, on affiche rien
} Aff7Seg;

typedef struct QuiClignote_{
	unsigned char les14Seg[2];

	unsigned char les7Seg[2][2];

	unsigned char indices[NB_SYMBOLS];
	unsigned char taillePile;
}QuiClignote;

typedef struct Ecran_{
	Aff7Seg aff7Seg[2][2];
	Aff14Seg aff14Seg[2];
	Symbole symboles[NB_SYMBOLS]; // on pointe vers les booleens voulus.
	QuiClignote quiClignote;
//	VarAffSpecial * lesVarAff7Seg[2][2];
//	VarAffSpecial * lesVarAff14Seg[2];
//	VarAffSpecial * lesVarAffSymboles[9];
} Ecran;


typedef struct {
	unsigned char x; // 0 ou 1
	unsigned char y;
} Coord; // IntegerPosition



///////////////////////////////////////////////////////
extern Ecran ecran;

////////////////////////////////////////
// pas de doublons

void empile(QuiClignote * a, unsigned char b);
void clearListe(QuiClignote * a);
void depile(QuiClignote * a, unsigned char b);

//////////////////////////////////////////

void afficher7Seg(unsigned char a, unsigned char b);
void  afficher14Seg(unsigned char a);
void afficheSymbole(unsigned char indice);

///////////////////////////////////////////////////

void afficheClignotementParticulier(unsigned char a, unsigned char indice);
void afficheParticulier(unsigned char indice);
void effaceParticulier(unsigned char indice);

////////////////////////////////////////

void afficheEcranAll();
void afficheEcranClignotement(unsigned char a);

///////////////////////////////////////////////////

void mettreSurEcranTexte(unsigned char zoneNb, char texte[5]);
void mettreAuClignotementTexte(unsigned char zoneNb, char texte[5]);

///////////////////////////////////////

void mettreSurEcranNombre7Seg(unsigned char a, unsigned char b, /*int*/unsigned char * nb, unsigned char que2Seg);
void mettreAuClignotementNombre7Seg(unsigned char a, unsigned char b, /*int*/unsigned char* nb, unsigned char que2Seg);

////////////////////////////////////////
void mettreSurEcranNombre14Seg(unsigned char a, unsigned char * nb, unsigned char que2Seg);
void mettreAuClignotement14Seg(unsigned char a, unsigned char * nb, unsigned char que2Seg);

///////////////////////////////////////////////////
void enleverSymboleDeLEcran(unsigned char indice);
void mettreSurEcranForceSymbole(unsigned char indice);
void mettreSurEcranPasForceSymbole(unsigned char indice, unsigned char * contenu, unsigned char contraire);
void mettreAuClignotementForceSymbole(unsigned char indice);
void mettreAuClignotementPasForceSymbole(unsigned char indice, unsigned char * contenu, unsigned char contraire);

//////////////////////////////////////
void mettreAuClignotementVarAff(VarAff * varAff);
void desactiverClignotement();
void viderEcran();

void mettreAuClignotementDefilement(unsigned char zoneNb, char * texte);


#endif /* ECRAN_H_ */
