/****************
 * Les fonctions de ce fichier permettent de modifier l'heure hardware
 * (contenue dans les registres du real time clock).
 * Pour modifier l'heure software --> fichier time.c
 * ****************/

#include "rtca.h"
#include "globalVar.h"

void setRtcaAlarmSecond(unsigned char second){
	RTCALM1_RTCSLA = second % 10;
	RTCALM1_RTCSHA = (second / 10) %10;
}

void setRtcaAlarmHour( unsigned char hour)
{
	if ( getRtca24hMode() == RTCCTL_RTC24H_24H && hour > 23 ) {
		return;
	}
	if ( getRtca24hMode() == RTCCTL_RTC24H_12H && ( hour < 1 || hour > 12 ) ) {
		return;
	}

	RTCALM2_RTCHHA  = hour / 10 % 10;
	RTCALM2_RTCHLA = hour /  1 % 10;
}


unsigned char getRtcaAlarmHour( void )
{
	unsigned char result;
	result = RTCALM2_RTCHHA * 10 + RTCALM2_RTCHLA;
	return result;
}

void setRtcaAlarmMinute( unsigned char minute )
{
	if ( minute > 59 ) {
		return;
	}

	RTCALM2_RTCMIHA = minute / 10 % 10;		/// Set year(tenths digit).
	RTCALM2_RTCMILA = minute /  1 % 10;		/// Set year(unit digit).
}

unsigned char getRtcaAlarmMinute( void )
{
	unsigned char result;
	result = RTCALM2_RTCMIHA * 10 + RTCALM2_RTCMILA;
	return result;
}

//void enableRtca1_2Timer( void){
//	quarterCount	= 0;
//	RTCINTF = 0x0008; //RTCINTF_1_2SECIF= 1;
//	RTCINTE = 0x0008;//RTCINTE_1_2SECIE= 1;
//}

void disableRtca1_2Timer( void ){
	RTCINTE= 0x0000;//RTCINTE_1_2SECIE= 0;
	RTCINTF= 0x0008;//RTCINTF_1_2SECIF= 1;
}

//void enableRtca1QuarterTimer( void){
//	quarterCount	= 0;
//	RTCINTF_1_4SECIF	= 1;
//	RTCINTE_1_4SECIE	= 1;
//}

void disableRtca1QuarterTimer( void )
{
	RTCINTE_1_4SECIE		= 0;
	RTCINTF_1_4SECIF		= 1;
}

void setRtca24hMode( unsigned char mode1 )
{
	unsigned char indicator = 0;
	unsigned char alarmIndicator = 0;
	unsigned char hour;
	unsigned char alarmHour;

	if ( RTCCTL_RTC24H_24H != mode1 && RTCCTL_RTC24H_12H != mode1 ) {
		return ;
	}

	/// It doesn't do at all for the same mode.
	if ( RTCCTL_RTC24H == mode1 ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// The hour take out.
	hour = getRtcaHour();
	alarmHour = getRtcaAlarmHour();

	/// The set value calculate.
	// 24H mode -> 12H mode.
	if ( getRtca24hMode() == RTCCTL_RTC24H_24H ) {
		if ( hour == 0 ) {					// 0o'clock(12AM).
			hour = 12;
			indicator = RTCHUR_RTCAP_AM;
		} else if ( hour == 12 ) {			// 12o'clock(12PM).
			indicator = RTCHUR_RTCAP_PM;
		} else if ( hour >= 13 ) {			// 13 to 23o'clock(01PM to 11PM).
			hour = hour - 12;
			indicator = RTCHUR_RTCAP_PM;
		} else {							// 1 to 11o'clock(01AM to 11AM).
			indicator = RTCHUR_RTCAP_AM;
		}

		if ( alarmHour == 0 ) {					// 0o'clock(12AM).
			alarmHour = 12;
			alarmIndicator = 0;
		} else if ( alarmHour == 12 ) {			// 12o'clock(12PM).
			alarmIndicator = 1;
		} else if ( alarmHour >= 13 ) {			// 13 to 23o'clock(01PM to 11PM).
			alarmHour = alarmHour - 12;
			alarmIndicator = 1;
		} else {							// 1 to 11o'clock(01AM to 11AM).
			alarmIndicator = 0;
		}


	// 12H mode -> 24H mode.
	} else {
		// 12AM(0o'clock).
		if ( getRtcaIndicator() == RTCHUR_RTCAP_AM && hour == 12) {
			hour = 0;
		// 01PM to 11PM(13 to 23o'clock).
		} else 	if ( getRtcaIndicator() == RTCHUR_RTCAP_PM && hour < 12 ) {
			hour = hour + 12;
		}

		if ( RTCALM2_RTCAPA == 0 && alarmHour == 12) {
			alarmHour = 0;
		} else if (  RTCALM2_RTCAPA == 1 && alarmHour < 12 ) {
			alarmHour = alarmHour + 12;
		}
	}

	// Set mode.
	RTCCTL_RTC24H = mode1;

	/// Set hour.
	setRtcaHour( hour );
	setRtcaAlarmHour( alarmHour ) ;

	/// Set indicator(A.M/P.M).
	setRtcaIndicator( indicator );
	RTCALM2_RTCAPA = alarmIndicator;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return;
}


unsigned char getRtca24hMode( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCCTL_RTC24H;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaYear( unsigned char year )
{
	if ( year > 99 ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCYAR_RTCYH = year / 10 % 10;		/// Set year(tenths digit).
	RTCYAR_RTCYL = year /  1 % 10;		/// Set year(unit digit).

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}


unsigned char getRtcaYear( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCYAR_RTCYH * 10 + RTCYAR_RTCYL;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaMonth( unsigned char month )
{
	if ( month < 1 || month > 12 ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCMON_RTCMOH = month / 10 % 10;		/// Set month(tenths digit).
	RTCMON_RTCMOL = month /  1 % 10;		/// Set month(unit digit).

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}


unsigned char getRtcaMonth( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCMON_RTCMOH * 10 + RTCMON_RTCMOL;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaDay( unsigned char day )
{
	if ( day < 1 || day > 31 ) {
		return;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCMON_RTCDH = day / 10 % 10;		/// Set day(tenths digit).
	RTCMON_RTCDL = day /  1 % 10;		/// Set day(unit digit).

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}


unsigned char getRtcaDay( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCMON_RTCDH * 10 + RTCMON_RTCDL;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaWeek( unsigned char week )
{
	if ( week > RTCYAR_RTCWK_SAT ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCYAR_RTCWK = week;				/// Set weak;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}


unsigned char getRtcaWeek( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCYAR_RTCWK;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaHour( unsigned char hour )
{
	if ( getRtca24hMode() == RTCCTL_RTC24H_24H && hour > 23 ) {
		return ;
	}

	if ( getRtca24hMode() == RTCCTL_RTC24H_12H && ( hour < 1 || hour > 12 ) ) {
		return ;
	}


	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCHUR_RTCHH	= (hour / 10);		/// Set hour(tenths digit).
	RTCHUR_RTCHL	= hour % 10;		/// Set hour(unit digit).

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}

unsigned char getRtcaHour( void )
{
	unsigned char result = 0;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCHUR_RTCHH * 10 + RTCHUR_RTCHL;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaMinute( unsigned char minute )
{
	if ( minute > 59 ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCHUR_RTCMIH = minute / 10 % 10;	/// Set minute(tenths digit).
	RTCHUR_RTCMIL = minute /  1 % 10;	/// Set minute(unit digit).

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}

unsigned char getRtcaMinute( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCHUR_RTCMIH * 10 + RTCHUR_RTCMIL;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaSecond( unsigned char second )
{
	if ( second > 59 ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCSEC_RTCSH = second / 10 % 10;	/// Set second(tenths digit).
	RTCSEC_RTCSL = second /  1 % 10;	/// Set second(unit digit).

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return;
}


unsigned char getRtcaSecond( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCSEC_RTCSH * 10 + RTCSEC_RTCSL;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}


void setRtcaIndicator( unsigned char indicator )
{
	if ( indicator > RTCHUR_RTCAP_PM ) {
		return ;
	}

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Set value.
	RTCHUR_RTCAP = indicator;				/// Set AM/PM;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;
}

unsigned char getRtcaIndicator( void )
{
	unsigned char result;

	/// Check busy.
	while ( RTCCTL_RTCBSY == 1 ) {
		// Wait...
	}

	/// Hold RTCA count-up.
	RTCCTL_RTCHLD = 1;

	/// Get value.
	result = RTCHUR_RTCAP;

	/// Resume RTCA count-up.
	RTCCTL_RTCHLD = 0;

	return result;
}

void setRtcaAlarmIndicator( unsigned char indicator ){
	RTCALM2_RTCAPA = indicator;
}

unsigned char getRtcaAlarmIndicator( void ) {
	unsigned char result;
	result = RTCALM2_RTCAPA;
	return result;
}
