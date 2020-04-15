#ifndef INIT_H__
#define INIT_H__

//#include "c17w23_reg.h"
#include "c17w15_reg.h"

#define CpuIntDisable()			asm("di")	///< Disable interrupt.
#define CpuIntEnable()				asm("ei")	///< Enable interrupt.

#define FALSE						( 0 )		///< False.
#define TRUE						( 1 )		///< True.
#define SUCCESS					( 0 )		///< Success.
#define ERROR						( -1 )		///< Error.

// These protect the control registers related to the system against writings.
#define MSCPROT_PROTECT_ON			( 0x00 )	///< Set the write protect.
#define MSCPROT_PROTECT_OFF		( 0x96 )	///< Remove the write protect.

// These set the internal RAM size that can be used.
#define MSCIRAMSZ_512B				( 0x0 )		///< internal RAM size 512b.
#define MSCIRAMSZ_1KB				( 0x1 )		///< internal RAM size 1kb.
#define MSCIRAMSZ_2KB				( 0x2 )		///< internal RAM size 2kb.
#define MSCIRAMSZ_4KB				( 0x3 )		///< internal RAM size 4kb.
#define MSCIRAMSZ_8KB				( 0x4 )		///< internal RAM size 8kb.

// This indicates whether the Flash memory can be accessed or not.
#define FLASHCWAIT_XBUSY_ON		( 0x0 )		///< Flash access prohibited.
#define FLASHCWAIT_XBUSY_OFF		( 0x1 )		///< Flash memory ready to access.

// These set the number of bus access cycles for reading from the Flash memory.
#define FLASHCWAIT_RDWAIT_1		( 0x0 )		///< Flash access prohibited.
#define FLASHCWAIT_RDWAIT_2		( 0x1 )		///< Flash access prohibited.
#define FLASHCWAIT_RDWAIT_3		( 0x2 )		///< Flash access prohibited.
#define FLASHCWAIT_RDWAIT_4		( 0x3 )		///< Flash access prohibited.


/* --- external declaration --- */

extern void protectMisc(unsigned char protectCode);
extern void setFlashcAccessCycle(unsigned char flashc);
extern void setMiscIRAMSize(unsigned char iramSize);
extern void setMiscVectorAddress(unsigned short baseAdrL, unsigned short baseAdrH);


#endif	// INIT_H__
