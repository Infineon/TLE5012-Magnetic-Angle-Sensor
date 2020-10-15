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
#include "gpio-arduino.hpp"
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
		uint8_t     csPin;                        //<! c\brief hipselect pin for the device
		uint8_t     misoPin;                      //<! \brief SPI miso pin
		uint8_t     mosiPin;                      //<! \brief SPI mosi pin
		uint8_t     sckPin;                       //<! \brief SPI system clock pin
		SPIClass    *spi;                         //<! \brief Arduino SPI class pointer

	public:
					SPICIno();
					SPICIno(uint8_t lsb, uint8_t mode, uint8_t divider,uint32_t clock);
					SPICIno(SPIClass &port, uint8_t csPin, uint8_t misoPin=MISO, uint8_t mosiPin=MOSI, uint8_t sckPin=SCK);
					~SPICIno();
		Error_t     init();
		Error_t     deinit();
		Error_t     transfer(uint8_t send, uint8_t &received);
		Error_t     transfer16(uint16_t send, uint16_t &received);
		Error_t     sendConfig();
		Error_t     receiveConfig();

		GPIOIno       *miso;                         //<! \brief shield enable GPIO for misoPin
		GPIOIno       *mosi;                         //<! \brief shield enable GPIO for mosiPin
		GPIOIno       *sck;                          //<! \brief shield enable GPIO for sckPin

		uint8_t    divider = SPI_CLOCK_DIV4;      //<! \brief the SPI clock divider
		uint8_t    lsb     = MSBFIRST;            //<! \brief LSB or MSB first
		uint8_t    mode    = SPI_MODE1;           //<! \brief SPI mode setting
		uint32_t   clock   = ARDUINO_SPI_CLOCK;   //<! \brief system clock rate

		SPISettings SPISet;                       //<! \brief Arduino SPI settings class

};
/** @} */

#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_ARDUINO_HPP_ **/
