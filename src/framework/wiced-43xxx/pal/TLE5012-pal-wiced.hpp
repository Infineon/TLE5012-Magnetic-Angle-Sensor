/*!
 * \file        TLE5012-pal-wiced.hpp
 * \name        TLE5012-pal-wiced.hpp - Wiced Hardware Abstraction Layer
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \ref         wicedPal
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLE5012_PAL_WICED_HPP_
#define TLE5012_PAL_WICED_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

namespace tle5012
{

/**
 * @addtogroup wicedPal
 *
 * @{
 */

#include "../../../corelib/TLE5012b.hpp"
#include <platform.h>
#include <wiced_platform.h>
#include <gpio-wiced.hpp>
#include <timer-wiced.hpp>
#include <spic-wiced.hpp>

//! Check for XMC mcu family */
#define PIN_SPI_EN    UNUSED_PIN  /*!< TLE5012 with any other PCB has no switch on/off */

/*!
 * Standard chip select pin for first TLE5012 sensor
 * on Arduino header
 */
#define TLE94112_PIN_CS1     WICED_GPIO_7

/**
 * @brief represents a basic TLE5012b Wiced class.
 *
 * This class provides a simple API for connecting Wiced/Genuio and compatible
 * MCUs. As the default interface for the sensor is the 3wire SSC SPI interface,
 * the default SPIClass is extended by the SPIclass3W.
 *
 * @see Tle5012
 */

class Tle5012Wiced: virtual public Tle5012b
{

	public:

		uint8_t     mSpiNum = 0;          //!< Number of used SPI channel

					Tle5012Wiced();
					Tle5012Wiced(wiced_gpio_t csPin, slaveNum slave=TLE5012B_S0);
		errorTypes  begin();

};

/**
 * @}
 */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_PAL_WICED_HPP_ **/