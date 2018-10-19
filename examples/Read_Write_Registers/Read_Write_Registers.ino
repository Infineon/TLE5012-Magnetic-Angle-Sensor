#include "Tle5012b.h"

// Tle5012b Object
Tle5012b Tle5012MagneticAngleSensor = Tle5012b();

errorTypes checkError;
bool s = true;

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("init done!");
  checkError = Tle5012MagneticAngleSensor.begin();
  // If you do not use the standard SPI pins, you can reconfigure these
  // Check the other begin functions for other options
  // checkError = Tle5012MagneticAngleSensor.begin(SPI, MISO, MOSI, SCK, SS, SPISettings(SPEED,MSBFIRST,SPI_MODE1));
}

void loop() {
  if (s && (checkError == 0))
  {
    uint16_t a = 0;
  
    Serial.println("read intmode2");
    checkError = Tle5012MagneticAngleSensor.readIntMode2(a);
    Serial.println(a,HEX);
  
    Serial.println("write intmode 2");
    checkError  = Tle5012MagneticAngleSensor.writeIntMode2(0x804);
  
    Serial.println("read intmode2");
    checkError = Tle5012MagneticAngleSensor.readIntMode2(a);
    Serial.println(a,HEX);
  
    Serial.println("read intmode3");
    checkError = Tle5012MagneticAngleSensor.readIntMode3(a);
    Serial.println(a,HEX);
  
    Serial.println("write intmode 3");
    checkError  = Tle5012MagneticAngleSensor.writeIntMode3(0x8000);
  
    Serial.println("intmode3");
    checkError = Tle5012MagneticAngleSensor.readIntMode3(a);
    Serial.println(a,HEX);
  
    Serial.println("Offset X");
    checkError = Tle5012MagneticAngleSensor.readOffsetX(a);
    Serial.println(a,HEX);
  
    Serial.println("write Offset X");
    checkError  = Tle5012MagneticAngleSensor.writeOffsetX(0xD960);
  
    Serial.println("read Offset X");
    checkError = Tle5012MagneticAngleSensor.readOffsetX(a);
    Serial.println(a,HEX);
  
    s = false;
  }
}
