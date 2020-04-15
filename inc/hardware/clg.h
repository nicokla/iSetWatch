#ifndef CLG_H__
#define CLG_H__

#include "init.h"

#define CLG_OSC1_STOP_DETECT		( 1 )		///< Oscillation stop detection(OSC1).
#define CLG_OSC1_STOP_NO_DETECT	( 0 )		///< Not oscillation stop detection(OSC1).

extern void startClgOSC1( void );
extern void stopClgOSC1( void );
extern void enableClgStopDetectionOSC1( void );
extern void disableClgStopDetectionOSC1( void );
int isClgStopDetectionOSC1( void );
#ifdef CLG_OSC3_ENABLE
extern void startClgOSC3( void );
extern void stopClgOSC3( void );
#endif	// CLG_OSC3_ENABLE
extern void startClgIOSC( void );
extern void stopClgIOSC( void );
extern void runClgAutoTrimmingIOSC( void );
extern void switchClgSystemClockOSC1( void );
extern void switchClgSystemClockIOSC( void );
#ifdef CLG_OSC3_ENABLE
extern int switchClgSystemClockOSC3( void );
#endif	// CLG_OSC3_ENABLE


#endif	// CLG_H__
