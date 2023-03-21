/* 
 * File:   MessageTest.c
 * Author: Werec
 *
 * Created on May 31, 2021, 4:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Message.h"

int test_counter;
BB_Event thing = {BB_EVENT_NO_EVENT};
/*
 * 
 */
int main(void) {
    BOARD_Init();
    test_counter = 0;
    printf("The beginning of Xuxuan and Jerret's Message test harness\n\n");
    printf("-----------------------------\n");
    
    printf("Testing of Message_CaculateChecksum\n");
    uint8_t correct_answer_1 = 0x5A;
    const char* test_1 = {"RES,1,0,3"};
    if(Message_CalculateChecksum(test_1) == correct_answer_1){
        test_counter += 1;
    }
    uint8_t correct_answer_2 = 0x52;
    const char* test_2 = {"SHO,2,4"};
    if(Message_CalculateChecksum(test_2) == correct_answer_2){
        test_counter += 1;
    }
    printf("Message_CalculateChecksum passed (%d/2)\n", test_counter);
    printf("-----------------------------\n");
    test_counter = 0;
    
    
    printf("Testing of Message_ParseMessage\n");
    char error_checker_1[4] = "5A";
    const char* error_checker_2 = {"544"};
    //checking if errors are activated with bad inputs
    if(Message_ParseMessage(test_1, error_checker_2, &thing) == STANDARD_ERROR){
        test_counter += 1;
    }
    if(Message_ParseMessage(test_1, error_checker_1, &thing) == SUCCESS){
        test_counter += 1;
    }
    const char* test_3 = {"CHA,"};
    if(Message_ParseMessage(test_3, error_checker_1, &thing) == STANDARD_ERROR){
        test_counter += 1;
    }
    char test_4[9] = "CHA,1";
    char error_checker_3[4] = "57";
    if(Message_ParseMessage(test_4, error_checker_3, &thing) == SUCCESS){
        test_counter += 1;
    }
    char test_5[9] = "ACC,1";
    if(Message_ParseMessage(test_5, error_checker_3, &thing) == STANDARD_ERROR){
        test_counter += 1;
    }
    char test_6[9] = "REV,1";
    if(Message_ParseMessage(test_6, error_checker_3, &thing) == STANDARD_ERROR){
        test_counter += 1;
    }
    char test_7[9] = "SHO,1,2";
    if(Message_ParseMessage(test_7, error_checker_3, &thing) == SUCCESS){
        test_counter += 1;
    }
    char test_8[23] = "RESert,1,0,2";
    if(Message_ParseMessage(test_8, error_checker_3, &thing) == STANDARD_ERROR){
        test_counter += 1;
    }
    printf("Message_ParseMessage passed (%d/8)\n", test_counter);
    printf("-----------------------------\n");
    test_counter = 0;
    
    
    printf("Testing of Message_Encode\n");
    Message test_struct = {MESSAGE_CHA,4};
    char message;
    if (Message_Encode(&message, test_struct) == 10){
        test_counter += 1;
    }
    Message test_struct_2 = {MESSAGE_NONE};
    if (Message_Encode(&message, test_struct_2) == 0){
        test_counter += 1;
    }
    printf("Message_Encode passed (%d/2)\n", test_counter);
    printf("-----------------------------\n");
    test_counter = 0;
    
    
    printf("Testing of Message_Decode\n");
    BB_Event test_struct_3 = {BB_EVENT_NO_EVENT};
    unsigned char test_char_0 = '$';
    unsigned char test_char_1 = 'R';
    unsigned char test_char_2 = 'E';
    unsigned char test_char_3 = 'S';
    unsigned char test_char_4 = ',';
    unsigned char test_char_5 = '1';
    unsigned char test_char_6 = ',';
    unsigned char test_char_7 = '0';
    unsigned char test_char_8 = ',';
    unsigned char test_char_9 = '3';
    unsigned char test_char_10 = '*';
    unsigned char test_char_11 = '5';
    unsigned char test_char_12 = 'A';
    unsigned char test_char_13 = '\n';
    Message_Decode(test_char_0, &test_struct_3);
    Message_Decode(test_char_1, &test_struct_3);
    Message_Decode(test_char_2, &test_struct_3);
    Message_Decode(test_char_3, &test_struct_3);
    Message_Decode(test_char_4, &test_struct_3);
    Message_Decode(test_char_5, &test_struct_3);
    Message_Decode(test_char_6, &test_struct_3);
    Message_Decode(test_char_7, &test_struct_3);
    Message_Decode(test_char_8, &test_struct_3);
    Message_Decode(test_char_9, &test_struct_3);
    Message_Decode(test_char_10, &test_struct_3);
    Message_Decode(test_char_11, &test_struct_3);
    Message_Decode(test_char_12, &test_struct_3);
    if (Message_Decode(test_char_13, &test_struct_3) == SUCCESS){
        test_counter += 1;
    }
    BB_Event test_struct_4 = {BB_EVENT_NO_EVENT};
    Message_Decode(test_char_0, &test_struct_4);
    if (Message_Decode(test_char_0, &test_struct_4) == STANDARD_ERROR){
        test_counter += 1;
    }
    if (Message_Decode(test_char_0, &test_struct_4) == SUCCESS){
        test_counter += 1;
    }
    if (Message_Decode(test_char_13, &test_struct_4) == STANDARD_ERROR){
        test_counter += 1;
    }
    Message_Decode(test_char_0, &test_struct_4);
    Message_Decode(test_char_1, &test_struct_4);
    Message_Decode(test_char_10, &test_struct_4);
    Message_Decode(test_char_11, &test_struct_4);
    if (Message_Decode(test_char_13, &test_struct_4) == STANDARD_ERROR){
       test_counter += 1;
    }
    
    printf("Message_Decode passed (%d/5)\n", test_counter);
    printf("-----------------------------\n");
    test_counter = 0;
    
    
    

    BOARD_End();
    while (1);
    return 0;
}

