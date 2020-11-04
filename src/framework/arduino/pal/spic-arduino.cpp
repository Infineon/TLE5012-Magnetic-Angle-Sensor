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
 * @addtogroup arduinoPal
 * @{
 */

/**
 * @brief Construct a new SPICIno::SPICIno object
 * 
 * This function is setting the basics for a SPIC and the default spi.
 * Use this call if:
 * - you use the default SPI channel
 * - if use the default SPI channel with up to four sensors
 * 
 * @param csPin optional chipselect pin. If not set it will be default PIN_SPI_SS
 */
SPICIno::SPICIno(uint8_t csPin)
{
	this->csPin = csPin;
	this->spi = &SPI;
}

/**
 * @brief Construct a new SPICIno::SPICIno object of the Arduino SPIC class
 *
 * This function sets all pins for a given SPI port, allowing a free setting
 * of the SPI interface
 * Use this call of:
 * - you want to use a different than this default SPI channel
 * - also with up to four sensors per channel
 *
 * @param port     SPI port if not default
 * @param csPin    chipselect pin for the SPI port
 * @param misoPin  miso pin number
 * @param mosiPin  mosi pin number
 * @param sckPin   systemclock pin number
 */
SPICIno::SPICIno(SPIClass3W &port, uint8_t csPin, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin)
{
	this->csPin   = csPin;
	this->misoPin = misoPin;
	this->mosiPin = mosiPin;
	this->sckPin  = sckPin;
	this->spi = &port;
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
	this->spi->begin(this->misoPin, this->mosiPin, this->sckPin, this->csPin);
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
	this->spi->endTransaction();
	this->spi->end();
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * 
 * @return             SPICIno::Error_t
 */
SPICIno::Error_t SPICIno::transfer(uint8_t send, uint8_t &received)
{
	received = this->spi->transfer(send);
	return OK;
}

/**
 * @brief transfers a data package via the spi bus with 16 bit length
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * 
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

/**
 * @brief 
 * Triggers an update in the register buffer. This function
 * should be triggered once before UPD registers where read as
 * it generates a snapshot of the UPD register values at trigger point
 * 
 * @return SPICIno::Error_t 
 */
SPICIno::Error_t SPICIno::triggerUpdate()
{
	digitalWrite(this->sckPin, LOW);
	digitalWrite(this->mosiPin, HIGH);
	digitalWrite(this->csPin, LOW);
	//grace period for register snapshot
	delayMicroseconds(5);
	digitalWrite(this->csPin, HIGH);
	return OK;
}

/*!
* Main SPI three wire communication functions for sending and receiving data
* @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
* @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
* @param received_data pointer to data structure buffer for the read data
* @param size_of_received_data size of data words to be read
*/
SPICIno::Error_t SPICIno::sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
{
	this->spi->setCSPin(this->csPin);
	this->spi->sendReceiveSpi(sent_data,size_of_sent_data,received_data,size_of_received_data);
	return OK;
}

/** @} */

#endif /** TLE5012_FRAMEWORK **/
