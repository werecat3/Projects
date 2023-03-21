/*
 * File:   HelloWorldMain.c
 * Author: Werec
 *
 * Created on January 12, 2023, 1:54 PM
 */


#include <stdio.h>
#include "BOARD.h"
#include "Buttons.h"
#include "Leds.h"
#include <xc.h>
#include <sys/attribs.h>

static uint8_t buttonEvents;


int main(void) {
    BOARD_Init();
    T1CON = 0; 
    T1CONbits.TCKPS = 1;
    PR1 = 0xFFFF;
    T1CONbits.ON = 1;
    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 4;
    IPC1bits.T1IS = 0;
    IEC0bits.T1IE = 1;
    //starting the board type of stuff
    
    ButtonsInit();
    LEDS_INIT();
    //gets the leds and  buttons initialized
    
    uint8_t my_leds = 0x00;
    int counter;
    int inc = 1;
          
    while (1) {
        LEDS_SET(my_leds)
        counter = counter + inc;
        my_leds = (uint8_t)(counter);
        if (buttonEvents != BUTTON_EVENT_NONE) {
            my_leds = 0x00;
        }
        if (my_leds > 0xff){
            my_leds = 0x00;
        }
        int i;
        int random;
        int NOPS_FOR_5MS = 200;//this is gonna change
        //this is my nop stop. 
        //i need to figure out what the nops for 5ms is
        //i need to find a number that when i count to it will equal 5ms
        for (i = 0; i < NOPS_FOR_5MS ; i++){
            random++;
        }
    }
}

void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    buttonEvents = ButtonsCheckEvents();
}