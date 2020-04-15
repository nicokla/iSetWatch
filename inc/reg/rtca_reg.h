/** *************************************************************************
 *
 * @file	rtc_reg.h
 * @brief	Definition of the Real-time Clock(RTC) Register.
 *
 * @par		Copyright:
 *			Copyright (C) SEIKO EPSON CORPORATION 2012. All rights reserved.
 *
 * @warning -
 *
 * @par		History:
 *			- 10/31/2012    0.90
 *				- First revision.
 *
 ************************************************************************* */
#ifndef	RTC_REG_H__
#define	RTC_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// RTC Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RTCRUN		: 1;	///< This bit starts/stops the real-time clock counter.
		volatile unsigned short		RTCRST		: 1;	///< This bit resets the 1 Hz counter, the RTCCTL.RTCADJ bit, and the RTCCTL.RTCHLD bit.
		volatile unsigned short		RTCADJ		: 1;	///< This bit executes the 30-second correction time adjustment function.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		RTC24H		: 1;	///< This bit sets the hour counter to 24H mode or 12H mode.
		volatile unsigned short		RTCHLD		: 1;	///< This bit halts the count-up operation of the real-time clock counter.
		volatile unsigned short		RTCBSY		: 1;	///< This bit indicates whether the counter is performing count-up operation or not.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
		volatile unsigned short		RTCTRM		: 7;	///< Write the correction value for adjusting the 1 Hz frequency to these bits to execute theoretical regulation.
		volatile unsigned short		RTCTRMBSY	: 1;	///< This bit indicates whether the theoretical regulation is currently executed or not.
	} bit;
} RTCCTL_REG;


/// RTC Second Alarm Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
		volatile unsigned short		RTCSLA		: 4;	///< There bits set the 1-second digit of the alarm time.
		volatile unsigned short		RTCSHA		: 3;	///< There bits set the 10-second digit of the alarm time.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
	} bit;
} RTCALM1_REG;


/// RTC Hour/Minute Alarm Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RTCMILA		: 4;	///< There bits set the 1-minute digit of the alarm time.
		volatile unsigned short		RTCMIHA		: 3;	///< There bits set the 10-minute digit of the alarm time.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		RTCHLA		: 4;	///< There bits set the 1-hour digit of the alarm time.
		volatile unsigned short		RTCHHA		: 2;	///< There bits set the 10-hour digit of the alarm time.
		volatile unsigned short		RTCAPA		: 1;	///< This bit set A.M. or P.M. of the alarm time in 12H mode (RTCCTL.RTC24H bit = 0).
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
	} bit;
} RTCALM2_REG;


/// RTC Stopwatch Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		SWRUN		: 1;	///< This bit starts/stops the stopwatch counter.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		SWRST		: 1;	///< This bit resets the stopwatch counter to 0x00.
		volatile unsigned short		reserved_2	: 3;	///< Reserved.
		volatile unsigned short		BCD100		: 4;	///< The 1/100-second digits of the stopwatch counter can be read as a BCD code.
		volatile unsigned short		BCD10		: 4;	///< The 1/10-second digits of the stopwatch counter can be read as a BCD code.
	} bit;
} RTCSWCTL_REG;


/// RTC Second/1[Hz] Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RTC128HZ	: 1;	///< 1 Hz counter data can be read from these bits(128Hz).
		volatile unsigned short		RTC64HZ		: 1;	///< 1 Hz counter data can be read from these bits(64Hz).
		volatile unsigned short		RTC32HZ		: 1;	///< 1 Hz counter data can be read from these bits(32Hz).
		volatile unsigned short		RTC16HZ		: 1;	///< 1 Hz counter data can be read from these bits(16Hz).
		volatile unsigned short		RTC8HZ		: 1;	///< 1 Hz counter data can be read from these bits(8Hz).
		volatile unsigned short		RTC4HZ		: 1;	///< 1 Hz counter data can be read from these bits(4Hz).
		volatile unsigned short		RTC2HZ		: 1;	///< 1 Hz counter data can be read from these bits(2Hz).
		volatile unsigned short		RTC1HZ		: 1;	///< 1 Hz counter data can be read from these bits(1Hz).
		volatile unsigned short		RTCSL		: 4;	///< There bits are used to set and read the 1-second digit of the second counter.
		volatile unsigned short		RTCSH		: 3;	///< There bits are used to set and read the 10-second digit of the second counter.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
	} bit;
} RTCSEC_REG;


/// RTC Hour/Minute Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RTCMIL		: 4;	///< There bits are used to set and read the 1-minute digit of the minute counter.
		volatile unsigned short		RTCMIH		: 3;	///< There bits are used to set and read the 10-minute digit of the minute counter.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		RTCHL		: 4;	///< There bits are used to set and read the 1-hour digit of the hour counter.
		volatile unsigned short		RTCHH		: 2;	///< There bits are used to set and read the 10-hour digit of the hour counter.
		volatile unsigned short		RTCAP		: 1;	///< This bit is used to set and read A.M. or P.M. data in 12H mode (RTCCTL.RTC24H bit = 0).
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
	} bit;
} RTCHUR_REG;


/// RTC Month/Day Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RTCDL		: 4;	///< There bits are used to set and read the 1-day digit of the day counter.
		volatile unsigned short		RTCDH		: 2;	///< There bits are used to set and read the 10-day digit of the day counter.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		RTCMOL		: 4;	///< There bits are used to set and read the 1-month digit of the month counter.
		volatile unsigned short		RTCMOH		: 1;	///< There bits are used to set and read the 10-month digit of the month counter.
		volatile unsigned short		reserved_2	: 3;	///< Reserved.
	} bit;
} RTCMON_REG;


/// RTC Year/Week Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RTCYL		: 4;	///< There bits are used to set and read the 1-year digit of the year counter.
		volatile unsigned short		RTCYH		: 4;	///< There bits are used to set and read the 10-year digit of the year counter.
		volatile unsigned short		RTCWK		: 3;	///< These bits are used to set and read day of the week.
		volatile unsigned short		reserved_1	: 5;	///< Reserved.
	} bit;
} RTCYAR_REG;


/// RTC Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		_1_32SECIF	: 1;	///< This bit indicate 1/32-second interrupt cause occurrence status.
		volatile unsigned short		_1_8SECIF	: 1;	///< This bit indicate 1/8-second interrupt cause occurrence status.
		volatile unsigned short		_1_4SECIF	: 1;	///< This bit indicate 1/4-second interrupt cause occurrence status.
		volatile unsigned short		_1_2SECIF	: 1;	///< This bit indicate 1/2-second interrupt cause occurrence status.
		volatile unsigned short		_1SECIF		: 1;	///< This bit indicate 1-second interrupt cause occurrence status.
		volatile unsigned short		_1MINIF		: 1;	///< This bit indicate 1-minute interrupt cause occurrence status.
		volatile unsigned short		_1HURIF		: 1;	///< This bit indicate 1-day interrupt cause occurrence status.
		volatile unsigned short		_1DAYIF		: 1;	///< This bit indicate 1-day interrupt cause occurrence status.
		volatile unsigned short		ALARMIF		: 1;	///< This bit indicate Alarm interrupt cause occurrence status.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		SW100IF		: 1;	///< This bit indicate Stopwatch 100 Hz interrupt cause occurrence status.
		volatile unsigned short		SW10IF		: 1;	///< This bit indicate Stopwatch 10 Hz interrupt cause occurrence status.
		volatile unsigned short		SW1IF		: 1;	///< This bit indicate Stopwatch 1 Hz interrupt cause occurrence status.
		volatile unsigned short		RTCTRMIF	: 1;	///< This bit indicate Theoretical regulation completion interrupt cause occurrence status.
	} bit;
} RTCINTF_REG;


/// RTC Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		_1_32SECIE	: 1;	///< This bits enable 1/32-second interrupt.
		volatile unsigned short		_1_8SECIE	: 1;	///< This bits enable 1/8-second interrupt.
		volatile unsigned short		_1_4SECIE	: 1;	///< This bits enable 1/4-second interrupt.
		volatile unsigned short		_1_2SECIE	: 1;	///< This bits enable 1/2-second interrupt.
		volatile unsigned short		_1SECIE		: 1;	///< This bits enable 1-second interrupt.
		volatile unsigned short		_1MINIE		: 1;	///< This bits enable 1-minute interrupt.
		volatile unsigned short		_1HURIE		: 1;	///< This bits enable 1-hour interrupt.
		volatile unsigned short		_1DAYIE		: 1;	///< This bits enable 1-day interrupt.
		volatile unsigned short		ALARMIE		: 1;	///< This bits enable Alarm interrupt.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		SW100IE		: 1;	///< This bit enable Stopwatch 100 Hz interrupt.
		volatile unsigned short		SW10IE		: 1;	///< This bit enable Stopwatch 10 Hz interrupt.
		volatile unsigned short		SW1IE		: 1;	///< This bit enable Stopwatch 1 Hz interrupt.
		volatile unsigned short		RTCTRMIE	: 1;	///< This bit enable Theoretical regulation completion interrupt.
	} bit;
} RTCINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// RTC_REG_H__

