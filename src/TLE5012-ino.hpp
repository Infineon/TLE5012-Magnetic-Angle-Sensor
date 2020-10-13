/*!
 * \file        TLE5012-ino.hpp
 * \name        TLE5012-ino.hpp - Arduino library for the Infineon Tle5012 magnetic angular sensor
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \ref         tle5012ino
 * \version     2.0.0
 * \brief       This is a Arduino platform file use Infineon's TLE5012B magnetic angular sensor
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLE5012_INO_HPP_
#define TLE5012_INO_HPP_

#include "config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup inoApi
 * @{
 */

#include "corelib/TLE5012b.hpp"
#include "framework/arduino/wrapper/TLE5012-platf-ino.hpp"

/**
 * @class Tle5012Ino
 *
 * @brief represents the TLE5012 base class
 *
 * This class provides a simple API for connecting the TLE5012 via SSC interface,
 * which is included into all flavours the TLE5012 sensor. This setup also
 * works with the Sens2Kit (Sensor including XMC1100 mcu), breakout board (only the Sensor
 * from the Sens2Kit) and bulk chip (read the section on who to connect the bulk chip via 3wire SPI).
 */

class Tle5012Ino: virtual public TLE5012Ino
{
	public:
		//! \brief standard constructor with default SPI and pin assignment
		Tle5012Ino(void);

		/*!
		 * \brief constructor with individual SPI assignment
		 *
		 * \param bus     void pointer to the object representing the SPI class
		 */
		Tle5012Ino(SPIClass &bus);

		/*!
		 * \brief constructor with individual SPI and pin assignment
		 *
		 * \param bus      void pointer to the object representing the SPI class
		 * \param misoPin  MISO pin for the SPI/SSC interface
		 * \param mosiPin  MOSI pin for the SPI/SSC interface
		 * \param sckPin   system clock pin for external sensor clock setting
		 */
		Tle5012Ino(SPIClass &bus, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin);

		/*! \brief begin method with default assignments for the SPI bus
		 * and pin setting.
		 * Use this if you have Sensor2go Kit or only one sensor used with Arduino default SPI
		 */
		errorTypes begin();

		/*! \brief begin method with individual cs and slave number assignment
		 * Use this method if you connect up to four sensors on one SPI channel or
		 * if you use a none standard cs (chipselect) pin.
		 *
		 * \param csPin    pin number of the CS pin
		 * \param slave    slave offset setting for the SNR register, default is TLE5012B_S0
		 */
		errorTypes begin(uint8_t csPin, slaveNum slave=TLE5012B_S0);
};
/* @} */

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_INO_HPP_ **/
