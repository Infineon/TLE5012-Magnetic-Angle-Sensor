/*!
 * \name        useMultipleChannels
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       test script for a first check.
 * \details
 * This examples show how to use other SPI channels than the default one on the Arduino header.
 * This example is specially made for the XMC4700 Relax Kit which has five SPI channels.
 * From these five channels three can be used with overlapping other functionality.wrong 
 * THis example should also work for other MCUs with more than one SPI channel by setting the
 * right pin numbers.
 * It is also possible to combine this with the multi sensor example, as we can define up to
 * four independent sensors on each SPI channel.
 *
 * \attention
 * We use default very low speed 9600 baud, but the sensor can much more, see the other examples
 *
 * \attention
 * This example is limited to the Infineon XMC4700, but you can use it also for other MCUs with
 * multiple SPI channels. It will not work on MCUs which have only one SPI channel
 * 
 * SPDX-License-Identifier: MIT
 *
 */

#include <tlx5012-arduino.hpp>

using namespace tle5012;

#if !defined(XMC4700_Relax_Kit)

 void setup()
 {
   delay(1000);
   Serial.begin(9600);
   while (!Serial) {};
   Serial.println("STOP: this sketch needs multiple SPI channels");
 }

void loop()
{
}

#else


/*!
 * Main pin defines for XMC4700 SPI in extended pins X1 and X2
 * the XMC4700 has multiple SPI channels, but only three can be used.
 * SPI or SPI0 the default SPI on the Arduino header four up to four ange sensors
 * SPI1 can be used for up to four angle-sensors
 * SPI2 can also used for up to four angle-sensors
 * The angle-sensors ar using 3wire SPI (SSC) where MISO and MOSI Pins are shorted.
 * The SPI (0-2) numbering is used from the HW SPI interface.
 * For multiple Sensors on one SPI channel see useMultipleSensors.ino example
 *
 * SCK                  13                        //! P3.9
 * MISO                 12                        //! P3.7
 * MOSI                 11                        //! P3.8
 * CS1                  10                        //! P3.10
 */
#define PIN_SPI1_SS0   36                       //! P0.3
#define PIN_SPI1_SS1   64                       //! P0.2
#define PIN_SPI1_SS2   66                       //! P0.4
#define PIN_SPI1_SS3   35                       //! P0.5
#define PIN_SPI1_MOSI  37                       //! P0.1
#define PIN_SPI1_MISO  63                       //! P0.0
#define PIN_SPI1_SCK   38                       //! P0.10
// Pin selection for SPI2 on X2
#define PIN_SPI2_SS0   94                       //! P0.12
#define PIN_SPI2_SS1   93                       //! P0.15
#define PIN_SPI2_SS2   71                       //! P3.14
#define PIN_SPI2_SS3   70                       //! P0.14
#define PIN_SPI2_MOSI  69                       //! P3.11
#define PIN_SPI2_MISO  95                       //! P3.12
#define PIN_SPI2_SCK   68                       //! P3.13

// we need SPIClass3W which overloads the SPI class and includes 3wire functions
tle5012::SPIClass3W tle5012::SPI3W1(1);         //!< SPI port 1 on XMC4700 X1 according HW SPI setup
tle5012::SPIClass3W tle5012::SPI3W2(2);         //!< SPI port 2 on XMC4700 X2 according HW SPI setup

// Set the Sensor library pointer with full parameter set for SPI1 and SPI2
// It does not matter if there is a sensor attached to the SPI chancel. I will throw a
// checkError with the begin function.
Tle5012Ino Tle5012SensorSPI1 = Tle5012Ino(&SPI3W1, PIN_SPI1_SS0, PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SCK, Tle5012Ino::TLE5012B_S0);
Tle5012Ino Tle5012SensorSPI2 = Tle5012Ino(&SPI3W2, PIN_SPI2_SS0, PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SCK, Tle5012Ino::TLE5012B_S0);
errorTypes checkError = NO_ERROR;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  delay(5000);

  // Run the initialize function on SPI1
  // this will throw an error if there is no sensor attached or
  // if there is no magnetic field around the sensor
  checkError = Tle5012SensorSPI1.begin();
  Serial.print("checkError SPI1: ");
  Serial.println(checkError,HEX);

  // same for SPI channel two
  checkError = Tle5012SensorSPI2.begin();
  Serial.print("checkError SPI2: ");
  Serial.println(checkError,HEX);

  delay(1000);
  Serial.println("Init done");
}

void loop() {
  double angleSPI1 = 0.0;
  double rangeSPI1 = 0.0;
  double speedSPI1 = 0.0;
  double temperatureSPI1 = 0;
  int16_t revolutionSPI1 = 0;

  double angleSPI2 = 0.0;
  double rangeSPI2 = 0.0;
  double speedSPI2 = 0.0;
  double temperatureSPI2 = 0;
  int16_t revolutionSPI2 = 0;

  // read values from SPI1 and print
  Tle5012SensorSPI1.getAngleValue(angleSPI1);
  Tle5012SensorSPI1.getNumRevolutions(revolutionSPI1);
  Tle5012SensorSPI1.getAngleSpeed(speedSPI1);
  Tle5012SensorSPI1.getAngleRange(rangeSPI1);
  Tle5012SensorSPI1.getTemperature(temperatureSPI1);

  Serial.print("SPI1:\t");
  Serial.print("Temperature:"); Serial.print(temperatureSPI1);
  Serial.print("°C\tangle:");   Serial.print(angleSPI1);
  Serial.print("°\trange:");    Serial.print(rangeSPI1);
  Serial.print("\tspeed:");	    Serial.print(speedSPI1);
  Serial.print("\t Revolution:");Serial.println(revolutionSPI1);

  // read values from SPI2 and print
  Tle5012SensorSPI2.getAngleValue(angleSPI2);
  Tle5012SensorSPI2.getNumRevolutions(revolutionSPI2);
  Tle5012SensorSPI2.getAngleSpeed(speedSPI2);
  Tle5012SensorSPI2.getAngleRange(rangeSPI2);
  Tle5012SensorSPI2.getTemperature(temperatureSPI2);

  Serial.print("SPI2:\t");
  Serial.print("Temperature:"); Serial.print(temperatureSPI2);
  Serial.print("°C\tangle:");   Serial.print(angleSPI2);
  Serial.print("°\trange:");    Serial.print(rangeSPI2);
  Serial.print("\tspeed:");	    Serial.print(speedSPI2);
  Serial.print("\t Revolution:");Serial.println(revolutionSPI2);

  delay(1000);
}

#endif