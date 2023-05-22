/*!
 * \name        sensorType
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       prints register bit matrix and sensor interface type
 * \details
 * This example program prints the bit matrix of all registers and the sensors default
 * interface type and its settings.
 * From special registers MOD1,2,3,4 and IFAB the explicit sensor
 * interface set and the PCB board will be identified. See the Sensor manual for further
 * information on the different interfaces and the different sensor boards.
 *
 * \attention
 * Additional by removing the remarks on certain write functions, some sensor setups can
 * be set/unset or switched on/off.
 *
 */

#ifndef SENSORTYPE_HPP_
#define SENSORTYPE_HPP_

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
#endif /* SENSORTYPE_HPP_ */
