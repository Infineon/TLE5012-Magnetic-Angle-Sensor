/*!
 * \name        testSensorMainValues
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       This example can be used for a first fast test if the sensors works
 * \details
 * It will generate a looped output of the direct measured data (DIR) and
 * data from the update (UPD) registers. Therefore it demonstrates also the use of
 * the direct read (without UPD) and the snapshot registers (with UPD). See Sensor
 * manual for more information of the UPD mode and the snapshot registers.
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
  delay(2000);
  Serial.begin(115200);
  while (!Serial) {};
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
  double a = 0.0; double au = 0.0; double rr = 0.0;
  int16_t ra = 0; int16_t rau = 0;
  int16_t r = 0;  int16_t ru = 0;
  double t = 0.0; double tu = 0.0;
  int16_t rt = 0; int16_t rtu = 0;
  double s = 0.0; double su = 0.0;
  int16_t rs = 0; int16_t rsu = 0;
  
  Tle5012Sensor.getAngleRange(rr);
  Tle5012Sensor.getAngleValue(a,ra);
  Tle5012Sensor.getNumRevolutions(r);
  Tle5012Sensor.getTemperature(t,rt);
  Tle5012Sensor.getAngleSpeed(s,rs);
  
  // to read UPD registers, call triggerUpdate once and
  // than read all UPD registers you need before calling
  // triggerUpdate again
  Tle5012Sensor.sBus->triggerUpdate();
  Tle5012Sensor.getAngleValue(au,rau,upd);
  Tle5012Sensor.getTemperature(tu,rtu,upd);
  Tle5012Sensor.getAngleSpeed(su,rsu,upd);
  Tle5012Sensor.getNumRevolutions(ru);

  Serial.print("range:      ");      Serial.print(rr); Serial.println("°");
  Serial.print("revolution: ");      Serial.print(r);
  Serial.print("\trevolutionUPD: "); Serial.println(ru);

  Serial.print("DIR\tangle:  "); Serial.print(a);  Serial.print("°   "); Serial.print(ra,HEX);
  Serial.print("\ttemp:      "); Serial.print(t);  Serial.print("°C  "); Serial.print(rt,HEX);
  Serial.print("\tspeed:     "); Serial.print(s);  Serial.print("°/s "); Serial.print(rs,HEX);

  Serial.println("");

  Serial.print("UPD\tangUPD: "); Serial.print(au); Serial.print("°   "); Serial.print(rau,HEX);
  Serial.print("\ttempUPD:   "); Serial.print(tu); Serial.print("°C  "); Serial.print(rtu,HEX);
  Serial.print("\tspeedUPD:  "); Serial.print(su); Serial.print("°/s "); Serial.print(rsu,HEX);

  Serial.println("\n");
  delay(1000);
}
