################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib_mcu/wdt/wdt_drv.c 

OBJS += \
./lib_mcu/wdt/wdt_drv.o 

C_DEPS += \
./lib_mcu/wdt/wdt_drv.d 


# Each subdirectory must supply rules for building sources it contributes
lib_mcu/wdt/%.o: ../lib_mcu/wdt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=at90usb162 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


