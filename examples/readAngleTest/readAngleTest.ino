/*!
 * \name        readAngleTest
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.1.0
 * \brief       Testscript for a first check.
 * \details
 * This example reads all main Sensor registers (angle,revolution,speed,range and temperature)
 * for a simple first test of the sensor and comunication.
 * 
 * \attention
 * We use default very low speed 9600 baud, but the sensor can much more, see the other examples
 * 
 * SPDX-License-Identifier: MIT
 *
 */

#include <TLE5012-ino.hpp>

using namespace tle5012;

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(2000);
  Serial.begin(9600);
  while (!Serial) {};
  checkError = Tle5012Sensor.begin();
  Serial.print("checkError: ");
  Serial.println(checkError,HEX);
  delay(1000);
  Serial.println("Init done");
}

void loop() {
  double d = 0.0;
  double r = 0.0;
  double s = 0.0;
  double t = 0;
  int16_t b = 0;

  Tle5012Sensor.getAngleValue(d);
  Tle5012Sensor.getNumRevolutions(b);
  Tle5012Sensor.getAngleSpeed(s);
  Tle5012Sensor.getAngleRange(r);
  Tle5012Sensor.getTemperature(t);

  Serial.print("Temperature:"); Serial.print(t);
  Serial.print("°C\tangle:");   Serial.print(d);
  Serial.print("°\trange:");    Serial.print(r);
  Serial.print("\tspeed:");	    Serial.print(s);
  Serial.print("\t Revolution:");Serial.println(b);

  delay(1000);
}
