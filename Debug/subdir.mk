################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IN_report.c \
../hid_task.c \
../main.c \
../usb_descriptors.c \
../usb_specific_request.c 

OBJS += \
./IN_report.o \
./hid_task.o \
./main.o \
./usb_descriptors.o \
./usb_specific_request.o 

C_DEPS += \
./IN_report.d \
./hid_task.d \
./main.d \
./usb_descriptors.d \
./usb_specific_request.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=at90usb162 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


