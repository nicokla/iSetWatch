#ifndef TEST_H_
#define TEST_H_

#include "varAff.h"

extern char blTestTerminated;
extern char macTexte[22];
extern unsigned char macNb[6];
extern unsigned char swVersion[3];
extern VarAff freqTestBl;
extern unsigned char blMACTestTerminated;
extern unsigned char blSwRevTestTerminated;

char toTxt(unsigned char a);
void mettreMacNbDansMacTexte();
void initConstantesTest();
void actionModeTest(unsigned char typeEvenement);
void prepareDisplayTestBl();
void endModeTest();

void testAffichage1();
void testAffichage2();
void testAffichage3();
void testAffichage4();
void testAffichage5();
void testAffichage6();

#endif /* TEST_H_ */
