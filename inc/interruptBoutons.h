#ifndef	STR_LCD
#define	STR_LCD

#include "init.h"


///////////////////
// 1.2) Defines relatifs aux boutons
#define SW1 4
#define SW2 0
#define SW3 5
#define SW4 6

// vaut 1 ssi on attend un appui vers le bas (ce qui est le cas quand on vient de remonter le bouton vers le haut)
// vaut 0 ssi on attend une remontée de bouton (ce qui est le cas si on vient de cliquer vers le bas, ie qu'on est en bas)
//#define SW1EDGE_BUTTON_DOWN P0INTCTL_P04EDGE
#define SW1EDGE_BUTTON_DOWN (*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px4EDGE
#define SW2EDGE_BUTTON_DOWN (*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px0EDGE
#define SW3EDGE_BUTTON_DOWN (*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px5EDGE
#define SW4EDGE_BUTTON_DOWN (*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px6EDGE

//#define SW1IN_BUTTON_UP P0DAT_P04IN
// vaut 1 ssi le bouton est relaché
#define SW1IN_BUTTON_UP (*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px4IN
#define SW2IN_BUTTON_UP (*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px0IN
#define SW3IN_BUTTON_UP (*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px5IN
#define SW4IN_BUTTON_UP (*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px6IN


#define BOUTON1COURT 0x01
#define BOUTON2COURT 0x02
#define BOUTON3COURT 0x03
#define BOUTON4COURT 0x04
#define BOUTON2ET3 0x05
#define BOUTON1LONG 0x11
#define BOUTON2LONG 0x12
#define BOUTON3LONG 0x13
#define BOUTON4LONG 0x14
#define BOUTON_ALL 0x21
#define BOUTON4AFTEROTHER 0x22
#define TEMPS_SECONDE 0x31
#define TEMPS_CLIGNOTEMENT 0x32
#define TEMPS_DEFILEMENT 0x33


extern void intPortInput( void )	__attribute__ ((interrupt_handler));
//int nouveauMode();
void bouton1AppuiCourt(void);
void bouton2AppuiCourt(void);
void bouton3AppuiCourt(void);
void bouton4AppuiCourt(void);
void bouton4apresAutre(void);
void actionBoutons2Et3(void);
void actionTousLesBoutons(void);
void initP0();
void bouton1AppuiLong(void);
void bouton2AppuiLong(void);
void bouton3AppuiLong(void);
void bouton4AppuiLong();
unsigned char sontActifsAppuisLongs2Et3();

#endif
