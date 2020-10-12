/**
 * @file        timer-arduino.cpp
 * @brief       Arduino Timer Platform Abstraction Layer
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include <Arduino.h>
#include "timer-arduino.hpp"

/**
 * @brief Constructor of the Arduino Timer class
 *
 */
TimerIno::TimerIno()
{
}

/**
 * @brief Destructor of the Arduino Timer class
 *
 */
TimerIno::~TimerIno()
{
}

/**
 * @brief Initialization of the Timer
 *
 * This function is initializing the Timer and sets
 * the elapsed time to zero.
 *
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::init()
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
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::deinit()
{
	startTime = 0;
	return OK;
}

/**
 * @brief Start the timer
 *
 * This function is starting the timer.
 *
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::start()
{
	startTime = millis();
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
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::elapsed(uint32_t &elapsed)
{
	elapsed = millis() - startTime;
	return OK;
}

/**
 * @brief Stop the timer
 *
 * This function stops the timer and resets the
 * start time variable.
 *
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::stop()
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
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::delayMilli(uint32_t timeout)
{
	delay(timeout);
	return OK;
}

/**
 * @brief Time delay
 *
 * This function is causing a desired delay of the application.
 * The input value is given in microseconds.
 *
 * @param[in]   timeout                 Desired timeout in us
 * @return      TimerIno::Error_t
 */
TimerIno::Error_t TimerIno::delayMicro(uint32_t timeout)
{
	delayMicroseconds(timeout);
	return OK;
}

#endif /** TLE5012_FRAMEWORK **/
