/*!
 * \name        testSensorMainValues
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       This example can be used for a first fast test if the sensors works
 * \details
 * It will generate a looped output of the direct measured data (DIR) and
 * data from the update (UPD) registers. Therefore it demonstrats also the use of
 * the direct read (without UPD) and the snapshoot registers (with UPD). See Sensor
 * manual for more information of the UPD mode and the snapshoot registers.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TESTSENSORMAINVALUES_HPP_
#define TESTSENSORMAINVALUES_HPP_

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
#endif /* TESTSENSORMAINVALUES_HPP_ */
