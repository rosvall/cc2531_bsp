// SPDX-FileCopyrightText: 2023 Andreas Sig Rosvall
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <compiler.h>
#include <stdint.h>

__xdata __at(0x6230) struct {
	/* 0x6230 ### I2CCFG (0x6230) - I2C Control */ 
	struct { 
	      uint8_t  CR0                    :1,     /* Clock rate bit 0 
                                                (Reset=0) (R/W)*/ 
              CR1                    :1,     /* Clock rate bit 1 
		                                        (Reset=0) (R/W)*/ 
              AA                     :1,     /* Assert acknowledge flag for the I2C module.
												When set (AA = 1), an acknowledge is returned when:
												* Slave address is recognized
												* General call is recognized, when the I2C module is enabled
												* Data byte received while in master or slave receive mode
												When not set (AA = 0), an acknowledge is returned when:
												* Data byte is received while in master or slave receive mode 
											    (Reset=0) (R/W)*/ 
              SI                     :1,     /* Interrupt flag 
		                                        (Reset=0) (R/W0)*/ 
              STO                    :1,     /* STOP flag.
												When set and in master mode, a STOP condition is transmitted on the I2C bus.
												HW is cleared when transmit has completed successfully. 
											    (Reset=0) (R/W1)*/ 
              STA                    :1,     /* START flag. When set, HW detects when I2C is free and generates a START condition. 
		                                        (Reset=0) (R/W)*/ 
              ENS1                   :1,     /* Enable bit
												0: I2C module disabled SCL and SDA are set to high-impedance inputs. The inputs are ignored by the I2C module. Note that setting ENS1 = 0 disables the I2C module but does not reset its state.
												1: I2C module enabled 
											    (Reset=0) (R/W)*/ 
              CR2                    :1;     /* Clock rate bit 2 
		                                        (Reset=0) (R/W)*/ 
	} CFG;

	/* 0x6231 ### I2CSTAT (0x6231) - I2C Status */ 
	uint8_t  STAT;                                /* Status code. Contains the state of the I2C core.
												27 states are defined: 0 to 25 and 31.
												Interrupt is only requested when in states 0 to 25.
												The value 0xF8 indicates that there is no relevant state information available and that I2CCFG.SI = 0. 
											    (Reset=11111) (R)*/ 

	/* 0x6232 ### I2CDATA (0x6232) - I2C Data */ 
	uint8_t  DATA;                                /* Serial data in/out (MSB is bit 7, LSB is bit 0).
												Contains data byte to be transmitted or byte which has just been received.
												Can be read or written while not in the process of shifting a byte.
												The register is not shadowed or double buffered, so it should only be accessed on an interrupt. 
											    (Reset=00000000) (R/W)*/ 

	/* 0x6233 ### I2CADDR (0x6233) - I2C Own Slave Address */ 
	struct { 
	      uint8_t  GC                     :1,     /* General-call address acknowledge. If set, the general-call address is recognized. 
                                                (Reset=0) (R/W)*/ 
              ADDR                   :7;     /* Own slave address 
		                                        (Reset=0000000) (R/W)*/ 
	} ADDR;

	/* 0x6234 ### I2CWC (0x6234) - Wrapper Control */ 
	struct { 
	      uint8_t  SDAOE                  :1,     /* SDA pin output enable 
                                                (Reset=0) (R/W)*/ 
              SCLOE                  :1,     /* SCL pin output enable 
		                                        (Reset=0) (R/W)*/ 
              SDAPUE                 :1,     /* SDA pin pullup enable 
		                                        (Reset=1) (R/W)*/ 
              SCLPUE                 :1,     /* SCL pin pullup enable 
		                                        (Reset=1) (R/W)*/ 
                                     :3,     /* Reserved 
								                (Reset=000) (R0)*/ 
              OVR                    :1;     /* Override enable:
												0: I2C functionality (ignore other bits in this register)
												1: GPIO functionality 
											    (Reset=0) (R/W)*/ 
	} WC;

	/* 0x6235 ### I2CIO (0x6235) - GPIO */ 
	struct { 
	      uint8_t  SDAD                   :1,     /* SDA data value
												When I2CWC.SDAOE is set, reading SDAD reads the output register, not the pin.
												When I2CWC.SDAOE is cleared, reading SDAD reads the pin.
												Writing SDAD writes to the output register. 
											    (Reset=0) (R/W)*/ 
              SCLD                   :1,     /* SCL data value
												When I2CWC.SCLOE is set, reading SCLD reads the output register, not the pin.
												When I2CWC.SCLOE is cleared, reading SCLD reads the pin.
												Writing SCLD writes to the output register. 
											    (Reset=0) (R/W)*/ 
                                     :6;     /* Reserved 
								                (Reset=000) (R0)*/ 
	} IO;

} I2C;
