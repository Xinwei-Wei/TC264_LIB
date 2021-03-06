################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/4_McHal/Tricore/_PinMap/IfxAsclin_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxCcu6_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxCif_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxDsadc_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxEray_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxEth_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxGpt12_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxGtm_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxI2c_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxMsc_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxMultican_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxPort_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxPsi5_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxPsi5s_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxQspi_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxScu_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxSent_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxSmu_PinMap.c \
../src/4_McHal/Tricore/_PinMap/IfxVadc_PinMap.c 

OBJS += \
./src/4_McHal/Tricore/_PinMap/IfxAsclin_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxCcu6_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxCif_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxDsadc_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxEray_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxEth_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxGpt12_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxGtm_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxI2c_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxMsc_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxMultican_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxPort_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxPsi5_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxPsi5s_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxQspi_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxScu_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxSent_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxSmu_PinMap.o \
./src/4_McHal/Tricore/_PinMap/IfxVadc_PinMap.o 

C_DEPS += \
./src/4_McHal/Tricore/_PinMap/IfxAsclin_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxCcu6_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxCif_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxDsadc_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxEray_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxEth_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxGpt12_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxGtm_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxI2c_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxMsc_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxMultican_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxPort_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxPsi5_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxPsi5s_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxQspi_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxScu_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxSent_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxSmu_PinMap.d \
./src/4_McHal/Tricore/_PinMap/IfxVadc_PinMap.d 


# Each subdirectory must supply rules for building sources it contributes
src/4_McHal/Tricore/_PinMap/%.o: ../src/4_McHal/Tricore/_PinMap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw\Tricore\Compilers" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\0_AppSw\Config\Common" -I"D:\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore\_Reg" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC26XB -fshort-double -mcpu=tc26xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


