/*!
 * \name        readAngleTest
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Testscript for a first check.
 * \details
 * This example reads all main Sensor registers (angle,revolution,speed,range and temperature)
 * for a simple first test of the sensor and comunication.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef READANGLETEST_HPP_
#define READANGLETEST_HPP_

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <stdlib.h>
#include <wiced.h>
#include <TLE5012-platf-wiced.hpp>
#include <TLE5012-pal-wiced.hpp>
#include <TLE5012b.hpp>
#include "wiced_rtos.h"

extern "C" void application_start();

#endif /** TLE5012_FRMWK_WICED **/
#endif /* READANGLETEST_HPP_ */
