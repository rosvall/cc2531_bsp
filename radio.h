// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>
#include "bits.h"


enum rfc_obs_mux {
	RFC_OBS_MUX_0                =  0, // 000000: 0 - Constant value
	RFC_OBS_MUX_1                =  1, // 000001: 1 - Constant value
	// 2: short spikes after RX and peppered here and there
	// 3: 0
	// 4: 2MHz data on TX (includes preamble)
	// 5: 2MHz data on TX (includes preamble)
	// 6: Mangled RFC_SNIFF_DATA only on TX
	// 7: Clock for 6
	RFC_OBS_MUX_RFC_SNIFF_DATA   =  8, // 001000: rfc_sniff_data - Data from packet sniffer. Sample data on rising edges of sniff_clk.
	RFC_OBS_MUX_RFC_SNIFF_CLK    =  9, // 001001: rfc_sniff_clk - 250-kHz clock for packet sniffer data
	// 10: 0
	// 11: spike on RX of some, rare packets
	RFC_OBS_MUX_RSSI_VALID       = 12, // 001100: rssi_valid - Pin is high when the RSSI value has been updated at least once since RX was started. Cleared when leaving RX.
	RFC_OBS_MUX_DEMOD_CCA        = 13, // 001101: demod_cca - Clear channel assessment. See FSMSTAT1 register for details on how to configure the behavior of this signal.
	RFC_OBS_MUX_SAMPLED_CCA      = 14, // 001110: sampled_cca - A sampled version of the CCA bit from demodulator. The value is updated whenever a SSAMPLECCA or STXONCCA strobe is issued.
	RFC_OBS_MUX_SFD_SYNC         = 15, // 001111: sfd_sync - Pin is high when an SFD has been received or transmitted. Cleared when leaving RX or TX, respectively. Not to be confused with the SFD exception.
	RFC_OBS_MUX_TX_ACTIVE        = 16, // 010000: tx_active - Indicates that FFCTRL is in one of the TX states. Active-high. Note: This signal might have glitches, because it has no output flip-flop and is based on the current state register of the FFCTRL FSM.
	RFC_OBS_MUX_RX_ACTIVE        = 17, // 010001: rx_active - Indicates that FFCTRL is in one of the RX states. Active-high. Note: This signal might have glitches, because it has no output flip-flop and is based on the current state register of the FFCTRL FSM.
	RFC_OBS_MUX_FFCTRL_FIFO      = 18, // 010010: ffctrl_fifo - Pin is high when one or more bytes are in the RXFIFO. Low during RXFIFO overflow.
	RFC_OBS_MUX_FFCTRL_FIFOP     = 19, // 010011: ffctrl_fifop - Pin is high when the number of bytes in the RXFIFO exceeds the programmable threshold or at least one complete frame is in the RXFIFO. Also high during RXFIFO overflow. Not to be confused with the FIFOP exception.
	RFC_OBS_MUX_PACKET_DONE      = 20, // 010100: packet_done - A complete frame has been received. That is, the number of bytes set by the frame-length field has been received.
	// 21: 0
	RFC_OBS_MUX_RFC_XOR_RAND_I_Q = 22, // 010110: rfc_xor_rand_i_q - XOR between I and Q random outputs. Updated at 8 MHz.
	RFC_OBS_MUX_RFC_RAND_Q       = 23, // 010111: rfc_rand_q - Random data output from the Q channel of the receiver. Updated at 8 MHz.
	RFC_OBS_MUX_RFC_RAND_I       = 24, // 011000: rfc_rand_i - Random data output from the I channel of the receiver. Updated at 8 MHz
	RFC_OBS_MUX_LOCK_STATUS      = 25, // 011001: lock_status - 1 when PLL is in lock, otherwise 0
	// 26: Weird 30MHz clock. On for 125us, off for 125 us. Interrupted just before TX.
	// 27: 4MHz clock
	// 28: Flag. Shortly low before TX.
	// 29: flag. periodic burst of 10 spikes times every 100us when radio isn't active
	// 30: rx byte start-ish flag
	// 31: almost same as 30, but not quite
	// 32: tx_active, but high for 49 us longer
	// 33: 0
	// 34: spike when tx_active goes high
	// 35: same as 34
	// 36: same as 34
	// 37: rx_active for high for slightly longer
	// 38: same as 37
	// 39: same as 32
	RFC_OBS_MUX_PA_PD            = 40, // 101000: pa_pd - Power amplifier power-down signal
	// 41: same as 32
	RFC_OBS_MUX_LNA_PD           = 42, // 101010: lna_pd - LNA power-down signal
	// 43..63: 0
};

#define RFC_OBS_INVERT BIT(6)

// Radio RX/TX Data FIFO
SFR(RFD, 0xD9); // RF Data
SFRX(X_RFD, 0x7000 + 0xD9);

// ### RFIRQF0 (0xE9) RF Interrupt Flags
SFR(RFIRQF0, 0xE9);
#define RFIRQF0_SFD BIT(1)                 // SFD has been received or transmitted.  (reset=0 R/W0)
#define RFIRQF0_FIFOP BIT(2)               // The number of bytes in the RXFIFO is above the threshold. Also raised when a complete frame has been received, and when a packet has been read out completely and there are more complete packets available.  (reset=0 R/W0)
#define RFIRQF0_SRC_MATCH_DONE BIT(3)      // Source matching complete  (reset=0 R/W0)
#define RFIRQF0_SRC_MATCH_FOUND BIT(4)     // Source match found  (reset=0 R/W0)
#define RFIRQF0_FRAME_ACCEPTED BIT(5)      // Frame has passed frame filtering.  (reset=0 R/W0)
#define RFIRQF0_RXPKTDONE BIT(6)           // A complete frame has been received.  (reset=0 R/W0)
#define RFIRQF0_RXMASKZERO BIT(7)          // The RXENABLE register has gone from a nonzero state to an all-zero state.  (reset=0 R/W0)

// ### RFIRQF1 (0x91) RF Interrupt Flags
SFR(RFIRQF1, 0x91);
#define RFIRQF1_TXACKDONE BIT(0)           // An acknowledgment frame has been completely transmitted.  (reset=0 R/W0)
#define RFIRQF1_TXDONE BIT(1)              // A complete frame has been transmitted.  (reset=0 R/W0)
#define RFIRQF1_RFIDLE BIT(2)              // Radio state machine has entered the idle state.  (reset=0 R/W0)
#define RFIRQF1_CSP_MANINT BIT(3)          // Manual interrupt generated from CSP  (reset=0 R/W0)
#define RFIRQF1_CSP_STOP BIT(4)            // CSP has stopped program execution.  (reset=0 R/W0)
#define RFIRQF1_CSP_WAIT BIT(5)            // Execution continued after a wait instruction in CSP.  (reset=0 R/W0)

// ### RFERRF (0xBF) - RF Error Interrupt Flags
SFR(RFERRF, 0xBF);
#define RFERRF_NLOCK BIT(0)                // Frequency synthesizer failed to achieve lock after time-out, or lock is lost during reception. Receiver must be restarted to clear this error situation.  (reset=0 R/W0)
#define RFERRF_RXABO BIT(1)                // Reception of a frame was aborted.  (reset=0 R/W0)
#define RFERRF_RXOVERF BIT(2)              // RXFIFO overflowed  (reset=0 R/W0)
#define RFERRF_RXUNDERF BIT(3)             // RXFIFO underflowed  (reset=0 R/W0)
#define RFERRF_TXOVERF BIT(4)              // TXFIFO overflowed  (reset=0 R/W0)
#define RFERRF_TXUNDERF BIT(5)             // TXFIFO underflowed  (reset=0 R/W0)
#define RFERRF_STROBEERR BIT(6)            // A command strobe was issued at a time it could not be processed. Triggered if trying to disable radio when already disabled, or when trying to do a SACK, SACKPEND, or SNACK command when not in active RX.  (reset=0 R/W0)


__xdata __at(0x6000) struct {
	/* 0x6000 ### RXFIFO_MEM */
	uint8_t rxfifo_mem[128];

	/* 0x6080 ### RXFIFO_MEM */
	uint8_t txfifo_mem[128];

	/* 0x6100 ### SRCTABLE */
	union {
		struct {
			uint16_t panid;
			uint16_t addr;
		} shortaddr[24];
		uint64_t extaddr[12];
	} srctable;

	/* 0x6160 ### SRCRESMASK0 Extended address matching. When there is a match on entry ext_n, bits 2n and 2n + 1 are set in SRCRESMASK. */
	uint8_t srcresmask0;

	/* 0x6161 ### SRCRESMASK1 Short address matching. When there is a match on entry panid_n + short_n, bit n is set in SRCRESMASK. */
	uint8_t srcresmask1;

	/* 0x6162 ### SRCRESMASK2 24-bit mask that indicates source address match for each individual entry in the source address table */
	uint8_t srcresmask2;

	/* 0x6163 ### SRCRESINDEX The bit index of the least-significant 1 in SRCRESMASK, or 0x3F when there is no source match.
	On a match, bit 5 is 0 when the match is on a short address and 1 when it is on an extended address.
	On a match, bit 6 is 1 when the conditions for automatic pending bit in acknowledgment have been met (see the description of SRCMATCH.AUTOPEND).
	The bit gives no indication of whether or not the acknowledgment actually is transmitted, and does not take the PENDING_OR register bit and the SACK, SACKPEND, and SNACK strobes into account. */
	uint8_t srcresindex;

	/* 0x6164 SRCEXTPENDEN0 8 LSBs of the 24-bit mask that enables and disables automatic pending for each of the 12 extended addresses. Entry n is mapped to SRCEXTPENDEN[2n]. All SRCEXTPENDEN[2n + 1] bits are don't care. */
	uint8_t srcextpenden0;

	/* 0x6165 SRCEXTPENDEN1 8 middle bits of the 24-bit mask that enables and disables automatic pending for each of the 12 extended addresses. Entry n is mapped to SRCEXTPENDEN[2n]. All SRCEXTPENDEN[2n + 1] bits are don't care. */
	uint8_t srcextpenden1;

	/* 0x6166 SRCEXTPENDEN2 8 MSBs of the 24-bit mask that enables and disables automatic pending for each of the 12 extended addresses. Entry n is mapped to SRCEXTPENDEN[2n]. All SRCEXTPENDEN[2n + 1] bits are don't care. */
	uint8_t srcextpenden2;

	/* 0x6167 SRCSHORTPENDEN0 8 LSBs of the 24-bit mask that enables and disables automatic pending for each of the 24 short addresses */
	uint8_t srcshortpenden0;

	/* 0x6168 SRCSHORTPENDEN1 8 middle bits of the 24-bit mask that enables and disables automatic pending for each of the 24 short addresses */
	uint8_t srcshortpenden1;

	/* 0x6169 SRCSHORTPENDEN2 8 MSBs of the 24-bit mask that enables and disables automatic pending for each of the 24 short addresses */
	uint8_t srcshortpenden2;

	/* 0x616A–0x6171 EXT_ADD LE The IEEE extended address used during destination address filtering */
	uint64_t ext_add;

	/* 0x6172–0x6173 PAN_ID LE The PAN ID used during destination address filtering */
	uint16_t pan_id;

	/* 0x6174–0x6175 SHORT_ADDR LE The short address used during destination address filtering */
	uint16_t short_addr;

	/* reserved: Memory space used for temporary storage of variables */
	uint8_t _reserved_6176[10]; 

	/* 0x6180 ### FRMFILT0 (0x6180) - Frame Filtering */ 
	struct { 
	      uint8_t frame_filter_en        :1, /* Enables frame filtering
													When this bit is set, the radio performs frame filtering as specified in section 7.5.6.2 of IEEE 802.15.4(b), third filtering level.
													FRMFILT0[6:1] and FRMFILT1[7:1], together with the local address information, define the behavior of the filtering algorithm.
													0: Frame filtering off. (FRMFILT0[6:1], FRMFILT1[7:1] and SRCMATCH[2:0] are don't care.)
													1: Frame filtering on. 
												    (Reset=1) (R/W)*/ 
	              pan_coordinator        :1, /* Should be set high when the device is a PAN coordinator, to accept frames with no destination address (as specified in section 7.5.6.2 of IEEE 802.15.4(b))
													0: Device is not PAN coordinator.
													1: Device is PAN coordinator. 
												    (Reset=0) (R/W)*/ 
	              max_frame_version      :2, /* Used for filtering on the frame version field of the frame control field (FCF).
													If FCF[13:12] (the frame version subfield) is higher than MAX_FRAME_VERSION[1:0] and frame filtering is enabled, the frame is rejected. 
												    (Reset=11) (R/W)*/ 
	              fcf_reserved_mask      :3, /* Used for filtering on the reserved part of the frame control field (FCF).
													FCF_RESERVED_MASK[2:0] is ANDed with FCF[9:7].
													If the result is nonzero and frame filtering is enabled, the frame is rejected. 
												    (Reset=000) (R/W)*/ 
	                                     :1;     /* Reserved. Always write 0 
									                (Reset=0) (R/W)*/ 
	} frmfilt0;

	/* 0x6181 ### FRMFILT1 (0x6181) - Frame Filtering */ 
	struct { 
	      uint8_t _reserved_0            :1, /* Reserved. Always write 0 
	                                                (Reset=0) (R/W)*/ 
	              modify_ft_filter       :2, /* These bits are used to modify the frame-type field of a received frame before frame-type filtering is performed.
													The modification does not influence the frame that is written to the RXFIFO.
													00: Leave as it is
													01: Invert MSB
													10: Set MSB to 0
													11: Set MSB to 1 
												    (Reset=00) (R/W)*/ 
	              accept_ft_0_beacon     :1, /* Defines whether beacon frames are accepted or not. Beacon frames have frame type = 000.
													0: Reject
													1: Accept 
												    (Reset=1) (R/W)*/ 
	              accept_ft_1_data       :1, /* Defines whether data frames are accepted or not. Data frames have frame type = 001.
													0: Reject
													1: Accept 
												    (Reset=1) (R/W)*/ 
	              accept_ft_2_ack        :1, /* Defines whether acknowledgment frames are accepted or not. Acknowledgment frames have frame type = 010.
													0: Reject
													1: Accept 
												    (Reset=1) (R/W)*/ 
	              accept_ft_3_mac_cmd    :1, /* Defines whether MAC command frames are accepted or not. MAC command frames have frame type = 011.
													0: Reject
													1: Accept 
												    (Reset=1) (R/W)*/ 
	              accept_ft_4to7_reserved:1;     /* Defines whether reserved frames are accepted or not. Reserved frames have frame type = 100, 101, 110, or 111.
													0: Reject
													1: Accept 
												    (Reset=0) (R/W)*/ 
	} frmfilt1;

	/* 0x6182 ### SRCMATCH (0x6182) - Source Address Matching and Pending Bits */ 
	struct { 
	      uint8_t src_match_en           :1, /* Source address matching enable (This bit is don't care if FRMFILT0.FRAME_FILTER_EN = 0) 
	                                                (Reset=1) (R/W)*/ 
	              autopend               :1, /* Automatic acknowledgment pending flag enable.
													On reception of a frame, the pending bit in the (possibly) returned acknowledgment is set automatically, given that all the following conditions are met:
													- FRMFILT0.FRAME_FILTER_EN is set.
													- SRCMATCH.SRC_MATCH_EN is set.
													- SRCMATCH.AUTOPEND is set.
													- The received frame matches the current SRCMATCH.PEND_DATAREQ_ONLY setting.
													- The received source address matches at least one source-match table entry, which is enabled in both SHORT_ADDR_EN and SHORT_PEND_EN or EXT_ADDR_EN and EXT_PEND_EN.
													Note: Details for SHORT_PEND_EN and EXT_PEND_EN are found in the memory map description (Section 23.4). 
												    (Reset=1) (R/W)*/ 
	              pend_datareq_only      :1, /* When this bit is set, the AUTOPEND function also requires that the received frame is a DATA REQUEST MAC command frame. 
			                                        (Reset=1) (R/W)*/ 
	                                     :5;     /* Reserved. Always write 0 
									                (Reset=00000) (R/W)*/ 
	} srcmatch;

	/* 0x6183 ### SRCSHORTEN0 (0x6183) - Short Address Matching */ 
	uint8_t srcshorten0;        /* The 7:0 part of the 24-bit word SHORT_ADDR_EN that enables or disables source address matching for each of the 24 short address table entries.
														Optional safety feature:
														To ensure that an entry in the source-matching table is not used while it is being updated, set the corresponding SHORT_ADDR_EN bit to 0 while updating. 
													    (Reset=0x00) (R/W)*/ 

	/* 0x6184 ### SRCSHORTEN1 (0x6184) - Short Address Matching */ 
	uint8_t srcshorten1;        /* The 15:8 part of the 24-bit word SHORT_ADDR_EN. See previoius description of SRCSHORTEN0. 
	                                                    (Reset=0x00) (R/W)*/ 

	/* 0x6185 ### SRCSHORTEN2 (0x6185) - Short Address Matching */ 
	 uint8_t srcshorten2;        /* The 23:16 part of the 24-bit word SHORT_ADDR_EN. See previous description of SRCSHORTEN0. 
	                                                    (Reset=0x00) (R/W)*/ 

	/* 0x6186 ### SRCEXTEN0 (0x6186) - Extended Address Matching */ 
	 uint8_t srcexten0;          /* The 7:0 part of the 24-bit word EXT_ADDR_EN that enables or disables source address matching for each of the 12 extended address table entries.
														Write access: Extended address enable for table entry n (0 to 7) is mapped to EXT_ADDR_EN[2n]. All EXT_ADDR_EN[2n + 1] bits are read-only and don't care when written to.
														Read access: Extended address enable for table entry n (0 to 7) is mapped to both EXT_ADDR_EN[2n] and EXT_ADDR_EN[2n + 1].
														To ensure that an entry in the source matching table is not used while it is being updated, set the corresponding EXT_ADDR_EN bit to 0 while updating. 
													    (Reset=0x00) (R/W)*/ 

	/* 0x6187 ### SRCEXTEN1 (0x6187) - Extended Address Matching */ 
	 uint8_t srcexten1;          /* The 15:8 part of the 24-bit word EXT_ADDR_EN. See previous description of SRCEXTEN0. 
	                                                    (Reset=0x00) (R/W)*/ 

	/* 0x6188 ### SRCEXTEN2 (0x6188) - Extended Address Matching */ 
	 uint8_t srcexten2;          /* The 23:16 part of the 24-bit word EXT_ADDR_EN. See previous description of SRCEXTEN0. 
	                                                    (Reset=0x00) (R/W)*/ 

	/* 0x6189 ### FRMCTRL0 (0x6189) - Frame Handling */ 
	struct { 
	      uint8_t tx_mode                :2, /* Set test modes for TX
													00: Normal operation, transmit TXFIFO
													01: Reserved. Should not be used
													10: TXFIFO looping ignores underflow in TXFIFO and reads cyclically; infinite transmission.
													11: Send pseudorandom data from CRC, infinite transmission. 
												    (Reset=00) (R/W)*/ 
	              rx_mode                :2, /* Set RX modes
													00: Normal operation, use RXFIFO.
													01: Reserved
													10: RXFIFO looping ignores overflow in RXFIFO; infinite reception.
													11: Same as normal operation except that symbol search is disabled.
													Can be used for RSSI or CCA measurements when it is not desired to find symbol. 
												    (Reset=00) (R/W)*/ 
	              energy_scan            :1, /* Defines whether the RSSI register contains the most-recent signal strength or the peak signal strength since the energy scan was enabled.
													0: Most-recent signal strength
													1: Peak signal strength 
												    (Reset=0) (R/W)*/ 
	              autoack                :1, /* Defines whether the radio automatically transmits acknowledge frames or not.
													When autoack is enabled, all frames that are accepted by address filtering, have the acknowledge request flag set,
													and have a valid CRC are automatically acknowledged 12 symbol periods after being received.
													0: Autoack disabled
													1: Autoack enabled 
												    (Reset=0) (R/W)*/ 
	              autocrc                :1, /* In TX:
														1: A CRC-16 (ITU-T) is generated in hardware and appended to the transmitted frame. There is no need to write the last 2 bytes to TXBUF.
														0: No CRC-16 is appended to the frame. The last 2 bytes of the frame must be generated manually and written to TXBUF (if not, TX_UNDERFLOW occurs).
													In RX:
														1: The CRC-16 is checked in hardware, and replaced in the RXFIFO by a 16-bit status word which contains a CRC OK bit. The status word is controllable through APPEND_DATA_MODE.
														0: The last two bytes of the frame (CRC-16 field) are stored in the RXFIFO. The CRC check (if any) must be done manually. Note that this setting does not influence acknowledgment transmission (including AUTOACK). 
													(Reset=1) (R/W)*/ 
	              append_data_mode       :1;     /* When AUTOCRC = 0:
														Don't care
													When AUTOCRC = 1:
														0: RSSI + The CRC_OK bit and the 7-bit correlation value are appended at the end of each received frame
														1: RSSI + The CRC_OK bit and the 7-bit SRCRESINDEX are appended at the end of each received frame. See Table 23-1 for details. 
													(Reset=0) (R/W)*/ 
	} frmctrl0;

	/* 0x618A ### FRMCTRL1 (0x618A) - Frame Handling */ 
	struct { 
	      uint8_t set_rxenmask_on_tx     :1, /* Defines whether STXON sets bit 6 in the RXENABLE register or leaves it unchanged.
												0: Does not affect RXENABLE.
												1: Sets bit 6 in RXENABLE. Used for backwards compatibility with the CC2420. 
											    (Reset=1) (R/W)*/ 
              ignore_tx_underf       :1, /* Defines whether TX underflow should be ignored or not.
												0: Normal TX operation. TX underflow is detected and TX is aborted if underflow occurs.
												1: Ignore TX underflow. Transmit the number of bytes given by the frame-length field. 
											    (Reset=0) (R/W)*/ 
              pending_or             :1, /* Defines whether the pending data bit in outgoing acknowledgment frames is always set to 1 or controlled by the main FSM and the address filtering.
												0: Pending data bit is controlled by main FSM and address filtering.
												1: Pending data bit is always 1. 
											    (Reset=0) (R/W)*/ 
                                     :5;     /* Read as zero 
								                (Reset=00000) (R0)*/ 
	} frmctrl1;

	/* 0x618B ### RXENABLE (0x618B) - RX Enabling */ 
	uint8_t rxenable;           /* RXENABLE enables the receiver. A nonzero value in this register causes the main FSM to enable the receiver when in idle, after transmission, and after acknowledgment transmission.
								The following strobes can modify RXENMASK:
								SRXON: Sets bit 7 in RXENMASK
								STXON: Sets bit 6 in RXENMASK if SET_RXENMASK_ON_TX = 1
								SRFOFF: Clears all bits in RXENMASK
								SRXMASKBITSET: Sets bit 5 in RXENMASK
								SRXMASKBITCLR: Clears bit 5 in RXENMASK
								RXENABLE can be modified directly by the CPU by accessing registers RXMASKSET and RXMASKCLR.
								There might be conflicts between the CSP and CPU operations if both try to modify RXENMASK simultaneously. To handle the case of simultaneous access to RXENMASK, the following rules apply:
								- If two sources are not in conflict (they modify different parts of the register), both their requests to modify RXENMASK are processed.
								- If both try to modify the mask simultaneously, bus-write operations to RXMASKSET and RXMASKCLR have priority over the CSP. It is strongly recommended to avoid this situation. 
							    (Reset=0x00) (R)*/ 

	/* 0x618C ### RXMASKSET (0x618C) - RX Enabling */ 
	uint8_t rxmaskset;          /* When written, the written data is ORed with RXENMASK and stored in RXENMASK. 
	                                                    (Reset=0x00) (R0/W)*/ 

	/* 0x618D ### RXMASKCLR (0x618D) - RX Disabling */ 
	uint8_t rxmaskclr;          /* When written, the written data is inverted and ANDed with RXENMASK and stored in RXENMASK.
														For example, if a 1 is written to one or more bit positions in this register, the corresponding bits are cleared in RXENMASK. 
													    (Reset=0x00) (R0/W)*/ 

	/* 0x618E ### FREQTUNE (0x618E) - Crystal Oscillator Frequency Tuning */
	uint8_t freqtune; /* Tune crystal oscillator
                         The default setting, 1111, leaves the XOSC not tuned. Changing the
                         setting from default switches in extra capacitance to the oscillator,
                         effectively lowering the XOSC frequency. Hence, a higher setting gives
                         a higher frequency. */

	/* 0x618F ### FREQCTRL (0x618F) - Controls the RF Frequency */ 
	uint8_t freqctrl;           /* Frequency control word (at reset=2405MHz)
								fRF = fLO = (2394 + FREQCTRL) [MHz]
								The frequency word in FREQCTRL is an offset value from 2394.
								The device supports the frequency range from 2394 MHz to 2507 MHz. The usable settings for FREQCTRL are consequently 0 to 113.
								Settings outside this range (114-127) give a frequency of 2507 MHz.
								IEEE 802.15.4-2006 specifies a frequency range from 2405 MHz to 2480 MHz with 16 channels 5 MHz apart. The channels are numbered 11 through 26.
								For an IEEE 802.15.4-2006 compliant system, the only valid settings are thus FREQCTRL = 11 + 5*(channel number - 11). 
							    (Reset=0x0B) (R/W)*/

	/* 0x6190 ### TXPOWER (0x6190) - Controls the Output Power */
	uint8_t txpower;            /* PA power control.
								NOTE: Before going to TX, this value should be updated. Please
								consult the data sheet of the device (Appendix C) for recommended
								values; see also Section 23.8.13.
								TXPOWER (0x6190) – Controls the Output Power
								(Reset=0xF5) (R/W) */

	/* 0x6191 ### TXCTRL (0x6191) - Controls the TX Settings */ 
	struct { 
	      uint8_t txmix_current          :2, /* Transmit mixers core current: current increases with increasing setting. 
                                                (Reset=01) (R/W)*/ 
              dac_dc                 :2, /* Adjusts the dc level to the TX mixer. 
		                                        (Reset=10) (R/W)*/ 
              dac_curr               :3, /* Change the current in the DAC. 
		                                        (Reset=110) (R/W)*/ 
                                     :1;     /* Reserved 
								                (Reset=0) (R0)*/ 
	} txctrl;
	
	/* 0x6192 ### FSMSTAT0 (0x6192) – Radio Status Register */
	struct {
		uint8_t fsm_ffctrl_state         :6, /* Gives the current state of the FIFO and frame-control (FFCTRL) finite-state machine.  (R) */
	        cal_running              :1, /* Frequency synthesizer calibration status
                                            0: Calibration done or not started
                                            1: Calibration in progress
							                (Reset=0) (R)*/
			                         :1; /* (Reset=0) (R) */
	} fsmstat0;

	/* 0x6193 ### FSMSTAT1 (0x6193) - Radio Status Register */ 
	struct { 
	      uint8_t rx_active              :1, /* Status signal, active when FFCTRL is in one of the receive states 
                                                (Reset=0) (R)*/ 
              tx_active              :1, /* Status signal, active when FFCTRL is in one of the transmit states 
		                                        (Reset=0) (R)*/ 
              lock_status            :1, /* 1 when PLL is in lock, otherwise 0. 
		                                        (Reset=0) (R)*/ 
              sampled_cca            :1, /* Contains a sampled value of the CCA.
												The value is updated whenever a SSAMPLECCA or STXONCCA strobe is issued. 
											    (Reset=0) (R)*/ 
              cca                    :1, /* Clear-channel assessment. Dependent on CCA_MODE settings. See the following description of CCACTRL1. 
		                                        (Reset=0) (R)*/ 
              sfd                    :1, /* In TX
													0: When a complete frame with SFD has been sent or no SFD has been sent
													1: SFD has been sent.
												In RX
													0: When a complete frame has been received or no SFD has been received
													1: SFD has been received. 
												(Reset=0) (R)*/ 
              fifop                  :1, /* FIFOP is set high when there are more than FIFOP_THR bytes of data in the RXFIFO that have passed frame filtering.
												FIFOP is set high when there is at least one complete frame in the RXFIFO.
												FIFOP is set low again when a byte is read from the RXFIFO and this leaves FIFOP_THR bytes in the FIFO.
												FIFOP is high during RXFIFO overflow. 
											    (Reset=0) (R)*/ 
              fifo                   :1;     /* FIFO is high whenever there is data in the RXFIFO. Low during RXFIFO overflow 
		                                        (Reset=0) (R)*/ 
	} fsmstat1;

	/* 0x6194 ### FIFOPCTRL (0x6194) - FIFOP Threshold */ 
	uint8_t fifop_thr;              /* Threshold used when generating FIFOP signal 
                                    (Reset=1000000) (R/W)*/ 

	/* 0x6195 ### FSMCTRL (0x6195) - FSM Options */ 
	struct { 
	      uint8_t rx2rx_time_off         :1, /* Defines whether or not a 12-symbol time-out should be used after frame reception has ended.
												0: No time-out
												1: 12-symbol-period time-out 
											    (Reset=1) (R/W)*/ 
              slotted_ack            :1, /* Controls timing of transmission of acknowledge frames
												0: The acknowledge frame is sent 12 symbol periods after the end of the received frame which requests the acknowledge.
												1: The acknowledge frame is sent at the first backoff-slot boundary more than 12 symbol periods after the end of the received frame which requests the acknowledge. 
											    (Reset=0) (R/W)*/ 
                                     :6;     /* Read as zero 
								                (Reset=000000) (R0)*/ 
	} fsmctrl;

	/* 0x6196 ### CCACTRL0 (0x6196) - CCA Threshold */ 
	int8_t cca_thr;            /* Clear-channel-assessment threshold value, signed 2s-complement number for comparison with the RSSI.
							  The unit is 1 dB, offset is about 76 dBm.
							  The CCA signal goes high when the received signal is below this value.
							  The CCA signal is available on the CCA pin and in the FSMSTAT1 register.
							  Note that the value should never be set lower than CCA_HYST - 128 in order to avoid erroneous behavior of the CCA signal.
							  NOTE: The reset value translates to an input level of approximately -32 - 76 = -108 dBm, which is well below the sensitivity limit.
							  That means the CCA signal never indicates a clear channel.
							  This register should be updated to 0xF8, which translates to an input level of about -8 - 76 = -84 dBm. 
							  (Reset=0xE0) (R/W)*/ 

	/* 0x6197 ### CCACTRL1 (0x6197) - Other CCA Options */ 
	struct { 
	      uint8_t cca_hyst               :3, /* Sets the level of CCA hysteresis. Unsigned values given in dB 
                                                (Reset=010) (R/W)*/ 
              cca_mode               :2, /* 00: CCA always set to 1
												01: CCA = 1 when RSSI < CCA_THR - CCA_HYST; CCA = 0 when RSSI >= CCA_THR
												10: CCA = 1 when not receiving a frame, else CCA = 0
												11: CCA = 1 when RSSI < CCA_THR - CCA_HYST and not receiving a frame; CCA = 0 when RSSI >= CCA_THR or when receiving a frame 
											    (Reset=11) (R/W)*/ 
                                     :3;     /* Read as zero 
								                (Reset=000) (R0)*/ 
	} ccactrl1;

	/* 0x6198 ### RSSI (0x6198) - RSSI Status Register */ 
	int8_t rssi;                /* RSSI estimate on a logarithmic scale, signed number in 2s complement. Unit is 1 dB.
								The offset to use in order to convert the register value into the real RSSI value can be found in the data sheet of the device (Appendix C).
								The RSSI value is averaged over 8 symbol periods.
								The RSSI_VALID status bit should be checked before reading RSSI_VAL the first time.
								The reset value of -128 also indicates that the RSSI value is invalid. 
							    (Reset=0x80) (R)*/ 

	/* 0x6199 ### RSSISTAT (0x6199) - RSSI Valid Status Register */ 
	uint8_t rssi_valid;     /* RSSI value is valid. Occurs eight symbol periods after entering RX  (Reset=0) (R)*/ 

	/* 0x619A ### RXFIRST (0x619A) - First Byte in RXFIFO */ 
	uint8_t rxfirst;            /* First byte of the RXFIFO. Note: Reading this register does not modify the contents of the FIFO.  (Reset=0x00) (R)*/ 

	/* 0x619B ### RXFIFOCNT (0x619B) - Number of Bytes in RXFIFO */ 
	uint8_t rxfifocnt;          /* Number of bytes in the RXFIFO. Unsigned integer  (Reset=0x00) (R)*/ 

	/* 0x619C ### TXFIFOCNT (0x619C) - Number of Bytes in TXFIFO */ 
	uint8_t txfifocnt;          /* Number of bytes in the TXFIFO. Unsigned integer  (Reset=0x00) (R)*/ 

	/* 0x619D ### RXFIRST_PTR (0x619D) - RXFIFO Pointer */ 
	uint8_t rxfirst_ptr; 		 /* RAM address offset of the first byte in the RXFIFO  (Reset=0x00) (R)*/ 

	/* 0x619E ### RXLAST_PTR (0x619E) - RXFIFO Pointer */ 
	uint8_t rxlast_ptr; 		 /* RAM address offset of the last byte +1 byte in the RXFIFO  (Reset=0x00) (R)*/

	/* 0x619F ### RXP1_PTR (0x619F) - RXFIFO Pointer */ 
	uint8_t rxp1_ptr;           /* RAM address offset of the first byte of the first frame in the RXFIFO  (Reset=0x00) (R)*/ 

	uint8_t _reserved_61a0;

	/* 0x61A1 ### TXFIRST_PTR (0x61A1) - TXFIFO Pointer */ 
	uint8_t txfirst_ptr;        /* RAM address offset of the next byte to be transmitted from the TXFIFO  (Reset=0x00) (R)*/ 

	/* 0x61A2 ### TXLAST_PTR (0x61A2) - TXFIFO Pointer */ 
	uint8_t txlast_ptr;         /* RAM address offset of the last byte +1 byte of the TXFIFO  (Reset=0x00) (R)*/ 

	/* 0x61A3 ### RFIRQM0 (0x61A3) - RF Interrupt Masks */ 
	uint8_t rfirqm0;

	/* 0x61A4  ### RFIRQM1 (0x61A4 ) - RF Interrupt Masks */ 
	uint8_t rfirqm1;

	/* 0x61A5 ### RFERRM (0x61A5) - RF Error Interrupt Masks */ 
	uint8_t rferrm;

	/* 0x61A6 ### OPAMPMC (CC2530, CC2531: 0x61A6. CC2540: 0x61AD) - Operational Amplifier Mode Control */ 
	struct { 
	      uint8_t mode                   :2, /* Operational amplifier mode
												00 and 01: Non-chop mode - Higher offset (approximately 500 uV), but no chopper ripple. Use in conjunction with Mode 10 if offset cancellation is required. Offset for these two modes is the opposite of the offset seen in Mode 10.
												10: Non-chop mode - Higher offset (approximately 500 uV), but no chopper ripple. Use in conjunction with Mode 00 or Mode 01 to double sample and correct for the offset by averaging the two samples.
												11: Chop mode - Very low offset (approximately 50 uV), and very low noise (1/f noise shifted to 1 MHz due to chopping), and 1 MHz ripple 
											    (Reset=00) (R/W)*/ 
                                     :6;     /* Reserved. Always write 000000. 
								                (Reset=000000) (R/W)*/ 
	} opampmc;

	/* 0x61A7 ### RFRND (0x61A7) - Random Data */ 
	struct { 
	      uint8_t irnd                   :1, /* Random bit from the I channel of the receiver 
                                                (Reset=0) (R0)*/ 
              qrnd                   :1, /* Random bit from the Q channel of the receiver 
		                                        (Reset=0) (R0)*/ 
                                     :6;     /* Reserved. Read as 0 
								                (Reset=000000) (R0)*/ 
	} rfrnd;

	/* 0x61A8 ### MDMCTRL0 (0x61A8) - Controls Modem */ 
	struct { 
	      uint8_t tx_filter              :1, /* Defines the kind of TX filter that is used.
												The normal TX filter is as defined by the IEEE802.15.4 standard.
												Extra filtering may be applied in order to lower the out-of-band emissions.
												0: Normal TX filtering
												1: Enable extra filtering 
											    (Reset=1) (R/W)*/ 
              preamble_length        :4, /* The number of preamble bytes (two zero-symbols) to be sent in TX mode prior to the SFD, encoded in steps of 2 symbols (1 byte).
												The reset value of 2 is compliant with IEEE 802.15.4.
												0000: 2 leading-zero bytes
												0001: 3 leading-zero bytes
												0010: 4 leading-zero bytes
												...         ...
												1111: 17 leading-zero bytes 
											    (Reset=0010) (R/W)*/ 
              demod_avg_mode         :1, /* Defines the behavior or the frequency offset averaging filter.
												0: Lock average level after preamble match. Restart frequency offset calibration when searching for the next frame.
												1: Continuously update average level. 
											    (Reset=0) (R/W)*/ 
              dem_num_zeros          :2;     /* Sets how many zero symbols must be detected before the sync word when searching for sync.
												Note that only one is required to have a correlation value above the correlation threshold set in the MDMCTRL1 register.
												00: Reserved
												01: 1 zero symbol
												10: 2 zero symbols
												11: 3 zero symbols 
											    (Reset=10) (R/W)*/ 
	} mdmctrl0;

	/* 0x61A9 ### MDMCTRL1 (0x61A9) - Controls Modem */ 
	struct { 
	      uint8_t corr_thr               :5, /* Demodulator correlator threshold value, required before SFD search.
												Threshold value adjusts how the receiver synchronizes to data from the radio.
												If the threshold is set too low, sync can more easily be found on noise.
												If set too high, the sensitivity is reduced, but sync is not likely to be found on noise.
												In combination with DEM_NUM_ZEROS, the system can be tuned so sensitivity is high with less sync found on noise. 
											    (Reset=10100) (R/W)*/ 
              corr_thr_sfd           :1, /* Defines requirements for SFD detection:
												0: The correlation value of one of the zero symbols of the preamble must be above the correlation threshold.
												1: The correlation value of one zero symbol of the preamble and both symbols in the SFD must be above the correlation threshold. 
											    (Reset=0) (R/W)*/ 
                                     :2;     /* Read as zero 
								                (Reset=00) (R0)*/ 
	} mdmctrl1;

	/* 0x61AA ### FREQEST (0x61AA) - Estimated RF Frequency Offset */ 
	int8_t freqest;             /* Signed 2s-complement value. Contains an estimate of the frequency offset between carrier and the receiver LO.
								The offset frequency is FREQEST * 7800 Hz.
								DEM_AVG_MODE controls when this estimate is updated.
								If DEM_AVG_MODE = 0, it is updated until sync is found. Then the frequency offset estimate is frozen until the end of the received frame.
								If DEM_AVG_MODE = 1, it is updated as long as the demodulator is enabled.
								To calculate the correct value, one must use an offset (FREQEST_offset), which can be found in the data sheet of the device (Appendix C).
								Real FREQEST value = FREQEST - FREQEST_offset. 
							    (Reset=0x00) (R)*/ 

	/* 0x61AB ### RXCTRL (0x61AB) - Tune Receive Section */ 
	struct { 
	      uint8_t mix_current            :2, /* Control of the receiver mixers output current. The current increases with increasing setting. 
                                                (Reset=11) (R/W)*/ 
              gbias_lna_ref          :2, /* Adjusts front-end LNA PTAT current output (from M = 3 to M = 6), default: M = 5 
		                                        (Reset=11) (R/W)*/ 
              gbias_lna2_ref         :2, /* Adjusts front-end LNA2 or mixer PTAT current output (from M = 3 to M = 6), default: M = 5 
		                                        (Reset=11) (R/W)*/ 
                                     :2;     /* Reserved 
								                (Reset=00) (R0)*/ 
	} rxctrl;

	/* 0x61AC ### FSCTRL (0x61AC) - Tune Frequency Synthesizer */ 
	struct { 
	      uint8_t lodiv_current          :2, /* Adjusts divider currents, except mixer and PA buffers. 
                                                (Reset=10) (R/W)*/ 
              lodiv_buf_current_rx   :2, /* Adjusts current in mixer and PA buffers. Used when TX_ACTIVE = 0 
		                                        (Reset=10) (R/W)*/ 
              lodiv_buf_current_tx   :2, /* Adjusts current in mixer and PA buffers. Used when TX_ACTIVE = 1 
		                                        (Reset=01) (R/W)*/ 
              pre_current            :2;     /* Prescaler current setting 
		                                        (Reset=01) (R/W)*/ 
	} fsctrl;
	
	uint8_t _reserved_61ad;

	/* 0x61AE ### FSCAL1 (0x61AE) - Tune Frequency Calibration */ 
	uint8_t  fscal1_vco_curr;                       /* Defines current in VCO core.
												Sets the multiplier between calibrated current and VCO current.
												For the best value to use, see Table 23-6 in Section 23.15.1. 
											    (Reset=11) (R/W)*/ 

	/* 0x61AF ### FSCAL2 (0x61AF) - Tune Frequency Calibration */ 
	struct { 
	      uint8_t vco_caparr             :6, /* VCO capacitor array setting. Programmed during calibration. Override value when VCO_CAPARR_OE = 1. 
                                                (Reset=100000) (R/W)*/ 
              vco_caparr_oe          :1, /* Override the calibration result with the value from VCO_CAPARR[5:0]. 
		                                        (Reset=0) (R/W)*/ 
                                     :1;     /* Reserved. Read as 0 
								                (Reset=0) (R0)*/ 
	} fscal2;

	/* 0x61B0 ### FSCAL3 (0x61B0) - Tune Frequency Calibration */ 
	struct { 
	      uint8_t vco_caparr_cal_ctrl    :2, /* Calibration accuracy setting for the capacitor array part of the calibration
												00: 80 XOSC periods
												01: 100 XOSC periods
												10: 125 XOSC periods
												11: 250 XOSC periods 
											    (Reset=10) (R/W)*/ 
              vco_vc_dac             :4, /* Bit vector for programming varactor control voltage from VC DAC. 
		                                        (Reset=1010) (R/W)*/ 
              vco_dac_en_ov          :1, /* Enables the VCO DAC when 1 
		                                        (Reset=0) (R/W)*/ 
                                     :1;     /* Reserved. Read as 0 
								                (Reset=0) (R0)*/ 
	} fscal3;

	/* 0x61B1 ### AGCCTRL0 (0x61B1) - AGC Dynamic Range Control */ 
	struct { 
	      uint8_t agc_dr_xtnd_thr        :6, /* If the measured error between the AGC reference magnitude and the actual magnitude in dB is larger than this threshold, the extra attenuation is enabled in the front end.
												This threshold should be set higher than 0x0C. This feature is enabled by AGC_DR_XTND_EN. 
											    (Reset=011111) (R/W)*/ 
              agc_dr_xtnd_en         :1, /* 
												0: The AGC performs no adjustment of attenuation in the AAF.
												1: The AGC adjusts the gain in the AAF to achieve extra dynamic range for the receiver. 
											    (Reset=1) (R/W)*/ 
                                     :1;     /* Reserved. Read as 0 
								                (Reset=0) (R0)*/ 
	} agcctrl0;

	/* 0x61B2 ### AGCCTRL1 (0x61B2) - AGC Reference Level */ 
	uint8_t agcctrl1_agc_ref;                     /* Target value for the AGC control loop, given in 1-dB steps. For the best value to use see Table 23-6 in Section 23.15.1. 
                                        (Reset=010001) (R/W)*/ 

	/* 0x61B3 ### AGCCTRL2 (0x61B3) - AGC Gain Override */ 
	struct { 
	      uint8_t lna_current_oe         :1, /* Write 1 to override the AGC LNA current setting with the values above (LNA1_CURRENT, LNA2_CURRENT, and LNA3_CURRENT). 
                                                (Reset=0) (R/W)*/ 
              lna3_current           :2, /* Overrride value for LNA 3. Only used when LNA_CURRENT_OE = 1. When read, this register returns the current applied gain setting.
												00: 0-dB gain (reference level)
												01: 3-dB gain
												10: 6-dB gain
												11: 9-dB gain 
											    (Reset=00) (R'/W)*/ 
              lna2_current           :3, /* Overrride value for LNA 2. Only used when LNA_CURRENT_OE = 1. When read, this register returns the current applied gain setting.
												000: 0-dB gain (reference level)
												001: 3-dB gain
												010: 6-dB gain
												011: 9-dB gain
												100: 12-dB gain
												101: 15-dB gain
												110: 18-dB gain
												111: 21-dB gain 
											    (Reset=000) (R'/W)*/ 
              lna1_current           :2;     /* Overrride value for LNA 1. Only used when LNA_CURRENT_OE = 1. When read, this register returns the current applied gain setting.
												00: 0-dB gain (reference level)
												01: 3-dB gain
												10: Reserved
												11: 6-dB gain 
											    (Reset=00) (R'/W)*/ 
	} agcctrl2;

	/* 0x61B4 ### AGCCTRL3 (0x61B4) - AGC Control */ 
	struct { 
	      uint8_t aaf_rp_oe              :1, /* Write 1 to override the AGC AAF control signals with the values stored in AAF_RP. 
                                                (Reset=0) (R/W)*/ 
              aaf_rp                 :2, /* Overrides the AGC control signals to AAF when AAF_RP_OE = 1. When read, it returns the applied signal to the AAF.
												00: 9-dB attenuation in AAF
												01: 6-dB attenuation in AAF
												10: 3-dB attenuation in AAF
												11: 0-dB attenuation in AAF (reference level) 
											    (Reset=11) (R'/W)*/ 
              agc_win_size           :2, /* Window size for the accumulate and dump function in the AGC
												00: 16 samples
												01: 32 samples
												10: 64 samples
												11: 128 samples 
											    (Reset=01) (R/W)*/ 
              agc_settle_wait        :2, /* Time for AGC to wait for analog gain to settle after a gain change. During this period, the energy measurement in the AGC is paused.
												00: 15 periods
												01: 20 periods
												10: 25 periods
												11: 30 periods 
											    (Reset=01) (R/W)*/ 
                                     :1;     /* Reserved. Read as 0 
								                (Reset=0) (R0)*/ 
	} agcctrl3;

	/* 0x61B5 ### ADCTEST0 (0x61B5) - ADC Tuning */ 
	struct { 
	      uint8_t adc_dac2_en            :1, /* Enables DAC2 for enhanced ADC stability 
                                                (Reset=0) (R/W)*/ 
              adc_gm_adj             :3, /* Gm control for test and debug 
		                                        (Reset=000) (R/W)*/ 
              adc_quant_adj          :2, /* Quantizer threshold control for test and debug 
		                                        (Reset=01) (R/W)*/ 
              adc_vref_adj           :2;     /* Quantizer threshold control for test and debug 
		                                        (Reset=00) (R/W)*/ 
	} adctest0;

	/* 0x61B6 ### ADCTEST1 (0x61B6) - ADC Tuning */ 
	struct { 
	      uint8_t adc_c3_adj             :2, /* Used to adjust capacitor values in ADC 
                                                (Reset=10) (R/W)*/ 
              adc_c2_adj             :2, /* Used to adjust capacitor values in ADC 
		                                        (Reset=11) (R/W)*/ 
              adc_test_ctrl          :4;     /* ADC test mode selector 
		                                        (Reset=0000) (R/W)*/ 
	} adctest1;

	/* 0x61B7 ### ADCTEST2 (0x61B7) - ADC Tuning */ 
	struct { 
	      uint8_t adc_dac_rot            :1, /* Control of DAC DWA scheme
												0: DWA (scrambling) disabled
												1: DWA enabled 
											    (Reset=1) (R/W)*/ 
              adc_ff_adj             :2, /* Adjust feedforward 
		                                        (Reset=01) (R/W)*/ 
              aaf_rs                 :2, /* Controls series resistance of AAF 
		                                        (Reset=00) (R/W)*/ 
              adc_test_mode          :2, /* Test mode to enable output of ADC data from demodulator. When enabled, raw ADC data is clocked out on the GPIO pins.
												00: Test mode disabled
												01: Data from both I and Q ADCs is output, data rate 76 MHz
												10: Data from I ADC is output. Two and two ADC samples grouped, data rate 38 MHz
												11: Data from Q ADC is output. Two and two ADC samples grouped, data rate 38 MHz 
											    (Reset=00) (R/W)*/ 
                                     :1;     /* Reserved. Read as 0 
								                (Reset=0) (R0)*/ 
	} adctest2;

	/* 0x61B8 ### MDMTEST0 (0x61B8) - Test Register for Modem */ 
	struct { 
	      uint8_t dc_block_mode          :2, /* Selects the mode of operation:
												00: The input signal to the dc blocker is passed on to the output without any attempt to remove dc.
												01: Enable dc cancellation. Normal operation
												10: Freeze estimates of dc when sync is found. Start estimating dc again when searching for the next frame.
												11: Reserved 
											    (Reset=01) (R/W)*/ 
              dc_win_size            :2, /* Controls the number of samples to be accumulated between each dump of the accumulate-and-dump filter used in dc removal.
												00: 32 samples
												01: 64 samples
												10: 128 samples
												11: 256 samples 
											    (Reset=01) (R/W)*/ 
              tx_tone                :4;     /* Enables the possibility to transmit a baseband tone by picking samples from the sine tables with a controllable phase step between the samples. The step size is controlled by TX_TONE.
												If MDMTEST1.MOD_IF is 0, the tone is superimposed on the modulated data, effectively giving modulation with an IF.
												If MDMTEST1.MOD_IF is 1, only the tone is transmitted.
												0000: -6 MHz
												0001: -4 MHz
												0010: -3 MHz
												0011: -2 MHz
												0100: -1 MHz
												0101: -500 kHz
												0110: -4 kHz
												0111: 0
												1000: 4 kHz
												1001: 500 kHz
												1010: 1 MHz
												1011: 2 MHz
												1100: 3 MHz
												1101: 4 MHz
												1110: 6 MHz
												Others: Reserved 
											    (Reset=0111) (R/W)*/ 
	} mdmtest0;

	/* 0x61B9 ### MDMTEST1 (0x61B9) - Test Register for Modem */ 
	struct { 
	      uint8_t reserved               :1, /* Reserved. Do not write. 
                                                (Reset=0) (R/W)*/ 
              modulation_mode        :1, /* Set one of two RF modulation modes for RX/TX
												0: IEEE 802.15.4 compliant mode
												1: Reversed phase, non-IEEE compliant 
											    (Reset=0) (R/W)*/ 
              rfc_sniff_en           :1, /* 
												0: Packet sniffer module disabled
												1: Packet sniffer module enabled. The received and transmitted data can be observed on GPIO pins. 
											    (Reset=0) (R/W)*/ 
              ramp_amp               :1, /* 
												1: Enable ramping of DAC output amplitude during startup and finish.
												0: Disable ramping of DAC output amplitude 
											    (Reset=1) (R/W)*/ 
              mod_if                 :1, /* 
												0: Modulation is performed at an IF set by MDMTEST0.X_TONE.
												1: A tone is transmitted with frequency set by MDMTEST0.TX_TONE. 
											    (Reset=0) (R/W)*/ 
                                     :3;     /* Reserved. Read as 0 
								                (Reset=000) (R0)*/ 
	} mdmtest1;

	/* 0x61BA ### DACTEST0 (0x61BA) - DAC Override Value */ 
	struct { 
	      uint8_t dac_q_o                :7, /* Q-branch DAC override value when DAC_SRC = 001
													If DAC_SRC is set to be ADC data, CORDIC magnitude, channel filtered data, then DAC_Q_O controls the part of the word in question that actually is muxed to the DAC as described in the following list.
													000110 >= bits 6:0
													000111 >= bits 7:1
													001000 >= bits 8:2
													And so on
													If an invalid setting is chosen, then the DAC outputs only zeros (minimum value). 
												    (Reset=0000000) (R/W)*/ 
	                                     :1;     /* Reserved. Read as 0 
									                (Reset=0) (R0)*/ 
	} dactest0;

	/* 0x61BB ### DACTEST1 (0x61BB) - DAC Override Value */ 
	struct { 
	      uint8_t dac_i_o                :7, /* I-branch DAC override value when DAC_SRC = 001
													If DAC_SRC is set to be ADC data, CORDIC magnitude, channel filtered data, then DAC_I_O controls the part of the word in question that actually is muxed to the DAC as described in the following list.
													000110 >= bits 6:0
													000111 >= bits 7:1
													001000 >= bits 8:2
													And so on
													If an invalid setting is chosen, then the DAC outputs only zeros (minimum value), 
												    (Reset=0000000) (R/W)*/ 
	                                     :1;     /* Reserved. Read as 0 
									                (Reset=0) (R0)*/ 
	} dactest1;

	/* 0x61BC ### DACTEST2 (0x61BC) - DAC Test Setting */ 
	struct { 
	      uint8_t dac_src                :3, /* The data source for the TX DAC is selected by DAC_SRC according to:
													000: Normal operation (from modulator).
													001: The DAC_I_O and DAC_Q_O override values
													010: ADC data after decimation, magnitude-controlled by DAC_I_O and DAC_Q_O
													011: I/Q after decimation, channel and dc filtering, magnitude-controlled by DAC_I_O and DAC_Q_O
													100: Cordic magnitude output and front-end gain is output, magnitude-controlled by DAC_I_O and DAC_Q_O
													101: RSSI I output on the I DAC
													111: Reserved 
												    (Reset=000) (R/W)*/ 
	                                     :5;     /* Reserved 
									                (Reset=00101) (R0)*/ 
	} dactest2;

	/* 0x61BD ### ATEST (0x61BD) - Analog Test Control */ 
	struct { 
	      uint8_t atest_ctrl             :6, /* Controls the analog test mode:
													000000: Disabled
													000001: Enables the temperature sensor (see also the TR0 register description in Section 12.2.10).
													000010 : Enables the temperature sensor in the CC2533 (see also the TR0 register description in Section 12.2.10)
													Other values reserved. 
												    (Reset=000000) (R/W)*/ 
	                                     :2;     /* Reserved. Read as 0 
									                (Reset=00) (R0)*/ 
	} atest;

	/* 0x61BE ### PTEST0 (0x61BE) - Override Power-Down Register */ 
	struct { 
	      uint8_t aaf_pd                 :1, /* Antialiasing filter power-down signal when PD_OVERRIDE = 1 
                                                (Reset=0) (R/W)*/ 
              txmix_pd               :1, /* Transmit mixer power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
              lna_pd                 :2, /* Low-noise amplifier power-down signal. Defines LNA and mixer PD modes.
												00: Power up
												01: LNA off, mixer and regulator on
												10: LNA and mixer off, regulator on
												11: Power down
												When PD_OVERRIDE = 1 
											    (Reset=00) (R/W)*/ 
              dac_pd                 :1, /* Digital-to-analog converter power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
              adc_pd                 :1, /* Analog-to-digital converter power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
              chp_pd                 :1, /* Charge-pump power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
              pre_pd                 :1;     /* Prescaler power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
	} ptest0;

	/* 0x61BF ### PTEST1 (0x61BF) - Override Power-Down Register */ 
	struct { 
	      uint8_t lodiv_pd               :1, /* LO power-down signal when PD_OVERRIDE = 1 
                                                (Reset=0) (R/W)*/ 
              vco_pd                 :1, /* Voltage-controlled oscillator power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
              pa_pd                  :1, /* Power amplifier power-down signal when PD_OVERRIDE = 1 
		                                        (Reset=0) (R/W)*/ 
              pd_override            :1, /* Override enabling and disabling of various modules.
												For debug and testing only.
												It is impossible to override hard-coded BIAS_PD[1:0] dependency. 
											    (Reset=0) (R/W)*/ 
                                     :4;     /* Reserved. Read as 0 
								                (Reset=0000) (R0)*/ 
	} ptest1;

	/* 0x61C0 + N ### CSPROG<N> (N Ranging From 0 to 23) (0x61C0 + N) - CSP Program */ 
	uint8_t csprog[24];                  /* R             Byte N of the CSP program memory 
	                                                    (Reset=0xD0)*/ 

	uint8_t _reserved_61d8[8];
	
	/* 0x61E0 ### CSPCTRL (0x61E0) - CSP Control Bit */ 
	struct { 
		uint8_t mcu_ctrl               :1, /* CSP MCU control input 
	                                              (Reset=0) (R/W)*/ 
	                                   :7;     /* Reserved. Read as 0 
								                (Reset=0000000) (R0)*/ 

	/* 0x61E1 ### CSPSTAT (0x61E1) - CSP Status Register */ 
		uint8_t pc                 :5, /* CSP program counter  (Reset=00000) (R)*/ 
	       running            :1, /* 1: CSP is running.
												0: CSP is idle. 
											    (Reset=0) (R)*/ 
	                          :2;     /* Reserved. Read as 0  (Reset=00) (R0)*/ 

		/* 0x61E2 ### CSPX (0x61E2) - CSP X Register */ 
		uint8_t x;               /* CSP X data register. Used by CSP instructions WAITX, RANDXY, INCX, DECX, and conditional instructions 
		                                                    (Reset=0x00) (R/W)*/ 

		/* 0x61E3 ### CSPY (0x61E3) - CSP Y Register */ 
		uint8_t y;               /* CSP Y data register. Used by CSP instructions RANDXY, INCY, DECY, and conditional instructions 
		                                                    (Reset=0x00) (R/W)*/ 

		/* 0x61E4 ### CSPZ (0x61E4) - CSP Z Register */ 
		uint8_t z;               /* CSP Z data register. Used by CSP instructions INCZ, DECZ, and conditional instructions 
		                                                    (Reset=0x00) (R/W)*/ 

		/* 0x61E5 ### CSPT (0x61E5) - CSP T Register */ 
		uint8_t t;               /* CSP T data register.
															Content is decremented each time the MAC Timer overflows while the CSP program is running.
															The SCP program stops when decremented to 0.
															Setting CSPT = 0xFF prevents the register from being decremented. 
														    (Reset=0xFF) (R/W)*/ 
	} csp;

	uint8_t _reserved_61e6[5];

	/* 0x61EB ### RFC_OBS_CTRL[0..2] (0x61EB) - RF Observation Mux Control  */
	uint8_t rfc_obs_ctrl[3];
	
	uint8_t _reserved_61ee[12];

	/* 0x61FA ### TXFILTCFG (0x61FA) - TX Filter Configuration */ 
	uint8_t txfiltcfg_fc;                             /* Sets TX anti-aliasing filter to appropriate bandwidth.
													Reduces spurious emissions close to signal.
													For the best value to use, see Table 23-6 in Section 23.15.1. 
												    (Reset=1111) (R/W)*/ 

} RADIO;
