/*!
 * \name        ReadAngleValueProcessing
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example shows a fast readout of the angle value.
 * Depending on your microcontroller more or less speed on
 * the serial port is possible.
 * 
 * \Atteintion
 * we use fast serail output setting og 1000000 baud.
 */

#include "Tle5012b_reg.h"

Tle5012b_reg Tle5012Sensor;
errorTypes checkError = NO_ERROR;

void setup() {
  delay(2000);
  Serial.begin(1000000);
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
