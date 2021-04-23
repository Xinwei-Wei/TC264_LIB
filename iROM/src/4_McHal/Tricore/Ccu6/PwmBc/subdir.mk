################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/4_McHal/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.c 

OBJS += \
./src/4_McHal/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.o 

C_DEPS += \
./src/4_McHal/Tricore/Ccu6/PwmBc/IfxCcu6_PwmBc.d 


# Each subdirectory must supply rules for building sources it contributes
src/4_McHal/Tricore/Ccu6/PwmBc/%.o: ../src/4_McHal/Tricore/Ccu6/PwmBc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw\Tricore\Compilers" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\1_SrvSw" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\0_AppSw\Config\Common" -I"C:\Users\16528\Documents\htc-workspace\LQ_TC26xB_ASC\src\4_McHal\Tricore\_Reg" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC26XB -fshort-double -mcpu=tc26xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


