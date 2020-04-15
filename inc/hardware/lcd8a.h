#ifndef LCD8A_H__
#define LCD8A_H__

#include <init.h>
#include "globalVar.h"

// Display STATE.
#define	LCD8A_STATE_ALL_OFF		( 0x3 )							///< Mode : All off.
#define	LCD8A_STATE_ALL_ON		( 0x2 )							///< Mode : All on.
#define	LCD8A_STATE_NORMAL		( 0x1 )							///< Mode : Normal display.
#define	LCD8A_STATE_OFF			( 0x0 )							///< Mode : Display off.

// Display Memory Address.
#define	LCD8A_SEGRAM_TOP_ADDR	( 0x7000 )
#define	LCD8A_SEGRAM_SIZE				( 0x100 )

#ifdef NEW_SCREEN
#define SYMBOL_INDEX_24HMODE 0
#else
#define SYMBOL_INDEX_AM 0
#endif
#define SYMBOL_INDEX_PM 1
#define SYMBOL_INDEX_ALARM 2
#define SYMBOL_INDEX_BT 3
#define SYMBOL_INDEX_SEPARATION 4
#define SYMBOL_INDEX_SERVER1 5
#define SYMBOL_INDEX_SERVER2 6
#define SYMBOL_INDEX_2PTS1 7
#define SYMBOL_INDEX_2PTS2 8
#define SYMBOL_INDEX_S1 9
#define SYMBOL_INDEX_S2 10
#define SYMBOL_INDEX_S3 11
#define SYMBOL_INDEX_S4 12
#define NB_SYMBOLS 13


#define SIZE_MAX_DEFILEMENT 50

//#define activerBit(a,b) (*(a) |= b)
//#define desactiverBit(a,b) (*(a) &= (0xFF ^ b))
//#define setBit(a,b,c) (if (c) activerBit(a,b) else desactiverBit(a,b))
//#define setSymbole(symb, valeur) (setBit(symb.a, symb.b, valeur))

//////////////////////////////////////////////////


typedef struct SymboleAdresse_{
	unsigned char * a;
	unsigned char b;
}SymboleAdresse;


//////////////////////////////////////////////////

extern unsigned char l_haut[14];
extern unsigned char l_bas[14];
extern unsigned char l_7[7];
extern unsigned char nb7Seg[16];
extern unsigned short nbHaut[16];
extern unsigned short nbBas[16];
extern unsigned short *nbAll[2];
extern unsigned short lettresHaut[28];
extern unsigned short lettresBas[28];
extern unsigned short * lettresAll[2];
extern unsigned short * assoc14[2][5];
extern unsigned char* assoc7[2][4] ;

extern SymboleAdresse assocSymbole[NB_SYMBOLS];


void initLcd8a( void );
void onLcd8aDisplay( void ) ;
void offLcd8aDisplay( void ) ;
void setLcd8aDisplayState( unsigned char state ) ;
unsigned char getLcd8aDisplayState( void ) ;
void clearLcd(  ) ;

/////////////////////////////////

void initSymbolesPositions();
void activerBit(unsigned char * a, unsigned char b);
void desactiverBit(unsigned char * a, unsigned char b);
void setSymbole(unsigned char index, unsigned char value);



////////////////////////////////
// 2.2) Low to middle level display function
// 2.2.1) For 7 segments



void effacer7Seg(unsigned char a, unsigned char b);
void effacerDeux7Seg(unsigned char a, unsigned char b);
void afficherSeqSur7Seg(unsigned char a, unsigned char b, unsigned char seq);
unsigned char avoirSeqSur7Seg(unsigned char a, unsigned char b);
void afficherChiffreSur7Seg(unsigned char a, unsigned char b, unsigned char n);
void afficherChiffreSur7Ou14Seg(unsigned char a, unsigned char b, unsigned char n);
void afficherNbSur7ou14Seg(unsigned char a, unsigned char b, unsigned char n);
void afficherNbA2ChiffresSur7ou14Seg(unsigned char a, unsigned char b, unsigned char n);
void afficherNbSur7ou14SegGeneral(unsigned char a, unsigned char b, unsigned char n, unsigned char que2ch);
void afficherNbSur7Seg(unsigned char n, unsigned char a, unsigned char b);
void afficherNbA2ChiffresSur7Seg(unsigned char n, unsigned char a, unsigned char b);
void afficherTournant(unsigned char a, unsigned char b);


///////////////////////////
// 2.2.2) For 14 segments


void effacer14Seg(unsigned char a, unsigned char b);
void afficherSeqSur14Seg(unsigned char a, unsigned char b, unsigned short seq);
unsigned short avoirSeqSur14Seg(unsigned char a, unsigned char b);
unsigned short seq14SegOfChar(char c, unsigned char a);
void afficherLettreSur14Seg(unsigned char a, unsigned char b ,char c);
void afficherChiffreSur14Seg(unsigned char a, unsigned char b,unsigned char n);
void afficherNbSur14Seg(unsigned char n,  unsigned char a, unsigned char b );
void afficherNbA2ChiffresSur14Seg(unsigned char n,  unsigned char a, unsigned char b);
void effacerZone14Seg( unsigned char zoneNb);
void afficherTexteSur14Seg(char s[5], unsigned char zoneNb);


/////////////////////////////////////////

void afficherDefilement(unsigned char zoneNb);
void updatePositionDefilement(unsigned char zoneNb);
void afficheDefilementAll();
void mettreAuDefilement(unsigned char zoneNb, char * texte);
void desactiverDefilement();



#endif // LCD8A_H__

