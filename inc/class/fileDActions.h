#ifndef FILEACTIONS_H_
#define FILEACTIONS_H_


// Sert ainsi à éviter les depassements de memoires dus a un bug.
// Si on arrive dans ce cas, on vide la liste d'actions et on reinitialise la montre.

// Taille de la file auxiliaire ( ListeDActionsAMettreDansLaFile )
#define TAILLE_FILE_AUX 10
#define MAX_SIZE_FILE_ACTIONS 6

typedef struct CellAction_{
	struct CellAction_ * actionAFaireApres;
	void (* action)(void);
	unsigned short attenteEnPlus;
} CellAction;
typedef CellAction * pCellAction; // can be used if we don't want the * to appear

typedef struct FileDActions_{
	unsigned char size; // can add an action only if size <= MAX_SIZE_FILE_ACTIONS
	pCellAction actionAFaireEnPremier; // la premiere action a faire
	unsigned char estEnTrainDEtreModifiee;
} FileDActions;

typedef struct ActionToWait_{
	void (* actionAFaire)(void);
	unsigned short attente; // en 128 eme de secondes
} ActionToWait;

typedef struct ListeDActionsAMettreDansLaFile_{
//	unsigned char size;
	unsigned char iMin;
	unsigned char iMax;
	ActionToWait actionsToWait[TAILLE_FILE_AUX];
}ListeDActionsAMettreDansLaFile;

extern ListeDActionsAMettreDansLaFile listeDActionsAMettreDansLaFile;
extern FileDActions fileDActions;
extern unsigned char cellsUtilisees[MAX_SIZE_FILE_ACTIONS];

void transfererActionsPasTraitees();
void initFileDActions();
void waitAndDoFile(
	unsigned short count ,
	void (* actionAFaire)(void),
	FileDActions * pFile);
void fairePuisDefilerUneAction(FileDActions * pFile);
void defileAllNecessaryActions(	FileDActions * pFile );
void enleverUneAction(FileDActions * pFile, void (* actionAFaire)(void), unsigned char faireLAction );




#endif /* FILEACTIONS_H_ */
