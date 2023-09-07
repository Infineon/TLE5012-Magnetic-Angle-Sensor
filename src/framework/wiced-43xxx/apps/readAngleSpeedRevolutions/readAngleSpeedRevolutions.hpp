/*!
 * \name        readAngleSpeedRevolutions
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       reads angle value, rotation speed and number of revolutions
 * \details
 * This is a fast running example to demonstrate the possible readout
 * speed of the sensor for the angle, angle speed and number of revolutions
 * at once.
 * For reconfiguring of the SPI interface, have a look at the documentation.
 *
 * \attention Use together with the speed.pde processing script
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef READANGLESPEEDREVOLUTIONS_HPP_
#define READANGLESPEEDREVOLUTIONS_HPP_

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
#endif /* READANGLESPEEDREVOLUTIONS_HPP_ */
