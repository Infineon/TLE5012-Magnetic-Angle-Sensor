/** 
 * @file        TLE5012-platf-ino.cpp
 * @brief       TLE5012 Arduino Hardware Platforms
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "TLE5012-platf-ino.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup tle5012inohw
 */

sensType_t TLE5012_Sens2Go   =  {8,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MOSI,PIN_SPI_SCK};          /**< TLE5012 Sensor2Go Kit with XMC1100 */
sensType_t TLE5012_breakOut  =  {UNUSED_PIN,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MOSI,PIN_SPI_SCK}; /**< TLE5012 breakout board removed from the Sensor2Go Kit */
sensType_t TLE5012_bulk      =  {UNUSED_PIN,PIN_SPI_SS,PIN_SPI_MOSI,PIN_SPI_MOSI,PIN_SPI_SCK}; /**< TLE5012 bulk chip (see manual on how to connect the 3wire SPI */

#endif /** TLE5012_FRAMEWORK **/
/** @} */