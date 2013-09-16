#include "internal.h"
#include "opcodes.h"
#include "../IN_report.h"
#include "../usb_descriptors.h"
#include <stdlib.h>

extern char buffer_REPLY[BUF_SIZE_REPLY];

//internal section is 0x3A
void instrCall_internal(char instruction, char* datain, char dataLength)
{
  switch (instruction)
  {
  case INTERNAL_DEVICEINFO:
  {
	  getDeviceInfo();
	  break;
  }
  case INTERNAL_GET_STATUS:
  {
	  //not yet implmented
	  break;
  }
  case INTERNAL_MEM_WRITE:
  {
	  genericMemoryWrite(datain[0], datain[1], &datain[2]);
	  break;
  }
  case INTERNAL_MEM_READ:
  {
	  genericMemoryRead(datain[0], datain[1]);
	  break;
  }
  }
}

//Returns a struct of the device information:
//U8	device info version
//U8	device info table size
//U8	firmware version minor
//U8 	firmware version major (eg 2.106 or 1.00)
//U8	product ID
void getDeviceInfo(void)
{
	char i = 0;
	buffer_REPLY[IN_REPORT_HEADER_LENGTH + i++] = DEVICE_INFO_VERSION;
	buffer_REPLY[IN_REPORT_HEADER_LENGTH + i++] = DEVICE_INFO_TABLE_SIZE;
	buffer_REPLY[IN_REPORT_HEADER_LENGTH + i++] = FIRMWARE_VER_MINOR;
	buffer_REPLY[IN_REPORT_HEADER_LENGTH + i++] = FIRMWARE_VER_MAJOR;
	buffer_REPLY[IN_REPORT_HEADER_LENGTH + i++] = PRODUCT_NUMBER;
	//reply with data table
	setReplyInherentData(S_INTERNAL, INTERNAL_DEVICEINFO, DEVICE_INFO_TABLE_SIZE, 0x00);

}

void genericMemoryWrite(char addr, char dataLength, char* datain)
{
	char* ptr = addr;
	for(char i = 0; i < dataLength; i++)
		*ptr++ = datain[i];
}

void genericMemoryRead(char addr, char dataLength)
{
	char* ptr = addr;
	for(char i = 0; i < dataLength; i++)
		buffer_REPLY[IN_REPORT_HEADER_LENGTH + i] = *ptr++;

	setReplyInherentData(S_INTERNAL, INTERNAL_MEM_READ, dataLength, 0x00);
}
