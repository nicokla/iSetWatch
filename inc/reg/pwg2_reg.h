/** *************************************************************************
 *
 * @file	pwg2_reg.h
 * @brief	Definition of the Power Generator(PWG) Register.
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
#ifndef	PWG2_REG_H__
#define	PWG2_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// PWG2 Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		PWGMOD		: 3;	///< These bits control the internal regulator operating mode.
		volatile unsigned short		reserved_1	:13;	///< Reserved.
	} bit;
} PWGCTL_REG;

/// PWG2 Timing Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		DCCCLK		: 2;	///< These bits set the charge pump operating clock (select an OSC1 clock division ratio).
		volatile unsigned short		reserved_1	:14;	///< Reserved.
	} bit;
} PWGTIM_REG;

/// PWG2 Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODCMPIF	: 1;	///< This bit indicates the PWG2 mode transition completion interrupt cause occurrence status.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} PWGINTF_REG;

/// PWG2 Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODCMPIE	: 1;	///< This bit enables the PWG2 mode transition completion interrupt.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} PWGINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// PWG2_REG_H__

