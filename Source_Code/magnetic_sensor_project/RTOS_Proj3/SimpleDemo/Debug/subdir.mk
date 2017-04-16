################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sensors.c \
../cr_startup_lpc17.c \
../main.c 

OBJS += \
./Sensors.o \
./cr_startup_lpc17.o \
./main.o 

C_DEPS += \
./Sensors.d \
./cr_startup_lpc17.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"/Users/sudheerdoddapaneni/Documents/Sudheer/Sem4/Project/LPCXpresso/RTOS_Proj3/SimpleDemo" -I"/Users/sudheerdoddapaneni/Documents/Sudheer/Sem4/Project/LPCXpresso/RTOS_Proj3/CMSISv1p30_LPC17xx/inc" -I"/Users/sudheerdoddapaneni/Documents/Sudheer/Sem4/Project/LPCXpresso/RTOS_Proj3/FreeRTOS_Library/include" -I"/Users/sudheerdoddapaneni/Documents/Sudheer/Sem4/Project/LPCXpresso/RTOS_Proj3/FreeRTOS_Library/portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


