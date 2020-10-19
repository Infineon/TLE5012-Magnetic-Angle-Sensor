#include <TLE5012-ino.hpp>

/*!
 * \name        ReadTest
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example can be used for a first fast test if the sensors works
 * 
 * \detail
 * It will generate looped out of the direct measured data (DIR) and
 * the data from the update (UPD) registers.Therefore it demonstrats also the use of
 * the direct read (without UPD) and the snapshoot registers (with UPD). See Sensor
 * manual for more information of the UPD mode and the snapshoot registers.
 */

// Tle5012b Object
Tle5012Ino Tle5012MagneticAngleSensor;
errorTypes checkError = NO_ERROR;
updTypes upd = UPD_high;

void setup() {
  delay(2000);
  Serial.begin(115200);
  checkError = Tle5012MagneticAngleSensor.begin();
  Serial.println("init done!");
  Tle5012MagneticAngleSensor.resetFirmware();
  Tle5012MagneticAngleSensor.triggerUpdate();
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
  
  Tle5012MagneticAngleSensor.getAngleRange(rr);
  Tle5012MagneticAngleSensor.getAngleValue(a,ra);
  Tle5012MagneticAngleSensor.getNumRevolutions(r);
  Tle5012MagneticAngleSensor.getTemperature(t,rt);
  Tle5012MagneticAngleSensor.getAngleSpeed(s,rs);
  
  // to read UPD registers, call triggerUpdate once and
  // than read all UPD registers you need before calling
  // triggerUpdate again
  Tle5012MagneticAngleSensor.triggerUpdate();
  Tle5012MagneticAngleSensor.getAngleValue(au,rau,upd);
  Tle5012MagneticAngleSensor.getTemperature(tu,rtu,upd);
  Tle5012MagneticAngleSensor.getAngleSpeed(su,rsu,upd);
  Tle5012MagneticAngleSensor.getNumRevolutions(ru);

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
