#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BOARD.h"
#include "stack.h"



void StackInit(struct Stack *stack) {
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackPush(struct Stack *stack, double value) {
    if (stack->initialized != TRUE || StackIsFull(stack) == TRUE){
        return STANDARD_ERROR;
    }
    
    stack->stackItems[++stack->currentItemIndex] = value;
    //stack->currentItemIndex + 1;
    return SUCCESS;       
    
}

int StackPop(struct Stack *stack, double *value) {
    if (stack->initialized != TRUE || StackIsEmpty(stack) == TRUE){
        return STANDARD_ERROR;
    }
    *value = stack->stackItems[stack->currentItemIndex];
    stack->currentItemIndex -= 1 ;
    return SUCCESS;
}

int StackIsEmpty(const struct Stack *stack) {
    if (stack->initialized != TRUE){
        return FALSE;
    }
    if (stack->currentItemIndex == - 1){
        return TRUE;
    }
    else{
        return FALSE;
    }
    
}

int StackIsFull(const struct Stack *stack) {
    if (stack->initialized != TRUE){
        return FALSE;
    }
    if (stack->currentItemIndex == STACK_SIZE - 1){
        return TRUE;
    }
    else{
        return FALSE;
    }
    
}

int StackGetSize(const struct Stack *stack) { 
    if (stack->initialized != TRUE){
        return FALSE;
    }
    return stack->currentItemIndex + 1;
}