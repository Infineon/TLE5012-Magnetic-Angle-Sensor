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

/*!
* Triggers an update in the register buffer. This function
* should be triggered once before UPD registers where read as
* it generates a snapshot of the UPD register values at trigger point
*/

/*!
* Main SPI three wire communication functions for sending and receiving data
* @param sent_data pointer two 2*unit16_t value for one command word and one data word if something should be written
* @param size_of_sent_data the size of the command word default 1 = only command 2 = command and data word
* @param received_data pointer to data structure buffer for the read data
* @param size_of_received_data size of data words to be read
*/
void Tle5012b::sendReceiveSpi(uint16_t* sent_data, uint16_t size_of_sent_data, uint16_t* received_data, uint16_t size_of_received_data)
{
	uint32_t data_index = 0;
	//send via TX
	sBus->sendConfig();
	cs->disable();

	//beginTransaction
	for(data_index = 0; data_index < size_of_sent_data; data_index++)
	{
		sBus->transfer16(sent_data[data_index],received_data[0]);
	}
	
	// receive via RX
	sBus->receiveConfig();
	timer->delayMicro(TRIGGER_DELAY);

	for(data_index = 0; data_index < size_of_received_data; data_index++)
	{
		sBus->transfer16(0x0000,received_data[data_index]);
	}
	//endTransaction

	cs->enable();
}
