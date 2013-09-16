################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../lib_mcu/flash/flash_drv.s 

OBJS += \
./lib_mcu/flash/flash_drv.o 

S_DEPS += \
./lib_mcu/flash/flash_drv.d 


# Each subdirectory must supply rules for building sources it contributes
lib_mcu/flash/%.o: ../lib_mcu/flash/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=at90usb162 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


