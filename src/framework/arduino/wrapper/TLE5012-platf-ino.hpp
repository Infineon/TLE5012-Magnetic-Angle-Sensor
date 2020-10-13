/** 
 * @file        TLE5012-platf-ino.hpp
 * @brief       TLE5012 Arduino Hardware Platforms
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE5012_PLATF_INO_HPP_
#define TLE5012_PLATF_INO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

#include "../pal/TLE5012-pal-ino.hpp"

#define SENS_TYPE TLE5012_Sens2Go

/**
 * @addtogroup tle5012inohw
 * @{
 */

/**
 * @brief Arduino Hardware Platform Pins
 */
typedef struct {
	uint8_t power;      //!< Switch on/off power pin */
	uint8_t csPin;      //!< chipselect pin for first sensor */
	uint8_t mMOSI;      //!< Pin for SPI MOSI (pin 0.6 on test board);
	uint8_t mMISO;      //!< Pin for SPI MISO (pin 0.7 on test board)
	uint8_t mSCK;       //!< Pin for CLOCK (pin 0.8 on test board)
}sensType_t;

extern sensType_t TLE5012_Sens2Go;     //!< TLE5012 Sensor2Go Kit with XMC1100 */
extern sensType_t TLE5012_breakOut;    //!< TLE5012 breakout board removed from the Sensor2Go Kit */
extern sensType_t TLE5012_bulk;        //!< TLE5012 bulk chip (se manual on how to connect the 3wire SPI */

/** @} */

#endif /** TLE5012_SWITCH_FRAMEWORK **/
#endif /** TLE5012_PLATF_INO_HPP_ **/