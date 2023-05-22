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

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <useMultipleSensors.hpp>

//! number of connected sensors
#define SENSOR_NUM 1

//! define more unique chipselect pins for more connected Sensors
#define CS_PIN_SENSOR_1   10  //!< This is a setup for the default Arduino, use 3 for the Sensor2Go kit
#define CS_PIN_SENSOR_2   5   //!< This is also a setup for the Sensor2Go kit but with a second sensor attached
//#define CS_PIN_SENSOR_3   x
//#define CS_PIN_SENSOR_4   x

//! Tle5012b Object, set/remove depending on the number of connected sensors
Tle5012Wiced sensor[SENSOR_NUM] = {
	(Tle5012Wiced(WICED_GPIO_7,sensor[1].TLE5012B_S0)),
//  (Tle5012Wiced(CS_PIN_SENSOR_2,sensor[1].TLE5012B_S1)),
//  (Tle5012Wiced(CS_PIN_SENSOR_3,sensor[1].TLE5012B_S2)),
//  (Tle5012Wiced(CS_PIN_SENSOR_4,sensor[1].TLE5012B_S3)),
};

//! Sensor IFX SIL(TM) errorCheck
errorTypes checkError = NO_ERROR;

//! array if the read angle values and revolutions
double d[4] = {0.0, 0.0, 0.0, 0.0};
int16_t r[4] = {0, 0, 0, 0};

void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );

	// Remove remark if you have more than one sensor,
	// or change the Tle5012Sensor.TLE5012B_S0 to S1-S3 to demonstrate the effect
	for (int8_t i=0;i<SENSOR_NUM;i++)
	{
		checkError = sensor[i].begin();
		WPRINT_APP_INFO(("[TLE5012B] : Sensor -> %u Check Error -> %u\n", i, checkError));
	}
	wiced_rtos_delay_milliseconds( 1000 );

	uint16_t stat;
	double a = 0.0;
	for (int8_t i=0;i<SENSOR_NUM;i++)
	{
		sensor[i].readStatus(stat);
		sensor[i].reg.getSlaveNumber();
		sensor[i].getAngleValue(a);
		sensor[i].safetyStatus.fetch_Safety(sensor[i].safetyWord);
		uint8_t snr = sensor[i].reg.getSlaveNumber();
		WPRINT_APP_INFO(("%u\tangle: %f\tSTAT SNR: %u\tRESP: ",i,a,snr));
		switch (sensor[i].safetyStatus.responseSlave()) {
			case sensor[i].TLE5012B_S3:
				WPRINT_APP_INFO(("0x0111 = TLE5012B_S3\n"));
				break;
			case sensor[i].TLE5012B_S2:
				WPRINT_APP_INFO(("0x1011 = TLE5012B_S2\n"));
				break;
			case sensor[i].TLE5012B_S1:
				WPRINT_APP_INFO(("0x1101 = TLE5012B_S1\n"));
				break;
			default:
				WPRINT_APP_INFO(("0x1110 = TLE5012B_S0\n"));
				break;
		}
	}
	WPRINT_APP_INFO(("\n"));
	wiced_rtos_delay_milliseconds( 1000 );
}

void loop() {
	for (int8_t i=0;i<SENSOR_NUM;i++){
		d[i] = 0.0;
		r[i] = 0;
		sensor[i].getAngleValue(d[i]);
		sensor[i].getNumRevolutions(r[i]);
		WPRINT_APP_INFO(("\t%f,%u",d[i],r[i]));
	}
	WPRINT_APP_INFO(("\n"));
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
