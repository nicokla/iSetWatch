/** *************************************************************************
 *
 * @file	snda_reg.h
 * @brief	Definition of the Sound Generator(SNDA) Register.
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
#ifndef	SNDA_REG_H__
#define	SNDA_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// SNDA Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of SNDA.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 3;	///< These bits select the division ratio of the SNDA operating clock.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the SNDA operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_3	: 7;	///< Reserved.
	} bit;
} SNDCLK_REG;


/// SNDA Select Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MOSEL		: 2;	///< These bits select a sound output mode.
		volatile unsigned short		SINV		: 1;	///< This bit selects an output pin drive mode.
		volatile unsigned short		reserved_1	: 5;	///< Reserved.
		volatile unsigned short		STIM		: 4;	///< These bits select a tempo or a one-shot buzzer output duration.
		volatile unsigned short		reserved_2	: 4;	///< Reserved.
	} bit;
} SNDSEL_REG;


/// SNDA Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the SNDA operations.
		volatile unsigned short		reserved_1	: 7;	///< Reserved.
		volatile unsigned short		SSTP		: 1;	///< This bit stops sound output.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} SNDCTL_REG;


/// SNDA Data Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		SFRQ		: 8;	///< These bits select a scale or a buzzer signal frequency.
		volatile unsigned short		SLEN		: 6;	///< These bits select a duration or a buzzer signal duty ratio.
		volatile unsigned short		MDRS		: 1;	///< This bit selects the output type in melody mode from a note or a rest.
		volatile unsigned short		MDTI		: 1;	///< This bit specifies a tie in melody mode.
	} bit;
} SNDDAT_REG;


/// SNDA Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		EDIF		: 1;	///< Sound buffer empty interrupt status.
		volatile unsigned short		EMIF		: 1;	///< Sound output completion interrupt status.
		volatile unsigned short		reserved_1	: 6;	///< Reserved.
		volatile unsigned short		SBSY		: 1;	///< This bit indicates the sound output status.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} SNDINTF_REG;


/// SNDA Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		EDIE		: 1;	///< Sound output completion interrupt.
		volatile unsigned short		EMIE		: 1;	///< Sound buffer empty interrupt.
		volatile unsigned short		reserved_1	: 14;	///< Reserved.
	} bit;
} SNDINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// SNDA_REG_H__
