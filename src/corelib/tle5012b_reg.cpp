/*!
 * \file        tle5012b_reg.cpp
 * \name        tle5012b_reg.cpp - core support for the TLEx012B angle sensor family.
 * \author      Infineon Technologies AG
 * \copyright   2019-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \details
 *              This file includes the registry definition macros of all Sensor registers and
 *              the bit settings for each of the register content values. Depending on
 *              the type of secondary interface (PWM, IIF or HSM) the meaning of some register values
 *              differs, so please have look in the TLE5012 manual for the exact meaning.
 *              Also included here are other senseful macros for handling the TLE5012 sensor.
 * \ref         tle5012corelib
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "TLE5012b.hpp"
#include "tle5012b_reg.hpp"

using namespace tle5012;

const Reg::AddressField_t Reg::addrFields[] =
{
    {REG_STAT,     1    },    //!< \brief STAT status register
    {REG_ACSTAT,   2    },    //!< \brief ACSTAT activation status register
    {REG_AVAL,     3    },    //!< \brief AVAL angle value register
    {REG_ASPD,     4    },    //!< \brief ASPD angle speed register
    {REG_AREV,     5    },    //!< \brief AREV angle revolution register
    {REG_FSYNC,    6    },    //!< \brief FSYNC frame synchronization register
    {REG_MOD_1,    7    },    //!< \brief MOD_1 interface mode1 register
    {REG_SIL,      8    },    //!< \brief SIL register
    {REG_MOD_2,    9    },    //!< \brief MOD_2 interface mode2 register
    {REG_MOD_3,   10    },    //!< \brief MOD_3 interface mode3 register
    {REG_OFFX,    11    },    //!< \brief OFFX offset x
    {REG_OFFY,    12    },    //!< \brief OFFY offset y
    {REG_SYNCH,   13    },    //!< \brief SYNCH synchronicity
    {REG_IFAB,    14    },    //!< \brief IFAB register
    {REG_MOD_4,   15    },    //!< \brief MOD_4 interface mode4 register
    {REG_TCO_Y,   16    },    //!< \brief TCO_Y temperature coefficient register
    {REG_ADC_X,   17    },    //!< \brief ADC_X ADC X-raw value
    {REG_ADC_Y,   18    },    //!< \brief ADC_Y ADC Y-raw value
    {REG_D_MAG,   19    },    //!< \brief D_MAG angle vector magnitude
    {REG_T_RAW,   20    },    //!< \brief T_RAW temperature sensor raw-value
    {REG_IIF_CNT, 21    },    //!< \brief IIF_CNT IIF counter value
    {REG_T25O,    22    },    //!< \brief T25O temperature 25°c offset value
};

const Reg::BitField_t Reg::bitFields[] =
{
    {REG_ACCESS_RU,  REG_STAT,    0x2,    1,  0x00,  0},       //!< 00 bits 0:0 SRST status watch dog
    {REG_ACCESS_R,   REG_STAT,    0x2,    1,  0x00,  0},       //!< 01 bits 1:1 SWD status watch dog
    {REG_ACCESS_R,   REG_STAT,    0x4,    2,  0x00,  0},       //!< 02 bits 2:2 SVR status voltage regulator
    {REG_ACCESS_R,   REG_STAT,    0x8,    3,  0x00,  0},       //!< 03 bits 3:3 SFUSE status fuses
    {REG_ACCESS_R,   REG_STAT,    0x10,   4,  0x00,  0},       //!< 04 bits 4:4 SDSPU status digital signal processing unit
    {REG_ACCESS_RU,  REG_STAT,    0x20,   5,  0x00,  0},       //!< 05 bits 5:5 SOV status overflow
    {REG_ACCESS_RU,  REG_STAT,    0x40,   6,  0x00,  0},       //!< 06 bits 6:6 SXYOL status X/Y data out limit
    {REG_ACCESS_RU,  REG_STAT,    0x80,   7,  0x00,  0},       //!< 07 bits 7:7 SMAGOL status magnitude out limit
    {REG_ACCESS_RES, REG_STAT,    0x100,  8,  0x00,  0},       //!< 08 bits 8:8 reserved
    {REG_ACCESS_R,   REG_STAT,    0x200,  9,  0x00,  0},       //!< 09 bits 9:9 SADCT status ADC test
    {REG_ACCESS_R,   REG_STAT,    0x400,  10, 0x00,  0},       //!< 10 bits 10:10 SROM status ROM
    {REG_ACCESS_RU,  REG_STAT,    0x800,  11, 0x00,  0},       //!< 11 bits 11:11 NOGMRXY no valid GMR XY Values
    {REG_ACCESS_RU,  REG_STAT,    0x1000, 12, 0x00,  0},       //!< 12 bits 12:12 NOGMRA no valid GMR Angle Value
    {REG_ACCESS_RW,  REG_STAT,    0x6000, 13, 0x00,  0},       //!< 13 bits 14:13 SNR slave number
    {REG_ACCESS_RU,  REG_STAT,    0x8000, 15, 0x00,  0},       //!< 14 bits 15:15 RDST read status

    {REG_ACCESS_RW,  REG_ACSTAT,  0x1,    0,  0x00,  1},       //!< 15 bits 0:0 ASRST Activation of Hardware Reset
    {REG_ACCESS_RWU, REG_ACSTAT,  0x2,    1,  0x00,  1},       //!< 16 bits 1:1 ASWD Enable DSPU Watch dog
    {REG_ACCESS_RWU, REG_ACSTAT,  0x4,    2,  0x00,  1},       //!< 17 bits 2:2 ASVR Enable Voltage regulator Check
    {REG_ACCESS_RWU, REG_ACSTAT,  0x8,    3,  0x00,  1},       //!< 18 bits 3:3 ASFUSE Activation Fuse CRC
    {REG_ACCESS_RWU, REG_ACSTAT,  0x10,   4,  0x00,  1},       //!< 19 bits 4:4 ASDSPU Activation DSPU BIST
    {REG_ACCESS_RWU, REG_ACSTAT,  0x20,   5,  0x00,  1},       //!< 20 bits 5:5 ASOV Enable of DSPU Overflow Check
    {REG_ACCESS_RWU, REG_ACSTAT,  0x40,   6,  0x00,  1},       //!< 21 bits 6:6 ASVECXY Activation of X,Y Out of Limit-Check
    {REG_ACCESS_RWU, REG_ACSTAT,  0x80,   7,  0x00,  1},       //!< 22 bits 7:7 ASVEGMAG Activation of Magnitude Check
    {REG_ACCESS_RES, REG_ACSTAT,  0x100,  8,  0x00,  1},       //!< 23 bits 8:8 Reserved
    {REG_ACCESS_RWU, REG_ACSTAT,  0x200,  9,  0x00,  1},       //!< 24 bits 9:9 ASADCT Enable ADC Test vector Check
    {REG_ACCESS_RWU, REG_ACSTAT,  0x400,  10, 0x00,  1},       //!< 25 bits 10:10 ASFRST Activation of Firmware Reset
    {REG_ACCESS_RES, REG_ACSTAT,  0xF800, 11, 0x00,  1},       //!< 26 bits 15:11 Reserved

    {REG_ACCESS_RU,  REG_AVAL,    0x7FFF, 0,  0x00,  2},       //!< 27 bits 14:0 ANGVAL Calculated Angle Value (signed 15-bit)
    {REG_ACCESS_R,   REG_AVAL,    0x8000, 15, 0x00,  2},       //!< 28 bits 15:15 RDAV Read Status, Angle Value

    {REG_ACCESS_RU,  REG_ASPD,    0x7FFF, 0,  0x00,  3},       //!< 29 bits 14:0 ANGSPD Signed value, where the sign bit [14] indicates the direction of the rotation
    {REG_ACCESS_R,   REG_ASPD,    0x8000, 15, 0x00,  3},       //!< 30 bits 15:15 RDAS Read Status, Angle Speed

    {REG_ACCESS_RU,  REG_AREV,    0xFF,   0,  0x00,  4},       //!< 31 bits 8:0 REVOL Revolution counter. Increments for every full rotation in counter-clockwise direction
    {REG_ACCESS_RWU, REG_AREV,    0x7E00, 9,  0x00,  4},       //!< 32 bits 14:9 FCNT Internal frame counter. Increments every update period
    {REG_ACCESS_R,   REG_AREV,    0x8000, 15, 0x00,  4},       //!< 33 its 15:15 RDREV Read Status, Revolution

    {REG_ACCESS_RWU, REG_FSYNC,   0xFF,   0,  0x00,  5},       //!< 34 bits 8:0 TEMPR Signed offset compensated temperature value
    {REG_ACCESS_RU,  REG_FSYNC,   0xFE00, 9,  0x00,  5},       //!< 35 bits 15:9 FSYNC Frame Synchronization Counter Value

    {REG_ACCESS_RW,  REG_MOD_1,   0x3,    0,  0x00,  6},       //!< 36 bits 1:0 IIFMOD Incremental Interface Mode
    {REG_ACCESS_RW,  REG_MOD_1,   0x4,    2,  0x00,  6},       //!< 37 bits 2:2 DSPUHOLD if DSPU is on hold, no watch dog reset is performed by DSPU
    {REG_ACCESS_RES, REG_MOD_1,   0x8,    3,  0x00,  6},       //!< 38 bits 3:3 Reserved1
    {REG_ACCESS_RW,  REG_MOD_1,   0x10,   4,  0x00,  6},       //!< 39 bits 4:4 CLKSEL switch to external clock at start-up only
    {REG_ACCESS_RES, REG_MOD_1,   0x3FE0, 5,  0x00,  6},       //!< 40 bits 13:5 Reserved2
    {REG_ACCESS_RW,  REG_MOD_1,   0x6000, 13, 0x00,  6},       //!< 41 bits 15:14 FIRMD Update Rate Setting

    {REG_ACCESS_RW,  REG_SIL,     0x7,    0,  0x00,  7},       //!< 42 bits 2:0 ADCTVX Test vector X
    {REG_ACCESS_RW,  REG_SIL,     0x38,   3,  0x00,  7},       //!< 43 bits 5:3 ADCTVY Test vector Y
    {REG_ACCESS_RW,  REG_SIL,     0x40,   6,  0x00,  7},       //!< 44 bits 6:6 ADCTVEN Sensor elements are internally disconnected and test voltages are connected to ADCs
    {REG_ACCESS_RES, REG_SIL,     0x380,  7,  0x00,  7},       //!< 45 bits 9:7 Reserved1
    {REG_ACCESS_RW,  REG_SIL,     0x400,  10, 0x00,  7},       //!< 46 bits 10:10 FUSEREL Triggers reload of default values from laser fuses into configuration registers
    {REG_ACCESS_RES, REG_SIL,     0x3800, 11, 0x00,  7},       //!< 47 bits 13:11 Reserved2
    {REG_ACCESS_RW,  REG_SIL,     0x4000, 14, 0x00,  7},       //!< 48 bits 14:14 FILTINV the X- and Y-signals are inverted. The angle output is then shifted by 180°
    {REG_ACCESS_RW,  REG_SIL,     0x8000, 15, 0x00,  7},       //!< 49 bits 15:15 FILTPAR the raw X-signal is routed also to the raw Y-signal input of the filter so SIN and COS signal should be identical

    {REG_ACCESS_RW,  REG_MOD_2,   0x3,    0,  0x00,  8},       //!< 50 bits 1:0 AUTOCAL Automatic calibration of offset and amplitude synchronicity for applications with full-turn
    {REG_ACCESS_RW,  REG_MOD_2,   0x4,    2,  0x00,  8},       //!< 51 bits 2:2 PREDICT Prediction of angle value based on current angle speed
    {REG_ACCESS_RW,  REG_MOD_2,   0x8,    3,  0x00,  8},       //!< 52 bits 3:3 ANGDIR Inverts angle and angle speed values and revolution counter behavior
    {REG_ACCESS_RW,  REG_MOD_2,   0x7FF0, 4,  0x00,  8},       //!< 53 bits 14:4 ANGRANGE Changes the representation of the angle output by multiplying the output with a factor ANG_RANGE/128
    {REG_ACCESS_RES, REG_MOD_2,   0x8000, 15, 0x00,  8},       //!< 54 bits 15:15 Reserved1

    {REG_ACCESS_RW,  REG_MOD_3,   0x3,    0,  0x00,  9},       //!< 55 bits 1:0 PADDRV Configuration of Pad-Driver
    {REG_ACCESS_RW,  REG_MOD_3,   0x4,    2,  0x00,  9},       //!< 56 bits 2:2 SSCOD SSC-Interface Data Pin Output Mode
    {REG_ACCESS_RW,  REG_MOD_3,   0x8,    3,  0x00,  9},       //!< 57 bits 3:3 SPIKEF Filters voltage spikes on input pads (IFC, SCK and CSQ)
    {REG_ACCESS_RW,  REG_MOD_3,   0xFFF0, 4,  0x00,  9},       //!< 58 bits 15:4 ANG_BASE Sets the 0° angle position (12 bit value). Angle base is factory-calibrated to make the 0° direction parallel to the edge of the chip

    {REG_ACCESS_RES, REG_OFFX,    0xF,    0,  0x00, 10},       //!< 59 bits 3:0 Reserved1
    {REG_ACCESS_RW,  REG_OFFX,    0xFFF0, 4,  0x00, 10},       //!< 60 bits 15:4 XOFFSET 12-bit signed integer value of raw X-signal offset correction at 25°C

    {REG_ACCESS_RES, REG_OFFY,    0xF,    0,  0x00, 11},       //!< 61 bits 3:0 Reserved1
    {REG_ACCESS_RW,  REG_OFFY,    0xFFF0, 4,  0x00, 11},       //!< 62 bits 15:4 YOFFSET 12-bit signed integer value of raw Y-signal offset correction at 25°C

    {REG_ACCESS_RES, REG_SYNCH,   0xF,    0,  0x00, 12},       //!< 63 bits 3:0 Reserved1
    {REG_ACCESS_RW,  REG_SYNCH,   0xFFF0, 4,  0x00, 12},       //!< 64 bits 15:4 SYNCH 12-bit signed integer value of amplitude synchronicity

    {REG_ACCESS_RW,  REG_IFAB,    0x3,    0,  0x00, 13},       //!< 65 bits 1:0 IFADHYST Hysteresis (multi-purpose)
    {REG_ACCESS_RW,  REG_IFAB,    0x4,    2,  0x00, 13},       //!< 66 bits 2:2 IFABOD IFA,IFB,IFC Output Mode
    {REG_ACCESS_RW,  REG_IFAB,    0x8,    3,  0x00, 13},       //!< 67 bits 3:3 FIRUDR Initial filter update rate (FIR)
    {REG_ACCESS_RW,  REG_IFAB,    0xFFF0, 4,  0x00, 13},       //!< 68 bits 15:4 ORTHO Orthogonality Correction of X and Y Components

    {REG_ACCESS_RW,  REG_MOD_4,   0x3,    0,  0x00, 14},       //!< 69 bits 1:0 IFMD Interface Mode on IFA,IFB,IFC
    {REG_ACCESS_RES, REG_MOD_4,   0x4,    2,  0x00, 14},       //!< 70 bits 2:2 Reserved1
    {REG_ACCESS_RW,  REG_MOD_4,   0x18,   3,  0x00, 14},       //!< 71 bits 4:3 IFABRES IIF resolution (multi-purpose)
    {REG_ACCESS_RW,  REG_MOD_4,   0x1E0,  5,  0x00, 14},       //!< 72 bits 8:5 HSMPLP Hall Switch mode (multi-purpose)
    {REG_ACCESS_RW,  REG_MOD_4,   0x7E00, 9,  0x00, 14},       //!< 73 bits 15:9 TCOXT 7-bit signed integer value of X-offset temperature coefficient

    {REG_ACCESS_RW,  REG_TCO_Y,   0x7F,   0,  0x00, 15},       //!< 74 bits 7:0 CRCPAR CRC of Parameters
    {REG_ACCESS_RW,  REG_TCO_Y,   0x80,   8,  0x00, 15},       //!< 75 bits 8:8 SBIST Startup-BIST
    {REG_ACCESS_RW,  REG_TCO_Y,   0x7E00, 9,  0x00, 15},       //!< 76 bits 15:9 TCOYT 7-bit signed integer value of Y-offset temperature coefficient

    {REG_ACCESS_R,   REG_ADC_X,   0xFFFF, 0,  0x00, 16},       //!< 77 bits 15:0 ADCX ADC value of X-GMR

    {REG_ACCESS_R,   REG_ADC_Y,   0xFFFF, 0,  0x00, 17},       //!< 78 bits 15:0 ADCY ADC value of Y-GMR

    {REG_ACCESS_RU,  REG_D_MAG,   0x3FF,  0,  0x00, 18},       //!< 79 bits 9:0 MAG Unsigned Angle Vector Magnitude after X, Y error compensation (due to temperature)
    {REG_ACCESS_RES, REG_D_MAG,   0xFC00, 10, 0x00, 18},       //!< 80 bits 15:10 Reserved1

    {REG_ACCESS_RU,  REG_T_RAW,   0x3FF,  0,  0x00, 19},       //!< 81 bits 9:0 TRAW Temperature Sensor Raw-Value at ADC without offset
    {REG_ACCESS_RES, REG_T_RAW,   0xFC00, 10, 0x00, 19},       //!< 82 bits 14:10 Reserved1
    {REG_ACCESS_RU,  REG_T_RAW,   0x8000, 15, 0x00, 19},       //!< 83 bits 15:15 TTGL Temperature Sensor Raw-Value Toggle toggles after every new temperature value

    {REG_ACCESS_RU,  REG_IIF_CNT, 0x7FFF, 0,  0x00, 20},       //!< 84 bits 14:0 IIFCNT 14 bit counter value of IIF increments
    {REG_ACCESS_RES, REG_IIF_CNT, 0x8000, 15, 0x00, 20},       //!< 85 bits 15:14 Reserved1

    {REG_ACCESS_R,   REG_T25O,    0x1FFF, 0,  0x00, 21},       //!< 86 bit 8:0 T250 Signed offset value at 25°C temperature; 1dig=0.36°C
    {REG_ACCESS_RES, REG_T25O,    0xFE00, 9,  0x00, 21},       //!< 87 bits 15:9 Reserved1
};

/**
 * @brief Construct a new Reg::Reg object
 *
 * @param p nested pointer to parent
 */
Reg::Reg(void * p): regMap(), parent_(p)
{
}

/**
 * @brief Destroy the Reg::Reg object
 *
 */
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
bool Reg::getBitField(BitField_t bitField, uint16_t &bitFValue)
{
    bool err = false;
    if ((REG_ACCESS_R & bitField.regAccess) == REG_ACCESS_R)
    {
        Tle5012b *p = static_cast<Tle5012b*>(parent_);
        if ((REG_ACCESS_U & bitField.regAccess) == REG_ACCESS_U)
        {
            p->sBus->triggerUpdate();
        }
        p->readFromSensor(addrFields[bitField.posMap].regAddress, regMap[bitField.posMap], UPD_low, SAFE_high);
        bitFValue = (( regMap[bitField.posMap] & bitField.mask) >> bitField.position);
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
bool Reg::setBitField(BitField_t bitField, uint16_t bitFNewValue)
{
    bool err = false;

    if ((REG_ACCESS_W & bitField.regAccess) == REG_ACCESS_W)
    {
        Tle5012b *p = static_cast<Tle5012b*>(parent_);
        regMap[bitField.posMap] = (regMap[bitField.posMap] & ~bitField.mask) | ((bitFNewValue << bitField.position) & bitField.mask);
        p->writeToSensor(addrFields[bitField.posMap].regAddress, regMap[bitField.posMap], true);
        err = true;
    }

    return err;
}

/**
 * @brief Indication that there was a reset state
 *
 * @return true  indication of reset, power up power break firmware or active reset
 * @return false no reset since last readout
 */
bool Reg::isStatusReset(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SRST], bitf);
    return bitf;
}

/**
 * @brief Permanent check of watchdog
 *
 * @return true  watchdog counter expired, ASRST must be activated
 * @return false normal operation
 */
bool Reg::isStatusWatchDog(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SWD], bitf);
    return bitf;
}

/**
 * @brief Permanent check of internal and external supply voltages
 *
 * @return true  over voltage, GND off
 * @return false voltages ok
 */
bool Reg::isStatusVoltage(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SVR], bitf);
    return bitf;
}

/**
 * @brief Cyclic CRC check of configuration registers and startup CRC
 *
 * @return true  CRC fail
 * @return false CRC ok
 */
bool Reg::isStatusFuse(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SFUSE], bitf);
    return bitf;
}

/**
 * @brief Check DSPU, CORDIC and CAPCOM at startup
 *
 * @return true  DSPU self-test not ok or still running
 * @return false DSPU self-test ok
 */
bool Reg::isStatusDSPU(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SDSPU], bitf);
    return bitf;
}

/**
 * @brief Cyclic check of DSPU (Digital Signal Processing Unit) overflow
 *
 * @return true  DSPU overflow occurred
 * @return false No DSPU overflow occurred
 */
bool Reg::isStatusOverflow(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SOV], bitf);
    return bitf;
}

/**
 * @brief Cyclic check of X and > raw values
 *
 * @return true  X,Y data out of limit
 * @return false X,Y data ok
 */
bool Reg::isStatusXYOutOfLimit(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SXYOL], bitf);
    return bitf;
}

/**
 * @brief Vector lengths cyclic check of X,Y values after error compensation
 *
 * @return true  GMR-magnitude out of limit
 * @return false GMR magnitude ok
 */
bool Reg::isStatusMagnitudeOutOfLimit(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SMAGOL], bitf);
    return bitf;
}

/**
 * @brief Check signal path with test vectors
 *
 * @return true  Test vectors out of limit
 * @return false Test vectors ok
 */
bool Reg::isStatusADC(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SADCT], bitf);
    return bitf;
}

/**
 * @brief Check of ROM-CRC at startup
 *
 * @return true  CRC fail or running
 * @return false CRC ok
 */
bool Reg::isStatusROM(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SROM], bitf);
    return bitf;
}

/**
 * @brief No valid GMR X,Y values, cyclic check of ADC input
 *
 * @return true  no valid GMR X,Y values
 * @return false valid GMR X,Y value
 */
bool Reg::isStatusGMRXY(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_NOGMRXY], bitf);
    return bitf;
}

/**
 * @brief No value GMR angle value, cyclic check of DSPU output
 *
 * @return true  no valid GMR angle values on the interface
 * @return false valid GMR angle values
 */
bool Reg::isStatusGMRA(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_NOGMRA], bitf);
    return bitf;
}

/**
 * @brief Read status, checks if any status register changed since last readout
 *
 * @return true  status values changed since last readout
 * @return false status values not changed
 */
bool Reg::isStatusRead(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_RDST], bitf);
    return bitf;
}

/**
 * @brief Get the actual slave number of the sensor. Up to
 * four sensors can be selected via this register field.
 * @return uint8_t
 */
uint8_t Reg::getSlaveNumber(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_STAT_SNR], bitf);
    return bitf;
}

/**
 * @brief Set the slave number of the sensor. Up to four
 * sensors can be selected with this register field.
 * @param snr Slave number between 0 and 3
 */
void Reg::setSlaveNumber(uint8_t snr)
{
    setBitField(bitFields[REG_STAT_SNR], snr);
}

/**
 * @brief Hardware reset, will be performed after chip select returns to high.
 *
 * @return true  activation of hardware reset
 * @return false after reset, thus always returns false
 */
bool Reg::isActivationReset(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASRST], bitf);
    return bitf;
}

/**
 * @brief Set the Activation Reset object
 * Performs a hardware reset.
 */
void Reg::setActivationReset(void)
{
    setBitField(bitFields[REG_ACSTAT_ASRST], 1);
}

/**
 * @brief Enable the DSPU watchdog
 *
 */
void Reg::enableWatchdog(void)
{
    setBitField(bitFields[REG_ACSTAT_ASWD], 1);
}

/**
 * @brief disable the DSPU watchdog
 *
 */
void Reg::disableWatchdog(void)
{
    setBitField(bitFields[REG_ACSTAT_ASWD], 0);
}

/**
 * @brief Get the status of the DSPU watchdog
 *
 * @return true  DSPU watchdog is enabled
 * @return false DSPU watchdog is disabled
 */
bool Reg::isWatchdog(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASWD], bitf);
    return bitf;
}

/**
 * @brief Enable the voltage regulator check
 *
 */
void Reg::enableVoltageCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASVR], 1);
}

/**
 * @brief disable the voltage regulator check
 *
 */
void Reg::disableVoltageCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASVR], 0);
}

/**
 * @brief Get the status of the voltage regulator check
 *
 * @return true  voltage regulator check is enabled
 * @return false voltage regulator check is disabled
 */
bool Reg::isVoltageCheck(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASVR], bitf);
    return bitf;
}

/**
 * @brief Enable the fuse CRC check
 *
 */
void Reg::enableFuseCRC(void)
{
    setBitField(bitFields[REG_ACSTAT_ASFUSE], 1);
}

/**
 * @brief disable the fuse CRC check
 *
 */
void Reg::disableFuseCRC(void)
{
    setBitField(bitFields[REG_ACSTAT_ASFUSE], 0);
}

/**
 * @brief Get the status of the fuse CRC check
 *
 * @return true  fuse CRC check is enabled
 * @return false fuse CRC check is disabled
 */
bool Reg::isFuseCRC(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASFUSE], bitf);
    return bitf;
}

/**
 * @brief Enable the DSPU bist check
 *
 */
void Reg::enableDSPUbist(void)
{
    setBitField(bitFields[REG_ACSTAT_ASDSPU], 1);
}

/**
 * @brief disable the DSPU bist check
 *
 */
void Reg::disableDSPUbist(void)
{
    setBitField(bitFields[REG_ACSTAT_ASDSPU], 0);
}

/**
 * @brief Get the status of the DSPU bist check
 *
 * @return true  DSPU bist check is enabled
 * @return false DSPU bist check is disabled
 */
bool Reg::isDSPUbist(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASDSPU], bitf);
    return bitf;
}

/**
 * @brief Enable the DSPU overflow check
 *
 */
void Reg::enableDSPUoverflow(void)
{
    setBitField(bitFields[REG_ACSTAT_ASOV], 1);
}

/**
 * @brief disable the DSPU overflow check
 *
 */
void Reg::disableDSPUoverflow(void)
{
    setBitField(bitFields[REG_ACSTAT_ASOV], 0);
}

/**
 * @brief Get the status of the DSPU overflow check
 *
 * @return true  DSPU overflow check is enabled
 * @return false DSPU overflow check is disabled
 */
bool Reg::isDSPUoverflow(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASOV], bitf);
    return bitf;
}

/**
 * @brief Enable the X,Y out of limit check
 *
 */
void Reg::enableXYCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASVECXY], 1);
}

/**
 * @brief disable the X,Y out of limit check
 *
 */
void Reg::disableXYCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASVECXY], 0);
}

/**
 * @brief Get the status of the X,Y out of limit check
 *
 * @return true  X,Y out of limit check is enabled
 * @return false X,Y out of limit check is disabled
 */
bool Reg::isXYCheck(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASVECXY], bitf);
    return bitf;
}

/**
 * @brief Enable the GMR magnitude check
 *
 */
void Reg::enableGMRCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASVEGMAG], 1);
}

/**
 * @brief disable the GMR magnitude check
 *
 */
void Reg::disableGMRCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASVEGMAG], 0);
}

/**
 * @brief Get the status of the GMR magnitude check
 *
 * @return true  GMR magnitude check is enabled
 * @return false GMR magnitude check is disabled
 */
bool Reg::isGMRCheck(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASVEGMAG], bitf);
    return bitf;
}

/**
 * @brief Enable the ADC test vector check
 *
 */
void Reg::enableADCCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASADCT], 1);
}

/**
 * @brief disable the ADC test vector check
 *
 */
void Reg::disableADCCheck(void)
{
    setBitField(bitFields[REG_ACSTAT_ASADCT], 0);
}

/**
 * @brief Get the status of the ADC test vectorGMR magnitude check
 *
 * @return true  ADC test vector check is enabled
 * @return false ADC test vector check is disabled
 */
bool Reg::isADCCheck(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASADCT], bitf);
    return bitf;
}

/**
 * @brief Activate the firmware reset, all configuration registers retain their contents.
 * Will also set the SRST register.
 *
 */
void Reg::activateFirmwareReset(void)
{
    setBitField(bitFields[REG_ACSTAT_ASFRST], 1);
}

/**
 * @brief Get the status of the firmware reset register
 *
 * @return true  activation on firmware reset
 * @return false default after execution of reset
 */
bool Reg::isFirmwareReset(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ACSTAT_ASFRST], bitf);
    return bitf;
}

/**
 * @brief Do we have a new calculated angle value since last readout
 *
 * @return true  new angle value available
 * @return false no new angle value calculated
 */
bool Reg::isAngleValueNew(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_AVAL_RDAV], bitf);
    return bitf;
}

/**
 * @brief Get a new calculated angle value
 *
 * @return uint16_t calculated angle value
 */
uint16_t Reg::getAngleValue(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_AVAL_ANGVAL], bitf);
    return bitf;
}

/**
 * @brief  Do we have a new calculated speed value since last readout
 *
 * @return true  new speed value available
 * @return false no new speed value calculated
 */
bool Reg::isSpeedValueNew(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ASPD_RDAS], bitf);
    return bitf;
}

/**
 * @brief Get a new calculated speed value
 *
 * @return uint16_t calculated speed value
 */
uint16_t Reg::getSpeedValue(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ASPD_ANGSPD], bitf);
    return bitf;
}

/**
 * @brief  Do we have a new number of revolutions since last readout
 *
 * @return true  new number of revolutions available
 * @return false no number of revolutions
 */
bool Reg::isNumberOfRevolutionsNew(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_AREV_RDREV], bitf);
    return bitf;
}

/**
 * @brief Get a new number of revolutions value
 *
 * @return uint16_t number of revolutions
 */
uint16_t Reg::getNumberOfRevolutions(void)
{
    uint16_t bitf = 0x00;
    uint16_t revolutions = 0x00;
    getBitField(bitFields[REG_AREV_REVOL], bitf);
    revolutions = (bitf & 0xFF);
    if (revolutions & 0x100)
    {
        revolutions = revolutions * -1;
    }
    return revolutions;
}

/**
 * @brief Get the frame counter value.
 * Internal frame counter increments every update period.
 *
 * @return uint16_t frame counter
 */
uint16_t Reg::getFrameCounter(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_AREV_FCNT], bitf);
    return bitf;
}

/**
 * @brief Set the frame counter value
 *
 */
void Reg::setFrameCounter(uint16_t fcnt)
{
    setBitField(bitFields[REG_AREV_FCNT], fcnt);
}

/**
 * @brief Get the frame synchronisation counter value
 * Internal frame sub counter within one frame.
 *
 * @return uint16_t frame synchronisation counter
 */
uint16_t Reg::getFrameSyncCounter(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_FSYNC_FSYNC], bitf);
    //FSYNC = (reg & 0xFE00) >> 9;
    return bitf;
}

/**
 * @brief Set the frame synchronisation counter value
 *
 */
void Reg::setFrameSyncCounter(uint16_t fsync)
{
    setBitField(bitFields[REG_FSYNC_FSYNC], fsync);
}

/**
 * @brief Get the temperature value as signed offset compensated temperature value
 * Saturated between -30°C  and above 140°C
 *
 * @return uint16_t temperature value
 */
uint16_t Reg::getTemperatureValue(void)
{
    uint16_t bitf = 0x00;
    uint16_t temperature = 0x00;
    getBitField(bitFields[REG_FSYNC_TEMPR], bitf);
    return bitf;
    temperature = (bitf & 0xFF);
    if (temperature & 0x100)
    {
        temperature = temperature * -1;
    }
    return temperature;
}

/**
 * @brief Set the filter decimation, update rate setting
 *
 */
void Reg::setFilterDecimation(uint8_t firmd)
{
    setBitField(bitFields[REG_MOD_1_FIRMD], firmd);
}

/**
 * @brief Get the filter decimation, update rate setting
 *
 * @return uint16_t filter decimation
 */
uint8_t Reg::getFilterDecimation(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_1_FIRMD], bitf);
    return bitf;
}

/**
 * @brief Set the IIF (Incremental Interface Mode)
 *
 */
void Reg::setIIFMod(uint8_t iifmod)
{
    setBitField(bitFields[REG_MOD_1_IIFMOD], iifmod);
}

/**
 * @brief Get the temperature value as signed offset compensated temperature value
 * Saturated between -30°C  and above 140°C
 *
 * @return uint16_t IIF mode
 */
uint8_t Reg::getIIFMod(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_1_IIFMOD], bitf);
    return bitf;
}

/**
 * @brief Set DSPU on hold
 *
 */
void Reg::holdDSPU(void)
{
    setBitField(bitFields[REG_MOD_1_DSPUHOLD], 1);
}

/**
 * @brief release DSPU operations
 *
 */
void Reg::releaseDSPU(void)
{
    setBitField(bitFields[REG_MOD_1_DSPUHOLD], 0);
}

/**
 * @brief Get the status of DSPU operations
 *
 * @return true  DSPU is on hold
 * @return false DSPU is in operation
 */
bool Reg::isDSPUhold(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_1_DSPUHOLD], bitf);
    return bitf;
}

/**
 * @brief Set the clock source to internal oscillator
 *
 */
void Reg::setInternalClock(void)
{
    setBitField(bitFields[REG_MOD_1_CLKSEL], 0);
}

/**
 * @brief Set clock source to external SCK
 *
 */
void Reg::setExternalClock(void)
{
    setBitField(bitFields[REG_MOD_1_CLKSEL], 1);
}

/**
 * @brief Get the status of the clock source
 *
 * @return true  external 4MHz clock on pin IFC selected
 * @return false internal oscillator
 */
bool Reg::statusClockSource(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_1_CLKSEL], bitf);
    return bitf;
}

/**
 * @brief Enable the Filter parallel diagnostics function
 *
 */
void Reg::enableFilterParallel(void)
{
    setBitField(bitFields[REG_SIL_FILTPAR], 1);
}

/**
 * @brief disable the Filter parallel diagnostics function
 *
 */
void Reg::disableFilterParallel(void)
{
    setBitField(bitFields[REG_SIL_FILTPAR], 0);
}

/**
 * @brief Get the status of the Filter parallel diagnostics function
 *
 * @return true  filter parallel is enabled
 * @return false filter parallel is disabled
 */
bool Reg::isFilterParallel(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SIL_FILTPAR], bitf);
    return bitf;
}

/**
 * @brief Enable the Filter inverted diagnostics function
 *
 */
void Reg::enableFilterInverted(void)
{
    setBitField(bitFields[REG_SIL_FILTINV], 1);
}

/**
 * @brief disable the Filter inverted diagnostics function
 *
 */
void Reg::disableFilterInverted(void)
{
    setBitField(bitFields[REG_SIL_FILTINV], 0);
}

/**
 * @brief Get the status of the Filter inverted diagnostics function
 *
 * @return true  filter inverted is enabled
 * @return false filter inverted is disabled
 */
bool Reg::isFilterInverted(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SIL_FILTINV], bitf);
    return bitf;
}

/**
 * @brief Enable the ADC test vector diagnostics function
 *
 */
void Reg::enableADCTestVector(void)
{
    setBitField(bitFields[REG_SIL_ADCTVEN], 1);
}

/**
 * @brief disable the ADC test vector diagnostics function
 *
 */
void Reg::disableADCTestVector(void)
{
    setBitField(bitFields[REG_SIL_ADCTVEN], 0);
}

/**
 * @brief Get the status of the ADC test vector diagnostics function
 *
 * @return true  ADC test vector is enabled
 * @return false ADC test vector is disabled
 */
bool Reg::isADCTestVector(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SIL_ADCTVEN], bitf);
    return bitf;
}

/**
 * @brief Set the fuse reload register and trigger a reload
 *
 */
void Reg::setFuseReload(void)
{
    setBitField(bitFields[REG_SIL_FUSEREL], 1);
}

/**
 * @brief Get the status of the fuse reload register
 *
 * @return true  reload of registers from fuses immediately
 * @return false normal operations
 */
bool Reg::getFuseReload(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SIL_FUSEREL], bitf);
    return bitf;
}

/**
 * @brief Set the test vector x
 *
 */
void Reg::setTestVectorX(uint8_t adctvx)
{
    setBitField(bitFields[REG_SIL_ADCTVX], adctvx);
}

/**
 * @brief Get the test vector x
 *
 * @return uint8_t test vector x
 */
uint8_t Reg::getTestVectorX(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SIL_ADCTVX], bitf);
    return bitf;
}

/**
 * @brief Set the test vector s
 *
 */
void Reg::setTestVectorY(uint8_t adctvy)
{
    setBitField(bitFields[REG_SIL_ADCTVY], adctvy);
}

/**
 * @brief Get the test vector y
 *
 * @return uint8_t test vector y
 */
uint8_t Reg::getTestVectorY(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SIL_ADCTVY], bitf);
    return bitf;
}

/**
 * @brief Set angle direction clockwise
 *
 */
void Reg::directionClockwise(void)
{
    setBitField(bitFields[REG_MOD_2_ANGDIR], 1);
}

/**
 * @brief Set angle direction counter clockwise
 *
 */
void Reg::directionCounterClockwise(void)
{
    setBitField(bitFields[REG_MOD_2_ANGDIR], 0);
}

/**
 * @brief Get the angle direction
 *
 * @return true  angle direction is clockwise
 * @return false angle direction is counter clockwise
 */
bool Reg::isAngleDirection(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_2_ANGDIR], bitf);
    return bitf;
}

/**
 * @brief Enable the angle prediction based on current speed
 *
 */
void Reg::enablePrediction(void)
{
    setBitField(bitFields[REG_MOD_2_PREDICT], 1);
}

/**
 * @brief disable the angle prediction
 *
 */
void Reg::disablePrediction(void)
{
    setBitField(bitFields[REG_MOD_2_PREDICT], 0);
}

/**
 * @brief Get the status of angle prediction
 *
 * @return true  prediction is enabled
 * @return false prediction is disabled
 */
bool Reg::isPrediction(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_2_PREDICT], bitf);
    return bitf;
}

/**
 * @brief Set the representation of the angle output value and the speed value
 *
 */
void Reg::setAngleRange(angleRange_t range)
{
    setBitField(bitFields[REG_MOD_2_ANGRANGE], range);
}

/**
 * @brief Get the representation of the angle range
 *
 * @return angleRange_t type of angle range
 */
Reg::angleRange_t Reg::getAngleRange(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_2_ANGRANGE], bitf);
    return (angleRange_t)bitf;
}

/**
 * @brief Set the automatic calibration mode
 *
 */
void Reg::setCalibrationMode(calibrationMode_t autocal)
{
    setBitField(bitFields[REG_MOD_2_AUTOCAL], autocal);
}

/**
 * @brief Get the actual automatic calibration mode
 *
 * @return angleRange_t type of calibration mode
 */
Reg::calibrationMode_t Reg::getCalibrationMode(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_2_AUTOCAL], bitf);
    return (calibrationMode_t)bitf;
}

/**
 * @brief Enable the analog spike filter to filter voltage spikes in IFC, SCK, CS
 *
 */
void Reg::enableSpikeFilter(void)
{
    setBitField(bitFields[REG_MOD_3_SPIKEF], 1);
}

/**
 * @brief disable the analog spike filter to filter
 *
 */
void Reg::disableSpikeFilter(void)
{
    setBitField(bitFields[REG_MOD_3_SPIKEF], 0);
}

/**
 * @brief Get the status of the analog spike filter
 *
 * @return true  spike filter is enabled
 * @return false spike filter is disabled
 */
bool Reg::isSpikeFilter(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_3_SPIKEF], bitf);
    return bitf;
}

/**
 * @brief Enable open drain on SSC interface
 *
 */
void Reg::enableSSCOpenDrain(void)
{
    setBitField(bitFields[REG_MOD_3_SSCOD], 1);
}

/**
 * @brief Enable push pull on SSC interface
 *
 */
void Reg::enableSSCPushPull(void)
{
    setBitField(bitFields[REG_MOD_3_SSCOD], 0);
}

/**
 * @brief Get the status of the SSC output mode
 *
 * @return true  SSC open drain
 * @return false SSC push pull default
 */
bool Reg::isSSCOutputMode(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_3_SSCOD], bitf);
    return bitf;
}

/**
 * @brief Set a new value for the angle base calibration
 *
 */
void Reg::setAngleBase(uint16_t base)
{
    setBitField(bitFields[REG_MOD_3_ANG_BASE], base);
}

/**
 * @brief Get the actual 0° angle position
 * The 0° angle position is factory calibrated parallel to the edge of the chip
 *
 * @return uint16_t angle base calibration
 */
uint16_t Reg::getAngleBase(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_3_ANG_BASE], bitf);
    return bitf;
}

/**
 * @brief Set a new pad driver configuration
 *
 */
void Reg::setPadDriver(uint8_t pad)
{
    setBitField(bitFields[REG_MOD_3_PADDRV], pad);
}

/**
 * @brief Get the pad driver configuration
 *
 * @return uint8_t pad driver
 */
uint8_t Reg::getPadDriver(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_3_PADDRV], bitf);
    return bitf;
}

/**
 * @brief Set offset correction x value
 *
 */
void Reg::setOffsetX(int16_t offx)
{
    setBitField(bitFields[REG_OFFX_XOFFSET], offx);
}

/**
 * @brief Get offset correction x value
 *
 * @return int16_t offset x value
 */
int16_t Reg::getOffsetX(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_OFFX_XOFFSET], bitf);
    return (int16_t)bitf;
}

/**
 * @brief Set offset correction y value
 *
 */
void Reg::setOffsetY(int16_t offy)
{
    setBitField(bitFields[REG_OFFY_YOFFSET], offy);
}

/**
 * @brief Get offset correction y value
 *
 * @return int16_t offset y value
 */
int16_t Reg::getOffsetY(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_OFFY_YOFFSET], bitf);
    return (int16_t)bitf;
}

/**
 * @brief Set amplitude correction value
 *
 */
void Reg::setAmplitudeSynch(int16_t synch)
{
    setBitField(bitFields[REG_SYNCH_SYNCH], synch);
}

/**
 * @brief Get amplitude correction value
 *
 * @return int16_t offset y value
 */
int16_t Reg::getAmplitudeSynch(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_SYNCH_SYNCH], bitf);
    return (int16_t)bitf;
}

/**
 * @brief Set the FIR (Filter Initial Rate) update rate
 *
 */
void Reg::setFIRUpdateRate(bool fir)
{
    setBitField(bitFields[REG_IFAB_FIRUDR], fir);
}

/**
 * @brief Get the FIR update rate
 *
 * @return uint8_t(bool) FIR update rate
 */
uint8_t Reg::getFIRUpdateRate(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_IFAB_FIRUDR], bitf);
    return bitf;
}

/**
 * @brief Enable open drain in IFA, IFB and IFC
 *
 */
void Reg::enableIFABOpenDrain(void)
{
    setBitField(bitFields[REG_IFAB_IFABOD], 1);
}

/**
 * @brief Enable push pull in IFA, IFB and IFC
 *
 */
void Reg::enableIFABPushPull(void)
{
    setBitField(bitFields[REG_IFAB_IFABOD], 0);
}

/**
 * @brief Get the status of the IFA, IFB and IFC output mode
 *
 * @return true  IFA, IFB and IFC open drain
 * @return false IFA, IFB and IFC push pull default
 */
bool Reg::isIFABOutputMode(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_IFAB_IFABOD], bitf);
    return bitf;
}

/**
 * @brief Set the orthogonality correction of x y components
 *
 */
void Reg::setOrthogonality(int16_t ortho)
{
    setBitField(bitFields[REG_IFAB_ORTHO], ortho);
}

/**
 * @brief Get the orthogonality correction of x y components
 *
 * @return int16_t orthogonality correction
 */
int16_t Reg::getOrthogonality(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_IFAB_ORTHO], bitf);
    return (int16_t)bitf;
}

/**
 * @brief Set the hysteresis mode for HSM,
 * or the unit time if in SPC mode (see manual)
 *
 */
void Reg::setHysteresisMode(uint8_t hyst)
{
    setBitField(bitFields[REG_IFAB_IFADHYST], hyst);
}

/**
 * @brief Get the hysteresis mode for HSM,
 * or the unit time if in SPC mode (see manual)
 *
 * @return uint8_t hysteresis mode/unit time
 */
uint8_t Reg::getHysteresisMode(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_IFAB_IFADHYST], bitf);
    return bitf;
}

/**
 * @brief Set the interface Mode on IFA,IFB,IFC
 *
 */
void Reg::setInterfaceMode(interfaceType_t ifmd)
{
    setBitField(bitFields[REG_MOD_4_IFMD], ifmd);
}

/**
 * @brief Get the interface Mode on IFA,IFB,IFC
 *
 * @return interfaceType_t interface type
 */
Reg::interfaceType_t Reg::getInterfaceMode(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_4_IFMD], bitf);
    return (interfaceType_t)bitf;
}

/**
 * @brief Set multipurpose register,
 * PWM frequency, IIF resolution, SPC frame configuration
 */
void Reg::setIFABres(uint8_t res)
{
    setBitField(bitFields[REG_MOD_4_IFABRES], res);
}

/**
 * @brief Get multipurpose register
 *
 * @return uint8_t multipurpose, PWM frequency, IIF resolution, SPC frame configuration
 */
uint8_t Reg::getIFABres(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_4_HSMPLP], bitf);
    return bitf;
}

/**
 * @brief Set multipurpose register,
 *
 */
void Reg::setHSMplp(uint8_t plp)
{
    setBitField(bitFields[REG_MOD_4_HSMPLP], plp);
}

/**
 * @brief Get multipurpose register
 *
 * @return uint8_t multipurpose, PWM frequency, IIF resolution, SPC frame configuration
 */
uint8_t Reg::getHSMplp(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_4_IFABRES], bitf);
    return bitf;
}

/**
 * @brief Set offset temperature coefficient for x component
 *
 */
void Reg::setOffsetTemperatureX(int8_t tcox)
{
    setBitField(bitFields[REG_MOD_4_TCOXT], tcox);
}

/**
 * @brief Get offset temperature coefficient for x component
 *
 * @return int8_t x temperature coefficient
 */
int8_t Reg::getOffsetTemperatureX(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_MOD_4_TCOXT], bitf);
    if (bitf & 0x8000)
    {
        bitf = bitf * -1;
    }
    return (int8_t)bitf;
}

/**
 * @brief Set offset temperature coefficient for y component
 *
 */
void Reg::setOffsetTemperatureY(int8_t tcoy)
{
    setBitField(bitFields[REG_TCO_Y_TCOYT], tcoy);
}

/**
 * @brief Get offset temperature coefficient for y component
 *
 * @return int8_t x temperature coefficient
 */
int8_t Reg::getOffsetTemperatureY(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_TCO_Y_TCOYT], bitf);
    if (bitf & 0x8000)
    {
        bitf = bitf * -1;
    }
    return (int8_t)bitf;
}

/**
 * @brief Enable startup bist
 *
 */
void Reg::enableStartupBist(void)
{
    setBitField(bitFields[REG_TCO_Y_SBIST], 1);
}

/**
 * @brief Disable startup bist
 *
 */
void Reg::disableStartupBist(void)
{
    setBitField(bitFields[REG_TCO_Y_SBIST], 0);
}

/**
 * @brief Get the status of startup bist
 *
 * @return true  Bist enabled
 * @return false Bist disabled
 */
bool Reg::isStartupBist(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_TCO_Y_SBIST], bitf);
    return bitf;
}

/**
 * @brief Set CRC of parameters from address 08h to 0Fh
 *
 */
void Reg::setCRCpar(uint16_t crc)
{
    setBitField(bitFields[REG_TCO_Y_CRCPAR], crc);
}

/**
 * @brief Get CRC of parameters from address 08h to 0Fh
 *
 * @return uint16_t CRC
 */
uint16_t Reg::getCRCpar(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_TCO_Y_CRCPAR], bitf);
    return bitf;
}

/**
 * @brief Get GMR ADC x value
 *
 * @return uint16_t ADC x
 */
int16_t Reg::getADCx(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ADC_X_ADCX], bitf);
    return (int16_t)bitf;
}

/**
 * @brief Get GMR ADC y value
 *
 * @return uint16_t ADC y
 */
int16_t Reg::getADCy(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_ADC_Y_ADCY], bitf);
    return (int16_t)bitf;
}

/**
 * @brief Get angle vector magnitude
 *
 * @return uint16_t MAG
 */
uint16_t Reg::getVectorMagnitude(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_D_MAG_MAG], bitf);
    return bitf;
}

/**
 * @brief Get Temperature Sensor raw value
 *
 * @return uint16_t Temperature raw value
 */
uint16_t Reg::getTemperatureRAW(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_T_RAW_TRAW], bitf);
    return bitf;
}

/**
 * @brief Is there a new Temperature Sensor RAW value
 *
 * @return true  Bist enabled
 * @return false Bist disabled
 */
bool Reg::isTemperatureToggle(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_T_RAW_TTGL], bitf);
    return bitf;
}

/**
 * @brief Get Counter value of increments
 *
 * @return uint16_t Temperature raw value
 */
uint16_t Reg::getCounterIncrements(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_IIF_CNT_IIFCNT], bitf);
    return bitf;
}

/**
 * @brief Get Temperature 25°C offset value
 *
 * @return uint16_t T25 offset value
 */
uint16_t Reg::getT25Offset(void)
{
    uint16_t bitf = 0x00;
    getBitField(bitFields[REG_T25O_T250], bitf);
    return bitf;
}
