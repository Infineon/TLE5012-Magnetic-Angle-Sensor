/** 
 * @file        spic.cpp
 * @brief       PAL of the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "spic.hpp"


SPIC::Error_t SPIC::checkErrorStatus()
{
	return errorStatus;
}