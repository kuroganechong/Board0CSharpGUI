#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source;C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/kernel/tirtos/packages
override XDCROOT = C:/ti/ccs1100/xdctools_3_50_07_20_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/source;C:/ti/ccs1100/simplelink_msp432p4_sdk_2_20_00_12/kernel/tirtos/packages;C:/ti/ccs1100/xdctools_3_50_07_20_core/packages;..
HOSTOS = Windows
endif
