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

#define NO_LIVES 0x00
#define FIELD_DIR 2
#define FULL 0x0F

void FieldPrint_UART(Field *own_field, Field * opp_field) {
    printf("\nown_field");
    printf("\n0 1 2 3 4 5 6 7 8 9\n");
    printf("-----------------------\n");
    SquareStatus status;
    int i;
    int j;
    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            status = FieldGetSquareStatus(own_field, i, j);
            printf("%d ", status);
        }
        printf("\n");
    }
    printf("\nopp_field");
    printf("\n0 1 2 3 4 5 6 7 8 9\n");
    printf("-----------------------\n");
    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            status = FieldGetSquareStatus(opp_field, i, j);
            printf("%d ", status);
        }
        printf("\n");
    }
}

void FieldInit(Field *own_field, Field * opp_field) {
    int i = 0;
    int j = 0;
    // Fill own_field with empty, unknown for opp_field
    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;
        }
    }
    for (i = 0; i < FIELD_ROWS; i++) {
        for (j = 0; j < FIELD_COLS; j++) {
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;
        }
    }

    // Initialize lives for opp and own.
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;

    own_field->smallBoatLives = 0;
    own_field->mediumBoatLives = 0;
    own_field->largeBoatLives = 0;
    own_field->hugeBoatLives = 0;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col) {
    /* Check if coordinate are out of bound or not. If not
     * return the status
     */
    if (row > FIELD_ROWS) {
        return FIELD_SQUARE_INVALID;
    } else if (col > FIELD_COLS) {
        return FIELD_SQUARE_INVALID;
    } else {
        return f->grid[row][col];
    }
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p) {
    SquareStatus temp = f->grid[row][col];
    f->grid[row][col] = p;
    return temp;
}

uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type) {
    int size = 0;
    int status = 0;
    int i;
    int j;
    /* For different boat type, set their corresponding size and squareStatus,
     * so that I can use it inside the for loop
     */
    switch (boat_type) {
        case FIELD_BOAT_TYPE_SMALL:
            size = FIELD_BOAT_SIZE_SMALL;
            status = FIELD_SQUARE_SMALL_BOAT;
            break;
        case FIELD_BOAT_TYPE_MEDIUM:
            size = FIELD_BOAT_SIZE_MEDIUM;
            status = FIELD_SQUARE_MEDIUM_BOAT;
            break;
        case FIELD_BOAT_TYPE_LARGE:
            size = FIELD_BOAT_SIZE_LARGE;
            status = FIELD_SQUARE_LARGE_BOAT;
            break;
        case FIELD_BOAT_TYPE_HUGE:
            size = FIELD_BOAT_SIZE_HUGE;
            status = FIELD_SQUARE_HUGE_BOAT;
            break;
        default:
            return STANDARD_ERROR;
            break;
    }

    switch (dir) {
        case FIELD_DIR_EAST:
            if ((col + size) > FIELD_COLS) {// check if enough grid or not
                return STANDARD_ERROR;
            } else {
                // first for loop to check if the coordinate is empty or not
                for (j = col; j < (col + size); j++) {
                    if (own_field->grid[row][j] != FIELD_SQUARE_EMPTY) {
                        return STANDARD_ERROR;
                    }
                }
                // if empty, set the status with second for loop
                for (j = col; j < (col + size); j++) {
                    own_field->grid[row][j] = status;
                }
            }
            break;
        case FIELD_DIR_SOUTH:
            if ((row + size) > FIELD_ROWS) {
                return STANDARD_ERROR;
            } else {
                for (i = row; i < (row + size); i++) {
                    if (own_field->grid[i][col] != FIELD_SQUARE_EMPTY) {
                        return STANDARD_ERROR;
                    }
                }
                for (i = row; i < (row + size); i++) {
                    own_field->grid[i][col] = status;
                }
            }
            break;
    }
    // set up lives for boat if successfully added.
    switch (boat_type) {
        case FIELD_BOAT_TYPE_SMALL:
            own_field->smallBoatLives = size; // lives equal size of boat
            break;
        case FIELD_BOAT_TYPE_MEDIUM:
            own_field->mediumBoatLives = size;
            break;
        case FIELD_BOAT_TYPE_LARGE:
            own_field->largeBoatLives = size;
            break;
        case FIELD_BOAT_TYPE_HUGE:
            own_field->hugeBoatLives = size;
            break;
        default:
            return STANDARD_ERROR;
            break;
    }
    return SUCCESS;
}

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess) {
    // Get status of the grid to see what types of boat being hit
    SquareStatus status = FieldGetSquareStatus(own_field, opp_guess->row, 
                                                            opp_guess->col);
    switch (status) {
        /* Set field status to corresponding result.
         * If shot hit a boat, decrement the lives of it. Once lives
         * equal 0, report boat sunk.
         */
        case FIELD_SQUARE_EMPTY:
            opp_guess->result = RESULT_MISS;
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_MISS;
            break;
        case FIELD_SQUARE_SMALL_BOAT:
            own_field->smallBoatLives -= 1;
            if (own_field->smallBoatLives <= 0) {
                opp_guess->result = RESULT_SMALL_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            break;
        case FIELD_SQUARE_MEDIUM_BOAT:
            own_field->mediumBoatLives -= 1;
            if (own_field->mediumBoatLives <= 0) {
                opp_guess->result = RESULT_MEDIUM_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            break;
        case FIELD_SQUARE_LARGE_BOAT:
            own_field->largeBoatLives -= 1;
            if (own_field->largeBoatLives <= 0) {
                opp_guess->result = RESULT_LARGE_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            break;
        case FIELD_SQUARE_HUGE_BOAT:
            own_field->hugeBoatLives -= 1;
            if (own_field->hugeBoatLives <= 0) {
                opp_guess->result = RESULT_HUGE_BOAT_SUNK;
            } else {
                opp_guess->result = RESULT_HIT;
            }
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            break;

            // do nothing if opponent attack known coordinate
        case FIELD_SQUARE_HIT:
            break;
        case FIELD_SQUARE_MISS:
            break;
        default:
            opp_guess->result = RESULT_MISS;
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_MISS;
            break;
    }
    return status;
}

SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess) {
    //Set status on grid with the feedback
    switch (own_guess->result) {
        case RESULT_MISS:
            FieldSetSquareStatus(opp_field, own_guess->row, 
                        own_guess->col, FIELD_SQUARE_EMPTY);
            break;
        case RESULT_HIT:
            FieldSetSquareStatus(opp_field, own_guess->row, 
                        own_guess->col, FIELD_SQUARE_HIT);
            break;
        case RESULT_SMALL_BOAT_SUNK:
            FieldSetSquareStatus(opp_field, own_guess->row, 
                        own_guess->col, FIELD_SQUARE_HIT);
            opp_field->smallBoatLives = 0;
            break;
        case RESULT_MEDIUM_BOAT_SUNK:
            FieldSetSquareStatus(opp_field, own_guess->row, 
                        own_guess->col, FIELD_SQUARE_HIT);
            opp_field->mediumBoatLives = 0;
            break;
        case RESULT_LARGE_BOAT_SUNK:
            FieldSetSquareStatus(opp_field, own_guess->row, 
                        own_guess->col, FIELD_SQUARE_HIT);
            opp_field->largeBoatLives = 0;
            break;
        case RESULT_HUGE_BOAT_SUNK:
            FieldSetSquareStatus(opp_field, own_guess->row, 
                        own_guess->col, FIELD_SQUARE_HIT);
            opp_field->hugeBoatLives = 0;
            break;
    }
    return opp_field->grid[own_guess->row][own_guess->col];
}

uint8_t FieldGetBoatStates(const Field *f) {
    uint8_t lives = NO_LIVES;
    if (f->smallBoatLives != 0) {
        lives ^= FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives != 0) {
        lives ^= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives != 0) {
        lives ^= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives != 0) {
        lives ^= FIELD_BOAT_STATUS_HUGE;
    }
    return lives;
}

uint8_t FieldAIPlaceAllBoats(Field *own_field) {
    //place boats randomly on the field
    int boatCounter = 0;
    int row;
    int col;
    int dir;
    int checkStatus1 = STANDARD_ERROR;
    int checkStatus2 = STANDARD_ERROR;
    int checkStatus3 = STANDARD_ERROR;
    int checkStatus4 = STANDARD_ERROR;
    // let addedBoats ++ each time if successfully add, 
    // break from the while loop if addedBoats == 4.
    while (1) {
        if (checkStatus1 == STANDARD_ERROR) {
            row = rand() % FIELD_ROWS;
            col = rand() % FIELD_COLS;
            dir = rand() % FIELD_DIR;
            checkStatus1 = FieldAddBoat(own_field, row, col, 
                                dir, FIELD_BOAT_TYPE_SMALL);
            if (checkStatus1 == SUCCESS) {
                boatCounter += 1;
            }
        }
        if (checkStatus2 == STANDARD_ERROR) {
            row = rand() % FIELD_ROWS;
            col = rand() % FIELD_COLS;
            dir = rand() % FIELD_DIR;
            checkStatus2 = FieldAddBoat(own_field, row, col, 
                                dir, FIELD_BOAT_TYPE_MEDIUM);
            if (checkStatus2 == SUCCESS) {
                boatCounter += 1;
            }
        }
        if (checkStatus3 == STANDARD_ERROR) {
            row = rand() % FIELD_ROWS;
            col = rand() % FIELD_COLS;
            dir = rand() % FIELD_DIR;
            checkStatus3 = FieldAddBoat(own_field, row, col, 
                                dir, FIELD_BOAT_TYPE_LARGE);
            if (checkStatus3 == SUCCESS) {
                boatCounter += 1;
            }
        }
        if (checkStatus4 == STANDARD_ERROR) {
            row = rand() % FIELD_ROWS;
            col = rand() % FIELD_COLS;
            dir = rand() % FIELD_DIR;
            checkStatus4 = FieldAddBoat(own_field, row, col, 
                                dir, FIELD_BOAT_TYPE_HUGE);
            if (checkStatus4 == SUCCESS) {
                boatCounter += 1;
            }
        }
        if (boatCounter == 4) {
            break;
        }
    }
    return SUCCESS;
}

GuessData FieldAIDecideGuess(const Field *opp_field) {
    GuessData return_guess = {0, 0, 0}; 
    while (1) {
        int row = rand() % FIELD_ROWS;
        int col = rand() % FIELD_COLS;
        SquareStatus checkStatus = FieldGetSquareStatus(opp_field, row, col);
        // if statement make sure it doesn't hit the same grid
        if (checkStatus == FIELD_SQUARE_UNKNOWN) {
            return_guess.row = row;
            return_guess.col = col;
            break;
        }
    }
    return return_guess;
}

