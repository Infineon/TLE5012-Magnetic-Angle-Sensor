/**
 * @file        gpio-mtb.hpp
 * @brief       MTB PAL for the GPIO
 * @date        Spt 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef GPIO_MTB_HPP_
#define GPIO_MTB_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_MTB)

#include "../../../pal/gpio.hpp"
#include <mtb_platform.h>

namespace tle5012
{

/**
 * @addtogroup mtbPal
 * @{
 */

class GPIOMtb : virtual public GPIO
{
	private:
		#define             UNUSED_PIN (mtb_gpio_t)(MTB_GPIO_51 + 1)     /**< Unused pin */
		mtb_gpio_t          pin;                                         /**< GPIO number */
		mtb_gpio_config_t   config;                                      /**< GPIO configuration */
		VLogic_t            logic;                                       /**< Pin logic */

	public:
					GPIOMtb();
					GPIOMtb(mtb_gpio_t pin, mtb_gpio_config_t config, VLogic_t logic);
					~GPIOMtb();
		Error_t     init();
		Error_t     deinit();
		VLevel_t    read();
		Error_t     write(VLevel_t level);
		Error_t     enable();
		Error_t     disable();
};


/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** GPIO_MTB_HPP_ **/
