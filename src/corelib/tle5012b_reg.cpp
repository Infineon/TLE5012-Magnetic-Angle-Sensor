/*!
 * \file        tle5012b_reg.cpp
 * \name        tle5012b_reg.cpp - core support for the TLE5012B angle sensor.
 * \author      Infineon Technologies AG
 * \copyright   2019-2020 Infineon Technologies AG
 * \version     3.0.0
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \details
 *              This file includes the registry definition macros of all Sensor registers and
 *              the bit settings for each of the register content values. Depending on
 *              the type of secondary interface (PWM, IIF or HSM) the meaning of some register values
 *              differs, so please have look in the TLE5012 manual for the exact meaning.
 *              Also included here are other sensefull macros for handling the TLE5012 sensor.
 * \ref         tle5012corelib
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "TLE5012b.hpp"
#include "tle5012b_reg.hpp"

const Reg::BitField_t Reg::bitFields[] =
{
	{ REG_ACCESS_R,     REG_STAT,         0x2,    1,   0x00 },          //!< bits 0:0 SRST status watch dog
	{ REG_ACCESS_R,     REG_STAT,         0x2,    1,   0x00 },          //!< bits 1:1 SWD status watch dog
	{ REG_ACCESS_R,     REG_STAT,         0x4,    2,   0x00 },          //!< bits 2:2 SVR status voltage regulator
	{ REG_ACCESS_R,     REG_STAT,         0x8,    3,   0x00 },          //!< bits 3:3 SFUSE status fuses
	{ REG_ACCESS_R,     REG_STAT,         0x10,   4,   0x00 },          //!< bits 4:4 SDSPU status digital signal processing unit
	{ REG_ACCESS_R,     REG_STAT,         0x20,   5,   0x00 },          //!< bits 5:5 SOV status overflow
	{ REG_ACCESS_R,     REG_STAT,         0x40,   6,   0x00 },          //!< bits 6:6 SXYOL status X/Y data out limit
	{ REG_ACCESS_R,     REG_STAT,         0x80,   7,   0x00 },          //!< bits 7:7 SMAGOL status magnitude out limit
	{ REG_ACCESS_R,     REG_STAT,         0x100,  8,   0x00 },          //!< bits 8:8 reserved
	{ REG_ACCESS_R,     REG_STAT,         0x200,  9,   0x00 },          //!< bits 9:9 SADCT status ADC test
	{ REG_ACCESS_R,     REG_STAT,         0x400,  10,  0x00 },          //!< bits 10:10 SROM status ROM
	{ REG_ACCESS_R,     REG_STAT,         0x800,  11,  0x00 },          //!< bits 11:11 NOGMRXY no valid GMR XY Values
	{ REG_ACCESS_R,     REG_STAT,         0x1000, 12,  0x00 },          //!< bits 12:12 NOGMRA no valid GMR Angle Value
	{ REG_ACCESS_R,     REG_STAT,         0x6000, 13,  0x00 },          //!< bits 14:13 SNR slave number
	{ REG_ACCESS_R,     REG_STAT,         0x8000, 15,  0x00 },          //!< bits 15:15 RDST read status

	{ REG_ACCESS_R,     REG_ACSTAT,       0x1,    0,   0x00 },          //!< bits 0:0 ASRST Activation of Hardware Reset
	{ REG_ACCESS_R,     REG_ACSTAT,       0x2,    1,   0x00 },          //!< bits 1:1 ASWD Enable DSPU Watch dog
	{ REG_ACCESS_R,     REG_ACSTAT,       0x4,    2,   0x00 },          //!< bits 2:2 ASVR Enable Voltage regulator Check
	{ REG_ACCESS_R,     REG_ACSTAT,       0x8,    3,   0x00 },          //!< bits 3:3 ASFUSE Activation Fuse CRC
	{ REG_ACCESS_R,     REG_ACSTAT,       0x10,   4,   0x00 },          //!< bits 4:4 ASDSPU Activation DSPU BIST
	{ REG_ACCESS_R,     REG_ACSTAT,       0x20,   5,   0x00 },          //!< bits 5:5 ASOV Enable of DSPU Overflow Check
	{ REG_ACCESS_R,     REG_ACSTAT,       0x40,   6,   0x00 },          //!< bits 6:6 ASVECXY Activation of X,Y Out of Limit-Check
	{ REG_ACCESS_R,     REG_ACSTAT,       0x80,   7,   0x00 },          //!< bits 7:7 ASVEGMAG Activation of Magnitude Check
	{ REG_ACCESS_R,     REG_ACSTAT,       0x100,  8,   0x00 },          //!< bits 8:8 Reserved
	{ REG_ACCESS_R,     REG_ACSTAT,       0x200,  9,   0x00 },          //!< bits 9:9 ASADCT Enable ADC Test vector Check
	{ REG_ACCESS_R,     REG_ACSTAT,       0x400,  10,  0x00 },          //!< bits 10:10 ASFRST Activation of Firmware Reset
	{ REG_ACCESS_R,     REG_ACSTAT,       0xF800, 11,  0x00 },          //!< bits 15:11 Reserved

	{ REG_ACCESS_R,     REG_AVAL,         0x7FFF, 0,   0x00 },          //!< bits 14:0 ANGVAL Calculated Angle Value (signed 15-bit)
	{ REG_ACCESS_R,     REG_AVAL,         0x8000, 15,  0x00 },          //!< bits 15:15 RDAV Read Status, Angle Value

	{ REG_ACCESS_R,     REG_ASPD,         0x7FFF, 0,   0x00 },          //!< bits 14:0 ANGSPD Signed value, where the sign bit [14] indicates the direction of the rotation
	{ REG_ACCESS_R,     REG_ASPD,         0x8000, 15,  0x00 },          //!< bits 15:15 RDAS Read Status, Angle Speed

	{ REG_ACCESS_R,     REG_AREV,         0xFF,   0,   0x00 },          //!< bits 8:0 REVOL Revolution counter. Increments for every full rotation in counter-clockwise direction
	{ REG_ACCESS_R,     REG_AREV,         0x7E00, 9,   0x00 },          //!< bits 14:9 FCNT Internal frame counter. Increments every update period
	{ REG_ACCESS_R,     REG_AREV,         0x8000, 15,  0x00 },          //!< its 15:15 RDREV Read Status, Revolution

	{ REG_ACCESS_R,     REG_FSYNC,        0xFF,   0,   0x00 },          //!< bits 8:0 TEMPR Signed offset compensated temperature value
	{ REG_ACCESS_R,     REG_FSYNC,        0xFE00, 9,   0x00 },          //!< bits 15:9 FSYNC Frame Synchronization Counter Value

	{ REG_ACCESS_R,     REG_MOD_1,        0x3,    0,   0x00 },          //!< bits 1:0 IIFMOD Incremental Interface Mode
	{ REG_ACCESS_R,     REG_MOD_1,        0x4,    2,   0x00 },          //!< bits 2:2 DSPUHOLD if DSPU is on hold, no watch dog reset is performed by DSPU
	{ REG_ACCESS_R,     REG_MOD_1,        0x8,    3,   0x00 },          //!< bits 3:3 Reserved1
	{ REG_ACCESS_R,     REG_MOD_1,        0x10,   4,   0x00 },          //!< bits 4:4 CLKSEL switch to external clock at start-up only
	{ REG_ACCESS_R,     REG_MOD_1,        0x3FE0, 5,   0x00 },          //!< bits 13:5 Reserved2
	{ REG_ACCESS_R,     REG_MOD_1,        0x6000, 13,  0x00 },          //!< bits 15:14 FIRMD Update Rate Setting

	{ REG_ACCESS_R,     REG_SIL,          0x7,    0,   0x00 },          //!< bits 2:0 ADCTVX Test vector X
	{ REG_ACCESS_R,     REG_SIL,          0x38,   3,   0x00 },          //!< bits 5:3 ADCTVY Test vector Y
	{ REG_ACCESS_R,     REG_SIL,          0x40,   6,   0x00 },          //!< bits 6:6 ADCTVEN Sensor elements are internally disconnected and test voltages are connected to ADCs
	{ REG_ACCESS_R,     REG_SIL,          0x380,  7,   0x00 },          //!< bits 9:7 Reserved1
	{ REG_ACCESS_R,     REG_SIL,          0x400,  10,  0x00 },          //!< bits 10:10 FUSEREL Triggers reload of default values from laser fuses into configuration registers
	{ REG_ACCESS_R,     REG_SIL,          0x3800, 11,  0x00 },          //!< bits 13:11 Reserved2
	{ REG_ACCESS_R,     REG_SIL,          0x4000, 14,  0x00 },          //!< bits 14:14 FILTINV the X- and Y-signals are inverted. The angle output is then shifted by 180°
	{ REG_ACCESS_R,     REG_SIL,          0x8000, 15,  0x00 },          //!< bits 15:15 FILTPAR the raw X-signal is routed also to the raw Y-signal input of the filter so SIN and COS signal should be identical

	{ REG_ACCESS_R,     REG_MOD_2,        0x3,    0,   0x00 },          //!< bits 1:0 AUTOCAL Automatic calibration of offset and amplitude synchronicity for applications with full-turn
	{ REG_ACCESS_R,     REG_MOD_2,        0x4,    2,   0x00 },          //!< bits 2:2 PREDICT Prediction of angle value based on current angle speed
	{ REG_ACCESS_R,     REG_MOD_2,        0x8,    3,   0x00 },          //!< bits 3:3 ANGDIR Inverts angle and angle speed values and revolution counter behavior
	{ REG_ACCESS_R,     REG_MOD_2,        0x7FF0, 4,   0x00 },          //!< bits 14:4 ANGRANGE Changes the representation of the angle output by multiplying the output with a factor ANG_RANGE/128
	{ REG_ACCESS_R,     REG_MOD_2,        0x8000, 15,  0x00 },          //!< bits 15:15 Reserved1

	{ REG_ACCESS_R,     REG_MOD_3,        0x3,    0,   0x00 },          //!< bits 1:0 PADDRV Configuration of Pad-Driver
	{ REG_ACCESS_R,     REG_MOD_3,        0x4,    2,   0x00 },          //!< bits 2:2 SSCOD SSC-Interface Data Pin Output Mode
	{ REG_ACCESS_R,     REG_MOD_3,        0x8,    3,   0x00 },          //!< bits 3:3 SPIKEF Filters voltage spikes on input pads (IFC, SCK and CSQ)
	{ REG_ACCESS_R,     REG_MOD_3,        0xFFF0, 4,   0x00 },          //!< bits 15:4 ANG_BASE Sets the 0° angle position (12 bit value). Angle base is factory-calibrated to make the 0° direction parallel to the edge of the chip

	{ REG_ACCESS_R,     REG_OFFX,         0xF,    0,   0x00 },          //!< bits 3:0 Reserved1
	{ REG_ACCESS_R,     REG_OFFX,         0xFFF0, 4,   0x00 },          //!< bits 15:4 XOFFSET 12-bit signed integer value of raw X-signal offset correction at 25°C

	{ REG_ACCESS_R,     REG_OFFY,         0xF,    0,   0x00 },          //!< bits 3:0 Reserved1
	{ REG_ACCESS_R,     REG_OFFY,         0xFFF0, 4,   0x00 },          //!< bits 15:4 YOFFSET 12-bit signed integer value of raw Y-signal offset correction at 25°C

	{ REG_ACCESS_R,     REG_SYNCH,        0xF,    0,   0x00 },          //!< bits 3:0 Reserved1
	{ REG_ACCESS_R,     REG_SYNCH,        0xFFF0, 4,   0x00 },          //!< bits 15:4 SYNCH 12-bit signed integer value of amplitude synchronicity


	{ REG_ACCESS_R,     REG_IFAB,         0x3,    0,   0x00 },          //!< bits 1:0 IFADHYST Hysteresis (multi-purpose)
	{ REG_ACCESS_R,     REG_IFAB,         0x4,    2,   0x00 },          //!< bits 2:2 IFABOD IFA,IFB,IFC Output Mode
	{ REG_ACCESS_R,     REG_IFAB,         0x8,    3,   0x00 },          //!< bits 3:3 FIRUDR Initial filter update rate (FIR)
	{ REG_ACCESS_R,     REG_IFAB,         0xFFF0, 4,   0x00 },          //!< bits 15:4 ORTHO Orthogonality Correction of X and Y Components


	{ REG_ACCESS_R,     REG_MOD_4,        0x3,    0,   0x00 },          //!< bits 1:0 IFMD Interface Mode on IFA,IFB,IFC
	{ REG_ACCESS_R,     REG_MOD_4,        0x4,    2,   0x00 },          //!< bits 2:2 Reserved1
	{ REG_ACCESS_R,     REG_MOD_4,        0x18,   3,   0x00 },          //!< bits 4:3 IFABRES IIF resolution (multi-purpose)
	{ REG_ACCESS_R,     REG_MOD_4,        0x1E0,  5,   0x00 },          //!< bits 8:5 HSMPLP Hall Switch mode (multi-purpose)
	{ REG_ACCESS_R,     REG_MOD_4,        0x7E00, 9,   0x00 },          //!< bits 15:9 TCOXT 7-bit signed integer value of X-offset temperature coefficient


	{ REG_ACCESS_R,     REG_TCO_Y,        0x7F,   0,   0x00 },          //!< bits 7:0 CRCPAR CRC of Parameters
	{ REG_ACCESS_R,     REG_TCO_Y,        0x80,   8,   0x00 },          //!< bits 8:8 SBIST Startup-BIST
	{ REG_ACCESS_R,     REG_TCO_Y,        0x7E00, 9,   0x00 },          //!< bits 15:9 TCOYT 7-bit signed integer value of Y-offset temperature coefficient

	{ REG_ACCESS_R,     REG_ADC_X,        0xFFFF, 0,   0x00 },          //!< bits 15:0 ADCX ADC value of X-GMR

	{ REG_ACCESS_R,     REG_ADC_Y,        0xFFFF, 0,   0x00 },          //!< bits 15:0 ADCY ADC value of Y-GMR

	{ REG_ACCESS_R,     REG_D_MAG,        0x3FF,  0,   0x00 },          //!< bits 9:0 MAG Unsigned Angle Vector Magnitude after X, Y error compensation (due to temperature)
	{ REG_ACCESS_R,     REG_D_MAG,        0xFC00, 10,  0x00 },          //!< bits 15:10 Reserved1

	{ REG_ACCESS_R,     REG_T_RAW,        0x3FF,  0,   0x00 },          //!< bits 9:0 TRAW Temperature Sensor Raw-Value at ADC without offset
	{ REG_ACCESS_R,     REG_T_RAW,        0xFC00, 10,  0x00 },          //!< bits 14:10 Reserved1
	{ REG_ACCESS_R,     REG_T_RAW,        0x8000, 15,  0x00 },          //!< bits 15:15 TTGL Temperature Sensor Raw-Value Toggle toggles after every new temperature value

	{ REG_ACCESS_R,     REG_IIF_CNT,      0x7FFF, 0,   0x00 },          //!< bits 14:0 IIFCNT 14 bit counter value of IIF increments
	{ REG_ACCESS_R,     REG_IIF_CNT,      0x8000, 15,  0x00 },          //!< bits 15:14 Reserved1

	{ REG_ACCESS_R,     REG_T25O,         0x1FFF, 0,   0x00 },          //!< bit 8:0 T250 Signed offset value at 25°C temperature; 1dig=0.36°C
	{ REG_ACCESS_R,     REG_T25O,         0xFE00, 9,   0x00 },          //!< bits 15:9 Reserved1

};


Reg::Reg():regMap()
{
}

Reg::~Reg()
{
}


/**
 * @brief       Gets the bit field value 
 * 
 * @param[in]   bitField    Bit field parameters structure
 * @param[out]  bitFValue   Value of the bit field
 * @retval      TRUE if success
 * @retval      FALSE if register access denied
 * @pre         None
 */
bool Reg::getBitField(BitField_t bitField, uint8_t & bitFValue)
{
    bool err = false;

    if( (REG_ACCESS_R & bitField.regAccess) ==  REG_ACCESS_R)
    {
        bitFValue =  ((regMap[bitField.regAddress] & bitField.mask) >> bitField.position); 
        err = true;
    }

    return err;
}

/**
 * @brief       Sets the bit field value 
 * 
 * @param[in]   bitField        Bit field parameters structure
 * @param[in]   bitFNewValue    Value of the bit field
 * @retval      TRUE if success
 * @retval      FALSE if register access denied
 * @pre         None
 */
bool Reg::setBitField(BitField_t bitField, uint8_t bitFNewValue)
{
    bool err = false;

    if( (REG_ACCESS_W & bitField.regAccess) == REG_ACCESS_W)
    {
        regMap[bitField.regAddress] = (regMap[bitField.regAddress] & ~bitField.mask) | ((bitFNewValue << bitField.position) & bitField.mask);
        err = true;
    }

    return err;
}