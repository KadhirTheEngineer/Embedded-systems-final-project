################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
images/pipedreams/%.o: ../images/pipedreams/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"images/pipedreams/$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


