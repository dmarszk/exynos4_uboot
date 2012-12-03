/* I2C-GPIO driver for Exynos4.
 *
 * (C) Copyright 2012 Dominik Marszk <dmarszk@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
 
#ifndef __I2C_GPIO_H__
#define __I2C_GPIO_H__
#include <asm/arch/gpio.h>



#define	DELAY_TIME				1000
#define	PORT_CHANGE_DELAY_TIME	1000


#define	HIGH					1
#define	LOW						0


int i2c_gpio_new_port(	enum GPIO_Id sda_port, enum GPIO_BitPos sda_pin,
						enum GPIO_Id scl_port, enum GPIO_BitPos scl_pin);
/* Returns 0 in case of success, non-zero in case of failure. */
int i2c_gpio_write_reg(int port, uint8_t slave_addr, uint8_t reg, uint8_t val);
/* Returns 0 in case of success, non-zero in case of failure. */
int i2c_gpio_read_reg(int port, uint8_t slave_addr, uint8_t reg, uint8_t* val);
 
 
 
#endif /* __I2C_GPIO_H__ */
 
 