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
#include "../wrapper//spi-platf-ino.hpp"

/**
 * @addtogroup arduinoPal
 * @{
 */

/**
 * @brief Arduino SPIC class
 * This class can be used for all Arduino/Genuino and compliant mcu if:
 * - you use a breakout board with a 3wire SSC SPI interface
 * - you use a bulk chip with a 3wire SSC SPI interface (see wiki page on how to connect)
 */

class SPICIno: virtual public SPIC
{
	private:

		uint8_t       csPin   = PIN_SPI_SS;          //<! \brief hipselect pin for the device
		uint8_t       misoPin = PIN_SPI_MISO;        //<! \brief SPI miso pin
		uint8_t       mosiPin = PIN_SPI_MOSI;        //<! \brief SPI mosi pin
		uint8_t       sckPin  = PIN_SPI_SCK;         //<! \brief SPI system clock pin
		Tle5012b_SPI  *spi;                          //<! \brief extended SPI class pointer

	public:
					SPICIno();
					SPICIno(Tle5012b_SPI &port, uint8_t csPin=PIN_SPI_SS, uint8_t misoPin=PIN_SPI_MISO, uint8_t mosiPin=PIN_SPI_MOSI, uint8_t sckPin=PIN_SPI_SCK);
					~SPICIno();
		Error_t     init();
		Error_t     deinit();
		Error_t     triggerUpdate();
		Error_t     transfer(uint8_t send, uint8_t &received);
		Error_t     transfer16(uint16_t send, uint16_t &received);
		Error_t     sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

};

/** @} */

#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_ARDUINO_HPP_ **/
