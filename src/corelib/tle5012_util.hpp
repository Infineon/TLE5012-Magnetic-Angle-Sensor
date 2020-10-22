/*!
 * \file        tle5012b_util.hpp
 * \name        tle5012b_util.hpp - core support header for the TLE5012B angle sensor.
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


#ifndef TLE5012B_REG_HPP
#define TLE5012B_REG_HPP

// Common macros
#define TRIGGER_DELAY               5         //!< \brief 5 microseconds trigger delay time

// Sensor registers
#define READ_SENSOR                 0x8000    //!< \brief base command for read
#define WRITE_SENSOR                0x5000    //!< \brief base command for write
#define READ_BLOCK_CRC              0x8088    //!< \brief initialize block CRC check command

// Bitmasks for several read and write functions
#define SYSTEM_ERROR_MASK           0x4000    //!< \brief System error masks for safety words
#define INTERFACE_ERROR_MASK        0x2000    //!< \brief Interface error masks for safety words
#define INV_ANGLE_ERROR_MASK        0x1000    //!< \brief Angle error masks for safety words

#define CRC_POLYNOMIAL              0x1D      //!< \brief values used for calculating the CRC
#define CRC_SEED                    0xFF
#define CRC_NUM_REGISTERS           0x0008    //!< \brief number of CRC relevant registers
#define MAX_REGISTER_MEM            0x0030    //!< \brief max readable register values buffer

#define DELETE_BIT_15               0x7FFF    //!< \brief Value used to delete everything except the first 15 bits
#define CHANGE_UINT_TO_INT_15       0x8000    //!< \brief Value used to change unsigned 16bit integer into signed
#define CHECK_BIT_14                0x4000    //!< \brief
#define GET_BIT_14_4                0x7FF0    //!< \brief

#define DELETE_7BITS                0x01FF    //!< \brief values used to calculate 9 bit signed integer sent by the sensor
#define CHANGE_UNIT_TO_INT_9        0x0200    //!< \brief Value used to change unsigned 9bit integer into signed
#define CHECK_BIT_9                 0x0100

#define POW_2_15                    32768.0   //!< \brief values used to for final calculations of angle speed, revolutions, range and value
#define POW_2_7                     128.0     //!< \brief
#define ANGLE_360_VAL               360.0     //!< \brief

#define TEMP_OFFSET                 152.0     //!< \brief values used to calculate the temperature
#define TEMP_DIV                    2.776

// Register address offsets
#define REG_STAT                    0x0000    //!< \brief STAT status register
#define REG_ACSTAT                  0x0010    //!< \brief ACSTAT activation status register
#define REG_AVAL                    0x0020    //!< \brief AVAL angle value register
#define REG_ASPD                    0x0030    //!< \brief ASPD angle speed register
#define REG_AREV                    0x0040    //!< \brief AREV angle revolution register
#define REG_FSYNC                   0x0050    //!< \brief FSYNC frame synchronization register
#define REG_MOD_1                   0x0060    //!< \brief MOD_1 interface mode1 register
#define REG_SIL                     0x0070    //!< \brief SIL register
#define REG_MOD_2                   0x0080    //!< \brief MOD_2 interface mode2 register
#define REG_MOD_3                   0x0090    //!< \brief MOD_3 interface mode3 register
#define REG_OFFX                    0x00A0    //!< \brief OFFX offset x
#define REG_OFFY                    0x00B0    //!< \brief OFFY offset y
#define REG_SYNCH                   0x00C0    //!< \brief SYNCH synchronicity
#define REG_IFAB                    0x00D0    //!< \brief IFAB register
#define REG_MOD_4                   0x00E0    //!< \brief MOD_4 interface mode4 register
#define REG_TCO_Y                   0x00F0    //!< \brief TCO_Y temperature coefficient register
#define REG_ADC_X                   0x0100    //!< \brief ADC_X ADC X-raw value
#define REG_ADC_Y                   0x0110    //!< \brief ADC_Y ADC Y-raw value
#define REG_D_MAG                   0x0140    //!< \brief D_MAG angle vector magnitude
#define REG_T_RAW                   0x0150    //!< \brief T_RAW temperature sensor raw-value
#define REG_IIF_CNT                 0x0200    //!< \brief IIF_CNT IIF counter value
#define REG_T25O                    0x0300    //!< \brief T25O temperature 25°c offset value

// Support macros
//!< \brief Prints a binary number with leading zeros (Automatic Handling)
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0');
//!< \brief Prints a binary number with leading zeros (Automatic Handling) with space
#define PRINTBINS(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? " 1 " : " 0 ");


// Error types from safety word
enum errorTypes
{
	NO_ERROR               = 0x00,  //!< \brief NO_ERROR = Safety word was OK
	SYSTEM_ERROR           = 0x01,  //!< \brief SYSTEM_ERROR = over/under voltage, VDD negative, GND off, ROM defect
	INTERFACE_ACCESS_ERROR = 0x02,  //!< \brief INTERFACE_ACCESS_ERROR = wrong address or wrong lock
	INVALID_ANGLE_ERROR    = 0x03,  //!< \brief INVALID_ANGLE_ERROR = NO_GMR_A = 1 or NO_GMR_XY = 1
	ANGLE_SPEED_ERROR      = 0x04,  //!< \brief ANGLE_SPEED_ERROR = combined error, angular speed calculation wrong
	CRC_ERROR              = 0xFF   //!< \brief CRC_ERROR = Cyclic Redundancy Check (CRC), which includes the STAT and RESP bits wrong
};

// Set the UPDate bit high (read from update buffer) or low (read directly)
enum updTypes
{
	UPD_low  = 0x0000,           //!< \brief read normal registers
	UPD_high = 0x0400,           //!< \brief read update buffer registers
};

// Switch on/off safety word generation
enum safetyTypes
{
	SAFE_low  = 0x0000,          //!< \brief switch of safety word generation
	SAFE_high = 0x0001,          //!< \brief switch on safety word generation
};


#endif