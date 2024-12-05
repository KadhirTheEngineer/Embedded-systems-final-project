################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Clock.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/Clock.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Clock.d_raw" -MT"Clock.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DAC5.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/DAC5.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"DAC5.d_raw" -MT"DAC5.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/LaunchPad.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LaunchPad.d_raw" -MT"LaunchPad.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/SPI.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"SPI.d_raw" -MT"SPI.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ST7735.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/ST7735.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ST7735.d_raw" -MT"ST7735.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SlidePot.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/SlidePot.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"SlidePot.d_raw" -MT"SlidePot.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TExaS.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/TExaS.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"TExaS.d_raw" -MT"TExaS.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: D:/more\ setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/inc/Timer.cpp $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/program files/ccs-studio/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug" -I"D:/program files/mspm0_sdk_1_20_01_06/source/third_party/CMSIS/Core/Include" -I"D:/program files/mspm0_sdk_1_20_01_06/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Timer.d_raw" -MT"Timer.o" -I"D:/more setups/MSPM0_ValvanoWare/MSPM0_ValvanoWare/ECE319K_Lab9H/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


