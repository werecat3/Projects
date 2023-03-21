#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BOARD.h"
#include "Message.h"

int string_counter;
int top_of_ascii = 127;

uint8_t Message_CalculateChecksum(const char* payload){
    int length = strlen(payload);
    int i;
    uint8_t checkSum = 0;
    //const char* null = {"\0"};
    for(i = 0; i < length; i++){
        checkSum = checkSum ^ payload[i];
        string_counter += 1;
    }
    return checkSum;
}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event){
    if (strlen(payload) < 5){
        return STANDARD_ERROR;
    }
    if (strlen(checksum_string) != 2){
        return STANDARD_ERROR;
    }
    char *ptr;
    long checksum_checker = strtoul(checksum_string, &ptr, 16);
    if (Message_CalculateChecksum(payload) != checksum_checker){
        return STANDARD_ERROR;
    }
    //
    //checking the message id now this is what changes the state in the struct
    //
    char str[MESSAGE_MAX_PAYLOAD_LEN];
    strcpy(str, payload);
    const char delim[2] = ",";
    char *index;
    char *message_id;
    
    int counter = 0;
    index = strtok(str, delim);
    while(index != NULL) {
        if (counter == 0){
            message_id = index;
        }
        else if (counter == 1){
            message_event->param0 = (unsigned)atol(index);
        }
        else if (counter == 2){
            message_event->param1 = (unsigned)atol(index);
        }
        else if (counter == 3){
            message_event->param2 = (unsigned)atol(index);
        }
        else {
            return STANDARD_ERROR;
        }
        counter += 1;
        index = strtok(NULL, delim);
    }
    
    if (strcmp(message_id, "CHA") == 0){ //for CHA
        if (counter != 2){
            return STANDARD_ERROR;
        }
        message_event->type = BB_EVENT_CHA_RECEIVED;
        return SUCCESS;
    }
    
    else if (strcmp(message_id, "ACC") == 0){ //for ACC
        if (counter != 2){
            return STANDARD_ERROR;
        }
        message_event->type = BB_EVENT_ACC_RECEIVED;
        return SUCCESS;
    }
    
    else if (strcmp(message_id, "REV") == 0){ //for REV
        if (counter != 2){
            return STANDARD_ERROR;
        }
        message_event->type = BB_EVENT_REV_RECEIVED;
        return SUCCESS;
    }
    
    else if (strcmp(message_id, "SHO") == 0){ //for SHO
        if (counter != 3){
            return STANDARD_ERROR;
        }
        message_event->type = BB_EVENT_SHO_RECEIVED;
        return SUCCESS;
    }
    
    else if (strcmp(message_id, "RES") == 0){ //for RES
        if (counter != 4){
            return STANDARD_ERROR;
        }
        message_event->type = BB_EVENT_RES_RECEIVED;
        return SUCCESS;
    }
    
    else {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }
    
    return SUCCESS; //only happens if it gets through the gauntlet of ifs
}

int Message_Encode(char *message_string, Message message_to_encode){
    char string[MESSAGE_MAX_LEN];
    char another_string[MESSAGE_MAX_LEN];
    uint8_t checksum;
    switch(message_to_encode.type){
        case MESSAGE_CHA:
            sprintf(string, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
            break;
        case MESSAGE_ACC:
            sprintf(string, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
            break;
        case MESSAGE_REV:
            sprintf(string, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
            break;
        case MESSAGE_SHO:
            sprintf(string, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, 
                    message_to_encode.param1);
            break;
        case MESSAGE_RES:
            sprintf(string, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, 
                    message_to_encode.param1, message_to_encode.param2);
            break;
        default:
            return 0;
    }
    checksum = Message_CalculateChecksum(string);
    sprintf(another_string, MESSAGE_TEMPLATE, string, checksum);
    message_string = another_string;
    int length = strlen(message_string);
    return length;
}
typedef enum{
    WAITING, RECORDING_PAYLOAD, RECORDING_CHECKSUM,
}DecodeState;

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event){
    static DecodeState decState = WAITING;
    static char created_payload[MESSAGE_MAX_PAYLOAD_LEN + 1];
    static char created_checksum[MESSAGE_CHECKSUM_LEN + 1];
    static int index_1;
    static int index_2;
    switch(decState){
        case WAITING:
            if (char_in == '$'){
                index_1 = 0;
                index_2 = 0;
                decState = RECORDING_PAYLOAD;
            }
            break;
        case RECORDING_PAYLOAD:
            if (char_in == '$' || char_in == '\n'){
                decState = WAITING;
                decoded_message_event->type = BB_EVENT_ERROR;
                decoded_message_event->param0 = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
                return STANDARD_ERROR;
            }
            else if(char_in == '*'){
                decState = RECORDING_CHECKSUM;
            }
            else{
                created_payload[index_1] = char_in;
                index_1 += 1;
                if (index_1 >= MESSAGE_MAX_PAYLOAD_LEN){
                    return STANDARD_ERROR;
                }
            }
            break;
        case RECORDING_CHECKSUM:
            if (char_in == '*'){
                decState = WAITING;
                decoded_message_event->type = BB_EVENT_ERROR;
                decoded_message_event->param0 = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
                return STANDARD_ERROR;
            }
            else if (char_in == '\n'){
                decState = WAITING;
                if (strlen(created_checksum) != MESSAGE_CHECKSUM_LEN){
                    return STANDARD_ERROR;
                }
                if (Message_ParseMessage(created_payload, created_checksum, decoded_message_event) == SUCCESS){
                    memset(created_payload, 0, MESSAGE_MAX_PAYLOAD_LEN + 1);
                    memset(created_checksum, 0, MESSAGE_CHECKSUM_LEN + 1);
                    return SUCCESS;
                }
                else{
                    memset(created_payload, 0, MESSAGE_MAX_PAYLOAD_LEN + 1);
                    memset(created_checksum, 0, MESSAGE_CHECKSUM_LEN + 1);
                    return STANDARD_ERROR;
                }
            }
            else{
                created_checksum[index_2] = char_in;
                index_2 += 1;
                if (index_2 >= MESSAGE_CHECKSUM_LEN){
                    return STANDARD_ERROR;
                }
            }
            break;
        default:
            decState = WAITING;
            break;
    }
    return SUCCESS;
}
