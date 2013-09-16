#include "eeprom.h"
#include "opcodes.h"
#include "../IN_report.h"
#include <stdlib.h>
#include <avr/eeprom.h>

extern char buffer_REPLY[BUF_SIZE_REPLY];

//EEPROM section is 0x31
void instrCall_EEPROM(char instruction, char* data, char dataLength)
{
  switch (instruction)
  {
  case EEPROM_WRITE:
    {
      eepromWrite(data, dataLength);       //only writes the first byte
      break;
    }
  case EEPROM_READ:
    {
      eepromRead(data);
      break;
    }
  }
}

//data: addr LSB, addr MSB, data to write
void eepromWrite(char* data, char dataLength)
{
	unsigned int address;
	address = (data[1] << 8) + data[0];
	eeprom_write_block((const void*)&data[2], (void*)address, dataLength - 2);
}

//data: address LSB, address MSB, numBytes
void eepromRead(char* data)
{
	unsigned char numBytes = data[2];
	unsigned int address;
	address = (data[1] << 8) + data[0];

	//use inherent data method - eeprom read function writes directly to the reply buffer
	eeprom_read_block((void*)(&buffer_REPLY[IN_REPORT_HEADER_LENGTH]), (const void*)address, numBytes);
	//setReply(S_EEPROM, EEPROM_READ, numBytes, 0x00, outData);
	setReplyInherentData(S_EEPROM, EEPROM_READ, numBytes, 0x00);
}


