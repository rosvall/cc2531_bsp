// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>
#include "bits.h"

//  R/W    DMA transfer interrupt enable # 0: Interrupt disabled # 1: Interrupt enabled
SBIT(IEN1_DMAIE, 0xB8, 0);

//  R/W    DMA-complete interrupt flag # 0: Interrupt not pending # 1: Interrupt pending
SBIT(IRCON_DMAIF, 0xC0, 0);

SFR(DMA1CFGL, 0xD2); // DMA Channel 1-4 Configuration Address Low Byte
SFR(DMA1CFGH, 0xD3); // DMA Channel 1-4 Configuration Address High Byte
SFR(DMA0CFGL, 0xD4); // DMA Channel-0 Configuration Address Low Byte
SFR(DMA0CFGH, 0xD5); // DMA Channel-0 Configuration Address High Byte

#define DMA_CHANNEL_COUNT 5

// ### DMAARM (0xD6) - DMA Channel Arm
SFR(DMAARM, 0xD6);
// DMA Channel Arm
#define DMAARM_DMAARM0 BIT(0)  // (reset=0 R/W1) DMA arm channel 0 # This bit must be set in order for any DMA transfers to occur on the channel. For nonrepetitive # transfer modes, the bit is automatically cleared on completion.
#define DMAARM_DMAARM1 BIT(1)  // (reset=0 R/W1) DMA arm channel 1 # This bit must be set in order for any DMA transfers to occur on the channel. For nonrepetitive # transfer modes, the bit is automatically cleared on completion.
#define DMAARM_DMAARM2 BIT(2)  // (reset=0 R/W1) DMA arm channel 2 # This bit must be set in order for any DMA transfers to occur on the channel. For nonrepetitive # transfer modes, the bit is automatically cleared on completion.
#define DMAARM_DMAARM3 BIT(3)  // (reset=0 R/W1) DMA arm channel 3 # This bit must be set in order for any DMA transfers to occur on the channel. For nonrepetitive # transfer modes, the bit is automatically cleared on completion.
#define DMAARM_DMAARM4 BIT(4)  // (reset=0 R/W1) DMA arm channel 4 # This bit must be set in order for any DMA transfers to occur on the channel. For nonrepetitive # transfer modes, the bit is automatically cleared on completion.
#define DMAARM_ABORT   BIT(7)  // (reset=0 R0/W) DMA abort. This bit is used to stop ongoing DMA transfers. Writing a 1 to this bit aborts all # channels which are selected by setting the corresponding DMAARM bit to 1.

// ### DMAREQ (0xD7) - DMA Channel Start Request and Status
SFR(DMAREQ, 0xD7); // DMA Channel Start Request and Status
#define DMAREQ_DMAREQ0 BIT(0)  // (reset=0 R/W1) H0 DMA transfer request, channel 0 # When set to 1, activate the DMA channel (has the same effect as a single trigger event). This bit # is cleared when DMA transfer is started.
#define DMAREQ_DMAREQ1 BIT(1)  // (reset=0 R/W1) H0 DMA transfer request, channel 1 # When set to 1, activate the DMA channel (has the same effect as a single trigger event). This bit # is cleared when DMA transfer is started.
#define DMAREQ_DMAREQ2 BIT(2)  // (reset=0 R/W1) H0 DMA transfer request, channel 2 # When set to 1, activate the DMA channel (has the same effect as a single trigger event). This bit # is cleared when DMA transfer is started.
#define DMAREQ_DMAREQ3 BIT(3)  // (reset=0 R/W1) H0 DMA transfer request, channel 3 # When set to 1, activate the DMA channel (has the same effect as a single trigger event). This bit # is cleared when DMA transfer is started.
#define DMAREQ_DMAREQ4 BIT(4)  // (reset=0 R/W1) H0 DMA transfer request, channel 4 # When set to 1, activate the DMA channel (has the same effect as a single trigger event). This bit # is cleared when DMA transfer is started.

// ### DMAIRQ (0xD1) - DMA Interrupt Flag
SFR(DMAIRQ, 0xD1); // DMA Interrupt Flag
#define DMAIRQ_DMAIF0 BIT(0)  // (reset=0 R/W0) DMA channel-0 interrupt flag
#define DMAIRQ_DMAIF1 BIT(1)  // (reset=0 R/W0) DMA channel-1 interrupt flag
#define DMAIRQ_DMAIF2 BIT(2)  // (reset=0 R/W0) DMA channel-2 interrupt flag
#define DMAIRQ_DMAIF3 BIT(3)  // (reset=0 R/W0) DMA channel-3 interrupt flag
#define DMAIRQ_DMAIF4 BIT(4)  // (reset=0 R/W0) DMA channel-4 interrupt flag

enum dma_trig {
	DMA_TRIG_NONE      =  0,  // No trigger, setting the DMAREQ.DMAREQx bit starts transfer.
	DMA_TRIG_PREV      =  1,  // DMA channel is triggered by completion of previous channel.
	DMA_TRIG_T1_CH0    =  2,  // Timer 1, compare, channel 0
	DMA_TRIG_T1_CH1    =  3,  // Timer 1, compare, channel 1
	DMA_TRIG_T1_CH2    =  4,  // Timer 1, compare, channel 2
	DMA_TRIG_T2_EVENT1 =  5,  // Timer 2, event pulse 1
	DMA_TRIG_T2_EVENT2 =  6,  // Timer 2, event pulse 2
	DMA_TRIG_T3_CH0    =  7,  // Timer 3, compare, channel 0
	DMA_TRIG_T3_CH1    =  8,  // Timer 3, compare, channel 1
	DMA_TRIG_T4_CH0    =  9,  // Timer 4, compare, channel 0
	DMA_TRIG_T4_CH1    = 10,  // Timer 4, compare, channel 1
	DMA_TRIG_ST        = 11,  // Sleep Timer compare
	DMA_TRIG_IOC_0     = 12,  // Port 0 I/O pin input transition (1)
	DMA_TRIG_IOC_1     = 13,  // Port 1 I/O pin input transition (1)
	DMA_TRIG_URX0      = 14,  // USART 0 RX complete
	DMA_TRIG_UTX0      = 15,  // USART 0 TX complete
	DMA_TRIG_URX1      = 16,  // USART 1 RX complete
	DMA_TRIG_UTX1      = 17,  // USART 1 TX complete
	DMA_TRIG_FLASH     = 18,  // Flash data write complete
	DMA_TRIG_RADIO     = 19,  // CC253x: RF packet byte received (see Section 23.3)
	DMA_TRIG_ADC_CHALL = 20,  // ADC end of a conversion in a sequence, sample ready
	DMA_TRIG_ADC_CH11  = 21,  // ADC end of conversion channel 0 in sequence, sample ready
	DMA_TRIG_ADC_CH21  = 22,  // ADC end of conversion channel 1 in sequence, sample ready
	DMA_TRIG_ADC_CH32  = 23,  // ADC end of conversion channel 2 in sequence, sample ready
	DMA_TRIG_ADC_CH42  = 24,  // ADC end of conversion channel 3 in sequence, sample ready
	DMA_TRIG_ADC_CH53  = 25,  // ADC end of conversion channel 4 in sequence, sample ready
	DMA_TRIG_ADC_CH63  = 26,  // ADC end of conversion channel 5 in sequence, sample ready
	DMA_TRIG_ADC_CH74  = 27,  // ADC end of conversion channel 6 in sequence, sample ready
	DMA_TRIG_ADC_CH84  = 28,  // ADC end of conversion channel 7 in sequence, sample ready
	DMA_TRIG_ENC_DW    = 29,  // AES encryption processor requests download of input data
	DMA_TRIG_ENC_UP    = 30,  // AES encryption processor requests upload of output data
	DMA_TRIG_DBG_BW    = 31,  // Debug interface burst write
};

enum dma_vlen {
	DMA_VLEN_FIXED   = 0u,  // 000:     Use LEN for transfer count
	DMA_VLEN_PREFIX1 = 1u,  // 001:     Transfer the number of bytes or words specified by the first byte or word + 1 (up to a maximum specified by LEN). Thus, the transfer count excludes the length byte or word.
	DMA_VLEN_PREFIX0 = 2u,  // 010:     Transfer the number of bytes or words specified by the first byte or word (up to a maximum specified by LEN). Thus, the transfer count includes the length byte or word.
	DMA_VLEN_PREFIX2 = 3u,  // 011:     Transfer the number of bytes/words specified by the first byte/word + 2 (up to a maximum specified by LEN).
	DMA_VLEN_PREFIX3 = 4u,  // 100:     Transfer the number of bytes/words specified by the first byte/word + 3 (up to a maximum specified by LEN).
};

enum dma_addrmode {
	DMA_ADDRMODE_CONST = 0u,  // 00: 0 bytes or words
	DMA_ADDRMODE_INC_1 = 1u,  // 01: 1 byte or word
	DMA_ADDRMODE_INC_2 = 2u,  // 10: 2 bytes or word
	DMA_ADDRMODE_DEC_1 = 3u,  // 11: –1 byte or word
};

// REF: Table 8-2. DMA Configuration-Data Structure

struct dma_conf {
	// Big endian! DMA channel source address, low
	uint16_t src;
	// Big endian! DMA channel destination address, high. Note that flash memory is not directly writable.
	uint16_t dst;

	// The DMA channel transfer count. Used as the maximum allowable length when VLEN differs from 000 and 111.
	// The DMA channel counts in words when in WORDSIZE mode, and in bytes otherwise.
	union {
		uint16_t len;  // Big endian!
		struct {
			uint8_t lenh:5,
			    vlen:3;  // Variable-length transfer mode. In word mode, bits 12:0 of the first word are considered as the transfer length.
			uint8_t lenl;
		};
	};

	union {
		uint8_t mode1;
		uint8_t trig   :5,  // Selects one of the triggers shown in Table 8-1
		    block :1,  // Block transfer mode
		    repeat:1,  // Repeated transfer mode
		    wordsize:1;  // Selects whether each DMA transfer is 8-bit (0) or 16-bit (1).
	};

	union {
		uint8_t mode2;
		uint8_t priority:2,  // The DMA channel priority:
		    m8:1,  // Mode of 8th bit for VLEN transfer length; only applicable when WORDSIZE = 0 and VLEN differs from 000 and 111. 0: Use all 8 bits for transfer count 1: Use 7 LSB for transfer count
		    irqmask:1,  // Interrupt mask for this channel. 1: Enable interrupt generation on DMA channel done
		    dstinc:2,  // Destination address increment mode (after each transfer):
		    srcinc:2;  // Source address increment mode (after each transfer):
	};
};

enum {
	DMA_MODE1_BYTEMODE  = 0,
	DMA_MODE1_BLOCKMODE = BIT(5),
};

enum {
	DMA_MODE1_ONESHOT = 0,
	DMA_MODE1_REPEAT  = BIT(6),
};

enum {
	DMA_MODE1_WORD8  = 0,
	DMA_MODE1_WORD16 = BIT(6),
};

enum {
	DMA_MODE2_PRIORITY_LOW     = 0u,  // 00:      Low, CPU has priority.
	DMA_MODE2_PRIORITY_ASSURED = 1u,  // 01:      Assured, DMA at least every second try
	DMA_MODE2_PRIORITY_HIGH    = 2u,  // 10:      High, DMA has priority
};

enum {
	DMA_MODE2_NO_MASK8 = 0,
	DMA_MODE2_MASK8    = BIT(2),
};

enum {
	DMA_MODE2_INTR_DISABLE = 0,
	DMA_MODE2_INTR_ENABLE  = BIT(3),
};

#define DMA_MODE2_SRCMODE_SHIFT 6
#define DMA_MODE2_SRCMODE__MASK (0x3 << 6)
enum {
	DMA_MODE2_SRC_CONST = (DMA_ADDRMODE_CONST << 6),
	DMA_MODE2_SRC_INC_1 = (DMA_ADDRMODE_INC_1 << 6),
	DMA_MODE2_SRC_INC_2 = (DMA_ADDRMODE_INC_2 << 6),
	DMA_MODE2_SRC_DEC_1 = (DMA_ADDRMODE_DEC_1 << 6),
};

#define DMA_MODE2_DSTMODE_SHIFT 4
#define DMA_MODE2_DSTMODE__MASK (0x3 << 4)
enum {
	DMA_MODE2_DST_CONST = (DMA_ADDRMODE_CONST << 4),
	DMA_MODE2_DST_INC_1 = (DMA_ADDRMODE_INC_1 << 4),
	DMA_MODE2_DST_INC_2 = (DMA_ADDRMODE_INC_2 << 4),
	DMA_MODE2_DST_DEC_1 = (DMA_ADDRMODE_DEC_1 << 4),
};

#define DMA_MAX_LEN (BIT(16 - 3) - 1)

#define DMA_LEN(_len, _vlen_mode) (SWAP16(_len) | (DMA_VLEN_##_vlen_mode << 5))
#define DMA_MODE1(_trig, _block, _repeat, _wordsize)                           \
	(DMA_##_trig | DMA_MODE1_##_block | DMA_MODE1_##_repeat | DMA_MODE1_##_wordsize)
#define DMA_MODE2(_prio, _mask8, _intr, _srcmode, _dstmode)                    \
	(DMA_MODE2_##_prio | DMA_MODE2_##_mask8 | DMA_MODE2_##_intr                \
	 | DMA_MODE2_##_srcmode | DMA_MODE2_##_dstmode)

inline void
dma_init_ch0(struct dma_conf __xdata * dma_conf)
{
	// DMA0CFGH:DMA0CFGL gives the start address for the DMA channel 0 configuration data structure.
	DMA0CFGH = ADDR_H(dma_conf);
	DMA0CFGL = ADDR_L(dma_conf);
}

inline void
dma_init_ch1_4(struct dma_conf __xdata * dma_conf)
{
	// DMA1CFGH:DMA1CFGL gives the start address for the DMA channel 1 configuration data structure,
	// followed by the channel 2–4 configuration-data structures.
	DMA1CFGH = ADDR_H(dma_conf);
	DMA1CFGL = ADDR_L(dma_conf);
}

#define dma_trig(_ch)                                                          \
	do {                                                                       \
		DMAREQ |= BIT(_ch);                                                    \
	} while (0)

#define dma_arm(_ch)                                                           \
	do {                                                                       \
		DMAARM |= BIT(_ch);                                                    \
	} while (0)

#define dma_is_armed(_ch) (DMAARM & BIT(_ch))

#define dma_abort_all()                                                        \
	do {                                                                       \
		DMAARM = BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | DMAARM_ABORT;    \
	} while (0)

#define dma_abort(_ch)                                                         \
	do {                                                                       \
		DMAARM = BIT(_ch) | DMAARM_ABORT;                                      \
	} while (0)

#define dma_set_src(_conf, _addr)                                              \
	do {                                                                       \
		_conf.src = SWAP16((uint16_t)_addr);                                        \
	} while (0)

#define dma_set_dst(_conf, _addr)                                              \
	do {                                                                       \
		_conf.dst = SWAP16((uint16_t)_addr);                                        \
	} while (0)

#define dma_set_len(_conf, _len)                                               \
	do {                                                                       \
		_conf.len = SWAP16(_len);                                              \
	} while (0)

#define dma_set_varlen(_conf, _len, _mode)                                     \
	do {                                                                       \
		_conf.len = DMA_LEN(_len, _mode);                                      \
	} while (0)

#define dma_set_mode1(_conf, _trig, _block, _repeat, _wordsize)                \
	do {                                                                       \
		_conf.mode1 = DMA_MODE1(_trig, _block, _repeat, _wordsize);            \
	} while (0)

#define dma_set_mode2(_conf, _prio, _mask8, _intr, _srcmode, _dstmode)         \
	do {                                                                       \
		_conf.mode2 = DMA_MODE2(_prio, _mask8, _intr, _srcmode, _dstmode);     \
	} while (0)

#define dma_wait(_ch)                                                          \
	do {                                                                       \
	} while (DMAARM & BIT(_ch))

#define dma_wait_trig(_ch)                                                     \
	do {                                                                       \
	} while (DMAREQ & BIT(_ch))
