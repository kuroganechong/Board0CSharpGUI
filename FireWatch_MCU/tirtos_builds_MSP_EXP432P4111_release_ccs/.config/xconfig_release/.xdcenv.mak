#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_msp432p4_sdk_2_20_00_12/source;C:/ti/simplelink_msp432p4_sdk_2_20_00_12/kernel/tirtos/packages;E:/HuuDuoc/WirelessBoard/tirtos_builds_MSP_EXP432P4111_release_ccs/.config
override XDCROOT = C:/ti/xdctools_3_50_07_20_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_msp432p4_sdk_2_20_00_12/source;C:/ti/simplelink_msp432p4_sdk_2_20_00_12/kernel/tirtos/packages;E:/HuuDuoc/WirelessBoard/tirtos_builds_MSP_EXP432P4111_release_ccs/.config;C:/ti/xdctools_3_50_07_20_core/packages;..
HOSTOS = Windows
endif
