/*
 * I2C.h
 *
 *  Created on: 6/06/2011
 *      Author: Admin
 */

#ifndef I2C_H_
#define I2C_H_

#include "avr\io.h"
#include <avr/interrupt.h>
#include "opcodes.h"
#include "../IN_report.h"
#include "../usb_descriptors.h"
#include "GPIO.h"

#define cbi(reg,bit)	reg &= ~(BV(bit))
#define sbi(reg,bit)	reg |= (BV(bit))
#define BV(bit)			(1<<(bit))
#define	inb(addr)			(addr)

#define I2C_WRITE 0x10
#define I2C_READ 0x11
#define I2C_SETUP 0x12
#define I2C_SEND_START 0x13
#define I2C_SEND_STOP 0x14
#define I2C_SEND_BYTES 0x15
#define I2C_READ_BYTES 0x16
#define I2C_CHECK_ERROR 0x17
#define I2C_ASYNC_REPLY 0x18
#define I2C_BUS_SCAN	0x19

#define ERROR_I2C_NOERROR 	0
#define ERROR_I2C_NOACK		1
#define ERROR_I2C_LOST_ARB 	2
#define ERROR_I2C_SETUP_FAIL 3	//both lines could not be released

#define I2C_FLAG_REQUIRE_ACK 0x01
#define I2C_FLAG_PUT_ACK 0x02

#define READ		0x01	// I2C READ bit
// clock line port
#define SCLPORT	PORTB	// i2c clock port
#define SCLDDR	DDRB	// i2c clock port direction
// data line port
#define SDAPORT	PORTB	// i2c data port
#define SDADDR	DDRB	// i2c data port direction
#define SDAPIN	PINB	// i2c data port input
// pin assignments
#define SCL		PB6		// i2c clock pin
#define SDA		PB5		// i2c data pin


void instrCall_I2C(char instruction, char* datain, char datainLength);
char I2C_setup(void);
void I2C_busScan(char startAddr, char endAddr, char increment);
char I2C_read(char writeDataLength, char readDataLength, char* writeData);
char I2C_write(char writeDataLength, char* writeData);
char i2cPutbyte(char b);
char i2cGetbyte(char last);
char I2C_sendBytes(char* datain);
char I2C_writeByte(char byte);
void I2C_readBytes(char dataLength);
char I2C_readByte(void);
char I2C_start(void);
char I2C_stop(void);
void I2C_delay(char numDelays);
void I2C_setSCL(void);
void I2C_releaseSCL(void);
void I2C_setSDA(void);
void I2C_releaseSDA(void);
char I2C_readSCL(void);
char I2C_readSDA(void);

#endif /* I2C_H_ */
