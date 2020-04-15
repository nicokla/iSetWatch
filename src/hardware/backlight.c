/* ***********
 * Fonctions pour activer/desactiver la lumiere
 * lightOn() est appelée après un clic sur S1 court la plupart du temps (sauf si la bluetooth est activée en fait)
 *************** */

#include "hardware/backlight.h"
#include "init.h"
#include "t16_ch0_smallDelays.h"
#include "bluetooth.h"

// light on
void lightOn(){
	if(bluetoothMode.nb == BL_OFF){ // on ne veut pas allumer le backlight si la bluetooth fonctionne
		P3DAT_P30OUT=1;
		waitAndDo(4, &lightOff);
	}
}

void lightOnSimple(){
	P3DAT_P30OUT=1;
}

// light off
void lightOff(){
	P3DAT_P30OUT=0;
}

// initialisation du backlight
void initBacklight(){
	//P30 output a 0
	P3IOEN_P30IEN=0;
	P3IOEN_P30OEN=1;
	P3DAT_P31OUT=0;
}
