/** *************************************************************************
 *
 * @file	itc_reg.h
 * @brief	Definition of the Interrupt Controller(ITC) Register
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
#ifndef	ITC_REG_H__
#define	ITC_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// ITC Interrupt Level Setup Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		ILV_L		: 3;	///< These bits set the interrupt level of each interrupt.
		volatile unsigned short		reserved_1	: 5;	///< Reserved.
		volatile unsigned short		ILV_H		: 3;	///< These bits set the interrupt level of each interrupt.
		volatile unsigned short		reserved_2	: 5;	///< Reserved.
	} bit;
} ITCLVX_REG;


#ifdef __cplusplus
}
#endif

#endif	// ITC_REG_H__

