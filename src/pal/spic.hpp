/**
 * @file        spic.hpp
 * @brief       PAL of the SPI cover
 * @date        June 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>

#ifndef SPIC_HPP_
#define SPIC_HPP_

/**
 * @addtogroup pal
 * @{
 */

class SPIC
{
	public:

		enum Error_t
		{
			OK          = 0,     /**< No error */
			INTF_ERROR  = -1,    /**< Interface error */
			CONF_ERROR  = -2,    /**< Configuration error */
			READ_ERROR  = -3,    /**< Read error */
			WRITE_ERROR = -4,    /**< Write error */
		};

		/**
		 * @brief       Initializes the SPIC
		 * @return      SPIC error code
		 * @retval      OK if success
		 * @retval      INIT_ERROR if initialization error
		 */
		virtual Error_t        init        () = 0;

		/**
		 * @brief       Deinitializes the SPIC
		 * @return      SPIC error code
		 * @retval      OK if success
		 * @retval      INIT_ERROR if deinitialization error
		 */
		virtual Error_t       deinit      () = 0;

		/**
		 * @brief           Send/receives data from SPI bus
		 * @param send      address or command to send 
		 * @param received  data from SPI bus
		 * @return          SPIC error code
		 * @retval          OK if success
		 * @retval          INIT_ERROR if transfer fails
		 */
		virtual Error_t       transfer(uint8_t send, uint8_t &received) = 0;

		/**
		 * @brief           Send/receives data from SPI bus
		 * @param send      address or command to send 
		 * @param received  data from SPI bus
		 * @return          SPIC error code
		 * @retval          OK if success
		 * @retval          INIT_ERROR if transfer fails
		 */
		virtual Error_t       transfer16(uint16_t send, uint16_t &received) = 0;

		Error_t checkErrorStatus();

		private:
		Error_t errorStatus;

};

/** @} */

#endif /** SPIC_HPP_ **/