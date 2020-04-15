#ifndef TENNIS_H_
#define TENNIS_H_

#include "class/varAff.h"

#define NB_TOUR_SAUVEGARDES_MAX 6

///////////////////////////////
// 3.3) Variables du tennis

extern unsigned short tennisStartingMinute;
extern unsigned char tennisOntLAirDEtreEnTrainDeJouer;
extern unsigned short tennisLastPointChangeMinute;

extern unsigned char suivantTennis[17];

extern unsigned char tennisMinute;
extern unsigned char tennisHour;
extern unsigned short tennisSetMinutes[5];
extern unsigned char nbScoresSauvegardes;

extern unsigned char scoreManche[NB_TOUR_SAUVEGARDES_MAX+1][2][5];
extern unsigned char servGagn[NB_TOUR_SAUVEGARDES_MAX+1][2][5];
extern unsigned char servPerd[NB_TOUR_SAUVEGARDES_MAX+1][2][5];
extern unsigned char jeuxBlancs[NB_TOUR_SAUVEGARDES_MAX+1][2][5];
extern unsigned char nbManches[NB_TOUR_SAUVEGARDES_MAX+1][2]; // = scorePartie

extern unsigned char serveurDebutTb[NB_TOUR_SAUVEGARDES_MAX+1];
extern unsigned char chgtDeCoteEnCours[NB_TOUR_SAUVEGARDES_MAX+1];
extern unsigned char tennisMode[1+NB_TOUR_SAUVEGARDES_MAX]; // ??

extern unsigned char scoreJeu[NB_TOUR_SAUVEGARDES_MAX][2]; // avantage = 50
extern unsigned char jeSuisAuService[NB_TOUR_SAUVEGARDES_MAX];

extern char typeTbTexte[4][5];
extern char bluetoothStrings[3][5];

extern VarAff scoreManche0;//[5]; // existe pour l'affichage mais les vrais nb ne sont pas dedans
extern VarAff scoreJeu0[2]; // avantage = 50
extern VarAff jeSuisAuService0;
//extern unsigned char tennisMode0; ??

extern VarAff nbManchesGagnantes; // (1 2 ou 3)
extern VarAff nbJeuxGagnantsUneManche; //(3 a 6)
extern VarAff avantageActive; //(par defaut active, ie si 40/40, on ne gagne pas apres, il faut d'abord passer par l'avantage)
extern VarAff tbActive; //(a 7 ou pas de jeu decisif. Par defaut a 7. Attention si il n'y a pas de jeu decisif, pb d'affichage possible si les scores depassent dix jeux, sauf eventuellement si c'est le dernier set.)
extern VarAff stbActive; //(a 10, pour les doubles, compte pour 1 manche entiere.)
extern VarAff tbType;
extern ChiffresAff * c0;

extern unsigned char abandonne[2];

void mettreModeTennis();
void actionsCounterApresUpdateScore();
unsigned char tbCommence();
unsigned char stbCommence();
void prepareDisplayTennis(unsigned char m);
void actionModeTennis(unsigned char typeEvenement);
unsigned char suivant(unsigned char a);
unsigned char tbEnCours();
unsigned char stbEnCours();
unsigned char numManche();
unsigned char matchFini();
unsigned char matchEnCours();
unsigned char chgtCoteTb();
unsigned char chgtCoteHorsTb();
void saveSit();
void loadOldSit();
void augmenterScore(unsigned char joueur);
unsigned char tennisCommence();
void afficherjeSuisAuService();
void afficheTennisEndBasis();
void afficherTennisBasis();
void razTennis();
void initTennis(void);
void afficherTennis7Seg();
void actionFinClignotementChangeSide();
void actionFinClignotementTbOuStb();
//void commentAfficherScoreJeu(unsigned char a, unsigned char b, unsigned char n);
void commentAfficherScoreJeu(VarAff * v);
void commentPlacerDansEcranScoreJeu(VarAffSpecial1 * v);
unsigned char chgtCote();
void abandon(unsigned char joueur);

#endif /* TENNIS_H_ */
