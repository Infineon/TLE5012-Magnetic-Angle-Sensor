/*
 * @file        spi-platf-ino.hpp
 * @brief       TLE5012 Arduino SPI class wrapper
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include "Arduino.h"
#include "SPI.h"

#ifndef SPI_PLATF_INO_HPP
#define SPI_PLATF_INO_HPP

#define SPEED            1000000U //!< default speed of SPI transfer
#define MAX_SLAVE_NUM    4        //!< Maximum numbers of slaves on one SPI bus
                                  //!< Attention, keep in mind, you can set more different chipselect pins, but
                                  //!< you can not separate more than 4 sensors data streams from each other


class Tle5012b_SPI : public SPIClass
{
	public:

	Tle5012b_SPI(uint8_t spiNum = 0);
	~Tle5012b_SPI();

	uint8_t mCS;                    //!< Pin for chip select
	uint8_t mSpiNum;                //!< Number of used SPI channel

	void begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs);

	void setCSPin(uint8_t cs);
	void sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

	private:

		uint8_t mMOSI;                //!< Pin for SPI MOSI
		uint8_t mMISO;                //!< Pin for SPI MISO
		uint8_t mSCK;                 //!< Pin for CLOCK
		SPISettings mSPISetting;      //!< We need the original SPI class setting in case none XMC microcontroller

		#if defined(UC_FAMILY) && (UC_FAMILY == 1 || UC_FAMILY == 4)
		/*!
		 * The enhanced 3-Wire parameter structure includes miso/mosi open and close
		 * setting and for the enable pin setting for the Sensor2Go evaluation boards.
		 */
		typedef struct
		{
			XMC_USIC_CH_t*           channel;
			XMC_SPI_CH_CONFIG_t      channel_config;
			XMC_PORT_PIN_t           mosi;
			XMC_GPIO_CONFIG_t        mosi_open;
			XMC_GPIO_CONFIG_t        mosi_close;
			XMC_PORT_PIN_t           miso;
			XMC_GPIO_CONFIG_t        miso_open;
			XMC_GPIO_CONFIG_t        miso_close;
			XMC_USIC_INPUT_t         input_source;
			XMC_PORT_PIN_t           sck;
			XMC_GPIO_CONFIG_t        sck_config;
		} XMC_3W_SPI_t;

		XMC_3W_SPI_t m3Wire;        //!< enhanced 3-Wire SPI parameter structure

		void setupSPI();            //!< initial 3-Wire SPI setup
		void initSpi();             //!< initial startup of the 3-Wire SPI interface
		void enableSpi();           //!< enables 3-Wire SPI interface
		#endif
};

#endif
#endif