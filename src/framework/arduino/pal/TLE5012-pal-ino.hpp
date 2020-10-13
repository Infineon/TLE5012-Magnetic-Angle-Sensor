/*!
 * \file        TLE5012-pal-ino.hpp
 * \name        TLE5012-pal-ino.hpp - Arduino Hardware Abstraction Layer
 * \author      Infineon Technologies AG
 * \copyright   2020 Infineon Technologies AG
 * \version     2.0.0
 * \ref         arduinoPal
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef TLE5012_PAL_INO_HPP_
#define TLE5012_PAL_INO_HPP_

#include "../../../config/tle5012-conf.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_ARDUINO)

/**
 * @addtogroup arduinoPal
 * @{
 */

#include <Arduino.h>
#include <SPI.h>
#include "../../../corelib/TLE5012b.hpp"
#include "gpio-arduino.hpp"
#include "timer-arduino.hpp"
#include "spic-arduino.hpp"

/**
 * @brief represents a basic TLE5012
 *
 * This class provides a simple API for connecting and controlling motors.
 * Each motor is assigned to a Tle5012 which acts as output driver. Calls to
 * Tle5012Motor instances are mapped to calls to Tle5012. Therefore, this
 * class does not bring new features, it does only provide further abstraction.
 *
 * @see Tle5012
 */
class TLE5012Ino: virtual public Tle5012b
{

	public:

		uint8_t mSpiNum;              //!< Number of used SPI channel

		/*!
		* Triggers an update in the register buffer. This function
		* should be triggered once before UPD registers where read as
		* it generates a snapshot of the UPD register values at trigger point
		*/
		void triggerUpdate();

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

};
/**
 * @}
 */

#endif /** TLE5012_FRAMEWORK **/
#endif /** TLE5012_PAL_INO_HPP_ **/