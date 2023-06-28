// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>

__xdata __at(0x7800) struct {
	uint8_t _reserved_7800[12];
	uint64_t ieee_addr;
	uint8_t _reserved_7814[18];
	uint8_t adc_cal_h;
	uint8_t adc_cal_l;
} INFOPAGE;
