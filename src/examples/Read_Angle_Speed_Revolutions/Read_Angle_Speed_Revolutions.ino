/*!
 * \name        ReadAngleSpeedRevolutions
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This is a fast running example to demonstrate the possible readout
 * speed of the sensor for the angle, angle speed and number of revolutions
 * at once.
 * For reconfiguring of the SPI interface, have a look at the documentation.
 * 
 * \attention
 * we use fast serail output setting og 1000000 baud.
 */

#include <TLE5012-ino.hpp>


// Tle5012b Object
Tle5012Ino Tle5012MagneticAngleSensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(2000);
  Serial.begin(1000000);
  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.println("init done!");
  Serial.println("AngleSpeed\tAngleValue\trevolutions\tAngleRange");
  delay(1000);
}

void loop() {
  if (checkError == 0)
  {
    double d = 0.0;
    int16_t b = 0;
    checkError = Tle5012MagneticAngleSensor.getAngleSpeed(d);
    Serial.print(d);
  
    Serial.print("\t");
    checkError = Tle5012MagneticAngleSensor.getAngleValue(d);
    Serial.print(d);
  
    Serial.print("\t\t");
    checkError = Tle5012MagneticAngleSensor.getNumRevolutions(b);
    Serial.print(b);
    
    Serial.print("\t\t");
    Tle5012MagneticAngleSensor.getAngleRange(d);
    Serial.println(d);
  }
  delay(30); //can be removed
}
