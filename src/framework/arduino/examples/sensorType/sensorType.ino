/*!
 * \name        sensorType
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       prints register bit matrix and sensor interface type
 * \details
 * This example program prints the bit matrix of all registers and the sensors default
 * interface type and its settings.
 * From special registers MOD1,2,3,4 and IFAB the explicit sensor
 * interface set and the PCB board will be identified. See the Sensor manual for further
 * information on the different interfaces and the different sensor boards.
 *
 * \attention
 * Additional by removing the remarks on certain write functions, some sensor setups can
 * be set/unset or switched on/off.
 *
 */

#include <tlx5012-arduino.hpp>
#include "const.h"

using namespace tle5012;

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {};
  delay(5000);
  checkError  = Tle5012Sensor.begin();
  delay(1000);
  Serial.print("\n\ncheckError: ");
  Serial.println(checkError, HEX);

  /**
   * @brief You can use resetFirmware to set all register settings
   * back to factory defaults
   */
  //checkError = Tle5012Sensor.resetFirmware();

  /**
   * @brief You can set the sensor slave number to one of
   * four possible settings
   */
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
     Checkout the different auto calibration modes by removing the
     remarks. As each predefined interface has its default auto calibration
     mode, a restart or resetFirmware will set everything back to
     factory defaults.
  */
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.noAutoCal);
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode1);
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode2);
  //checkError = Tle5012Sensor.setCalibration(Tle5012Sensor.mode3);

  // read all registers
  checkError = Tle5012Sensor.readRegMap();
  Serial.print("Register Map checkError: ");
  Serial.println(checkError, HEX);

  // printout register binary values and sensor identity
  show_bin();
  show_identity();
  show_additional();
}

void loop() {
}

/**
 * @brief Function prints the binary code of each documented register
 *
 */
void show_bin()
{
  char nameOfRegister[MAX_NUM_REG][10] = {
    "STAT  ","ACSTAT","AVAL  ","ASPD  ","AREV  ",
    "FSYNC ","MOD1  ","SIL   ","MOD2  ","MOD3  ",
    "OFFX  ","OFFY  ","SYNCH ","IFAB  ","MOD4  ",
    "TCOY  ","ADCX  ","ADCY  ","DMAG  ","TRAW  ",
    "IIFCNT","T250  "
  };

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
    Serial.print(i);                         Serial.print("\t");
    Serial.print(nameOfRegister[i]);         Serial.print("\t");
    PRINTBINS(Tle5012Sensor.reg.regMap[i]);  Serial.println("");
  }
  Serial.flush();
}

/**
 * @brief This function prints the identity of the sensor which
 * is set as factory default inside the sensor fuses.
 *
 */
void show_identity()
{
  uint8_t interface = Tle5012Sensor.reg.getInterfaceMode();
  uint8_t slavenum  = Tle5012Sensor.reg.getSlaveNumber();

  Serial.println("----------------------------------------------------------------");
  Serial.print(sc_slave);
  Serial.print(slavenum, BIN);
  Serial.print(sc_slavename);
  Serial.print(slavenum);
  Serial.println("");
  Serial.print(sc_Interface);
  Serial.print(interface);

  switch (interface)
  {
    case Tle5012Sensor.reg.IIF:
      Serial.println(sc_IIF);
      iifInterface();
      break;
    case Tle5012Sensor.reg.PWM:
      Serial.println(sc_PWM);
      pwmInterface();
      break;
    case Tle5012Sensor.reg.HSM:
      Serial.println(sc_HSM);
      hsmInterface();
      break;
    case Tle5012Sensor.reg.SPC:
      Serial.println(sc_SPC);
      spcInterface();
      break;
  }
}

/**
 * @brief Sensor is set with PWM interface with the following settings
 *
 */
void pwmInterface()
{
  uint8_t value = 0;
  uint8_t firupdate = Tle5012Sensor.reg.getFIRUpdateRate();
  bool ifabout      = Tle5012Sensor.reg.isIFABOutputMode();

  Serial.print(sc_PCB);
  if (firupdate == 0x0 && ifabout )
  {
    Serial.print(Tle5012Sensor.reg.TLE5012B_E5000);
    Serial.println(sc_E5000);
  }else{
    Serial.print(Tle5012Sensor.reg.TLE5012B_E5020);
    Serial.println(sc_E5020);
  }
  Serial.print(sc_ifsetPWM);

  value = Tle5012Sensor.reg.getIFABres();
  Serial.print(sc_PWMfreq);
  Serial.print(value == 0 ? "244 Hz" : (value == 1 ? "488 Hz" : (value == 2 ? "977 Hz" : "1953 Hz")));

  value = Tle5012Sensor.reg.getHysteresisMode();
  Serial.print(sc_PWMtime);
  Serial.print(value == 0 ? "3.0 μs" : (value == 1 ? "2.5 μs" : (value == 2 ? "2.0 μs" : "1.5 μs")));

  Serial.print(sc_PWMfilter);
  Serial.print(Tle5012Sensor.reg.getFIRUpdateRate() ? "85.3 μs" : "42.7 μs");

  Serial.print(sc_PWMpin);
  Serial.print(ifabout ? sc_OpenDrain : sc_PushPull);
}

/**
 * @brief Sensor is set with IIF interface with the following settings
 *
 */
void iifInterface()
{
  uint8_t value = 0;

  Serial.print(sc_PCB);
  Serial.print(Tle5012Sensor.reg.TLE5012B_E1000);
  Serial.println(sc_E1000);

  Serial.print(sc_ifsetIIF);

  value = Tle5012Sensor.reg.getIIFMod();
  Serial.print(sc_IIFmod);
  Serial.print(value == 0
               ? sc_disable
               : (value == 1
                  ? sc_IIFab
                  : (value == 2
                    ? sc_IIFdirection
                    : sc_NotAllowed)));

  value = Tle5012Sensor.reg.getIFABres();
  Serial.print(sc_IIFres);
  Serial.print(value == 0 ? "0.088° step" : (value == 1 ? "0.176° step" : (value == 2 ? "0.352° step" : "0.703° step")));

  value = Tle5012Sensor.reg.getHysteresisMode();
  Serial.print(sc_IIFhyster);
  Serial.print(value == 0 ? "HSM: 0°" : (value == 1 ? "HSM: 0.175°" : (value == 2 ? "HSM: 0.35°" : "HSM: 0.70°")));

  Serial.print(sc_IIFfilter);
  Serial.print(Tle5012Sensor.reg.getFIRUpdateRate() ? "85.3 μs" : "42.7 μs");

  Serial.print(sc_IIFpin);
  Serial.print(Tle5012Sensor.reg.isIFABOutputMode() ? sc_OpenDrain : sc_PushPull);
}

/**
 * @brief Sensor is set with IIF interface with the following settings
 *
 */
void hsmInterface()
{
  uint8_t value = 0;

  Serial.print(sc_PCB);
  Serial.print(Tle5012Sensor.reg.TLE5012B_E3005);
  Serial.println(sc_E3005);

  Serial.print(sc_ifsetHSM);

  value = Tle5012Sensor.reg.getIFABres();
  Serial.print(sc_HSMframe);
  Serial.print(value == 0 ? sc_Angle12 : (value == 1 ? sc_Angle16 : (value == 2 ? sc_Angle12Temp : sc_Angle16Temp)));

  value = Tle5012Sensor.reg.getHysteresisMode();
  Serial.print(sc_HSMhyster);
  Serial.print(value == 0 ? "0°" : (value == 1 ? "0.175°" : (value == 2 ? "0.35°" : "0.70°")));

  Serial.print(sc_HSMfilter);
  Serial.print(Tle5012Sensor.reg.getFIRUpdateRate() ? "85.3 μs" : "42.7 μs");

  Serial.print(sc_HSMpin);
  Serial.print(Tle5012Sensor.reg.isIFABOutputMode() ? sc_OpenDrain : sc_PushPull);
}

/**
 * @brief Sensor is set with SPC interface with the following settings
 *
 */
void spcInterface()
{
  uint8_t value = 0;

  Serial.print(sc_PCB);
  Serial.print(Tle5012Sensor.reg.TLE5012B_E9000);
  Serial.println(sc_E9000);

  Serial.print(sc_ifsetSPC);

  value = Tle5012Sensor.reg.getIFABres();
  Serial.print(sc_SPCframe);
  Serial.print(value == 0 ? sc_Angle12 : (value == 1 ? sc_Angle16 : (value == 2 ? sc_Angle12Temp : sc_Angle16Temp)));

  value = Tle5012Sensor.reg.getHysteresisMode();
  Serial.print(sc_SPCtime);
  Serial.print(value == 0 ? "3.0 μs" : (value == 1 ? "2.5 μs" : (value == 2 ? "2.0 μs" : "1.5 μs")));

  value = Tle5012Sensor.reg.getHSMplp();
  Serial.print(sc_SPCtrigger);
  Serial.print(value == 0 ? "90 μs" : "t_mlow + 12 UT");

  Serial.print(sc_SPCpin);
  Serial.print(Tle5012Sensor.reg.isIFABOutputMode() ? sc_OpenDrain : sc_PushPull);
}

/**
 * @brief Shows additional information for each sensor type
 * from the additional registers MOD2 and MOD3
 *
 */
void show_additional()
{
  uint8_t value = 0;

  Serial.println();
  value = Tle5012Sensor.reg.getCalibrationMode();
  Serial.print(sc_MOD2cal);
  Serial.print(value == 0
              ? sc_Cal1
              : (value == 1
                 ? sc_Cal1
                 : (value == 2
                    ? sc_Cal2
                    : sc_Cal3)));

  Serial.print(sc_MOD2predict);
  Serial.print(Tle5012Sensor.reg.isPrediction() ? sc_enable : sc_disable);

  value = Tle5012Sensor.reg.getPadDriver();
  Serial.print(sc_MODpin);
  Serial.print(value == 0
              ? sc_MODstrongfast
              : (value == 1
                 ? sc_MODstrongslow
                 : (value == 2
                    ? sc_MODweakfast
                    : sc_MODweakslow)));

  Serial.print(sc_MODssc);
  Serial.print(Tle5012Sensor.reg.isSSCOutputMode() ? sc_PushPull : sc_OpenDrain);

  Serial.print(sc_MODvoltage);
  Serial.print(Tle5012Sensor.reg.isSpikeFilter() ? sc_Spikeenable : sc_Spikedisbale);
}
