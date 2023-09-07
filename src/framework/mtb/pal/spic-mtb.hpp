/**
 * @file        spic-mtb.hpp
 * @brief       MTB PAL for the SPI cover
 * @date        Spt 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef SPIC_MTB_HPP_
#define SPIC_MTB_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_MTB)

#include "../../../pal/spic.hpp"
#include <platform.h>
#include <mtb_platform.h>

namespace tle5012
{

/**
 * @addtogroup mtbPal
 * @{
 */


/**
 * @brief Mtb SPIC class
 *
 */
class SPICMtb: virtual public SPIC
{
	private:
		mtb_gpio_t         csPin;
		mtb_gpio_t         misoPin;
		mtb_gpio_t         mosiPin;
		mtb_gpio_t         sckPin;

		mtb_spi_t          port;
		mtb_spi_device_t   spi;
		uint8_t     lsb;
		uint8_t     mode;
		uint8_t     clock;

		uint8_t sendBuffer[2];
		uint8_t receiveBuffer[2];
		bool spiSetting = false;

		//* @brief Definition of the SPI-Segment which contains the data for the communication
		mtb_spi_message_segment_t segment;

	public:
		SPICMtb();
		SPICMtb(mtb_spi_t port, mtb_gpio_t csPin);
		SPICMtb(mtb_spi_t port, mtb_gpio_t csPin, uint8_t speed, uint8_t mode, uint8_t bits);
		~SPICMtb();
		Error_t     init();
		Error_t     deinit();
		Error_t     transfer(uint8_t send, uint8_t &received);
		Error_t     transfer16(uint16_t send, uint16_t &received);

};

/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** SPIC_MTB_HPP_ **/
