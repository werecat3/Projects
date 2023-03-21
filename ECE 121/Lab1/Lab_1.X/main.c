/*
 * File:   main.c
 * Author: Werec
 *
 * Created on January 24, 2023, 9:40 PM
 */


#include <xc.h>
#include <stdio.h>
#include <sys/attribs.h>
#include "BOARD.h"
#include "Uart.h"
#include "circularBuffer.h"
#include "MessageIDs.h"
#include "Protocol2.h"
#include "PacketBuffer.h"

extern CircularBuffer uart1RxBuffer;
extern CircularBuffer uart1TxBuffer;
extern PacketBuffer Packet_Buffer;
static int packetcomplete;

//PART 1 test harness
//#define PART_1
#ifdef PART_1
int main(void){
    BOARD_Init();
    Uart_Init(115200);
    while(1){
        U1TXREG = U1RXREG;
    }
}
#endif

//#define PART_2
#ifdef PART_2
int main(void) {
    BOARD_Init();
    Uart_Init(115200);
    //char test_in[] = "hello world!\n";
    //int i = 0;
    //while(i < 13){
    //    PutChar(test_in[i]);
    //    i++;
    //}
    while(1){
        if(empty(&uart1RxBuffer) == FALSE){
            PutChar(GetChar());
        }
    }
    return 0;
}
#endif

//#define PART_3
#ifdef PART_3
int main(void){
    BOARD_Init();
    Protocol_Init(115200);
    rxpADT temp_packet;
    rxpADT printer;
    while(1){
        if(empty(&uart1RxBuffer) == FALSE){
            BuildRxPacket(&temp_packet, GetChar());
            if(packetcomplete == 1){
                Protocol_QueuePacket(temp_packet);
                packetcomplete = 0;
                printer = PB_dequeue(&Packet_Buffer);
                Protocol_SendPacket(printer.len, printer.ID, printer.payLoad);
            }
        }
    }
    return 0;
}
#endif