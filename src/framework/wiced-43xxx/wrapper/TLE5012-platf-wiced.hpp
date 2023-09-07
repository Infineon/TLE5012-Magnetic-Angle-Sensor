/**
 * @file        TLE5012-platf-wiced.hpp
 * @brief       TLE5012 Wiced Hardware Platforms
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE5012_PLATF_WICED_HPP_
#define TLE5012_PLATF_WICED_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

namespace tle5012
{

/**
 * @class Tle5012Wiced
 *
 * @brief represents the TLE5012 base class
 *
 * This class provides a simple API for connecting the TLE5012 via SSC interface,
 * which is included into all flavours the TLE5012 sensor. This setup also
 * works with the Sens2Kit (Sensor including XMC1100 mcu), breakout board (only the Sensor
 * from the Sens2Kit) and bulk chip (read the section on how to connect the bulk chip via 3wire SPI).
 *
 * @addtogroup platfWiced
 * @{
 */

#include "../pal/TLE5012-pal-wiced.hpp"
#include <wiced.h>

// Support macros
//!< \brief Prints a binary number with leading zeros (Automatic Handling)
#define PRINTBIN(Num) for (uint32_t t = (1UL << ((sizeof(Num)*8)-1)); t; t >>= 1) WPRINT_APP_INFO(("%u ",(Num  & t ? 1 : 0) ));
//!< \brief Prints a binary number with leading zeros (Automatic Handling) with space
#define PRINTBINS(Num) for (uint32_t t = (1UL << ((sizeof(Num)*8)-1)); t; t >>= 1) WPRINT_APP_INFO((" %u ",(Num  & t ? 1 : 0) ));

/** @} */

}

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_PLATF_WICED_HPP_ **/