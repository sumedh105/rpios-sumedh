#pragma once

#include "common.h"

#include "peripherals/base.h"

struct GpioPinData {
	reg32 reserved;
	reg32 data[2];
};

struct GpioRegs {
	reg32 func_select[6];
	struct GpioPinData output_set;
	struct GpioPinData output_clear;
	struct GpioPinData level;
	struct GpioPinData ev_detect_status;
	struct GpioPinData re_detect_enable;
	struct GpioPinData fe_detect_enable;
	struct GpioPinData hi_detect_enable;
	struct GpioPinData lo_detect_enable;
	struct GpioPinData async_re_detect;
	struct GpioPinData aysnc_fe_detect;
	reg32 reserved[24];
	reg32 pup_pdn_cntrl_reg[4];
};

#define REGS_GPIO ((struct GpioRegs *)(PBASE + 0x00200000))
