/**
 * @file        spic-wiced.hpp
 * @brief       WICED PAL for the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef SPIC_WICED_HPP_
#define SPIC_WICED_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include "../../../pal/spic.hpp"
#include <platform.h>
#include <wiced_platform.h>
#include "wiced_time.h"
#include "wiced_rtos.h"

namespace tle5012
{

/**
 * @addtogroup wicedPal
 * @{
 */


/**
 * @brief Wiced SPIC class
 *
 */
class SPICWiced: virtual public SPIC
{
	private:
		wiced_gpio_t       csPin   = WICED_GPIO_7;
		wiced_gpio_t       misoPin = WICED_GPIO_8;
		wiced_gpio_t       mosiPin = WICED_GPIO_6;
		wiced_gpio_t       sckPin  = WICED_GPIO_5;
		wiced_spi_t        port;
		wiced_spi_device_t spi;
		uint8_t            lsb;
		uint8_t            mode;
		uint8_t            clock;

		uint8_t           sendBuffer[2];
		uint8_t           receiveBuffer[2];
		bool               spiSetting = false;

		//* @brief Definition of the SPI-Segment which contains the data for the communication
		wiced_spi_message_segment_t segment;

	public:

		SPICWiced(wiced_gpio_t csPin);
		SPICWiced(wiced_spi_t port, wiced_gpio_t csPin, wiced_gpio_t misoPin , wiced_gpio_t mosiPin , wiced_gpio_t sckPin );
		~SPICWiced();
		Error_t     init();
		Error_t     deinit();
		Error_t     transfer16(uint16_t send, uint16_t &received);
		Error_t     triggerUpdate();
		Error_t     sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

};

/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_WICED_HPP_ **/
