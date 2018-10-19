#include "Tle5012b.h"

// Tle5012b Object
Tle5012b Tle5012MagneticAngleSensor = Tle5012b();

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  Tle5012MagneticAngleSensor.begin();
  // If you do not use the standard SPI pins, you can reconfigure these
  // Check the other begin functions for other options
  // checkError = Tle5012MagneticAngleSensor.begin(SPI, MISO, MOSI, SCK, SS, SPISettings(SPEED,MSBFIRST,SPI_MODE1));
  Serial.println("init done");

}

void loop() {
  // put your main code here, to run repeatedly:
  double d = 0.0;
  Tle5012MagneticAngleSensor.getAngleValue(d);
  Serial.println(d);
  delay(10);
}
