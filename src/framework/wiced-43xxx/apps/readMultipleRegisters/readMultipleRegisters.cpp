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

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)


#include <readMultipleRegisters.hpp>

Tle5012Wiced Tle5012Sensor = Tle5012Wiced();
errorTypes checkError = NO_ERROR;

uint16_t command = 0x0050; //!< read register beginning with REG_FSYNC
uint8_t leng = 5;          //!< and the next four registers REG_MOD_1, REG_SIL, REG_MOD2 and REG_MOD3
bool s = true;

void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	wiced_rtos_delay_milliseconds( 1000 );
}

void loop()
{
	if (s && (checkError == 0))
	{
		uint16_t data[leng];
		command = command + leng;
		checkError = Tle5012Sensor.readMoreRegisters(command, data, UPD_low, SAFE_low);
		if (checkError == 0)
		{
			for (int i = 0; i<leng; i++)
			{
				WPRINT_APP_INFO(("%X\t\t", data[i] ));
				PRINTBIN(data[i]);
				WPRINT_APP_INFO(("\n" ));
			}
			s = false;
		}
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
