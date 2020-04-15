/****************
 * La structure Time (heure SW) permet de régler facilement le temps, elle connait donc les règles
 * pour augmenter les secondes, les minutes (modulo 59), les heures (modulo 12 ou 24 selon le 24HMode), etc.
 * Pour modifier ou lire l'heure HW, se référer au fichier rtca.c
 * **************/

#include "time.h"
#include "watch.h"
#include "alarm.h"
#include "ecranPourClignotements.h"
#include "globalVar.h"
#include "rtca.h"


//////////////////////////////////////

// Mets l'heure SW dans l'heure HW
// à faire apres chaque fin de reglage
void putAbstractTimeInHardwareTime(Time * t){
	// premiere chose a faire pour ensuite qu'il n'y ait pas de bug avec l'heure
	setRtca24hMode(  t->shortTime.is24HMode.nb );

	setRtcaAlarmHour( t->shortTimeAlarm.hour.nb );
	setRtcaAlarmMinute( t->shortTimeAlarm.minute.nb );
	if( ! t->shortTime.is24HMode.nb )
		setRtcaAlarmIndicator( t->shortTimeAlarm.pm.nb );
	RTCINTF_ALARMIF = 1;
	RTCINTE_ALARMIE = t->activated.nb;

	setRtcaYear( t->year.nb );
	setRtcaMonth( t->month.nb );
	setRtcaDay( t->dayOfMonth.nb );
	setRtcaWeek( t->dayOfWeek.nb );
	setRtcaHour( t->shortTime.hour.nb  );
	setRtcaMinute( t->shortTime.minute.nb );
	setRtcaSecond( t->shortTime.second.nb );
	if( ! t->shortTime.is24HMode.nb )
		setRtcaIndicator( t->shortTime.pm.nb );
}


// Mets l'heure HW dans l'heure SW
// a faire a chaque seconde
// flags=(unsigned char) (rtcaIntf & 0x00F0);
void putHardwareTimeInAbstractTime(Time * t, unsigned char flags ){
	switch(flags) {
	case 0xFC: // day
		setVarAffValue(&t->year , RTCYAR_RTCYH * 10 + RTCYAR_RTCYL);
		setVarAffValue(&t->month , RTCMON_RTCMOH * 10 + RTCMON_RTCMOL);
		setVarAffValue(&t->dayOfMonth , RTCMON_RTCDH * 10 + RTCMON_RTCDL);
		setVarAffValue(&t->dayOfWeek , RTCYAR_RTCWK);
	case 0x7C: // hour
		setVarAffValue(&t->shortTime.hour , RTCHUR_RTCHH * 10 + RTCHUR_RTCHL);
		setVarAffValue(&t->shortTime.pm , RTCHUR_RTCAP);
	case 0x3C: // minute
		setVarAffValue(&t->shortTime.minute , RTCHUR_RTCMIH * 10 + RTCHUR_RTCMIL);
	case 0x1C: // second
		setVarAffValue(&t->shortTime.second , RTCSEC_RTCSH * 10 + RTCSEC_RTCSL);
		break;
	}
}

/////////////////////////////////////////////

// initialise l'heure
void initTime(Time * t){
	setBounds(&t->activated, 0, 1, 0);
	setBounds(&t->dayOfMonth, 1, 31, 1);
	setBounds(&t->dayOfWeek, 0, 6, 1);
	setBounds(&t->month, 1, 12, 1);
	setBounds(&t->year, 0, 99, 14); // va jusqu'a 2099
	initTimeShort(&t->shortTime);
	initTimeShort(&t->shortTimeAlarm);
	putAbstractTimeInHardwareTime(t);
}

// initialise une structure timeShort (par exemple le chrono ou le compte à rebours)
void initTimeShort(ShortTime * t){
	setBounds(&t->pm, 0, 1, 0); // minuit donc am
	setBounds(&t->second, 0, 59, 0);
	setBounds(&t->is24HMode, 0, 1, 1); // en 24 H mode
	setBounds(&t->minute, 0, 59, 0);
	setBounds(&t->hour, 0, 23, 0); // can change to (1, 12) if 12h mode and not 24h mode
}

/////////////////////////////////////////

// compte les secondes  depuis le debut de la journee
long long totalSecond (ShortTime * t){
	long long a=0;
	a+=t->second.nb;
	a+=60*t->minute.nb;
	a+=3600*t->hour.nb;
	return a;
}

// compte les minutes  depuis le debut de la journee
unsigned short totalMinute(ShortTime * t){
	unsigned short a=0;
	a+=((unsigned short) (t->minute.nb));
	a+=60*((unsigned short) (t->hour.nb));
	return a;
}

// renvoie un nombre positif indicant dans combien de secondes on passera du time 2 au time 1
long long differenceSecond(ShortTime * t1, ShortTime * t2){
	return differenceSecondGen(totalSecond(t1),totalSecond(t2));
}

// renvoie un nombre positif indicant dans combien de secondes on passera du time 2 au time 1
long long differenceSecondGen(long long a, long long b){
	long long result=86400;
	result += a;
	result -= b;
	result %= 86400;
	return result;
}

// renvoie un nombre positif indicant dans combien de minutes on passera du time 2 au time 1
unsigned short differenceMinute(ShortTime * t1, ShortTime * t2){
	return differenceMinuteGen(totalMinute(t1),totalMinute(t2));
}

// renvoie un nombre positif indicant dans combien de minutes on passera du time 2 au time 1
unsigned short differenceMinuteGen(unsigned short a, unsigned short b){
	unsigned short result=1440;
	result += a;
	result -= b;
	result %= 1440;
	return result;
}

/////////////////////////////////////////////

// Cache l'évolution du temps (fonction appelée quand on sort du mode WATCH)
void desactiverDisplayTime(Time * t){
	t->activated.toDisplayIfChanged=0;
	t->dayOfMonth.toDisplayIfChanged=0;
	t->dayOfWeek.toDisplayIfChanged=0;
	t->month.toDisplayIfChanged=0;
	t->year.toDisplayIfChanged=0;
	desactiverDisplayTimeShort(&t->shortTime);
	desactiverDisplayTimeShort(&t->shortTimeAlarm);
//	deuxPointsSecondes.toDisplayIfChanged=0;
}

// equivalent à la fonction precedente mais pour un timeShort.
// par exemple appelée lorsqu'on sort du chrono, ainsi que quand on sort du compte à rebours
void desactiverDisplayTimeShort(ShortTime * t){
	t->hour.toDisplayIfChanged=0;
	t->is24HMode.toDisplayIfChanged=0;
	t->minute.toDisplayIfChanged=0;
	t->pm.toDisplayIfChanged=0;
	t->second.toDisplayIfChanged=0;
}

// fait passer le shortTime pointé du mode 12h au mode 24H
void from12Hto24H(ShortTime * t){
	setVarAffValue(&(t->is24HMode), 1);

	enleverSymboleDeLEcran(SYMBOL_INDEX_PM);
	setSymbole(SYMBOL_INDEX_PM,0);

#ifndef NEW_SCREEN
	setSymbole(SYMBOL_INDEX_AM,0);
	enleverSymboleDeLEcran(SYMBOL_INDEX_AM);
#endif

	if(t->hour.nb==12 && ! t->pm.nb) // minuit = 12 am
		setVarAffValue(&(t->hour), 0);
	else if (t->pm.nb && t->hour.nb != 12 ) // apres-midi mais pas midi = 12 pm
		setVarAffValue(&(t->hour), t->hour.nb + 12);
	t->hour.min=0;
	t->hour.max=23;
}

// fait passer le shortTime pointé du mode 24h au mode 12h
void from24Hto12H(ShortTime* t){
	setVarAffValue(&(t->is24HMode), 0);

//	placerDansEcran(&(t->pm));
//	t->pm.toDisplayIfChanged=1;

	setVarAffValue(&(t->pm), (t->hour.nb >=12));
	if(t->hour.nb % 12 != 0) // si on est pas sur midi on minuit
		setVarAffValue(&(t->hour), t->hour.nb % 12); // on met modulo 12
	else
		setVarAffValue(&(t->hour), 12); // sinon on met à 12
	t->hour.min=1;
	t->hour.max=12;
}

// change le 24HMode
void change24HMode(ShortTime * t){
	if(t->is24HMode.nb)
		from24Hto12H(t);
	else
		from12Hto24H(t);
}

//change le 24H mode du WATCH et de l'alarm d'un seul coup
void changeAll24HMode(){
	change24HMode(&watch.shortTime);
	change24HMode(&watch.shortTimeAlarm);
}

//////////////////////////////////////////

// augmente les secondes
// si repercussion vaut 1, cela va aussi augmenter les minutes au passage de 59 à 0
void augmenteSecondes(ShortTime * t, unsigned char repercussion){
	augmenterVarAff(&(t->second));
	if(repercussion && t->second.nb==0)
		augmenteMinutes(t);
}

// augmenter les minutes
void augmenteMinutes(ShortTime * t){
	augmenterVarAff(&(t->minute));
	if(t->minute.nb==0)
		augmenteHeures(t,1);
}

// augmente les heures
// si repercussion vaut 1, cela va aussi augmenter le jour au passage de 23h à minuit
void augmenteHeures(ShortTime* t, unsigned char repercussion){
	augmenterVarAff(&(t->hour));
	if(t->is24HMode.nb){ // si 24Hmode
		if(t->hour.nb==0)
			if(repercussion && t==&watch.shortTime)
				augmenteJour(&watch);
		}
	else // si 12HMode, c-a-d if(! t->is24HMode.nb)
		if(t->hour.nb==12){
			augmenterVarAff(&t->pm);
			if( ! t->pm.nb )
				if(repercussion && t==&watch.shortTime)
					augmenteJour(&watch);
		}
}


//////////////////////////////////////////

// diminue les secondes
// si repercussion vaut 1, cela va aussi diminuer les minutes au passage de 0 à 59
void diminueSecondes(ShortTime * t, unsigned char repercussion){
	diminuerVarAff(&(t->second));
	if(t->second.nb==59 && repercussion)
		diminueMinutes(t);
}

// diminue les minutes
void diminueMinutes(ShortTime * t){
	diminuerVarAff(&(t->minute));
	if(t->minute.nb==59)
		diminueHeures(t,1);
}

// diminue les heures
// si repercussion vaut 1, cela va aussi diminuer le jour au passage de minuit à 23h
void diminueHeures(ShortTime* t, unsigned char repercussion){
	diminuerVarAff(&(t->hour));
	if(t->is24HMode.nb){ // si 24Hmode
		if(t->hour.nb==23)
			if(repercussion && t==&watch.shortTime)
				diminueJour(&watch);
		}
	else // si 12HMode, c-a-d if(! t->is24HMode.nb)
		if(t->hour.nb==11){
			augmenterVarAff(&t->pm);
			if( t->pm.nb )
				if(repercussion && t==&watch.shortTime)
					diminueJour(&watch);
		}
}


////////////////////////////////////////////


// augmente le jour
void augmenteJour(Time * t){
	augmenteJourSemaine(t);
	augmenteJourMois(t);
}

// augmente le jour de la semaine
void augmenteJourSemaine(Time * t){
	augmenterVarAff(&t->dayOfWeek);
}

// augmente le jour du mois
void augmenteJourMois(Time * t){
	augmenterVarAff(&t->dayOfMonth);
	if(t->dayOfMonth.nb == 1){
		augmenteMois(t);
		t->dayOfMonth.max=longueursDesMois[t->month.nb];
	}
}

// augmente le mois
void augmenteMois(Time * t){
	augmenterVarAff(&t->month);
	if(t->month.nb==1){
		augmenteAnnee(t);
	}
}

// augmente l'annee
void augmenteAnnee(Time * t){
	augmenterVarAff(&t->year);
}




/////////////////////////////////////////

// diminue le jour
void diminueJour(Time * t){
	diminueJourSemaine(t);
	diminueJourMois(t);
}

// diminuer le jour de la semaine
void diminueJourSemaine(Time * t){
	diminuerVarAff(&t->dayOfWeek);
}

// diminue le jour du mois
void diminueJourMois(Time * t){
	diminuerVarAff(&t->dayOfMonth);
	if(t->dayOfMonth.nb == t->dayOfMonth.max ){
		diminueMois(t);
		setVarAffValue(&t->dayOfMonth,longueursDesMois[t->month.nb]);
		t->dayOfMonth.max=longueursDesMois[t->month.nb];
	}
}

// diminue le mois
void diminueMois(Time * t){
	diminuerVarAff(&t->month);
	if(t->month.nb==12){
		diminueAnnee(t);
	}
}

// diminue l'année
void diminueAnnee(Time * t){
	diminuerVarAff(&t->year);
}




