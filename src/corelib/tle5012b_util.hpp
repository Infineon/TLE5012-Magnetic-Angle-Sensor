/*!
 * \file        tle5012b_util.hpp
 * \name        tle5012b_util.hpp - core support header for the TLE5012B angle sensor.
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


#ifndef TLE5012B_UTIL_HPP
#define TLE5012B_UTIL_HPP

#include <stdint.h>
#include <stdlib.h>
#include "TLE5012b.hpp"


namespace tle5012
{
    /**
     * @addtogroup tle5012util
     *
     * @{
     */

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
    #define MAX_NUM_REG                 0x16      //!< \brief defines the value for temporary data to read all readable registers

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

    /**
     * @brief Error types from safety word
     */
    enum errorTypes
    {
        NO_ERROR               = 0x00,  //!< \brief NO_ERROR = Safety word was OK
        SYSTEM_ERROR           = 0x01,  //!< \brief SYSTEM_ERROR = over/under voltage, VDD negative, GND off, ROM defect
        INTERFACE_ACCESS_ERROR = 0x02,  //!< \brief INTERFACE_ACCESS_ERROR = wrong address or wrong lock
        INVALID_ANGLE_ERROR    = 0x03,  //!< \brief INVALID_ANGLE_ERROR = NO_GMR_A = 1 or NO_GMR_XY = 1
        ANGLE_SPEED_ERROR      = 0x04,  //!< \brief ANGLE_SPEED_ERROR = combined error, angular speed calculation wrong
        CRC_ERROR              = 0xFF   //!< \brief CRC_ERROR = Cyclic Redundancy Check (CRC), which includes the STAT and RESP bits wrong
    };

    //!< \brief Set the UPDate bit high (read from update buffer) or low (read directly)
    enum updTypes
    {
        UPD_low  = 0x0000,              //!< \brief read normal registers
        UPD_high = 0x0400,              //!< \brief read update buffer registers
    };

    //!< \brief Switch on/off safety word generation
    enum safetyTypes
    {
        SAFE_low  = 0x0000,             //!< \brief switch of safety word generation
        SAFE_high = 0x0001,             //!< \brief switch on safety word generation
    };

    /**
     * @}
     */
}

#endif /* TLE5012B_UTIL_HPP */