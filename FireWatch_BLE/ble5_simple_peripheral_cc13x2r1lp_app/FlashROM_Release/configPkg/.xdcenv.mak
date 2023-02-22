#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source;C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages;C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack
override XDCROOT = C:/ti/ccs1100/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source;C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/kernel/tirtos/packages;C:/ti/ccs1100/simplelink_cc13x2_26x2_sdk_2_40_00_81/source/ti/ble5stack;C:/ti/ccs1100/xdctools_3_51_01_18_core/packages;..
HOSTOS = Windows
endif
