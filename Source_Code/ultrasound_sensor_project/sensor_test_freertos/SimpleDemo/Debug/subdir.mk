################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cr_startup_lpc17.c \
../main.c \
../ultsensor.c 

OBJS += \
./cr_startup_lpc17.o \
./main.o \
./ultsensor.o 

C_DEPS += \
./cr_startup_lpc17.d \
./main.d \
./ultsensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\SimpleDemo" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\CMSISv1p30_LPC17xx\inc" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\FreeRTOS_Library\include" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


