/*!
 * \name        E9000SPC
 * \author      Infineon Technologies AG
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       This example shows how to handle the TLE5012B-E9000 variant with SPC interface
 * \details
 * The TLE5012B-E9000 with SPC interface does not start the DSP automatically in a loop at start up.
 * It will need a certain trigger on the IFA pin of the sensor.
 * This trigger must be in a 90 UT time frame at least 12 UT long for the first sensor. By
 * multiplying the 12 UT with the sensor slave number up to four sensors can be triggered.
 * This trigger setting UT the unittime must multiplied with the sensors base unittime which
 * is default 3.0µs. Setting the IFA pin to low and waiting atleast the total trigger time
 * will set all registers by the DSP.
 * For more information please read the SPC Interface section of the manual.
 * The default setup ist:
 * - unittime =3.0µs,
 * - total trigger time = 90 * 3.0µs = 270 µs
 * - t_mlow the time for the first sensor to trigger = 12 * 3.0µs = 36 µs
 * so we have to set the IFA pin 36µs to low, than back to high and wait (90-12)*3.0µs = 224µs
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <tlx5012-arduino.hpp>

using namespace tle5012;

//!< \brief GPIO pin number of IFA on the Sensor2Go kit
#define        IFA        9

float    unitTime    = 3.0;  //!< \brief UT is default 3.0µs but will be read with getHysteresisMode
float    triggerTime = 90;   //!< \brief trigger total time is default 90UT * 3.0µs
float    t_mlow      = 12;   //!< \brief trigger will last default for 12 * 3.0µs


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
  Serial.println(checkError, HEX);
  delay(1000);

  Tle5012Sensor.resetFirmware();
  Tle5012Sensor.sBus->triggerUpdate();
  Serial.println("init done!");
  delay(1000);

  pinMode(IFA, OUTPUT);
  digitalWrite(IFA, HIGH);

  // Fetch sensor UT base value
  uint8_t val = Tle5012Sensor.reg.getHysteresisMode();
  unitTime = (val == 0
    ? 3.0
    : (val == 1
      ? 2.5
      : (val == 2
        ? 2.0
        : 1.5
      )
    )
  );

  // Fetch SPC Total Trigger Time
  val = Tle5012Sensor.reg.getHSMplp();
  triggerTime = ( val == 0
    ? 90
    : (t_mlow + 12)
  );

}

void loop() {

  double a = 0.0;
  double rr = 0.0;
  int16_t ra = 0;
  int16_t r = 0;
  double t = 0.0;
  int16_t rt = 0;
  double s = 0.0;
  int16_t rs = 0;

  digitalWrite(IFA, LOW);
  delayMicroseconds(t_mlow + unitTime);
  digitalWrite(IFA, HIGH);
  delayMicroseconds((triggerTime - t_mlow) * unitTime);

  Tle5012Sensor.getAngleRange(rr);
  Tle5012Sensor.getAngleValue(a,ra);
  Tle5012Sensor.getNumRevolutions(r);
  Tle5012Sensor.getTemperature(t,rt);
  Tle5012Sensor.getAngleSpeed(s,rs);

  Serial.print("range:      ");  Serial.print(rr); Serial.println("°");
  Serial.print("revolution: ");  Serial.println(r);

  Serial.print("DIR\tangle:  "); Serial.print(a);  Serial.print("°   "); Serial.print(ra,HEX);
  Serial.print("\ttemp:      "); Serial.print(t);  Serial.print("°C  "); Serial.print(rt,HEX);
  Serial.print("\tspeed:     "); Serial.print(s);  Serial.print("°/s "); Serial.print(rs,HEX);

  Serial.println("\n");
  delay(1000);
}
