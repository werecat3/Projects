#include <stdio.h>
#include <string.h>
#include "BOARD.h"
#include "circularBuffer.h"
#include <xc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


int CB_Init(CircularBuffer *b)
{
    b->head = 0;
    b->tail = 0;
    b->size = 0;
    memset(b->buffer, 0, sizeof(b->buffer));
	return TRUE;
}

int full(CircularBuffer *b) {
    if(b->head == (b->tail) % BUFFER_SIZE ){
        if(b->size > 0){
            return TRUE;
        }
    }
    return FALSE;
}
    

int empty(CircularBuffer *b){
    if(b->size == 0){
        return TRUE;
    }
    return FALSE;
}

int CB_enqueue(CircularBuffer *b, char input){
    if(full(b) == TRUE){
        return FALSE;
    }
    b->buffer[b->tail] = input;
    b->tail = (b->tail + 1) %  BUFFER_SIZE;
    b->size++;
}

unsigned char CB_dequeue(CircularBuffer *b){
    unsigned char output;
    if(empty(b) == TRUE){
        return FALSE;
    }
    output = b->buffer[b->head];
    b->head = (b->head + 1) % BUFFER_SIZE;
    b->size--;
    return output;
}

//#define TEST_CIRCULAR

#ifdef TEST_CIRCULAR
//TEST HARNESS
int main(void) {
    CircularBuffer test_buffer;
    CB_Init(&test_buffer);
    char input[2] = "AB";
    int i = 0;
    while(i < 26){
        if(i < 16){
            CB_enqueue(&test_buffer, input[0]);
            if(full(&test_buffer) == TRUE){
                int itsfull = 223;
            }
        }
        else if(i >= 16 & i < 21){
            unsigned char output = CB_dequeue(&test_buffer);
            int stop = 0;
        }
        else{
            CB_enqueue(&test_buffer, input[1]);
        }
        i++;
    }
    return 0;
}
#endif
