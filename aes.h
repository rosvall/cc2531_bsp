// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

//  R/W    AES encryption and decryption interrupt enable # 0: Interrupt disabled # 1: Interrupt enabled
SBIT(IEN0_ENCIE, 0xA8, 4);

//  R/W    AES interrupt. ENC has two interrupt flags, ENCIF_1 and ENCIF_0. Setting one of # these flags requests interrupt service. Both flags are set when the AES coprocessor # requests the interrupt. # 0: Interrupt not pending # 1: Interrupt pending
SBIT(S0CON_ENCIF_0, 0x98, 0);

//  R/W    AES interrupt. ENC has two interrupt flags, ENCIF_1 and ENCIF_0. Setting one of # these flags requests interrupt service. Both flags are set when the AES coprocessor # requests the interrupt. # 0: Interrupt not pending # 1: Interrupt pending
SBIT(S0CON_ENCIF_1, 0x98, 1);

// Encryption Input Data
SFR(ENCDI, 0xB1);

// Encryption Output Data
SFR(ENCDO, 0xB2);

// Encryption Control and Status
SFR(ENCCS, 0xB3);
#define ENCCS_ST BIT(0)     // (reset=0 R/W1) Start processing command set by CMD. Must be issued for each command or 128-bit block of data. H0 # Cleared by hardware.

// ENCCS_CMD reset=0 R/W Command to be performed when a 1 is written to ST 
#define MASK_ENCCS_CMD BITMASK(2, 1)
#define ENCCS_CMD_ENCRYPT_BLOCK (0U<<1) // Encrypt block 
#define ENCCS_CMD_DECRYPT_BLOCK (1U<<1) // Decrypt block 
#define ENCCS_CMD_LOAD_KEY      (2U<<1) // Load key 
#define ENCCS_CMD_LOAD_IV_NONCE (3U<<1) // Load IV/nonce

#define ENCCS_RDY BIT(3)     // (reset=1 R) Encryption or decryption ready status 

// ENCCS_MODE reset=000 R/W Encryption/decryption mode 
#define MASK_ENCCS_MODE BITMASK(3, 4)
#define ENCCS_MODE_CBC     (0U<<4) // CBC 
#define ENCCS_MODE_CFB     (1U<<4) // CFB 
#define ENCCS_MODE_OFB     (2U<<4) // OFB 
#define ENCCS_MODE_CTR     (3U<<4) // CTR 
#define ENCCS_MODE_ECB     (4U<<4) // ECB 
#define ENCCS_MODE_CBC_MAC (5U<<4) // CBC MAC 
