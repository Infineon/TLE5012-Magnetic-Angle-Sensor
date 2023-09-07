/*!
 * \name        readAngleTest
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Testscript for a first check.
 * \details
 * This example reads all main Sensor registers (angle,revolution,speed,range and temperature)
 * for a simple first test of the sensor and comunication.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <readAngleTest.hpp>

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
	double r = 0.0;
	double s = 0.0;
	double t = 0;
	int16_t b = 0;

	Tle5012Sensor.getAngleValue(d);
	Tle5012Sensor.getNumRevolutions(b);
	Tle5012Sensor.getAngleSpeed(s);
	Tle5012Sensor.getAngleRange(r);
	Tle5012Sensor.getTemperature(t);

	WPRINT_APP_INFO(("Temperature: %f°C\tangle: %f°\trange: %f\tspeed: %f\trevolution:%u\n",t,d,r,s,b));

	wiced_rtos_delay_milliseconds( 1000 );
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
