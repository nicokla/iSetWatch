#ifndef	C17W15_REG_H__
#define	C17W15_REG_H__

#ifdef	__cplusplus
extern "C" {
#endif

// Include Files
#include "./reg/misc_reg.h"
#include "./reg/pwg2_reg.h"
#include "./reg/clg_reg.h"
#include "./reg/itc_reg.h"
#include "./reg/wdt_reg.h"
#include "./reg/rtca_reg.h"
#include "./reg/svd_reg.h"
#include "./reg/t16_reg.h"
#include "./reg/t16b_reg.h"
#include "./reg/flashc_reg.h"
#include "./reg/pport_reg.h"
#include "./reg/upmux_reg.h"
#include "./reg/uart_reg.h"
#include "./reg/spia_reg.h"
#include "./reg/i2c_reg.h"
#include "./reg/snda_reg.h"
#include "./reg/lcd8b_reg.h"
#include "./reg/rfc_reg.h"


// Status
#define 	STATUS_NG				( 0 )	///< Status fail.
#define 	STATUS_OK				( 1 )	///< Status success.
#define 	STATUS_DISABLE			( 0 )	///< Status disable.
#define 	STATUS_ENABLE			( 1 )	///< Status enable.
#define 	STATUS_NO_OCCURRED		( 0 )	///< No cause of interrupt occurred.
#define 	STATUS_OCCURRED			( 1 )	///< Cause of interrupt occurred.


// Interrupt Level Select
#define	INTERRUPT_LEVEL0		( 0x0 )		///< Interrupt priorities 0
#define	INTERRUPT_LEVEL1		( 0x1 )		///< Interrupt priorities 1
#define	INTERRUPT_LEVEL2		( 0x2 )		///< Interrupt priorities 2
#define	INTERRUPT_LEVEL3		( 0x3 )		///< Interrupt priorities 3
#define	INTERRUPT_LEVEL4		( 0x4 )		///< Interrupt priorities 4
#define	INTERRUPT_LEVEL5		( 0x5 )		///< Interrupt priorities 5
#define	INTERRUPT_LEVEL6		( 0x6 )		///< Interrupt priorities 6
#define	INTERRUPT_LEVEL7		( 0x7 )		///< Interrupt priorities 7


// Register Base Address
#define	MISC_REG_BASE_ADDR		( 0x4000 )	///< Misc Registers (MISC) Register Base Address.
#define	PWG2_REG_BASE_ADDR		( 0x4020 )	///< Power Generator (PWG2) Register Base Address.
#define	CLG_REG_BASE_ADDR		( 0x4040 )	///< Clock Generator (CLG) Register Base Address.
#define	ITC_REG_BASE_ADDR		( 0x4080 )	///< Interrupt Controller (ITC) Register Base Address.
#define	WDT_REG_BASE_ADDR		( 0x40A0 )	///< Watchdog Timer (WDT) Register Base Address.
#define	RTC_REG_BASE_ADDR		( 0x40C0 )	///< Real-time Clock (RTCA) Register Base Address.
#define	SVD_REG_BASE_ADDR		( 0x4100 )	///< Supply Voltage Detector (SVD) Register Base Address.
#define	T16_0_REG_BASE_ADDR		( 0x4160 )	///< 16-bit Timer (T16) Ch.0 Register Base Address.
#define	FLASHC_REG_BASE_ADDR	( 0x41B0 )	///< Flash Controller (FLASHC) Register Base Address.
#define	PPORT_REG_BASE_ADDR		( 0x4200 )	///< I/O Ports (PPORT) Register Base Address.
#define	UPMUX_REG_BASE_ADDR		( 0x4300 )	///< Universal Port Multiplexer (UPMUX) Register Base Address.
#define	UART_0_REG_BASE_ADDR	( 0x4380 )	///< UART (UART) Ch.0 Register Base Address.
#define	T16_1_REG_BASE_ADDR		( 0x43A0 )	///< 16-bit Timer (T16) Ch.1 Register Base Address.
#define	SPI_0_REG_BASE_ADDR		( 0x43B0 )	///< Synchronous Serial Interface (SPIA) Ch.0 Register Base Address.
#define	I2C_REG_BASE_ADDR		( 0x43C0 )	///< I2C (I2C) Register Base Address Register Base Address.
#define	T16B_0_REG_BASE_ADDR	( 0x5000 )	///< 16-bit PWM Timer (T16B) Ch.0 Register Base Address.
#define	T16B_1_REG_BASE_ADDR	( 0x5040 )	///< 16-bit PWM Timer (T16B) Ch.1 Register Base Address.
#define	UART_1_REG_BASE_ADDR	( 0x5200 )	///< UART (UART) Ch.1 Register Base Address.
#define	T16_2_REG_BASE_ADDR		( 0x5260 )	///< 16-bit Timer (T16) Ch.2 Register Base Address.
#define	SNDA_REG_BASE_ADDR		( 0x5300 )	///< Sound Generator (SNDA) Register Base Address.
#define	LCD8B_REG_BASE_ADDR		( 0x5400 )	///< LCD Driver (LCD8B) Register Base Address.
#define	RFC_0_REG_BASE_ADDR		( 0x5440 )	///< R/F Converter (RFC) ch.0 Register Base Address.
#define	RFC_1_REG_BASE_ADDR		( 0x5460 )	///< R/F Converter (RFC) ch.1 Register Base Address.
#define	RFC_2_REG_BASE_ADDR		( 0x5480 )	///< R/F Converter (RFC) ch.2 Register Base Address.
#define	RFC_3_REG_BASE_ADDR		( 0x54a0 )	///< R/F Converter (RFC) ch.3 Register Base Address.


/* ----- C17W15 Registers ----- */

/********************/
/* ----- MISC ----- */
/********************/

/// MISC System Protect Register.
#define	MSCPROT				(*((MSCPROT_REG *)(MISC_REG_BASE_ADDR + 0x00))).reg

/// MISC IRAM Size Register.
#define	MSCIRAMSZ			(*((MSCIRAMSZ_REG *)(MISC_REG_BASE_ADDR + 0x02))).reg
#define	MSCIRAMSZ_IRAMSZ	(*((MSCIRAMSZ_REG *)(MISC_REG_BASE_ADDR + 0x02))).bit.IRAMSZ		///< These bits set the internal RAM size that can be used.

/// MISC Vector Table Address Low Register.
#define	MSCTTBRL			(*((MSCTTBRL_REG *)(MISC_REG_BASE_ADDR + 0x04))).reg

/// MISC Vector Table Address High Register.
#define	MSCTTBRH			(*((MSCTTBRH_REG *)(MISC_REG_BASE_ADDR + 0x06))).reg
#define	MSCTTBRH_TTBR		(*((MSCTTBRH_REG *)(MISC_REG_BASE_ADDR + 0x06))).bit.TTBR			///< These bits set the vector table base address (eight high-order bits).

/// MISC PSR Register.
#define	MSCPSR				(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).reg
#define	MSCPSR_PSRN			(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).bit.PSRN				///< The value (0 or 1) of the PSR N (negative) flag can be read out with this bit.
#define	MSCPSR_PSRZ			(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).bit.PSRZ				///< The value (0 or 1) of the PSR Z (zero) flag can be read out with this bit.
#define	MSCPSR_PSRV			(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).bit.PSRV				///< The value (0 or 1) of the PSR V (overflow) flag can be read out with this bit.
#define	MSCPSR_PSRC			(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).bit.PSRC				///< The value (0 or 1) of the PSR C (carry) flag can be read out with this bit.
#define	MSCPSR_PSRIE		(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).bit.PSRIE			///< The value (0 or 1) of the PSR IE (interrupt enable) bit can be read out with this bit.
#define	MSCPSR_PSRIL		(*((MSCPSR_REG *)(MISC_REG_BASE_ADDR + 0x08))).bit.PSRIL			///< The value (0 to 7) of the PSR IL[2:0] (interrupt level) bits can be read out with these bits.


/*******************/
/* ----- PWG2 ----- */
/*******************/

/// PWG2 Control Register.
#define	PWGCTL				(*((PWGCTL_REG *)(PWG2_REG_BASE_ADDR + 0x00))).reg
#define	PWGCTL_PWGMOD		(*((PWGCTL_REG *)(PWG2_REG_BASE_ADDR + 0x00))).bit.PWGMOD			///< These bits control the internal regulator operating mode.

/// PWG2 Timing Control Register.
#define	PWGTIM				(*((PWGTIM_REG *)(PWG2_REG_BASE_ADDR + 0x02))).reg
#define	PWGTIM_DCCCLK		(*((PWGTIM_REG *)(PWG2_REG_BASE_ADDR + 0x02))).bit.DCCCLK			///< These bits set the charge pump operating clock (select an OSC1 clock division ratio).

/// PWG2 Interrupt Flag Register.
#define	PWGINTF				(*((PWGINTF_REG *)(PWG2_REG_BASE_ADDR + 0x04))).reg
#define	PWGINTF_MODCMPIF	(*((PWGINTF_REG *)(PWG2_REG_BASE_ADDR + 0x04))).bit.MODCMPIF		///< This bit indicates the PWG2 mode transition completion interrupt cause occurrence status.

/// PWG2 Interrupt Enable Register.
#define	PWGINTE				(*((PWGINTE_REG *)(PWG2_REG_BASE_ADDR + 0x06))).reg
#define	PWGINTE_MODCMPIF	(*((PWGINTE_REG *)(PWG2_REG_BASE_ADDR + 0x06))).bit.MODCMPIE		///< This bit enables the PWG2 mode transition completion interrupt.


/*******************/
/* ----- CLG ----- */
/*******************/

/// CLG System Clock Control Register.
#define	CLGSCLK				(*((CLGSCLK_REG *)(CLG_REG_BASE_ADDR + 0x00))).reg
#define	CLGSCLK_CLKSRC		(*((CLGSCLK_REG *)(CLG_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the SYSCLK clock source.
#define	CLGSCLK_CLKDIV		(*((CLGSCLK_REG *)(CLG_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits set the division ratio of the clock source to determine the SYSCLK frequency.
#define	CLGSCLK_WUPSRC		(*((CLGSCLK_REG *)(CLG_REG_BASE_ADDR + 0x00))).bit.WUPSRC			///< These bits select the SYSCLK clock source for resetting the CLGSCLK.CLKSRC[1:0] bits at wake-up.
#define	CLGSCLK_WUPDIV		(*((CLGSCLK_REG *)(CLG_REG_BASE_ADDR + 0x00))).bit.WUPDIV			///< These bits select the SYSCLK division ratio for resetting the CLGSCLK.CLKDIV[1:0] bits at wake-up.
#define	CLGSCLK_WUPMD		(*((CLGSCLK_REG *)(CLG_REG_BASE_ADDR + 0x00))).bit.WUPMD			///< This bit enables the SYSCLK switching function at wake-up.

/// CLG Oscillation Control Registe.
#define	CLGOSC				(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).reg
#define	CLGOSC_IOSCEN		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.IOSCEN			///< This bit control the clock source(IOSC) operation.
#define	CLGOSC_OSC1EN		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.OSC1EN			///< This bit control the clock source(OSC1) operation.
#define	CLGOSC_OSC3EN		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.OSC3EN			///< This bit control the clock source(OSC3) operation.
#define	CLGOSC_EXOSCEN		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.EXOSCEN			///< This bit control the clock source(EXOSC) operation.
#define	CLGOSC_IOSCSLPC		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.IOSCSLPC			///< This bit control the clock source(IOSC) operations in SLEEP mode.
#define	CLGOSC_OSC1SLPC		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.OSC1SLPC			///< This bit control the clock source(OSC1) operations in SLEEP mode.
#define	CLGOSC_OSC3SLPC		(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.OSC3SLPC			///< This bit control the clock source(OSC3) operations in SLEEP mode.
#define	CLGOSC_EXOSCSLPC	(*((CLGOSC_REG *)(CLG_REG_BASE_ADDR + 0x02))).bit.EXOSCSLPC			///< This bit control the clock source(EXOSC) operations in SLEEP mode.

/// CLG IOSC Control Register.
#define	CLGIOSC				(*((CLGIOSC_REG *)(CLG_REG_BASE_ADDR + 0x04))).reg
#define	CLGIOSC_IOSCSTM		(*((CLGIOSC_REG *)(CLG_REG_BASE_ADDR + 0x04))).bit.IOSCSTM			///< This bit controls the IOSCCLK auto-trimming function.

/// CLG OSC1 Control Register.
#define	CLGOSC1				(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).reg
#define	CLGOSC1_OSC1WT		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.OSC1WT			///< These bits set the oscillation stabilization waiting time for the OSC1 oscillator circuit.
#define	CLGOSC1_INV1N		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.INV1N			///< These bits set the oscillation inverter gain applied at normal operation of the OSC1 oscillator circuit.
#define	CLGOSC1_INV1B		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.INV1B			///< These bits set the oscillation inverter gain that will be applied at boost startup of the OSC1 oscillator circuit.
#define	CLGOSC1_CGI1		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.CGI1				///< These bits set the internal gate capacitance in the OSC1 oscillator circuit.
#define	CLGOSC1_OSC1BUP		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.OSC1BUP			///< This bit enables the oscillation startup control circuit in the OSC1 oscillator circuit.
#define	CLGOSC1_OSDEN		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.OSDEN			///< This bit controls the oscillation stop detector in the OSC1 oscillator circuit.
#define	CLGOSC1_OSDRB		(*((CLGOSC1_REG *)(CLG_REG_BASE_ADDR + 0x06))).bit.OSDRB			///< This bit enables the OSC1 oscillator circuit restart function by the oscillation stop detector when OSC1 oscillation stop is detected.

/// CLG OSC3 Control Register.
#define	CLGOSC3				(*((CLGOSC3_REG *)(CLG_REG_BASE_ADDR + 0x08))).reg
#define	CLGOSC3_OSC3WT		(*((CLGOSC3_REG *)(CLG_REG_BASE_ADDR + 0x08))).bit.OSC3WT			///< These bits set the oscillation stabilization waiting time for the OSC3 oscillator circuit.
#define	CLGOSC3_OSC3INV		(*((CLGOSC3_REG *)(CLG_REG_BASE_ADDR + 0x08))).bit.OSC3INV			///< These bits set the oscillation inverter gain of the OSC3 oscillator circuit.
#define	CLGOSC3_OSC3MD		(*((CLGOSC3_REG *)(CLG_REG_BASE_ADDR + 0x08))).bit.OSC3MD			///< These bits select an oscillator type of the OSC3 oscillator circuit.
#define	CLGOSC3_OSC3FQ		(*((CLGOSC3_REG *)(CLG_REG_BASE_ADDR + 0x08))).bit.OSC3FQ			///< These bits set the oscillation frequency when the internal oscillator is selected as the OSC3 oscillator.

/// CLG Interrupt Flag Register.
#define	CLGINTF				(*((CLGINTF_REG *)(CLG_REG_BASE_ADDR + 0x0C))).reg
#define	CLGINTF_IOSCSTAIF	(*((CLGINTF_REG *)(CLG_REG_BASE_ADDR + 0x0C))).bit.IOSCSTAIF		///< This bit indicate the oscillation stabilization waiting completion interrupt cause occurrence status in each clock source(IOSC).
#define	CLGINTF_OSC1STAIF	(*((CLGINTF_REG *)(CLG_REG_BASE_ADDR + 0x0C))).bit.OSC1STAIF		///< This bit indicate the oscillation stabilization waiting completion interrupt cause occurrence status in each clock source(OSC1).
#define	CLGINTF_OSC3STAIF	(*((CLGINTF_REG *)(CLG_REG_BASE_ADDR + 0x0C))).bit.OSC3STAIF		///< This bit indicate the oscillation stabilization waiting completion interrupt cause occurrence status in each clock source(OSC3).
#define	CLGINTF_IOSCTEDIF	(*((CLGINTF_REG *)(CLG_REG_BASE_ADDR + 0x0C))).bit.IOSCTEDIF		///< This bit indicate the IOSC oscillation auto-trimming completion interrupt cause occurrence statuses.
#define	CLGINTF_OSC1STPIF	(*((CLGINTF_REG *)(CLG_REG_BASE_ADDR + 0x0C))).bit.OSC1STPIF		///< This bit indicate the OSC1 oscillation stop.

/// CLG Interrupt Enable Register.
#define	CLGINTE				(*((CLGINTE_REG *)(CLG_REG_BASE_ADDR + 0x0E))).reg
#define	CLGINTE_IOSCSTAIE	(*((CLGINTE_REG *)(CLG_REG_BASE_ADDR + 0x0E))).bit.IOSCSTAIE		///< This bit enable the oscillation stabilization waiting completion interrupt of each clock source(IOSC).
#define	CLGINTE_OSC1STAIE	(*((CLGINTE_REG *)(CLG_REG_BASE_ADDR + 0x0E))).bit.OSC1STAIE		///< This bit enable the oscillation stabilization waiting completion interrupt of each clock source(OSC1).
#define	CLGINTE_OSC3STAIE	(*((CLGINTE_REG *)(CLG_REG_BASE_ADDR + 0x0E))).bit.OSC3STAIE		///< This bit enable the oscillation stabilization waiting completion interrupt of each clock source(OSC3).
#define	CLGINTE_IOSCTEDIE	(*((CLGINTE_REG *)(CLG_REG_BASE_ADDR + 0x0E))).bit.IOSCTEDIE		///< This bit enable the IOSC oscillation auto-trimming completion interrupts.
#define	CLGINTE_OSC1STPIE	(*((CLGINTE_REG *)(CLG_REG_BASE_ADDR + 0x0E))).bit.OSC1STPIE		///< This bit enable the OSC1 oscillation stop.

/// CLG FOUT Control Register.
#define	CLGFOUT				(*((CLGFOUT_REG *)(CLG_REG_BASE_ADDR + 0x10))).reg
#define	CLGFOUT_FOUTEN		(*((CLGFOUT_REG *)(CLG_REG_BASE_ADDR + 0x10))).bit.FOUTEN			///< This bit controls the FOUT clock external output.
#define	CLGFOUT_FOUTSRC		(*((CLGFOUT_REG *)(CLG_REG_BASE_ADDR + 0x10))).bit.FOUTSRC			///< These bits select the FOUT clock source.
#define	CLGFOUT_FOUTDIV		(*((CLGFOUT_REG *)(CLG_REG_BASE_ADDR + 0x10))).bit.FOUTDIV			///< These bits set the FOUT clock division ratio.


/*******************/
/* ----- ITC ----- */
/*******************/

// ITC Interrupt Level Setup Register 0
#define	ITCLV0				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x00))).reg
#define	ITCLV0_ILV0			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x00))).bit.ILV_L				///< Supply voltage detector interrupt.
#define	ITCLV0_ILV1			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x00))).bit.ILV_H				///< Port interrupt.

// ITC Interrupt Level Setup Register 1
#define	ITCLV1				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x02))).reg
#define	ITCLV1_ILV2			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x02))).bit.ILV_L				///< Power generator interrupt.
#define	ITCLV1_ILV3			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x02))).bit.ILV_H				///< Clock generator interrupt.

// ITC Interrupt Level Setup Register 2
#define	ITCLV2				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x04))).reg
#define	ITCLV2_ILV4			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x04))).bit.ILV_L				///< Real-time clock interrupt.
#define	ITCLV2_ILV5			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x04))).bit.ILV_H				///< 16-bit timer Ch.0 interrupt.

// ITC Interrupt Level Setup Register 3
#define	ITCLV3				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x06))).reg
#define	ITCLV3_ILV6			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x06))).bit.ILV_L				///< UART Ch.0 interrupt.
#define	ITCLV3_ILV7			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x06))).bit.ILV_H				///< 16-bit timer Ch.1 interrupt.

// ITC Interrupt Level Setup Register 4
#define	ITCLV4				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x08))).reg
#define	ITCLV4_ILV8			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x08))).bit.ILV_L				///< Synchronous serial interface Ch.0 interrupt.
#define	ITCLV4_ILV9			(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x08))).bit.ILV_H				///< I2C interrupt.

// ITC Interrupt Level Setup Register 5
#define	ITCLV5				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0A))).reg
#define	ITCLV5_ILV10		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0A))).bit.ILV_L				///< 16-bit PWM timer Ch.0 interrupt.
#define	ITCLV5_ILV11		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0A))).bit.ILV_H				///< 16-bit PWM timer Ch.1 interrupt.

// ITC Interrupt Level Setup Register 6
#define	ITCLV6				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0C))).reg
#define	ITCLV6_ILV12		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0C))).bit.ILV_L				///< UART Ch.1 interrupt.
#define	ITCLV6_ILV13		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0C))).bit.ILV_H				///< 16-bit timer Ch.2 interrupt.

// ITC Interrupt Level Setup Register 7
#define	ITCLV7				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0E))).reg
#define	ITCLV7_ILV14		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0E))).bit.ILV_L				///< Sound generator interrupt.
#define	ITCLV7_ILV15		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x0E))).bit.ILV_H				///< LCD driver interrupt.

// ITC Interrupt Level Setup Register 8
#define	ITCLV8				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x10))).reg
#define	ITCLV8_ILV16		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x10))).bit.ILV_L				///< R/F converter Ch.0 interrupt.
#define	ITCLV8_ILV17		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x10))).bit.ILV_H				///< R/F converter Ch.1 interrupt.

// ITC Interrupt Level Setup Register 9
#define	ITCLV9				(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x12))).reg
#define	ITCLV9_ILV18		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x12))).bit.ILV_L				///< R/F converter Ch.2 interrupt.
#define	ITCLV9_ILV19		(*((ITCLVX_REG *)(ITC_REG_BASE_ADDR + 0x12))).bit.ILV_H				///< R/F converter Ch.3 interrupt.

// Interrupt Level Registers.
#define	ILVSVD				( ITCLV0_ILV0 )			///< Supply voltage detector interrupt.
#define	ILVPPORT			( ITCLV0_ILV1 )			///< Port interrupt.
#define	ILVPWG2				( ITCLV1_ILV2 )			///< Power generator interrupt.
#define	ILVCLG				( ITCLV1_ILV3 )			///< Clock generator interrupt.
#define	ILVRTCA_0			( ITCLV2_ILV4 )			///< Real-time clock interrupt.
#define	ILVT16_0			( ITCLV2_ILV5 )			///< 16-bit timer Ch.0 interrupt.
#define	ILVUART_0			( ITCLV3_ILV6 )			///< UART Ch.0 interrupt.
#define	ILVT16_1			( ITCLV3_ILV7 )			///< 16-bit timer Ch.1 interrupt.
#define	ILVSPIA_0			( ITCLV4_ILV8 )			///< Synchronous serial interface interrupt.
#define	ILVI2C_0			( ITCLV4_ILV9 )			///< I2C interrupt.
#define	ILVT16B_0			( ITCLV5_ILV10 )		///< 16-bit PWM timer Ch.0 interrupt.
#define	ILVT16B_1			( ITCLV5_ILV11 )		///< 16-bit PWM timer Ch.1 interrupt.
#define	ILVUART_1			( ITCLV6_ILV12 )		///< UART Ch.1 interrupt.
#define	ILVT16_2			( ITCLV6_ILV13 )		///< 16-bit timer Ch.2 interrupt.
#define	ILVSNDA_0			( ITCLV7_ILV14 )		///< Sound generator interrupt.
#define	ILVLCD8B			( ITCLV7_ILV15 )		///< LCD driver interrupt.
#define	ILVRFC_0			( ITCLV8_ILV16 )		///< R/F converter Ch.0 interrupt.
#define	ILVRFC_1			( ITCLV8_ILV17 )		///< R/F converter Ch.1 interrupt.
#define	ILVRFC_2			( ITCLV9_ILV18 )		///< R/F converter Ch.2 interrupt.
#define	ILVRFC_3			( ITCLV9_ILV19 )		///< R/F converter Ch.3 interrupt.


/*******************/
/* ----- WDT ----- */
/*******************/

// WDT Clock Control Register
#define	WDTCLK				(*((WDTCLK_REG *)(WDT_REG_BASE_ADDR + 0x00))).reg
#define	WDTCLK_CLKSRC		(*((WDTCLK_REG *)(WDT_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of WDT.
#define	WDTCLK_CLKDIV		(*((WDTCLK_REG *)(WDT_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the WDT operating clock (counter clock).
#define	WDTCLK_DBRUN		(*((WDTCLK_REG *)(WDT_REG_BASE_ADDR + 0x00))).bit.DBRUN				///< This bit sets whether the WDT operating clock is supplied in DEBUG mode or not.

// WDT Control Register
#define	WDTCTL				(*((WDTCTL_REG *)(WDT_REG_BASE_ADDR + 0x02))).reg
#define	WDTCTL_WDTRUN		(*((WDTCTL_REG *)(WDT_REG_BASE_ADDR + 0x02))).bit.WDTRUN			///< These bits control WDT to run and stop.
#define	WDTCTL_WDTCNTRST	(*((WDTCTL_REG *)(WDT_REG_BASE_ADDR + 0x02))).bit.WDTCNTRST			///< This bit resets WDT.
#define	WDTCTL_STATNMI		(*((WDTCTL_REG *)(WDT_REG_BASE_ADDR + 0x02))).bit.STATNMI			///< This bit indicates that a counter overflow and NMI have occurred.
#define	WDTCTL_NMIXRST		(*((WDTCTL_REG *)(WDT_REG_BASE_ADDR + 0x02))).bit.NMIXRST			///< This bit sets the WDT operating mode.


/*******************/
/* ----- RTC ----- */
/*******************/

// RTC Control Register
#define	RTCCTL				(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).reg
#define	RTCCTL_RTCRUN		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCRUN			///< This bit starts/stops the real-time clock counter.
#define	RTCCTL_RTCRST		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCRST			///< This bit resets the 1 Hz counter, the RTCCTL.RTCADJ bit, and the RTCCTL.RTCHLD bit.
#define	RTCCTL_RTCADJ		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCADJ			///< This bit executes the 30-second correction time adjustment function.
#define	RTCCTL_RTC24H		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTC24H			///< This bit sets the hour counter to 24H mode or 12H mode.
#define	RTCCTL_RTCHLD		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCHLD			///< This bit halts the count-up operation of the real-time clock counter.
#define	RTCCTL_RTCBSY		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCBSY			///< This bit indicates whether the counter is performing count-up operation or not.
#define	RTCCTL_RTCTRM		(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCTRM			///< Write the correction value for adjusting the 1 Hz frequency to these bits to execute theoretical regulation.
#define	RTCCTL_RTCTRMBSY	(*((RTCCTL_REG *)(RTC_REG_BASE_ADDR + 0x00))).bit.RTCTRMBSY			///< This bit indicates whether the theoretical regulation is currently executed or not.

// RTC Second Alarm Register
#define	RTCALM1				(*((RTCALM1_REG *)(RTC_REG_BASE_ADDR + 0x02))).reg
#define	RTCALM1_RTCSLA		(*((RTCALM1_REG *)(RTC_REG_BASE_ADDR + 0x02))).bit.RTCSLA			///< There bits set the 1-second digit of the alarm time.
#define	RTCALM1_RTCSHA		(*((RTCALM1_REG *)(RTC_REG_BASE_ADDR + 0x02))).bit.RTCSHA			///< There bits set the 10-second digit of the alarm time.

// RTC Hour/Minute Alarm Register
#define	RTCALM2				(*((RTCALM2_REG *)(RTC_REG_BASE_ADDR + 0x04))).reg
#define	RTCALM2_RTCMILA		(*((RTCALM2_REG *)(RTC_REG_BASE_ADDR + 0x04))).bit.RTCMILA			///< There bits set the 1-minute digit of the alarm time.
#define	RTCALM2_RTCMIHA		(*((RTCALM2_REG *)(RTC_REG_BASE_ADDR + 0x04))).bit.RTCMIHA			///< There bits set the 10-minute digit of the alarm time
#define	RTCALM2_RTCHLA		(*((RTCALM2_REG *)(RTC_REG_BASE_ADDR + 0x04))).bit.RTCHLA			///< There bits set the 1-hour digit of the alarm time.
#define	RTCALM2_RTCHHA		(*((RTCALM2_REG *)(RTC_REG_BASE_ADDR + 0x04))).bit.RTCHHA			///< There bits set the 10-hour digit of the alarm time.
#define	RTCALM2_RTCAPA		(*((RTCALM2_REG *)(RTC_REG_BASE_ADDR + 0x04))).bit.RTCAPA			///< This bit set A.M. or P.M. of the alarm time in 12H mode (RTCCTL.RTC24H bit = 0).

// RTC Stopwatch Control Register
#define	RTCSWCTL			(*((RTCSWCTL_REG *)(RTC_REG_BASE_ADDR + 0x06))).reg
#define	RTCSWCTL_SWRUN		(*((RTCSWCTL_REG *)(RTC_REG_BASE_ADDR + 0x06))).bit.SWRUN			///< This bit starts/stops the stopwatch counter.
#define	RTCSWCTL_SWRST		(*((RTCSWCTL_REG *)(RTC_REG_BASE_ADDR + 0x06))).bit.SWRST			///< This bit resets the stopwatch counter to 0x00.
#define	RTCSWCTL_BCD100		(*((RTCSWCTL_REG *)(RTC_REG_BASE_ADDR + 0x06))).bit.BCD100			///< The 1/100-second digits of the stopwatch counter can be read as a BCD code.
#define	RTCSWCTL_BCD10		(*((RTCSWCTL_REG *)(RTC_REG_BASE_ADDR + 0x06))).bit.BCD10			///< The 1/10-second digits of the stopwatch counter can be read as a BCD code.

// RTC Second/1[Hz] Register
#define	RTCSEC				(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).reg
#define	RTCSEC_RTC128HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC128HZ			///< 1 Hz counter data can be read from these bits(128Hz).
#define	RTCSEC_RTC64HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC64HZ			///< 1 Hz counter data can be read from these bits(64Hz).
#define	RTCSEC_RTC32HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC32HZ			///< 1 Hz counter data can be read from these bits(32Hz).
#define	RTCSEC_RTC16HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC16HZ			///< 1 Hz counter data can be read from these bits(16Hz).
#define	RTCSEC_RTC8HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC8HZ			///< 1 Hz counter data can be read from these bits(8Hz).
#define	RTCSEC_RTC4HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC4HZ			///< 1 Hz counter data can be read from these bits(4Hz).
#define	RTCSEC_RTC2HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC2HZ			///< 1 Hz counter data can be read from these bits(2Hz).
#define	RTCSEC_RTC1HZ		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTC1HZ			///< 1 Hz counter data can be read from these bits(1Hz).
#define	RTCSEC_RTCSL		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTCSL				///< There bits are used to set and read the 1-second digit of the second counter.
#define	RTCSEC_RTCSH		(*((RTCSEC_REG *)(RTC_REG_BASE_ADDR + 0x08))).bit.RTCSH				///< There bits are used to set and read the 10-second digit of the second counter.

// RTC Hour/Minute Register
#define	RTCHUR				(*((RTCHUR_REG *)(RTC_REG_BASE_ADDR + 0x0A))).reg
#define	RTCHUR_RTCMIL		(*((RTCHUR_REG *)(RTC_REG_BASE_ADDR + 0x0A))).bit.RTCMIL			///< There bits are used to set and read the 1-minute digit of the minute counter.
#define	RTCHUR_RTCMIH		(*((RTCHUR_REG *)(RTC_REG_BASE_ADDR + 0x0A))).bit.RTCMIH			///< There bits are used to set and read the 10-minute digit of the minute counter.
#define	RTCHUR_RTCHL		(*((RTCHUR_REG *)(RTC_REG_BASE_ADDR + 0x0A))).bit.RTCHL				///< There bits are used to set and read the 1-hour digit of the hour counter.
#define	RTCHUR_RTCHH		(*((RTCHUR_REG *)(RTC_REG_BASE_ADDR + 0x0A))).bit.RTCHH				///< There bits are used to set and read the 10-hour digit of the hour counter.
#define	RTCHUR_RTCAP		(*((RTCHUR_REG *)(RTC_REG_BASE_ADDR + 0x0A))).bit.RTCAP				///< This bit is used to set and read A.M. or P.M. data in 12H mode (RTCCTL.RTC24H bit = 0).

// RTC Month/Day Register
#define	RTCMON				(*((RTCMON_REG *)(RTC_REG_BASE_ADDR + 0x0C))).reg
#define	RTCMON_RTCDL		(*((RTCMON_REG *)(RTC_REG_BASE_ADDR + 0x0C))).bit.RTCDL				///< There bits are used to set and read the 1-day digit of the day counter.
#define	RTCMON_RTCDH		(*((RTCMON_REG *)(RTC_REG_BASE_ADDR + 0x0C))).bit.RTCDH				///< There bits are used to set and read the 10-day digit of the day counter.
#define	RTCMON_RTCMOL		(*((RTCMON_REG *)(RTC_REG_BASE_ADDR + 0x0C))).bit.RTCMOL			///< There bits are used to set and read the 1-month digit of the month counter.
#define	RTCMON_RTCMOH		(*((RTCMON_REG *)(RTC_REG_BASE_ADDR + 0x0C))).bit.RTCMOH			///< There bits are used to set and read the 10-month digit of the month counter.

// RTC Year/Week Register
#define	RTCYAR				(*((RTCYAR_REG *)(RTC_REG_BASE_ADDR + 0x0E))).reg
#define	RTCYAR_RTCYL		(*((RTCYAR_REG *)(RTC_REG_BASE_ADDR + 0x0E))).bit.RTCYL				///< There bits are used to set and read the 1-year digit of the year counter.
#define	RTCYAR_RTCYH		(*((RTCYAR_REG *)(RTC_REG_BASE_ADDR + 0x0E))).bit.RTCYH				///< There bits are used to set and read the 10-year digit of the year counter.
#define	RTCYAR_RTCWK		(*((RTCYAR_REG *)(RTC_REG_BASE_ADDR + 0x0E))).bit.RTCWK				///< These bits are used to set and read day of the week.

// RTC Interrupt Flag Register
#define	RTCINTF				(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).reg
#define	RTCINTF_1_32SECIF	(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1_32SECIF		///< This bit indicate 1/32-second interrupt cause occurrence status.
#define	RTCINTF_1_8SECIF	(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1_8SECIF		///< This bit indicate 1/8-second interrupt cause occurrence status.
#define	RTCINTF_1_4SECIF	(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1_4SECIF		///< This bit indicate 1/4-second interrupt cause occurrence status.
#define	RTCINTF_1_2SECIF	(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1_2SECIF		///< This bit indicate 1/2-second interrupt cause occurrence status.
#define	RTCINTF_1SECIF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1SECIF			///< This bit indicate 1-second interrupt cause occurrence status.
#define	RTCINTF_1MINIF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1MINIF			///< This bit indicate 1-minute interrupt cause occurrence status.
#define	RTCINTF_1HURIF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1HURIF			///< This bit indicate 1-day interrupt cause occurrence status.
#define	RTCINTF_1DAYIF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit._1DAYIF			///< This bit indicate 1-day interrupt cause occurrence status.
#define	RTCINTF_ALARMIF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit.ALARMIF			///< This bit indicate Alarm interrupt cause occurrence status.
#define	RTCINTF_SW100IF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit.SW100IF			///< This bit indicate Stopwatch 100 Hz interrupt cause occurrence status.
#define	RTCINTF_SW10IF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit.SW10IF			///< This bit indicate Stopwatch 10 Hz interrupt cause occurrence status.
#define	RTCINTF_SW1IF		(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit.SW1IF			///< This bit indicate Stopwatch 1 Hz interrupt cause occurrence status.
#define	RTCINTF_RTCTRMIF	(*((RTCINTF_REG *)(RTC_REG_BASE_ADDR + 0x10))).bit.RTCTRMIF			///< This bit indicate Theoretical regulation completion interrupt cause occurrence status.

// RTC Interrupt Enable Register
#define	RTCINTE				(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).reg
#define	RTCINTE_1_32SECIE	(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1_32SECIE		///< This bits enable 1/32-second interrupt.
#define	RTCINTE_1_8SECIE	(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1_8SECIE		///< This bits enable 1/8-second interrupt.
#define	RTCINTE_1_4SECIE	(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1_4SECIE		///< This bits enable 1/4-second interrupt.
#define	RTCINTE_1_2SECIE	(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1_2SECIE		///< This bits enable 1/2-second interrupt.
#define	RTCINTE_1SECIE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1SECIE			///< This bits enable 1-second interrupt.
#define	RTCINTE_1MINIE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1MINIE			///< This bits enable 1-minute interrupt.
#define	RTCINTE_1HURIE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1HURIE			///< This bits enable 1-hour interrupt.
#define	RTCINTE_1DAYIE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit._1DAYIE			///< This bits enable 1-day interrupt.
#define	RTCINTE_ALARMIE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit.ALARMIE			///< This bits enable Alarm interrupt.
#define	RTCINTE_SW100IE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit.SW100IE			///< This bit enable Stopwatch 100 Hz interrupt.
#define	RTCINTE_SW10IE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit.SW10IE			///< This bit enable Stopwatch 10 Hz interrupt.
#define	RTCINTE_SW1IE		(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit.SW1IE			///< This bit enable Stopwatch 1 Hz interrupt.
#define	RTCINTE_RTCTRMIE	(*((RTCINTE_REG *)(RTC_REG_BASE_ADDR + 0x12))).bit.RTCTRMIE			///< This bit enable Theoretical regulation completion interrupt.


/*******************/
/* ----- SVD ----- */
/*******************/

// SVD Clock Control Register
#define	SVDCLK				(*((SVDCLK_REG *)(SVD_REG_BASE_ADDR + 0x00))).reg
#define	SVDCLK_CLKSRC		(*((SVDCLK_REG *)(SVD_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of SVD.
#define	SVDCLK_CLKDIV		(*((SVDCLK_REG *)(SVD_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the SVD operating clock.
#define	SVDCLK_DBRUN		(*((SVDCLK_REG *)(SVD_REG_BASE_ADDR + 0x00))).bit.DBRUN				///< This bit sets whether the SVD operating clock is supplied in DEBUG mode or not.

// SVD Control Register
#define	SVDCTL				(*((SVDCTL_REG *)(SVD_REG_BASE_ADDR + 0x02))).reg
#define	SVDCTL_MODEN		(*((SVDCTL_REG *)(SVD_REG_BASE_ADDR + 0x02))).bit.MODEN				///< This bit enables/disables for the SVD circuit to operate.
#define	SVDCTL_SVDMD		(*((SVDCTL_REG *)(SVD_REG_BASE_ADDR + 0x02))).bit.SVDMD				///< These bits select intermittent operation mode and its detection cycle.
#define	SVDCTL_SVDRE		(*((SVDCTL_REG *)(SVD_REG_BASE_ADDR + 0x02))).bit.SVDRE				///< These bits enable/disable the reset issuance function when a low power supply voltage is detected.
#define	SVDCTL_SVDC			(*((SVDCTL_REG *)(SVD_REG_BASE_ADDR + 0x02))).bit.SVDC				///< These bits select a comparison voltage for detecting low voltage from among 20 levels.
#define	SVDCTL_SVDSC		(*((SVDCTL_REG *)(SVD_REG_BASE_ADDR + 0x02))).bit.SVDSC				///< These bits set the condition to generate an interrupt/reset in intermittent operation mode.

// SVD Status and Interrupt Flag Register
#define	SVDINTF				(*((SVDINTF_REG *)(SVD_REG_BASE_ADDR + 0x04))).reg
#define	SVDINTF_SVDIF		(*((SVDINTF_REG *)(SVD_REG_BASE_ADDR + 0x04))).bit.SVDIF			///< This bit indicates the low power supply voltage detection interrupt cause occurrence status.
#define	SVDINTF_SVDDT		(*((SVDINTF_REG *)(SVD_REG_BASE_ADDR + 0x04))).bit.SVDDT			///< The power supply voltage detection results can be read out from this bit.

// SVD Interrupt Enable Register
#define	SVDINTE				(*((SVDINTE_REG *)(SVD_REG_BASE_ADDR + 0x06))).reg
#define	SVDINTE_SVDIE		(*((SVDINTE_REG *)(SVD_REG_BASE_ADDR + 0x06))).bit.SVDIE			///< This bit enables low power supply voltage detection interrupts.


/*******************/
/* ----- T16 ----- */
/*******************/

// T16 Ch.0 Clock Control Register
#define	T16_0CLK			(*((T16_NCLK_REG *)(T16_0_REG_BASE_ADDR + 0x00))).reg
#define	T16_0CLK_CLKSRC		(*((T16_NCLK_REG *)(T16_0_REG_BASE_ADDR + 0x00))).bit.CLKSRC		///< These bits select the clock source of T16 Ch.0.
#define	T16_0CLK_CLKDIV		(*((T16_NCLK_REG *)(T16_0_REG_BASE_ADDR + 0x00))).bit.CLKDIV		///< These bits select the division ratio of the T16 Ch.0 operating clock (counter clock).
#define	T16_0CLK_DBRUN		(*((T16_NCLK_REG *)(T16_0_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the T16 Ch.0 operating clock is supplied in DEBUG mode or not.

// T16 Ch.0 Mode Register
#define	T16_0MOD			(*((T16_NMOD_REG *)(T16_0_REG_BASE_ADDR + 0x02))).reg
#define	T16_0MOD_TRMD		(*((T16_NMOD_REG *)(T16_0_REG_BASE_ADDR + 0x02))).bit.TRMD			///< This bit selects the T16(Ch.0) operation mode.

// T16 Ch.0 Control Register
#define	T16_0CTL			(*((T16_NCTL_REG *)(T16_0_REG_BASE_ADDR + 0x04))).reg
#define	T16_0CTL_MODEN		(*((T16_NCTL_REG *)(T16_0_REG_BASE_ADDR + 0x04))).bit.MODEN			///< This bit enables the T16 operations(Ch.0).
#define	T16_0CTL_PRESET		(*((T16_NCTL_REG *)(T16_0_REG_BASE_ADDR + 0x04))).bit.PRESET		///< This bit presets the reload data stored in the T16_0TR register to the counter.
#define	T16_0CTL_PRUN		(*((T16_NCTL_REG *)(T16_0_REG_BASE_ADDR + 0x04))).bit.PRUN			///< This bit starts/stops the timer(Ch.0).

// T16 Ch.0 Reload Data Register
#define	T16_0TR				(*((T16_NTR_REG *)(T16_0_REG_BASE_ADDR + 0x06))).reg

// T16 Ch.0 Counter Data Register
#define	T16_0TC				(*((T16_NTC_REG *)(T16_0_REG_BASE_ADDR + 0x08))).reg

// T16 Ch.0 Interrupt Flag Register
#define	T16_0INTF			(*((T16_NINTF_REG *)(T16_0_REG_BASE_ADDR + 0x0A))).reg
#define	T16_0INTF_UFIF		(*((T16_NINTF_REG *)(T16_0_REG_BASE_ADDR + 0x0A))).bit.UFIF			///< This bit indicates the T16 Ch.0 underflow interrupt cause occurrence status.

// T16 Ch.0 Interrupt Enable Register
#define	T16_0INTE			(*((T16_NINTE_REG *)(T16_0_REG_BASE_ADDR + 0x0C))).reg
#define	T16_0INTE_UFIE		(*((T16_NINTE_REG *)(T16_0_REG_BASE_ADDR + 0x0C))).bit.UFIE			///< This bit enables T16 Ch.0 underflow interrupts.

// T16 Ch.1 Clock Control Register
#define	T16_1CLK			(*((T16_NCLK_REG *)(T16_1_REG_BASE_ADDR + 0x00))).reg
#define	T16_1CLK_CLKSRC		(*((T16_NCLK_REG *)(T16_1_REG_BASE_ADDR + 0x00))).bit.CLKSRC		///< These bits select the clock source of T16 Ch.1.
#define	T16_1CLK_CLKDIV		(*((T16_NCLK_REG *)(T16_1_REG_BASE_ADDR + 0x00))).bit.CLKDIV		///< These bits select the division ratio of the T16 Ch.1 operating clock (counter clock).
#define	T16_1CLK_DBRUN		(*((T16_NCLK_REG *)(T16_1_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the T16 Ch.1 operating clock is supplied in DEBUG mode or not.

// T16 Ch.1 Mode Register
#define	T16_1MOD			(*((T16_NMOD_REG *)(T16_1_REG_BASE_ADDR + 0x02))).reg
#define	T16_1MOD_TRMD		(*((T16_NMOD_REG *)(T16_1_REG_BASE_ADDR + 0x02))).bit.TRMD			///< This bit selects the T16(Ch.1) operation mode.

// T16 Ch.1 Control Register
#define	T16_1CTL			(*((T16_NCTL_REG *)(T16_1_REG_BASE_ADDR + 0x04))).reg
#define	T16_1CTL_MODEN		(*((T16_NCTL_REG *)(T16_1_REG_BASE_ADDR + 0x04))).bit.MODEN			///< This bit enables the T16 operations(Ch.1).
#define	T16_1CTL_PRESET		(*((T16_NCTL_REG *)(T16_1_REG_BASE_ADDR + 0x04))).bit.PRESET		///< This bit presets the reload data stored in the T16_1TR register to the counter.
#define	T16_1CTL_PRUN		(*((T16_NCTL_REG *)(T16_1_REG_BASE_ADDR + 0x04))).bit.PRUN			///< This bit starts/stops the timer(Ch.1).

// T16 Ch.1 Reload Data Register
#define	T16_1TR				(*((T16_NTR_REG *)(T16_1_REG_BASE_ADDR + 0x06))).reg

// T16 Ch.1 Counter Data Register
#define	T16_1TC				(*((T16_NTC_REG *)(T16_1_REG_BASE_ADDR + 0x08))).reg

// T16 Ch.1 Interrupt Flag Register
#define	T16_1INTF			(*((T16_NINTF_REG *)(T16_1_REG_BASE_ADDR + 0x0A))).reg
#define	T16_1INTF_UFIF		(*((T16_NINTF_REG *)(T16_1_REG_BASE_ADDR + 0x0A))).bit.UFIF			///< This bit indicates the T16 Ch.1 underflow interrupt cause occurrence status.

// T16 Ch.1 Interrupt Enable Register
#define	T16_1INTE			(*((T16_NINTE_REG *)(T16_1_REG_BASE_ADDR + 0x0C))).reg
#define	T16_1INTE_UFIE		(*((T16_NINTE_REG *)(T16_1_REG_BASE_ADDR + 0x0C))).bit.UFIE			///< This bit enables T16 Ch.1 underflow interrupts.

// T16 Ch.2 Clock Control Register
#define	T16_2CLK			(*((T16_NCLK_REG *)(T16_2_REG_BASE_ADDR + 0x00))).reg
#define	T16_2CLK_CLKSRC		(*((T16_NCLK_REG *)(T16_2_REG_BASE_ADDR + 0x00))).bit.CLKSRC		///< These bits select the clock source of T16 Ch.2.
#define	T16_2CLK_CLKDIV		(*((T16_NCLK_REG *)(T16_2_REG_BASE_ADDR + 0x00))).bit.CLKDIV		///< These bits select the division ratio of the T16 Ch.2 operating clock (counter clock).
#define	T16_2CLK_DBRUN		(*((T16_NCLK_REG *)(T16_2_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the T16 Ch.2 operating clock is supplied in DEBUG mode or not.

// T16 Ch.2 Mode Register
#define	T16_2MOD			(*((T16_NMOD_REG *)(T16_2_REG_BASE_ADDR + 0x02))).reg
#define	T16_2MOD_TRMD		(*((T16_NMOD_REG *)(T16_2_REG_BASE_ADDR + 0x02))).bit.TRMD			///< This bit selects the T16(Ch.2) operation mode.

// T16 Ch.2 Control Register
#define	T16_2CTL			(*((T16_NCTL_REG *)(T16_2_REG_BASE_ADDR + 0x04))).reg
#define	T16_2CTL_MODEN		(*((T16_NCTL_REG *)(T16_2_REG_BASE_ADDR + 0x04))).bit.MODEN			///< This bit enables the T16 operations(Ch.2).
#define	T16_2CTL_PRESET		(*((T16_NCTL_REG *)(T16_2_REG_BASE_ADDR + 0x04))).bit.PRESET		///< This bit presets the reload data stored in the T16_1TR register to the counter.
#define	T16_2CTL_PRUN		(*((T16_NCTL_REG *)(T16_2_REG_BASE_ADDR + 0x04))).bit.PRUN			///< This bit starts/stops the timer(Ch.2).

// T16 Ch.2 Reload Data Register
#define	T16_2TR				(*((T16_NTR_REG *)(T16_2_REG_BASE_ADDR + 0x06))).reg

// T16 Ch.2 Counter Data Register
#define	T16_2TC				(*((T16_NTC_REG *)(T16_2_REG_BASE_ADDR + 0x08))).reg

// T16 Ch.2 Interrupt Flag Register
#define	T16_2INTF			(*((T16_NINTF_REG *)(T16_2_REG_BASE_ADDR + 0x0A))).reg
#define	T16_2INTF_UFIF		(*((T16_NINTF_REG *)(T16_2_REG_BASE_ADDR + 0x0A))).bit.UFIF			///< This bit indicates the T16 Ch.2 underflow interrupt cause occurrence status.

// T16 Ch.2 Interrupt Enable Register
#define	T16_2INTE			(*((T16_NINTE_REG *)(T16_2_REG_BASE_ADDR + 0x0C))).reg
#define	T16_2INTE_UFIE		(*((T16_NINTE_REG *)(T16_2_REG_BASE_ADDR + 0x0C))).bit.UFIE			///< This bit enables T16 Ch.2 underflow interrupts.


/**********************/
/* ----- FLASHC ----- */
/**********************/

// FLASHC Flash Read Cycle Register
#define	FLASHCWAIT			(*((FLASHCWAIT_REG *)(FLASHC_REG_BASE_ADDR + 0x00))).reg
#define	FLASHCWAIT_RDWAIT	(*((FLASHCWAIT_REG *)(FLASHC_REG_BASE_ADDR + 0x00))).bit.RDWAIT		///< These bits set the number of bus access cycles for reading from the Flash memory.
#define	FLASHCWAIT_XBUSY	(*((FLASHCWAIT_REG *)(FLASHC_REG_BASE_ADDR + 0x00))).bit.XBUSY		///< This bit indicates whether the Flash memory can be accessed or not.


/*********************/
/* ----- PPORT ----- */
/*********************/

// P0 Port Data Register
#define	P0DAT				(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).reg
#define	P0DAT_P00IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px0IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P01IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px1IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P02IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px2IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P03IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px3IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P04IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px4IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P05IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px5IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P06IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px6IN			///< The GPIO port pin status can be read out from this bit.
#define	P0DAT_P00OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px0OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P0DAT_P01OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px1OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P0DAT_P02OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px2OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P0DAT_P03OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px3OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P0DAT_P04OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px4OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P0DAT_P05OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px5OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P0DAT_P06OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x00))).bit.Px6OUT			///< This bit are used to set data to be output from the GPIO port pin.

// P0 Port Enable Register
#define	P0IOEN				(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).reg
#define	P0IOEN_P00OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px0OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P01OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px1OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P02OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px2OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P03OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px3OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P04OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px4OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P05OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px5OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P06OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px6OEN			///< This bit enable/disable the GPIO port output.
#define	P0IOEN_P00IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px0IEN			///< This bit enable/disable the GPIO port input.
#define	P0IOEN_P01IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px1IEN			///< This bit enable/disable the GPIO port input.
#define	P0IOEN_P02IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px2IEN			///< This bit enable/disable the GPIO port input.
#define	P0IOEN_P03IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px3IEN			///< This bit enable/disable the GPIO port input.
#define	P0IOEN_P04IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px4IEN			///< This bit enable/disable the GPIO port input.
#define	P0IOEN_P05IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px5IEN			///< This bit enable/disable the GPIO port input.
#define	P0IOEN_P06IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x02))).bit.Px6IEN			///< This bit enable/disable the GPIO port input.

// P0 Port Pull-up/down Control Register
#define	P0RCTL				(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).reg
#define	P0RCTL_P00REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px0REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P01REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px1REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P02REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px2REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P03REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px3REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P04REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px4REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P05REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px5REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P06REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px6REN			///< This bit enable/disable the port pull-up/down control.
#define	P0RCTL_P00PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px0PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P0RCTL_P01PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px1PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P0RCTL_P02PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px2PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P0RCTL_P03PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px3PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P0RCTL_P04PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px4PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P0RCTL_P05PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px5PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P0RCTL_P06PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x04))).bit.Px6PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.

// P0 Port Interrupt Flag Register
#define	P0INTF				(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).reg
#define	P0INTF_P00IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px0IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P0INTF_P01IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px1IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P0INTF_P02IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px2IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P0INTF_P03IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px3IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P0INTF_P04IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px4IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P0INTF_P05IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px5IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P0INTF_P06IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x06))).bit.Px6IF			///< This bit indicate the port input interrupt cause occurrence status.

// P0 Port Interrupt Control Register
#define	P0INTCTL			(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).reg
#define	P0INTCTL_P00IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px0IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P01IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px1IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P02IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px2IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P03IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px3IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P04IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px4IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P05IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px5IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P06IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px6IE			///< This bit enable port input interrupt.
#define	P0INTCTL_P00EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px0EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P0INTCTL_P01EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px1EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P0INTCTL_P02EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px2EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P0INTCTL_P03EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px3EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P0INTCTL_P04EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px4EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P0INTCTL_P05EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px5EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P0INTCTL_P06EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x08))).bit.Px6EDGE		///< This bit select the input signal edge to generate a port input interrupt.

// P0 Port Chattering Filter Enable Register
#define	P0CHATEN			(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).reg
#define	P0CHATEN_P00CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px0CHATEN		///< This bit enable/disable the chattering filter function.
#define	P0CHATEN_P01CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px1CHATEN		///< This bit enable/disable the chattering filter function.
#define	P0CHATEN_P02CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px2CHATEN		///< This bit enable/disable the chattering filter function.
#define	P0CHATEN_P03CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px3CHATEN		///< This bit enable/disable the chattering filter function.
#define	P0CHATEN_P04CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px4CHATEN		///< This bit enable/disable the chattering filter function.
#define	P0CHATEN_P05CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px5CHATEN		///< This bit enable/disable the chattering filter function.
#define	P0CHATEN_P06CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x0A))).bit.Px6CHATEN		///< This bit enable/disable the chattering filter function.

// P0 Port Mode Select Register
#define	P0MODSEL			(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).reg
#define	P0MODSEL_P00SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px0SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P0MODSEL_P01SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px1SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P0MODSEL_P02SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px2SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P0MODSEL_P03SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px3SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P0MODSEL_P04SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px4SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P0MODSEL_P05SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px5SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P0MODSEL_P06SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0C))).bit.Px6SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.

// P0 Port Function Select Register
#define	P0FNCSEL			(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).reg
#define	P0FNCSEL_P00MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px0MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P0FNCSEL_P01MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px1MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P0FNCSEL_P02MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px2MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P0FNCSEL_P03MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px3MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P0FNCSEL_P04MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px4MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P0FNCSEL_P05MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px5MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P0FNCSEL_P06MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x0E))).bit.Px6MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.

// P1 Port Data Register
#define	P1DAT				(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).reg
#define	P1DAT_P10IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px0IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P11IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px1IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P12IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px2IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P13IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px3IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P14IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px4IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P15IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px5IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P16IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px6IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P17IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px7IN			///< The GPIO port pin status can be read out from this bit.
#define	P1DAT_P10OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px0OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P11OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px1OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P12OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px2OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P13OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px3OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P14OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px4OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P15OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px5OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P16OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px6OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P1DAT_P17OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x10))).bit.Px7OUT			///< This bit are used to set data to be output from the GPIO port pin.

// P1 Port Enable Register
#define	P1IOEN				(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).reg
#define	P1IOEN_P10OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px0OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P11OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px1OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P12OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px2OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P13OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px3OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P14OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px4OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P15OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px5OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P16OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px6OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P17OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px7OEN			///< This bit enable/disable the GPIO port output.
#define	P1IOEN_P10IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px0IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P11IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px1IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P12IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px2IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P13IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px3IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P14IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px4IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P15IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px5IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P16IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px6IEN			///< This bit enable/disable the GPIO port input.
#define	P1IOEN_P17IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x12))).bit.Px7IEN			///< This bit enable/disable the GPIO port input.

// P1 Port Pull-up/down Control Register
#define	P1RCTL				(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).reg
#define	P1RCTL_P10REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px0REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P11REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px1REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P12REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px2REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P13REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px3REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P14REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px4REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P15REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px5REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P16REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px6REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P17REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px7REN			///< This bit enable/disable the port pull-up/down control.
#define	P1RCTL_P10PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px0PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P11PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px1PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P12PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px2PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P13PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px3PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P14PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px4PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P15PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px5PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P16PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px6PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P1RCTL_P17PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x14))).bit.Px7PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.

// P1 Port Interrupt Flag Register
#define	P1INTF				(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).reg
#define	P1INTF_P10IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px0IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P11IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px1IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P12IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px2IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P13IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px3IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P14IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px4IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P15IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px5IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P16IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px6IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P1INTF_P17IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x16))).bit.Px7IF			///< This bit indicate the port input interrupt cause occurrence status.

// P1 Port Interrupt Control Register
#define	P1INTCTL			(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).reg
#define	P1INTCTL_P10IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px0IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P11IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px1IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P12IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px2IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P13IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px3IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P14IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px4IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P15IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px5IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P16IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px6IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P17IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px7IE			///< This bit enable port input interrupt.
#define	P1INTCTL_P10EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px0EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P11EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px1EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P12EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px2EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P13EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px3EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P14EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px4EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P15EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px5EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P16EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px6EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P1INTCTL_P17EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x18))).bit.Px7EDGE		///< This bit select the input signal edge to generate a port input interrupt.

// P1 Port Chattering Filter Enable Register
#define	P1CHATEN			(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).reg
#define	P1CHATEN_P10CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px0CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P11CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px1CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P12CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px2CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P13CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px3CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P14CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px4CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P15CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px5CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P16CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px6CHATEN		///< This bit enable/disable the chattering filter function.
#define	P1CHATEN_P17CHATEN	(*((PXCHATEN_REG *)(PPORT_REG_BASE_ADDR + 0x1A))).bit.Px7CHATEN		///< This bit enable/disable the chattering filter function.

// P1 Port Mode Select Register
#define	P1MODSEL			(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).reg
#define	P1MODSEL_P10SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px0SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P11SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px1SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P12SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px2SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P13SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px3SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P14SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px4SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P15SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px5SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P16SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px6SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P1MODSEL_P17SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1C))).bit.Px7SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.

// P1 Port Function Select Register
#define	P1FNCSEL			(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).reg
#define	P1FNCSEL_P10MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px0MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P11MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px1MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P12MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px2MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P13MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px3MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P14MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px4MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P15MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px5MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P16MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px6MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P1FNCSEL_P17MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x1E))).bit.Px7MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.

// P2 Port Data Register
#define	P2DAT				(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).reg
#define	P2DAT_P20IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px0IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P21IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px1IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P22IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px2IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P23IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px3IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P24IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px4IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P25IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px5IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P26IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px6IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P27IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px7IN			///< The GPIO port pin status can be read out from this bit.
#define	P2DAT_P20OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px0OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P21OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px1OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P22OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px2OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P23OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px3OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P24OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px4OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P25OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px5OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P26OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px6OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P2DAT_P27OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x20))).bit.Px7OUT			///< This bit are used to set data to be output from the GPIO port pin.

// P2 Port Enable Register
#define	P2IOEN				(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).reg
#define	P2IOEN_P20OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px0OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P21OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px1OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P22OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px2OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P23OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px3OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P24OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px4OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P25OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px5OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P26OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px6OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P27OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px7OEN			///< This bit enable/disable the GPIO port output.
#define	P2IOEN_P20IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px0IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P21IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px1IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P22IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px2IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P23IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px3IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P24IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px4IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P25IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px5IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P26IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px6IEN			///< This bit enable/disable the GPIO port input.
#define	P2IOEN_P27IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x22))).bit.Px7IEN			///< This bit enable/disable the GPIO port input.

// P2 Port Pull-up/down Control Register
#define	P2RCTL				(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).reg
#define	P2RCTL_P20REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px0REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P21REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px1REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P22REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px2REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P23REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px3REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P24REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px4REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P25REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px5REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P26REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px6REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P27REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px7REN			///< This bit enable/disable the port pull-up/down control.
#define	P2RCTL_P20PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px0PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P21PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px1PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P22PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px2PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P23PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px3PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P24PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px4PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P25PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px5PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P26PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px6PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P2RCTL_P27PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x24))).bit.Px7PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.

// P2 Port Interrupt Flag Register
#define	P2INTF				(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).reg
#define	P2INTF_P20IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px0IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P21IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px1IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P22IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px2IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P23IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px3IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P24IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px4IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P25IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px5IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P26IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px6IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P2INTF_P27IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x26))).bit.Px7IF			///< This bit indicate the port input interrupt cause occurrence status.

// P2 Port Interrupt Control Register
#define	P2INTCTL			(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).reg
#define	P2INTCTL_P20IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px0IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P21IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px1IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P22IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px2IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P23IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px3IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P24IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px4IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P25IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px5IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P26IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px6IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P27IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px7IE			///< This bit enable port input interrupt.
#define	P2INTCTL_P20EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px0EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P21EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px1EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P22EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px2EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P23EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px3EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P24EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px4EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P25EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px5EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P26EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px6EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P2INTCTL_P27EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x28))).bit.Px7EDGE		///< This bit select the input signal edge to generate a port input interrupt.

// P2 Port Mode Select Register
#define	P2MODSEL			(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).reg
#define	P2MODSEL_P20SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px0SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P21SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px1SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P22SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px2SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P23SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px3SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P24SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px4SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P25SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px5SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P26SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px6SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P2MODSEL_P27SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2C))).bit.Px7SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.

// P2 Port Function Select Register
#define	P2FNCSEL			(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).reg
#define	P2FNCSEL_P20MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px0MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P21MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px1MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P22MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px2MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P23MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px3MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P24MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px4MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P25MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px5MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P26MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px6MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	P2FNCSEL_P27MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0x2E))).bit.Px7MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.

// P3 Port Data Register
#define	P3DAT				(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).reg
#define	P3DAT_P30IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px0IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P31IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px1IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P32IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px2IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P33IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px3IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P34IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px4IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P35IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px5IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P36IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px6IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P37IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px7IN			///< The GPIO port pin status can be read out from this bit.
#define	P3DAT_P30OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px0OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P31OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px1OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P32OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px2OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P33OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px3OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P34OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px4OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P35OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px5OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P36OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px6OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	P3DAT_P37OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0x30))).bit.Px7OUT			///< This bit are used to set data to be output from the GPIO port pin.

// P3 Port Enable Register
#define	P3IOEN				(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).reg
#define	P3IOEN_P30OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px0OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P31OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px1OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P32OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px2OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P33OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px3OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P34OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px4OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P35OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px5OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P36OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px6OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P37OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px7OEN			///< This bit enable/disable the GPIO port output.
#define	P3IOEN_P30IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px0IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P31IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px1IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P32IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px2IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P33IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px3IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P34IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px4IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P35IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px5IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P36IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px6IEN			///< This bit enable/disable the GPIO port input.
#define	P3IOEN_P37IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0x32))).bit.Px7IEN			///< This bit enable/disable the GPIO port input.

// P3 Port Pull-up/down Control Register
#define	P3RCTL				(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).reg
#define	P3RCTL_P30REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px0REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P31REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px1REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P32REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px2REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P33REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px3REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P34REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px4REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P35REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px5REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P36REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px6REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P37REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px7REN			///< This bit enable/disable the port pull-up/down control.
#define	P3RCTL_P30PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px0PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P31PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px1PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P32PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px2PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P33PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px3PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P34PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px4PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P35PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px5PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P36PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px6PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	P3RCTL_P37PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0x34))).bit.Px7PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.

// P3 Port Interrupt Flag Register
#define	P3INTF				(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).reg
#define	P3INTF_P30IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px0IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P31IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px1IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P32IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px2IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P33IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px3IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P34IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px4IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P35IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px5IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P36IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px6IF			///< This bit indicate the port input interrupt cause occurrence status.
#define	P3INTF_P37IF		(*((PXINTF_REG *)(PPORT_REG_BASE_ADDR + 0x36))).bit.Px7IF			///< This bit indicate the port input interrupt cause occurrence status.

// P3 Port Interrupt Control Register
#define	P3INTCTL			(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).reg
#define	P3INTCTL_P30IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px0IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P31IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px1IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P32IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px2IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P33IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px3IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P34IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px4IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P35IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px5IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P36IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px6IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P37IE		(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px7IE			///< This bit enable port input interrupt.
#define	P3INTCTL_P30EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px0EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P31EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px1EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P32EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px2EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P33EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px3EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P34EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px4EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P35EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px5EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P36EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px6EDGE		///< This bit select the input signal edge to generate a port input interrupt.
#define	P3INTCTL_P37EDGE	(*((PXINTCTL_REG *)(PPORT_REG_BASE_ADDR + 0x38))).bit.Px7EDGE		///< This bit select the input signal edge to generate a port input interrupt.

// P3 Port Mode Select Register
#define	P3MODSEL			(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).reg
#define	P3MODSEL_P30SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px0SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P31SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px1SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P32SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px2SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P33SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px3SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P34SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px4SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P35SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px5SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P36SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px6SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	P3MODSEL_P37SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0x3C))).bit.Px7SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.


// Pd Port Data Register
#define	PDDAT				(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).reg
#define	PDDAT_PD0IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px0IN			///< The GPIO port pin status can be read out from this bit.
#define	PDDAT_PD1IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px1IN			///< The GPIO port pin status can be read out from this bit.
#define	PDDAT_PD3IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px3IN			///< The GPIO port pin status can be read out from this bit.
#define	PDDAT_PD4IN			(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px4IN			///< The GPIO port pin status can be read out from this bit.
#define	PDDAT_PD0OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px0OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	PDDAT_PD1OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px1OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	PDDAT_PD2OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px2OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	PDDAT_PD3OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px3OUT			///< This bit are used to set data to be output from the GPIO port pin.
#define	PDDAT_PD4OUT		(*((PXDAT_REG *)(PPORT_REG_BASE_ADDR + 0xD0))).bit.Px4OUT			///< This bit are used to set data to be output from the GPIO port pin.

// Pd Port Enable Register
#define	PDIOEN				(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).reg
#define	PDIOEN_PD0OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px0OEN			///< This bit enable/disable the GPIO port output.
#define	PDIOEN_PD1OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px1OEN			///< This bit enable/disable the GPIO port output.
#define	PDIOEN_PD3OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px3OEN			///< This bit enable/disable the GPIO port output.
#define	PDIOEN_PD4OEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px4OEN			///< This bit enable/disable the GPIO port output.
#define	PDIOEN_PD0IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px0IEN			///< This bit enable/disable the GPIO port input.
#define	PDIOEN_PD1IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px1IEN			///< This bit enable/disable the GPIO port input.
#define	PDIOEN_PD3IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px3IEN			///< This bit enable/disable the GPIO port input.
#define	PDIOEN_PD4IEN		(*((PXIOEN_REG *)(PPORT_REG_BASE_ADDR + 0xD2))).bit.Px4IEN			///< This bit enable/disable the GPIO port input.

// Pd Port Pull-up/down Control Register
#define	PDRCTL				(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).reg
#define	PDRCTL_PD0REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px0REN			///< This bit enable/disable the port pull-up/down control.
#define	PDRCTL_PD1REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px1REN			///< This bit enable/disable the port pull-up/down control.
#define	PDRCTL_PD3REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px3REN			///< This bit enable/disable the port pull-up/down control.
#define	PDRCTL_PD4REN		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px4REN			///< This bit enable/disable the port pull-up/down control.
#define	PDRCTL_PD0PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px0PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	PDRCTL_PD1PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px1PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	PDRCTL_PD3PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px3PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.
#define	PDRCTL_PD4PDPU		(*((PXRCTL_REG *)(PPORT_REG_BASE_ADDR + 0xD4))).bit.Px4PDPU			///< This bit select either the pull-up resistor or the pull-down resistor when using a resistor built into the port.

// Pd Port Mode Select Register
#define	PDMODSEL			(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDC))).reg
#define	PDMODSEL_PD0SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDC))).bit.Px0SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	PDMODSEL_PD1SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDC))).bit.Px1SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	PDMODSEL_PD2SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDC))).bit.Px2SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	PDMODSEL_PD3SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDC))).bit.Px3SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.
#define	PDMODSEL_PD4SEL		(*((PXMODSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDC))).bit.Px4SEL		///< This bit select whether each port is used for the GPIO function or a peripheral I/O function.

// Pd Port Function Select Register
#define	PDFNCSEL			(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDE))).reg
#define	PDFNCSEL_PD0MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDE))).bit.Px0MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	PDFNCSEL_PD1MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDE))).bit.Px1MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	PDFNCSEL_PD2MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDE))).bit.Px2MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	PDFNCSEL_PD3MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDE))).bit.Px3MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.
#define	PDFNCSEL_PD4MUX		(*((PXFNCSEL_REG *)(PPORT_REG_BASE_ADDR + 0xDE))).bit.Px4MUX		///< This bit select the peripheral I/O function to be assigned to each port pin.

// P Port Clock Control Register
#define	PCLK				(*((PCLK_REG *)(PPORT_REG_BASE_ADDR + 0xE0))).reg
#define	PCLK_CLKSRC			(*((PCLK_REG *)(PPORT_REG_BASE_ADDR + 0xE0))).bit.CLKSRC			///< These bits select the clock source of PPORT (chattering filter).
#define	PCLK_KRSTCFG		(*((PCLK_REG *)(PPORT_REG_BASE_ADDR + 0xE0))).bit.KRSTCFG			///< These bits configure the key-entry reset function.
#define	PCLK_CLKDIV			(*((PCLK_REG *)(PPORT_REG_BASE_ADDR + 0xE0))).bit.CLKDIV			///< These bits select the division ratio of the PPORT operating clock (chattering filter clock).
#define	PCLK_DBRUN			(*((PCLK_REG *)(PPORT_REG_BASE_ADDR + 0xE0))).bit.DBRUN				///< This bit sets whether the PPORT operating clock is supplied in DEBUG mode or not.

// P Port Interrupt Flag Group Register
#define	PINTFGRP			(*((PINTFGRP_REG *)(PPORT_REG_BASE_ADDR + 0xE2))).reg
#define	PINTFGRP_P0INT		(*((PINTFGRP_REG *)(PPORT_REG_BASE_ADDR + 0xE2))).bit.P0INT			///< This bit indicate that P0 port group includes a port that has generated an interrupt.
#define	PINTFGRP_P1INT		(*((PINTFGRP_REG *)(PPORT_REG_BASE_ADDR + 0xE2))).bit.P1INT			///< This bit indicate that P1 port group includes a port that has generated an interrupt.
#define	PINTFGRP_P2INT		(*((PINTFGRP_REG *)(PPORT_REG_BASE_ADDR + 0xE2))).bit.P2INT			///< This bit indicate that P2 port group includes a port that has generated an interrupt.
#define	PINTFGRP_P3INT		(*((PINTFGRP_REG *)(PPORT_REG_BASE_ADDR + 0xE2))).bit.P3INT			///< This bit indicate that P3 port group includes a port that has generated an interrupt.


/********************/
/* ----- UPMUX ---- */
/********************/
// P00-01 Universal Port Multiplexer Setting Register
#define	P0UPMUX0			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).reg
#define	P0UPMUX0_P00PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX0_P00PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX0_P00PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P0UPMUX0_P01PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX0_P01PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX0_P01PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x00))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P02-03 Universal Port Multiplexer Setting Register
#define	P0UPMUX1			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).reg
#define	P0UPMUX1_P02PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX1_P02PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX1_P02PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P0UPMUX1_P03PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX1_P03PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX1_P03PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x02))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P04-05 Universal Port Multiplexer Setting Register
#define	P0UPMUX2			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).reg
#define	P0UPMUX2_P04PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX2_P04PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX2_P04PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P0UPMUX2_P05PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX2_P05PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX2_P05PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x04))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P06-07 Universal Port Multiplexer Setting Register
#define	P0UPMUX3			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x06))).reg
#define	P0UPMUX3_P06PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x06))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX3_P06PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x06))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P0UPMUX3_P06PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x06))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P0UPMUX3_P07PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x06))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P0UPMUX3_P07PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x06))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.

// P10-11 Universal Port Multiplexer Setting Register
#define	P1UPMUX0			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).reg
#define	P1UPMUX0_P10PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX0_P10PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX0_P10PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P1UPMUX0_P11PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX0_P11PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX0_P11PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x08))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P12-13 Universal Port Multiplexer Setting Register
#define	P1UPMUX1			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).reg
#define	P1UPMUX1_P12PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX1_P12PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX1_P12PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P1UPMUX1_P13PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX1_P13PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX1_P13PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0A))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P14-15 Universal Port Multiplexer Setting Register
#define	P1UPMUX2			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).reg
#define	P1UPMUX2_P14PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX2_P14PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX2_P14PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P1UPMUX2_P15PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX2_P15PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX2_P15PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0C))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P16-17 Universal Port Multiplexer Setting Register
#define	P1UPMUX3			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).reg
#define	P1UPMUX3_P16PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX3_P16PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX3_P16PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P1UPMUX3_P17PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P1UPMUX3_P17PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P1UPMUX3_P17PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x0E))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P20-21 Universal Port Multiplexer Setting Register
#define	P2UPMUX0			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).reg
#define	P2UPMUX0_P20PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX0_P20PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX0_P20PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P2UPMUX0_P21PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX0_P21PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX0_P21PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x10))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P22-23 Universal Port Multiplexer Setting Register
#define	P2UPMUX1			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).reg
#define	P2UPMUX1_P22PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX1_P22PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX1_P22PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P2UPMUX1_P23PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX1_P23PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX1_P23PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x12))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P24-25 Universal Port Multiplexer Setting Register
#define	P2UPMUX2			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).reg
#define	P2UPMUX2_P24PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX2_P24PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX2_P24PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P2UPMUX2_P25PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX2_P25PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX2_P25PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x14))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.

// P26-27 Universal Port Multiplexer Setting Register
#define	P2UPMUX3			(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).reg
#define	P2UPMUX3_P26PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).bit.PxyPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX3_P26PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).bit.PxyPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX3_P26PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).bit.PxyPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.
#define	P2UPMUX3_P27PERISEL	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).bit.PxzPERISEL	///< These bits specify a peripheral circuit.
#define	P2UPMUX3_P27PERICH	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).bit.PxzPERICH		///< These bits specify a peripheral circuit channel number.
#define	P2UPMUX3_P27PPFNC	(*((PXUPMUXN_REG *)(UPMUX_REG_BASE_ADDR + 0x16))).bit.PxzPPFNC		///< These bits specify the peripheral I/O function to be assigned to the port.


/********************/
/* ----- UART ----- */
/********************/

// UART Ch.0 Clock Control Register
#define	UA0CLK				(*((UANCLK_REG *)(UART_0_REG_BASE_ADDR + 0x00))).reg
#define	UA0CLK_CLKSRC		(*((UANCLK_REG *)(UART_0_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the UART.
#define	UA0CLK_CLKDIV		(*((UANCLK_REG *)(UART_0_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the UART operating clock.
#define	UA0CLK_DBRUN		(*((UANCLK_REG *)(UART_0_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the UART operating clock is supplied in DEBUG mode or not.

// UART Ch.0 Mode Register
#define	UA0MOD				(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).reg
#define	UA0MOD_STPB			(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.STPB			///< This bit sets the stop bit length.
#define	UA0MOD_PRMD			(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.PRMD			///< This bit selects either odd parity or even parity when using the parity function.
#define	UA0MOD_PREN			(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.PREN			///< This bit sets the data length.
#define	UA0MOD_CHLN			(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.CHLN			///< This bit sets the data length.
#define	UA0MOD_IRMD			(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.IRMD			///< This bit enables the IrDA interface function.
#define	UA0MOD_OUTMD		(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.OUTMD			///< This bit sets the USOUT0 pin output mode.
#define	UA0MOD_PUEN			(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.PUEN			///< This bit enables pull-up of the USIN0 pin.
#define	UA0MOD_INVIRTX		(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.INVIRTX		///< This bit enables the USOUT0 output inverting function when the IrDA interface function is enabled.
#define	UA0MOD_INVIRRX		(*((UANMOD_REG *)(UART_0_REG_BASE_ADDR + 0x02))).bit.INVIRRX		///< This bit enables the USIN0 input inverting function when the IrDA interface function is enabled.

// UART Ch.0 Baud-Rate Register
#define	UA0BR				(*((UANBR_REG *)(UART_0_REG_BASE_ADDR + 0x04))).reg
#define	UA0BR_BRT			(*((UANBR_REG *)(UART_0_REG_BASE_ADDR + 0x04))).bit.BRT				///< These bits set the UART transfer rate.
#define	UA0BR_FMD			(*((UANBR_REG *)(UART_0_REG_BASE_ADDR + 0x04))).bit.FMD				///< These bits set the UART transfer rate.

// UART Ch.0 Control Register
#define	UA0CTL				(*((UANCTL_REG *)(UART_0_REG_BASE_ADDR + 0x06))).reg
#define	UA0CTL_MODEN		(*((UANCTL_REG *)(UART_0_REG_BASE_ADDR + 0x06))).bit.MODEN			///< This bit enables the UART operations.
#define	UA0CTL_SFTRST		(*((UANCTL_REG *)(UART_0_REG_BASE_ADDR + 0x06))).bit.SFTRST			///< This bit issues software reset to the UART.

// UART Ch.0 Transmit Data Register
#define	UA0TXD				(*((UANTXD_REG *)(UART_0_REG_BASE_ADDR + 0x08))).reg
#define	UA0TXD_TXD			(*((UANTXD_REG *)(UART_0_REG_BASE_ADDR + 0x08))).bit.TXD			///< Data can be written to the transmit data buffer through these bits.

// UART Ch.0 Receive Data Register
#define	UA0RXD				(*((UANRXD_REG *)(UART_0_REG_BASE_ADDR + 0x0A))).reg
#define	UA0RXD_RXD			(*((UANRXD_REG *)(UART_0_REG_BASE_ADDR + 0x0A))).bit.RXD			///< The receive data buffer can be read through these bits.

// UART Ch.0 Status and Interrupt Flag Register
#define	UA0INTF				(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).reg
#define	UA0INTF_TBEIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.TBEIF			///< These bits indicate Transmit buffer empty interrupt cause occurrence status.
#define	UA0INTF_RB1FIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.RB1FIF		///< These bits indicate Receive buffer one byte full interrupt cause occurrence status.
#define	UA0INTF_RB2FIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.RB2FIF		///< These bits indicate Receive buffer two bytes full interrupt cause occurrence status.
#define	UA0INTF_OEIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.OEIF			///< These bits indicate Overrun error interrupt cause occurrence status.
#define	UA0INTF_PEIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.PEIF			///< These bits indicate Parity error interrupt cause occurrence status.
#define	UA0INTF_FEIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.FEIF			///< These bits indicate Framing error interrupt cause occurrence status.
#define	UA0INTF_TENDIF		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.TENDIF		///< These bits indicate End-of-transmission interrupt cause occurrence status.
#define	UA0INTF_TBSY		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.TBSY			///< This bit indicates the sending status.
#define	UA0INTF_RBSY		(*((UANINTF_REG *)(UART_0_REG_BASE_ADDR + 0x0C))).bit.RBSY			///< This bit indicates the receiving status.

// UART Ch.0 Interrupt Enable Register
#define	UA0INTE				(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).reg
#define	UA0INTE_TBEIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.TBEIE			///< These bits enable Transmit buffer empty interrupt.
#define	UA0INTE_RB1FIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.RB1FIE		///< These bits enable Receive buffer one byte full interrupt.
#define	UA0INTE_RB2FIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.RB2FIE		///< These bits enable Receive buffer two bytes full interrupt.
#define	UA0INTE_OEIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.OEIE			///< These bits enable Overrun error interrupt.
#define	UA0INTE_PEIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.PEIE			///< These bits enable Parity error interrupt.
#define	UA0INTE_FEIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.FEIE			///< These bits enable Framing error interrupt.
#define	UA0INTE_TENDIE		(*((UANINTE_REG *)(UART_0_REG_BASE_ADDR + 0x0E))).bit.TENDIE		///< These bits enable End-of-transmission interrupt.

// UART Ch.1 Clock Control Register
#define	UA1CLK				(*((UANCLK_REG *)(UART_1_REG_BASE_ADDR + 0x00))).reg
#define	UA1CLK_CLKSRC		(*((UANCLK_REG *)(UART_1_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the UART.
#define	UA1CLK_CLKDIV		(*((UANCLK_REG *)(UART_1_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the UART operating clock.
#define	UA1CLK_DBRUN		(*((UANCLK_REG *)(UART_1_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the UART operating clock is supplied in DEBUG mode or not.

// UART Ch.1 Mode Register
#define	UA1MOD				(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).reg
#define	UA1MOD_STPB			(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.STPB			///< This bit sets the stop bit length.
#define	UA1MOD_PRMD			(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.PRMD			///< This bit selects either odd parity or even parity when using the parity function.
#define	UA1MOD_PREN			(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.PREN			///< This bit sets the data length.
#define	UA1MOD_CHLN			(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.CHLN			///< This bit sets the data length.
#define	UA1MOD_IRMD			(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.IRMD			///< This bit enables the IrDA interface function.
#define	UA1MOD_OUTMD		(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.OUTMD			///< This bit sets the USOUT0 pin output mode.
#define	UA1MOD_PUEN			(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.PUEN			///< This bit enables pull-up of the USIN0 pin.
#define	UA1MOD_INVIRTX		(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.INVIRTX		///< This bit enables the USOUT0 output inverting function when the IrDA interface function is enabled.
#define	UA1MOD_INVIRRX		(*((UANMOD_REG *)(UART_1_REG_BASE_ADDR + 0x02))).bit.INVIRRX		///< This bit enables the USIN0 input inverting function when the IrDA interface function is enabled.

// UART Ch.1 Baud-Rate Register
#define	UA1BR				(*((UANBR_REG *)(UART_1_REG_BASE_ADDR + 0x04))).reg
#define	UA1BR_BRT			(*((UANBR_REG *)(UART_1_REG_BASE_ADDR + 0x04))).bit.BRT				///< These bits set the UART transfer rate.
#define	UA1BR_FMD			(*((UANBR_REG *)(UART_1_REG_BASE_ADDR + 0x04))).bit.FMD				///< These bits set the UART transfer rate.

// UART Ch.1 Control Register
#define	UA1CTL				(*((UANCTL_REG *)(UART_1_REG_BASE_ADDR + 0x06))).reg
#define	UA1CTL_MODEN		(*((UANCTL_REG *)(UART_1_REG_BASE_ADDR + 0x06))).bit.MODEN			///< This bit enables the UART operations.
#define	UA1CTL_SFTRST		(*((UANCTL_REG *)(UART_1_REG_BASE_ADDR + 0x06))).bit.SFTRST			///< This bit issues software reset to the UART.

// UART Ch.1 Transmit Data Register
#define	UA1TXD				(*((UANTXD_REG *)(UART_1_REG_BASE_ADDR + 0x08))).reg
#define	UA1TXD_TXD			(*((UANTXD_REG *)(UART_1_REG_BASE_ADDR + 0x08))).bit.TXD			///< Data can be written to the transmit data buffer through these bits.

// UART Ch.1 Receive Data Register
#define	UA1RXD				(*((UANRXD_REG *)(UART_1_REG_BASE_ADDR + 0x0A))).reg
#define	UA1RXD_RXD			(*((UANRXD_REG *)(UART_1_REG_BASE_ADDR + 0x0A))).bit.RXD			///< The receive data buffer can be read through these bits.

// UART Ch.1 Status and Interrupt Flag Register
#define	UA1INTF				(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).reg
#define	UA1INTF_TBEIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.TBEIF			///< These bits indicate Transmit buffer empty interrupt cause occurrence status.
#define	UA1INTF_RB1FIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.RB1FIF		///< These bits indicate Receive buffer one byte full interrupt cause occurrence status.
#define	UA1INTF_RB2FIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.RB2FIF		///< These bits indicate Receive buffer two bytes full interrupt cause occurrence status.
#define	UA1INTF_OEIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.OEIF			///< These bits indicate Overrun error interrupt cause occurrence status.
#define	UA1INTF_PEIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.PEIF			///< These bits indicate Parity error interrupt cause occurrence status.
#define	UA1INTF_FEIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.FEIF			///< These bits indicate Framing error interrupt cause occurrence status.
#define	UA1INTF_TENDIF		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.TENDIF		///< These bits indicate End-of-transmission interrupt cause occurrence status.
#define	UA1INTF_TBSY		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.TBSY			///< This bit indicates the sending status.
#define	UA1INTF_RBSY		(*((UANINTF_REG *)(UART_1_REG_BASE_ADDR + 0x0C))).bit.RBSY			///< This bit indicates the receiving status.

// UART Ch.1 Interrupt Enable Register
#define	UA1INTE				(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).reg
#define	UA1INTE_TBEIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.TBEIE			///< These bits enable Transmit buffer empty interrupt.
#define	UA1INTE_RB1FIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.RB1FIE		///< These bits enable Receive buffer one byte full interrupt.
#define	UA1INTE_RB2FIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.RB2FIE		///< These bits enable Receive buffer two bytes full interrupt.
#define	UA1INTE_OEIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.OEIE			///< These bits enable Overrun error interrupt.
#define	UA1INTE_PEIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.PEIE			///< These bits enable Parity error interrupt.
#define	UA1INTE_FEIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.FEIE			///< These bits enable Framing error interrupt.
#define	UA1INTE_TENDIE		(*((UANINTE_REG *)(UART_1_REG_BASE_ADDR + 0x0E))).bit.TENDIE		///< These bits enable End-of-transmission interrupt.

/*******************/
/* ----- SPI ----- */
/*******************/

// SPI Ch.0 Mode Register
#define	SPI0MOD				(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).reg
#define	SPI0MOD_MST			(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.MST			///< This bit sets the SPIA operating mode (master mode or slave mode).
#define	SPI0MOD_CPOL		(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.CPOL			///< This bit set the SPI clock phase and polarity.
#define	SPI0MOD_CPHA		(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.CPHA			///< This bit set the SPI clock phase and polarity.
#define	SPI0MOD_LSBFST		(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.LSBFST			///< This bit configures the data format (input/output permutation).
#define	SPI0MOD_NOCLKDIV	(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.NOCLKDIV		///< This bit selects SPICLKn in master mode. This setting is ineffective in slave mode.
#define	SPI0MOD_PUEN		(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.PUEN			///< This bit enables pull-up/down of the input pins.
#define	SPI0MOD_CHLN		(*((SPINMOD_REG *)(SPI_0_REG_BASE_ADDR + 0x00))).bit.CHLN			///< These bits set the bit length of transfer data.

// SPI Ch.0 Control Register
#define	SPI0CTL				(*((SPINCTL_REG *)(SPI_0_REG_BASE_ADDR + 0x02))).reg
#define	SPI0CTL_MODEN		(*((SPINCTL_REG *)(SPI_0_REG_BASE_ADDR + 0x02))).bit.MODEN			///< This bit enables the SPIA operations.
#define	SPI0CTL_SFTRST		(*((SPINCTL_REG *)(SPI_0_REG_BASE_ADDR + 0x02))).bit.SFTRST			///< This bit issues software reset to SPIA.

// SPI Ch.0 Transmit Data Register
#define	SPI0TXD				(*((SPINTXD_REG *)(SPI_0_REG_BASE_ADDR + 0x04))).reg
#define	SPI0TXD_TXD			(*((SPINTXD_REG *)(SPI_0_REG_BASE_ADDR + 0x04))).bit.TXD			///< Data can be written to the transmit data buffer through these bits.

// SPI Ch.0 Receive Data Register
#define	SPI0RXD				(*((SPINRXD_REG *)(SPI_0_REG_BASE_ADDR + 0x06))).reg
#define	SPI0RXD_RXD			(*((SPINRXD_REG *)(SPI_0_REG_BASE_ADDR + 0x06))).bit.RXD			///< The receive data buffer can be read through these bits.

// SPI Ch.0 Interrupt Flag Register
#define	SPI0INTF			(*((SPININTF_REG *)(SPI_0_REG_BASE_ADDR + 0x08))).reg
#define	SPI0INTF_TBEIF		(*((SPININTF_REG *)(SPI_0_REG_BASE_ADDR + 0x08))).bit.TBEIF			///< This bit indicate Transmit buffer empty interrupt cause occurrence status.
#define	SPI0INTF_RBFIF		(*((SPININTF_REG *)(SPI_0_REG_BASE_ADDR + 0x08))).bit.RBFIF			///< This bit indicate Receive buffer full interrupt cause occurrence status.
#define	SPI0INTF_TENDIF		(*((SPININTF_REG *)(SPI_0_REG_BASE_ADDR + 0x08))).bit.TENDIF		///< This bit indicate End-of-transmission interrupt cause occurrence status.
#define	SPI0INTF_OEIF		(*((SPININTF_REG *)(SPI_0_REG_BASE_ADDR + 0x08))).bit.OEIF			///< This bit indicate Overrun error interrupt cause occurrence status.
#define	SPI0INTF_BSY		(*((SPININTF_REG *)(SPI_0_REG_BASE_ADDR + 0x08))).bit.BSY			///< This bit indicates the SPIA operating status.

// SPI Ch.0 Interrupt Enable Register
#define	SPI0INTE			(*((SPININTE_REG *)(SPI_0_REG_BASE_ADDR + 0x0A))).reg
#define	SPI0INTE_TBEIE		(*((SPININTE_REG *)(SPI_0_REG_BASE_ADDR + 0x0A))).bit.TBEIE			///< This bit enable Transmit buffer empty interrupt.
#define	SPI0INTE_RBFIE		(*((SPININTE_REG *)(SPI_0_REG_BASE_ADDR + 0x0A))).bit.RBFIE			///< This bit enable Receive buffer full interrupt.
#define	SPI0INTE_TENDIE		(*((SPININTE_REG *)(SPI_0_REG_BASE_ADDR + 0x0A))).bit.TENDIE		///< This bit enable End-of-transmission interrupt.
#define	SPI0INTE_OEIE		(*((SPININTE_REG *)(SPI_0_REG_BASE_ADDR + 0x0A))).bit.OEIE			///< This bit enable Overrun error interrupt.


/*******************/
/* ----- I2C ----- */
/*******************/

// I2C Ch.0 Clock Control Register
#define	I2C0CLK				(*((I2CNCLK_REG *)(I2C_REG_BASE_ADDR + 0x00))).reg
#define	I2C0CLK_CLKSRC		(*((I2CNCLK_REG *)(I2C_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the I2C.
#define	I2C0CLK_CLKDIV		(*((I2CNCLK_REG *)(I2C_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the I2C operating clock.
#define	I2C0CLK_DBRUN		(*((I2CNCLK_REG *)(I2C_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the I2C operating clock is supplied in DEBUG mode or not.

// I2C Ch.0 Mode Register
#define	I2C0MOD				(*((I2CNMOD_REG *)(I2C_REG_BASE_ADDR + 0x02))).reg
#define	I2C0MOD_GCEN		(*((I2CNMOD_REG *)(I2C_REG_BASE_ADDR + 0x02))).bit.GCEN				///< This bit sets whether to respond to master general calls in slave mode or not.
#define	I2C0MOD_OADR10		(*((I2CNMOD_REG *)(I2C_REG_BASE_ADDR + 0x02))).bit.OADR10			///< This bit sets the number of own address bits for slave mode.

// I2C Ch.0 Baud-Rate Register
#define	I2C0BR				(*((I2CNBR_REG *)(I2C_REG_BASE_ADDR + 0x04))).reg
#define	I2C0BR_BRT			(*((I2CNBR_REG *)(I2C_REG_BASE_ADDR + 0x04))).bit.BRT				///< These bits set the I2C Ch.n transfer rate for master mode.

// I2C Ch.0 Own Address Register
#define	I2C0OADR			(*((I2CNOADR_REG *)(I2C_REG_BASE_ADDR + 0x08))).reg
#define	I2C0OADR_OADR		(*((I2CNOADR_REG *)(I2C_REG_BASE_ADDR + 0x08))).bit.OADR			///< These bits set the own address for slave mode.

// I2C Ch.0 Control Register
#define	I2C0CTL				(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).reg
#define	I2C0CTL_MODEN		(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).bit.MODEN			///< This bit enables the I2C operations.
#define	I2C0CTL_SFTRST		(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).bit.SFTRST			///< This bit issues software reset to the I2C.
#define	I2C0CTL_TXSTART		(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).bit.TXSTART			///< This bit issues a START condition in master mode.
#define	I2C0CTL_TXSTOP		(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).bit.TXSTOP			///< This bit issues a STOP condition in master mode.
#define	I2C0CTL_TXNACK		(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).bit.TXNACK			///< This bit issues a request for sending a NACK at the next responding.
#define	I2C0CTL_MST			(*((I2CNCTL_REG *)(I2C_REG_BASE_ADDR + 0x0A))).bit.MST				///< This bit selects the I2C Ch.n operating mode.

// I2C Ch.0 Transmit Data Register
#define	I2C0TXD				(*((I2CNTXD_REG *)(I2C_REG_BASE_ADDR + 0x0C))).reg
#define	I2C0TXD_TXD			(*((I2CNTXD_REG *)(I2C_REG_BASE_ADDR + 0x0C))).bit.TXD				///< Data can be written to the transmit data buffer through these bits.

// I2C Ch.0 Receive Data Register
#define	I2C0RXD				(*((I2CNRXD_REG *)(I2C_REG_BASE_ADDR + 0x0E))).reg
#define	I2C0RXD_RXD			(*((I2CNRXD_REG *)(I2C_REG_BASE_ADDR + 0x0E))).bit.RXD				///< The receive data buffer can be read through these bits.

// I2C Ch.0 Status and Interrupt Flag Register
#define	I2C0INTF			(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).reg
#define	I2C0INTF_TBEIF		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.TBEIF			///< This bit indicate Transmit buffer empty interrupt cause occurrence status.
#define	I2C0INTF_RBFIF		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.RBFIF			///< This bit indicate Receive buffer full interrupt cause occurrence status.
#define	I2C0INTF_ERRIF		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.ERRIF			///< This bit indicate Error detection interrupt cause occurrence status.
#define	I2C0INTF_STARTIF	(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.STARTIF			///< This bit indicate START condition interrupt cause occurrence status.
#define	I2C0INTF_STOPIF		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.STOPIF			///< This bit indicate STOP condition interrupt cause occurrence status.
#define	I2C0INTF_NACKIF		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.NACKIF			///< This bit indicate NACK reception interrupt cause occurrence status.
#define	I2C0INTF_GCIF		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.GCIF			///< This bit indicate General call address reception interrupt cause occurrence status.
#define	I2C0INTF_BYTEENDIF	(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.BYTEENDIF		///< This bit indicate End of transfer interrupt cause occurrence status.
#define	I2C0INTF_TR			(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.TR				///< This bit indicates whether the I2C is set in transmission mode or not.
#define	I2C0INTF_BSY		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.BSY				///< This bit indicates that the I2C bus is placed into busy status.
#define	I2C0INTF_SCLLOW		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.SCLLOW			///< This bit indicates that SCL is set to low level.
#define	I2C0INTF_SDALOW		(*((I2CNINTF_REG *)(I2C_REG_BASE_ADDR + 0x10))).bit.SDALOW			///< This bit indicates that SDA is set to low level.

// I2C Ch.0 Interrupt Enable Register
#define	I2C0INTE			(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).reg
#define	I2C0INTE_TBEIE		(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.TBEIE			///< This bit enable Transmit buffer empty interrupt.
#define	I2C0INTE_RBFIE		(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.RBFIE			///< This bit enable Receive buffer full interrupt.
#define	I2C0INTE_ERRIE		(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.ERRIE			///< This bit enable Error detection interrupt.
#define	I2C0INTE_STARTIE	(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.STARTIE			///< This bit enable START condition interrupt.
#define	I2C0INTE_STOPIE		(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.STOPIE			///< This bit enable STOP condition interrupt.
#define	I2C0INTE_NACKIE		(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.NACKIE			///< This bit enable NACK reception interrupt.
#define	I2C0INTE_GCIE		(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.GCIE			///< This bit enable General call address reception interrupt.
#define	I2C0INTE_BYTEENDIE	(*((I2CNINTE_REG *)(I2C_REG_BASE_ADDR + 0x12))).bit.BYTEENDIE		///< This bit enable End of transfer interrupt.

/*********************/
/* ----- T16B ------ */
/*********************/

// T16B Ch.0 Clock Control Register
#define	T16B0CLK			(*((T16BNCLK_REG *)(T16B_0_REG_BASE_ADDR + 0x00))).reg
#define	T16B0CLK_CLKSRC		(*((T16BNCLK_REG *)(T16B_0_REG_BASE_ADDR + 0x00))).bit.CLKSRC		///< These bits select the clock source of T16B Ch.0.
#define	T16B0CLK_CLKDIV		(*((T16BNCLK_REG *)(T16B_0_REG_BASE_ADDR + 0x00))).bit.CLKDIV		///< These bits select the division ratio of the T16B Ch.0 operating clock (counter clock).
#define	T16B0CLK_DBRUN		(*((T16BNCLK_REG *)(T16B_0_REG_BASE_ADDR + 0x00))).bit.DBRUN		///< This bit sets whether the T16B Ch.0 operating clock is supplied in DEBUG mode or not.

// T16B Ch.0 Counter Control Register.
#define	T16B0CTL			(*((T16BNCLK_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).reg
#define	T16B0CTL_MODEN		(*((T16BNCTL_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).bit.MODEN		///< This bit enables the T16B Ch.0 operations.
#define	T16B0CTL_PRESET		(*((T16BNCTL_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).bit.PRESET		///< This bit resets the counter.
#define	T16B0CTL_RUN		(*((T16BNCTL_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).bit.RUN			///< This bit starts/stops counting.
#define	T16B0CTL_ONEST		(*((T16BNCTL_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).bit.ONEST		///< This bit selects the counter repeat/one-shot mode.
#define	T16B0CTL_CNTMD		(*((T16BNCTL_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).bit.CNTMD		///< These bits select the counter up/down mode.
#define	T16B0CTL_MAXBSY		(*((T16BNCTL_REG *)(T16B_0_REG_BASE_ADDR + 0x02))).bit.MAXBSY		///< This bit indicates whether data can be written to the T16BnMC register or not.

// T16B Ch.0 Max Counter Data Register
#define	T16B0MC				(*((T16BNMC_REG *)(T16B_0_REG_BASE_ADDR + 0x04))).reg

// T16B Ch.0 Timer Counter Data Register.
#define	T16B0TC				(*((T16BNTC_REG *)(T16B_0_REG_BASE_ADDR + 0x06))).reg

// T16B Ch.0 Counter Status Register
#define	T16B0CS				(*((T16BNCS_REG *)(T16B_0_REG_BASE_ADDR + 0x08))).reg
#define	T16B0CS_BSY			(*((T16BNCS_REG *)(T16B_0_REG_BASE_ADDR + 0x08))).bit.BSY			///< This bit indicates the counter operating status.
#define	T16B0CS_UP_DOWN		(*((T16BNCS_REG *)(T16B_0_REG_BASE_ADDR + 0x08))).bit.UP_DOWN		///< This bit indicates the currently set count direction.
#define	T16B0CS_CAPI0		(*((T16BNCS_REG *)(T16B_0_REG_BASE_ADDR + 0x08))).bit.CAPI0			///< These bits indicate the signal level currently input to the CAPx0 pin.
#define	T16B0CS_CAPI1		(*((T16BNCS_REG *)(T16B_0_REG_BASE_ADDR + 0x08))).bit.CAPI1			///< These bits indicate the signal level currently input to the CAPx1 pin.

// T16B Ch.0 Interrupt Flag Register.
#define	T16B0INTF			(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).reg
#define	T16B0INTF_CNTZEROIF	(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).bit.CNTZEROIF	///< Counter zero interrupt
#define	T16B0INTF_CNTMAXIF	(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).bit.CNTMAXIF	///< Counter MAX interrupt
#define	T16B0INTF_CMPCAP0IF	(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).bit.CMPCAP0IF	///< Compare/capture 0 interrupt
#define	T16B0INTF_CAPOW0IF	(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).bit.CAPOW0IF	///< Capture 0 overwrite interrupt
#define	T16B0INTF_CMPCAP1IF	(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).bit.CMPCAP1IF	///< Compare/capture 1 interrupt
#define	T16B0INTF_CAPOW1IF	(*((T16BNINTF_REG *)(T16B_0_REG_BASE_ADDR + 0x0A))).bit.CAPOW1IF	///< Capture 1 overwrite interrupt

// T16B Ch.0 Interrupt Enable Register.
#define	T16B0INTE			(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).reg
#define	T16B0INTE_CNTZEROIE	(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).bit.CNTZEROIE	///< Counter zero interrupt
#define	T16B0INTE_CNTMAXIE	(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).bit.CNTMAXIE	///< Counter MAX interrupt
#define	T16B0INTE_CMPCAP0IE	(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).bit.CMPCAP0IE	///< Compare/capture 0 interrupt
#define	T16B0INTE_CAPOW0IE	(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).bit.CAPOW0IE	///< Capture 0 overwrite interrupt
#define	T16B0INTE_CMPCAP1IE	(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).bit.CMPCAP1IE	///< Compare/capture 1 interrupt
#define	T16B0INTE_CAPOW1IE	(*((T16BNINTE_REG *)(T16B_0_REG_BASE_ADDR + 0x0C))).bit.CAPOW1IE	///< Capture 1 overwrite interrupt

// T16B Ch.0 Comparator/Capture 0 Control Register.
#define	T16B0CCCTL0			(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).reg
#define	T16B0CCCTL0_CCMD	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.CCMD		///< This bit selects the operating mode of the comparator/capture circuit m.
#define	T16B0CCCTL0_TOUTINV	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.TOUTINV	///< This bit selects the TOUT00 signal polarity.
#define	T16B0CCCTL0_TOUTMD	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.TOUTMD	///< These bits configure how the TOUT00 signal waveform is changed.
#define	T16B0CCCTL0_TOUTO	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.TOUTO		///< This bit sets the TOUT00 signal output level
#define	T16B0CCCTL0_TOUTMT	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.TOUTMT	///< This bit selects whether the comparator equal signal.
#define	T16B0CCCTL0_CAPTRG	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.CAPTRG	///< These bits select the trigger edge(s) of the trigger signal.
#define	T16B0CCCTL0_CAPIS	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.CAPIS		///< These bits select the trigger signal for capturing.
#define	T16B0CCCTL0_CBUFMD	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.CBUFMD	///< These bits select the timing to load the comparison value written.
#define	T16B0CCCTL0_SCS		(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x10))).bit.SCS		///< This bit selects either synchronous capture mode or asynchronous capture mode.

// T16B Ch.0 Compare/Capture 0 Data Register.
#define	T16B0CCR0			(*((T16BNCCRM_REG *)(T16B_0_REG_BASE_ADDR + 0x12))).reg

// T16B Ch.0 Comparator/Capture 1 Control Register.
#define	T16B0CCCTL1			(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).reg
#define	T16B0CCCTL1_CCMD	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.CCMD		///< This bit selects the operating mode of the comparator/capture circuit m.
#define	T16B0CCCTL1_TOUTINV	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.TOUTINV	///< This bit selects the TOUT01 signal polarity.
#define	T16B0CCCTL1_TOUTMD	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.TOUTMD	///< These bits configure how the TOUT01 signal waveform is changed.
#define	T16B0CCCTL1_TOUTO	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.TOUTO		///< This bit sets the TOUT01 signal output level
#define	T16B0CCCTL1_TOUTMT	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.TOUTMT	///< This bit selects whether the comparator equal signal.
#define	T16B0CCCTL1_CAPTRG	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.CAPTRG	///< These bits select the trigger edge(s) of the trigger signal.
#define	T16B0CCCTL1_CAPIS	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.CAPIS		///< These bits select the trigger signal for capturing.
#define	T16B0CCCTL1_CBUFMD	(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.CBUFMD	///< These bits select the timing to load the comparison value written.
#define	T16B0CCCTL1_SCS		(*((T16BNCCCTLM_REG *)(T16B_0_REG_BASE_ADDR + 0x18))).bit.SCS		///< This bit selects either synchronous capture mode or asynchronous capture mode.

// T16B Ch.0 Compare/Capture 1 Data Register.
#define	T16B0CCR1			(*((T16BNCCRM_REG *)(T16B_0_REG_BASE_ADDR + 0x1a))).reg

// T16B Ch.1 Clock Control Register
#define	T16B1CLK			(*((T16BNCLK_REG *)(T16B_1_REG_BASE_ADDR + 0x00))).reg
#define	T16B1CLK_CLKSRC		(*((T16BNCLK_REG *)(T16B_1_REG_BASE_ADDR + 0x00))).bit.CLKSRC		///< These bits select the clock source of T16B Ch.1.
#define	T16B1CLK_CLKDIV		(*((T16BNCLK_REG *)(T16B_1_REG_BASE_ADDR + 0x00))).bit.CLKDIV		///< These bits select the division ratio of the T16B Ch.1 operating clock (counter clock).
#define	T16B1CLK_DBRUN		(*((T16BNCLK_REG *)(T16B_1_REG_BASE_ADDR + 0x00))).bit.DBRUN		///< This bit sets whether the T16B Ch.1 operating clock is supplied in DEBUG mode or not.

// T16B Ch.1 Counter Control Register.
#define	T16B1CTL			(*((T16BNCLK_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).reg
#define	T16B1CTL_MODEN		(*((T16BNCTL_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).bit.MODEN		///< This bit enables the T16B Ch.1 operations.
#define	T16B1CTL_PRESET		(*((T16BNCTL_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).bit.PRESET		///< This bit resets the counter.
#define	T16B1CTL_RUN		(*((T16BNCTL_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).bit.RUN			///< This bit starts/stops counting.
#define	T16B1CTL_ONEST		(*((T16BNCTL_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).bit.ONEST		///< This bit selects the counter repeat/one-shot mode.
#define	T16B1CTL_CNTMD		(*((T16BNCTL_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).bit.CNTMD		///< These bits select the counter up/down mode.
#define	T16B1CTL_MAXBSY		(*((T16BNCTL_REG *)(T16B_1_REG_BASE_ADDR + 0x02))).bit.MAXBSY		///< This bit indicates whether data can be written to the T16BnMC register or not.

// T16B Ch.1 Max Counter Data Register
#define	T16B1MC				(*((T16BNMC_REG *)(T16B_1_REG_BASE_ADDR + 0x04))).reg

// T16B Ch.1 Timer Counter Data Register.
#define	T16B1TC				(*((T16BNTC_REG *)(T16B_1_REG_BASE_ADDR + 0x06))).reg

// T16B Ch.1 Counter Status Register
#define	T16B1CS				(*((T16BNCS_REG *)(T16B_1_REG_BASE_ADDR + 0x08))).reg
#define	T16B1CS_BSY			(*((T16BNCS_REG *)(T16B_1_REG_BASE_ADDR + 0x08))).bit.BSY			///< This bit indicates the counter operating status.
#define	T16B1CS_UP_DOWN		(*((T16BNCS_REG *)(T16B_1_REG_BASE_ADDR + 0x08))).bit.UP_DOWN		///< This bit indicates the currently set count direction.
#define	T16B1CS_CAPI0		(*((T16BNCS_REG *)(T16B_1_REG_BASE_ADDR + 0x08))).bit.CAPI0			///< These bits indicate the signal level currently input to the CAPx0 pin.
#define	T16B1CS_CAPI1		(*((T16BNCS_REG *)(T16B_1_REG_BASE_ADDR + 0x08))).bit.CAPI1			///< These bits indicate the signal level currently input to the CAPx1 pin.

// T16B Ch.1 Interrupt Flag Register.
#define	T16B1INTF			(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).reg
#define	T16B1INTF_CNTZEROIF	(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).bit.CNTZEROIF	///< Counter zero interrupt
#define	T16B1INTF_CNTMAXIF	(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).bit.CNTMAXIF	///< Counter MAX interrupt
#define	T16B1INTF_CMPCAP0IF	(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).bit.CMPCAP0IF	///< Compare/capture 0 interrupt
#define	T16B1INTF_CAPOW0IF	(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).bit.CAPOW0IF	///< Capture 0 overwrite interrupt
#define	T16B1INTF_CMPCAP1IF	(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).bit.CMPCAP1IF	///< Compare/capture 1 interrupt
#define	T16B1INTF_CAPOW1IF	(*((T16BNINTF_REG *)(T16B_1_REG_BASE_ADDR + 0x0A))).bit.CAPOW1IF	///< Capture 1 overwrite interrupt

// T16B Ch.1 Interrupt Enable Register.
#define	T16B1INTE			(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).reg
#define	T16B1INTE_CNTZEROIE	(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).bit.CNTZEROIE	///< Counter zero interrupt
#define	T16B1INTE_CNTMAXIE	(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).bit.CNTMAXIE	///< Counter MAX interrupt
#define	T16B1INTE_CMPCAP0IE	(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).bit.CMPCAP0IE	///< Compare/capture 0 interrupt
#define	T16B1INTE_CAPOW0IE	(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).bit.CAPOW0IE	///< Capture 0 overwrite interrupt
#define	T16B1INTE_CMPCAP1IE	(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).bit.CMPCAP1IE	///< Compare/capture 1 interrupt
#define	T16B1INTE_CAPOW1IE	(*((T16BNINTE_REG *)(T16B_1_REG_BASE_ADDR + 0x0C))).bit.CAPOW1IE	///< Capture 1 overwrite interrupt

// T16B Ch.1 Comparator/Capture 0 Control Register.
#define	T16B1CCCTL0			(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).reg
#define	T16B1CCCTL0_CCMD	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.CCMD		///< This bit selects the operating mode of the comparator/capture circuit m.
#define	T16B1CCCTL0_TOUTINV	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.TOUTINV	///< This bit selects the TOUT10 signal polarity.
#define	T16B1CCCTL0_TOUTMD	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.TOUTMD	///< These bits configure how the TOUT10 signal waveform is changed.
#define	T16B1CCCTL0_TOUTO	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.TOUTO		///< This bit sets the TOUT10 signal output level
#define	T16B1CCCTL0_TOUTMT	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.TOUTMT	///< This bit selects whether the comparator equal signal.
#define	T16B1CCCTL0_CAPTRG	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.CAPTRG	///< These bits select the trigger edge(s) of the trigger signal.
#define	T16B1CCCTL0_CAPIS	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.CAPIS		///< These bits select the trigger signal for capturing.
#define	T16B1CCCTL0_CBUFMD	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.CBUFMD	///< These bits select the timing to load the comparison value written.
#define	T16B1CCCTL0_SCS		(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x10))).bit.SCS		///< This bit selects either synchronous capture mode or asynchronous capture mode.

// T16B Ch.1 Compare/Capture 0 Data Register.
#define	T16B1CCR0			(*((T16BNCCRM_REG *)(T16B_1_REG_BASE_ADDR + 0x12))).reg

// T16B Ch.1 Comparator/Capture 1 Control Register.
#define	T16B1CCCTL1			(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).reg
#define	T16B1CCCTL1_CCMD	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.CCMD		///< This bit selects the operating mode of the comparator/capture circuit m.
#define	T16B1CCCTL1_TOUTINV	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.TOUTINV	///< This bit selects the TOUT11 signal polarity.
#define	T16B1CCCTL1_TOUTMD	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.TOUTMD	///< These bits configure how the TOUT11 signal waveform is changed.
#define	T16B1CCCTL1_TOUTO	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.TOUTO		///< This bit sets the TOUT11 signal output level
#define	T16B1CCCTL1_TOUTMT	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.TOUTMT	///< This bit selects whether the comparator equal signal.
#define	T16B1CCCTL1_CAPTRG	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.CAPTRG	///< These bits select the trigger edge(s) of the trigger signal.
#define	T16B1CCCTL1_CAPIS	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.CAPIS		///< These bits select the trigger signal for capturing.
#define	T16B1CCCTL1_CBUFMD	(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.CBUFMD	///< These bits select the timing to load the comparison value written.
#define	T16B1CCCTL1_SCS		(*((T16BNCCCTLM_REG *)(T16B_1_REG_BASE_ADDR + 0x18))).bit.SCS		///< This bit selects either synchronous capture mode or asynchronous capture mode.

// T16B Ch.1 Compare/Capture 1 Data Register.
#define	T16B1CCR1			(*((T16BNCCRM_REG *)(T16B_1_REG_BASE_ADDR + 0x1A))).reg


/*********************/
/* ----- SNDA ------ */
/*********************/

// SNDA Clock Control Register
#define	SNDCLK				(*((SNDCLK_REG *)(SNDA_REG_BASE_ADDR + 0x00))).reg
#define	SNDCLK_CLKSRC		(*((SNDCLK_REG *)(SNDA_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of SNDA.
#define	SNDCLK_CLKDIV		(*((SNDCLK_REG *)(SNDA_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the SNDA operating clock.
#define	SNDCLK_DBRUN		(*((SNDCLK_REG *)(SNDA_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the SNDA operating clock is supplied in DEBUG mode or not.

// SNDA Select Register
#define	SNDSEL				(*((SNDSEL_REG *)(SNDA_REG_BASE_ADDR + 0x02))).reg
#define	SNDSEL_MOSEL		(*((SNDSEL_REG *)(SNDA_REG_BASE_ADDR + 0x02))).bit.MOSEL			///< These bits select a sound output mode.
#define	SNDSEL_SINV			(*((SNDSEL_REG *)(SNDA_REG_BASE_ADDR + 0x02))).bit.SINV				///< This bit selects an output pin drive mode.
#define	SNDSEL_STIM			(*((SNDSEL_REG *)(SNDA_REG_BASE_ADDR + 0x02))).bit.STIM				///< These bits select a tempo or a one-shot buzzer output duration.

// SNDA Control Register
#define	SNDCTL				(*((SNDCTL_REG *)(SNDA_REG_BASE_ADDR + 0x04))).reg
#define	SNDCTL_MODEN		(*((SNDCTL_REG *)(SNDA_REG_BASE_ADDR + 0x04))).bit.MODEN			///< This bit enables the SNDA operations.
#define	SNDCTL_SSTP			(*((SNDCTL_REG *)(SNDA_REG_BASE_ADDR + 0x04))).bit.SSTP				///< This bit stops sound output.

// SNDA Data Register
#define	SNDDAT				(*((SNDDAT_REG *)(SNDA_REG_BASE_ADDR + 0x06))).reg
#define	SNDDAT_SFRQ			(*((SNDDAT_REG *)(SNDA_REG_BASE_ADDR + 0x06))).bit.SFRQ				///< These bits select a scale or a buzzer signal frequency.
#define	SNDDAT_SLEN			(*((SNDDAT_REG *)(SNDA_REG_BASE_ADDR + 0x06))).bit.SLEN				///< These bits select a duration or a buzzer signal duty ratio.
#define	SNDDAT_MDRS			(*((SNDDAT_REG *)(SNDA_REG_BASE_ADDR + 0x06))).bit.MDRS				///< This bit selects the output type in melody mode from a note or a rest.
#define	SNDDAT_MDTI			(*((SNDDAT_REG *)(SNDA_REG_BASE_ADDR + 0x06))).bit.MDTI				///< This bit specifies a tie in melody mode.

// SNDA Interrupt Flag Register
#define	SNDINTF				(*((SNDINTF_REG *)(SNDA_REG_BASE_ADDR + 0x08))).reg
#define	SNDINTF_EDIF		(*((SNDINTF_REG *)(SNDA_REG_BASE_ADDR + 0x08))).bit.EDIF			///< Sound buffer empty interrupt status.
#define	SNDINTF_EMIF		(*((SNDINTF_REG *)(SNDA_REG_BASE_ADDR + 0x08))).bit.EMIF			///< Sound output completion interrupt status.
#define	SNDINTF_SBSY		(*((SNDINTF_REG *)(SNDA_REG_BASE_ADDR + 0x08))).bit.SBSY			///< This bit indicates the sound output status.

// SNDA Interrupt Enable Register
#define	SNDINTE				(*((SNDINTE_REG *)(SNDA_REG_BASE_ADDR + 0x0A))).reg
#define	SNDINTE_EDIE		(*((SNDINTE_REG *)(SNDA_REG_BASE_ADDR + 0x0A))).bit.EDIE			///< Sound output completion interrupt.
#define	SNDINTE_EMIE		(*((SNDINTE_REG *)(SNDA_REG_BASE_ADDR + 0x0A))).bit.EMIE			///< Sound buffer empty interrupt.


/*********************/
/* ----- LCD8B ---- */
/*********************/

// LCD8B Clock Control Register
#define	LCD8CLK			(*((LCD8CLK_REG *)(LCD8B_REG_BASE_ADDR + 0x00))).reg
#define	LCD8CLK_CLKSRC		(*((LCD8CLK_REG *)(LCD8B_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the LCD8B.
#define	LCD8CLK_CLKDIV		(*((LCD8CLK_REG *)(LCD8B_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the LCD8B operating clock.
#define	LCD8CLK_DBRUN		(*((LCD8CLK_REG *)(LCD8B_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the LCD8B operating clock is supplied in DEBUG mode or not.

// LCD8B Control Register
#define	LCD8CTL			(*((LCD8CTL_REG *)(LCD8B_REG_BASE_ADDR + 0x02))).reg
#define	LCD8CTL_MODEN		(*((LCD8CTL_REG *)(LCD8B_REG_BASE_ADDR + 0x02))).bit.MODEN			///< This bit enables the LCD8B operations.

// LCD8B Timing Control Register 1
#define	LCD8TIM1			(*((LCD8TIM1_REG *)(LCD8B_REG_BASE_ADDR + 0x04))).reg
#define	LCD8TIM1_LDUTY		(*((LCD8TIM1_REG *)(LCD8B_REG_BASE_ADDR + 0x04))).bit.LDUTY			///< These bits set the drive duty.
#define	LCD8TIM1_FRMCNT	(*((LCD8TIM1_REG *)(LCD8B_REG_BASE_ADDR + 0x04))).bit.FRMCNT			///< These bits set the frame frequency.

// LCD8B Timing Control Register 2
#define	LCD8TIM2			(*((LCD8TIM2_REG *)(LCD8B_REG_BASE_ADDR + 0x06))).reg
#define	LCD8TIM2_NLINE		(*((LCD8TIM2_REG *)(LCD8B_REG_BASE_ADDR + 0x06))).bit.NLINE			///< These bits enable the n-line inverse AC drive function and set the number of inverse lines.
#define	LCD8TIM2_BSTC		(*((LCD8TIM2_REG *)(LCD8B_REG_BASE_ADDR + 0x06))).bit.BSTC			///< These bits select the booster clock frequency for the LCD voltage booster.

// LCD8B Power Control Register
#define	LCD8PWR			(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).reg
#define	LCD8PWR_VCEN		(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).bit.VCEN				///< This bit turns the LCD voltage regulator on and off.
#define	LCD8PWR_VCSEL		(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).bit.VCSEL			///< This bit sets the LCD voltage regulator output (reference voltage for boosting).
#define	LCD8PWR_HVLD		(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).bit.HVLD				///< This bit sets the LCD voltage regulator into heavy load protection mode.
#define	LCD8PWR_BISEL		(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).bit.BISEL			///< This bit selects the LCD drive bias.
#define	LCD8PWR_BSTEN		(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).bit.BSTEN			///< This bit turns the LCD voltage booster on and off.
#define	LCD8PWR_LC			(*((LCD8PWR_REG *)(LCD8B_REG_BASE_ADDR + 0x08))).bit.LC				///< These bits set the LCD panel contrast.

// LCD8B Display Control Register
#define	LCD8DSP			(*((LCD8DSP_REG *)(LCD8B_REG_BASE_ADDR + 0x0A))).reg
#define	LCD8DSP_DSPC		(*((LCD8DSP_REG *)(LCD8B_REG_BASE_ADDR + 0x0A))).bit.DSPC				///< These bits control the LCD display on/off and select a display mode.
#define	LCD8DSP_DSPAR		(*((LCD8DSP_REG *)(LCD8B_REG_BASE_ADDR + 0x0A))).bit.DSPAR			///< This bit switches the display area in the display data RAM.
#define	LCD8DSP_DSPREV		(*((LCD8DSP_REG *)(LCD8B_REG_BASE_ADDR + 0x0A))).bit.DSPREV			///< This bit controls black/white inversion on the LCD display.
#define	LCD8DSP_COMREV		(*((LCD8DSP_REG *)(LCD8B_REG_BASE_ADDR + 0x0A))).bit.COMREV			///< This bit selects the common pin assignment direction.
#define	LCD8DSP_SEGREV		(*((LCD8DSP_REG *)(LCD8B_REG_BASE_ADDR + 0x0A))).bit.SEGREV			///< This bit selects the segment pin assignment direction.

/// LCD8B COM Pin Control Register 0
#define	LCD8COMC0			(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).reg
#define	LCD8COMC0_COM0DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN0			///< These bits configure the partial drive of the COM0 pin.
#define	LCD8COMC0_COM1DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN1			///< These bits configure the partial drive of the COM1 pin.
#define	LCD8COMC0_COM2DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN2			///< These bits configure the partial drive of the COM2 pin.
#define	LCD8COMC0_COM3DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN3			///< These bits configure the partial drive of the COM3 pin.
#define	LCD8COMC0_COM4DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN4			///< These bits configure the partial drive of the COM4 pin.
#define	LCD8COMC0_COM5DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN5			///< These bits configure the partial drive of the COM5 pin.
#define	LCD8COMC0_COM6DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN6			///< These bits configure the partial drive of the COM6 pin.
#define	LCD8COMC0_COM7DEN	(*((LCD8COMCX_REG *)(LCD8B_REG_BASE_ADDR + 0x0C))).bit.PIN7			///< These bits configure the partial drive of the COM7 pin.

// LCD8B Interrupt Flag Register
#define	LCD8INTF			(*((LCD8INTF_REG *)(LCD8B_REG_BASE_ADDR + 0x10))).reg
#define	LCD8INTF_FRMIF		(*((LCD8INTF_REG *)(LCD8B_REG_BASE_ADDR + 0x10))).bit.FRMIF			///< This bit indicates the frame interrupt cause occurrence status.

// LCD8B Interrupt Enable Register
#define	LCD8INTE			(*((LCD8INTE_REG *)(LCD8B_REG_BASE_ADDR + 0x12))).reg
#define	LCD8INTE_FRMIE		(*((LCD8INTE_REG *)(LCD8B_REG_BASE_ADDR + 0x12))).bit.FRMIE			///< This bit enables the frame interrupt.


/*******************/
/* ----- RFC ----- */
/*******************/

// RFC Ch.0 Clock Control Register
#define	RFC0CLK				(*((RFCNCLK_REG *)(RFC_0_REG_BASE_ADDR + 0x00))).reg
#define	RFC0CLK_CLKSRC		(*((RFCNCLK_REG *)(RFC_0_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the RFC.
#define	RFC0CLK_CLKDIV		(*((RFCNCLK_REG *)(RFC_0_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the RFC operating clock.
#define	RFC0CLK_DBRUN		(*((RFCNCLK_REG *)(RFC_0_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the RFC operating clock is supplied in DEBUG mode or not.

// RFC Ch.0 Control Register
#define	RFC0CTL				(*((RFCNCTL_REG *)(RFC_0_REG_BASE_ADDR + 0x02))).reg
#define	RFC0CTL_MODEN		(*((RFCNCTL_REG *)(RFC_0_REG_BASE_ADDR + 0x02))).bit.MODEN			///< This bit enables the RFC operations.
#define	RFC0CTL_SMODE		(*((RFCNCTL_REG *)(RFC_0_REG_BASE_ADDR + 0x02))).bit.SMODE			///< These bits configure the oscillation mode.
#define	RFC0CTL_EVTEN		(*((RFCNCTL_REG *)(RFC_0_REG_BASE_ADDR + 0x02))).bit.EVTEN			///< This bit enables external clock input mode (event counter mode).

// RFC Ch.0 Oscillation Trigger Register
#define	RFC0TRG				(*((RFCNTRG_REG *)(RFC_0_REG_BASE_ADDR + 0x04))).reg
#define	RFC0TRG_SREF		(*((RFCNTRG_REG *)(RFC_0_REG_BASE_ADDR + 0x04))).bit.SREF			///< This bit controls CR oscillation for the reference resistor.
#define	RFC0TRG_SSENA		(*((RFCNTRG_REG *)(RFC_0_REG_BASE_ADDR + 0x04))).bit.SSENA			///< This bit controls CR oscillation for sensor A.
#define	RFC0TRG_SSENB		(*((RFCNTRG_REG *)(RFC_0_REG_BASE_ADDR + 0x04))).bit.SSENB			///< This bit controls CR oscillation for sensor B.

// RFC Ch.0 Measurement Counter Low Register
#define	RFC0MCL				(*((RFCNMCL_REG *)(RFC_0_REG_BASE_ADDR + 0x06))).reg

// RFC Ch.0 Measurement Counter High Register
#define	RFC0MCH				(*((RFCNMCH_REG *)(RFC_0_REG_BASE_ADDR + 0x08))).reg
#define	RFC0MCH_MC			(*((RFCNMCH_REG *)(RFC_0_REG_BASE_ADDR + 0x08))).bit.MC				///< Measurement counter data can be read and written through these bits.

// RFC Ch.0 Time Base Counter Low Register
#define	RFC0TCL				(*((RFCNTCL_REG *)(RFC_0_REG_BASE_ADDR + 0x0A))).reg

// RFC Ch.0 Time Base Counter High Register
#define	RFC0TCH				(*((RFCNTCH_REG *)(RFC_0_REG_BASE_ADDR + 0x0C))).reg
#define	RFC0TCH_TC			(*((RFCNTCH_REG *)(RFC_0_REG_BASE_ADDR + 0x0C))).bit.TC				///< Time base counter data can be read and written through these bits.

// RFC Ch.0 Interrupt Flag Register
#define	RFC0INTF			(*((RFCNINTF_REG *)(RFC_0_REG_BASE_ADDR + 0x0E))).reg
#define	RFC0INTF_EREFIF		(*((RFCNINTF_REG *)(RFC_0_REG_BASE_ADDR + 0x0E))).bit.EREFIF		///< This bit indicate Reference oscillation completion interrupt cause occurrence status.
#define	RFC0INTF_ESENAIF	(*((RFCNINTF_REG *)(RFC_0_REG_BASE_ADDR + 0x0E))).bit.ESENAIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC0INTF_ESENBIF	(*((RFCNINTF_REG *)(RFC_0_REG_BASE_ADDR + 0x0E))).bit.ESENBIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC0INTF_OVMCIF		(*((RFCNINTF_REG *)(RFC_0_REG_BASE_ADDR + 0x0E))).bit.OVMCIF		///< This bit indicate Measurement counter overflow error interrupt cause occurrence status.
#define	RFC0INTF_OVTCIF		(*((RFCNINTF_REG *)(RFC_0_REG_BASE_ADDR + 0x0E))).bit.OVTCIF		///< This bit indicate Time base counter overflow error interrupt cause occurrence status.

// RFC Ch.0 Interrupt Enable Register
#define	RFC0INTE			(*((RFCNINTE_REG *)(RFC_0_REG_BASE_ADDR + 0x10))).reg
#define	RFC0INTE_EREFIE		(*((RFCNINTE_REG *)(RFC_0_REG_BASE_ADDR + 0x10))).bit.EREFIE		///< This bit enable Reference oscillation completion interrupt.
#define	RFC0INTE_ESENAIE	(*((RFCNINTE_REG *)(RFC_0_REG_BASE_ADDR + 0x10))).bit.ESENAIE		///< This bit enable Sensor A oscillation completion interrupt.
#define	RFC0INTE_ESENBIE	(*((RFCNINTE_REG *)(RFC_0_REG_BASE_ADDR + 0x10))).bit.ESENBIE		///< This bit enable Sensor B oscillation completion interrupt.
#define	RFC0INTE_OVMCIE		(*((RFCNINTE_REG *)(RFC_0_REG_BASE_ADDR + 0x10))).bit.OVMCIE		///< This bit enable Measurement counter overflow error interrupt.
#define	RFC0INTE_OVTCIE		(*((RFCNINTE_REG *)(RFC_0_REG_BASE_ADDR + 0x10))).bit.OVTCIE		///< This bit enable Time base counter overflow error interrupt.

// RFC Ch.1 Clock Control Register
#define	RFC1CLK				(*((RFCNCLK_REG *)(RFC_1_REG_BASE_ADDR + 0x00))).reg
#define	RFC1CLK_CLKSRC		(*((RFCNCLK_REG *)(RFC_1_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the RFC.
#define	RFC1CLK_CLKDIV		(*((RFCNCLK_REG *)(RFC_1_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the RFC operating clock.
#define	RFC1CLK_DBRUN		(*((RFCNCLK_REG *)(RFC_1_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the RFC operating clock is supplied in DEBUG mode or not.

// RFC Ch.1 Control Register
#define	RFC1CTL				(*((RFCNCTL_REG *)(RFC_1_REG_BASE_ADDR + 0x02))).reg
#define	RFC1CTL_MODEN		(*((RFCNCTL_REG *)(RFC_1_REG_BASE_ADDR + 0x02))).bit.MODEN			///< This bit enables the RFC operations.
#define	RFC1CTL_SMODE		(*((RFCNCTL_REG *)(RFC_1_REG_BASE_ADDR + 0x02))).bit.SMODE			///< These bits configure the oscillation mode.
#define	RFC1CTL_EVTEN		(*((RFCNCTL_REG *)(RFC_1_REG_BASE_ADDR + 0x02))).bit.EVTEN			///< This bit enables external clock input mode (event counter mode).

// RFC Ch.1 Oscillation Trigger Register
#define	RFC1TRG				(*((RFCNTRG_REG *)(RFC_1_REG_BASE_ADDR + 0x04))).reg
#define	RFC1TRG_SREF		(*((RFCNTRG_REG *)(RFC_1_REG_BASE_ADDR + 0x04))).bit.SREF			///< This bit controls CR oscillation for the reference resistor.
#define	RFC1TRG_SSENA		(*((RFCNTRG_REG *)(RFC_1_REG_BASE_ADDR + 0x04))).bit.SSENA			///< This bit controls CR oscillation for sensor A.
#define	RFC1TRG_SSENB		(*((RFCNTRG_REG *)(RFC_1_REG_BASE_ADDR + 0x04))).bit.SSENB			///< This bit controls CR oscillation for sensor B.

// RFC Ch.1 Measurement Counter Low Register
#define	RFC1MCL				(*((RFCNMCL_REG *)(RFC_1_REG_BASE_ADDR + 0x06))).reg

// RFC Ch.1 Measurement Counter High Register
#define	RFC1MCH				(*((RFCNMCH_REG *)(RFC_1_REG_BASE_ADDR + 0x08))).reg
#define	RFC1MCH_MC			(*((RFCNMCH_REG *)(RFC_1_REG_BASE_ADDR + 0x08))).bit.MC				///< Measurement counter data can be read and written through these bits.

// RFC Ch.1 Time Base Counter Low Register
#define	RFC1TCL				(*((RFCNTCL_REG *)(RFC_1_REG_BASE_ADDR + 0x0A))).reg

// RFC Ch.1 Time Base Counter High Register
#define	RFC1TCH				(*((RFCNTCH_REG *)(RFC_1_REG_BASE_ADDR + 0x0C))).reg
#define	RFC1TCH_TC			(*((RFCNTCH_REG *)(RFC_1_REG_BASE_ADDR + 0x0C))).bit.TC				///< Time base counter data can be read and written through these bits.

// RFC Ch.1 Interrupt Flag Register
#define	RFC1INTF			(*((RFCNINTF_REG *)(RFC_1_REG_BASE_ADDR + 0x0E))).reg
#define	RFC1INTF_EREFIF		(*((RFCNINTF_REG *)(RFC_1_REG_BASE_ADDR + 0x0E))).bit.EREFIF		///< This bit indicate Reference oscillation completion interrupt cause occurrence status.
#define	RFC1INTF_ESENAIF	(*((RFCNINTF_REG *)(RFC_1_REG_BASE_ADDR + 0x0E))).bit.ESENAIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC1INTF_ESENBIF	(*((RFCNINTF_REG *)(RFC_1_REG_BASE_ADDR + 0x0E))).bit.ESENBIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC1INTF_OVMCIF		(*((RFCNINTF_REG *)(RFC_1_REG_BASE_ADDR + 0x0E))).bit.OVMCIF		///< This bit indicate Measurement counter overflow error interrupt cause occurrence status.
#define	RFC1INTF_OVTCIF		(*((RFCNINTF_REG *)(RFC_1_REG_BASE_ADDR + 0x0E))).bit.OVTCIF		///< This bit indicate Time base counter overflow error interrupt cause occurrence status.

// RFC Ch.1 Interrupt Enable Register
#define	RFC1INTE			(*((RFCNINTE_REG *)(RFC_1_REG_BASE_ADDR + 0x10))).reg
#define	RFC1INTE_EREFIE		(*((RFCNINTE_REG *)(RFC_1_REG_BASE_ADDR + 0x10))).bit.EREFIE		///< This bit enable Reference oscillation completion interrupt.
#define	RFC1INTE_ESENAIE	(*((RFCNINTE_REG *)(RFC_1_REG_BASE_ADDR + 0x10))).bit.ESENAIE		///< This bit enable Sensor A oscillation completion interrupt.
#define	RFC1INTE_ESENBIE	(*((RFCNINTE_REG *)(RFC_1_REG_BASE_ADDR + 0x10))).bit.ESENBIE		///< This bit enable Sensor B oscillation completion interrupt.
#define	RFC1INTE_OVMCIE		(*((RFCNINTE_REG *)(RFC_1_REG_BASE_ADDR + 0x10))).bit.OVMCIE		///< This bit enable Measurement counter overflow error interrupt.
#define	RFC1INTE_OVTCIE		(*((RFCNINTE_REG *)(RFC_1_REG_BASE_ADDR + 0x10))).bit.OVTCIE		///< This bit enable Time base counter overflow error interrupt.

// RFC Ch.2 Clock Control Register
#define	RFC2CLK				(*((RFCNCLK_REG *)(RFC_2_REG_BASE_ADDR + 0x00))).reg
#define	RFC2CLK_CLKSRC		(*((RFCNCLK_REG *)(RFC_2_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the RFC.
#define	RFC2CLK_CLKDIV		(*((RFCNCLK_REG *)(RFC_2_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the RFC operating clock.
#define	RFC2CLK_DBRUN		(*((RFCNCLK_REG *)(RFC_2_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the RFC operating clock is supplied in DEBUG mode or not.

// RFC Ch.2 Control Register
#define	RFC2CTL				(*((RFCNCTL_REG *)(RFC_2_REG_BASE_ADDR + 0x02))).reg
#define	RFC2CTL_MODEN		(*((RFCNCTL_REG *)(RFC_2_REG_BASE_ADDR + 0x02))).bit.MODEN			///< This bit enables the RFC operations.
#define	RFC2CTL_SMODE		(*((RFCNCTL_REG *)(RFC_2_REG_BASE_ADDR + 0x02))).bit.SMODE			///< These bits configure the oscillation mode.
#define	RFC2CTL_EVTEN		(*((RFCNCTL_REG *)(RFC_2_REG_BASE_ADDR + 0x02))).bit.EVTEN			///< This bit enables external clock input mode (event counter mode).

// RFC Ch.2 Oscillation Trigger Register
#define	RFC2TRG				(*((RFCNTRG_REG *)(RFC_2_REG_BASE_ADDR + 0x04))).reg
#define	RFC2TRG_SREF		(*((RFCNTRG_REG *)(RFC_2_REG_BASE_ADDR + 0x04))).bit.SREF			///< This bit controls CR oscillation for the reference resistor.
#define	RFC2TRG_SSENA		(*((RFCNTRG_REG *)(RFC_2_REG_BASE_ADDR + 0x04))).bit.SSENA			///< This bit controls CR oscillation for sensor A.
#define	RFC2TRG_SSENB		(*((RFCNTRG_REG *)(RFC_2_REG_BASE_ADDR + 0x04))).bit.SSENB			///< This bit controls CR oscillation for sensor B.

// RFC Ch.2 Measurement Counter Low Register
#define	RFC2MCL				(*((RFCNMCL_REG *)(RFC_2_REG_BASE_ADDR + 0x06))).reg

// RFC Ch.2 Measurement Counter High Register
#define	RFC2MCH				(*((RFCNMCH_REG *)(RFC_2_REG_BASE_ADDR + 0x08))).reg
#define	RFC2MCH_MC			(*((RFCNMCH_REG *)(RFC_2_REG_BASE_ADDR + 0x08))).bit.MC				///< Measurement counter data can be read and written through these bits.

// RFC Ch.2 Time Base Counter Low Register
#define	RFC2TCL				(*((RFCNTCL_REG *)(RFC_2_REG_BASE_ADDR + 0x0A))).reg

// RFC Ch.2 Time Base Counter High Register
#define	RFC2TCH				(*((RFCNTCH_REG *)(RFC_2_REG_BASE_ADDR + 0x0C))).reg
#define	RFC2TCH_TC			(*((RFCNTCH_REG *)(RFC_2_REG_BASE_ADDR + 0x0C))).bit.TC				///< Time base counter data can be read and written through these bits.

// RFC Ch.2 Interrupt Flag Register
#define	RFC2INTF			(*((RFCNINTF_REG *)(RFC_2_REG_BASE_ADDR + 0x0E))).reg
#define	RFC2INTF_EREFIF		(*((RFCNINTF_REG *)(RFC_2_REG_BASE_ADDR + 0x0E))).bit.EREFIF		///< This bit indicate Reference oscillation completion interrupt cause occurrence status.
#define	RFC2INTF_ESENAIF	(*((RFCNINTF_REG *)(RFC_2_REG_BASE_ADDR + 0x0E))).bit.ESENAIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC2INTF_ESENBIF	(*((RFCNINTF_REG *)(RFC_2_REG_BASE_ADDR + 0x0E))).bit.ESENBIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC2INTF_OVMCIF		(*((RFCNINTF_REG *)(RFC_2_REG_BASE_ADDR + 0x0E))).bit.OVMCIF		///< This bit indicate Measurement counter overflow error interrupt cause occurrence status.
#define	RFC2INTF_OVTCIF		(*((RFCNINTF_REG *)(RFC_2_REG_BASE_ADDR + 0x0E))).bit.OVTCIF		///< This bit indicate Time base counter overflow error interrupt cause occurrence status.

// RFC Ch.2 Interrupt Enable Register
#define	RFC2INTE			(*((RFCNINTE_REG *)(RFC_2_REG_BASE_ADDR + 0x10))).reg
#define	RFC2INTE_EREFIE		(*((RFCNINTE_REG *)(RFC_2_REG_BASE_ADDR + 0x10))).bit.EREFIE		///< This bit enable Reference oscillation completion interrupt.
#define	RFC2INTE_ESENAIE	(*((RFCNINTE_REG *)(RFC_2_REG_BASE_ADDR + 0x10))).bit.ESENAIE		///< This bit enable Sensor A oscillation completion interrupt.
#define	RFC2INTE_ESENBIE	(*((RFCNINTE_REG *)(RFC_2_REG_BASE_ADDR + 0x10))).bit.ESENBIE		///< This bit enable Sensor B oscillation completion interrupt.
#define	RFC2INTE_OVMCIE		(*((RFCNINTE_REG *)(RFC_2_REG_BASE_ADDR + 0x10))).bit.OVMCIE		///< This bit enable Measurement counter overflow error interrupt.
#define	RFC2INTE_OVTCIE		(*((RFCNINTE_REG *)(RFC_2_REG_BASE_ADDR + 0x10))).bit.OVTCIE		///< This bit enable Time base counter overflow error interrupt.

// RFC Ch.3 Clock Control Register
#define	RFC3CLK				(*((RFCNCLK_REG *)(RFC_3_REG_BASE_ADDR + 0x00))).reg
#define	RFC3CLK_CLKSRC		(*((RFCNCLK_REG *)(RFC_3_REG_BASE_ADDR + 0x00))).bit.CLKSRC			///< These bits select the clock source of the RFC.
#define	RFC3CLK_CLKDIV		(*((RFCNCLK_REG *)(RFC_3_REG_BASE_ADDR + 0x00))).bit.CLKDIV			///< These bits select the division ratio of the RFC operating clock.
#define	RFC3CLK_DBRUN		(*((RFCNCLK_REG *)(RFC_3_REG_BASE_ADDR + 0x00))).bit.DBRUN			///< This bit sets whether the RFC operating clock is supplied in DEBUG mode or not.

// RFC Ch.3 Control Register
#define	RFC3CTL				(*((RFCNCTL_REG *)(RFC_3_REG_BASE_ADDR + 0x02))).reg
#define	RFC3CTL_MODEN		(*((RFCNCTL_REG *)(RFC_3_REG_BASE_ADDR + 0x02))).bit.MODEN			///< This bit enables the RFC operations.
#define	RFC3CTL_SMODE		(*((RFCNCTL_REG *)(RFC_3_REG_BASE_ADDR + 0x02))).bit.SMODE			///< These bits configure the oscillation mode.
#define	RFC3CTL_EVTEN		(*((RFCNCTL_REG *)(RFC_3_REG_BASE_ADDR + 0x02))).bit.EVTEN			///< This bit enables external clock input mode (event counter mode).

// RFC Ch.3 Oscillation Trigger Register
#define	RFC3TRG				(*((RFCNTRG_REG *)(RFC_3_REG_BASE_ADDR + 0x04))).reg
#define	RFC3TRG_SREF		(*((RFCNTRG_REG *)(RFC_3_REG_BASE_ADDR + 0x04))).bit.SREF			///< This bit controls CR oscillation for the reference resistor.
#define	RFC3TRG_SSENA		(*((RFCNTRG_REG *)(RFC_3_REG_BASE_ADDR + 0x04))).bit.SSENA			///< This bit controls CR oscillation for sensor A.
#define	RFC3TRG_SSENB		(*((RFCNTRG_REG *)(RFC_3_REG_BASE_ADDR + 0x04))).bit.SSENB			///< This bit controls CR oscillation for sensor B.

// RFC Ch.3 Measurement Counter Low Register
#define	RFC3MCL				(*((RFCNMCL_REG *)(RFC_3_REG_BASE_ADDR + 0x06))).reg

// RFC Ch.3 Measurement Counter High Register
#define	RFC3MCH				(*((RFCNMCH_REG *)(RFC_3_REG_BASE_ADDR + 0x08))).reg
#define	RFC3MCH_MC			(*((RFCNMCH_REG *)(RFC_3_REG_BASE_ADDR + 0x08))).bit.MC				///< Measurement counter data can be read and written through these bits.

// RFC Ch.3 Time Base Counter Low Register
#define	RFC3TCL				(*((RFCNTCL_REG *)(RFC_3_REG_BASE_ADDR + 0x0A))).reg

// RFC Ch.3 Time Base Counter High Register
#define	RFC3TCH				(*((RFCNTCH_REG *)(RFC_3_REG_BASE_ADDR + 0x0C))).reg
#define	RFC3TCH_TC			(*((RFCNTCH_REG *)(RFC_3_REG_BASE_ADDR + 0x0C))).bit.TC				///< Time base counter data can be read and written through these bits.

// RFC Ch.3 Interrupt Flag Register
#define	RFC3INTF			(*((RFCNINTF_REG *)(RFC_3_REG_BASE_ADDR + 0x0E))).reg
#define	RFC3INTF_EREFIF		(*((RFCNINTF_REG *)(RFC_3_REG_BASE_ADDR + 0x0E))).bit.EREFIF		///< This bit indicate Reference oscillation completion interrupt cause occurrence status.
#define	RFC3INTF_ESENAIF	(*((RFCNINTF_REG *)(RFC_3_REG_BASE_ADDR + 0x0E))).bit.ESENAIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC3INTF_ESENBIF	(*((RFCNINTF_REG *)(RFC_3_REG_BASE_ADDR + 0x0E))).bit.ESENBIF		///< This bit indicate Sensor B oscillation completion interrupt cause occurrence status.
#define	RFC3INTF_OVMCIF		(*((RFCNINTF_REG *)(RFC_3_REG_BASE_ADDR + 0x0E))).bit.OVMCIF		///< This bit indicate Measurement counter overflow error interrupt cause occurrence status.
#define	RFC3INTF_OVTCIF		(*((RFCNINTF_REG *)(RFC_3_REG_BASE_ADDR + 0x0E))).bit.OVTCIF		///< This bit indicate Time base counter overflow error interrupt cause occurrence status.

// RFC Ch.3 Interrupt Enable Register
#define	RFC3INTE			(*((RFCNINTE_REG *)(RFC_3_REG_BASE_ADDR + 0x10))).reg
#define	RFC3INTE_EREFIE		(*((RFCNINTE_REG *)(RFC_3_REG_BASE_ADDR + 0x10))).bit.EREFIE		///< This bit enable Reference oscillation completion interrupt.
#define	RFC3INTE_ESENAIE	(*((RFCNINTE_REG *)(RFC_3_REG_BASE_ADDR + 0x10))).bit.ESENAIE		///< This bit enable Sensor A oscillation completion interrupt.
#define	RFC3INTE_ESENBIE	(*((RFCNINTE_REG *)(RFC_3_REG_BASE_ADDR + 0x10))).bit.ESENBIE		///< This bit enable Sensor B oscillation completion interrupt.
#define	RFC3INTE_OVMCIE		(*((RFCNINTE_REG *)(RFC_3_REG_BASE_ADDR + 0x10))).bit.OVMCIE		///< This bit enable Measurement counter overflow error interrupt.
#define	RFC3INTE_OVTCIE		(*((RFCNINTE_REG *)(RFC_3_REG_BASE_ADDR + 0x10))).bit.OVTCIE		///< This bit enable Time base counter overflow error interrupt.


#ifdef __cplusplus
}
#endif

#endif	// C17W15_REG_H__
