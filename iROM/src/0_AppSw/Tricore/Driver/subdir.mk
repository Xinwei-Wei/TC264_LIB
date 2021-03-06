################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/0_AppSw/Tricore/Driver/LQ_ADC.c \
../src/0_AppSw/Tricore/Driver/LQ_DMA.c \
../src/0_AppSw/Tricore/Driver/LQ_EEPROM.c \
../src/0_AppSw/Tricore/Driver/LQ_FFT.c \
../src/0_AppSw/Tricore/Driver/LQ_GPIO.c \
../src/0_AppSw/Tricore/Driver/LQ_GPT12_ENC.c \
../src/0_AppSw/Tricore/Driver/LQ_GTM.c \
../src/0_AppSw/Tricore/Driver/LQ_SOFTI2C.c \
../src/0_AppSw/Tricore/Driver/LQ_SPI.c \
../src/0_AppSw/Tricore/Driver/LQ_STM.c \
../src/0_AppSw/Tricore/Driver/LQ_UART.c 

OBJS += \
./src/0_AppSw/Tricore/Driver/LQ_ADC.o \
./src/0_AppSw/Tricore/Driver/LQ_DMA.o \
./src/0_AppSw/Tricore/Driver/LQ_EEPROM.o \
./src/0_AppSw/Tricore/Driver/LQ_FFT.o \
./src/0_AppSw/Tricore/Driver/LQ_GPIO.o \
./src/0_AppSw/Tricore/Driver/LQ_GPT12_ENC.o \
./src/0_AppSw/Tricore/Driver/LQ_GTM.o \
./src/0_AppSw/Tricore/Driver/LQ_SOFTI2C.o \
./src/0_AppSw/Tricore/Driver/LQ_SPI.o \
./src/0_AppSw/Tricore/Driver/LQ_STM.o \
./src/0_AppSw/Tricore/Driver/LQ_UART.o 

C_DEPS += \
./src/0_AppSw/Tricore/Driver/LQ_ADC.d \
./src/0_AppSw/Tricore/Driver/LQ_DMA.d \
./src/0_AppSw/Tricore/Driver/LQ_EEPROM.d \
./src/0_AppSw/Tricore/Driver/LQ_FFT.d \
./src/0_AppSw/Tricore/Driver/LQ_GPIO.d \
./src/0_AppSw/Tricore/Driver/LQ_GPT12_ENC.d \
./src/0_AppSw/Tricore/Driver/LQ_GTM.d \
./src/0_AppSw/Tricore/Driver/LQ_SOFTI2C.d \
./src/0_AppSw/Tricore/Driver/LQ_SPI.d \
./src/0_AppSw/Tricore/Driver/LQ_STM.d \
./src/0_AppSw/Tricore/Driver/LQ_UART.d 


# Each subdirectory must supply rules for building sources it contributes
src/0_AppSw/Tricore/Driver/%.o: ../src/0_AppSw/Tricore/Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw\Tricore\Compilers" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\0_AppSw\Config\Common" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore\_Reg" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC26XB -fshort-double -mcpu=tc26xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


