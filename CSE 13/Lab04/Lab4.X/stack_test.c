// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning Jrschlos's stack test harness: ####\n\n");
    printf("Testing all functions within stack.c\n\n");
    //showing stack init works correctly
    
    int counter = 0;
    
    struct Stack stack = {};
    StackInit(&stack);
    
    struct Stack stack2 = {};
    
    //checks if the stack is initialized
    if (stack.initialized == TRUE){
        counter += 1;
    }
    if (stack2.initialized == FALSE) {
        counter += 1;
    }
    printf("Initializing stack - passed (%d/2)\n", counter);
    counter  = 0;
    
    //checks if it sets the index to the bottom of the stack
    if (stack.currentItemIndex == -1) { 
        counter += 1;
    }
    if (stack2.currentItemIndex != -1) {
        counter += 1;
    }
    printf("Setting stack pointer to beginning - passed (%d/2)\n", counter);
    counter  = 0;
    
    //checking that stack is empty works
    if (StackIsEmpty(&stack) == TRUE){
        counter += 1;
    }
    StackInit(&stack2);
    double value = 7;
    StackPush(&stack2, value);
    if (StackIsEmpty(&stack2) != TRUE){
        counter += 1;
    }
    printf("Checking if Stack Is Empty works - passed (%d/2)\n", counter); 
    counter  = 0;
    
    //checks that stack is full works
    if (StackIsFull(&stack) != TRUE){
        counter += 1;
    }
    struct Stack stack_full = {};
    StackInit(&stack_full);
    double i;
    for (i = 0; i<=19; i++){
        StackPush(&stack_full, i);
    }
    if (StackIsFull(&stack_full) == TRUE){
        counter += 1;
    }
    printf("Checking if Stack Is Full works - passed (%d/2)\n", counter); 
    counter = 0;
    
    
    //checks that stack push works
    value = 7;
    StackPush(&stack, value);
    if ((stack.stackItems[stack.currentItemIndex]) == 7) {
        counter += 1;
    }
    if (StackPush(&stack_full, value) == STANDARD_ERROR){
        counter += 1;
    }
    printf("Checking if Stack Push works - passed (%d/2)\n", counter);
    counter = 0;
    
    //checking get size works without error
    if (StackGetSize(&stack) == 1){
        counter += 1;
    }
    if (StackGetSize(&stack_full) == 20) {
        counter += 1;
    }
    printf("Checking if Stack Get Size works - passed (%d/2)\n", counter);
    counter = 0;
    
    //checks stack pop works well
    double value_from_pop;
    StackPop(&stack, &value_from_pop);
    if (value_from_pop == 7){
        counter += 1;
    }
    struct Stack stack_empty = {};
    StackInit(&stack_empty);
    if (StackPop(&stack_empty, &value_from_pop) == STANDARD_ERROR){
        counter +=1;
    }
    printf("Checking if Stack Pop works - passed (%d/2)\n", counter);

    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


