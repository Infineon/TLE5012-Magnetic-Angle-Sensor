/*!
 * \name        writeRegisters
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       test script for a writing register settings.
 * \details
 * This example show how to use the register write functions
 * of the sensor, to change certain bits with default low speed
 * 9600 baud communication and standard sensor settings
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <tlx5012-arduino.hpp>

using namespace tle5012;

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;
bool s = true;

void setup() {
  delay(1000);
  Serial.begin(9600);
  while (!Serial) {};
  delay(5000);
  Serial.println("init done!");
  checkError = Tle5012Sensor.begin();
  Serial.print("checkError: ");
  Serial.println(checkError, HEX);
  delay(1000);
}

void loop() {
  if (s && (checkError == 0))
  {
    uint16_t a = 0;

    checkError = Tle5012Sensor.readIntMode2(a);
    Serial.print("read intmode2:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError  = Tle5012Sensor.writeIntMode2(0x804);
    Serial.print("write intmode2:\t0x804\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError = Tle5012Sensor.readIntMode2(a);
    Serial.print("read intmode2:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
    Serial.println("");
    //
    checkError = Tle5012Sensor.readIntMode3(a);
    Serial.print("read intmode3:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError  = Tle5012Sensor.writeIntMode3(0x8000);
    Serial.print("write intmode3:\t0x8000\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError = Tle5012Sensor.readIntMode3(a);
    Serial.print("read intmode3:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
    Serial.println("");
    //
    checkError = Tle5012Sensor.readOffsetX(a);
    Serial.print("read OffsetX:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError  = Tle5012Sensor.writeOffsetX(0xD960);
    Serial.print("write OffsetX;\t0xD960\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError = Tle5012Sensor.readOffsetX(a);
    Serial.print("read OffsetX:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);

    s = false;
  }
}
