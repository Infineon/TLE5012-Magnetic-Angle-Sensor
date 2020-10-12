/**
 * @file        spic-arduino.hpp
 * @brief       Arduino PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef SPIC_ARDUINO_HPP_
#define SPIC_ARDUINO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include "../../../pal/spic.hpp"
#include <Arduino.h>
#include "SPI.h"

/**
 * @addtogroup arduinoPal
 * @{
 */


/**
 * @brief Arduino SPIC class
 *
 */
class SPICIno: virtual public SPIC
{
	private:
		uint8_t     csPin;
		uint8_t     misoPin;
		uint8_t     mosiPin;
		uint8_t     sckPin;
		SPIClass    *spi;
		uint8_t     lsb;
		uint8_t     mode;
		uint8_t     clock;

	public:
					SPICIno();
					SPICIno(uint8_t lsb, uint8_t mode, uint8_t clock);
					SPICIno(SPIClass &port, uint8_t csPin, uint8_t misoPin=MISO, uint8_t mosiPin=MOSI, uint8_t sckPin=SCK);
					~SPICIno();
		Error_t     init();
		Error_t     deinit();
		Error_t     transfer(uint8_t send, uint8_t &received);
		Error_t     transfer16(uint16_t send, uint16_t &received);
};
/** @} */

#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_ARDUINO_HPP_ **/
