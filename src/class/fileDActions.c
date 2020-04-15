#include "fileDActions.h"
#include "class/time.h"
#include "stdlib.h"
#include "globalVar.h"
#include "t16_ch0_smallDelays.h"
#include "stddef.h" // for NULL
#include <string.h>

FileDActions fileDActions;
ListeDActionsAMettreDansLaFile listeDActionsAMettreDansLaFile;
CellAction cells[MAX_SIZE_FILE_ACTIONS];
//FileDActions fileDActionsVides;
unsigned char cellsUtilisees[MAX_SIZE_FILE_ACTIONS];

void transfererActionsPasTraitees(){
	// si entre temps des choses ont été mises dans la liste d'actions, on les transfert dans la file
	while(listeDActionsAMettreDansLaFile.iMin != listeDActionsAMettreDansLaFile.iMax && fileDActions.size < MAX_SIZE_FILE_ACTIONS){
		waitAndDoFile(listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMin].attente,
				listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMin].actionAFaire,
				&fileDActions);
		augmenterModulo(listeDActionsAMettreDansLaFile.iMin, 0, TAILLE_FILE_AUX-1);
	}

	if(fileDActions.actionAFaireEnPremier != NULL && fileDActions.size>0){
		presetT16Ch0CountShortTimes( fileDActions.actionAFaireEnPremier->attenteEnPlus );
		startT16Ch0();
	}
}


// Initialisation de la file d'actions
// En pratique cette fonction n'est appelé qu'après un reset lors de la fonction d'initialisation
// appelée "commence()".
void initFileDActions(FileDActions * pFileDActions){
//	unsigned char i=0;
//	CellAction * p;
	// maybe TODO ?  Free toutes les variables éventuellement allouées ?
	// Par exemple si reset sw apres appui sur tous les boutons ?
	// Mais risqué, si on fait un free et que c'est faux ?
	// Les free sont ils faits automatiquement avec ansi_InitMalloc ou lors du reset sw ?
	// je pense que ça va mais si doute --> demandez à Eiji l'ingenieur d'Epson
	pFileDActions->actionAFaireEnPremier=NULL;
	pFileDActions->size=0; // can add an action only if size <= MAX_SIZE_FILE_ACTIONS
	pFileDActions->estEnTrainDEtreModifiee=0;

	//listeDActionsAMettreDansLaFile.size=0;
	memset(&listeDActionsAMettreDansLaFile, 0, sizeof(ListeDActionsAMettreDansLaFile));

	memset(&(cellsUtilisees[0]),0,MAX_SIZE_FILE_ACTIONS);

//	fileDActionsVides.size=MAX_SIZE_FILE_ACTIONS;
//	fileDActionsVides.actionAFaireEnPremier=&(cells[0]);
//	for(i=0; i<MAX_SIZE_FILE_ACTIONS; i++){
//		p=&(cells[i]);
//		p->actionAFaireApres=&(cells[(i+1)%MAX_SIZE_FILE_ACTIONS]);
//	}
//	fileDActionsVides.estEnTrainDEtreModifiee=0;
}


CellAction * alloue(){
	unsigned char i=0;
	while(cellsUtilisees[i] && i < MAX_SIZE_FILE_ACTIONS ){
		i++;
	}
	if(i < MAX_SIZE_FILE_ACTIONS){
		cellsUtilisees[i]=1;
		return &(cells[i]);
	} else { // --> ne doit pas arriver car on ne remplit pas si on a pas la place
		return &(cells[0]); //NULL ?
	}
}

void libere(CellAction * p){
	unsigned long p2 = (unsigned long)p-(unsigned long)(&(cells[0]));
	unsigned int p3 = (unsigned int)p2/sizeof(CellAction);
	cellsUtilisees[p3]=0;
}

// Comme un waitAndDo, mais plus safe
// Attention le count est en 128eme de secondes.
// En pratique, on utilise waitAndDo et waitAndDoShortTimes qui sont dans t16_ch0_smallDelays.c et qui appellent
// waitAndDoFile.
void waitAndDoFile(
	unsigned short count ,
	void (* actionAFaire)(void),
	FileDActions * pFile)
{
	pCellAction newPCell=NULL;

	pCellAction actionAFaireAvant;
	pCellAction actionAFaireApres;
	unsigned short attenteEnPlus;
//	unsigned char i;
	unsigned char difference;
	unsigned char indice;

	// Si la limite d'actions n'a pas été dépassée
	if(pFile->size < MAX_SIZE_FILE_ACTIONS){
		// On precise que la file est en train d'etre modifiee
		pFile->estEnTrainDEtreModifiee=1;

//		newPCell=malloc(sizeof(CellAction));
		newPCell = alloue();
		newPCell->action=actionAFaire;
		newPCell->actionAFaireApres=NULL;
		newPCell->attenteEnPlus=count;

	if(pFile->size == 0){
		pFile->actionAFaireEnPremier=newPCell;
	}else{
		// on suppose qu'on doit attendre count au depart
		attenteEnPlus=count;

		// on initialise l'action a faire apres comme la premiere (on suppose qu'on est en fait la premiere action a faire)
		actionAFaireApres=pFile->actionAFaireEnPremier;
		if(actionAFaireApres != NULL)
			actionAFaireApres->attenteEnPlus = getT16Ch0Count();

		// on suppose donc au depart qu'aucune action n'est a faire avant nous
		actionAFaireAvant=NULL;

		// on suppose qu'on se trompe pour pouvoir rentrer dans la boucle
		difference=1;
		// tant qu'on se trompe et tant qu'il reste une action à faire apres dans la liste, on regarde si c'est bon pour la suivante
		while(actionAFaireApres != NULL && difference>0){
			// on regarde combien on a de temps a attendre en plus
			difference=attenteEnPlus - actionAFaireApres->attenteEnPlus;

			// si on doit attendre (strictement) plus, l'action à faire juste apres n'est pas celle-là, on regarde donc la suivante
			if(difference>0){
				actionAFaireAvant = actionAFaireApres; // celle qu'on pensait apres est en fait avant
				actionAFaireApres = actionAFaireApres->actionAFaireApres; // on regarde la suivante
				attenteEnPlus = difference; // on s'est rendu compte qu'on devait attendre ça de plus que l'action devant nous
			}
		}

		// On remplis newPCell avec les parametres trouves
		newPCell->actionAFaireApres = actionAFaireApres;
		newPCell->attenteEnPlus = attenteEnPlus;

		// Si il y a une action apres nous,
		// Il faut changer le temps d'attente de cette action,
		// car ce temps est compté en relatif par rapport à nous et pas à l'action avant nous.
		if(actionAFaireApres != NULL){
			actionAFaireApres->attenteEnPlus -= attenteEnPlus;
			// c'est toujours positif car si on est sorti de la boucle et qu'on a qqchose apres nous, c'est que difference <= 0,
			// c-a-d newPCell->actionAFaireApres->attenteEnPlus >= newPCell->attenteEnPlus
		}

		// si l'action a faire juste apres est la premiere, on est en fait la premiere action a faire
		if(actionAFaireApres == pFile->actionAFaireEnPremier){
			pFile->actionAFaireEnPremier=newPCell;
		}

		// s'il y a une action à faire juste avant, on est donc juste apres elle.
		if(actionAFaireAvant != NULL){
			actionAFaireAvant->actionAFaireApres = newPCell;
		}
	}

		// on a rajoute une action a faire
		pFile->size ++;

		// La file n'est plus en train d'etre modifiee
		pFile->estEnTrainDEtreModifiee=0;

	}
	else{
		//commence(0); --> non finalement pas la peine de tout casser pour ça, on la met de côté.
		// --> non en fait testé et bug, cree une boucle infinie : donc ne PAS decommenter les lignes suivantes :
//		listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMax].attente=128*count;
//		listeDActionsAMettreDansLaFile.actionsToWait[listeDActionsAMettreDansLaFile.iMax].actionAFaire=actionAFaire;
//		augmenterModulo(listeDActionsAMettreDansLaFile.iMax, 0, TAILLE_FILE_AUX-1);
	}
}

// pas de vérification que la liste n'est pas vide , on suppose que la verif a été faite avant l'appel de la fonction
// en fait defiler puis faire, sinon bug
// on ne l'appelle que de t16_ch0_smallDelays, fonction intT16Ch0(), et dans ce cas le counter est en pause
// puisqu'on a touché l'interruption --> pas la peine d'appeler stopT16Ch0();
void fairePuisDefilerUneAction(FileDActions * pFile){
	void (* action)(void);
	pCellAction p;
//	unsigned char i;

	pFile->estEnTrainDEtreModifiee=1;

	// on sauvegarde l'action
	action = pFile->actionAFaireEnPremier->action;
	// on sauvegarde le pointeur sur la cell
	p=pFile->actionAFaireEnPremier;

	// on fait l'action
	(*action)();
	// on fait defiler
	pFile->actionAFaireEnPremier = pFile->actionAFaireEnPremier->actionAFaireApres;
	// on precise qu'on a enlevé une action
	(pFile->size)--;
	// on libere la memoire
//	free(p);
	libere(p);

	pFile->estEnTrainDEtreModifiee=0;

	transfererActionsPasTraitees();
}

// Permet d'enlever une action de la file
// si on veut finalement la faire tout de suite, on met l'argument faireLAction à 1
// sinon à 0
void enleverUneAction(FileDActions * pFile, void (* actionAFaire)(void), unsigned char faireLAction ){
	pCellAction p=pFile->actionAFaireEnPremier;
	pCellAction pBefore=NULL;
	unsigned char i;
	unsigned char actionFaite=0;

	stopT16Ch0();

	if (p == NULL || pFile->size==0){
		if(faireLAction){
			(*actionAFaire)();
		}
		transfererActionsPasTraitees(); // --> pas forcement utile mais ne coûte rien
		return;
	}

	else{
		pFile->estEnTrainDEtreModifiee=1;
		i=0;
		while(p != NULL && i<pFile->size){
			i++;
			if(p->action != actionAFaire){
				pBefore=p;
				p=p->actionAFaireApres;
			}
			else{
				// on fait l'action
				if(faireLAction){
					(*actionAFaire)();
				}
				actionFaite=1;

				// On enleve l'action
				if(pBefore != NULL)
					pBefore->actionAFaireApres = p->actionAFaireApres;
				else
					pFile->actionAFaireEnPremier = p->actionAFaireApres;

				// on ajoute de l'attente pour l'action suivante
				if(p->actionAFaireApres != NULL)
					p->actionAFaireApres->attenteEnPlus += p->attenteEnPlus;

				// on precise qu'on a enleve une fonction
				pFile->size--;

				// on libere la memoire
//				free(p);
				libere(p);

				// on sort de la boucle
				break;
			}
		}

		// si elle n'était en fait pas dans la file d'attente, on la fait quand même
		if(! actionFaite){
			if(faireLAction){
				(*actionAFaire)();
			}
		}

		if(pFile->size == 0)
			pFile->actionAFaireEnPremier = NULL;
		if(pFile->actionAFaireEnPremier == NULL)
			pFile->size = 0;

		pFile->estEnTrainDEtreModifiee=0;

		transfererActionsPasTraitees();
	}
}

//unsigned char isEmpty( FileActions * pFileActions ){
//	return (pFileActions->size == 0);
//}

// called each second
//void defileAllNecessaryActions(	FileDActions * pFile ){
//	if( pFile->size != 0 ){
//		pFile->actionAFaireEnPremier->attenteEnPlus --;
//		while( pFile->actionAFaireEnPremier->attenteEnPlus == 0 ) {
//			fairePuisDefilerUneAction(pFile);
//			// wait_general(10) // --> utile ?
//			if(pFile->size == 0){ // si la liste est vide on sort du while
//				break;
//			}
//		}
//	}
//}
