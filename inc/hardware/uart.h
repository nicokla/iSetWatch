#ifndef UART_H__
#define UART_H__

#include <init.h>
#include "class/que.h"

//////////////////////

#define SOF 			0xAA
#define SIZE_BUFFER_UART 128

#define CC254X_RESET P3DAT_P31OUT
//#define UART_TX P01
//#define UART_RX P03
#define CC254X_WAKEUP P3DAT_P32OUT
//#define CC254X_UNUSED P02

////////////////////////////

#define UART_INC_BUFFER_IDX(_idx)  (_idx=(_idx==SIZE_BUFFER_UART-1)?0:_idx+1)
#define UART_DEC_BUFFER_IDX(_idx)  (_idx=(_idx==0)?SIZE_BUFFER_UART-1:_idx-1)

#define UART_NEXT_BUFFER_IDX(_idx) (_idx!=SIZE_BUFFER_UART-1?_idx+1:0)
#define UART_PREV_BUFFER_IDX(_idx) (_idx==0?SIZE_BUFFER_UART-1:_idx-1)

#define UART_OFFSET_BUFFER_IDX(_idx, _offset) \
do{\
if(_idx+_offset<=SIZE_BUFFER_UART-1)\
{_idx+=_offset;} \
else \
{_idx=_offset-(SIZE_BUFFER_UART-_idx);}\
}while(0)

#define UART_NEG_OFFSET_BUFFER_IDX(_idx, _offset) \
do{\
if(_idx>=_offset)\
{_idx-=_offset;}\
else \
{_idx=SIZE_BUFFER_UART-_offset+idx;} \
}while(0)

#define UART_FRAME_LENGTH (tail<=head?(head-tail):(SIZE_BUFFER_UART-tail+head))

#define UART_MOVE_SOF do{while((0xAA != rcvData[tail])&&(tail!=head)) UART_INC_BUFFER_IDX(tail); }while(0) // Increment tail to find 0xAA


///////////////////////////////

typedef struct{
	QUE_Elem queElem;

    unsigned char cmd;
    unsigned char fLen;

    unsigned char buffer[30];
}iSetFrameBuffer_t;



extern iSetFrameBuffer_t bufferPool[];

extern volatile unsigned char uartCharRcvd;

extern QUE_Obj freeBuffQue;
extern QUE_Obj pendingBuffQue;

/////////////////////////

extern unsigned short sizeTrameRecue;
extern unsigned short sizeTrameEnvoyee;
extern unsigned char sndData[SIZE_BUFFER_UART];
extern /*volatile*/ unsigned char rcvData[SIZE_BUFFER_UART];
extern unsigned char checkSum;
extern /*volatile*/ unsigned char head;
extern /*volatile*/ unsigned char tail;

unsigned char checkIfImageB();
extern void recevoirOctet( void )	__attribute__ ((interrupt_handler));
extern void flushRcvData(void);
extern void flushSndData(void);
extern void initUart( void );
extern void startUart(void);
extern void stopUart(void);
void sendUartDataGeneral( unsigned char *data, unsigned short size );
void sendUartData(unsigned char m, unsigned char *data, unsigned char length);

void sendByte(unsigned char m, unsigned char a);
unsigned char xor( unsigned char *data, unsigned char size );
unsigned char longueurTrame(unsigned char typeTrame);
void ExtractFrame();

#endif	// UART_H__


