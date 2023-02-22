################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1754108049:
	@$(MAKE) --no-print-directory -Onone -f TOOLS/subdir_rules.mk build-1754108049-inproc

build-1754108049-inproc: ../TOOLS/ble_release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs1100/xdctools_3_51_01_18_core/xs" --xdcpath="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source;C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages;C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.simplelink:CC1352R1F3 -r release -c "C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS" --compileOptions "-mv7M4 --code_state=16 -me -O4 --opt_for_speed=0 --include_path=\"C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_app\" --include_path=\"C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_app/Application\" --include_path=\"C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_app/Startup\" --include_path=\"C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_app/PROFILES\" --include_path=\"C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_app/Include\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/controller/cc26xx/inc\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/inc\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/rom\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/inc\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/target\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common/cc26xx\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/inc\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/heapmgr\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/src/inc\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/osal/src/inc\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/saddr\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/sdata\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv/cc26xx\" --include_path=\"C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2\" --include_path=\"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include\" --define=DeviceFamily_CC13X2 -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1754108049 ../TOOLS/ble_release.cfg
configPkg/compiler.opt: build-1754108049
configPkg/: build-1754108049


