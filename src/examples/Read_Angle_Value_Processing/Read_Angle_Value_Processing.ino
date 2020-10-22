/*!
   \name        ReadAngleValueProcessing
   \author      Infineon Technologies AG
   \copyright   2019 Infineon Technologies AG
   \version     2.0.1
   \brief
   This example shows a fast readout of the angle value.
   Depending on your microcontroller more or less speed on
   the serial port is possible.

   \attention
   we use fast serail output setting of 1000000 baud and a
   10ms delay in the loop. You set smaller values down to 1ms
   but that will somehow overload the console log out put.
*/

#include <TLE5012-ino.hpp>

Tle5012Ino Tle5012Sensor = Tle5012Ino();
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
