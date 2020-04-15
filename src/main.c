#include <string.h>
#include <stdio.h>
#include "init.h"
#include "clg.h"
#include "lcd8a.h"
#include "globalVar.h"

#include "que.h"

int main(void);

extern unsigned char frameSize;
extern volatile unsigned char uartCharRcvd;

extern QUE_Obj pendingBuffQue;

extern void ExtractFrame(void);
extern void ParseFrame(void);

/* Dans la m�moire les premiers bits sont les bits de poids faibles.
 * --> si on fait une structure avec la syntaxe "unsigned char x : 4"
 * par exemple pour un champ de 4 bits, le premier champs sera celui
 * des bits de poids faibles.
 * */

// Cette fonction est une boucle attendant le prochain évènement.
// Dans le cas d'un évènement uart (fonction recevoirOctet()),
// le main() appelle les fonctions parseFrame et ExtractFrame, ce qui va cause à la fin de la trame
// l'appel à la fonction traiterTrameRecue() qui va finalement traiter la trame.
int main(void){
	commence(1); // on initialise tout
	uartCharRcvd=TRUE;
	while(TRUE){

		// Sleep until a new char is received
		while(uartCharRcvd==0x00)// Loop around
		{
			asm("halt");
			asm("nop");

			// On parse si nvl existante
			if(QUE_length(&pendingBuffQue)!=0)
				ParseFrame();
		}

		// On Extract la/les nouvelles frames UART
		ExtractFrame();

	}
	return STATUS_OK;
}
