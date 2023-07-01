// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "chipinfo.h"

// Memory Page Select.
// Sets the high byte of the address for __idata accesses, i.e. the instructions movx @rn,a and movx a,@rn.
SFR(MPAGE, 0x93);

// MEMCTR (0xC7) - Memory Arbiter Control XDATA bank select.
SFR(MEMCTR, 0xC7);
// Controls which code bank of the physical flash memory is
// mapped into the XDATA region (0x8000-0xFFFF).
// When set to 0, the root bank is mapped in.
// Valid settings depend on the flash size for the device.
// Writing an invalid setting is ignored, that is, no update to XBANK[2:0] is performed.
// 32-KB version: 0 only (that is, the root bank is always mapped in.)
// 64-KB version: 0-1
// 96-KB version: 0-2
// 128-KB version: 0-3
// 256-KB version: 0-7
#define MEMCTR_XBANK_MAX 7
#define MEMCTR_XBANK__MASK BITMASK(3, 0)

// XDATA map to code. (reset=0 R/W) 
// When this bit is set, the SRAM XDATA region, from 0x0000
// through (SRAM_SIZE - 1), is mapped into the CODE region from 0x8000 through
// (0x8000 + SRAM_SIZE - 1). This enables execution of program code from RAM.
#define MEMCTR_XMAP BIT(3)

#define XBANK_SIZE 0x8000u
#define FLASH_MAPPING_IN_XDATA 0x8000u
#define SFR_MAPPING_IN_XDATA 0x7000u

// This assumes MEMCTR is set correctly
#define CODE_TO_XDATA(_code_addr)                                              \
	(void __xdata *)(((uint16_t)(_code_addr)) | FLASH_MAPPING_IN_XDATA)

#define SFR_TO_XDATA(_sfr_name)                                                \
	((__xdata uint8_t *)(SFR_MAPPING_IN_XDATA + SFR_ADDR_##_sfr_name))

inline const void __xdata *
mmap_code_to_xdata(const void __code * addr)
{
	MEMCTR &= ~MEMCTR_XBANK__MASK;
	uint8_t bank = (uint16_t)addr / XBANK_SIZE;
	MEMCTR |= bank;
	return (const void __xdata *)((uint16_t)addr | FLASH_MAPPING_IN_XDATA);
}

// On the cc2531, the 8051 data space is at the top of sram in xdata space
inline void __xdata *
mmap_idata_to_xdata(void __idata * addr)
{
	uint8_t h = (CHIPINFO.sramsize << 2) | 0x3;
	return (void __xdata *)((uint16_t)addr | ((uint16_t)h << 8));
}
