#include <stdio.h>
#include "BOARD.h"
#include "Buttons.h"

#define MASK_BUTTON_1_DOWN 0x1111
#define MASK_BUTTON_2_DOWN 0x2222
#define MASK_BUTTON_3_DOWN 0x4444
#define MASK_BUTTON_4_DOWN 0x8888

void ButtonsInit(void){
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}


uint8_t ButtonsCheckEvents(void){
    static uint32_t prev_val = 0;
    prev_val = (prev_val << BUTTONS_DEBOUNCE_PERIOD) | BUTTON_STATES();
    uint8_t returnButtonEvent = BUTTON_EVENT_NONE;
    static uint8_t prevButton_1_Event = BUTTON_EVENT_NONE;
    static uint8_t prevButton_2_Event = BUTTON_EVENT_NONE;
    static uint8_t prevButton_3_Event = BUTTON_EVENT_NONE;
    static uint8_t prevButton_4_Event = BUTTON_EVENT_NONE;
    
    if ((prev_val & MASK_BUTTON_1_DOWN) && !(prevButton_1_Event & BUTTON_EVENT_1DOWN)){
        returnButtonEvent |= BUTTON_EVENT_1DOWN;
        prevButton_1_Event = BUTTON_EVENT_1DOWN;
    }
    
    if(!(prev_val & MASK_BUTTON_1_DOWN) && (prevButton_1_Event & BUTTON_EVENT_1DOWN)){
        returnButtonEvent |= BUTTON_EVENT_1UP;
        prevButton_1_Event = BUTTON_EVENT_1UP;
    }
    
    if ((prev_val & MASK_BUTTON_2_DOWN) && !(prevButton_2_Event & BUTTON_EVENT_2DOWN)){
        returnButtonEvent |= BUTTON_EVENT_2DOWN;
        prevButton_2_Event = BUTTON_EVENT_2DOWN;
    }
    
    if(!(prev_val & MASK_BUTTON_2_DOWN) && (prevButton_2_Event & BUTTON_EVENT_2DOWN)){
        returnButtonEvent |= BUTTON_EVENT_2UP;
        prevButton_2_Event = BUTTON_EVENT_2UP;
    }
    
    if ((prev_val & MASK_BUTTON_3_DOWN) && !(prevButton_3_Event & BUTTON_EVENT_3DOWN)){
        returnButtonEvent |= BUTTON_EVENT_3DOWN;
        prevButton_3_Event = BUTTON_EVENT_3DOWN;
    }
    
    if(!(prev_val & MASK_BUTTON_3_DOWN) && (prevButton_3_Event & BUTTON_EVENT_3DOWN)){
        returnButtonEvent |= BUTTON_EVENT_3UP;
        prevButton_3_Event = BUTTON_EVENT_3UP;
    }
    
    if ((prev_val & MASK_BUTTON_4_DOWN) && !(prevButton_4_Event & BUTTON_EVENT_4DOWN)){
        returnButtonEvent |= BUTTON_EVENT_4DOWN;
        prevButton_4_Event = BUTTON_EVENT_4DOWN;
    }
    
    if(!(prev_val & MASK_BUTTON_4_DOWN) && (prevButton_4_Event & BUTTON_EVENT_4DOWN)){
        returnButtonEvent |= BUTTON_EVENT_4UP;
        prevButton_4_Event = BUTTON_EVENT_4UP;
    }
    
    return returnButtonEvent;
}