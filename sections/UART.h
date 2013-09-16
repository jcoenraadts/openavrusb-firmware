#ifndef UART_H_
#define UART_H_

#include "avr\io.h"
#include <avr/interrupt.h>
#include "opcodes.h"
#include "../IN_report.h"
#include "../usb_descriptors.h"

#ifndef RXB8
#define RXB8 1
#endif

#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

#define UART_WRITE 0x10
#define UART_SET_BAUD 0x20
#define UART_SET_REGS 0x21
#define UART_ASYNC_RX 0x11

//#define RX_BUFFER_SIZE1 59
#define TX_BUFFER_SIZE1 (LENGTH_OF_REPORT_OUT - IN_REPORT_HEADER_LENGTH)

void instrCall_UART(char instruction, char* data, char dataLength);
void UART_setBaudRate(char* data);
void UART_write(char* data, char dataLength);
void UART_setRegisters(char *data);
char getchar1(void);
void putchar1(char c);

#endif /* UART_H_ */
