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
#include "gpio-arduino.hpp"
#include "timer-arduino.hpp"
//#include "spic-arduino.hpp"
#include "spic-xmc.hpp"

/**
 * @brief represents a basic TLE5012
 *
 * This class provides a simple API for connecting and controlling motors.
 * Each motor is assigned to a Tle5012 which acts as output driver. Calls to
 * Tle5012Motor instances are mapped to calls to Tle5012. Therefore, this
 * class does not bring new features, it does only provide further abstraction.
 *
 * @see Tle5012
 */

#define PIN_SPI_EN    EN_PIN  /*!< Set switch on/off pin if we need one */

class Tle5012Ino: virtual public Tle5012b
{

	public:

		uint8_t mSpiNum = 0;          //!< Number of used SPI channel

					Tle5012Ino();
					Tle5012Ino(SPIClass &bus, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin);
		errorTypes  begin();
		errorTypes  begin(uint8_t csPin, slaveNum slave=TLE5012B_S0);

};

/**
 * @}
 */

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_PAL_INO_HPP_ **/