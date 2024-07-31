/**
 * \file        tlx5012-arduino.cpp
 * \name        tlx5012-arduino.cpp - Arduino library for the Infineon TLx5012 magnetic angular sensor
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       This is a Arduino platform file use Infineon's TLE5012B magnetic angular sensor
 *
 * SPDX-License-Identifier: MIT
 */

#include "tlx5012-arduino.hpp"

using namespace tle5012;

/**
 * @addtogroup arduinoPal
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
    Tle5012b::mSlave = TLE5012B_S0;
    Tle5012b::sBus = new SPICIno();
}

/**
 * @brief Construct a new Tle5012Ino::Tle5012Ino object with chip select and sensor slave
 * Use this constructor if:
 * - you use more than one sensor with one SPI channel (up to four are possible)
 *
 * @param csPin    pin number of the CS pin
 * @param slave    optional sensor slave setting
 */
Tle5012Ino::Tle5012Ino(uint8_t csPin, slaveNum slave):Tle5012b()
{
    Tle5012b::mSlave = slave;
    Tle5012b::sBus = new SPICIno(csPin);
}

/**
 * Construct a new Tle5012Ino::Tle5012Ino object with individual SPI and pin assignment
 * Use this if:
 * - you use different SPI channels than default
 * - you use a software SPI with different pin settings than default
 *
 * @param bus      void pointer to the object representing the SPI class
 * @param csPin    pin number of the CS pin
 * @param misoPin  MISO pin for the SPI/SSC interface
 * @param mosiPin  MOSI pin for the SPI/SSC interface
 * @param sckPin   system clock pin for external sensor clock setting
 * @param slave    optional sensor slave setting
 */
Tle5012Ino::Tle5012Ino(SPIClass3W *bus, uint8_t csPin, uint8_t misoPin, uint8_t mosiPin, uint8_t sckPin, slaveNum slave):Tle5012b()
{
    Tle5012b::mSlave = slave;
    Tle5012b::sBus = new SPICIno(*bus,csPin,misoPin,mosiPin,sckPin);
}

/**
 * @brief begin method with default assignments for the SPI bus
 * and pin setting.
 * The EN pin is only available for the Sensor2go kit, therefore we only
 * set it in that case, otherwise it will be NULL.
 *
 * @return errorTypes
 */
errorTypes Tle5012Ino::begin(void)
{
    #if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
        #undef PIN_SPI_EN
        #define PIN_SPI_EN    8           /*!< TLE5012 Sensor2Go Kit has a switch on/off pin */
    #endif
    // init helper libs

    Tle5012b::sBus->init();
    if (PIN_SPI_EN != UNUSED_PIN) {
        Tle5012b::en = new GPIOIno(PIN_SPI_EN, OUTPUT, GPIOIno::POSITIVE);
        Tle5012b::en->init();
    }else{
        Tle5012b::en = NULL;
    }
    // start sensor
    enableSensor();
    writeSlaveNumber(Tle5012b::mSlave);
    // initial CRC check, should be = 0
    return (readBlockCRC());
}


/** @} */