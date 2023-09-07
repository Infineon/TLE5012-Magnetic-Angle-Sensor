/*!
 * \name        testSensorMainValues
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       This example can be used for a first fast test if the sensors works
 * \details
 * It will generate a looped output of the direct measured data (DIR) and
 * data from the update (UPD) registers. Therefore it demonstrats also the use of
 * the direct read (without UPD) and the snapshoot registers (with UPD). See Sensor
 * manual for more information of the UPD mode and the snapshoot registers.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <testSensorMainValues.hpp>

// Tle5012b Object
Tle5012Wiced Tle5012Sensor = Tle5012Wiced();
errorTypes checkError = NO_ERROR;
updTypes upd = UPD_high;

void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	Tle5012Sensor.resetFirmware();
	Tle5012Sensor.sBus->triggerUpdate();
	wiced_rtos_delay_milliseconds( 1000 );
}

void loop() {
	double a = 0.0; double au = 0.0; double rr = 0.0;
	int16_t ra = 0; int16_t rau = 0;
	int16_t r = 0;  int16_t ru = 0;
	double t = 0.0; double tu = 0.0;
	int16_t rt = 0; int16_t rtu = 0;
	double s = 0.0; double su = 0.0;
	int16_t rs = 0; int16_t rsu = 0;

	Tle5012Sensor.getAngleRange(rr);
	Tle5012Sensor.getAngleValue(a,ra);
	Tle5012Sensor.getNumRevolutions(r);
	Tle5012Sensor.getTemperature(t,rt);
	Tle5012Sensor.getAngleSpeed(s,rs);

	// to read UPD registers, call triggerUpdate once and
	// than read all UPD registers you need before calling
	// triggerUpdate again
	Tle5012Sensor.sBus->triggerUpdate();
	Tle5012Sensor.getAngleValue(au,rau,upd);
	Tle5012Sensor.getTemperature(tu,rtu,upd);
	Tle5012Sensor.getAngleSpeed(su,rsu,upd);
	Tle5012Sensor.getNumRevolutions(ru);

	WPRINT_APP_INFO(("range:         %f°\nrevolution:    %u\trevolutionUPD: %u\n",rr,r,ru));
	WPRINT_APP_INFO(("DIR\tangle:    %f°   %X",a,ra));
	WPRINT_APP_INFO(("   \ttemp:     %f°C  %X",t,rt));
	WPRINT_APP_INFO(("   \tspeed:    %f°/s %X\n",s,rs));

	WPRINT_APP_INFO(("UPD\tangUPD:   %f°   %X",au,rau));
	WPRINT_APP_INFO(("   \ttempUPD:  %f°C  %X",tu,rtu));
	WPRINT_APP_INFO(("   \tspeedUPD: %f°/s %X\n\n",su,rsu));

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
