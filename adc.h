// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

//  R/W/H0    ADC interrupt flag. Set to 1 when ADC interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TCON_ADCIF,    0x88, 5);

//  R/W    ADC interrupt enable # 0: Interrupt disabled # 1: Interrupt enabled
SBIT(IEN0_ADCIE,    0xA8, 1);

// ADC Control 1
SFR(ADCCON1,        0xB4);
// ADCCON1_RCTRL reset=00 R/W Controls the 16-bit random-number generator (Chapter 14). When 01 is written, the setting # automatically returns to 00 when the operation has completed. 
#define MASK_ADCCON1_RCTRL BITMASK(2, 2)
#define ADCCON1_RCTRL_NORMAL (0u << 2) // Normal operation. (13x unrolling) 
#define ADCCON1_RCTRL_ONCE   (1u << 2) // Clock the LFSR once (13x unrolling) 
#define ADCCON1_RCTRL_STOP   (3u << 2) // Stopped. Random-number generator is turned off.

// ADCCON1_STSEL reset=11 R/W Start select. Selects the event that starts a new conversion sequence 
#define MASK_ADCCON1_STSEL BITMASK(2, 4)
#define ADCCON1_STSEL_EXT_P2_0   (0u << 4) // External trigger on P2.0 pin 
#define ADCCON1_STSEL_FULL_SPEED (1u << 4) // Full speed. Do not wait for triggers 
#define ADCCON1_STSEL_TIM1CH0    (2u << 4) // Timer 1 channel 0 compare event 
#define ADCCON1_STSEL_ST_BIT     (3u << 4) // ADCCON1.ST = 1

#define ADCCON1_ST  BIT(6)     // (reset=0 R/W1/H0) Start conversion. Read as 1 until conversion has completed
#define ADCCON1_EOC BIT(7)     // (reset=0 R/H0) End of conversion. Cleared when ADCH has been read. If a new conversion is completed # before the previous data has been read, the EOC bit remains high. 


// ADC Control 2
SFR(ADCCON2,        0xB5);
// ADCCON2_SCH reset=0000 R/W Sequence channel select. Selects the end of the sequence. A sequence can either be from AIN0 # to AIN7 (SCH <= 7) or from differential input AIN0-AIN1 to AIN6-AIN7 (8 <= SCH <= 11). For other # settings, only one conversion is performed. # When read, these bits indicate the channel number on which a conversion is ongoing. 
#define MASK_ADCCON2_SCH BITMASK(4, 0)
#define ADCCON2_SCH_AIN0            (0u << 0) // AIN0 
#define ADCCON2_SCH_AIN1            (1u << 0) // AIN1 
#define ADCCON2_SCH_AIN2            (2u << 0) // AIN2 
#define ADCCON2_SCH_AIN3            (3u << 0) // AIN3 
#define ADCCON2_SCH_AIN4            (4u << 0) // AIN4 
#define ADCCON2_SCH_AIN5            (5u << 0) // AIN5 
#define ADCCON2_SCH_AIN6            (6u << 0) // AIN6 
#define ADCCON2_SCH_AIN7            (7u << 0) // AIN7 
#define ADCCON2_SCH_AIN0_MINUS_AIN1 (8u << 0) // AIN0-AIN1 
#define ADCCON2_SCH_AIN2_MINUS_AIN3 (9u << 0) // AIN2-AIN3 
#define ADCCON2_SCH_AIN4_MINUS_AIN5 (10u << 0) // AIN4-AIN5 
#define ADCCON2_SCH_AIN6_MINUS_AIN7 (11u << 0) // AIN6-AIN7 
#define ADCCON2_SCH_GND             (12u << 0) // GND 
#define ADCCON2_SCH_TEMP_SENSOR     (14u << 0) // Temperature sensor 
#define ADCCON2_SCH_VDD_DIV_3       (15u << 0) // VDD / 3

// ADCCON2_SDIV reset=01 R/W Sets the decimation rate for channels included in the sequence of conversions. The decimation # rate also determines the resolution and time required to complete a conversion. 
#define MASK_ADCCON2_SDIV BITMASK(2, 4)
#define ADCCON2_SDIV_DIV64  (0u << 4) // 64 decimation rate (7 bits ENOB setting) 
#define ADCCON2_SDIV_DIV128 (1u << 4) // 128 decimation rate (9 bits ENOB setting) 
#define ADCCON2_SDIV_DIV256 (2u << 4) // 256 decimation rate (10 bits ENOB setting) 
#define ADCCON2_SDIV_DIV512 (3u << 4) // 512 decimation rate (12 bits ENOB setting)

// ADCCON2_SREF reset=00 R/W Selects reference voltage used for the sequence of conversions 
#define MASK_ADCCON2_SREF BITMASK(2, 6)
#define ADCCON2_SREF_INTERNAL           (0u << 6) // Internal reference 
#define ADCCON2_SREF_EXT_AIN7           (1u << 6) // External reference on AIN7 pin 
#define ADCCON2_SREF_EXT_AVDD5          (2u << 6) // AVDD5 pin 
#define ADCCON2_SREF_EXT_DIFF_AIN6_AIN7 (3u << 6) // External reference on AIN6-AIN7 differential input



// ADC Control 3
SFR(ADCCON3,        0xB6);
// ADCCON3_ECH reset=0000 R/W Single channel select. Selects the channel number of the single conversion that is triggered by # writing to ADCCON3. 
#define MASK_ADCCON3_ECH BITMASK(4, 0)
#define ADCCON3_ECH_AIN0            (0u << 0) // AIN0 
#define ADCCON3_ECH_AIN1            (1u << 0) // AIN1 
#define ADCCON3_ECH_AIN2            (2u << 0) // AIN2 
#define ADCCON3_ECH_AIN3            (3u << 0) // AIN3 
#define ADCCON3_ECH_AIN4            (4u << 0) // AIN4 
#define ADCCON3_ECH_AIN5            (5u << 0) // AIN5 
#define ADCCON3_ECH_AIN6            (6u << 0) // AIN6 
#define ADCCON3_ECH_AIN7            (7u << 0) // AIN7 
#define ADCCON3_ECH_AIN0_MINUS_AIN1 (8u << 0) // AIN0-AIN1 
#define ADCCON3_ECH_AIN2_MINUS_AIN3 (9u << 0) // AIN2-AIN3 
#define ADCCON3_ECH_AIN4_MINUS_AIN5 (10u << 0) // AIN4-AIN5 
#define ADCCON3_ECH_AIN6_MINUS_AIN7 (11u << 0) // AIN6-AIN7 
#define ADCCON3_ECH_GND             (12u << 0) // GND 
#define ADCCON3_ECH_TEMP_SENSOR     (14u << 0) // Temperature sensor 
#define ADCCON3_ECH_VDD_DIV_3       (15u << 0) // VDD / 3

// ADCCON3_EDIV reset=00 R/W Sets the decimation rate used for the extra conversion. The decimation rate also determines the # resolution and the time required to complete the conversion. 
#define MASK_ADCCON3_EDIV BITMASK(2, 4)
#define ADCCON3_EDIV_DIV64  (0u << 4) // 64 decimation rate (7 bits ENOB) 
#define ADCCON3_EDIV_DIV128 (1u << 4) // 128 decimation rate (9 bits ENOB) 
#define ADCCON3_EDIV_DIV256 (2u << 4) // 256 decimation rate (10 bits ENOB) 
#define ADCCON3_EDIV_DIV512 (3u << 4) // 512 decimation rate (12 bits ENOB)

// ADCCON3_EREF reset=00 R/W Selects reference voltage used for the extra conversion 
#define MASK_ADCCON3_EREF BITMASK(2, 6)
#define ADCCON3_EREF_INTERNAL           (0u << 6) // Internal reference 
#define ADCCON3_EREF_EXT_AIN7           (1u << 6) // External reference on AIN7 pin 
#define ADCCON3_EREF_EXT_AVDD5          (2u << 6) // AVDD5 pin 
#define ADCCON3_EREF_EXT_DIFF_AIN6_AIN7 (3u << 6) // External reference on AIN6-AIN7 differential input


// ADC Data, Low
SFR(ADCL,           0xBA);

// ADC Data, High
SFR(ADCH,           0xBB);


// Analog Peripheral I/O Configuration
SFR(APCFG,          0xF2);
// reset=0x00 R/W Analog Perpheral I/O configuration . APCFG[7:0] select P0.7-P0.0 as analog I/O. 
#define APCFG_APCFG0 BIT(0)
#define APCFG_APCFG1 BIT(1)
#define APCFG_APCFG2 BIT(2)
#define APCFG_APCFG3 BIT(3)
#define APCFG_APCFG4 BIT(4)
#define APCFG_APCFG5 BIT(5)
#define APCFG_APCFG6 BIT(6)
#define APCFG_APCFG7 BIT(7)
