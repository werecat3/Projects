#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 1024

typedef struct {
	unsigned char buffer[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} CircularBuffer;

int full(CircularBuffer *b);

int empty(CircularBuffer *b);

int CB_Init(CircularBuffer *b);

int CB_enqueue(CircularBuffer *b, char input);

unsigned char CB_dequeue(CircularBuffer *b);

#endif /* CIRCULAR_BUFFER_H */