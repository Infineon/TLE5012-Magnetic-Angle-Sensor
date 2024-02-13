/*!
 * \name        readAngleSpeedRevolutions
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       reads angle value, rotation speed and number of revolutions
 * \details
 * This is a fast running example to demonstrate the possible readout
 * speed of the sensor for the angle, angle speed and number of revolutions
 * at once.
 * For reconfiguring of the SPI interface, have a look at the documentation.
 *
 * \attention Use together with the speed.pde processing script
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <tlx5012-arduino.hpp>

using namespace tle5012;

// Tle5012b Object
Tle5012Ino Tle5012MagneticAngleSensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  delay(5000);

  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.print("checkError: ");
  Serial.println(checkError, HEX);
  Serial.println("init done!");
  delay(1000);
  Serial.println("AngleSpeed\tAngleValue\trevolutions\tAngleRange");
  delay(1000);
}

void loop() {
  if (checkError == 0)
  {
    double speed = 0.0;
    double angle = 0.0;
    double range = 0.0;
    int16_t revol = 0;

    Tle5012MagneticAngleSensor.getAngleSpeed(speed);
    Tle5012MagneticAngleSensor.getAngleValue(angle);
    Tle5012MagneticAngleSensor.getAngleRange(range);
    Tle5012MagneticAngleSensor.getNumRevolutions(revol);

    Serial.print(speed);    Serial.print("\t\t");
    Serial.print(angle);    Serial.print("\t\t");
    Serial.print(revol);    Serial.print("\t\t");
    Serial.print(range);
    Serial.print("\n");

    checkError = Tle5012MagneticAngleSensor.readBlockCRC();

  }else{
    checkError = Tle5012MagneticAngleSensor.readBlockCRC();
    Serial.print("checkError: ");
    Serial.println(checkError, HEX);
  }
  delay(100); //can be removed
}
