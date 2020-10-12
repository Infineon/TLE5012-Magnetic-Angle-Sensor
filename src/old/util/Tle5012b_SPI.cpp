/*!
 * \name        Tle5012b_SPI.h - Library for Arduino for the TLE5012B angle sensor.
 * \author      Infineon Technologies AG
 * \copyright   Infineon Technologies AG
 * \version     2.0.1
 * \brief       GMR-based angle sensor for angular position sensing in automotive applications
 *              This library includes the 3-wire SPI connection for the TLE5012B -E1000/E5000/E9000 sensor2GO kits
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

#include "Tle5012b.h"
#include "Wire.h"

Tle5012b_SPI::Tle5012b_SPI(uint8_t spiNum)
{
	mCS = PIN_SPI_SS;
	mMISO = PIN_SPI_MISO;
	mMOSI = PIN_SPI_MOSI;
	mSCK = PIN_SPI_SCK;
	mSpiNum = spiNum;
	mSPISetting = SPISettings(SPEED,MSBFIRST,SPI_MODE1);
}
Tle5012b_SPI::~Tle5012b_SPI()
{
}

void Tle5012b_SPI::begin(uint8_t miso, uint8_t mosi, uint8_t sck, uint8_t cs)
{
	setCSPin(cs);
	mMOSI = mosi;
	mMISO = miso;
	mSCK = sck;
	#if defined(UC_FAMILY) && (UC_FAMILY == XMC1 || UC_FAMILY == XMC4)
		m3Wire.mosi	= mapping_port_pin[mosi];
		m3Wire.miso	= mapping_port_pin[miso];
		m3Wire.sck	= mapping_port_pin[sck];
		setupSPI();
		enableSpi();
	#else
		mSPISetting = SPISettings(SPEED,MSBFIRST,SPI_MODE1);
		SPIClass::begin();
		//SPI.setClockDivider(SPI_CLOCK_DIV4);
	#endif
}

void Tle5012b_SPI::setCSPin(uint8_t cs)
{
	mCS = cs;
}


#if defined(UC_FAMILY) && (UC_FAMILY == XMC1 || UC_FAMILY == XMC4)
	/*!
	* XMC microcontroller familly needs special settings for
	* using SPI channels settings for each type and SPI channel.
	* Also the send/receive should be done in XMC CMSIS function for
	* a fast data fetch by avoiding the SPI library.
	*/

	void Tle5012b_SPI::setupSPI()
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
		#elif defined(XMC4700_Relax_Kit)
			m3Wire.miso_close.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
			m3Wire.miso_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
			m3Wire.mosi_open.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
			m3Wire.sck_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
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

	void Tle5012b_SPI::initSpi()
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
	}

	 void Tle5012b_SPI::enableSpi()
	 {
	 	initSpi();
	 	XMC_GPIO_Init(m3Wire.sck.port, m3Wire.sck.pin, &m3Wire.sck_config);
	 }

	 void Tle5012b_SPI::sendConfig()
	 {
	 	XMC_GPIO_Init(m3Wire.miso.port, m3Wire.miso.pin, &m3Wire.miso_close);
	 	XMC_GPIO_Init(m3Wire.mosi.port, m3Wire.mosi.pin, &m3Wire.mosi_open);
	 }

	 void Tle5012b_SPI::receiveConfig()
	 {
	 	XMC_GPIO_Init(m3Wire.miso.port, m3Wire.miso.pin, &m3Wire.miso_open);
	 	XMC_GPIO_Init(m3Wire.mosi.port, m3Wire.mosi.pin, &m3Wire.mosi_close);
	 }

	void Tle5012b_SPI::sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
	{
		uint32_t data_index = 0;
		//send via TX
		sendConfig();
		digitalWrite(mCS, LOW);

		for(data_index = 0; data_index < size_of_sent_data; data_index++)
		{
			XMC_SPI_CH_Transmit(m3Wire.channel, sent_data[data_index], XMC_SPI_CH_MODE_STANDARD);
			while((XMC_SPI_CH_GetStatusFlag(m3Wire.channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
			XMC_SPI_CH_ClearStatusFlag(m3Wire.channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);
			while (XMC_USIC_CH_GetReceiveBufferStatus(m3Wire.channel) == 0U);
			received_data[0] = XMC_SPI_CH_GetReceivedData(m3Wire.channel);
		}

		// receive via RX
		receiveConfig();
		delayMicroseconds(5);

		for(data_index = 0; data_index < size_of_received_data; data_index++)
		{
			XMC_SPI_CH_Transmit(m3Wire.channel, 0x0000, XMC_SPI_CH_MODE_STANDARD);
			while((XMC_SPI_CH_GetStatusFlag(m3Wire.channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
			XMC_SPI_CH_ClearStatusFlag(m3Wire.channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);
			while (XMC_USIC_CH_GetReceiveBufferStatus(m3Wire.channel) == 0U);
			received_data[data_index] = XMC_SPI_CH_GetReceivedData(m3Wire.channel);
		}

		digitalWrite(mCS, HIGH);
	}

#else
	/*!
	 * Any other arduino compliant library such run through the default
	 * SPI setup. This implement the 3-Wire SPI, so MISO/MOSI are connected short.
	 * If you want to us the build chip with a 4-Wire SPI than checkout the
	 * special 4-Wire library
	 */

	void Tle5012b_SPI::sendConfig()
	{
		pinMode(mMISO,INPUT);
		pinMode(mMOSI,OUTPUT);
	}

	void Tle5012b_SPI::receiveConfig()
	{
		pinMode(mMISO,INPUT);
		pinMode(mMOSI,INPUT);
	}

	void Tle5012b_SPI::sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
	{
		uint32_t data_index = 0;
		//send via TX
		sendConfig();
		digitalWrite(mCS, LOW);

		beginTransaction(mSPISetting);
		for(data_index = 0; data_index < size_of_sent_data; data_index++)
		{
			received_data[0] = transfer16(sent_data[data_index] );
		}
		
		// receive via RX
		receiveConfig();
		delayMicroseconds(5);

		for(data_index = 0; data_index < size_of_received_data; data_index++)
		{
			received_data[data_index] = transfer16(0x0000);
		}
		endTransaction();

		digitalWrite(mCS, HIGH);
	}

#endif
