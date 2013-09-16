/*
 * IN_report.h
 *
 *  Created on: 13/04/2011
 *      Author: Admin
 */

#ifndef IN_REPORT_H_
#define IN_REPORT_H_

//Buffer sizes
#define BUF_SIZE_REPLY		64
#define BUF_SIZE_UART_RX	64
#define BUF_SIZE_SPI_RX		64
#define BUF_SIZE_I2C_RX		64
#define IN_REPORT_HEADER_LENGTH	5

//Message layout
#define IN_REPORT_SECTION_INDEX 	0
#define IN_REPORT_INSTRUCTION_INDEX 1
#define IN_REPORT_FLAGS_L_INDEX 	2
#define IN_REPORT_FLAGS_H_INDEX 	3
#define IN_REPORT_DATALENGTH_INDEX 	4


void setINreport(void);
void setReply(char section, char instruction, char dataLength, char flags, char* dataBytes);
void setReplyInherentData(char section, char instruction, char dataLength, char flags);
void setReplyHeader(char* bufferPtr, char section, char instruction, char flagsL, char flagsH, char dataLength);

#endif /* IN_REPORT_H_ */
