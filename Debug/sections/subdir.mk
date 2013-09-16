################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sections/GPIO.c \
../sections/I2C.c \
../sections/SPI.c \
../sections/UART.c \
../sections/eeprom.c \
../sections/hd44780.c \
../sections/init.c \
../sections/internal.c \
../sections/lcd.c \
../sections/sections.c \
../sections/timers.c 

OBJS += \
./sections/GPIO.o \
./sections/I2C.o \
./sections/SPI.o \
./sections/UART.o \
./sections/eeprom.o \
./sections/hd44780.o \
./sections/init.o \
./sections/internal.o \
./sections/lcd.o \
./sections/sections.o \
./sections/timers.o 

C_DEPS += \
./sections/GPIO.d \
./sections/I2C.d \
./sections/SPI.d \
./sections/UART.d \
./sections/eeprom.d \
./sections/hd44780.d \
./sections/init.d \
./sections/internal.d \
./sections/lcd.d \
./sections/sections.d \
./sections/timers.d 


# Each subdirectory must supply rules for building sources it contributes
sections/%.o: ../sections/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=at90usb162 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


