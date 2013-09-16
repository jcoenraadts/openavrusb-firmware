#include "IN_report.h"
#include "usb_descriptors.h"
#include "lib_mcu/usb/usb_drv.h"
#include "sections/UART.h"


//Define buffers for all message types
char buffer_UART_RX[BUF_SIZE_UART_RX];
char buffer_SPI_RX[BUF_SIZE_SPI_RX];
char buffer_I2C_RX[BUF_SIZE_I2C_RX];
char buffer_REPLY[BUF_SIZE_REPLY];

//Define counters for each buffer
char buf_UART_RX_count = 0;
char buf_SPI_RX_count = 0;
char buf_I2C_RX_count = 0;
char buf_REPLY_RX_count = 0;

//Precedence of IN reports:
//Message reply
//UART RX
//SPI RX
//I2C RX
void setINreport(void)
{
	char pktLength = 0;
	char* ptr = &buffer_REPLY[0];
	if (buf_REPLY_RX_count > 0)	//message reply is ready
	{
		buf_REPLY_RX_count = 0;
	}
	else if (buf_UART_RX_count > 0)	//UART data has been received
	{
		ptr = &buffer_UART_RX[0];
		buffer_UART_RX[IN_REPORT_DATALENGTH_INDEX] = buf_UART_RX_count - IN_REPORT_HEADER_LENGTH;
		buf_UART_RX_count = 0;
	}
	else if (buf_SPI_RX_count > 0)
	{
		ptr = &buffer_SPI_RX[0];
		buffer_SPI_RX[IN_REPORT_DATALENGTH_INDEX] = buf_SPI_RX_count - IN_REPORT_HEADER_LENGTH;
		buf_SPI_RX_count = 0;
	}
	else if (buf_I2C_RX_count > 0)	//TODO remove the I2C async reply part if this is not to be a slave
	{
		ptr = &buffer_I2C_RX[0];
		buffer_I2C_RX[IN_REPORT_DATALENGTH_INDEX] = buf_I2C_RX_count - IN_REPORT_HEADER_LENGTH;
		buf_I2C_RX_count = 0;
	}
	else
		return; //do not send an input report if there is no data to send

	pktLength = *(ptr + 4) + IN_REPORT_HEADER_LENGTH;

	// Send report
    unsigned char i;
    for(i = 0; i < (pktLength); i++)		//ptr[5] is the datalength field
	    Usb_write_byte(*(ptr + i));
    for(; i < EP_IN_LENGTH; i++)
    	Usb_write_byte(0);			//Pad the rest of the message with zeroes

    Usb_ack_in_ready();                       // Send data over the USB
}

void setReply(char section, char instruction, char dataLength, char flags, char* dataBytes)
{
	buf_REPLY_RX_count = 0;
	buffer_REPLY[IN_REPORT_SECTION_INDEX] = section;
	buffer_REPLY[IN_REPORT_INSTRUCTION_INDEX] = instruction;
	buffer_REPLY[IN_REPORT_FLAGS_L_INDEX] = flags;
	buffer_REPLY[IN_REPORT_FLAGS_H_INDEX] = 0x00;		//TODO make flags 16bit
	buffer_REPLY[IN_REPORT_DATALENGTH_INDEX] = dataLength;

	char i;
	for(i = 0; i < dataLength; i++)
		buffer_REPLY[i + IN_REPORT_HEADER_LENGTH] = dataBytes[i];

	buf_REPLY_RX_count = i;		//When this global is non-zero, a report will be sent to the host
}

//Use this method when data has already been written to the reply buffer (to save on RAM for long messages)
void setReplyInherentData(char section, char instruction, char dataLength, char flags)
{
	buf_REPLY_RX_count = 0;
	setReplyHeader(&buffer_REPLY[0], section, instruction, dataLength, flags, 0x00);
	buf_REPLY_RX_count = IN_REPORT_HEADER_LENGTH + dataLength;		//When this global is non-zero, a report will be sent to the host
}

void setReplyHeader(char* bufferPtr, char section, char instruction, char dataLength, char flagsL, char flagsH)
{
	bufferPtr[IN_REPORT_SECTION_INDEX] = section;
	bufferPtr[IN_REPORT_INSTRUCTION_INDEX] = instruction;
	bufferPtr[IN_REPORT_FLAGS_L_INDEX] = flagsL;
	bufferPtr[IN_REPORT_FLAGS_H_INDEX] = flagsH;
	bufferPtr[IN_REPORT_DATALENGTH_INDEX] = dataLength;
}
