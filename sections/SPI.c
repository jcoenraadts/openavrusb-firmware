#include "SPI.h"
#include "GPIO.h"

extern char buf_SPI_RX_count;
extern char buffer_REPLY[BUF_SIZE_REPLY];
extern char buffer_SPI_RX[BUF_SIZE_SPI_RX];

//SPI section is 0x12
void instrCall_SPI(char instruction, char* datain, char dataLength)
{
  switch (instruction)
  {
  case SPI_TRANSACTION:		//protocol: b[0] CS port, b[1] CS bitmask, [2..N] data
    {
      writeIOPort(datain[0], 0x00, datain[1]);		//set nominated CS line low
      SPI_TransactionExt(&datain[2], dataLength - 2);
      writeIOPort(datain[0], 0xFF, datain[1]);		//set nominated CS line high
      break;
    }
  case SPI_SET_CTRL_REG:
    {
      SPI_setCtrlRegisters(datain);
      break;
    }
  }
}

void SPI_setCtrlRegisters(char* datain)
{
  SPCR = datain[0];
  SPSR = datain[1];
}

void SPI_TransactionExt(char* datain, char dataLength)
{
  char i;

  //begin transfer
  for(i = 0; i < dataLength; i++)
	  buffer_REPLY[IN_REPORT_HEADER_LENGTH + i] = SPI_byteTransactionExt(datain[i]);  //replaces the sent data with received data

  //reply with data shifted in
  setReplyInherentData(S_SPI, SPI_SLAVE_REPLY, dataLength, 0x00);
}

char SPI_byteTransactionExt(char byte)
{

  SPDR = byte;
  while(!(SPSR & (1 << SPIF)));  //wait for the flag to be set such that the transaction is complete
  SPSR &= 0x7F;                 //clear the TXC flag
  return SPDR;
}

ISR(SPI_STC_vect)
{
	char SPI_data = SPDR;
	if (buf_SPI_RX_count == 0)	//a new in-report must be created
	{
		//This will be set later in the setInReport method (datalength)
		setReplyHeader(&buffer_SPI_RX[0], S_SPI, SPI_SLAVE_REPLY, 0x00, 0x00, 0x00);
		buf_SPI_RX_count = IN_REPORT_HEADER_LENGTH;
	}

	if (buf_SPI_RX_count >= BUF_SIZE_UART_RX)
		return;			//dump any bytes if the buffer overflows

	buffer_SPI_RX[buf_SPI_RX_count] = SPI_data;
	buf_SPI_RX_count++;
}

