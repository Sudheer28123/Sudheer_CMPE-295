################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/mb.c \
../src/mbcrc.c \
../src/mbfunccoils.c \
../src/mbfuncdisc.c \
../src/mbfuncinput.c \
../src/mbfuncother.c \
../src/mbrtu.c \
../src/mbutils.c \
../src/modbus.c \
../src/portevent.c \
../src/portserial.c \
../src/porttimer.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/mb.o \
./src/mbcrc.o \
./src/mbfunccoils.o \
./src/mbfuncdisc.o \
./src/mbfuncinput.o \
./src/mbfuncother.o \
./src/mbrtu.o \
./src/mbutils.o \
./src/modbus.o \
./src/portevent.o \
./src/portserial.o \
./src/porttimer.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/mb.d \
./src/mbcrc.d \
./src/mbfunccoils.d \
./src/mbfuncdisc.d \
./src/mbfuncinput.d \
./src/mbfuncother.d \
./src/mbrtu.d \
./src/mbutils.d \
./src/modbus.d \
./src/portevent.d \
./src/portserial.d \
./src/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\CMSISv1p30_LPC17xx\inc" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\SimpleDemo\include" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\SimpleDemo\src" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\SimpleDemo" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\FreeRTOS_Library\include" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\FreeRTOS_workfolder\SourceCode\FreeRTOS_workspac\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


