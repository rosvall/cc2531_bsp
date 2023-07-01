// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

SBIT(IRCON2_UTX0IF, 0xE8, 1); // R/W USART 0 TX interrupt flag
SBIT(IRCON2_UTX1IF, 0xE8, 2); // R/W USART 1 TX interrupt flag

SBIT(TCON_URX0IF, 0x88, 3); // R/W USART 0 RX interrupt flag. Set to 1 when USART 0 RX interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TCON_URX1IF, 0x88, 7); // R/W USART 1 RX interrupt flag. Set to 1 when USART 1 RX interrupt occurs and cleared when CPU vectors to the interrupt service routine.

SBIT(IEN0_URX0IE, 0xA8, 2); // R/W USART0 RX interrupt enable
SBIT(IEN0_URX1IE, 0xA8, 3); // R/W USART1 RX interrupt enable

/*
Baud Rate UxBAUD  UxGCR  Error
(B/s)     BAUD_M  BAUD_E (%)
------------------------------
   2400       59       6 0.14
   4800       59       7 0.14
   9600       59       8 0.14
  14400      216       8 0.03
  19200       59       9 0.14
  28800      216       9 0.03
  38400       59      10 0.14
  57600      216      10 0.03
  76800       59      11 0.14
 115200      216      11 0.03
 230400      216      12 0.03
1000000        0      15 0
2000000        0      16 0
*/

enum {
	UXBAUD_BAUD_M_2400    =  59u,
	UXBAUD_BAUD_M_4800    =  59u,
	UXBAUD_BAUD_M_9600    =  59u,
	UXBAUD_BAUD_M_14400   = 216u,
	UXBAUD_BAUD_M_19200   =  59u,
	UXBAUD_BAUD_M_28800   = 216u,
	UXBAUD_BAUD_M_38400   =  59u,
	UXBAUD_BAUD_M_57600   = 216u,
	UXBAUD_BAUD_M_76800   =  59u,
	UXBAUD_BAUD_M_115200  = 216u,
	UXBAUD_BAUD_M_230400  = 216u,
	UXBAUD_BAUD_M_1000000 =   0u,
	UXBAUD_BAUD_M_2000000 =   0u,
};

enum {
	UXGCR_BAUD_E_2400    =  6u,
	UXGCR_BAUD_E_4800    =  7u,
	UXGCR_BAUD_E_9600    =  8u,
	UXGCR_BAUD_E_14400   =  8u,
	UXGCR_BAUD_E_19200   =  9u,
	UXGCR_BAUD_E_28800   =  9u,
	UXGCR_BAUD_E_38400   = 10u,
	UXGCR_BAUD_E_57600   = 10u,
	UXGCR_BAUD_E_76800   = 11u,
	UXGCR_BAUD_E_115200  = 11u,
	UXGCR_BAUD_E_230400  = 12u,
	UXGCR_BAUD_E_1000000 = 15u,
	UXGCR_BAUD_E_2000000 = 16u,
};

#define usart_set_baudrate(_n, _baudrate)                                      \
	{                                                                          \
		U##_n##BAUD = UXBAUD_BAUD_M_##_baudrate;                               \
		U##_n##GCR &= ~UXGCR_BAUD_E__MASK;                                     \
		U##_n##GCR |= UXGCR_BAUD_E_##_baudrate;                                \
	}

#define USART_BAUD_REG(_n) U##_n##BAUD

#define usart_set_spi_mode(_n)                                                 \
	{                                                                          \
		U##_n##CSR &= ~UXCSR_MODE;                                             \
	}

#define usart_set_uart_mode(_n)                                                \
	{                                                                          \
		U##_n##CSR |= UXCSR_MODE;                                              \
	}

SFR(U0CSR, 0x86); // USART 0 Control and Status
#define UXCSR_ACTIVE  BIT(0)  //  R       USART transmit or receive active status. In SPI slave mode, this bit equals slave select. # 0:    USART idle # 1:    USART busy in transmit or receive mode
#define UXCSR_TX_BYTE BIT(1)  //  R/W0    Transmit byte status. UART mode and SPI master mode # 0:    Byte not transmitted # 1:    Last byte written to data buffer register has been transmitted
#define UXCSR_RX_BYTE BIT(2)  //  R/W0    Receive byte status. UART mode and SPI slave mode. This bit is automatically cleared when # reading U1DBUF; clearing this bit by writing 0 to it effectively discards the data in U1DBUF.
#define UXCSR_ERR     BIT(3)  //  R/W0    UART parity error status. This bit is automatically cleared on a read of the U1CSR register or bits in the U1CSR register.
#define UXCSR_FE      BIT(4)  //  R/W0    UART framing error status. This bit is automatically cleared on a read of the U1CSR register or bits in the U1CSR register.
#define UXCSR_SLAVE   BIT(5)  //  R/W     SPI master- or slave-mode select # 0:      SPI master # 1:      SPI slave
#define UXCSR_RE      BIT(6)  //  R/W     UART receiver enable. Note: Do not enable receive before UART is fully configured. # 0:      Receiver disabled # 1:      Receiver enabled
#define UXCSR_MODE    BIT(7)  //  R/W     USART mode select # 0:      SPI mode # 1:      UART mode

SFR(U1CSR, 0xF8); // USART 1 Control and Status
SBIT(U1CSR_ACTIVE,  0xF8, 0); //  R       USART transmit or receive active status. In SPI slave mode, this bit equals slave select. # 0:    USART idle # 1:    USART busy in transmit or receive mode
SBIT(U1CSR_TX_BYTE, 0xF8, 1); //  R/W0    Transmit byte status. UART mode and SPI master mode # 0:    Byte not transmitted # 1:    Last byte written to data buffer register has been transmitted
SBIT(U1CSR_RX_BYTE, 0xF8, 2); //  R/W0    Receive byte status. UART mode and SPI slave mode. This bit is automatically cleared when # reading U1DBUF; clearing this bit by writing 0 to it effectively discards the data in U1DBUF.
SBIT(U1CSR_ERR,     0xF8, 3); //  R/W0    UART parity error status. This bit is automatically cleared on a read of the U1CSR register or bits in the U1CSR register.
SBIT(U1CSR_FE,      0xF8, 4); //  R/W0    UART framing error status. This bit is automatically cleared on a read of the U1CSR register or bits in the U1CSR register.
SBIT(U1CSR_SLAVE,   0xF8, 5); //  R/W     SPI master- or slave-mode select # 0:      SPI master # 1:      SPI slave
SBIT(U1CSR_RE,      0xF8, 6); //  R/W     UART receiver enable. Note: Do not enable receive before UART is fully configured. # 0:      Receiver disabled # 1:      Receiver enabled
SBIT(U1CSR_MODE,    0xF8, 7); //  R/W     USART mode select # 0:      SPI mode # 1:      UART mode

SFR(U0DBUF, 0xC1); // USART 0 Receive- and Transmit-Data Buffer

SFR(U1DBUF, 0xF9); // USART 1 Receive- and Transmit-Data Buffer

SFR(U0BAUD, 0xC2); // USART 0 Baud-Rate Control

SFR(U1BAUD, 0xFA); // USART 1 Baud-Rate Control

SFR(U0UCR, 0xC4); // USART 0 UART Control
SFR(U1UCR, 0xFB); // USART 1 UART Control
#define UXUCR_START  BIT(0) // UART start-bit level. Ensure that the polarity of the start bit is opposite the level of the idle line.  (reset=0 R/W)
#define UXUCR_STOP   BIT(1) // UART stop-bit level must be different from start-bit level.  (reset=1 R/W)
#define UXUCR_SPB    BIT(2) // UART number of stop bits. Selects the number of stop bits to transmit (reset=0 R/W)
#define UXUCR_PARITY BIT(3) // UART parity enable. One must set BIT9 in addition to setting this bit for parity to be calculated.  (reset=0 R/W)
#define UXUCR_BIT9   BIT(4) // Set this bit to 1 in order to enable the parity bit tranfer (as 9th bit).
#define UXUCR_D9     BIT(5) // The content of this 9th bit is given by D9, if parity is enabled by PARITY. (reset=0 R/W)
#define UXUCR_FLOW   BIT(6) // If parity is enabled (see PARITY, bit 3 in this register), then this bit sets the parity level as follows.  (reset=0 R/W)
#define UXUCR_FLUSH  BIT(7) // UART hardware flow enable. Selects use of hardware flow control with RTS and CTS pins  (reset=0 R/W)

SFR(U0GCR, 0xC5); // USART 0 Generic Control
SFR(U1GCR, 0xFC); // USART 1 Generic Control

// Baud rate exponent value.
// BAUD_E along with BAUD_M determines the UART baud rate and the SPI master SCK clock frequency. (Reset=00000 R/W)
#define UXGCR_BAUD_E__MASK BITMASK(5, 0)
#define UXGCR_ORDER BIT(5) // Bit order for transfers  (reset=0 R/W)
#define UXGCR_CPHA  BIT(6) // SPI clock phase  (reset=0 R/W)
#define UXGCR_CPOL  BIT(7) // SPI clock polarity  (reset=0 R/W)
