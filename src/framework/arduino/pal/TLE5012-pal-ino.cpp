/*!
 * \file        TLE5012-pal-ino.cpp
 * \name        TLE5012-pal-ino.cpp - Arduino library to control Infineon's DC Motor Control Shield with Tle5012
 * \author      Infineon Technologies AG
 * \copyright   2019 Infineon Technologies AG
 * \version     2.0.0
 * \brief       This file has to be included in projects that use Infineon's DC Motor Control Shield with TLE5012
 * \ref         arduinoPal
 *
 * SPDX-License-Identifier: MIT
 *
 */


#include "TLE5012-pal-ino.hpp"

	void Tle5012b::triggerUpdate()
	{
		sBus->sck->disable();
		sBus->mosi->enable();
		cs->disable();
		//grace period for register snapshot
		timer->delayMicro(TRIGGER_DELAY);
		cs->enable();
	}

	void Tle5012b::sendConfig()
	{
		pinMode(mMISO,INPUT);
		pinMode(mMOSI,OUTPUT);
	}

	void Tle5012b::receiveConfig()
	{
		pinMode(mMISO,INPUT);
		pinMode(mMOSI,INPUT);
	}

	void Tle5012b::sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
	{
		uint32_t data_index = 0;
		//send via TX
		sendConfig();
		cs->disable();

		sBus->init();
		for(data_index = 0; data_index < size_of_sent_data; data_index++)
		{
			sBus->transfer16(sent_data[data_index],received_data[0]);
		}
		
		// receive via RX
		receiveConfig();
		timer->delayMicro(TRIGGER_DELAY);

		for(data_index = 0; data_index < size_of_received_data; data_index++)
		{
			sBus->transfer16(0x0000,received_data[data_index]);
		}
		sBus->deinit();

		cs->enable();
	}
