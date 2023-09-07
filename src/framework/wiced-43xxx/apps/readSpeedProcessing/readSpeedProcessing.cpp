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

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <readSpeedProcessing.hpp>

Tle5012Wiced Tle5012Sensor = Tle5012Wiced();
errorTypes checkError = NO_ERROR;

void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	wiced_rtos_delay_milliseconds( 1000 );
}

void loop() {
	double d = 0.0;
	Tle5012Sensor.getAngleSpeed(d);
	WPRINT_APP_INFO(("%f\n", d));

	wiced_rtos_delay_milliseconds( 10 );
}

/******************************************************
 *               Function Definitions
 ******************************************************/

void application_start( )
{
	wiced_result_t      result;

	/* Initialize the device */
	result = wiced_init();
	if (result != WICED_SUCCESS)
	{
		return;
	}

	setup();

	while(1)
	{
		loop();
	}
}

#endif
