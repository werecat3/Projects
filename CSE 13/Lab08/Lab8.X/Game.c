//Jerret Schlosser
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"

static struct{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t north;
    uint8_t south;
    uint8_t west;
    uint8_t east;    
}currentRoom = {};

//prototype
int loadRoom(uint16_t roomNumber);

//defined version
int loadRoom(uint16_t roomNumber){
    FILE *room;
    
    char roomFileName[50];
    
    sprintf(roomFileName, "RoomFiles/room%d.txt", roomNumber);
    
    if ((room = fopen(roomFileName, "rb")) == NULL){
        return STANDARD_ERROR;
    }
    
    //if not null
    fgetc(room);
    fgetc(room);
    fgetc(room);
    
    int titleLength = fgetc(room);
    
    if(titleLength == EOF || titleLength == 0 || fgets(currentRoom.title, titleLength + 1, room) == NULL){
        fclose(room);
        return STANDARD_ERROR;
    }
    
    currentRoom.title[titleLength] = '\0';
    
    //check for the item if you have it then display normal
    //if you dont have it find the length and ski the first description
    int itemsReq = fgetc(room);
    int index;
    int missingItem = 0;
    for (index = 0; index < itemsReq; index++){
        if (FindInInventory(fgetc(room) == STANDARD_ERROR)){
            missingItem = 1;
        }
    }
    
   
    int descriptionLength = fgetc(room);
    if (missingItem != 0){
        fseek(room, descriptionLength, SEEK_CUR);
        int numberItems = fgetc(room);
        fseek(room, numberItems, SEEK_CUR);
        int numberExits = fgetc(room);
        fseek(room, numberExits, SEEK_CUR);
        fgetc(room);
        descriptionLength = fgetc(room);
    }
    if(descriptionLength == EOF || titleLength == 0 || fgets(currentRoom.description, descriptionLength + 1, room) == NULL){
        fclose(room);
        return STANDARD_ERROR;
    }
    
    currentRoom.description[descriptionLength] = '\0';

    int numberItems = fgetc(room);
    for (index = 0; index < numberItems; index++){
        AddToInventory(fgetc(room));
    }
    currentRoom.north = fgetc(room);
    currentRoom.east = fgetc(room);
    currentRoom.south = fgetc(room);
    currentRoom.west = fgetc(room);
    fclose(room);
    return SUCCESS;
}

int GameGoNorth(void){
    if (currentRoom.north != TRUE){
        return loadRoom(currentRoom.north);
    }
    return STANDARD_ERROR;
}

int GameGoEast(void){
    if (currentRoom.east != TRUE){
        return loadRoom(currentRoom.east);
    }
    return STANDARD_ERROR;
}

int GameGoSouth(void){
    if (currentRoom.south != TRUE){
        return loadRoom(currentRoom.south);
    }
    return STANDARD_ERROR;
}

int GameGoWest(void){
    if (currentRoom.west != TRUE){
        return loadRoom(currentRoom.west);
    }
    return STANDARD_ERROR;
}

int GameInit(void){
    loadRoom(STARTING_ROOM);
    return SUCCESS;
}

int GameGetCurrentRoomTitle(char *title){
    strcpy(title, currentRoom.title);
    return (strlen(title) + 1);
}

int GameGetCurrentRoomDescription(char *desc){
    strcpy(desc, currentRoom.description);
    return (strlen(desc) + 1);
}

uint8_t GameGetCurrentRoomExits(void){
    uint8_t exit = 0b0000;
    if(currentRoom.north != 0){
        exit ^= GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if(currentRoom.east != 0){
        exit ^= GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if(currentRoom.south != 0){
        exit ^= GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if(currentRoom.west != 0){
        exit ^= GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return exit;
}
