
#ifndef RTCA_H__
#define RTCA_H__

#include "init.h"


// Hour counter mode.
#define RTCCTL_RTC24H_12H				( 0 )			///< Hour counter - 12H mode.
#define RTCCTL_RTC24H_24H				( 1 )			///< Hour counter - 24H mode.

// A.M. or P.M. data in 12H mode.
#define RTCHUR_RTCAP_AM				( 0 )			///< Mode - A.M.
#define RTCHUR_RTCAP_PM				( 1 )			///< Mode - P.M.

// Day of the week.
#define RTCYAR_RTCWK_SUN				( 0 )			///< Day of the week - Sunday.
#define RTCYAR_RTCWK_MON				( 1 )			///< Day of the week - Monday.
#define RTCYAR_RTCWK_TUE				( 2 )			///< Day of the week - Tuesday.
#define RTCYAR_RTCWK_WED				( 3 )			///< Day of the week - Wednesday.
#define RTCYAR_RTCWK_THU				( 4 )			///< Day of the week - Thursday.
#define RTCYAR_RTCWK_FRI				( 5 )			///< Day of the week - Friday.
#define RTCYAR_RTCWK_SAT				( 6 )			///< Day of the week - Saturday.


void setRtcaAlarmHour( unsigned char hour );
unsigned char getRtcaAlarmHour( void );
void setRtcaAlarmMinute( unsigned char minute );
unsigned char getRtcaAlarmMinute( void );
extern void enableRtca1_2Timer( void);
extern void disableRtca1_2Timer( void );
extern void enableRtca1QuarterTimer( void);
extern void disableRtca1QuarterTimer( void );
// 24h/12h mode setting.
extern void setRtca24hMode( unsigned char mode );
extern unsigned char getRtca24hMode( void );
// Date setting.
extern void setRtcaYear( unsigned char year );
extern unsigned char getRtcaYear( void );
extern void setRtcaMonth( unsigned char month );
extern unsigned char getRtcaMonth( void );
extern void setRtcaDay( unsigned char day );
extern unsigned char getRtcaDay( void );
extern void setRtcaWeek( unsigned char week );
extern unsigned char getRtcaWeek( void );
// Time setting.
extern void setRtcaHour( unsigned char hour );
extern unsigned char getRtcaHour( void );
extern void setRtcaMinute( unsigned char minute );
extern unsigned char getRtcaMinute( void );
extern void setRtcaSecond( unsigned char second );
extern unsigned char getRtcaSecond( void );
// AM/PM setting.
extern void setRtcaIndicator( unsigned char indicator );
extern unsigned char getRtcaIndicator( void );
void setRtcaAlarmIndicator( unsigned char indicator );
unsigned char getRtcaAlarmIndicator( void );

#endif	//RTCA_H__
