/*!
 * \file        TLE5012-ino.cpp
 * \name        TLE5012.ino.cpp - Arduino library for the Infineon Tle5012b magnetic angular sensor
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     2.0.0
 * \ref         tle5012ino
 * \brief       This is a Arduino platform file use Infineon's TLE5012B magnetic angular sensor
 * \details
 * 
 */


#include <TLE5012-ino.hpp>

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

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
