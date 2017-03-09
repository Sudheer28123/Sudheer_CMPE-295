################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc175x_6x.cpp \
../src/sensor_test.cpp 

C_SRCS += \
../src/crp.c 

OBJS += \
./src/cr_cpp_config.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/sensor_test.o 

C_DEPS += \
./src/crp.d 

CPP_DEPS += \
./src/cr_cpp_config.d \
./src/cr_startup_lpc175x_6x.d \
./src/sensor_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\sujee\Documents\LPCXpresso_7.9.2_493\workspace\sensor_test\inc" -I"C:\Users\sujee\Desktop\ARC\SJSU_Coursework\Spring_2017\295B\SimpleDemo\SimpleDemo\include" -I"C:\Users\sujee\Documents\LPCXpresso_7.9.2_493\workspace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\sujee\Documents\LPCXpresso_7.9.2_493\workspace\CMSIS_DSPLIB_CM3\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -DCPP_USE_HEAP -D__LPC17XX__ -D__NEWLIB__ -I"C:\Users\sujee\Documents\LPCXpresso_7.9.2_493\workspace\sensor_test\inc" -I"C:\Users\sujee\Documents\LPCXpresso_7.9.2_493\workspace\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\sujee\Documents\LPCXpresso_7.9.2_493\workspace\CMSIS_DSPLIB_CM3\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


