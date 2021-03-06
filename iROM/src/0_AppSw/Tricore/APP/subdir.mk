################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/0_AppSw/Tricore/APP/LQ_ADC_7Mic.c \
../src/0_AppSw/Tricore/APP/LQ_Atom_Motor.c \
../src/0_AppSw/Tricore/APP/LQ_CAMERA.c \
../src/0_AppSw/Tricore/APP/LQ_GPIO_ExInt.c \
../src/0_AppSw/Tricore/APP/LQ_GPIO_KEY.c \
../src/0_AppSw/Tricore/APP/LQ_GPIO_LED.c \
../src/0_AppSw/Tricore/APP/LQ_GPT_mini512.c \
../src/0_AppSw/Tricore/APP/LQ_I2C_9AX.c \
../src/0_AppSw/Tricore/APP/LQ_I2C_MPU6050.c \
../src/0_AppSw/Tricore/APP/LQ_I2C_VL53.c \
../src/0_AppSw/Tricore/APP/LQ_ICM20602.c \
../src/0_AppSw/Tricore/APP/LQ_MT9V034.c \
../src/0_AppSw/Tricore/APP/LQ_STM_Timer.c \
../src/0_AppSw/Tricore/APP/LQ_TFT18.c \
../src/0_AppSw/Tricore/APP/LQ_Tim_InputCature.c \
../src/0_AppSw/Tricore/APP/LQ_Tom_Servo.c \
../src/0_AppSw/Tricore/APP/LQ_UART_Bluetooth.c \
../src/0_AppSw/Tricore/APP/OLED_IIC.c 

OBJS += \
./src/0_AppSw/Tricore/APP/LQ_ADC_7Mic.o \
./src/0_AppSw/Tricore/APP/LQ_Atom_Motor.o \
./src/0_AppSw/Tricore/APP/LQ_CAMERA.o \
./src/0_AppSw/Tricore/APP/LQ_GPIO_ExInt.o \
./src/0_AppSw/Tricore/APP/LQ_GPIO_KEY.o \
./src/0_AppSw/Tricore/APP/LQ_GPIO_LED.o \
./src/0_AppSw/Tricore/APP/LQ_GPT_mini512.o \
./src/0_AppSw/Tricore/APP/LQ_I2C_9AX.o \
./src/0_AppSw/Tricore/APP/LQ_I2C_MPU6050.o \
./src/0_AppSw/Tricore/APP/LQ_I2C_VL53.o \
./src/0_AppSw/Tricore/APP/LQ_ICM20602.o \
./src/0_AppSw/Tricore/APP/LQ_MT9V034.o \
./src/0_AppSw/Tricore/APP/LQ_STM_Timer.o \
./src/0_AppSw/Tricore/APP/LQ_TFT18.o \
./src/0_AppSw/Tricore/APP/LQ_Tim_InputCature.o \
./src/0_AppSw/Tricore/APP/LQ_Tom_Servo.o \
./src/0_AppSw/Tricore/APP/LQ_UART_Bluetooth.o \
./src/0_AppSw/Tricore/APP/OLED_IIC.o 

C_DEPS += \
./src/0_AppSw/Tricore/APP/LQ_ADC_7Mic.d \
./src/0_AppSw/Tricore/APP/LQ_Atom_Motor.d \
./src/0_AppSw/Tricore/APP/LQ_CAMERA.d \
./src/0_AppSw/Tricore/APP/LQ_GPIO_ExInt.d \
./src/0_AppSw/Tricore/APP/LQ_GPIO_KEY.d \
./src/0_AppSw/Tricore/APP/LQ_GPIO_LED.d \
./src/0_AppSw/Tricore/APP/LQ_GPT_mini512.d \
./src/0_AppSw/Tricore/APP/LQ_I2C_9AX.d \
./src/0_AppSw/Tricore/APP/LQ_I2C_MPU6050.d \
./src/0_AppSw/Tricore/APP/LQ_I2C_VL53.d \
./src/0_AppSw/Tricore/APP/LQ_ICM20602.d \
./src/0_AppSw/Tricore/APP/LQ_MT9V034.d \
./src/0_AppSw/Tricore/APP/LQ_STM_Timer.d \
./src/0_AppSw/Tricore/APP/LQ_TFT18.d \
./src/0_AppSw/Tricore/APP/LQ_Tim_InputCature.d \
./src/0_AppSw/Tricore/APP/LQ_Tom_Servo.d \
./src/0_AppSw/Tricore/APP/LQ_UART_Bluetooth.d \
./src/0_AppSw/Tricore/APP/OLED_IIC.d 


# Each subdirectory must supply rules for building sources it contributes
src/0_AppSw/Tricore/APP/%.o: ../src/0_AppSw/Tricore/APP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw\Tricore\Compilers" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\0_AppSw\Config\Common" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore\_Reg" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC26XB -fshort-double -mcpu=tc26xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


