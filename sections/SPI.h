
#ifndef SPI_H_
#define SPI_H_

#include "avr\io.h"
#include <avr/interrupt.h>
#include "opcodes.h"
#include "../IN_report.h"
#include "../usb_descriptors.h"
#include "GPIO.h"

#define SPI_TRANSACTION    0x10
#define SPI_SLAVE_REPLY    0x11
#define SPI_SET_CTRL_REG   0x12

void instrCall_SPI(char instruction, char* data, char dataLength);

void SPI_setCtrlRegisters(char* data);
void SPI_TransactionExt(char* data, char dataLength);
char SPI_byteTransactionExt(char byte);

#endif /* SPI_H_ */
