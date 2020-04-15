#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "globalVar.h"
#include "hardware/lcd8a.h"
#include "interruptBoutons.h"
#include "interruptTime.h"
#include "init.h"
#include "lcd8a.h"
#include "tennis.h"
#include "watch.h"
#include "class/time.h"
#include "t16_ch0_smallDelays.h"
#include "buzzer.h"
#include "backlight.h"
#include "bluetooth.h"

#include "class/iSetService.h"
#include "class/que.h"

// Les cellules qui sont échangées entre freeBuffQue et pendingBuffQue
iSetFrameBuffer_t bufferPool[5];

// Permet de détecter depuis le main si on a avalé un octet lors du dernier interrupt.
// Est mis à 1 à la fin de recevoirOctet().
volatile unsigned char uartCharRcvd = 0;

// Contient des cellules pretes à etre empilees dans l'autre liste fifo pendingBuffQue
// à la reception d'une trame
QUE_Obj freeBuffQue;

// une liste Fifo dans laquelle on mets la trame dès qu'on l'a reçue. Vide par defaut.
QUE_Obj pendingBuffQue;

////////////////////
// variables uart

// Head et tails sont des indices pointant dans le buffer de réception vers les octets
// - où commence la trame pour head
// - où est le dernier octet reçu pour tail
/*volatile*/ unsigned char head=0;
/*volatile*/ unsigned char tail=0;

unsigned short sizeTrameEnvoyee=SIZE_BUFFER_UART;
unsigned char sndData[SIZE_BUFFER_UART];
/*volatile*/ unsigned char rcvData[SIZE_BUFFER_UART];

// le checkbyte == xor de tous les octets d'une trame
unsigned char checkSum;
unsigned char newByte=0;


/////////////////////////////////////

void finirPairing();
unsigned char ComputeCheckSum();

/////////////////////////////////////////////////
// Initialisations et procedures de demarrage/arret

// initalise l'uart
void initUart( void ){
	stopUart();

	/// Initialize the UART input/output function to the ports.
	P0IOEN_P03IEN		= 0;			/// - P03 : Disable input.
	P0IOEN_P03OEN		= 0;			/// - P03 : Disable output.
	P0MODSEL_P03SEL		= 0;			/// - P03 : Disable peripheral I/O function.
	P0IOEN_P01IEN		= 0;			/// - P01 : Disable input.
	P0IOEN_P01OEN		= 0;			/// - P01 : Disable output.
	P0MODSEL_P01SEL		= 0;			/// - P01 : Disable peripheral I/O function.

	/// Assign the UART input/output function to the ports.
	P0FNCSEL_P03MUX		= 1;			/// - P03 : UPMUX.
	P0MODSEL_P03SEL		= 1;			/// - P03 : Enable peripheral I/O function.
	P0FNCSEL_P01MUX		= 1;			/// - P01 : UPMUX.
	P0MODSEL_P01SEL		= 1;			/// - P01 : Enable peripheral I/O function.

	/// Set Universal Port Multiplexer (UPMUX).
	P0UPMUX1_P03PERISEL	= 3;			/// - P03 : UART.
	P0UPMUX1_P03PERICH	= 0;			/// - P03 : Ch.0.
	P0UPMUX0_P01PERISEL	= 3;			/// - P01 : UART.
	P0UPMUX0_P01PERICH	= 0;			/// - P01 : Ch.0.

	P0UPMUX0_P01PPFNC	= 2;			/// - P01 : USOUT.
	P0UPMUX1_P03PPFNC	= 1;			/// - P03 : USIN.

	/// Configure operating clock.
	UA0CLK_CLKSRC		= 1;			/// - Select the clock source of the UART(OSC1).
	UA0CLK_CLKDIV		= 0;			/// - Select the division ratio(1/1).
	UA0CLK_DBRUN		= 1;			/// - Clock supplied in DEBUG mode.

	/// The clock source operations in SLEEP mode.
	CLGOSC_IOSCSLPC		= 0;			/// - Continue operation state before SLEEP.

	/// Configure the following UA0MOD register bits.
	UA0MOD_PUEN			= 1;			/// - Set USIN0 pin(0=Disable pull-up / 1=Enable pull-up).
	UA0MOD_OUTMD		= 0;			/// - Set USOUT0 pin(0=Push-pull output / 1=open-drain output).
	UA0MOD_IRMD			= 0;			/// - IrDA interface(0=Disable / 1=Enable).
	UA0MOD_CHLN			= 1;			/// - Data length(0=7-bit  / 1=8-bit).
	UA0MOD_PREN			= 0;			/// - Parity function(0=Disable / 1=Enable).
	UA0MOD_PRMD			= 0;			/// - Even parity selection(0=Unused / 1=Used).
	UA0MOD_STPB			= 0;			/// - Stop bit length(0=1-bit  / 1=2-bit).

	/// Set transfer rate( bps = CLK_UART / {(BRT + 1) x 16 + FMD} ).
	/// - S1C17M01     : 460800 bps = 7.37MHz / 16 = 460625(-0.038%).
	/// - S1C17W22_W23 :  43750 bps =  700KHz / 16 = 43750.
	// S1C17W15 : 2048 bps = 32768 / 16 (OSC1)
	UA0BR_BRT			= 0x0;			/// - BRT : 0
	UA0BR_FMD			= 0x0;			///	- FMD : 0

	/// Set interrupt level.
	ILVUART_0			= INTERRUPT_LEVEL7;	/// - Set interrupt level 7=max.
}

// Start l'uart
void startUart( void )
{
	head = tail = 0;
	QUE_reset(&freeBuffQue);
	QUE_reset(&pendingBuffQue);

	QUE_reset((QUE_Handle)&bufferPool[0]);
	QUE_reset((QUE_Handle)&bufferPool[1]);
	QUE_reset((QUE_Handle)&bufferPool[2]);
	QUE_reset((QUE_Handle)&bufferPool[3]);
	QUE_reset((QUE_Handle)&bufferPool[4]);

	QUE_enqueue(&freeBuffQue, (QUE_Handle)&bufferPool[0]);
	QUE_enqueue(&freeBuffQue, (QUE_Handle)&bufferPool[1]);
	QUE_enqueue(&freeBuffQue, (QUE_Handle)&bufferPool[2]);
	QUE_enqueue(&freeBuffQue, (QUE_Handle)&bufferPool[3]);
	QUE_enqueue(&freeBuffQue, (QUE_Handle)&bufferPool[4]);


    /// Execute software reset.
    UA0CTL_SFTRST		= 1;
    while( UA0CTL_SFTRST == 1 ) {
        // Wait...
    }

    /// Enable UART Ch.0 operations.
    UA0CTL_MODEN		= 1;

    UA0INTF=0xFFFF; // clear flags
    //UA0INTE_TBEIE=1; // quand on envoie quelque chose c'est decide, pas par interrupt.
    // si on met malgre tout UA0INTE_TBEIE a 1, cela creerait une interrupt, cf doc partie 12.5.1
    UA0INTE_RB1FIE=1; // on recoit par interrupt. Attention cela cree une
}

// Arrete l'uart
void stopUart( void ){
	/// Disable UART Ch.0 operations.
	UA0CTL_MODEN		= 0;

	/// Execute software reset.
	UA0CTL_SFTRST		= 1;
	while( UA0CTL_SFTRST == 1 ) {
		;// Wait...
	}
}



/////////////////////////////////////////////
// Envoi

// Flush le buffer d'envoi
void flushSndData(void){
	memset(sndData,0,SIZE_BUFFER_UART);
}

// Check si on a l'image B, renvoie 1 si oui, 0 sinon
unsigned char checkIfImageB() {
	unsigned char value;
	// port en entrée
	P3IOEN_P32IEN=1;
	P3IOEN_P32OEN=0;

	// on met un pull-up, comme ça il faut vraiment que le CC soit en sortie à zero pour qu'on
	// reçoive un zero
	P3RCTL_P32REN=1; // activate the pull-?
	P3RCTL_P32PDPU=1; // set to pull-up

	wait_general(10);

	//puis on le lit :
	value = P3DAT_P32IN;

	// port remis en sortie
	P3IOEN_P32IEN=1;
	P3IOEN_P32OEN=0;

	// on desactive le pull-up.
	P3RCTL_P32REN=0;

	return value;
}

// Envoie une trame complete, avec la trame id valant m, les données étant
// de longueur length et stockée là où pointe data.
// Dans la pratique on prends data = sndData, et avant d'appeler sendUartData, on fait
// memset (sndData, pointeur, length).
void sendUartData(unsigned char m, unsigned char *data, unsigned char length){
	unsigned short i;
	unsigned char xorxor=0x00;
	//unsigned char length = longueurTrame(m);
//	if(checkIfImageB()){
		wakeup_ble();

		// TODO1 : D�lai entre les trames
		// wait_general(100);

		// Send data.
		while ( UA0INTF_TBEIF == 0 ) { }
		UA0TXD_TXD = 0xAA;
		xorxor ^=  0xAA;

		while ( UA0INTF_TBEIF == 0 ) { }
		UA0TXD_TXD = (length+3);
		xorxor ^=  (length+3);

		while ( UA0INTF_TBEIF == 0 ) { }
		UA0TXD_TXD = m;
		xorxor ^=  m;

		for ( i = 0 ; i < length ; i++ ) {
			// TODO2 : ligne de ralentissement volontaire de l'uart
			// wait_general(20);

			/// Check Transmit buffer empty interrupt.
			while ( UA0INTF_TBEIF == 0 ) { }

			/// Send data.
			UA0TXD_TXD = data[i];
			xorxor ^=  data[i];
		}

		while ( UA0INTF_TBEIF == 0 ) { }
		UA0TXD_TXD = xorxor;

		memset(data,0,12);
//	} else {
		//////// lignes vraiment commentees :
		//reset_radio(); // le CC est en image A, donc demarre automatiquement l'advertizing pour lancer l'oad
		//mettreMode(OAD_CHOICE); // on met l'ecran d'attente de 90 secondes.
		//////////////
		//		mettreMode(OAD_UPDATING);
//	}
}

// Envoi de données mais pas nécessairement avec le format de trame utilisé
// Non utilisé dans la pratique, mais on peut la garder au cas où elle nous serait utile plus tard dans le projet
void sendUartDataGeneral( unsigned char *data, unsigned short size ){
	unsigned short i;

	wakeup_ble();

	// Send data.
	for ( i = 0 ; i < size ; i++ ) {

		/// Check Transmit buffer empty interrupt.
		while ( UA0INTF_TBEIF == 0 ) {
			// Wait...
		}

		/// Send data.
		UA0TXD_TXD = data[i];
	}
	memset(data,0,12);
}


/////////////////////////////////////////////////
// Reception

// Reçois par interruption un octet venant de l'uart
void recevoirOctet( void )
{
    while ( UA0INTF_RB1FIF == 0 ); // Wait end of reception
    rcvData[head]	= UA0RXD_RXD;
    UART_INC_BUFFER_IDX(head);

    // This guaranty a SOF at tail at all time or tail = head
    if(head==tail)
    {   // Handle buffer overflow
        flushRcvData();
        tail=head=0;
        return;
    }
    else if(rcvData[tail]!=SOF)
    	UART_MOVE_SOF;

    uartCharRcvd = TRUE;
    return;
}

// Calcule le checksum
unsigned char ComputeCheckSum()
{
    unsigned char i;
    unsigned char xor = 0;

    i=head;
    UART_DEC_BUFFER_IDX(i);

    while(i!=tail)
    {
        UART_DEC_BUFFER_IDX(i);
        xor ^= rcvData[i];
    }
    return xor;
}

// Flush le buffer de reception
void flushRcvData(void){
    head=0;
    tail=0;
    memset(rcvData,0,SIZE_BUFFER_UART);
}

// Extrait la trames si elle est terminée, et la mets dans pendingBuff
void ExtractFrame()
{
    unsigned char i, cIdx, xor = 0, tmpLen = 0, ckLen, fLen = 0xFF;
    iSetFrameBuffer_t *frameBuff;

    uartCharRcvd = FALSE;

    // If start byte is not SOF, move to next one
    while(tail!=head)
    {
        cIdx = tail;
    	tmpLen = UART_FRAME_LENGTH;

        if((fLen==0xFF)&&(2<=tmpLen))
            fLen = rcvData[UART_NEXT_BUFFER_IDX(cIdx)]+1;

        // Check if we have yet received enough data
        if(fLen<=tmpLen)
        {
            // Check xor and if ok, feed iSetUartBuffer
        	for(i=0; i<fLen-1; i++)
        	{
        		xor ^= rcvData[cIdx];
        		UART_INC_BUFFER_IDX(cIdx);
        	}

            if((xor==rcvData[cIdx])&&
            		(QUE_Handle)(frameBuff = QUE_dequeue(&freeBuffQue))
            		!= &freeBuffQue)
            {
            	cIdx = tail;
                UART_OFFSET_BUFFER_IDX(cIdx, 2);

                // Fill buffer to pass for processing
                frameBuff->fLen = fLen;
                frameBuff->cmd = rcvData[cIdx];

                UART_INC_BUFFER_IDX(cIdx); // Go to beginning of payload

                // No more than 20 bytes in payload, else a second buffer will carry remaining of the data
                ckLen = (fLen-4<=(SIZE_BUFFER_UART-cIdx)?fLen-4:SIZE_BUFFER_UART-cIdx);

                // Copy msg data in temp buffer to avoid conflicts during interrupts
                memcpy(frameBuff->buffer, &rcvData[cIdx], ckLen);
                memcpy(&frameBuff->buffer[ckLen],  &rcvData[0], (fLen-4)-ckLen);

                // Swap Rx/Processing buffers
                QUE_enqueue(&pendingBuffQue, (QUE_Handle)frameBuff);

                UART_OFFSET_BUFFER_IDX(tail, fLen); // Move tail up to next frame or head
            }
            else
            {
                // Start a SOF retrieval
        	    UART_INC_BUFFER_IDX(tail);
                UART_MOVE_SOF;
            }
        }
        else // Not enough data to process all, so stop here
        	return;

        fLen=0; // Re-initialize frame length
    }
}


