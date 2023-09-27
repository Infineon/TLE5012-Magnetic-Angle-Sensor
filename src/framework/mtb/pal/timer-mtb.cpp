/**
 * @file        timer-mtb.cpp
 * @brief       MTB Timer Platform Abstraction Layer
 * @date        Spt 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "timer-mtb.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_MTB)

using namespace tle5012;

/**
 * @brief Constructor of the MTB Timer class
 *
 */
TimerMtb::TimerMtb()
{
}

/**
 * @brief Destructor of the MTB Timer class
 *
 */
TimerMtb::~TimerMtb()
{
}

/**
 * @brief Initialization of the Timer
 *
 * This function is initializing the Timer and sets
 * the elapsed time to zero.
 *
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::init()
{
	startTime = 0;
	return OK;
}

/**
 * @brief Deinitialize the Timer
 *
 * This function deinitialize the Timer and also
 * resets the elapsed time variable.
 *
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::deinit()
{
	startTime = 0;
	return OK;
}

/**
 * @brief Start the timer
 *
 * This function is starting the timer.
 *
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::start()
{
	mtb_time_get_time( &startTime );
	return OK;
}

/**
 * @brief Calculate the elapsed time
 *
 * This function is calculating the elapsed time since the
 * start of the timer. The value stored in the given variable
 * is in milliseconds.
 *
 * @param[in]   &elapsed                Address of a value where the elapsed time should be stored
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::elapsed(mtb_time_t &elapsed)
{
	mtb_time_t endTime;
	mtb_time_get_time( &endTime );
	elapsed = endTime - startTime;
	return OK;
}

/**
 * @brief Stop the timer
 *
 * This function stops the timer and resets the
 * start time variable.
 *
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::stop()
{
	startTime = 0;
	return OK;
}

/**
 * @brief Time delay
 *
 * This function is causing a desired delay of the application.
 * The input value is given in milliseconds.
 *
 * @param[in]   timeout                 Desired timeout in ms
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::delayMilli(uint32_t timeout)
{
	mtb_rtos_delay_milliseconds( timeout );
	return OK;
}

/**
 * @brief Time delay
 *
 * This function is causing a desired delay of the application.
 * The input value is given in microseconds.
 *
 * @param[in]   timeout                 Desired timeout in us
 * @return      TimerMtb::Error_t
 */
TimerMtb::Error_t TimerMtb::delayMicro(uint32_t timeout)
{
	mtb_rtos_delay_microseconds( timeout );
	return OK;
}

#endif /** TLE5012_FRAMEWORK **/
