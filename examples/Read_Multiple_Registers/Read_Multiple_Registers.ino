#include "Tle5012b.h"

// Tle5012b Object
Tle5012b Tle5012MagneticAngleSensor = Tle5012b();

//here for the command: 
//the first two digits (80) is for read
//the third digits is from which address to start from (here 0)
//the fourth digit is how many consective registers to read
uint16_t command = 0x8005;
errorTypes checkError;
bool s = true;
uint8_t leng = 5;

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("init done!");
  checkError = Tle5012MagneticAngleSensor.begin();
  // If you do not use the standard SPI pins, you can reconfigure these
  // Check the other begin functions for other options
  // checkError = Tle5012MagneticAngleSensor.begin(SPI, MISO, MOSI, SCK, SS, SPISettings(SPEED,MSBFIRST,SPI_MODE1));
}

void loop() 
{
  if (s && (checkError == 0))
  {
    uint16_t data[leng];
    checkError = Tle5012MagneticAngleSensor.readMoreRegisters(command, data);
    if (checkError == 0)
    {
      for (int i = 0; i<leng; i++)
      {
        Serial.println(data[i], HEX);
      } 
      s = false;
    }
  }
  

}
