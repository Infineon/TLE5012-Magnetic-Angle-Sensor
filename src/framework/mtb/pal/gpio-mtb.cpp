/**
 * @file        gpio-mtb.hpp
 * @brief       MTB PAL for the GPIO
 * @date        Spt 2020
 * @copyright   Copyright (c) 2019-2020 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "gpio-mtb.hpp"

#if (TLE5012_FRAMEWORK == TLE5012_FRMWK_MTB)

using namespace tle5012;

/**
 * @brief GPIO MTB default constructor
 */
GPIOMtb::GPIOMtb(mtb_gpio_t pin, mtb_gpio_config_t config, VLogic_t logic)
	: pin(pin), config(config), logic(logic)
{
}

/**
 * @brief GPIO MTB default constructor
 */
GPIOMtb::GPIOMtb() : pin(MTB_GPIO_1), config(INPUT_HIGH_IMPEDANCE), logic(POSITIVE)
{
}

/**
 * @brief GPIO MTB destructor
 */
GPIOMtb::~GPIOMtb()
{
	disable();
	deinit();
}

/**
 * @brief   Initializes the MTB GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if initialization error
 */
inline GPIOMtb::Error_t GPIOMtb::init()
{
	GPIOMtb::Error_t err = GPIOMtb::OK;
	if (MTB_SUCCESS != mtb_gpio_init(pin, config))
		err = GPIOMtb::INTF_ERROR;

	return err;
}

/**
 * @brief   Initializes the MTB GPIO
 * @return  GPIO error code
 * @retval  OK if success
 * @retval  INTF_ERROR if deinitialization error
 */
inline GPIOMtb::Error_t GPIOMtb::deinit()
{
	GPIOMtb::Error_t err = GPIOMtb::OK;
	if (MTB_SUCCESS != mtb_gpio_deinit(pin))
		err = GPIOMtb::INTF_ERROR;

	return err;
}

/**
 * @brief       Reads the MTB GPIO voltage level
 * @return      GPIO voltage level
 * @retval      GPIO_LOW if voltage low
 * @retval      GPIO_HIGH if voltage high
 */
inline GPIOMtb::VLevel_t GPIOMtb::read()
{
	return (VLevel_t)mtb_gpio_input_get(pin);
}

/**
 * @brief       Writes the MTB GPIO output voltage level
 * @param[in]   level  Voltage level
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline GPIOMtb::Error_t GPIOMtb::write(VLevel_t level)
{
	GPIOMtb::Error_t err = GPIOMtb::OK;

	if (GPIO_LOW == level)
	{
		if (MTB_SUCCESS != mtb_gpio_output_low(pin))
			err = GPIOMtb::INTF_ERROR;
	}
	else if (GPIO_HIGH == level)
	{
		if (MTB_SUCCESS != mtb_gpio_output_high(pin))
			err = GPIOMtb::INTF_ERROR;
	}

	return err;
}

/**
 * @brief       Enables the MTB output according to the GPIO logic
 *              - Low if negative
 *              - High if positive
 * @return      GPIO interrupt event
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline GPIOMtb::Error_t GPIOMtb::enable()
{
	GPIOMtb::Error_t err = GPIOMtb::OK;

	if (this->logic == POSITIVE)
	{
		if (MTB_SUCCESS != mtb_gpio_output_high(pin))
			err = GPIOMtb::INTF_ERROR;
	}
	else if (this->logic == NEGATIVE)
	{
		if (MTB_SUCCESS != mtb_gpio_output_low(pin))
			err = GPIOMtb::INTF_ERROR;
	}
	return err;
}

/**
 * @brief       Disables the MTB output according to the GPIO logic
 *              - Low if positive
 *              - High if negative
 * @return      GPIO error code
 * @retval      OK if success
 * @retval      INTF_ERROR if error
 */
inline GPIOMtb::Error_t GPIOMtb::disable()
{
	GPIOMtb::Error_t err = GPIOMtb::OK;

	if (this->logic == POSITIVE)
	{
		if (MTB_SUCCESS != mtb_gpio_output_low(pin))
			err = GPIOMtb::INTF_ERROR;
	}
	else if (this->logic == NEGATIVE)
	{
		if (MTB_SUCCESS != mtb_gpio_output_high(pin))
			err = GPIOMtb::INTF_ERROR;
	}
	return err;
}

#endif /** TLE5012_FRAMEWORK **/
