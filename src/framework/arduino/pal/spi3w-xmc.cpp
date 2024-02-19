/*
 * \file        spi3w-xmc-ino.cpp
 * \brief       XMC 3wire SPI cover
 * \author      Infineon Technologies AG
 * \version     4.0.0
 * \copyright   2020-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#include "spi3w-ino.hpp"

#if (SPI3W_INO == SPI3W_XMC)

using namespace tle5012;

/**
 * @addtogroup arduinoPal
 * @{
 *
 * @brief This class extends the XMC4Arduino SPIClass to handle 3wire SSC SPI
 * also on other than the default SPI channel in case of the XMC4xxx boards
 */

/**
 * @brief Construct a new SPIClass3W::SPIClass3W object
 *
 */
SPIClass3W::SPIClass3W(uint8_t spiNum):SPIClass()
{
    this->mCS = PIN_SPI_SS;
    this->mMISO = PIN_SPI_MISO;
    this->mMOSI = PIN_SPI_MOSI;
    this->mSCK = PIN_SPI_SCK;
    this->mSpiNum = spiNum;
}

/**
 * @brief Destroy the SPIClass3W::SPIClass3W object
 *
 */
SPIClass3W::~SPIClass3W()
{
}

/*!
 * @brief overwrite the default begin function
 *
 * @param miso [in] pin number for miso, on sensor2go boards the same than mosi
 * @param mosi [in] pin number for mosi, on sensor2go boards the same than miso
 * @param sck  [in] the system clock pin for external clock driver
 * @param cs   [in] chip select pin, up to four different cs pins can be used together with the slave number
 */
void SPIClass3W::begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs)
{
    setCSPin(cs);
    this->mMOSI = mosi;
    this->mMISO = miso;
    this->mSCK = sck;
    m3Wire.mosi = mapping_port_pin[this->mMOSI];
    m3Wire.miso = mapping_port_pin[this->mMISO];
    m3Wire.sck  = mapping_port_pin[this->mSCK];
    setupSPI();
    initSpi();
}

/*!
 * @brief Set the chip select pin. This function is needed if more than one
 * sensor is in the SPI bus
 * @param cs [in] Pin number of the sensors chip select
 */
void SPIClass3W::setCSPin(uint8_t cs)
{
    this->mCS = cs;
    m3Wire.cs   = mapping_port_pin[this->mCS];
}

/**
 * @brief The setup function fills the XMC_3W_SPI_t structure for all XMC boards
 * with the appropiate values.
 *
 */
void SPIClass3W::setupSPI()
{
    m3Wire.miso_open.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
    m3Wire.miso_close.mode = XMC_GPIO_MODE_INPUT_TRISTATE;

    m3Wire.mosi_open.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
    m3Wire.mosi_close.mode = XMC_GPIO_MODE_INPUT_TRISTATE;

    m3Wire.sck_config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
    m3Wire.channel_config.baudrate = SPEED;
    m3Wire.channel_config.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER;
    m3Wire.channel_config.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS;
    m3Wire.channel_config.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE;

    m3Wire.cs_config.mode = OUTPUT;
    m3Wire.cs_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;

    #if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
        m3Wire.channel = XMC_SPI0_CH1;
        m3Wire.input_source = XMC_INPUT_C;
        m3Wire.miso_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
        m3Wire.miso_close.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
        m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
        m3Wire.mosi_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
        m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
        m3Wire.sck_config.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
    #elif defined(XMC1100_Boot_Kit) || defined(XMC1300_Boot_Kit) || defined(XMC1400_Boot_Kit)
        m3Wire.channel = XMC_SPI0_CH0;
        m3Wire.input_source = XMC_INPUT_D;
        m3Wire.miso_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
        m3Wire.miso_close.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
        m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6;
        m3Wire.mosi_open.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
        m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6;
        m3Wire.sck_config.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD;
    #elif defined(XMC4400_Platform2GO) || defined(XMC4200_Platform2GO)
        m3Wire.channel = XMC_SPI1_CH1;
        m3Wire.miso_close.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.miso_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.mosi_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
        m3Wire.sck_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.cs_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4;
        m3Wire.input_source = XMC_INPUT_D;
    #elif defined(XMC4700_Relax_Kit)
        m3Wire.miso_close.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.miso_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.mosi_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.sck_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        m3Wire.cs_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
        if (mSpiNum == 1) {
            m3Wire.channel = XMC_SPI1_CH1;
            m3Wire.input_source = XMC_INPUT_D;
            m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2;
            m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2;
        }else if (mSpiNum == 2) {
            m3Wire.channel = XMC_SPI2_CH1;
            m3Wire.input_source = XMC_INPUT_D;
            m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
            m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
        }else {
            m3Wire.channel = XMC_SPI2_CH0;
            m3Wire.input_source = XMC_INPUT_C;
            m3Wire.mosi_open.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
            m3Wire.sck_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1;
        }
    #endif
}

/**
 * @brief Overwrite the default SPIClass init function for the
 * use with the 3wire SSC SPI interface
 *
 */
void SPIClass3W::initSpi()
{
    if((m3Wire.channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_I2C)
    {
        Wire.end();
    }
    XMC_SPI_CH_EnableMasterClock(m3Wire.channel);
    XMC_SPI_CH_Init(m3Wire.channel, &(m3Wire.channel_config));

    XMC_SPI_CH_SetWordLength(m3Wire.channel, (uint8_t)16U);
    XMC_SPI_CH_SetFrameLength(m3Wire.channel, (uint8_t)16U);
    XMC_SPI_CH_SetInputSource(m3Wire.channel, XMC_SPI_CH_INPUT_DIN0, (uint8_t)m3Wire.input_source);

    XMC_SPI_CH_ConfigureShiftClockOutput(m3Wire.channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
    XMC_SPI_CH_SetBaudrate(m3Wire.channel, (uint32_t)m3Wire.channel_config.baudrate);
    XMC_SPI_CH_SetBitOrderMsbFirst(m3Wire.channel);

    XMC_SPI_CH_Start(m3Wire.channel);

    XMC_GPIO_Init(m3Wire.sck.port, m3Wire.sck.pin, &m3Wire.sck_config);
    XMC_GPIO_Init(m3Wire.cs.port, m3Wire.cs.pin, &m3Wire.cs_config);
    XMC_GPIO_SetOutputLevel( m3Wire.cs.port, m3Wire.cs.pin,XMC_GPIO_OUTPUT_LEVEL_HIGH);
}

/*!
 * @brief Main SPI three wire communication functions for sending and receiving data
 *
 * @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
 * @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
 * @param received_data pointer to data structure buffer for the read data
 * @param size_of_received_data size of data words to be read
 */
void SPIClass3W::sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
{
    uint32_t data_index = 0;
    //send via TX
    XMC_GPIO_Init(m3Wire.miso.port, m3Wire.miso.pin, &m3Wire.miso_close);
    XMC_GPIO_Init(m3Wire.mosi.port, m3Wire.mosi.pin, &m3Wire.mosi_open);
    XMC_GPIO_SetOutputLevel(m3Wire.cs.port, m3Wire.cs.pin,XMC_GPIO_OUTPUT_LEVEL_LOW);

    for(data_index = 0; data_index < size_of_sent_data; data_index++)
    {
        XMC_SPI_CH_Transmit(m3Wire.channel, sent_data[data_index], XMC_SPI_CH_MODE_STANDARD);
        while((XMC_SPI_CH_GetStatusFlag(m3Wire.channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
        XMC_SPI_CH_ClearStatusFlag(m3Wire.channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);
        while (XMC_USIC_CH_GetReceiveBufferStatus(m3Wire.channel) == 0U);
        received_data[0] = XMC_SPI_CH_GetReceivedData(m3Wire.channel);
    }

    // receive via RX
    XMC_GPIO_Init(m3Wire.miso.port, m3Wire.miso.pin, &m3Wire.miso_open);
    XMC_GPIO_Init(m3Wire.mosi.port, m3Wire.mosi.pin, &m3Wire.mosi_close);
    delayMicroseconds(5);

    for(data_index = 0; data_index < size_of_received_data; data_index++)
    {
        XMC_SPI_CH_Transmit(m3Wire.channel, 0x0000, XMC_SPI_CH_MODE_STANDARD);
        while((XMC_SPI_CH_GetStatusFlag(m3Wire.channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
        XMC_SPI_CH_ClearStatusFlag(m3Wire.channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);
        while (XMC_USIC_CH_GetReceiveBufferStatus(m3Wire.channel) == 0U);
        received_data[data_index] = XMC_SPI_CH_GetReceivedData(m3Wire.channel);
    }

    XMC_GPIO_SetOutputLevel(m3Wire.cs.port, m3Wire.cs.pin,XMC_GPIO_OUTPUT_LEVEL_HIGH);
}

/** @} */

#endif /* SPI3W_INO */
