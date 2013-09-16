#include "UART.h"

extern char buffer_UART_RX[BUF_SIZE_UART_RX];
extern char buf_UART_RX_count;

//UART section is 0x10
void instrCall_UART(char instruction, char* datain, char dataLength)
{
  switch (instruction)
  {
  case UART_WRITE:
    {
      UART_write(datain, dataLength);
      break;
    }
  case UART_SET_BAUD:
    {
      UART_setBaudRate(datain);
      break;
    }
  case UART_SET_REGS:
    {
	  UART_setRegisters(datain);
	  break;
    }
  }
}

//Set baud rate method
void UART_setBaudRate(char* datain)
{
  UBRR1H = datain[1];
  UBRR1L = datain[0];
}

//data: UCSR1A UCSR1B UCSR1C UCSR1D UBRR1H UBRR1L
void UART_setRegisters(char *datain)
{
	UCSR1A = datain[0];
	UCSR1B = datain[1];
	UCSR1C = datain[2];
	UCSR1D = datain[3];

	UBRR1L = datain[4];
	UBRR1H = datain[5];
}

void UART_write(char* datain, char dataLength)
{
  unsigned char i;
  //Send dataPacket to uart buffer
  for (i = 0; i < dataLength; i++)
      putchar1(datain[i]);
}

//-------------- UART RX Code -----------------------------
// This interrupt will copy the byte to the UART RX buffer which will be
// automatically transmitted to the PC in IN_report.c

// USART1 Receiver interrupt service routine
ISR(USART1_RX_vect)
{
	char status,datain;
	status=UCSR1A;
	datain=UDR1;
	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))!=0)
		return;			//dump the byte if the status is bad

	if (buf_UART_RX_count == 0)	//a new in-report must be created
	{
		//This will be set later in the setInReport method (datalength)
		setReplyHeader(&buffer_UART_RX[0], S_UART, UART_ASYNC_RX, 0x00, 0x00, 0x00);
		buf_UART_RX_count = IN_REPORT_HEADER_LENGTH;
	}

	if (buf_UART_RX_count >= BUF_SIZE_UART_RX)
		return;			//dump any bytes if the buffer overflows

	buffer_UART_RX[buf_UART_RX_count] = datain;
	buf_UART_RX_count++;
}

//-------------- UART TX Code -----------------------------
char tx_buffer1[TX_BUFFER_SIZE1];
unsigned char tx_wr_index1,tx_rd_index1,tx_counter1;

// USART1 Transmitter interrupt service routine
ISR(USART1_TX_vect)
{
if (tx_counter1)
   {
   --tx_counter1;
   UDR1=tx_buffer1[tx_rd_index1];
   if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
   }
}

// Write a character to the USART1 Transmitter buffer
void putchar1(char c)
{
while (tx_counter1 == TX_BUFFER_SIZE1);
asm("cli");
if (tx_counter1 || ((UCSR1A & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer1[tx_wr_index1]=c;
   if (++tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
   ++tx_counter1;
   }
else
   UDR1=c;
asm("sei");
}


