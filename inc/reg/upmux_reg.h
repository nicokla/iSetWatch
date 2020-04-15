/** *************************************************************************
 *
 * @file	upmux_reg.h
 * @brief	Definition of the Universal Port Multiplexer (UPMUX) Register.
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
#ifndef	UPMUX_REG_H__
#define	UPMUX_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// Pxy-xz Universal Port Multiplexer Setting Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		PxyPERISEL	: 3;	///< These bits specify the peripheral I/O function to be assigned to the port.
		volatile unsigned short		PxyPERICH	: 2;	///< These bits specify a peripheral circuit channel number.
		volatile unsigned short		PxyPPFNC	: 3;	///< These bits specify a peripheral circuit.
		volatile unsigned short		PxzPERISEL	: 3;	///< These bits specify the peripheral I/O function to be assigned to the port.
		volatile unsigned short		PxzPERICH	: 2;	///< These bits specify a peripheral circuit channel number.
		volatile unsigned short		PxzPPFNC	: 3;	///< These bits specify a peripheral circuit.
	} bit;
} PXUPMUXN_REG;

#ifdef __cplusplus
}
#endif

#endif	// UPMUX_REG_H__

