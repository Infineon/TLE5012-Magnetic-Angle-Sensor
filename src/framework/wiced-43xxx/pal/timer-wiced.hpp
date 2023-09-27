/**
 * @file        timer-wiced.hpp
 * @brief       WICED Timer PAL
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TIMER_WICED_HPP_
#define TIMER_WICED_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include "../../../pal/timer.hpp"
#include "wiced_time.h"
#include "wiced_rtos.h"

namespace tle5012
{

/**
 * @addtogroup wicedPal
 * @{
 */

class TimerWiced: virtual public Timer
{
	public:
		TimerWiced();
		~TimerWiced();
		Error_t init();
		Error_t deinit();
		Error_t start();
		Error_t elapsed(wiced_time_t &elapsed);
		Error_t stop();
		Error_t delayMilli(uint32_t timeout);
		Error_t delayMicro(uint32_t timeout);

	private:
		wiced_time_t startTime;
};

/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** TIMER_WICED_HPP_ **/
