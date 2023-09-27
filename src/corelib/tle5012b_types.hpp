	/**
 * @file        hss-types.hpp
 * @brief       High side switch types
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLE5012B_TYPES_HPP_
#define TLE5012B_TYPES_HPP_

namespace tle5012
{
    /**
     * @addtogroup tle5012bCorelib
     * @{
     */

    /**
     * @brief Error codes
     * @{
     */
    enum Error_t
    {
        OK                   =  0,   /**< No error */
        INTF_ERROR           = -1,   /**< Interface error */
        CONF_ERROR           = -2,   /**< Configuration error */
        READ_ERROR           = -3,   /**< Read error */
        WRITE_ERROR          = -4,   /**< Write error */
        NULLPTR_ERROR        = -5,   /**< Null pointer error */
        INVALID_CH_ERROR     = -6,   /**< Invalid channel error */
        UNSUPPORTED_OP_ERROR = -7,   /**< Invalid channel error */
        INIT_ERROR           = -8    /**< Not initialized */
    };
    /** @} */

}
/** @} */


#endif /** TLE5012B_TYPES_HPP_ **/