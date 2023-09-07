/**
 * @file        spic-mtb.hpp
 * @brief       Mtb PAL for the SPI cover
 * @date        Spt 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "spic-mtb.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_MTB)
#include "mtb_rtos.h"
#include <mtb.h>
#include <platform.h>

using namespace tle5012;

/**
 * @brief Constructor of the MTB SPIC class
 *
 * This function is setting the basics for a SPIC and the default
 * spi on Arduino which is implemented as MTB_SPI_0 by patching the following:
 *
 */
SPICMtb::SPICMtb() : csPin(MTB_GPIO_NONE), port(MTB_SPI_0)
{
	this->spi.port = port;
	this->spi.chip_select = csPin;
	this->spi.speed = 1000000;
	this->spi.mode = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_LOW | SPI_NO_DMA | SPI_LSB_FIRST | SPI_CS_ACTIVE_LOW);
	this->spi.bits = 8;
}

/**
 * @brief Construct a new SPICMtb::SPICMtb object
 *
 * This function is setting the basics for a SPIC. It allows to set the
 * SPI channel and the used GPIOs if they are different from the standard GPIOs.
 *
 * @param port     SPI channel to be used
 * @param csPin    Number of the desired ChipSelect pin
 * 
 * @attention Yet not implemented
 */
SPICMtb::SPICMtb(mtb_spi_t port, mtb_gpio_t csPin)
{
	this->spi.port = port;
	this->spi.chip_select = csPin;
	this->spi.speed = 1000000;
	this->spi.mode = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_LOW | SPI_NO_DMA | SPI_LSB_FIRST | SPI_CS_ACTIVE_LOW);
	this->spi.bits = 8;
}

/**
 * @brief Construct a new SPICMtb::SPICMtb object
 * 
 * This function allows to set all parameters of the SPI master.
 * 
 * @param port     SPI channel to be used
 * @param csPin    Number of the desired ChipSelect pin
 * @param speed    SPI baud setting
 * @param mode     SPI mode setting
 * @param bits     number of bits in one command
 * 
 * @attention This does not set the platform_spi_peripherals structure yet
 */
SPICMtb::SPICMtb(mtb_spi_t port, mtb_gpio_t csPin, uint8_t speed, uint8_t mode, uint8_t bits)
{
	this->spi.port = port;
	this->spi.chip_select = csPin;
	this->spi.speed = speed;
	this->spi.mode = mode;
	this->spi.bits = bits;
}

/**
 * @brief Destructor of the MTB SPIC class
 *
 */
SPICMtb::~SPICMtb()
{
	deinit();
}
/**
 * @brief Initialize the SPIC
 *
 * This function is initializing the chosen spi channel
 * with the given values for lsb,clock and mode
 *
 * @return      SPICMtb::Error_t
 */
SPICMtb::Error_t SPICMtb::init()
{
	this->segment.tx_buffer = sendBuffer;
	this->segment.rx_buffer = receiveBuffer;
	this->segment.length = 1;

	mtb_spi_init( &this->spi );
	return OK;
}

/**
 * @brief Deinitialize the SPIC
 *
 * This function is deinitializing the chosen spi channel.
 *
 * @return      SPICMtb::Error_t
 */
SPICMtb::Error_t SPICMtb::deinit()
{
	mtb_spi_deinit( &this->spi );
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 *
 * @param send         address and/or command to send
 * @param received     received data from spi bus
 * @return             SPICMtb::Error_t
 */
SPICMtb::Error_t SPICMtb::transfer(uint8_t send, uint8_t &received)
{
	sendBuffer[0] = send;
	receiveBuffer[0] = received;
	mtb_spi_transfer( &this->spi, &this->segment, 1);
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 *
 * @param send         address and/or command to send as 16bit
 * @param received     received data from spi bus as 16bit
 * @return             SPICMtb::Error_t
 */
SPICMtb::Error_t SPICMtb::transfer16(uint16_t send, uint16_t &received)
{
	sendBuffer[0] = (uint8_t)((send >> 8) & 0xFF);
	sendBuffer[1] = (uint8_t)(send & 0xFF);

	mtb_spi_transfer( &this->spi, &this->segment, 2);
	received = (uint16_t)(((uint16_t)receiveBuffer[0] << 8) | (receiveBuffer[1]));

	return OK;
}

#endif /** TLE5012_FRAMEWORK **/
