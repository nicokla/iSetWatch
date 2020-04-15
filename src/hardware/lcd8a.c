/***************
 * Gestion bas niveau du LCD
 * **************/

#include <string.h>
#include <lcd8a.h>
#include "tennis.h"
#include "ecranPourClignotements.h"
#include "globalVar.h"

unsigned char l_haut[14]={11, 9, 14, 6, 4, 3, 0, 8, 1, 12, 2, 10, 5, 13};
unsigned char l_bas[14]={6, 4, 3, 11, 9, 14, 8, 0, 12, 1, 13, 5, 10, 2};
unsigned char l_7[7]={6, 4, 2, 3, 1, 5, 0};

unsigned char nb7Seg[16]={
0x7e, 0x14, 0x5b, 0x5d, 0x35, 0x6d, 0x6f, 0x54, 0x7f, 0x7d, 0x77, 0x2f, 0x6a, 0x1f, 0x6b, 0x63 };

unsigned short nbHaut[16]={
0x4a58, 0x4200, 0xb51, 0x4b41, 0x4309, 0x4949, 0x4959, 0x4a00, 0x4b59, 0x4b49, 0x4b19, 0x4159, 0x858, 0x4351, 0x859, 0x819 };

unsigned short nbBas[16]={
0x4a58, 0x18, 0xb51, 0x959, 0x4119, 0x4949, 0x4b49, 0x58, 0x4b59, 0x4959, 0x4359, 0x4b09, 0x4a40, 0xb19, 0x4b40, 0x4340 };

unsigned short *nbAll[2]={nbHaut, nbBas};

unsigned short lettresHaut[28]={ // pour chiffres on se refere a nb. Ici les 26 lettres de l'alphabet, et "-" et "="en dernier.
0x4b19, 0x5b42, 0x858, 0x5a42, 0x859, 0x819, 0x4958, 0x4319, 0x1842, 0x4250, 0x2419, 0x58, 0x461c, 0x621c, 0x4a58, 0xb19,
0x6a58, 0x2b19, 0x4949, 0x1802, 0x4258, 0x438, 0x6238, 0x2424, 0x1404, 0xc60, 0x101, 0x141 };

unsigned short lettresBas[28]={ // pour chiffres on se refere a nb. Ici les 26 lettres de l'alphabet, et "-" et "="en dernier.
0x4359, 0x185b, 0x4a40, 0x185a, 0x4b40, 0x4340, 0x4a49, 0x4319, 0x1842, 0xa18, 0x4324, 0x4a00, 0x6238, 0x621c, 0x4a58, 0x4351,
0x4a5c, 0x4355, 0x4949, 0x1042, 0x4a18, 0x4620, 0x461c, 0x2424, 0x2022, 0xc60, 0x101, 0x901 };

unsigned short * lettresAll[2] = {lettresHaut, lettresBas};

// adresse mémoires des 14 segments
unsigned short * assoc14[2][5]
#ifdef NEW_SCREEN
 = {
	{((unsigned short*) (0x7000 + 14)),
	 ((unsigned short*) (0x7000 + 16)),
	 ((unsigned short*) (0x7000 + 18)),
	 ((unsigned short*) (0x7000 + 20)),
	 ((unsigned short*) (0x7000 + 22))
	 },

	 { ((unsigned short*) (0x7000 + 12)), // faux mais jamais utilisé
	 ((unsigned short*) (0x7000 + 10)),
	 ((unsigned short*) (0x7000 + 8)),
	 ((unsigned short*) (0x7000 + 6)),
	 ((unsigned short*) (0x7000 + 4)) }
};
#else
= {
	{((unsigned short*) (0x7000 + 14)), // faux mais jamais utilisé
	 ((unsigned short*) (0x7000 + 14)),
	 ((unsigned short*) (0x7000 + 16)),
	 ((unsigned short*) (0x7000 + 18)),
	 ((unsigned short*) (0x7000 + 20))
	 },

	 { ((unsigned short*) (0x7000 + 10)),
	 ((unsigned short*) (0x7000 + 8)),
	 ((unsigned short*) (0x7000 + 6)),
	 ((unsigned short*) (0x7000 + 4)),
	 ((unsigned short*) (0x7000 + 26)) }
};
#endif

// adresses mémoires des 7 segments
unsigned char* assoc7[2][4]
#ifdef NEW_SCREEN
= {
	{ ((unsigned char*) 0x7000 + 24),
	((unsigned char*) 0x7000 + 25),
	((unsigned char*) 0x7000 + 26),
	((unsigned char*) 0x7000 + 27)
	},
	{ ((unsigned char*) 0x7000+13),
	((unsigned char*) 0x7000+33),
	((unsigned char*) 0x7000+32),
	((unsigned char*) 0x7000 + 31)}
};
#else
= {
	{ ((unsigned char*) 0x7000 + 23),
	((unsigned char*) 0x7000 + 22),
	((unsigned char*) 0x7000 + 24),
	((unsigned char*) 0x7000 + 25)
	},
	{ ((unsigned char*) 0x7000+32),
	((unsigned char*) 0x7000+31),
	((unsigned char*) 0x7000+30),
	((unsigned char*) 0x7000 + 12)}
};
#endif


SymboleAdresse assocSymbole[NB_SYMBOLS];


static void initLcd8aMode(void);
static void initLcd8aPort(void);

// initialisation du lcd
void initLcd8a( void ){
	clearLcd();
	initLcd8aMode();
	initLcd8aPort();
}

// activation du lcd
void onLcd8aDisplay( void ) {
	LCD8CTL_MODEN	= 1;	/// Enable LCD8A.
	LCD8DSP_DSPC	= 1;	/// The LCD8A display state set to "normal display".
}

// desactivation du lcd
void offLcd8aDisplay( void ) {
	LCD8DSP_DSPC	= 0;	/// The LCD8A display state set to "display off".
	LCD8CTL_MODEN	= 0;	/// Disable LCD8A.
}


/*
ALL_OFF		3
ALL_ON		2
NORMAL		1
OFF			0 */
// permet de mettre tous les segments à 1 ou à 0 (utilise pour la transition vers le mode de test)
// par défaut est en état normal (1)
void setLcd8aDisplayState( unsigned char state ) {
	LCD8DSP_DSPC = state;	/// The LCD8A display state set.
}

// permet de connaitre l'état de l'écran (renvoie 1 la plupart du temps)
unsigned char getLcd8aDisplayState( void ) {
	return ( (unsigned char)LCD8DSP_DSPC );
}

// efface le LCD. Utilisé quand on change de mode principal dans mettreMode().
void clearLcd(  ) {
	unsigned char	*segram = (unsigned char *)LCD8A_SEGRAM_TOP_ADDR;
	unsigned short	i;

	for(i = 0 ; i < LCD8A_SEGRAM_SIZE ; i++){
		*segram++ = 0x00;
	}
}

// initialise le lcd
static void initLcd8aMode( void )
{
	LCD8CTL_MODEN		= 0;		/// LCD disable.

	LCD8INTF			= 0x0001;	/// Clear frame interrupt flag.
	LCD8INTE			= 0x0000;	/// Disable frame interrupt.

	LCD8CLK_CLKSRC		= 1;		/// the clock source = OSC1.
	LCD8CLK_CLKDIV		= 0;		/// the division ratio = 1/1.
	LCD8CLK_DBRUN		= 1;		/// Clock supplied in DEBUG mode.

	LCD8TIM1_LDUTY	= 0x7;		/// the drive duty = 1/8. //!!!
	LCD8TIM1_FRMCNT		= 3;		/// the frame frequency = 170.7 Hz.
	LCD8TIM2_NLINE		= 0;		/// the n-line inverse AC drive function = Normal drive.
	LCD8TIM2_BSTC		= 1;		/// the booster clock frequency = fCLK_LCD8A/16 Hz.

	LCD8PWR_VCEN		= 1;		/// the LCD8A voltage regulator = on.
	LCD8PWR_VCSEL		= 1;		/// the LCD8A voltage regulator output = VC2.
	LCD8PWR_HVLD		= 0;		/// the LCD8A voltage regulator into heavy load protection mode = Normal mode.
	LCD8PWR_BSTEN		= 1;		/// the LCD8A voltage booster = off.

	// la valeur 1A de LCD8PWR_LC est optimisée pour l'ecran lcd numero 14032602
	LCD8PWR_LC			= 0x12;		/// the LCD8A panel contrast = 0x00:light - 0x1F:dark.
	LCD8PWR_BISEL=1;

	LCD8DSP_DSPC		= 0;		/// the LCD8A display = display off.
	LCD8DSP_DSPAR		= 0;		/// the display area in the display data RAM = Display area 0.
	LCD8DSP_DSPREV		= 1;		/// black/white inversion = Normal display.
	LCD8DSP_COMREV		= 1;		/// the common pin assignment direction = Normal assignment.
	LCD8DSP_SEGREV		= 1;		/// the segment pin assignment direction = Normal assignment.
	LCD8COMC0_COM0DEN		= 1;		/// the partial drive of COM0 pin = Normal output;
	LCD8COMC0_COM1DEN		= 1;		/// the partial drive of COM1 pin = Normal output;
	LCD8COMC0_COM2DEN	= 1;		/// the partial drive of COM2 pin = Normal output;
}

// autre fonction d'initialisation des ports du lcd
static void initLcd8aPort( void ) {
	P2FNCSEL |= 0xFFFF;		/// P20 to P27 = Function 3(LCD8A / SEG16 to SEG23).
	P2MODSEL |= 0x00FF;		/// P20 to P27 = Use peripheral I/O function.
}

/////////////////////////////////


// initialisation des symboles de l'écran (adresses mémoires, choisies en fonction du routage)
void initSymbolesPositions(){
#ifdef NEW_SCREEN
	assocSymbole[SYMBOL_INDEX_24HMODE].a=((unsigned char*) (0x7000 + 27)) ;
	assocSymbole[SYMBOL_INDEX_PM].a=((unsigned char*) (0x7000 + 25)) ;
	assocSymbole[SYMBOL_INDEX_ALARM].a=((unsigned char*) (0x7000 + 20));
	assocSymbole[SYMBOL_INDEX_BT].a=((unsigned char*) (0x7000 + 22)) ;
	assocSymbole[SYMBOL_INDEX_SEPARATION].a=((unsigned char*) (0x7000 + 33)) ;
	assocSymbole[SYMBOL_INDEX_SERVER1].a=((unsigned char*) (0x7000 + 21)) ;
	assocSymbole[SYMBOL_INDEX_SERVER2].a=((unsigned char*) (0x7000 + 31)) ;
	assocSymbole[SYMBOL_INDEX_2PTS1].a=((unsigned char*) (0x7000 + 26));
	assocSymbole[SYMBOL_INDEX_2PTS2].a=((unsigned char*) (0x7000 + 32));
	assocSymbole[SYMBOL_INDEX_S3].a=((unsigned char*) (0x7000 + 4)) ;//BD
	assocSymbole[SYMBOL_INDEX_S4].a=((unsigned char*) (0x7000 + 13)) ;//BG
	assocSymbole[SYMBOL_INDEX_S1].a=((unsigned char*) (0x7000 + 24)) ;//HG
	assocSymbole[SYMBOL_INDEX_S2].a=((unsigned char*) (0x7000 + 23)) ;//HD
#else
	assocSymbole[SYMBOL_INDEX_AM].a=((unsigned char*) (0x7000 + 24)) ;
	assocSymbole[SYMBOL_INDEX_PM].a=((unsigned char*) (0x7000 + 25)) ;
	assocSymbole[SYMBOL_INDEX_ALARM].a=((unsigned char*) (0x7000 + 22));
	assocSymbole[SYMBOL_INDEX_BT].a=((unsigned char*) (0x7000 + 21)) ;
	assocSymbole[SYMBOL_INDEX_SEPARATION].a=((unsigned char*) (0x7000 + 26)) ;
	assocSymbole[SYMBOL_INDEX_SERVER1].a=((unsigned char*) (0x7000 + 33)) ;
	assocSymbole[SYMBOL_INDEX_SERVER2].a=((unsigned char*) (0x7000 + 32)) ;
	assocSymbole[SYMBOL_INDEX_2PTS1].a=((unsigned char*) (0x7000 + 23));
	assocSymbole[SYMBOL_INDEX_2PTS2].a=((unsigned char*) (0x7000 + 30));
#endif
}

//void activerBit(unsigned char * a, unsigned char b){
//	*a |= b;
//}
//
//void desactiverBit(unsigned char * a, unsigned char b){
//	*a &= (0xFF ^ b);
//}

// activer un symbole a l'ecran.
// La signification du nombre index est décrite dans lcd8a.h
// Par exemple on a "#define SYMBOL_INDEX_ALARM 2"
void setSymbole(unsigned char index, unsigned char value){
	if(value)
		*(assocSymbole[index].a) |= 0x80;//assocSymbole[index].b;
	else
		//desactiverBit(assocSymbole[index].a, assocSymbole[index].b);
		*(assocSymbole[index].a) &= 0x7F;
}


////////////////////////////////
// 2.2) Low to middle level display function
// 2.2.1) For 7 segments


// efface un 7 segment, de coordonnees à l'écran a (0 pour la ligne du haut, 1 pour celle du bas)
// et b (de 0 à 3 selon le 7 segment choisi)
void effacer7Seg(unsigned char a, unsigned char b){
	*(assoc7[a][b])&=0x80;
}

// affiche une sequence sur le 7 segment de coordonnées (a, b)
void afficherSeqSur7Seg(unsigned char a, unsigned char b, unsigned char seq){
	//if b<4 && a<2
	*(assoc7[a][b])=(seq | (*(assoc7[a][b]) & 0x80));
}

// affiche un chiffre sur un 7 segment
//n doit être inferieur a 10
void afficherChiffreSur7Seg(unsigned char a, unsigned char b, unsigned char n){
	afficherSeqSur7Seg(a, b, nb7Seg[n]);
}

// affiche un nombre sur un ou deux (cas où le nombre est supérieur à 10) 7 segments
// la coordonnée b sera pour les unités, elle vaut donc 1 ou 3 dans les cas pratiques.
void afficherNbSur7Seg(/*int*/unsigned char n, unsigned char a, unsigned char b){
	afficherChiffreSur7Seg(a, b, n%10);
	if(n>=10){
		afficherChiffreSur7Seg(a, b-1, (n/10)%10);
	} else {
		effacer7Seg(a, b-1);
	}
}

//Affiche un nombre en forçant les dizaines à être affichées, même si le nombre est inférieur à 10.
// Par exemple, 2 sera marqué 02.
void afficherNbA2ChiffresSur7Seg(/*int*/unsigned char n, unsigned char a, unsigned char b){
	afficherChiffreSur7Seg(a, b, n%10);
	afficherChiffreSur7Seg(a, b-1, (n/10)%10);
}

// Permet d'afficher un segment tournant.
// La fonction est appelée tous les quarts de secondes via afficheDefilementAll()
// Used when we wait the bluetooth connexion : the segment move in circle
// c= 0 ou 1, indice du digit tournant.
void afficherTournant(unsigned char a, unsigned char b){
	afficherSeqSur7Seg(a, 2*b+1, (0x01<< (l_7[ecran.aff7Seg[a][b].contenu.tournant])) );
	if (ecran.aff7Seg[a][b].contenu.tournant < 5){
		ecran.aff7Seg[a][b].contenu.tournant++;
	} else {
		ecran.aff7Seg[a][b].contenu.tournant=0;
	}
}


///////////////////////////
// 2.2.2) For 14 segments

// Permet d'effacer un 14 segment
void effacer14Seg(unsigned char a, unsigned char b){
#ifdef NEW_SCREEN
	if(a==1 && b==0){
			*((unsigned char*) (0x7000 + 12)) &= 0x80;
			*((unsigned char*) (0x7000 + 30)) &= 0x80;
	}else
		*(assoc14[a][b])&=0x8080;
#else
	if(a==0 && b==0){
			*((unsigned char*) 0x7021) &= 0x80;
			*((unsigned char*) 0x700D)=0x00;
	}else
		*(assoc14[a][b])&=0x8080;
#endif
}

// Affiche une sequence sur un 14 segment.
// en pratique les sequences affichées seront des dessins de chiffres ou de lettres
// contenues dans lettresAll et nbAll
void afficherSeqSur14Seg(unsigned char a, unsigned char b, unsigned short seq){
#ifdef NEW_SCREEN
	if (a==1 && b==0){
		*((unsigned char*) (0x7000 + 12))=( ((unsigned char)(seq & 0x00FF)) | ( *((unsigned char*) (0x7000 + 12)) & 0x80 ) );
		*((unsigned char*) (0x7000 + 30))=(unsigned char) ((seq&0xFF00)>>8);
	}
	else //if(b==4 || b==0)
		*(assoc14[a][b])=(seq | (*(assoc14[a][b]) & 0x8080));
	//else
		//*(assoc14[a][b])=seq;
#else
	if(b==4 && (a== 0 || a == 1))
		*(assoc14[a][b])=(seq | (*(assoc14[a][b]) & 0x8080));
	else if (a==0 && b==0){
		*((unsigned char*) 0x7021)=( ((unsigned char)(seq & 0x00FF)) | ( *((unsigned char*) 0x7021) & 0x80 ) );
		*((unsigned char*) 0x700D)=(unsigned char) ((seq&0xFF00)>>8);
	}else
		*(assoc14[a][b])=seq;
#endif
}

// renvoie la séquence associée à un caractere
unsigned short seq14SegOfChar(char c, unsigned char a){
	// majuscules et minuscules
	if (c >= 0x41  &&  c <= 0x5A)
		return lettresAll[a][c-0x41];
	else if(c >= 0x61  &&  c <= 0x7A)
		return lettresAll[a][c-0x61];

	// nombres
	else if (c >= 0x30 && c <= 0x39)
		return nbAll[a][c - 0x30];
	//else if (c >= 0 && c <= 10) // char and unsigned char have the same hexa value if positive or null
		//return nbAll[a][(unsigned char) c];

	// tiret et signe egal
	 else if (c==0x3D)
		 return lettresAll[a][27];
	 else if (c==0x2D)
		return lettresAll[a][26] ;

	 else
		 return 0;
}

// Affiche une lettre sur un 14 segment, à la position (a,b), a pouvant valoir 0 (ligne du haut) ou 1 (ligne du bas)
// et b pouvant valoir de 0 à 4 (de gauche à droite)
void afficherLettreSur14Seg(unsigned char a, unsigned char b ,char c){
	short seq = seq14SegOfChar(c, a);
	if (seq != 0)
		afficherSeqSur14Seg(a,b, seq );
	else
		effacer14Seg(a,b);// on ecrit un espace
}

// Affiche un chiffre sur un 14 segment
void afficherChiffreSur14Seg(unsigned char a, unsigned char b,unsigned char n){
	afficherSeqSur14Seg(a, b, nbAll[a][n] );
}

// Affiche un nombre de plusieurs chiffres sur un 14 segments (comme le jour du mois)
void afficherNbSur14Seg(/*int*/unsigned char n,  unsigned char a, unsigned char b ){
	char i=b;
	char chiffre;
	do{
		chiffre = n%10;
		afficherChiffreSur14Seg(a, i , chiffre);
		n /= 10;
		i--;
	}while (n!=0);
	/*for ( ; i >=0 ; i--){
		effacer14Seg(a , i);
	}*/
}

// Affiche un nombre de plusieurs chiffres sur un 14 segments (comme le jour du mois)
// en forçant les dizaines à s'afficher, même si elles valent zéro
void afficherNbA2ChiffresSur14Seg(/*int*/unsigned char n,  unsigned char a, unsigned char b){
	afficherChiffreSur14Seg(a, b, n%10);
	afficherChiffreSur14Seg(a, b-1, (n/10)%10);
}

// efface une ligne de 14 segments
void effacerZone14Seg( unsigned char zoneNb){
	unsigned char i;
	for (i=0; i<5 ; i++){
		effacer14Seg(zoneNb, i);
	}
}

// affiche un texte de 5 caracteres sur une ligne (la ligne étant celle du haut si zoneNb vaut 0, celle du bas si
// zoneNb vaut 1)
void afficherTexteSur14Seg(char s[5], unsigned char zoneNb){
	unsigned char i=0;
	for(i=0; i<5; i++){
		afficherLettreSur14Seg(zoneNb, i, s[i]);
	}
}



///////////////////////////
// defilement

// affiche le texte au défilement tout en l'incrémentant (le texte défile)
void afficherDefilement(unsigned char zoneNb){
	char i = ecran.aff14Seg[zoneNb].contenu.defilement.pos;

	effacerZone14Seg(zoneNb);

	while (i<=ecran.aff14Seg[zoneNb].contenu.defilement.pos + 4 ){
		//if(i<0 || ecran.aff14Seg[zoneNb].contenu.defilement.txt[i] == '\0' ){
			//effacer14Seg(zoneNb, i-ecran.aff14Seg[zoneNb].contenu.defilement.pos; // inutile car deja effacerZone avant
		/*} else*/ if( i>=0 ){
			afficherLettreSur14Seg(zoneNb, i-ecran.aff14Seg[zoneNb].contenu.defilement.pos, ecran.aff14Seg[zoneNb].contenu.defilement.txt[i]);
		}
		i++;
	}
}

// mets à jour la position du défilement
void updatePositionDefilement(unsigned char zoneNb){
	if(ecran.aff14Seg[zoneNb].contenu.defilement.pos<0){
		ecran.aff14Seg[zoneNb].contenu.defilement.pos++;
	} else if(
			ecran.aff14Seg[zoneNb].contenu.defilement.txt[(unsigned char)  ( ecran.aff14Seg[zoneNb].contenu.defilement.pos )] == '\0'
				|| ecran.aff14Seg[zoneNb].contenu.defilement.pos > SIZE_MAX_DEFILEMENT-1 ){
		ecran.aff14Seg[zoneNb].contenu.defilement.pos = -4;
	} else {
		ecran.aff14Seg[zoneNb].contenu.defilement.pos++;
	}
}


// Appelé tout les quarts de secondes pour faire défiler les textes
void afficheDefilementAll(){
	unsigned char zoneNb;
	for(zoneNb=0; zoneNb<=1; zoneNb++){
		if(ecran.aff14Seg[zoneNb].type==DEFILEMENT){
			afficherDefilement(zoneNb);
			updatePositionDefilement(zoneNb);
		}
	}
	if(ecran.aff7Seg[0][0].type == TOURNANT){
		afficherTournant(0,0);
	}
	if(ecran.aff7Seg[1][0].type == TOURNANT){
		afficherTournant(1,0);
	}
}


// Mets au défilement un texte
void mettreAuDefilement(unsigned char zoneNb, char * texte){
	unsigned char i=0;
	memset ( ecran.aff14Seg[zoneNb].contenu.defilement.txt, '\0', SIZE_MAX_DEFILEMENT );
//	strcpy(ecran.aff14Seg[zoneNb].contenu.defilement.txt,texte);
	while(i<SIZE_MAX_DEFILEMENT && texte[i] != '\0'){
		ecran.aff14Seg[zoneNb].contenu.defilement.txt[i]=texte[i];
		i++;
	}
	ecran.aff14Seg[zoneNb].contenu.defilement.pos = -1;
	ecran.aff14Seg[zoneNb].type=DEFILEMENT;
	afficherDefilement(zoneNb);
}

// Désactive le défilement
void desactiverDefilement(){
	ecran.aff14Seg[0].type=RIEN;
	ecran.aff14Seg[1].type=RIEN;
}

///////////////////////////////////////////////////////


