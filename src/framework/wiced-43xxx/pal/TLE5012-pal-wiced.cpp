/** 
 * @file        TLE5012-pal-wiced.cpp
 * @brief       TLE5012 Wiced Hardware Platforms
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "TLE5012-pal-wiced.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

using namespace tle5012;

/**
 * @addtogroup wicedPal
 */

/**
 * Construct a new Tle5012Wiced::Tle5012Wiced object with default SPI and pin assignment.
 * Use this if:
 * - you have TLE5012B Sensor2go kit (all types)
 * - attached the breakout board on the default SPI of your MCU
 * - attached a bulk chip with the SSC interface to the default SPI of your MCU
 */
Tle5012Wiced::Tle5012Wiced():Tle5012b()
{
	Tle5012b::mSlave = TLE5012B_S0;
	Tle5012b::sBus = new SPICWiced(TLE94112_PIN_CS1);
}

/**
 * @brief Construct a new Tle5012Wiced::Tle5012Wiced object with chipselect and sensor slave
 * Use this constructor if:
 * - you use more than one sensor with one SPI channel (up to four are possible)
 * 
 * @param csPin    pin number of the CS pin
 * @param slave    optional sensor slave setting
 */
Tle5012Wiced::Tle5012Wiced(wiced_gpio_t csPin, slaveNum slave):Tle5012b()
{
	Tle5012b::mSlave = slave;
	Tle5012b::sBus = new SPICWiced(csPin);
}

/**
 * @brief begin method with default assignments for the SPI bus
 * and pin setting.
 * The EN pin is only available for the Sensor2go kit, therefore we only
 * set it in that case, otherwise it will be NULL.
 * 
 * @return errorTypes 
 */
errorTypes Tle5012Wiced::begin(void)
{
	// init helper libs
	sBus->init();
	Tle5012b::en = NULL;
	// start sensor
	enableSensor();
	writeSlaveNumber(Tle5012b::mSlave);
	// initial CRC check, should be = 0
	return (readBlockCRC());
}

#endif /** TLE5012_FRAMEWORK **/
/** @} */