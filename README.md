openavrusb-firmware
===================

openAvrUsb is an open source USB HID interface software project designed to run on Atmel AVR hardware. It includes all source code for simple and reliable communications over USB to embedded devices. For more information on the HID device class, see the hid-sharp project on Github (check the wiki!).

This project was born out of the Helion Microsystems HU320 USB interface products. It was found, due to customer feedback, that the real power of these products could only be unleashed by allowing user customisation. While they provided a number of useful interfaces, another processor was often required to do grunt-work at the PCB level. With the software released as open-source, user functions can be added with the utmost of ease.

## Environment
The firmware for this project is developed in C, and compiled under GCC/winAVR

## Architecture
The USB stack is based on an Atmel AVR application note, with extensions to expose other standard microcontroller functions. Input and output HID reports are configured at 64 bytes (max for HID) by default. Each out report (to the microcontroller) includes a firmware section ID, an instruction code and the relevant data packet if required.

When using the default structure,a fixed 8-byte packet header is used. This header specifies the firmware section (HD44780 LCD interface, SPI port, I2C, timers/PWM etc), the instruction (read/write, start/stop etc) and the relevant data packet.

## Functionality
The firmware supports the following functions without modification. Most options available in firmware for each of the hardware peripherals are catered for. All of these functions are also fully supported in the .NET PC software, with most functions simply requiring two lines of code to implement.

* 16bit timer setup - PWM, one shot, pulse counting
* UART setup and data transfer
* Software I2C port setup and data transfer
* SPI port setup and data transfer (master/slave operation)
* HD44780 LCD interface
* General digital IO - set direction and pullups, read/write pins

## User Functions
A simple switch statement is used to determine the section/instruction to execute, so adding user functions is as simple as writing said functions, and adding a case to the switch statement with a unique section/instruction.
