// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

/*
Table 2-5. Interrupts Overview

Num  Description                                  Name   Vector Flag          Mask

  0  RF core-error situation                      RFERR  0x03   IEN0.RFERRIE  TCON.RFERRIF (1)
  1  ADC end of conversion                        ADC    0x0B   IEN0.ADCIE    TCON.ADCIF (1)
  2  USART 0 RX complete                          URX0   0x13   IEN0.URX0IE   TCON.URX0IF (1)
  3  USART 1 RX complete                          URX1   0x1B   IEN0.URX1IE   TCON.URX1IF (1)
  4  AES encryption or decryption complete        ENC    0x23   IEN0.ENCIE    S0CON.ENCIF
  5  Sleep Timer compare                          ST     0x2B   IEN0.STIE     IRCON.STIF
  6  Port-2 inputs, USB, or I2C                   P2INT  0x33   IEN2.P2IE     IRCON2.P2IF (2)
  7  USART 0 TX complete                          UTX0   0x3B   IEN2.UTX0IE   IRCON2.UTX0IF
  8  DMA transfer complete                        DMA    0x43   IEN1.DMAIE    IRCON.DMAIF
  9  Timer 1 (16-bit) capture, compare, overflow  T1     0x4B   IEN1.T1IE     IRCON.T1IF (1) (2)
 10  Timer 2                                      T2     0x53   IEN1.T2IE     IRCON.T2IF (1) (2)
 11  Timer 3 (8-bit) capture, compare, overflow   T3     0x5B   IEN1.T3IE     IRCON.T3IF (1) (2)
 12  Timer 4 (8-bit) capture, compare, overflow   T4     0x63   IEN1.T4IE     IRCON.T4IF (1) (2)
 13  Port 0 inputs                                P0INT  0x6B   IEN1.P0IE     IRCON.P0IF (2)
 14  USART 1 TX complete                          UTX1   0x73   IEN2.UTX1IE   IRCON2.UTX1IF
 15  Port 1 inputs                                P1INT  0x7B   IEN2.P1IE     IRCON2.P1IF (2)
 16  RF general interrupts                        RF     0x83   IEN2.RFIE     S1CON.RFIF (2)
 17  Watchdog overflow in timer mode              WDT    0x8B   IEN2.WDTIE    IRCON2.WDTIF

(1) Hardware-cleared when interrupt service routine is called
(2) Additional IRQ mask and IRQ flag bits exist.
*/


enum intr {
    INTR_RFERR         = 0,   // RF core-error situation                     
    INTR_ADC           = 1,   // ADC end of conversion                       
    INTR_URX0          = 2,   // USART 0 RX complete                         
    INTR_URX1          = 3,   // USART 1 RX complete                         
    INTR_ENC           = 4,   // AES encryption or decryption complete       
    INTR_ST            = 5,   // Sleep Timer compare                         
    INTR_P2INT_USB_I2C = 6,   // Port-2 inputs, USB, or I2C                  
    INTR_UTX0          = 7,   // USART 0 TX complete                         
    INTR_DMA           = 8,   // DMA transfer complete                       
    INTR_T1            = 9,   // Timer 1 (16-bit) capture, compare, overflow 
    INTR_T2            = 10,  // Timer 2                                     
    INTR_T3            = 11,  // Timer 3 (8-bit) capture, compare, overflow  
    INTR_T4            = 12,  // Timer 4 (8-bit) capture, compare, overflow  
    INTR_P0INT         = 13,  // Port 0 inputs                               
    INTR_UTX1          = 14,  // USART 1 TX complete                         
    INTR_P1INT         = 15,  // Port 1 inputs                               
    INTR_RF            = 16,  // RF general interrupts                       
    INTR_WDT           = 17,  // Watchdog overflow in timer mode             
};

// Interrupt Enable 0
SFR(IEN0,           0xA8);
SBIT(IEN0_RFERRIE,  0xA8, 0); //  R/W    RF core error interrupt enable
SBIT(IEN0_ADCIE,    0xA8, 1); //  R/W    ADC interrupt enable
SBIT(IEN0_URX0IE,   0xA8, 2); //  R/W    USART0 RX interrupt enable
SBIT(IEN0_URX1IE,   0xA8, 3); //  R/W    USART 1 RX interrupt enable
SBIT(IEN0_ENCIE,    0xA8, 4); //  R/W    AES encryption and decryption interrupt enable
SBIT(IEN0_STIE,     0xA8, 5); //  R/W    Sleep Timer interrupt enable
SBIT(IEN0_EA,       0xA8, 7); //  R/W    Disables all interrupts.

// Interrupt Enable 1
SFR(IEN1,           0xB8);
SBIT(IEN1_DMAIE,    0xB8, 0); //  R/W    DMA transfer interrupt enable
SBIT(IEN1_T1IE,     0xB8, 1); //  R/W    Timer 1 interrupt enable
SBIT(IEN1_T2IE,     0xB8, 2); //  R/W    Timer 2 interrupt enable
SBIT(IEN1_T3IE,     0xB8, 3); //  R/W    Timer 3 interrupt enable
SBIT(IEN1_T4IE,     0xB8, 4); //  R/W    Timer 4 interrupt enable
SBIT(IEN1_P0IE,     0xB8, 5); //  R/W    Port 0 interrupt enable

// Interrupt Enable 2
SFR(IEN2,           0x9A);
#define IEN2_RFIE   BIT(0) //  RF general interrupt enable (reset=0 R/W)
#define IEN2_P2IE   BIT(1) //  Port 2 and USB interrupt enable (reset=0 R/W)
#define IEN2_UTX0IE BIT(2) //  USART 0 TX interrupt enable (reset=0 R/W)
#define IEN2_UTX1IE BIT(3) //  USART 1 TX interrupt enable (reset=0 R/W)
#define IEN2_P1IE   BIT(4) //  Port 1 interrupt enable (reset=0 R/W)
#define IEN2_WDTIE  BIT(5) //  Watchdog Timer interrupt enable (reset=0 R/W)


// Interrupt Flags
SFR(TCON,           0x88);
SBIT(TCON_IT0,      0x88, 0); //  R/W    Reserved. Must always be set to 1. Setting a zero enables low-level interrupt detection, which is almost always the case (one-shot when interrupt request is initiated).
SBIT(TCON_RFERRIF,  0x88, 1); //  R/W    RF core error interrupt flag. Set to 1 when RFERR interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TCON_IT1,      0x88, 2); //  R/W    Reserved. Must always be set to 1. Setting a zero enables low-level interrupt detection, which is almost always the case (one-shot when interrupt request is initiated).
SBIT(TCON_URX0IF,   0x88, 3); //  R/W    USART 0 RX interrupt flag. Set to 1 when USART 0 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TCON_ADCIF,    0x88, 5); //  R/W    ADC interrupt flag. Set to 1 when ADC interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(TCON_URX1IF,   0x88, 7); //  R/W    USART 1 RX interrupt flag. Set to 1 when USART 1 RX interrupt occurs and cleared when CPU vectors to the interrupt service routine.

// Interrupt Flags 2
//  R/W    AES interrupt. ENC has two interrupt flags, ENCIF_1 and ENCIF_0. Setting one of these flags requests interrupt service. Both flags are set when the AES coprocessor requests the interrupt.
SFR(S0CON,          0x98);
SBIT(S0CON_ENCIF_0, 0x98, 0);
SBIT(S0CON_ENCIF_1, 0x98, 1);

// Interrupt Flags 3
SFR(S1CON,          0x9B);
//  RF general interrupt. RF has two interrupt flags, RFIF_1 and RFIF_0. Setting one of
// these flags requests interrupt service. Both flags are set when the radio requests the
// interrupt.
// 0: Interrupt not pending
// 1: Interrupt pending (reset=0 R/W)
#define S1CON_RFIF_0 BIT(0)
//  RF general interrupt. RF has two interrupt flags, RFIF_1 and RFIF_0. Setting one of
// these flags requests interrupt service. Both flags are set when the radio requests the
// interrupt.
// 0: Interrupt not pending
// 1: Interrupt pending (reset=0 R/W)
#define S1CON_RFIF_1 BIT(1)

// Interrupt Flags 4
SFR(IRCON,          0xC0);
SBIT(IRCON_DMAIF,   0xC0, 0); //  R/W    DMA-complete interrupt flag
SBIT(IRCON_T1IF,    0xC0, 1); //  R/W    Timer 1 interrupt flag. Set to 1 when Timer 1 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(IRCON_T2IF,    0xC0, 2); //  R/W    Timer 2 interrupt flag. Set to 1 when Timer 2 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(IRCON_T3IF,    0xC0, 3); //  R/W    Timer 3 interrupt flag. Set to 1 when Timer 3 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(IRCON_T4IF,    0xC0, 4); //  R/W    Timer 4 interrupt flag. Set to 1 when Timer 4 interrupt occurs and cleared when CPU vectors to the interrupt service routine.
SBIT(IRCON_P0IF,    0xC0, 5); //  R/W    Port 0 interrupt flag
SBIT(IRCON_STIF,    0xC0, 7); //  R/W    Sleep Timer interrupt flag


// Interrupt Flags 5
SFR(IRCON2,         0xE8);
SBIT(IRCON2_P2IF,   0xE8, 0); //  R/W    Port 2 interrupt flag
SBIT(IRCON2_UTX0IF, 0xE8, 1); //  R/W    USART 0 TX interrupt flag
SBIT(IRCON2_UTX1IF, 0xE8, 2); //  R/W    USART 1 TX interrupt flag
SBIT(IRCON2_P1IF,   0xE8, 3); //  R/W    Port 1 interrupt flag
SBIT(IRCON2_WDTIF,  0xE8, 4); //  R/W    Watchdog Timer interrupt flag

// Interrupt Priority 0
SFR(IP0,            0xA9);
// ### IP0 (0xA9) - Interrupt Priority 0
//  Interrupt group 0, priority control bit 0, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP0_IP0_IPG0 BIT(0)
//  Interrupt group 1, priority control bit 0, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP0_IP0_IPG1 BIT(1)
//  Interrupt group 2, priority control bit 0, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP0_IP0_IPG2 BIT(2)
//  Interrupt group 3, priority control bit 0, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP0_IP0_IPG3 BIT(3)
//  Interrupt group 4, priority control bit 0, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP0_IP0_IPG4 BIT(4)
//  Interrupt group 5, priority control bit 0, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP0_IP0_IPG5 BIT(5)



// Interrupt Priority 1
SFR(IP1,            0xB9);
// ### IP1 (0xB9) - Interrupt Priority 1
//  Interrupt group 0, priority control bit 1, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP1_IP1_IPG0 BIT(0)
//  Interrupt group 1, priority control bit 1, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP1_IP1_IPG1 BIT(1)
//  Interrupt group 2, priority control bit 1, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP1_IP1_IPG2 BIT(2)
//  Interrupt group 3, priority control bit 1, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP1_IP1_IPG3 BIT(3)
//  Interrupt group 4, priority control bit 1, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP1_IP1_IPG4 BIT(4)
//  Interrupt group 5, priority control bit 1, see Table 2-7: Interrupt Priority Groups (reset=0 R/W)
#define IP1_IP1_IPG5 BIT(5)
  
#define interrupts_enable()  { IEN0_EA = 1; }
#define interrupts_disable() { IEN0_EA = 0; }

