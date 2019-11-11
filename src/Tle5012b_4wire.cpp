/**
 * Tle5012b_4wire.cpp - Library for Arduino for the Tle5012b_4wire angle sensor.
 *
 * The Tle5012b_4wire is a pre-calibrated 360° angle sensor that detects the orientation 
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

#include "Tle5012b_4wire.h"
#include "Arduino.h"


Tle5012b_4wire::Tle5012b_4wire()
{
	_spiConnection = &SPI;
	_spiSetting = SPISettings(SPEED,MSBFIRST,SPI_MODE1);
	_chipselect = SS;
	_masterout = MOSI;
	_masterin = MISO;
	_clock = SCK;
}

Tle5012b_4wire::~Tle5012b_4wire()
{
	_spiConnection->end();
}

errorTypes Tle5012b_4wire::begin()
{
	return begin(SPI, _masterin, _masterout, _clock, _chipselect, _spiSetting);
}


errorTypes Tle5012b_4wire::begin(uint32_t cs)
{
	return begin(SPI, _masterin, _masterout, _clock, cs, _spiSetting);
}

errorTypes Tle5012b_4wire::begin(SPIClass &conf, uint16_t miso, uint16_t mosi, uint16_t sck, uint32_t cs)
{
	return begin(conf, miso, mosi, sck, cs, _spiSetting);
}

errorTypes Tle5012b_4wire::begin(SPIClass &conf, uint16_t miso, uint16_t mosi, uint16_t sck, uint32_t cs, SPISettings &settings)
{
	_masterout = mosi;
	_masterin = miso;
	_clock = sck;
	_spiConnection = &conf;
	
	_chipselect = cs;
	_spiSetting = settings;

	_spiConnection->begin();
	pinMode(_chipselect,OUTPUT);
	digitalWrite(_chipselect,HIGH);
	
	//To make sure that all the _registers are storing values that are not corrupted, the function calculates the CRC based on the initial values of the _registers and stores the values for future use
	return readBlockCRC();
}

/**
 * Gets the first byte of a 2 byte word
 */
uint8_t Tle5012b_4wire::_getFirstByte(uint16_t twoByteWord)
{
	return (uint8_t) (twoByteWord >> 8);
}

/**
 * Gets the second byte of the 2 byte word
 */
uint8_t Tle5012b_4wire::_getSecondByte(uint16_t twoByteWord)
{
	return (uint8_t) twoByteWord;
}

/**
 * Function for calculation the CRC.
 */
uint8_t Tle5012b_4wire::_crc8(uint8_t *data ,uint8_t length) {
    uint32_t crc;
    int16_t i,bit;

    crc = CRC_SEED;
    for ( i=0 ; i<length ; i++ )
    {
        crc ^= data[i];
        for ( bit=0 ; bit<8 ; bit++)
        {
            if ( (crc & 0x80)!=0 )
            {
                crc <<= 1;
                crc ^= CRC_POLYNOMIAL;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return (~crc) & CRC_SEED;
}

/**
 * Function for calculation of the CRC
 */
uint8_t Tle5012b_4wire::_crcCalc(uint8_t* crcData, uint8_t length)
{
    return _crc8(crcData, length);
}

/**
 * Triggers an update
 */
void Tle5012b_4wire::triggerUpdate()
{
	digitalWrite(_clock, LOW);
	digitalWrite(_masterout, HIGH);
	digitalWrite(_chipselect,LOW);
	delayMicroseconds(DELAYuS);
	digitalWrite(_chipselect,HIGH);
}


/**
 * After every transaction with the Tle5012b_4wire, a safety word is returned to check the validity of the value received.
 * This is the structure of safety word, in which the numbers represent the bit position in 2 bytes.
 * 15 - indication of chip reset or watchdog overflow: 0 reset occurred, 1 no reset
 * 14 - 0 System error, 1 No error
 * 13 - 0 Infterface access error, 1 No error
 * 12 - 0 Invalid angle value, 1 valid angle value
 * 11:8 - Sensor number response indicator, the sensor number bit is pulled low and other bits are high
 * 7:0 - CRC
 *
 * A CRC needs to be calculated using all the data sent and received (i.e. the command and the value return from the register, which is 4 bytes),
 * and needs to be checked with the CRC sent in the safety word.
 */

errorTypes Tle5012b_4wire::checkSafety(uint16_t safety, uint16_t command, uint16_t* readreg, uint16_t length)
{
	errorTypes errorCheck ;

	if (!((safety) & SYSTEM_ERROR_MASK))
	{
		errorCheck = SYSTEM_ERROR;
	}

	else if (!((safety) & INTERFACE_ERROR_MASK))
	{
		errorCheck = INTERFACE_ACCESS_ERROR;
	}

	else if (!((safety) & INV_ANGLE_ERROR_MASK))
	{
		errorCheck = INVALID_ANGLE_ERROR;
	}

	else
	{
		uint16_t lengthOfTemp = length*2 + 2;
		uint8_t temp[lengthOfTemp];

		temp[0] = _getFirstByte(command);
		temp[1] = _getSecondByte(command);

		for (uint16_t i = 0; i<length; i++)
		{
			temp[2 + 2*i] = _getFirstByte(readreg[i]);
			temp[2 + 2*i+1] = _getSecondByte(readreg[i]);
		}

		uint8_t crcReceivedFinal = _getSecondByte(safety);

		uint8_t crc = _crcCalc(temp, lengthOfTemp);

		if (crc == crcReceivedFinal)
		{
			errorCheck = NO_ERROR;
		}
		else
		{
			errorCheck = CRC_ERROR;
			resetSafety();
		}
	}

	return errorCheck;
}

//when an error occurs in the safety word, the error bit remains 0(error), until the status register is read again.
//flushes out safety errors, that might have occurred by reading the register without a safety word.
void Tle5012b_4wire::resetSafety()
{
	triggerUpdate();

	digitalWrite(_chipselect,LOW);

	_spiConnection->beginTransaction(_spiSetting);
	_spiConnection->transfer16(READ_STA_CMD);
	_spiConnection->transfer16(DUMMY);
	_spiConnection->transfer16(DUMMY);
	_spiConnection->endTransaction();
	
	digitalWrite(_chipselect,HIGH);
}


/**
 * General read function for reading _registers from the Tle5012b_4wire.
 * Command[in]	-- the command for reading
 * data[out] 	-- where the data received from the _registers will be stored
 *
 *
 * structure of command word, the numbers represent the bit position of the 2 byte command
 * 15 - 0 write, 1 read
 * 14:11 -  0000 for default operational access for addresses between 0x00 - 0x04, 1010 for configuration access for addresses between 0x05 - 0x11
 * 10 - 0 access to current value, 1 access to value in update buffer
 * 9:4 - access to 6 bit register address
 * 3:0 - 4 bit number of data words.
 */

errorTypes Tle5012b_4wire::readFromSensor(uint16_t command, uint16_t &data)
{
	uint16_t safety = 0;
	uint16_t readreg;

	digitalWrite(_chipselect,LOW);

	_spiConnection->beginTransaction(_spiSetting);
	_spiConnection->transfer16(command);
	readreg = _spiConnection->transfer16(DUMMY);
	safety = _spiConnection->transfer16(DUMMY);
	_spiConnection->endTransaction();

	digitalWrite(_chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, command, &readreg, 1);

	if (checkError != NO_ERROR)
	{
		data = 0;
		return checkError;
	}
	else
	{
		data = readreg;
		return NO_ERROR;
	}

}

/**
 * Reads the block of _registers from addresses 08 - 0F in order to figure out the CRC.
 */
errorTypes Tle5012b_4wire::readBlockCRC()
{
	uint16_t safety = 0;

	digitalWrite(_chipselect,LOW);

	_spiConnection->beginTransaction(_spiSetting);
	_spiConnection->transfer16(READ_BLOCK_CRC);

	for (uint8_t i=0; i < CRC_NUM_REGISTERS; i++)
	{
		_registers[i] = _spiConnection->transfer16(DUMMY);
	}

	safety = _spiConnection->transfer16(DUMMY);
	_spiConnection->endTransaction();

	digitalWrite(_chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, READ_BLOCK_CRC, _registers, CRC_NUM_REGISTERS);

	return checkError;

}

/**
 * used to read 1 or more than 1 consecutive _registers
 */
errorTypes Tle5012b_4wire::readMoreRegisters(uint16_t command, uint16_t data[])
{
	uint16_t lengthOfResponse = command & (0x000F);
	uint16_t safety = 0;

	digitalWrite(_chipselect,LOW);

	_spiConnection->beginTransaction(_spiSetting);
	_spiConnection->transfer16(command);

	for (uint8_t i=0; i < lengthOfResponse; i++)
	{
		data[i] = _spiConnection->transfer16(DUMMY);
	}

	safety = _spiConnection->transfer16(DUMMY);
	_spiConnection->endTransaction();

	digitalWrite(_chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, command, data, lengthOfResponse);

	return checkError;


}

errorTypes Tle5012b_4wire::readStatus(uint16_t &data)
{
	return readFromSensor(READ_STA_CMD, data);
}

errorTypes Tle5012b_4wire::readUpdStatus(uint16_t &data)
{
	return readFromSensor(READ_UPD_STA_CMD, data);
}


errorTypes Tle5012b_4wire::readActivationStatus(uint16_t &data)
{
	return readFromSensor(READ_ACTIV_STA_CMD, data);
}

/**
 * The angle value is a 15 bit signed integer. However, the register returns 16 bits, so we need to do some bit arithmetic.
 */
errorTypes Tle5012b_4wire::readAngleValue(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status = readFromSensor(READ_ANGLE_VAL_CMD, rawData);

	if (status != NO_ERROR)
	{
		return status;
	}

	rawData = (rawData & (DELETE_BIT_15));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_14)
	{
		rawData = rawData - CHANGE_UINT_TO_INT_15;
	}

	data = rawData;

	return NO_ERROR;
}

/**
 * The angle speed is a 15 bit signed integer. However, the register returns 16 bits, so we need to do some bit arithmetic.
 */
errorTypes Tle5012b_4wire::readAngleSpeed(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status =  readFromSensor(READ_ANGLE_SPD_CMD, rawData);

	if (status != NO_ERROR)
	{
		return status;
	}

	rawData = (rawData & (DELETE_BIT_15));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_14)
	{
		rawData = rawData - CHANGE_UINT_TO_INT_15;
	}

	data = rawData;

	return NO_ERROR;
}

/**
 * The angle value is a 9 bit signed integer. However, the register returns 16 bits, so we need to do some bit arithmetic.
 */
errorTypes Tle5012b_4wire::readAngleRevolution(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status =	readFromSensor(READ_ANGLE_REV_CMD, rawData);
	if (status != NO_ERROR)
	{
		return status;
	}

	rawData = (rawData & (DELETE_7BITS));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_9)
	{
		rawData = rawData - CHANGE_UNIT_TO_INT_9;
	}

	data = rawData;

	return NO_ERROR;
}

/**
 * The angle value is a 9 bit signed integer. However, the register returns 16 bits, so we need to do some bit arithmetic.
 */
errorTypes Tle5012b_4wire::readTemp(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status =	readFromSensor(READ_TEMP_CMD, rawData);

	if (status != NO_ERROR)
	{
		data = 0;
		return status;
	}

	rawData = (rawData & (DELETE_7BITS));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_9)
	{
		rawData = rawData - CHANGE_UNIT_TO_INT_9;
	}

	data = rawData;

	return NO_ERROR;
}

/**
 * The rawX value is signed 16 bit value
 */
errorTypes Tle5012b_4wire::readRawX(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status =	readFromSensor(READ_RAW_X_CMD, rawData);

	if (status != NO_ERROR)
	{
		data = 0;
		return status;
	}

	data = rawData;

	return NO_ERROR;
}

/**
 * The rawY is a signed 16 bit value
 */
errorTypes Tle5012b_4wire::readRawY(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status =	readFromSensor(READ_RAW_Y_CMD, rawData);

	if (status != NO_ERROR)
	{
		data = 0;
		return status;
	}

	data = rawData;

	return NO_ERROR;
}


errorTypes Tle5012b_4wire::readUpdAngleValue(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status = readFromSensor(READ_UPD_ANGLE_VAL_CMD, rawData);

	if (status != NO_ERROR)
	{
		data = 0;
		return status;
	}

	rawData = (rawData & (DELETE_BIT_15));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_14)
	{
		rawData = rawData - CHANGE_UINT_TO_INT_15;
	}

	data = rawData;

	return NO_ERROR;
}

errorTypes Tle5012b_4wire::readUpdAngleSpeed(int16_t &data)
{
	uint16_t rawData = 0;
	errorTypes status =  readFromSensor(READ_UPD_ANGLE_SPD_CMD, rawData);
	if (status != NO_ERROR)
	{
		data = 0;
		return status;
	}

	rawData = (rawData & (DELETE_BIT_15));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_14)
	{
		rawData = rawData - CHANGE_UINT_TO_INT_15;
	}

	data = rawData;

	return NO_ERROR;
}

errorTypes Tle5012b_4wire::readUpdAngleRevolution(int16_t &data)
{
	uint16_t rawData = 0;

	errorTypes status = readFromSensor(READ_UPD_ANGLE_REV_CMD, rawData);

	if (status != NO_ERROR)
	{
		data = 0;
		return status;
	}

	rawData = (rawData & (DELETE_7BITS));

	//check if the value received is positive or negative
	if (rawData & CHECK_BIT_9)
	{
		rawData = rawData - CHANGE_UNIT_TO_INT_9;
	}

	data = rawData;

	return NO_ERROR;
}

errorTypes Tle5012b_4wire::readIntMode1(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_1, data);
}

errorTypes Tle5012b_4wire::readSIL(uint16_t &data)
{
	return readFromSensor(READ_SIL, data);
}

/**
 * The next eight functions are used primarily for storing the parameters and control of how the sensor works.
 * The values stored in them are used to calculate the CRC, and their values are stored in the private component of the class, _registers.
 */

errorTypes Tle5012b_4wire::readIntMode2(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_2, data);
}

errorTypes Tle5012b_4wire::readIntMode3(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_3, data);
}


errorTypes Tle5012b_4wire::readOffsetX(uint16_t &data)
{
	return readFromSensor(READ_OFFSET_X, data);
}

errorTypes Tle5012b_4wire::readOffsetY(uint16_t &data)
{
	return readFromSensor(READ_OFFSET_Y, data);
}

errorTypes Tle5012b_4wire::readSynch(uint16_t &data)
{
	return readFromSensor(READ_SYNCH, data);
}

errorTypes Tle5012b_4wire::readIFAB(uint16_t &data)
{
	return readFromSensor(READ_IFAB,data);
}

errorTypes Tle5012b_4wire::readIntMode4(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_4, data);
}

errorTypes Tle5012b_4wire::readTempCoeff(uint16_t &data)
{
	return readFromSensor(READ_TEMP_COEFF, data);
}

/**
 * This function is called each time any register in the range 08 - 0F(first byte) is changed.
 * It calculates the new CRC based on the value of all the _registers and then stores the value in 0F(second byte)
 */
errorTypes Tle5012b_4wire::regularCrcUpdate()
{
	readBlockCRC();

	uint8_t temp[16];

	for (uint8_t i = 0; i < CRC_NUM_REGISTERS; i++)
	{
		temp[2*i] = _getFirstByte(_registers[i]);
		temp[(2*i)+1] = _getSecondByte(_registers[i]);
	}

	uint8_t crc = _crcCalc(temp, 15);

	uint16_t firstTempByte = (uint16_t) temp[14];
	uint16_t secondTempByte = (uint16_t) crc;
	uint16_t valToSend = (firstTempByte << 8) | secondTempByte;

	_registers[7] = valToSend;

	return writeTempCoeffUpdate(valToSend);
}

/**
 * General write function for writing _registers from the Tle5012b_4wire.
 * command[in]		-- the command to execute the write
 * dataToWrite[in]	-- the new data that will be written to the register
 * index[in]		-- the registerIndex helps figure out in which register the value changed, so that we don't need to read all the register again to calculate the CRC
 */
errorTypes Tle5012b_4wire::writeToSensor(uint16_t command, uint16_t dataToWrite, bool changeCRC)
{
	uint16_t safety = 0;

	digitalWrite(_chipselect,LOW);

	_spiConnection->beginTransaction(_spiSetting);
	_spiConnection->transfer16(command);
	_spiConnection->transfer16(dataToWrite);
	safety = _spiConnection->transfer16(DUMMY);
	_spiConnection->endTransaction();

	digitalWrite(_chipselect,HIGH);

	uint16_t data[1] = {dataToWrite};

	errorTypes checkError = checkSafety(safety, command, data, 1);

	//if we write to a register, which changes the CRC.
	if (changeCRC)
	{
		checkError = regularCrcUpdate();
	}

	return checkError;
}


errorTypes Tle5012b_4wire::writeActivationStatus(uint16_t dataToWrite)
{
	 return writeToSensor(WRITE_ACTIV_STA,dataToWrite, false);
}

errorTypes  Tle5012b_4wire::writeIntMode1(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_INTMODE_1,dataToWrite, false);
}

errorTypes  Tle5012b_4wire::writeSIL(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_SIL,dataToWrite, false);
}

/**
 * If the next eight function are called anytime and the values stored in the corresponding _registers is changed, then a new CRC has to be calculated and stored in register 0F (second byte)
 */

/**
 * The Interface Mode 2 register stores the following values
 	- angle range from bit 14 - 4, where 0x200 is 90° (-45° to 45°) and 0x80 is 360°(-180° to 180°). The calculation is based on the formula (360 * (2^7 / 2^9))
 	- angle direction in bit 3, 0 =  counterclockwise rotation of magnet and 1 = clockwise rotation of magnet
 	- prediction in bit 2, where 0 = prediction disabled and 1 = prediction enabled
 	- Autocalibration mode in bits 1 - 0, where 00 = no autocalibration mode, 01 = autocalibartion mode 1, 10 = autocalibration mode 2, 11 = autocalibration mode 3

 	Be careful when changing the values of this register. If the angle range is changed to 0x80 and the angle value exceeds the valid range of -45 to 45, you will get a DSPU overflow error, and the safety word will show a system error.
 	Furthermore, autocalibration only works with the angle range of 0x80, so if you change the angle range in autocalibration mode, then an error will occur.
 */
errorTypes  Tle5012b_4wire::writeIntMode2(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_INTMODE_2,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeIntMode3(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_INTMODE_3,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeOffsetX(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_OFFSET_X,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeOffsetY(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_OFFSET_Y,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeSynch(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_SYNCH,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeIFAB(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_IFAB,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeIntMode4(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_INTMODE_4,dataToWrite, true);
}

errorTypes  Tle5012b_4wire::writeTempCoeff(uint16_t dataToWrite)
{
	return writeToSensor(WRITE_TEMP_COEFF,dataToWrite, true);
}

/**
 * This function is used in order to update the CRC in the register 0F(second byte)
 */
errorTypes Tle5012b_4wire::writeTempCoeffUpdate(uint16_t dataToWrite)
{
	uint16_t safety = 0;
	uint16_t readreg = 0;
	uint16_t data[1] = {dataToWrite};

	digitalWrite(_chipselect,LOW);

	_spiConnection->beginTransaction(_spiSetting);
	_spiConnection->transfer16(WRITE_TEMP_COEFF);
	_spiConnection->transfer16(dataToWrite);
	safety = _spiConnection->transfer16(DUMMY);
	_spiConnection->endTransaction();

	digitalWrite(_chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, WRITE_TEMP_COEFF, data, 1);

	checkError = readStatus(readreg);

	if (readreg & 0x0008)
	{
		checkError = regularCrcUpdate();
	}

	return checkError;
}

/**
 * The formula to calculate the Angle Speed as per the data sheet.
 */

double Tle5012b_4wire::_calculateAngleSpeed(double angRange, int16_t rawAngleSpeed, uint16_t firMD, uint16_t predictionVal)
{
	double finalAngleSpeed;
	double microsecToSec = 0.000001;
	double firMDVal;

	if (firMD == 1)
	{
		firMDVal = 42.7;
	}

	else if (firMD == 0)
	{
		firMDVal = 21.3;
	}

	else if (firMD == 2)
	{
		firMDVal = 85.3;
	}

	else if (firMD == 3)
	{
		firMDVal = 170.6;
	}

	else
	{
		firMDVal = 0;
	}

	finalAngleSpeed = ((angRange / POW_2_15) * ((double)rawAngleSpeed)) / (((double)predictionVal) * firMDVal * microsecToSec);

	return finalAngleSpeed;

}

/**
 * returns the angle speed
 */
errorTypes Tle5012b_4wire::getAngleSpeed(double &finalAngleSpeed)
{
	int16_t rawAngleSpeed = 0;
	double angleRange = 0.0;
	uint16_t firMDVal = 0;
	uint16_t intMode2Prediction = 0;

	errorTypes checkError = readAngleSpeed(rawAngleSpeed);

	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	checkError = getAngleRange(angleRange);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	//checks the value of fir_MD according to which the value in the calculation of the speed will be determined
	checkError = readIntMode1(firMDVal);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}
	firMDVal >>= 14;

	//according to if prediction is enabled then, the formula for speed changes
	checkError = readIntMode2(intMode2Prediction);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	if(intMode2Prediction & 0x0004)
	{
		intMode2Prediction = 3;
	}

	else
	{
		intMode2Prediction = 2;
	}


	finalAngleSpeed = _calculateAngleSpeed(angleRange, rawAngleSpeed, firMDVal, intMode2Prediction);

	return NO_ERROR;

}

/**
 * returns the angle value
 */
errorTypes Tle5012b_4wire::getAngleValue(double &angleValue)
{
	int16_t rawAnglevalue = 0;
	errorTypes checkError = readAngleValue(rawAnglevalue);

	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	angleValue = (ANGLE_360_VAL / POW_2_15) * ((double)rawAnglevalue);

	return NO_ERROR;
}

/**
 * returns the number of revolutions
 */
errorTypes Tle5012b_4wire::getNumRevolutions(int16_t &numRev)
{
	return readAngleRevolution(numRev);
}

errorTypes Tle5012b_4wire::getUpdAngleSpeed(double &angleSpeed)
{
	int16_t rawAngleSpeed = 0;
	double angleRange = 0.0;
	uint16_t firMDVal = 0;
	uint16_t intMode2Prediction = 0;

	errorTypes checkError = readUpdAngleSpeed(rawAngleSpeed);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	checkError = getAngleRange(angleRange);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	checkError = readIntMode1(firMDVal);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	checkError = readIntMode2(intMode2Prediction);
	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	if(intMode2Prediction & 0x0004)
	{
		intMode2Prediction = 3;
	}

	else
	{
		intMode2Prediction = 2;
	}

	angleSpeed = _calculateAngleSpeed(angleRange, rawAngleSpeed, firMDVal, intMode2Prediction);

	return NO_ERROR;
}

errorTypes Tle5012b_4wire::getUpdAngleValue(double &angleValue)
{
	int16_t rawAnglevalue = 0;
	errorTypes checkError = readUpdAngleValue(rawAnglevalue);

	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	angleValue = (ANGLE_360_VAL / POW_2_15) * ((double)rawAnglevalue);

	return NO_ERROR;
}

errorTypes Tle5012b_4wire::getUpdNumRevolutions(int16_t &numRev)
{
	return readUpdAngleRevolution(numRev);
}

errorTypes Tle5012b_4wire::getTemperature(double &temperature)
{
	int16_t rawTemp = 0;
	errorTypes checkError = readTemp(rawTemp);

	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	temperature = (rawTemp + TEMP_OFFSET) / (TEMP_DIV);

	return NO_ERROR;
}

errorTypes Tle5012b_4wire::getAngleRange(double &angleRange)
{
	uint16_t rawData = 0;
	errorTypes checkError = readIntMode2(rawData);

	if (checkError != NO_ERROR)
	{
		return checkError;
	}

	//Angle Range is stored in bytes 14 - 4, so you have to do this bit shifting to get the right value
	rawData &=  GET_BIT_14_4;
	rawData >>= 4;

	angleRange = ANGLE_360_VAL * (POW_2_7 / (double)(rawData));

	return NO_ERROR;
}

