/**
 * @file        tlx512-pal-gpio.hpp
 * @brief       PAL of the GPIO
 * @date        January 2024
 * @copyright   Copyright (c) 2019-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TLX5012_PAL_GPIO_HPP_
#define TLX5012_PAL_GPIO_HPP_

#include <stdint.h>
#include "tle5012b_types.hpp"

namespace tle5012
{

/**
 * @addtogroup pal
 * @{
 */

class GPIOPAL
{
    public:

        /**
         * @name   Interrupt event
         * @{
         */
        enum IntEvent_t
        {
            INT_FALLING_EDGE   = 0,     /**< Interrupt on falling edge */
            INT_RISING_EDGE    = 1,     /**< Interrupt on rising edge */
        };
        /** @} */

        /**
         * @name    Voltage level
         * @{
         */
        enum VLevel_t
        {
            GPIO_LOW   = 0,        /**< Level low */
            GPIO_HIGH  = 1         /**< Level high */
        };
        /** @} */

        /**
         * @name    Voltage logic
         * @{
         */
        enum VLogic_t
        {
            NEGATIVE = 1,       /**< Negative logic. 0 on voltage level high, 1 on voltage low */
            POSITIVE = 2,       /**< Positive logic. 1 on voltage level high, 0 on voltage low */
        };
        /** @} */

        /**
         * @brief       Initializes the GPIO
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      INIT_ERROR if initialization error
         */
        virtual Error_t        init        () = 0;

        /**
             * @brief       Deinitialize the GPIO
             * @return      GPIO error code
             * @retval      OK if success
             * @retval      INIT_ERROR if deinitialization error
         */
        virtual Error_t       deinit      () = 0;

        /**
             * @brief       Changes the IN/OUT mode
             * @param[in]   mode INPUT or OUTPUT mode of pin
             * @return      GPIO error code
             * @retval      OK if success
             * @retval      INIT_ERROR if deinitialization error
         */
        virtual Error_t       changeMode  (uint8_t mode) = 0;

        /**
         * @brief       Reads the GPIO voltage level
         * @return      GPIO voltage level
         * @retval      GPIO_LOW if voltage low
         * @retval      GPIO_HIGH if voltage high
         */
        virtual VLevel_t       read        () = 0;

        /**
         * @brief       Writes the GPIO output voltage level
         * @param[in]   level  Voltage level
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      WRITE_ERROR if write error
         */
        virtual Error_t        write       (VLevel_t level) = 0;

        /**
         * @brief       Enables the GPIO output according to the GPIO logic
         *              - Low if negative
         *              - High if positive
         * @return      GPIO interrupt event
         * @retval      OK if success
         * @retval      WRITE_ERROR if write error
         */
        virtual Error_t        enable      () = 0;

        /**
         * @brief       Disables the GPIO output according to the GPIO logic
         *              - Low if positive
         *              - High if negative
         * @return      GPIO error code
         * @retval      OK if success
         * @retval      WRITE_ERROR if write error
         */
        virtual Error_t        disable     () = 0;

};

/** @} */

}

#endif /** TLX5012_PAL_GPIO_HPP_ **/