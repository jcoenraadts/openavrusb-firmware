/*
 * internal.h
 *
 *  Created on: 30/08/2011
 *      Author: Administrator
 */

#ifndef INTERNAL_H_
#define INTERNAL_H_

#define INTERNAL_DEVICEINFO		0x20
#define INTERNAL_GET_STATUS		0x21
#define INTERNAL_MEM_WRITE		0x22
#define INTERNAL_MEM_READ		0x23

#define DEVICE_INFO_VERSION		1	//increment if this struct changes
#define DEVICE_INFO_TABLE_SIZE	5	//bytes
#define FIRMWARE_VER_MINOR		0	//U8
#define FIRMWARE_VER_MAJOR		1	//U8
#define PRODUCT_NUMBER			1	//U8 0=IFB100, 1=IFBmini

void instrCall_internal(char instruction, char* data, char dataLength);
void getDeviceInfo(void);
void genericMemoryWrite(char addr, char dataLength, char* datain);
void genericMemoryRead(char addr, char dataLength);

#endif /* INTERNAL_H_ */
