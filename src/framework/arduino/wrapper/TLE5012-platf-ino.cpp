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

sensType_t TLE5012_Sens2Go   =  {8,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MOSI,PIN_SPI_SCK};          /**< TLE5012 Sensor2Go Kit with XMC1100 */
sensType_t TLE5012_breakOut  =  {UNUSED_PIN,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MOSI,PIN_SPI_SCK}; /**< TLE5012 breakout board removed from the Sensor2Go Kit */
sensType_t TLE5012_bulk      =  {UNUSED_PIN,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MOSI,PIN_SPI_SCK}; /**< TLE5012 bulk chip (see manual on how to connect the 3wire SPI */

Tle5012Ino::Tle5012Ino(void):Tle5012b()
{
	Tle5012b::timer = new TimerIno();
	Tle5012b::en == NULL;
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(SENS_TYPE.power, OUTPUT, GPIOIno::POSITIVE );
	}
	Tle5012b::sBus = new SPICIno();

}
Tle5012Ino::Tle5012Ino(SPIClass &bus):Tle5012b()
{
	Tle5012b::timer = new TimerIno();
	Tle5012b::en == NULL;
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(SENS_TYPE.power, OUTPUT, GPIOIno::POSITIVE );
	}
	Tle5012b::sBus = new SPICIno(bus,SENS_TYPE.csPin,SENS_TYPE.mMISO,SENS_TYPE.mMOSI,SENS_TYPE.mSCK);
}
Tle5012Ino::Tle5012Ino(SPIClass &bus, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin):Tle5012b()
{
	Tle5012b::timer = new TimerIno();
	Tle5012b::en == NULL;
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en = new GPIOIno(SENS_TYPE.power, OUTPUT, GPIOIno::POSITIVE );
	}
	Tle5012b::sBus = new SPICIno(bus,SENS_TYPE.csPin,misoPin,mosiPin,sckPin);
}

errorTypes Tle5012Ino::begin(void)
{
	begin(SENS_TYPE.csPin,TLE5012B_S0);
}
errorTypes Tle5012Ino::begin(uint8_t csPin, slaveNum slave)
{
	mEnabled = false;
	mSlave = slave;
	SENS_TYPE.csPin = csPin;
	Tle5012b::cs = new GPIOIno(SENS_TYPE.csPin, OUTPUT, GPIOIno::POSITIVE );
	// init helper libs
	Tle5012b::sBus->init();
	if (SENS_TYPE.power != UNUSED_PIN) {
		Tle5012b::en->init();
		Tle5012b::en->enable();
	}
	Tle5012b::cs->init();
	Tle5012b::cs->enable();
	Tle5012b::timer->init();
	// start sensor
	enableSensor();
	writeSlaveNumber(mSlave);
	mEnabled = true;
	return (readBlockCRC());
}


#endif /** TLE5012_FRAMEWORK **/
/** @} */