/*!
 * \file        TLE5012-ino.hpp
 * \name        TLE5012-ino.hpp - Arduino library for the Infineon Tle5012 magnetic angular sensor
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \ref         tle5012ino
 * \version     3.0.0
 * \brief       This is a Arduino platform file use Infineon's TLE5012B magnetic angular sensor
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLE5012_INO_HPP_
#define TLE5012_INO_HPP_

#include "config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup inoApi
 * @{
 */

#include "corelib/TLE5012b.hpp"
#include "framework/arduino/wrapper/TLE5012-platf-ino.hpp"

/**
 * @class Tle5012Ino
 *
 * @brief represents the TLE5012 base class
 * This file is only a startup wrapper for Arduino IDE so that the framework
 * setup can be handeld without any special setup.
 * 
 */

/* @} */

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_INO_HPP_ **/
