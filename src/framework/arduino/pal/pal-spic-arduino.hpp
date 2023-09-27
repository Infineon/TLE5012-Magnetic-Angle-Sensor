/**
 * @file        spic-arduino.hpp
 * @brief       Arduino PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */



#ifndef PAL_SPIC_ARDUINO_HPP_
#define PAL_SPIC_ARDUINO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include "Arduino.h"
#include "../../../pal/pal-spic.hpp"
#include "spi3w-ino.hpp"
#include "pal-pin-types.hpp"

namespace tle5012
{

/**
 * @addtogroup arduinoPal
 * @{
 */

/**
 * @brief Arduino SPIC class
 * This function is setting the basics for a SPIC and the default spi.
 */

class SPICIno: virtual public SPICPAL
{
	private:

		uint8_t       csPin   = PIN_SPI_SS;          //<! \brief chip select pin for the device
		uint8_t       misoPin = PIN_SPI_MISO;        //<! \brief SPI miso pin
		uint8_t       mosiPin = PIN_SPI_MOSI;        //<! \brief SPI mosi pin
		uint8_t       sckPin  = PIN_SPI_SCK;         //<! \brief SPI system clock pin
		SPIClass3W    *spi    = NULL;                //<! \brief extended SPI class pointer

	public:

					SPICIno(uint8_t csPin=PIN_SPI_SS);
					SPICIno(SPIClass3W &port, uint8_t csPin=PIN_SPI_SS, uint8_t misoPin=PIN_SPI_MISO, uint8_t mosiPin=PIN_SPI_MOSI, uint8_t sckPin=PIN_SPI_SCK);
					~SPICIno();
		Error_t     init();
		Error_t     deinit();
		Error_t     triggerUpdate();
		Error_t     sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

};

/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** PAL_SPIC_ARDUINO_HPP_ **/
