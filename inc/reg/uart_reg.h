/** *************************************************************************
 *
 * @file	uart_reg.h
 * @brief	Definition of the UART Register.
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
#ifndef	UART_REG_H__
#define	UART_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// UART Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of the UART.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		CLKDIV		: 2;	///< These bits select the division ratio of the UART operating clock.
		volatile unsigned short		reserved_2	: 2;	///< Reserved.
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the UART operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_3	: 7;	///< Reserved.
	} bit;
} UANCLK_REG;

/// UART Mode Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		STPB		: 1;	///< This bit sets the stop bit length.
		volatile unsigned short		PRMD		: 1;	///< This bit selects either odd parity or even parity when using the parity function.
		volatile unsigned short		PREN		: 1;	///< This bit sets the data length.
		volatile unsigned short		CHLN		: 1;	///< This bit sets the data length.
		volatile unsigned short		IRMD		: 1;	///< This bit enables the IrDA interface function.
		volatile unsigned short		OUTMD		: 1;	///< This bit sets the USOUTn pin output mode.
		volatile unsigned short		PUEN		: 1;	///< This bit enables pull-up of the USINn pin.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		INVIRTX		: 1;	///< This bit enables the USOUTn output inverting function when the IrDA interface function is enabled.
		volatile unsigned short		INVIRRX		: 1;	///< This bit enables the USINn input inverting function when the IrDA interface function is enabled.
		volatile unsigned short		reserved_2	: 6;	///< Reserved.
	} bit;
} UANMOD_REG;

/// UART Baud-Rate Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		BRT			: 8;	///< These bits set the UART transfer rate.
		volatile unsigned short		FMD			: 4;	///< These bits set the UART transfer rate.
		volatile unsigned short		reserved_1	: 4;	///< Reserved.
	} bit;
} UANBR_REG;

/// UART Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the UART operations.
		volatile unsigned short		SFTRST		: 1;	///< This bit issues software reset to the UART.
		volatile unsigned short		reserved_1	:14;	///< Reserved.
	} bit;
} UANCTL_REG;

/// UART Transmit Data Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TXD			: 8;	///< Data can be written to the transmit data buffer through these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} UANTXD_REG;

/// UART Receive Data Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		RXD			: 8;	///< The receive data buffer can be read through these bits.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} UANRXD_REG;

/// UART Status and Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TBEIF		: 1;	///< These bits indicate Transmit buffer empty interrupt cause occurrence status.
		volatile unsigned short		RB1FIF		: 1;	///< These bits indicate Receive buffer one byte full interrupt cause occurrence status.
		volatile unsigned short		RB2FIF		: 1;	///< These bits indicate Receive buffer two bytes full interrupt cause occurrence status.
		volatile unsigned short		OEIF		: 1;	///< These bits indicate Overrun error interrupt cause occurrence status.
		volatile unsigned short		PEIF		: 1;	///< These bits indicate Parity error interrupt cause occurrence status.
		volatile unsigned short		FEIF		: 1;	///< These bits indicate Framing error interrupt cause occurrence status.
		volatile unsigned short		TENDIF		: 1;	///< These bits indicate End-of-transmission interrupt cause occurrence status.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		TBSY		: 1;	///< This bit indicates the sending status.
		volatile unsigned short		RBSY		: 1;	///< This bit indicates the receiving status.
		volatile unsigned short		reserved_2	: 6;	///< Reserved.
	} bit;
} UANINTF_REG;

/// UART Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		TBEIE		: 1;	///< These bits enable Transmit buffer empty interrupt.
		volatile unsigned short		RB1FIE		: 1;	///< These bits enable Receive buffer one byte full interrupt.
		volatile unsigned short		RB2FIE		: 1;	///< These bits enable Receive buffer two bytes full interrupt.
		volatile unsigned short		OEIE		: 1;	///< These bits enable Overrun error interrupt.
		volatile unsigned short		PEIE		: 1;	///< These bits enable Parity error interrupt.
		volatile unsigned short		FEIE		: 1;	///< These bits enable Framing error interrupt.
		volatile unsigned short		TENDIE		: 1;	///< These bits enable End-of-transmission interrupt.
		volatile unsigned short		reserved_1	: 9;	///< Reserved.
	} bit;
} UANINTE_REG;


#ifdef __cplusplus
}
#endif

#endif	// UART_REG_H__

