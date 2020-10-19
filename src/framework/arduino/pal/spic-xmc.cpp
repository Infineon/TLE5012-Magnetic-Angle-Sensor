/**
 * @file        spic-arduino.hpp
 * @brief       Arduino PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "spic-xmc.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)
#if (TLE5012_SPIC_PAL == TLE5012_SPIC_XMC)

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
	enableSpi();
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
	spi->endTransaction();
	spi->end();
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
	received = spi->transfer(send);
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
 * XMC microcontroller familly needs special settings for
 * using SPI channels settings for each type and SPI channel.
 * Also the send/receive should be done in XMC CMSIS function for
 * a fast data fetch by avoiding the SPI library.
 * 
 * @return SPIIno::Error_t 
 */
SPICIno::Error_t SPICIno::setupSPI()
{
	m3Wire.miso_open.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
	m3Wire.miso_close.mode = XMC_GPIO_MODE_INPUT_TRISTATE;

	m3Wire.mosi_open.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	m3Wire.mosi_close.mode = XMC_GPIO_MODE_INPUT_TRISTATE;

	m3Wire.sck_config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
	m3Wire.channel_config.baudrate = this->clock;
	m3Wire.channel_config.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER;
	m3Wire.channel_config.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS;
	m3Wire.channel_config.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE;

	#if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
		m3Wire.channel = XMC_SPI0_CH1;
		m3Wire.input_source = XMC_INPUT_C;
		m3Wire.miso_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
		m3Wire.miso_close.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
		m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
		m3Wire.mosi_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
		m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
		m3Wire.sck_config.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
	#elif defined(XMC1100_Boot_Kit) || defined(XMC1300_Boot_Kit) || defined(XMC1400_Boot_Kit)
		m3Wire.channel = XMC_SPI0_CH0;
		m3Wire.input_source = XMC_INPUT_D;
		m3Wire.miso_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
		m3Wire.miso_close.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
		m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6;
		m3Wire.mosi_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
		m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6;
		m3Wire.sck_config.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
	#elif defined(XMC4700_Relax_Kit)
		m3Wire.miso_close.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
		m3Wire.miso_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
		m3Wire.mosi_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
		m3Wire.sck_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
		if (mSpiNum == 1) {
			m3Wire.channel = XMC_SPI1_CH1;
			m3Wire.input_source = XMC_INPUT_D;
			m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2;
			m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2;
		}else if (mSpiNum == 2) {
			m3Wire.channel = XMC_SPI2_CH1;
			m3Wire.input_source = XMC_INPUT_D;
			m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
			m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
		}else {
			m3Wire.channel = XMC_SPI2_CH0;
			m3Wire.input_source = XMC_INPUT_C;
			m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
			m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
		}
	#endif
	return OK;
}

SPICIno::Error_t SPICIno::initSpi()
{
	if((m3Wire.channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_I2C)
	{
		Wire.end();
	}
	XMC_SPI_CH_EnableMasterClock(m3Wire.channel);
	XMC_SPI_CH_Init(m3Wire.channel, &(m3Wire.channel_config));

	XMC_SPI_CH_SetWordLength(m3Wire.channel, (uint8_t)16U);
	XMC_SPI_CH_SetFrameLength(m3Wire.channel, (uint8_t)16U);
	XMC_SPI_CH_SetInputSource(m3Wire.channel, XMC_SPI_CH_INPUT_DIN0, (uint8_t)m3Wire.input_source);

	XMC_SPI_CH_ConfigureShiftClockOutput(m3Wire.channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
	XMC_SPI_CH_SetBaudrate(m3Wire.channel, (uint32_t)m3Wire.channel_config.baudrate);
	XMC_SPI_CH_SetBitOrderMsbFirst(m3Wire.channel);

	XMC_SPI_CH_Start(m3Wire.channel);
	return OK;
}

/**
 * @brief enables the XMC 3wire SPI settings
 * 
 * @return SPICIno::Error_t 
 */
SPICIno::Error_t SPICIno::enableSpi()
{
	m3Wire.mosi	= mapping_port_pin[this->mosiPin];
	m3Wire.miso	= mapping_port_pin[this->misoPin];
	m3Wire.sck	= mapping_port_pin[this->sckPin];
	setupSPI();
	initSpi();
	XMC_GPIO_Init(m3Wire.sck.port, m3Wire.sck.pin, &m3Wire.sck_config);
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

/**
 * @brief set SPI to send mode
 * 
 * @return SPIIno::Error_t
 */
SPICIno::Error_t SPICIno::sendConfig()
{
	XMC_GPIO_Init(m3Wire.miso.port, m3Wire.miso.pin, &m3Wire.miso_close);
	XMC_GPIO_Init(m3Wire.mosi.port, m3Wire.mosi.pin, &m3Wire.mosi_open);
}

/**
 * @brief set SPI to receive mode
 * 
 * @return SPIIno::Error_t
 */
SPICIno::Error_t SPICIno::receiveConfig()
{
	XMC_GPIO_Init(m3Wire.miso.port, m3Wire.miso.pin, &m3Wire.miso_open);
	XMC_GPIO_Init(m3Wire.mosi.port, m3Wire.mosi.pin, &m3Wire.mosi_close);
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
	uint32_t data_index = 0;
	//send via TX
	sendConfig();
	digitalWrite(this->csPin, LOW);

	for(data_index = 0; data_index < size_of_sent_data; data_index++)
	{
		XMC_SPI_CH_Transmit(m3Wire.channel, sent_data[data_index], XMC_SPI_CH_MODE_STANDARD);
		while((XMC_SPI_CH_GetStatusFlag(m3Wire.channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
		XMC_SPI_CH_ClearStatusFlag(m3Wire.channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);
		while (XMC_USIC_CH_GetReceiveBufferStatus(m3Wire.channel) == 0U);
		received_data[0] = XMC_SPI_CH_GetReceivedData(m3Wire.channel);
	}

	// receive via RX
	receiveConfig();
	delayMicroseconds(5);

	for(data_index = 0; data_index < size_of_received_data; data_index++)
	{
		XMC_SPI_CH_Transmit(m3Wire.channel, 0x0000, XMC_SPI_CH_MODE_STANDARD);
		while((XMC_SPI_CH_GetStatusFlag(m3Wire.channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
		XMC_SPI_CH_ClearStatusFlag(m3Wire.channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);
		while (XMC_USIC_CH_GetReceiveBufferStatus(m3Wire.channel) == 0U);
		received_data[data_index] = XMC_SPI_CH_GetReceivedData(m3Wire.channel);
	}

	digitalWrite(this->csPin, HIGH);
}

#endif /** TLE5012_SPIC_XMC **/
#endif /** TLE5012_FRAMEWORK **/
