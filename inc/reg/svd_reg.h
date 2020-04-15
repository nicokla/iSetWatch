/** *************************************************************************
 *
 * @file	svd_reg.h
 * @brief	Definition of the Supply Voltage Detector(SVD) Register.
 *
 * @par		Copyright:
 *			Copyright (C) SEIKO EPSON CORPORATION 2013. All rights reserved.
 *
 * @warning -
 *
 * @par		History:
 *			- 07/10/2013    0.10
 *				- First revision.
 *
 ************************************************************************* */
#ifndef	SVD_REG_H__
#define	SVD_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// SVD Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of SVD.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 3;	///< These bits select the division ratio of the SVD operating clock.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the SVD operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_3	: 7;	///< Reserved.
	} bit;
} SVDCLK_REG;

/// SVD Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables/disables for the SVD circuit to operate.
		volatile unsigned short		SVDMD		: 2;	///< These bits select intermittent operation mode and its detection cycle.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		SVDRE		: 4;	///< These bits enable/disable the reset issuance function when a low power supply voltage is detected.
		volatile unsigned short		SVDC		: 5;	///< These bits select a comparison voltage for detecting low voltage from among 20 levels.
		volatile unsigned short		SVDSC		: 2;	///< These bits set the condition to generate an interrupt/reset in intermittent operation mode.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
	} bit;
} SVDCTL_REG;

/// SVD Status and Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		SVDIF		: 1;	///< This bit indicates the low power supply voltage detection interrupt cause occurrence status.
		volatile unsigned short		reserved_1	: 7;	///< Reserved.
		volatile unsigned short		SVDDT		: 1;	///< The power supply voltage detection results can be read out from this bit.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} SVDINTF_REG;

/// SVD Interrupt Enable Register.
typedef union {
	volatile unsigned short		reg;
	struct {
		volatile unsigned short		SVDIE		: 1;	///< This bit enables low power supply voltage detection interrupts.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} SVDINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// SVD_REG_H__

