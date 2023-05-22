/*!
 * \name        E9000SPC
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       This example shows how to handle the TLE5012B-E9000 variant with SPC interface
 * \details
 * The TLE5012B-E9000 with SPC interface does not start the DSP automatically in a loop at start up.
 * It will need a certain trigger on the IFA pin of the sensor.
 * This trigger must be in a 90 UT time frame at least 12 UT long for the first sensor. By
 * multiplying the 12 UT with the sensor slave number up to four sensors can be triggered.
 * This trigger setting UT the unittime must multiplied with the sensors base unittime which
 * is default 3.0µs. Setting the IFA pin to low and waiting atleast the total trigger time
 * will set all registers by the DSP.
 * For more information please read the SPC Interface section of the manual.
 * The default setup ist:
 * - unittime =3.0µs,
 * - total trigger time = 90 * 3.0µs = 270 µs
 * - t_mlow the time for the first sensor to trigger = 12 * 3.0µs = 36 µs
 * so we have to set the IFA pin 36µs to low, than back to high and wait (90-12)*3.0µs = 224µs
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef E9000SPC_HPP_
#define E9000SPC_HPP_

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <stdlib.h>
#include <wiced.h>
#include <TLE5012-platf-wiced.hpp>
#include <TLE5012-pal-wiced.hpp>
#include <TLE5012b.hpp>
#include "wiced_rtos.h"
#include "wiced_time.h"

extern "C" void application_start();

#endif /** TLE5012_FRMWK_WICED **/
#endif /* E9000SPC_HPP_ */
