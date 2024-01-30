/*!
 * \name        const
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   2020-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       macros and other const variables
 *
 * \attention
 * Ths setup reduces variable memory so that the sensorType can run on MCUs
 * with low memory by shifting global variable memory to main program memory.
 */


#define sc_PCB          F("Identified Sensor PCB: ")
#define sc_Interface    F("Identified Interface:  ")
#define sc_slave        F("Identified Slave:      ")
#define sc_slavename    F(" = TLE5012_S")
#define sc_enable       F("enabled")
#define sc_disable      F("disabled")
#define sc_PushPull     F("Push-Pull")
#define sc_OpenDrain    F("Open Drain")
#define sc_NotAllowed   F("not allowed")

// PWM interface
#define sc_E3005        F(" = TLE5012B_E3005")
#define sc_E5000        F(" = TLE5012B_E5000")
#define sc_PWM          F(" = PWM")
#define sc_ifsetPWM     F("\nPWM Interface settings\n")
#define sc_PWMfreq      F("\nMOD4 Frequency:         \t")
#define sc_PWMtime      F("\nIFAB Unit time:         \t")
#define sc_PWMfilter    F("\nIFAB Filter update time:\t")
#define sc_PWMpin       F("\nIFAB IFA pin:           \t")

//IIF Interface
#define sc_E1000        F(" = TLE5012B_E1000")
#define sc_IIF          F(" = IIF")
#define sc_ifsetIIF     F("\nIIF Interface settings\n")
#define sc_IIFmod       F("\nMOD1 IIF Mode:          \t")
#define sc_IIFres       F("\nMOD4 Resolution:        \t")
#define sc_IIFhyster    F("\nIFAB Hysteresis:        \t")
#define sc_IIFfilter    F("\nIFAB Filter update time:\t")
#define sc_IIFpin       F("\nIFAB IFA pin:           \t")
#define sc_IIFab        F("A/B operation with Index on IFC pin")
#define sc_IIFdirection F("Step/Direction operation with Index on IFC pin")

// HSM Interface
#define sc_E5020        F(" = TLE5012B_E5020")
#define sc_HSM          F(" = HSM")
#define sc_ifsetHSM     F("\nHSM Interface settings\n")
#define sc_HSMframe     F("\nMOD4 Frame config:      \t")
#define sc_HSMhyster    F("\nIFAB Hysteresis:        \t")
#define sc_HSMfilter    F("\nIFAB Filter update time:\t")
#define sc_HSMpin       F("\nIFAB IFA pin:           \t")

// SPC Interface
#define sc_E9000        F(" = TLE5012B_E9000")
#define sc_SPC          F(" = SPC")
#define sc_ifsetSPC     F("\nSPC Interface settings\n")
#define sc_SPCframe     F("\nMOD4 Frame config:      \t")
#define sc_SPCtime      F("\nSPC Unit time:          \t")
#define sc_SPCtrigger   F("\nSPC Trigger time:       \t")
#define sc_SPCpin       F("\nIFAB IFA pin:           \t")

// additional
#define sc_MOD2cal        F("\nMOD2 auto calibration:  \t")
#define sc_MOD2predict    F("\nMOD2 Prediction:        \t")
#define sc_MODpin         F("\nMOD3 IFA/B/C pin set:   \t")
#define sc_MODstrongfast  F("strong driver, DATA: strong driver, fast edge")
#define sc_MODstrongslow  F("strong driver, DATA: strong driver, slow edge")
#define sc_MODweakfast    F("weak driver, DATA: medium driver, fast edge")
#define sc_MODweakslow    F("weak driver, DATA: weak driver, slow edge")
#define sc_MODssc         F("\nMOD3 SSC interface:     \t")
#define sc_MODvoltage     F("\nMOD3 Voltage filter:    \t")
#define sc_Spikeenable    F("spike filter enabled")
#define sc_Spikedisbale   F("spike filter disabled")
#define sc_Angle12        F("12bit angle")
#define sc_Angle16        F("16bit angle")
#define sc_Angle12Temp    F("12bit angle + 8bit temperature")
#define sc_Angle16Temp    F("16bit angle + 8bit temperature")
#define sc_Nocalib        F("no auto-calibration")
#define sc_Cal1           F("auto-cal. mode 1: update every angle update cycle")
#define sc_Cal2           F("auto-cal. mode 2: update every 1.5 revolutions")
#define sc_Cal3           F("auto-cal. mode 3: update every 11.25°")
