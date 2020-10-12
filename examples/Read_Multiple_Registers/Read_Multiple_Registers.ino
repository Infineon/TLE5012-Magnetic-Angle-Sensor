/*!
 * \name        ReadMultipleRegisters
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example demonstrates how to read multiple raw registers at once.
 * In this case you have to recalculate values like angle, angle speed etc.
 * be your self.
 * 
 * \details
 * the read command offset of 0x8000 will be set by the readMoreRegisters command
 * so we need only the register offset from where we start and 
 * the second digit is how many consecutive registers to read which is
 * be done by adding the length and the command values.
 * A max of 15 value can read at once, one additional value is reserved for
 * the safety bit.
 */
#include "Tle5012b_reg.h"

Tle5012b_reg Tle5012Sensor;
errorTypes checkError = NO_ERROR;

uint16_t command = 0x0050; //!< read register beginning with REG_FSYNC
uint8_t leng = 5;          //!< and the next four registers REG_MOD_1, REG_SIL, REG_MOD2 and REG_MOD3
bool s = true;

void setup() {
  delay(2000);
  Serial.begin(9600);
  checkError = Tle5012Sensor.begin();
  Serial.print("checkerror: ");
  Serial.println(checkError, HEX);
  delay(1000);
  Serial.println("init done!");
}

void loop() 
{
  if (s && (checkError == 0))
  {
    uint16_t data[leng];
    command = command + leng;
    checkError = Tle5012Sensor.readMoreRegisters(command, data, UPD_low, SAFE_low);
    if (checkError == 0)
    {
      for (int i = 0; i<leng; i++)
      {
        Serial.print(data[i], HEX);
        Serial.print("\t;\t");
        PRINTBIN(data[i]);
        Serial.println();
      } 
      s = false;
    }
  }
}
