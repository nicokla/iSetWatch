/***********
 * Ce fichier sert à gérer le buzzer.
 * C'est utile par exemple pour que l'alarme puisse sonner.
 * ***********/

#include "hardware/buzzer.h"
#include "init.h"
#include "globalVar.h"

// initialisation du buzzer
void init_bz(){
	//1) P15 = BZ
	// Choisi pour P15 le mode BZOUT
	P1FNCSEL_P15MUX=0;
	// Choisi peripheral IO au lieu de GPIO
	P1MODSEL_P15SEL=1;

	// ou bien on peut mettre au lieu de ces deux lignes juste celle-ci, mais qui est moins explicite :
	//  *(volatile unsigned int *)(0x421c) = (unsigned int )0x0020;


	// 2) SNDA clock = OSC1
	*(volatile unsigned int *)(0x5300) = (unsigned int )0x0101;

	// 3) SNDCTL.MODEN  = 1
	*(volatile unsigned int *)(0x5304) = (unsigned int )0x0001;

	// 4) SNDSEL.SINV = 0
	*(volatile unsigned int *)(0x5302) &= (unsigned int )0xfffd;
}

// bip moyennement long du buzzer
void out_bz(){
	SNDSEL_MOSEL = 0x01;
	while(SNDINTF_SBSY){ }
	SNDSEL_STIM = 0x06;
	SNDDAT = (unsigned int )0x0307;

	/* On pourrait en theorie faire au lieu de cette ligne:
	SNDDAT_SLEN = 0x03;//(50%)
	SNDDAT_SFRQ = 0x07;// (4kHz)
	Mais :
	The SNDDAT register allows 16-bit data writing only. Data writings in 8-bit size will be ignored.
	*/
}

// bip court du buzzer
void out_bz_short(){
	SNDSEL_MOSEL = 0x01;
	while(SNDINTF_SBSY){ }
	SNDSEL_STIM = 0x04;
	SNDDAT = (unsigned int )0x0307;
}

// bip long du buzzer
void out_bz_long(){
	SNDSEL_MOSEL = 0x01;
	while(SNDINTF_SBSY){ }
	SNDSEL_STIM = 0x0C;
	SNDDAT = (unsigned int )0x0307;
}

// plusieurs bips successifs du buzzer
void bipBip(int n){
	int i;
	for (i=0; i<n-1; i++){
		out_bz();
		wait_s();
	}
	out_bz();
}
