/** *************************************************************************
 *
 * @file	rfc_reg.h
 * @brief	Definition of the R/F Converter(RFC) Register.
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
#ifndef	RFC_REG_H__
#define	RFC_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// RFC Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of the RFC.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 2;	///< These bits select the division ratio of the RFC operating clock.
		volatile unsigned short		reserved_2	: 2;	///< Reserved.
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the RFC operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_3	: 7;	///< Reserved.
	} bit;
} RFCNCLK_REG;

/// RFC Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the RFC operations.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		SMODE		: 2;	///< These bits configure the oscillation mode.
		volatile unsigned short		EVTEN		: 1;	///< This bit enables external clock input mode (event counter mode).
		volatile unsigned short		reserved_2	: 9;	///< Reserved.
	} bit;
} RFCNCTL_REG;

/// RFC Oscillation Trigger Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		SREF		: 1;	///< This bit controls CR oscillation for the reference resistor.
		volatile unsigned short		SSENA		: 1;	///< This bit controls CR oscillation for sensor A.
		volatile unsigned short		SSENB		: 1;	///< This bit controls CR oscillation for sensor B.
		volatile unsigned short		reserved_1	:13;	///< Reserved.
	} bit;
} RFCNTRG_REG;

/// RFC Measurement Counter Low Register.
typedef union {
	volatile unsigned short			reg;
} RFCNMCL_REG;

/// RFC Measurement Counter High Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MC			: 8;	///< Measurement counter data can be read and written through these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} RFCNMCH_REG;

/// RFC Time Base Counter Low Register.
typedef union {
	volatile unsigned short			reg;
} RFCNTCL_REG;

/// RFC Time Base Counter High Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TC			: 8;	///< Time base counter data can be read and written through these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} RFCNTCH_REG;

/// RFC Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		EREFIF		: 1;	///< This bit indicate Reference oscillation completion interrupt cause occurrence status.
		volatile unsigned short		ESENAIF		: 1;	///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
		volatile unsigned short		ESENBIF		: 1;	///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
		volatile unsigned short		OVMCIF		: 1;	///< This bit indicate Measurement counter overflow error interrupt cause occurrence status.
		volatile unsigned short		OVTCIF		: 1;	///< This bit indicate Time base counter overflow error interrupt cause occurrence status.
		volatile unsigned short		reserved_1	:11;	///< Reserved.
	} bit;
} RFCNINTF_REG;

/// RFC Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		EREFIE		: 1;	///< This bit enable Reference oscillation completion interrupt.
		volatile unsigned short		ESENAIE		: 1;	///< This bit enable Sensor A oscillation completion interrupt.
		volatile unsigned short		ESENBIE		: 1;	///< This bit enable Sensor B oscillation completion interrupt.
		volatile unsigned short		OVMCIE		: 1;	///< This bit enable Measurement counter overflow error interrupt.
		volatile unsigned short		OVTCIE		: 1;	///< This bit enable Time base counter overflow error interrupt.
		volatile unsigned short		reserved_1	:11;	///< Reserved.
	} bit;
} RFCNINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// RFC_REG_H__

