// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

#define FP_DELTA .000001
int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning Jrschlos's rpn test harness: ####\n\n");

    printf("Testing if max string length works\n");
    char test_max[] = "1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + 1 1 + ";
    double result_max;
    RPN_Evaluate(test_max, &result_max);
    printf("Wanted to trigger the error, and it successfully has done so.\n\n");
    printf("Now testing the capabilities of the calculator\n");
    
    //What follows is starter code.  You will need to modify it!
    
    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }
    
    char test1[] = "3 2 *";
    double result1;
    double expected1 = 6;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected1 - result1) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("   Success!\n");
    }
    
    char test2[] = "4 2 /";
    double result2;
    double expected2 = .5;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected2 - result2) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("   Success!\n");
    }
    
    char test3[] = "9 2 -";
    double result3;
    double expected3 = -7;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected3 - result3) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected3, result3);
    } else {
        printf("   Success!\n");
    }
    
    char test4[] = "2.2 6 +";
    double result4;
    double expected4 = 8.2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected4 - result4) < FP_DELTA) {
        printf("   Success!\n");
    } else {
        printf("   Failed, expected = %f , result = %f\n", expected4, result4);
    }
    
    char test5[] = "3 -2 *";
    double result5;
    double expected5 = -6;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test5);
    error = RPN_Evaluate(test5, &result5);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected5 - result5) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected5, result5);
    } else {
        printf("   Success!\n");
    }
    
    char test6[] = "-4 2 /";
    double result6;
    double expected6 = -.5;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test6);
    error = RPN_Evaluate(test6, &result6);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected6 - result6) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected6, result6);
    } else {
        printf("   Success!\n");
    }
    
    char test7[] = ".4 -2 -";
    double result7;
    double expected7 = -2.4;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test7);
    error = RPN_Evaluate(test7, &result7);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected7 - result7) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected7, result7);
    } else {
        printf("   Success!\n");
    }
    
    
    char test8[] = "2 6 + 2 3 4 5 + + + +";
    double result8;
    double expected8 = 22;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test8);
    error = RPN_Evaluate(test8, &result8);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected8 - result8) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected8, result8);
    } else {
        printf("   Success!\n");
    }
    
    char test9[] = "2 7 - 5 6 / 8 7 * 8 9 - + + +";
    double result9;
    double expected9 = 63.2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test9);
    error = RPN_Evaluate(test9, &result9);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected9 - result9) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected9, result9);
    } else {
        printf("   Success!\n");
    }
    
    char test10[] = "57838.4444 9843 /";
    double result10;
    double expected10 = .170;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test10);
    error = RPN_Evaluate(test10, &result10);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected10 - result10) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected10, result10);
    } else {
        printf("   Success!\n");
    }
    
    char test11[] = "9 -2 - 2 3 4 - + 5 5 * 7 8 / + + + ";
    double result11;
    double expected11 = 18.142857;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test11);
    error = RPN_Evaluate(test11, &result11);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (abs(expected11 - result11) > FP_DELTA) {
        printf("   Failed, expected = %f , result = %f\n", expected11, result11);
    } else {
        printf("   Success!\n");
    }
    
    BOARD_End();
    while (1);
     
}


