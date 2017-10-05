#include "Tle5012.h"
#include "Arduino.h"


Tle5012::Tle5012()
{
	spiConnection = &SPI;
}

Tle5012::Tle5012(SPIClass &conf, uint16_t miso, uint16_t mosi, uint16_t sck)
{
	masterout = mosi;
	masterin = miso;
	clock = sck;
	spiConnection = &conf;
}

Tle5012::~Tle5012()
{
	spiConnection->end();
}

errorTypes Tle5012::begin()
{
	spiConnection->begin();
	pinMode(chipselect,OUTPUT);
	digitalWrite(chipselect,HIGH);

	//To make sure that all the registers are storing values that are not corrupted, the function calculates the CRC based on the initial values of the registers and stores the values for future use

	return readBlockCRC();
}



errorTypes Tle5012::begin(SPISettings setting, uint32_t chipselectPin)
{
	spiSetting = setting;
	chipselect = chipselectPin;
	return begin();

}

errorTypes Tle5012::begin(uint32_t clockFrequency, uint8_t bitOrder, uint8_t dataMode, uint32_t chipselectPin)
{
	SPISettings spiSet = SPISettings(clockFrequency,bitOrder,dataMode);
	return begin(spiSet, chipselectPin);
}

/**
 * Gets the first byte of a 2 byte word
 */
uint8_t getFirstByte(uint16_t twoByteWord)
{
	return (uint8_t) (twoByteWord >> 8);
}

/**
 * Gets the second byte of the 2 byte word
 */
uint8_t getSecondByte(uint16_t twoByteWord)
{
	return (uint8_t) twoByteWord;
}

/**
 * Function for calculation the CRC.
 */
uint8_t crc8(uint8_t *data ,uint8_t length) {
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
uint8_t crcCalc(uint8_t* crcData, uint8_t length)
{
    return crc8(crcData, length);
}

/**
 * Triggers an update
 */
void Tle5012::triggerUpdate()
{
	digitalWrite(clock, LOW);
	digitalWrite(masterout, HIGH);
	digitalWrite(chipselect,LOW);
	delay(1);
	digitalWrite(chipselect,HIGH);
}


/**
 * After every transaction with the Tle5012, a safety word is returned to check the validity of the value received.
 * This is the structure of safety word, in which the numbers represent the bit position in 2 bytes.
 * 15 - indication of chip reset or watchdog overflow: 0 reset occured, 1 no reset
 * 14 - 0 System error, 1 No error
 * 13 - 0 Infterface access error, 1 No error
 * 12 - 0 Invalid angle value, 1 valid angle value
 * 11:8 - Sensor number response indicator, the sensor number bit is pulled low and other bits are high
 * 7:0 - CRC
 *
 * A CRC needs to be calculated using all the data sent and received (i.e. the command and the value return from the register, which is 4 bytes),
 * and needs to be checked with the CRC sent in the safety word.
 */

errorTypes Tle5012::checkSafety(uint16_t safety, uint16_t command, uint16_t* readreg, uint16_t length)
{
	errorTypes errorCheck ;

	if (!((safety) & SYSTEM_ERROR_MASK))
	{
		errorCheck = SYSTEM_ERROR;
		resetSafety();
	}

	else if (!((safety) & INTERFACE_ERROR_MASK))
	{
		errorCheck = INTERFACE_ACCESS_ERROR;
		resetSafety();
	}

	else if (!((safety) & INV_ANGLE_ERROR_MASK))
	{
		errorCheck = INVALID_ANGLE_ERROR;
		resetSafety();
	}

	else
	{
		uint16_t lengthOfTemp = length*2 + 2;
		uint8_t temp[lengthOfTemp];

		temp[0] = getFirstByte(command);
		temp[1] = getSecondByte(command);

		for (uint16_t i = 0; i<length; i++)
		{
			temp[2 + 2*i] = getFirstByte(readreg[i]);
			temp[2 + 2*i+1] = getSecondByte(readreg[i]);
		}

		uint8_t crcReceivedFinal = getSecondByte(safety);

		uint8_t crc = crcCalc(temp, lengthOfTemp);

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
//flushes out safety errors, that might have occured by reading the register without a safety word.
void Tle5012::resetSafety()
{
	triggerUpdate();

	digitalWrite(chipselect,LOW);

	delayMicroseconds(DELAYuS);
	spiConnection->beginTransaction(spiSetting);
	spiConnection->transfer16(READ_STA_CMD);
	spiConnection->transfer16(DUMMY);
	spiConnection->transfer16(DUMMY);
	spiConnection->endTransaction();
	delayMicroseconds(DELAYuS);

	digitalWrite(chipselect,HIGH);
}


/**
 * General read function for reading registers from the Tle5012.
 * Command[in]	-- the command for reading
 * data[out] 	-- where the data received from the registers will be stored
 *
 *
 * structure of command word, the numbers represent the bit position of the 2 byte command
 * 15 - 0 write, 1 read
 * 14:11 -  0000 for default operational access for addresses between 0x00 - 0x04, 1010 for configuration access for addresses between 0x05 - 0x11
 * 10 - 0 access to current value, 1 access to value in update buffer
 * 9:4 - access to 6 bit register address
 * 3:0 - 4 bit number of data words.
 */

errorTypes Tle5012::readFromSensor(uint16_t command, uint16_t &data)
{
	uint16_t safety = 0;

	if (command & CHECK_CMD_UPDATE)
	{
		triggerUpdate();
	}

	uint16_t readreg;

	digitalWrite(chipselect,LOW);

	delayMicroseconds(DELAYuS);
	spiConnection->beginTransaction(spiSetting);
	spiConnection->transfer16(command);
	readreg = spiConnection->transfer16(DUMMY);
	safety = spiConnection->transfer16(DUMMY);
	spiConnection->endTransaction();
	delayMicroseconds(DELAYuS);

	digitalWrite(chipselect,HIGH);

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
 * Reads the block of registers from addresses 08 - 0F in order to figure out the CRC.
 */
errorTypes Tle5012::readBlockCRC()
{
	uint16_t safety = 0;

	digitalWrite(chipselect,LOW);

	delayMicroseconds(DELAYuS);
	spiConnection->beginTransaction(spiSetting);
	spiConnection->transfer16(READ_BLOCK_CRC);

	for (uint8_t i=0; i < CRC_NUM_REGISTERS; i++)
	{
		registers[i] = spiConnection->transfer16(DUMMY);
	}

	safety = spiConnection->transfer16(DUMMY);
	spiConnection->endTransaction();
	delayMicroseconds(DELAYuS);

	digitalWrite(chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, READ_BLOCK_CRC, registers, CRC_NUM_REGISTERS);

	return checkError;

}

/**
 * used to read 1 or more than 1 consecutive registers
 */
errorTypes Tle5012::readMoreRegisters(uint16_t command, uint16_t data[])
{
	uint16_t lengthOfResponse = command & (0x000F);
	uint16_t safety = 0;

	digitalWrite(chipselect,LOW);

	delayMicroseconds(DELAYuS);
	spiConnection->beginTransaction(spiSetting);
	spiConnection->transfer16(command);

	for (uint8_t i=0; i < lengthOfResponse; i++)
	{
		data[i] = spiConnection->transfer16(DUMMY);
	}

	safety = spiConnection->transfer16(DUMMY);
	spiConnection->endTransaction();
	delayMicroseconds(DELAYuS);

	digitalWrite(chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, command, data, lengthOfResponse);

	return checkError;


}

errorTypes Tle5012::readStatus(uint16_t &data)
{
	return readFromSensor(READ_STA_CMD, data);
}

errorTypes Tle5012::readUpdStatus(uint16_t &data)
{
	return readFromSensor(READ_UPD_STA_CMD, data);
}


errorTypes Tle5012::readActivationStatus(uint16_t &data)
{
	return readFromSensor(READ_ACTIV_STA_CMD, data);
}

/**
 * The angle value is a 15 bit signed integer. However, the register returns 16 bits, so we need to do some bit arithmetic.
 */
errorTypes Tle5012::readAngleValue(int16_t &data)
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
errorTypes Tle5012::readAngleSpeed(int16_t &data)
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
errorTypes Tle5012::readAngleRevolution(int16_t &data)
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
errorTypes Tle5012::readTemp(int16_t &data)
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
errorTypes Tle5012::readRawX(int16_t &data)
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
errorTypes Tle5012::readRawY(int16_t &data)
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


errorTypes Tle5012::readUpdAngleValue(int16_t &data)
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

errorTypes Tle5012::readUpdAngleSpeed(int16_t &data)
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

errorTypes Tle5012::readUpdAngleRevolution(int16_t &data)
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

errorTypes Tle5012::readIntMode1(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_1, data);
}

errorTypes Tle5012::readSIL(uint16_t &data)
{
	return readFromSensor(READ_SIL, data);
}

/**
 * The next eight functions are used primarily for storing the parameters and control of how the sensor works.
 * The values stored in them are used to calculate the CRC, and their values are stored in the private component of the class, registers.
 */

errorTypes Tle5012::readIntMode2(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_2, data);
}

errorTypes Tle5012::readIntMode3(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_3, data);
}


errorTypes Tle5012::readOffsetX(uint16_t &data)
{
	return readFromSensor(READ_OFFSET_X, data);
}

errorTypes Tle5012::readOffsetY(uint16_t &data)
{
	return readFromSensor(READ_OFFSET_Y, data);
}

errorTypes Tle5012::readSynch(uint16_t &data)
{
	return readFromSensor(READ_SYNCH, data);
}

errorTypes Tle5012::readIFAB(uint16_t &data)
{
	return readFromSensor(READ_IFAB,data);
}

errorTypes Tle5012::readIntMode4(uint16_t &data)
{
	return readFromSensor(READ_INTMODE_4, data);
}

errorTypes Tle5012::readTempCoeff(uint16_t &data)
{
	return readFromSensor(READ_TEMP_COEFF, data);
}

/**
 * This function is called each time any register in the range 08 - 0F(first byte) is changed.
 * It calculates the new CRC based on the value of all the registers and then stores the value in 0F(second byte)
 */
errorTypes Tle5012::regularCrcUpdate()
{
	readBlockCRC();

	uint8_t temp[16];

	for (uint8_t i = 0; i < CRC_NUM_REGISTERS; i++)
	{
		temp[2*i] = getFirstByte(registers[i]);
		temp[(2*i)+1] = getSecondByte(registers[i]);
	}

	uint8_t crc = crcCalc(temp, 15);

	uint16_t firstTempByte = (uint16_t) temp[14];
	uint16_t secondTempByte = (uint16_t) crc;
	uint16_t valToSend = (firstTempByte << 8) | secondTempByte;

	registers[7] = valToSend;

	return writeTempCoeffUpdate(valToSend);
}

/**
 * General write function for writing registers from the Tle5012.
 * commmand[in]		-- the command to execute the write
 * dataToWrite[in]	-- the new data that will be written to the register
 * index[in]		-- the registerIndex helps figure out in which register the value changed, so that we don't need to read all the register again to calculate the CRC
 */
errorTypes Tle5012::writeToSensor(uint16_t command, uint16_t dataToWrite, bool changeCRC)
{
	uint16_t safety = 0;

	digitalWrite(chipselect,LOW);

	delayMicroseconds(DELAYuS);
	spiConnection->beginTransaction(spiSetting);
	spiConnection->transfer16(command);
	spiConnection->transfer16(dataToWrite);
	safety = spiConnection->transfer16(DUMMY);
	spiConnection->endTransaction();
	delayMicroseconds(DELAYuS);

	digitalWrite(chipselect,HIGH);

	uint16_t data[1] = {dataToWrite};

	errorTypes checkError = checkSafety(safety, command, data, 1);

	//if we write to a register, which changes the CRC.
	if (changeCRC)
	{
		checkError = regularCrcUpdate();
	}

	return checkError;
}


errorTypes Tle5012::writeActivationStatus(uint16_t dataToWrite)
{
	 return writeToSensor(WRITE_ACTIV_STA,dataToWrite, false);
}

errorTypes  Tle5012::writeIntMode1(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_INTMODE_1,dataToWrite, false);
}

errorTypes  Tle5012::writeSIL(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_SIL,dataToWrite, false);
}

/**
 * If the next eight function are called anytime and the values stored in the corresponding registers is changed, then a new CRC has to be calculated and stored in register 0F (second byte)
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
errorTypes  Tle5012::writeIntMode2(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_INTMODE_2,dataToWrite, true);
}

errorTypes  Tle5012::writeIntMode3(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_INTMODE_3,dataToWrite, true);
}

errorTypes  Tle5012::writeOffsetX(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_OFFSET_X,dataToWrite, true);
}

errorTypes  Tle5012::writeOffsetY(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_OFFSET_Y,dataToWrite, true);
}

errorTypes  Tle5012::writeSynch(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_SYNCH,dataToWrite, true);
}

errorTypes  Tle5012::writeIFAB(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_IFAB,dataToWrite, true);
}

errorTypes  Tle5012::writeIntMode4(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_INTMODE_4,dataToWrite, true);
}

errorTypes  Tle5012::writeTempCoeff(uint16_t dataToWrite)
{
	return writeToSensor(WIRTE_TEMP_COEFF,dataToWrite, true);
}

/**
 * This function is used in order to update the CRC in the register 0F(second byte)
 */
errorTypes  Tle5012::writeTempCoeffUpdate(uint16_t dataToWrite)
{
	uint16_t safety = 0;
	uint16_t readreg = 0;
	uint16_t data[1] = {dataToWrite};

	triggerUpdate();

	digitalWrite(chipselect,LOW);

	delayMicroseconds(DELAYuS);
	spiConnection->beginTransaction(spiSetting);
	spiConnection->transfer16(WIRTE_TEMP_COEFF);
	spiConnection->transfer16(dataToWrite);
	safety = spiConnection->transfer16(DUMMY);
	spiConnection->endTransaction();
	delayMicroseconds(DELAYuS);

	digitalWrite(chipselect,HIGH);

	errorTypes checkError = checkSafety(safety, WIRTE_TEMP_COEFF, data, 1);

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

double calculateAngleSpeed(double angRange, int16_t rawAngleSpeed, uint16_t firMD, uint16_t predictionVal)
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
errorTypes Tle5012::getAngleSpeed(double &finalAngleSpeed)
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


	finalAngleSpeed = calculateAngleSpeed(angleRange, rawAngleSpeed, firMDVal, intMode2Prediction);

	return NO_ERROR;

}

/**
 * returns the angle value
 */
errorTypes Tle5012::getAngleValue(double &angleValue)
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
errorTypes Tle5012::getNumRevolutions(int16_t &numRev)
{
	return readAngleRevolution(numRev);
}

errorTypes Tle5012::getUpdAngleSpeed(double &angleSpeed)
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

	angleSpeed = calculateAngleSpeed(angleRange, rawAngleSpeed, firMDVal, intMode2Prediction);

	return NO_ERROR;
}

errorTypes Tle5012::getUpdAngleValue(double &angleValue)
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

errorTypes Tle5012::getUpdNumRevolutions(int16_t &numRev)
{
	return readAngleRevolution(numRev);
}

errorTypes Tle5012::getTemperature(double &temperature)
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

errorTypes Tle5012::getAngleRange(double &angleRange)
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

