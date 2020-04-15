/** *************************************************************************
 *
 * @file	spi_reg.h
 * @brief	Definition of the Synchronous Serial Interface(SPI) Register.
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
#ifndef	SPI_REG_H__
#define	SPI_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// SPI Mode Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MST			: 1;	///< This bit sets the SPIA operating mode (master mode or slave mode).
		volatile unsigned short		CPOL		: 1;	///< This bit set the SPI clock phase and polarity.
		volatile unsigned short		CPHA		: 1;	///< This bit set the SPI clock phase and polarity.
		volatile unsigned short		LSBFST		: 1;	///< This bit configures the data format (input/output permutation).
		volatile unsigned short		NOCLKDIV	: 1;	///< This bit selects SPICLKn in master mode. This setting is ineffective in slave mode.
		volatile unsigned short		PUEN		: 1;	///< This bit enables pull-up/down of the input pins.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CHLN		: 4;	///< These bits set the bit length of transfer data.
		volatile unsigned short		reserved_2	: 4;	///< Reserved.
	} bit;
} SPINMOD_REG;

/// SPI Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the SPIA operations.
		volatile unsigned short		SFTRST		: 1;	///< This bit issues software reset to SPIA.
		volatile unsigned short		reserved_1	:14;	///< Reserved.
	} bit;
} SPINCTL_REG;

/// SPI Transmit Data Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TXD			: 8;	///< Data can be written to the transmit data buffer through these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} SPINTXD_REG;

/// SPI Receive Data Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RXD			: 8;	///< The receive data buffer can be read through these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} SPINRXD_REG;

/// SPI Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TBEIF		: 1;	///< This bit indicate Transmit buffer empty interrupt cause occurrence status.
		volatile unsigned short		RBFIF		: 1;	///< This bit indicate Receive buffer full interrupt cause occurrence status.
		volatile unsigned short		TENDIF		: 1;	///< This bit indicate End-of-transmission interrupt cause occurrence status.
		volatile unsigned short		OEIF		: 1;	///< This bit indicate Overrun error interrupt cause occurrence status.
		volatile unsigned short		reserved_1	: 3;	///< Reserved.
		volatile unsigned short		BSY			: 1;	///< This bit indicates the SPIA operating status.
		volatile unsigned short		reserved_2	: 8;	///< Reserved.
	} bit;
} SPININTF_REG;

/// SPI Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TBEIE		: 1;	///< This bit enable Transmit buffer empty interrupt.
		volatile unsigned short		RBFIE		: 1;	///< This bit enable Receive buffer full interrupt.
		volatile unsigned short		TENDIE		: 1;	///< This bit enable End-of-transmission interrupt.
		volatile unsigned short		OEIE		: 1;	///< This bit enable Overrun error interrupt.
		volatile unsigned short		reserved_1	:12;	///< Reserved.
	} bit;
} SPININTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// SPI_REG_H__

