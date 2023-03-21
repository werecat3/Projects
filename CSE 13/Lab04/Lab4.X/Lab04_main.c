// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to Jrschlos'S RPN calculator.  Compiled on %s %s \n", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and + - / * in RPN format:\n");
        

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        if (strlen(rpn_sentence) > 60){
            printf("Too long of an entry.");
            continue;
        }

        RPN_Evaluate(rpn_sentence, &result);

        printf("result = %f\n", result);

    }

    while (1);
}
