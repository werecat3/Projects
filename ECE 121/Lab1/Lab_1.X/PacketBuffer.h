#ifndef PACKET_BUFFER_H
#define PACKET_BUFFER_H

#include <stdint.h>
#include "Protocol2.h"

#define BUFFER_SIZE 16

typedef struct {
	rxpADT buffer[PACKETBUFFERSIZE];
    int head;
    int tail;
    int size;
} PacketBuffer;

int PB_full(PacketBuffer *b);

int PB_empty(PacketBuffer *b);

int PB_Init(PacketBuffer *b);

int PB_enqueue(PacketBuffer *b, rxpADT input);

rxpADT PB_dequeue(PacketBuffer *b);

#endif 