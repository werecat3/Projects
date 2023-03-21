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

AgentState state;
int test_counter = 0;
BB_Event event;
Message message;
/*
typedef enum {
    AGENT_STATE_START, //0
    AGENT_STATE_CHALLENGING, //1
    AGENT_STATE_ACCEPTING, //2
    AGENT_STATE_ATTACKING, //3
    AGENT_STATE_DEFENDING, //4
    AGENT_STATE_WAITING_TO_SEND, //5
    AGENT_STATE_END_SCREEN, //6

    //If implementing a human agent, you will need a state to setup boats:
    AGENT_STATE_SETUP_BOATS, //7
} AgentState;
*/
int main()
{
    BOARD_Init();
    printf("\n-----Agent.c Testing-----\n");
    
    
    printf("---Testing AgentInit---\n");
    AgentInit();
    state = AgentGetState();
    if(state == AGENT_STATE_START){
        test_counter += 1;
    }
    printf("AgentInit passed %d/1.\n",test_counter);
    
    printf("---Testing RESET_BUTTON&&ERROR---\n");
    test_counter = 0;
    event.type = BB_EVENT_RESET_BUTTON;
    message = AgentRun(event);
    if(state == AGENT_STATE_START){
        test_counter += 1;
    }
    event.type = BB_EVENT_ERROR;
    message = AgentRun(event);
    if(message.type == MESSAGE_ERROR){
        test_counter += 1;
    }
    printf("RESET_BUTTON&&ERROR passed %d/2.\n",test_counter);
    
    printf("---Testing AGENT_STATE_START---\n");
    test_counter = 0;
    event.type = BB_EVENT_START_BUTTON;
    message = AgentRun(event);
    state = AgentGetState();
    if(state == AGENT_STATE_CHALLENGING){
        test_counter += 1;
    }
    if(message.type == MESSAGE_CHA){
        test_counter += 1;
    }
    
    AgentSetState(AGENT_STATE_START);
    event.type = BB_EVENT_CHA_RECEIVED;
    message = AgentRun(event);
    state = AgentGetState();
    if(state == AGENT_STATE_ACCEPTING){
        test_counter += 1;
    }
    if(message.type == MESSAGE_ACC){
        test_counter += 1;
    }
    printf("AGENT_STATE_START passed %d/4.\n",test_counter);

    printf("---Testing AGENT_STATE_CHALLENGING---\n");
    test_counter = 0;
    event.type = BB_EVENT_ACC_RECEIVED;
    event.param0 = 5;
    event.param1 = 25;
    message = AgentRun(event);
    state = AgentGetState();
    if(state == AGENT_STATE_DEFENDING){
        test_counter += 1;
    }
    if(message.type == MESSAGE_REV){
        test_counter += 1;
    }
    printf("AGENT_STATE_CHALLENGING passed %d/2.\n", test_counter);
    
    printf("---Testing AGENT_STATE_ACCEPTING---\n");
    test_counter = 0;
    event.type = BB_EVENT_ACC_RECEIVED;
    event.param0 = 5;
    event.param1 = 25;
    message = AgentRun(event);
    state = AgentGetState();
    if(state == AGENT_STATE_END_SCREEN){
        test_counter += 1;
    }
    if(message.type == MESSAGE_SHO){
        test_counter += 1;
    }
    printf("AGENT_STATE_ACCEPTING passed %d/2.\n", test_counter);
    
    printf("---Testing AGENT_STATE_ATTACKING---\n");
    test_counter = 0;
    event.type = BB_EVENT_RESET_BUTTON;
    message = AgentRun(event);
    AgentSetState(AGENT_STATE_ATTACKING);
    event.type = BB_EVENT_RES_RECEIVED;
    event.param0 = 5;
    event.param1 = 2;
    message = AgentRun(event);
    state = AgentGetState();
    if(message.param0 == 5){
        test_counter += 1;
    }
    if(message.param1 == 2){
        test_counter += 1;
    }
    printf("AGENT_STATE_ATTACKING passed %d/2.\n", test_counter);
    
    printf("---Testing AGENT_STATE_DEFENDING---\n");
    test_counter = 0;
    event.type = BB_EVENT_RES_RECEIVED;
    event.param0 = 2;
    event.param1 = 4;
    message = AgentRun(event);
    if(message.param0 == 2){
        test_counter += 1;
    }
    if(message.param1 == 4){
        test_counter += 1;
    }
    if(message.type == MESSAGE_RES){
        test_counter += 1;
    }
    printf("AGENT_STATE_DEFENDING passed %d/3.\n", test_counter);
    
    printf("---Testing AGENT_STATE_WAITING_TO_SEND---\n");
    test_counter = 0;
    event.type = BB_EVENT_RES_RECEIVED;
    message = AgentRun(event);
    state = AgentGetState();
    if(state == AGENT_STATE_ATTACKING){
        test_counter += 1;
    }
    if(message.type == MESSAGE_SHO){
        test_counter += 1;
    }
    printf("AGENT_STATE_WAITING_TO_SEND passed %d/2.\n", test_counter);
    
    
    while(1);
}