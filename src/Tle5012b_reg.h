/*!
 * \name        Tle5012b_reg.h - Library for Arduino for the TLE5012B angle sensor.
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 *              This library include the register read and bit separation function.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef TLE5012B_REG_H
#define TLE5012B_REG_H

#include "Arduino.h"
#include "Tle5012b.h"

#define MAX_NUM_REG    0x16   //!< defines the value for temporary data to read all readable registers

class Tle5012b_reg: public Tle5012b
{
	public:

	/*!
	 * Automatic calibration of offset and amplitude synchronicity for applications
	 * with full-turn. Only 1 LSB corrected at each update. CRC check of calibration
	 * registers is automatically disabled if AUTOCAL activated.
	 */
	enum calibrationMode
	{
		noAutoCal = 0x0,//!< noAutoCal = no auto-calibration
		mode1,          //!< mode1 update every angle update cycle (FIR_MD setting)
		mode2,          //!< mode2 update every 1.5 revolutions
		mode3           //!< mode3 update every 11.25°
	};

	/*!
	 * List of possible interface types
	 * witch are preset by fuses and can
	 * be changed into each other
	 */
	enum interfaceType
	{
		IIF = 0,  //!< IIF Incremental Interface (IIF)
		PWM,      //!< PWM Pulse-Width-Modulation (PWM)
		HSM,      //!< HSM Hall Switch Mode (HSM)
		SPC,      //!< SPC Short-PWM-Code (SPC)
		SSC       //!< SSC Synchronous Serial Communication (SSC)
	};

	/*!
	 * List of possible Sensor types and PCB variants
	 * with and without attached XMC2Go
	 */
	enum sensorType
	{
		TLE5012B_E1000= 0x0,//!< TLE5012B_E1000 Sensor2Go variant
		TLE5012B_E3005,     //!< TLE5012B_E3005
		TLE5012B_E5000,     //!< TLE5012B_E5000 Sensor2Go variant
		TLE5012B_E5020,     //!< TLE5012B_E5020
		TLE5012B_E9000,     //!< TLE5012B_E9000 Sensor2Go variant
	};

	using Tle5012b::Tle5012b;   //!< Using the inherited constructor

	typedef struct stat_t       //!< Status register 0x00
	{
		boolean RDST;           //!< bits 15:15 Read status
		uint8_t SNR;            //!< bits 14:13 Slave number
		boolean NOGMRA;         //!< bits 12:12 No valid GMR angle value
		boolean NOGMRXY;        //!< bits 11:11 No valid GMR XY values
		boolean SROM;           //!< bits 10:10 Status ROM
		boolean SADCT;          //!< bits 9:9 Status ADC Test
		boolean Reserved1;      //!< bits 8:8
		boolean SMAGOL;         //!< bits 7:7 Status magnitude out of Limit
		boolean SXYOL;          //!< bits 6:6 Status  X,Y Data out of Limit
		boolean SOV;            //!< bits 5:5 Status overflow
		boolean SDSPU;          //!< bits 4:4 Status digital signal processing unit
		boolean SFUSE;          //!< bits 3:3 Status fuse CRC
		boolean SVR;            //!< bits 2:2 Status voltage regulator
		boolean SWD;            //!< bits 1:1 Status Watch dog
		boolean SRST;           //!< bits 0:0 Status Reset
		uint16_t reg;           //!< the register value

		boolean fetch_SRST(uint16_t reg) {SRST = (reg & 0x1);return (SRST);}                        //!< status reset
		boolean fetch_SWD(uint16_t reg) {SWD = (reg & 0x2) >> 1;return (SWD);}                      //!< status watch dog
		boolean fetch_SVR(uint16_t reg) {SVR = (reg & 0x4) >> 2;return (SVR);}                      //!< status voltage regulator
		boolean fetch_SFUSE(uint16_t reg) {SFUSE = (reg & 0x8) >> 3;return (SFUSE);}                //!< status fuses
		boolean fetch_SDSPU(uint16_t reg) {SDSPU = (reg & 0x10) >> 4;return (SDSPU);}               //!< status digital signal processing unit
		boolean fetch_SXYOL(uint16_t reg) {SXYOL = (reg & 0x20) >> 5;return (SXYOL);}               //!< status overflow
		boolean fetch_SOV(uint16_t reg) {SOV = (reg & 0x40) >> 6;return (SOV);}                     //!< status X/Y data out limit
		boolean fetch_SMAGOL(uint16_t reg) {SMAGOL = (reg & 0x80) >> 7;return (SMAGOL);}            //!< status magnitude out limit
		boolean fetch_Reserved1(uint16_t reg) {Reserved1 = (reg & 0x100) >> 8;return (Reserved1);}  //!< reserved
		boolean fetch_SADCT(uint16_t reg) {SADCT = (reg & 0x200) >> 9;return (SADCT);}              //!< status ADC test
		boolean fetch_SROM(uint16_t reg) {SROM = (reg & 0x400) >> 10;return (SROM);}                //!< status ROM
		boolean fetch_NOGMRXY(uint16_t reg) {NOGMRXY = (reg & 0x800) >> 11;return (NOGMRXY);}       //!< no valid GMR XY Values
		boolean fetch_NOGMRA(uint16_t reg) {NOGMRA = (reg & 0x1000) >> 12;return (NOGMRA);}         //!< no valid GMR Angle Value
		uint8_t fetch_SNR(uint16_t reg) {SNR = (reg & 0x6000) >> 13;return (SNR);}                  //!< slave number
		boolean fetch_RDST(uint16_t reg) {RDST = (reg & 0x8000) >> 15;return (RDST);}               //!< read status
	};

	typedef struct acstat_t     //!< Activation Status register offset 0x01
	{
		uint8_t Reserved1;      //!< bits 15:11
		boolean ASFRST;         //!< bits 10:10 Activation of Firmware Reset
		boolean ASADCT;         //!< bits 9:9 Enable ADC Test vector Check
		boolean Reserved2;      //!< bits 8:8
		boolean ASVEGMAG;       //!< bits 7:7 Activation of Magnitude Check
		boolean ASVECXY;        //!< bits 6:6 Activation of X,Y Out of Limit-Check
		boolean ASOV;           //!< bits 5:5 Enable of DSPU Overflow Check
		boolean ASDSPU;         //!< bits 4:4 Activation DSPU BIST
		boolean ASFUSE;         //!< bits 3:3 Activation Fuse CRC
		boolean ASVR;           //!< bits 2:2 Enable Voltage regulator Check
		boolean ASWD;           //!< bits 1:1 Enable DSPU Watch dog
		boolean ASRST;          //!< bits 0:0 Activation of Hardware Reset
		uint16_t reg;           //!< the register value

		boolean fetch_ASRST(uint16_t reg) {ASRST = (reg & 0x1);return (ASRST);}
		boolean fetch_ASWD(uint16_t reg) {ASWD = (reg & 0x2) >> 1;return (ASWD);}
		boolean fetch_ASVR(uint16_t reg) {ASVR = (reg & 0x4) >> 2;return (ASVR);}
		boolean fetch_ASFUSE(uint16_t reg) {ASFUSE = (reg & 0x8) >> 3;return (ASFUSE);}
		boolean fetch_ASDSPU(uint16_t reg) {ASDSPU = (reg & 0x10) >> 4;return (ASDSPU);}
		boolean fetch_ASOV(uint16_t reg) {ASOV = (reg & 0x20) >> 5;return (ASOV);}
		boolean fetch_ASVECXY(uint16_t reg) {ASVECXY = (reg & 0x40) >> 6;return (ASVECXY);};
		boolean fetch_ASVEGMAG(uint16_t reg) {ASVEGMAG = (reg & 0x80) >> 7;return (ASVEGMAG);}
		boolean fetch_Reserved2(uint16_t reg) {Reserved2 = (reg & 0x100) >> 8;return (Reserved2);}
		boolean fetch_ASADCT(uint16_t reg) {ASADCT = (reg & 0x200) >> 9;return (ASADCT);}
		boolean fetch_ASFRST(uint16_t reg) {ASFRST = (reg & 0x400) >> 10;return (ASFRST);}
		uint8_t fetch_Reserved1(uint16_t reg) {Reserved1 = (reg & 0xF800) >> 11;return (Reserved1);}
	};

	typedef struct aval_t       //!< Angle Value register offset 0x02
	{
		uint16_t ANGVAL;        //!< bits 14:0 Calculated Angle Value (signed 15-bit)
		boolean RDAV;           //!< bits 15:15  Read Status, Angle Value
		uint16_t reg;           //!< the register value

		boolean fetch_ANGVAL(uint16_t reg) {ANGVAL = (reg & 0x7FFF);return (ANGVAL);}
		uint16_t fetch_RDAV(uint16_t reg) {RDAV = (reg & 0x8000) >> 15;return (RDAV);}
	};

	typedef struct aspd_t       //!< Angle Speed register offset 0x03
	{
		uint16_t ANGSPD;        //!< bits 14:0 Signed value, where the sign bit [14] indicates the direction of the rotation.
		boolean RDAS;           //!< bits 15:15 Read Status, Angle Speed
		uint16_t reg;           //!< the register value

		boolean fetch_ANGSPD(uint16_t reg) {ANGSPD = (reg & 0x7FFF);return (ANGSPD);}
		uint16_t fetch_RDAS(uint16_t reg) {RDAS = (reg & 0x8000) >> 15;return (RDAS);}
	};

	typedef struct arev_t       //!< Angle Revolution register offset 0x04
	{
		int16_t REVOL;          //!< bits 8:0 Revolution counter. Increments for every full rotation in counter-clockwise direction
		uint16_t FCNT;          //!< bits 14:9 Internal frame counter. Increments every update period
		boolean RDREV;          //!< bits 15:15 Read Status, Revolution
		uint16_t reg;           //!< the register value

		uint16_t fetch_FCNT(uint16_t reg) {FCNT = (reg & 0x7E00) >> 9;return (FCNT);}        //!< Frame Counter
		boolean fetch_RDREV(uint16_t reg) {RDREV = (reg & 0x8000) >> 15;return (RDREV);}     //!< Read Status, Revolution
		int16_t fetch_REVOL(uint16_t reg)
		{
			REVOL = (reg & 0xFF);
			if (REVOL & 0x100)
			{
				REVOL = REVOL * -1;
			}
			return (REVOL);
		}
	};

	typedef struct fsync_t      //!< Frame Synchronization register offset 0x05
	{
		uint16_t FSYNC;         //!< bits 15:9 Frame Synchronization Counter Value
		int16_t TEMPR;          //!< bits 8:0 Signed offset compensated temperature value.
		uint16_t reg;           //!< the register value

		int16_t fetch_TEMPR(uint16_t reg)
		{
			TEMPR = (reg & 0xFF);
			if (TEMPR & 0x100)
			{
				TEMPR = TEMPR * -1;
			}
			return (TEMPR);
		}
		uint16_t fetch_FSYNC(uint16_t reg)
		{
			FSYNC = (reg & 0xFE00) >> 9;
			return (FSYNC);
		}
	};

	typedef struct mod1_t       //!< MOD_1 Interface Mode1 register offset 0x06
	{
		uint8_t FIRMD;          //!< bits 15:14 Update Rate Setting
		uint16_t Reserverd1;    //!< bits 13:5
		boolean CLKSEL;         //!< bits 4:4 Switch to external clock at start-up only.
		boolean Reserverd2;     //!< bits 3:3
		boolean DSPUHOLD;       //!< bits 2:2 If DSPU is on hold, no watch dog reset is performed by DSPU
		uint8_t IIFMOD;         //!< bits 1:0 Incremental Interface Mode
		uint16_t reg;           //!< the register value

		uint8_t fetch_IIFMOD(uint16_t reg) {IIFMOD = (reg & 0x3);return (IIFMOD);}
		boolean fetch_DSPUHOLD(uint16_t reg) {DSPUHOLD = (reg & 0x4) >> 2;return (DSPUHOLD);}
		uint16_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0x8) >> 3;return (Reserverd1);}
		boolean fetch_CLKSEL(uint16_t reg) {CLKSEL = (reg & 0x10) >> 4;return (CLKSEL);}
		boolean fetch_Reserverd2(uint16_t reg) {Reserverd2 = (reg & 0x3FE0) >> 5;return (Reserverd2);}
		uint8_t fetch_FIRMD(uint16_t reg) {FIRMD = (reg & 0x6000) >> 13;return (FIRMD);}
	};

	typedef struct sil_t        //!< SIL register offset 0x07
	{
		boolean FILTPAR;        //!< bits 15:15
		boolean FILTINV;        //!< bits 14:14 The raw X-signal is routed also to the raw Y-signal input of the filter so SIN and COS signal should be identical.
		uint8_t Reserverd1;     //!< bits 13:11 The X- and Y-signals are inverted. The angle output is then shifted by 180°.
		boolean FUSEREL;        //!< bits 10:10 Triggers reload of default values from laser fuses into configuration registers.
		uint8_t Reserverd2;     //!< bits 9:7
		boolean ADCTVEN;        //!< bits 6:6 Sensor elements are internally disconnected and test voltages are connected to ADCs.
		uint8_t ADCTVY;         //!< bits 5:3 Test vector X
		uint8_t ADCTVX;         //!< bits 2:0 Test vector Y
		uint16_t reg;           //!< the register value

		uint8_t fetch_ADCTVX(uint16_t reg) {ADCTVX = (reg & 0x7);return (ADCTVX);}
		uint8_t fetch_ADCTVY(uint16_t reg) {ADCTVY = (reg & 0x38) >> 3;return (ADCTVY);}
		boolean fetch_ADCTVEN(uint16_t reg) {ADCTVEN = (reg & 0x40) >> 6;return (ADCTVEN);}
		uint8_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0x380) >> 7;return (Reserverd1);}
		boolean fetch_FUSEREL(uint16_t reg) {FUSEREL = (reg & 0x400) >> 10;return (FUSEREL);}
		uint8_t fetch_Reserverd2(uint16_t reg) {Reserverd2 = (reg & 0x3800) >> 11;return (Reserverd2);}
		boolean fetch_FILTINV(uint16_t reg) {FILTINV = (reg & 0x4000) >> 14;return (FILTINV);}
		boolean fetch_FILTPAR(uint16_t reg) {FILTPAR = (reg & 0x8000) >> 15;return (FILTPAR);}
	};

	typedef struct mod2_t       //!< MOD_2 Interface Mode2 register offset 0x08
	{
		boolean Reserverd1;     //!< bits 15:15
		uint16_t ANGRANGE;      //!< bits 14:4 Changes the representation of the angle output by multiplying the output with a factor ANG_RANGE/128.
		boolean ANGDIR;         //!< bits 3:3 Inverts angle and angle speed values and revolution counter behavior.
		boolean PREDICT;        //!< bits 2:2 Prediction of angle value based on current angle speed
		uint8_t AUTOCAL;        //!< bits 1:0 Automatic calibration of offset and amplitude synchronicity for applications with full-turn.
		uint16_t reg;           //!< the register value

		uint8_t fetch_AUTOCAL(uint16_t reg) {AUTOCAL = (reg & 0x3);return (AUTOCAL);}
		boolean fetch_PREDICT(uint16_t reg) {PREDICT = (reg & 0x4) >> 2;return (PREDICT);}
		boolean fetch_ANGDIR(uint16_t reg) {ANGDIR = (reg & 0x8) >> 3;return (ANGDIR);}
		uint16_t fetch_ANGRANGE(uint16_t reg) {ANGRANGE = (reg & 0x7FF0) >> 4;return (ANGRANGE);}
		boolean fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0x8000) >> 15;return (Reserverd1);}
	};

	typedef struct mod3_t       //!< MOD_3 Interface Mode3 register offset 0x09
	{
		uint16_t ANG_BASE;      //!< bits 15:4 Sets the 0° angle position (12 bit value). Angle base is factory-calibrated to make the 0° direction parallel to the edge of the chip.
		boolean SPIKEF;         //!< bits 3:3 Filters voltage spikes on input pads (IFC, SCK and CSQ).
		boolean SSCOD;          //!< bits 2:2 SSC-Interface Data Pin Output Mode
		uint8_t PADDRV;         //!< bits 1;0 Configuration of Pad-Driver
		uint16_t reg;           //!< the register value

		uint8_t fetch_PADDRV(uint16_t reg) {PADDRV = (reg & 0x3);return (PADDRV);}
		boolean fetch_SSCOD(uint16_t reg) {SSCOD = (reg & 0x4) >> 2;return (SSCOD);}
		boolean fetch_SPIKEF(uint16_t reg) {SPIKEF = (reg & 0x8) >> 3;return (SPIKEF);}
		uint16_t fetch_ANG_BASE(uint16_t reg) {ANG_BASE = (reg & 0xFFF0) >> 4;return (ANG_BASE);}
	};

	typedef struct offx_t       //!< Offset X offset 0x0a
	{
		int16_t XOFFSET;        //!< bits 15:4 12-bit signed integer value of raw X-signal offset correction at 25°C.
		uint8_t Reserverd1;     //!< bits 3:0
		uint16_t reg;           //!< the register value

		uint8_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0xF);return (Reserverd1);}
		int16_t fetch_XOFFSET(uint16_t reg)
		{
			XOFFSET = ((reg & 0xFFF0) >> 4);
			if (XOFFSET & 0x800)
			{
				XOFFSET = XOFFSET * -1;
			}
			return (XOFFSET);
		}
	};

	typedef struct offy_t       //!< Offset Y offset 0x0b
	{
		int16_t YOFFSET;        //!< bits 15:4 12-bit signed integer value of raw Y-signal offset correction at 25°C.
		uint8_t Reserverd1;     //!< bits 3:0
		uint16_t reg;           //!< the register value

		uint8_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0xF);return (Reserverd1);}
		int16_t fetch_YOFFSET(uint16_t reg)
		{
			YOFFSET = ((reg & 0xFFF0) >> 4);
			if (YOFFSET & 0x800)
			{
				YOFFSET = YOFFSET * -1;
			}
			return (YOFFSET);
		}
	};

	typedef struct synch_t {	//!< Synchronicity offset 0x0c
		int16_t SYNCH;			//!< bits 15:4 12-bit signed integer value of amplitude synchronicity
		uint8_t Reserverd1;		//!< bits 3:0
		uint16_t reg;			//!< the register value

		uint8_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0xF);return (Reserverd1);}
		int16_t fetch_SYNCH(uint16_t reg) {
			SYNCH = ((reg & 0xFFF0) >> 4);
			if (SYNCH & 0x800) {
				SYNCH = SYNCH * -1;
			}
			return (SYNCH);
		}
	};

	typedef struct ifab_t {		//!< IFAB register offset 0x0d
		int16_t ORTHO;			//!< bits 15:4 Orthogonality Correction of X and Y Components
		boolean FIRUDR;			//!< bits 3:3 Initial filter update rate (FIR)
		boolean IFABOD;			//!< bits 2:2 IFA,IFB,IFC Output Mode
		uint8_t IFADHYST;		//!< bits 1:0 Hysteresis (multi-purpose)
		uint16_t reg;			//!< the register value

		uint8_t fetch_IFADHYST(uint16_t reg) {IFADHYST = (reg & 0x3);return (IFADHYST);}
		boolean fetch_IFABOD(uint16_t reg) {IFABOD = (reg & 0x4) >> 2;return (IFABOD);}
		boolean fetch_FIRUDR(uint16_t reg) {FIRUDR = (reg & 0x8) >> 3;return (FIRUDR);}
		int16_t fetch_ORTHO(uint16_t reg) {
			ORTHO = ((reg & 0xFFF0) >> 4);
			if (ORTHO & 0x800) {
				ORTHO = ORTHO * -1;
			}
			return (ORTHO);
		}
	};

	typedef struct mod4_t {		//!< MOD_4 Interface Mode4 register offset 0x0e
		int8_t TCOXT;			//!< bits 15:9 7-bit signed integer value of X-offset temperature coefficient.
		uint8_t HSMPLP;			//!< bits 8:5 Hall Switch mode (multi-purpose)
		uint8_t IFABRES;		//!< bits 4:3 IIF resolution (multi-purpose)
		boolean Reserverd1;		//!< bits 2:2
		uint8_t IFMD;			//!< bits 1:0 Interface Mode on IFA,IFB,IFC
		uint16_t reg;			//!< the register value

		uint8_t fetch_IFMD(uint16_t reg) {IFMD = (reg & 0x3);return (IFMD);}
		boolean fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0x4) >> 2;return (Reserverd1);}
		uint8_t fetch_IFABRES(uint16_t reg) {IFABRES = (reg & 0x18) >> 3;return (IFABRES);}
		uint8_t fetch_HSMPLP(uint16_t reg) {HSMPLP = (reg & 0x1E0) >> 5;return (HSMPLP);}
		int8_t fetch_TCOXT(uint16_t reg) {
			TCOXT = ((reg & 0x7E00) >> 9);
			if (TCOXT & 0x8000) {
				TCOXT = TCOXT * -1;
			}
			return (TCOXT);
		}
	};

	typedef struct tcoy_t {		//!< TCO_Y Temperature Coefficient register offset 0x0f
		int8_t TCOYT;			//!< bits 15:9 7-bit signed integer value of Y-offset temperature coefficient.
		boolean SBIST;			//!< bits 8:8 Startup-BIST
		uint16_t CRCPAR;		//!< bits 7:0 CRC of Parameters
		uint16_t reg;			//!< the register value

		uint16_t fetch_CRCPAR(uint16_t reg) {TCOYT = (reg & 0x7F);return (TCOYT);}
		boolean fetch_SBIST(uint16_t reg) {SBIST = (reg & 0x80) >> 8;return (SBIST);}
		int8_t fetch_TCOYT(uint16_t reg) {
			TCOYT = ((reg & 0x7E00) >> 9);
			if (TCOYT & 0x8000) {
				TCOYT = TCOYT * -1;
			}
			return (TCOYT);
		}
	};

	typedef struct adc_t {		//!< ADC_X offset 0x10, ADC_Y offset 0x11
		int16_t ADCX;			//!< bits 15:0 ADC value of X-GMR
		int16_t ADCY;			//!< bits 15:0 ADC value of Y-GMR
	};

	typedef struct dmag_t {		//!< D_Mag vector magnitude offset 0x14
		uint8_t Reserverd1;		//!< bits 15:10
		uint16_t MAG;			//!< bits 9:0 Unsigned Angle Vector Magnitude after X, Y error compensation (due to temperature).
		uint16_t reg;			//!< the register value

		uint16_t fetch_MAG(uint16_t reg) {MAG = (reg & 0x3FF);return (MAG);}
		uint8_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0xFC00) >> 10;return (Reserverd1);}
	};

	typedef struct traw_t {		//!< T_RAW temperature raw data offset 0x15
		boolean TTGL;			//!< bits 15:15 Temperature Sensor Raw-Value Toggle toggles after every new temperature value
		uint8_t Reserverd1;		//!< bits 14:10
		uint16_t TRAW;			//!< bits 9:0 Temperature Sensor Raw-Value at ADC without offset
		uint16_t reg;			//!< the register value

		boolean fetch_TRAW(uint16_t reg) {TRAW = (reg & 0x3FF);return (TRAW);}
		uint8_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0xFC00) >> 10;return (Reserverd1);}
		uint16_t fetch_TTGL(uint16_t reg) {TTGL = (reg & 0x8000) >> 15;return (TTGL);}
	};

	typedef struct iifcnt_t {	//!< IIF counter value offset 0x20
		boolean Reserverd1;		//!< bits 15:14
		uint16_t IIFCNT;		//!< bits 14:0 14 bit counter value of IIF increments
		uint16_t reg;			//!< the register value

		uint16_t fetch_IIFCNT(uint16_t reg) {IIFCNT = (reg & 0x7FFF);return (IIFCNT);}
		boolean fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0x8000) >> 15;return (Reserverd1);}
	};

	typedef struct t250_t {		//!< register T250 offset 0x30
		int16_t T250;			//!< bits 15:9 Signed offset value at 25°C temperature; 1dig=0.36°C.
		uint16_t Reserverd1;	//!< bit 8:0
		uint16_t reg;			//!< the register value

		int16_t fetch_T250(uint16_t reg) {T250 = (reg & 0x1FFF);return (T250);}
		uint16_t fetch_Reserverd1(uint16_t reg) {Reserverd1 = (reg & 0xFE00) >> 9;return (Reserverd1);}
	};

	typedef struct {
		uint16_t registers[MAX_NUM_REG];	//!< raw register memory
		interfaceType interface;			//!< enum identify the Interface type
		sensorType sensorBoard;				//!< enum identify the PCM board type
		String interfaceName;
		String sensorName;
		String nameOfRegister[MAX_NUM_REG] = {
				"STAT  ","ACSTAT","AVAL  ","ASPD  ","AREV  ",
				"FSYNC ","MOD1  ","SIL   ","MOD2  ","MOD3  ",
				"OFFX  ","OFFY  ","SYNCH ","IFAB  ","MOD4  ",
				"TCOY  ","ADCX  ","ADCY  ","DMAG  ","TRAW  ",
				"IIFCNT","T250  "
		};
		struct stat_t stat;
		struct acstat_t acstat;
		struct aval_t aval;
		struct aspd_t aspd;
		struct arev_t arev;
		struct fsync_t fsync;
		struct mod1_t mod1;
		struct sil_t sil;
		struct mod2_t mod2;
		struct mod3_t mod3;
		struct offx_t offx;
		struct offy_t offy;
		struct synch_t synch;
		struct ifab_t ifab;
		struct mod4_t mod4;
		struct tcoy_t tcoy;
		struct adc_t adc;
		struct dmag_t dmag;
		struct traw_t traw;
		struct iifcnt_t iifcnt;
		struct t250_t t250;
	} regSensor_t;

	regSensor_t sensorRegister;		//!< sensor register read and separation

	/*!
	 * Function reads all readable sensor registers
	 * and separates the information fields. This function
	 * is needed for finding the selected interface type.
	 * @param [in,out] sensorRegister point to the sensor register structure
	 * @return CRC error type
	 */
	errorTypes readSensorType();

	/*!
	 * Function identifies the current set interface type
	 * according some characteristic register settings
	 * @return CRC error type
	 */
	errorTypes identifyInterfaceType();

	/*!
	 * Functions switches between all possible interface types.
	 * ATTENTION: The different interfaces support not always all
	 * values, see documentation for the ability of each interface.
	 * If you want to be save, than choose the default SSC interface
	 * which always supports all possible parameter.
	 * @param iface type of interface to switch to
	 * @return CRC error type
	 */
	errorTypes writeInterfaceType(interfaceType iface);

	/*!
	 * Function reset the Sensor to fuse defaults
	 * @return CRC error type
	 */
	errorTypes resetFirmware();

	/*!
	 * Function set the sensors calibration mode. Keep in mind,
	 * not all Sensor interface setups have the autocalibration
	 * switched on, so maybe you have to set it explicitly.
	 * @param [in] calibrationMode the auto calibration mode to set
	 * @return CRC error type
	 */
	errorTypes setCalibration(calibrationMode calMode);


	private:

	/*!
	 * Identify the sensor interface and PCB board
	 */
	void identify();

};

#endif
