#include "Tle5012.h"

// Tle5012 Object
Tle5012 Tle5012MagneticAngleSensor = Tle5012();

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  Tle5012MagneticAngleSensor.begin();
  Serial.println("init done");

}

void loop() {
  // put your main code here, to run repeatedly:
  double d = 0.0;
  Tle5012MagneticAngleSensor.getAngleValue(d);
  Serial.println(d);
  delay(10);
}
