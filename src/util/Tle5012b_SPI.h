/*!
 * \name        Tle5012b_SPI.h - Library for Arduino for the TLE5012B angle sensor.
 * \author      Infineon Technologies AG (Dr.Olaf Filies)
 * \copyright   Infineon Technologies AG
 * \version     2.0.1
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 * \details
 * This library includes the 3-wire/4-wire SPI connection for the TLE5012B -E1000/E5000/E9000
 * Sensor2GO kits are 3-wire connected, so MOSI/MISO are the same and read/write must be switched.
 * Only if you break the sensor or use the Evalboard a 4-wire SPI is possible.
 * If you use the Evalboard, than also use the resistors as mentioned in the manual.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Arduino.h"
#include "SPI.h"

#ifndef TLE5012B_SPI_H
#define TLE5012B_SPI_H

#define SPEED            1000000U //!< default speed of SPI transfer
#define PIN_SPI_EN       8        //!< Sensor Enable pin for XMC Sensor2Go only
#define MAX_SLAVE_NUM    4        //!< Maximum numbers of slaves on one SPI bus
                                  //!< Attention, keep in mind, you can set more different chipselect pins, but
                                  //!< you can not separate more than 4 sensors data streams from each other


class Tle5012b_SPI : public SPIClass
{
	public:

	/*!
	 * Constructor with optional SPI channel number which can be used for XMC4700 or
	 * any other microcontroller with more than the default SPI to connect more
	 * than four sensors at a time.
	 * @param spiNum [in] optional SPI channel number
	 */
	Tle5012b_SPI(uint8_t spiNum = 0);
	~Tle5012b_SPI();

	uint8_t mCS;                    //!< Pin for chip select (pin 0.9 on test board)
	uint8_t mSpiNum;                //!< Number of used SPI channel

	/*!
	 * New for fetching SPI parameter
	 * @param miso [in] pin number for miso, on sensor2go boards the same than mosi
	 * @param mosi [in] pin number for mosi, on sensor2go boards the same than miso
	 * @param sck [in] the system clock pin for external clock driver
	 * @param cs [in] chipselect pin, up to four different cs pins can be used together with the slave number
	 */
	void begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs);

	/*!
	 * Set the chipselect pin. This function is needed if more than one
	 * sensor is in the SPI bus
	 * @param cs [in] Pin number of the sensors chip select
	 */
	void setCSPin(uint8_t cs);

	/*!
	 * Main SPI three wire communication functions for sending and receiving data
	 * @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
	 * @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
	 * @param received_data pointer to data structure buffer for the read data
	 * @param size_of_received_data size of data words to be read
	 */
	void sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data);

	void sendConfig();            //!< set SPI to send mode
	void receiveConfig();         //!< set SPI to receive mode

	private:
	uint8_t mMOSI;                //!< Pin for SPI MOSI (e.g. pin 0.6 on test board);
	uint8_t mMISO;                //!< Pin for SPI MISO (e.g. pin 0.7 on test board)
	uint8_t mSCK;                 //!< Pin for CLOCK (e.g. pin 0.8 on test board)
	SPISettings mSPISetting;      //!< We need the original SPI class setting in case none XMC microcontroller

	#if defined(UC_FAMILY) && (UC_FAMILY == 1 || UC_FAMILY == 4)
		/*!
		 * The enhanced 3-Wire parameter structure includes miso/mosi open and close
		 * setting and for the enable pin setting for the Sensor2Go evaluation boards.
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
		} XMC_3W_SPI_t;

		XMC_3W_SPI_t m3Wire;        //!< enhanced 3-Wire SPI parameter structure

		void setupSPI();            //!< initial 3-Wire SPI setup
		void initSpi();             //!< initial startup of the 3-Wire SPI interface
		void enableSpi();           //!< enables 3-Wire SPI interface
	#endif
};

#endif
