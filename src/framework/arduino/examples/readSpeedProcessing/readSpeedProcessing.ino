/*!
 * \name        readSpeedProcessing
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       reads the angle speed
 * \details
 * Demonstrates the fast readout of the angle speed.
 * Depending on the microcontroller you use more or less
 * speed on the serial port is possible.
 *
 * \attention Use this sketch together with the processing script examples
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <tlx5012-arduino.hpp>

using namespace tle5012;

Tle5012Ino Tle5012MagneticAngleSensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(1000);
  Serial.begin(1000000);
  while (!Serial) {};
  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.print("checkError: ");
  Serial.println(checkError, HEX);
  Serial.println("init done");
  delay(1000);
}

void loop() {
  double d = 0.0;
  Tle5012MagneticAngleSensor.getAngleSpeed(d);
  Serial.println(d);
  // remark this for even more speed
  delay(10);
}
