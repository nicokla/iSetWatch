#ifndef TIME_H_
#define TIME_H_

#include "class/varAff.h"

//	 Int7Seg second;
//	 Int7Seg minute;
//	 Int7Seg hour;
//	 StringAff dayOfWeek; // 0=sunday
//	 Int14Seg dayOfMonth;
//	 StringAff month; // 1 = january
//	 Int14Seg year;//IntAff * year; // up to 65536
//
//	 BoolAff pm; // 1 iff the evening. not used when in 12h Mode
//	 StringAff is24HMode; // is 1 iff it's 24h mode
//	 BoolAff activated; // used only in alarm


typedef struct ShortTime_{
	VarAff second;
	VarAff minute;
	VarAff hour;
	VarAff pm; // 1 iff the evening. not used when in 12h Mode
	VarAff is24HMode; // is 1 iff it's 24h mode
}ShortTime;

typedef struct Time_{
	ShortTime shortTime;
	ShortTime shortTimeAlarm;

	VarAff dayOfWeek; // 0=sunday
	VarAff dayOfMonth;
	VarAff month; // 1 = january
	VarAff year;//IntAff * year; // up to 65536
	VarAff activated; // used only in alarm
} Time;

void putAbstractTimeInHardwareTime(Time * t);
void putHardwareTimeInAbstractTime(Time * t, unsigned char flags);

void initTimeShort(ShortTime * t);
void initTime(Time * t);
void desactiverDisplayTime(Time * t);
void desactiverDisplayTimeShort(ShortTime * t);

extern long long totalSecond (ShortTime * t);
extern unsigned short totalMinute(ShortTime * t);
extern long long differenceSecond(ShortTime * t1, ShortTime * t2);
extern unsigned short differenceMinute(ShortTime * t1, ShortTime * t2);
unsigned short differenceMinuteGen(unsigned short a, unsigned short b);
long long differenceSecondGen(long long a, long long b);

extern void from12Hto24H(ShortTime * t);
extern void from24Hto12H(ShortTime* t);
extern void change24HMode(ShortTime * t);
extern void changeAll24HMode();
extern void augmenteSecondes(ShortTime * t, unsigned char repercussion);
extern void augmenteMinutes(ShortTime * t);
extern void augmenteHeures(ShortTime * t, unsigned char repercussion);



extern void diminueSecondes(ShortTime * t,  unsigned char repercussion);
extern void diminueMinutes(ShortTime * t);
extern void diminueHeures(ShortTime * t, unsigned char repercussion);
//extern void diminueHeures24HMode(Time* t);
//extern void diminueHeures12HMode(Time * t);

////////////////////////////

extern void augmenteJour(Time * t);
extern void augmenteJourSemaine(Time * t);
extern void augmenteJourMois(Time * t);
extern void augmenteMois(Time * t);
extern void augmenteAnnee(Time * t);

extern void diminueJour(Time * t);
extern void diminueJourSemaine(Time * t);
extern void diminueJourMois(Time * t);
extern void diminueMois(Time * t);
extern void diminueAnnee(Time * t);

#endif /* TIME_H_ */
