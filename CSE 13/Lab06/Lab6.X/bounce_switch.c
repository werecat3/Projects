
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
					


//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
#define Timer_value 1
static struct Timer Main_Timer = {FALSE, Timer_value};

// **** Define global, module-level, or external variables here ****				 
#define right 0x01
#define left 0x80
#define leftMover 0
#define rightMover 1
// **** Declare function prototypes ****


int main(void)
{
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
    printf("Welcome to Jrschlos's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
    LEDS_SET(right);
	int x = leftMover; //i am using this to know which light to turn on next
    unsigned char y;
	while(1){
        //poll timer events and react if any occur
        if (Main_Timer.event == TRUE){
            Main_Timer.event = FALSE;
            if (x == leftMover){    
                if ((LEDS_GET() & 0x80) == left){
                    x = rightMover;
                    y = LEDS_GET();
                    LEDS_SET(y >> 0x01);
                }
                else{
                    y = LEDS_GET();
                    LEDS_SET(y << 0x01);
                }
            }
            else{
                if ((LEDS_GET() & 0x01) == right){
                    x = leftMover;
                    y = LEDS_GET();
                    LEDS_SET(y << 0x01);
                }
                else{
                    y = LEDS_GET();
                    LEDS_SET(y >> 0x01);
                }
            }
        }
        
    }			


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}


/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    Main_Timer.timeRemaining -= 1;
    if (Main_Timer.timeRemaining == 0){
        Main_Timer.event = TRUE;
        int t = SWITCH_STATES();
        Main_Timer.timeRemaining = t + 1;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}