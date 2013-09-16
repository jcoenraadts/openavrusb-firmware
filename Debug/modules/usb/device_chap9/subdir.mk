################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/usb/device_chap9/usb_device_task.c \
../modules/usb/device_chap9/usb_standard_request.c 

OBJS += \
./modules/usb/device_chap9/usb_device_task.o \
./modules/usb/device_chap9/usb_standard_request.o 

C_DEPS += \
./modules/usb/device_chap9/usb_device_task.d \
./modules/usb/device_chap9/usb_standard_request.d 


# Each subdirectory must supply rules for building sources it contributes
modules/usb/device_chap9/%.o: ../modules/usb/device_chap9/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=at90usb162 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


