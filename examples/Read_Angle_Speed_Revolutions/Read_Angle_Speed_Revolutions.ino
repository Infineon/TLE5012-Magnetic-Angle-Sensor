#include "Tle5012b.h"

// Tle5012b Object
Tle5012b Tle5012MagneticAngleSensor = Tle5012b();

errorTypes checkError = NO_ERROR;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  checkError = Tle5012MagneticAngleSensor.begin();
  // If you do not use the standard SPI pins, you can reconfigure these
  // Check the other begin functions for other options
  // checkError = Tle5012MagneticAngleSensor.begin(SPI, MISO, MOSI, SCK, SS, SPISettings(SPEED,MSBFIRST,SPI_MODE1));

  Serial.println("init done!");
  Serial.println("AngleSpeed\tAngleValue\trevolutions\tAngleRange");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (checkError == 0)
  {
    double d = 0.0;
    int16_t b = 0;
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
  Serial.println(checkError);
  delay(30);
}