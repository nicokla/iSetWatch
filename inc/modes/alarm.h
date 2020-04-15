#ifndef ALARME_H_
#define ALARME_H_

#include "class/time.h"

//extern ShortTime alarme;
extern unsigned char suivantAlarme[3];

void prepareDisplayAlarme();
void afficheAlarmeBasis();
unsigned char alarmeDeclenchee();
void actionModeAlarm(unsigned char typeEvenement);
void initConstantesAlarme();

#endif /* ALARME_H_ */
