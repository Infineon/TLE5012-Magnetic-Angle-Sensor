#include "TLE5012.h"

errorTypes checkError;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  checkError = tle5012.begin();
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
    checkError = tle5012.getAngleSpeed(d);
    Serial.print(d);
  
    Serial.print("\t\t");
    checkError = tle5012.getAngleValue(d);
    Serial.print(d);
  
    Serial.print("\t\t");
    checkError = tle5012.getNumRevolutions(b);
    Serial.print(b);
    
    Serial.print("\t\t");
    tle5012.getAngleRange(d);
    Serial.println(d);
  }
  

  
  delay(30);
}
