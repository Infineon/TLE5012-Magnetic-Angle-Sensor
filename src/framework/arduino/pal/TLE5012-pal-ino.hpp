/*!
 * \file        TLE5012-pal-ino.hpp
 * \name        TLE5012-pal-ino.hpp - Arduino Hardware Abstraction Layer
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.0.0
 * \ref         arduinoPal
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLE5012_PAL_INO_HPP_
#define TLE5012_PAL_INO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup arduinoPal
 * @{
 */

#include "../../../corelib/TLE5012b.hpp"
#include <Arduino.h>
#include "spic-arduino.hpp"
#include "gpio-arduino.hpp"
#include "spic-arduino.hpp"

//! Check for XMC mcu family */
#define PIN_SPI_EN    UNUSED_PIN  /*!< TLE5012 with any other PCB has no switch on/off */

/**
 * @brief represents a basic TLE5012b Arduino class.
 *
 * This class provides a simple API for connecting Arduino/Genuio and compatible
 * MCUs. As the default interface for the sensor is the 3wire SSC SPI interface,
 * the default SPIClass is extended by the SPIclass3W.
 *
 * @see Tle5012
 */

class Tle5012Ino: virtual public Tle5012b
{

	public:

		uint8_t     mSpiNum = 0;          //!< Number of used SPI channel

					Tle5012Ino();
					Tle5012Ino(uint8_t csPin, slaveNum slave=TLE5012B_S0);
					Tle5012Ino(SPIClass3W &bus, uint8_t csPin, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin, slaveNum slave=TLE5012B_S0);
		errorTypes  begin();

};

/**
 * @}
 */

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_PAL_INO_HPP_ **/