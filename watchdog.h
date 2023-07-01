// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

// ### WDCTL (0xC9) - Watchdog Timer Control
SFR(WDCTL, 0xC9);

// Reset=00 R/W Timer interval select.
// These bits select the timer interval, which is defined as a given number
// of 32 kHz oscillator periods.
// Note that the interval can only be changed when the WDT is IDLE, so the
// interval must be set at the same time as the timer is started.
#define MASK_WDCTL_INT BITMASK(2, 0)
// Clock period * 64 (approximately 1.9 ms)
// For CC253x and CC2540, when clock division is enabled through CLKCONCMD.CLKSPD, the
// length of the watchdog timer interval is reduced by a factor equal to the current oscillator clock
// frequency divided by the set clock speed. For example, if the 32-MHz crystal is selected and the
// clock speed is set to 4 MHz, then the watchdog timeout is reduced by a factor of 32 MHz / 4 MHz =
// 8. If the watchdog interval set by WDCTL.INT was 1 s, nominally it is 1 / 8 s with this clock division
// factor. For CC2541, the watchdog timer interval is independent of the clock division rate.
enum wdctl_int {
	WDCTL_INT_1000MS = 0u,  // Clock period * 32,768 (approximately 1 s) when running the 32-kHz XOSC
	WDCTL_INT_250MS  = 1u,  // Clock period * 8192 (approximately 0.25 s)
	WDCTL_INT_15MS   = 2u,  // Clock period * 512 (approximately 15.625 ms)
	WDCTL_INT_2MS    = 3u,  // Clock period × 64 (approximately 1.9 ms)
};

// WDCTL_MODE:2, % SIZE=2% 3:2 MODE[1:0] 00 R/W Mode select. These bits are used to start the WDT in watchdog mode or timer mode. Setting these
// bits to IDLE stops the timer when in timer mode. Note: to switch to watchdog mode when operating
// in timer mode, first stop the WDT - then start the WDT in Watchdog mode. When operating in
// Watchdog mode, writing these bits has no effect.
#define MASK_WDCTL_MODE BITMASK(2, 2)
enum wdctl_mode {
	WDCTL_MODE_IDLE     = (0u << 2),  // IDLE
	WDCTL_MODE_WATCHDOG = (2u << 2),  // Watchdog mode
	WDCTL_MODE_TIMER    = (3u << 2),  // Timer mode
};

// WDCTL_CLR:4, % SIZE=4% 7:4 CLR[3:0] 0000 R0/W Clear timer.
#define MASK_WDCTL_CLR BITMASK(4, 4)

// In watchdog mode, when 0xA followed by 0x5 is written to these bits, the timer is
// cleared (that is, loaded with 0). Note that the timer is only cleared when 0x5 is written within one
// watchdog clock period after 0xA was written. Writing these bits when the Watchdog Timer is IDLE
// has no effect. When operating in timer mode, the timer can be cleared to 0x0000 (but not stopped)
// by writing 1 to CLR[0] (the other 3 bits are don't care).
#define WDCTL_CLR_FEED1 0xA0
#define WDCTL_CLR_FEED2 0x50

#define WDCTL_CLR_TIM (1u << 4)  // Clear timer to 0x0000

//  R/W    Watchdog Timer interrupt flag # 0: Interrupt not pending # 1: Interrupt pending
SBIT(IRCON2_WDTIF, 0xE8, 4);

#define watchdog_feed()                                                        \
	{                                                                          \
		WDCTL = WDCTL_CLR_FEED1;                                               \
		WDCTL = WDCTL_CLR_FEED2;                                               \
	}

#define watchdog_start(_interval)                                              \
	{                                                                          \
		WDCTL = WDCTL_MODE_WATCHDOG | WDCTL_INT_##_interval;                   \
	}
