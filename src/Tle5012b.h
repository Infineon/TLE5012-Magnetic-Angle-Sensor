/**
 * Tle5012b.h - Library for Arduino for the TLE5012B angle sensor.
 *
 * The TLE5012B is a pre-calibrated 360° angle sensor that detects the orientation 
 * of a magnetic field. The raw signals (sine and cosine) are digitally processed 
 * internally to calculate the angle orientation of the magnetic field (magnet).
 *
 * Have a look at the application note/datasheet for more information.
 *
 * Copyright (c) 2018 Infineon Technologies AG
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
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
 */

/**
 * This class controls the Tle5012b Angle sensor
 */

#ifndef TLE5012B_H_
#define TLE5012B_H_

#include "SPI.h"

//Error masks for safety words
#define SYSTEM_ERROR_MASK 			0x4000
#define INTERFACE_ERROR_MASK		0x2000
#define INV_ANGLE_ERROR_MASK		0x1000

//Commands for read
#define READ_STA_CMD_NOSAFETY		0x8000
#define READ_STA_CMD				0x8001
#define READ_ACTIV_STA_CMD			0x8011
#define READ_ANGLE_VAL_CMD			0x8021
#define READ_ANGLE_SPD_CMD			0x8031
#define READ_ANGLE_REV_CMD			0x8041
#define READ_TEMP_CMD				0x8051
#define READ_INTMODE_1				0x8061
#define READ_SIL					0x8071
#define READ_INTMODE_2				0x8081
#define READ_INTMODE_3				0x8091
#define READ_OFFSET_X				0x80A1
#define READ_OFFSET_Y				0x80B1
#define READ_SYNCH					0x80C1
#define READ_IFAB					0x80D1
#define READ_INTMODE_4				0x80E1
#define READ_TEMP_COEFF				0x80F1
#define READ_RAW_X_CMD				0x8101
#define READ_RAW_Y_CMD				0x8111

//Commands for updated read
#define READ_UPD_STA_CMD			0x8401
#define READ_UPD_ANGLE_VAL_CMD		0x8421
#define READ_UPD_ANGLE_SPD_CMD		0x8431
#define READ_UPD_ANGLE_REV_CMD		0x8441

#define READ_BLOCK_CRC				0x8088

//Commands for write
#define WRITE_ACTIV_STA				0x0011
#define WIRTE_INTMODE_1				0x5061
#define WIRTE_SIL					0x5071
#define WIRTE_INTMODE_2				0x5081
#define WIRTE_INTMODE_3				0x5091
#define WIRTE_OFFSET_X				0x50A1
#define WIRTE_OFFSET_Y				0x50B1
#define WIRTE_SYNCH					0x50C1
#define WIRTE_IFAB					0x50D1
#define WIRTE_INTMODE_4				0x50E1
#define WIRTE_TEMP_COEFF			0x50F1

//mask to check if the command want the value in the register or the value in the update buffer
#define CHECK_CMD_UPDATE			0x0400

//values used for calculating the CRC
#define CRC_POLYNOMIAL				0x1D
#define CRC_SEED					0xFF
#define CRC_NUM_REGISTERS			8

//Values used to calculate 15 bit signed int sent by the sensor
#define DELETE_BIT_15				0x7FFF
#define CHANGE_UINT_TO_INT_15		32768
#define CHECK_BIT_14				0x4000

//values used to calculate 9 bit signed int sent by the sensor
#define DELETE_7BITS				0x01FF
#define CHANGE_UNIT_TO_INT_9		512
#define CHECK_BIT_9					0x0100

//values used to for final calculations of angle speed, revolutions, range and value
#define POW_2_15					32768.0
#define POW_2_7						128.0
#define ANGLE_360_VAL				360.0

//values used to calculate the temperature
#define TEMP_OFFSET					152.0
#define TEMP_DIV					2.776

#define GET_BIT_14_4				0x7FF0

//default speed of SPI transfer
#define SPEED					8000000

//delay for the update
#define DELAYuS 				10

//dummy variable used for receive. Each time this is sent, it is for the purposes of receiving using SPI transfer.
#define DUMMY 					0xFFFF

/**
 * This is used for keeping track of which register need to have its value changed, so that you don't need to read all the _registers each time the CRC needs to be updated
 */
//typedef enum registerIndex
//{
//	INT_MODE2_INDEX = 0x00,
//	INT_MODE3_INDEX = 0x01,
//	OFFSET_X_INDEX = 0x02,
//	OFFSET_Y_INDEX = 0x03,
//	SYNCH_INDEX = 0x04,
//	IFAB_INDEX = 0x05,
//	INT_MODE4_INDEX = 0x06,
//	TEMP_COEFF_INDEX = 0x07,
//	NO_INDEX = 0x08,
//}registerIndex;

/**
 * Error types from safety word
 */
enum errorTypes
{
	NO_ERROR = 0x00,
	SYSTEM_ERROR = 0x01,
	INTERFACE_ACCESS_ERROR = 0x02,
	INVALID_ANGLE_ERROR = 0x03,
	CRC_ERROR = 0xFF
};


class Tle5012b
{
public:
	//standard constructor
	Tle5012b();

	//constructor given own SPI Class
	Tle5012b(SPIClass &conf, uint16_t miso, uint16_t mosi, uint16_t sck);

	//standard deconstructor
	~Tle5012b();

	//the next four functions initialize the spi connections and the _chipselect and reads all the register values from 08 - 0F(first byte) and stores them that are needed to calculate the CRC
	errorTypes begin();
	errorTypes begin(uint32_t cs);
	errorTypes begin(SPIClass &conf, uint16_t miso, uint16_t mosi, uint16_t sck, uint32_t cs);
	errorTypes begin(SPIClass &conf, uint16_t miso, uint16_t mosi, uint16_t sck, uint32_t cs, SPISettings &settings);

	//ends the SPI connection
	void end();

	//general Function to read from the Tle5012b.
	errorTypes readFromSensor(uint16_t command, uint16_t &data);
	//used to read all the _registers used to calculate the CRC
	errorTypes readBlockCRC();
	//can be used to read 1 or more consecutive _registers, and the values of the various _registers are stored in data
	errorTypes readMoreRegisters(uint16_t command, uint16_t data[]);

	//reads functions for reading the various _registers in the Tle5012b.
	errorTypes readStatus(uint16_t &data);
	errorTypes readAngleValue(int16_t &data);
	errorTypes readAngleSpeed(int16_t &data);
	errorTypes readAngleRevolution(int16_t &data);

	errorTypes readUpdStatus(uint16_t &data);
	errorTypes readUpdAngleValue(int16_t &data);
	errorTypes readUpdAngleSpeed(int16_t &data);
	errorTypes readUpdAngleRevolution(int16_t &data);

	errorTypes readTemp(int16_t &data);
	errorTypes readRawX(int16_t &data);
	errorTypes readRawY(int16_t &data);

	errorTypes readActivationStatus(uint16_t &data);
	errorTypes readOffsetX(uint16_t &data);
	errorTypes readOffsetY(uint16_t &data);

	errorTypes readIntMode1(uint16_t &data);
	errorTypes readSIL(uint16_t &data);
	errorTypes readIntMode2(uint16_t &data);
	errorTypes readIntMode3(uint16_t &data);
	errorTypes readSynch(uint16_t &data);
	errorTypes readIFAB(uint16_t &data);
	errorTypes readIntMode4(uint16_t &data);
	errorTypes readTempCoeff(uint16_t &data);

	//Standard function to write to a register in the Tle5012b
	errorTypes writeToSensor(uint16_t command,uint16_t dataToWrite, bool changeCRC);

	//Write functions for writing to various _registers in the Tle5012b
	errorTypes writeActivationStatus(uint16_t dataToWrite);
	errorTypes writeIntMode1(uint16_t dataToWrite);
	errorTypes writeSIL(uint16_t dataToWrite);

	errorTypes writeIntMode2(uint16_t dataToWrite);
	errorTypes writeIntMode3(uint16_t dataToWrite);
	errorTypes writeOffsetX(uint16_t dataToWrite);
	errorTypes writeOffsetY(uint16_t dataToWrite);
	errorTypes writeSynch(uint16_t dataToWrite);
	errorTypes writeIFAB(uint16_t dataToWrite);
	errorTypes writeIntMode4(uint16_t dataToWrite);
	errorTypes writeTempCoeff(uint16_t dataToWrite);

	//Standard function used for updating the CRC
	errorTypes writeTempCoeffUpdate(uint16_t dataToWrite);

	//returns the angle speed
	errorTypes getAngleSpeed(double &angleSpeed);
	//returns the angleValue
	errorTypes getAngleValue(double &angleValue);
	//returns the number of revolutions done
	errorTypes getNumRevolutions(int16_t &numRev);

	//returns the updated angle speed
	errorTypes getUpdAngleSpeed(double &angleSpeed);
	//returns the updated angle value
	errorTypes getUpdAngleValue(double &angleVal);
	//returns the updated number of revolutions
	errorTypes getUpdNumRevolutions(int16_t &numRev);
	//return the temperature
	errorTypes getTemperature(double &temp);
	//returns the Angle Range
	errorTypes getAngleRange(double &angleRange);


private:

	SPIClass* _spiConnection;
	SPISettings _spiSetting;
	uint16_t _chipselect;
	uint16_t _masterout;
	uint16_t _masterin;
	uint16_t _clock;
	//keeps track of the values stored in the 8 _registers, for which the crc is calculated
	uint16_t _registers[CRC_NUM_REGISTERS];

	errorTypes regularCrcUpdate();

	//checks the safety by looking at the safety word and calculating the crc such that the data received is valid
	errorTypes checkSafety(uint16_t safety, uint16_t command, uint16_t* readreg, uint16_t length);

	//in case the safety word sends an error, this function is called so that the error bit is reset to 1.
	void resetSafety();

	//triggers an update in the register
	void triggerUpdate();

};

#endif
