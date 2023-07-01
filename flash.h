// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>
#include "bits.h"

// Flash Bank Map
SFR(FMAP, 0x9F);

/* Page erase.
	Erase the page that is given by FADDRH[7 (CC2530, CC2531, CC2540, and CC2541) or FADDRH[6 (CC2533).
	The ERASE bit stays at 1 until the erase completes.
	The clearing of this bit indicates that the erase has completed successfully or aborted.
	Setting ERASE to 1 when WRITE is 1 has no effect. 
    (Reset=0) (R/W1/H0)*/ 
#define FLASH_CTL_ERASE BIT(0)

/* Start writing word at location given by FADDRH:FADDRL.
	The WRITE bit stays at 1 until the write completes.
	The clearing of this bit indicates that the erase has completed, that is, it has timed out or aborted.
	If ERASE is also set to 1, a page erase of the whole page addressed by FADDRH[7 is performed before the write.
	Setting WRITE to 1 when ERASE is 1 has no effect. 
    (Reset=0) (R/W1/H0)*/ 
#define FLASH_CTL_WRITE BIT(1)

/* Cache mode
	00: Cache disabled
	01: Cache enabled
	10: Cache enabled, prefetch mode
	11: Cache enabled, real-time mode
	Cache mode. Disabling the cache increases the power consumption and reduces performance.
	Prefetching, for most applications, improves performance by up to 33% at the expense of potentially increased power consumption.
	Real-time mode provides predictable flash-read access time; the execution time is equal to that in cache-disabled mode, but the power consumption is lower.
	Note: The value read always represents the current cache mode.
	Writing a new cache mode starts a cache mode-change request that may take several clock cycles to complete.
	Writing to this register is ignored if there is a current cache-change request in progress. 
    (Reset=01) (R/W)*/ 

enum flash_fctl_cache_mode {
	FLASH_CTL_CACHE_MODE_DISABLED = (0u<<2),
	FLASH_CTL_CACHE_MODE_ENABLED  = (1u<<2),
	FLASH_CTL_CACHE_MODE_PREFETCH = (2u<<2),
	FLASH_CTL_CACHE_MODE_REALTIME = (3u<<2),
};

/* Abort status. This bit is set when a write operation or page erase is aborted.
	An operation is aborted when the page accessed is locked.
	The abort bit is cleared when a write or page erase is started. 
    (Reset=0) (R/H0)*/ 
#define FLASH_CTL_ABORT BIT(5)

/* Write buffer-full status.
	This flag is set when 4 bytes have been written to FWDATA during flash write.
	The write buffer is then full and does not accept more data; that is, writes to FWDATA are ignored when the FULL flag is set.
	The FULL flag is cleared when the write buffer again is ready to receive 4 more bytes.
	This flag is only needed when the CPU is used to write to the flash.
	0: Write buffer can accept more data.
	1: Write buffer full  (R/H0)*/ 
#define FLASH_CTL_FULL BIT(6)

/* Indicates that write or erase is in operation.
	This flag is set when the WRITE or ERASE bit is set.
	0: No write or erase operation active
	1: Write or erase operation activated 
    (Reset=0) (R)*/ 
#define FLASH_CTL_BUSY BIT(7)

__xdata __at(0x6270) struct {
	/* 0x6270 ### FCTL (0x6270) - Flash Control */ 
	uint8_t ctl;

	// Flash address (in units of 32 bit words!)
	union {
		struct {
			/* 0x6271 ### FADDRL (0x6271) - Flash-Address Low Byte */ 
			uint8_t addrl;             /* Low byte of flash word address  (Reset=0x00) (R/W)*/ 

			/* 0x6272 ### FADDRH (0x6272) - Flash-Address High Byte */ 
			uint8_t addrh;             /* Page address and high byte of flash word address Bits [7:1] (CC2530, CC2531, CC2540, and CC2541) or bits [6:0] (CC2533) select which page to access.  (Reset=0x00) (R/W)*/ 
		};
		uint16_t addr;
	};

	/* 0x6273 ### FWDATA (0x6273) - Flash Write Data */ 
	uint8_t wdata;             /* Flash write data. This register can only be written to when FCTL.WRITE is 1.  (Reset=0x00) (R0/W)*/ 

} FLASH;

#define FLASH_PAGE_SIZE 2048u
#define FLASH_WORD_SIZE 4u
