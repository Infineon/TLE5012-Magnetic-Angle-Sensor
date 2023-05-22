/*!
 * \name        sensorRegisters
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Reads all sensor registers and reports there status
 * \details
 * This example program will read all documented registers from the sensor and
 * writes this to the serial port with remark info for each register.
 * Please have look to the sensor manual for more and more detailed information
 * about each register.
 *
 * SPDX-License-Identifier: MIT
 *
 */


#include "../../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

#include <sensorRegisters.hpp>

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


void show_STAT()
{
	bool valb;
	uint8_t vali;

	WPRINT_APP_INFO(("\nRegister:\tSTAT\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_STAT));

	valb = Tle5012Sensor.reg.isStatusRead();
	WPRINT_APP_INFO(("RDST      0x%X\t%u\t1,  boolean\tr\t15:15\t%s\n",valb,valb,valb
			? "status values changed"
			: "status values not changed since last readout"));

	vali = Tle5012Sensor.reg.getSlaveNumber();
	WPRINT_APP_INFO(("SNR       0x%X\t%u\t2,  uint8_t\trw\t13:14 \tSlave Number of this sensor out of up to four sensors\n",vali,vali));

	valb = Tle5012Sensor.reg.isStatusGMRA();
	WPRINT_APP_INFO(("NOGMRA    0x%X\t%u\t1,  boolean\tru\t12   \t%s\n",valb,valb,valb
		? "no valid GMR angle value on the interface"
		: "valid GMR angle value on the interface"));

	valb = Tle5012Sensor.reg.isStatusGMRXY();
	WPRINT_APP_INFO(("NOGMRXY   0x%X\t%u\t1,  boolean\tru\t11   \t%s\n",valb,valb,valb
		? "no valid GMR_XY values on the ADC input"
		: "valid GMR_XY values on the ADC input and thus on filter output"));

	valb = Tle5012Sensor.reg.isStatusROM();
	WPRINT_APP_INFO(("SROM      0x%X\t%u\t1,  boolean\tr\t10    \t%s\n",valb,valb,valb
		? "CRC fail or still running"
		: "CRC Ok"));

	valb = Tle5012Sensor.reg.isStatusADC();
	WPRINT_APP_INFO(("SADCT     0x%X\t%u\t1,  boolean\tr\t9     \t%s\n",valb,valb,valb
		? "Test vectors out of limit"
		: "Test vectors Ok"));

	valb = Tle5012Sensor.reg.isStatusMagnitideOutOfLimit();
	WPRINT_APP_INFO(("SMAGOL    0x%X\t%u\t1,  boolean\tru\t7    \t%s\n",valb,valb,valb
		? "GMR magnitude out of limit"
		: "GMR magnitude Ok"));

	valb = Tle5012Sensor.reg.isStatusXYOutOfLimit();
	WPRINT_APP_INFO(("SXYOL     0x%X\t%u\t1,  boolean\tru\t6    \t%s\n",valb,valb,valb
		? "X/Y data out of limit"
		: "X/Y data Ok"));

	valb = Tle5012Sensor.reg.isStatusOverflow();
	WPRINT_APP_INFO(("SOV       0x%X\t%u\t1,  boolean\tru\t5    \t%s\n",valb,valb,valb
		? "DSPU overflow occurred"
		: "No DSPU overflow occurred"));

	valb = Tle5012Sensor.reg.isStatusDSPU();
	WPRINT_APP_INFO(("SDSPU     0x%X\t%u\t1,  boolean\tr\t4     \t%s\n",valb,valb,valb
		? "DPSU self-test not Ok or still running"
		: "DPSU self-test Ok"));

	valb = Tle5012Sensor.reg.isStatusFuse();
	WPRINT_APP_INFO(("SFUSE     0x%X\t%u\t1,  boolean\tr\t3     \t%s\n",valb,valb,valb
		? "CRC on fuse fail"
		: "CRC on fuse Ok"));

	valb = Tle5012Sensor.reg.isStatusVoltage();
	WPRINT_APP_INFO(("SVR       0x%X\t%u\t1,  boolean\tr\t2     \t%s\n",valb,valb,valb
		? "over voltage VDD-off, GND-off or VOVG/A/D too high"
		: "Voltages Ok"));

	valb = Tle5012Sensor.reg.isStatusWatchDog();
	WPRINT_APP_INFO(("SWD       0x%X\t%u\t1,  boolean\tr\t1     \t%s\n",valb,valb,valb
		? "watch dog counter expired (DSPU stop)"
		: "normal operation"));

	valb = Tle5012Sensor.reg.isStatusReset();
	WPRINT_APP_INFO(("SRST      0x%X\t%u\t1,  boolean\tr\t0     \t%s\n",valb,valb,valb
		? "indication of power-up, short power-break, firmware or active reset"
		: "no reset since last readout"));
}


void show_ACSTAT()
{
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tACSTAT\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_ACSTAT));

	valb = Tle5012Sensor.reg.isFirmwareReset();
	WPRINT_APP_INFO(("ASFRST    0x%X\t%u\t1,  boolean\truw\t10  \t%s\n",valb,valb,valb
		? "activation of HW Reset (S_RST is set)"
		: "after execution (write only, thus always returns 0)"));

	valb = Tle5012Sensor.reg.isADCCheck();
	WPRINT_APP_INFO(("ASADCT    0x%X\t%u\t1,  boolean\truw\t9   \t%s\n",valb,valb,valb
		? "after execution"
		: "activation of ADC Test vector Check"));

	valb = Tle5012Sensor.reg.isGMRCheck();
	WPRINT_APP_INFO(("ASVEGMAG  0x%X\t%u\t1,  boolean\truw\t7   \t%s\n",valb,valb,valb
		? "monitoring of magnitude enabled"
		: "monitoring of magnitude disabled"));

	valb = Tle5012Sensor.reg.isXYCheck();
	WPRINT_APP_INFO(("ASVECXY   0x%X\t%u\t1,  boolean\truw\t6   \t%s\n",valb,valb,valb
		? "monitoring of X,Y Out of Limit enabled"
		: "monitoring of X,Y Out of Limit disabled"));

	valb = Tle5012Sensor.reg.isDSPUoverflow();
	WPRINT_APP_INFO(("ASOV      0x%X\t%u\t1,  boolean\truw\t5   \t%s\n",valb,valb,valb
		? "monitoring of DSPU Overflow enabled"
		: "monitoring of DSPU Overflow disabled"));

	valb = Tle5012Sensor.reg.isDSPUbist();
	WPRINT_APP_INFO(("ASDSPU    0x%X\t%u\t1,  boolean\truw\t4   \t%s\n",valb,valb,valb
		? "activation of DSPU BIST or BIST running"
		: "after execution"));

	valb = Tle5012Sensor.reg.isFuseCRC();
	WPRINT_APP_INFO(("ASFUSE    0x%X\t%u\t1,  boolean\truw\t3   \t%s\n",valb,valb,valb
		? "monitoring of CRC enabled"
		: "monitoring of CRC disabled"));

	valb = Tle5012Sensor.reg.isVoltageCheck();
	WPRINT_APP_INFO(("ASVR      0x%X\t%u\t1,  boolean\truw\t2   \t%s\n",valb,valb,valb
		? "check of regulator voltages enabled"
		: "check of regulator voltages disabled"));

	valb = Tle5012Sensor.reg.isWatchdog();
	WPRINT_APP_INFO(("ASWD      0x%X\t%u\t1,  boolean\truw\t1   \t%s\n",valb,valb,valb
		? "DSPU Watch dog monitoring enabled"
		: "DSPU watch dog monitoring disabled"));

	valb = Tle5012Sensor.reg.isActivationReset();
	WPRINT_APP_INFO(("ASRST     0x%X\t%u\t1,  boolean\truw\t0   \t%s\n",valb,valb,valb
		? "default or after execution of firmware reset"
		: "activation of firmware reset"));
}

void show_MAINA()
{
	bool valb;
	uint16_t vali;

	WPRINT_APP_INFO(("\nRegister:\tAVAL\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_AVAL));

	valb = Tle5012Sensor.reg.isAngleValueNew();
	WPRINT_APP_INFO(("RDAV      0x%X\t%u\t1,  boolean\tr\t15    \t%s\n",valb,valb,valb
		? "new angle value present"
		: "no new angle value since last readout"));

	vali = Tle5012Sensor.reg.getAngleValue();
	WPRINT_APP_INFO(("ANGVAL    %X\t%u\t16, uint16_t\tru\t0:14 \tCalculated Angle Value (signed 15-bit)\n",vali,vali));


	WPRINT_APP_INFO(("\nRegister:\tASPD\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_ASPD));

	valb = Tle5012Sensor.reg.isSpeedValueNew();
	WPRINT_APP_INFO(("RDAS      0x%X\t%u\t1,  boolean\tr\t15    \t%s\n",valb,valb,valb
		? "new angle speed value present"
		: "no new speed angle value since last readout"));

	vali = Tle5012Sensor.reg.getSpeedValue();
	WPRINT_APP_INFO(("ANGSPD    %X\t%u\t16, uint16_t\tru\t0:14 \tCalculated Angle Speed, where the sign indicates the direction of the rotation\n",vali,vali));


	WPRINT_APP_INFO(("\nRegister:\tAREV\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_AREV));

	valb = Tle5012Sensor.reg.isNumberOfRevolutionsNew();
	WPRINT_APP_INFO(("RDREV     0x%X\t%u\t1,  boolean\tr\t15    \t%s\n",valb,valb,valb
		? "new value present"
		: "no new value since last readout"));

	vali = Tle5012Sensor.reg.getNumberOfRevolutions();
	WPRINT_APP_INFO(("FCNT      %X\t%u\t6,  uint8_t\truw\t9:14 \tInternal frame counter. Increments every update period (FIR_MD setting)\n",vali,vali));

	vali = Tle5012Sensor.reg.getFrameCounter();
	WPRINT_APP_INFO(("REVOL     %X\t%u\t8,  uint16_t\tru\t0:8 \tNumber of Revolutions (signed 9-bit value)\n",vali,vali));


	WPRINT_APP_INFO(("\nRegister:\tFSYNC\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_FSYNC));

	vali = Tle5012Sensor.reg.getFrameSyncCounter();
	WPRINT_APP_INFO(("TEMPR     %X\t%u\t7,  int16_t\trw\t9:15 \tSigned offset compensated temperature value\n",vali,vali));

	vali = Tle5012Sensor.reg.getTemperatureValue();
	WPRINT_APP_INFO(("FSYNC     %X\t%u\t9,  uint16_t\tr\t0:9  \tFrame Synchronization Counter Value\n",vali,vali));

}

void show_MOD1()
{
	uint16_t vali;
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tMOD1\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_MOD_1));

	vali = Tle5012Sensor.reg.getFilterDecimation();
	WPRINT_APP_INFO(("FIRMD     0x%X\t%u\t2,  uint8_t \trw\t14:15\t%s\n",vali,vali,
		vali == 0
			? "Update Rate Setting (Filter Decimation): 00b none"
			: (vali == 1
				? "Update Rate Setting (Filter Decimation): 01b 42.7 μs"
				: (vali == 2
					? "Update Rate Setting (Filter Decimation): 10b 85.3 μs"
					: "Update Rate Setting (Filter Decimation): 11b 170.6 μs")) ));

	valb = Tle5012Sensor.reg.statusClockSource();
	WPRINT_APP_INFO(("CLKSEL    0x%X\t%u\t1,  boolean\tru \t4    \t%s\n",valb,valb,valb
		? "external 4-MHz clock (IFC pin switched to input)"
		: "internal oscillator" ));

	valb = Tle5012Sensor.reg.isDSPUhold();
	WPRINT_APP_INFO(("DSPUHOLD  0x%X\t%u\t1,  boolean\trw\t2     \t%s\n",valb,valb,valb
		? "DSPU is on hold"
		: "DSPU in normal schedule operation" ));

	vali = Tle5012Sensor.reg.getIIFMod();
	WPRINT_APP_INFO(("IIFMOD    0x%X\t%u\t2,  uint8_t \trw\t0:1  \t%s\n",vali,vali,
		vali == 0
			? "Incremental Interface Mode: 00b IIF disabled"
			: (vali == 1
				? "Incremental Interface Mode: 01b A/B operation with Index on IFC pin"
				: (vali == 2
					? "Incremental Interface Mode: 10b Step/Direction operation with Index on IFC pin"
					: "Incremental Interface Mode: 11b not allowed")) ));
}

void show_SIL()
{
	uint16_t vali;
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tSIL\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_SIL));

	valb = Tle5012Sensor.reg.isFilterParallel();
	WPRINT_APP_INFO(("FILTPAR   0x%X\t%u\t1,  boolean\trw\t15   \t%s\n",valb,valb,valb
		? "filter parallel enabled (source: X-value)"
		: "filter parallel disabled" ));

	valb = Tle5012Sensor.reg.isFilterInverted();
	WPRINT_APP_INFO(("FILTINV   0x%X\t%u\t1,  boolean\trw\t14   \t%s\n",valb,valb,valb
		? "filter inverted enabled"
		: "filter inverted disabled" ));

	valb = Tle5012Sensor.reg.getFulseReload();
	WPRINT_APP_INFO(("FUSEREL   0x%X\t%u\t1,  boolean\trw\t10   \t%s\n",valb,valb,valb
		? "normal operation"
		: "reload of registers with fuse values immediately" ));

	valb = Tle5012Sensor.reg.isADCTestVector();
	WPRINT_APP_INFO(("ADCTVEN   0x%X\t%u\t1,  boolean\trw\t6    \t%s\n",valb,valb,valb
		? "ADC-Test Vectors enabled"
		: "ADC-Test Vectors disabled" ));

	vali = Tle5012Sensor.reg.getTestVectorY();
	WPRINT_APP_INFO(("ADCTVY    0x%X\t%u\t3,  uint16_t\trw\t3:5  \tTest vector Y: %s\n",vali,vali,
		vali == 0
			? "000b 0V"
			: (vali == 1
				? "001b +70%"
				: (vali == 2
					? "010b +100%"
					: (vali == 3
						? "011b +Overflow"
						: (vali == 5
							? "101b -70%"
								: (vali == 6
									? "110b -100%"
									: "111b -Overflow" ))))) ));

	vali = Tle5012Sensor.reg.getTestVectorX();
	WPRINT_APP_INFO(("ADCTVX    0x%X\t%u\t3,  uint16_t\trw\t0:2  \tTest vector X: %s\n",vali,vali,
		vali == 0
			? "000b 0V"
			: (vali == 1
				? "001b +70%"
				: (vali == 2
					? "010b +100%"
					: (vali == 3
						? "011b +Overflow"
						: (vali == 5
							? "101b -70%"
								: (vali == 6
									? "110b -100%"
									: "111b -Overflow" ))))) ));
}

void show_MOD2()
{
	uint16_t vali;
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tMOD2\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_MOD_2));

	vali = Tle5012Sensor.reg.getAngleRange();
	WPRINT_APP_INFO(("ANGRANGE  0x%X\t%u\t1,  uint8_t\trw\t11:14\t%s\n",vali,vali,
		vali == 0x080
			? "080h factor 1 (default), magnetic angle -180°..180°"
			: (vali == 0x200
				? "200h factor 4, magnetic angle -45°..45°"
				: "040h factor 0.5, magnetic angle -180°..180°" ) ));

	valb = Tle5012Sensor.reg.isAngleDirection();
	WPRINT_APP_INFO(("ANGDIR    0x%X\t%u\t1,  boolean\trw\t10  \t%s\n",valb,valb,valb
		? "counterclockwise rotation of magnet"
		: "counterclockwise rotation of magnet" ));

	valb = Tle5012Sensor.reg.isPrediction();
	WPRINT_APP_INFO(("PREDICT   0x%X\t%u\t1,  boolean\trw\t2   \t%s\n",valb,valb,valb
		? "prediction enabled"
		: "prediction disabled" ));

	vali = Tle5012Sensor.reg.getCalibrationMode();
	WPRINT_APP_INFO(("AUTOCAL   0x%X\t%u\t2,  uint8_t \trw\t0:1  \t%s\n",vali,vali,
		vali == 0
			? "00b no auto-calibration"
			: (vali == 1
				? "01b auto-cal. mode 1: update every angle update cycle"
				: (vali == 2
					? "10b auto-cal. mode 2: update every 1.5 revolutions"
					: "11b auto-cal. mode 3: update every 11.25°" )) ));
}

void show_MOD3()
{
	uint16_t vali;
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tMOD3\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_MOD_3));

	vali = Tle5012Sensor.reg.getAngleBase();
	WPRINT_APP_INFO(("ANG_BASE  0x%X\t%u\t12, uint16_t \trw\t4:15 \tAngle Base at 0°: %s\n",vali,vali,
		vali == 0x800
			? "800H -180°"
			: (vali == 0
				? "000H 0°"
				: "7FFH +179.912°") ));

	vali = Tle5012Sensor.reg.getPadDriver();
	WPRINT_APP_INFO(("PADDRV    0x%X\t%u\t2,  uint8_t     rw \t0:1 \tConfig of Pad-Driver: %s\n",vali,vali,
		vali == 0
			? "00b IFA/IFB/IFC: strong driver, DATA: strong driver, fast edge"
			: (vali == 1
				? "01b IFA/IFB/IFC: strong driver, DATA: strong driver, slow edge"
				: (vali == 2
					? "10B IFA/IFB/IFC: weak driver, DATA: medium driver, fast edge"
					: "11B IFA/IFB/IFC: weak driver, DATA: weak driver, slow edge")) ));

	valb = Tle5012Sensor.reg.isSSCOutputMode();
	WPRINT_APP_INFO(("SSCOD     0x%X\t%u\t1,  boolean\trw\t2   \t%s\n",valb,valb,valb
		? "Push-Pull"
		: "Open Drain" ));

	valb = Tle5012Sensor.reg.isSpikeFilter();
	WPRINT_APP_INFO(("SPIKEF    0x%X\t%u\t1,  boolean\trw\t3   \t%s\n",valb,valb,valb
		? "spike filter enabled"
		: "spike filter disabled" ));
}

void show_OFFSETS()
{
	int16_t vali;

	WPRINT_APP_INFO(("\nRegister:\tOFFX\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_OFFX));
	vali = Tle5012Sensor.reg.getOffsetX();
	WPRINT_APP_INFO(("XOFFSET   0x%X\t%u\t12, int16_t\trw\t4:15 \t12-bit signed integer value of raw X-signal offset\n",vali,vali));

	WPRINT_APP_INFO(("\nRegister:\tOFFY\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_OFFY));
	vali = Tle5012Sensor.reg.getOffsetY();
	WPRINT_APP_INFO(("YOFFSET   0x%X\t%u\t12, int16_t\trw\t4:15 \t12-bit signed integer value of raw Y-signal offset\n",vali,vali));

	WPRINT_APP_INFO(("\nRegister:\tSYNCH\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_SYNCH));
	vali = Tle5012Sensor.reg.getAmplitudeSynch();
	WPRINT_APP_INFO(("SYNCH     0x%X\t%u\t12, int16_t\trw\t4:15 \t12-bit signed integer value of amplitude synchronicity correction\n",vali,vali));
}

void show_IFAB()
{
	uint16_t vali;
	bool valb;
	uint8_t iface = Tle5012Sensor.reg.getInterfaceMode();

	WPRINT_APP_INFO(("\nRegister:\tIFAB\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_IFAB));

	vali = Tle5012Sensor.reg.getOrthogonality();
	WPRINT_APP_INFO(("ORTHO     0x%X\t%u\t3,  uint16_t\trw\t4:15 \t12-bit signed integer value of orthogonality correction\n",vali,vali));

	vali = Tle5012Sensor.reg.getHysteresisMode();
	WPRINT_APP_INFO(("IFADHYST  0x%X\t%u\t2,  uint8_t \trw\t0:1  \tHSM and IIF Mode:%s\n",vali,vali,
		(iface == 0 || iface == 2
			? (vali == 0
				? "00b HSM: 0°"
				: (vali == 1
					? "01b HSM: 0.175°"
					: (vali == 2
						? "10b HSM: 0.35°"
						: "11b HSM: 0.70°")))
			: (iface == 3
				? (vali == 0
					? "00b SPC: 3.0 μs"
					: (vali == 1
						? "01b SPC: 2.5 μs"
						: (vali == 2
							? "10b SPC: 2.0 μs"
							: "11b SPC: 1.5 μs")))
				: "none")
			)
		));

	valb = Tle5012Sensor.reg.getFIRUpdateRate();
	WPRINT_APP_INFO(("FIRUDR    0x%X\t%u\t1,  boolean\trw\t2   \t%s\n",valb,valb,valb
		? "FIR_MD = ‘10’ (85.3 μs)"
		: "FIR_MD = ‘01’ (42.7 μs)" ));

	valb = Tle5012Sensor.reg.isIFABOutputMode();
	WPRINT_APP_INFO(("IFABOD    0x%X\t%u\t1,  boolean\trw\t2   \t%s\n",valb,valb,valb
		? "Push-Pull"
		: "Push-Pull" ));
}

void show_MOD4()
{
	uint16_t vali;
	uint8_t iface = Tle5012Sensor.reg.getInterfaceMode();

	WPRINT_APP_INFO(("\nRegister:\tMOD4\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_MOD_4));

	vali = Tle5012Sensor.reg.getOffsetTemperatureX();
	WPRINT_APP_INFO(("TCOXT     0x%X\t%u\t7,  int8_t\trw\t9:15  \t7-bit signed integer value of X-offset temperature coefficient\n",vali,vali));

	vali = Tle5012Sensor.reg.getHSMplp();
	WPRINT_APP_INFO(("HSMPLP    0x%X\t%u\t2,  uint8_t\trw\t5:8  \t%s\n",vali,vali,
		(iface == 0
			? "IIF Absolute Count, x0xxb enabled, x1xxb disabled"
			: (iface == 1
				? "PWM Error Indication, xx0xb enabled, xx1xb disabled"
				: (iface == 2
					? "HSM Pole-Pair Configuration 0000b=1 - 1111b=16"
					: (iface == 3
						? "SPC Total Trigger Time, 0000b 90*UT, 0100b tmlow + 12 UT"
						: "none" )))) ));

	vali = Tle5012Sensor.reg.getIFABres();
	WPRINT_APP_INFO(("IFABRES   0x%X\t%u\t2,  uint8_t\trw\t3:4  \t%s\n",vali,vali,
		(iface == 1
			? (vali == 0
				? "00b PWM: 244 Hz"
				: (vali == 1
					? "01b PWM: 488 Hz"
					: (vali == 2
						? "10b PWM: 977 Hz"
						: "11b PWM: 1953 Hz")))
			: (iface == 0
					? (vali == 0
						? "00b IIF: 12bit, 0.088° step"
						: (vali == 1
							? "01b IIF: 11bit, 0.176° step"
							: (vali == 2
								? "10b IIF: 10bit, 0.352° step"
								: "11b IIF: 9bit, 0.703° step")))
					: (iface == 3
						? (vali == 0
							? "00b SPC: 00B 12bit angle"
							: (vali == 1
								? "01b SPC: 01B 16bit angle"
								: (vali == 2
									? "10b SPC: 10B 12bit angle + 8bit temperature"
									: "11b SPC: 11B 16bit angle + 8bit temperature")))
						: "none")
		)) ));

	vali = Tle5012Sensor.reg.getInterfaceMode();
	WPRINT_APP_INFO(("IFMD      0x%X\t%u\t2,  uint8_t\trw\t0:1  \tInterface Mode on IFA,IFB,IFC: %u\n",vali,vali,iface));
}

void show_TCOTY()
{
	int16_t vali;
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tTCOY\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_TCO_Y));

	vali = Tle5012Sensor.reg.getOffsetTemperatureY();
	WPRINT_APP_INFO(("TCOYT     0x%X\t%u\t7,  int8_t  \tr\t9:15  \t7-bit signed integer value of Y-offset temperature coefficient\n",vali,vali));

	valb = Tle5012Sensor.reg.isStartupBist();
	WPRINT_APP_INFO(("SBIST     0x%X\t%u\t1,  boolean\trw\t8    \t%s\n",valb,valb,valb
		? "Startup-BIST enabled"
		: "Startup-BIST disabled" ));

	vali = Tle5012Sensor.reg.getCRCpar();
	WPRINT_APP_INFO(("CRCPAR    0x%X\t%u\t7,  int8_t\trw\t0:7   \tCRC of parameters from address 08H to 0FH\n",vali,vali));
}

void show_ADC()
{
	int16_t vali;
	uint16_t valu;
	bool valb;

	WPRINT_APP_INFO(("\nRegister:\tADCX\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_ADC_X));
	vali = Tle5012Sensor.reg.getADCx();
	WPRINT_APP_INFO(("ADCX      0x%X\t16, int16_t\tr\t0:15\t%u\n",vali,vali));

	WPRINT_APP_INFO(("\nRegister:\tADCY\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_ADC_Y));
	vali = Tle5012Sensor.reg.getADCy();
	WPRINT_APP_INFO(("ADCY      0x%X\t16, int16_t\tr\t0:15\t%u\n",vali,vali));

	WPRINT_APP_INFO(("\nRegister:\tDMAG\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_D_MAG));
	valu = Tle5012Sensor.reg.getVectorMagnitude();
	WPRINT_APP_INFO(("MAG       0x%X\t%u\t9,  uint16_t\tru\t0:9  \tUnsigned Angle Vector Magnitude after X, Y error\n",valu,valu));

	WPRINT_APP_INFO(("\nRegister:\tTRAW\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_T_RAW));
	valb = Tle5012Sensor.reg.getTemperatureRAW();
	WPRINT_APP_INFO(("TTGL      0x%X\t%u\t1,  boolean\tr\t15    \tToggles after every new temperature value\n",valb,valb));

	WPRINT_APP_INFO(("\nRegister:\tIIFCNT\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_IIF_CNT));
	valu = Tle5012Sensor.reg.getCounterIncrements();
	WPRINT_APP_INFO(("IIFCNT    0x%X\t13, uint16_t    r   \t0:13 \t%u, Internal 14-bit counter for the incremental interface, counts from 0 to 16383 during one full turn\n",valu,valu));

	WPRINT_APP_INFO(("\nRegister:\tT250\tOffset: 0x%X\n",Tle5012Sensor.reg.REG_T25O));
	vali = Tle5012Sensor.reg.getT25Offset();
	WPRINT_APP_INFO(("T250      0x%X\t%u\t9,  int16_t\tr\t9:15  \tSigned offset value at 25°C temperature; 1dig=0.36°C.\n",vali,vali));
}


void setup() {
	// Enable Sensor and check the return value
	WPRINT_APP_INFO(("[TLE5012B] : setup begin -> %u\n", 0));
	wiced_rtos_delay_milliseconds( 1000 );
	checkError = Tle5012Sensor.begin();
	WPRINT_APP_INFO(("[TLE5012B] : Check Error -> %u\n", checkError));
	wiced_rtos_delay_milliseconds( 1000 );

	// read all registers
	checkError = Tle5012Sensor.readRegMap();
	show_bin();

	show_STAT();
	show_ACSTAT();
	show_MAINA();
	show_MOD1();
	show_SIL();
	show_MOD2();
	show_MOD3();
	show_OFFSETS();
	show_IFAB();
	show_MOD4();
	show_TCOTY();
	show_ADC();
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

#endif