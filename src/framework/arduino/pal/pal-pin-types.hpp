/**
 * @file        pal-pin-types.hpp
 * @brief       Arduino PAL for the GPIO and SPI
 * @date        July 2023
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef PAL_PIN_TYPES_HPP_
#define PAL_PIN_TYPES_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

namespace tle5012
{

    /**
     * @addtogroup arduinoPal
     * @{
     * The pin definition here is only used when no PIN_SPI_xx is defined, otherwise the original setting is used.
     * THe set pins should be valid for esp32 boards for the VSPI (channel 3 SPI).
     * Change if you have other pin settings
     */
    #define UNUSED_PIN          0xFF

    #ifndef PIN_SPI_EN
    #define PIN_SPI_EN          UNUSED_PIN  /*!< TLE5012 with any other PCB has no switch on/off */
    #endif

    #ifndef PIN_SPI_SS
    #define PIN_SPI_SS          5
    #define SS                  5
    #endif

    #ifndef PIN_SPI_MISO
    #define PIN_SPI_MISO        19
    #define MISO                19
    #endif

    #ifndef PIN_SPI_MOSI
    #define PIN_SPI_MOSI        23
    #define MOSI                23
    #endif

    #ifndef PIN_SPI_SCK
    #define PIN_SPI_SCK         18
    #define SCK                 18
    #endif

    /** @} */
    // Support macros
    //!< \brief Prints a binary number with leading zeros (Automatic Handling)
    #define PRINTBIN(Num) for (uint32_t t = (1UL << ((sizeof(Num)*8)-1)); t; t >>= 1) Serial.write(Num  & t ? '1' : '0');
    //!< \brief Prints a binary number with leading zeros (Automatic Handling) with space
    #define PRINTBINS(Num) for (uint32_t t = (1UL << ((sizeof(Num)*8)-1)); t; t >>= 1) Serial.write(Num  & t ? " 1 " : " 0 ");


}


#endif /** TLE5012_FRAMEWORK **/
#endif /** PAL_PIN_TYPES_HPP_ **/
