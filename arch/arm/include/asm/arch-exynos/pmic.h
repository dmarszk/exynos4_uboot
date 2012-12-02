/*
 * (C) Copyright 2011 Samsung Electronics Co. Ltd
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#ifndef __PMIC_H__
#define __PMIC_H__


#define MAX8952_ADDR            0xc0	// VDD_ARM - I2C0
#define MAX8649_ADDR            0xc0	// VDD_INT - I2C1
#define MAX8649A_ADDR           0xc4	// VDD_G3D - I2C0
#define MAX8997_ADDR            0xCC	// MAX8997 - I2C0
#define MAX77686_ADDR           0x12	// MAX77686 - I2C0
#define MAX77686_BUCK1OUT       0x11
#define MAX77686_BUCK2TV_DVS1   0x14
#define MAX77686_BUCK3TV_DVS1   0x1E
#define MAX77686_BUCK4TV_DVS1   0x28
#define MAX77686_BUCK5OUT       0x31
#define MAX8997_ID              0x00
#define MAX8997_BUCK1TV_DVS     0x19
#define MAX8997_BUCK2TV_DVS     0x22
#define MAX8997_BUCK3TV_DVS     0x2B
#define MAX8997_BUCK4TV_DVS     0x2D
#define MAX8997_LDO10CTRL       0x44
#define S5M8767_ADDR			0xCC	// S5M8767 - I2C0
#define PMIC_RTC_ADDR			0x0C //S5M8767 RTC subsystem - I2C0

#define CALC_MAXIM_BUCK1245_VOLT(x)     	( (x<650) ? 0 : ((x-650)/25) )
#define CALC_MAXIM_BUCK37_VOLT(x)       	( (x<750) ? 0 : ((x-750)/50) )
#define CALC_MAXIM_ALL_LDO(x)	        	( (x<800) ? 0 : ((x-800)/50) )
#define CALC_MAXIM77686_BUCK156789_VOLT(x)   	( (x<750) ? 0 : ((x-750)/50) )
#define CALC_MAXIM77686_BUCK234_VOLT(x) 	( (x<600) ? 0 : ((x-600)/12.5) )
#define CALC_MAXIM77686_LDO1267815_VOLT(x)	( (x<800) ? 0 : ((x-800)/25) )
#define CALC_MAXIM77686_ALL_LDO_VOLT(x)         ( (x<800) ? 0 : ((x-800)/50) )

#define CALC_S5M8767_BUCK234_VOLT(x)	( (x<600) ? 0 : ((x-600)/6.25) )
#define CALC_S5M8767_BUCK156_VOLT(x)	( (x<650) ? 0 : ((x-650)/6.25) )
#define CALC_S5M8767_LDO1267815_VOLT(x)	( (x<800) ? 0 : ((x-800)/25) )
#define CALC_S5M8767_ALL_LDO_VOLT(x)	( (x<800) ? 0 : ((x-800)/50) )

typedef enum
{
	PMIC_BUCK1=0,
	PMIC_BUCK2,
	PMIC_BUCK3,
	PMIC_BUCK4,
	PMIC_BUCK5,
}PMIC_RegNum;

extern void pmic_init(void);

#endif /*__PMIC_H__*/

