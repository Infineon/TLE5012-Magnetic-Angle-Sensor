/*!
 * \file        TLE5012b.cpp
 * \name        TLE5012b.cpp - core library for the TLx5012B angle sensor family.
 * \author      Infineon Technologies AG
 * \copyright   2019-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \ref         tle5012corelib
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "TLE5012b.hpp"
#include "Arduino.h"

using namespace tle5012;

//-----------------------------------------------------------------------------
// none_class functions

/*!
 * Gets the first byte of a 2 byte word
 * @param twoByteWord insert word of two bytes long
 * @return returns the first byte
 */
uint8_t getFirstByte(uint16_t twoByteWord)
{
    return ((uint8_t) (twoByteWord >> 8));
}

/*!
 * Gets the second byte of the 2 byte word
 * @param twoByteWord insert word of two bytes long
 * @return returns the second byte
 */
uint8_t getSecondByte(uint16_t twoByteWord)
{
    return ((uint8_t) twoByteWord);
}

/*!
 * Function for calculation the CRC.
 * @param data byte long data for CRC check
 * @param length length of data
 * @return returns 8bit CRC
 */
uint8_t crc8(uint8_t *data, uint8_t length)
{
    uint32_t crc;
    int16_t i, bit;

    crc = CRC_SEED;
    for (i = 0; i < length; i++)
    {
        crc ^= data[i];
        for (bit = 0; bit < 8; bit++)
        {
            if ((crc & 0x80) != 0)
            {
                crc <<= 1;
                crc ^= CRC_POLYNOMIAL;
            }else{
                crc <<= 1;
            }
        }
    }

    return ((~crc) & CRC_SEED);
}

/*!
 * Function for calculation of the CRC
 * @param crcData byte long data for CRC check
 * @param length length of data
 * @return runs crc8 calculation and returns CRC
 */
uint8_t crcCalc(uint8_t* crcData, uint8_t length)
{
    return (crc8(crcData, length));
}

/*!
 * Calculate the angle speed
 * @param angRange set angular range value
 * @param rawAngleSpeed raw speed value from read function
 * @param firMD
 * @param predictionVal
 * @return calculated angular speed
 */
double calculateAngleSpeed(double angRange, int16_t rawAngleSpeed, uint16_t firMD, uint16_t predictionVal)
{
    double microsecToSec = 0.000001;
    double firMDVal;
    switch ( firMD )
    {
        case 1:
            firMDVal = 42.7;
            break;
        case 2:
            firMDVal = 85.3;
            break;
        case 3:
            firMDVal = 170.6;
            break;
        default:
            firMDVal = 21.3;
    }

    double dividend = angRange * (double)rawAngleSpeed / (POW_2_15 * microsecToSec);
    double divisor = (double)predictionVal * firMDVal;
    double finalAngleSpeed = dividend / divisor;

    return ( finalAngleSpeed);
}
// end none class functions

//-----------------------------------------------------------------------------

Tle5012b::Tle5012b():reg(this)
{
    sBus = NULL;
    en = NULL;
    safetyWord = 0;
    mSlave = TLE5012B_S0;
}

Tle5012b::~Tle5012b()
{
    end();
    en = NULL;
    sBus = NULL;
}

void Tle5012b::end(void)
{
    disableSensor();
    sBus->deinit();
}

void Tle5012b::enableSensor()
{
    if (en != NULL) {
        en->enable();
    }
}

void Tle5012b::disableSensor()
{
    if (en != NULL) {
        en->disable();
    }
}

//-----------------------------------------------------------------------------
// begin generic data transfer functions
errorTypes Tle5012b::readFromSensor(uint16_t command, uint16_t &data, updTypes upd, safetyTypes safe)
{
    errorTypes checkError = NO_ERROR;

    _command[0] = READ_SENSOR | command | upd | safe;
    uint16_t _received[MAX_REGISTER_MEM] = {0};
    sBus->sendReceive(_command, 1, _received, 2);
    data = _received[0];
    if (safe == SAFE_high)
    {
        checkError = checkSafety(_received[1], _command[0], &_received[0], 1);
        if (checkError != NO_ERROR)
        {
            data = 0;
        }
    }
    return (checkError);
}

errorTypes Tle5012b::readMoreRegisters(uint16_t command, uint16_t data[], updTypes upd, safetyTypes safe)
{
    errorTypes checkError = NO_ERROR;

    _command[0] = READ_SENSOR | command | upd | safe;
    uint16_t _received[MAX_REGISTER_MEM] = {0};
    uint16_t _recDataLength = (_command[0] & (0x000F)); // Number of registers to read
    sBus->sendReceive(_command, 1, _received, _recDataLength + safe);
    memcpy(data, _received, (_recDataLength)* sizeof(uint16_t));
    if (safe == SAFE_high)
    {
        checkError = checkSafety(_received[_recDataLength], _command[0], _received, _recDataLength);
        if (checkError != NO_ERROR)
        {
            data = 0;
        }
    }
    return (checkError);
}

errorTypes Tle5012b::writeToSensor(uint16_t command, uint16_t dataToWrite, bool changeCRC)
{
    uint16_t safety = 0;
    _command[0] = WRITE_SENSOR | command | SAFE_high;
    _command[1] = dataToWrite;
    sBus->sendReceive(_command, 2, &safety, 1);

    errorTypes checkError = checkSafety(safety, _command[0], &_command[1], 1);
    //if we write to a register, which changes the CRC.
    if (changeCRC)
    {
        checkError = regularCrcUpdate();
    }
    return (checkError);
}

errorTypes Tle5012b::writeTempCoeffUpdate(uint16_t dataToWrite)
{
    uint16_t safety = 0;
    uint16_t readreg = 0;
    sBus->triggerUpdate();
    _command[0] = WRITE_SENSOR | reg.REG_TCO_Y | SAFE_high;
    _command[1] = dataToWrite;
    sBus->sendReceive(_command, 2, &safety, 1);
    errorTypes checkError = checkSafety(safety, _command[0], &_command[1], 1);
    //
    checkError = readStatus(readreg);
    if (readreg & 0x0008)
    {
        checkError = regularCrcUpdate();
    }
    return (checkError);
}
// end generic data transfer functions


//-----------------------------------------------------------------------------
// begin CRC functions
errorTypes Tle5012b::checkSafety(uint16_t safety, uint16_t command, uint16_t* readreg, uint16_t length)
{
    errorTypes errorCheck;
    safetyWord = safety;


    if (!((safety) & SYSTEM_ERROR_MASK))
    {
        errorCheck = SYSTEM_ERROR;
        // resetSafety();
    } else if (!((safety) & INTERFACE_ERROR_MASK))
    {
        errorCheck = INTERFACE_ACCESS_ERROR;
        // resetSafety();
    } else if (!((safety) & INV_ANGLE_ERROR_MASK))
    {
        errorCheck = INVALID_ANGLE_ERROR;
        // resetSafety();
    }else{
        resetSafety();
        const uint16_t lengthOfTemp = MAX_REGISTER_MEM * 2 + 2;
        uint8_t temp[lengthOfTemp];

        temp[0] = getFirstByte(command);
        temp[1] = getSecondByte(command);

        for (uint16_t i = 0; i < length; i++)
        {
            temp[2 + 2 * i] = getFirstByte(readreg[i]);
            temp[2 + 2 * i + 1] = getSecondByte(readreg[i]);
        }

        uint8_t crcReceivedFinal = getSecondByte(safety);
        uint8_t crc = crcCalc(temp, length * 2 + 2);

        if (crc == crcReceivedFinal)
        {
            errorCheck = NO_ERROR;
        }else{
            errorCheck = CRC_ERROR;
            resetSafety();
        }
    }
    return (errorCheck);
}

void Tle5012b::resetSafety()
{
    uint16_t command = READ_SENSOR + SAFE_high;
    uint16_t receive[4];
    sBus->triggerUpdate();
    sBus->sendReceive(&command, 1, receive, 3);
}

errorTypes Tle5012b::resetFirmware()
{
    uint16_t rawData = 0x401;
    errorTypes status = writeActivationStatus(rawData);
    return (status);
}

errorTypes Tle5012b::regularCrcUpdate()
{
    readBlockCRC();
    uint8_t temp[16];
    for (uint8_t i = 0; i < CRC_NUM_REGISTERS; i++)
    {
        temp[2 * i] = getFirstByte(_registers[i]);
        temp[(2 * i) + 1] = getSecondByte(_registers[i]);
    }
    uint8_t crc = crcCalc(temp, 15);
    uint16_t firstTempByte = (uint16_t) temp[14];
    uint16_t secondTempByte = (uint16_t) crc;
    uint16_t valToSend = (firstTempByte << 8) | secondTempByte;
    _registers[7] = valToSend;

    return (writeTempCoeffUpdate(valToSend));
}
// end CRC functions


//-----------------------------------------------------------------------------
// begin read functions
errorTypes Tle5012b::readBlockCRC()
{
    _command[0] = READ_BLOCK_CRC;
    _registers[CRC_NUM_REGISTERS + 1] = {0};  // Number of CRC Registers + 1 Register for Safety word
    sBus->sendReceive(_command, 1, _registers, CRC_NUM_REGISTERS+1);
    errorTypes checkError = checkSafety(_registers[8], READ_BLOCK_CRC, _registers, CRC_NUM_REGISTERS);
    resetSafety();
    return (checkError);
}

errorTypes Tle5012b::readStatus(uint16_t &data, updTypes upd, safetyTypes safe)
{
    return (readFromSensor(reg.REG_STAT, data, upd, safe));
}
errorTypes Tle5012b::readActivationStatus(uint16_t &data, updTypes upd, safetyTypes safe)
{
    return (readFromSensor(reg.REG_ACSTAT, data, upd, safe));
}
errorTypes Tle5012b::readSIL(uint16_t &data)
{
    return (readFromSensor(reg.REG_SIL, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readIntMode1(uint16_t &data)
{
    return (readFromSensor(reg.REG_MOD_1, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readIntMode2(uint16_t &data)
{
    return (readFromSensor(reg.REG_MOD_2, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readIntMode3(uint16_t &data)
{
    return (readFromSensor(reg.REG_MOD_3, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readIntMode4(uint16_t &data)
{
    return (readFromSensor(reg.REG_MOD_4, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readOffsetX(uint16_t &data)
{
    return (readFromSensor(reg.REG_OFFX, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readOffsetY(uint16_t &data)
{
    return (readFromSensor(reg.REG_OFFY, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readSynch(uint16_t &data)
{
    return (readFromSensor(reg.REG_SYNCH, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readIFAB(uint16_t &data)
{
    return (readFromSensor(reg.REG_IFAB, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readTempCoeff(uint16_t &data)
{
    return (readFromSensor(reg.REG_TCO_Y, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readTempDMag(uint16_t &data)
{
    return (readFromSensor(reg.REG_D_MAG, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readTempIIFCnt(uint16_t &data)
{
    return (readFromSensor(reg.REG_IIF_CNT, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readTempRaw(uint16_t &data)
{
    return (readFromSensor(reg.REG_T_RAW, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readTempT25(uint16_t &data)
{
    return (readFromSensor(reg.REG_T25O, data, UPD_low, SAFE_high));
}
errorTypes Tle5012b::readRawX(int16_t &data)
{
    uint16_t rawData = 0;
    errorTypes status = readFromSensor(reg.REG_ADC_X, rawData);
    if (status != NO_ERROR)
    {
        return (status);
    }
    data = rawData;
    return (status);
}
errorTypes Tle5012b::readRawY(int16_t &data)
{
    uint16_t rawData = 0;
    errorTypes status = readFromSensor(reg.REG_ADC_Y, rawData);
    if (status != NO_ERROR)
    {
        return (status);
    }
    data = rawData;
    return (status);
}
// end read functions


//-----------------------------------------------------------------------------
// begin get functions
errorTypes Tle5012b::getAngleValue(double &angleValue)
{
    int16_t rawAngleValue = 0;
    return (getAngleValue(angleValue, rawAngleValue, UPD_low, SAFE_high));
}
errorTypes Tle5012b::getAngleValue(double &angleValue, int16_t &rawAngleValue, updTypes upd, safetyTypes safe)
{
    uint16_t rawData = 0;
    errorTypes status = readFromSensor(reg.REG_AVAL, rawData, upd, safe);
    if (status != NO_ERROR)
    {
        return (status);
    }
    rawData = (rawData & (DELETE_BIT_15));
    //check if the value received is positive or negative
    if (rawData & CHECK_BIT_14)
    {
        rawData = rawData - CHANGE_UINT_TO_INT_15;
    }
    rawAngleValue = rawData;
    angleValue = (ANGLE_360_VAL / POW_2_15) * ((double) rawAngleValue);
    return (status);
}

errorTypes Tle5012b::getTemperature(double &temperature)
{
    int16_t rawTemp = 0;
    return (getTemperature(temperature, rawTemp, UPD_low, SAFE_high));
}
errorTypes Tle5012b::getTemperature(double &temperature, int16_t &rawTemp, updTypes upd, safetyTypes safe)
{
    uint16_t rawData = 0;
    errorTypes status = readFromSensor(reg.REG_FSYNC, rawData, upd, safe);
    if (status != NO_ERROR)
    {
        return (status);
    }
    rawData = (rawData & (DELETE_7BITS));
    //check if the value received is positive or negative
    if (rawData & CHECK_BIT_9)
    {
        rawData = rawData - CHANGE_UNIT_TO_INT_9;
    }
    rawTemp = rawData;
    temperature = (rawTemp + TEMP_OFFSET) / (TEMP_DIV);
    return (status);
}

errorTypes Tle5012b::getNumRevolutions(int16_t &numRev, updTypes upd, safetyTypes safe)
{
    uint16_t rawData = 0;
    errorTypes status = readFromSensor(reg.REG_AREV, rawData, upd, safe);
    if (status != NO_ERROR)
    {
        return (status);
    }
    rawData = (rawData & (DELETE_7BITS));
    //check if the value received is positive or negative
    if (rawData & CHECK_BIT_9)
    {
        rawData = rawData - CHANGE_UNIT_TO_INT_9;
    }
    numRev = rawData;
    return (status);
}

errorTypes Tle5012b::getAngleSpeed(double &finalAngleSpeed)
{
    int16_t rawSpeed = 0;
    return (getAngleSpeed(finalAngleSpeed, rawSpeed, UPD_low, SAFE_high));
}
errorTypes Tle5012b::getAngleSpeed(double &finalAngleSpeed, int16_t &rawSpeed, updTypes upd, safetyTypes safe)
{
    const int8_t numOfData = 0x7;
    uint16_t rawData[numOfData] = {};

    errorTypes status = readMoreRegisters(reg.REG_ASPD + numOfData, rawData, upd, safe);
    if (status != NO_ERROR)
    {
        return (status);
    }
    // Prepare raw speed
    rawSpeed = rawData[0];
    rawSpeed = (rawSpeed & (DELETE_BIT_15));
    // check if the value received is positive or negative
    if (rawSpeed & CHECK_BIT_14)
    {
        rawSpeed = rawSpeed - CHANGE_UINT_TO_INT_15;
    }

    // Prepare firMD
    uint16_t firMD = rawData[3];
    firMD >>= 14;

    // Prepare intMode2Prediction
    uint16_t intMode2Prediction = rawData[5];
    if (intMode2Prediction & 0x0004)
    {
        intMode2Prediction = 3;
    }else{
        intMode2Prediction = 2;
    }

    // Prepare angle range
    uint16_t rawAngleRange = rawData[5];
    rawAngleRange &= GET_BIT_14_4;
    rawAngleRange >>= 4;
    double angleRange = ANGLE_360_VAL * (POW_2_7 / (double) (rawAngleRange));

    //checks the value of fir_MD according to which the value in the calculation of the speed will be determined
    //according to if prediction is enabled then, the formula for speed changes
    finalAngleSpeed = calculateAngleSpeed(angleRange, rawSpeed, firMD, intMode2Prediction);

    return (status);
}

errorTypes Tle5012b::getAngleRange(double &angleRange)
{
    uint16_t rawData = 0;
    errorTypes status = readIntMode2(rawData);
    if (status != NO_ERROR)
    {
        return (status);
    }
    //Angle Range is stored in bytes 14 - 4, so you have to do this bit shifting to get the right value
    rawData &= GET_BIT_14_4;
    rawData >>= 4;
    angleRange = ANGLE_360_VAL * (POW_2_7 / (double) (rawData));
    return (status);
}
// end get functions


//-----------------------------------------------------------------------------
// begin write functions
errorTypes Tle5012b::writeIntMode2(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_MOD_2, dataToWrite, true));
}
errorTypes Tle5012b::writeIntMode3(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_MOD_3, dataToWrite, true));
}
errorTypes Tle5012b::writeOffsetX(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_OFFX, dataToWrite, true));
}
errorTypes Tle5012b::writeOffsetY(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_OFFY, dataToWrite, true));
}
errorTypes Tle5012b::writeSynch(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_SYNCH, dataToWrite, true));
}
errorTypes Tle5012b::writeIFAB(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_IFAB, dataToWrite, true));
}
errorTypes Tle5012b::writeIntMode4(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_MOD_4, dataToWrite, true));
}
errorTypes Tle5012b::writeTempCoeff(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_TCO_Y, dataToWrite, true));
}
errorTypes Tle5012b::writeActivationStatus(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_ACSTAT, dataToWrite, false));
}
errorTypes Tle5012b::writeIntMode1(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_MOD_1, dataToWrite, false));
}
errorTypes Tle5012b::writeSIL(uint16_t dataToWrite)
{
    return (writeToSensor(reg.REG_SIL, dataToWrite, false));
}
errorTypes Tle5012b::writeSlaveNumber(uint16_t dataToWrite)
{
    return(writeToSensor(WRITE_SENSOR, dataToWrite, false));
}
// end write functions

errorTypes Tle5012b::readRegMap()
{
    errorTypes status;

    sBus->triggerUpdate();
    for (int8_t i = 0; i < MAX_NUM_REG; i++)
    {
        status = readFromSensor(reg.addrFields[i].regAddress, reg.regMap[i], UPD_low, SAFE_high);
    }

    return (status);
}

errorTypes Tle5012b::writeInterfaceType(Reg::interfaceType_t iface)
{
    uint16_t rawData = 0;

    errorTypes status = readIntMode4(rawData);
    if (status != NO_ERROR) {
        return (status);
    }

    rawData &= ~(1UL << 0);
    rawData &= ~(1UL << 1);
    rawData = rawData | iface;
    status = writeIntMode4(rawData);

    return (status);
}

errorTypes Tle5012b::setCalibration(Reg::calibrationMode_t calMode)
{
    uint16_t rawData = 0;

    errorTypes status = readIntMode2(rawData);
    if (status != NO_ERROR) {
        return (status);
    }

    rawData &= ~(1UL << 0);
    rawData &= ~(1UL << 1);
    rawData = rawData | calMode;
    status = writeIntMode2(rawData);

    return (status);
}
// end register functions
