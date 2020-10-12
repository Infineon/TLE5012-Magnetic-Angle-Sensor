/*!
 * \file        TLE5012-ino.cpp
 * \name        TLE5012.ino.cpp - Arduino library for the Infineon Tle5012 magnetic angular sensor
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

Tle5012Ino::Tle5012Ino(void):Tle5012()
{
	Tle5012::timer = new TimerIno();

	Tle5012::cs = new GPIOIno(TLE5012_PIN_CS1, OUTPUT, GPIOIno::POSITIVE );
	Tle5012::sBus = new SPICIno();

	Tle5012::en = new GPIOIno(TLE5012_PIN_EN, OUTPUT, GPIOIno::POSITIVE );
}

Tle5012Ino::Tle5012Ino(SPIClass &bus):Tle5012()
{
	Tle5012::timer = new TimerIno();


	Tle5012::cs = new GPIOIno(TLE5012_PIN_CS1, OUTPUT, GPIOIno::POSITIVE );
	Tle5012::sBus = new SPICIno(bus,csPin,MISO,MOSI,SCK);
	Tle5012::en = new GPIOIno(TLE5012_PIN_EN, OUTPUT, GPIOIno::POSITIVE );
}

Tle5012Ino::Tle5012Ino(SPIClass &bus, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin):Tle5012()
{
		Tle5012Ino(SPIClass &bus,);
}

errorTypes Tle5012Ino::begin(void)
{
	mEnabled = false;
	Tle5012::sBus->init();
	Tle5012::en->init();
	Tle5012::en->enable();
	Tle5012::cs->init();
	Tle5012::cs->enable();
	Tle5012::timer->init();
	mEnabled = true;
	init();
}
errorTypes begin(uint8_t csPin, slaveNum slave)
{

}

errorTypes Tle5012Ino::end(void)
{
	mEnabled = false;
	Tle5012::en->disable();
	Tle5012::cs->disable();
	Tle5012::timer->stop();
	Tle5012::sBus->deinit();
}

#endif /** TLE5012_FRAMEWORK **/
