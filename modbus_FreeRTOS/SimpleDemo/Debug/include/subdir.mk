################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/mbfuncholding.c 

OBJS += \
./include/mbfuncholding.o 

C_DEPS += \
./include/mbfuncholding.d 


# Each subdirectory must supply rules for building sources it contributes
include/%.o: ../include/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\SimpleDemo" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\SimpleDemo\include" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\CMSISv1p30_LPC17xx\inc" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\FreeRTOS_Library\include" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


