/*!
 * \name        writeRegisters
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Testscript for a writing register settings.
 * \details
 * This example show how to use the register write functions
 * of the sensor, to change certain bits with deafult low speed
 * 9600 baud comunication and standard sensor settings
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef WRITEREGISTERS_HPP_
#define WRITEREGISTERS_HPP_

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
#endif /* WRITEREGISTERS_HPP_ */
