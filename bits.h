// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once


#define ADDR_H(addr) (((uint16_t)addr) >> 8)
#define ADDR_L(addr) (((uint16_t)addr) & 0xff)

#define SWAP16(_n)   (((uint16_t)(_n) >> 8) | ((uint16_t)(_n) << 8))

#define BIT(_n) (1U << (_n))

#define BITMASK(_sz, _offs) (((1U<<(_sz))-1U)<<(_offs))

#define __reserved_byte__  uint8_t :8


