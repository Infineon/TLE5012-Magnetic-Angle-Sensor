/**
 * @file        spic-xmc.hpp
 * @brief       XMC4Arduino PAL for the SPI cover
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#if (TLE5012_SPIC_PAL == TLE5012_SPIC_XMC)

#ifndef SPIC_XMC_HPP_
#define SPIC_XMC_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include "../../../pal/spic.hpp"
#include <Arduino.h>
#include "SPI.h"
#include "Wire.h"

/**
 * @addtogroup xmcPal
 * @{
 */


/**
 * @brief XMC SPIC class
 * This class extens the XMC for Arduino library to be used with the TLE5012B sensor and its SSC
 * interface. Therefore we use original XMC library ports for setting up the specific SSC send/receive
 * functionality for the XMC types:
 * - Sensor2go kit which includes a XMC2go with a XMC1100 mcu
 * - XMC2go and compatible boards with XMX110 mcu
 * - XMC1100/XMC1300/XMC1400 boot kits (only the XMC1100 boot kit has Arduino compatible headers)
 * - XMC4700 relax kit and specially for this the SPI channels 0(default),1 and 2
 */

#define EN_PIN    8           /*!< TLE5012 Sensor2Go Kit has a switch on/off pin */

class SPICIno: virtual public SPIC
{
	private:
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

		XMC_3W_SPI_t m3Wire;                       //!< enhanced 3-Wire SPI parameter structure

		uint8_t     csPin   = PIN_SPI_SS;          //<! \brief hipselect pin for the device
		uint8_t     misoPin = PIN_SPI_MISO;        //<! \brief SPI miso pin
		uint8_t     mosiPin = PIN_SPI_MOSI;        //<! \brief SPI mosi pin
		uint8_t     sckPin  = PIN_SPI_SCK;         //<! \brief SPI system clock pin
		SPIClass    *spi;                          //<! \brief Arduino SPI class pointer

		Error_t     setupSPI();                    //!< initial 3-Wire SPI setup
		Error_t     initSpi();                     //!< initial startup of the 3-Wire SPI interface
		Error_t     sendConfig();
		Error_t     receiveConfig();
		Error_t     enableSpi();                   //!< enables 3-Wire SPI interface

	public:
					SPICIno();
					SPICIno(SPIClass &port, uint8_t csPin=PIN_SPI_SS, uint8_t misoPin=PIN_SPI_MISO, uint8_t mosiPin=PIN_SPI_MOSI, uint8_t sckPin=PIN_SPI_SCK);
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

#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_XMC_HPP_ **/

#endif /** TLE5012_SPIC_XMC **/
