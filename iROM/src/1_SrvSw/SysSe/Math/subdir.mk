################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/1_SrvSw/SysSe/Math/Ifx_AngleTrkF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_Cf32.c \
../src/1_SrvSw/SysSe/Math/Ifx_Crc.c \
../src/1_SrvSw/SysSe/Math/Ifx_FftF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_FftF32_BitReverseTable.c \
../src/1_SrvSw/SysSe/Math/Ifx_FftF32_TwiddleTable.c \
../src/1_SrvSw/SysSe/Math/Ifx_IntegralF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_LowPassPt1F32.c \
../src/1_SrvSw/SysSe/Math/Ifx_LutAtan2F32.c \
../src/1_SrvSw/SysSe/Math/Ifx_LutAtan2F32_Table.c \
../src/1_SrvSw/SysSe/Math/Ifx_LutLSincosF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_LutLinearF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_LutSincosF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_LutSincosF32_Table.c \
../src/1_SrvSw/SysSe/Math/Ifx_RampF32.c \
../src/1_SrvSw/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.c \
../src/1_SrvSw/SysSe/Math/Ifx_WndF32_HannTable.c 

OBJS += \
./src/1_SrvSw/SysSe/Math/Ifx_AngleTrkF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_Cf32.o \
./src/1_SrvSw/SysSe/Math/Ifx_Crc.o \
./src/1_SrvSw/SysSe/Math/Ifx_FftF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_FftF32_BitReverseTable.o \
./src/1_SrvSw/SysSe/Math/Ifx_FftF32_TwiddleTable.o \
./src/1_SrvSw/SysSe/Math/Ifx_IntegralF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_LowPassPt1F32.o \
./src/1_SrvSw/SysSe/Math/Ifx_LutAtan2F32.o \
./src/1_SrvSw/SysSe/Math/Ifx_LutAtan2F32_Table.o \
./src/1_SrvSw/SysSe/Math/Ifx_LutLSincosF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_LutLinearF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_LutSincosF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_LutSincosF32_Table.o \
./src/1_SrvSw/SysSe/Math/Ifx_RampF32.o \
./src/1_SrvSw/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.o \
./src/1_SrvSw/SysSe/Math/Ifx_WndF32_HannTable.o 

C_DEPS += \
./src/1_SrvSw/SysSe/Math/Ifx_AngleTrkF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_Cf32.d \
./src/1_SrvSw/SysSe/Math/Ifx_Crc.d \
./src/1_SrvSw/SysSe/Math/Ifx_FftF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_FftF32_BitReverseTable.d \
./src/1_SrvSw/SysSe/Math/Ifx_FftF32_TwiddleTable.d \
./src/1_SrvSw/SysSe/Math/Ifx_IntegralF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_LowPassPt1F32.d \
./src/1_SrvSw/SysSe/Math/Ifx_LutAtan2F32.d \
./src/1_SrvSw/SysSe/Math/Ifx_LutAtan2F32_Table.d \
./src/1_SrvSw/SysSe/Math/Ifx_LutLSincosF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_LutLinearF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_LutSincosF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_LutSincosF32_Table.d \
./src/1_SrvSw/SysSe/Math/Ifx_RampF32.d \
./src/1_SrvSw/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.d \
./src/1_SrvSw/SysSe/Math/Ifx_WndF32_HannTable.d 


# Each subdirectory must supply rules for building sources it contributes
src/1_SrvSw/SysSe/Math/%.o: ../src/1_SrvSw/SysSe/Math/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw\Tricore\Compilers" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\0_AppSw\Config\Common" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore\_Reg" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC26XB -fshort-double -mcpu=tc26xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


