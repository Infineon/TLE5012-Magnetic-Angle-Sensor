/** 
 * @file        TLE5012-platf-ino.cpp
 * @brief       TLE5012 Arduino Hardware Platforms
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "TLE5012-platf-ino.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup tle5012inohw
 */

sensType_t TLE5012_Sens2Go   =  {8,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MISO,PIN_SPI_SCK};          /**< TLE5012 Sensor2Go Kit with XMC1100 */
sensType_t TLE5012_breakOut  =  {UNUSED_PIN,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MISO,PIN_SPI_SCK}; /**< TLE5012 breakout board removed from the Sensor2Go Kit */
sensType_t TLE5012_bulk      =  {UNUSED_PIN,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MISO,PIN_SPI_SCK}; /**< TLE5012 bulk chip (see manual on how to connect the 3wire SPI */

/**
 * @brief Construct a new Tle5012Ino::Tle5012Ino object
 * standard constructor with default SPI and pin assignment
 */
Tle5012Ino::Tle5012Ino(void):Tle5012b()
{
	Tle5012b::timer = new TimerIno();
	Tle5012b::en == NULL;
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(SENS_TYPE.power, OUTPUT, GPIOIno::POSITIVE );
	}
	Tle5012b::sBus = new SPICIno();
}

/**
 * @brief Construct a new Tle 5012Ino::Tle 5012Ino object
 * constructor with individual SPI assignment
 * @param bus          void pointer to the object representing the SPI class
 */
Tle5012Ino::Tle5012Ino(SPIClass &bus):Tle5012b()
{
	Tle5012b::timer = new TimerIno();
	Tle5012b::en == NULL;
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(SENS_TYPE.power, OUTPUT, GPIOIno::POSITIVE );
	}
	Tle5012b::sBus = new SPICIno(bus,SENS_TYPE.csPin,SENS_TYPE.mMISO,SENS_TYPE.mMOSI,SENS_TYPE.mSCK);
}

/**
 * @brief Construct a new Tle5012Ino::Tle5012Ino object
 * constructor with individual SPI and pin assignment
 * @param bus      void pointer to the object representing the SPI class
 * @param misoPin  MISO pin for the SPI/SSC interface
 * @param mosiPin  MOSI pin for the SPI/SSC interface
 * @param sckPin   system clock pin for external sensor clock setting
 */
Tle5012Ino::Tle5012Ino(SPIClass &bus, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin):Tle5012b()
{
	Tle5012b::timer = new TimerIno();
	Tle5012b::en == NULL;
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(SENS_TYPE.power, OUTPUT, GPIOIno::POSITIVE );
	}
	Tle5012b::sBus = new SPICIno(bus,SENS_TYPE.csPin,misoPin,mosiPin,sckPin);
}

/**
 * @brief begin method with default assignments for the SPI bus
 * and pin setting.
 * Use this if you have Sensor2go Kit or only one sensor used with Arduino default SPI
 * @return errorTypes 
 */
errorTypes Tle5012Ino::begin(void)
{
	return begin(SENS_TYPE.csPin,TLE5012B_S0);
}

/**
 * @brief begin method with individual cs and slave number assignment
 * Use this method if you connect up to four sensors on one SPI channel or
 * if you use a none standard cs (chipselect) pin
 * 
 * @param csPin    pin number of the CS pin
 * @param slave    slave offset setting for the SNR register, default is TLE5012B_S0
 * @return errorTypes 
 */
errorTypes Tle5012Ino::begin(uint8_t csPin, slaveNum slave)
{
	mSlave = slave;
	SENS_TYPE.csPin = csPin;
	Tle5012b::cs = new GPIOIno(SENS_TYPE.csPin, OUTPUT, GPIOIno::POSITIVE );
	// init helper libs
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en->init();
	}
	Tle5012b::timer->init();
	Tle5012b::cs->init();
	Tle5012b::sBus->init();
	// start sensor
	enableSensor();

	writeSlaveNumber(mSlave);
	return (readBlockCRC());
}


#endif /** TLE5012_FRAMEWORK **/
/** @} */