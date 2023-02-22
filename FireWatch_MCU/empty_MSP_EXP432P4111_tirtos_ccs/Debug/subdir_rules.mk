################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Administrator/Downloads/230216_SCDF_Firewatch/MCU_Load/empty_MSP_EXP432P4111_tirtos_ccs" --include_path="C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source/ti/posix/ccs" --include_path="C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source/ti/devices/msp432p4xx/inc" --include_path="C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include" --advice:power=none --define=IMU_BUF_SIZE=50 --define=NODOMINANTFREQUENCY=14 --define=MPU9250 --define=NO_CHANNEL_STI=4 --define=__MSP432P4011__ --define=AUDIO_SAMPLE_RATE=16000 --define=FFT_SIZE=1024 --define=SAMPLE_SIZE=576 --define=ARM_MATH_CM4 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


