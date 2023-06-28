// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <stdint.h>

/* 0x6260 ### DBGDATA (0x6260) - Debug Data */ 
__xdata __at(0x6260) uint8_t DBGDATA;            /* Debug data from BURST_WRITE command
												This register is updated each time a new byte has been transferred to the debug interface using the BURST_WRITE command.
													A DBG_BW DMA trigger is generated when this byte is updated.
													This allows the DMA controller to fetch the data. 
												    (Reset=0) (R)*/ 
