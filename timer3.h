// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>

SBIT(IEN1_T3IE, 0xB8, 3); // R/W Timer 3 interrupt enable
SBIT(IRCON_T3IF, 0xC0, 3); // R/W/H0 Timer 3 interrupt flag. Set to 1 when Timer 3 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TIMIF_T3OVFIF, 0xD8, 0); // R/W0 Timer 3 overflow interrupt flag
SBIT(TIMIF_T3CH0IF, 0xD8, 1); // R/W0 Timer 3 channel 0 interrupt flag
SBIT(TIMIF_T3CH1IF, 0xD8, 2); // R/W0 Timer 3 channel 1 interrupt flag

SFR(T3CNT, 0xCA); // Timer 3 Counter
SFR(T3CTL, 0xCB); // Timer 3 Control

// T3CTL_MODE reset=00 R/W Timer 3 mode. Select the mode as follows: 
#define MASK_T3CTL_MODE BITMASK(2, 0)
#define T3CTL_MODE_FREE_RUNNING (0u << 0) // Free-running, repeatedly count from 0x00 to 0xFF 
#define T3CTL_MODE_DOWN         (1u << 0) // Down, count from T3CC0 to 0x00 
#define T3CTL_MODE_MODULO       (2u << 0) // Modulo, repeatedly count from 0x00 to T3CC0 
#define T3CTL_MODE_UP_AND_DOWN  (3u << 0) // Up-and-down, repeatedly count from 0x00 to T3CC0 and down to 0x00

#define T3CTL_CLR   BIT(2)     // (reset=0 R0 (W1) Clear counter. Writing a 1 to CLR resets the counter to 0x00 and initializes all output pins of # associated channels. Always read as 0.
#define T3CTL_OVFIM BIT(3)     // (reset=1 R/W) Overflow interrupt mask 
#define T3CTL_START BIT(4)     // (reset=0 R/W) Start timer. Normal operation when set, suspended when cleared

// T3CTL_DIV reset=000 R/W Prescaler divider value. Generates the active clock edge used to clock the timer from # CLKCONCMD.TICKSPD as follows: 
#define MASK_T3CTL_DIV BITMASK(3, 5)
#define T3CTL_DIV_DIV1   (0u << 5) // Tick frequency / 1 
#define T3CTL_DIV_DIV2   (1u << 5) // Tick frequency / 2 
#define T3CTL_DIV_DIV4   (2u << 5) // Tick frequency / 4 
#define T3CTL_DIV_DIV8   (3u << 5) // Tick frequency / 8 
#define T3CTL_DIV_DIV6   (4u << 5) // Tick frequency 1 6 
#define T3CTL_DIV_DIV32  (5u << 5) // Tick frequency / 32 
#define T3CTL_DIV_DIV64  (6u << 5) // Tick frequency / 64 
#define T3CTL_DIV_DIV128 (7u << 5) // Tick frequency / 128



SFR(T3CCTL0, 0xCC); // Timer 3 Channel 0 Capture or Compare Control
// ### T3CCTL0 (0xCC) - Timer 3 Channel 0 Capture or Compare Control

// T3CCTL0_CAP reset=00 R/W Capture mode select 
#define MASK_T3CCTL0_CAP BITMASK(2, 0)
#define T3CCTL0_CAP_NONE     (0u << 0) // No capture 
#define T3CCTL0_CAP_RISING   (1u << 0) // Capture on rising edge 
#define T3CCTL0_CAP_FALLING  (2u << 0) // Capture on falling edge 
#define T3CCTL0_CAP_ANY_EDGE (3u << 0) // Capture on both edges

#define T3CCTL0_MODE BIT(2)     // (reset=0 R/W) Mode. Select Timer 3 channel 0 mode 

// T3CCTL0_CMP reset=000 R/W Channel 0 compare output mode select. Specified action occurs on output when timer value # equals compare value in T3CC0. 
#define MASK_T3CCTL0_CMP BITMASK(3, 3)
#define T3CCTL0_CMP_SET_ON_CMP             (0u << 3) // Set output on compare 
#define T3CCTL0_CMP_CLK_ON_CMP             (1u << 3) // Clear output on compare 
#define T3CCTL0_CMP_TOGGLE                 (2u << 3) // Toggle output on compare 
#define T3CCTL0_CMP_SET_ON_CMP_UP          (3u << 3) // Set output on compare-up, clear on 0 
#define T3CCTL0_CMP_CLR_ON_CMP_UP          (4u << 3) // Clear output on compare-up, set on 0 
#define T3CCTL0_CMP_SET_ON_CMP_CLEAR_ON_FF (5u << 3) // Set output on compare, clear on 0xFF 
#define T3CCTL0_CMP_CLR_ON_CMP_SET_ON_0    (6u << 3) // Clear output on compare, set on 0x00 
#define T3CCTL0_CMP_INIT_PIN               (7u << 3) // Initialize output pin. CMP[2:0] is not changed.

#define T3CCTL0_IM BIT(6)     // (reset=1 R/W) Channel 0 interrupt mask 



SFR(T3CC0, 0xCD); // Timer 3 Channel 0 Capture or Compare Value

SFR(T3CCTL1, 0xCE); // Timer 3 Channel 1 Capture or Compare Control

// T3CCTL1_CAP reset=00 R/W Capture mode select 
#define MASK_T3CCTL1_CAP BITMASK(2, 0)
#define T3CCTL1_CAP_NONE     (0u << 0) // No capture 
#define T3CCTL1_CAP_RISING   (1u << 0) // Capture on rising edge 
#define T3CCTL1_CAP_FALLING  (2u << 0) // Capture on falling edge 
#define T3CCTL1_CAP_ANY_EDGE (3u << 0) // Capture on both edges

#define T3CCTL1_MODE BIT(2)     // (reset=0 R/W) Mode. Select Timer 3 channel 1 mode 

// T3CCTL1_CMP reset=000 R/W Channel 1 compare output-mode select. Specified action on output when timer value equals # compare value in T3CC1 
#define MASK_T3CCTL1_CMP BITMASK(3, 3)
#define T3CCTL1_CMP_SET_ON_CMP             (0u << 3) // Set output on compare 
#define T3CCTL1_CMP_CLK_ON_CMP             (1u << 3) // Clear output on compare 
#define T3CCTL1_CMP_TOGGLE                 (2u << 3) // Toggle output on compare 
#define T3CCTL1_CMP_SET_ON_CMP_UP          (3u << 3) // Set on compare-up, clear on compare-down in up-and-down mode. Otherwise, set output on compare, clear on 0. 
#define T3CCTL1_CMP_CLR_ON_CMP_UP          (4u << 3) // Clear output on compare-up, set on compare-down in up-and-down mode. Otherwise clear output on compare, set on 0. 
#define T3CCTL1_CMP_SET_ON_CMP_CLEAR_ON_FF (5u << 3) // Set output on compare, clear on 0xFF 
#define T3CCTL1_CMP_CLR_ON_CMP_SET_ON_0    (6u << 3) // Clear output on compare, set on 0x00 
#define T3CCTL1_CMP_INIT_PIN               (7u << 3) // Initialize output pin. CMP[2:0] is not changed

#define T3CCTL1_IM BIT(6) // (reset=1 R/W) Channel 1 interrupt mask 


SFR(T3CC1, 0xCF); // Timer 3 Channel 1 Capture or Compare Value

