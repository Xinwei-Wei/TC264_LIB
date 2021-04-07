################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/4_McHal/Tricore/Scu/Std/IfxScuCcu.c \
../src/4_McHal/Tricore/Scu/Std/IfxScuEru.c \
../src/4_McHal/Tricore/Scu/Std/IfxScuWdt.c 

OBJS += \
./src/4_McHal/Tricore/Scu/Std/IfxScuCcu.o \
./src/4_McHal/Tricore/Scu/Std/IfxScuEru.o \
./src/4_McHal/Tricore/Scu/Std/IfxScuWdt.o 

C_DEPS += \
./src/4_McHal/Tricore/Scu/Std/IfxScuCcu.d \
./src/4_McHal/Tricore/Scu/Std/IfxScuEru.d \
./src/4_McHal/Tricore/Scu/Std/IfxScuWdt.d 


# Each subdirectory must supply rules for building sources it contributes
src/4_McHal/Tricore/Scu/Std/%.o: ../src/4_McHal/Tricore/Scu/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"C:\Users\11373\Desktop\LQ_TC26xB_ASC\src\4_McHal\Tricore" -I"C:\Users\11373\Desktop\LQ_TC26xB_ASC\src\1_SrvSw\Tricore\Compilers" -I"C:\Users\11373\Desktop\LQ_TC26xB_ASC\src\1_SrvSw" -I"C:\Users\11373\Desktop\LQ_TC26xB_ASC\src\0_AppSw\Config\Common" -I"C:\Users\11373\Desktop\LQ_TC26xB_ASC\src\4_McHal\Tricore\_Reg" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC26XB -fshort-double -mcpu=tc26xx -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


