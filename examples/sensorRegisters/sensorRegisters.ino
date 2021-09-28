/*!
 * \name        sensorRegisters
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     3.0.1
 * \brief       Reads all sensor registers and reports there status
 * \details
 * This example program will read all documented registers from the sensor and
 * writes this to the serial port with remark info for each register.
 * Please have look to the sensor manual for more and more detailed information
 * about each register.
 * 
 * \attention This Sketch needs ca. 35kB of memory and does not compile on the original
 * Arduino/Genuino Uno. Use the sensorType.ino instead
 * 
 * SPDX-License-Identifier: MIT
 *
 */

 #if defined(__AVR_ATmega328P__) 
 // Needs more memory than the Arduino/Genuino UNO has
 void setup()
 {
   delay(1000);
   Serial.begin(115200);
   while (!Serial) {};
   Serial.println("STOP: this sketch needs more memory than available");
 }

void loop()
{
}

#else

#include <TLE5012-ino.hpp>
#include "const.h"

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;


void printval(uint16_t regValue, String regType)
{
  Serial.print("0x");
  Serial.print(regValue,HEX);
  Serial.print("\t");

  Serial.print(regValue);
  Serial.print("\t");

  Serial.print(regType);
  Serial.print("\t");
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

void show_STAT()
{
  boolean valb;

  Serial.print("\nRegister:\tSTAT\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_STAT,HEX);

  valb = Tle5012Sensor.reg.isStatusRead();
  Serial.print(sc_rdst);
  printval(valb,"1,  boolean\tr\t15:15 ");
  Serial.println(valb ? sc_RDST0 : sc_RDST1);

  Serial.print(sc_snr);
  printval(Tle5012Sensor.reg.getSlaveNumber(),"2,  uint8_t\trw\t13:14 ");
  Serial.println(sc_SNR0);

  valb = Tle5012Sensor.reg.isStatusGMRA();
  Serial.print(sc_nogmra);
  printval(valb,"1,  boolean\tru\t12   ");
  Serial.println(valb ? sc_NOGMRA0 : sc_NOGMRA1);

  valb = Tle5012Sensor.reg.isStatusGMRXY();
  Serial.print(sc_nogmrxy);
  printval(valb,"1,  boolean\tru\t11   ");
  Serial.println(valb ? sc_NOGMRXY0 : sc_NOGMRXY1);

  valb = Tle5012Sensor.reg.isStatusROM();
  Serial.print(sc_srom);
  printval(valb,"1,  boolean\tr\t10    ");
  Serial.println(valb ? sc_SROM0 : sc_SROM1);

  valb = Tle5012Sensor.reg.isStatusADC();
  Serial.print(sc_sadct);
  printval(valb,"1,  boolean\tr\t9     ");
  Serial.println(valb ? sc_SADCT0 : sc_SADCT1);

  valb = Tle5012Sensor.reg.isStatusMagnitideOutOfLimit();
  Serial.print(sc_smagol);
  printval(valb,"1,  boolean\tru\t7    ");
  Serial.println(valb ? sc_SMAGOL0 : sc_SMAGOL1);

  valb = Tle5012Sensor.reg.isStatusXYOutOfLimit();
  Serial.print(sc_sxyol);
  printval(valb,"1,  boolean\tru\t6    ");
  Serial.println(valb ? sc_SXYOL0 : sc_SXYOL1);

  valb = Tle5012Sensor.reg.isStatusOverflow();
  Serial.print(sc_sov);
  printval(valb,"1,  boolean\tru\t5    ");
  Serial.println(valb ? sc_SOV0 : sc_SOV1);

  valb = Tle5012Sensor.reg.isStatusDSPU();
  Serial.print(sc_sdspu);
  printval(valb,"1,  boolean\tr\t4     ");
  Serial.println(valb ? sc_SDSPU0 : sc_SDSPU1);

  valb = Tle5012Sensor.reg.isStatusFuse();
  Serial.print(sc_sfuse);
  printval(valb,"1,  boolean\tr\t3     ");
  Serial.println(valb ? sc_SFUSE0 : sc_SFUSE1);

  valb = Tle5012Sensor.reg.isStatusVoltage();
  Serial.print(sc_svr);
  printval(valb,"1,  boolean\tr\t2     ");
  Serial.println(valb ? sc_SVR0 : sc_SVR1);

  valb = Tle5012Sensor.reg.isStatusWatchDog();
  Serial.print(sc_swd);
  printval(valb,"1,  boolean\tr\t1     ");
  Serial.println(valb ? sc_SWD0 : sc_SWD1);

  valb = Tle5012Sensor.reg.isStatusReset();
  Serial.print(sc_srst);
  printval(valb,"1,  boolean\tr\t0     ");
  Serial.println(valb ? sc_SRST0 : sc_SRST1);
}

void show_ACSTAT()
{
  boolean valb;

  Serial.print("\nRegister:\tACSTAT\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_ACSTAT,HEX);

  valb = Tle5012Sensor.reg.isFirmwareReset();
  Serial.print(sc_asfrst);
  printval(valb,"1,  boolean\truw\t10  ");
  Serial.println(valb ? sc_ASFRST0 : sc_ASFRST1);

  valb = Tle5012Sensor.reg.isADCCheck();
  Serial.print(sc_asadct);
  printval(valb,"1,  boolean\truw\t9   ");
  Serial.println(valb ? sc_ASADCT0 : sc_ASADCT1);

  valb = Tle5012Sensor.reg.isGMRCheck();
  Serial.print(sc_asvegmag);
  printval(valb,"1,  boolean\truw\t7   ");
  Serial.println(valb ? sc_ASVEGMAG0 : sc_ASVEGMAG1);

  valb = Tle5012Sensor.reg.isXYCheck();
  Serial.print(sc_asvecxy);
  printval(valb,"1,  boolean\truw\t6   ");
  Serial.println(valb ? sc_ASVECXY0 : sc_ASVECXY1);

  valb = Tle5012Sensor.reg.isDSPUoverflow();
  Serial.print(sc_asov);
  printval(valb,"1,  boolean\truw\t5   ");
  Serial.println(valb ? sc_ASOV0 : sc_ASOV1);

  valb = Tle5012Sensor.reg.isDSPUbist();
  Serial.print(sc_asdspu);
  printval(valb,"1,  boolean\truw\t4   ");
  Serial.println(valb ? sc_ASDSPU0 : sc_ASDSPU1);

  valb = Tle5012Sensor.reg.isFuseCRC();
  Serial.print(sc_asfuse);
  printval(valb,"1,  boolean\truw\t3   ");
  Serial.println(valb ? sc_ASFUSE0 : sc_ASFUSE1);

  valb = Tle5012Sensor.reg.isVoltageCheck();
  Serial.print(sc_asvr);
  printval(valb,"1,  boolean\truw\t2   ");
  Serial.println(valb ? sc_ASVR0 : sc_ASVR1);

  valb = Tle5012Sensor.reg.isWatchdog();
  Serial.print(sc_aswd);
  printval(valb,"1,  boolean\truw\t1   ");
  Serial.println(valb ? sc_ASWD0 : sc_ASWD1);

  valb = Tle5012Sensor.reg.isActivationReset();
  Serial.print(sc_asrst);
  printval(valb,"1,  boolean\truw\t0   ");
  Serial.println(valb ? sc_ASRST0 : sc_ASRST1);
}

void show_MAINA()
{
  boolean valb;

  Serial.print("\nRegister:\tAVAL\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_AVAL,HEX);

  valb = Tle5012Sensor.reg.isAngleValueNew();
  Serial.print(sc_rdav);
  printval(valb,"1,  boolean\tr\t15    ");
  Serial.println(valb ? sc_RDAV0 : sc_RDAV1);

  Serial.print(sc_angval);
  printval(Tle5012Sensor.reg.getAngleValue(),"16, uint16_t\tru\t0:14 ");
  Serial.println(sc_ANGVAL);


  Serial.print("\nRegister:\tASPD\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_ASPD,HEX);

  valb = Tle5012Sensor.reg.isSpeedValueNew();
  Serial.print(sc_rdas);
  printval(valb,"1,  boolean\tr\t15    ");
  Serial.println(valb ? sc_RDAS0 : sc_RDAS1);

  Serial.print(sc_angspd);
  printval(Tle5012Sensor.reg.getSpeedValue(),"16, uint16_t\tru\t0:14 ");
  Serial.println(sc_ANGSPD);


  Serial.print("\nRegister:\tAREV\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_AREV,HEX);

  valb = Tle5012Sensor.reg.isNumberOfRevolutionsNew();
  Serial.print(sc_rdrev);
  printval(valb,"1,  boolean\tr\t15    ");
  Serial.println(valb ? sc_RDREV0 : sc_RDREV1);

  Serial.print(sc_fcnt);
  printval(Tle5012Sensor.reg.getNumberOfRevolutions(),"6,  uint8_t\truw\t9:14 ");
  Serial.println(sc_FCNT);

  Serial.print(sc_revol);
  printval(Tle5012Sensor.reg.getFrameCounter(),"8,  uint16_t\tru\t0:8 ");
  Serial.println(sc_REVOL);


  Serial.print("\nRegister:\tFSYNC\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_FSYNC,HEX);

  Serial.print(sc_tempr);
  printval(Tle5012Sensor.reg.getFrameSyncCounter(),"7,  int16_t\trw\t9:15 ");
  Serial.println(sc_TEMPR);

  Serial.print(sc_fsync);
  printval(Tle5012Sensor.reg.getTemperatureValue(),"9,  uint16_t\tr\t0:9  ");
  Serial.println(sc_FSYNC);
}


void show_MOD1()
{
  uint16_t val = 0;
  boolean valb;

  Serial.print("\nRegister:\tMOD1\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_MOD_1,HEX);

  val = Tle5012Sensor.reg.getFilterDecimation();
  Serial.print(sc_firmd);
  printval(val,"2, uint8_t \trw\t14:15");
  Serial.println(
              val == 0
                ? sc_FIRMD0
                : (val == 1
                  ? sc_FIRMD1
                  : (val == 2
                    ? sc_FIRMD2
                    : sc_FIRMD3)));

  valb = Tle5012Sensor.reg.statusClockSource();
  Serial.print(sc_clksel);
  printval(valb,"1, boolean \tru \t4   ");
  Serial.println(valb ? sc_CLKS0 : sc_CLKS1);

  valb = Tle5012Sensor.reg.isDSPUhold();
  Serial.print(sc_dsphold);
  printval(valb,"1, boolean \trw\t2     ");
  Serial.println(valb ? sc_DSPU0 : sc_DSPU1);

  val = Tle5012Sensor.reg.getIIFMod();
  Serial.print(sc_mod1);
  printval(val,"2, uint8_t \trw\t0:1  ");
  Serial.println(
              val == 0
                ? sc_IIF0
                : (val == 1
                  ? sc_IIF1
                  : (val == 2
                    ? sc_IIF2
                    : sc_IIF3)));
}

void show_SIL()
{
  uint16_t val = 0;
  boolean valb;

  Serial.print("\nRegister:\tSIL\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_SIL,HEX);

  valb = Tle5012Sensor.reg.isFilterParallel();
  Serial.print(sc_filterpar);
  printval(valb,"1, boolean \trw\t15   ");
  Serial.println(valb ? sc_FPAR0 : sc_FPAR1);

  valb = Tle5012Sensor.reg.isFilterInverted();
  Serial.print(sc_filtinv);
  printval(valb,"1, boolean \trw\t14   ");
  Serial.println(valb ? sc_FINV0 : sc_FINV1);

  valb = Tle5012Sensor.reg.getFulseReload();
  Serial.print(sc_fuserel);
  printval(valb,"1, boolean \trw\t10   ");
  Serial.println(valb ? sc_FREL0 : sc_FREL1);

  valb = Tle5012Sensor.reg.isADCTestVector();
  Serial.print(sc_adctven);
  printval(valb,"1, boolean \trw\t6    ");
  Serial.println(valb ? sc_AVEN0 : sc_AVEN1);

  val = Tle5012Sensor.reg.getTestVectorY();
  Serial.print(sc_adctvy);
  printval(val,"3, uint16_t\trw\t3:5  ");
  Serial.print(sc_ADCY);
  Serial.println(
                val == 0
                  ? sc_adctv0
                  : (val == 1
                    ? sc_adctv1
                    : (val == 2
                      ? sc_adctv2
                      : (val == 3
                        ? sc_adctv3
                        : (val == 5
                          ? sc_adctv4
                            : (val == 6
                              ? sc_adctv5
                              : sc_adctv6))))));

  val = Tle5012Sensor.reg.getTestVectorX();
  Serial.print(sc_adctvx);
  printval(val,"3, uint16_t\trw\t0:2  ");
  Serial.print(sc_ADCX);
  Serial.println(
                val == 0
                  ? sc_adctv0
                  : (val == 1
                    ? sc_adctv1
                    : (val == 2
                      ? sc_adctv2
                      : (val == 3
                        ? sc_adctv3
                        : (val == 5
                          ? sc_adctv4
                            : (val == 6
                              ? sc_adctv5
                              : sc_adctv6))))));
}

void show_MOD2()
{
  uint16_t val = 0;
  boolean valb;

  Serial.print("\nRegister:\tMOD2\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_MOD_2,HEX);

  val = Tle5012Sensor.reg.getAngleRange();
  Serial.print(sc_angrange);
  printval(val,"1, boolean \trw\t11:14");
  Serial.println(
                val == 0x080
                  ? sc_arng0
                  : (val == 0x200
                    ? sc_arng1
                    : sc_arng2));

  valb = Tle5012Sensor.reg.isAngleDirection();
  Serial.print(sc_angdir);
  printval(valb,"1, boolean \trw\t10  ");
  Serial.println(valb ? sc_adir0 :sc_adir1);

  valb = Tle5012Sensor.reg.isPrediction();
  Serial.print(sc_predict);
  printval(valb,"1, boolean \trw\t2   ");
  Serial.println(valb ? sc_pred0 :sc_pred1);

  val = Tle5012Sensor.reg.getCalibrationMode();
  Serial.print(sc_autocal);
  printval(val,"2, uint8_t \trw\t0:1  ");
  Serial.println(
                val == 0
                  ? sc_aucl0
                  : (val == 1
                    ? sc_aucl1
                    : (val == 2
                      ? sc_aucl2
                      : sc_aucl3)));
}

void show_MOD3()
{
  uint16_t val = 0;
  boolean valb;

  Serial.print("\nRegister:\tMOD3\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_MOD_3,HEX);

  val = Tle5012Sensor.reg.getAngleBase();
  Serial.print(sc_angbase);
  printval(val,"12,uint16_t \trw\t4:15");
  Serial.print("Angle Base at 0°: ");
  Serial.println(
                val == 0x800
                  ? sc_angb0
                  : (val == 0
                    ? sc_angb1
                    : sc_angb2));

  val = Tle5012Sensor.reg.getPadDriver();
  Serial.print(sc_paddrv);
  printval(val,"2,  uint8_t      rw \t0:1");
  Serial.print("Config of Pad-Driver: ");
  Serial.println(
                val == 0
                  ? sc_pad0
                  : (val == 1
                    ? sc_pad1
                    : (val == 2
                      ? sc_pad2
                      : sc_pad3)));

  valb = Tle5012Sensor.reg.isSSCOutputMode();
  Serial.print(sc_sscod);
  printval(valb,"1, boolean \trw\t2   ");
  Serial.println(valb ? sc_ssco0 :sc_ssco1);

  valb = Tle5012Sensor.reg.isSpikeFilter();
  Serial.print(sc_spikef);
  printval(valb,"1, boolean \trw\t3   ");
  Serial.println(valb ? sc_spik0 :sc_spik1);
}

void show_OFFSETS()
{
  Serial.print("\nRegister:\tOFFX\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_OFFX,HEX);
  Serial.print(sc_xoff);
  printval(Tle5012Sensor.reg.getOffsetX(),"12, int16_t\trw\t4:15 ");
  Serial.println(sc_XOFFSET);

  Serial.print("\nRegister:\tOFFY\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_OFFY,HEX);
  Serial.print(sc_yoff);
  printval(Tle5012Sensor.reg.getOffsetY(),"12, int16_t\trw\t4:15 ");
  Serial.println(sc_YOFFSET);

  Serial.print("\nRegister:\tSYNCH\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_SYNCH,HEX);
  Serial.print(sc_sync);
  printval(Tle5012Sensor.reg.getAmplitudeSynch(),"12, int16_t\trw\t4:15 ");
  Serial.println(sc_SYNCH);
}

void show_IFAB()
{
  uint16_t val = 0;
  boolean valb;
  uint8_t iface = Tle5012Sensor.reg.getInterfaceMode();

  Serial.print("\nRegister:\tIFAB\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_IFAB,HEX);

  Serial.print(sc_ortho);
  printval(Tle5012Sensor.reg.getOrthogonality(),"3, uint16_t\trw\t4:15 ");
  Serial.println(sc_ORTH);

  val = Tle5012Sensor.reg.getHysteresisMode();
  Serial.print(sc_hyst);
  printval(val,"2, uint8_t \trw\t0:1  \tHSM and IIF Mode:");
  Serial.println(
              (iface == 0 || iface == 2
                ? (val == 0
                  ? "00b HSM: 0°"
                  : (val == 1
                    ? "01b HSM: 0.175°"
                    : (val == 2
                      ? "10b HSM: 0.35°"
                      : "11b HSM: 0.70°")))
                : (iface == 3
                  ? (val == 0
                    ? "00b SPC: 3.0 μs"
                    : (val == 1
                      ? "01b SPC: 2.5 μs"
                      : (val == 2
                        ? "10b SPC: 2.0 μs"
                        : "11b SPC: 1.5 μs")))
                  : "none")
                )
              );

  val = Tle5012Sensor.reg.getFIRUpdateRate();
  Serial.print(sc_fir);
  printval(val,"1, boolean \trw\t2   ");
  Serial.println(valb ? sc_fir0 : sc_fir1);

  val = Tle5012Sensor.reg.isIFABOutputMode();
  Serial.print(sc_ifabod);
  printval(val,"1, boolean \trw\t2   ");
  Serial.println(valb ? sc_PushPull : sc_PushPull);
}

void show_MOD4()
{
  uint16_t val = 0;
  boolean valb;
  uint8_t iface = Tle5012Sensor.reg.getInterfaceMode();

  Serial.print("\nRegister:\tMOD4\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_MOD_4,HEX);

  Serial.print(sc_tcoxt);
  printval(Tle5012Sensor.reg.getOffsetTemperatureX(),"7,  int8_t\t\trw\t9:15  ");
  Serial.println(sc_TCOXT);

  val = Tle5012Sensor.reg.getHSMplp();
  Serial.print(sc_hsmplp);
  printval(val,"2,  uint8_t\trw\t5:8  ");
  Serial.println(
    (iface == 0
      ? sc_hsm0
      : (iface == 1
        ? sc_hsm1
        : (iface == 2
          ? sc_hsm2
          : (iface == 3
            ? sc_hsm3
            : sc_hsm4)))));

  val = Tle5012Sensor.reg.getIFABres();
  Serial.print(sc_ifabres);
  printval(val,"2,  uint8_t\trw\t3:4  ");
  Serial.println(
          (iface == 1
            ? (val == 0
              ? "00b PWM: 244 Hz"
              : (val == 1
                ? "01b PWM: 488 Hz"
                : (val == 2
                  ? "10b PWM: 977 Hz"
                  : "11b PWM: 1953 Hz")))
            : (iface == 0
                ? (val == 0
                  ? "00b IIF: 12bit, 0.088° step"
                  : (val == 1
                    ? "01b IIF: 11bit, 0.176° step"
                    : (val == 2
                      ? "10b IIF: 10bit, 0.352° step"
                      : "11b IIF: 9bit, 0.703° step")))
                : (iface == 3
                  ? (val == 0
                    ? "00b SPC: 00B 12bit angle"
                    : (val == 1
                      ? "01b SPC: 01B 16bit angle"
                      : (val == 2
                        ? "10b SPC: 10B 12bit angle + 8bit temperature"
                        : "11b SPC: 11B 16bit angle + 8bit temperature")))
                  : "none")
          )));

  Serial.print(sc_ifmd);
  printval(Tle5012Sensor.reg.getInterfaceMode(),"2,  uint8_t\trw\t0:1  ");
  Serial.print(sc_IFDM0);
  Serial.println(Tle5012Sensor.reg.getInterfaceMode());
}

void show_TCOTY()
{
  uint16_t val = 0;
  boolean valb;

  Serial.print("\nRegister:\tTCOY\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_TCO_Y,HEX);

  Serial.print(sc_tcoyt);
  printval(Tle5012Sensor.reg.getOffsetTemperatureY(),"7, int8_t  \tr\t9:15  ");
  Serial.println(sc_TCOYT);

  valb = Tle5012Sensor.reg.isStartupBist();
  Serial.print(sc_sbist);
  printval(valb,"1,  boolean\trw\t8    ");
  Serial.println(valb ? sc_BISTenable : sc_BISTdisable);

  Serial.print(sc_crcpar);
  printval(Tle5012Sensor.reg.getCRCpar(),"7,  int8_t\t\trw\t0:7   ");
  Serial.println(sc_CPAR);
}

void show_ADC()
{
  Serial.print("\nRegister:\tADCX\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_ADC_X,HEX);
  Serial.print(sc_adcx);
  printval(Tle5012Sensor.reg.getADCx(),"16, int16_t\tr\t0:15  ");
  Serial.println("");

  Serial.print("\nRegister:\tADCY\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_ADC_Y,HEX);
  Serial.print(sc_adcy);
  printval(Tle5012Sensor.reg.getADCy(),"16, int16_t\tr\t0:15  ");
  Serial.println("");

  Serial.print("\nRegister:\tDMAG\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_D_MAG,HEX);
  Serial.print(sc_mag);
  printval(Tle5012Sensor.reg.getVectorMagnitude(),"9,  uint16_t\tru\t0:9  ");
  Serial.println(sc_MAG);

  Serial.print("\nRegister:\tTRAW\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_T_RAW,HEX);
  Serial.print(sc_ttgl);
  printval(Tle5012Sensor.reg.getTemperatureRAW(),"1,  boolean\tr\t15    ");
  Serial.println(sc_TRAWTTGL);

  Serial.print("\nRegister:\tIIFCNT\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_IIF_CNT,HEX);
  Serial.print(sc_iifcnt);
  printval(Tle5012Sensor.reg.getCounterIncrements(),"13, uint16_t    r   \t0:13 ");
  Serial.println(sc_TRAWIIFCNT);

  Serial.print("\nRegister:\tT250\tOffset: 0x");
  Serial.println(Tle5012Sensor.reg.REG_T25O,HEX);
  Serial.print(sc_t250);
  printval(Tle5012Sensor.reg.getT25Offset(),"9,  int16_t\tr\t9:15  ");
  Serial.println(sc_T250);
}



void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {};
  checkError = Tle5012Sensor.begin();
  Serial.print("checkerror: "); Serial.println(checkError,HEX);
  delay(1000);

  // read all registers
  checkError = Tle5012Sensor.readRegMap();
  show_bin();

  show_STAT();
  show_ACSTAT();
  show_MAINA();
  show_MOD1();
  show_SIL();
  show_MOD2();
  show_MOD3();
  show_OFFSETS();
  show_IFAB();
  show_MOD4();
  show_TCOTY();
  show_ADC();

  Serial.end();
}

void loop() {
}



#endif
