/** *************************************************************************
 *
 * @file	pport_reg.h
 * @brief	Definition of the I/O Ports(PPORT) Register.
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
#ifndef	PPORT_REG_H__
#define	PPORT_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// PPORT Port Data Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px1IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px2IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px3IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px4IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px5IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px6IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px7IN		: 1;	///< The GPIO port pin status can be read out from this bit.
		volatile unsigned short		Px0OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px1OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px2OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px3OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px4OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px5OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px6OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
		volatile unsigned short		Px7OUT		: 1;	///< This bit are used to set data to be output from the GPIO port pin.
	} bit;
} PXDAT_REG;

/// PPORT Port Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px1OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px2OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px3OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px4OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px5OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px6OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px7OEN		: 1;	///< This bit enable/disable the GPIO port output.
		volatile unsigned short		Px0IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px1IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px2IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px3IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px4IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px5IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px6IEN		: 1;	///< This bit enable/disable the GPIO port input.
		volatile unsigned short		Px7IEN		: 1;	///< This bit enable/disable the GPIO port input.
	} bit;
} PXIOEN_REG;

/// PPORT Port Pull-up/down Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px1REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px2REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px3REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px4REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px5REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px6REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px7REN		: 1;	///< This bit enable/disable the port pull-up/down control.
		volatile unsigned short		Px0PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px1PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px2PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px3PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px4PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px5PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px6PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
		volatile unsigned short		Px7PDPU		: 1;	///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
	} bit;
} PXRCTL_REG;

/// PPORT Port Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px1IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px2IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px3IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px4IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px5IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px6IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		Px7IF		: 1;	///< This bit indicate the port input interrupt cause occurrence status.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} PXINTF_REG;

/// PPORT Port Interrupt Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px1IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px2IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px3IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px4IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px5IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px6IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px7IE		: 1;	///< This bit enable port input interrupt.
		volatile unsigned short		Px0EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px1EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px2EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px3EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px4EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px5EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px6EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
		volatile unsigned short		Px7EDGE		: 1;	///< This bit select the input signal edge to generate a port input interrupt.
	} bit;
} PXINTCTL_REG;

/// PPORT Port Chattering Filter Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px1CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px2CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px3CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px4CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px5CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px6CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		Px7CHATEN	: 1;	///< This bit enable/disable the chattering filter function.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} PXCHATEN_REG;

/// PPORT Port Mode Select Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px1SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px2SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px3SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px4SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px5SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px6SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		Px7SEL		: 1;	///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} PXMODSEL_REG;

/// PPORT Port Function Select Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		Px0MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px1MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px2MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px3MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px4MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px5MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px6MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
		volatile unsigned short		Px7MUX		: 2;	///< This bit select the peripheral I/O function to be assigned to each port pin.
	} bit;
} PXFNCSEL_REG;

/// PPORT Port Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 2;	///< These bits select the clock source of PPORT (chattering filter).
		volatile unsigned short		KRSTCFG		: 2;	///< These bits configure the key-entry reset function.
		volatile unsigned short		CLKDIV		: 4;	///< These bits select the division ratio of the PPORT operating clock (chattering filter clock).
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the PPORT operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} PCLK_REG;

/// PPORT Port Interrupt Flag Group Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		P0INT		: 1;	///< This bit indicate that P0 port group includes a port that has generated an interrupt.
		volatile unsigned short		P1INT		: 1;	///< This bit indicate that P1 port group includes a port that has generated an interrupt.
		volatile unsigned short		P2INT		: 1;	///< This bit indicate that P2 port group includes a port that has generated an interrupt.
		volatile unsigned short		P3INT		: 1;	///< This bit indicate that P3 port group includes a port that has generated an interrupt.
		volatile unsigned short		P4INT		: 1;	///< This bit indicate that P4 port group includes a port that has generated an interrupt.
		volatile unsigned short		P5INT		: 1;	///< This bit indicate that P5 port group includes a port that has generated an interrupt.
		volatile unsigned short		P6INT		: 1;	///< This bit indicate that P6 port group includes a port that has generated an interrupt.
		volatile unsigned short		P7INT		: 1;	///< This bit indicate that P7 port group includes a port that has generated an interrupt.
		volatile unsigned short		P8INT		: 1;	///< This bit indicate that P8 port group includes a port that has generated an interrupt.
		volatile unsigned short		P9INT		: 1;	///< This bit indicate that P9 port group includes a port that has generated an interrupt.
		volatile unsigned short		PAINT		: 1;	///< This bit indicate that PA port group includes a port that has generated an interrupt.
		volatile unsigned short		PBINT		: 1;	///< This bit indicate that PB port group includes a port that has generated an interrupt.
		volatile unsigned short		PCINT		: 1;	///< This bit indicate that PC port group includes a port that has generated an interrupt.
		volatile unsigned short		PDINT		: 1;	///< This bit indicate that PD port group includes a port that has generated an interrupt.
		volatile unsigned short		PEINT		: 1;	///< This bit indicate that PE port group includes a port that has generated an interrupt.
		volatile unsigned short		PFINT		: 1;	///< This bit indicate that PF port group includes a port that has generated an interrupt.
	} bit;
} PINTFGRP_REG;


#ifdef __cplusplus
}
#endif

#endif	// PPORT_REG_H__

