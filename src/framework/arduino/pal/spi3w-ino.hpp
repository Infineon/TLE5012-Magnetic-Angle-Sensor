/*
 * \file        spi3w-ino.hpp
 * \brief       Arduino SPI 3wire extension
 * \author      Infineon Technologies AG
 * \version     4.0.0
 * \copyright   2020-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

/**
 * @addtogroup arduinoPal
 * @{
 */
namespace tle5012
{


/**
 * @brief Arduino SPIClass3W extends the default SPIClass
 * The extension allows the use of 3wire SSC SPI interfaces for
 * default Arduino and for XMC, special for the Sensor2go kit
 * Therefore via the correct code is loaded via SPI3W_INO macro settings.
 *
 * @attention keep in mind, you can set more different chip select pins, but
 * you can not separate more than 4 sensors data streams from each other
 *
 */

#ifndef SPI3W_INO_HPP
#define SPI3W_INO_HPP

#define SPI3W_ARD        1
#define SPI3W_XMC        2
#define SPI3W_ESP32      3

#define MAX_SLAVE_NUM    4              //!< Maximum numbers of slaves on one SPI bus
#define SPEED            1000000U       //!< default speed of SPI transfer

class SPIClass3W : public SPIClass
{

    public:
        #if defined(UC_FAMILY) && (UC_FAMILY == 1 || UC_FAMILY == 4)
            #define SPI3W_INO SPI3W_XMC
        #elif defined(ESP32)
            #define SPI3W_INO SPI3W_ESP32
        #else
            #define SPI3W_INO SPI3W_ARD
        #endif


        uint8_t     mCS;                //!< Pin for chip select
        uint8_t     mSpiNum;            //!< Number of used SPI channel

                SPIClass3W(uint8_t spiNum = 0);
                ~SPIClass3W();
        void    begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs);
        void    setCSPin(uint8_t cs);
        void    sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

    private:

        uint8_t     mMOSI;               //!< Pin for SPI MOSI
        uint8_t     mMISO;               //!< Pin for SPI MISO
        uint8_t     mSCK;                //!< Pin for SPI System Clock


        #if defined(UC_FAMILY) && (UC_FAMILY == 1 || UC_FAMILY == 4)
            /*!
            * The enhanced 3-Wire parameter structure includes miso/mosi open and close
            * setting and for the enable pin setting of the Sensor2Go evaluation boards.
            */
            typedef struct
            {
                XMC_USIC_CH_t*           channel;
                XMC_SPI_CH_CONFIG_t      channel_config;
                XMC_PORT_PIN_t           mosi;
                XMC_GPIO_CONFIG_t        mosi_open;
                XMC_GPIO_CONFIG_t        mosi_close;
                XMC_PORT_PIN_t           miso;
                XMC_GPIO_CONFIG_t        miso_open;
                XMC_GPIO_CONFIG_t        miso_close;
                XMC_USIC_INPUT_t         input_source;
                XMC_PORT_PIN_t           sck;
                XMC_GPIO_CONFIG_t        sck_config;
                XMC_PORT_PIN_t           cs;
                XMC_GPIO_CONFIG_t        cs_config;
            } XMC_3W_SPI_t;

            XMC_3W_SPI_t      m3Wire;    //!< enhanced 3-Wire SPI parameter structure

            void setupSPI();             //!< initial 3-Wire SPI setup
            void initSpi();              //!< initial startup of the 3-Wire SPI interface

        #elif defined(ESP32)
            void *e3Wire;                //!< we use a void pointer to avoid loading the ESP-IDF driver here
        #endif


};

/**
 * @brief define a new SPI3W macro for handling more than the default SPI channel
 *
 */
extern SPIClass3W SPI3W;
#if (NUM_SPI > 1)
    extern SPIClass3W SPI3W1;
#   if (NUM_SPI > 2)
        extern SPIClass3W SPI3W2;
#       if (NUM_SPI > 3)
            extern SPIClass3W SPI3W3;
#           if (NUM_SPI > 4)
                extern SPIClass3W SPI3W4;
#           endif
#       endif
#   endif
#endif

/** @} */
}

#endif /* SPI3W_INO_HPP */
