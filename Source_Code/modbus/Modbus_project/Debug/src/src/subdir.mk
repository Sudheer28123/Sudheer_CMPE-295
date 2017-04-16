################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/src/cr_startup_lpc175x_6x.c \
../src/src/crp.c \
../src/src/main.c \
../src/src/mbcrc.c \
../src/src/mbfunccoils.c \
../src/src/mbfuncdisc.c \
../src/src/mbfuncholding.c \
../src/src/mbfuncinput.c \
../src/src/mbfuncother.c \
../src/src/mbrtu.c \
../src/src/mbutils.c \
../src/src/modbus.c \
../src/src/portevent.c \
../src/src/portserial.c \
../src/src/porttimer.c 

OBJS += \
./src/src/cr_startup_lpc175x_6x.o \
./src/src/crp.o \
./src/src/main.o \
./src/src/mbcrc.o \
./src/src/mbfunccoils.o \
./src/src/mbfuncdisc.o \
./src/src/mbfuncholding.o \
./src/src/mbfuncinput.o \
./src/src/mbfuncother.o \
./src/src/mbrtu.o \
./src/src/mbutils.o \
./src/src/modbus.o \
./src/src/portevent.o \
./src/src/portserial.o \
./src/src/porttimer.o 

C_DEPS += \
./src/src/cr_startup_lpc175x_6x.d \
./src/src/crp.d \
./src/src/main.d \
./src/src/mbcrc.d \
./src/src/mbfunccoils.d \
./src/src/mbfuncdisc.d \
./src/src/mbfuncholding.d \
./src/src/mbfuncinput.d \
./src/src/mbfuncother.d \
./src/src/mbrtu.d \
./src/src/mbutils.d \
./src/src/modbus.d \
./src/src/portevent.d \
./src/src/portserial.d \
./src/src/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/src/%.o: ../src/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\veena\Documents\LPCXpresso_8.1.2_603\workspace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\LPC1769_GPIO\include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


