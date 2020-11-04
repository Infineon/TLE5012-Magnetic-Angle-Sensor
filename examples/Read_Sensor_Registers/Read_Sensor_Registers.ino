/*!
 * \name        Read_Sensor_Registers
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     2.0.1
 * \brief       Reads all registers and reports there status
 * \details
 * This example program will read and all documented registers from the sensor and
 * fill the sensorRegister structure with it and writes this to the serial port
 * with remark info for each register. Please have look to the sensor manual for 
 * more and more detailed information about each register.
 * The sensorRegister structure consists out of included structures
 * for each register word and will separate the bits for each bitwise information.
 * As this is much overhead for normal sensor use, this information is set into its
 * own library Tle5012b_reg which resides on top of the normal Tle5012b library.
 * Therefore it should only be used if extensive register operations are needed.
 * 
 * \attention This Sketch needs ca. 35kB of  memory and does not compile on the original
 * Arduino/Genuino Uno. Use the Read_Sensor_Type.ino instead
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
  Serial.println("STOP: this scetch needs more momory than available");
}

void loop()
{

}

#else

#include <TLE5012-ino.hpp>

Tle5012Ino Tle5012Sensor = Tle5012Ino();
errorTypes checkError = NO_ERROR;

void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {};
  checkError = Tle5012Sensor.begin();
  Serial.println("init done!");
  Serial.print("checkerror: "); Serial.println(checkError,HEX);
  delay(1000);

  // read all registers
  checkError = Tle5012Sensor.readSensorType();
  checkError = Tle5012Sensor.identifyInterfaceType();

  show_bin();

  // Printout of each documented register
  reg_stat();
  reg_acstat();
  reg_aval();
  reg_aspd();
  reg_arev();
  reg_fsync();
  reg_mod1();
  reg_sil();
  reg_mod2();
  reg_mod3();
  reg_offx();
  reg_offy();
  reg_synch();
  reg_ifab();
  reg_mod4();
  reg_tcoy();
  reg_adc();
  reg_dmag();
  reg_traw();
  reg_iifcnt();
  reg_t250();
  //
  Serial.end();
}

void loop() {
}
 

/*!
 * Function prints the binary code of each documented register
 */
void show_bin()
{
  Serial.print("\t\t");
  for (int8_t i=15; i>-1; i--)
  {
    Serial.print(" ");
    Serial.print(i,HEX);
    Serial.print(" ");
  }
  Serial.println("\n\t\t------------------------------------------------");
  for (int8_t i=0; i<MAX_NUM_REG; i++)
  {
    Serial.print(i);                                              Serial.print("\t");
    Serial.print(Tle5012Sensor.sensorRegister.nameOfRegister[i]); Serial.print("\t");
    PRINTBINS(Tle5012Sensor.sensorRegister.registers[i]);         Serial.println("");
  }
}

/*!
 * Function prints a common header for each register entries
 */
void printHeader(String name,int8_t num, uint16_t reg)
{
  Serial.println("");
  Serial.println("");
  Serial.print("Register:\t");   Serial.println(name);
  Serial.print("Offset:  \t0x"); Serial.println(num,HEX);
  Serial.print("Binary:  \t");   PRINTBIN(reg); Serial.println("b");
  Serial.println("================================================================================================================");
  Serial.println("Register\tHEX\tDEC\tvariable\ttype\tbit\tremark");
  Serial.println("----------------------------------------------------------------------------------------------------------------");
}

/*!
 * Function prints the separated register entries with there
 * type and remark
 */
void printValue(String regName, uint16_t regValue, String regType, String regRemark="", String regExtra="")
{
  Serial.print(regName);
  Serial.print("\t");

  Serial.print("0x");
  Serial.print(regValue,HEX);
  Serial.print("\t");  
 
  Serial.print(regValue);
  Serial.print("\t");

  Serial.print(regType);
  Serial.print("\t");

  Serial.print(regRemark);
  Serial.print(regExtra);
  Serial.println("");
}

void reg_stat()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.stat.reg;
  uint16_t val = 0;
  printHeader("STAT",0,reg);

  val = Tle5012Sensor.sensorRegister.stat.fetch_SRST(reg);
  printValue("SRST      ",val,"1, boolean \tru \t0    ",(val
    ? "indication of power-up, short power-break, firmware or active reset"
    : "no reset since last readout"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SWD(reg);
  printValue("SWD       ",val,"1, boolean \tr  \t1    ",(val
    ? "watch dog counter expired (DSPU stop)"
    : "normal operation"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SVR(reg);
  printValue("SVR       ",val,"1, boolean \tr  \t2    ",(val
    ? "over voltage VDD-off, GND-off or VOVG/A/D too high"
    : "Voltages OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SFUSE(reg);
  printValue("SFUSE     ",val,"1, boolean \tr  \t3    ",(val
    ? "CRC fail"
    : "CRC OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SDSPU(reg);
  printValue("SDSPU     ",val,"1, boolean \tr  \t4    ",(val
    ? "DPSU self-test not OK or still running"
    : "DPSU self-test OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SOV(reg);
  printValue("SOV       ",val,"1, boolean \tru \t5    ",(val
    ? "DSPU overflow occurred"
    : "No DSPU overflow occurred"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SXYOL(reg);
  printValue("SXYOL     ",val,"1, boolean \tru \t6    ",(val
    ? "X/Y data out of limit"
    : "X/Y data OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SMAGOL(reg);
  printValue("SMAGOL    ",val,"1, boolean \tru \t7    ",(val
		    ? "GMR magnitude out of limit"
		    : "GMR magnitude OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_Reserved1(reg);
  printValue("Reserverd1",val,"1, boolean \t   \t8    ","");


  val = Tle5012Sensor.sensorRegister.stat.fetch_SADCT(reg);
  printValue("SADCT     ",val,"1, boolean \tr  \t9    ",(val
    ? "Test vectors out of limit"
    : "Test vectors OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SROM(reg);
  printValue("SROM      ",val,"1, boolean \tr  \t10    ",(val
    ? "CRC fail or still running"
    : "CRC OK"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_NOGMRXY(reg);
  printValue("NOGMRXY   ",val,"1, boolean \tru \t11   ",(val
    ? "no valid GMR_XY values on the ADC input"
    : "valid GMR_XY values on the ADC input and thus on filter output"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_NOGMRA(reg);
  printValue("NOGMRA    ",val,"1, boolean \tru \t12   ",(val
    ? "no valid GMR angle value on the interface"
    : "valid GMR angle value on the interface"));

  val = Tle5012Sensor.sensorRegister.stat.fetch_SNR(reg);
  printValue("SNR       ",val,"2, uint8_t \tr w\t13:14","Slave Number of this sensor out of up to four sensors");

  val = Tle5012Sensor.sensorRegister.stat.fetch_RDST(reg);
  printValue("RDST      ",val,"1, boolean \tr  \t15   ",(val
    ? "status values changed"
    : "status values not changed since last readout"));

  Serial.println("");
}

void reg_acstat()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.acstat.reg;
  uint16_t val = 0;
  printHeader("ACSTAT",1,reg);

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASRST(reg);
  printValue("ASRST     ",val,"1, boolean \truw\t0    ",(val
    ? "activation of HW Reset (S_RST is set)"
    : "after execution (write only, thus always returns 0)"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASWD(reg);
  printValue("ASWD      ",val,"1, boolean \truw\t1    ",(val
    ? "DSPU Watch dog monitoring enabled"
    : "DSPU watch dog monitoring disabled"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASVR(reg);
  printValue("ASVR      ",val,"1, boolean \truw\t2    ",(val
    ? "check of regulator voltages enabled"
    : "check of regulator voltages disabled"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASFUSE(reg);
  printValue("ASFUSE    ",val,"1, boolean \truw\t3    ",(val
    ? "monitoring of CRC enabled"
    : "monitoring of CRC disabled"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASDSPU(reg);
  printValue("ASDSPU    ",val,"1, boolean \truw\t4    ",(val
    ? "activation of DSPU BIST or BIST running"
    : "after execution"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASOV(reg);
  printValue("ASOV      ",val,"1, boolean \truw\t5    ",(val
    ? "monitoring of DSPU Overflow enabled"
    : "monitoring of DSPU Overflow disabled"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASVECXY(reg);
  printValue("ASVECXY   ",val,"1, boolean \truw\t6    ",(val
    ? "monitoring of X,Y Out of Limit enabled"
    : "monitoring of X,Y Out of Limit disabled"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASVEGMAG(reg);
  printValue("ASVEGMAG  ",val,"1, boolean \truw\t7    ",(val
    ? "monitoring of magnitude enabled"
    : "monitoring of magnitude disabled"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_Reserved2(reg);
  printValue("Reserverd2",val,"1, boolean \t   \t8    ","");

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASADCT(reg);
  printValue("ASADCT    ",val,"1, boolean \truw\t9    ",(val
		    ? "after execution"
		    : "activation of ADC Test vector Check"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_ASFRST(reg);
  printValue("ASFRST    ",val,"1, boolean \truw\t10   ",(val
    ? "default or after execution of firmware reset"
    : "activation of firmware reset"));

  val = Tle5012Sensor.sensorRegister.acstat.fetch_Reserved1(reg);
  printValue("Reserverd1",val,"1, uint8_t \t   \t11:15","");

  Serial.println("");
}

void reg_aval()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.aval.reg;
  uint16_t val = 0;
  printHeader("AVAL",2,reg);

  val = Tle5012Sensor.sensorRegister.aval.fetch_RDAV(reg);
  printValue("RDAV      ",val,"1, boolean \tr  \t15   ",(val
    ? "new angle value present"
    : "no new angle value since last readout"));

  val = Tle5012Sensor.sensorRegister.aval.fetch_ANGVAL(reg);
  printValue("ANGVAL    ",val,"16,uint16_t\tru \t0:14 ","Calculated Angle Value (signed 15-bit)");

  Serial.println("");

}

void reg_aspd()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.aspd.reg;
  uint16_t val = 0;
  printHeader("AVAL",3,reg);

  val = Tle5012Sensor.sensorRegister.aspd.fetch_RDAS(reg);
  printValue("RDAS      ",val,"1, boolean \tr  \t15   ",(val
    ? "new angle speed value present"
    : "no new speed angle value since last readout"));

  val = Tle5012Sensor.sensorRegister.aspd.fetch_ANGSPD(reg);
  printValue("ANGSPD    ",val,"16,uint16_t\tru \t0:14 ","Calculated Angle Speed, where the sign indicates the direction of the rotation");

  Serial.println("");
}

void reg_arev()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.arev.reg;
  uint16_t val = 0;
  printHeader("AREV",4,reg);

  val = Tle5012Sensor.sensorRegister.arev.fetch_RDREV(reg);
  printValue("RDREV     ",val,"1, boolean \tr  \t15   ",(val
    ? "new value present"
    : "no new value since last readout"));

  val = Tle5012Sensor.sensorRegister.arev.fetch_FCNT(reg);
  printValue("FCNT      ",val,"6,uint8_t \truw\t9:14 ","Internal frame counter. Increments every update period (FIR_MD setting)");

  val = Tle5012Sensor.sensorRegister.arev.fetch_REVOL(reg);
  printValue("REVOL     ",val,"8,uint16_t\tru \t0:8 ","Number of Revolutions (signed 9-bit value)");

  Serial.println("");
}

void reg_fsync()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.fsync.reg;
  uint16_t val = 0;
  printHeader("FSYNC",5,reg);

  val = Tle5012Sensor.sensorRegister.fsync.fetch_TEMPR(reg);
  printValue("TEMPR     ",val,"7,int16_t \tr  \t9:15 ","Signed offset compensated temperature value");

  val = Tle5012Sensor.sensorRegister.fsync.fetch_FSYNC(reg);
  printValue("FSYNC     ",val,"9,uint16_t\tr  \t0:9  ","Frame Synchronization Counter Value");

  Serial.println("");
}

void reg_mod1()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.mod1.reg;
  uint16_t val = 0;
  printHeader("MOD1",6,reg);

  val = Tle5012Sensor.sensorRegister.mod1.fetch_IIFMOD(reg);
  printValue("IIFMOD    ",val,"2, uint8_t \tr w\t0:1  ","Incremental Interface Mode: ",(val == 0
    ? " 00b IIF disabled"
    : (val == 1
      ? " 01b A/B operation with Index on IFC pin"
      : (val == 2
         ? "10b Step/Direction operation with Index on IFC pin"
         : "11b not allowed"))));

  val = Tle5012Sensor.sensorRegister.mod1.fetch_DSPUHOLD(reg);
  printValue("DSPUHOLD  ",val,"1, boolean \tr w\t2    ",(val
    ? "DSPU is on hold"
    : "DSPU in normal schedule operation"));

  val = Tle5012Sensor.sensorRegister.mod1.fetch_Reserverd2(reg);
  printValue("Reserverd2",val,"1, boolean \t   \t3   ","");

  val = Tle5012Sensor.sensorRegister.mod1.fetch_CLKSEL(reg);
  printValue("CLKSEL    ",val,"1, boolean \tru \t4   ",(val
    ? "external 4-MHz clock (IFC pin switched to input)"
    : "internal oscillator"));

  val = Tle5012Sensor.sensorRegister.mod1.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"1, uint16_t\t   \t5:13 ","");

  val = Tle5012Sensor.sensorRegister.mod1.fetch_FIRMD(reg);
  printValue("FIRMD     ",val,"2, uint8_t \tr w\t14:15","Update Rate Setting (Filter Decimation): ",(val == 0
     ? "00b none"
     : (val == 1
       ? "01b 42.7 μs"
       : (val == 2
          ? "10b 85.3 μs"
          : "11b 170.6 μs"))));

  Serial.println("");

}

void reg_sil()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.sil.reg;
  uint16_t val = 0;
  printHeader("SIL",7,reg);

  val = Tle5012Sensor.sensorRegister.sil.fetch_ADCTVX(reg);
  printValue("ADCTVX    ",val,"3, uint16_t\tr w\t0:2 ","Test vector X: ",(val == 0
    ? "000b 0V"
    : (val == 1
      ? "001b +70%"
      : (val == 2
        ? "010b +100%"
        : (val == 3
          ? "011b +Overflow"
          : (val == 5
            ? "101b -70%"
            : (val == 6
              ? "110b -100%"
              : "111b -Overflow")))))));

  val = Tle5012Sensor.sensorRegister.sil.fetch_ADCTVY(reg);
  printValue("ADCTVY    ",val,"3, uint16_t\tr w\t3:5 ","Test vector Y: ",(val == 0
    ? "000b 0V"
    : (val == 1
      ? "001b +70%"
      : (val == 2
        ? "010b +100%"
        : (val == 3
          ? "011b +Overflow"
          : (val == 5
            ? "101b -70%"
            : (val == 6
              ? "110b -100%"
              : "111b -Overflow")))))));

  val = Tle5012Sensor.sensorRegister.sil.fetch_ADCTVEN(reg);
  printValue("ADCTVEN   ",val,"1, boolean \tr w\t6   ",(val
    ? "ADC-Test Vectors enabled"
    : "ADC-Test Vectors disabled"));

  val = Tle5012Sensor.sensorRegister.sil.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"3, uint16_t\t   \t7:9 ","");

  val = Tle5012Sensor.sensorRegister.sil.fetch_FUSEREL(reg);
  printValue("FUSEREL   ",val,"1, boolean \tr w\t10  ",(val
    ? "normal operation"
    : "reload of registers with fuse values immediately"));

  val = Tle5012Sensor.sensorRegister.sil.fetch_Reserverd2(reg);
  printValue("Reserverd2",val,"3, uint16_t\t   \t11:13","");

  val = Tle5012Sensor.sensorRegister.sil.fetch_FILTINV(reg);
  printValue("FILTINV   ",val,"1, boolean \tr w\t14  ",(val
    ? "filter inverted enabled"
    : "filter inverted disabled"));

  val = Tle5012Sensor.sensorRegister.sil.fetch_FILTPAR(reg);
  printValue("FILTPAR   ",val,"1, boolean \tr w\t15  ",(val
    ? "filter parallel enabled (source: X-value)"
    : "filter parallel disabled"));

}

void reg_mod2()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.mod2.reg;
  uint16_t val = 0;
  printHeader("MOD2",8,reg);

  val = Tle5012Sensor.sensorRegister.mod2.fetch_AUTOCAL(reg);
  printValue("AUTOCAL   ",val,"2, uint8_t \tr w\t0:1  ","Autocalibration Mode: ",(val == 0
    ? "00b no auto-calibration"
    : (val == 1
      ? "01b auto-cal. mode 1: update every angle update cycle"
      : (val == 2
        ? "10b auto-cal. mode 2: update every 1.5 revolutions"
        : "11b auto-cal. mode 3: update every 11.25°"))));

  val = Tle5012Sensor.sensorRegister.mod2.fetch_PREDICT(reg);
  printValue("PREDICT   ",val,"1, boolean \tr w\t2   ",(val
    ? "prediction enabled"
    : "prediction disabled"));

  val = Tle5012Sensor.sensorRegister.mod2.fetch_ANGDIR(reg);
  printValue("ANGDIR    ",val,"1, boolean \tr w\t10  ",(val
    ? "counterclockwise rotation of magnet"
    : "clockwise rotation of magnet"));

  val = Tle5012Sensor.sensorRegister.mod2.fetch_ANGRANGE(reg);
  printValue("ANGRANGE  ",val,"1, boolean \tr w\t11:14","AngleRange: ",(val == 0x080
    ? "080h factor 1 (default), magnetic angle -180°..180°"
    : (val == 0x200
      ? "200h factor 4, magnetic angle -45°..45°"
      : "040h factor 0.5, magnetic angle -180°..180°")));

  val = Tle5012Sensor.sensorRegister.mod2.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"1, boolean \t   \t15  ","");

  Serial.println("");
}

void reg_mod3()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.mod3.reg;
  uint16_t val = 0;
  printHeader("MOD3",9,reg);

  val = Tle5012Sensor.sensorRegister.mod3.fetch_PADDRV(reg);
  printValue("PADDRV    ",val,"2, uint8_t \tr w\t0:1  ","Configuration of Pad-Driver: ",(val == 0
    ? "00b IFA/IFB/IFC: strong driver, DATA: strong driver, fast edge"
    : (val == 1
      ? "01b IFA/IFB/IFC: strong driver, DATA: strong driver, slow edge"
      : (val == 2
        ? "10B IFA/IFB/IFC: weak driver, DATA: medium driver, fast edge"
        : "11B IFA/IFB/IFC: weak driver, DATA: weak driver, slow edge"))));

  val = Tle5012Sensor.sensorRegister.mod3.fetch_SSCOD(reg);
  printValue("SSCOD     ",val,"1, boolean \tr w\t2   ",(val
    ? "Push-Pull"
    : "Open Drain"));

  val = Tle5012Sensor.sensorRegister.mod3.fetch_SPIKEF(reg);
  printValue("SPIKEF    ",val,"1, boolean \tr w\t3   ",(val
    ? "spike filter enabled"
    : "spike filter disabled"));

  val = Tle5012Sensor.sensorRegister.mod3.fetch_ANG_BASE(reg);
  printValue("ANG_BASE  ",val,"12,uint16_t\tr w\t4:15 ","Angle Base sets the 0° angle position: ",(val == 0x800
    ? "800H -180°"
    : (val == 0
       ? "000H 0°"
       : "7FFH +179.912°")));

  Serial.println("");
}

void reg_offx()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.offx.reg;
  uint16_t val = 0;
  printHeader("OFFX",10,reg);

  val = Tle5012Sensor.sensorRegister.offx.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"3, uint8_t \t   \t0:3  ","");

  val = Tle5012Sensor.sensorRegister.offx.fetch_XOFFSET(reg);
  printValue("XOFFSET   ",val,"12, int16_t\tr w\t4:15 ","12-bit signed integer value of raw X-signal offset");

  Serial.println("");
}

void reg_offy()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.offy.reg;
  uint16_t val = 0;
  printHeader("OFFY",11,reg);

  val = Tle5012Sensor.sensorRegister.offy.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"3, uint8_t \t   \t0:3  ","");

  val = Tle5012Sensor.sensorRegister.offy.fetch_YOFFSET(reg);
  printValue("YOFFSET   ",val,"12, int16_t\tr w\t4:15 ","12-bit signed integer value of raw Y-signal offset");

  Serial.println("");
}

void reg_synch()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.synch.reg;
  uint16_t val = 0;
  printHeader("SYNCH",12,reg);

  val = Tle5012Sensor.sensorRegister.synch.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"3, uint8_t \t   \t0:3  ","");

  val = Tle5012Sensor.sensorRegister.synch.fetch_SYNCH(reg);
  printValue("SYNCH     ",val,"12, int16_t\t   \t4:15 ","12-bit signed integer value of amplitude synchronicity correction");

  Serial.println("");
}

void reg_ifab()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.ifab.reg;
  uint16_t val = 0;
  printHeader("IFAB",13,reg);

  val = Tle5012Sensor.sensorRegister.ifab.fetch_IFADHYST(reg);
  printValue("IFADHYST  ",val,"2, uint8_t \tr w\t0:1  ","HSM and IIF Mode: Hysteresis: ",
    (Tle5012Sensor.sensorRegister.interface == 0 || Tle5012Sensor.sensorRegister.interface == 2
      ? (val == 0
         ? "00b HSM: 0°"
         : (val == 1
           ? "01b HSM: 0.175°"
           : (val == 2
             ? "10b HSM: 0.35°"
             : "11b HSM: 0.70°")))
      : (Tle5012Sensor.sensorRegister.interface == 3
          ? (val == 0
            ? "00b SPC: 3.0 μs"
            : (val == 1
              ? "01b SPC: 2.5 μs"
              : (val == 2
                ? "10b SPC: 2.0 μs"
                : "11b SPC: 1.5 μs")))
          : "none")
    ));

  val = Tle5012Sensor.sensorRegister.ifab.fetch_IFABOD(reg);
  printValue("IFABOD    ",val,"1, boolean \tr w\t2   ",(val
    ? "Open Drain"
    : "Push-Pull"));

  val = Tle5012Sensor.sensorRegister.ifab.fetch_FIRUDR(reg);
  printValue("FIRUDR    ",val,"1, boolean \tr w\t2   ",(val
    ? "FIR_MD = ‘10’ (85.3 μs)"
    : "FIR_MD = ‘01’ (42.7 μs)"));

  val = Tle5012Sensor.sensorRegister.ifab.fetch_ORTHO(reg);
  printValue("ORTHO     ",val,"3,uint16_t\tr w\t4:15 ","12-bit signed integer value of orthogonality correction");

  Serial.println("");
}

void reg_mod4()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.mod4.reg;
  uint16_t val = 0;
  printHeader("MOD4",14,reg);

  val = Tle5012Sensor.sensorRegister.mod4.fetch_IFMD(reg);
  printValue("IFMD      ",val,"2,uint8_t \tr w\t0:1 ","Interface Mode on IFA,IFB,IFC: ",Tle5012Sensor.sensorRegister.interfaceName);

  val = Tle5012Sensor.sensorRegister.mod2.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"1, boolean \t   \t2   ","");

  val = Tle5012Sensor.sensorRegister.mod4.fetch_IFABRES(reg);
  printValue("IFABRES   ",val,"2, uint8_t \t   \t3:4  ",
    (Tle5012Sensor.sensorRegister.interface == 1
      ? (val == 0
         ? "00b PWM: 244 Hz"
         : (val == 1
           ? "01b PWM: 488 Hz"
           : (val == 2
             ? "10b PWM: 977 Hz"
             : "11b PWM: 1953 Hz")))
      : (Tle5012Sensor.sensorRegister.interface == 0
          ? (val == 0
            ? "00b IIF: 12bit, 0.088° step"
            : (val == 1
              ? "01b IIF: 11bit, 0.176° step"
              : (val == 2
                ? "10b IIF: 10bit, 0.352° step"
                : "11b IIF: 9bit, 0.703° step")))
          : (Tle5012Sensor.sensorRegister.interface == 3
            ? (val == 0
              ? "00b SPC: 00B 12bit angle"
              : (val == 1
                ? "01b SPC: 01B 16bit angle"
                : (val == 2
                  ? "10b SPC: 10B 12bit angle + 8bit temperature"
                  : "11b SPC: 11B 16bit angle + 8bit temperature")))
            : "none")
    )));

  val = Tle5012Sensor.sensorRegister.mod4.fetch_HSMPLP(reg);
  printValue("HSMPLP    ",val,"2, uint8_t \t   \t5:8  ",
    (Tle5012Sensor.sensorRegister.interface == 0
      ? "IIF Absolute Count, x0xxb enabled, x1xxb disabled"
      : (Tle5012Sensor.sensorRegister.interface == 1
        ? "PWM Error Indication, xx0xb enabled, xx1xb disabled"
        : (Tle5012Sensor.sensorRegister.interface == 2
          ? "HSM Pole-Pair Configuration 0000b=1 - 1111b=16"
          : (Tle5012Sensor.sensorRegister.interface == 3
            ? "SPC Total Trigger Time, 0000b 90*UT, 0100b tmlow + 12 UT"
            : "none")))));

  val = Tle5012Sensor.sensorRegister.mod4.fetch_TCOXT(reg);
  printValue("TCOXT     ",val,"7, int8_t \tr w\t9:15 ","7-bit signed integer value of X-offset temperature coefficient");

  Serial.println("");
}

void reg_tcoy()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.tcoy.reg;
  uint16_t val = 0;
  printHeader("TCOY",15,reg);

  val = Tle5012Sensor.sensorRegister.tcoy.fetch_SBIST(reg);
  printValue("SBIST     ",val,"7, int8_t \t   \t0:7  ","CRC of parameters from address 08H to 0FH");

  val = Tle5012Sensor.sensorRegister.tcoy.fetch_CRCPAR(reg);
  printValue("CRCPAR    ",val,"1, boolean \tr w\t8   ",(val
    ? "Startup-BIST enabled"
    : "Startup-BIST disabled"));

  val = Tle5012Sensor.sensorRegister.tcoy.fetch_TCOYT(reg);
  printValue("TCOYT     ",val,"7, int8_t \t   \t9:15 ","7-bit signed integer value of Y-offset temperature coefficient");
  Serial.println("");
}

void reg_adc()
{
  uint16_t reg1 = Tle5012Sensor.sensorRegister.adc.ADCX;
  uint16_t reg2 = Tle5012Sensor.sensorRegister.adc.ADCY;
  uint16_t val = 0;
  printHeader("ADCX",16,reg1);

  val = Tle5012Sensor.sensorRegister.adc.ADCX;
  printValue("ADCX    ",val,"16,uint16_t\tr  \t0:15 ","");
  Serial.println("");

  printHeader("ADCX",17,reg2);
  val = Tle5012Sensor.sensorRegister.adc.ADCY;
  printValue("ADCY    ",val,"16,uint16_t\tr  \t0:15 ","");
  Serial.println("");
}

void reg_dmag()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.dmag.reg;
  uint16_t val = 0;
  printHeader("DMAG",20,reg);

  val = Tle5012Sensor.sensorRegister.dmag.fetch_MAG(reg);
  printValue("MAG       ",val,"9 ,uint16_t\tru \t0:9  ","Unsigned Angle Vector Magnitude after X, Y error");

  val = Tle5012Sensor.sensorRegister.dmag.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"6 ,uint8_t \t   \t10:15","");
  Serial.println("");
}

void reg_traw()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.traw.reg;
  uint16_t val = 0;
  printHeader("SYNCH",21,reg);

  val = Tle5012Sensor.sensorRegister.traw.fetch_Reserverd1(reg);
  printValue("TRAW      ",val,"9 ,uint16_t\tr  \t0:9  ","Temperature value not compensated with the offset temperature at ADC");

  val = Tle5012Sensor.sensorRegister.traw.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"6 ,uint8_t \t   \t10:14","");

  val = Tle5012Sensor.sensorRegister.traw.fetch_TTGL(reg);
  printValue("TTGL      ",val,"1, boolean \tr  \t15  ","Toggles after every new temperature value");

  Serial.println("");
}

void reg_iifcnt()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.iifcnt.reg;
  uint16_t val = 0;
  printHeader("IIFCNT",32,reg);

  val = Tle5012Sensor.sensorRegister.iifcnt.fetch_IIFCNT(reg);
  printValue("IIFCNT    ",val,"13,uint16_t\tr  \t0:13 ","Internal 14-bit counter for the incremental interface, counts from 0 to 16383 during one full turn");

  val = Tle5012Sensor.sensorRegister.iifcnt.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"2, uint8_8 \tr  \t14:15","");

  Serial.println("");
}

void reg_t250()
{
  uint16_t reg = Tle5012Sensor.sensorRegister.t250.reg;
  uint16_t val = 0;
  printHeader("T250",48,reg);

  val = Tle5012Sensor.sensorRegister.t250.fetch_Reserverd1(reg);
  printValue("Reserverd1",val,"9 ,uint16_t\tr  \t0:8  ","");

  val = Tle5012Sensor.sensorRegister.t250.fetch_T250(reg);
  printValue("T250      ",val,"9 , int16_t\tr  \t9:15 ","Signed offset value at 25°C temperature; 1dig=0.36°C.");

  Serial.println("");
}

#endif
