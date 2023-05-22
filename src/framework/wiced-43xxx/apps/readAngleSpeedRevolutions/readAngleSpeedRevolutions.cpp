/*!
 * \name        readAngleSpeedRevolutions
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       reads angle value, rotation speed and number of revolutions
 * \details
 * This is a fast running example to demonstrate the possible readout
 * speed of the sensor for the angle, angle speed and number of revolutions
 * at once.
 * For reconfiguring of the SPI interface, have a look at the documentation.
 *
 * \attention Use together with the speed.pde processing script
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <readAngleSpeedRevolutions.hpp>

// Tle5012b Object
Tle5012Wiced Tle5012Sensor = Tle5012Wiced();
errorTypes checkError = NO_ERROR;

void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	wiced_rtos_delay_milliseconds( 1000 );

	WPRINT_APP_INFO(("AngleSpeed\tAngleValue\trevolutions\tAngleRange\n"));
}

void loop() {
	double d = 0.0;
	int16_t b = 0;
	checkError = Tle5012Sensor.getAngleSpeed(d);
	if (checkError == 0)
	{
		WPRINT_APP_INFO(("%f\t", d));

		checkError = Tle5012Sensor.getAngleValue(d);
		WPRINT_APP_INFO(("%f\t\t", d));

		checkError = Tle5012Sensor.getNumRevolutions(b);
		WPRINT_APP_INFO(("%i\t\t", b));

		checkError = Tle5012Sensor.getAngleRange(d);
		WPRINT_APP_INFO(("%f\n", d));
	}
	wiced_rtos_delay_milliseconds( 100 );
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
