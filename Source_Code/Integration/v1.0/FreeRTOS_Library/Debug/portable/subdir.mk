################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../portable/heap_2.c \
../portable/port.c 

OBJS += \
./portable/heap_2.o \
./portable/port.o 

C_DEPS += \
./portable/heap_2.d \
./portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
portable/%.o: ../portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\FreeRTOS_Library\include" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\CMSISv1p30_LPC17xx\inc" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\FreeRTOS_Library\portable" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\FreeRTOS-Demo-and-Docs-for-the-LPCXpresso-LPC1768\SourceCode\FreeRTOS-simple-demo-for-LPCXpresso\SimpleDemo" -O1 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


