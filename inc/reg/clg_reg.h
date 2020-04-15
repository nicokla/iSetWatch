/** *************************************************************************
 *
 * @file	clg_reg.h
 * @brief	Definition of the Clock Generator(CLG) Register.
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
#ifndef	CLG_REG_H__
#define	CLG_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// CLG System Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the SYSCLK clock source.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 2;	///< These bits set the division ratio of the clock source to determine the SYSCLK frequency.
		volatile unsigned short		reserved_2	: 2;	///< Reserved.
		volatile unsigned short		WUPSRC		: 2;	///< These bits select the SYSCLK clock source for resetting the CLGSCLK.CLKSRC[1:0] bits at wake-up.
		volatile unsigned short		reserved_3	: 2;	///< Reserved.
		volatile unsigned short		WUPDIV		: 2;	///< These bits select the SYSCLK division ratio for resetting the CLGSCLK.CLKDIV[1:0] bits at wake-up.
		volatile unsigned short		reserved_4	: 1;	///< Reserved.
		volatile unsigned short		WUPMD		: 1;	///< This bit enables the SYSCLK switching function at wake-up.
	} bit;
} CLGSCLK_REG;

/// CLG Oscillation Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		IOSCEN		: 1;	///< This bit control the clock source(IOSC) operation.
		volatile unsigned short		OSC1EN		: 1;	///< This bit control the clock source(OSC1) operation.
		volatile unsigned short		OSC3EN		: 1;	///< This bit control the clock source(OSC3) operation.
		volatile unsigned short		EXOSCEN		: 1;	///< This bit control the clock source(EXOSC) operation.
		volatile unsigned short		reserved_1	: 4;	///< Reserved.
		volatile unsigned short		IOSCSLPC	: 1;	///< This bit control the clock source(IOSC) operations in SLEEP mode.
		volatile unsigned short		OSC1SLPC	: 1;	///< This bit control the clock source(OSC1) operations in SLEEP mode.
		volatile unsigned short		OSC3SLPC	: 1;	///< This bit control the clock source(OSC3) operations in SLEEP mode.
		volatile unsigned short		EXOSCSLPC	: 1;	///< This bit control the clock source(EXOSC) operations in SLEEP mode.
		volatile unsigned short		reserved_2	: 4;	///< Reserved.
	} bit;
} CLGOSC_REG;

/// CLG IOSC Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		reserved_1	: 4;	///< Reserved.
		volatile unsigned short		IOSCSTM		: 1;	///< This bit controls the IOSCCLK auto-trimming function.
		volatile unsigned short		reserved_2	:11;	///< Reserved.
	} bit;
} CLGIOSC_REG;

/// CLG OSC1 Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		OSC1WT		: 2;	///< These bits set the oscillation stabilization waiting time for the OSC1 oscillator circuit.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		INV1N		: 2;	///< These bits set the oscillation inverter gain applied at normal operation of the OSC1 oscillator circuit.
		volatile unsigned short		INV1B		: 2;	///< These bits set the oscillation inverter gain that will be applied at boost startup of the OSC1 oscillator circuit.
		volatile unsigned short		CGI1		: 3;	///< These bits set the internal gate capacitance in the OSC1 oscillator circuit.
		volatile unsigned short		reserved_2	: 1;	///< Reserved.
		volatile unsigned short		OSC1BUP		: 1;	///< This bit enables the oscillation startup control circuit in the OSC1 oscillator circuit.
		volatile unsigned short		OSDEN		: 1;	///< This bit controls the oscillation stop detector in the OSC1 oscillator circuit.
		volatile unsigned short		OSDRB		: 1;	///< This bit enables the OSC1 oscillator circuit restart function by the oscillation stop detector when OSC1 oscillation stop is detected.
		volatile unsigned short		reserved_3	: 1;	///< Reserved.
	} bit;
} CLGOSC1_REG;

/// CLG OSC3 Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		OSC3WT		: 3;	///< These bits set the oscillation stabilization waiting time for the OSC3 oscillator circuit.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		OSC3INV		: 2;	///< These bits set the oscillation inverter gain of the OSC3 oscillator circuit.
		volatile unsigned short		reserved_2	: 2;	///< Reserved.
		volatile unsigned short		OSC3MD		: 2;	///< These bits select an oscillator type of the OSC3 oscillator circuit.
		volatile unsigned short		OSC3FQ		: 2;	///< These bits set the oscillation frequency when the internal oscillator is selected as the OSC3 oscillator.
		volatile unsigned short		reserved_3	: 4;	///< Reserved.
	} bit;
} CLGOSC3_REG;

/// CLG Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		IOSCSTAIF	: 1;	///< This bit indicate the oscillation stabilization waiting completion interrupt cause occurrence status in each clock source(IOSC).
		volatile unsigned short		OSC1STAIF	: 1;	///< This bit indicate the oscillation stabilization waiting completion interrupt cause occurrence status in each clock source(OSC1).
		volatile unsigned short		OSC3STAIF	: 1;	///< This bit indicate the oscillation stabilization waiting completion interrupt cause occurrence status in each clock source(OSC3).
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		IOSCTEDIF	: 1;	///< This bit indicate the IOSC oscillation auto-trimming completion interrupt cause occurrence statuses.
		volatile unsigned short		OSC1STPIF	: 1;	///< This bit indicate the OSC1 oscillation stop.
		volatile unsigned short		reserved_2	:10;	///< Reserved.
	} bit;
} CLGINTF_REG;

/// CLG Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		IOSCSTAIE	: 1;	///< This bit enable the oscillation stabilization waiting completion interrupt of each clock source(IOSC).
		volatile unsigned short		OSC1STAIE	: 1;	///< This bit enable the oscillation stabilization waiting completion interrupt of each clock source(OSC1).
		volatile unsigned short		OSC3STAIE	: 1;	///< This bit enable the oscillation stabilization waiting completion interrupt of each clock source(OSC3).
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		IOSCTEDIE	: 1;	///< This bit enable the IOSC oscillation auto-trimming completion interrupts.
		volatile unsigned short		OSC1STPIE	: 1;	///< This bit enable the OSC1 oscillation stop.
		volatile unsigned short		reserved_2	:10;	///< Reserved.
	} bit;
} CLGINTE_REG;

/// CLG FOUT Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		FOUTEN		: 1;	///< This bit controls the FOUT clock external output.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		FOUTSRC		: 2;	///< These bits select the FOUT clock source.
		volatile unsigned short		FOUTDIV		: 3;	///< These bits set the FOUT clock division ratio.
		volatile unsigned short		reserved_2	: 9;	///< Reserved.
	} bit;
} CLGFOUT_REG;


#ifdef __cplusplus
}
#endif

#endif	// CLG_REG_H__

