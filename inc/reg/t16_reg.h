/** *************************************************************************
 *
 * @file	t16_reg.h
 * @brief	Definition of the 16-bit Timer(T16) Register.
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
#ifndef	T16_REG_H__
#define	T16_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// T16 Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of T16 Ch.n.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 4;	///< These bits select the division ratio of the T16 Ch.n operating clock (counter clock).
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the T16 Ch.n operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} T16_NCLK_REG;

/// T16 Mode Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TRMD		: 1;	///< This bit selects the T16 operation mode.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} T16_NMOD_REG;

/// T16 Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the T16 Ch.n operations.
		volatile unsigned short		PRESET		: 1;	///< This bit presets the reload data stored in the T16_nTR register to the counter.
		volatile unsigned short		reserved_1	: 6;	///< Reserved.
		volatile unsigned short		PRUN		: 1;	///< This bit starts/stops the timer.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} T16_NCTL_REG;

/// T16 Reload Data Register.
typedef union {
	volatile unsigned short			reg;
} T16_NTR_REG;

/// T16 Counter Data Register.
typedef union {
	volatile unsigned short			reg;
} T16_NTC_REG;

/// T16 Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		UFIF		: 1;	///< This bit indicates the T16 Ch.n underflow interrupt cause occurrence status.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} T16_NINTF_REG;

/// T16 Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		UFIE		: 1;	///< This bit enables T16 Ch.n underflow interrupts.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} T16_NINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// T16_REG_H__

