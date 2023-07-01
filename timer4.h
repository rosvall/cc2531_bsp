// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

SBIT(IEN1_T4IE,     0xB8, 4); //  R/W    Timer 4 interrupt enable
SBIT(IRCON_T4IF,    0xC0, 4); //  R/W/H0    Timer 4 interrupt flag. Set to 1 when Timer 4 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TIMIF_T4OVFIF, 0xD8, 3); //  R/W0   Timer 4 overflow interrupt flag
SBIT(TIMIF_T4CH0IF, 0xD8, 4); //  R/W0   Timer 4 channel 0 interrupt flag
SBIT(TIMIF_T4CH1IF, 0xD8, 5); //  R/W0   Timer 4 channel 1 interrupt flag

SFR(T4CTL, 0xEB); // Timer 4 Control

// 0 R/W Timer 4 mode. Select the mode as follows:
#define MASK_T4CTL_MODE BITMASK(2, 0)
enum T4_MODE {
	T4CTL_MODE_FREE_RUNNING = 0u,  // Free running, repeatedly count from 0x00 to 0xFF
	T4CTL_MODE_DOWN         = 1u,  // Down, count from T4CC0 to 0x00
	T4CTL_MODE_MODULO       = 2u,  // Modulo, repeatedly count from 0x00 to T4CC0
	T4CTL_MODE_UP_AND_DOWN  = 3u,  // Up-and-down, repeatedly count from 0x00 to T4CC0 and down to 0x00
};

#define T4CTL_CLR BIT(2) // (reset=0 R0/W1) Clear counter. Writing a 1 to CLR resets the counter to 0x00 and initializes all output pins of associated channels. Always read as 0.

// Overflow interrupt mask (reset=1 R/W)
enum {
	T4CTL_OVFIM_DISABLED = 0,
	T4CTL_OVFIM          = BIT(3),
};

#define T4CTL_START BIT(4) // (reset=R/) Start timer. Normal operation when set, suspended when cleared

// T4CTL_DIV (Reset=000 R/W) Prescaler divider value.
// Generates the active clock edge used to clock the timer from CLKCONCMD.TICKSPD as follows:
#define MASK_T4CTL_DIV BITMASK(3, 5)
enum T4_DIV {
	T4CTL_DIV1   = (0U << 5),  // Tick frequency / 1
	T4CTL_DIV2   = (1U << 5),  // Tick frequency / 2
	T4CTL_DIV4   = (2U << 5),  // Tick frequency / 4
	T4CTL_DIV8   = (3U << 5),  // Tick frequency / 8
	T4CTL_DIV16  = (4U << 5),  // Tick frequency / 16
	T4CTL_DIV32  = (5U << 5),  // Tick frequency / 32
	T4CTL_DIV64  = (6U << 5),  // Tick frequency / 64
	T4CTL_DIV128 = (7U << 5),  // Tick frequency / 128
};

#define timer4_setup(_mode, _ovfim, _divider)                                  \
	do {                                                                       \
		T4CTL = T4CTL_##_mode | T4CTL_##_ovfim | T4CTL_##_divider;             \
	} while (0)


SFR(T4CCTL0, 0xEC); // Timer 4 Channel 0 Capture/Compare Control
SFR(T4CCTL1, 0xEE); // Timer 4 Channel 1 Capture/Compare Control

//  Capture mode select. (Reset=00 R/W)
#define MASK_T4CCTL_CAP BITMASK(2, 0)
enum T4CCTL_EDGE {
	T4CCTL_CAP_EDGE_NONE     = 0U, // No capture
	T4CCTL_CAP_EDGE_RISING   = 1U, // Capture on rising edge
	T4CCTL_CAP_EDGE_FALLING  = 2U, // Capture on falling edge
	T4CCTL_CAP_EDGE_ANY_EDGE = 3U, // Capture on both edges
};

// T4CCTL_MODE  Select Timer 4 channel n mode (reset=0 R/W)
enum T4CCTL_MODE {
	T4CCTL_MODE_CAPTURE = 0,
	T4CCTL_MODE_COMPARE = BIT(2),
};

// T4CCTLn_CMP
// Channel n Compare output-mode select.
// Specified action on output when timer value equals compare value in T4CC1 (Reset=000 R/W)
#define MASK_T4CCTL_CMP BITMASK(3, 3)

enum T4CCTL_CMP {
	T4CCTL_CMP_SET_ON_CMP             = (0U << 3), // Set output on compare
	T4CCTL_CMP_CLK_ON_CMP             = (1U << 3), // Clear output on compare
	T4CCTL_CMP_TOGGLE                 = (2U << 3), // Toggle output on compare
	T4CCTL_CMP_SET_ON_CMP_UP          = (3U << 3), // Set on compare-up, clear on compare-down in up-down mode. Otherwise, set output on  compare, clear on 0.
	T4CCTL_CMP_CLR_ON_CMP_UP          = (4U << 3), // Clear output on compare-up, set on compare-down in up-down mode. Otherwise clear output on compare, set on 0.
	T4CCTL_CMP_SET_ON_CMP_CLEAR_ON_FF = (5U << 3), // Set output on compare, clear on 0xFF
	T4CCTL_CMP_CLR_ON_CMP_SET_ON_0    = (6U << 3), // Clear output on compare, set on 0x00
	T4CCTL_CMP_INIT_PIN               = (7U << 3), // Initialize output pin. CMP[2:0] is not changed.
};

// Channel 1 interrupt mask (reset=1 R/W)
enum T4CCTL_IM {
	T4CCTL_INTR_DISABLED = 0,
	T4CCTL_INTR_ENABLED  = BIT(6),
};

#define timer4_ch_setup(_n, _cap, _mode, _cmp, _intr)                                 \
	do {                                                                              \
		T4CCTL##_n = T4CCTL_##_cap | T4CCTL_##_mode | T4CCTL_##_cmp | T4CCTL_##_intr; \
	} while (0)


SFR(T4CNT, 0xEA); // Timer 4 Counter
SFR(T4CC0, 0xED); // Timer 4 Channel 0 Capture or Compare Value
SFR(T4CC1, 0xEF); // Timer 4 Channel 1 Capture or Compare Value
