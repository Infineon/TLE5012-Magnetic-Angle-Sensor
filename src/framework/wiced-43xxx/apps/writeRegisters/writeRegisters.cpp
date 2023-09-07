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

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <writeRegisters.hpp>

Tle5012Wiced Tle5012Sensor = Tle5012Wiced();
errorTypes checkError = NO_ERROR;
bool s = true;

void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	wiced_rtos_delay_milliseconds( 1000 );
}

void loop() {
	if (s && (checkError == 0))
	{
		uint16_t a = 0;

		checkError = Tle5012Sensor.readIntMode2(a);
		WPRINT_APP_INFO(("read intmode2:\t0x%X\tcheckError: %X\n",a,checkError));
		checkError  = Tle5012Sensor.writeIntMode2(0x804);
		WPRINT_APP_INFO(("write intmode2:\t0x804\tcheckError: %X\n",checkError));
		checkError = Tle5012Sensor.readIntMode2(a);
		WPRINT_APP_INFO(("read intmode2:\t0x%X\tcheckError: %X\n\n",a,checkError));
		//
		checkError = Tle5012Sensor.readIntMode3(a);
		WPRINT_APP_INFO(("read intmode3:\t0x%X\tcheckError: %X\n",a,checkError));
		checkError  = Tle5012Sensor.writeIntMode3(0x8000);
		WPRINT_APP_INFO(("write intmode3:\t0x8000\tcheckError: %X\n",checkError));
		checkError = Tle5012Sensor.readIntMode3(a);
		WPRINT_APP_INFO(("read intmode3:\t0x%X\tcheckError: %X\n\n",a,checkError));
		//
		checkError = Tle5012Sensor.readOffsetX(a);
		WPRINT_APP_INFO(("read OffsetX:\t0x%X\tcheckError: %X\n",a,checkError));
		checkError  = Tle5012Sensor.writeOffsetX(0xD960);
		WPRINT_APP_INFO(("write OffsetX;\t0xD960\tcheckError: %X\n",checkError));
		checkError = Tle5012Sensor.readOffsetX(a);
		WPRINT_APP_INFO(("read OffsetX:\t0x%X\tcheckError: %X\n\n",a,checkError));

		s = false;
	}
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
