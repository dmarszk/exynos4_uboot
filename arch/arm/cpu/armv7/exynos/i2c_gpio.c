/* I2C-GPIO driver for Exynos4.
 *
 * (C) Copyright 2012 Dominik Marszk <dmarszk@gmail.com>
 *
 * Based on pmic_hkdk4412.c
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <common.h>
#include <asm/arch/i2c_gpio.h>
#include <asm/arch/gpio.h>
#undef DEBUG

static int new_port_id = 0;

struct i2c_gpio_port
{
	enum GPIO_Id sda_port;
	enum GPIO_BitPos sda_pin;
	enum GPIO_Id scl_port;
	enum GPIO_BitPos scl_pin;
};
#define MAX_I2C_GPIO_PORTS 10

static struct i2c_gpio_port ports[MAX_I2C_GPIO_PORTS];

static	void			delay_func					(unsigned int us);

static	unsigned char	i2c_gpio_get_sda			(int port);
static	void			i2c_gpio_set_sda			(int port, unsigned char hi_lo);
static	void			i2c_gpio_set_clk			(int port, unsigned char hi_lo);
                                        	
static 	void			i2c_gpio_start				(int port);
static 	void			i2c_gpio_stop				(int port);
                                        	
static 	void			i2c_gpio_send_ack			(int port);
static 	void			i2c_gpio_send_noack			(int port);
static 	unsigned char	i2c_gpio_chk_ack			(int port);

static void 			i2c_gpio_write				(int port, uint8_t val);
static void 			i2c_gpio_read				(int port, uint8_t* val);                		                      
		  

int i2c_gpio_new_port(	enum GPIO_Id sda_port, enum GPIO_BitPos sda_pin,
						enum GPIO_Id scl_port, enum GPIO_BitPos scl_pin)
{
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	if(new_port_id == MAX_I2C_GPIO_PORTS)
	{
		printf("%s Error - maximum number of %d ports registered!\n", __func__, MAX_I2C_GPIO_PORTS);
		return -1;
	}
	ports[new_port_id].scl_port = scl_port;
	ports[new_port_id].scl_pin = scl_pin;
	ports[new_port_id].sda_port = sda_port;
	ports[new_port_id].sda_pin = sda_pin;
	GPIO_SetDataEach(sda_port, sda_pin, HIGH);
	GPIO_SetDataEach(scl_port, scl_pin, HIGH);
	GPIO_SetFunctionEach(sda_port, sda_pin, GPIO_OUTPUT);
	GPIO_SetFunctionEach(scl_port, scl_pin, GPIO_OUTPUT);
	GPIO_SetPullUpDownEach(scl_port, scl_pin, GPIO_PULL_NONE);
	GPIO_SetPullUpDownEach(sda_port, sda_pin, GPIO_PULL_NONE);
	printf("%s virtual channel %d registered\n", __func__, new_port_id);
	return new_port_id++;
}

static unsigned char i2c_gpio_get_sda(int port)
{
	return GPIO_GetDataEach(ports[port].sda_port, ports[port].sda_pin);
}

static void i2c_gpio_set_sda(int port, unsigned char hi_lo)
{
	GPIO_SetDataEach(ports[port].sda_port, ports[port].sda_pin, hi_lo);
}

static void i2c_gpio_set_clk(int port, unsigned char hi_lo)
{
	GPIO_SetDataEach(ports[port].scl_port, ports[port].scl_pin, hi_lo);
}

int i2c_gpio_write_reg(int port, uint8_t slave_addr, uint8_t reg, uint8_t val)
{
	unsigned char ack;
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	i2c_gpio_start(port);
	
	i2c_gpio_write(port, slave_addr & 0xFE);	// I2C WRITE mask

	if((ack = i2c_gpio_chk_ack(port)))
	{
	//	printf("%s: no addr ack\n", __func__);
		goto write_stop;
	}
	
	i2c_gpio_write(port, reg);
	
	if((ack = i2c_gpio_chk_ack(port)))
	{
	//	printf("%s: no data ack\n", __func__);
		goto write_stop;	
	}
	i2c_gpio_write(port, val);
	ack = i2c_gpio_chk_ack(port);

write_stop:
	i2c_gpio_stop(port);
	return ack;
}

int i2c_gpio_read_reg(int port, uint8_t slave_addr, uint8_t reg, uint8_t* val)
{
	unsigned char ack;
	(*val) = 0;

#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	i2c_gpio_start(port);
	
	i2c_gpio_write(port, slave_addr & 0xFE);	// I2C WRITE mask

	if((ack = i2c_gpio_chk_ack(port)))
	{
		printf("%s: no addr ack\n", __func__);
		goto read_stop;
	}
	
	i2c_gpio_write(port, reg);		
	if((ack = i2c_gpio_chk_ack(port)))
	{
		printf("%s: no reg_id ack\n", __func__);
		goto read_stop;
	}

	// Restart
	i2c_gpio_start(port);
	
	i2c_gpio_write(port, slave_addr | 0x1);	// I2C READ flag

	if((ack = i2c_gpio_chk_ack(port)))
	{
		printf("%s: no data ack\n", __func__);
		goto read_stop;
	}

	i2c_gpio_read(port, val);
	i2c_gpio_send_noack(port);

read_stop:
	i2c_gpio_stop(port);
	return ack;
}
		
static void i2c_gpio_write(int port, uint8_t val)
{	
	unsigned char cnt, mask;
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	for(cnt = 0, mask = 0x80; cnt < 8; cnt++, mask >>= 1)	{
		if(val & mask)
			i2c_gpio_set_sda(port, HIGH);
		else
			i2c_gpio_set_sda(port, LOW);
			
		i2c_gpio_set_clk(port, HIGH);
		delay_func(DELAY_TIME);
		i2c_gpio_set_clk(port, LOW);
		delay_func(DELAY_TIME);
	}
}

static void i2c_gpio_read(int port, uint8_t* val)
{
	unsigned char	cnt, mask;
#ifdef DEBUG
	printf("%s\n", __func__);
#endif	
	GPIO_SetFunctionEach(ports[port].sda_port, ports[port].sda_pin, GPIO_INPUT);
	delay_func(PORT_CHANGE_DELAY_TIME);

	for(cnt = 0, mask = 0x80, *val = 0; cnt < 8; cnt++, mask >>= 1)	{
		i2c_gpio_set_clk(port, HIGH);
		delay_func(DELAY_TIME);
		if(i2c_gpio_get_sda(port))
			*val |= mask;
		i2c_gpio_set_clk(port, LOW);
		delay_func(DELAY_TIME);
		
	}
	GPIO_SetFunctionEach(ports[port].sda_port, ports[port].sda_pin, GPIO_OUTPUT);
	delay_func(PORT_CHANGE_DELAY_TIME);
}

 
static void delay_func(unsigned int us)
{
	unsigned long i;

	for(i = 0; i < us; i++){
		i++;
		i--;
	}
}

static void i2c_gpio_start(int port)
{
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	// Setup SDA, CLK output High
	i2c_gpio_set_sda(port, HIGH);
	i2c_gpio_set_clk(port, HIGH);	
	delay_func(DELAY_TIME);
	// SDA low before CLK low
	i2c_gpio_set_sda(port, LOW);
	delay_func(DELAY_TIME);
	i2c_gpio_set_clk(port, LOW);
	delay_func(DELAY_TIME);
}

static void i2c_gpio_stop(int port)
{
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	// Setup SDA, CLK output low
	i2c_gpio_set_sda(port, LOW);
	i2c_gpio_set_clk(port, LOW);
	
	delay_func(DELAY_TIME);
	
	// SDA high after CLK high
	i2c_gpio_set_clk(port, HIGH);
	delay_func(DELAY_TIME);
	i2c_gpio_set_sda(port, HIGH);
	delay_func(DELAY_TIME);
}

static	void i2c_gpio_send_ack (int port)
{
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	// SDA Low
	i2c_gpio_set_sda(port, LOW);	delay_func(DELAY_TIME);
	i2c_gpio_set_clk(port, HIGH);	delay_func(DELAY_TIME);
	i2c_gpio_set_clk(port, LOW);	delay_func(DELAY_TIME);
}

static void i2c_gpio_send_noack (int port)
{
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	// SDA High
	i2c_gpio_set_sda(port, HIGH);	delay_func(DELAY_TIME);
	i2c_gpio_set_clk(port, HIGH);	delay_func(DELAY_TIME);
	i2c_gpio_set_clk(port, LOW);	delay_func(DELAY_TIME);
}

static unsigned char i2c_gpio_chk_ack (int port)
{
#ifdef DEBUG
	printf("%s\n", __func__);
#endif
	unsigned char count = 0, ret = 0;

	i2c_gpio_set_sda(port, LOW);		delay_func(DELAY_TIME);
	i2c_gpio_set_clk(port, HIGH);		delay_func(DELAY_TIME);

	GPIO_SetFunctionEach(ports[port].sda_port, ports[port].sda_pin, GPIO_INPUT);
	delay_func(PORT_CHANGE_DELAY_TIME);

	while(i2c_gpio_get_sda(port))	{
		if(count++ > 10000){
			ret = 1;
			break;
		}
		else
			delay_func(DELAY_TIME);	
	}

	i2c_gpio_set_clk(port, LOW);
	delay_func(DELAY_TIME);
	GPIO_SetFunctionEach(ports[port].sda_port, ports[port].sda_pin, GPIO_OUTPUT);
	delay_func(PORT_CHANGE_DELAY_TIME);
	
	if(ret)
		printf("%s: virtual channel %d no ack!!\n", __func__, port);

	return ret;
}