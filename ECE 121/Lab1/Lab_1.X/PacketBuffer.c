#include <stdio.h>
#include <string.h>
#include "BOARD.h"
#include "PacketBuffer.h"
#include <xc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

static rxpADT fail;

int PB_Init(PacketBuffer *b)
{
    b->head = 0;
    b->tail = 0;
    b->size = 0;
    memset(b->buffer, 0, sizeof(b->buffer));
	return TRUE;
}

int PB_full(PacketBuffer *b) {
    if(b->head == (b->tail) % BUFFER_SIZE ){
        if(b->size > 0){
            return TRUE;
        }
    }
    return FALSE;
}
    

int PB_empty(PacketBuffer *b){
    if(b->size == 0){
        return TRUE;
    }
    return FALSE;
}

int PB_enqueue(PacketBuffer *b, rxpADT input){
    if(PB_full(b) == TRUE){
        return FALSE;
    }
    b->buffer[b->tail] = input;
    b->tail = (b->tail + 1) %  BUFFER_SIZE;
    b->size++;
}

rxpADT PB_dequeue(PacketBuffer *b){
    rxpADT output;
    if(PB_empty(b) == TRUE){
        return fail;
    }
    output = b->buffer[b->head];
    b->head = (b->head + 1) % BUFFER_SIZE;
    b->size--;
    return output;
}

