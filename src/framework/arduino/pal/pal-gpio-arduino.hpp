/**
 * \file        pal-gpio-arduino.hpp
 * \brief       Arduino PAL for the GPIO
 * \author      Infineon Technologies AG
 * \version     4.0.0
 * \copyright   2020-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef PAL_GPIO_ARDUINO_HPP_
#define PAL_GPIO_ARDUINO_HPP_


#include "tlx5012-pal-gpio.hpp"


namespace tle5012
{
    /**
     * @addtogroup arduinoPal
     * @{
     */


    /**
     * @class  GPIOIno
     * @brief  GPIO platform abstraction layer Arduino API
     */
    class GPIOIno: virtual public GPIOPAL
    {
        private:
            uint8_t     pin;
            uint8_t     mode;
            VLogic_t    logic;

        public:
            static constexpr uint8_t  UNUSED_PIN = 0xFFU;    /**< Unused pin */

                        GPIOIno();
                        GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic);
                        ~GPIOIno();
            Error_t     init();
            Error_t     changeMode(uint8_t mode);
            Error_t     deinit();
            VLevel_t    read();
            Error_t     write(VLevel_t level);
            Error_t     enable();
            Error_t     disable();
    };

    /** @} */

}

#endif /** PAL_GPIO_ARDUINO_HPP_ **/
