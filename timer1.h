// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>


SBIT(IEN1_T1IE, 0xB8, 1);     //  R/W    Timer 1 interrupt enable # 0: Interrupt disabled # 1: Interrupt enabled
SBIT(IRCON_T1IF, 0xC0, 1);    //  R/W    Timer 1 interrupt flag. Set to 1 when Timer 1 interrupt occurs and cleared when CPU # H0     vectors to the interrupt service routine. # 0: Interrupt not pending # 1: Interrupt pending
SBIT(TIMIF_T1OVFIM, 0xD8, 6); //  R/W    Timer 1 overflow interrupt mask

SFR(T1STAT, 0xAF);        // Timer 1 Status
#define T1STAT_CH0IF BIT(0)     // (reset=0 R/W0) Timer 1 channel 0 interrupt flag. Set when the channel 0 interrupt condition occurs. Writing a 1 has no # effect.
#define T1STAT_CH1IF BIT(1)     // (reset=0 R/W0) Timer 1 channel 1 interrupt flag. Set when the channel 1 interrupt condition occurs. Writing a 1 has no # effect.
#define T1STAT_CH2IF BIT(2)     // (reset=0 R/W0) Timer 1 channel 2 interrupt flag. Set when the channel 2 interrupt condition occurs. Writing a 1 has no # effect.
#define T1STAT_CH3IF BIT(3)     // (reset=0 R/W0) Timer 1 channel 3 interrupt flag. Set when the channel 3 interrupt condition occurs. Writing a 1 has no # effect.
#define T1STAT_CH4IF BIT(4)     // (reset=0 R/W0) Timer 1 channel 4 interrupt flag. Set when the channel 4 interrupt condition occurs. Writing a 1 has no # effect.
#define T1STAT_OVFIF BIT(5)     // (reset=0 R/W0) Timer 1 counter-overflow interrupt flag. Set when the counter reaches the terminal count value in free- # running or modulo mode, and when zero is reached counting down in up-and-down mode. Writing a 1 # has no effect.

SFR(T1CC0L, 0xDA);        // Timer 1 Channel 0 Capture or Compare Value, Low
SFR(T1CC0H, 0xDB);        // Timer 1 Channel 0 Capture or Compare Value, High
SFR(T1CC1L, 0xDC);        // Timer 1 Channel 1 Capture or Compare Value, Low
SFR(T1CC1H, 0xDD);        // Timer 1 Channel 1 Capture or Compare Value, High
SFR(T1CC2L, 0xDE);        // Timer 1 Channel 2 Capture or Compare Value, Low
SFR(T1CC2H, 0xDF);        // Timer 1 Channel 2 Capture or Compare Value, High
SFR(T1CNTL, 0xE2);        // Timer 1 Counter Low
SFR(T1CNTH, 0xE3);        // Timer 1 Counter High
SFR(T1CTL, 0xE4);         // Timer 1 Control

// T1CTL_MODE reset=00 R/W Timer 1 mode select. The timer operating mode is selected as follows: # [1:0] 
#define MASK_T1CTL_MODE BITMASK(2, 0)
#define T1CTL_MODE_SUSPEND      (0U<<0) // Operation is suspended. 
#define T1CTL_MODE_FREE_RUNNING (1U<<0) // Free-running, repeatedly count from 0x0000 to 0xFFFF. 
#define T1CTL_MODE_MODULO       (2U<<0) // Modulo, repeatedly count from 0x0000 to T1CC0. 
#define T1CTL_MODE_UP_AND_DOWN  (3U<<0) // Up-and-down, repeatedly count from 0x0000 to T1CC0 and from T1CC0 down to 0x0000.

// T1CTL_DIV reset=00 R/W Prescaler divider value. Generates the active clock edge used to update the counter as follows: 
#define MASK_T1CTL_DIV BITMASK(2, 2)
#define T1CTL_DIV_DIV1   (0U<<2) // Tick frequency / 1 
#define T1CTL_DIV_DIV8   (1U<<2) // Tick frequency / 8 
#define T1CTL_DIV_DIV32  (2U<<2) // Tick frequency / 32 
#define T1CTL_DIV_DIV128 (3U<<2) // Tick frequency / 128




SFR(T1CCTL0, 0xE5);       // Timer 1 Channel 0 Capture or Compare Control

// T1CCTL0_CAP reset=00 R/W Channel 0 capture-mode select 
#define MASK_T1CCTL0_CAP BITMASK(2, 0)
#define T1CCTL0_CAP_NONE     (0U<<0) // No capture 
#define T1CCTL0_CAP_RISING   (1U<<0) // Capture on rising edge 
#define T1CCTL0_CAP_FALLING  (2U<<0) // Capture on falling edge 
#define T1CCTL0_CAP_ANY_EDGE (3U<<0) // Capture on all edges

#define T1CCTL0_MODE BIT(2)     // (reset=0 R/W) Mode. Select Timer 1 channel 0 capture or compare mode 

// T1CCTL0_CMP reset=000 R/W Channel 0 compare-mode select. Selects action on output when timer value equals compare value in # T1CC0 
#define MASK_T1CCTL0_CMP BITMASK(3, 3)
#define T1CCTL0_CMP_SET_ON_CMP    (0U<<3) // Set output on compare 
#define T1CCTL0_CMP_CLK_ON_CMP    (1U<<3) // Clear output on compare 
#define T1CCTL0_CMP_TOGGLE        (2U<<3) // Toggle output on compare 
#define T1CCTL0_CMP_SET_ON_CMP_UP (3U<<3) // Set output on compare-up, clear on 0 
#define T1CCTL0_CMP_CLR_ON_CMP_UP (4U<<3) // Clear output on compare-up, set on 0 
#define T1CCTL0_CMP_INIT_PIN      (7U<<3) // Initialize output pin. CMP[2:0] is not changed.

#define T1CCTL0_IM BIT(6)     // (reset=1 R/W) Channel 0 interrupt mask. Enables interrupt request when set.

#define T1CCTL0_RFIRQ BIT(7)     // (reset=0 R/W) When set, use RF interrupt for capture instead of regular capture input.



SFR(T1CCTL1, 0xE6);       // Timer 1 Channel 1 Capture or Compare Control
// T1CCTL1_CAP reset=00 R/W Channel 1 capture-mode select 
#define MASK_T1CCTL1_CAP BITMASK(2, 0)
#define T1CCTL1_CAP_NONE     (0U<<0) // No capture 
#define T1CCTL1_CAP_RISING   (1U<<0) // Capture on rising edge 
#define T1CCTL1_CAP_FALLING  (2U<<0) // Capture on falling edge 
#define T1CCTL1_CAP_ANY_EDGE (3U<<0) // Capture on all edges

#define T1CCTL1_MODE BIT(2)     // (reset=0 R/W) Mode. Select Timer 1 channel 1 capture or compare mode 

// T1CCTL1_CMP reset=000 R/W Channel 1 compare-mode select. Selects action on output when timer value equals compare value in # T1CC1. 
#define MASK_T1CCTL1_CMP BITMASK(3, 3)
#define T1CCTL1_CMP_SET_ON_CMP                (0U<<3) // Set output on compare 
#define T1CCTL1_CMP_CLK_ON_CMP                (1U<<3) // Clear output on compare 
#define T1CCTL1_CMP_TOGGLE                    (2U<<3) // Toggle output on compare 
#define T1CCTL1_CMP_SET_ON_CMP_UP             (3U<<3) // Set output on compare-up, clear on compare-down in up-and-down mode. Otherwise set output on compare, clear on 0. 
#define T1CCTL1_CMP_CLR_ON_CMP_UP             (4U<<3) // Clear output on compare-up, set on compare-down in up-and-down mode. Otherwise clear output on compare, set on 0. 
#define T1CCTL1_CMP_CLR_ON_T1CC0_SET_ON_T1CC1 (5U<<3) // Clear when equal T1CC0, set when equal T1CC1 
#define T1CCTL1_CMP_SET_ON_T1CC0_CLR_ON_T1CC1 (6U<<3) // Set when equal T1CC0, clear when equal T1CC1 
#define T1CCTL1_CMP_INIT_PIN                  (7U<<3) // Initialize output pin. CMP[2:0] is not changed.

#define T1CCTL1_IM BIT(6)     // (reset=1 R/W) Channel 1 interrupt mask. Enables interrupt request when set.

#define T1CCTL1_RFIRQ BIT(7)     // (reset=0 R/W) When set, use RF interrupt for capture instead of regular capture input.



SFR(T1CCTL2, 0xE7);       // Timer 1 Channel 2 Capture or Compare Control
// T1CCTL2_CAP reset=00 R/W Channel 2 capture-mode select 
#define MASK_T1CCTL2_CAP BITMASK(2, 0)
#define T1CCTL2_CAP_NONE     (0U<<0) // No capture 
#define T1CCTL2_CAP_RISING   (1U<<0) // Capture on rising edge 
#define T1CCTL2_CAP_FALLING  (2U<<0) // Capture on falling edge 
#define T1CCTL2_CAP_ANY_EDGE (3U<<0) // Capture on all edges

#define T1CCTL2_MODE BIT(2)     // (reset=0 R/W) Mode. Select Timer 1 channel 2 capture or compare mode 

// T1CCTL2_CMP reset=000 R/W Channel 2 compare mode select. Selects action on output when timer value equals compare value in # T1CC2. 
#define MASK_T1CCTL2_CMP BITMASK(3, 3)
#define T1CCTL2_CMP_SET_ON_CMP                (0U<<3) // Set output on compare 
#define T1CCTL2_CMP_CLK_ON_CMP                (1U<<3) // Clear output on compare 
#define T1CCTL2_CMP_TOGGLE                    (2U<<3) // Toggle output on compare 
#define T1CCTL2_CMP_SET_ON_CMP_UP             (3U<<3) // Set output on compare-up, clear on compare-down in up-and-down mode. Otherwise set output on compare, clear on 0. 
#define T1CCTL2_CMP_CLR_ON_CMP_UP             (4U<<3) // Clear output on compare-up, set on compare-down in up-and-down mode. Otherwise clear output on compare, set on 0. 
#define T1CCTL2_CMP_CLR_ON_T1CC0_SET_ON_T1CC2 (5U<<3) // Clear when equal T1CC0, set when equal T1CC2 
#define T1CCTL2_CMP_SET_ON_T1CC0_CLR_ON_T1CC2 (6U<<3) // Set when equal T1CC0, clear when equal T1CC2 
#define T1CCTL2_CMP_INIT_PIN                  (7U<<3) // Initialize output pin. CMP[2:0] is not changed.

#define T1CCTL2_IM BIT(6)     // (reset=1 R/W) Channel 2 interrupt mask. Enables interrupt request when set.

#define T1CCTL2_RFIRQ BIT(7)     // (reset=0 R/W) When set, use RF interrupt for capture instead of regular capture input.





__xdata __at(0x62A3) struct {
	/* 0x62A3 ### T1CCTL3 (0x62A3) - Timer 1 Channel 3 Capture/Compare Control */ 
	struct { 
	      uint8_t CAP                    :2,     /* Channel 3 capture-mode select
												00: No capture
												01: Capture on rising edge
												10: Capture on falling edge
												11: Capture on all edges 
											    (Reset=00) (R/W)*/ 
              MODE                   :1,     /* Select Timer 1 channel 3 capture or compare mode
												0: Capture mode
												1: Compare mode 
											    (Reset=0) (R/W)*/ 
              CMP                    :3,     /* Channel 3 compare mode select. Selects action on output when timer value equals compare value in T1CC3.
												000: Set output on compare
												001: Clear output on compare
												010: Toggle output on compare
												011: Set output on compare-up, clear on compare-down in up-and-down mode. Otherwise set output on compare, clear on 0.
												100: Clear output on compare-up, set on compare down in up-and-down mode. Otherwise clear output on compare, set on 0.
												101: Clear when equal T1CC0, set when equal T1CC3
												110: Set when equal T1CC0, clear when equal T1CC3
												111: Initialize output pin. CMP[2:0] is not changed. 
											    (Reset=000) (R/W)*/ 
              IM                     :1,     /* Channel 3 interrupt mask. Enables interrupt request when set. 
		                                        (Reset=1) (R/W)*/ 
              RFIRQ                  :1;     /* When set, use RF interrupt for capture instead of regular capture input. 
		                                        (Reset=0) (R/W)*/ 
	} t1cctl3;

	/* 0x62A4 ### T1CCTL4 (0x62A4) - Timer 1 Channel 4 Capture or Compare Control */ 
	struct { 
	      uint8_t CAP                    :2,     /* Channel 4 capture-mode select
												00: No capture
												01: Capture on rising edge
												10: Capture on falling edge
												11: Capture on all edges 
											    (Reset=00) (R/W)*/ 
              MODE                   :1,     /* Select Timer 1 channel 4 capture or compare mode
												0: Capture mode
												1: Compare mode 
											    (Reset=0) (R/W)*/ 
              CMP                    :3,     /* Channel 4 compare mode select. Selects action on output when timer value equals compare value in T1CC4.
												000: Set output on compare
												001: Clear output on compare
												010: Toggle output on compare
												011: Set output on compare-up, clear on compare down in up-and-down mode. Otherwise set output on compare, clear on 0.
												100: Clear output on compare-up, set on compare down in up-and-down mode. Otherwise clear output on compare, set on 0.
												101: Clear when equal T1CC0, set when equal T1CC4
												110: Set when equal T1CC0, clear when equal T1CC4
												111: Initialize output pin. CMP[2:0] is not changed. 
											    (Reset=000) (R/W)*/ 
              IM                     :1,     /* Channel 4 interrupt mask. Enables interrupt request when set. 
		                                        (Reset=1) (R/W)*/ 
              RFIRQ                  :1;     /* When set, use RF interrupt for capture instead of regular capture input. 
		                                        (Reset=0) (R/W)*/ 
	} t1cctl4;

	// 0x62A6 T1CC0L Timer 1 channel 0 capture or compare value low (additional XREG mapping of SFR register)
	// 0x62A7 T1CC0H Timer 1 channel 0 capture or compare value high (additional XREG mapping of SFR register)
	uint16_t t1cc0;

	// 0x62A8 T1CC1L Timer 1 channel 1 capture or compare value low (additional XREG mapping of SFR register)
	// 0x62A9 T1CC1H Timer 1 channel 1 capture or compare value high (additional XREG mapping of SFR register)
	uint16_t t1cc1;

	// 0x62AA T1CC2L Timer 1 channel 2 capture or compare value low (additional XREG mapping of SFR register)
	// 0x62AB T1CC2H Timer 1 channel 2 capture or compare value high (additional XREG mapping of SFR register)
	uint16_t t1cc2;
	
	/* 0x62AC ### T1CC3L (0x62AC) - Timer 1 Channel 3 Capture or Compare Value, Low */ 
	/* 0x62AD ### T1CC3H (0x62AD) - Timer 1 Channel 3 Capture or Compare Value, High */ 
	uint16_t t1cc3;

	/* Timer 1 channel 3 capture or compare value low-order byte. Data written to this register is stored in a buffer but not written to T1CC3[7:0] until, and at the same time as, a later write to T1CC3H takes effect.  (Reset=0x00) (R/W)*/ 
	// __xdata __at(0x62AC) uint8_t t1cc3l;

	/* Timer 1 channel 3 capture or compare value high-order byte. Writing to this register when T1CCTL3.MODE = 1 (compare mode) causes the T1CC3[15:0] update to the written value to be delayed until T1CNT = 0x0000.  (Reset=0x00) (R/W)*/ 
	// __xdata __at(0x62AD) uint8_t t1cc3h;

	/* 0x62AE ### T1CC4L (0x62AE) - Timer 1 Channel 4 Capture or Compare Value, Low */ 
	/* Timer 1 channel 4 capture or compare value low-order byte. Data written to this register is stored in a buffer but not written to T1CC4[7:0] until, and at the same time as, a later write to T1CC4H takes effect.  (Reset=0x00) (R/W)*/ 
	// __xdata __at(0x62AE) uint8_t t1cc4l;

	/* 0x62AF ### T1CC4H (0x62AF) - Timer 1 Channel 4 Capture or Compare Value, High */ 
	/* Timer 1 channel 4 capture or compare value high-order byte. Writing to this register when T1CCTL4.MODE = 1 (compare mode) causes the T1CC4[15:0] update to the written value to be delayed until T1CNT = 0x0000.  (Reset=0x00) (R/W)*/ 
	// __xdata __at(0x62AF) uint8_t t1cc4h;
} TIMER1;
