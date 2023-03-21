// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Leds_Lab06.h"

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

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to Jrschlos's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    ButtonsInit();
    LEDS_INIT();
    while (1) {
        if (SWITCH_STATES() == 0b0000) {
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
        if (SWITCH_STATES() == 0b0001) {
            if(buttonEvents != BUTTON_EVENT_NONE){    
                if ((buttonEvents & BUTTON_EVENT_1UP) == 0x01) {
                    LEDS_SET(LEDS_GET() ^ 0x03);
                }
                if ((buttonEvents & BUTTON_EVENT_2UP) == 0x04) {
                    LEDS_SET(LEDS_GET() ^ 0x0C);
                }
                if ((buttonEvents & BUTTON_EVENT_3UP) == 0x10) {
                    LEDS_SET(LEDS_GET() ^ 0x30);
                }
                if ((buttonEvents & BUTTON_EVENT_4UP) == 0x40) {
                    LEDS_SET(LEDS_GET() ^ 0xC0);
                }
                buttonEvents = BUTTON_EVENT_NONE;
            }
        }
    }
}

/***************************************************************************************************
 * Your code goes in between this comment and the preceding one with asterisks
 **************************************************************************************************/



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