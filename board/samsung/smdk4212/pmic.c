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

#include <common.h>
#include <asm/arch/pmic.h>
#include <asm/arch/i2c.h>


void IIC7_ERead(unsigned char ChipId, unsigned char IicAddr, unsigned char* IicData)
{
	I2C_RecvEx(I2C7, ChipId, &IicAddr, 1, IicData, 1);
}

void IIC7_EWrite (unsigned char ChipId, unsigned char IicAddr, unsigned char IicData)
{
	I2C_SendEx(I2C7, ChipId, &IicAddr, 1, &IicData, 1);
}

void pmic_s5m8767_update_reg(uint8_t reg_id, uint8_t value, uint8_t mask)
{
	uint8_t read_val;
	value &= mask; //just for sanity	
	IIC7_ERead(S5M8767_ADDR, reg_id, &read_val);
	read_val &= ~mask;
	read_val |= value;	
	IIC7_EWrite(S5M8767_ADDR, reg_id, read_val);
}

void I2C_S5M8767_SetupBuck(PMIC_RegNum eRegNum, unsigned char ucVolLevel, unsigned char ucEnable)
{
	unsigned char reg_addr, reg_bitpos, reg_bitmask, vol_level;

	reg_bitpos = 0;
	reg_bitmask = 0xFF;
	
	if(eRegNum == PMIC_BUCK1)  // BUCK1
	{
		reg_addr = 0x33;
	}
	else if(eRegNum == PMIC_BUCK2)  // BUCK2
	{
		reg_addr = 0x35;
	}
	else if(eRegNum == PMIC_BUCK3)  //  BUCK3
	{
		reg_addr = 0x3E;
	}
	else if(eRegNum == PMIC_BUCK4)  // BUCK4
	{
		reg_addr = 0x47;
	}
	else if(eRegNum == PMIC_BUCK5) // BUCK5
	{
		reg_addr = 0x50;
	}
	else
	      while(1);

	vol_level = ucVolLevel & reg_bitmask ;
	IIC7_EWrite(S5M8767_ADDR, reg_addr, vol_level);
}
void pmic_max77686_print(void)
{	
#if 0
	u8 read_vol_arm;
	u8 read_vol_int;
	u8 read_vol_g3d;
	u8 read_vol_mif;
	u8 read_vol_mem;
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK2TV_DVS1, &read_vol_arm);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK3TV_DVS1, &read_vol_int);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK4TV_DVS1, &read_vol_g3d);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK1OUT, &read_vol_mif);
	IIC0_ERead(MAX77686_ADDR, MAX77686_BUCK5OUT, &read_vol_mem);
	
	printf("ARM: %dmV\t", ((unsigned int)(read_vol_arm >> 1) * 25) + 600);
	printf("INT: %dmV\t", ((unsigned int)(read_vol_int >> 1) * 25) + 600);
	printf("G3D: %dmV\n", ((unsigned int)(read_vol_g3d >> 1)* 25) + 600);
	printf("MIF: %dmV\t", ((unsigned int)(read_vol_mif & 0x3F) * 50) + 750);
	printf("MEM: %dmV\n", ((unsigned int)(read_vol_mem & 0x3F) * 50) + 750);
#endif
}

void pmic_max77686_init(void)
{
#if 0	
	/* set DVS1,2,3 as 0 by GPL0 */
	*((volatile unsigned int *)0x110000c0) = 0x11111111;
	*((volatile unsigned int *)0x110000c4) = 0x7;
	*((volatile unsigned int *)0x110000c4) = 0x0;
	*((volatile unsigned int *)0x110000c4) = 0x7;
	*((volatile unsigned int *)0x110000c4) = 0x0;
	*((volatile unsigned int *)0x110000c0) = 0x0;
	
		
	/* VDD_MIF */
	IIC0_EWrite(MAX77686_ADDR, 0x11, CALC_MAXIM77686_BUCK156789_VOLT(CONFIG_PM_VDD_MIF));
	/* VDD_ARM */
	IIC0_EWrite(MAX77686_ADDR, 0x14, CALC_MAXIM77686_BUCK234_VOLT(CONFIG_PM_VDD_ARM));
	/* VDD_INT */
	IIC0_EWrite(MAX77686_ADDR, 0x1E, CALC_MAXIM77686_BUCK234_VOLT(CONFIG_PM_VDD_INT));
	/* VDD_G3D */
	IIC0_EWrite(MAX77686_ADDR, 0x28, CALC_MAXIM77686_BUCK234_VOLT(CONFIG_PM_VDD_G3D));
#endif
}

void pmic_s5m8767_print(void)
{
	u8 read_data;
	printf("====================\n");
	printf("S5M8767 PMIC registers \n");
	printf("====================\n");
	IIC7_ERead(S5M8767_ADDR, 0, &read_data);
	printf("ID = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 0xE0, &read_data);
	printf("ONSRC = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 7, &read_data);
	printf("STATUS1 = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 8, &read_data);
	printf("STATUS2 = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 9, &read_data);
	printf("STATUS3 = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 1, &read_data);
	printf("IRQ1 = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 2, &read_data);
	printf("IRQ2 = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 3, &read_data);
	printf("IRQ3 = 0x%02x \n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 0xE1, &read_data);
	printf("PWROFFSRC = 0x%02x \n", read_data);
	
	IIC7_ERead(PMIC_RTC_ADDR, 0x1B, &read_data);
	printf("PMIC_RTC_WTSR_SMPL_REG = 0x%02x\n", read_data);
	
	IIC7_ERead(S5M8767_ADDR, 0xE, &read_data);
	printf("S5M8767_REG_BUCHG = 0x%02x\n", read_data);	
	
}

int is_ldo_1_2_6_7_8_15(uint8_t ldo_id)
{
	if (ldo_id <= 0xE && (1 << ldo_id) & 0x40E3 )
		return 1;
	return 0;
}

struct pmic_s5m8767_init_reg_entry
{
	uint8_t reg_id;
	uint8_t value;
	uint8_t mask;
};
struct pmic_s5m8767_init_ldo_val
{
	uint8_t en1;
	uint8_t en2;
	uint16_t voltage;
};
struct pmic_s5m8767_init_reg_entry pmic_s5m8767_init_data[] = {
	{0xE, 0x6F, 0},
	{0x5A, 0x58, 0},
	{0x5B, 0xB4, 0},
	{0xA, 0xE, 0xE},
	{0xFF, 0xFF, 0}
};
struct pmic_s5m8767_init_ldo_val pmic_s5m8767_init_ldos[29] =
{
  { 0x3, 0x3, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x3, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 0 },
  { 0, 0, 1800 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 1950 },
  { 0x3, 0x1, 0 },
  { 0x3, 0, 0 },
  { 0x3, 0x1, 1950 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x1, 0 },
  { 0x3, 0x3, 0 },
  { 0, 0, 0 },
  { 0, 0x1, 1800 },
  { 0, 0, 3300 },
  { 0, 0, 3300 },
  { 0, 0, 2800 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 0 },
  { 0, 0, 1500 },
  { 0, 0, 0 },
  { 0xFF, 0xFF, 0 }
};

void pmic_s5m8767_init(void)
{
	struct pmic_s5m8767_init_reg_entry* cur_reg;
	struct pmic_s5m8767_init_ldo_val* cur_ldo;
	uint8_t val;
	int ldo_id;
	int ldo_reg_id;
	cur_reg = pmic_s5m8767_init_data;
	while(cur_reg->reg_id != 0xFF)
	{
		val = cur_reg->value;
		if(cur_reg->mask)
		{
			IIC7_ERead(S5M8767_ADDR, cur_reg->reg_id, &val);
			val = ~cur_reg->mask;
			val |= cur_reg->value;
		}
		IIC7_EWrite(S5M8767_ADDR, cur_reg->reg_id, val);
		cur_reg++;
	}
	ldo_id = 0;
	cur_ldo = pmic_s5m8767_init_ldos;
	while(cur_ldo->en1 != 0xFF)
	{		
		if (ldo_id > 1) //after LDO2 there are LDO2_2 LDO2_3 LDO2_4, jump over them
			ldo_reg_id = ldo_id + 95;
		else
			ldo_reg_id = ldo_id + 92;
		if(cur_ldo->en1 == cur_ldo->en2) {
			if(is_ldo_1_2_6_7_8_15(ldo_id))
				pmic_s5m8767_update_reg(ldo_reg_id, CALC_S5M8767_LDO1267815_VOLT(cur_ldo->voltage), 0x3F);
			else				
				pmic_s5m8767_update_reg(ldo_reg_id, CALC_S5M8767_ALL_LDO_VOLT(cur_ldo->voltage), 0x3F);
		}
		else if(cur_ldo->voltage) {
		    if(is_ldo_1_2_6_7_8_15(ldo_id))
				pmic_s5m8767_update_reg(ldo_reg_id, (cur_ldo->en2 << 6) | CALC_S5M8767_LDO1267815_VOLT(cur_ldo->voltage), 0xFF);
			else				
				pmic_s5m8767_update_reg(ldo_reg_id, (cur_ldo->en2 << 6) | CALC_S5M8767_ALL_LDO_VOLT(cur_ldo->voltage), 0xFF);				
		}
		else {		
			pmic_s5m8767_update_reg(ldo_reg_id, (cur_ldo->en2 << 6), 0xC0);	
		}		
		cur_ldo++;
		ldo_id++;
	}
}

void pmic_print_info(void)
{	
	uint8_t pmic_id;
	IIC7_ERead(MAX8997_ADDR, 0, &pmic_id);
	if (pmic_id == 0x77) {
		printf("PMIC: MAX8997\n");

	} else if(pmic_id >= 0x0 && pmic_id <= 0x5) {
		printf("PMIC: S5M8767\n");
		pmic_s5m8767_print();
	} else {
		printf("PMIC: MAX77686\n");
		pmic_max77686_print();
	}
}

void pmic_init(void)
{
	u8 pmic_id;
	I2C_InitIp(7, 400*1000, 1000000);

#if 0
	/* read ID */
	IIC7_ERead(S5M8767_ADDR, 0, &pmic_id);
	if(pmic_id >= 0x0 && pmic_id <= 0x5) {
		pmic_s5m8767_init();
	} else {
		pmic_max77686_init();
	}
#endif
	//GPA1PUD |= (0x5<<4);	// restore reset value: Pull Up/Down Enable SCL, SDA
}
