/*!
 * \name        Read_Sensor_Type
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.1
 * \brief
 * This example program reads all documented registers and print out the binary
 * register map. From special registers MOD1,2,3,4 and IFAB the explicit sensor
 * interface set and the PCB board will be identified. See the Sensor manual for further
 * information on the different interfaces and the different sensor boards.
 *
 * \attention
 * Additional by removing the remarks on certain write functions, some sensor setups can
 * be set/unset or switched on/off.
 *
 * \attention This Sketch needs more memroy then the Arduino/Genuino UNO has so some
 * routines are not available
 */

#include <TLE5012-ino.hpp>

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {};
  Serial.println("init done!");
  checkError  = Tle5012Sensor.begin();
  Serial.print("checkerror: "); Serial.println(checkError, HEX);
  //checkError = Tle5012Sensor.resetFirmware();
  Tle5012Sensor.writeSlaveNumber(Tle5012Sensor.TLE5012B_S0);
  /*
     Checkout one of these interface modes. Each Sensor2go board
     comes with a predefined interface, but this can be changed
     during the runtime. A restart or with the resetFirmware function
     the changes will be set to the factory defaults.
  */
  //checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.IIF);
  //checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.PWM);
  //checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.HSM);
  //checkError = Tle5012Sensor.writeInterfaceType(Tle5012Sensor.SPC);

  /*
     Checkout the different autocalibration modes by removing the
     remarks. As each predefined interface has its default auto calibration
     mode, a restart or resetFirmware will set everything back to
     factory defaults.
  */
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.noAutoCal);
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode1);
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode2);
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode3);

  // read all registers
  //checkError = Tle5012Sensor.identifyInterfaceType();

  checkError = Tle5012Sensor.readRegMap();
  Serial.print("checkerror: "); Serial.println(checkError, HEX);

  // printout register binary values
  show_bin();

//  /*
//     Prints the sensor board type, interface and slave number
//  */
//  Serial.println("----------------------------------------------------------------------------------------------------------------");
//  Serial.print("Identified Sensor PCB: " );
//  Serial.print(Tle5012Sensor.sensorRegister.sensorBoard);
//  Serial.print(" = ");
//  Serial.print(Tle5012Sensor.sensorRegister.sensorName);
//  Serial.println("");
//
//  Serial.print("Identified Interface:  ");
//  Serial.print(Tle5012Sensor.sensorRegister.interface);
//  Serial.print(" = ");
//  Serial.print(Tle5012Sensor.sensorRegister.interfaceName);
//  Serial.println("");
//
//  Serial.print("Identified Slave:      ");
//  Serial.print(Tle5012Sensor.sensorRegister.stat.SNR, BIN);
//  Serial.print(" = TLE5012_S");
//  Serial.print(Tle5012Sensor.sensorRegister.stat.SNR);
//  Serial.println("");
//
//  /*
//     This part fetches additional interface dependent
//     data and prints them.
//     This part can not be used on the original Arduino/Genuino Uno due to memory limitations
//  */
//#if !defined(__AVR_ATmega328P__) 
//  uint16_t val = 0;
//  uint16_t mod1 = Tle5012Sensor.sensorRegister.mod1.reg;
//  uint16_t mod4 = Tle5012Sensor.sensorRegister.mod4.reg;
//  uint16_t ifab = Tle5012Sensor.sensorRegister.ifab.reg;
//  switch (Tle5012Sensor.sensorRegister.interface) {
//    case 0:
//      Serial.print("\nIIF Interface settings\n");
//
//      val = Tle5012Sensor.sensorRegister.mod1.fetch_IIFMOD(mod1);
//      Serial.print("\nMOD1 IIF Mode:          \t");
//      Serial.print(val == 0
//                   ? "disabled"
//                   : (val == 1
//                      ? "A/B operation with Index on IFC pin"
//                      : (val == 2
//                         ? "Step/Direction operation with Index on IFC pin"
//                         : "not allowed")));
//
//
//      val = Tle5012Sensor.sensorRegister.mod4.fetch_IFABRES(mod4);
//      Serial.print("\nMOD4 Resolution:        \t");
//      Serial.print(val == 0 ? "0.088° step" : (val == 1 ? "0.176° step" : (val == 2 ? "0.352° step" : "0.703° step")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFADHYST(ifab);
//      Serial.print("\nIFAB Hysteresis:        \t");
//      Serial.print(val == 0 ? "HSM: 0°" : (val == 1 ? "HSM: 0.175°" : (val == 2 ? "HSM: 0.35°" : "HSM: 0.70°")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_FIRUDR(ifab);
//      Serial.print("\nIFAB Filter update time:\t");
//      Serial.print(val ? "85.3 μs" : "42.7 μs");
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFABOD(ifab);
//      Serial.print("\nIFAB IFA pin:           \t");
//      Serial.print(val ? "Open Drain" : "Push-Pull");
//
//      break;
//    case 1:
//      Serial.print("\nPWM Interface settings\n");
// 
//      val = Tle5012Sensor.sensorRegister.mod4.fetch_IFABRES(mod4);
//      Serial.print("\nMOD4 Frequnecy:         \t");
//      Serial.print(val == 0 ? "244 Hz" : (val == 1 ? "488 Hz" : (val == 2 ? "977 Hz" : "1953 Hz")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFADHYST(ifab);
//      Serial.print("\nIFAB Unit time:         \t");
//      Serial.print(val == 0 ? "3.0 μs" : (val == 1 ? "2.5 μs" : (val == 2 ? "2.0 μs" : "1.5 μs")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_FIRUDR(ifab);
//      Serial.print("\nIFAB Filter update time:\t");
//      Serial.print(val ? "85.3 μs" : "42.7 μs");
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFABOD(ifab);
//      Serial.print("\nIFAB IFA pin:           \t");
//      Serial.print(val ? "Open Drain" : "Push-Pull");
//
//      break;
//    case 2:
//      Serial.print("\nHSM Interface settings\n");
//
//      val = Tle5012Sensor.sensorRegister.mod4.fetch_IFABRES(mod4);
//      Serial.print("\nMOD4 Frame config:      \t");
//      Serial.print(val == 0 ? "12bit angle" : (val == 1 ? "16bit angle" : (val == 2 ? "12bit angle + 8bit temperature" : "16bit angle + 8bit temperature")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFADHYST(ifab);
//      Serial.print("\nIFAB Hysteresis:        \t");
//      Serial.print(val == 0 ? "0°" : (val == 1 ? "0.175°" : (val == 2 ? "0.35°" : "0.70°")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_FIRUDR(ifab);
//      Serial.print("\nIFAB Filter update time:\t");
//      Serial.print(val ? "85.3 μs" : "42.7 μs");
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFABOD(ifab);
//      Serial.print("\nIFAB IFA pin:           \t");
//      Serial.print(val ? "Open Drain" : "Push-Pull");
//      break;
//    case 3:
//      Serial.print("\nSPC Interface settings\n");
//
//      val = Tle5012Sensor.sensorRegister.mod4.fetch_IFABRES(mod4);
//      Serial.print("\nMOD4 Frame config:      \t");
//      Serial.print(val == 0 ? "12bit angle" : (val == 1 ? "16bit angle" : (val == 2 ? "12bit angle + 8bit temperature" : "16bit angle + 8bit temperature")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFADHYST(ifab);
//      Serial.print("\nIFAB Unit time:         \t");
//      Serial.print(val == 0 ? "3.0 μs" : (val == 1 ? "2.5 μs" : (val == 2 ? "2.0 μs" : "1.5 μs")));
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_FIRUDR(ifab);
//      Serial.print("\nIFAB Filter update time:\t");
//      Serial.print(val ? "85.3 μs" : "42.7 μs");
//
//      val = Tle5012Sensor.sensorRegister.ifab.fetch_IFABOD(ifab);
//      Serial.print("\nIFAB IFA pin:           \t");
//      Serial.print(val ? "Open Drain" : "Push-Pull");
//      break;
//  }
//  mod2(Tle5012Sensor.sensorRegister.mod2.reg);
//  mod3(Tle5012Sensor.sensorRegister.mod3.reg);
//
//#endif
//
//  //Serial.end();
}

void loop() {
}

/*!
   Function prints the binary code of each documented register
*/
void show_bin()
{
  Serial.print("\t\t");
  for (int8_t i = 15; i > -1; i--)
  {
    Serial.print(" ");
    Serial.print(i, HEX);
    Serial.print(" ");
  }
  Serial.println("\n\t\t------------------------------------------------");
  for (int8_t i = 0; i < MAX_NUM_REG; i++)
  {
    Serial.print(i);                                              Serial.print("\t");
    Serial.print(Tle5012Sensor.sensorRegister.nameOfRegister[i]); Serial.print("\t");
    PRINTBINS(Tle5012Sensor.reg.regMap[i]);                       Serial.println("");
  }
}

///*!
//   Function prints register mod2
//*/
//void mod2(uint16_t reg)
//{
//  uint16_t val = 0;
//  Serial.println();
//  val = Tle5012Sensor.sensorRegister.mod2.fetch_AUTOCAL(reg);
//  Serial.print("\nMOD2 Autocalibration:   \t");
//  Serial.print(val == 0
//               ? "no auto-calibration"
//               : (val == 1
//                  ? "auto-cal. mode 1: update every angle update cycle"
//                  : (val == 2
//                     ? "auto-cal. mode 2: update every 1.5 revolutions"
//                     : "auto-cal. mode 3: update every 11.25°")));
//
//  val = Tle5012Sensor.sensorRegister.mod2.fetch_PREDICT(reg);
//  Serial.print("\nMOD2 Prediction:        \t");
//  Serial.print(val ? "enabled" : "disabled");
//}
//
///*!
//   Function prints register mod3
//*/
//void mod3(uint16_t reg)
//{
//  uint16_t val = 0;
//  Serial.println();
//  val = Tle5012Sensor.sensorRegister.mod3.fetch_PADDRV(reg);
//  Serial.print("\nMOD3 IFA/B/C pin set:   \t");
//  Serial.print(val == 0
//               ? "strong driver, DATA: strong driver, fast edge"
//               : (val == 1
//                  ? "strong driver, DATA: strong driver, slow edge"
//                  : (val == 2
//                     ? "weak driver, DATA: medium driver, fast edge"
//                     : "weak driver, DATA: weak driver, slow edge")));
//
//  val = Tle5012Sensor.sensorRegister.mod3.fetch_SSCOD(reg);
//  Serial.print("\nMOD3 SSC interface:     \t");
//  Serial.print(val ? "Push-Pull" : "Open Drain");
//
//  val = Tle5012Sensor.sensorRegister.mod3.fetch_SPIKEF(reg);
//  Serial.print("\nMOD3 Voltage filter:    \t");
//  Serial.print(val ? "spike filter enabled" : "spike filter disabled");
//}
