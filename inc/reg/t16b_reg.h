/** *************************************************************************
 *
 * @file	t16b_reg.h
 * @brief	Definition of the 16-bit PWM Timer(T16B) Register.
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
#ifndef	T16B_REG_H__
#define	T16B_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif


/// T16B Ch.n Clock Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CLKSRC		: 3;	///< These bits select the clock source of T16B Ch.n.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		CLKDIV		: 4;	///< These bits select the division ratio of the T16B Ch.n operating clock (counter clock).
		volatile unsigned short		DBRUN		: 1;	///< This bit sets whether the T16B Ch.n operating clock is supplied in DEBUG mode or not.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} T16BNCLK_REG;

/// T16B Ch.n Counter Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		MODEN		: 1;	///< This bit enables the T16B Ch.n operations.
		volatile unsigned short		PRESET		: 1;	///< This bit resets the counter.
		volatile unsigned short		RUN			: 1;	///< This bit starts/stops counting.
		volatile unsigned short		ONEST		: 1;	///< This bit selects the counter repeat/one-shot mode.
		volatile unsigned short		CNTMD		: 2;	///< These bits select the counter up/down mode.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
		volatile unsigned short		MAXBSY		: 1;	///< This bit indicates whether data can be written to the T16BnMC register or not.
		volatile unsigned short		reserved_2	: 7;	///< Reserved.
	} bit;
} T16BNCTL_REG;

/// T16B Ch.n Max Counter Data Register.
typedef union {
	volatile unsigned short			reg;
} T16BNMC_REG;

/// T16B Ch.n Timer Counter Data Register.
typedef union {
	volatile unsigned short			reg;
} T16BNTC_REG;

/// T16B Ch.n Counter Status Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		BSY			: 1;	///< This bit indicates the counter operating status.
		volatile unsigned short		UP_DOWN		: 1;	///< This bit indicates the currently set count direction.
		volatile unsigned short		CAPI0		: 1;	///< These bits indicate the signal level currently input to the CAPx0 pin.
		volatile unsigned short		CAPI1		: 1;	///< These bits indicate the signal level currently input to the CAPx1 pin.
		volatile unsigned short		CAPI2		: 1;	///< These bits indicate the signal level currently input to the CAPx2 pin.
		volatile unsigned short		CAPI3		: 1;	///< These bits indicate the signal level currently input to the CAPx3 pin.
		volatile unsigned short		CAPI4		: 1;	///< These bits indicate the signal level currently input to the CAPx4 pin.
		volatile unsigned short		CAPI5		: 1;	///< These bits indicate the signal level currently input to the CAPx5 pin.
		volatile unsigned short		reserved_1	: 8;	///< Reserved.
	} bit;
} T16BNCS_REG;

/// T16B Ch.n Interrupt Flag Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CNTZEROIF	: 1;	///< Counter zero interrupt.
		volatile unsigned short		CNTMAXIF	: 1;	///< Counter MAX interrupt.
		volatile unsigned short		CMPCAP0IF	: 1;	///< Compare/capture 0 interrupt.
		volatile unsigned short		CAPOW0IF	: 1;	///< Capture 0 overwrite interrupt.
		volatile unsigned short		CMPCAP1IF	: 1;	///< Compare/capture 1 interrupt.
		volatile unsigned short		CAPOW1IF	: 1;	///< Capture 1 overwrite interrupt.
		volatile unsigned short		CMPCAP2IF	: 1;	///< Compare/capture 2 interrupt.
		volatile unsigned short		CAPOW2IF	: 1;	///< Capture 2 overwrite interrupt.
		volatile unsigned short		CMPCAP3IF	: 1;	///< Compare/capture 3 interrupt.
		volatile unsigned short		CAPOW3IF	: 1;	///< Capture 3 overwrite interrupt.
		volatile unsigned short		CMPCAP4IF	: 1;	///< Compare/capture 4 interrupt.
		volatile unsigned short		CAPOW4IF	: 1;	///< Capture 4 overwrite interrupt.
		volatile unsigned short		CMPCAP5IF	: 1;	///< Compare/capture 5 interrupt.
		volatile unsigned short		CAPOW5IF	: 1;	///< Capture 5 overwrite interrupt.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
	} bit;
} T16BNINTF_REG;

/// T16B Ch.n Interrupt Enable Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CNTZEROIE	: 1;	///< Counter zero interrupt.
		volatile unsigned short		CNTMAXIE	: 1;	///< Counter MAX interrupt.
		volatile unsigned short		CMPCAP0IE	: 1;	///< Compare/capture 0 interrupt.
		volatile unsigned short		CAPOW0IE	: 1;	///< Capture 0 overwrite interrupt.
		volatile unsigned short		CMPCAP1IE	: 1;	///< Compare/capture 1 interrupt.
		volatile unsigned short		CAPOW1IE	: 1;	///< Capture 1 overwrite interrupt.
		volatile unsigned short		CMPCAP2IE	: 1;	///< Compare/capture 2 interrupt.
		volatile unsigned short		CAPOW2IE	: 1;	///< Capture 2 overwrite interrupt.
		volatile unsigned short		CMPCAP3IE	: 1;	///< Compare/capture 3 interrupt.
		volatile unsigned short		CAPOW3IE	: 1;	///< Capture 3 overwrite interrupt.
		volatile unsigned short		CMPCAP4IE	: 1;	///< Compare/capture 4 interrupt.
		volatile unsigned short		CAPOW4IE	: 1;	///< Capture 4 overwrite interrupt.
		volatile unsigned short		CMPCAP5IE	: 1;	///< Compare/capture 5 interrupt.
		volatile unsigned short		CAPOW5IE	: 1;	///< Capture 5 overwrite interrupt.
		volatile unsigned short		reserved_1	: 2;	///< Reserved.
	} bit;
} T16BNINTE_REG;

/// T16B Ch.n Comparator/Capture m Control Register.
typedef union {
	volatile unsigned short			reg;
	struct {
		volatile unsigned short		CCMD		: 1;	///< This bit selects the operating mode of the comparator/capture circuit m.
		volatile unsigned short		TOUTINV		: 1;	///< This bit selects the TOUTnm signal polarity.
		volatile unsigned short		TOUTMD		: 3;	///< These bits configure how the TOUTnm signal waveform is changed.
		volatile unsigned short		TOUTO		: 1;	///< This bit sets the TOUTnm signal output level
		volatile unsigned short		TOUTMT		: 1;	///< This bit selects whether the comparator equal signal.
		volatile unsigned short		reserved_1	: 1;	///< Reserved.
		volatile unsigned short		CAPTRG		: 2;	///< These bits select the trigger edge(s) of the trigger signal.
		volatile unsigned short		CAPIS		: 2;	///< These bits select the trigger signal for capturing.
		volatile unsigned short		CBUFMD		: 3;	///< These bits select the timing to load the comparison value written.
		volatile unsigned short		SCS			: 1;	///< This bit selects either synchronous capture mode or asynchronous capture mode.
	} bit;
} T16BNCCCTLM_REG;

/// T16B Ch.n Compare/Capture m Data Register.
typedef union {
	volatile unsigned short			reg;
} T16BNCCRM_REG;


#ifdef __cplusplus
}
#endif

#endif	// T16B_REG_H__

