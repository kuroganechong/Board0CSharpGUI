################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Host/gap.obj: C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/host/gap.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/defines/ble5_simple_peripheral_cc13x2r1lp_stack_library_FlashROM_Library.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/build_components.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/factory_config.opt" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/build_config.opt"  -mv7M4 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/controller/cc26xx/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/rom" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx/npi/stack" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/npi/src" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/osal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/aes/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/saddr" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/rf_patches" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages" --include_path="C:/ti/ccs1100/xdctools_3_51_01_18_core/packages" --include_path="C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include" --define=DeviceFamily_CC13X2 -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Host/$(basename $(<F)).d_raw" --obj_directory="Host" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Host/gapbondmgr.obj: C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/host/gapbondmgr.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/defines/ble5_simple_peripheral_cc13x2r1lp_stack_library_FlashROM_Library.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/build_components.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/factory_config.opt" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/build_config.opt"  -mv7M4 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/controller/cc26xx/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/rom" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx/npi/stack" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/npi/src" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/osal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/aes/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/saddr" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/rf_patches" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages" --include_path="C:/ti/ccs1100/xdctools_3_51_01_18_core/packages" --include_path="C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include" --define=DeviceFamily_CC13X2 -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Host/$(basename $(<F)).d_raw" --obj_directory="Host" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Host/gatt_uuid.obj: C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/host/gatt_uuid.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/defines/ble5_simple_peripheral_cc13x2r1lp_stack_library_FlashROM_Library.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/build_components.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/factory_config.opt" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/build_config.opt"  -mv7M4 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/controller/cc26xx/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/rom" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx/npi/stack" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/npi/src" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/osal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/aes/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/saddr" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/rf_patches" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages" --include_path="C:/ti/ccs1100/xdctools_3_51_01_18_core/packages" --include_path="C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include" --define=DeviceFamily_CC13X2 -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Host/$(basename $(<F)).d_raw" --obj_directory="Host" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Host/gattservapp_util.obj: C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/host/gattservapp_util.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/defines/ble5_simple_peripheral_cc13x2r1lp_stack_library_FlashROM_Library.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/build_components.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/factory_config.opt" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/build_config.opt"  -mv7M4 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/controller/cc26xx/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/rom" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx/npi/stack" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/npi/src" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/osal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/aes/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/saddr" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/rf_patches" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages" --include_path="C:/ti/ccs1100/xdctools_3_51_01_18_core/packages" --include_path="C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include" --define=DeviceFamily_CC13X2 -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Host/$(basename $(<F)).d_raw" --obj_directory="Host" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Host/sm_ecc.obj: C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/host/sm_ecc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/bin/armcl" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/defines/ble5_simple_peripheral_cc13x2r1lp_stack_library_FlashROM_Library.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/build_components.opt" --cmd_file="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/config/factory_config.opt" --cmd_file="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library/TOOLS/build_config.opt"  -mv7M4 --code_state=16 -me -O4 --opt_for_speed=0 --include_path="C:/Users/Administrator/Downloads/SCDF/BLE/ble5_simple_peripheral_cc13x2r1lp_stack_library" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/controller/cc26xx/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/rom" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/common/cc26xx/npi/stack" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target/_common/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/target" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/hal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/icall/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/npi/src" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/osal/src/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/aes/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv/cc26xx" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/nv" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack/services/src/saddr" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/rf_patches" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/devices/cc13x2_cc26x2/inc" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source" --include_path="C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages" --include_path="C:/ti/ccs1100/xdctools_3_51_01_18_core/packages" --include_path="C:/ti/ccs1100/ti-cgt-arm_18.1.4.LTS/include" --define=DeviceFamily_CC13X2 -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="Host/$(basename $(<F)).d_raw" --obj_directory="Host" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


