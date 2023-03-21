/* 
 * File:   part0.c
 * Author: Werec
 *
 * Created on April 3, 2021, 8:59 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "Oled.h"

/*
 * 
 */
int main(void) 
{
    BOARD_Init();
    OledInit();
    OledDrawString("Hello World\nI'm Working!\n");
    OledUpdate();
    while(1);
    //printf("Hello World!\n");
    
    
    
    BOARD_End(); //handles cleanup of the system
    while(1); //if embedded we should never exit
}

