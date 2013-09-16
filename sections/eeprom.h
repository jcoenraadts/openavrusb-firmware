#ifndef EEPROM_H_
#define EEPROM_H_

//EEPROM IFB instruction set
#define EEPROM_WRITE 0x10
#define EEPROM_READ 0x11

void instrCall_EEPROM(char instruction, char* data, char dataLength);
void eepromWrite(char* data, char dataLength);
void eepromRead(char* data);

#endif /* EEPROM_H_ */
