/**
 * @file        timer-mtb.hpp
 * @brief       MTB Timer PAL
 * @date        Spt 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TIMER_MTB_HPP_
#define TIMER_MTB_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_MTB)

#include "../../../pal/timer.hpp"

namespace tle5012
{

/**
 * @addtogroup mtbPal
 * @{
 */

class TimerMtb: virtual public Timer
{
	public:
		TimerMtb();
		~TimerMtb();
		Error_t init();
		Error_t deinit();
		Error_t start();
		Error_t elapsed(mtb_time_t &elapsed);
		Error_t stop();
		Error_t delayMilli(uint32_t timeout);
		Error_t delayMicro(uint32_t timeout);

	private:
		mtb_time_t startTime;
};

/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** TIMER_MTB_HPP_ **/
