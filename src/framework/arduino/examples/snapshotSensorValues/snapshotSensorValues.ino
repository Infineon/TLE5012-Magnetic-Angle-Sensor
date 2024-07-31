/*!
 * \name        snapshotSensorValues
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       This example can be used for a first fast test if the sensors works
 * \details
 * It will generate a looped output of the direct measured data (DIR) and
 * data from the update (UPD) registers. Therefore it demonstrates also the use of
 * the direct read (without UPD) and the snapshot registers (with UPD). See Sensor
 * manual for more information of the UPD mode and the snapshot registers.
 * Running the update trigger before reading a value guarantees that all values
 * are actual measurement.
 * Using the UPD flag will read all values into the snapshot before reading them,
 * so that all values are from the same measurement.
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <tlx5012-arduino.hpp>

using namespace tle5012;

// Tle5012b Object
Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;
updTypes upd = UPD_high;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  delay(5000);

  checkError = Tle5012Sensor.begin();
  Serial.print("checkError: ");
  Serial.println(checkError,HEX);
  delay(1000);

  Tle5012Sensor.resetFirmware();
  Tle5012Sensor.sBus->triggerUpdate();
  Serial.println("init done!");
  delay(1000);
}

void loop() {
  double  range = 0.0;                //<! actual angle range setting

  double  angle_dir = 0.0;            //<! direct read angle value from the register
  double  angle_upd = 0.0;            //<! direct read raw data where the angle is calculated from
  int16_t angle_raw_dir = 0;          //<! angle data after an update trigger
  int16_t angle_raw_upd = 0;          //<! raw binary angle data after an update trigger
  
  int16_t revolution_dir = 0;         //<! direct read number of revolution
  int16_t revolution_upd = 0;         //<! number of revolution after an update trigger
  
  
  double  temperature_dir = 0.0;      //<! direct read temperature
  double  temperature_upd = 0.0;      //<! temperature after and update trigger
  int16_t temperature_raw_dir = 0;    //<! direct read binary raw temperature
  int16_t temperature_raw_upd = 0;    //<! binary read temperature after an update trigger
  
  double  anglespeed_dir = 0.0;       //<! direct read angular velocity
  double  anglespeed_upd = 0.0;       //<! binary value of the direct read angular velocity
  int16_t anglespeed_raw_dir = 0;     //<! angular velocity after an update trigger
  int16_t anglespeed_raw_upd = 0;     //<! binary value of the angular velocity after an update trigger


  Tle5012Sensor.getAngleRange(range);
  Tle5012Sensor.getNumRevolutions(revolution_dir);

  Tle5012Sensor.getAngleValue(angle_dir,angle_raw_dir);

  Tle5012Sensor.getTemperature(temperature_dir,temperature_raw_dir);
  Tle5012Sensor.getAngleSpeed(anglespeed_dir,anglespeed_raw_dir);

  // to read UPD registers, call triggerUpdate once and
  // than read all UPD registers you need before calling
  // triggerUpdate again
  Tle5012Sensor.sBus->triggerUpdate();
  Tle5012Sensor.getAngleValue (angle_upd,angle_raw_upd,upd);
  Tle5012Sensor.getNumRevolutions(revolution_upd);
  Tle5012Sensor.getTemperature(temperature_upd,temperature_raw_upd,upd);
  Tle5012Sensor.getAngleSpeed (anglespeed_upd,anglespeed_raw_upd,upd);

  Serial.print("range:      ");      Serial.print(range); Serial.println("°");
  Serial.print("revolution: ");      Serial.print(revolution_dir);
  Serial.print("\trevolutionUPD: "); Serial.println(revolution_upd);

  Serial.print("DIR\tangle:  "); Serial.print(angle_dir);        Serial.print("°   0x"); Serial.print(angle_raw_dir,HEX);
  Serial.print("\ttemp:      "); Serial.print(temperature_dir);  Serial.print("°C  0x"); Serial.print(temperature_raw_dir,HEX);
  Serial.print("\tspeed:     "); Serial.print(anglespeed_dir);   Serial.print("°/s 0x"); Serial.print(anglespeed_raw_dir,HEX);

  Serial.println("");

  Serial.print("UPD\tangUPD: "); Serial.print(angle_upd);        Serial.print("°   0x"); Serial.print(angle_raw_upd,HEX);
  Serial.print("\ttempUPD:   "); Serial.print(temperature_upd);  Serial.print("°C  0x"); Serial.print(temperature_raw_upd,HEX);
  Serial.print("\tspeedUPD:  "); Serial.print(anglespeed_upd);   Serial.print("°/s 0x"); Serial.print(anglespeed_raw_upd,HEX);

  Serial.println("\n");
  delay(1000);
}
