/*!
 * \file        tle5012b_reg.hpp
 * \name        tle5012b_reg.hpp - core register support header for the TLE5012B angle sensor.
 * \author      Infineon Technologies AG
 * \copyright   2019-2020 Infineon Technologies AG
 * \version     3.0.0
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \details
 *              This file includes the registry definition macros of all Sensor registers and
 *              the bit settings for each of the register content values. Depending on
 *              the type of secondary interface (PWM, IIF or HSM) the meaning of some register values
 *              differs, so please have look in the TLE5012 manual for the exact meaning.
 *              Also included here are other sensefull macros for handling the TLE5012 sensor.
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

class Reg
{
	public:

		/**
		 * \brief register address enumeration for all sensor registers
		 *
		 */
		enum Addr_t
		{
			REG_STAT         = (0x0000),    //!< \brief STAT status register
			REG_ACSTAT       = (0x0010),    //!< \brief ACSTAT activation status register
			REG_AVAL         = (0x0020),    //!< \brief AVAL angle value register
			REG_ASPD         = (0x0030),    //!< \brief ASPD angle speed register
			REG_AREV         = (0x0040),    //!< \brief AREV angle revolution register
			REG_FSYNC        = (0x0050),    //!< \brief FSYNC frame synchronization register
			REG_MOD_1        = (0x0060),    //!< \brief MOD_1 interface mode1 register
			REG_SIL          = (0x0070),    //!< \brief SIL register
			REG_MOD_2        = (0x0080),    //!< \brief MOD_2 interface mode2 register
			REG_MOD_3        = (0x0090),    //!< \brief MOD_3 interface mode3 register
			REG_OFFX         = (0x00A0),    //!< \brief OFFX offset x
			REG_OFFY         = (0x00B0),    //!< \brief OFFY offset y
			REG_SYNCH        = (0x00C0),    //!< \brief SYNCH synchronicity
			REG_IFAB         = (0x00D0),    //!< \brief IFAB register
			REG_MOD_4        = (0x00E0),    //!< \brief MOD_4 interface mode4 register
			REG_TCO_Y        = (0x00F0),    //!< \brief TCO_Y temperature coefficient register
			REG_ADC_X        = (0x0100),    //!< \brief ADC_X ADC X-raw value
			REG_ADC_Y        = (0x0110),    //!< \brief ADC_Y ADC Y-raw value
			REG_D_MAG        = (0x0140),    //!< \brief D_MAG angle vector magnitude
			REG_T_RAW        = (0x0150),    //!< \brief T_RAW temperature sensor raw-value
			REG_IIF_CNT      = (0x0200),    //!< \brief IIF_CNT IIF counter value
			REG_T25O         = (0x0300)     //!< \brief T25O temperature 25°c offset value
		};

		int regAddrItems[MAX_NUM_REG] = {
			REG_STAT,
			REG_ACSTAT,
			REG_AVAL,
			REG_ASPD,
			REG_AREV,
			REG_FSYNC,
			REG_MOD_1,
			REG_SIL,
			REG_MOD_2,
			REG_MOD_3,
			REG_OFFX,
			REG_OFFY,
			REG_SYNCH,
			REG_IFAB,
			REG_MOD_4,
			REG_TCO_Y,
			REG_ADC_X,
			REG_ADC_Y,
			REG_D_MAG,
			REG_T_RAW,
			REG_IIF_CNT,
			REG_T25O
		};

		uint16_t regMap[MAX_NUM_REG];              //!< Register map */

		Reg();
		~Reg();



		/**
		 * \brief Register access type
		 */
		enum Access_t
		{
			REG_ACCESS_R    = (0x01U),      //!< \brief Read access register */
			REG_ACCESS_W    = (0x02U),      //!< \brief Write access register */
			REG_ACCESS_RW   = (0x03U),      //!< \brief Read & write access register */
			REG_ACCESS_RH   = (0x05U),      //!< \brief Read & internal hardware/firmware access register */
			REG_ACCESS_RWH  = (0x07U),      //!< \brief Read & write & hardware/firmware access register */
			REG_ACCESS_S    = (0x08U),      //!< \brief Sticky access register */
			REG_ACCESS_RHS  = (0x0DU),      //!< \brief Read & internal sticky hardware/firmware access register */
			REG_ACCESS_RES  = (0x10U)       //!< \brief Reserved access register */
		};

		/**
		 * \brief Bit field parameters
		 */
		typedef struct
		{
			uint8_t regAccess;              //!< \brief Bitfield register access */
			uint8_t regAddress;             //!< \brief Bitfiled register address */
			uint8_t mask;                   //!< \brief Bitfield mask */
			uint8_t position;               //!< \brief Bitfiled position */
			uint8_t resetValue;             //!< \brief Bitfield register reset value */
		}BitField_t;

	private:

		static const BitField_t bitFields[];    //!< \brief Registers bitfields

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

		
		bool getBitField (BitField_t bitField, uint8_t & bitFValue);
		bool setBitField (BitField_t bitField, uint8_t bitFNewValue);


};

#endif /* TLE5012B_REG_HPP */