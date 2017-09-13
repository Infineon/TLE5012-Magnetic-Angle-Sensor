#include "TLE5012.h"

errorTypes checkError;
bool s = true;

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("init done!");
  checkError = tle5012.begin();
}

void loop() {
  if (s && (checkError == 0))
  {
    uint16_t a = 0;
  
    Serial.println("read intmode2");
    checkError = tle5012.readIntMode2(a);
    Serial.println(a,HEX);
  
    Serial.println("write intmode 2");
    checkError  = tle5012.writeIntMode2(0x804);
  
    Serial.println("read intmode2");
    checkError = tle5012.readIntMode2(a);
    Serial.println(a,HEX);
  
    Serial.println("read intmode3");
    checkError = tle5012.readIntMode3(a);
    Serial.println(a,HEX);
  
    Serial.println("write intmode 3");
    checkError  = tle5012.writeIntMode3(0x8000);
  
    Serial.println("intmode3");
    checkError = tle5012.readIntMode3(a);
    Serial.println(a,HEX);
  
    Serial.println("Offset X");
    checkError = tle5012.readOffsetX(a);
    Serial.println(a,HEX);
  
    Serial.println("write Offset X");
    checkError  = tle5012.writeOffsetX(0xD960);
  
    Serial.println("read Offset X");
    checkError = tle5012.readOffsetX(a);
    Serial.println(a,HEX);
  
    s = false;
  }
}
