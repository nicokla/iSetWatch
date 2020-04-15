/** *************************************************************************
 *
 * @file	misc_reg.h
 * @brief	Definition of the Misc Registers(MISC) Register.
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
#ifndef	MISC_REG_H__
#define	MISC_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// MISC System Protect Register.
typedef union {
	volatile unsigned short			reg;
} MSCPROT_REG;

/// MISC IRAM Size Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		IRAMSZ		: 3;	///< These bits set the internal RAM size that can be used.
		volatile unsigned short		reserved_1	:13;	///< Reserved.
	} bit;
} MSCIRAMSZ_REG;

/// MISC Vector Table Address Low Register.
typedef union {
	volatile unsigned short			reg;
} MSCTTBRL_REG;

/// MISC Vector Table Address High Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TTBR		: 8;	///< These bits set the vector table base address (eight high-order bits).
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} MSCTTBRH_REG;

/// MISC PSR Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		PSRN		: 1;	///< The value (0 or 1) of the PSR N (negative) flag can be read out with this bit.
		volatile unsigned short		PSRZ		: 1;	///< The value (0 or 1) of the PSR Z (zero) flag can be read out with this bit.
		volatile unsigned short		PSRV		: 1;	///< The value (0 or 1) of the PSR V (overflow) flag can be read out with this bit.
		volatile unsigned short		PSRC		: 1;	///< The value (0 or 1) of the PSR C (carry) flag can be read out with this bit.
		volatile unsigned short		PSRIE		: 1;	///< The value (0 or 1) of the PSR IE (interrupt enable) bit can be read out with this bit.
		volatile unsigned short		PSRIL		: 3;	///< The value (0 to 7) of the PSR IL[2:0] (interrupt level) bits can be read out with these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} MSCPSR_REG;

#ifdef __cplusplus
}
#endif

#endif	// MISC_REG_H__

