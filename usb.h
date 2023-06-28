// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <stdint.h>
#include "bits.h"

__xdata __at(0x6200) struct {
	/* 0x6200 ### USBADDR (0x6200) - Function Address */
	uint8_t addr;

	/* Device address  (Reset=0000000) (R/W)*/
	#define USBADDR_ADDR_MASK ~BIT(7)

	/* This bit is set when the USBADDR register is written
		and cleared when the address becomes effective.
		(Reset=0) (R)*/
	#define USBADDR_UPDATE BIT(7)


	/* 0x6201 ### USBPOW (0x6201) - Power and Control Register */
	uint8_t pow;

	/* Suspend enable.
	When this bit is set to 1, suspend mode is entered when the USB has been idle for 3 ms.
	(Reset=0) (R/W)*/
	#define USBPOW_SUSPEND_EN             BIT(0)

	/* Suspend mode entered.
	This bit is only used when SUSPEND_EN = 1.
	Reading the USBCIF register or asserting RESUME clears this bit.
	(Reset=0) (R)*/
	#define USBPOW_SUSPEND                BIT(1)

	/* Drives resume signaling for remote wakeup.
	According to the USB Specification, the duration of driving resume must be at least 1 ms and no more than 15 ms.
	It is recommended to keep this bit set for approximately 10 ms.
	(Reset=0) (R/W)*/
	#define USBPOW_RESUME                 BIT(2)

	/* During reset signaling, this bit is set to 1.
	(Reset=0) (R)*/
	#define USBPOW_RST                    BIT(3)

	/* Reserved  (Reset=000) (R0)*/
	// #define USBPOW_RESERVED               (BIT(4) | BIT(5) | BIT(6))

	/* When this bit is set to 1, the USB controller sends zero-length data packets
	from the time INPKT_RDY is asserted and until the first SOF token has been received.
	This only applies to isochronous endpoints.
	(Reset=0) (R/W)*/
	#define USBPOW_ISO_WAIT_SOF           BIT(7)

	/* 0x6202 ### USBIIF (0x6202) - IN Endpoints and EP0 Interrupt Flags */
	uint8_t  iif;
	#define USBII_EP0   BIT(0)
	#define USBII_INEP1 BIT(1)
	#define USBII_INEP2 BIT(2)
	#define USBII_INEP3 BIT(3)
	#define USBII_INEP4 BIT(4)
	#define USBII_INEP5 BIT(5)

	__reserved_byte__;

	/* 0x6204 ### USBOIF (0x6204) - OUT-Endpoint Interrupt Flags */
	uint8_t  oif;
	#define USBOI_OUTEP1 BIT(1)
	#define USBOI_OUTEP2 BIT(2)
	#define USBOI_OUTEP3 BIT(3)
	#define USBOI_OUTEP4 BIT(4)
	#define USBOI_OUTEP5 BIT(5)

	__reserved_byte__;

	/* 0x6206 ### USBCIF (0x6206) - Common USB Interrupt Flags */
	uint8_t  cif;
	#define USBCI_SUSPEND BIT(0)
	#define USBCI_RESUME  BIT(1)
	#define USBCI_RST     BIT(2)
	#define USBCI_SOF     BIT(3)


	/* 0x6207 ### USBIIE (0x6207) - IN Endpoints and EP0 Interrupt-Enable Mask */
	uint8_t  iie;

	__reserved_byte__;

	/* 0x6209 ### USBOIE (0x6209) - OUT Endpoints Interrupt Enable Mask */
	uint8_t  oie;

	__reserved_byte__;

	/* 0x620B ### USBCIE (0x620B) - Common USB Interrupt-Enable Mask */
	uint8_t  cie;
	// See: cif

	union {
		uint16_t frm;
		struct {
			/* 0x620C ### USBFRML (0x620C) - Current Frame Number (Low Byte) */
			/* Low byte of 11-bit frame number  (Reset=0x00) (R)*/
			uint8_t  frml;
			/* 0x620D ### USBFRMH (0x620D) - Current Frame Number (High Byte) */
			/* 3 MSBs of 11-bit frame number  (Reset=000) (R)*/
			uint8_t  frmh;
		};
	};

	/* 0x620E ### USBINDEX (0x620E) - Current-Endpoint Index Register */
	/* Endpoint selected. Must be set to a value in the range 0-5  (Reset=0000) (R/W)*/
	uint8_t index;

	/* 0x620F ### USBCTRL (0x620F) - USB Control Register */
	uint8_t  ctrl;

	/* USB enable. The USB controller is reset when writing 0 to this bit.  (Reset=0) (R/W)*/
	#define USBCTRL_USB_EN BIT(0)

	/* 48-MHz USB PLL enable. When this bit is set, the 48-MHz PLL is started.
		However, the USB must not be accessed before the PLL has locked, that is, PLL_LOCKED is 1.
		This bit can only be set when USB_EN = 1.
		Note: The PLL must be disabled before exiting active mode and re-enabled after entering active mode.
		(Reset=0) (R/W)*/
	#define USBCTRL_PLL_EN BIT(1)

	/* Reserved. Always write 0 (Reset=0) (R/W)*/
	// #define USBCTRL_RESERVED BIT(2)

	/* PLL locked status  (Reset=0) (R)*/
	#define USBCTRL_PLL_LOCKED  BIT(7)

	union {
		struct {
			__reserved_byte__;

			/* 0x6211 ### USBCS0 (0x6211) - EP0 Control and Status (USBINDEX = 0) */
			uint8_t  cs0;
			/* Data packet received.
				This bit is set when an incoming data packet has been placed in the OUT FIFO.
				An interrupt request (EP0) is generated if the interrupt is enabled.
				Set CLR_OUTPKT_RDY = 1 to de-assert this bit.
			    (Reset=0) (R)*/
			#define USBCS0_OUTPKT_RDY     BIT(0)

			/*  Set this bit when a data packet has been loaded into the EP0 FIFO to notify the USB controller that a new data packet is ready to be transferred.
				When the data packet has been sent, this bit is cleared, and an interrupt request (EP0) is generated if the interrupt is enabled.
			    (Reset=0) (R/W H0)*/
			#define USBCS0_INPKT_RDY      BIT(1)

			/*  This bit is set when a STALL handshake has been sent.
				An interrupt request (EP0) is generated if the interrupt is enabled.
				This bit must be cleared from firmware.
			    (Reset=0) (R/W H1)*/
			#define USBCS0_SENT_STALL     BIT(2)

			/*  This bit is used to signal the end of a data transfer and must be asserted in the following three situations:
				- When the last data packet has been loaded and USBCS0.INPKT_RDY is set to 1
				- When the last data packet has been unloaded and USBCS0.CLR_OUTPKT_RDY is set to 1
				- When USBCS0.INPKT_RDY has been asserted without having loaded the FIFO (for sending a zero-length data packet).
				The USB controller clears this bit automatically.
			    (Reset=0) (R/W H0)*/
			#define USBCS0_DATA_END       BIT(3)

			/* This bit is set if the control transfer ends due to a premature end-of-control transfer.
				The FIFO is flushed and an interrupt request (EP0) is generated if the interrupt is enabled.
				Setting CLR_SETUP_END = 1 de-asserts this bit.
			    (Reset=0) (R)*/
			#define USBCS0_SETUP_END      BIT(4)

			/*  Set this bit to 1 to terminate the current transaction.
				The USB controller sends the STALL handshake and this bit is de-asserted.
			    (Reset=0) (R/W H0)*/
			#define USBCS0_SEND_STALL     BIT(5)

			/*  Set this bit to 1 to de-assert the OUTPKT_RDY bit of this register.
				This bit is cleared automatically.
			    (Reset=0) (R/W H0)*/
			#define USBCS0_CLR_OUTPKT_RDY BIT(6)

			/*  Set this bit to 1 to de-assert the SETUP_END bit of this register.
				This bit is cleared automatically.
			    (Reset=0) (R/W H0)*/
			#define USBCS0_CLR_SETUP_END  BIT(7)
		} ctrl_ep;

		struct {
			/* 0x6210 ### USBMAXI (0x6210) - Maximum Packet Size for IN Endpoint{1-5} */
			/* Maximum packet size, in units of 8 bytes, for IN endpoint selected by USBINDEX register.
				The value of this register should correspond to the wMaxPacketSize field in the standard endpoint descriptor for the endpoint.
				This register must not be set to a value greater than the available FIFO memory for the endpoint.
			    (Reset=0x00) (R/W)*/
			uint8_t  maxi;

			/* 0x6211 ### USBCSIL (0x6211) - IN EP{1-5} Control and Status, Low */
			uint8_t  csil;

			/* Set this bit when a data packet has been loaded into the IN FIFO to notify the USB controller that a new data packet is ready to be transferred. When the data packet has been sent, this bit is cleared, and an interrupt request (INEPn) is generated if the interrupt is enabled.
			(Reset=0) (R/W H0)*/
			#define USBCSIL_INPKT_RDY    BIT(0)

			/* This bit is 1 when there is at least one packet in the IN FIFO.
			(Reset=0) (R)*/
			#define USBCSIL_PKT_PRESENT  BIT(1)

			/* In isochronous mode, this bit is set if an IN token is received when INPKT_RDY=0, and a zero-length data packet is transmitted in response to the IN token.
			In bulk or interrupt mode, this bit is set when a NAK is returned in response to an IN token.
			Firmware should clear this bit.
			(Reset=0) (R/W)*/
			#define USBCSIL_UNDERRUN     BIT(2)

			/*       Set to 1 to flush next packet that is ready to transfer from the IN FIFO.
			The INPKT_RDY bit in this register is cleared.
			If there are two packets in the IN FIFO due to double buffering, this bit must be set twice to completely flush the IN FIFO.
			This bit is automatically cleared.
			(Reset=0) (R/W H0)*/
			#define USBCSIL_FLUSH_PACKET BIT(3)

			/* Set this bit to 1 to make the USB controller reply with a STALL handshake when receiving IN tokens.
			Firmware must clear this bit to end the STALL condition.
			It is not possible to stall an isochronous endpoint; thus, this bit only has an effect if the IN endpoint is configured as bulk or interrupt.
			(Reset=0) (R/W)*/
			#define USBCSIL_SEND_STALL   BIT(4)

			/* This bit is set when a STALL handshake has been sent.
			The FIFO is flushed and the INPKT_RDY bit in this register is de-asserted.
			An interrupt request (INEPn) is generated if the interrupt is enabled.
			This bit must be cleared from firmware.
			(Reset=0) (R/W)*/
			#define USBCSIL_SENT_STALL   BIT(5)

			/*       Setting this bit resets the data toggle to 0.
			Thus, setting this bit forces the next data packet to be a DATA0 packet.
			This bit is automatically cleared.
			(Reset=0) (R/W H0)*/
			#define USBCSIL_CLR_DATA_TOG BIT(6)

			/* 0x6212 ### USBCSIH (0x6212) - IN EP{1-5} Control and Status, High */
			uint8_t  csih;
			/* Double buffering enable (IN FIFO)
			0: Double buffering disabled
			1: Double buffering enabled
			(Reset=0) (R/W)*/
			#define USBCSIH_IN_DBL_BUF  BIT(0)

			/* Reserved  (Reset=0) (R0)*/

			/* Setting this bit forces the IN endpoint data toggle to switch and the data packet to be flushed from the IN FIFO, even though an ACK was received.
			This feature can be useful when reporting rate feedback for isochronous endpoints.
			(Reset=0) (R/W)*/
			#define USBCSIH_FORCE_DATA_TOG BIT(3)

			/* Reserved. Always write 10  (R/W)*/
			#define USBCSIH_ENABLE	BIT(5)

			/* Selects IN endpoint type
			0: Bulk or interrupt
			1: Isochronous
			(Reset=0) (R/W)*/
			#define USBCSIH_ISO			BIT(6)

			#define USBCSIH_AUTOSET		BIT(7)
		} in_ep;
	};


	struct {
		/* 0x6213 ### USBMAXO (0x6213) - Max. Packet Size for OUT EP{1-5} */
		/* Maximum packet size, in units of 8 bytes, for OUT endpoint selected by USBINDEX register.
			The value of this register should correspond to the wMaxPacketSize field in the standard endpoint descriptor for the endpoint.
			This register must not be set to a value greater than the available FIFO memory for the endpoint.
		    (Reset=0x00) (R/W)*/
		uint8_t  maxo;

		/* 0x6214 ### USBCSOL (0x6214) - OUT EP{1-5} Control and Status, Low */
		uint8_t  csol;

		/* This bit is set when a packet has been received and is ready to be read from the OUT FIFO.
			An interrupt request (OUT EP{1-5}) is generated if the interrupt is enabled.
			This bit should be cleared when the packet has been unloaded from the FIFO.
		    (Reset=0) (R/W)*/
		#define USBCSOL_OUTPKT_RDY   BIT(0)

		/* This bit is asserted when no more packets can be loaded into the OUT FIFO because it is full.
		                               (Reset=0) (R)*/
		#define USBCSOL_FIFO_FULL    BIT(1)

		/* This bit is set when an OUT packet cannot be loaded into the OUT FIFO.
			Firmware should clear this bit.
			This bit is only valid in isochronous mode.
		    (Reset=0) (R/W)*/
		#define USBCSOL_OVERRUN      BIT(2)

		/* This bit is set if there is a CRC or bit-stuff error in the packet received.
			Cleared when OUTPKT_RDY is cleared.
			This bit is only valid if the OUT endpoint is isochronous.
		    (Reset=0) (R)*/
		#define USBCSOL_DATA_ERROR   BIT(3)

		/* (R/W       Set to 1 to flush the next packet that is to be read from the OUT FIFO.
			The OUTPKT_RDY bit in this register is cleared.
			If there are two packets in the OUT FIFO due to double buffering, this bit must be set twice to completely flush the OUT FIFO.
			This bit is automatically cleared after a write to 1.
		    (Reset=0) H0)*/
		#define USBCSOL_FLUSH_PACKET BIT(4)

		/* Set this bit to 1 to make the USB controller reply with a STALL handshake when receiving OUT tokens.
			Firmware must clear this bit to end the STALL condition.
			It is not possible to stall an isochronous endpoint; thus, this bit only has an effect if the IN endpoint is configured as bulk or interrupt.
		    (Reset=0) (R/W)*/
		#define USBCSOL_SEND_STALL   BIT(5)
		/* This bit is set when a STALL handshake has been sent.
			An interrupt request (OUTEP{1-5}) is generated if the interrupt is enabled.
			This bit must be cleared from firmware.
		    (Reset=0) (R/W)*/
		#define USBCSOL_SENT_STALL   BIT(6)
		/* (R/W       Setting this bit resets the data toggle to 0.
			Thus, setting this bit forces the next data packet to be a DATA0 packet.
			This bit is automatically cleared.
		    (Reset=0) H0)*/
		#define USBCSOL_CLR_DATA_TOG BIT(7)


		/* 0x6215 ### USBCSOH (0x6215) - OUT EP{1-5} Control and Status, High */
		uint8_t  csoh;

		/* Double buffering enable (OUT FIFO)
			0    Double buffering disabled
			1    Double buffering enabled
			(Reset=0) (R/W)*/
		#define USBCSOH_OUT_DBL_BUF BIT(0)

		/* Reserved. Always write 00  (Reset=00) (R/W)*/
		#define USBCSOH_RESERVED_4 BIT(4)
		#define USBCSOH_RESERVED_5 BIT(5)

		/* Selects OUT endpoint type
			0    Bulk or interrupt
			1    Isochronous
			(Reset=0) (R/W)*/
		#define USBCSOH_ISO BIT(6)

		 /* When this bit is set to 1, the USBCSOL.UTPKT_RDY bit is automatically cleared when
			a data packet of maximum size (specified by USBMAXO) has been unloaded to the OUT FIFO.
			(Reset=0) (R/W)*/
		#define USBCSOH_AUTOCLEAR BIT(7)

	} out_ep;

	union {
		uint16_t cnt;

		struct {
			/* 0x6216 ### USBCNT0 (0x6216) - Number of Received Bytes in EP0 FIFO (when USBINDEX = 0) */
			/* 0x6216 ### USBCNTL (0x6216) - Number of Bytes in EP{1-5} OUT FIFO, Low */
			/* 8 LSBs of number of received bytes in OUT FIFO selected by USBINDEX register.
				Only valid when USBCSOL.OUTPKT_RDY is asserted.
				(Reset=0) (R)*/
			uint8_t  cntl;
			/* 0x6217 ### USBCNTH (0x6217) - Number of Bytes in EP{1–5} OUT FIFO, High */
			/* MSBs of number of received bytes in OUT FIFO selected by USBINDEX register.
				Only valid when USBCSOL.OUTPKT_RDY is set
				(Reset=3) (R)*/
			uint8_t  cnth;
		};
	};

	uint64_t _reserved_zeroes;
	
	/* 0x6220 ### USBF0 (0x6220) - Endpoint 0 FIFO */
	/* Endpoint 0 FIFO.
		 Reading this register unloads one byte from the EP0 FIFO.
		 Writing to this register loads one byte into the EP0 FIFO.
		 Note: The FIFO memory for EP0 is used for both incoming and outgoing data packets.
		 (Reset=0x00) (R/W)*/
	union {
		uint8_t  fifo;
		uint16_t fifo16;
	} fifo[6];

} USB;

#define usb_select_endpoint(_idx) do { USB.index = _idx; } while (0)

enum usb_ep_fifo_size {
	USB_EP0_FIFO_SIZE = 32,
	USB_EP1_FIFO_SIZE = 32,
	USB_EP2_FIFO_SIZE = 64,
	USB_EP3_FIFO_SIZE = 128,
	USB_EP4_FIFO_SIZE = 256,
	USB_EP5_FIFO_SIZE = 512,
};

