/**
 * @file        spic-arduino.hpp
 * @brief       Arduino PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "spic-arduino.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @brief Constructor of the Arduino SPIC class
 *
 * This function is setting the basics for a SPIC and the default spi.
 *
 */
SPICIno::SPICIno()
{
	spi = &SPI;
}

/**
 * @brief Construct a new SPICIno::SPICIno object of the Arduino SPIC class
 * 
 * This function sets some basic SPI modes for the default SPI port.
 * 
 * @param lsb    lowside (LSB) or highside (MSB) mode
 * @param mode   SPI mode
 * @param clock  SPI clock divider
 */
SPICIno::SPICIno(uint8_t lsb, uint8_t mode, uint8_t clock)
{
	this->SPISet.lsb = lsb;
	this->SPISet.mode = mode;
	this->SPISet.clock = clock;
	spi = &SPI;
}

/**
 * @brief Construct a new SPICIno::SPICIno object of the Arduino SPIC class
 *
 * This function sets all pins for a given SPI port, allowing a free setting
 * of the SPI interface
 *
 * @param port     SPI port if not default
 * @param csPin    chipselect pin for the SPI port
 * @param misoPin  miso pin number
 * @param mosiPin  mosi pin number
 * @param sckPin   systemclock pin number
 */
SPICIno::SPICIno(SPIClass &port, uint8_t csPin, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin)
{
	this->csPin = csPin;
	this->misoPin = misoPin;
	this->mosiPin = mosiPin;
	this->sckPin = sckPin;
	spi = &port;
}

/**
 * @brief Initialize the SPIC
 *
 * This function is initializing the chosen spi channel
 * with the given values for lsb, clock and mode
 *
 * @return      SPICIno::Error_t
 */
SPICIno::Error_t SPICIno::init()
{
	spi->begin();
	spi->setClockDivider(this->SPISet.divider);
	spi->setDataMode(this->SPISet.mode);
	spi->setBitOrder(this->SPISet.lsb);

	miso = new GPIOIno(this->misoPin, OUTPUT, GPIOIno::POSITIVE );
	mosi = new GPIOIno(this->mosiPin, OUTPUT, GPIOIno::POSITIVE );
	sck =  new GPIOIno(this->sckPin,  OUTPUT, GPIOIno::POSITIVE );
	return OK;
}

/**
 * @brief Deinitialize the SPIC
 *
 * This function is deinitializing the chosen spi channel.
 *
 * @return      SPICIno::Error_t
 */
SPICIno::Error_t SPICIno::deinit()
{
	spi->end();
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * @return             SPICIno::Error_t
 */
SPICIno::Error_t SPICIno::transfer(uint8_t send, uint8_t &received)
{
	received = spi->transfer(send);
	return OK;
}

/**
 * @brief transfers a data package via the spi bus with 16 bit length
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * @return             SPICWiced::Error_t
 */
SPICIno::Error_t SPICIno::transfer16(uint16_t send, uint16_t &received)
{
	uint8_t data_out_msb = (uint8_t)((send >> 8) & 0xFF);
	uint8_t data_out_lsb = (uint8_t)(send & 0xFF);

	uint8_t data_in_msb = spi->transfer(data_out_msb);
	uint8_t data_in_lsb = spi->transfer(data_out_lsb);

	received = (uint16_t)(((uint16_t)data_in_msb << 8) | (data_in_lsb));
	return OK;
}

#endif /** TLE5012_FRAMEWORK **/
