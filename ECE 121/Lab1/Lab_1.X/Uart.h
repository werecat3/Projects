/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef UART_H    /* Guard against multiple inclusion */
#define UART_H

#define DESIRED_BAUD_RATE 115200 

void Uart_Init(unsigned long baudRate);

int PutChar(char ch);

unsigned char GetChar(void);

#endif /* _EXAMPLE_FILE_NAME_H */


