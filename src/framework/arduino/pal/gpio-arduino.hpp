/**
 * @file        gpio-arduino.hpp
 * @brief       Arduino PAL for the GPIO
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef GPIO_ARDUINO_HPP_
#define GPIO_ARDUINO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include "../../../corelib/TLE5012b.hpp"

/**
 * @addtogroup arduinoPal
 * @{
 */


/**
 * @brief Arduino GPIO class
 *
 */
class GPIOIno: virtual public GPIO
{
private:
	#define     UNUSED_PIN    0xFF  /**< Unused pin */
	uint8_t     pin;
	uint8_t     mode;
	VLogic_t    logic;

public:
				GPIOIno();
				GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic);
				~GPIOIno();
	Error_t     init();
	Error_t     deinit();
	VLevel_t    read();
	Error_t     write(VLevel_t level);
	Error_t     enable();
	Error_t     disable();
};
/** @} */

#endif /** TLE5012_FRAMEWORK **/
#endif /** GPIO_ARDUINO_HPP_ **/
