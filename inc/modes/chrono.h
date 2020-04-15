#ifndef CHRONO_H_
#define CHRONO_H_

#include "class/time.h"

extern VarAff chronoMode;
extern ShortTime chrono;

void prepareDisplayChrono();
void afficheChronoBasis();
void razChrono();
void initChrono(void);
void startChrono();
void actionModeChrono(unsigned char typeEvenement);
void mettreModePauseFaster();
void mettreModeLapFaster();
void mettreModeRunFaster();

#endif
