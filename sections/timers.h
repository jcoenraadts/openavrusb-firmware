#ifndef TIMERS_H_
#define TIMERS_H_

//instructions
#define TIMER_SET_CTRL_REG      0x10
#define TIMER_SET_MASK_FLAGS    0x11
#define TIMER_SET_OCRS          0x12
#define TIMER_SET_TCNT          0x13
#define TIMER_SERVO_SWEEP		0x14
#define TIMER_SET_ALL			0x15

//timer IDs
#define TIMERA 0x01
#define TIMERB 0x03
#define TIMERC 0x04
#define TIMERD 0x05

//register offsets
#define TCCRA 0x00
#define TCCRB 0x01
#define TCCRC 0x02
#define TCNTL 0x04
#define TCNTH 0x05
#define ICRL  0x06
#define ICRH  0x07
#define OCRAL 0x08
#define OCRAH 0x09
#define OCRBL 0x0A
#define OCRBH 0x0B
#define OCRCL 0x0C
#define OCRCH 0x0D

#define TIMER1_OFFSET   0x80

char* getTimerRegBase(char timerID);
void instrCall_Timer(char instruction, char* data, char dataLength);
void timerSetCtrlRegs(char* data);
void setTCNT(char* data);
void timerSetOCRs(char* data);
void timerSetMaskAndFlags(char* data);
void timerSetAllRegs(char* data);
void timerServoSweep(char* data);

#endif /* TIMERS_H_ */
