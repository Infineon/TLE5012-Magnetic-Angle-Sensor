#include <Tle5012b.h>

/*!
 * \name        ReadAngleTest
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example reads all main Sensor registers (angle,revolution,speed,range and temperature)
 * for a simple first test of the sensor and comunication.
 * 
 * \Attention
 * We use default very low spee 9600 baud, but the sensor can much more, see the other examples
 */

Tle5012b Tle5012MagneticAngleSensor;
errorTypes checkError = NO_ERROR;

void setup() {
  delay(2000);
  Serial.begin(9600);
  checkError = Tle5012MagneticAngleSensor.begin();
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

  Tle5012MagneticAngleSensor.getAngleValue(d);
  Tle5012MagneticAngleSensor.getNumRevolutions(b);
  Tle5012MagneticAngleSensor.getAngleSpeed(s);
  Tle5012MagneticAngleSensor.getAngleRange(r);
  Tle5012MagneticAngleSensor.getTemperature(t);

  Serial.print("Temperature:"); Serial.print(t);
  Serial.print("°C\tangle:");   Serial.print(d);
  Serial.print("°\trange:");    Serial.print(r);
  Serial.print("\tspeed:");	    Serial.print(s);
  Serial.print("\t Revolution:");Serial.println(b);

  delay(1000);
}
