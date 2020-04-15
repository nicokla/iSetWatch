#ifndef VARAFF_H_
#define VARAFF_H_


#define augmenterModulo(x,min,max) (x=(x>=max ? min : x+1))
#define diminuerModulo(x,min,max) (x=(x<=min ? max : x-1))


////////////////////////////////

//typedef struct PosSymbol_{
//	unsigned char index;
//} PosSymbol;
//
//typedef struct Pos14Seg_{
//	unsigned char x;
//} Pos14Seg;
//
//typedef struct Pos7Seg_{
//	unsigned char x;
//	unsigned char y;
//} Pos7Seg;

//typedef struct PosInt_{
//	unsigned char x;
//	unsigned char y;
//} PosInt;


//////////////////////////////////////
// Si changement par clic

typedef struct Int7Seg_ {
//	Pos7Seg pos;
	unsigned char x;
	unsigned char y;

	unsigned char que2Chiffres;
}Int7Seg;

typedef struct Int14Seg_ {
//	Pos14Seg pos;
	unsigned char x;
	unsigned char que2Chiffres;
}Int14Seg;

//typedef struct IntAff_ {
//	unsigned short * contenu;
//	unsigned short min;
//	unsigned short max;
//
//	PosInt pos;
//
//	unsigned char que2Chiffres;
//
//	unsigned char toDisplayIfChanged=1;
//}IntAff;

typedef struct BoolAff_ {
	unsigned char index;
	unsigned char index_contraire;
	unsigned char index_contraire_used;
	unsigned char index_used;
//	unsigned char clignote;
}BoolAff;

typedef struct StringAff_ {
	char *textes;
	unsigned char zone14Seg;
}StringAff;

typedef struct ChiffresAff_{
	unsigned char * tabNb[2];
	//unsigned char maxToDisplay;//0-4 numManche()
}ChiffresAff;

//typedef struct VarAffSpecial_ VarAffSpecial;
//struct VarAffSpecial_ {
//	void (*commentAfficherVarAff)(unsigned char, unsigned char, unsigned char); // x,y,n
//	//void (*commentAfficherVarAff)(VarAff * v);
//	void (*commentPlacerDansEcran)(VarAffSpecial * v);
//	unsigned char x;
//	unsigned char y;
//	unsigned char * pnb;
//};

typedef struct VarAffSpecial1_ {
	unsigned char x;
	unsigned char y;
}VarAffSpecial1;

typedef struct VarAffSpecial2_ {
	unsigned char x;
	unsigned char y;
}VarAffSpecial2;

typedef union VariableAffGen_{
	Int7Seg int7Seg;
	Int14Seg int14Seg;
//	IntAff intAff;
	BoolAff boolAff;
	StringAff stringChoice;
	ChiffresAff chiffresAff;
	VarAffSpecial1 varAffSpecial1;
	VarAffSpecial2 varAffSpecial2;
} VariableAffGen;

typedef enum TypeVarAff_{
	UNDEFINED=0x00,
	INT7,
	INT14,
//	INT=0x00,
	BOOL,
	STR,
	PLUSIEURS_CHIFFRES,
	SPECIAL1, // pour les 15/30/40/Ad, il faut un ad.
	SPECIAL2,
	SPECIAL3
}TypeVarAff;



typedef struct VarAff_{
	TypeVarAff type;
	VariableAffGen contenu;

	// pour l'année on aurait besoin d'un short mais on peux aller de 2000 à 2255 et on revient à 2000.
	// le 2 sera affiché séparément exceptionellement.
	unsigned char nb;
	unsigned char min;
	unsigned char max;
	// unsigned char x;
	// unsigned char y;

	unsigned char toDisplayIfChanged;//=1
}VarAff;

extern VarAff enModif;

//////////////////

void dispNb(unsigned char a,unsigned char b,ChiffresAff * c);
void disp2Nb(unsigned char b, ChiffresAff * c );
void dispAllTabNb(ChiffresAff * c);
void setTabNb(unsigned char a, unsigned char b, unsigned char n, ChiffresAff * c);
void mettreSurEcranTabNb(unsigned char a, unsigned char b, ChiffresAff * c);
void mettreSurEcranTabNbAll(ChiffresAff * c);

///////////////////

void setBluetoothModeValue(unsigned char nb);
void augmenterBluetoothMode();
void diminuerBluetoothMode();
void displayIfNecessary(VarAff * varAff);
void afficherVarAff(VarAff * varAff);
void augmenterVarAff (VarAff * varAff);
void diminuerVarAff (VarAff * varAff);
void setBounds(VarAff* varAff,  unsigned char min, unsigned char max, unsigned char initValue);
void setPosBool(VarAff* varAff, unsigned char index, unsigned char index_contraire, unsigned char index_contraire_used);
void setPosInt7(VarAff* varAff, unsigned char x, unsigned char y, unsigned char que2Chiffres);
void setPosInt14(VarAff* varAff, unsigned char x, unsigned char que2Chiffres);
void setPosString(VarAff* varAff, char * textes, unsigned char zone14Seg);
void placerDansEcran(VarAff * varAff);
void setVarAffValue(VarAff * varAff, unsigned char nb);
void setVarAffValueWithPointer(VarAff * varAff, void * nb);

#endif /* VARAFF_H_ */
