// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>

SFR(PCON,           0x87); // Power Mode Control
// (reset=0 R0/W) Power mode control. Writing 1 to this bit forces the device to enter the power mode
// H0 set by SLEEPCMD.MODE (note that MODE = 0x00 AND IDLE = 1 stops the CPU core activity).
// This bit is always read as 0.
// All enabled interrupts clear this bit when active, and the device re-enters active mode.
#define PCON_IDLE BIT(0)

SFR(SLEEPCMD,       0xBE); // Sleep-Mode Control Command
// Reserved. Always write as 1
#define SLEEPCMD_RES1 BIT(2)
// ### SLEEPCMD (0xBE) - Sleep-Mode Control Command
// SLEEPCMD_MODE:2, % SIZE=2% 1:0 MODE[1:0] 00 R/W Power-mode setting 
#define MASK_SLEEPCMD_MODE BITMASK(2, 0)

// Active or Idle mode 
#define SLEEPCMD_MODE_ACTIVE ((0U<<0) | SLEEPCMD_RES1)
// Power mode 1 (PM1) 
#define SLEEPCMD_MODE_PM1    ((1U<<0) | SLEEPCMD_RES1)
// Power mode 2 (PM2) 
#define SLEEPCMD_MODE_PM2    ((2U<<0) | SLEEPCMD_RES1)
// Power mode 3 (PM3)
#define SLEEPCMD_MODE_PM3    ((3U<<0) | SLEEPCMD_RES1)

// (reset=0 R/W) Disable 32-kHz RC oscillator calibration 
#define SLEEPCMD_OSC32K_CALDIS (BIT(7) | SLEEPCMD_RES1)



SFR(SLEEPSTA,       0x9D); // Sleep-Mode Control Status
#define SLEEPSTA_CLK32K BIT(0) // (reset=0 R) The 32-kHz clock signal (synchronized to the system clock)

// SLEEPSTA_RST (R) Status bit indicating the cause of the last reset. If there are multiple resets, the register only contains the last event. 
#define SLEEPSTA_RST__SHIFT 3
#define SLEEPSTA_RST__BITS 2
#define SLEEPSTA_RST__MASK BITMASK(SLEEPSTA_RST__BITS, SLEEPSTA_RST__SHIFT)

// (reset=0 R( 32-kHz) RC oscillator calibration status # SLEEPSTA.OSC32K_CALDIS shows the current status of disabling of the 32-kHz # RC calibration. The bit is not set to the same value as # SLEEPCMD.OSC32K_CALDIS before the chip has been run on the 32-kHz RC # oscillator.
#define SLEEPSTA_OSC32K_CALDIS BIT(7)

enum sleepsta_rst {
	SLEEPSTA_RST_POWER      = 0u, // Power-on reset and brownout detection 
	SLEEPSTA_RST_EXT_RESET  = 1u, // External reset 
	SLEEPSTA_RST_WATCHDOG   = 2u, // Watchdog Timer reset 
	SLEEPSTA_RST_CLOCK_LOSS = 3u, // Clock loss reset
};

// Power-Down Signal Mux
SFR(PMUX,           0xAE);
// ### PMUX (0xAE) - Power-Down Signal Mux
// DREGSTAPIN reset=000 R/W Digital Voltage Regulator Status Pin. Selects which P1 pin is to be used to output # the DREGSTA signal.
#define MASK_PMUX_DREGSTAPIN BITMASK(3, 0)
#define PMUX_DREGSTAPIN0 BIT(0)
#define PMUX_DREGSTAPIN1 BIT(1)
#define PMUX_DREGSTAPIN2 BIT(2)

#define PMUX_DREGSTA BIT(3) // (reset=0 R/W) Digital Voltage Regulator Status. When this bit is set, the status of the digital voltage regulator # is output on one of the P1 pins. DREGSTAPIN selects the pin. When DREGSTA is set, all other # configurations for the selected pin are overridden. The selected pin outputs 1 when the 1.8-V # on-chip digital voltage regulator is powered up (chip has regulated power). The selected pin # outputs 0 when the 1.8-V on-chip digital voltage regulator is powered down.

// CKOPIN reset=000 R/W Clock Out Pin. Selects which P0 pin is to be used to output the selected 32-kHz clock.
#define MASK_PMUX_CKOPIN BITMASK(3, 4)

#define PMUX_CKOEN   BIT(7) // (reset=0 R/W) Clock Out Enable. When this bit is set, the selected 32-kHz clock is output on one of the P0 # pins. CKOPIN selects the pin to use. This overrides all other configurations for the selected # pin. The clock is output in all power modes; however, in PM3 the clock stops (see PM3 in # Chapter 4).
