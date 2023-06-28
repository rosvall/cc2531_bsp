// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <stdint.h>

enum {
	CHIPID_CC2530 = 0xA5,
	CHIPID_CC2531 = 0xB5,
	CHIPID_CC2533 = 0x95,
	CHIPID_CC2540 = 0x8D,
	CHIPID_CC2541 = 0x41,
};

const __xdata __at(0x6249) struct {
	/* 0x6249 ### CHVER (0x6249) - Chip Version */ 
	uint8_t ver;              /* Chip revision number (R)*/ 

	/* 0x624A ### CHIPID (0x624A) - Chip ID */ 
	uint8_t id;             /* Chip identification number.
								CC2530: 0xA5
								CC2531: 0xB5
								CC2533: 0x95
								CC2540: 0x8D
								CC2541: 0x41  (R)*/ 
} CHIPID;

const __xdata __at(0x6276) struct {
	/* 0x6276 ### CHIPINFO0 (0x6276) - Chip Information Byte 0 */ 
	uint8_t                    :2,     /* Reserved. Always 00 
                                          (Reset=00) (R0)*/ 
	                           :1,     /* Reserved. Always 1 
							              (Reset=1) (R1)*/ 
          usb                  :1,     /* 1 if chip has USB, 0 otherwise dependent  (R)*/ 
          flashsize            :3,     /* Flash Size.
										001 - 32 KB,
										010 - 64 KB,
										011 - 128 KB (for CC2533: 011 - 96 KB), 
										100 - 256 KB  (R)*/ 
                               :1;     /* Reserved. Always 0. (R)*/ 

	/* 0x6277 ### CHIPINFO1 (0x6277) - Chip Information Byte 1 */ 
	uint8_t sramsize           :3,     /* SRAM size in KB minus 1.
										For example, a 4-KB device has this field set to 011.
										Add 1 to the number to get the number of KB available.  (R)*/ 
                               :5;     /* Reserved. dependent  (R)*/ 
} CHIPINFO;


#define chipinfo_read_flash_size_kb() (16u<<(CHIPINFO.flashsize))
#define chipinfo_read_sram_size_kb() (CHIPINFO.sramsize + 1)
