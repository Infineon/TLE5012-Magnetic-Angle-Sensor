/*!
 * \file        tle5012b_reg.hpp
 * \name        tle5012b_reg.hpp - core register support header for the TLx5012B angle sensor family.
 * \author      Infineon Technologies AG
 * \copyright   2019-2024 Infineon Technologies AG
 * \version     4.0.0
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \details
 *              This file includes the registry definition macros of all Sensor registers and
 *              the bit settings for each of the register content values. Depending on
 *              the type of secondary interface (PWM, IIF or HSM) the meaning of some register values
 *              differs, so please have look in the TLE5012 manual for the exact meaning.
 *              Also included here are other senseful macros for handling the TLE5012 sensor.
 * \ref         tle5012corelib
 *
 * SPDX-License-Identifier: MIT
 *
 */


#ifndef TLE5012B_REG_HPP
#define TLE5012B_REG_HPP

#include <stdint.h>
#include <stdlib.h>
#include "TLE5012b.hpp"

namespace tle5012
{

/**
 * @addtogroup tle5012reg
 *
 * @{
 */

class Reg
{
    public:

        void *p;

        /*!
        * \brief Automatic calibration of offset and amplitude synchronicity for applications
        * with full-turn. Only 1 LSB corrected at each update. CRC check of calibration
        * registers is automatically disabled if AUTOCAL activated.
        */
        enum calibrationMode_t
        {
            noAutoCal = 0x0,//!< noAutoCal = no auto-calibration
            mode1,          //!< mode1 update every angle update cycle (FIR_MD setting)
            mode2,          //!< mode2 update every 1.5 revolutions
            mode3           //!< mode3 update every 11.25°
        };

        enum angleRange_t
        {
            factor1 = 0x080, //!< magnetic angle from -180° to +180°, mapped values from -16384 to 16384
            factor4 = 0x200, //!< magnetic angle from -45° to +45°, mapped values from -16384 to 16384
            factor5 = 0x040  //!< magnetic angle from -180° to +180°, mapped values from -8192 to 8192
        };

        /*!
        * \brief List of possible interface types witch are preset by fuses and can
        * be changed into each other
        */
        enum interfaceType_t
        {
            IIF = 0,  //!< IIF Incremental Interface (IIF)
            PWM,      //!< PWM Pulse-Width-Modulation (PWM)
            HSM,      //!< HSM Hall Switch Mode (HSM)
            SPC,      //!< SPC Short-PWM-Code (SPC)
            SSC       //!< SSC Synchronous Serial Communication (SSC)
        };

        //!< \brief List of possible Sensor types and PCB variants with and without attached XMC2Go
        enum sensorType_t
        {
            TLE5012B_E1000= 0x0,  //!< TLE5012B_E1000 Sensor2Go variant
            TLE5012B_E3005,       //!< TLE5012B_E3005
            TLE5012B_E5000,       //!< TLE5012B_E5000 Sensor2Go variant
            TLE5012B_E5020,       //!< TLE5012B_E5020
            TLE5012B_E9000,       //!< TLE5012B_E9000 Sensor2Go variant
        };

        /**
         * \brief Register access type
         */
        enum Access_t
        {
            REG_ACCESS_R    = (0x01U),      //!< \brief Read access register */
            REG_ACCESS_W    = (0x02U),      //!< \brief Write access register */
            REG_ACCESS_RW   = (0x03U),      //!< \brief Read & write access register */
            REG_ACCESS_U    = (0x04U),      //!< \brief Update register */
            REG_ACCESS_RU   = (0x05U),      //!< \brief Read & update register */
            REG_ACCESS_RWU  = (0x07U),      //!< \brief Read & write & update register */
            REG_ACCESS_RES  = (0x10U)       //!< \brief Reserved access register */
        };

        /**
         * \brief Bit field parameters
         */
        typedef struct
        {
            uint8_t  regAccess;              //!< \brief Bitfield register access */
            uint16_t regAddress;             //!< \brief Bitfield register address */
            uint16_t mask;                   //!< \brief Bitfield mask */
            uint8_t  position;               //!< \brief Bitfield position */
            uint8_t  resetValue;             //!< \brief Bitfield register reset value */
            uint8_t  posMap;                 //!< \brief Bitfield position of register in regMap */
        }BitField_t;

        /**
         * @brief Register address field
         *
         */
        typedef struct
        {
            uint16_t regAddress;            //!< \brief Address field register address */
            uint8_t  posMap;                //!< \brief Address field register regMap position */
        }AddressField_t;

        static const AddressField_t addrFields[];    //!< \brief Registers bitfields

        /**
         * \brief register address enumeration for all sensor registers
         *
         */
        enum Addr_t
        {
            REG_STAT         = (0x0000U),    //!< \brief STAT status register
            REG_ACSTAT       = (0x0010U),    //!< \brief ACSTAT activation status register
            REG_AVAL         = (0x0020U),    //!< \brief AVAL angle value register
            REG_ASPD         = (0x0030U),    //!< \brief ASPD angle speed register
            REG_AREV         = (0x0040U),    //!< \brief AREV angle revolution register
            REG_FSYNC        = (0x0050U),    //!< \brief FSYNC frame synchronization register
            REG_MOD_1        = (0x0060U),    //!< \brief MOD_1 interface mode1 register
            REG_SIL          = (0x0070U),    //!< \brief SIL register
            REG_MOD_2        = (0x0080U),    //!< \brief MOD_2 interface mode2 register
            REG_MOD_3        = (0x0090U),    //!< \brief MOD_3 interface mode3 register
            REG_OFFX         = (0x00A0U),    //!< \brief OFFX offset x
            REG_OFFY         = (0x00B0U),    //!< \brief OFFY offset y
            REG_SYNCH        = (0x00C0U),    //!< \brief SYNCH synchronicity
            REG_IFAB         = (0x00D0U),    //!< \brief IFAB register
            REG_MOD_4        = (0x00E0U),    //!< \brief MOD_4 interface mode4 register
            REG_TCO_Y        = (0x00F0U),    //!< \brief TCO_Y temperature coefficient register
            REG_ADC_X        = (0x0100U),    //!< \brief ADC_X ADC X-raw value
            REG_ADC_Y        = (0x0110U),    //!< \brief ADC_Y ADC Y-raw value
            REG_D_MAG        = (0x0140U),    //!< \brief D_MAG angle vector magnitude
            REG_T_RAW        = (0x0150U),    //!< \brief T_RAW temperature sensor raw-value
            REG_IIF_CNT      = (0x0200U),    //!< \brief IIF_CNT IIF counter value
            REG_T25O         = (0x0300U)     //!< \brief T25O temperature 25°c offset value
        };

        uint16_t regMap[MAX_NUM_REG];              //!< Register map */

        Reg(void* p);
        ~Reg();

        // REG_STAT
        bool isStatusReset(void);
        bool isStatusWatchDog(void);
        bool isStatusVoltage(void);
        bool isStatusFuse(void);
        bool isStatusDSPU(void);
        bool isStatusOverflow(void);
        bool isStatusXYOutOfLimit(void);
        bool isStatusMagnitudeOutOfLimit(void);
        bool isStatusADC(void);
        bool isStatusROM(void);
        bool isStatusGMRXY(void);
        bool isStatusGMRA(void);
        bool isStatusRead(void);
        uint8_t getSlaveNumber(void);
        void setSlaveNumber(const uint8_t snr);

        // REG_ACSTAT
        bool isActivationReset(void);
        void setActivationReset(void);
        void enableWatchdog(void);
        void disableWatchdog(void);
        bool isWatchdog(void);
        void enableVoltageCheck(void);
        void disableVoltageCheck(void);
        bool isVoltageCheck(void);
        void enableFuseCRC(void);
        void disableFuseCRC(void);
        bool isFuseCRC(void);
        void enableDSPUbist(void);
        void disableDSPUbist(void);
        bool isDSPUbist(void);
        void enableDSPUoverflow(void);
        void disableDSPUoverflow(void);
        bool isDSPUoverflow(void);
        void enableXYCheck(void);
        void disableXYCheck(void);
        bool isXYCheck(void);
        void enableGMRCheck(void);
        void disableGMRCheck(void);
        bool isGMRCheck(void);
        void enableADCCheck(void);
        void disableADCCheck(void);
        bool isADCCheck(void);
        void activateFirmwareReset(void);
        bool isFirmwareReset(void);

        // REG_AVAL
        bool isAngleValueNew(void);
        uint16_t getAngleValue(void);

        // REG_ASPD
        bool isSpeedValueNew(void);
        uint16_t getSpeedValue(void);

        // REG_AREV
        bool isNumberOfRevolutionsNew(void);
        uint16_t getNumberOfRevolutions(void);
        uint16_t getFrameCounter(void);
        void setFrameCounter(uint16_t fcnt);

        // REG_FSYNC
        uint16_t getFrameSyncCounter(void);
        void setFrameSyncCounter(uint16_t fsync);
        uint16_t getTemperatureValue(void);

        // REG_MOD_1
        void setFilterDecimation(uint8_t firmd);
        uint8_t getFilterDecimation(void);
        void setIIFMod(uint8_t iifmod);
        uint8_t getIIFMod(void);
        void holdDSPU(void);
        void releaseDSPU(void);
        bool isDSPUhold(void);
        void setInternalClock(void);
        void setExternalClock(void);
        bool statusClockSource(void);

        // REG_SIL
        void enableFilterParallel(void);
        void disableFilterParallel(void);
        bool isFilterParallel(void);
        void enableFilterInverted(void);
        void disableFilterInverted(void);
        bool isFilterInverted(void);
        void enableADCTestVector(void);
        void disableADCTestVector(void);
        bool isADCTestVector(void);
        void setFuseReload(void);
        bool getFuseReload(void);
        void setTestVectorX(uint8_t adctvx);
        uint8_t getTestVectorX(void);
        void setTestVectorY(uint8_t adctvy);
        uint8_t getTestVectorY(void);

        // REG_MOD_2
        void directionClockwise(void);
        void directionCounterClockwise(void);
        bool isAngleDirection(void);
        void enablePrediction(void);
        void disablePrediction(void);
        bool isPrediction(void);
        void setAngleRange(angleRange_t range);
        angleRange_t getAngleRange(void);
        void setCalibrationMode(calibrationMode_t autocal);
        calibrationMode_t getCalibrationMode(void);

        // REG_MOD_3
        void enableSpikeFilter(void);
        void disableSpikeFilter(void);
        bool isSpikeFilter(void);
        void enableSSCOpenDrain(void);
        void enableSSCPushPull(void);
        bool isSSCOutputMode(void);
        void setAngleBase(uint16_t base);
        uint16_t getAngleBase(void);
        void setPadDriver(uint8_t pad);
        uint8_t getPadDriver(void);

        // REG_OFFX
        int16_t getOffsetX(void);
        void setOffsetX(int16_t offx);

        // REG_OFFY
        int16_t getOffsetY(void);
        void setOffsetY(int16_t offy);

        // REG_SYNCH
        void setAmplitudeSynch(int16_t synch);
        int16_t getAmplitudeSynch(void);

        // REG_IFAB
        void setFIRUpdateRate(bool fir);
        uint8_t getFIRUpdateRate(void);
        void enableIFABOpenDrain(void);
        void enableIFABPushPull(void);
        bool isIFABOutputMode(void);
        void setOrthogonality(int16_t ortho);
        int16_t getOrthogonality(void);
        void setHysteresisMode(uint8_t hyst);
        uint8_t getHysteresisMode(void);

        // REG_MOD_4
        void setInterfaceMode(interfaceType_t ifmd);
        interfaceType_t getInterfaceMode(void);
        void setIFABres(uint8_t res);
        uint8_t getIFABres(void);
        void setHSMplp(uint8_t plp);
        uint8_t getHSMplp(void);
        void setOffsetTemperatureX(int8_t tcox);
        int8_t getOffsetTemperatureX(void);

        // REG_TCO_Y
        void setOffsetTemperatureY(int8_t tcoy);
        int8_t getOffsetTemperatureY(void);
        void enableStartupBist(void);
        void disableStartupBist(void);
        bool isStartupBist(void);
        void setCRCpar(uint16_t crc);
        uint16_t getCRCpar(void);

        // REG_ADC_X REG_ADC_Y
        int16_t getADCx(void);
        int16_t getADCy(void);

        // REG_D_MAG
        uint16_t getVectorMagnitude(void);
        uint16_t getTemperatureRAW(void);
        bool isTemperatureToggle(void);

        // REG_T25O
        uint16_t getCounterIncrements(void);
        uint16_t getT25Offset(void);

    private:

        static const BitField_t     bitFields[];        //!< \brief Registers bitfields

        /**
         * \brief Bit fields
         */
        enum BitFieldReg_t
        {
            REG_STAT_SRST,
            REG_STAT_SWD,
            REG_STAT_SVR,
            REG_STAT_SFUSE,
            REG_STAT_SDSPU,
            REG_STAT_SOV,
            REG_STAT_SXYOL,
            REG_STAT_SMAGOL,
            REG_STAT_RESERVED,
            REG_STAT_SADCT,
            REG_STAT_SROM,
            REG_STAT_NOGMRXY,
            REG_STAT_NOGMRA,
            REG_STAT_SNR,
            REG_STAT_RDST,

            REG_ACSTAT_ASRST,
            REG_ACSTAT_ASWD,
            REG_ACSTAT_ASVR,
            REG_ACSTAT_ASFUSE,
            REG_ACSTAT_ASDSPU,
            REG_ACSTAT_ASOV,
            REG_ACSTAT_ASVECXY,
            REG_ACSTAT_ASVEGMAG,
            REG_ACSTAT_RESERVED1,
            REG_ACSTAT_ASADCT,
            REG_ACSTAT_ASFRST,
            REG_ACSTAT_RESERVED2,

            REG_AVAL_ANGVAL,
            REG_AVAL_RDAV,

            REG_ASPD_ANGSPD,
            REG_ASPD_RDAS,

            REG_AREV_REVOL,
            REG_AREV_FCNT,
            REG_AREV_RDREV,

            REG_FSYNC_TEMPR,
            REG_FSYNC_FSYNC,

            REG_MOD_1_IIFMOD,
            REG_MOD_1_DSPUHOLD,
            REG_MOD_1_RESERVED1,
            REG_MOD_1_CLKSEL,
            REG_MOD_1_RESERVED2,
            REG_MOD_1_FIRMD,

            REG_SIL_ADCTVX,
            REG_SIL_ADCTVY,
            REG_SIL_ADCTVEN,
            REG_SIL_RESERVED1,
            REG_SIL_FUSEREL,
            REG_SIL_RESERVED2,
            REG_SIL_FILTINV,
            REG_SIL_FILTPAR,

            REG_MOD_2_AUTOCAL,
            REG_MOD_2_PREDICT,
            REG_MOD_2_ANGDIR,
            REG_MOD_2_ANGRANGE,
            REG_MOD_2_RESERVED1,

            REG_MOD_3_PADDRV,
            REG_MOD_3_SSCOD,
            REG_MOD_3_SPIKEF,
            REG_MOD_3_ANG_BASE,

            REG_OFFX_RESERVED1,
            REG_OFFX_XOFFSET,

            REG_OFFY_RESERVED1,
            REG_OFFY_YOFFSET,

            REG_SYNCH_RESERVED1,
            REG_SYNCH_SYNCH,

            REG_IFAB_IFADHYST,
            REG_IFAB_IFABOD,
            REG_IFAB_FIRUDR,
            REG_IFAB_ORTHO,

            REG_MOD_4_IFMD,
            REG_MOD_4_RESERVED1,
            REG_MOD_4_IFABRES,
            REG_MOD_4_HSMPLP,
            REG_MOD_4_TCOXT,

            REG_TCO_Y_CRCPAR,
            REG_TCO_Y_SBIST,
            REG_TCO_Y_TCOYT,

            REG_ADC_X_ADCX,

            REG_ADC_Y_ADCY,

            REG_D_MAG_MAG,
            REG_D_MAG_RESERVED1,

            REG_T_RAW_TRAW,
            REG_T_RAW_RESERVED1,
            REG_T_RAW_TTGL,

            REG_IIF_CNT_IIFCNT,
            REG_IIF_CNT_RESERVED1,

            REG_T25O_T250,
            REG_T25O_RESERVED1,
        };

        bool getBitField (BitField_t bitField, uint16_t & bitFValue);
        bool setBitField (BitField_t bitField, uint16_t bitFNewValue);

        void* parent_;

};

/**
 * @}
 */

}
#endif /* TLE5012B_REG_HPP */