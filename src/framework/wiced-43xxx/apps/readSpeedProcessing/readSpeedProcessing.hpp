/*!
 * \name        readSpeedProcessing
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       This example can be used for a first fast test if the sensors works
 * \details
 * Demonstrates the fast readout of the angle speed.
 * Depending on the microcontroller you use more or less
 * speed on the serial port is possible.
 *
 * \attention Use this sketch together with the processing script examples
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef READSPEEDPROCESSING_HPP_
#define READSPEEDPROCESSING_HPP_

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
#endif /* READSPEEDPROCESSING_HPP_ */
