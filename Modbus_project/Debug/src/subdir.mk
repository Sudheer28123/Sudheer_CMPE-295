################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/main.c \
../src/mb.c \
../src/mbcrc.c \
../src/mbfunccoils.c \
../src/mbfuncdisc.c \
../src/mbfuncholding.c \
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
./src/main.o \
./src/mb.o \
./src/mbcrc.o \
./src/mbfunccoils.o \
./src/mbfuncdisc.o \
./src/mbfuncholding.o \
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
./src/main.d \
./src/mb.d \
./src/mbcrc.d \
./src/mbfunccoils.d \
./src/mbfuncdisc.d \
./src/mbfuncholding.d \
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
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\veena\Documents\LPCXpresso_8.1.2_603\workspace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\Modbus_project\include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


