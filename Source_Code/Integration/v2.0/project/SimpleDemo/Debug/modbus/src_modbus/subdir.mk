################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/src_modbus/cr_startup_lpc175x_6x.c \
../modbus/src_modbus/crp.c \
../modbus/src_modbus/mb.c \
../modbus/src_modbus/mbcrc.c \
../modbus/src_modbus/mbfunccoils.c \
../modbus/src_modbus/mbfuncdisc.c \
../modbus/src_modbus/mbfuncholding.c \
../modbus/src_modbus/mbfuncinput.c \
../modbus/src_modbus/mbfuncother.c \
../modbus/src_modbus/mbrtu.c \
../modbus/src_modbus/mbutils.c \
../modbus/src_modbus/modbus.c \
../modbus/src_modbus/portevent.c \
../modbus/src_modbus/portserial.c \
../modbus/src_modbus/porttimer.c 

OBJS += \
./modbus/src_modbus/cr_startup_lpc175x_6x.o \
./modbus/src_modbus/crp.o \
./modbus/src_modbus/mb.o \
./modbus/src_modbus/mbcrc.o \
./modbus/src_modbus/mbfunccoils.o \
./modbus/src_modbus/mbfuncdisc.o \
./modbus/src_modbus/mbfuncholding.o \
./modbus/src_modbus/mbfuncinput.o \
./modbus/src_modbus/mbfuncother.o \
./modbus/src_modbus/mbrtu.o \
./modbus/src_modbus/mbutils.o \
./modbus/src_modbus/modbus.o \
./modbus/src_modbus/portevent.o \
./modbus/src_modbus/portserial.o \
./modbus/src_modbus/porttimer.o 

C_DEPS += \
./modbus/src_modbus/cr_startup_lpc175x_6x.d \
./modbus/src_modbus/crp.d \
./modbus/src_modbus/mb.d \
./modbus/src_modbus/mbcrc.d \
./modbus/src_modbus/mbfunccoils.d \
./modbus/src_modbus/mbfuncdisc.d \
./modbus/src_modbus/mbfuncholding.d \
./modbus/src_modbus/mbfuncinput.d \
./modbus/src_modbus/mbfuncother.d \
./modbus/src_modbus/mbrtu.d \
./modbus/src_modbus/mbutils.d \
./modbus/src_modbus/modbus.d \
./modbus/src_modbus/portevent.d \
./modbus/src_modbus/portserial.d \
./modbus/src_modbus/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/src_modbus/%.o: ../modbus/src_modbus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\CMSISv1p30_LPC17xx\inc" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\SimpleDemo\modbus\inc_modbus" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\SimpleDemo\modbus\src_modbus" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\SimpleDemo" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\FreeRTOS_Library\include" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


