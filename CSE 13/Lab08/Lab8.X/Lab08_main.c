//Jerret Schlosser
// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//CSE013E Support Library
#include "UNIXBOARD.h"




// User libraries
#include "Game.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
char Title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
char Description[GAME_MAX_ROOM_DESC_LENGTH + 1];

// **** Declare any function prototypes here ****
#define NORTH 'n'
#define EAST 'e'
#define SOUTH 's'
#define WEST 'w'
#define QUIT 'q'



int main()
{
    uint8_t dir = 0;
    uint8_t roomExits = 0;
    
    if (GameInit() == STANDARD_ERROR){
        printf("Failed to load starting room");
    }
    //your own function to display the room
    GameInit();
    while(TRUE){
        system("clear");
        roomExits = GameGetCurrentRoomExits();
        GameGetCurrentRoomTitle(Title);
        printf("-----%s-----\n", Title);
        GameGetCurrentRoomDescription(Description);
        printf("%s\n", Description);
        printf("_______________________\n\n\n");
        printf("Avaiable Directions:\n");
        if((GAME_ROOM_EXIT_NORTH_EXISTS & roomExits) == GAME_ROOM_EXIT_NORTH_EXISTS){
            printf("North\n");
        }
        if((GAME_ROOM_EXIT_EAST_EXISTS & roomExits) == GAME_ROOM_EXIT_EAST_EXISTS){
            printf("East\n");
        }
        if((GAME_ROOM_EXIT_SOUTH_EXISTS & roomExits) == GAME_ROOM_EXIT_SOUTH_EXISTS){
            printf("South\n");
        }
        if((GAME_ROOM_EXIT_WEST_EXISTS & roomExits) == GAME_ROOM_EXIT_WEST_EXISTS){
            printf("West\n");
        }

        printf("\nPlease enter a key to choose a direction(n,e,s,w) or q to quit the game:");
        dir = getchar();
        while(getchar() != '\n');
        switch(dir){
            case NORTH:
                if(roomExits & GAME_ROOM_EXIT_NORTH_EXISTS){
                    if(GameGoNorth()){
                        
                    }
                    else{
                        FATAL_ERROR();
                    }
                }
                break;
            case EAST:
                if(roomExits & GAME_ROOM_EXIT_EAST_EXISTS){
                    if(GameGoEast()){
                        
                    }
                    else{
                        FATAL_ERROR();
                    }
                }
                break;
            case SOUTH:
                if(roomExits & GAME_ROOM_EXIT_SOUTH_EXISTS){
                    if(GameGoSouth()){
                        
                    }
                    else{
                        FATAL_ERROR();
                    }
                }
                break;
            case WEST:
                if(roomExits & GAME_ROOM_EXIT_WEST_EXISTS){
                    if(GameGoWest()){
                        
                    }
                    else{
                        FATAL_ERROR();
                    }
                }
                break;
            case QUIT:
                printf("\nThank you for playing. See you next time.\n");
                exit(0);
                break;
            default:
                printf("\nInvalid key entered, please try again\n");
                break;
        }
        
        //your own function to display the room
    }


    /******************************** Your custom code goes below here ********************************/
    


    /**************************************************************************************************/
}

