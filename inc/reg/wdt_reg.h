/** *************************************************************************
 *
 * @file	wdt_reg.h
 * @brief	Definition of the Watchdog Timer(WDT) Register.
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
#ifndef	WDT_REG_H__
#define	WDT_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// WDT Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of WDT.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 2;	///< These bits select the division ratio of the WDT operating clock (counter clock).
		volatile unsigned short		reserved_2	: 2;	///< Reserved.
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the WDT operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_3	: 7;	///< Reserved.
	} bit;
} WDTCLK_REG;

/// WDT Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		WDTRUN		: 4;	///< These bits control WDT to run and stop.
		volatile unsigned short		WDTCNTRST	: 1;	///< This bit resets WDT.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		STATNMI		: 1;	///< This bit indicates that a counter overflow and NMI have occurred.
		volatile unsigned short		NMIXRST		: 1;	///< This bit sets the WDT operating mode.
		volatile unsigned short		reserved_2	: 6;	///< Reserved.
	} bit;
} WDTCTL_REG;


#ifdef __cplusplus
}
#endif

#endif	// WDT_REG_H__

