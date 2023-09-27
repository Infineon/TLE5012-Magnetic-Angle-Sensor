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


#include "../../../../config/tle5012-conf.hpp"
#include "readAngleValueProcessing.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

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
	Tle5012Sensor.getAngleValue(d);
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


#endif /** TLE5012_FRAMEWORK **/
