/**
 * @file        gpio.cpp
 * @brief       PAL of the GPIO
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "gpio.hpp"


GPIO::Error_t GPIO::checkErrorStatus()
{
	return errorStatus;
}