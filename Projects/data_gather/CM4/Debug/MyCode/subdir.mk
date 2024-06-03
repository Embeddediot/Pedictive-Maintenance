################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MyCode/iis3dwb.cpp \
../MyCode/stts22h.cpp 

OBJS += \
./MyCode/iis3dwb.o \
./MyCode/stts22h.o 

CPP_DEPS += \
./MyCode/iis3dwb.d \
./MyCode/stts22h.d 


# Each subdirectory must supply rules for building sources it contributes
MyCode/%.o MyCode/%.su MyCode/%.cyclo: ../MyCode/%.cpp MyCode/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_NUCLEO_64 -c -I../Core/Inc -I.../MyCode -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyCode

clean-MyCode:
	-$(RM) ./MyCode/iis3dwb.cyclo ./MyCode/iis3dwb.d ./MyCode/iis3dwb.o ./MyCode/iis3dwb.su ./MyCode/stts22h.cyclo ./MyCode/stts22h.d ./MyCode/stts22h.o ./MyCode/stts22h.su

.PHONY: clean-MyCode

