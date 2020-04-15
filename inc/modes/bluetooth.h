#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define LENGTH_STATISTICS 57
#define LENGTH_SCORE_UPDATE 9
#define LENGTH_MATCH_SETUP 5

#include "class/varAff.h"

//////////////////
// Struct pour la bluetooth


typedef union {
	 unsigned char reg[LENGTH_SCORE_UPDATE];
	struct {
		 unsigned char changeSide : 1;
		 unsigned char tieBreak : 1;
		 unsigned char superTieBreak : 1;
		 unsigned char counterAuService : 1;
		 unsigned char gameOver : 1;
		 unsigned char	unused_1 : 3;

		 unsigned char	setsWonByCounter : 2;
		 unsigned char	setsWonByPartner : 2;
		 unsigned char	counterAbandon : 1;
		 unsigned char	partnerAbandon : 1;
		 unsigned char	unused_2 : 2;

		 unsigned char	currentGameScoreCounter ;
		 unsigned char	currentGameScorePartner ;

		unsigned char	counter1 : 4;
		unsigned char	partner1 : 4;
		unsigned char	counter2 : 4;
		unsigned char	partner2 : 4;
		unsigned char	counter3 : 4;
		unsigned char	partner3 : 4;
		unsigned char	counter4 : 4;
		unsigned char	partner4 : 4;
		unsigned char	counter5 : 4;
		unsigned char	partner5 : 4;
	} bit;
} ScoreUpdate;

typedef union{
	volatile unsigned char reg[LENGTH_STATISTICS];
	struct {
	volatile unsigned char matchUUID[4]; // Match UUID provided by server
	volatile unsigned char matchDateYear ;
	volatile unsigned char matchDateMonth;
	volatile unsigned char matchDateDay;
	volatile unsigned char setsCounter:2;
	volatile unsigned char setsPartner:2;
	volatile unsigned char counterAbandonStats:1;
	volatile unsigned char partnerAbandonStats:1;
	volatile unsigned char unused_1:2;

	volatile unsigned char spare1;
	volatile unsigned char spare2;
	volatile unsigned char spare3;
	volatile unsigned char spare4;

//	StatistiquesSet statsSet[5];
	// --> cela avait ete fait ainsi avant mais avait engendre des problèmes
	// donc nous avons finalement fait ca de maniere moins elegante avec du copie/colle :
	volatile unsigned char setScoreCounter1:4;
	volatile unsigned char setScorePartner1:4;
	volatile unsigned char setTime1;
	volatile unsigned char setSceGagnantCounter1;
	volatile unsigned char setSceGagnantPartner1;
	volatile unsigned char setScePerdantCounter1;
	volatile unsigned char setScePerdantPartner1;
	volatile unsigned char setJeuxBlancsCounter1:4;
	volatile unsigned char setJeuxBlancsPartner1:4;
	volatile unsigned char set1Spare1;
	volatile unsigned char set1Spare2;

	volatile unsigned char setScoreCounter2:4;
	volatile unsigned char setScorePartner2:4;
	volatile unsigned char setTime2;
	volatile unsigned char setSceGagnantCounter2;
	volatile unsigned char setSceGagnantPartner2;
	volatile unsigned char setScePerdantCounter2;
	volatile unsigned char setScePerdantPartner2;
	volatile unsigned char setJeuxBlancsCounter2:4;
	volatile unsigned char setJeuxBlancsPartner2:4;
	volatile unsigned char set2Spare1;
	volatile unsigned char set2Spare2;

	volatile unsigned char setScoreCounter3:4;
	volatile unsigned char setScorePartner3:4;
	volatile unsigned char setTime3;
	volatile unsigned char setSceGagnantCounter3;
	volatile unsigned char setSceGagnantPartner3;
	volatile unsigned char setScePerdantCounter3;
	volatile unsigned char setScePerdantPartner3;
	volatile unsigned char setJeuxBlancsCounter3:4;
	volatile unsigned char setJeuxBlancsPartner3:4;
	volatile unsigned char set3Spare1;
	volatile unsigned char set3Spare2;

	volatile unsigned char setScoreCounter4:4;
	volatile unsigned char setScorePartner4:4;
	volatile unsigned char setTime4;
	volatile unsigned char setSceGagnantCounter4;
	volatile unsigned char setSceGagnantPartner4;
	volatile unsigned char setScePerdantCounter4;
	volatile unsigned char setScePerdantPartner4;
	volatile unsigned char setJeuxBlancsCounter4:4;
	volatile unsigned char setJeuxBlancsPartner4:4;
	volatile unsigned char set4Spare1;
	volatile unsigned char set4Spare2;

	volatile unsigned char setScoreCounter5:4;
	volatile unsigned char setScorePartner5:4;
	volatile unsigned char setTime5;
	volatile unsigned char setSceGagnantCounter5;
	volatile unsigned char setSceGagnantPartner5;
	volatile unsigned char setScePerdantCounter5;
	volatile unsigned char setScePerdantPartner5;
	volatile unsigned char setJeuxBlancsCounter5:4;
	volatile unsigned char setJeuxBlancsPartner5:4;
	volatile unsigned char set5Spare1;
	volatile unsigned char set5Spare2;
} bit;
} MatchStatistics ;


typedef union{
	unsigned char reg[LENGTH_MATCH_SETUP];
	struct {
		unsigned char matchFormat:1;
		unsigned char counterServes:1;
		unsigned char nGame:2;
		unsigned char advantage:1;
		unsigned char tb:1;
		unsigned char isShortMatch:1;
		unsigned char stb:1;

		unsigned char matchUUID[4];
	} bit;
} MatchSetup;

extern unsigned char flagEndMatchNow;
extern unsigned char searchOtherDevice;
extern unsigned char oadUpdateSuccessfull;
extern unsigned char matchUUID[4];
extern unsigned char countDownPairingStopped;
extern char nomPeer[20]; //={0};
extern ScoreUpdate scoreUpdate;
extern unsigned char peerConnected;
extern unsigned char countDownBluetooth;
extern MatchSetup matchSetup;
extern VarAff shouldStartOad;
extern char laterOrNow[2][5];

//////////////////////////
// 1.1) Defines relatifs au bluetooth

#define BL_OFF 0
#define BL_COUNTER 1
#define BL_PARTNER 2
//#define BL_SEARCHING_TO_RECONNECT 3

#define CC254X_RESET P3DAT_P31OUT
//#define UART_TX P01
//#define UART_RX P03
#define CC254X_WAKEUP P3DAT_P32OUT
//#define CC254X_UNUSED P02

extern VarAff btConnexionTimeLeft;
extern VarAff bluetoothMode;

void askOadToStart();
void askOadToStartWithoutReset();
void endTheScreenOfSetupAborted();
void actionMettreModeSuivantPairing();
void setMatchSetup();
void getMatchSetup();
void storeMatchSetup(unsigned char *data);
void sndMatchSetup();
void initConstantesBluetooth();
void initFout();
void initDiversBluetooth();
void reset_radio();
void wakeup_ble();
void arret_ble();
void rcvTennisScoreFromBluetooth();
void sndTennisScoreWithBluetooth();


void actionBluetoothPartnerShow5Sec();
void actionSecondeBluetoothWaitConnexion();
void initConnexion();
//void prepareDisplayBluetoothPairing();
void prepareDisplayBluetoothPairing();
void ParseFrame(void);
void finirPairing();
//void commentAfficherBlMode(VarAff* v);//unsigned char a, unsigned char b, unsigned char n);
void commentPlacerDansEcranBlMode();
void sndScoreBluetooth200Ms();
void sndStatistics();

#endif /* BLUETOOTH_H_ */
