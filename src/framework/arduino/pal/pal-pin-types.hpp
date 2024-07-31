/**
 * \file        pal-pin-types.hpp
 * \brief       pin settings if not pins are defined
 * \author      Infineon Technologies AG
 * \version     4.0.0
 * \copyright   2020-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#ifndef PAL_PIN_TYPES_HPP_
#define PAL_PIN_TYPES_HPP_

namespace tle5012
{

    /**
     * @addtogroup arduinoPal
     * @{
     * The pin definition here is only used when no PIN_SPI_xx is defined, otherwise the original setting is used.
     * The set pins used here should be valid for esp32 boards with the VSPI (channel 3 SPI).
     * Change them if you have other pin settings
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


}

#endif /** PAL_PIN_TYPES_HPP_ **/
