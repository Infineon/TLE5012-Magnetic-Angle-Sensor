/**
 * @file        tle5012-conf.hpp
 * @brief       TLE5012 Library Configuration
 * @date        October 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE5012_CONF_HPP_
#define TLE5012_CONF_HPP_

#include "tle5012-conf-opts.hpp"

/**
 * @addtogroup tle5012frmw
 * @{
 */

#ifndef TLE5012_FRAMEWORK
#define TLE5012_FRAMEWORK    TLE5012_FRMWK_ARDUINO
#endif

#ifndef TLE5012_SPIC_PAL
#define TLE5012_SPIC_PAL     TLE5012_SPIC_XMC
#endif

#include "tle5012-conf-dfl.hpp"
/** @} */

#endif /** TLE5012_CONF_HPP_ **/