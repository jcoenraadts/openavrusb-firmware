#include "I2C.h"
#include "GPIO.h"
#include "opcodes.h"

char I2C_error = ERROR_I2C_NOERROR;
char I2C_flags = 0;
extern char buffer_REPLY[BUF_SIZE_REPLY];

// Standard I2C bit rates are:
// 100KHz for slow speed
// 400KHz for high speed

//#define QDEL	delay(5)		// i2c quarter-bit delay
//#define HDEL	delay(10)		// i2c half-bit delay

// i2c quarter-bit delay
#define QDEL	asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop");
// i2c half-bit delay
#define HDEL	QDEL asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop");
#define LDEL	HDEL asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop"); asm volatile("nop");

#define I2C_SDL_HI		DDRB &= 0xDF
#define I2C_SDL_LO		DDRB |= 0x20
#define I2C_SDL_READ	PINB & 0x20

#define I2C_SCL_HI      DDRB &= 0xBF
#define I2C_SCL_LO      DDRB |= 0x40
#define I2C_SCL_READ	PINB & 0x40

#define I2C_SCL_TOGGLE  HDEL; I2C_SCL_HI; LDEL; I2C_SCL_LO;
#define I2C_START       I2C_SDL_LO; HDEL; I2C_SCL_LO;
#define I2C_STOP        HDEL; I2C_SCL_HI; QDEL; I2C_SDL_HI; HDEL;


void instrCall_I2C(char instruction, char* datain, char datainLength)
{
  switch (instruction)
    {
    case I2C_WRITE:
      {
          I2C_error = I2C_write(datain[0], &datain[1]);
          break;
      }
    case I2C_READ:
      {
    	  I2C_read(datain[0], datain[1], &datain[2]);
          setReplyInherentData(S_I2C, I2C_READ, datain[1], 0x00);
          break;
      }
    case I2C_SETUP:
      {
          I2C_error = I2C_setup();
          break;
      }
    case I2C_SEND_START:
      {
    	  I2C_error = ERROR_I2C_NOERROR;
    	  I2C_SCL_LO; QDEL;
    	  I2C_SDL_HI; QDEL;
    	  I2C_SCL_HI; QDEL;	//ensure the lines are in the correct state before issuing the start

          I2C_START;
          break;
      }
    case I2C_SEND_STOP:
      {
    	  I2C_STOP;
          break;
      }
    case I2C_SEND_BYTES:
      {
    	  char ack = 0;
  		  // send the data
    	  char writeDataLength = datain[0];
    	  char* writeData = &datain[1];
    	  while (writeDataLength--)
    		  ack |= i2cPutbyte(*writeData++);

   		  I2C_SDL_LO;					// clear data line
   		  if (ack == 0)	//all bytes acked
   			  I2C_error =  ERROR_I2C_NOERROR;
   		  else
   			  I2C_error = ERROR_I2C_NOACK;
   		  break;
      }
    case I2C_READ_BYTES:
      {
    	  char readDataLength = datain[0];
    	  char j = readDataLength;
    	  while (j--)
    		  buffer_REPLY[IN_REPORT_HEADER_LENGTH + readDataLength - 1 - j] = i2cGetbyte(j == 0);

    	  I2C_SDL_HI;					// clear data line and
    	  setReplyInherentData(S_I2C, I2C_READ_BYTES, readDataLength, 0x00);
    	  break;
      }
    case I2C_CHECK_ERROR:
      {
          setReply(S_I2C, I2C_CHECK_ERROR, 1, 0x00, &I2C_error);
          I2C_error = ERROR_I2C_NOERROR;	//reset the error code
          break;
      }
    case I2C_BUS_SCAN:
      {
        I2C_busScan(datain[0], datain[1], datain[2]);
        break;
      }
    }

}

char I2C_setup(void)
{
	cbi( SDAPORT, SDA);			// set SDA low
	cbi( SCLPORT, SCL);			// set SCL low
	I2C_SDL_HI;					// set I/O state and pull-ups
	I2C_SCL_HI;					// set I/O state and pull-ups

	//check the states of the lines (they should be high)
	if (I2C_SCL_READ && I2C_SDL_READ)
		return ERROR_I2C_NOERROR;
	else
		return ERROR_I2C_SETUP_FAIL;
}

//Ensure that the number of addresses does not exceed the reply report length //NOT YET WORKING RIGHT
void I2C_busScan(char startAddr, char endAddr, char increment)
{
	char index = 0;
	for(int i = startAddr; i <= endAddr; i += increment)	//loops through available addresses
	{
		I2C_START;      			// do start transition
		buffer_REPLY[IN_REPORT_HEADER_LENGTH + index++] = i2cPutbyte(i);			// write address to bus, check for ACK
		I2C_SDL_LO;					// clear data line and
		I2C_STOP;					// send STOP transition
		HDEL; HDEL;
	}
	setReplyInherentData(S_I2C, I2C_BUS_SCAN, index, 0x00);
}

//Data input is
//[0] writeDatalength
//[1-n] write data (includes address)
char I2C_write(char writeDataLength, char* writeData)
{
	char ack = 0;	//this stores the values of the ACKs, if any byte is not acked, the error code will be set
	I2C_START;      			// do start transition

	// send the data
	while (writeDataLength--)
		ack |= i2cPutbyte(*writeData++);

	I2C_SDL_LO;					// clear data line and
	I2C_STOP;					// send STOP transition
	if (ack == 0)	//all bytes acked
		return ERROR_I2C_NOERROR;
	else
		return ERROR_I2C_NOACK;
}

char i2cPutbyte(char b)
{
	for (unsigned int i = 0x80; i & 0xFF; i = i >> 1)	//tests whether the 1 is still within the scope of a single byte
	{
		if ( b & i)
			I2C_SDL_HI;
		else
			I2C_SDL_LO;			// address bit
		I2C_SCL_TOGGLE;			// clock HI, delay, then LO
	}

	I2C_SDL_HI;					// leave SDL HI
	HDEL;
	I2C_SCL_HI;					// clock back up
  	b = I2C_SDL_READ;			// get the ACK bit

	HDEL; HDEL;
	I2C_SCL_LO;					// not really ??
	QDEL;
	return (b);					// return ACK value
}

char I2C_read(char writeDataLength, char readDataLength, char* writeData)
{
	char j = readDataLength;

	I2C_START;					// do start transition
	// send the data
	writeDataLength--;			//decrement this to begin with, as the last byte (second addr) will be sent after the repeated start
	while (writeDataLength--)
		i2cPutbyte(*writeData++);

	//repeated start
	HDEL;
	I2C_SDL_HI;					//prepare for the repeated start
	HDEL;
	I2C_SCL_HI;      			// do a repeated START
	I2C_START;
	i2cPutbyte(*writeData);		// Send the last byte in the write data array

	// receive data bytes
	while (j--)
		buffer_REPLY[IN_REPORT_HEADER_LENGTH + readDataLength - 1 - j] = i2cGetbyte(j == 0);

	I2C_SDL_LO;					// clear data line and
	I2C_STOP;					// send STOP transition
	return ERROR_I2C_NOERROR;
}

char i2cGetbyte(char last)
{
	char c,b = 0;

	I2C_SDL_HI;					// make sure pullups are activated

	for (unsigned int i = 0x80; i & 0xFF; i = i >> 1)	//tests whether the 1 is still within the scope of a single byte
	{	//clock low, HDEL, clock hi, QDEL, read pin, QDEL, repeat
		HDEL; QDEL; QDEL;
		I2C_SCL_HI;				// clock HI
		HDEL;
	  	c = I2C_SDL_READ;
		if(c)
			b |= i;				//if the read byte from PINB is non zero, add the bitmask
		HDEL;
    	I2C_SCL_LO;				// clock LO
	}

	if (last)
		I2C_SDL_HI;				// set NAK
	else
		I2C_SDL_LO;				// set ACK

	I2C_SCL_TOGGLE;				// clock pulse
	I2C_SDL_HI;					// leave with SDL HI
	return b;					// return received byte
}


