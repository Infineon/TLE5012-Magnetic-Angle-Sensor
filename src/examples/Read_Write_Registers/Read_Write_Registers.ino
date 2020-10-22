/*!
 * \name        Read_Write_Registers
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example show how to use the register write functions
 * of the sensor, to change certain bits with deafult low speed
 * 9600 baud comunication and standard sensor settings
 */

#include <TLE5012-ino.hpp>

// Tle5012b Object
Tle5012Ino Tle5012MagneticAngleSensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;
bool s = true;

void setup() {
  delay(2000);
  Serial.begin(9600);
  Serial.println("init done!\n");
  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.print("checkerror: ");
  Serial.println(checkError, HEX);
  delay(1000);
}

void loop() {
  if (s && (checkError == 0))
  {
    uint16_t a = 0;
  
    checkError = Tle5012MagneticAngleSensor.readIntMode2(a);
    Serial.print("read intmode2:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
    
    checkError  = Tle5012MagneticAngleSensor.writeIntMode2(0x804);
    Serial.print("write intmode2:\t0x804\tcheckError: ");
    Serial.println(checkError,HEX);
    
    checkError = Tle5012MagneticAngleSensor.readIntMode2(a);
    Serial.print("read intmode2:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
    Serial.println("");
    //  
    checkError = Tle5012MagneticAngleSensor.readIntMode3(a);
    Serial.print("read intmode3:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
    
    checkError  = Tle5012MagneticAngleSensor.writeIntMode3(0x8000);
    Serial.print("write intmode3:\t0x8000\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError = Tle5012MagneticAngleSensor.readIntMode3(a);
    Serial.print("read intmode3:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
    Serial.println("");
    //
    checkError = Tle5012MagneticAngleSensor.readOffsetX(a);
    Serial.print("read OffsetX:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);

    checkError  = Tle5012MagneticAngleSensor.writeOffsetX(0xD960);
    Serial.print("write OffsetX;\t0xD960\tcheckError: ");
    Serial.println(checkError,HEX);
    
    checkError = Tle5012MagneticAngleSensor.readOffsetX(a);
    Serial.print("read OffsetX:\t0x");
    Serial.print(a,HEX);
    Serial.print("\tcheckError: ");
    Serial.println(checkError,HEX);
  
    s = false;
  }
}
