/*!
 * \name        readMultipleRegisters
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Demostrates how to read multiple registers
 * \details
 * This example demonstrates how to read multiple raw registers at once.
 * In this case you have to recalculate values like angle, angle speed etc.
 * be your self.
 *
 * \details
 * the read command offset of 0x8000 will be set by the readMoreRegisters command
 * so we need only the register offset from where we start and
 * the second digit is how many consecutive registers to read which is
 * be done by adding the length and the command values.
 * A max of 15 value can read at once, one additional value is reserved for
 * the safety bit.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef READMULTIPLEREGISTERS_HPP_
#define READMULTIPLEREGISTERS_HPP_

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
#endif /* READMULTIPLEREGISTERS_HPP_ */
