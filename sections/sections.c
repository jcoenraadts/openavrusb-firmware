#include "sections.h"
#include "opcodes.h"
#include "GPIO.h"
#include "UART.h"
#include "eeprom.h"
#include "SPI.h"
#include "I2C.h"
#include "lcd.h"
#include "timers.h"
#include "internal.h"
#include "..\IN_report.h"

void sectionCall(char section, char instruction, char* datain, char datainLength)
{
  switch (section)
  {
  case (S_EEPROM):
    {
    instrCall_EEPROM(instruction, datain, datainLength);
    break;
    }
  case (S_INTERNAL):
    {
    instrCall_internal(instruction, datain, datainLength);
    break;
    }
  case (S_GPIO):
    {
    instrCall_GPIO(instruction, datain, datainLength);
    break;
    }
  case (S_LED):
    {
    //instrCall_LED(instruction, datain, datainLength);
    break;
    }
  case (S_TIMER):
    {
    instrCall_Timer(instruction, datain, datainLength);
    break;
    }
  case (S_SPI):
    {
    instrCall_SPI(instruction, datain, datainLength);
    break;
    }
  case (S_I2C):
    {
    instrCall_I2C(instruction, datain, datainLength);
    break;
    }
  case (S_UART):
    {
    instrCall_UART(instruction, datain, datainLength);
    break;
    }
  case (S_LCD):
	{
	instrCall_LCD(instruction, datain, datainLength);
	break;
	}
  default:
    {
    }
  }
}
