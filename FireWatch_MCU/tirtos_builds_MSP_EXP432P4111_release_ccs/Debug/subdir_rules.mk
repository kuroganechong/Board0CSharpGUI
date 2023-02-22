################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1328398049:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1328398049-inproc

build-1328398049-inproc: ../release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs1100/xdctools_3_50_07_20_core/xs" --xdcpath="C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source;C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P4111 -r release -c "C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1328398049 ../release.cfg
configPkg/compiler.opt: build-1328398049
configPkg/: build-1328398049


