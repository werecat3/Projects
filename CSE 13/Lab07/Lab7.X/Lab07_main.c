// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Leds.h"
#include "Oled.h"
#include "Adc.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****


// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    Bake, Broil, Toast
} Mode;

typedef enum {
    Time, Temp
} Selector;

typedef struct {
    OvenState state;
    uint16_t cooktime;
    uint16_t startcooktime;
    uint16_t cookTimeRemaining;
    uint16_t temperature;
    uint16_t button;
    Mode mode;
    Selector selector;
    //add more members to this struct
} OvenData;

// **** Declare any datatypes here ****
OvenData ovenData;
// **** Define any module-level, global, or external variables here ****
static uint16_t freeRunningTime = 0;
static uint16_t secondaryTimer = 0;
static uint16_t thirdTimer = 0;
static uint16_t ledTimer = 0;
static uint16_t ledCountdownTimer = 0;
static uint8_t TimerTickEvent = FALSE;
static uint8_t buttonEvent = FALSE;
static uint8_t ADCevent = FALSE;
static uint8_t ADCvalue;
static int  number_of_leds = 8;

// **** Put any helper functions here ****
#define LONG_PRESS 1
#define MIN_TIME 1
#define MIN_TEMP 300
#define Broil_temp 500

#define OVEN_TOP_ON_5 "|\x01\x01\x01\x01\x01|"
#define OVEN_TOP_OFF_5 "|\x02\x02\x02\x02\x02|"
#define OVEN_BOTTOM_ON_5 "|\x03\x03\x03\x03\x03|"
#define OVEN_BOTTOM_OFF_5 "|\x04\x04\x04\x04\x04|"
#define OVEN_SECOND_LINE "|     |"
#define OVEN_THIRD_LINE "|-----|"



/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    //update OLED here
    char display[100];
    int display_minute = ovenData.cooktime / 60;
    int display_second = ovenData.cooktime % 60;
    int minute = ovenData.cookTimeRemaining / 60;
    int second = ovenData.cookTimeRemaining % 60;
    OledClear(OLED_COLOR_BLACK);
    OledUpdate();
    if (ovenData.mode == Bake){
        if (ovenData.state == COOKING){
            sprintf(display, "%s MODE: BAKE\n"
                    "%s  TIME: %d:%02d\n"
                    "%s  TEMP: %d\n"
                    "%s\n", OVEN_TOP_ON_5, OVEN_SECOND_LINE, minute, second, 
                    OVEN_THIRD_LINE, ovenData.temperature, OVEN_BOTTOM_ON_5);
        }
        else{
            if (ovenData.selector == Time){
                sprintf(display, "%s MODE: BAKE\n"
                    "%s >TIME: %d:%02d\n"
                    "%s  TEMP: %d\n"
                    "%s\n", OVEN_TOP_OFF_5, OVEN_SECOND_LINE, display_minute, display_second, 
                    OVEN_THIRD_LINE, ovenData.temperature, OVEN_BOTTOM_OFF_5);
            }
            else{
                sprintf(display, "%s MODE: BAKE\n"
                    "%s  TIME: %d:%02d\n"
                    "%s >TEMP: %d\n"
                    "%s\n", OVEN_TOP_OFF_5, OVEN_SECOND_LINE, display_minute, display_second, 
                    OVEN_THIRD_LINE, ovenData.temperature, OVEN_BOTTOM_OFF_5);
            }
        }
        
    }
    if (ovenData.mode == Broil){
        if (ovenData.state == COOKING){
            sprintf(display, "%s MODE: Broil\n"
                    "%s  TIME: %d:%02d\n"
                    "%s  TEMP: %d\n"
                    "%s\n", OVEN_TOP_ON_5, OVEN_SECOND_LINE, minute, second, 
                    OVEN_THIRD_LINE, Broil_temp, OVEN_BOTTOM_OFF_5);
        }
        else{
            sprintf(display, "%s MODE: Broil\n"
                   "%s  TIME: %d:%02d\n"
                   "%s  TEMP: %d\n"
                   "%s\n", OVEN_TOP_OFF_5, OVEN_SECOND_LINE, display_minute, display_second, 
                   OVEN_THIRD_LINE, Broil_temp, OVEN_BOTTOM_OFF_5);
        }
        
    }
    if (ovenData.mode == Toast){
        if (ovenData.state == COOKING){
            sprintf(display, "%s MODE: Toast\n"
                    "%s  TIME: %d:%02d\n"
                    "%s\n"
                    "%s\n", OVEN_TOP_OFF_5, OVEN_SECOND_LINE, minute, second, 
                    OVEN_THIRD_LINE, OVEN_BOTTOM_ON_5);
        }
        else{
            sprintf(display, "%s MODE: Toast\n"
                   "%s  TIME: %d:%02d\n"
                   "%s\n"
                   "%s\n", OVEN_TOP_OFF_5, OVEN_SECOND_LINE, display_minute, display_second, 
                   OVEN_THIRD_LINE, OVEN_BOTTOM_OFF_5);
        }
    }
    OledDrawString(display);
    OledUpdate();
    //check ovenData.state; //check if it is bake toast or broil
    
    //check state for setup or selector pending
    //this makes the > to point to stuff
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    //write your SM logic here.
    switch(ovenData.state){
        case SETUP:
            if((buttonEvent & BUTTON_EVENT_4DOWN) == 0x80){
                ovenData.startcooktime = freeRunningTime;
                ovenData.cookTimeRemaining = ovenData.cooktime;
                LEDS_SET(0xFF);
                ovenData.state = COOKING;
            }
            else if((buttonEvent & BUTTON_EVENT_3DOWN) == 0x20){
                secondaryTimer = freeRunningTime;
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            updateOvenOLED(ovenData);
            break;
        case SELECTOR_CHANGE_PENDING:
            if ((buttonEvent & BUTTON_EVENT_3UP) == 0x10){
                if(((freeRunningTime - secondaryTimer) / 5) < LONG_PRESS){
                    if(ovenData.mode == Bake){
                        ovenData.mode = Toast;
                        ovenData.selector = Time;
                        ovenData.state = SETUP;
                    }
                    else if(ovenData.mode == Toast){
                        ovenData.mode = Broil;
                        ovenData.selector = Time;
                        ovenData.state = SETUP;
                    }
                    else if(ovenData.mode == Broil){
                        ovenData.mode = Bake;
                        ovenData.selector = Time;
                        ovenData.state = SETUP;
                    }
                    
                }
                if(((freeRunningTime - secondaryTimer) / 5) > LONG_PRESS){
                    if(ovenData.selector == Time){
                        ovenData.selector = Temp;
                        ovenData.state = SETUP;
                    }
                    else{
                        ovenData.selector = Time;
                        ovenData.state = SETUP;
                    }
                }
            }
            updateOvenOLED(ovenData);
            break;
        case COOKING:
            ledTimer = ovenData.cooktime / 8;
            if((buttonEvent & BUTTON_EVENT_4DOWN) == 0x80){
                thirdTimer = freeRunningTime;
                ovenData.state = RESET_PENDING;
            }
            if(TimerTickEvent == TRUE){
                ovenData.cookTimeRemaining = ovenData.cooktime - ((freeRunningTime - ovenData.startcooktime)/5);
                ledTimer = ovenData.cookTimeRemaining * number_of_leds / ovenData.cooktime;
                LEDS_SET(0xFF << (number_of_leds - ledTimer));
                    
                
                if (ovenData.cookTimeRemaining <= 0) {
                    ovenData.cookTimeRemaining = ovenData.cooktime;
                    ovenData.state = SETUP;
                    LEDS_SET(0x00);
                }
            }
            updateOvenOLED(ovenData);
            break;
        case RESET_PENDING:
            if((buttonEvent & BUTTON_EVENT_4UP) == 0x40){
                if((freeRunningTime - thirdTimer) / 5 >= LONG_PRESS){
                    ovenData.cookTimeRemaining = ovenData.cooktime;
                    ovenData.state = SETUP;
                    LEDS_SET(0x00);
                }
                else{
                    ovenData.state = COOKING;
                }
            }
            updateOvenOLED(ovenData);
            break;
        default:
            ovenData.state = SETUP;
            updateOvenOLED(ovenData);
            break;
    }
   
}


int main()
{
    BOARD_Init();
    LEDS_INIT();
    OledInit();
    ButtonsInit();
    AdcInit();
     //initialize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
   
    printf("Welcome to jrschlos's Lab07 (Toaster Oven).  Compiled on %s %s.\n", __TIME__, __DATE__);
    
    ovenData.state = SETUP;
    ovenData.mode = Bake;
    ovenData.selector = Time;
    updateOvenOLED(ovenData);
    //initialize state machine (and anything else you need to init) here
    
    while (1){
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
        if(ADCevent == TRUE){
            runOvenSM();
            ADCevent = FALSE;
        }
        if(buttonEvent != BUTTON_EVENT_NONE){
            runOvenSM();
            buttonEvent = BUTTON_EVENT_NONE;
        }
        if(TimerTickEvent == TRUE){
            runOvenSM();
            TimerTickEvent = FALSE;
        }
    }
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;
    TimerTickEvent = TRUE; //goes every 5hz
    freeRunningTime += 1; //take this and divide by 5 to get seconds
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    if(AdcChanged() == TRUE){
        if(ovenData.selector == Time){
            ovenData.cooktime = (AdcRead() >> 2) + 1;  
        }
        else if(ovenData.selector == Temp){
            ovenData.temperature = (AdcRead() >> 2) + 300;
        }
    }
    buttonEvent = ButtonsCheckEvents();
}