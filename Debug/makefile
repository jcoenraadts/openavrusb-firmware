################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include sections/subdir.mk
-include modules/usb/subdir.mk
-include modules/usb/device_chap9/subdir.mk
-include modules/scheduler/subdir.mk
-include lib_mcu/wdt/subdir.mk
-include lib_mcu/util/subdir.mk
-include lib_mcu/usb/subdir.mk
-include lib_mcu/power/subdir.mk
-include lib_mcu/flash/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
USB_demo.lss \

FLASH_IMAGE += \
USB_demo.hex \

EEPROM_IMAGE += \
USB_demo.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: USB_demo.elf secondary-outputs

# Tool invocations
USB_demo.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,USB_demo.map -mmcu=at90usb162 -o"USB_demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

USB_demo.lss: USB_demo.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S USB_demo.elf  >"USB_demo.lss"
	@echo 'Finished building: $@'
	@echo ' '

USB_demo.hex: USB_demo.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex USB_demo.elf  "USB_demo.hex"
	@echo 'Finished building: $@'
	@echo ' '

USB_demo.eep: USB_demo.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex USB_demo.elf  "USB_demo.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: USB_demo.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=at90usb162 USB_demo.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) USB_demo.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
