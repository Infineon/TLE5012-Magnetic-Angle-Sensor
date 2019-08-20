/*!
 * \name        ReadSpeedProcessing
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * Demonstrates the fast readout of the angle speed.
 * Depending on the microcontroller you use more or less
 * speed on the serial port is possible.
 */

#include "Tle5012b_reg.h"

Tle5012b_reg Tle5012MagneticAngleSensor;
errorTypes checkError = NO_ERROR;

void setup() {
  delay(2000);
  Serial.begin(1000000);
  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.print("checkerror: ");
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
