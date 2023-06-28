// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>

// Clock Control Command
// ### CLKCONCMD (0xC6) - Clock Control Command
SFR(CLKCONCMD, 0xC6);

// CLKCONCMD_CLKSPD (Reset=001 R/W) Clock speed.
// Cannot be higher than system clock setting given by the OSC bit
// setting. Indicates current system-clock frequency
enum CLK_CLKSPD {
	CLK_CLKSPD_32M  = (0u << 0),
	CLK_CLKSPD_16M  = (1u << 0),
	CLK_CLKSPD_8M   = (2u << 0),
	CLK_CLKSPD_4M   = (3u << 0),
	CLK_CLKSPD_2M   = (4u << 0),
	CLK_CLKSPD_1M   = (5u << 0),
	CLK_CLKSPD_500K = (6u << 0),
	CLK_CLKSPD_250K = (7u << 0),
};

// Note that CLKCONCMD.CLKSPD can be set to any value, but the effect is
// limited by the CLKCONCMD.OSC setting; that is, if
// CLKCONCMD.OSC = 1 and CLKCONCMD.CLKSPD = 000,
// CLKCONSTA.CLKSPD reads 001, and the real CLKSPD is 16 MHz.
// Note also that the debugger cannot be used with a divided system clock. When
// running the debugger, the value of CLKCONCMD.CLKSPD should
// be set to 000 when CLKCONCMD.OSC = 0 or to 001 when CLKCONCMD.OSC = 1.

// TICKSPD reset=001 R/W Timer ticks output setting.
// Cannot be higher than system clock setting given by OSC bit setting.
// Note that CLKCONCMD.TICKSPD can be set to any value, but the effect is
// limited by the CLKCONCMD.OSC setting; that is, if CLKCONCMD.OSC = 1 and
// CLKCONCMD.TICKSPD = 000, CLKCONSTA.TICKSPD reads 001, and the real TICKSPD is 16 MHz.
enum CLK_TICKSPD {
	CLK_TICKSPD_32M  = (0u << 3),
	CLK_TICKSPD_16M  = (1u << 3),
	CLK_TICKSPD_8M   = (2u << 3),
	CLK_TICKSPD_4M   = (3u << 3),
	CLK_TICKSPD_2M   = (4u << 3),
	CLK_TICKSPD_1M   = (5u << 3),
	CLK_TICKSPD_500K = (6u << 3),
	CLK_TICKSPD_250K = (7u << 3),
};

// (reset=1 R/W) System clock-source select. Setting this bit initiates a
// clock-source change only. CLKCONSTA.OSC reflects the current setting. 0: 32
// MHz XOSC 1: 16 MHz RCOSC
enum CLK_OSC {
	CLK_OSC_32MHZ_XTAL = (0u << 6),
	CLK_OSC_16MHZ_RC   = (1u << 6),
};

// (reset=1 R/W) 32-kHz clock-source select. Setting this bit initiates a
// clock-source change only. CLKCONSTA.OSC32K reflects the current setting. The
// 16-MHz RCOSC must be selected as system clock when this bit is to be changed.
// This bit does not give an indication of the stability of the 32-kHz XOSC. 0:
// 32 kHz XOSC 1: 32 kHz RCOSC
enum CLK_OSC32K {
	CLK_OSC32K_XTAL = (0u << 7),
	CLK_OSC32K_RC   = (1u << 7),
};

// Clock Control Status
// ### CLKCONSTA (0x9E) - Clock Control Status
SFR(CLKCONSTA, 0x9E);

#define clk_setup(_clkspd, _tickspd, _cpu_osc, _time_osc)                                    \
	{                                                                                        \
		uint8_t setting = CLK_##_clkspd | CLK_##_tickspd | CLK_##_cpu_osc | CLK_##_time_osc; \
		CLKCONCMD = setting;                                                                 \
		while (CLKCONSTA != setting)                                                         \
			;                                                                                \
	}
