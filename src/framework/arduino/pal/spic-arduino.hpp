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
#if (TLE5012_SPIC_PAL == TLE5012_SPIC_ARDUINO)

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
		uint8_t     csPin   = PIN_SPI_SS;         //<! \brief hipselect pin for the device
		uint8_t     misoPin = PIN_SPI_MISO;       //<! \brief SPI miso pin
		uint8_t     mosiPin = PIN_SPI_MOSI;       //<! \brief SPI mosi pin
		uint8_t     sckPin  = PIN_SPI_SCK;        //<! \brief SPI system clock pin
		SPIClass    *spi;                         //<! \brief Arduino SPI class pointer
		Error_t     enableSpi();                  //!< enables 3-Wire SPI interface
		Error_t     sendConfig();
		Error_t     receiveConfig();

	public:
					SPICIno();
					SPICIno(SPIClass &port, uint8_t csPin, uint8_t misoPin=PIN_SPI_MISO, uint8_t mosiPin=PIN_SPI_MOSI, uint8_t sckPin=PIN_SPI_SCK);
					~SPICIno();
		Error_t     init();
		Error_t     deinit();
		Error_t     triggerUpdate();
		Error_t     transfer(uint8_t send, uint8_t &received);
		Error_t     transfer16(uint16_t send, uint16_t &received);
		Error_t     sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

		uint8_t     divider = SPI_CLOCK_DIV4;      //<! \brief the SPI clock divider
		uint8_t     lsb     = MSBFIRST;            //<! \brief LSB or MSB first
		uint8_t     mode    = SPI_MODE1;           //<! \brief SPI mode setting
		uint32_t    clock   = 1000000U;            //<! \brief system clock rate

		SPISettings SPISet;                        //<! \brief Arduino SPI settings class

};

/** @} */

#endif /** TLE5012_SPIC_ARDUINO **/
#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_ARDUINO_HPP_ **/
