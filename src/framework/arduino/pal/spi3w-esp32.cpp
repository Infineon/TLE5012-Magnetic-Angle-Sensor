/*
 * \file        spi3w-esp32-ino.cpp
 * \brief       ESP32 3wire SPI cover
 * \author      Infineon Technologies AG
 * \version     4.0.0
 * \copyright   2020-2024 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "spi3w-ino.hpp"
#include "pal-pin-types.hpp"

#if (SPI3W_INO == SPI3W_ESP32)

#include <driver/spi_master.h>
#include "sdkconfig.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

using namespace tle5012;

/**
 * @brief This is a special spi send and receive function for the TLE5012 based on
 * the ESP-IDF library. We avoid here the ESP32hal driver from the Arduino package.
 *
 * Function is from easyio-lib-for-esp32 see https://github.com/ZhiliangMa/easyio-lib-for-esp32
 *
 * @param spi       the spi structure
 * @param senddata  the send buffer
 * @return uint16_t the result from the rx buffer
 */
uint16_t tle5012b_spi_send_and_recv_uint16(spi_device_handle_t spi, uint16_t senddata)
{
    uint8_t temp = 0;
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));

    uint8_t p_data[2];
    p_data[0] = senddata >> 8;
    p_data[1] = senddata;

    t.length = 8 * 2;
    t.tx_buffer = p_data;
    t.flags = SPI_TRANS_USE_RXDATA;
    ret = spi_device_polling_transmit(spi, &t);
    assert(ret == ESP_OK);

    temp = *t.rx_data;
    *t.rx_data = *(t.rx_data + 1);
    *(t.rx_data + 1) = temp;

    return *(uint16_t*)t.rx_data;
}


/**
 * @addtogroup arduinoPal
 * @{
 *
 * @brief Arduino SPIClass extension to use 3wire SSC SPI interfaces
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
    spi_device_handle_t esp3Wire = NULL; // Some C structure and
    this->e3Wire = &esp3Wire;            // void pointer magic
}

/**
 * @brief Destroy the SPIClass3W::SPIClass3W object
 *
 */
SPIClass3W::~SPIClass3W()
{
}

/*!
 * @brief New for fetching SPI parameter
 * We use the ESP32-IDF driver instead of the ESP32hal from the Arduino core as the IDF is more complete
 * and allows some tricks we need here.
 * To avoid conflicts we do not set the CS via the driver but set is manually.
 * This is made for the ESP32 not for the ESP S2/S3/C3 versions.
 * @param miso [in] pin number for miso, on sensor2go boards the same than mosi
 * @param mosi [in] pin number for mosi, on sensor2go boards the same than miso
 * @param sck [in] the system clock pin for external clock driver
 * @param cs [in] chip select pin, up to four different cs pins can be used together with the slave number
 */
void SPIClass3W::begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs)
{
    setCSPin(cs);
    this->mMOSI = mosi;
    this->mMISO = miso;
    this->mSCK = sck;

    esp_err_t intError;
    // bus config for the ESP-IDF driver
    spi_bus_config_t bus_config = {};
    bus_config.sclk_io_num = this->mSCK;                            // CLK
    bus_config.mosi_io_num = this->mMOSI;                           // MOSI
    bus_config.miso_io_num = this->mMISO;                           // no MISO setting for 3Wire but we use 4Wire
    bus_config.quadwp_io_num = -1;                                  // Not used
    bus_config.quadhd_io_num = -1;                                  // Not used
    intError = spi_bus_initialize(VSPI_HOST, &bus_config, false);   // use the VSPI of the ESP32 which is SPI3

    // add device for the ESP-IDF driver
    spi_device_interface_config_t dev_config = {}; // initializes all field to 0
    dev_config.address_bits = 0;
    dev_config.command_bits = 0;
    dev_config.dummy_bits = 0;
    dev_config.mode = 1;
    dev_config.clock_speed_hz = SPEED;
    dev_config.spics_io_num = -1;                                   // we set CS external
   // dev_config.flags = SPI_DEVICE_3WIRE;
    dev_config.queue_size = 7;
    dev_config.pre_cb = NULL;
    dev_config.post_cb = NULL;
    intError = spi_bus_add_device(VSPI_HOST, &dev_config, &(*(spi_device_handle_t*)this->e3Wire));
    ESP_ERROR_CHECK(intError);

    gpio_set_direction((gpio_num_t)this->mMOSI, GPIO_MODE_INPUT_OUTPUT_OD); // set the MOSI for INPUT and OUTPUT
    gpio_set_pull_mode((gpio_num_t)this->mMOSI, GPIO_PULLUP_ONLY);

    pinMode(this->mCS, OUTPUT);
    digitalWrite(this->mCS, HIGH);
}

/*!
 * @brief Set the chip select pin. This function is needed if more than one
 * sensor is in the SPI bus
 *
 * @param cs [in] Pin number of the sensors chip select
 */
void SPIClass3W::setCSPin(uint8_t cs)
{
    this->mCS = cs;
}

/*!
 * @brief Main SPI three wire communication functions for sending and receiving data
 *
 * @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
 * @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
 * @param received_data pointer to data structure buffer for the read data
 * @param size_of_received_data size of data words to be read
 */
void SPIClass3W::sendReceiveSpi(uint16_t *sent_data, uint16_t size_of_sent_data, uint16_t *received_data, uint16_t size_of_received_data)
{
    uint32_t data_index = 0;
    // Command send
    digitalWrite(this->mCS, LOW);

    for (data_index = 0; data_index < size_of_sent_data; data_index++)
    {
        received_data[0] = tle5012b_spi_send_and_recv_uint16( (*(spi_device_handle_t*)this->e3Wire), sent_data[data_index]);
    }

    // Receive result
    for(data_index = 0; data_index < size_of_received_data; data_index++)
    {
      received_data[data_index] = tle5012b_spi_send_and_recv_uint16( (*(spi_device_handle_t*)this->e3Wire), 0x0000);
    }

    digitalWrite(this->mCS, HIGH);
}

/** @} */

#endif /* SPI3W_INO */
