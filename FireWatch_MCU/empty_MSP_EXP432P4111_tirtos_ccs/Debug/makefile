################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS

GEN_OPTS__FLAG := --cmd_file="C:/Users/Administrator/Downloads/230216_SCDF_Firewatch/MCU_Load/tirtos_builds_MSP_EXP432P4111_release_ccs/Debug/configPkg/compiler.opt" 
GEN_CMDS__FLAG := -l"C:/Users/Administrator/Downloads/230216_SCDF_Firewatch/MCU_Load/tirtos_builds_MSP_EXP432P4111_release_ccs/Debug/configPkg/linker.cmd" 

ORDERED_OBJS += \
"./AmbientConditionTask.obj" \
"./Ambient_Sensor.obj" \
"./AnalogTask.obj" \
"./Board.obj" \
"./DACDriver.obj" \
"./HumanDetection.obj" \
"./IMU_Task.obj" \
"./IMU_driver.obj" \
"./IRSensorTask.obj" \
"./IR_Sensor.obj" \
"./LevyWalkTask.obj" \
"./MPU9250_9Axis_MotionApps.obj" \
"./StimulationTask.obj" \
"./data_fusion.obj" \
"./empty.obj" \
"./ext_flash.obj" \
"./fftTask.obj" \
"./inv_mpu.obj" \
"./inv_mpu_dmp_motion_driver.obj" \
"./main_tirtos.obj" \
"../MSP_EXP432P4111_TIRTOS.cmd" \
-l"ti/display/lib/display.aem4f" \
-l"ti/grlib/lib/ccs/m4f/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4f/spiffs.a" \
-l"ti/drivers/lib/drivers_msp432p4x1xi.aem4f" \
-l"third_party/fatfs/lib/ccs/m4f/fatfs.a" \
-l"ti/dpl/lib/dpl_msp432p4x1xi.aem4f" \
$(GEN_CMDS__FLAG) \
-l"ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
empty_MSP_EXP432P4111_tirtos_ccs.out \

EXE_OUTPUTS__QUOTED += \
"empty_MSP_EXP432P4111_tirtos_ccs.out" \

BIN_OUTPUTS += \
empty_MSP_EXP432P4111_tirtos_ccs.hex \

BIN_OUTPUTS__QUOTED += \
"empty_MSP_EXP432P4111_tirtos_ccs.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(A_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "empty_MSP_EXP432P4111_tirtos_ccs.out"

dependents:
	-cd C:/Users/Administrator/Downloads/230216_SCDF_Firewatch/MCU_Load/tirtos_builds_MSP_EXP432P4111_release_ccs/Debug && $(MAKE) all

# Tool invocations
empty_MSP_EXP432P4111_tirtos_ccs.out: $(OBJS) $(CMD_SRCS) $(A_SRCS) $(GEN_CMDS) C:/Users/Administrator/Downloads/230216_SCDF_Firewatch/MCU_Load/tirtos_builds_MSP_EXP432P4111_release_ccs/Debug/tirtos_builds_MSP_EXP432P4111_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=none --define=IMU_BUF_SIZE=50 --define=NODOMINANTFREQUENCY=14 --define=MPU9250 --define=NO_CHANNEL_STI=4 --define=__MSP432P4011__ --define=AUDIO_SAMPLE_RATE=16000 --define=FFT_SIZE=1024 --define=SAMPLE_SIZE=576 --define=ARM_MATH_CM4 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"empty_MSP_EXP432P4111_tirtos_ccs.map" -i"C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source" -i"C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/kernel/tirtos/packages" -i"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="empty_MSP_EXP432P4111_tirtos_ccs_linkInfo.xml" --rom_model -o "empty_MSP_EXP432P4111_tirtos_ccs.out" $(ORDERED_OBJS) $(A_SRCS)
	@echo 'Finished building target: "$@"'
	@echo ' '

empty_MSP_EXP432P4111_tirtos_ccs.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armhex" --diag_wrap=off -o "empty_MSP_EXP432P4111_tirtos_ccs.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "AmbientConditionTask.obj" "Ambient_Sensor.obj" "AnalogTask.obj" "Board.obj" "DACDriver.obj" "HumanDetection.obj" "IMU_Task.obj" "IMU_driver.obj" "IRSensorTask.obj" "IR_Sensor.obj" "LevyWalkTask.obj" "MPU9250_9Axis_MotionApps.obj" "StimulationTask.obj" "data_fusion.obj" "empty.obj" "ext_flash.obj" "fftTask.obj" "inv_mpu.obj" "inv_mpu_dmp_motion_driver.obj" "main_tirtos.obj" 
	-$(RM) "AmbientConditionTask.d" "Ambient_Sensor.d" "AnalogTask.d" "Board.d" "DACDriver.d" "HumanDetection.d" "IMU_Task.d" "IMU_driver.d" "IRSensorTask.d" "IR_Sensor.d" "LevyWalkTask.d" "MPU9250_9Axis_MotionApps.d" "StimulationTask.d" "data_fusion.d" "empty.d" "ext_flash.d" "fftTask.d" "inv_mpu.d" "inv_mpu_dmp_motion_driver.d" "main_tirtos.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/Users/Administrator/Downloads/230216_SCDF_Firewatch/MCU_Load/tirtos_builds_MSP_EXP432P4111_release_ccs/Debug/tirtos_builds_MSP_EXP432P4111_release_ccs.lib:

-include ../makefile.targets

