#include "Tle5012.h"

// Tle5012 Object
Tle5012 Tle5012MagneticAngleSensor = Tle5012();

errorTypes checkError;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.println("init done!");
  Serial.println("AngleSpeed\tAngleValue\trevolutions\tAngleRange");
}

void loop() {
  if (checkError == 0)
  {
    errorTypes checkError;
    double d = 0.0;
    int16_t b = 0;
    uint16_t a = 0;
    checkError = Tle5012MagneticAngleSensor.getAngleSpeed(d);
    Serial.print(d);
  
    Serial.print("\t\t");
    checkError = Tle5012MagneticAngleSensor.getAngleValue(d);
    Serial.print(d);
  
    Serial.print("\t\t");
    checkError = Tle5012MagneticAngleSensor.getNumRevolutions(b);
    Serial.print(b);
    
    Serial.print("\t\t");
    Tle5012MagneticAngleSensor.getAngleRange(d);
    Serial.println(d);
  }
  

  
  delay(30);
}
