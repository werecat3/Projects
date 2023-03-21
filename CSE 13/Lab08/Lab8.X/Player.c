//Jerret Schlosser
#include <stdio.h>
#include <string.h>
#include "UNIXBOARD.h"
#include "Player.h"

static uint8_t inventory[INVENTORY_SIZE] = {0};
static uint8_t my_counter = 0;

int AddToInventory(uint8_t item){
    if (my_counter == INVENTORY_SIZE){
        return STANDARD_ERROR;
    }
    inventory[my_counter] =  item;
    my_counter += 1;
    return SUCCESS;
}

int FindInInventory(uint8_t item){
    for (int counter = 0; counter < INVENTORY_SIZE; counter++){
        if (inventory[counter] == item){
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}