/**
 * @file        spic-arduino.hpp
 * @brief       WICED PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "spic-wiced.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)
#include "wiced_rtos.h"
#include <wiced.h>
#include <platform.h>

using namespace tle5012;

/**
 * @brief Constructor of the WICED SPIC class
 *
 * This function is setting the basics for a SPIC and the default
 * spi on Arduino which is implemented as WICED_SPI_0 by patching the following:
 *
 * - \<WICED_SDK\>/platforms/\<platform_name\>/platform.h
 *   add WICED_SPI_0, to the wiced_spi_t
 * - \<WICED_SDK\>/platforms/\<platform_name\>/platform.c
 *   add the following to the platform_spi_peripherals
 *   [WICED_SPI_0]  =
 *      {
 *          .port                    = BCM4390X_SPI_0,
 *          .pin_mosi                = &platform_gpio_pins[WICED_GPIO_6],
 *          .pin_miso                = &platform_gpio_pins[WICED_GPIO_8],
 *          .pin_clock               = &platform_gpio_pins[WICED_GPIO_5],
 *          .pin_cs                  = &platform_gpio_pins[WICED_GPIO_7],
 *          .driver                  = &spi_bb_driver,
 *      },
 *    which sets the Arduino header GPIOs and the bit banging driver.
 *
 * @param csPin    Number of the desired ChipSelect pin
 *
 * @attention Yet not implemented
 */
SPICWiced::SPICWiced(wiced_gpio_t csPin)
{
	this->spi.port = WICED_SPI_0;
	this->spi.chip_select = csPin;
	this->spi.speed = 1000000;
	this->spi.mode = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_LOW | SPI_NO_DMA | SPI_MSB_FIRST | SPI_CS_ACTIVE_LOW);
	this->spi.bits = 16U;
	this->csPin = csPin;
}

/**
 * @brief Construct a new SPICWiced::SPICWiced object
 *
 * This function allows to set all parameters of the SPI master.
 *
 * @param port     SPI channel to be used
 * @param csPin    Number of the desired ChipSelect pin
 * @param misoPin  miso pin number
 * @param mosiPin  mosi pin number
 * @param sckPin   systemclock pin number
 *
 * @attention This does not set the platform_spi_peripherals structure yet
 */
SPICWiced::SPICWiced(wiced_spi_t port, wiced_gpio_t csPin, wiced_gpio_t misoPin , wiced_gpio_t mosiPin , wiced_gpio_t sckPin )
{
	this->spi.port = port;
	this->spi.chip_select = csPin;
	this->spi.speed = 1000000;
	this->spi.mode = (SPI_CLOCK_RISING_EDGE | SPI_CLOCK_IDLE_LOW | SPI_NO_DMA | SPI_MSB_FIRST | SPI_CS_ACTIVE_LOW);
	this->spi.bits = 16U;
	this->csPin   = csPin;
	this->misoPin = misoPin;
	this->mosiPin = mosiPin;
	this->sckPin  = sckPin;
}

/**
 * @brief Destructor of the WICED SPIC class
 *
 */
SPICWiced::~SPICWiced()
{
	deinit();
}
/**
 * @brief Initialize the SPIC
 *
 * This function is initializing the chosen spi channel
 * with the given values for lsb,clock and mode
 *
 * @return      SPICWiced::Error_t
 */
SPICWiced::Error_t SPICWiced::init()
{
	this->segment.tx_buffer = sendBuffer;
	this->segment.rx_buffer = receiveBuffer;
	this->segment.length = 2;

	wiced_spi_init( &this->spi );
	wiced_gpio_init(this->csPin, OUTPUT_PUSH_PULL);
	return OK;
}

/**
 * @brief Deinitialize the SPIC
 *
 * This function is deinitializing the chosen spi channel.
 *
 * @return      SPICWiced::Error_t
 */
SPICWiced::Error_t SPICWiced::deinit()
{
	wiced_spi_deinit( &this->spi );
	return OK;
}

/**
 * @brief transfers a data package via the spi bus
 *
 * @param send         address and/or command to send as 16bit
 * @param received     received data from spi bus as 16bit
 * @return             SPICWiced::Error_t
 */
SPICWiced::Error_t SPICWiced::transfer16(uint16_t send, uint16_t &received)
{
	sendBuffer[0] = (uint8_t)((send >> 8) & 0xFF);
	sendBuffer[1] = (uint8_t)(send & 0xFF);

	wiced_spi_transfer( &this->spi, &this->segment, 1);
	received = (uint16_t)(((uint16_t)receiveBuffer[0] << 8) | (receiveBuffer[1]));

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
SPICWiced::Error_t SPICWiced::triggerUpdate()
{
	wiced_gpio_output_low(this->sckPin);
	wiced_gpio_output_high(this->mosiPin);
	wiced_gpio_output_low(this->csPin);
	// grace period for register snapshot
	wiced_rtos_delay_microseconds( 5 );
	wiced_gpio_output_high(this->csPin);
	return OK;
}

/*!
* Main SPI three wire communication functions for sending and receiving data
* @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
* @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
* @param received_data pointer to data structure buffer for the read data
* @param size_of_received_data size of data words to be read
*/
SPICWiced::Error_t SPICWiced::sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
{
	uint32_t data_index = 0;
	//send via TX

	wiced_gpio_init(this->misoPin, INPUT_HIGH_IMPEDANCE);
	wiced_gpio_init(this->mosiPin, OUTPUT_PUSH_PULL);
	wiced_gpio_output_low(this->csPin);
	for(data_index = 0; data_index < size_of_sent_data; data_index++)
	{
		transfer16(sent_data[data_index],received_data[0]);
	}

	// For timing reasons we use only one gpio change
	// wiced_gpio_init(this->misoPin, OUTPUT_PUSH_PULL);
	wiced_gpio_init(this->mosiPin, INPUT_HIGH_IMPEDANCE);
	wiced_rtos_delay_microseconds( 5 );

	for(data_index = 0; data_index < size_of_received_data; data_index++)
	{
		transfer16(0x0000,received_data[data_index]);
	}

	wiced_gpio_output_high(this->csPin);
	return OK;
}

#endif /** TLE5012_FRAMEWORK **/
