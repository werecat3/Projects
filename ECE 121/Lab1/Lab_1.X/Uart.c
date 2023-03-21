/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */


#include <stdio.h>
#include "BOARD.h"
#include "Uart.h"
#include <xc.h>
#include "circularBuffer.h"
#include <sys/attribs.h>

CircularBuffer uart1RxBuffer;
CircularBuffer uart1TxBuffer;


unsigned char output;

static int transmit;
static int collision;
static int testing;
static int collision;
static int clear;
static int charflag;

void Uart_Init(unsigned long baudRate){
    U1MODE = 0x0; // Clear U1MODE register
    U1STA = 0x0; // Clear U1STA register
    U1BRG = 0x0; // Clear U1BRG register
    U1BRG = ((40000000/baudRate)/16) - 1; // Configure baud rate, we want 20 or 21
    //U1MODEbits.ON = 1; // Enable UART1, 8N1
    //U1MODEbits.PDSEL = 00;
    U1MODE = 0x8000;
    
    U1STAbits.URXEN = 1; // Enable transmitter and receiver
    U1STAbits.UTXEN = 1;
    
    IEC0bits.U1TXIE = 1; //turns on tx interrupt
    U1STAbits.UTXISEL = 0b01; //makes interrupt happen when nothing is in tx buffer
    IFS0bits.U1TXIF = 0; //clears the flags
    
    IEC0bits.U1RXIE = 1; //turns on rx interrupt
    U1STAbits.URXISEL = 0b00; //makes interrupt happen when something is in rx buffer
    IFS0bits.U1RXIF = 0; //clears the flags
    
    IPC6bits.U1IP = 6; //interrupt protocol priority
    IPC6bits.U1IS = 0; //interrupt sub protocol priority
    
    CB_Init(&uart1RxBuffer);
    CB_Init(&uart1TxBuffer);
    collision = 0;
}

int PutChar(char ch){ 
    if(full(&uart1TxBuffer) == TRUE){
        return FALSE;
    }
    charflag = 1;
    CB_enqueue(&uart1TxBuffer, ch);
    charflag = 0;
    
    
    if(U1STAbits.TRMT == 1){
        IFS0bits.U1TXIF = 1;
    }
    else if(collision == 1){
        IFS0bits.U1TXIF = 1;
        collision = 0;
    }
    return TRUE;
}

unsigned char GetChar(void) {
    if(empty(&uart1RxBuffer) == TRUE){
        return FALSE;
    }
    unsigned char output;
    output = CB_dequeue(&uart1RxBuffer);
    return output;
}


void __ISR(_UART_1_VECTOR)IntUart1Handler(void){
    if(IFS0bits.U1RXIF == 1)
        IFS0bits.U1RXIF = 0;
        CB_enqueue(&uart1RxBuffer, U1RXREG);
    }
    
    
    if(IFS0bits.U1TXIF == 1){
        if(charflag == 1){
            collision = 1;
            IFS0bits.U1TXIF = 0;
        }
        else if(empty(&uart1TxBuffer) == FALSE){
            if(U1STAbits.UTXBF ==  0){
                output = CB_dequeue(&uart1TxBuffer);
                U1TXREG = output;
                IFS0bits.U1TXIF = 0;
            } else {
                IFS0bits.U1TXIF = 0;
            }
        }
    }
    IFS0bits.U1TXIF = 0;
}


//#define UART_TEST_HARNESS
#ifdef UART_TEST_HARNESS

int main(void){
    //CircularBuffer test_buff;
    //CB_Init(test_buff);
    int empty_flag = 0;
    int non_empty_flag = 0;
    Uart_Init(115200);
    if(empty(&uart1TxBuffer) == TRUE){
        empty_flag = 1;
    }
    char *input = "A";
    PutChar(input[0]);
    char *input2 = "a";
    char idk = input[0];
    CB_enqueue(&uart1TxBuffer, idk);
    if(empty(&uart1TxBuffer) == FALSE){
        non_empty_flag = 1;
    }
    return 0;
}

#endif