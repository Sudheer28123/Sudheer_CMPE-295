################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/main.c \
../src/mbcrc.c \
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
./src/mbcrc.o \
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
./src/mbcrc.d \
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
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\SimpleDemo" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\SimpleDemo\include" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\CMSISv1p30_LPC17xx\inc" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\FreeRTOS_Library\include" -I"C:\Users\veena\Documents\LPCXpresso_8.1.0_597\workspace\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


