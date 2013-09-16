#include "GPIO.h"
#include <avr/io.h>
#include "opcodes.h"
#include "../IN_report.h"
#include "UART.h"
#include "stdlib.h"

//GPIO section is 0x15
void instrCall_GPIO(char instruction, char* datain, char dataLength)
{
  switch (instruction)
  {
  case PORT_WRITE:
    {
      writeIOPort(datain[0], datain[1], datain[2]);
      break;
    }
  case PORT_READ:
    {
      char reply = readIOPort(datain[0]);
      setReply(S_GPIO, PORT_READ, 1, 0, &reply);
      break;
    }
  case SET_DIR:
    {
      setIODirection(datain[0], datain[1], datain[2]);
      break;
    }
  }
}

char readIOPort(char port)
{
  switch (port)
  {
  case 'B':
    {
      return PINB;
    }
  case 'C':
    {
      return PINC;
    }
  case 'D':
    {
      return PIND;
    }
   }
  //default
  return 0;
}

//sets the direction of a specific port, according to the mask (1=change, 0=ignore)
void setIODirection(char port, char direction, char mask)
{
  switch (port)
  {
  case 'B':
    {
      mask &= MASK_PORTB;
      DDRB = (~mask & DDRB) | (mask & direction);
      break;
   }
  case 'C':
    {
      mask &= MASK_PORTC;
      DDRC = (~mask & DDRC) | (mask & direction);
      break;
    }
  case 'D':
    {
      mask &= MASK_PORTD;
      DDRD = (~mask & DDRD) | (mask & direction);
      break;
    }
  }
}

//sets the state of a specific port, according to the mask (1=change, 0=ignore)
void writeIOPort(char port, char value, char mask)
{

  switch (port)
  {
  case 'B':
    {
      mask &= MASK_PORTB;
      PORTB = (~mask & PORTB) | (mask & value);
      break;
   }
  case 'C':
    {
      mask &= MASK_PORTC;
      PORTC = (~mask & PORTC) | (mask & value);
      break;
    }
  case 'D':
    {
      mask &= MASK_PORTD;
      PORTD = (~mask & PORTD) | (mask & value);
      break;
    }
  }
}

void toggleLED(void)
{
	if (PORTC & 0x10)
		PORTC &= 0xEF;
	else
		PORTC |= 0x10;
}
