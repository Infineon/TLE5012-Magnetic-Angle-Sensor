/*
 * \file        spi3w-ard-ino.cpp
 * \brief       Arduino 3wire SPI cover
 * \author      Infineon Technologies AG
 * \version     4.0.0
 * \copyright   2020-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#include "spi3w-ino.hpp"
#include "pal-pin-types.hpp"

#if (SPI3W_INO == SPI3W_ARD)

using namespace tle5012;

/**
 * @addtogroup arduinoPal
 * @{
 *
 * @brief Arduino SPIClass extension to use 3wire SSC SPI interfaces
 */

/**
 * @brief Construct a new SPIClass3W::SPIClass3W object
 *
 */
SPIClass3W::SPIClass3W(uint8_t spiNum):SPIClass()
{
    this->mCS = PIN_SPI_SS;
    this->mMISO = PIN_SPI_MISO;
    this->mMOSI = PIN_SPI_MOSI;
    this->mSCK = PIN_SPI_SCK;
    this->mSpiNum = spiNum;
}

/**
 * @brief Destroy the SPIClass3W::SPIClass3W object
 *
 */
SPIClass3W::~SPIClass3W()
{
}

/*!
 * @brief New for fetching SPI parameter
 *
 * @param miso [in] pin number for miso, on sensor2go boards the same than mosi
 * @param mosi [in] pin number for mosi, on sensor2go boards the same than miso
 * @param sck [in] the system clock pin for external clock driver
 * @param cs [in] chip select pin, up to four different cs pins can be used together with the slave number
 */
void SPIClass3W::begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs)
{
    setCSPin(cs);
    this->mMOSI = mosi;
    this->mMISO = miso;
    this->mSCK = sck;
    pinMode(this->mCS,OUTPUT);
    digitalWrite(this->mCS, HIGH);
    SPIClass::begin();
}

/*!
 * @brief Set the chip select pin. This function is needed if more than one
 * sensor is in the SPI bus
 *
 * @param cs [in] Pin number of the sensors chip select
 */
void SPIClass3W::setCSPin(uint8_t cs)
{
    this->mCS = cs;
}

/*!
 * @brief Main SPI three wire communication functions for sending and receiving data
 *
 * @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
 * @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
 * @param received_data pointer to data structure buffer for the read data
 * @param size_of_received_data size of data words to be read
 */
void SPIClass3W::sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
{
    uint32_t data_index = 0;
    //send via TX
    digitalWrite(this->mCS, LOW);
    pinMode(this->mMISO,INPUT);
    pinMode(this->mMOSI,OUTPUT);
    beginTransaction(SPISettings(SPEED,MSBFIRST,SPI_MODE1));

    for(data_index = 0; data_index < size_of_sent_data; data_index++)
    {
        received_data[0] = transfer16(sent_data[data_index]);
    }

    // receive via RX
    pinMode(this->mMISO,OUTPUT);
    pinMode(this->mMOSI,INPUT);
    delayMicroseconds(5);

    for(data_index = 0; data_index < size_of_received_data; data_index++)
    {
        received_data[data_index] = transfer16(0x0000);
    }

    endTransaction();
    digitalWrite(this->mCS, HIGH);
}

/** @} */

#endif /* SPI3W_INO */
