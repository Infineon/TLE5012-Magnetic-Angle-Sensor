/**
 * @file        gpio-arduino.hpp
 * @brief       Arduino PAL for the GPIO
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef PAL_GPIO_ARDUINO_HPP_
#define PAL_GPIO_ARDUINO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

//#include "../../../corelib/TLE5012b.hpp"
#include "../../../pal/pal-gpio.hpp"


namespace tle5012
{
	/**
	 * @addtogroup arduinoPal
	 * @{
	 */


	/**
	 * @class  GPIOIno
	 * @brief  GPIO platform abstraction layer Arduino API
	 */
	class GPIOIno: virtual public GPIOPAL
	{
	private:
		uint8_t     pin;
		uint8_t     mode;
		VLogic_t    logic;

	public:
		static constexpr uint8_t  UNUSED_PIN = 0xFFU;    /**< Unused pin */

					GPIOIno();
					GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic);
					~GPIOIno();
		Error_t     init();
		Error_t     changeMode(uint8_t mode);
		Error_t     deinit();
		VLevel_t    read();
		Error_t     write(VLevel_t level);
		Error_t     enable();
		Error_t     disable();
	};

	/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** PAL_GPIO_ARDUINO_HPP_ **/
