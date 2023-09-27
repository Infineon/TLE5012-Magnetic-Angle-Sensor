/*!
 * \name        readAngleValueProcessing
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       reads angle values
 * \details
 * This is a fast running example to demonstrate the possible readout
 * speed of the sensor for the angle. Depending on your microcontroller
 * more or less speed on the serial port is possible.
 * For reconfiguring of the SPI interface, have a look at the documentation.
 *
 * \attention Use together with the several processing scripts
 * \attention We use standard WiCED output speed of 115200 baud. If you need
 * more, than switch the output setting to 1000000 baud and a
 * 10ms delay in the loop. You can set smaller values down to 1ms,
 * but that will somehow overload the console log output.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef READANGLEVALUEPROCESSING_HPP_
#define READANGLEVALUEPROCESSING_HPP_

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
#endif /* READANGLEVALUEPROCESSING_HPP_ */
