#ifndef WATCH_H_
#define WATCH_H_

#include "lcd8a.h"
#include "class/time.h"

extern Time watch;
extern char jours[7][5];
extern char mois[13][5];
extern char texte24HMode[2][5] ;
extern unsigned char longueursDesMois[13];
extern unsigned char suivantMontre[9];
extern VarAff deuxPointsSecondes;

void commentAfficher24HMode();
void commentPlacerDansEcran24HMode();
void actionModeWatch(unsigned char typeEvenement);
//extern void afficherMontreBasis();
extern void prepareDisplayMontre();
void initConstantesMontre();

#endif /* WATCH_H_ */
