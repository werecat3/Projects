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


int main()
{
    BOARD_Init();
    
    Field field1;
    Field field2;
    uint8_t result;
    SquareStatus status;
    GuessData guess ={1,1,0};
    GuessData guess1 ={0,0,0};
    
    int test_counter = 0;
    
    printf("---Testing FieldInit---\n");
    FieldInit(&field1,&field2);
    if (field1.smallBoatLives == 0 &&
        field1.mediumBoatLives == 0 &&
        field1.largeBoatLives == 0 &&
        field1.hugeBoatLives == 0) {
        printf("All player's BoatLives set successfully.\n");
        test_counter += 1;
    } else {
        printf("Player's BoatLives test FAILED.\n");
    }
    if (field2.smallBoatLives == FIELD_BOAT_SIZE_SMALL &&
        field2.mediumBoatLives == FIELD_BOAT_SIZE_MEDIUM &&
        field2.largeBoatLives == FIELD_BOAT_SIZE_LARGE &&
        field2.hugeBoatLives == FIELD_BOAT_SIZE_HUGE) {
        printf("All opponent's BoatLives set successfully.\n");
        test_counter += 1;
    } else {
        printf("Opponent's BoatLives test FAILED.\n");
    }
    printf("FieldInit pass %d/2.\n",test_counter);
    
//    printf("There should be '0' on all the grid in own_field.\n");
//    printf("And there should be '5' on all the grid in opp_field.\n");
//    FieldPrint_UART(&field1,&field2);
    
    
    printf("\n---Testing FieldGetSquareStatus&FieldSetSquareStatus---\n");
    test_counter = 0;
    status = FieldSetSquareStatus(&field1,0,0,FIELD_SQUARE_HIT);
    if(status == FIELD_SQUARE_EMPTY){
        test_counter += 1;
    }
    status = FieldSetSquareStatus(&field2,1,1,FIELD_SQUARE_MISS);
    if(status == FIELD_SQUARE_UNKNOWN){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,0,0);
    if(status == FIELD_SQUARE_HIT){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field2,1,1);
    if(status == FIELD_SQUARE_MISS){
        test_counter += 1;
    }
    status = FieldSetSquareStatus(&field1,3,9,FIELD_SQUARE_HIT);
    if(status == FIELD_SQUARE_EMPTY){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,3,9);
    if(status == FIELD_SQUARE_HIT){
        test_counter += 1;
    }
    printf("FieldGetSquareStatus&FieldSetSquareStatus pass %d/6.\n",test_counter);

    printf("\n---Testing FieldAddBoat---\n");
    test_counter = 0;
    // Add small boat
    result = FieldAddBoat(&field1,1,0,FIELD_DIR_SOUTH,FIELD_BOAT_TYPE_SMALL);
    if(result == SUCCESS){
        test_counter += 1;
    }
    if (field1.smallBoatLives == 3){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,3,0);
    if(status == FIELD_SQUARE_SMALL_BOAT){
        test_counter += 1;
    }
    // Add Huge boat
    result = FieldAddBoat(&field1,5,4,FIELD_DIR_EAST,FIELD_BOAT_TYPE_HUGE);
    if(result == SUCCESS){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,5,8);
    if(status == FIELD_SQUARE_HUGE_BOAT){
        test_counter += 1;
    }
    // Overlap existing boat
    result = FieldAddBoat(&field1,0,0,FIELD_DIR_EAST,FIELD_BOAT_TYPE_HUGE);
    if(result == STANDARD_ERROR){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,0,1);
    if(status == FIELD_SQUARE_EMPTY){
        test_counter += 1;
    }
    // Out of bound
    result = FieldAddBoat(&field1,0,6,FIELD_DIR_EAST,FIELD_BOAT_TYPE_LARGE);
    if(result == STANDARD_ERROR){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,0,9);
    if(status == FIELD_SQUARE_EMPTY){
        test_counter += 1;
    }
    printf("FieldAddBoat pass %d/9.\n",test_counter);
    
    printf("\n---Testing FieldRegisterEnemyAttack---\n");
    test_counter = 0;
    status = FieldRegisterEnemyAttack(&field1,&guess);
    if(status == FIELD_SQUARE_EMPTY){
        test_counter += 1;
    }
    if(guess.result == RESULT_MISS){
        test_counter += 1;
    }
    status = FieldGetSquareStatus(&field1,1,1);
    if(status == FIELD_SQUARE_MISS){
        test_counter += 1;
    }
    // Attack small boat three times
    guess.col = 0;
    status = FieldRegisterEnemyAttack(&field1,&guess);
    guess.row = 2;
    status = FieldRegisterEnemyAttack(&field1,&guess);
    guess.row = 3;
    status = FieldRegisterEnemyAttack(&field1,&guess);
    
    status = FieldGetSquareStatus(&field1,3,0);
    if(status == FIELD_SQUARE_HIT){
        test_counter += 1;
    }
    if(guess.result == RESULT_SMALL_BOAT_SUNK){
        test_counter += 1;
    }
    printf("FieldRegisterEnemyAttack pass %d/5.\n",test_counter);
    
    
    printf("\n---Testing FieldUpdateKnowledge---\n");
    test_counter = 0;
    // Clear the grid for opp field so that I can add ship for opponent. It is 
    // not going to work like this in the real game.
    FieldSetSquareStatus(&field2,0,0,FIELD_SQUARE_EMPTY);
    FieldSetSquareStatus(&field2,0,1,FIELD_SQUARE_EMPTY);
    FieldSetSquareStatus(&field2,0,2,FIELD_SQUARE_EMPTY);
    FieldAddBoat(&field2,0,0,FIELD_DIR_EAST,FIELD_BOAT_TYPE_SMALL);
    FieldRegisterEnemyAttack(&field2,&guess1);
    FieldUpdateKnowledge(&field2,&guess1);
    if(guess1.result == RESULT_HIT){
        test_counter += 1;
    }
    guess1.col = 1;
    FieldRegisterEnemyAttack(&field2,&guess1);
    FieldUpdateKnowledge(&field2,&guess1);
    
    guess1.col = 2;
    FieldUpdateKnowledge(&field2,&guess1);
    FieldRegisterEnemyAttack(&field2,&guess1);
    guess1.col = 3;
    guess1.result = RESULT_MISS;
    status = FieldUpdateKnowledge(&field2,&guess1);
    if(status == FIELD_SQUARE_EMPTY){
        test_counter += 1;
    }
    printf("FieldUpdateKnowledge pass %d/2.\n",test_counter);
    
    printf("\n---Testing FieldGetBoatStates---\n");
    test_counter = 0;
    result = FieldGetBoatStates(&field1);
    if(result == 8){
        test_counter += 1;
    }
    FieldAddBoat(&field1,2,5,FIELD_DIR_EAST,FIELD_BOAT_TYPE_MEDIUM);
    result = FieldGetBoatStates(&field1);
    if(result == 10){
        test_counter += 1;
    }
    
    printf("FieldGetBoatStates pass %d/2.\n",test_counter);
    
    
    printf("\n---Testing FieldAIPlaceAllBoats---\n");
    test_counter = 0;
    FieldInit(&field1,&field2); 
    FieldAIPlaceAllBoats(&field1);
    result = FieldGetBoatStates(&field1);
    if(result == 15){
        test_counter += 1;
    }
    FieldInit(&field1,&field2); 
    FieldAIPlaceAllBoats(&field1);
    result = FieldGetBoatStates(&field1);
    if(result == 15){
        test_counter += 1;
    }    
    printf("FieldAIPlaceAllBoats pass %d/2.\n", test_counter);
    
    
    printf("\n---Testing FieldAIDecideGuess---\n");
    test_counter = 0;
    guess1 = FieldAIDecideGuess(&field2);
    printf("Row: %d, Col: %d\n",guess1.row,guess1.col);
    guess1 = FieldAIDecideGuess(&field2);
    printf("Row: %d, Col: %d\n",guess1.row,guess1.col);
    guess1 = FieldAIDecideGuess(&field2);
    printf("Row: %d, Col: %d\n",guess1.row,guess1.col);
    guess1 = FieldAIDecideGuess(&field2);
    printf("Row: %d, Col: %d\n",guess1.row,guess1.col);
    guess1 = FieldAIDecideGuess(&field2);
    printf("Row: %d, Col: %d\n",guess1.row,guess1.col);
    
    while(1);
}