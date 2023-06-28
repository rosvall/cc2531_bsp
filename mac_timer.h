// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>
#include "bits.h"

//  R/W    Timer 2 interrupt enable
// 0: Interrupt disabled # 1: Interrupt enabled
SBIT(IEN1_T2IE,     0xB8, 2);

//  R/W    Timer 2 interrupt flag.
// Set to 1 when Timer 2 interrupt occurs and cleared when CPU
// H0     vectors to the interrupt service routine.
// 0: Interrupt not pending # 1: Interrupt pending
SBIT(IRCON_T2IF,    0xC0, 2);

// Timer 2 Control Register
SFR(T2CTRL,         0x94);
// ### T2CTRL (0x94) - Timer 2 Control Register
// (reset=0 R/W) Write 1 to start timer, write 0 to stop timer. When read, it returns the last written # value.
#define T2CTRL_RUN        BIT(0)
// (reset=1 R/W) 0: Starting and stopping of timer is immediate, i.e., synchronous with clk_rf_32m. 
// 1: Starting and stopping of timer happens at the first positive edge of the 32-kHz clock. 
//  Read Section 22.4 for more details regarding timer start and stop.
#define T2CTRL_SYNC       BIT(1)
// (reset=0 R) State of Timer 2 # 0: Timer idle # 1: Timer running
#define T2CTRL_STATE      BIT(2)
// (reset=0 R/W) 0: Reading T2M0 with T2MSEL.T2MSEL = 000 latches the
// high byte of the timer, # making it ready to be read from T2M1.
// Reading T2MOVF0 with T2MSEL.T2MOVFSEL # = 000 latches the two most-significant
// bytes of the overflow counter, making it
// possible to read these from T2MOVF1 and T2MOVF2.
// 1: Reading T2M0 with T2MSEL.T2MSEL = 000 latches the high byte of the timer and
// the entire overflow counter at once, making it possible to read the values from T2M1,
// T2MOVF0, T2MOVF1, and T2MOVF2.
#define T2CTRL_LATCH_MODE BIT(3)  

// Timer 2 Event Configuration
SFR(T2EVTCFG,       0x9C);
enum T2EVTCFG {
	T2EVTCFG_PER      = 0u,
	T2EVTCFG_CMP1     = 1u,
	T2EVTCFG_CMP2     = 2u,
	T2EVTCFG_OVF_PER  = 3u,
	T2EVTCFG_OVF_CMP1 = 4u,
	T2EVTCFG_OVF_CMP2 = 5u,
	T2EVTCFG_NONE     = 7u,
};

#define mac_timer_setup_event_pulses(_evt1, _evt2)                             \
	do {                                                                       \
		T2EVTCFG = (T2EVTCFG_##_evt2) << 4 | T2EVTCFG_##_evt1;                 \
	} while (0)

SFR(T2IRQF,         0xA1); // Timer 2 Interrupt Flags
// ### T2IRQF (0xA1) - Timer 2 Interrupt Flags
// T2IRQF_PERF          (reset=0 R/W0) Set when the Timer 2 counter would have counted to a value equal to t2_per, # but instead wraps to 0.
// T2IRQF_COMPARE1F     (reset=0 R/W0) Set when the Timer 2 counter counts to the value set at t2_cmp1
// T2IRQF_COMPARE2F     (reset=0 R/W0) Set when the Timer 2 counter counts to the value set at t2_cmp2
// T2IRQF_OVF_PERF      (reset=0 R/W0) Set when the Timer 2 overflow counter would have counted to a value equal to # t2ovf_per, but instead wraps to 0
// T2IRQF_OVF_COMPARE1F (reset=0 R/W0) Set when the Timer 2 overflow counter counts to the value set at Timer 2 # t2ovf_cmp1
// T2IRQF_OVF_COMPARE2F (reset=0 R/W0) Set when the Timer 2 overflow counter counts to the value set at t2ovf_cmp2

SFR(T2IRQM,         0xA7); // Timer 2 Interrupt Mask
// T2IRQM_PERM          (reset=0 R/W) Enables the TIMER2_PER interrupt
// T2IRQM_COMPARE1M     (reset=0 R/W) Enables the TIMER2_COMPARE1 interrupt
// T2IRQM_COMPARE2M     (reset=0 R/W) Enables the TIMER2_COMPARE2 interrupt
// T2IRQM_OVF_PERM      (reset=0 R/W) Enables the TIMER2_OVF_PER interrupt
// T2IRQM_OVF_COMPARE1M (reset=0 R/W) Enables the TIMER2_OVF_COMPARE1 interrupt
// T2IRQM_OVF_COMPARE2M (reset=0 R/W) Enables the TIMER2_OVF_COMPARE2 interrupt
enum T2IRQ {
	T2IRQ_PER          = BIT(0),  // TIMER2_PER interrupt bit
	T2IRQ_COMPARE1     = BIT(1),  // TIMER2_COMPARE1 interrupt bit
	T2IRQ_COMPARE2     = BIT(2),  // TIMER2_COMPARE2 interrupt bit
	T2IRQ_OVF_PER      = BIT(3),  // TIMER2_OVF_PER interrupt bit
	T2IRQ_OVF_COMPARE1 = BIT(4),  // TIMER2_OVF_COMPARE1 interrupt bit
	T2IRQ_OVF_COMPARE2 = BIT(5),  // TIMER2_OVF_COMPARE2 interrupt bit
};

SFR(T2M0,           0xA2); // Timer 2 Multiplexed Register 0
SFR(T2M1,           0xA3); // Timer 2 Multiplexed Register 1
SFR(T2MOVF0,        0xA4); // Timer 2 Multiplexed Overflow Register 0
SFR(T2MOVF1,        0xA5); // Timer 2 Multiplexed Overflow Register 1
SFR(T2MOVF2,        0xA6); // Timer 2 Multiplexed Overflow Register 2

SFR(T2MSEL,         0xC3); // Timer 2 Multiplex Select
// T2MSEL_T2MSEL (Reset=000 R/W)
// The value of this register selects the internal registers that are modified or read when accessing T2M0 and T2M1.

enum T2MSEL_T2M {
	T2MSEL_T2M_TIMER      = (0u << 0),  // t2tim (timer count value)
	T2MSEL_T2M_CAPTURE    = (1u << 0),  // t2_cap (timer capture)
	T2MSEL_T2M_PERIOD     = (2u << 0),  // t2_per (timer period)
	T2MSEL_T2M_CMP1       = (3u << 0),  // t2_cmp1 (timer compare 1)
	T2MSEL_T2M_CMP2       = (4u << 0),  // t2_cmp2 (timer compare 2)
};
// T2MSEL_T2MOVFSEL (Reset=000 R/W)
// The value of this register selects the internal registers that are modified or read when accessing T2MOVF0, T2MOVF1, and T2MOVF2.
enum T2MSEL_T2OVF {
	T2MSEL_T2OVF_OVERFLOW = (0u << 4),  // t2ovf (overflow counter)
	T2MSEL_T2OVF_CAPTURE  = (1u << 4),  // t2ovf_cap (overflow capture)
	T2MSEL_T2OVF_PERIOD   = (2u << 4),  // t2ovf_per (overflow period)
	T2MSEL_T2OVF_CMP1     = (3u << 4),  // t2ovf_cmp1 (overflow compare 1)
	T2MSEL_T2OVF_CMP2     = (4u << 4),  // t2ovf_cmp2 (overflow compare 2)
};

#define mac_timer_select_multiplexed_regs(_t2m, _t2ovf)                        \
	{                                                                       \
		T2MSEL = T2MSEL_##_t2m | T2MSEL_##_t2ovf;                              \
	}

#define mac_timer_set_period(_value)                                           \
	{                                                                       \
		mac_timer_select_multiplexed_regs(T2M_PERIOD, T2OVF_PERIOD);         \
		uint16_t period = _value;                                                      \
		T2M0 = period;                                                            \
		T2M1 = period >> 8;                                                       \
	}
