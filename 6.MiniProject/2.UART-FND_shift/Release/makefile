################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
UART-FND_shift.lss \

FLASH_IMAGE += \
UART-FND_shift.hex \

EEPROM_IMAGE += \
UART-FND_shift.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: UART-FND_shift.elf secondary-outputs

# Tool invocations
UART-FND_shift.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,UART-FND_shift.map -mmcu=atmega128 -o "UART-FND_shift.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

UART-FND_shift.lss: UART-FND_shift.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S UART-FND_shift.elf  >"UART-FND_shift.lss"
	@echo 'Finished building: $@'
	@echo ' '

UART-FND_shift.hex: UART-FND_shift.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex UART-FND_shift.elf  "UART-FND_shift.hex"
	@echo 'Finished building: $@'
	@echo ' '

UART-FND_shift.eep: UART-FND_shift.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex UART-FND_shift.elf  "UART-FND_shift.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: UART-FND_shift.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 UART-FND_shift.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) UART-FND_shift.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
