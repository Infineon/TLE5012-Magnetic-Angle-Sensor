/**
 * @file        gpio-wiced.hpp
 * @brief       WICED PAL for the GPIO
 * @date        May 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "gpio-wiced.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_WICED)

using namespace tle5012;

/**
 * @brief GPIO WICED default constructor
 */
GPIOWiced::GPIOWiced(wiced_gpio_t pin, wiced_gpio_config_t config, VLogic_t logic)
	: pin(pin), config(config), logic(logic)
{
}

/**
 * @brief GPIO WICED default constructor
 */
GPIOWiced::GPIOWiced() : pin(WICED_GPIO_1), config(INPUT_HIGH_IMPEDANCE), logic(POSITIVE)
{
}

/**
 * @brief GPIO WICED destructor
 */
GPIOWiced::~GPIOWiced()
{
	disable();
	deinit();
}

/**
 * @brief   Initializes the WICED GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if initialization error
 */
inline GPIOWiced::Error_t GPIOWiced::init()
{
	GPIOWiced::Error_t err = GPIOWiced::OK;
	if (WICED_SUCCESS != wiced_gpio_init(pin, config))
		err = GPIOWiced::INTF_ERROR;

	return err;
}

/**
 * @brief   Initializes the WICED GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if deinitialization error
 */
inline GPIOWiced::Error_t GPIOWiced::deinit()
{
	GPIOWiced::Error_t err = GPIOWiced::OK;
	if (WICED_SUCCESS != wiced_gpio_deinit(pin))
		err = GPIOWiced::INTF_ERROR;

	return err;
}

/**
 * @brief       Reads the WICED GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
inline GPIOWiced::VLevel_t GPIOWiced::read()
{
	return (VLevel_t)wiced_gpio_input_get(pin);
}

/**
 * @brief       Writes the WICED GPIO output voltage level
 * @param[in]   level  Voltage level
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline GPIOWiced::Error_t GPIOWiced::write(VLevel_t level)
{
	GPIOWiced::Error_t err = GPIOWiced::OK;

	if (GPIO_LOW == level)
	{
		if (WICED_SUCCESS != wiced_gpio_output_low(pin))
			err = GPIOWiced::INTF_ERROR;
	}
	else if (GPIO_HIGH == level)
	{
		if (WICED_SUCCESS != wiced_gpio_output_high(pin))
			err = GPIOWiced::INTF_ERROR;
	}

	return err;
}

/**
 * @brief       Enables the WICED output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline GPIOWiced::Error_t GPIOWiced::enable()
{
	GPIOWiced::Error_t err = GPIOWiced::OK;

	if (this->logic == POSITIVE)
	{
		if (WICED_SUCCESS != wiced_gpio_output_high(pin))
			err = GPIOWiced::INTF_ERROR;
	}
	else if (this->logic == NEGATIVE)
	{
		if (WICED_SUCCESS != wiced_gpio_output_low(pin))
			err = GPIOWiced::INTF_ERROR;
	}
	return err;
}

/**
 * @brief       Disables the WICED output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline GPIOWiced::Error_t GPIOWiced::disable()
{
	GPIOWiced::Error_t err = GPIOWiced::OK;

	if (this->logic == POSITIVE)
	{
		if (WICED_SUCCESS != wiced_gpio_output_low(pin))
			err = GPIOWiced::INTF_ERROR;
	}
	else if (this->logic == NEGATIVE)
	{
		if (WICED_SUCCESS != wiced_gpio_output_high(pin))
			err = GPIOWiced::INTF_ERROR;
	}
	return err;
}

#endif /** TLE5012_FRAMEWORK **/
