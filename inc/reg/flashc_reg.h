/** *************************************************************************
 *
 * @file	flashc_reg.h
 * @brief	Definition of the Flash Controller(FLASHC) Register.
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
#ifndef	FLASHC_REG_H__
#define	FLASHC_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// FLASHC Flash Read Cycle Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RDWAIT		: 2;	///< These bits set the number of bus access cycles for reading from the Flash memory.
		volatile unsigned short		reserved_1	: 5;	///< Reserved.
		volatile unsigned short		XBUSY		: 1;	///< This bit indicates whether the Flash memory can be accessed or not.
		volatile unsigned short		reserved_2	: 8;	///< Reserved.
	} bit;
} FLASHCWAIT_REG;


#ifdef __cplusplus
}
#endif

#endif	// FLASHC_REG_H__

