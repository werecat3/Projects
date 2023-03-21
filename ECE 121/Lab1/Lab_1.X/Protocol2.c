#include <stdio.h>
#include "BOARD.h"
#include "Protocol2.h"
#include <xc.h>
#include "Uart.h"
#include "MessageIDs.h"
#include "PacketBuffer.h"
#include <string.h>
#include <sys/attribs.h>
#include "circularBuffer.h"

static int collision;
static int charflag;
static int packetcomplete;
static int counter;
extern CircularBuffer uart1RxBuffer;
extern CircularBuffer uart1TxBuffer;
PacketBuffer Packet_Buffer;
rxpADT packets;

typedef enum {
    WAIT_FOR_HEAD, LENGTH, ID, PAYLOAD, S_TAIL,
    CHECKSUM, DETERMINE_RESPONSE, END1, END2, SEND
} states;

static states STATE = WAIT_FOR_HEAD;

int Protocol_Init(unsigned long baudrate){
    Uart_Init(baudrate);
    packetcomplete = 0;
    return TRUE;
}

int packet_init(rxpADT *input_p){
    input_p->ID = 0;
    input_p->len = 0;
    input_p->checkSum = 0;
    memset(input_p->payLoad, 0, sizeof(input_p->payLoad));
}

uint8_t Protocol_QueuePacket(rxpADT packet){
    PB_enqueue(&Packet_Buffer, packet);
    return TRUE;
}

int Protocol_GetInPacket(uint8_t *type, uint8_t *len, unsigned char *msg){
    rxpADT temp_packet;
    temp_packet = PB_dequeue(&Packet_Buffer);
    return TRUE;
}

int Protocol_SendDebugMessage(char *Message){
    return Protocol_SendPacket(strlen(Message), ID_DEBUG, Message);
}

int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload){
    PutChar(HEAD);
    PutChar(len);
    PutChar(ID);
    unsigned char checksum = Protocol_CalcIterativeChecksum(ID, 0x00);
    unsigned char* p_copy = Payload;
    p_copy++;
    for(int i = 1; i < len; i++){
        PutChar(*p_copy);
        checksum = Protocol_CalcIterativeChecksum(*p_copy, checksum);
        p_copy++;
    }
    PutChar(TAIL);
    PutChar(checksum);
    PutChar('\r');
    PutChar('\n');
    return TRUE;
}

unsigned char Protocol_ReadNextPacketID(void){
    if(PB_empty(&Packet_Buffer) != TRUE){
        rxpADT temp = PB_dequeue(&Packet_Buffer);
        return temp.ID;
    }
}

void flushPacketBuffer (){
    PB_Init(&Packet_Buffer);
    //this has a memset in it so it can flush it.
}

unsigned int convertEndian(unsigned int b){
    b = ((b >> 24) & 0xFF) | ((b << 8) & 0xFF0000) 
            | ((b >> 8) & 0xFF00) | ((b << 24) & 0xFF000000);
    return b;
}

//pong stuff is my idea for the convert endian. 
void pong_stuff(unsigned char* array){
    //unsigned char* pong_message = (unsigned char*) array;
    unsigned char* PONG = (unsigned char*) array;
    unsigned int zero = ((unsigned int) PONG[1]) << 24;
    unsigned int ones = ((unsigned int) PONG[2]) << 16;
    unsigned int twos = ((unsigned int) PONG[3]) << 8;
    unsigned int thrs = ((unsigned int) PONG[4]);
    
    uint32_t div = ((array[1]) << 24)| ((array[2]) << 16)|((array[3]) << 8)|((array[4]));
    div = (zero | ones | twos | thrs) >> 1;
    //div = (zero | ones | twos | thrs)/ 2;
    array[1] = (div >> 24) & 0xFF;
    array[2] = (div >> 16) & 0xFF;
    array[3] = (div >> 8) & 0xFF;
    array[4] = (div & 0xFF);
    
       
}

uint8_t BuildRxPacket (rxpADT *rxPacket, unsigned char input){
    char *error_tail = "There wasn't a tail given\n";
    char *error_checksum = "The checksums didn't end up matching\n";
    char *error_incomplete = "Something is missing from the packet\n";
    
    switch(STATE){
        case WAIT_FOR_HEAD:
            if(input == HEAD){
                STATE = LENGTH;
            }
            break;
        case LENGTH:
            rxPacket->len = input;
            STATE = ID;
            break;
            
        case ID:
            rxPacket->ID = input;
            counter = 1;
            STATE = PAYLOAD;
            break;
            
        case PAYLOAD:
            rxPacket->payLoad[counter] = input;
            if(counter == rxPacket->len){
                STATE = S_TAIL;
            }
            counter++;
            
        case S_TAIL:
            STATE = CHECKSUM;
            
        case CHECKSUM:
            rxPacket->checkSum = input;
            STATE = END1;
            
        case END1:
            if(input == 0x0D){
                STATE = END2;
            }
            
        case END2:
            if(input == 0x0A){
                STATE = SEND;
            }
            
        case SEND:
            
            counter = 0;
            if(rxPacket->ID == ID_LEDS_SET){
                LATE = rxPacket->payLoad[1];
                packetcomplete = 1;
                STATE = WAIT_FOR_HEAD;
            }
            else if(rxPacket->ID == ID_LEDS_GET){
                unsigned char leds = LEDS_GET();
                rxPacket->ID = ID_LEDS_STATE;
                rxPacket->len = 0x02;
                rxPacket->payLoad[1] = leds;
                packetcomplete = 1;
                STATE = WAIT_FOR_HEAD;
            }
            else if(rxPacket->ID == ID_PING){
                rxPacket->ID = ID_PONG;
                //pong_stuff(rxPacket->payLoad);
                STATE = WAIT_FOR_HEAD;
            }
            else{
                packetcomplete = 1;
                STATE = WAIT_FOR_HEAD;
            }
             
            packetcomplete = 1;
            STATE = WAIT_FOR_HEAD;
    }
    return TRUE;
}

unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum){
    curChecksum = (curChecksum >> 1) + (curChecksum << 7);
    curChecksum = curChecksum + charIn;
    return curChecksum;
}


#define PART_3
#ifdef PART_3
int main(void){
    BOARD_Init();
    Protocol_Init(115200);
    LEDS_INIT();
    rxpADT temp_packet;
    rxpADT printer;
    packet_init(&printer);
    packet_init(&temp_packet);
    
    printer.len = 0x07;
    printer.ID = ID_DEBUG;
    printer.payLoad[1] = 'J';
    printer.payLoad[2] = 'e';
    printer.payLoad[3] = 'r';
    printer.payLoad[4] = 'r';
    printer.payLoad[5] = 'e';
    printer.payLoad[6] = 't';
    Protocol_QueuePacket(printer);
    temp_packet = PB_dequeue(&Packet_Buffer);
    Protocol_SendPacket(temp_packet.len, temp_packet.ID, temp_packet.payLoad);
    
    
    while(1){
        if(empty(&uart1RxBuffer) == FALSE){
            unsigned char inputs = GetChar();
            BuildRxPacket(&temp_packet, inputs);
            if(packetcomplete == 1){
                Protocol_QueuePacket(temp_packet);
                packetcomplete = 0;
                printer = PB_dequeue(&Packet_Buffer);
                if(printer.ID == ID_PONG){
                }
                Protocol_SendPacket(printer.len, printer.ID, printer.payLoad);
            }
        }
    } 
    return 0;
}
#endif