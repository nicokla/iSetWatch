/***************************************************************************
 *
 * @file	lcd8b_reg.h
 * @brief	Definition of the LCD Driver(LCD8B) Register.
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
#ifndef	LCD8B_REG_H__
#define	LCD8B_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// LCD8B Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of the LCD8B.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 3;	///< These bits select the division ratio of the LCD8B operating clock.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the LCD8B operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_3	: 7;	///< Reserved.
	} bit;
} LCD8CLK_REG;

/// LCD8B Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the LCD8B operations.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} LCD8CTL_REG;

/// LCD8B Timing Control Register 1.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		LDUTY		: 3;	///< These bits set the drive duty.
		volatile unsigned short		reserved_1	: 5;	///< Reserved.
		volatile unsigned short		FRMCNT		: 4;	///< These bits set the frame frequency.
		volatile unsigned short		reserved_2	: 4;	///< Reserved.
	} bit;
} LCD8TIM1_REG;

/// LCD8B Timing Control Register 2.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		NLINE		: 3;	///< These bits enable the n-line inverse AC drive function and set the number of inverse lines.
		volatile unsigned short		reserved_1	: 5;	///< Reserved.
		volatile unsigned short		BSTC		: 2;	///< These bits select the booster clock frequency for the LCD voltage booster.
		volatile unsigned short		reserved_2	: 6;	///< Reserved.
	} bit;
} LCD8TIM2_REG;

/// LCD8B Power Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		VCEN		: 1;	///< This bit turns the LCD voltage regulator on and off.
		volatile unsigned short		VCSEL		: 1;	///< This bit sets the LCD voltage regulator output (reference voltage for boosting).
		volatile unsigned short		HVLD		: 1;	///< This bit sets the LCD voltage regulator into heavy load protection mode.
		volatile unsigned short		BISEL		: 1;	///< This bit selects the LCD drive bias.
		volatile unsigned short		BSTEN		: 1;	///< This bit turns the LCD voltage booster on and off.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		LC			: 5;	///< These bits set the LCD panel contrast.
		volatile unsigned short		reserved_2	: 3;	///< Reserved.
	} bit;
} LCD8PWR_REG;

/// LCD8B Display Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		DSPC		: 2;	///< These bits control the LCD display on/off and select a display mode.
		volatile unsigned short		DSPAR		: 1;	///< This bit switches the display area in the display data RAM.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		DSPREV		: 1;	///< This bit controls black/white inversion on the LCD display.
		volatile unsigned short		COMREV		: 1;	///< This bit selects the common pin assignment direction.
		volatile unsigned short		SEGREV		: 1;	///< This bit selects the segment pin assignment direction.
		volatile unsigned short		reserved_2	: 9;	///< Reserved.
	} bit;
} LCD8DSP_REG;

/// LCD8B COM Pin Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		PIN0		: 1;	///< These bits configure the partial drive of the COMx pins(0).
		volatile unsigned short		PIN1		: 1;	///< These bits configure the partial drive of the COMx pins(1).
		volatile unsigned short		PIN2		: 1;	///< These bits configure the partial drive of the COMx pins(2).
		volatile unsigned short		PIN3		: 1;	///< These bits configure the partial drive of the COMx pins(3).
		volatile unsigned short		PIN4		: 1;	///< These bits configure the partial drive of the COMx pins(4).
		volatile unsigned short		PIN5		: 1;	///< These bits configure the partial drive of the COMx pins(5).
		volatile unsigned short		PIN6		: 1;	///< These bits configure the partial drive of the COMx pins(6).
		volatile unsigned short		PIN7		: 1;	///< These bits configure the partial drive of the COMx pins(7).
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} LCD8COMCX_REG;

/// LCD8B Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		FRMIF		: 1;	///< This bit indicates the frame interrupt cause occurrence status.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} LCD8INTF_REG;

/// LCD8B Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		FRMIE		: 1;	///< This bit enables the frame interrupt.
		volatile unsigned short		reserved_1	:15;	///< Reserved.
	} bit;
} LCD8INTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// LCD8B_REG_H__

