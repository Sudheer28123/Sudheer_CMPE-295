################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Modbus_project.axf

# Tool invocations
Modbus_project.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\veena\Documents\LPCXpresso_8.1.2_603\workspace\CMSIS_CORE_LPC17xx\Debug" -Xlinker -Map="Modbus_project.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Hello_world_Debug.ld" -o "Modbus_project.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Modbus_project.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Modbus_project.axf"; # arm-none-eabi-objcopy -v -O binary "Modbus_project.axf" "Modbus_project.bin" ; # checksum -p LPC1769 -d "Modbus_project.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
