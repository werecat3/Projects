#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BOARD.h"
#include "stack.h"
#include "rpn.h"

int RPN_Evaluate(char * rpn_string, double * result) {
    struct Stack stack = {};
    StackInit(&stack);
    double num1;
    double num2;
    char *token;
    int check1;
    int check2;
    int check3;
    double total;
    float number;
    int l;
    int i;
     
    
    token = strtok(rpn_string, " ");
    
    while(token != NULL) {
        l = 0;
        for (i = 0; token[i] != '\0'; i++){
            if (token[i] == '-') {
                l++;
            }
            if (token[i] == '1') {
                l++;
            }
            if (token[i] == '2') {
                l++;
            }
            if (token[i] == '3') {
                l++;
            }
            if (token[i] == '4') {
                l++;
            }
            if (token[i] == '5') {
                l++;
            }
            if (token[i] == '6') {
                l++;
            }
            if (token[i] == '7') {
                l++;
            }
            if (token[i] == '8') {
                l++;
            }
            if (token[i] == '9') {
                l++;
            }
        }
        if (*token == '+'){
            check1 = StackPop(&stack, &num2);
            check2 = StackPop(&stack, &num1);
            if (check1 == STANDARD_ERROR || check2 == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            } 
            else {
                total = num2 + num1;
                StackPush(&stack, total);
                
            }
        }
        
        else if (*token == '-' && l == 1){
            check1 = StackPop(&stack, &num2);
            check2 = StackPop(&stack, &num1); 
            if (check1 == STANDARD_ERROR || check2 == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            } 
            else {
                total = num2 - num1;
                StackPush(&stack, total);
            }
        }
        else if (*token == '/'){
            check1 = StackPop(&stack, &num2);
            check2 = StackPop(&stack, &num1); 
            if (check1 == STANDARD_ERROR || check2 == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            } 
            else {
                if (num1 == 0) {
                    return RPN_ERROR_DIVIDE_BY_ZERO;
                }
                else {
                    total = num2 / num1;
                    StackPush(&stack, total);
                }
            }
        }
        else if (*token == '*'){
            check1 = StackPop(&stack, &num2);
            check2 = StackPop(&stack, &num1); 
            if (check1 == STANDARD_ERROR || check2 == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            } 
            else {
                total = num2 * num1;
                StackPush(&stack, total);
            }
        }   
        else{
            if(sscanf(token, "%f", &number) == 0){;
                return RPN_ERROR_INVALID_TOKEN;
            }
            else{
                number = atof(token);
                if (number == 0){
                    return RPN_ERROR_INVALID_TOKEN;
                }
                else{
                    check3 = StackPush(&stack, number);
                    if (check3 == STANDARD_ERROR) {
                        return RPN_ERROR_STACK_OVERFLOW;
                    }
                }
            }
        }
        token = strtok(NULL, " ");
        
    } 
    if (stack.currentItemIndex == 0){
        *result = stack.stackItems[stack.currentItemIndex];
        return RPN_NO_ERROR;
    }
    if (stack.currentItemIndex < 0){
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    else {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    
}
/*
int ProcessBackspaces(char *rpn_sentence) {
    
    //do this last
}
*/

