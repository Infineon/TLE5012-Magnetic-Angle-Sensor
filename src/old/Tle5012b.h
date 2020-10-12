/*!
 * \name        Tle5012b.h - Library for Arduino for the TLE5012B angle sensor.
 * \author      Infineon Technologies AG 
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \details
 * The TLE5012B is a 360° angle sensor that detects the orientation of a magnetic field.
 * This is achieved by measuring sine and cosine angle components with monolithic integrated
 * Giant Magneto Resistance (iGMR) elements. These raw signals (sine and cosine) are digitally
 * processed internally to calculate the angle orientation of the magnetic field (magnet).
 * The TLE5012B is a pre-calibrated sensor. The calibration parameters are stored in laser fuses.
 * At start-up the values of the fuses are written into flip-flops, where these values can be changed
 * by the application-specific parameters. Further precision of the angle measurement over a wide
 * temperature range and a long lifetime can be improved by enabling an optional internal autocalibration
 * algorithm. Data communications are accomplished with a bi-directional Synchronous Serial Communication (SSC)
 * that is SPI-compatible. The sensor configuration is stored in registers, which are accessible by the
 * SSC interface. Additionally four other interfaces are available with the TLE5012B: Pulse-Width-Modulation (PWM)
 * Protocol, Short-PWM-Code (SPC) Protocol, Hall Switch Mode (HSM) and Incremental Interface (IIF). These interfaces
 * can be used in parallel with SSC or alone. Pre-configured sensor derivate with different interface settings are available.
 * Online diagnostic functions are provided to ensure reliable operation.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Arduino.h"
#include "util/Tle5012b_SPI.h"

#ifndef TLE5012B_H
#define TLE5012B_H

// Sensor registers
#define READ_SENSOR                 0x8000    //!< base command for read
#define WRITE_SENSOR                0x5000    //!< base command for write
#define READ_BLOCK_CRC              0x8088    //!< initialize block CRC check command

#define REG_STAT                    0x0000    //!< STAT status register
#define REG_ACSTAT                  0x0010    //!< ACSTAT activation status register
#define REG_AVAL                    0x0020    //!< AVAL angle value register
#define REG_ASPD                    0x0030    //!< ASPD angle speed register
#define REG_AREV                    0x0040    //!< AREV angle revolution register
#define REG_FSYNC                   0x0050    //!< FSYNC frame synchronization register
#define REG_MOD_1                   0x0060    //!< MOD_1 interface mode1 register
#define REG_SIL                     0x0070    //!< SIL register
#define REG_MOD_2                   0x0080    //!< MOD_2 interface mode2 register
#define REG_MOD_3                   0x0090    //!< MOD_3 interface mode3 register
#define REG_OFFX                    0x00A0    //!< OFFX offset x
#define REG_OFFY                    0x00B0    //!< OFFY offset y
#define REG_SYNCH                   0x00C0    //!< SYNCH synchronicity
#define REG_IFAB                    0x00D0    //!< IFAB register
#define REG_MOD_4                   0x00E0    //!< MOD_4 interface mode4 register
#define REG_TCO_Y                   0x00F0    //!< TCO_Y temperature coefficient register
#define REG_ADC_X                   0x0100    //!< ADC_X ADC X-raw value
#define REG_ADC_Y                   0x0110    //!< ADC_Y ADC Y-raw value
#define REG_D_MAG                   0x0140    //!< D_MAG angle vector magnitude
#define REG_T_RAW                   0x0150    //!< T_RAW temperature sensor raw-value
#define REG_IIF_CNT                 0x0200    //!< IIF_CNT IIF counter value
#define REG_T25O                    0x0300    //!< T25O temperature 25°c offset value

#define SYSTEM_ERROR_MASK           0x4000    //!< System error masks for safety words
#define INTERFACE_ERROR_MASK        0x2000    //!< Interface error masks for safety words
#define INV_ANGLE_ERROR_MASK        0x1000    //!< Angle error masks for safety words

#define CRC_POLYNOMIAL              0x1D      //!< values used for calculating the CRC
#define CRC_SEED                    0xFF
#define CRC_NUM_REGISTERS           0x0008    //!< number of CRC relevant registers
#define MAX_REGISTER_MEM            0x0030    //!< max readable register values buffer

#define DELETE_BIT_15               0x7FFF    //!< Value used to delete everything except the first 15 bits
#define CHANGE_UINT_TO_INT_15       0x8000    //!< Value used to change unsigned 16bit integer into signed
#define CHECK_BIT_14                0x4000    //!<
#define GET_BIT_14_4                0x7FF0    //!<

#define DELETE_7BITS                0x01FF    //!< values used to calculate 9 bit signed integer sent by the sensor
#define CHANGE_UNIT_TO_INT_9        0x0200    //!< Value used to change unsigned 9bit integer into signed
#define CHECK_BIT_9                 0x0100

#define POW_2_15                    32768.0   //!< values used to for final calculations of angle speed, revolutions, range and value
#define POW_2_7                     128.0     //!<
#define ANGLE_360_VAL               360.0

#define TEMP_OFFSET                 152.0     //!< values used to calculate the temperature
#define TEMP_DIV                    2.776

//!< Prints a binary number with leading zeros (Automatic Handling)
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0');
//!< Prints a binary number with leading zeros (Automatic Handling) with space
#define PRINTBINS(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? " 1 " : " 0 ");

/*!
 * Error types from safety word
 */
enum errorTypes
{
	NO_ERROR               = 0x00,  //!< NO_ERROR = Safety word was OK
	SYSTEM_ERROR           = 0x01,  //!< SYSTEM_ERROR = over/under voltage, VDD negative, GND off, ROM defect
	INTERFACE_ACCESS_ERROR = 0x02,  //!< INTERFACE_ACCESS_ERROR = wrong address or wrong lock
	INVALID_ANGLE_ERROR    = 0x03,  //!< INVALID_ANGLE_ERROR = NO_GMR_A = 1 or NO_GMR_XY = 1
	ANGLE_SPEED_ERROR      = 0x04,  //!< ANGLE_SPEED_ERROR = combined error, angular speed calculation wrong
	CRC_ERROR              = 0xFF   //!< CRC_ERROR = Cyclic Redundancy Check (CRC), which includes the STAT and RESP bits wrong
};

/*!
  * Set the UPDate bit high (read from update buffer) or low (read directly)
  */
enum updTypes
{
	UPD_low  = 0x0000,           //!< read normal registers
	UPD_high = 0x0400,           //!< read update buffer registers
};

/*!
  * Switch on/off safety word generation
  */
enum safetyTypes
{
	SAFE_low  = 0x0000,          //!< switch of safety word generation
	SAFE_high = 0x0001,          //!< switch on safety word generation
};

class Tle5012b
{
	public:

	Tle5012b_SPI* _spiConnection;        //!< SPI library for 3/4wire setup

	/*!
	 * Offset for the slave number register to identify the
	 * right selected slave. Max 4 slaves with separated CSQ
	 * lines are possible. If more than one sensor is used on the SPI
	 * interface, than the SNR register must we written with the correct slave number
	 */
	enum slaveNum
	{
		TLE5012B_S0 = 0x0000,  //!< TLE5012B_S0 default setting for only one sensor on the SPI
		TLE5012B_S1 = 0x2000,  //!< TLE5012B_S1 second sensor needs also a second CSQ
		TLE5012B_S2 = 0x4000,  //!< TLE5012B_S2 third sensor and ditto
		TLE5012B_S3 = 0x6000   //!< TLE5012B_S3 fourth sensor and ditto
	};

	uint8_t mEN;               //!< Pin to switch on/off the sensor
	uint8_t mMOSI;             //!< Pin for SPI MOSI (pin 0.6 on test board);
	uint8_t mMISO;             //!< Pin for SPI MISO (pin 0.7 on test board)
	uint8_t mSCK;              //!< Pin for CLOCK (pin 0.8 on test board)
	uint8_t mCS;               //!< Pin for chip select (pin 0.9 on test board)
	slaveNum mSlave;           //!< actual set slave number

	typedef struct safetyWord {  //!< Safety word bit setting
		boolean STAT_RES;        //!< bits 15:15 Indication of chip reset or watchdog overflow
		boolean STAT_ERR;        //!< bits 14:14 System error
		boolean STAT_ACC;        //!< bits 13:13 Interface access error
		boolean STAT_ANG;        //!< bits 12:12 Invalid angle value
		uint8_t RESP;            //!< bits 11:8 Sensor number response indicator
		uint8_t CRC;             //!< bits 7:0 Status ADC Test

		/*!
		 * Returns the safety word slave number to identify the sensor
		 * @return slaveNum setting in safety word
		 */
		slaveNum responseSlave(){
			return (RESP == 0x7 ? TLE5012B_S3
					: (RESP == 0xB ? TLE5012B_S2
							: (RESP == 0xD ? TLE5012B_S1
									: TLE5012B_S0)));
		}

		/*!
		 * Function separates safety word bits
		 * @param [in,out] reg actual safety or last fetched as default
		 * @return safety word
		 */
		uint16_t fetch_Safety(uint16_t reg)
		{
			CRC      = (reg & 0x7F);
			RESP     = (reg & 0xF00) >> 8;
			STAT_ANG = (reg & 0x1000) >> 12;
			STAT_ACC = (reg & 0x2000) >> 13;
			STAT_ERR = (reg & 0x4000) >> 14;
			STAT_RES = (reg & 0x8000) >> 15;
			return (reg);
		}
	} safetyWord_t;

	
	Tle5012b();			//!< constructor for the Sensor
	~Tle5012b();		//!< destructor stops the Sensor

	/**
	 * All these functions cover the SPI interface and should be implemented
	 * into XMC SPI wrapper.
	 * In 3wire SPI mode miso and mosi are connected together, so read and
	 * write operations are on the same line. In 4wire more read and write are
	 * separated. The system clock SCK and the sensor enable EN line are used
	 * for all slaves whereas the chip select line CS must we set unique for
	 * each slave. A max of four slaves on one SPI interface are possible
	 * @return CRC error type
	 * @param [in] bus a SPIClass object
	 * @param [in] miso MISO pin for the SPI/SSC interface
	 * @param [in] mosi MOSI pin for the SPI/SSC interface
	 * @param [in] sck system clock pin for external sensor clock setting
	 * @param [in] cs chip select pin, must be unique for each slave
	 * @param [in] slave slave offset setting for the SNR register, default is TLE5012B_S0
	 */
	errorTypes begin();
	errorTypes begin(uint8_t cs, slaveNum slave=TLE5012B_S0 );
	errorTypes begin(Tle5012b_SPI &bus, uint8_t cs, slaveNum slave=TLE5012B_S0 );
	errorTypes begin(Tle5012b_SPI &bus, uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs,slaveNum slave=TLE5012B_S0);

	void end();			//!< Switches the sensor off and ends the comunication

	/*!
	 * Triggers an update in the register buffer. This function
	 * should be triggered once before UPD registers where read as
	 * it generates a snapshot of the UPD register values at trigger point
	 */
	void triggerUpdate();

	/*!
	 * Function enables Sensor by switch on EN pin which is only possible
	 * on Sensor2go shields, but also sets chipselect high.
	 * So it is called always.
	 */
	void enableSensor();

	/*!
	 * Functions disables Sensor by switch off EN pin (only possible on Sensor2go shield)
	 */
	void disableSensor();

	/*!
	 * Reads the block of _registers from addresses 08 - 0F in order to figure out the CRC.
	 * ATTENTION: You need a memory chunk of unit16_t * CRC Registers + 1 * uint16_t for the safety word.
	 * @return CRC error type
	 */
	errorTypes readBlockCRC();

	/*!
	 * General read function for reading _registers from the Tle5012b.
	 *
	 * structure of command word, the numbers represent the bit position of the 2 byte command
	 * 15 - 0 write, 1 read
	 * 14:11 -  0000 for default operational access for addresses between 0x00 - 0x04, 1010 for configuration access for addresses between 0x05 - 0x11
	 * 10 - 0 access to current value, 1 access to value in update buffer
	 * 9:4 - access to 6 bit register address
	 * 3:0 - 4 bit number of data words.
	 *
	 * @param [in] command the command for reading
	 * @param [out] data where the data received from the _registers will be stored
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or not (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes readFromSensor(uint16_t command, uint16_t &data, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * Can be used to read 1 or more consecutive _registers, and the values
	 * used to read 1 or more than 1 consecutive _registers.
	 * The maximum amount of registers are limited by the bit 3-0 of the command word, which means
	 * you can read max 15 registers and one safety word at once.
	 * @param [in] command the command for reading
	 * @param [out] data where the data received from the _registers will be stored
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes readMoreRegisters(uint16_t command, uint16_t data[], updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * This functions reads the main status word for the sensor,
	 * mainly for checking with the additional safety word
	 * @param [out] data pointer with the received data word
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes readStatus(uint16_t &data, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * This functions reads activation status word for the sensor,
	 * which held on/off information for all optional checks and additional functions
	 * @param [out] data pointer with the received data word
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes readActivationStatus(uint16_t &data, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * The next functions are used primarily for storing the parameters and
	 * control of how the sensor works. The values stored in them are used to calculate
	 * the CRC, and their values are stored in the private component of the class, _registers.
	 * @param [out] data where the data received from the _registers will be stored
	 * @return CRC error type
	 */
	errorTypes readActiveStatus(uint16_t &data);    //!< read register offset 0x01
	errorTypes readIntMode1(uint16_t &data);        //!< read register offset 0x06
	errorTypes readSIL(uint16_t &data);             //!< read register offset 0x07
	errorTypes readIntMode2(uint16_t &data);        //!< read register offset 0x08
	errorTypes readIntMode3(uint16_t &data);        //!< read register offset 0x09
	errorTypes readOffsetX(uint16_t &data);         //!< read register offset 0x0A
	errorTypes readOffsetY(uint16_t &data);         //!< read register offset 0x0B
	errorTypes readSynch(uint16_t &data);           //!< read register offset 0x0C
	errorTypes readIFAB(uint16_t &data);            //!< read register offset 0x0D
	errorTypes readIntMode4(uint16_t &data);        //!< read register offset 0x0E
	errorTypes readTempCoeff(uint16_t &data);       //!< read register offset 0x0F
	errorTypes readTempDMag(uint16_t &data);        //!< read register offset 0x14
	errorTypes readTempRaw(uint16_t &data);         //!< read register offset 0x15
	errorTypes readTempIIFCnt(uint16_t &data);      //!< read register offset 0x20
	errorTypes readTempT25(uint16_t &data);         //!< read register offset 0x30

	/*!
	 * The rawX value is signed 16 bit value
	 * @param data pointer to 16bit word
	 * @return CRC error type
	 */
	errorTypes readRawX(int16_t &data);

	/*!
	 * The rawY value is signed 16 bit value
	 * @param data pointer to 16bit word
	 * @return CRC error type
	 */
	errorTypes readRawY(int16_t &data);

	/*!
	 * returns the Angle Range
	 * Angle Range is stored in bytes 14 - 4 of MOD_2.
	 * @param angleRange pointer to 16bit double value
	 * @return CRC error type
	 */
	errorTypes getAngleRange(double &angleRange);

	/*!
	 * Returns the angleValue calculated on the base of a 15 bit signed integer.
	 * However, the register returns 16 bits, so we need to do some bit arithmetic.
	 * @param [in,out] angleValue pointer to 16bit double angle value
	 * @return CRC error type
	 */
	errorTypes getAngleValue(double &angleValue);
	/*!
	 * Same function as before but also returns a pointer to the raw data
	 * @param [in,out] angleValue pointer to 16bit double angle value
	 * @param [in,out] rawAnglevalue point to an int16_t raw data value
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes getAngleValue(double &angleValue, int16_t &rawAnglevalue, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * Returns the number of revolutions done from the angle value which is a 9 bit signed integer.
	 * However, the register returns 16 bits, so we need to do some bit arithmetic.
	 * Therefore the resulting revolution can b only between -256 < numRev < 256 and
	 * it will switch from positive to negative and vice versa values at the borders.
	 * @param [in,out] numRev pointer to 16bit word for the number of revolutions
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes getNumRevolutions(int16_t &numRev, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * Return the temperature.
	 * The temperature value is a 9 bit signed integer.
	 * However, the register returns 16 bits, so we need to do some bit arithmetic.
	 * @param [in,out] temp pointer to 16bit double value of the temperature
	 * @return CRC error type
	 */
	errorTypes getTemperature(double &temp);
	/*!
	 * Same as above but also returns a pointer to the raw data
	 * @param [in,out] temp pointer to 16bit double value of the temperature
	 * @param [in,out] rawTemp pointer to int16_t raw value data
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes getTemperature(double &temp, int16_t &rawTemp, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * Returns the calculated angle speed.
	 * The angle speed is a 15 bit signed integer,
	 * however, the register returns 16 bits, so we need to do some bit arithmetic.
	 * @param [in,out] angleSpeed pointer to 16bit double value
	 * @return CRC error type
	 */
	errorTypes getAngleSpeed(double &angleSpeed);
	/*!
	 * Same as above but also returns a pointer to the raw data
	 * @param [in,out] angleSpeed angleSpeed pointer to 16bit double value
	 * @param [in,out] rawSpeed pointer to int16_t raw value data
	 * @param [in] upd read from update (UPD_high) register or directly (default, UPD_low)
	 * @param [in] safe generate safety word (default, SAFE_high) or no (SAFE_low)
	 * @return CRC error type
	 */
	errorTypes getAngleSpeed(double &angleSpeed,int16_t &rawSpeed, updTypes upd=UPD_low, safetyTypes safe=SAFE_high);

	/*!
	 * Function sets the SNR register with the correct slave number
	 * @param [in] dataToWrite the new data that will be written to the register
	 * @return CRC error type
	 */
	errorTypes writeSlaveNumber(uint16_t dataToWrite);

	/*!
	 * General write function for writing registers to the Tle5012b. The safety flag will be
	 * set always and only some of all registers are writable. See documentation for further information.
	 * @param [in] command the command to execute the write
	 * @param [in] dataToWrite the new data that will be written to the register
	 * @param [in] changeCRC the registerIndex helps figure out in which register the value changed,
	 *        so that we don't need to read all the register again to calculate the CRC
	 * @return CRC error type
	 */
	errorTypes writeToSensor(uint16_t command, uint16_t dataToWrite, bool changeCRC);

	/*!
	 * This function is used in order to update the CRC in the register 0F(second byte)
	 * @param [in] dataToWrite the new data that will be written to the register
	 * @return CRC error type
	 */
	errorTypes writeTempCoeffUpdate(uint16_t dataToWrite);

	/*!
	 * Standard function used for updating the CRC
	 * @param [in] dataToWrite the new data that will be written to the register
	 * @return CRC error type
	 */
	errorTypes writeActivationStatus(uint16_t dataToWrite);    //!< write register offset 0x01
	errorTypes writeIntMode1(uint16_t dataToWrite);            //!< write register offset 0x06
	errorTypes writeSIL(uint16_t dataToWrite);                 //!< write register offset 0x07
	errorTypes writeIntMode2(uint16_t dataToWrite);            //!< write register offset 0x08
	errorTypes writeIntMode3(uint16_t dataToWrite);            //!< write register offset 0x09
	errorTypes writeOffsetX(uint16_t dataToWrite);             //!< write register offset 0x0A
	errorTypes writeOffsetY(uint16_t dataToWrite);             //!< write register offset 0x0B
	errorTypes writeSynch(uint16_t dataToWrite);               //!< write register offset 0x0C
	errorTypes writeIFAB(uint16_t dataToWrite);                //!< write register offset 0x0D
	errorTypes writeIntMode4(uint16_t dataToWrite);            //!< write register offset 0x0E
	errorTypes writeTempCoeff(uint16_t dataToWrite);           //!< write register offset 0x0F

	safetyWord safetyStatus;
	uint16_t safetyWord;                     //!< the last fetched safety word

	private:

	uint16_t _command[2];                    //!< command write data [0] = command [1] = data to write
	uint16_t _received[MAX_REGISTER_MEM];    //!< fetched data from sensor with last word = safety word
	uint16_t _registers[CRC_NUM_REGISTERS];  //!< keeps track of the values stored in the 8 _registers, for which the CRC is calculated

	/*!
	 * This function is called each time any register in the
	 * range 08 - 0F(first byte) is changed. It calculates the new CRC
	 * based on the value of all the _registers and then
	 * stores the value in 0F(second byte)
	 * @return CRC error type
	 */
	errorTypes regularCrcUpdate();

	/*!
	 * checks the safety by looking at the safety word and calculating
	 * the CRC such that the data received is valid
	 * @param safety register with the CRC check data
	 * @param command the command to execute the write
	 * @param readreg pointer to the read data
	 * @param length the length of the data structure
	 * @return CRC error type
	 */
	errorTypes checkSafety(uint16_t safety, uint16_t command, uint16_t* readreg, uint16_t length);

	/*!
	 * When an error occurs in the safety word, the error bit remains 0(error),
	 * until the status register is read again. Flushes out safety errors,
	 * that might have occurred by reading the register without a safety word.
	 * In case the safety word sends an error, this function is
	 * called so that the error bit is reset to 1.
	 */
	void resetSafety();

};

#endif
