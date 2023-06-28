// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <stdint.h>

__xdata __at(0x62C0) struct {
	/* 0x62C0 ### OPAMPC (0x62C0) - Operational Amplifier Control */ 
	struct { 
	      uint8_t EN                     :1,     /* Operational amplifier enable 
                                               (Reset=0) (R/W)*/ 
             CAL                    :1,     /* Start calibration. Calibration only starts if OPAMPC.EN is 1. 
	                                        (Reset=0) (W1/R0)*/ 
                                    :6;     /* Reserved 
							                (Reset=000000) (R0)*/ 
	} OPAMPC;

	/* 0x62C1 ### OPAMPS (0x62C1) - Operational Amplifier Status */ 
	uint8_t CAL_BUSY;                            /* Calibration in progress 
                                               (Reset=0) (R)*/ 
} OPAMP;


/* 0x62D0 ### CMPCTL (0x62D0) - Analog Comparator Control and Status */ 
__xdata __at(0x62C0) struct { 
      uint8_t OUTPUT                 :1,     /* Comparator output 
                                           (Reset=0) (R)*/ 
         EN                     :1,     /* Comparator enable 
                                        (Reset=0) (R/W)*/ 
                                :6;     /* Reserved 
						                (Reset=000000) (R0)*/ 
} CMPCTL;
