/***************
 * Les fonctions de ce fichier servent à remplir l'écran SW, qui va ensuite être affiché sur l'écran HW
 * via la fonction afficheEcranAll(), qui est appelée à la fin de mettreMode()
 * ***************/

#include "lcd8a.h"
#include "ecranPourClignotements.h"
#include <string.h>
#include "tennis.h"
#include "varAff.h"
#include "bluetooth.h"
#include "watch.h"

Ecran ecran;

// ajoute un symbole sur la pile des symboles qui clignotent
void empile(QuiClignote * a, unsigned char b){
	unsigned char i=0;
	while(i < a->taillePile && a->indices[i] != b ){
		i++;
	}
	if(i == a->taillePile){ // si on a pas vu de b, ie on est arrivé au bout de la pile sans s'arreter
		a->indices[a->taillePile]=b;
		a->taillePile++;
	}
}

// clear la liste des symboles qui clignotent
void clearListe(QuiClignote * a){
	memset(a->indices,0,a->taillePile);
	a->taillePile=0;
}

// enleve un symbole de la pile (il ne clignotera plus)
void depile(QuiClignote * a, unsigned char b){
	unsigned char i=0;
	if(a->taillePile > 0){
		while(i <= a->taillePile-1 && a->indices[i] != b ){
			i++; // on va au pire arriver � i==a->taillePile apres cette instruction
		}

		 // si on a pas trouv� b, ie si on a d�pass� la taille de la pile
		if(i == a->taillePile){
			// on ne fait rien
		} else{ // si on a pas depass� la taille de la pile
			// on decale d'un rang en arriere tous les elements a partir de b
			//(en ecrasant b avec le membre suivant).
			// on va jusqu'� i+1==a->taillePile-1 (bout de la pile)
			for( ; i <= a->taillePile-2 ;i++){
				a->indices[i]=a->indices[i+1];
			}

			// on ecrase le bout de la pile qu'on vient de copier sur la case d'avant
			a->indices[a->taillePile-1]=0;

			// on decremente la taille de la pile de 1 (on a enlev� b)
			a->taillePile--;
		}
	}
}

//////////////////////////////////////////

// affiche sur l'écran HW une paire de 7 segments, selon ce qui est marqué dans l'écran SW
void afficher7Seg(unsigned char a, unsigned char b){
	switch(ecran.aff7Seg[a][b].type){
	case SPECIAL1_7:
		commentAfficherScoreJeu(&scoreJeu0[a]);
		break;
	case RIEN_7:
		effacer7Seg(a,2*b);
		effacer7Seg(a,2*b+1);
		break;
	case NB:
		if (ecran.aff7Seg[a][b].contenu.nbToDisplay.que2Chiffres)
			afficherNbA2ChiffresSur7Seg(*(ecran.aff7Seg[a][b].contenu.nbToDisplay.nb),a,2*b+1);
		else
			afficherNbSur7Seg(*(ecran.aff7Seg[a][b].contenu.nbToDisplay.nb),a,2*b+1);
		break;
	case TOURNANT:
		afficherTournant(a,b);
		break;
	}
}

// affiche sur l'écran HW une ligne de 14 segments, selon ce qui est marqué dans l'écran SW
void afficher14Seg(unsigned char a){
	unsigned char i;
	switch(ecran.aff14Seg[a].type){
	case SPECIAL3_14:
		commentAfficher24HMode();
		break;
	case SPECIAL2_14:
//		commentPlacerDansEcranBlMode(1); // --> a déjà été fait, cas particulier
		break;
	case RIEN:
		effacerZone14Seg(a);
		break;
	case ONE_NB:
		if(ecran.aff14Seg[a].contenu.nbToDisplay.que2Chiffres)
			afficherNbA2ChiffresSur14Seg(*(ecran.aff14Seg[a].contenu.nbToDisplay.nb),a,4);
		else
			afficherNbSur14Seg(*(ecran.aff14Seg[a].contenu.nbToDisplay.nb),a,4);
		break;
	case CHIFFRES:
		for(i=0; i<=4; i++){
			afficherLettreSur14Seg(a,i,ecran.aff14Seg[a].contenu.lettres[i]);
		}
		break;
	case LETTRES:
		for(i=0; i<=4; i++){
			afficherLettreSur14Seg(a,i,ecran.aff14Seg[a].contenu.lettres[i]);
		}
		break;
	case DEFILEMENT:
		afficherDefilement(a);
		//updatePositionDefilement(a); // l'update se fait dans la fonction afficheDefilementAll
		break;
	}
}

// affiche sur l'écran HW un symbole, selon ce qui est marqué dans l'écran SW
// La signification de l'indice est décrite dans  lcd8a.h
// par exemple #define SYMBOL_INDEX_ALARM 2
void afficheSymbole(unsigned char indice){
	if(ecran.symboles[indice].forcerA1)
		setSymbole(indice,1);
	else if (ecran.symboles[indice].contenu != NULL){// si pas de nb pointé il n'y arien
//		if(ecran.symboles[indice].forcerA0)
//			setSymbole(indice,0);
		if (! ecran.symboles[indice].prendreLeContraire )
			setSymbole(indice,*(ecran.symboles[indice].contenu));
		else
			setSymbole(indice, ! *(ecran.symboles[indice].contenu));
	}
	else // si pas forcé à 1 et pas de nb pointé, il n'y a rien donc on l'efface
		setSymbole(indice,0);
}

///////////////////////////////////////////////////

//affiche sur l'écran HW la totalité de l'écran SW
void afficheEcranAll(){
	unsigned char i;
	for(i=0; i<NB_SYMBOLS; i++){
		afficheSymbole(i);
	}
	afficher7Seg(0,0);
	afficher7Seg(1,0);
	afficher7Seg(0,1);
	afficher7Seg(1,1);
	afficher14Seg(0);
	afficher14Seg(1);
}

// affiche ce qui clignote (utilisé toutes les demi-secondes)
void afficheQuiClignote(QuiClignote * l){ // lorsque interruption de clic
	unsigned char i,j;
	for(i=0; i<l->taillePile; i++){
		afficheSymbole(l->indices[i]);
	}
	for(i=0; i<=1;i++){
		if(l->les14Seg[i])
			afficher14Seg(i);
		for(j=0; j<=1; j++){
			if(l->les7Seg[i][j]){
				afficher7Seg(i,j);
			}
		}
	}
}

// affiche ce qui clignote (utilisé toutes les demi-secondes), ou bien efface tout ce qui clignote si on est
// dans la demi-seconde impaire
void afficheEcranClignotement(unsigned char a){ // lorsque interruption demi secondes
	int i,j;
	if (a)
		afficheQuiClignote(&(ecran.quiClignote));
	else{
		for(i=0; i<ecran.quiClignote.taillePile; i++){
			setSymbole(ecran.quiClignote.indices[i],0); // !! mettre breakpoint ici
		}
		for(i=0; i<=1;i++){
			if(ecran.quiClignote.les14Seg[i]){
				if(ecran.aff14Seg[i].type == ONE_NB && ecran.aff14Seg[i].contenu.nbToDisplay.que2Chiffres){
					effacer14Seg(i, 3);
					effacer14Seg(i, 4);
				}
				else
					effacerZone14Seg(i);
			}
			for(j=0; j<=1; j++){
				if(ecran.quiClignote.les7Seg[i][j]){
					effacer7Seg(i,2*j);
					effacer7Seg(i,2*j+1);
				}
			}
		}
	}
}

///////////////////////////////////////////////////

// mets un texte sur la ligne de 14 segments précisée par zoneNb (0=haut, 1=bas)
void mettreSurEcranTexte(unsigned char zoneNb, /*const*/ char texte[5]){ // pour la toile de fond
	ecran.aff14Seg[zoneNb].type=LETTRES;
	strncpy(ecran.aff14Seg[zoneNb].contenu.lettres,
			texte,
			5);
}

// mets un texte au clignotement, sur la ligne de 14 segments précisée par zoneNb (0=haut, 1=bas)
void mettreAuClignotementTexte(unsigned char zoneNb, char texte[5]){
	mettreSurEcranTexte(zoneNb, texte);
	ecran.quiClignote.les14Seg[zoneNb]=1;
}

///////////////////////////////////////

// mets sur l'écran SW une paire de 7 segments,
// pointant vers nb, et étant (ou pas) forcé à deux chiffres selon la valeur de que2Seg
// a vaut 0 (haut) ou 1 (bas)
// b vaut 0 (paire de 7 segments de gauche) ou 1 (paire de 7 segments de droite)
// on n'est donc plus dans le même système de coordonnées pour b que par exemple pour la fonction
// afficherNbA2ChiffresSur7Seg(unsigned char n, unsigned char a, unsigned char b);
// ceci est dû au fait que dans l'écran SW, on a choisi d'avoir seulement 4 zones de 7 segments (tableau [2][2])
// au lieu de 8 zones (tableau [2][4])
void mettreSurEcranNombre7Seg(unsigned char a, unsigned char b, /*int*/unsigned char * nb, unsigned char que2Seg){
		ecran.aff7Seg[a][b].type=NB;
		ecran.aff7Seg[a][b].contenu.nbToDisplay.que2Chiffres=que2Seg;
		ecran.aff7Seg[a][b].contenu.nbToDisplay.nb=nb;
}

// mets au clignotement un nombre, dans les coordonnées (a,b) appartenants chacun à {0; 1} comme dans
// la fonction précédente
void mettreAuClignotementNombre7Seg(unsigned char a, unsigned char b, /*int*/unsigned char* nb, unsigned char que2Seg){
	mettreSurEcranNombre7Seg(a,b,nb,que2Seg);
	ecran.quiClignote.les7Seg[a][b]=1;
}



/////////////////////////////////////////////////////

// mets sur une des lignes de 14 segments un nombre
void mettreSurEcranNombre14Seg(unsigned char a, unsigned char * nb, unsigned char que2Seg){
	ecran.aff14Seg[a].type=ONE_NB;
	ecran.aff14Seg[a].contenu.nbToDisplay.que2Chiffres=que2Seg;
	ecran.aff14Seg[a].contenu.nbToDisplay.nb=nb;
}

// mets sur une des lignes de 14 segment un nombre qui va clignoter
void mettreAuClignotement14Seg(unsigned char a, unsigned char * nb, unsigned char que2Seg){
	mettreSurEcranNombre14Seg(a,nb,que2Seg);
	ecran.quiClignote.les14Seg[a]=1;
}

/////////////////////////////////////////

// mets un texte défilant sur une des lignes de 14 segment (dans l'ecran SW)
void mettreAuClignotementDefilement(unsigned char zoneNb, char * texte){
	mettreAuDefilement(zoneNb, texte);
	ecran.quiClignote.les14Seg[zoneNb]=1;
}


////////////////////////////////////////

// mets un symbole activé sur l'écran SW
void mettreSurEcranForceSymbole(unsigned char indice){
	ecran.symboles[indice].forcerA1=1;
	depile(&(ecran.quiClignote), indice); // ne clignote plus
	setSymbole(indice,1); // normalement fait lors du afficheEcranAll, mais au cas o�
}

// Enlève un symbole de l'écran
void enleverSymboleDeLEcran(unsigned char indice){
	ecran.symboles[indice].contenu=NULL;
}

// mets à l'écran un symbole, qui sera actif seulement si le booléen pointé par contenu vaut 1,
// sauf si on prends la variable d'entrée "contraire" valant 1.
// Dans ce cas, le symbole représentera l'inverse du booléen pointé
void mettreSurEcranPasForceSymbole(unsigned char indice, unsigned char * contenu, unsigned char contraire){
	ecran.symboles[indice].contenu=contenu;
	ecran.symboles[indice].prendreLeContraire=contraire;
	ecran.symboles[indice].forcerA1=0;

	// normalement fait lors du afficheEcranAll, mais au cas o� :
//	setSymbole(indice, ((contraire + (*contenu))%2));
}

// Force un symbole à clignoter
void mettreAuClignotementForceSymbole(unsigned char indice){
	ecran.symboles[indice].forcerA1=1;
	empile(&(ecran.quiClignote), indice);
}

// Mets un symbole à clignoter si la valeur pointé par contenu vaut 1
// La règle s'inverse si contraire vaut 1
void mettreAuClignotementPasForceSymbole(unsigned char indice, unsigned char * contenu, unsigned char contraire){
	ecran.symboles[indice].contenu=contenu;
	ecran.symboles[indice].prendreLeContraire=contraire;
	ecran.symboles[indice].forcerA1=0;
	empile(&(ecran.quiClignote), indice);
	// on le fait non conditionnel car de toute façon,
	// lorsque la fonction afficheEcranClignotement, puis afficheQuiClignote est appelée,
	//afficheSymbole(ecran.quiClignote.indices[i]) va faire setSymbole(indice,*(ecran.symboles[indice].contenu));
	// --> le clignotement va clignoter sur rien du tout finalement, donc ne va pas être visible
	// cependant si le contenu passe à 1 ça clignotera.
}

// Mets au clignotement une varAff
void mettreAuClignotementVarAff(VarAff * varAff){
	placerDansEcran(varAff);

	switch(varAff->type){
	case INT7:
		ecran.quiClignote.les7Seg[varAff->contenu.int7Seg.x][varAff->contenu.int7Seg.y]=1;
		break;
	case INT14:
		ecran.quiClignote.les14Seg[varAff->contenu.int14Seg.x]=1;
		break;
	case BOOL:
		/*empile(&(ecran.quiClignote), varAff->contenu.boolAff.index);
		if(varAff->contenu.boolAff.index_contraire_used)
			empile(&(ecran.quiClignote), varAff->contenu.boolAff.index_contraire);
		break;*/
		 mettreAuClignotementPasForceSymbole (
		     varAff->contenu.boolAff.index ,
		     &(varAff->nb),
		      0);
				if(varAff->contenu.boolAff.index_contraire_used)
		    mettreAuClignotementPasForceSymbole (
		      varAff->contenu.boolAff.index_contraire ,
		     &(varAff->nb),
		      1);
		break;
	case STR:
		ecran.quiClignote.les14Seg[varAff->contenu.stringChoice.zone14Seg]=1;
		break;
	case PLUSIEURS_CHIFFRES:
		break; // pourrait etre codé mais pas utilisé pour l'instant
	case SPECIAL1:
		ecran.quiClignote.les14Seg[varAff->contenu.varAffSpecial1.x]=1;
		break;
	case SPECIAL2:
		ecran.quiClignote.les7Seg[varAff->contenu.varAffSpecial2.x][varAff->contenu.varAffSpecial2.y]=1;
		break;
	case SPECIAL3:
		ecran.quiClignote.les14Seg[0]=1;
		break;
	case UNDEFINED:
		break;
	}
}

//////////////////////////////////////

// desactive tous les clignotements
void desactiverClignotement(){
	clearListe(&(ecran.quiClignote));
}

// vide l'écran SW
void viderEcran(){
	memset(&ecran,0,sizeof(Ecran));
	//clearLcd(); // fait juste apres en pratique
}
