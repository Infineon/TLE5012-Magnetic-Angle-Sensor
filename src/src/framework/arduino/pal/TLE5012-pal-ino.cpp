/** 
 * @file        TLE5012-pal-ino.cpp
 * @brief       TLE5012 Arduino Hardware Platforms
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "TLE5012-pal-ino.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup tle5012inohw
 */

/**
 * Construct a new Tle5012Ino::Tle5012Ino object with default SPI and pin assignment.
 * Use this if:
 * - you have TLE5012B Sensor2go kit (all types)
 * - attached the breakout board on the default SPI of your MCU
 * - attached a bulk chip with the SSC interface to the default SPI of your MCU
 */
Tle5012Ino::Tle5012Ino():Tle5012b()
{
	mSlave = TLE5012B_S0;
	Tle5012b::en = NULL;
	Tle5012b::sBus = new SPICIno();
}

/**
 * Construct a new Tle5012Ino::Tle5012Ino object with individual SPI and pin assignment
 * Use this if:
 * - you use different SPI channels than default
 * - you use a software SPI with different pin settings than default
 * 
 * @param bus      void pointer to the object representing the SPI class
 * @param misoPin  MISO pin for the SPI/SSC interface
 * @param mosiPin  MOSI pin for the SPI/SSC interface
 * @param sckPin   system clock pin for external sensor clock setting
 */
Tle5012Ino::Tle5012Ino(Tle5012b_SPI &bus, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin):Tle5012b()
{
	mSlave = TLE5012B_S0;
	Tle5012b::en = NULL;
	Tle5012b::sBus = new SPICIno(bus,PIN_SPI_SS,misoPin,mosiPin,sckPin);
}

/**
 * @brief begin method with default assignments for the SPI bus
 * and pin setting.
 * Use this if you have Sensor2go Kit or only one sensor used with Arduino default SPI
 * @return errorTypes 
 */
errorTypes Tle5012Ino::begin(void)
{
	return begin(PIN_SPI_SS,TLE5012B_S0);
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
	#if defined(UC_FAMILY) && (UC_FAMILY == XMC1 || UC_FAMILY == XMC4)
		#undef PIN_SPI_EN
		#define PIN_SPI_EN    8           /*!< TLE5012 Sensor2Go Kit has a switch on/off pin */
	#endif

	mSlave = slave;
	// init helper libs
	Tle5012b::sBus->init();
	if (PIN_SPI_EN != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(PIN_SPI_EN, OUTPUT, GPIOIno::POSITIVE);
		Tle5012b::en->init();
		delay(100);
	}
	// start sensor
	enableSensor();
	writeSlaveNumber(mSlave);

	// initial CRC check, should be = 0
	return (readBlockCRC());
}

#endif /** TLE5012_FRAMEWORK **/
/** @} */