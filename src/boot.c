/********************
 * boot() est la premiere fonction appelee apres un reset.
 * C'est là qu'on désigne les fonctions d'interruptions et qu'on appelle le main()
 * ******************/

#include "boot.h"
#include <string.h>
#include <stdio.h>
#include <libstdio.h>
#include <stdlib.h>
#include "init.h"
#include "globalVar.h"
#include "interruptBoutons.h"
#include "interruptTime.h"
#include "uart.h"
#include "t16_ch0_smallDelays.h"
#include "t16_ch1_countdown.h"
#include "t16_ch2_appuiLongBouton.h"
#include "t16b_ch0_doubleAppui.h"
#include "t16b_ch1_verySmallDelays.h"

static void initPwg(void);
static void initItc(void);
static void clearBss(void);
static void loadLmaToVmaData(void);
static void end(void);

// Non Maskable Interrupt Handler
void intAddrErr(void)		__attribute__ ((interrupt_handler));
void intNmi(void)			__attribute__ ((interrupt_handler));
void intReserved(void)		__attribute__ ((interrupt_handler));

/* --- external declaration --- */

extern int main(void);

extern unsigned long __START_bss;
extern unsigned long __END_bss;
extern unsigned long __START_data;
extern unsigned long __START_data_lma;
//extern unsigned long __END_data;  --> have been put in boot.h to see it from outside boot.c
extern unsigned long __START_simio;
extern unsigned long __START_simio_lma;
extern unsigned long __END_simio;
extern unsigned long __START_stack;
//extern unsigned long __END_stack;

/* special definitions for vector table  */
typedef void func(void);
#ifdef __POINTER16
#define VECTOR(vec)  ( vec,0 )
#else
#define VECTOR(vec)  ( vec )
#endif

// La table d'interruptions
func *const vector[] = {			// No	Base+	Name

	/* ----- Non-Maskable Interrupts ----- */
	VECTOR( boot ),					// 0	00		Reset
	VECTOR( intAddrErr ),			// 1	04		Address misaligned
	VECTOR( intReserved ),			// 2	08		NMI
	VECTOR( intReserved ),			// 3	0C		Co-processor emulation emu_copro_process

	/* ----- Maskable Interrupts ----- */

//#ifdef VECTOR_TABLE_W23
	VECTOR( intReserved ),			// 4	10
	VECTOR( intPortInput ),			// 5	14		PORT interrupt
	VECTOR( intReserved ),			// 6	18
	VECTOR( intReserved ),			// 7	1C
	VECTOR( intRtca ),				// 8	20		RTCA interrupt
	VECTOR( intT16Ch0 ),			// 9	24		T16 ch.0 interrupt
	VECTOR( recevoirOctet ),			// 10	28		UART ch.0 interrupt
	VECTOR( intT16Ch1 ),			// 11	2C		T16 ch.1 interrupt
	VECTOR( intReserved ),			// 12	30
	VECTOR( intReserved ),			// 13	34
	VECTOR( intT16bCh0 ),			// 14	38		T16B ch.0 interrupt
	VECTOR( intT16bCh1 ),			// 15	3C		T16B ch.1 interrupt
	VECTOR( intReserved ),			// 16	40
	VECTOR( intT16Ch2 ),			// 17	44		T16 ch.2 interrupt
	VECTOR( intReserved ),			// 18	48
	VECTOR( intReserved ),			// 19	4C
	VECTOR( intReserved ),			// 20	50
	VECTOR( intReserved ),			// 21	54
	VECTOR( intReserved ),			// 22	58
	VECTOR( intReserved ),			// 23	5C
	VECTOR( intReserved ),			// 24	60
	VECTOR( intReserved ),			// 25	64
	VECTOR( intReserved ),			// 26	68
	VECTOR( intReserved ),			// 27	6C		reserved
	VECTOR( intReserved ),			// 28	70		reserved
	VECTOR( intReserved ),			// 29	74		reserved
	VECTOR( intReserved ),			// 30	78		reserved
	VECTOR( intReserved )			// 31	7C		reserved
//#endif	// VECTOR_TABLE_W23

};


/** *************************************************************************
 * boot function.
 *
 * @brief	First, it resets the Stack Pointer, clear the bss area,
 * 			and copy LMA to VMA.
 *			Next, it calls "main" function and calls "end" function.
 ************************************************************************* */
void boot(void)
{
	int status;

	/// Set stack pointer.
	asm("xld.a	%r0,	__START_stack	");
	asm("ld.a	%sp,	%r0				");

	/// Initialize module.
	initPwg();						/// - Initialize PWG.
	initItc();						/// - Initialize ITC.

	/// Initialize section.
	clearBss();						/// - Clear the bss area.
	loadLmaToVmaData();				/// - Copy LMA data to VMA data(".data" section).

	// Reset de ce qui est pres de la Start_stack : normalement inutile, seule la partie entre
	// INIT_MALLOC_START et INIT_MALLOC_END est utile, mais c'est fait plus tard.
	// Utile seulement pour des tests, pour visualiser où en est la stack.
	// Pas dangereux car à ce stade du programme il n'y a rien là dedans
	memset((void *)INIT_MALLOC_START , 0x00,
		(unsigned int)((unsigned long)&__START_stack - 4*5 - INIT_MALLOC_START) + 1);


	#ifdef SIM_IO_USED
	loadLmaToVmaSimIO();			/// - Copy LMA data to VMA data(".simio" section).
	#endif // SIM_IO_USED

	/// Initialize library.
    _init_sys();					/// - Initialize for sys.c.
    _init_lib();					/// - Initialize for lib.c.

	setFlashcAccessCycle( FLASHCWAIT_RDWAIT_1 );

	asm ( "ei" );					/// Interrupt enable.

	status = main(); 				/// Call main.

	if ( status == STATUS_NG ) {
		/* *** TEST ERROR *** */
		asm ( "brk" );
		asm ( "nop" );
	} else {
		/* *** TEST OK *** */
	}

	end(); 							/// Call end.
}


/* ----- static ----- */

/** *************************************************************************
 * initPwg function.
 *
 * @brief	Initialize PWG module.
 ************************************************************************* */
static void initPwg(void)
{

	/// disable write-protec.
	protectMisc( MSCPROT_PROTECT_OFF );

#ifdef	PWG2_ENABLE
	/// PWG2 Mode : Automatic mode.
	PWGCTL_PWGMOD		= 0;
#else
	/// PWG Mode : Automatic mode.
	//PWGVD1CTL_REGMODE	= 0;
#endif

	/// enable write-protect.
	protectMisc( MSCPROT_PROTECT_ON );

	return;
}


/** *************************************************************************
 * initItc function.
 *
 * @brief	 is initialized ITC module.
 ************************************************************************* */
static void initItc(void)
{
	/// Initialize interrupt level.
	ITCLV0_ILV0		= 0;
	ITCLV0_ILV1		= 0;
	ITCLV1_ILV2		= 0;
	ITCLV1_ILV3		= 0;
	ITCLV2_ILV4		= 0;
	ITCLV2_ILV5		= 0;
	ITCLV3_ILV6		= 0;
	ITCLV3_ILV7		= 0;
	ITCLV4_ILV8		= 0;
	ITCLV4_ILV9		= 0;
	ITCLV5_ILV10	= 0;
	ITCLV5_ILV11	= 0;
	ITCLV6_ILV12	= 0;
	ITCLV6_ILV13	= 0;
	ITCLV7_ILV14	= 0;
	ITCLV7_ILV15	= 0;
	ITCLV8_ILV16	= 0;
	ITCLV8_ILV17	= 0;
	ITCLV9_ILV18	= 0;
	ITCLV9_ILV19	= 0;
	//ITCLV10_ILV20	= 0;
	//ITCLV10_ILV21	= 0;
#ifndef ITC_LV_END_10
	//ITCLV11_ILV22	= 0;
#endif	// ITC_LV_END_10

	return;
}


/** *************************************************************************
 * clearBss function.
 *
 * @brief	Clear ".bss" Section.
 ************************************************************************* */
static void clearBss(void)
{
	unsigned char	*addr;
	unsigned long	size;
	unsigned long	i;

	addr	= (unsigned char *)&__START_bss;
	size	= (unsigned long)&__END_bss - (unsigned long)&__START_bss;

	/// Clear ".bss" section.
	for(i = 0 ; i < size ; i++){
		*addr++ = 0x00;
	}

	return;
}

/** *************************************************************************
 * loadLmaToVma function.
 *
 * @brief	This function copys LMA data to VMA data(".data" section).
 ************************************************************************* */
static void loadLmaToVmaData(void)
{
	unsigned char		*src;
	unsigned char		*dst;
	unsigned long		size;
	unsigned long		i;

	/// Load ".data" section.
	src		= (unsigned char *)&__START_data_lma;
	dst		= (unsigned char *)&__START_data;
	size	= (unsigned long)&__END_data - (unsigned long)&__START_data;

	for(i = 0 ; i < size ; i++){
		*dst++ = *src++;
	}

}


/** *************************************************************************
 * end function.
 *
 * @brief	This function has only infinite loop.
 ************************************************************************* */
static void end(void)
{
	/// Infinite loop.
	while ( 1 ){
		asm("halt");
	}
}

/* ----- Non Maskable Interrupt Handler ----- */

/** *************************************************************************
 * intAddrErr function.
 *
 * @brief	Interrupt handler for "Address misaligned".
 ************************************************************************* */
void intAddrErr(void)
{
	/// Undecid processing.
	asm("halt");
}


/** *************************************************************************
 * intNmi function.
 *
 * @brief	Interrupt handler for "NMI".
 ************************************************************************* */
void intNmi(void)
{
	/// Undecid Processing.
	asm("halt");
}


/** *************************************************************************
 * intReserved function.
 *
 * @brief	Interrupt handler for "Reserved".
 ************************************************************************* */
void intReserved(void)
{
	/// Infinite loop.
	while ( 1 ){
		;
	}
}
