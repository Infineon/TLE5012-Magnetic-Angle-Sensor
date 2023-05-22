/*!
 * \name        useMultipleSensors
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Testscript for using up to four sensors on one SPI channel.
 * \details
 * This example program starts one to four sensors on one SPI line with different CS pins
 * and returns the angle value together with the safety word and the status register SNR.
 * Due to the selected slave number the SNR will be set to 0x00, 0x01, 0x10 or 0x11. When
 * you fetch a value from the sensor with safety word on, than the safety word register RESP
 * will indicate the sensor who is responding. This should be the same than you have
 * ask for. The loop function will than print out the individual sensor(s) angle values.
 *
 * This example also demonstrates how to handle more than on sensor in an array setup.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef USEMULTIPLESENSORS_HPP_
#define USEMULTIPLESENSORS_HPP_

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
#endif /* USEMULTIPLESENSORS_HPP_ */
