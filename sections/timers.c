#include "avr\io.h"
#include "avr\interrupt.h"
#include "timers.h"
#include "GPIO.h"
//#include "..\lib_mcu\compiler.h"

//Timer section is 0x1B
//Messages for this section: data = timerID, data
void instrCall_Timer(char instruction, char* data, char dataLength)
{
  switch (instruction)
  {
  case TIMER_SET_CTRL_REG:
    {
      timerSetCtrlRegs(data);
      break;
    }
  case TIMER_SET_TCNT:
    {
      setTCNT(data);
      break;
    }
  case TIMER_SET_OCRS:
    {
      timerSetOCRs(data);
      break;
    }
  case TIMER_SET_MASK_FLAGS:
    {
      timerSetMaskAndFlags(data);
      break;
    }
  case TIMER_SET_ALL:
  {
	  timerSetAllRegs(data);
	  break;
  }
  case TIMER_SERVO_SWEEP:
    {
      timerServoSweep(data);
      break;
    }
  }
}

//data: timerID, TCCRA, TCCRB, TCCRC
void timerSetCtrlRegs(char* data)
{
  char* timerReg = getTimerRegBase(data[0]);

  timerReg += TCCRA;
  *timerReg = data[1];  //TCCRA
  timerReg++;
  *timerReg = data[2];  //TCCRB
  timerReg++;
  *timerReg = data[3];  //TCCRC
}

//data: timerID, TCNTL, TCNTH
void setTCNT(char* data)
{
  char* timerReg = getTimerRegBase(data[0]);
  timerReg += (TCNTH);
  *timerReg = data[1];
  timerReg--;
  *timerReg = data[2];
}

//data: timerID, OCRAL, OCRAH, OCRBL, OCRBH, OCRCL, OCRCH
//these 16bit registers must be written high byte first
void timerSetOCRs(char* data)
{
  char* timerReg = getTimerRegBase(data[0]);

  timerReg += (OCRCH);
  *timerReg = data[6];  //OCRCH
  timerReg--;
  *timerReg = data[5];  //OCRCL
  timerReg--;
  *timerReg = data[4];  //OCRBH
  timerReg--;
  *timerReg = data[3];  //OCRBL
  timerReg--;
  *timerReg = data[2];  //OCRAH
  timerReg--;
  *timerReg = data[1];  //OCRAL
}

//data: timerID, TIMSK, TIFR
//flags and masks are not in the same location as the other timer registers
//the mask is from 0x6E, and the flags are from 0x15 (timer0->timer5)
void timerSetMaskAndFlags(char* data)
{
  char* timerReg = (char*)(TIMSK0 + data[0]);    //the timer number is also the offset from timer0 registers
  *timerReg = data[1];                  //mask

  timerReg = (char*)(TIFR0 + data[0]);
  *timerReg = data[2];                  //flags
}

//Returns a pointer to the base of the register set for each timer in the uP
//Each timer has the same register set which can be indexed from the base
//in the USB162, there is only one 16bit timer
char* getTimerRegBase(char timerID)
{
  return (char*)TIMER1_OFFSET;
}

// message: byte timer #, byte TIMSK, byte TIFR, byte TCCRA, byte TCCRB, byte TCCRC, UInt16 OCRA, UInt16 OCRB, UInt16 OCRC
void timerSetAllRegs(char* data)
{
	timerSetMaskAndFlags(data);	//set flags with first three bytes
	data[2] = data[0];				//set timer number
	timerSetCtrlRegs(&data[2]);
	data[5] = data[0];
	timerSetOCRs(&data[5]);
}

unsigned int timerServoSweepEnd = 0;
unsigned char timerServoSweepincrement = 0;
void timerServoSweep(char* data)			//before this method is called the servo mode must be running
{
	//(((U8* )&wInterface)[0])
	(((char*)&timerServoSweepEnd)[0]) = data[1];
	(((char*)&timerServoSweepEnd)[1]) = data[0];
	timerServoSweepincrement = data[2];
	TIMSK1 = 0x04;
}

//The ISR is used in the PWM sweep function to adjust the compare value
ISR(TIMER1_COMPB_vect)
{
	if (timerServoSweepEnd == OCR1B)	//the sweep is over, stop firing this ISR
	{
		TIMSK1 &= 0xFB;					//mask ISR for OCB
		return;
	}

	if (timerServoSweepEnd > OCR1B)
		OCR1B -= timerServoSweepincrement;
	else
		OCR1B += timerServoSweepincrement;
}


