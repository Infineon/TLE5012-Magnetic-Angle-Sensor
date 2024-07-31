/**
 * @file        tlx512-pal-spic.hpp
 * @brief       PAL of the SPI cover
 * @date        January 2024
 * @copyright   Copyright (c) 2019-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */



#ifndef TLX5012_PAL_SPIC_HPP_
#define TLX5012_PAL_SPIC_HPP_

#include <stdint.h>
#include "tle5012b_types.hpp"

namespace tle5012
{

/**
 * @addtogroup pal
 * @{
 */

/**
 * @class SPICPAL
 * @brief SPI abstract API
 */
class SPICPAL
{
    public:

        /**
         * @brief       Initializes the SPIC
         * @return      SPIC error code
         * @retval      OK if success
         * @retval      INIT_ERROR if initialization error
         */
        virtual Error_t        init        () = 0;

        /**
         * @brief       Deinitialize the SPIC
         * @return      SPIC error code
         * @retval      OK if success
         * @retval      INIT_ERROR if deinitialization error
         */
        virtual Error_t       deinit      () = 0;

        /**
         * @brief       Sends a trigger through out the SPI bus
         * @return      SPIC error code
         * @retval      OK if success
         * @retval      INIT_ERROR if deinitialization error
         */
        virtual Error_t       triggerUpdate() = 0;

        /**
         * @brief           Function which allows 3wire SPI (SSC) by sending and receiving data in the same function
         *
         * @param sent_data              pointer two 2*unit16_t value for one command word and one data word if something should be written
         * @param size_of_sent_data      the size of the command word default 1 = only command 2 = command and data word
         * @param received_data          pointer to data structure buffer for the read data
         * @param size_of_received_data  size of data words to be read
         * @return                       SPIC error code
         * @retval                       OK if success
         * @retval                       INIT_ERROR if transfer fails
         */
        virtual Error_t       sendReceive(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data) = 0;

};

/** @} */

}

#endif /** TLX5012_PAL_SPIC_HPP_ **/