/**
 * @file        timer-wiced.cpp
 * @brief       WICED Timer Platform Abstraction Layer
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "timer-wiced.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

using namespace tle5012;

/**
 * @brief Constructor of the WICED Timer class
 *
 */
TimerWiced::TimerWiced()
{
}

/**
 * @brief Destructor of the WICED Timer class
 *
 */
TimerWiced::~TimerWiced()
{
}

/**
 * @brief Initialization of the Timer
 *
 * This function is initializing the Timer and sets
 * the elapsed time to zero.
 *
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::init()
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
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::deinit()
{
	startTime = 0;
	return OK;
}

/**
 * @brief Start the timer
 *
 * This function is starting the timer.
 *
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::start()
{
	wiced_time_get_time( &startTime );
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
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::elapsed(wiced_time_t &elapsed)
{
	wiced_time_t endTime;
	wiced_time_get_time( &endTime );
	elapsed = endTime - startTime;
	return OK;
}

/**
 * @brief Stop the timer
 *
 * This function stops the timer and resets the
 * start time variable.
 *
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::stop()
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
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::delayMilli(uint32_t timeout)
{
	wiced_rtos_delay_milliseconds( timeout );
	return OK;
}

/**
 * @brief Time delay
 *
 * This function is causing a desired delay of the application.
 * The input value is given in microseconds.
 *
 * @param[in]   timeout                 Desired timeout in us
 * @return      TimerWiced::Error_t
 */
TimerWiced::Error_t TimerWiced::delayMicro(uint32_t timeout)
{
	wiced_rtos_delay_microseconds( timeout );
	return OK;
}

#endif /** TLE5012_FRAMEWORK **/
