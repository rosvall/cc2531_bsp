// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include "bits.h"

//  R/W    Port 0 interrupt enable # 0: Interrupt disabled # 1: Interrupt enabled
SBIT(IEN1_P0IE, 0xB8, 5);
//  R/W    Port 0 interrupt flag # 0: Interrupt not pending # 1: Interrupt pending
SBIT(IRCON_P0IF, 0xC0, 5);

// Port 0 Interrupt Mask
SFR(P0IEN, 0xAB);
// ### P0IEN (0xAB) - Port 0 Interrupt Mask
// reset=0x00 R/W Port P0.7 to P0.0 interrupt enable 
#define P0IEN_P0_0_IEN BIT(0)
#define P0IEN_P0_1_IEN BIT(1)
#define P0IEN_P0_2_IEN BIT(2)
#define P0IEN_P0_3_IEN BIT(3)
#define P0IEN_P0_4_IEN BIT(4)
#define P0IEN_P0_5_IEN BIT(5)
#define P0IEN_P0_6_IEN BIT(6)
#define P0IEN_P0_7_IEN BIT(7)



// Port 0 Function Select
SFR(P0SEL, 0xF3);
// ### P0SEL (0xF3) - Port 0 Function Select
// Reset=0x00 R/W P0.7 to P0.0 function select 
#define P0SEL_SELP0_0 BIT(0)
#define P0SEL_SELP0_1 BIT(1)
#define P0SEL_SELP0_2 BIT(2)
#define P0SEL_SELP0_3 BIT(3)
#define P0SEL_SELP0_4 BIT(4)
#define P0SEL_SELP0_5 BIT(5)
#define P0SEL_SELP0_6 BIT(6)
#define P0SEL_SELP0_7 BIT(7)


// Port 0 Direction
SFR(P0DIR, 0xFD);
// ### P0DIR (0xFD) - Port 0 Direction
// Reset=0x00 R/W P0.7 to P0.0 I/O direction 
#define P0DIR_DIRP0_0 BIT(0)
#define P0DIR_DIRP0_1 BIT(1)
#define P0DIR_DIRP0_2 BIT(2)
#define P0DIR_DIRP0_3 BIT(3)
#define P0DIR_DIRP0_4 BIT(4)
#define P0DIR_DIRP0_5 BIT(5)
#define P0DIR_DIRP0_6 BIT(6)
#define P0DIR_DIRP0_7 BIT(7)



// Port 0 Input Mode
SFR(P0INP, 0x8F);
// ### P0INP (0x8F) - Port 0 Input Mode
// Reset=0x00 R/W P0.7 to P0.0 I/O input mode 
#define P0INP_MDP0_0 BIT(0)
#define P0INP_MDP0_1 BIT(1)
#define P0INP_MDP0_2 BIT(2)
#define P0INP_MDP0_3 BIT(3)
#define P0INP_MDP0_4 BIT(4)
#define P0INP_MDP0_5 BIT(5)
#define P0INP_MDP0_6 BIT(6)
#define P0INP_MDP0_7 BIT(7)



// Port 0 Interrupt Status Flag
SFR(P0IFG, 0x89);
// ### P0IFG (0x89) - Port 0 Interrupt Status Flag
// Reset=0x00 R/W0 Port 0, inputs 7 to 0 interrupt status flags. When an input port pin has an interrupt request # pending, the corresponding flag bit is set.
#define P0IFG_P0IF0 BIT(0)
#define P0IFG_P0IF1 BIT(1)
#define P0IFG_P0IF2 BIT(2)
#define P0IFG_P0IF3 BIT(3)
#define P0IFG_P0IF4 BIT(4)
#define P0IFG_P0IF5 BIT(5)
#define P0IFG_P0IF6 BIT(6)
#define P0IFG_P0IF7 BIT(7)



// Port 0
SFR(P0, 0x80);
SBIT(P0_0, 0x80, 0);
SBIT(P0_1, 0x80, 1);
SBIT(P0_2, 0x80, 2);
SBIT(P0_3, 0x80, 3);
SBIT(P0_4, 0x80, 4);
SBIT(P0_5, 0x80, 5);
SBIT(P0_6, 0x80, 6);
SBIT(P0_7, 0x80, 7);


// Port Interrupt Control
SFR(PICTL, 0x8C);
// ### PICTL (0x8C) - Port Interrupt Control
//  Port 0, inputs 7 to 0 interrupt configuration. This bit selects the interrupt request condition for all Port # 0 inputs.  (reset=0 R/W)
#define PICTL_P0ICON BIT(0)
//  Port 1, inputs 3 to 0 interrupt configuration. This bit selects the interrupt request condition for the low # nibble of Port 1 inputs.  (reset=0 R/W)
#define PICTL_P1ICONL BIT(1)
//  Port 1, inputs 7 to 4 interrupt configuration. This bit selects the interrupt request condition for the high # nibble of Port 1 inputs.  (reset=0 R/W)
#define PICTL_P1ICONH BIT(2)
//  Port 2, inputs 4 to 0 interrupt configuration. This bit selects the interrupt request condition for Port 2 # inputs 4 to 0.  (reset=0 R/W)
#define PICTL_P2ICON BIT(3)
//  Drive strength control for I/O pins in output mode. Selects output drive strength enhancement to # account for low I/O supply voltage on pin DVDD (this to ensure the same drive strength at lower # voltages as at higher).  (reset=0 R/W)
#define PICTL_PADSC BIT(7)






// Port 1 Input Mode
SFR(P1INP, 0xF6);
// ### P1INP (0xF6) - Port 1 Input Mode
// reset=000000 R/W P1.7 to P1.2 I/O input mode 
#define MASK_P1INP_ BITMASK(6, 2)
#define P1INP_MDP1_0 BIT(0)
#define P1INP_MDP1_1 BIT(1)
#define P1INP_MDP1_2 BIT(2)
#define P1INP_MDP1_3 BIT(3)
#define P1INP_MDP1_4 BIT(4)
#define P1INP_MDP1_5 BIT(5)



// Port 1 Direction
SFR(P1DIR, 0xFE);
// ### P1DIR (0xFE) - Port 1 Direction
// reset=0x00 R/W P1.7 to P1.0 I/O direction 
#define P1DIR_DIRP1_0 BIT(0)
#define P1DIR_DIRP1_1 BIT(1)
#define P1DIR_DIRP1_2 BIT(2)
#define P1DIR_DIRP1_3 BIT(3)
#define P1DIR_DIRP1_4 BIT(4)
#define P1DIR_DIRP1_5 BIT(5)
#define P1DIR_DIRP1_6 BIT(6)
#define P1DIR_DIRP1_7 BIT(7)



//  R/W    Port 1 interrupt flag # 0: Interrupt not pending # 1: Interrupt pending
SBIT(IRCON2_P1IF,   0xE8, 3);
// Port 1-Function Select
SFR(P1SEL, 0xF4);
// ### P1SEL (0xF4) - Port 1-Function Select
// reset=0x00 R/W P1.7 to P1.0 function select 
#define P1SEL_SELP1_0 BIT(0)
#define P1SEL_SELP1_1 BIT(1)
#define P1SEL_SELP1_2 BIT(2)
#define P1SEL_SELP1_3 BIT(3)
#define P1SEL_SELP1_4 BIT(4)
#define P1SEL_SELP1_5 BIT(5)
#define P1SEL_SELP1_6 BIT(6)
#define P1SEL_SELP1_7 BIT(7)

// Port 1 Interrupt Status Flag
SFR(P1IFG, 0x8A);
// ### P1IFG (0x8A) - Port 1 Interrupt Status Flag
// reset=0x00 R/W0 Port 1, inputs 7 to 0 interrupt status flags. When an input port pin has an interrupt request # pending, the corresponding flag bit is set.
#define P1IFG_P1IF0 BIT(0)
#define P1IFG_P1IF1 BIT(1)
#define P1IFG_P1IF2 BIT(2)
#define P1IFG_P1IF3 BIT(3)
#define P1IFG_P1IF4 BIT(4)
#define P1IFG_P1IF5 BIT(5)
#define P1IFG_P1IF6 BIT(6)
#define P1IFG_P1IF7 BIT(7)



// Port 1 Interrupt Mask
SFR(P1IEN, 0x8D);
// ### P1IEN (0x8D) - Port 1 Interrupt Mask
// reset=0x00 R/W Port P1.7 to P1.0 interrupt enable 
#define P1IEN_P1_0_IEN BIT(0)
#define P1IEN_P1_1_IEN BIT(1)
#define P1IEN_P1_2_IEN BIT(2)
#define P1IEN_P1_3_IEN BIT(3)
#define P1IEN_P1_4_IEN BIT(4)
#define P1IEN_P1_5_IEN BIT(5)
#define P1IEN_P1_6_IEN BIT(6)
#define P1IEN_P1_7_IEN BIT(7)



// Port 1
SFR(P1, 0x90);
SBIT(P1_0, 0x90, 0);
SBIT(P1_1, 0x90, 1);
SBIT(P1_2, 0x90, 2);
SBIT(P1_3, 0x90, 3);
SBIT(P1_4, 0x90, 4);
SBIT(P1_5, 0x90, 5);
SBIT(P1_6, 0x90, 6);
SBIT(P1_7, 0x90, 7);


//  R/W    Port 2 interrupt flag # 0: Interrupt not pending # 1: Interrupt pending
SBIT(IRCON2_P2IF, 0xE8, 0);
// Port 2 Input Mode
SFR(P2INP, 0xF7);
// ### P2INP (0xF7) - Port 2 Input Mode
// reset=00000 R/W P2.4 to P2.0 I/O input mode 
#define MASK_P2INP_ BITMASK(5, 0)
#define P2INP_MDP2_0 BIT(0)
#define P2INP_MDP2_1 BIT(1)
#define P2INP_MDP2_2 BIT(2)
#define P2INP_MDP2_3 BIT(3)
#define P2INP_MDP2_4 BIT(4)
//  Port 0 pullup-or-pulldown select. Selects function for all Port 0 pins configured as pullup-or- # pulldown inputs.  (reset=0 R/W)
#define P2INP_PDUP0 BIT(5)
//  Port 1 pullup-or-down select. Selects function for all Port 1 pins configured as pullup-or- # pulldown inputs.  (reset=0 R/W)
#define P2INP_PDUP1 BIT(6)
//  Port 2 pullup-or-pulldown select. Selects function for all Port 2 pins configured as pullup-or- # pulldown inputs.  (reset=0 R/W)
#define P2INP_PDUP2 BIT(7)



// Port 2 Direction and Port 0 Peripheral Priority Control
SFR(P2DIR, 0xFF);
// ### P2DIR (0xFF) - Port 2 Direction and Port 0 Peripheral Priority Control
// reset=00000 R/W P2.4 to P2.0 I/O direction 
#define MASK_P2DIR_ BITMASK(5, 0)
#define P2DIR_DIRP2_0 BIT(0)
#define P2DIR_DIRP2_1 BIT(1)
#define P2DIR_DIRP2_2 BIT(2)
#define P2DIR_DIRP2_3 BIT(3)
#define P2DIR_DIRP2_4 BIT(4)
// reset=00 R/W Port 0 peripheral priority control. These bits determine the order of priority in the case # when PERCFG assigns several peripherals to the same pins. # Detailed priority list: 
#define MASK_P2DIR_PRIP0 BITMASK(2, 6)
// 1st priority: USART 0
// 2nd priority: USART 1
// 3rd priority: Timer 1 
#define P2DIR_PRIP0_U0_U1_T1 (0U<<6)
// 1st priority: USART 1
// 2nd priority: USART 0
// 3rd priority: Timer 1 
#define P2DIR_PRIP0_U1_U0_T1 (1U<<6)
// 1st priority: Timer 1 channels 0-1
// 2nd priority: USART 1
// 3rd priority: USART 0
// 4th priority: Timer 1 channels 2-3 
#define P2DIR_PRIP0_T1CH01_U1_U0_T1CH23 (2U<<6)
// 1st priority: Timer 1 channels 2-3
// 2nd priority: USART 0
// 3rd priority: USART 1
// 4th priority: Timer 1 channels 0-1
#define P2DIR_PRIP0_T1CH23_U0_U1_T1CH01 (3U<<6)


// Port 2 Function Select and Port 1 Peripheral Priority Control
SFR(P2SEL, 0xF5);
// ### P2SEL (0xF5) - Port 2 Function Select and Port 1 Peripheral Priority Control
//  P2.0 function select  (reset=0 R/W)
#define P2SEL_SELP2_0 BIT(0)
//  P2.3 function select  (reset=0 R/W)
#define P2SEL_SELP2_3 BIT(1)
//  P2.4 function select  (reset=0 R/W)
#define P2SEL_SELP2_4 BIT(2)
//  Port 1 peripheral priority control. This bit determines the order of priority in the case when PERCFG # assigns USART 0 and Timer 1 to the same pins.  (reset=0 R/W)
#define P2SEL_PRI0P1 BIT(3)
//  Port 1 peripheral priority control. This bit determines the order of priority in the case when PERCFG # assigns Timer 1 and Timer 4 to the same pins.  (reset=0 R/W)
#define P2SEL_PRI1P1 BIT(4)
//  Port 1 peripheral priority control. This bit determines the order of priority in the case when PERCFG # assigns USART 1 and Timer 3 to the same pins.  (reset=0 R/W)
#define P2SEL_PRI2P1 BIT(5)
//  Port 1 peripheral priority control. This bit determines which module has priority in the case when # modules are assigned to the same pins.  (reset=0 R/W)
#define P2SEL_PRI3P1 BIT(6)

// Port 2 Interrupt Status Flag
SFR(P2IFG, 0x8B);
// ### P2IFG (0x8B) - Port 2 Interrupt Status Flag
// reset=00000 R/W0 Port 2, inputs 4 to 0 interrupt status flags. When an input port pin has an interrupt request # pending, the corresponding flag bit is set.
#define P2IFG_P2IF0 BIT(0)
#define P2IFG_P2IF1 BIT(1)
#define P2IFG_P2IF2 BIT(2)
#define P2IFG_P2IF3 BIT(3)
#define P2IFG_P2IF4 BIT(4)
//  USB D+ interrupt-status flag. This flag is set when the D+ line has an interrupt request pending # and is used to detect USB resume events in USB suspend state. This flag is not set when the # USB controller is not suspended. (reset=0 R/W0)
#define P2IFG_DPIF BIT(5)



// Port 2 Interrupt Mask
SFR(P2IEN, 0xAC);
// ### P2IEN (0xAC) - Port 2 Interrupt Mask
// reset=00000 R/W Port P2.4 to P2.0 interrupt enable 
#define MASK_P2IEN_ BITMASK(5, 0)
#define P2IEN_P2_0_IEN BIT(0)
#define P2IEN_P2_1_IEN BIT(1)
#define P2IEN_P2_2_IEN BIT(2)
#define P2IEN_P2_3_IEN BIT(3)
#define P2IEN_P2_4_IEN BIT(4)
//  USB D+ interrupt enable  (reset=0 R/W)
#define P2IEN_DPIEN BIT(5)



// Port 2
SFR(P2, 0xA0);
SBIT(P2_0, 0xA0, 0);
SBIT(P2_1, 0xA0, 1);
SBIT(P2_2, 0xA0, 2);
SBIT(P2_3, 0xA0, 3);
SBIT(P2_4, 0xA0, 4);




// ### PERCFG (0xF1) - Peripheral Control
// Peripheral Control
SFR(PERCFG, 0xF1);

// USART 0 I/O location   (reset=0 R/W)
#define PERCFG_U0CFG BIT(0)

// Alt 1:
//     RT/C  P0.5
//     CT/SS P0.4
//     TX/MO P0.3
//     RX/MI P0.2
#define PERCFG_U0_ALT1 0

// Alt 2:
//     TX/MO P1.5
//     RX/MI P1.4
//     RT/C  P1.3
//     CT/SS P1.2
#define PERCFG_U0_ALT2 PERCFG_U0CFG

// USART 1 I/O location   (reset=0 R/W)
#define PERCFG_U1CFG BIT(1)
// Alt 1:
//     RX/MI P0.5
//     TX/MO P0.4
//     RT/C  P0.3
//     CT/SS P0.2
#define PERCFG_U1_ALT1 0
// Alt 2:
//     RX/MI P1.7
//     TX/MO P1.6
//     RT/C  P1.5
//     CT/SS P1.4
#define PERCFG_U1_ALT2 PERCFG_U1CFG

// Timer 4 I/O location   (reset=0 R/W)
#define PERCFG_T4CFG BIT(4)
// Alt 1:
// 	OUT0  P1.0
// 	OUT1  P1.1
#define PERCFG_T4_ALT1 0
// Alt 2:
// 	OUT0  P2.0
// 	OUT1  P2.3
#define PERCFG_T4_ALT2 PERCFG_T4CFG

// Timer 3 I/O location   (reset=0 R/W)
#define PERCFG_T3CFG BIT(5)
// Alt 1:
// 	OUT0  P1.3
// 	OUT1  P1.4
#define PERCFG_T3_ALT1 0
// Alt 2:
// 	OUT0  P2.6
// 	OUT1  P2.7
#define PERCFG_T3_ALT2 PERCFG_T3CFG

// Timer 1 I/O location   (reset=0 R/W)
#define PERCFG_T1CFG BIT(6)
// Alt 1:
// 	OUT0  P0.2
// 	OUT1  P0.3
// 	OUT2  P0.4
// 	OUT3  P0.5
// 	OUT4  P0.6
#define PERCFG_T1_ALT1 0
// Alt 2:
// 	OUT0  P1.2
// 	OUT1  P1.1
// 	OUT2  P1.0
// 	OUT3  P0.6
// 	OUT4  P0.7
#define PERCFG_T1_ALT2 PERCFG_T1CFG

// I/O locations for alt configs, just for convenience
#define U0_ALT1_PORT  0
#define U0_ALT1_RT_C_PIN   5
#define U0_ALT1_CT_SS_PIN  4
#define U0_ALT1_TX_MO_PIN  3
#define U0_ALT1_RX_MI_PIN  2

#define U0_ALT2_PORT 1
#define U0_ALT2_TX_MO_PIN  5
#define U0_ALT2_RX_MI_PIN  4
#define U0_ALT2_RT_C_PIN   3
#define U0_ALT2_CT_SS_PIN  2

#define U1_ALT1_PORT 0
#define U1_ALT1_RX_MI_PIN  5
#define U1_ALT1_TX_MO_PIN  4
#define U1_ALT1_RT_C_PIN   3
#define U1_ALT1_CT_SS_PIN  2

#define U1_ALT2_PORT 1
#define U1_ALT2_RX_MI_PIN  7
#define U1_ALT2_TX_MO_PIN  6
#define U1_ALT2_RT_C_PIN   5
#define U1_ALT2_CT_SS_PIN  4

#define _PORT_NUM(_name) _name ## _PORT
#define PORT_NUM(_name) _PORT_NUM(_name)

#define _PIN_NUM(_name) _name ## _PIN
#define PIN_NUM(_name) _PIN_NUM(_name)

#define _P_SUFFIX2(_n, _suffix) P ## _n ## _suffix
#define _P_SUFFIX(_n, _suffix) _P_SUFFIX2(_n, _suffix)

#define _PIN2(_a, _b) P ## _a ## _ ## _b
#define _PIN(_a, _b) _PIN2(_a, _b)
#define PIN(_name) _PIN(PORT_NUM(_name), PIN_NUM(_name))

#define PDIR(_name) _P_SUFFIX(PORT_NUM(_name), DIR)
#define PIEN(_name) _P_SUFFIX(PORT_NUM(_name), IEN)
#define PIFG(_name) _P_SUFFIX(PORT_NUM(_name), IFG)
#define PINP(_name) _P_SUFFIX(PORT_NUM(_name), INP)
#define PSEL(_name) _P_SUFFIX(PORT_NUM(_name), SEL)

#define gpio_level_get(_name) PIN(_name)
#define gpio_level_set(_name, _level) { PIN(_name) = (_level); }
#define gpio_set_high(_name) gpio_level_set(_name, 1)
#define gpio_set_low(_name)  gpio_level_set(_name, 0)
#define gpio_toggle(_name)  { PIN(_name) ^= 1; }

#define gpio_dir_out(_name) { PDIR(_name) |=  BIT(PIN_NUM(_name)); }
#define gpio_dir_in(_name)  { PDIR(_name) &= ~BIT(PIN_NUM(_name)); }

#define gpio_intr_enable(_name)  { PIEN(_name) |=  BIT(PIN_NUM(_name)); }
#define gpio_intr_disable(_name) { PIEN(_name) &= ~BIT(PIN_NUM(_name)); }

#define gpio_tristate_enable(_name)  { PINP(_name) |=  BIT(PIN_NUM(_name)); }
#define gpio_tristate_disable(_name) { PINP(_name) &= ~BIT(PIN_NUM(_name)); }

#define gpio_pin_intr_flag(_name) (PIFG(_name) & BIT(PIN_NUM(_name)))

#define gpio_port_pulldown(_portnum) { P2INP |=  BIT(5 + (_portnum)); }
#define gpio_port_pullup(_portnum)   { P2INP &= ~BIT(5 + (_portnum)); }

#define gpio_connect_peripheral(_name)    { PSEL(_name) |=  BIT(PIN_NUM(_name)); }
#define gpio_disconnect_peripheral(_name) { PSEL(_name) &= ~BIT(PIN_NUM(_name)); }
