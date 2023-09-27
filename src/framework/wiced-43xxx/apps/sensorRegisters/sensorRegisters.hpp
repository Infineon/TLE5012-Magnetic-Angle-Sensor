/*!
 * \name        sensorRegisters
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Reads all sensor registers and reports there status
 * \details
 * This example program will read all documented registers from the sensor and
 * writes this to the serial port with remark info for each register.
 * Please have look to the sensor manual for more and more detailed information
 * about each register.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef SENSORREGISTERS_HPP_
#define SENSORREGISTERS_HPP_

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
#endif /* SENSORREGISTERS_HPP_ */
