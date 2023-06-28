// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <stdint.h>

__xdata __at(0x62B0) struct {

	/* 0x62B0 ### STCC (0x62B0) - Sleep Timer Capture Control */ 
	struct {
		uint8_t PIN                    :3,     /* Pin select.
											Valid settings are
											0-7 when PORT[1:0] is 0 or 1,
											0-5 when PORT[1:0] is 2.
											Capture is disabled when an invalid setting is selected. 
										    (Reset=111)*/ 
		  PORT                   :2,     /* Port select.
											Valid settings are 0-2.
											Capture is disabled when set to 3, that is, an invalid setting is selected. 
										    (Reset=11) (R)*/ 
		                         :3;     /* Reserved 
							                (Reset=000) (R0)*/ 
	} STCC;

	/* 0x62B1 ### STCS (0x62B1) - Sleep Timer Capture Status */ 
	struct { 
		uint8_t VALID                  :1,     /* Capture valid flag.
											Set to 1 when capture value in STCV has been updated.
											Clear explicitly to allow new capture. 
										    (Reset=0) (R/W0)*/ 
		                          :7;     /* Reserved 
							                (Reset=0000000) (R0)*/ 
	} STCS;

	/* 0x62B2 ### STCV0 (0x62B2) - Sleep Timer Capture Value Byte 0 */ 
	uint8_t STCV0;              /* Bits [7:0] of Sleep Timer capture value 
                              (Reset=0x00) (R)*/ 

	/* 0x62B3 ### STCV1 (0x62B3) - Sleep Timer Capture Value Byte 1 */ 
	uint8_t STCV1;              /* Bits [15:8] of Sleep Timer capture value 
                              (Reset=0x00) (R)*/ 

	/* 0x62B4 ### STCV2 (0x62B4) - Sleep Timer Capture Value Byte 2 */ 
	uint8_t STCV2;              /* Bits [23:16] of Sleep Timer capture value 
                              (Reset=0x00) (R)*/ 

} STC;
