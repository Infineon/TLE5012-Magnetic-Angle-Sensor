#include "Tle5012.h"

// Tle5012 Object
Tle5012 Tle5012MagneticAngleSensor = Tle5012();

errorTypes checkError;
bool s = true;

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("init done!");
  checkError = Tle5012MagneticAngleSensor.begin();
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
