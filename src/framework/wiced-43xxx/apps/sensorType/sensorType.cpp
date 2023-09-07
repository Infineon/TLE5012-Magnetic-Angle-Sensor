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

#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include "sensorType.hpp"

Tle5012Wiced Tle5012Sensor = Tle5012Wiced();
errorTypes checkError = NO_ERROR;


/**
 * @brief Function prints the binary code of each documented register
 *
 */
void show_bin()
{
	char nameOfRegister[MAX_NUM_REG][10] = {
	"STAT  ","ACSTAT","AVAL  ","ASPD  ","AREV  ",
	"FSYNC ","MOD1  ","SIL   ","MOD2  ","MOD3  ",
	"OFFX  ","OFFY  ","SYNCH ","IFAB  ","MOD4  ",
	"TCOY  ","ADCX  ","ADCY  ","DMAG  ","TRAW  ",
	"IIFCNT","T250  "
	};

	WPRINT_APP_INFO(("\t\t"));
	for (int8_t i = 15; i > -1; i--)
	{
		WPRINT_APP_INFO((" %X ",i));
	}
	WPRINT_APP_INFO(("\n\t\t------------------------------------------------\n"));
	for (int8_t i = 0; i < MAX_NUM_REG; i++)
	{
	 WPRINT_APP_INFO(("%i\t%s\t",i,nameOfRegister[i]));
	 PRINTBINS(Tle5012Sensor.reg.regMap[i]);
	 WPRINT_APP_INFO(("\n"));
	}
}


/**
 * @brief Sensor is set with PWM interface with the following settings
 *
 */
void pwmInterface()
{
	uint8_t val = 0;
	uint8_t firupdate = Tle5012Sensor.reg.getFIRUpdateRate();
	bool ifabout      = Tle5012Sensor.reg.isIFABOutputMode();

	WPRINT_APP_INFO(("Identified Sensor PCB: "));
	if (firupdate == 0x0 && ifabout )
	{
		WPRINT_APP_INFO(("%u  = TLE5012B_E5000\n",Tle5012Sensor.reg.TLE5012B_E5000 ));
	}else{
		WPRINT_APP_INFO(("%u  = TLE5012B_E5020\n",Tle5012Sensor.reg.TLE5012B_E5020 ));
	}
	WPRINT_APP_INFO(("\nPWM Interface settings\n"));

	val = Tle5012Sensor.reg.getIFABres();
	WPRINT_APP_INFO(("\nMOD4 Frequency:         \t%s",
		val == 0
			? "244 Hz"
			: (val == 1
				? "488 Hz"
				: (val == 2
					? "977 Hz"
					: "1953 Hz")) ));

	val = Tle5012Sensor.reg.getHysteresisMode();
	WPRINT_APP_INFO(("\nIFAB Unit time:         \t%s",
		val == 0
			? "3.0 μs"
			: (val == 1
				? "2.5 μs"
				: (val == 2
					? "2.0 μs"
					: "1.5 μs")) ));

	WPRINT_APP_INFO(("\nIFAB Filter update time:\t%s",
		Tle5012Sensor.reg.getFIRUpdateRate()
			? "85.3 μs"
			: "42.7 μs" ));

	WPRINT_APP_INFO(("\nIFAB IFA pin:           \t%s",
		ifabout
			? "Open Drain"
			: "Push-Pull" ));

}


/**
 * @brief Sensor is set with IIF interface with the following settings
 *
 */
void iifInterface()
{
	uint8_t val = 0;

	WPRINT_APP_INFO(("Identified Sensor PCB: %u = TLE5012B_E1000\n",Tle5012Sensor.reg.TLE5012B_E1000));
	WPRINT_APP_INFO(("\nIIF Interface settings\n"));

	val = Tle5012Sensor.reg.getIIFMod();
	WPRINT_APP_INFO(("\nMOD1 IIF Mode:          \t%s",
		val == 0
			? "disabled"
			: (val == 1
				? "A/B operation with Index on IFC pin"
				: (val == 2
					? "Step/Direction operation with Index on IFC pin"
					: "not allowed")) ));

	val = Tle5012Sensor.reg.getIFABres();
	WPRINT_APP_INFO(("\nMOD4 Resolution:        \t%s",
		val == 0
			? "0.088° step"
			: (val == 1
				? "0.176° step"
				: (val == 2
					? "0.352° step"
					: "0.703° step")) ));

	val = Tle5012Sensor.reg.getHysteresisMode();
	WPRINT_APP_INFO(("\nIFAB Hysteresis:        \t%s",
		val == 0
			? "HSM: 0°"
			: (val == 1
				? "HSM: 0.175°"
				: (val == 2
					? "HSM: 0.35°"
					: "HSM: 0.70°")) ));

	WPRINT_APP_INFO(("\nIFAB Filter update time:\t%s",
		Tle5012Sensor.reg.getFIRUpdateRate()
			? "85.3 μs"
			: "42.7 μs" ));

	WPRINT_APP_INFO(("\nIFAB IFA pin:           \t%s",
		Tle5012Sensor.reg.isIFABOutputMode()
			? "Open Drain"
			: "Push-Pull" ));

}


/**
 * @brief Sensor is set with IIF interface with the following settings
 *
 */
void hsmInterface()
{
	uint8_t val = 0;

	WPRINT_APP_INFO(("Identified Sensor PCB: %u = TLE5012B_E3005\n",Tle5012Sensor.reg.TLE5012B_E3005));
	WPRINT_APP_INFO(("\nHSM Interface settings\n"));
	
	val = Tle5012Sensor.reg.getIFABres();
	WPRINT_APP_INFO(("\nMOD4 Frame config:      \t%s",
		val == 0
			? "12bit angle"
			: (val == 1
				? "16bit angle"
				: (val == 2
					? "12bit angle + 8bit temperature"
					: "16bit angle + 8bit temperature")) ));

	val = Tle5012Sensor.reg.getHysteresisMode();
	WPRINT_APP_INFO(("\nIFAB Hysteresis:        \t%s",
		val == 0
			? "0°"
			: (val == 1
				? "0.175°"
				: (val == 2
					? "0.35°"
					: "0.70°")) ));

	WPRINT_APP_INFO(("\nIFAB Filter update time:\t%s",
		Tle5012Sensor.reg.getFIRUpdateRate()
			? "85.3 μs"
			: "42.7 μs" ));

	WPRINT_APP_INFO(("\nIFAB IFA pin:           \t%s",
		Tle5012Sensor.reg.isIFABOutputMode()
			? "Open Drain"
			: "Push-Pull" ));

}


/**
 * @brief Sensor is set with SPC interface with the following settings
 *
 */
void spcInterface()
{
	uint8_t val = 0;

	WPRINT_APP_INFO(("Identified Sensor PCB: %u = TLE5012B_E9000\n",Tle5012Sensor.reg.TLE5012B_E9000));
	WPRINT_APP_INFO(("\nSPC Interface settings\n"));

	val = Tle5012Sensor.reg.getIFABres();
	WPRINT_APP_INFO(("\nMOD4 Frame config:      \t%s",
		val == 0
			? "12bit angle"
			: (val == 1
				? "16bit angle"
				: (val == 2
					? "12bit angle + 8bit temperature"
					: "16bit angle + 8bit temperature")) ));

	val = Tle5012Sensor.reg.getHysteresisMode();
	WPRINT_APP_INFO(("\nSPC Unit time:          \t%s",
		val == 0
			? "3.0 μs"
			: (val == 1
				? "2.5 μs"
				: (val == 2
					? "2.0 μs"
					: "1.5 μs")) ));

	val = Tle5012Sensor.reg.getHSMplp();
	WPRINT_APP_INFO(("\nSPC Trigger time:       \t%s",
		val == 0
			? "90 μs"
			: "t_mlow + 12 UT" ));

	WPRINT_APP_INFO(("\nIFAB IFA pin:           \t%s",
		Tle5012Sensor.reg.isIFABOutputMode()
			? "Open Drain"
			: "Push-Pull" ));

}


/**
 * @brief This function prints the identity of the sensor which
 * is set as factory default inside the sensor fuses.
 *
 */
void show_identity()
{
	uint8_t interface = Tle5012Sensor.reg.getInterfaceMode();
	uint8_t slavenum  = Tle5012Sensor.reg.getSlaveNumber();

	WPRINT_APP_INFO(("----------------------------------------------------------------\n"));
	WPRINT_APP_INFO(("Identified Slave:      %x = TLE5012_S%u\nIdentified Interface:  %u",slavenum,slavenum,interface));

	switch (interface)
	{
	case Tle5012Sensor.reg.IIF:
		WPRINT_APP_INFO((" = IIF\n"));
		iifInterface();
		hsmInterface();
		spcInterface();
		break;
	case Tle5012Sensor.reg.PWM:
		WPRINT_APP_INFO((" = PWM\n"));
		pwmInterface();
		break;
	case Tle5012Sensor.reg.HSM:
		WPRINT_APP_INFO((" = HSM\n"));
		hsmInterface();
		break;
	case Tle5012Sensor.reg.SPC:
		WPRINT_APP_INFO((" = SPC\n"));
		spcInterface();
		break;
	}
}


/**
 * @brief Shows additional information for each sensor type
 * from the additional registers MOD2 and MOD3
 *
 */
void show_additional()
{
	uint8_t val = 0;
	val = Tle5012Sensor.reg.getCalibrationMode();
	WPRINT_APP_INFO(("\n\nMOD2 Autocalibration:   \t%s",
		val == 0
			? "auto-cal. mode 1: update every angle update cycle"
			: (val == 1
				? "auto-cal. mode 1: update every angle update cycle"
				: (val == 2
					? "auto-cal. mode 2: update every 1.5 revolutions"
					: "auto-cal. mode 3: update every 11.25°")) ));

	WPRINT_APP_INFO(("\nMOD2 Prediction:        \t%s",
		Tle5012Sensor.reg.isPrediction()
			? "enabled"
			: "disabled" ));

	val = Tle5012Sensor.reg.getPadDriver();
	WPRINT_APP_INFO(("\nMOD3 IFA/B/C pin set:   \t%s",
		val == 0
			? "strong driver, DATA: strong driver, fast edge"
			: (val == 1
				? "strong driver, DATA: strong driver, slow edge"
				: (val == 2
					? "weak driver, DATA: medium driver, fast edge"
					: "weak driver, DATA: weak driver, slow edge")) ));

	WPRINT_APP_INFO(("\nMOD3 SSC interface:     \t%s",
		Tle5012Sensor.reg.isSSCOutputMode()
			? "Push-Pull"
			: "Open Drain" ));

	WPRINT_APP_INFO(("\nMOD3 Voltage filter:    \t%s",
		Tle5012Sensor.reg.isSpikeFilter()
			? "spike filter enabled"
			: "spike filter disabled" ));

}


void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	wiced_rtos_delay_milliseconds( 1000 );

	/**
	 * @brief You can use resetFirmware to set all register settings
	 * back to factory defaults
	 */
	//checkError = Tle5012Sensor.resetFirmware();

	/**
	 * @brief You can set the sensor slave number to one of
	 * four possible settings
	 */
	Tle5012Sensor.writeSlaveNumber(Tle5012Sensor.TLE5012B_S0);

	/*
	 * Checkout one of these interface modes. Each Sensor2go board
	 * comes with a predefined interface, but this can be changed
	 * during the runtime. A restart or with the resetFirmware function
	 * the changes will be set to the factory defaults.
	 */
	//checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.IIF);
	//checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.PWM);
	//checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.HSM);
	//checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.SPC);

	/*
	 * Checkout the different auto calibration modes by removing the
	 * remarks. As each predefined interface has its default auto calibration
	 * mode, a restart or resetFirmware will set everything back to
	 * factory defaults.
	 */
	//checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.noAutoCal);
	//checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode1);
	//checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode2);
	//checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode3);

	// read all registers
	checkError = Tle5012Sensor.readRegMap();
	// printout register binary values and sensor identity
	show_bin();
	show_identity();
	show_additional();
}


void loop() {
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
