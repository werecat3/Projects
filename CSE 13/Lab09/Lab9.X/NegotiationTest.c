/* 
 * File:   NegotiationTest.c
 * Author: Werec
 *
 * Created on May 31, 2021, 1:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Negotiation.h"

int test_counter;
/*
 * 
 */
int main(void) {
    BOARD_Init();
    printf("The beginning of Xuxuan and Jerret's Negotiation test harness\n\n");
    printf("-----------------------------\n");
    printf("Testing of NegotiationHash\n");
    test_counter = 0;
    
    if (NegotiationHash(12345) == 43182){
        test_counter += 1;
    }
    if (NegotiationHash(3) == 9){
        test_counter += 1;
    }
    
    printf("NegotiationHash passed (%d/2)\n", test_counter);
    printf("-----------------------------\n");
    test_counter = 0;
    
    printf("testing of NegotiationVerify\n");
    if (NegotiationVerify(12345, NegotiationHash(12345)) == TRUE){
        test_counter += 1;
    }
    if (NegotiationVerify(3, NegotiationHash(3)) == TRUE){
        test_counter += 1;
    }
    printf("NegotiationVerify passed (%d/2)\n", test_counter);
    printf("-----------------------------\n");
    test_counter = 0;
    
    printf("testing of NegotiateCoinFlip\n");
    
    if (NegotiateCoinFlip(51, 73) == HEADS){
        test_counter += 1;
    }
    if (NegotiateCoinFlip(255, 255) == TAILS){
        test_counter += 1;
    }
    printf("NegotiateCoinFlip passed (%d/2)\n", test_counter);
    printf("-----------------------------\n\n");

    BOARD_End();
    while (1);
    return 0;
}

