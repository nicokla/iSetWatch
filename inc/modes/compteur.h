#ifndef COMPTEUR_H
#define COMPTEUR_H

#include "class/varAff.h"

extern VarAff compteur[2];
extern unsigned char compteurLastPoint;
extern unsigned char compteurMemoire;

void initCompteur();
void actionModeCompteur(unsigned char typeEvenement);
void prepareDisplayCompteur();

#endif
