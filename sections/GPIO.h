#ifndef GPIO_H_
#define GPIO_H_

//Port masks
#define MASK_PORTB 0xFF         //all pins available
#define MASK_PORTC 0xFC			//PC1 is reset, PC0 is clock (XTALx)
#define MASK_PORTD 0xFF

//Instructions
#define PORT_WRITE 0x10
#define PORT_READ 0x11
#define SET_DIR 0x12

char readIOPort(char port);
void instrCall_GPIO(char instruction, char* data, char dataLength);
void setIODirection(char port, char direction, char mask);
void writeIOPort(char port, char value, char mask);
void toggleLED(void);

#endif /* GPIO_H_ */
