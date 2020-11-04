/*!
 * \name        Read_Angle_Value_Processing
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     2.0.1
 * \brief       Reads rotation speed
 * \details
 * This is a fast running example to demonstrate the possible readout
 * speed of the sensor for the angle, angle speed and number of revolutions
 * at once. Depending on your microcontroller more or less speed on
 * the serial port is possible.
 * For reconfiguring of the SPI interface, have a look at the documentation.
 * 
 * \attention Use together with the several processing scripts
 * \attention We use fast serail output setting of 1000000 baud and a
 * 10ms delay in the loop. You set smaller values down to 1ms
 * but that will somehow overload the console log out put.
 * 
 * SPDX-License-Identifier: MIT
 *
 */

#include <TLE5012-ino.hpp>

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(1000);
  Serial.begin(1000000);
  while (!Serial) {};
  Serial.println("init done!");
  checkError = Tle5012Sensor.begin();
  Serial.print("checkerror: ");
  Serial.println(checkError, HEX);
  delay(1000);
}

void loop() {
  double d = 0.0;
  Tle5012Sensor.getAngleValue(d);
  Serial.println(d);
  delay(10);
}
