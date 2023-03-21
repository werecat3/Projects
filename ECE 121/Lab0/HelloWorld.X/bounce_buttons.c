// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Leds.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static uint8_t buttonEvents;
// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    ButtonsInit();
    LEDS_INIT();
    uint8_t my_leds = 0x00;
    int counter;
    int inc = 1;
    LEDS_SET(0x00);
    
    //Part 1
    /*
    while (1) {
        if (buttonEvents != BUTTON_EVENT_NONE) {
            if ((buttonEvents & BUTTON_EVENT_1DOWN) == 0x02) {
                LEDS_SET(LEDS_GET() ^ 0x03);
            }
            if ((buttonEvents & BUTTON_EVENT_2DOWN) == 0x08) {
                LEDS_SET(LEDS_GET() ^ 0x0C);
            }
            if ((buttonEvents & BUTTON_EVENT_3DOWN) == 0x20) {
                LEDS_SET(LEDS_GET() ^ 0x30);
            }
            if ((buttonEvents & BUTTON_EVENT_4DOWN) == 0x80) {
                LEDS_SET(LEDS_GET() ^ 0xC0);
            }
            buttonEvents = BUTTON_EVENT_NONE;
        }
    }
    */
    
          
    ///*
    while (1) {
        LEDS_SET(my_leds);
        counter = counter + inc;
        my_leds = (uint8_t)(counter);
        if (buttonEvents != BUTTON_EVENT_NONE){
            LEDS_SET(0x00);
            counter = 0;
        
        }
        if (my_leds > 0xff){
            LEDS_SET(0x00);
            counter = 0;
        }
        int i;
        int random;
        int NOPS_FOR_5MS = 200000;//this is gonna change
        //this is my nop stop. 
        //i need to figure out what the nops for 5ms is
        //i need to find a number that when i count to it will equal 5ms
        for (i = 0; i < NOPS_FOR_5MS ; i++){
            random++;
        }
    }
    //*/
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    buttonEvents = ButtonsCheckEvents();


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}