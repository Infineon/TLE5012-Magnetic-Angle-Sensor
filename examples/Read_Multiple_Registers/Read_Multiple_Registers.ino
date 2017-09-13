#include "TLE5012.h"

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
  checkError = tle5012.begin();
}

void loop() 
{
  if (s && (checkError == 0))
  {
    uint16_t data[leng];
    checkError = tle5012.readMoreRegisters(command, data);
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
