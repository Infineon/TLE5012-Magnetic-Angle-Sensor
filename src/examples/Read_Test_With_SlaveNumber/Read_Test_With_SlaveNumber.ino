/*!
 * \name        Read_Test_With_SlaveNumber
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example allows the control of multiple sensors on one SPI channel
 * \detail
 * This example program starts one to four sensors on one SPI line with different CS pins
 * and returns the angle value together with the safety word and the status register SNR.
 * Due to the selected slave number the SNR will be set to 0x00, 0x01, 0x10 or 0x11. When
 * you fetch a value from the sensor with safety word on than the safety word register RESP
 * will indicate the sensor who is responding. This should be the same than you have
 * ask for. The loop function will than print out the individual sensor(s) angle values.
 *  
 * This example also demonstrates how to handle more than on sensor in an array setup.
 * 
 * \attention Needs much memory which can be too much for the original Arduino/Genuino Uno
 */

#include <Tle5012b_reg.h>

//! number of connected sensors
#define SENSOR_NUM 1

//! define more unique chipselect pins for more connected Sensors
#define CS_PIN_SENSOR_1   10  //!< This is a setup for the default Arduino, use 3 for the Xensor2Go kit
#define CS_PIN_SENSOR_2   5   //!< This is also a setup for the Sens2Go board but with a second sensor attached
//#define CS_PIN_SENSOR_3   x
//#define CS_PIN_SENSOR_4   x

//! Tle5012b Object, set/remove depending on the number of connected sensors
Tle5012b_reg sensor[SENSOR_NUM] = {
  (Tle5012b_reg()),
//  (Tle5012b_reg()),
//  (Tle5012b_reg()),
//  (Tle5012b_reg()),
};

//! Sensor IFX SIL(TM) errorCheck
errorTypes checkError = NO_ERROR;

//! array if the read angle values and revolutions
double d[4] = {0.0, 0.0, 0.0, 0.0};
int16_t r[4] = {0, 0, 0, 0};

void setup() {
  delay(2000);
  Serial.begin(115200);
 
  // Remove remark if you have more than one sensor,
  // or change the Tle5012Sensor.TLE5012B_S0 to S1-S3 to demonstrate the effect
  checkError = sensor[0].begin(CS_PIN_SENSOR_1,sensor[1].TLE5012B_S0);
  //checkError = sensor[1].begin(CS_PIN_SENSOR_2,sensor[1].TLE5012B_S1);
  //checkError = sensor[2].begin(CS_PIN_SENSOR_3,sensor[2].TLE5012B_S2);
  //checkError = sensor[3].begin(CS_PIN_SENSOR_4,sensor[3].TLE5012B_S3);
  Serial.print("init done! with checkError ");
  Serial.println(checkError);
  Serial.println("");

  uint16_t stat;
  uint8_t resp;
  double a = 0.0;
  for (int8_t i=0;i<SENSOR_NUM;i++){
    sensor[i].readStatus(stat);
    sensor[i].sensorRegister.stat.fetch_SNR(stat);
    sensor[i].getAngleValue(a);
    sensor[i].safetyStatus.fetch_Safety(sensor[i].safetyWord);
  
    Serial.print(i);
    Serial.print("\tangle: ");
    Serial.print(a);
    Serial.print("\tSTAT SNR: ");
    Serial.print(sensor[i].sensorRegister.stat.SNR);
    Serial.print("\tRESP: ");
  
    switch (sensor[i].safetyStatus.responseSlave()) {
      case sensor[i].TLE5012B_S3:
        Serial.print("0x0111 = TLE5012B_S3");
        break;
      case sensor[i].TLE5012B_S2:
        Serial.print("0x1011 = TLE5012B_S2");
        break;
      case sensor[i].TLE5012B_S1:
        Serial.print("0x1101 = TLE5012B_S1");
        break;
      default:
        Serial.print("0x1110 = TLE5012B_S0");
        break;
    }
    Serial.println();
   }
  delay(1000);
  Serial.println();
}

void loop() {
  for (int8_t i=0;i<SENSOR_NUM;i++){
    d[i] = 0.0;
    r[i] = 0;
    sensor[i].getAngleValue(d[i]);
    sensor[i].getNumRevolutions(r[i]);
    Serial.print("\t");
    Serial.print(d[i]);
    Serial.print(",");
    Serial.print(r[i]);
  }
  Serial.println("");
  delay(100);
}
