#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include "class/VarAff.h"
#include "fileDActions.h"
// Version descendante de 150213-3

////////////////////////////////
// Si on veut être en mode normal au lieu , on met la ligne suivante en commentaire
//#define MODE_DEBUG_BLUETOOTH

//#define CC_DEBUGGER_BLOCKING_RESET TRUE

//#define WATCH_DOG_ACTIF

// etre dans ce mode a pour consequence
// - d'arriver des le debut du programme dans le mode TENNIS au lieu de WATCH
// - de limiter l'attente "time out" du tennis à 2 au lieu de 30 minutes

////////////////////////////////
// à utiliser si on veut utiliser le nouvel écran :
#define NEW_SCREEN

///////////////////////////

#define SW_SEIKO_VERSION_NUMBER 14
#define SW_SEIKO_SUBVERSION_NUMBER 2

// si aucun point n'a �t� marqu� depuis
// TIME_OUT_BLUETOOTH minutes, on reset le CC
// 6 equivaut en fait à 5 par sécurité car c'est toute les minutes de la montre et on ne démarre
// pas forcément sur zéro (la première minute peut arriver au bout d'à peine quelques secondes).
#define TIME_OUT_BLUETOOTH (unsigned short) 6

#define INIT_MALLOC_START ((unsigned long)&__END_data + 1)
//#define MAX_SIZE_FILE_ACTIONS 6

// sizeof(CellAction)+8 = 12+8 = 20
#define INIT_MALLOC_END (INIT_MALLOC_START + (unsigned long)((sizeof(CellAction)+8)*MAX_SIZE_FILE_ACTIONS + 16))

///////////////////////////////////
// defini dans init.h
//#define TRUE				1
//#define FALSE 			0


////////////////////////////////////////
// 1.3) Modes de fonctionnement de la montre, environ 40
// The submodes should have the same first digit (in hexa) than the main modes
// If you want to change that, change the conditions in the function brothersModes(int a, int b)

#define MASQUE_PRINCIPAL 0xE0
#define MASQUE_SUB 0x1F
#define DECALAGE 5

#define WATCH (unsigned char) 0x00
#define WATCH_HOUR (unsigned char) 0x01
#define WATCH_MINUTE (unsigned char) 0x02
#define WATCH_SECOND (unsigned char) 0x03
#define WATCH_WEEK (unsigned char) 0x04
#define WATCH_DAY (unsigned char) 0x05
#define WATCH_MONTH (unsigned char) 0x06
#define WATCH_YEAR (unsigned char) 0x07
#define WATCH_24HMODE (unsigned char) 0x08

#define ALARM (unsigned char) 0x20 // must not be 0, for bipBips to work
#define ALARM_HOUR (unsigned char) 0x21
#define ALARM_MINUTE (unsigned char) 0x22

#define STOPWATCH_PAUSE (unsigned char) 0x40
#define STOPWATCH_RUN (unsigned char) 0x41
#define STOPWATCH_LAP (unsigned char) 0x42

#define COUNTDOWN (unsigned char) 0x60 // must not be 0, for bipBips to work
#define COUNTDOWN_HOUR (unsigned char) 0x61
#define COUNTDOWN_MINUTE (unsigned char) 0x62
#define COUNTDOWN_SECOND (unsigned char) 0x63

#define TENNIS (unsigned char) 0x80
#define TENNIS_CHANGE_SIDE (unsigned char) 0x81// sert uniquement 4 secondes pour que ça clignote change side.
#define TENNIS_END (unsigned char) 0x82
#define TENNIS_TIE_BREAK (unsigned char) 0x83 // sert uniquement 4 secondes pour que ça clignote tie-break.
#define TENNIS_STB (unsigned char) 0x84 // sert uniquement 4 secondes pour que ça clignote super-tie-break.
#define TENNIS_SETTING_RAZ  (unsigned char) 0x85
#define TENNIS_SETTING_INITIAL_SERVER (unsigned char) 0x86
#define TENNIS_SETTING_NB_SET_PER_MATCH (unsigned char) 0x87
#define TENNIS_SETTING_NB_GAME_PER_SET (unsigned char) 0x88
#define TENNIS_SETTING_ADVANTAGE (unsigned char) 0x89
#define TENNIS_SETTING_TIE_BREAK (unsigned char) 0x8A
#define TENNIS_SETTING_TIE_BREAK_TYPE (unsigned char) 0x8B
#define TENNIS_SETTING_SUPER_TIE_BREAK (unsigned char) 0x8C
#define TENNIS_SETTING_BLUETOOTH (unsigned char) 0x8D
#define TENNIS_BLUETOOTH_WAIT_CONNEXION_PARTNER (unsigned char) 0x8E
#define TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_PARTNER (unsigned char) 0x8F
#define TENNIS_BLUETOOTH_WAIT_CONNEXION_COUNTER_SMARTPHONE (unsigned char) 0x90
#define TENNIS_BLUETOOTH_CONNEXION_ABORTED (unsigned char) 0x91
//#define OAD_CHOICE (unsigned char) 0x92
#define OAD_UPDATING (unsigned char) 0x92
#define OAD_END (unsigned char) 0x93

#define COMPTEUR (unsigned char) 0xA0
#define COMPTEUR_RAZ (unsigned char) 0xA1

#define TEST (unsigned char) 0xC0
#define TEST_BL (unsigned char) 0xC1
#define TEST_BL2_MIN (unsigned char) 0xC2
#define TEST_BL2_CNTR (unsigned char) 0xC3
#define TEST_BL2_MAX (unsigned char) 0xC4
#define TEST_UART (unsigned char) 0xC5

#define NB_TYPES_PRINCIPAUX 7

// type de tb
#define TB_TYPE_NORMAL 0x00
#define TB_TYPE_EARLY 0x01

// DO NOT MODIFY THESE !!!
#define MOI 1 // comme bas
#define LUI 0 // comme haut
//#define PARTNER 1
//#define COUNTER 0

typedef union Mode_{
	unsigned char reg;
	struct {
			unsigned char principal : 4;
			unsigned char sub : 4;
	} bit;
}Mode;

extern VarAff versionWatch;
extern VarAff subVersionWatch;
extern VarAff versionBle;
extern VarAff subVersionBle;

extern unsigned char advantageChar[2]; // Ad pour 7 seg, deja dans nb7seg

//extern unsigned char decalage;
extern char noYes[2][5] ;
extern char version[5];
extern unsigned char mode;
extern unsigned char avantChangementMode;
extern int notreStatus;
extern VarAff * currentVarAff;
//extern unsigned char suivantModePrincipal[8];
//extern unsigned char * suivantSubModes[8];


void commence(unsigned char a);
void dbrun();

void prepareDisplay();
void sauvegardeMode();
unsigned char brothersModes(unsigned char a, unsigned char b);
unsigned char modePrincipal(unsigned char m);
void mettreMode(unsigned char m);
void initSuivants();

void wait_general(int a);
void wait_s();
void wait_m();
void wait_l();
void designeVariableSiModeDeReglage();


#endif
