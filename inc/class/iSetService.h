/**************************************************************************************************
  Filename:       iSetService.h
  Revised:        $Date $
  Revision:       $Revision $

  Description:    This file contains the TxWatch service definitions and
                  prototypes.

  Copyright 2014 Jean-Christophe Billard. All rights reserved.

**************************************************************************************************/

#ifndef ISETSERVICE_H
#define ISETSERVICE_H

#ifdef __cplusplus
extern "C"
{
#endif

  /**
 * GATT Custom Service UUIDs
 */
#define ISET_PARTNER_SERV_UUID          0x2BB1  // TxWatch Partner service
#define ISET_SMARTPHONE_SERV_UUID       0x2BB2  // TxWatch Smartphone service
#define ISET_OAD_SERV_UUID              0x2BB3  // TxWatch OAD firmware service

#define ISET_MATCH_SETUP_UUID            0x2BC1  // Match setup statuts
#define ISET_SCORE_UPDATE_UUID           0x2BC2  // Score Vector service
#define ISET_SCORE_STATS_UUID            0x2BC3  // Score Vector service


/*********************************************************************
 * CONSTANTS
 */

// TxWatch Service Parameters
#define ISET_MATCH_SETUP                         0
#define ISET_MATCH_SETUP_CHAR_CFG                1
#define ISET_SCORE_VECTOR                        2
#define ISET_SCORE_VECTOR_CHAR_CFG               3

// Position  in attribute array of all TxWatch fields
#define ISET_MATCH_SETUP_POS                     2
#define ISET_MATCH_SETUP_CHAR_CONFIG_POS         3
#define ISET_SCORE_UPDATE_POS                    4
#define ISET_SCORE_UPDATE_CHAR_CONFIG_POS        5
#define ISET_SCORE_STATISTICS_POS                6
#define ISET_SCORE_STATISTICS_CHAR_CONFIG_POS    7

  /* ---------- Score vector structure -----------
  First Byte : (bit 7 - Will have complementary batch)
   (bit 6 to 0 - Batch payload) (less or equal to 21)
  Remainder of bytes is payload (21 bytes)
  */


// Length of bytes
#define ISET_MATCH_SETUP_LEN                     1
#define ISET_SCORE_VECTOR_MAXLEN                 (ATT_MTU_SIZE -5)

// Maximum length of txWatch
#define ISET_MEAS_MAX  (ATT_MTU_SIZE -5)

// Values for TxWatch Mode
#define TXWATCH_COUNTER                 0x00
#define TXWATCH_PARTNER                 0x01


// TxWatch Service bit fields
#define TXWATCH_SERVICE          0x00000001

// Callback events
#define TXWATCH_MS_IND_ENABLED        1
#define TXWATCH_MS_IND_DISABLED       2
#define TXWATCH_SV_IND_ENABLED        3
#define TXWATCH_SV_IND_DISABLED       4





  /* =================== TXW-Seiko Specific Macros =================== */

  /* the Base Mask Make macro */
#define ISET_BMMK(PER_REG_FIELD)  (ISET_##PER_REG_FIELD##_BASE_REG)

  /* the Field MaKe macro */
#define ISET_FMK(PER_REG_FIELD, val) (((val) << ISET_##PER_REG_FIELD##_SHIFT) & ISET_##PER_REG_FIELD##_MASK)

  /* the Field EXTract macro */
#define ISET_FEXT(reg, PER_REG_FIELD)  (((reg) & ISET_##PER_REG_FIELD##_MASK) >> ISET_##PER_REG_FIELD##_SHIFT)

  /* the Field INSert macro */
#define ISET_FINS(reg, PER_REG_FIELD, val) ((reg) = ((reg) & ~ISET_##PER_REG_FIELD##_MASK) | ISET_FMK(PER_REG_FIELD, val))


  /* the "token" macros */

  /* the Field MaKe (Token) macro */
#define ISET_FMKT(PER_REG_FIELD, TOKEN) ISET_FMK(PER_REG_FIELD, ISET_##PER_REG_FIELD##_##TOKEN)

  /* the Field INSert (Token) macro */
#define ISET_FINST(reg, PER_REG_FIELD, TOKEN) ISET_FINS((reg), PER_REG_FIELD, ISET_##PER_REG_FIELD##_##TOKEN)



/*********************************************************************
 * TYPEDEFS
 */

	// Define commands
  typedef enum {
    BLE_CMD = 0x01,
    BLE_REPORT, // 2
    MATCH_PARAMETERS, // 3
    MATCH_PARAMETERS_REQUEST, // 4
    CONNECTION_SETUP, // 5
    SCORE_UPDATE, // 6
    MATCH_STATISTICS, // 7
    MATCH_STATISTICS_REQUEST, // 8
    CC254X_MAC_ADDRESS, // 9
    CC254X_SW_VERSION, // A
    CC254X_ALIAS, // B
    RADIO_TESTS,	// CC254X_TEST // C
    CC254X_OAD_STATUS, // D
	SEIKO_SW_VERSION, // E
	RESET_REQUEST, 	// We request a software RESET // F
	NOT_A_VALID_CMD // 0x10
  }txw_commands;


  /*------------ WATCH_CMD fields ------------*/
#define ISET_WATCH_CMD_BLE_MODE_MASK            (0x02u)
#define ISET_WATCH_CMD_BLE_MODE_SHIFT           (0x01u)
#define ISET_WATCH_CMD_BLE_MODE_RESETVAL        (0x00u)

#define ISET_WATCH_CMD_BLE_RESET_MASK            (0x01u)
#define ISET_WATCH_CMD_BLE_RESET_SHIFT           (0x00u)
#define ISET_WATCH_CMD_BLE_RESET_RESETVAL        (0x00u)


  /*------------ CONNECTION_SETUP fields ------------*/
#define ISET_CONN_SETUP_NEW_MASK                (0x01u)
#define ISET_CONN_SETUP_NEW_SHIFT               (0x00u)
#define ISET_CONN_SETUP_NEW_RESETVAL            (0x00u)


#define ISET_CONN_SETUP_PEER_STATUS_MASK        (0x06u)
#define ISET_CONN_SETUP_PEER_STATUS_SHIFT       (0x01u)
#define ISET_CONN_SETUP_PEER_STATUS_RESETVAL    (0x00u)

  // Pear status
  typedef enum
  {
    NOT_A_PEER_STATUS_UPDATE = 0,
    PEER_CONNECTED,
    PEER_DISCONNECTED,
    PEER_STATUS_NOT_USED
  }iSet_peerStatus;


#define ISET_CONN_SETUP_PEER_MODE_MASK           (0x18u)
#define ISET_CONN_SETUP_PEER_MODE_SHIFT          (0x03u)
#define ISET_CONN_SETUP_PEER_MODE_RESETVAL       (0x00u)
  // Define Selected watch modes
  typedef enum
  {
    RETAIN_CURRENT_MODE = 0,
    PARTNER_MODE, 				// PARTNER_MODE can
    SMARTPHONE_MODE,    		// SMARTPHONE is COUNTER_PERIPHERAL -> First setup mode as COUNTER
    COUNTER_MODE,       		// COUNTER_MODE is second counter mode as central
    UNDETERMINED_MODE           //
  }iSet_peerModes;


#define ISET_CONN_SETUP_STATUS_MASK                     (0xC0u)
#define ISET_CONN_SETUP_STATUS_SHIFT                    (0x06u)
#define ISET_CONN_SETUP_STATUS_RESETVAL                 (0x00u)

  // Pear status
  typedef enum
  {
    NOT_A_STATUS_UPDATE = 0,
    SETUP_SUCCESSFULL,
    SETUP_ABORDED
  }iSet_setupStatus;


#define ISET_CONN_SETUP_ABORDED_MASK                    (0x80u)
#define ISET_CONN_SETUP_ABORDED_SHIFT                   (0x07u)
#define ISET_CONN_SETUP_ABORDED_RESETVAL                (0x00u)


  /*------------ SCORE_UPDATE field ------------*/

#define ISET_SCORE_CHANGE_SIDE__MASK             (0x30u)
#define ISET_SCORE_CHANGE_SIDE_SHIFT             (0x04u)
#define ISET_SCORE_CHANGE_SIDE_RESETVAL          (0x00u)

#define ISET_SCORE_TIE_BREAK__MASK               (0x30u)
#define ISET_SCORE_TIE_BREAK_SHIFT               (0x04u)
#define ISET_SCORE_TIE_BREAK_RESETVAL            (0x00u)

#define ISET_SCORE_SUPER_TIE_BREAK_MASK          (0x30u)
#define ISET_SCORE_SUPER_TIE_BREAK_SHIFT         (0x04u)
#define ISET_SCORE_SUPER_TIE_BREAK_RESETVAL      (0x00u)

#define ISET_SCORE_GAME_OVER_MASK                (0x30u)
#define ISET_SCORE_GAME_OVER_SHIFT               (0x04u)
#define ISET_SCORE_GAME_OVER_RESETVAL            (0x00u)

#define ISET_SCORE_SERVING_PLAYER_ID_MASK        (0x30u)
#define ISET_SCORE_SERVING_PLAYER_ID_SHIFT       (0x04u)
#define ISET_SCORE_SERVING_PLAYER_ID_RESETVAL    (0x00u)

  /*---- Tokens -> unsigned charean ----*/


  /*--------- SCORE_STATISTICS field ---------*/
typedef struct {
  unsigned char gameStats[8];
}txw_gameStatistics_t;



  /*------------ PAIRING_MODE field ------------*/
#define ISET_SEIKO_BLE_PAIRING_MODE_MASK         (0x30u)
#define ISET_SEIKO_BLE_PAIRING_MODE_SHIFT        (0x04u)
#define ISET_SEIKO_BLE_PAIRING_MODE_RESETVAL     (0x00u)


  /*------------ WATCH_MODE field ------------*/
#define ISET_SEIKO_WATCH_MODE_MASK            (0x08u)
#define ISET_SEIKO_WATCH_MODE_SHIFT           (0x03u)
#define ISET_SEIKO_WATCH_MODE_RESETVAL        (0x00u)


  /*------------ BLE_TEST_MODE field ------------*/
#define ISET_SEIKO_BLE_TEST_MODE_MASK            (0x06u)
#define ISET_SEIKO_BLE_TEST_MODE_SHIFT           (0x01u)
#define ISET_SEIKO_BLE_TEST_MODE_RESETVAL        (0x00u)


  /*---- BLE_STATUS Tokens----*/
#define ISET_SEIKO_BLE_STATUS_MASK               (0x01u)
#define ISET_SEIKO_BLE_STATUS_SHIFT              (0x00u)
#define ISET_SEIKO_BLE_STATUS_RESETVAL           (0x00u)

/*---- OAD field -----------*/
#define ISET_OAD_MASK        (0x03u)
#define ISET_OAD_SHIFT       (0x00u)
#define ISET_OAD_RESETVAL    (0x00u)

// Oad status
typedef enum
{
	OAD_NEEDS_UPDATE = 0,
	OAD_PROFILE_STARTED,
	OAD_UPGRADE_SUCCESS,
	OAD_UPGRADE_FAILURE
}iSet_oadStatus;


  /*---- Tokens ----*/
  typedef enum
  {
    RADIO_INACTIVE = 0,
    RADIO_ACTIVE
  }txw_radioModes;


  /*---- Simple player ID system ----*/
  typedef enum
  {
    ISET_PLAYER_1 = 1,
    ISET_PLAYER_2,
    ISET_PLAYER_3,
    ISET_PLAYER_4
  }txw_playerID;

  typedef enum
  {
    ISET_COUNTER_TEAM = 1,
    ISET_PARTNER_TEAM
  }txw_team;



  /*---- Game points counting system ----*/
  typedef enum
  {
    ISET_GAME_SCORE_0 = 0,
    ISET_GAME_SCORE_15,
    ISET_GAME_SCORE_30,
    ISET_GAME_SCORE_45,
    ISET_GAME_SCORE_DEUCE
  }txw_gamePoints;

  /*---- Radio Frequencies ----*/
  typedef enum
  {
    NOMINAL_FREQUENCY = 0,
    MIN_FREQUENCY,
    MID_FREQUENCY,
    MAX_FREQUENCY
  }txw_radioFrequencies;

  /*---- Radio Test modes ----*/
    typedef enum
  {
    START_ADVERTIZING = 0,
    START_CONNECTION,
    START_SNIFFING,
    END_CONNECTION
  }txw_radioTestModes;

  /*********************************************************************
  * STRUCTURES
  */
  typedef struct{
    txw_commands        code;           // Frame code
    unsigned char               len;            // Frame length
    unsigned char               args[24];       // Arguments transmitted together with the cmd
    unsigned char               *optionalArgs;  // Optional arguments (when transmitting random length data eg names)
  } txw_Frame_t;


  typedef struct
  {
    unsigned char          isMatchScore;   // Is match score present
    unsigned char         pairingMode;    // Type of pairing involved
    unsigned char         watchMode;      // In bytes of received data
    unsigned char         bleTestMode;    // In bytes of received data
    unsigned char         bleStatus;      // Data comming from Seiko
  }txw_status_t;


  /*
  * Set Vector provides the required info for  a quick push of the score update
  * It is taylored to fit with the 20 bytes ind/notif payload.
  */
  typedef struct
  {
    txw_playerID        serviceID;    // Who has the service

    unsigned char                isSuperTieBrake;  // Is it a super tie?
    txw_gamePoints      counterPoints;    // Points counter team has
    txw_gamePoints      partnerPoints;    // Points partner team has
    unsigned char               currentGame; // Current game
    unsigned char               currentSet;  // Current set
  }txw_setVector_t;


  /*
  * Set Vector provides the required info for  a quick push of the score update
  * It is taylored to fit with the 20 bytes ind/notif payload.
  */
  typedef struct
  {
    unsigned char               numPlayers;    // How many player are playing today
    txw_gamePoints      counterPoints;    // Points counter team has
  }txw_matchConfiguration_t;

  /*
  * Player's configuration
  */
  typedef struct
  {
    txw_playerID        myID;    // My player ID
    txw_team            myTeam;    // The team I belong to
  }txw_playerConfig_t;


  /*
  * Set Vector provides the required info for  a quick push of the score update
  * It is taylored to fit with the 20 bytes ind/notif payload.
  */
  typedef struct
  {
    unsigned char               setDuration; // Duration in minutes
    txw_gamePoints      myPoints;    // Points counter team has
    txw_gamePoints      hisPoints;   // Points partner team has
    unsigned char               currentGame; // Current game
    unsigned char               currentSet;  // Current set
  }txw_setStatistics_t;


  typedef struct
  {
    unsigned char          isMatchScore;   // Frame with Match score present
    unsigned char          isMacAddress;   // Frame with MAC address present
    unsigned char          isSwVersion;    // Frame with Software revision number
    unsigned char          ack;            // Acknowledgment flag for previous command
    unsigned char         numSlaves;      // In bytes of received data
    unsigned char          active;         // Is radio currently active
  }txw_radioStatus_t;



/*********************************************************************
 * MACROS
 */

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* TXWATCHSERVICE_H */
