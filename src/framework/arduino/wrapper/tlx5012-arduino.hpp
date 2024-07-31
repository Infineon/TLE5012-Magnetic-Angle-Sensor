/*!
 * \file        tlx5012-arduino.hpp
 * \name        tlx5012-arduino.hpp - Arduino library for the Infineon TLx5012 magnetic angular sensor
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \ref         tle5012ino
 * \version     4.0.0
 * \brief       This is a Arduino platform file use Infineon's TLE5012B magnetic angular sensor
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLX5012_ARDUINO_HPP_
#define TLX5012_ARDUINO_HPP_


#include <Arduino.h>

#include "TLE5012b.hpp"
#include "pal-gpio-arduino.hpp"
#include "pal-spic-arduino.hpp"

/**
 * @addtogroup inoApi
 * @{
 */
namespace tle5012
{


/**
 * @class Tle5012Ino
 *
 * @brief represents the TLx5012 base class
 *
 * This class provides a simple API for connecting the TLE5012B as well as the
 * TLI5012B via SSC interface, which is included into all flavours the TLx5012 sensor.
 * This setup works with the the Sens2Kit (Sensor including XMC1100 mcu),
 * the breakout board (only the Sensor from the Sens2Kit) and
 * bulk chips (read the section on how to connect the bulk chip via 3wire SPI).
 *
 * @see Tle5012
 *
 */

// Support macros
//!< \brief Prints a binary number with leading zeros (Automatic Handling)
#define PRINTBIN(Num) for (uint32_t t = (1UL << ((sizeof(Num)*8)-1)); t; t >>= 1) Serial.write(Num  & t ? '1' : '0');
//!< \brief Prints a binary number with leading zeros (Automatic Handling) with space
#define PRINTBINS(Num) for (uint32_t t = (1UL << ((sizeof(Num)*8)-1)); t; t >>= 1) Serial.write(Num  & t ? " 1 " : " 0 ");


class Tle5012Ino: public Tle5012b
{
    public:

        uint8_t     mSpiNum = 0;          //!< Number of used SPI channel

                    Tle5012Ino();
                    Tle5012Ino(uint8_t csPin, slaveNum slave=TLE5012B_S0);
                    Tle5012Ino(SPIClass3W *bus, uint8_t csPin, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin, slaveNum slave=TLE5012B_S0);
        errorTypes  begin();

};

/* @} */
}

#endif /** TLE5012_INO_HPP_ **/
