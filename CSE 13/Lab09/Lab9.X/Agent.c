#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "BattleBoats.h"
#include "Agent.h"
#include "Field.h"
#include "Negotiation.h"
#include "FieldOled.h"
#include "Oled.h"
#include "BOARD.h"


typedef enum {
    Victory,
    Lost,
    Cheating
} EndScreenMessage;

static AgentState currentState;
static Field own_field;
static Field opp_field;
static uint8_t turn_number;     // Counter for turn
static FieldOledTurn playerTurn;// Keep track of whose turn it is
static uint8_t lives;           // Check lives left for field
static NegotiationData secret;  // Random number for hash
static NegotiationData A;       // Hash A
static NegotiationData B;       // Hash B
static NegotiationOutcome coin; // Who is fisrt
static GuessData own_guess;  // for attacking
static GuessData opp_guess;  // for defending
static int verify;           // Check for cheating
static int gameOutcome;      // Decide EndScreen Message
char oled[100] = "";


#define MAX_UINT16_T 65535
#define NO_LIVES_LEFT 0


void AgentInit(void) {
    currentState = AGENT_STATE_START;
    turn_number = 0;
    playerTurn = FIELD_OLED_TURN_NONE;
}

Message AgentRun(BB_Event event) {
    Message returnMessage = {MESSAGE_NONE, 0, 0, 0};

    if (event.type == BB_EVENT_RESET_BUTTON) {
        AgentInit();                    // Restart the game
        sprintf(oled, "New game.\n");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(oled);
        OledUpdate();
        return returnMessage;
    }
    // ERROR STATE
    if (event.type == BB_EVENT_ERROR) {
        returnMessage.type = MESSAGE_ERROR; // Counter error
        sprintf(oled, "Game counters some error.\n");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(oled);
        OledUpdate();
        return returnMessage;
    }
    switch (currentState) {
        case AGENT_STATE_START:
            if (event.type == BB_EVENT_START_BUTTON) {
                currentState = AGENT_STATE_CHALLENGING;
                secret = rand() % MAX_UINT16_T;   //Generate random number
                returnMessage.param0 = NegotiationHash(secret); // Hash it 
                A = returnMessage.param0;//Store it and use it in challenge state
                returnMessage.type = MESSAGE_CHA; 
                FieldInit(&own_field, &opp_field);  
                FieldAIPlaceAllBoats(&own_field);
            } else if (event.type == BB_EVENT_CHA_RECEIVED) {
                currentState = AGENT_STATE_ACCEPTING;
                secret = rand() % MAX_UINT16_T; // Generate random number
                returnMessage.param0 = secret;  // Send it to other agent
                returnMessage.type = MESSAGE_ACC;
                FieldInit(&own_field, &opp_field);
                FieldAIPlaceAllBoats(&own_field);
            }
            break;
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_ACC_RECEIVED) {
                /* Hash the other agent's random number, and use own hash
                 * number to determine who go first with coinFlip
                 */
                B = NegotiationHash(event.param0); 
                coin = NegotiateCoinFlip(A, B);
                if (coin == HEADS) {
                    currentState = AGENT_STATE_WAITING_TO_SEND;
                } else {
                    currentState = AGENT_STATE_DEFENDING;
                }
                returnMessage.type = MESSAGE_REV;
            }
            break;
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_REV_RECEIVED) {
                /* Take the hash from another agent, and verify with 
                 * generated number. If verify success, do the same step as
                 * in challenging state to decide who go first
                 */
                verify = NegotiationVerify(secret,event.param0);
                if (verify == TRUE) {
                    A = NegotiationHash(secret);
                    B = event.param0;
                    coin = NegotiateCoinFlip(A, B);
                    if (coin == HEADS) {
                        currentState = AGENT_STATE_DEFENDING;
                    } else {
                        // generate guess and attack
                        own_guess = FieldAIDecideGuess(&opp_field);
                        returnMessage.type = MESSAGE_SHO;
                        returnMessage.param0 = own_guess.row;
                        returnMessage.param1 = own_guess.col;
                        currentState = AGENT_STATE_ATTACKING;
                    }
                } else {
                    // Go to End Screen if cheating detected
                    gameOutcome = Cheating;
                    currentState = AGENT_STATE_END_SCREEN;
                }
            }
            break;
        case AGENT_STATE_ATTACKING:
            /* Store the row and col and use them to update opponent's field.
             * If all opponent's boats sunk, win the game
             */
            if (event.type == BB_EVENT_RES_RECEIVED) {
                own_guess.row = event.param0;
                own_guess.col = event.param1;
                FieldUpdateKnowledge(&opp_field, &own_guess);
                returnMessage.param0 = own_guess.row;
                returnMessage.param1 = own_guess.col;
                playerTurn = FIELD_OLED_TURN_MINE;
            }
            lives = FieldGetBoatStates(&opp_field);
            if (lives == NO_LIVES_LEFT) {
                gameOutcome = Victory;
                currentState = AGENT_STATE_END_SCREEN;
            } else {
                currentState = AGENT_STATE_DEFENDING;
            }
            FieldOledDrawScreen(&own_field, &opp_field,
                    playerTurn, turn_number);
            break;
        case AGENT_STATE_DEFENDING:
            /* Store the row and col and use them to update own field.
             * If all own's boats sunk, lose the game
             */
            if (event.type == BB_EVENT_SHO_RECEIVED) {
                opp_guess.row = event.param0;
                opp_guess.col = event.param1;
                FieldRegisterEnemyAttack(&own_field, &opp_guess);
                returnMessage.param0 = opp_guess.row;
                returnMessage.param1 = opp_guess.col;
                returnMessage.param2 = opp_guess.result;
                returnMessage.type = MESSAGE_RES;
                playerTurn = FIELD_OLED_TURN_THEIRS;
            }
            lives = FieldGetBoatStates(&own_field);
            if (lives == NO_LIVES_LEFT) {
                gameOutcome = Lost;
                currentState = AGENT_STATE_END_SCREEN;
            } else {
                currentState = AGENT_STATE_ATTACKING;
            }
            FieldOledDrawScreen(&own_field, &opp_field,
                    playerTurn, turn_number);
            //      fill in message instance with ur guess data
            break;
        case AGENT_STATE_WAITING_TO_SEND:
            /* Use AI to generate random guess and store all 
             * the data of coordinate in returnMessage
             */
            turn_number += 1;
            own_guess = FieldAIDecideGuess(&opp_field);
            returnMessage.type = MESSAGE_SHO;
            returnMessage.param0 = own_guess.row;
            returnMessage.param1 = own_guess.col;
            currentState = AGENT_STATE_ATTACKING;
            break;
        case AGENT_STATE_END_SCREEN:
            // Print corresponding message under different condition
            
            if (gameOutcome == Lost) {
                sprintf(oled, "You Lost.\n");
            } else if (gameOutcome == Victory) {
                sprintf(oled, "You Win.\n");
            } else if (gameOutcome == Cheating) {
                sprintf(oled, "Cheating detected..\n");
            }
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(oled);
            OledUpdate();
            break;
        default:
            break;
    }
    return returnMessage;
}

AgentState AgentGetState(void) {
    return currentState;
}

void AgentSetState(AgentState newState) {
    currentState = newState;
}